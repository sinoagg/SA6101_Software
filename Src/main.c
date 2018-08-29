#include <ansi_c.h>
#include <utility.h>
#include "asynctmr.h"
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include "main.h"
#include "LoadPanel.h"
#include "MainPanelCb.h"
#include "Plot.h"
#include "Protocol.h"
#include "Graph.h"
#include "Cgs_mt.h"

extern int TimerID;
unsigned char measureComPort;				//Serial Com Number
unsigned char controlComPort;

unsigned char measUartTxBuf[32]={0};
unsigned char measUartRxBuf[1024]={0};

unsigned char SA11_Status=0;				//open comport status
unsigned char curveComplete;

void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void * callbackData); 

void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData)
{
	int rowNum;																	//表格新加行号
	int rxNum=0;																//串口收到字节数
	int i=0;																	//处理接收帧数
	RxDataTypeDef RxData;
	RxData.rxStopSign=0x00;
	rxNum = GetInQLen(portNumber);  											//读取串口中发送来的数据数量
	if(rxNum>1024) rxNum=1024;													//防止超过内存范围
	rxNum-=rxNum%MEASURE_UART_RX_LEN;											//只读取接收字符组整数倍的数据，不读零散数据
	ComRd(portNumber, (char *)measUartRxBuf, rxNum);							//Read UART Buffer to local buffer at one time  
	/*int CurveIndex;
	CurveIndex	= Graph1.pCurveArray->curveIndex;*/
	while(rxNum>=MEASURE_UART_RX_LEN)
	{														  
		ProtocolGetData(measUartRxBuf+i*MEASURE_UART_RX_LEN, &RxData);			//get data from uart buffer
		if(RxData.rxStopSign==0x01 || (Graph1.pCurveArray->numOfTotalDots == Graph1.pCurveArray->numOfPlotDots))												//if received end of test signal, stop the timer right now, or new query cmd will be transmitted
			DiscardAsyncTimer(TimerID);
		
		SetCtrlVal(hResultDispPanel, RESULTDISP_VD, RxData.rxVdtest);
		SetCtrlVal(hResultDispPanel, RESULTDISP_VG, RxData.rxVgtest);
		SetCtrlVal(hResultDispPanel, RESULTDISP_IDS, RxData.rxIdmeasured.num_float);
	
		(Graph1.pCurveArray+Graph1.pCurveArray->curveIndex)->numOfDotsToPlot++;									//number of dots to plot increase
					
		if(TestPara.testMode==SWEEP_DRAIN_VOL)
		{
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX++)=RxData.rxVdtest;						//get x, set pointer to the next data
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY++)=RxData.rxIdmeasured.num_float;		//get y, set pointer to the next data 
		}
		else if(TestPara.testMode==SWEEP_GATE_VOL)
		{
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX++)=RxData.rxVgtest;						//get x, set pointer to the next data
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY++)=RxData.rxIdmeasured.num_float;
		}
		else if(TestPara.testMode==SWEEP_IV) 
		{
			*(Graph1.pCurveArray->pDotX++)=RxData.rxVdtest;
			*(Graph1.pCurveArray->pDotY++)=RxData.rxIdmeasured.num_float;
		}
		else if(TestPara.testMode==NO_SWEEP_IT)
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, Graph1.pCurveArray->time*0.001);              
			*(Graph1.pCurveArray->pDotX++)=Graph1.pCurveArray->time*0.001;		//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep; 
			*(Graph1.pCurveArray->pDotY++)=RxData.rxIdmeasured.num_float;
		}
		else if(TestPara.testMode==NO_SWEEP_RT)
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, Graph1.pCurveArray->time*0.001);              
			*(Graph1.pCurveArray->pDotX++)=Graph1.pCurveArray->time*0.001;		//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep;
			*(Graph1.pCurveArray->pDotY++)=TestPara.VdStart/RxData.rxIdmeasured.num_float*0.001;   
			SetCtrlVal(hResultDispPanel, RESULTDISP_OHM,(TestPara.VdStart/RxData.rxIdmeasured.num_float)*0.001);
		}
		else if(TestPara.testMode==ID_T)
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, Graph1.pCurveArray->time*0.001);
			*(Graph1.pCurveArray->pDotX++)= Graph1.pCurveArray->time*0.001;
			Graph1.pCurveArray->time+=TestPara.timeStep;
			*(Graph1.pCurveArray->pDotY++)=RxData.rxIdmeasured.num_float; 
		}
		InsertTableRows (hTablePanel,TABLE_DISTABLE , -1, 1, VAL_CELL_NUMERIC);				          	 	//插入1行 
		GetNumTableRows (hTablePanel, TABLE_DISTABLE, &rowNum); 										  		//得到当前行数
		SetCtrlAttribute(hTablePanel,TABLE_DISTABLE, ATTR_FIRST_VISIBLE_ROW, rowNum);							//显示到最近添加的一行
		SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (1, rowNum), *(Graph1.pCurveArray->pDotX-1));  //写入X值
		SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (2, rowNum), *(Graph1.pCurveArray->pDotY-1));  //写入Y值  
	
		rxNum-=MEASURE_UART_RX_LEN;
		i++; 
	}	
		//GetSettingsCurveAttr(Graph1.graphIndex,Graph1.pCurveArray->curveIndex);       
	   	PlotCurve1(&Graph1, hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex); 
		
	  	if((RxData.rxStopSign==0x01) || (Graph1.pCurveArray->numOfTotalDots == Graph1.pCurveArray->numOfPlotDots))
		{
		/*	GraphDeinit(&Graph1);												//内存释放在画图之后，如果在画图之前释放导致错误
			GraphDeinit(&Graph2);*/
			RxData.rxStopSign=0;
			Graph1.pCurveArray->numOfPlotDots=0;
			curveComplete=1;
			FlushInQ(portNumber);	   											//Clear input and output buffer
			FlushOutQ(portNumber);
		   	ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send RUN command to instrument via UART 
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //禁用 停止按钮      
		    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //恢复 开始按钮
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //恢复 保存按钮
		}	
}	
	



