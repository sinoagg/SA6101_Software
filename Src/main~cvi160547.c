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
void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void * callbackData); 

static void Annotation(int panel,int control)
{
	     char curve[80];
		 sprintf(curve,"%s%d","Curve",curveIndex);
		 AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve,-30,25);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_BGCOLOR, VAL_RED);
		 ProcessDrawEvents();
	     SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YAXIS, VAL_LEFT_YAXIS);
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XAXIS, VAL_BOTTOM_XAXIS); 
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_LINE_COLOR, VAL_DK_BLUE);
		 ProcessDrawEvents(); 
}

static void RxDataToGraph(RxDataTypeDef *pRxData)
	{
		char time[80];
		int str = Graph1.pCurveArray->time*0.001;
		sprintf(time,"%s%d","",str); 
		if(TestPara.testMode==SWEEP_DRAIN_VOL)
		{
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX++)=pRxData->rxVdtest;						//get x, set pointer to the next data
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY++)=pRxData->rxIdmeasured.num_float;			//get y, set pointer to the next data 
			
		}
		else if(TestPara.testMode==SWEEP_GATE_VOL)
		{
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX++)=pRxData->rxVgtest;						//get x, set pointer to the next data
			*((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY++)=pRxData->rxIdmeasured.num_float;
		}
		else if(TestPara.testMode==SWEEP_IV) 
		{
			*(Graph1.pCurveArray->pDotX++)=pRxData->rxVdtest;
			*(Graph1.pCurveArray->pDotY++)=pRxData->rxIdmeasured.num_float;
		}
		else if(TestPara.testMode==NO_SWEEP_IT)	   
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, time);              
			*(Graph1.pCurveArray->pDotX++)=Graph1.pCurveArray->time*0.001;							//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep; 
			*(Graph1.pCurveArray->pDotY++)=pRxData->rxIdmeasured.num_float;
		}
		else if(TestPara.testMode == NO_SWEEP_RT)
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME,time);              
			*(Graph1.pCurveArray->pDotX++)=Graph1.pCurveArray->time*0.001;							//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep;
			*(Graph1.pCurveArray->pDotY++)=(TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001;   
			SetCtrlVal(hResultDispPanel, RESULTDISP_OHM,(TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001);
			
			if(((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001) <= Graph1.pGraphAttr->yAxisHead)
			{
				 Graph1.pGraphAttr->yAxisHead =((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001)*0.9; 
				 SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
			}
			else if(((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001)>= Graph1.pGraphAttr->yAxisTail)
			{
				Graph1.pGraphAttr->yAxisTail =  (TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001 + ((TestPara.VdStart/pRxData->rxIdmeasured.num_float)*0.001)* 0.1;
				SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
			}
		}
		else if(TestPara.testMode==ID_T)
		{
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, time);
			*(Graph1.pCurveArray->pDotX++)= Graph1.pCurveArray->time*0.001;
			Graph1.pCurveArray->time+=TestPara.timeStep;
			*(Graph1.pCurveArray->pDotY++)=pRxData->rxIdmeasured.num_float; 
		}
	
		
		 switch(TestPara.testMode)
    	 {    
			case SWEEP_GATE_VOL:
				Annotation(hGraphPanel,GRAPHDISP_GRAPH1);
				SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVgtest));	
			    SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YVALUE,(double)pRxData->rxIdmeasured.num_float);
				
				break;
			case SWEEP_DRAIN_VOL:
				Annotation(hGraphPanel,GRAPHDISP_GRAPH1);  
				SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVdtest));	
				SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YVALUE,(double)pRxData->rxIdmeasured.num_float);

				break;
		
		 }
		 ProcessDrawEvents();
		 curveIndex++;					  
	}

