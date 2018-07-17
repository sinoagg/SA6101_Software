#include "asynctmr.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>

#include "LoadPanel.h"
#include "MainPanelCb.h"

extern int TimerID;
unsigned char comSelect;				//Serial Com Number

unsigned char UartTxBuf[32]={0};
unsigned char UartRxBuf[64]={0};

void CVICALLBACK ComCallback(int portNumber ,int eventMask, void * callbackData);
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);

int main (int argc, char *argv[])
{
	int status;
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	//comSelect=argc;		//pass comSelect variable 
	comSelect=1;
	status = OpenComConfig(comSelect, "", 115200, 0, 8, 1, 512, 512);	   //Config and Connect serial port
	if(status != 0) 
	{
		MessagePopup("Error","Device unconnected!");
		return 0;
	}
	InstallComCallback (comSelect, LWRS_RECEIVE, 20, 0, ComCallback, 0);   //binding Callback function to serial input data		18 bytes received will calling for an interrupt
	SetCTSMode(comSelect, LWRS_HWHANDSHAKE_OFF);
	FlushInQ(comSelect);	   //Clear input and output buffer
	FlushOutQ(comSelect);
	LoadInitPanel(); 
	RunUserInterface ();
	CloseCom(comSelect);
	DiscardPanel (mainPanel);
	return 0;
}

void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData)
{
	int status;
	int rxNum;
	RxDataTypeDef RxData;
	rxNum = GetInQLen(comSelect);  											//读取串口中发送来的数据数量
	while(rxNum>=20)
	{
		status = ComRd(comSelect, (char *)UartRxBuf, 20);					//Read UART Buffer to local buffer
		ProtocolGetData(UartRxBuf, &RxData);								//get data from uart buffer
		Graph.pCurveArray->numOfDotsToPlot++;								//number of dots to plot increase
		*(Graph.pCurveArray->pDotX++)=RxData.rxVdtest;						//get x, set pointer to the next data
		*(Graph.pCurveArray->pDotY++)=RxData.rxIdmeasured.num_float;		//get y, set pointer to the next data
		if(RxData.rxStopSign==0x02)											//if complete the test, stop the timer
			DiscardAsyncTimer(TimerID);
		rxNum-=20;
		rxNum = GetInQLen(comSelect);  										//读取串口中发送来的数据数量 
	}
	
}


