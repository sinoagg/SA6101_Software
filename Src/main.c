#include "LoadPanel.h" 
#include <ansi_c.h>
#include <utility.h>
#include "asynctmr.h"
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include "main.h"

#include "MainPanelCb.h"
#include "Plot.h"
#include "Protocol.h"
#include "Graph.h"
#include "Cgs_mt.h"


unsigned char queryFlag = 1; 				//串口接收时要屏蔽数据查询  
const char IDquery[] = {0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};

const char CloseIDquery[] = {0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13};
char USART_RX_Buffer[40];   //接收 


extern int TimerID;

unsigned char measureComPort;				//Serial Com Number
unsigned char controlComPort;

unsigned char measUartTxBuf[32]={0};
unsigned char measUartRxBuf[1024]={0};

unsigned char SA11_Status=0;				//open comport status
unsigned char curveComplete;
int rows;
int curveIndex ;   
#define TXTCOLOR 0x3399FF
#define ANNOTATIONCOLOR 0x508EF4

void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void * callbackData); 

static int DeviceQuery();
static void RxDataToGraph(RxDataTypeDef *pRxData,float rxIdmeasured)
	{   
		char time[80];
		int str = Graph1.pCurveArray->time*0.001;
		sprintf(time,"%s%d","",str); 
		if(TestPara.testMode==SWEEP_DRAIN_VOL)
		{   
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX++)=pRxData->rxVdtest;								//get x, set pointer to the next data
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY++)=rxIdmeasured;			//get y, set pointer to the next data
			  
		}
		else if(TestPara.testMode==SWEEP_GATE_VOL)
		{
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX++)=pRxData->rxVgtest;						//get x, set pointer to the next data
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY++)=rxIdmeasured;
		}
		else if(TestPara.testMode==SWEEP_IV) 
		{
			*(Graph1.pCurveArray->pDotX++)=pRxData->rxVdtest;
			*(Graph1.pCurveArray->pDotY++)=rxIdmeasured;
		}
		else if(TestPara.testMode==NO_SWEEP_IT)	   
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, time);              
			*(Graph1.pCurveArray->pDotX++)=Graph1.pCurveArray->time*0.001;							//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep; 
			*(Graph1.pCurveArray->pDotY++)=rxIdmeasured; 
		}
		else if(TestPara.testMode == NO_SWEEP_RT)
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME,time);              
			*(Graph1.pCurveArray->pDotX++)=Graph1.pCurveArray->time*0.001;							//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep;
			*(Graph1.pCurveArray->pDotY++)=(TestPara.VdStart/rxIdmeasured)*0.001;   
			SetCtrlVal(hResultDispPanel, RESULTDISP_OHM,(TestPara.VdStart/rxIdmeasured)*0.001);
		
			if(((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001)>= 0)
			{																	 
				if((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001 >= Graph1.pGraphAttr->yAxisTail)
				{
					Graph1.pGraphAttr->yAxisTail=((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001)*1.005;   
					Graph1.pGraphAttr->yAxisHead=((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001)*0.991;  
					SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//设置 Y  轴的范围    
				}
				else if((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001 <= Graph1.pGraphAttr->yAxisHead )  
				{
					Graph1.pGraphAttr->yAxisTail=((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001)*1.005;   
					Graph1.pGraphAttr->yAxisHead=((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001)*0.991;  
					SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//设置 Y  轴的范围
				}
			
			}
	
		}
		else if(TestPara.testMode==ID_T)
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, time);
			*(Graph1.pCurveArray->pDotX++)= Graph1.pCurveArray->time*0.001;
			Graph1.pCurveArray->time+=TestPara.timeStep;
			*(Graph1.pCurveArray->pDotY++)=rxIdmeasured;  
		}

			
} 		
static void RxDataToTable(RxDataTypeDef *pRxData)
{
	//rows  table中行的标志来量，每条曲线从(rows+1)=1开始到最后一个点;一条曲线结束时置1 
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+1, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+2, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+1, rows+1), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //写入X值
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+2, rows+1), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //写入Y值 
	switch(TestPara.testMode)
	{    
		case SWEEP_DRAIN_VOL:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); 
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint(Graph1.plotCurveIndex*3+3, rows+1),(float)pRxData->rxVgtest);  //写入vg值  
			break;
		case SWEEP_GATE_VOL:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); 
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1),(float)pRxData->rxVdtest);  //写入vd值  
			break;
		case NO_SWEEP_IT:
		case NO_SWEEP_RT:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1),(float)pRxData->rxVdtest);  //写入vd值
			break;
		case ID_T:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1),(float)pRxData->rxVdtest);  //写入vd值
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, rows+1),(float)pRxData->rxVgtest);  //写入vg值
		   	break;
	  }


	   /*	int rowNum;									//表格新加行号  
		rowNum = rows+1;
		GetNumTableRows (hTablePanel, TABLE_DISTABLE, &rowNum); 										  		//得到当前行数 
		SetCtrlAttribute(hTablePanel,TABLE_DISTABLE, ATTR_FIRST_VISIBLE_ROW,rowNum);							//显示到最近添加的一行*/             
		rows++;  											  
										  
}
static void TestStop(RxDataTypeDef *pRxData,int portNumber)
{
	 
	DiscardAsyncTimer(TimerID);											//停止query定时器查询
	pRxData->rxStopSign=0;
	Graph1.pCurveArray->numOfPlotDots=0;
	curveComplete=1;
	rows=0;
	FlushInQ(portNumber);	   											//Clear input and output buffer
	FlushOutQ(portNumber);
	ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send RUN command to instrument via UART 
	Delay(1);
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0);   //恢复曲线属性设置  
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);        //禁用 停止按钮 //注释掉后可以在运行中点击停止     
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);        //恢复 开始按钮
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);       //恢复 保存按钮
	//GraphDeinit(&Graph1);												//内存释放在画图之后，如果在画图之前释放导致错误
	//GraphDeinit(&Graph2);
	
}

