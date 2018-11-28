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


unsigned char measure_Uart_Flag = 1; 				//电学测量串口接收时要屏蔽数据查询 
unsigned char control_Uart_Flag = 1; 				//环境参数串口接收时要屏蔽数据查询

const char IDquery1[] = {0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};
const char IDquery2[] = {0x11, 0x03, 0x00, 0x02, 0x00, 0x05, 0x26, 0x99};

const char CloseIDquery[] = {0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13};

char USART_RX_Buffer[50];   //接收 



extern int TimerID;

unsigned char measureComPort;				//Serial Com Number
unsigned char controlComPort;

unsigned char measUartTxBuf[32]={0};
unsigned char measUartRxBuf[1024]={0};


unsigned char curveComplete;
int rows;         //graph1
int curveIndex ;  //注释
int graphrows;    //graph2
int x2 = 0;
float ohm;
#define TXTCOLOR 0x3399FF
#define ANNOTATIONCOLOR 0x508EF4

void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void * callbackData); 


static void RxDataToGraph(RxDataTypeDef *pRxData,float rxIdmeasured)

{   

		if(TestPara.testMode==SWEEP_DRAIN_VOL)
		{   
			SetCtrlVal(hResultDispPanel, RESULTDISP_VG, pRxData->rxVgtest);  
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX++)=pRxData->rxVdtest;		//get x, set pointer to the next data
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY++)=rxIdmeasured;			//get y, set pointer to the next data
			  
		}
		else if(TestPara.testMode==SWEEP_GATE_VOL)
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_VG, pRxData->rxVgtest);  
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

			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, (Graph1.pCurveArray->time)*0.001);              
			*(Graph1.pCurveArray->pDotX++)=(Graph1.pCurveArray->time)*0.001;							//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep; 
			*(Graph1.pCurveArray->pDotY++)=rxIdmeasured; 
		}
		else if(TestPara.testMode == NO_SWEEP_RT)
		{

			ohm = (TestPara.VdStart/rxIdmeasured)*0.001; 
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME,(Graph1.pCurveArray->time)*0.001);                        
			*(Graph1.pCurveArray->pDotX++)=(Graph1.pCurveArray->time)*0.001;          						//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep;
			*(Graph1.pCurveArray->pDotY++)=ohm;   
			SetCtrlVal(hResultDispPanel, RESULTDISP_OHM,ohm);
			if( Graph1.pCurveArray->numOfPlotDots < 1)
			{  	if(ohm >= Graph1.pGraphAttr->yAxisTail )
					{
						Graph1.pGraphAttr->yAxisTail=ohm*1.0001;
						Graph1.pGraphAttr->yAxisHead=ohm*0.9999;
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//设置 Y  轴的范围
					} 		    
					else if(ohm <=Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=ohm*0.9999;
						Graph1.pGraphAttr->yAxisTail=ohm*1.0001; 
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//设置 Y  轴的范围
					}
				   
			}
			else
			{
				if(ohm >= Graph1.pGraphAttr->yAxisTail )
					{
						Graph1.pGraphAttr->yAxisTail=ohm*1.0001;   
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//设置 Y  轴的范围
					} 		    
					else if(ohm <=Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=ohm*0.9999;
					    SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//设置 Y  轴的范围
					}
				  
				
			}
		}
		else if(TestPara.testMode==ID_T)
		{

			SetCtrlVal(hResultDispPanel, RESULTDISP_VG, pRxData->rxVgtest);  
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, (Graph1.pCurveArray->time)*0.001);
			*(Graph1.pCurveArray->pDotX++)= (Graph1.pCurveArray->time)*0.001;
			Graph1.pCurveArray->time+=TestPara.timeStep;
			*(Graph1.pCurveArray->pDotY++)=rxIdmeasured;  
		}

			
} 		
static void RxDataToTable(RxDataTypeDef *pRxData)
{
	//rows  table中行的标志来量，每条曲线从(rows+1)=1开始到最后一个点;一条曲线结束时置1 
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //写入X值
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //写入Y值 
	switch(TestPara.testMode)
	{    
		case SWEEP_DRAIN_VOL:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); 
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint(Graph1.plotCurveIndex*6+3, rows),(float)pRxData->rxVgtest);  //写入vg值  
			break;
		case SWEEP_GATE_VOL:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); 
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+3, rows),(float)pRxData->rxVdtest);  //写入vd值  
			break;
		case NO_SWEEP_IT:
		case NO_SWEEP_RT:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows),(float)pRxData->rxVdtest);  //写入vd值
			break;
		case ID_T:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows),(float)pRxData->rxVdtest);  //写入vd值
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, rows),(float)pRxData->rxVgtest);  //写入vg值
		   	break;
	  }


	  rows++;      
	   /*	int rowNum;									//表格新加行号  
		rowNum = rows+1;
		GetNumTableRows (hTablePanel, TABLE_DISTABLE, &rowNum); 										  		//得到当前行数 
<<<<<<< HEAD
		SetCtrlAttribute(hTablePanel,TABLE_DISTABLE, ATTR_FIRST_VISIBLE_ROW,rowNum);							//显示到最近添加的一行*/ 

}


