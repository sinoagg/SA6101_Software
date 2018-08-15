#include <utility.h>
#include "asynctmr.h"
#include <ansi_c.h>
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

unsigned char SA11_Status=0;

GraphTypeDef Graph2;

void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void * callbackData); 

void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData)
{
	static int leftNum=0;
	int row;
	int rxNum=0;           
	int i=0, j=0;
	RxDataTypeDef RxData;   //接收数据类型
	RxData.rxStopSign=0x00;
	rxNum = GetInQLen(portNumber); //获取指定串行口输入队列内的字符数 //读取串口中发送来的数据数量
	if(rxNum>500) rxNum=500;											//防止超过内存范围
	ComRd(portNumber, (char *)measUartRxBuf+leftNum, rxNum);//指定端口读取一定长度字符并存放在缓冲区[字符型数组]中//Read UART Buffer to local buffer at one time  
	leftNum+=rxNum;
	while(leftNum>=MEASURE_UART_RX_LEN)	   //MEASURE_UART_RX_LEN=20  20个为一组
	{
		
		InsertTableRows (hTablePanel,TABLE_DISTABLE ,-1, 1, VAL_CELL_NUMERIC);		//插入1行 
		GetNumTableRows (hTablePanel, TABLE_DISTABLE, &row); 					    //得到当前行数

		ProtocolGetData(measUartRxBuf+i*MEASURE_UART_RX_LEN, &RxData);				//get data from uart buffer
																					
		SetCtrlVal(hResultDispPanel, RESULTDISP_VD, RxData.rxVdtest);
		SetCtrlVal(hResultDispPanel, RESULTDISP_VG, RxData.rxVgtest);
		SetCtrlVal(hResultDispPanel, RESULTDISP_IDS, RxData.rxIdmeasured.num_float);
		//SetGraphY_Axis(&Graph1, RxData.rxIdmeasured.num_float);
		
		Graph1.pCurveArray->numOfDotsToPlot++;										//number of dots to plot increase
		*(Graph1.pCurveArray->pDotY++)=RxData.rxIdmeasured.num_float;				//get y, set pointer to the next data
		SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (2,row), *(Graph1.pCurveArray->pDotY-1));
		
		int MaxRow; 													
		GetNumTableRows(hTablePanel,TABLE_DISTABLE,&MaxRow);
		SetCtrlAttribute(hTablePanel,TABLE_DISTABLE,ATTR_FIRST_VISIBLE_ROW,MaxRow); //超出table高度后显示总能显示最后一行数据    
		
		if(TestPara.testMode==SWEEP_DRAIN_VOL)
		{
			*(Graph1.pCurveArray->pDotX++)=RxData.rxVdtest;							//get x, set pointer to the next data
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (1,row), *(Graph1.pCurveArray->pDotX-1));//写入数据   
		}
		else if(TestPara.testMode==SWEEP_GATE_VOL)
		{
			*(Graph1.pCurveArray->pDotX++)=RxData.rxVgtest;							//get x, set pointer to the next data
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (1,row), *( Graph1.pCurveArray->pDotX-1));  
		}
		else if(TestPara.testMode==NO_SWEEP_IT)
		{
			*(Graph1.pCurveArray->pDotX++)=Graph1.pCurveArray->time;			//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep; 
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (1,row), *(Graph1.pCurveArray->pDotX-1));   
		}
		else if(TestPara.testMode==NO_SWEEP_RT)
		{
			*(Graph1.pCurveArray->pDotX++)=Graph1.pCurveArray->time;			//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep; 
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (1,row), *(Graph1.pCurveArray->pDotX-1));  
		}
		else if(TestPara.testMode==SWEEP_IV)
		{
			*(Graph1.pCurveArray->pDotX++)=Graph1.pCurveArray->time;
			Graph1.pCurveArray->time += TestPara.timeStep;
		    SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (1,row), *(Graph1.pCurveArray->pDotX-1));   

		}
		else if(TestPara.testMode==ID_T)
		{
			*(Graph1.pCurveArray->pDotX++)= Graph1.pCurveArray->time;
			Graph1.pCurveArray->time += TestPara.timeStep;
			SetTableCellVal(hTablePanel,TABLE_DISTABLE,MakePoint(1,row),*(Graph1.pCurveArray->pDotX-1));
		}
		
		leftNum-=MEASURE_UART_RX_LEN;
		i++; 
		if(RxData.rxStopSign==0x01)													//if complete the test, stop the timer
		{
			DiscardAsyncTimer(TimerID);
		}
	}
	
	for(j=0;j++;j<leftNum) //把最后几个字节散开的数据往前挪
	{
		measUartRxBuf[j]=measUartRxBuf[i*MEASURE_UART_RX_LEN+j];
	}
	
	PlotCurve(&Graph1, hGraphPanel, GRAPHDISP_GRAPH1);
	if(RxData.rxStopSign==0x01)
	{
		GraphDeinit(&Graph1);												//内存释放在画图之后
		GraphDeinit(&Graph2);
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //禁用 停止按钮      
	    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //恢复 开始按钮
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //恢复 保存按钮
	}
}


void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void* callbackData)
{
	int status;
	int rxNum;																							  
	int i=0;
	static a = 0;
	Rx_CGS_DataTypeDef Rx_CGS_Data;
	rxNum = GetInQLen(controlComPort);  									//读取串口中发送来的数据数量
	if(rxNum>500) rxNum=500;												//防止超过内存范围
	ComRd(controlComPort, (char *)meas_CGS_UartRxBuf, rxNum);	
	
	while(rxNum>=14)
	{			 
		ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);				// 从 串口中取出 环境测量参数
		*(Graph2.pCurveArray->pDotX++) = a++;
		*((Graph2.pCurveArray + 1)->pDotX++) = a-1; 
		*((Graph2.pCurveArray + 2)->pDotX++) = a-1; 
	    *(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 					//湿度
		*((Graph2.pCurveArray + 1)->pDotY++) = Rx_CGS_Data.temperature;		 			//温度
		*((Graph2.pCurveArray + 2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 	//压强
		(Graph2.pCurveArray +1)->numOfDotsToPlot++;
		(Graph2.pCurveArray +2)->numOfDotsToPlot++; 
		Graph2.pCurveArray->numOfDotsToPlot++; 
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_TEMPERATURE, Rx_CGS_Data.temperature);	
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_HUMIDITY,  Rx_CGS_Data.humidity);		
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_PRESSURE, Rx_CGS_Data.pressure);	
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
	measureComPort=4;
	controlComPort=5;
	if(CheckPortStatus(measureComPort, MEASURE_UART_RX_LEN, MeasureComCallback)<0) return -1;
	if(CheckPortStatus(controlComPort,14,CtrlComCallback)<0) SA11_Status=0;
	else SA11_Status=1;
	
	LoadInitPanel(); 
	CheckPortStatus(controlComPort, 14, CtrlComCallback); 
	RunUserInterface();
	CloseCom(measureComPort);
	
	if(SA11_Status==1) CloseCom(controlComPort);
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
	{					//  指定串口， 设置可响应的事件 ，输入缓存区的最小字节 ，，，，，
		InstallComCallback (portNumber, LWRS_RECEIVE, uartRxLen, 0, pFunc, 0);   //binding Callback function to serial input data		18 bytes received will calling for an interrupt
		SetCTSMode(portNumber, LWRS_HWHANDSHAKE_OFF);
		FlushInQ(portNumber);	   														//Clear input and output buffer
		FlushOutQ(portNumber);
		return 0;
	}
}

