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

extern int TimerID;
unsigned char measureComPort;				//Serial Com Number
unsigned char controlComPort;

unsigned char measUartTxBuf[32]={0};
unsigned char measUartRxBuf[500]={0};

unsigned char SA11_Status=0;

void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData)
{
	int rxNum;
	int i=0;
	RxDataTypeDef RxData;
	rxNum = GetInQLen(portNumber);  									//读取串口中发送来的数据数量
	if(rxNum>500) rxNum=500;											//防止超过内存范围
	ComRd(portNumber, (char *)measUartRxBuf, rxNum);					//Read UART Buffer to local buffer at one time  
	
	while(rxNum>=MEASURE_UART_RX_LEN)
	{
		ProtocolGetData(measUartRxBuf+i*MEASURE_UART_RX_LEN, &RxData);			//get data from uart buffer
		pGraph1->pCurveArray->numOfDotsToPlot++;								//number of dots to plot increase
		
		if(TestPara.testMode==SWEEP_DRAIN_VOL)
			*(pGraph1->pCurveArray->pDotX++)=RxData.rxVdtest;						//get x, set pointer to the next data
		else if(TestPara.testMode==SWEEP_GATE_VOL)
			*(pGraph1->pCurveArray->pDotX++)=RxData.rxVgtest;						//get x, set pointer to the next data
		else if(TestPara.testMode==NO_SWEEP_IT)
			*(pGraph1->pCurveArray->pDotX++)=pGraph1->pCurveArray->time;			//get x, set pointer to the next data
		else if(TestPara.testMode==NO_SWEEP_RT)
			*(pGraph1->pCurveArray->pDotX++)=pGraph1->pCurveArray->time;			//get x, set pointer to the next data
		
		pGraph1->pCurveArray->time+=TestPara.timeStep;
		*(pGraph1->pCurveArray->pDotY++)=RxData.rxIdmeasured.num_float;				//get y, set pointer to the next data
		if(RxData.rxStopSign==0x02)													//if complete the test, stop the timer
			DiscardAsyncTimer(TimerID);
		rxNum-=MEASURE_UART_RX_LEN;
		i++;
	}
	
	PlotCurve(pGraph1, hGraphPanel, GRAPHDISP_GRAPH1);
}

void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void* callbackData)
{
	

}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	//measureComPort=argc;		//pass measureComPort variable 
	measureComPort=1;
	controlComPort=5;
	if(CheckPortStatus(measureComPort, MEASURE_UART_RX_LEN, MeasureComCallback)<0) return -1;
	//if(CheckPortStatus(controlComPort)<0) SA11_Status=0;
	//else SA11_Status=1;
	
	LoadInitPanel(); 
	RunUserInterface();
	CloseCom(measureComPort);
	if(SA11_Status==1) CloseCom(controlComPort);
	DiscardPanel (mainPanel);
	return 0;
}

static int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFunc)(int, int, void*))
{
	int status;
	status = OpenComConfig(portNumber, "", 115200, 0, 8, 1, 512, 512);	   //Config and Connect serial port
	if(status != 0) 
	{
		MessagePopup("Error","Device unconnected.");
		return -1;
	}
	else
	{
		InstallComCallback (portNumber, LWRS_RECEIVE, uartRxLen, 0, pFunc, 0);   //binding Callback function to serial input data		18 bytes received will calling for an interrupt
		SetCTSMode(portNumber, LWRS_HWHANDSHAKE_OFF);
		FlushInQ(portNumber);	   														//Clear input and output buffer
		FlushOutQ(portNumber);
		return 0;
	}
}

