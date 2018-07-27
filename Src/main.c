#include <utility.h>
#include "asynctmr.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>

#include "main.h"
#include "LoadPanel.h"
#include "MainPanelCb.h"

#define UART_RX_LEN 20

extern int TimerID;
unsigned char comSelect1;				//Serial Com Number
unsigned char comSelect2;

unsigned char UartTxBuf[32]={0};
unsigned char UartRxBuf[500]={0};

unsigned char SA11_Status=0;


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	//comSelect1=argc;		//pass comSelect1 variable 
	comSelect1=1;
	comSelect2=5;
	if(CheckPortStatus(comSelect1)<0) return -1;
	//if(CheckPortStatus(comSelect2)<0) SA11_Status=0;
	//else SA11_Status=1;
	
	LoadInitPanel(); 
	RunUserInterface ();
	CloseCom(comSelect1);
	if(SA11_Status==1) CloseCom(comSelect2);
	DiscardPanel (mainPanel);
	return 0;
}

void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData)
{
	int status;
	int rxNum;
	int i=0;
	RxDataTypeDef RxData;
	if(portNumber==comSelect1)
	{
		rxNum = GetInQLen(portNumber);  									//读取串口中发送来的数据数量
		if(rxNum>500) rxNum=500;											//防止超过内存范围
		status = ComRd(portNumber, (char *)UartRxBuf, rxNum);				//Read UART Buffer to local buffer at one time  
		while(rxNum>=UART_RX_LEN)
		{
			ProtocolGetData(UartRxBuf+i*UART_RX_LEN, &RxData);					//get data from uart buffer
			pGraph1->pCurveArray->numOfDotsToPlot++;								//number of dots to plot increase
			*(pGraph1->pCurveArray->pDotX++)=RxData.rxVdtest;						//get x, set pointer to the next data
			*(pGraph1->pCurveArray->pDotY++)=RxData.rxIdmeasured.num_float;		//get y, set pointer to the next data
			if(RxData.rxStopSign==0x02)											//if complete the test, stop the timer
				DiscardAsyncTimer(TimerID);
			rxNum-=UART_RX_LEN;
			i++;
		}
	}
	else if(portNumber==comSelect2)
	{
	
	}
}

static int CheckPortStatus(unsigned char portNumber)
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
		InstallComCallback (portNumber, LWRS_RECEIVE, UART_RX_LEN, 0, ComCallback, 0);   //binding Callback function to serial input data		18 bytes received will calling for an interrupt
		SetCTSMode(portNumber, LWRS_HWHANDSHAKE_OFF);
		FlushInQ(portNumber);	   														//Clear input and output buffer
		FlushOutQ(portNumber);
		return 0;
	}
}