static void  DispVgTest(RxDataTypeDef *pRxData)  //IT、RT模式下Vg不显示
{
	  switch(TestPara.testMode)
		{
			case NO_SWEEP_IT:
			case NO_SWEEP_RT:
				SetCtrlVal(hResultDispPanel, RESULTDISP_VG,0); 
				break;
			case SWEEP_DRAIN_VOL:
			case SWEEP_GATE_VOL:
			case SWEEP_IV:
			case ID_T:
				SetCtrlVal(hResultDispPanel, RESULTDISP_VG, pRxData->rxVgtest); 
				break;
		}
}

static void AddGraphAnnotations(RxDataTypeDef *pRxData,float rxIdmeasured)
{
	 
	 if(TestPara.testMode==SWEEP_DRAIN_VOL)
	 {
		 char curve[80];
		 sprintf(curve,"%s%d","Vg=",pRxData->rxVgtest);
		 AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve ,-65,-25);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_BGCOLOR, VAL_RED);
		 ProcessDrawEvents();
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YAXIS, VAL_LEFT_YAXIS);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XAXIS, VAL_BOTTOM_XAXIS); 
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_LINE_COLOR, ANNOTATIONCOLOR);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_FONT, VAL_MENU_FONT);
		 ProcessDrawEvents(); 
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVdtest));	

	 } else if(TestPara.testMode==SWEEP_GATE_VOL)
	 {
		 char curve[80];
		 sprintf(curve,"%s%d","Vd=",pRxData->rxVdtest);
		 AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve   ,-65,-25);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_BGCOLOR, VAL_DK_MAGENTA);
		 ProcessDrawEvents();
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YAXIS, VAL_LEFT_YAXIS);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XAXIS, VAL_BOTTOM_XAXIS); 
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_LINE_COLOR, ANNOTATIONCOLOR);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_FONT, VAL_MENU_FONT);
		 //SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_ARROW_STYLE, VAL_NONE); //设置箭头样式
		 ProcessDrawEvents(); 
		SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVgtest));	
	 }
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YVALUE,(double)rxIdmeasured);
	 
     curveIndex++;
}


