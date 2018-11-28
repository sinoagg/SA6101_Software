
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
#include "Cgs_mt.h"
 #include "progressbar.h"   
#include "DataProcess.h"  
unsigned char measure_Uart_Flag = 0; 				//��ѧ�������ڽ���ʱҪ�������ݲ�ѯ 
unsigned char control_Uart_Flag = 0; 				//�����������ڽ���ʱҪ�������ݲ�ѯ


const char CloseIDquery[] = {0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13};

char USART_RX_Buffer[50];   //���� 
char  IDAddrress[30] = {0};         //�豸ID��    


float envtTime; 
unsigned char measureComPort;	 //Serial Com Number
unsigned char controlComPort;

unsigned char measUartTxBuf[32]={0};
unsigned char measUartRxBuf[1024]={0};
   

unsigned char curveComplete;
int rows;         //graph1 table��д���ݱ�־λ
int graphrows;    //graph2
float ohm;
int controlTime;
Rx_CGS_DataTypeDef Rx_CGS_Data; 
RxDataTypeDef RxData; 
#define TXTCOLOR 0x3399FF
#define ANNOTATIONCOLOR 0x508EF4
float reTime=0;
int c=0;  
void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData)
{
	//control_Uart_Flag = 0;
	measure_Uart_Flag = 0;  
	int rxNum=0;																//�����յ��ֽ���
	int i=0;																	//�������֡��
	//RxDataTypeDef RxData;
	RxData.rxStopSign=0x00;
	RxData.realTime=0;
    float rxIdmeasured=0;
	int log; 
	
	GetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_LINEAR, ATTR_CTRL_INDEX,&log);       
	rxNum = GetInQLen(portNumber);  											//��ȡ�����з���������������
	if(rxNum>1024) rxNum=1024;													//��ֹ�����ڴ淶Χ
	rxNum-=rxNum%MEASURE_UART_RX_LEN;											//ֻ��ȡ�����ַ��������������ݣ�������ɢ����
	ComRd(portNumber, (char *)measUartRxBuf, rxNum);							//Read UART Buffer to local buffer at one time
	Delay(0.02);
	if(measUartRxBuf[0]!=0x01)
	{
	    FlushInQ(portNumber);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
		FlushOutQ(portNumber);     
	}
	else
	{  
		while(rxNum>=MEASURE_UART_RX_LEN)
		{								  
			ProtocolGetData(measUartRxBuf+i*MEASURE_UART_RX_LEN, &RxData);			//get data from uart buffer
			SetCtrlVal(hResultDispPanel, RESULTDISP_VD, RxData.rxVdtest);
			(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase
			ohm = (TestPara.VdStart*0.001/RxData.rxIdmeasured.num_float);     
			reTime = RxData.realTime*0.001;
			if(log==1)   //log or Linear
				rxIdmeasured=log10(RxData.rxIdmeasured.num_float);
			else
				rxIdmeasured = RxData.rxIdmeasured.num_float; 
			SetCtrlVal(hResultDispPanel, RESULTDISP_IDS,rxIdmeasured);  
			RxDataToGraph(&RxData,rxIdmeasured,ohm);
			RxDataToTable(&RxData);
			rxNum-=MEASURE_UART_RX_LEN;
			i++; 
		}
			/*if(measUartRxBuf[1]!=0x03)PlotCurve1(&Graph1, hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex,rxIdmeasured,RxData.rxStopSign,ohm);
			if(measUartRxBuf[1]!=0x03)SetGraphX_Axis(hGraphPanel,GRAPHDISP_GRAPH1,&Graph1,reTime); 	*/
			TestStopActions(&RxData,portNumber,rxIdmeasured);
			int temp,hum,press;
			GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_TEMPTER,&temp); 
			GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_HUMIDITY,&hum); 
			GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_PRESSURE,&press); 
			if(controlComPort>0)
			{
			  if(temp||hum ||press)
				 control_Uart_Flag = 1;
			}
			  measure_Uart_Flag = 1;  
	}
}	
	
 
void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void* callbackData)
{
	measure_Uart_Flag =0;
//\	control_Uart_Flag = 0;														//����ʱ���β�ѯ�����ڲ�ѯ����
	int rxNum;
	int i,j;
	Rx_CGS_Data.heating_stage_temp = 0;
	Rx_CGS_Data.humidity = 0;
	Rx_CGS_Data.pressure = 0;	 //��ʼ��
	Rx_CGS_Data.environment_temp = 0; 
	rxNum = GetInQLen(controlComPort);  								//��ȡ�����з���������������
	if(rxNum>500) rxNum=500;											//��ֹ�����ڴ淶Χ
	while(rxNum>=15)
	{	
		if((Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots >0)
		{
			ComRd(controlComPort, (char *)meas_CGS_UartRxBuf, 15);
			ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);			//�Ӵ�����ȡ��������������
			switch(TestPara.testMode)
			{
				case SWEEP_DRAIN_VOL:
				case SWEEP_GATE_VOL :
				case SWEEP_IV:
				  j = (Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots - Graph2.pCurveArray->numOfPlotDots;  
					for(i = 0; i<=j; i++)
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
							Rx_CGS_DataToTable(&Rx_CGS_Data);
						}
					break;
				case NO_SWEEP_IT:
				case NO_SWEEP_RT:
				case ID_T:  
					*(Graph2.pCurveArray->pDotX++) =envtTime*timeStep-timeStep;       
					*((Graph2.pCurveArray +1)->pDotX++) =envtTime*timeStep-timeStep;       
					*((Graph2.pCurveArray +2)->pDotX++) =envtTime*timeStep-timeStep;       
					*(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 			 //����ʪ��      
					*((Graph2.pCurveArray+1)->pDotY++) = Rx_CGS_Data.heating_stage_temp;	 //��̨�¶�     
					*((Graph2.pCurveArray+2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //ѹǿ
					Rx_CGS_DataToTable(&Rx_CGS_Data);    
					Graph2.pCurveArray->numOfDotsToPlot++;  
					(Graph2.pCurveArray +1)->numOfDotsToPlot++;					    
					(Graph2.pCurveArray +2)->numOfDotsToPlot++;
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
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_TEMPERATURE, Rx_CGS_Data.heating_stage_temp);		//��̨�¶�   
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_HUMIDITY,  Rx_CGS_Data.humidity);					//��ʾʪ��     
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_PRESSURE, Rx_CGS_Data.pressure*0.001);		 		//��ʾѹǿ		  
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_times, envtTime*timeStep-timeStep);	
	
	PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);//������2ͼ 
	SetGraphX_Axis(hGraphPanel,GRAPHDISP_GRAPH2,&Graph2,envtTime*timeStep-timeStep); 
	int temp,hum,press;
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_TEMPTER,&temp); 
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_HUMIDITY,&hum); 
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_PRESSURE,&press); 
	if(controlComPort>0)
	{
	  if(temp||hum ||press)
		 control_Uart_Flag = 1;
	}
	measure_Uart_Flag = 1;	  //��ֹ���ݲ�ѯ����Ӱ��
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
 