static void RxDataToTable(RxDataTypeDef *pRxData)
{
	//rows  table���еı�־������ÿ�����ߴ�(rows+1)=1��ʼ�����һ����;һ�����߽���ʱ��0 
	/*SetTableCellAttribute (hTablePanel, TABLE_DISTABLE,MakePoint (Graph1.plotCurveIndex*3+1, rows+1)  , ATTR_TEXT_COLOR, TXTCOLOR);//��һ��
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE,MakePoint (Graph1.plotCurveIndex*3+2, rows+1)  , ATTR_TEXT_COLOR, TXTCOLOR);//�ڶ���*/
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+1, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+2, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+1, rows+1), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //д��Xֵ
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+2, rows+1), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //д��Yֵ 
	
		switch(TestPara.testMode)
    	{    
			case SWEEP_DRAIN_VOL:
				//SetTableCellAttribute (hTablePanel, TABLE_DISTABLE,MakePoint (Graph1.plotCurveIndex*3+3, rows+1)  , ATTR_TEXT_COLOR, TXTCOLOR); //������
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); 
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint(Graph1.plotCurveIndex*3+3, rows+1),(float)pRxData->rxVgtest);  //д��vgֵ  
				break;
			case SWEEP_GATE_VOL:
				//SetTableCellAttribute (hTablePanel, TABLE_DISTABLE,MakePoint (Graph1.plotCurveIndex*3+3, rows+1)  , ATTR_TEXT_COLOR, TXTCOLOR);
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); 
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1),(float)pRxData->rxVdtest);  //д��vdֵ  
				break;
			case NO_SWEEP_IT:
			case NO_SWEEP_RT:
			case ID_T: 
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows+1),(float)pRxData->rxVdtest);  //д��vdֵ
				//SetTableCellAttribute (hTablePanel, TABLE_DISTABLE,MakePoint (Graph1.plotCurveIndex*3+3, rows+1)  , ATTR_TEXT_COLOR, TXTCOLOR);       
				break;
		  }


   /*	int rowNum;									//�����¼��к�  
	rowNum = rows+1;
	GetNumTableRows (hTablePanel, TABLE_DISTABLE, &rowNum); 										  		//�õ���ǰ���� 
	SetCtrlAttribute(hTablePanel,TABLE_DISTABLE, ATTR_FIRST_VISIBLE_ROW,rowNum);							//��ʾ��������ӵ�һ��*/             
	rows++;  											  
										  
}
static void TestStop(RxDataTypeDef *pRxData,int portNumber)
{

	DiscardAsyncTimer(TimerID);											//ֹͣquery��ʱ����ѯ
	pRxData->rxStopSign=0;
	Graph1.pCurveArray->numOfPlotDots=0;
	curveComplete=1;
	rows=0;
	FlushInQ(portNumber);	   											//Clear input and output buffer
	FlushOutQ(portNumber);
	ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send RUN command to instrument via UART 
	Delay(1);
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0);   //�ָ�������������  
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);        //���� ֹͣ��ť //ע�͵�������������е��ֹͣ     
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);        //�ָ� ��ʼ��ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);       //�ָ� ���水ť
	
	GraphDeinit(&Graph1);												//�ڴ��ͷ��ڻ�ͼ֮������ڻ�ͼ֮ǰ�ͷŵ��´���
	GraphDeinit(&Graph2);
	
}