void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData)
{

	queryFlag = 0;     

	int rxNum=0;																//串口收到字节数
	int i=0;																	//处理接收帧数
	RxDataTypeDef RxData;
	RxData.rxStopSign=0x00;
    float rxIdmeasured=0;
	rxNum = GetInQLen(portNumber);  											//读取串口中发送来的数据数量
	if(rxNum>1024) rxNum=1024;													//防止超过内存范围
	rxNum-=rxNum%MEASURE_UART_RX_LEN;											//只读取接收字符组整数倍的数据，不读零散数据
	ComRd(portNumber, (char *)measUartRxBuf, rxNum);							//Read UART Buffer to local buffer at one time
	int curveNum = 0;
	curveNum = Graph1.numOfCurve;
	int log; 
	while(rxNum>=MEASURE_UART_RX_LEN)
	{	
		GetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_LINEAR, ATTR_CTRL_INDEX,&log);
		ProtocolGetData(measUartRxBuf+i*MEASURE_UART_RX_LEN, &RxData);			//get data from uart buffer
		SetCtrlVal(hResultDispPanel, RESULTDISP_VD, RxData.rxVdtest);
		DispVgTest(&RxData);
		(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;									//number of dots to plot increase
		if(log==1)
		{
		 	rxIdmeasured=log10(RxData.rxIdmeasured.num_float);	
		}
		else
		{
			rxIdmeasured = RxData.rxIdmeasured.num_float;  
		} 
		SetCtrlVal(hResultDispPanel, RESULTDISP_IDS,rxIdmeasured);        
		RxDataToGraph(&RxData,rxIdmeasured);
		RxDataToTable(&RxData);
		rxNum-=MEASURE_UART_RX_LEN;
		i++; 
	}
		PlotCurve1(&Graph1, hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex,rxIdmeasured);
		SetGraph_Axis(hGraphPanel,GRAPHDISP_GRAPH1,&Graph1,TestPara.testMode);
		switch(TestPara.testMode)
		{
			case NO_SWEEP_IT:
			case NO_SWEEP_RT:
			case SWEEP_IV:
				 if((RxData.rxStopSign==0x01) || (Graph1.pCurveArray->numOfTotalDots == Graph1.pCurveArray->numOfPlotDots))
				 	 TestStop(&RxData,portNumber);
				break;
			case SWEEP_DRAIN_VOL:
			case SWEEP_GATE_VOL:
				if((RxData.rxStopSign == 0x01)&&(Graph1.plotCurveIndex +1 == Graph1.numOfCurve))//实验结束
				{
					AddGraphAnnotations(&RxData,rxIdmeasured); 
					TestStop(&RxData,portNumber);
				}
				else if(RxData.rxStopSign == 0x01)	  //一条曲线结束
				{   
					AddGraphAnnotations(&RxData,rxIdmeasured);                                 
					curveComplete=1; 
					rows=1;		                      // 第二条曲线开始 大于0的任意值
				
					DiscardAsyncTimer(TimerID);       //第一条线之后的每条线结束时关闭定时器
				}
				break;

		
		}  

	  queryFlag = 1;     

}	
	

