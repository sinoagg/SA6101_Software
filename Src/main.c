
#include "LoadPanel.h" 
#include <ansi_c.h>
#include <utility.h>
#include "asynctmr.h"
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include "main.h"
#include"Timer.h"
#include "MainPanelCb.h"
#include "Plot.h"
#include "Protocol.h"
#include "Graph.h"
#include "DataProcess.h"    
#include "Cgs_mt.h"
 #include "progressbar.h"   
  
unsigned char measure_Uart_Flag = 0; 				//��ѧ�������ڽ���ʱҪ�������ݲ�ѯ 
unsigned char control_Uart_Flag = 0; 				//�����������ڽ���ʱҪ�������ݲ�ѯ

const char CloseIDquery[] = {0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13};

char USART_RX_Buffer[50];   		//���� 
char  IDAddrress[30] = {0};         //�豸ID��    

unsigned char measureComPort;	 //Serial Com Number
unsigned char controlComPort;
unsigned char measUartTxBuf[32]={0};
unsigned char measUartRxBuf[1024]={0};
unsigned char curveComplete;


float ohm;      
float reTime=0; 
float envtTime=0;  
RxDataTypeDef RxData; 
#define TXTCOLOR 0x3399FF
#define ANNOTATIONCOLOR 0x508EF4
Rx_CGS_DataTypeDef Rx_CGS_Data;  
void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData)
{
	control_Uart_Flag = 0;
	measure_Uart_Flag = 0;  
	int rxNum=0;																//�����յ��ֽ���
	int i=0;																	//�������֡��
	RxData.rxStopSign=0x00;
	RxData.realTime=0;
    float rxIdmeasured=0;
	rxNum = GetInQLen(portNumber);  											//��ȡ�����з���������������
	if(rxNum>1024) rxNum=1024;													//��ֹ�����ڴ淶Χ
	rxNum-=rxNum%MEASURE_UART_RX_LEN;											//ֻ��ȡ�����ַ��������������ݣ�������ɢ����
	ComRd(portNumber, (char *)measUartRxBuf, rxNum);							//Read UART Buffer to local buffer at one time
	if(measUartRxBuf[0]!=0x01)
	{
	    FlushInQ(portNumber);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
		ProtocolQuery(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);   
	}
	else
	{  
		while(rxNum>=MEASURE_UART_RX_LEN)
		{								  
			ProtocolGetData(measUartRxBuf+i*MEASURE_UART_RX_LEN, &RxData);			//get data from uart buffer
			SetCtrlVal(hResultDispPanel, RESULTDISP_VD, RxData.rxVdtest);
			(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase
			(Graph1.pCurveArray+Graph1.plotCurveIndex)->plotIndex++;     		 //�������ݵ������
			ohm = (TestPara.VdStart*0.001/RxData.rxIdmeasured.num_float);     
			reTime = RxData.realTime*0.001;
			if(logs==1)   //log or Linear
				rxIdmeasured=log10(RxData.rxIdmeasured.num_float);
			else
				rxIdmeasured = RxData.rxIdmeasured.num_float; 
			SetCtrlVal(hResultDispPanel, RESULTDISP_IDS,rxIdmeasured);  
			if(measUartRxBuf[1]!=0x03)RxDataToGraph(&RxData,rxIdmeasured,ohm);
			if(measUartRxBuf[1]!=0x03)RxDataToTable(&RxData);
			rxNum-=MEASURE_UART_RX_LEN;
			i++; 
		}
	
		if(measUartRxBuf[1]!=0x03)PlotCurve1(&Graph1, hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex,rxIdmeasured,RxData.rxStopSign,ohm);
		if(measUartRxBuf[1]!=0x03)SetGraphX_Axis(hGraphPanel,GRAPHDISP_GRAPH1,&Graph1,reTime); 	
		 TestStopActions(&RxData,portNumber,rxIdmeasured);
	}
	measure_Uart_Flag = 1; 
	
	if(controlComPort>0)
	{
		if(temp_flag||humidity_flag ||pressure_flag)
			 control_Uart_Flag = 1;      
	}
}	
	
void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void* callbackData)
{
	measure_Uart_Flag =0;										  //����ʱ���β�ѯ�����ڲ�ѯ����  
	control_Uart_Flag = 0;          
	int rxNum;
	int i,j;
	Rx_CGS_Data.heating_stage_temp = 0;
	Rx_CGS_Data.humidity = 0;
	Rx_CGS_Data.pressure = 0;	 //��ʼ��
	Rx_CGS_Data.environment_temp = 0; 
	rxNum = GetInQLen(controlComPort);  								//��ȡ�����з���������������
	if(rxNum>1024) rxNum=1024;											//��ֹ�����ڴ淶Χ
	while(rxNum>=CONTROL_URAT_RX_LEN)
	{	
		if(((Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots >0)&&(portNumber>0))
		{
			ComRd(controlComPort, (char *)meas_CGS_UartRxBuf, CONTROL_URAT_RX_LEN);
			ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);			//�Ӵ�����ȡ��������������
			j = (Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots - Graph2.pCurveArray->numOfPlotDots; 
				switch(TestPara.testMode)
				{
					case SWEEP_DRAIN_VOL:
					case SWEEP_GATE_VOL :
					case SWEEP_IV:
						for(i = 0; i<=j; i++)
						{
							DisplayEvntIv();   
						 }
						break;
					case NO_SWEEP_IT:
					case NO_SWEEP_RT:
					case ID_T:  
					for(i=0;i<=j;i++)	
					{
					    DisplayEnvtTime();
					}
					break;
				}
			}
			else
			{
				FlushInQ(controlComPort);	   											
				FlushOutQ(controlComPort);
			}
	rxNum -=CONTROL_URAT_RX_LEN;
	}
	PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);//������2ͼ 
	SetGraphX_Axis(hGraphPanel,GRAPHDISP_GRAPH2,&Graph2,envtTime*timeSteps); 
	measure_Uart_Flag = 1;	  //��ֹ���ݲ�ѯ����Ӱ��
	control_Uart_Flag = 1;          
}