static void  DispVgTest(RxDataTypeDef *pRxData)  //IT��RTģʽ��Vg����ʾ
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
void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData)
{
	int rxNum=0;																//�����յ��ֽ���
	int i=0;																	//��������֡��
	RxDataTypeDef RxData;
	RxData.rxStopSign=0x00;
    float rxIdmeasured=0;
	rxNum = GetInQLen(portNumber);  											//��ȡ�����з���������������
	if(rxNum>1024) rxNum=1024;													//��ֹ�����ڴ淶Χ
	rxNum-=rxNum%MEASURE_UART_RX_LEN;											//ֻ��ȡ�����ַ��������������ݣ�������ɢ����
	ComRd(portNumber, (char *)measUartRxBuf, rxNum);							//Read UART Buffer to local buffer at one time
	int curveNum = 0;
	curveNum = Graph1.numOfCurve;
	while(rxNum>=MEASURE_UART_RX_LEN)
	{														  
		ProtocolGetData(measUartRxBuf+i*MEASURE_UART_RX_LEN, &RxData);			//get data from uart buffer
		SetCtrlVal(hResultDispPanel, RESULTDISP_VD, RxData.rxVdtest);
		DispVgTest(&RxData);
		SetCtrlVal(hResultDispPanel, RESULTDISP_IDS, RxData.rxIdmeasured.num_float);
		(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;									//number of dots to plot increase
		rxIdmeasured = RxData.rxIdmeasured.num_float;
		RxDataToGraph(&RxData);
		RxDataToTable(&RxData);
		rxNum-=MEASURE_UART_RX_LEN;
		i++; 

	}
		 
	   	/*PlotCurve1(&Graph1, hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex);*/ 
		PlotCurve1(&Graph1, hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex,rxIdmeasured);

		switch(TestPara.testMode)
		{
			case NO_SWEEP_IT:
			case NO_SWEEP_RT:
			case SWEEP_IV:
			case ID_T:	
				
				 if((RxData.rxStopSign==0x01) || (Graph1.pCurveArray->numOfTotalDots == Graph1.pCurveArray->numOfPlotDots))
				 	TestStop(&RxData,portNumber);
				break;
			case SWEEP_DRAIN_VOL:
			case SWEEP_GATE_VOL:
				if((RxData.rxStopSign == 0x01)&&(Graph1.plotCurveIndex +1 == Graph1.numOfCurve))
				{
					TestStop(&RxData,portNumber);
				}
				else if(RxData.rxStopSign == 0x01)
				{
					curveComplete=1; 
					rows=2;		                 // �ڶ������߿�ʼ ����0������ֵ
					DiscardAsyncTimer(TimerID);  //��һ����֮���ÿ���߽���ʱ�رն�ʱ��
				}
				break;
		}  

	   
}	
	

void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void* callbackData)
{
	int rxNum;																							  
	int i=0;
	static a = 0;
	Rx_CGS_DataTypeDef Rx_CGS_Data;
	rxNum = GetInQLen(controlComPort);  								//��ȡ�����з���������������
	if(rxNum>500) rxNum=500;											//��ֹ�����ڴ淶Χ
	ComRd(controlComPort, (char *)meas_CGS_UartRxBuf, rxNum);	
	
	while(rxNum>=15)
	{			 
		ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);			// �Ӵ�����ȡ��������������
		*(Graph2.pCurveArray->pDotX++) = a++;
		*((Graph2.pCurveArray + 1)->pDotX++) = a-1; 
		*((Graph2.pCurveArray + 2)->pDotX++) = a-1; 
	    *(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 				 //����ʪ��      
		*((Graph2.pCurveArray + 1)->pDotY++) = Rx_CGS_Data.environment_temp;		 //�����¶�     
		*((Graph2.pCurveArray + 2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //ѹǿ    
		(Graph2.pCurveArray +1)->numOfDotsToPlot++;
		(Graph2.pCurveArray +2)->numOfDotsToPlot++; 
		Graph2.pCurveArray->numOfDotsToPlot++; 
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_TEMPERATURE, Rx_CGS_Data.environment_temp);			//��ʾ�¶�   
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_HUMIDITY,  Rx_CGS_Data.humidity);					//��ʾʪ��     
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_PRESSURE, Rx_CGS_Data.pressure*0.001);		 		//��ʾѹǿ         		 
		rxNum -=15; 
		i++; 
	}
	
	PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);//������2ͼ          
}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	//measureComPort=argc;		//pass measureComPort variable 
	measureComPort=5;
	controlComPort=4;
	if(CheckPortStatus(measureComPort, MEASURE_UART_RX_LEN, MeasureComCallback)<0) return -1;
	//if(CheckPortStatus(controlComPort)<0) SA11_Status=0;
	//else SA11_Status=1;
	
	LoadInitPanel(); 
	//CheckPortStatus(controlComPort, 15, CtrlComCallback); //controlComPort
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