void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void* callbackData)
{
//	int status;
	int rxNum;																							  
	int i=0;
	static a = 0;
	Rx_CGS_DataTypeDef Rx_CGS_Data;
	rxNum = GetInQLen(controlComPort);  								//读取串口中发送来的数据数量
	if(rxNum>500) rxNum=500;											//防止超过内存范围
	ComRd(controlComPort, (char *)meas_CGS_UartRxBuf, rxNum);	
	
	while(rxNum>=14)
	{			 
		ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);			// 从串口中取出环境测量参数
		*(Graph2.pCurveArray->pDotX++) = a++;
		*((Graph2.pCurveArray + 1)->pDotX++) = a-1; 
		*((Graph2.pCurveArray + 2)->pDotX++) = a-1; 
	    *(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 				 //环境湿度      
		*((Graph2.pCurveArray + 1)->pDotY++) = Rx_CGS_Data.environment_temp;		 //环境温度     
		*((Graph2.pCurveArray + 2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //压强    
		(Graph2.pCurveArray +1)->numOfDotsToPlot++;
		(Graph2.pCurveArray +2)->numOfDotsToPlot++; 
		Graph2.pCurveArray->numOfDotsToPlot++; 
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_TEMPERATURE, Rx_CGS_Data.environment_temp);			//显示温度   
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_HUMIDITY,  Rx_CGS_Data.humidity);					//显示湿度     
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_PRESSURE, Rx_CGS_Data.pressure*0.001);		 		//显示压强         		 
		rxNum -=14; 
		i++; 
	}
	
	PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);//画曲线图          
}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	//measureComPort=argc;		//pass measureComPort variable 
	measureComPort=8;
	controlComPort=5;
	if(CheckPortStatus(measureComPort, MEASURE_UART_RX_LEN, MeasureComCallback)<0) return -1;
	//if(CheckPortStatus(controlComPort)<0) SA11_Status=0;
	//else SA11_Status=1;
	
	LoadInitPanel(); 
	//CheckPortStatus(controlComPort, 14, CtrlComCallback); //controlComPort
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