static void AddGraphAnnotations(RxDataTypeDef *pRxData,float rxIdmeasured)
{
	 
	 if(TestPara.testMode==SWEEP_DRAIN_VOL)   //idvd
	 {
		 char curve[80];
		 sprintf(curve,"%s%d","Vg=",pRxData->rxVgtest);
		 if (TestPara.VdStart>TestPara.VdStop)
		 	AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve ,20,-20);
		 else 
			AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve ,-55,25);          	 
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_BGCOLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor/*VAL_RED*/);   // 注释背景色
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_COLOR,VAL_WHITE);  //  注释字体色
		 ProcessDrawEvents();
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YAXIS, VAL_LEFT_YAXIS);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XAXIS, VAL_BOTTOM_XAXIS); // pGraph->pCurveArray->pCurveAttr->lineColor
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_LINE_COLOR,(Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor);//注释连线色
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_FONT, VAL_MENU_FONT);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_GLYPH_STYLE, VAL_SOLID_CIRCLE);	//实心圆
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_GLYPH_COLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor); //注释远点颜色
		 
		 //SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_COLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor);
		 ProcessDrawEvents(); 
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVdtest));	

	 } else if(TestPara.testMode==SWEEP_GATE_VOL)
	 {
		 char curve[80];
		 sprintf(curve,"%s%d","Vd=",pRxData->rxVdtest);
		 if (TestPara.VgStart>TestPara.VgStop)
		 	AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve ,20,-20);
		 else 
			AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve ,-55,15);     
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_BGCOLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor/*VAL_RED*/);   // 注释背景色
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_COLOR,VAL_WHITE);  //  注释字体色 
		 ProcessDrawEvents();
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YAXIS, VAL_LEFT_YAXIS);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XAXIS, VAL_BOTTOM_XAXIS); 
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_LINE_COLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_FONT, VAL_MENU_FONT);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_GLYPH_STYLE, VAL_SOLID_CIRCLE);	//实心圆
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_GLYPH_COLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor); //注释远点颜色
		 //SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_ARROW_STYLE, VAL_NONE); //设置箭头样式
		 ProcessDrawEvents(); 
		SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVgtest));	
	 }
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YVALUE,(double)rxIdmeasured);
	 
     curveIndex++;
}


static void TestStop(RxDataTypeDef *pRxData,int portNumber)
{
	
	ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send RUN command to instrument via UART
	Delay(1);
	DiscardAsyncTimer(TimerID);											//停止query定时器查询
	pRxData->rxStopSign=0;
	Graph1.pCurveArray->numOfPlotDots=0;
	Graph2.pGraphAttr->xAxis= 0;
	Graph2.pGraphAttr->xAxisHead=0;
	curveComplete=1;
	//rows=0;
	FlushInQ(portNumber);	   											//Clear input and output buffer
	FlushOutQ(portNumber);
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0);   //恢复曲线属性设置  
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);        //禁用 停止按钮 //注释掉后可以在运行中点击停止     
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);        //恢复 开始按钮
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);       //恢复 保存按钮
	//GraphDeinit(&Graph1);												//内存释放在画图之后，如果在画图之前释放导致错误
	//GraphDeinit(&Graph2);
	
}