int main (int argc, char *argv[])
{
	int SA11_UART_Status=0; 																					//open comport status 
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	Delay(1);
	DeviceQuery();																								//�ж��豸��Ӧ�Ĵ����Ƿ����ӳɹ�
	SA11_UART_Status = CheckOpenCom(&measureComPort,&controlComPort,&measure_Uart_Flag,&control_Uart_Flag);	
	LoadInitPanel(); 
	ProgressBar_ConvertFromSlide (hSettingsAboutPanel, ABOUT_PROGRESSBAR);   	   
	RunUserInterface();
	CheckCloseCom(SA11_UART_Status,measureComPort,controlComPort);
	DiscardPanel (hMainPanel);
	return 0;
}

void DisplayEnvtTime()
{
	*(Graph2.pCurveArray->pDotX++) =envtTime*timeSteps;       
	*((Graph2.pCurveArray +1)->pDotX++) =envtTime*timeSteps;      
	*((Graph2.pCurveArray +2)->pDotX++) =envtTime*timeSteps;      
	*(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 			 //����ʪ��      
	*((Graph2.pCurveArray+1)->pDotY++) = Rx_CGS_Data.heating_stage_temp;	 //��̨�¶�     
	*((Graph2.pCurveArray+2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //ѹǿ
	Graph2.pCurveArray->numOfDotsToPlot++;  
	(Graph2.pCurveArray +1)->numOfDotsToPlot++;					    
	(Graph2.pCurveArray +2)->numOfDotsToPlot++;
	Rx_CGS_DataToTable(&Rx_CGS_Data,envtTime*timeSteps);  
	envtTime+=1;      
}

void DisplayEvntIv()
{
	if(TestPara.testMode==SWEEP_GATE_VOL)  //idvg
	{															 
		*(Graph2.pCurveArray->pDotX++)=TestPara.VgStart;
		*((Graph2.pCurveArray +1)->pDotX++) =TestPara.VgStart;        
		*((Graph2.pCurveArray +2)->pDotX++) = TestPara.VgStart;
		 if(TestPara.VgStart>TestPara.VgStop)TestPara.VgStart-=TestPara.VgStep; 
		else TestPara.VgStart+=TestPara.VgStep; 
	}
	else	  //idvd IdVd��IV
	{
		*(Graph2.pCurveArray->pDotX++)=TestPara.VdStart;
		*((Graph2.pCurveArray +1)->pDotX++) =TestPara.VdStart;        
		*((Graph2.pCurveArray +2)->pDotX++) = TestPara.VdStart;
		if(TestPara.VdStart>TestPara.VdStop)TestPara.VdStart-=TestPara.VdStep; 
		else TestPara.VdStart+=TestPara.VdStep; 
	}
		*(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 			//����ʪ��      
		*((Graph2.pCurveArray+1)->pDotY++) = Rx_CGS_Data.heating_stage_temp;	//��̨�¶�     
		*((Graph2.pCurveArray+2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		//ѹǿ
		Graph2.pCurveArray->numOfDotsToPlot++;  
		(Graph2.pCurveArray +1)->numOfDotsToPlot++;
		(Graph2.pCurveArray +2)->numOfDotsToPlot++;
		Rx_CGS_DataToTable(&Rx_CGS_Data,0);
}