void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void* callbackData)
{

	queryFlag = 0;														//接收时屏蔽查询，不在查询数据
	int rxNum;																							  
	Rx_CGS_DataTypeDef Rx_CGS_Data;
	Rx_CGS_Data.environment_temp = 0;
	Rx_CGS_Data.humidity = 0;
	Rx_CGS_Data.pressure = 0;
	rxNum = GetInQLen(controlComPort);  								//读取串口中发送来的数据数量
	if(rxNum>500) rxNum=500;											//防止超过内存范围
	while(rxNum>=15)
	{	
		if(Graph1.pCurveArray->numOfPlotDots >= 1)
		{
			ComRd(controlComPort, (char *)meas_CGS_UartRxBuf, 15);
			ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);			// 从串口中取出环境测量参数
		
			*(Graph2.pCurveArray->pDotX++) = Graph1.pCurveArray->numOfPlotDots-1;
			*((Graph2.pCurveArray + 1)->pDotX++) = Graph1.pCurveArray->numOfPlotDots-1; 
			*((Graph2.pCurveArray + 2)->pDotX++) = Graph1.pCurveArray->numOfPlotDots-1; 
		
		    *(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 				 //环境湿度      
			*((Graph2.pCurveArray + 1)->pDotY++) = Rx_CGS_Data.environment_temp;		 //环境温度     
			*((Graph2.pCurveArray + 2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //压强
		
			Graph2.pCurveArray->numOfDotsToPlot++;  
			(Graph2.pCurveArray +1)->numOfDotsToPlot++;
			(Graph2.pCurveArray +2)->numOfDotsToPlot++;
		}
		else
		{
		FlushInQ(controlComPort);	   											
		FlushOutQ(controlComPort);
		}
		rxNum -=15; 
	}
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_TEMPERATURE, Rx_CGS_Data.environment_temp);			//显示温度   
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_HUMIDITY,  Rx_CGS_Data.humidity);					//显示湿度     
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_PRESSURE, Rx_CGS_Data.pressure*0.001);		 		//显示压强
	PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);//画曲线2图
	
	FlushInQ(controlComPort);	   											
	FlushOutQ(controlComPort);
		
	queryFlag = 1;																//接收时屏蔽查询，不在查询数据 

		
}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */

	//measureComPort=argc;		//pass measureComPort variable
	DeviceQuery();	  
	//measureComPort=9;

//	measureComPort=2;
	controlComPort=2;

	if(CheckPortStatus(measureComPort, MEASURE_UART_RX_LEN, MeasureComCallback)<0) return -1;
	//if(CheckPortStatus(controlComPort)<0) SA11_Status=0;
	//else SA11_Status=1;
	
	LoadInitPanel(); 
	CheckPortStatus(controlComPort, 15, CtrlComCallback); //controlComPort
	RunUserInterface();
	CloseCom(measureComPort);
	
	if(SA11_Status==1) CloseCom(controlComPort);
	DiscardPanel (hMainPanel);
	//CmtReleaseThreadPoolFunctionID(DEFAULT_THREAD_POOL_HANDLE, threadID);
	return 0;
}

static int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFunc)(int, int, void*))
{
	int status;
	status = OpenComConfig(portNumber, "", 115200, 0, 8, 1, 1024, 1024);	   //Config and Connect serial port
	if(status != 0) 
	{
		MessagePopup("Error","Device unconnected.");
		return -1;
	}
	else
	{
		InstallComCallback (portNumber, LWRS_RECEIVE, uartRxLen, 0, pFunc, 0);   //binding Callback function to serial input data 18 bytes received will calling for an interrupt
		SetCTSMode(portNumber, LWRS_HWHANDSHAKE_OFF);
		FlushInQ(portNumber);	   														//Clear input and output buffer
		FlushOutQ(portNumber);
		return 0;
	}
}

static int DeviceQuery()
{
	unsigned char i; 
	int b, strLen;
	for(i = 1; i<=10; i++)
		{
			SetBreakOnLibraryErrors (0);
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 30, 30);  //设置和打开串口 
		    if(b<0 )
			{
				
			}else
			{	
			    ComWrt(i, IDquery, 30);//发送查询指令
				Delay(3);
				strLen = GetInQLen (i);
				ComRd (i,USART_RX_Buffer,strLen);
				if((USART_RX_Buffer[1]== '6') && (USART_RX_Buffer[2] == '1') &&  
				(USART_RX_Buffer[3] == '0') && (USART_RX_Buffer[4]== '1'))
				{
					measureComPort = i;
					FlushInQ(measureComPort);	   														//Clear input and output buffer
					FlushOutQ(measureComPort);
					CloseCom (measureComPort);
					break;
				}
				else
				{
					CloseCom(i);
				}
				SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);   //无硬件交互
			}
       }
	return 0;
}