void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData)
{

	measure_Uart_Flag = 0;     
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
		ProtocolGetData(measUartRxBuf+i*MEASURE_UART_RX_LEN, &RxData);			//get data from uart buffer
		SetCtrlVal(hResultDispPanel, RESULTDISP_VD, RxData.rxVdtest);
		(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase
		 GetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_LINEAR, ATTR_CTRL_INDEX,&log);  
		 if(log==1)   //log or Linear
			rxIdmeasured=log10(RxData.rxIdmeasured.num_float);
		 else
			rxIdmeasured = RxData.rxIdmeasured.num_float; 
		SetCtrlVal(hResultDispPanel, RESULTDISP_IDS,rxIdmeasured);        
		RxDataToGraph(&RxData,rxIdmeasured);
		RxDataToTable(&RxData);
		rxNum-=MEASURE_UART_RX_LEN;
		i++; 
	}
		PlotCurve1(&Graph1, hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex,rxIdmeasured);
		Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 	//得到曲线的属性      
		SetGraphX_Axis(hGraphPanel,GRAPHDISP_GRAPH1,&Graph1);
		switch(TestPara.testMode)
		{
			case NO_SWEEP_IT:
			case NO_SWEEP_RT:
			case SWEEP_IV:
			case ID_T:
				 if((RxData.rxStopSign==0x01) || (Graph1.pCurveArray->numOfTotalDots <= Graph1.pCurveArray->numOfPlotDots))//大于等于0，
					 
				 	 TestStop(&RxData,portNumber);
				break;
			case SWEEP_DRAIN_VOL:
			case SWEEP_GATE_VOL:
				if((RxData.rxStopSign == 0x01)&&(Graph1.plotCurveIndex +1 == Graph1.numOfCurve))//实验结束
				{   
					AddGraphAnnotations(&RxData,rxIdmeasured); 
				    //control_Uart_Flag=0;
					TestStop(&RxData,portNumber);
				}
				else if(RxData.rxStopSign == 0x01)	 											 //一条曲线结束
				{   
					AddGraphAnnotations(&RxData,rxIdmeasured);   
					curveComplete=1; 
					Graph2.pGraphAttr->xAxis = 0;
					Graph2.pGraphAttr->xAxisHead=0;
					x2=0;
					rows=2;		                      // 第二条曲线开始 大于0的任意值
					graphrows=2;
					GraphDeinit(&Graph2); 
					GraphInit(hGraphPanel,0, 3, Graph1.pCurveArray->numOfTotalDots+3, &Graph2); 
					DiscardAsyncTimer(TimerID);       //第一条线之后的每条线结束时关闭定时器
					
					
				}
				break;
		}  
	  measure_Uart_Flag = 1;     
}	
	
static void Rx_CGS_DataToTable(Rx_CGS_DataTypeDef* Rx_CGS_Data)
{
	int temp,hum,press;
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_TEMPTER,&temp); 
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_HUMIDITY,&hum); 
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_PRESSURE,&press); 

	switch(TestPara.testMode)
	{
		case SWEEP_DRAIN_VOL:
		case SWEEP_GATE_VOL :
		case NO_SWEEP_IT:
		case NO_SWEEP_RT:
		if(temp)
		{
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+4, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+4, graphrows),(float)Rx_CGS_Data->environment_temp) ;
	
		}
		if(hum)
		{
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+5, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+5, graphrows),(float)Rx_CGS_Data->humidity); 
		}
		if(press)
		{
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+6, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	    	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+6, graphrows),(float)Rx_CGS_Data->pressure); 
		}
		break;
		case SWEEP_IV:
			 if(temp)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, graphrows),(float)Rx_CGS_Data->environment_temp) ;
	
			}
			if(hum)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, graphrows),(float)Rx_CGS_Data->humidity); 
			}
			if(press)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+5, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
		    	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+5, graphrows),(float)Rx_CGS_Data->pressure); 
			}
			break;
		case ID_T:
			 if(temp)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+5, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+5, graphrows),(float)Rx_CGS_Data->environment_temp) ;
	
			}
			if(hum)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+6, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+6, graphrows),(float)Rx_CGS_Data->humidity); 
			}
			if(press)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+7, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
		    	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+7, graphrows),(float)Rx_CGS_Data->pressure); 
			}
			break;
		
	}

	graphrows++;        
	

}
void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void* callbackData)
{


	control_Uart_Flag = 0;														//接收时屏蔽查询，不在查询数据
	int rxNum;
	int i,j;
	Rx_CGS_DataTypeDef Rx_CGS_Data;
	Rx_CGS_Data.environment_temp = 0;
	Rx_CGS_Data.humidity = 0;
	Rx_CGS_Data.pressure = 0;	 //初始化
	rxNum = GetInQLen(controlComPort);  								//读取串口中发送来的数据数量
	if(rxNum>500) rxNum=500;											//防止超过内存范围
	while(rxNum>=15)
	{	
		if((Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots >0)
		{
			ComRd(controlComPort, (char *)meas_CGS_UartRxBuf, 15);
			ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);			//从串口中取出环境测量参数
			
			
			switch(TestPara.testMode)
			{
				case SWEEP_DRAIN_VOL:
				case SWEEP_GATE_VOL :
				case SWEEP_IV:
					j = (Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots - x2;   //j=>插入缺少点数
					for(i = 0; i<=j; i++)
					{

						*(Graph2.pCurveArray->pDotX++) = x2;
						*((Graph2.pCurveArray +1)->pDotX++) = x2; 
						*((Graph2.pCurveArray +2)->pDotX++) = x2; 
				
					    *(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 				 //环境湿度      
						*((Graph2.pCurveArray+1)->pDotY++) = Rx_CGS_Data.environment_temp;		 //环境温度     
						*((Graph2.pCurveArray+2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //压强
				
						 Graph2.pCurveArray->numOfDotsToPlot++;  
						(Graph2.pCurveArray +1)->numOfDotsToPlot++;
						(Graph2.pCurveArray +2)->numOfDotsToPlot++;
						Rx_CGS_DataToTable(&Rx_CGS_Data);
						x2++;
					}
					break;
				case NO_SWEEP_IT:
				case NO_SWEEP_RT:
				case ID_T: 
					j = (Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots - Graph2.pCurveArray->numOfPlotDots;   //j=>插入缺少点数    
					for(i = 0; i<=j; i++)
					{
	
						*(Graph2.pCurveArray->pDotX++) = Graph2.pGraphAttr->xAxis* TestPara.timeStep*0.001;	
						*((Graph2.pCurveArray +1)->pDotX++) = Graph2.pGraphAttr->xAxis* TestPara.timeStep*0.001;	 
						*((Graph2.pCurveArray +2)->pDotX++) =Graph2.pGraphAttr->xAxis* TestPara.timeStep*0.001;	
						 Graph2.pGraphAttr->xAxis++;          
						*(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 				 //环境湿度      
						*((Graph2.pCurveArray+1)->pDotY++) = Rx_CGS_Data.environment_temp;		 //环境温度     
						*((Graph2.pCurveArray+2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //压强

						 Graph2.pCurveArray->numOfDotsToPlot++;  
						(Graph2.pCurveArray +1)->numOfDotsToPlot++;
						(Graph2.pCurveArray +2)->numOfDotsToPlot++;
						Rx_CGS_DataToTable(&Rx_CGS_Data);
					
					}
					break;
				 }
		
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
	PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);											//画曲线2图
	Graph2.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph2.graphIndex,Graph2.plotCurveIndex); 	//得到曲线的属性
	SetGraphX_Axis(hGraphPanel,GRAPHDISP_GRAPH2,&Graph2);        
	control_Uart_Flag = 1;	
}
int main (int argc, char *argv[])
{
	int SA11_UART_Status=0;				//open comport status 
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	
	DeviceQuery();																		//判断设备对应的串口是否连接成功
		if(CheckPortStatus(measureComPort, MEASURE_UART_RX_LEN, MeasureComCallback)<0)
		{
			SA11_UART_Status=0;															//串口打开失败
			MessagePopup("Error","Failed to open the serial port of electrical measuring equipment"); 
			//要想打开软件，需要禁用此串口的操作命令
		}
		else 
		{
			SA11_UART_Status=1;															//串口打开成功  
		}
		if(CheckPortStatus(controlComPort, 15, CtrlComCallback)<0)						//判断环境测量设备对应的串口是否连接成功
		{
			control_Uart_Flag = 0;
			SA11_UART_Status=SA11_UART_Status + 0;     
			MessagePopup("Error","Failed to open the serial port of the environmental measuring equipment.Please check the communication line "); 
		}
		else
		{
			SA11_UART_Status=SA11_UART_Status + 2; 
		}
	
	LoadInitPanel(); 
	RunUserInterface();
	
		if(SA11_UART_Status==1)				//如果电学设备打开的话，关闭软件时需要关闭对应的串口。用户不使用电学测量设备时就没有打开，所以就不用关闭。
		{
				CloseCom(measureComPort);
		}
		if(SA11_UART_Status==2)				//如果环境设备打开的话，关闭软件时需要关闭对应的串口。用户不使用环境测量设备时就没有打开，所以就不用关闭。
		{
				CloseCom(controlComPort);
		}
		if(SA11_UART_Status==3)				//如果电学和环境的测量设备都打开的话，结束时需要同时关闭
		{
			CloseCom(controlComPort);
			CloseCom(measureComPort);
		}
		
	DiscardPanel (hMainPanel);
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
		FlushInQ(portNumber);	   			 											//Clear input and output buffer
		FlushOutQ(portNumber);
		return 0;
	}
}

void DeviceQuery()
{
	unsigned char i;
	char USART_RX_Buffer1[40];   //接收
	char USART_RX_Buffer2[40];   //接收
	int b,strLen;
	for(i = 1; i<=10; i++)
		{
			SetBreakOnLibraryErrors (0);
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 30, 30);  //设置和打开串口 
		    if(b<0 )
			{
				
			}else
			{	
			    ComWrt(i, IDquery1, 30);							//发送查询指令
				Delay(3);
				strLen = GetInQLen (i);
				ComRd (i,USART_RX_Buffer1,strLen);
				if((USART_RX_Buffer1[1]== '6') && (USART_RX_Buffer1[2] == '1') && (USART_RX_Buffer1[3] == '0') && (USART_RX_Buffer1[4]== '1'))
				{
					measureComPort = i;							
					FlushInQ(measureComPort);	   				//Clear input and output buffer
					FlushOutQ(measureComPort);
					CloseCom (measureComPort);
					break;
				}
				else
				{
					CloseCom(i);
				}

				SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//无硬件交互
			}
       }
	   
	   	for(i = 1; i<=10; i++)
		{
			SetBreakOnLibraryErrors (0);
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 30, 30);  //设置和打开串口 
		    if(b<0 )
			{
				
			}else
			{	
			    ComWrt(i, IDquery2, 8);							//发送查询指令
				Delay(3);
				strLen = GetInQLen (i);
				ComRd (i,USART_RX_Buffer2,strLen);
				if((USART_RX_Buffer2[0]== 0x11) && (USART_RX_Buffer2[1] == 0x03) && (USART_RX_Buffer2[2] == 0x0a))
				{
					controlComPort = i;							
					FlushInQ(controlComPort);	   				//Clear input and output buffer
					FlushOutQ(controlComPort);
					CloseCom (controlComPort);
					break;
				}
				else
				{
					CloseCom(i);
				}
				SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//无硬件交互

			}
       }
}

