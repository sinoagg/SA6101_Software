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


unsigned char measure_Uart_Flag = 1; 				//��ѧ�������ڽ���ʱҪ�������ݲ�ѯ 
unsigned char control_Uart_Flag = 1; 				//�����������ڽ���ʱҪ�������ݲ�ѯ

const char IDquery1[] = {0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};
const char IDquery2[] = {0x11, 0x03, 0x00, 0x02, 0x00, 0x05, 0x26, 0x99};

const char CloseIDquery[] = {0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13};

char USART_RX_Buffer[50];   //���� 



extern int TimerID;
extern int threadFlag;			 //�̱߳�־λ 
extern int CountFlag;			 //��־��ֹͣʱ���ڽ���������߳�
extern int CurveNums;   		 //������������4ʱ��ʼ����仯��
unsigned char measureComPort;	 //Serial Com Number
unsigned char controlComPort;

unsigned char measUartTxBuf[32]={0};
unsigned char measUartRxBuf[1024]={0};


unsigned char curveComplete;
int rows;         //graph1 table��д���ݱ�־λ
int curveIndex ;  //ע��
int graphrows;    //graph2
int x2 = 0;		  //����
int xAxis=0;	  //���ڵ������������������
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
	//rows  table���еı�־������ÿ�����ߴ�(rows=2��ʼ�����һ����;һ�����߽���ʱ��2 
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //д��Xֵ
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //д��Yֵ 
	switch(TestPara.testMode)
	{    
		case SWEEP_DRAIN_VOL:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); //���õ�Ԫ����������
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint(Graph1.plotCurveIndex*6+3, rows),(float)pRxData->rxVgtest);  //д��vgֵ������  
			break;
		case SWEEP_GATE_VOL:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); 
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+3, rows),(float)pRxData->rxVdtest);  //д��vdֵ  
			break;
		case NO_SWEEP_IT:
		case NO_SWEEP_RT:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows),(float)pRxData->rxVdtest);  //д��vdֵ ������
			break;
		case ID_T:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows),(float)pRxData->rxVdtest);  //д��vdֵ ������
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, rows),(float)pRxData->rxVgtest);  //д��vgֵ ����������
		   	break;
	  }
	  rows++;      
}

void SetGraphAnnotation()
{
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_BGCOLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor/*VAL_RED*/);   // ע�ͱ���ɫ
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_COLOR,VAL_WHITE);  //  ע������ɫ
	 ProcessDrawEvents();
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YAXIS, VAL_LEFT_YAXIS);
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XAXIS, VAL_BOTTOM_XAXIS); // pGraph->pCurveArray->pCurveAttr->lineColor
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_LINE_COLOR,(Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor);//ע������ɫ
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_FONT, VAL_MENU_FONT);
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_GLYPH_STYLE, VAL_SOLID_CIRCLE);	//ʵ��Բ
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_GLYPH_COLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor); //ע��Զ����ɫ
	 //SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_CAPTION_COLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor);
	 ProcessDrawEvents(); 
}
 static void AddGraphAnnotations(RxDataTypeDef *pRxData,float rxIdmeasured)
{
	 
	 if(TestPara.testMode==SWEEP_DRAIN_VOL)   //idvd
	 {
		 char curve[80];
		 sprintf(curve,"%s%d","Vg=",pRxData->rxVgtest);
		 if (TestPara.VdStart>TestPara.VdStop)
		 	AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve ,20,-20); //ע��λ��
		 else 
			AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve ,-55,25);          	 
		 SetGraphAnnotation();
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVdtest));	

	 } 
	 else if(TestPara.testMode==SWEEP_GATE_VOL)
	 {
		 char curve[80];
		 sprintf(curve,"%s%d","Vd=",pRxData->rxVdtest);
		 if (TestPara.VgStart>TestPara.VgStop)
		 	AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve ,20,-20);
		 else 
		 	AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curve ,-55,15);     
		SetGraphAnnotation();
		SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVgtest));	
	 }
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex+1, ATTR_ANNOTATION_YVALUE,(double)rxIdmeasured);
     curveIndex++;
}

static void TestStop(RxDataTypeDef *pRxData,int portNumber)
{
	
	threadFlag = 0;					//�������ݵ��߳�
	control_Uart_Flag = 0;			//ֹͣʱ��������Ҳֹͣ ��Ϊ����һֱ��ѯ������ 
	xAxis=0; 						//���ƻ������ߵ�X��仯
	x2=0;							//����������0
	CountFlag=0;       				//ֹͣ�߳��ж��η���ָ��
	Graph1.pCurveArray->numOfPlotDots=0; 
	pRxData->rxStopSign=0;
	curveComplete=0; 	  			//���ƶ���ģʽ���̱߳�־��
	CurveNums=0;					//���ڳ�������ʱ��������ɫ
	measure_Uart_Flag=0;		 	 //ֹͣʱ��ѯֹͣ��    
	DiscardAsyncTimer(TimerID);											//ֹͣquery��ʱ����ѯ
	Delay(0.1);															//�ڲ�ѯ��ֹͣ������0.1��
	ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send STOP command to instrument via UART 
	Delay(0.1);	
	FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
	FlushOutQ(measureComPort);
	FlushInQ(controlComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
	FlushOutQ(controlComPort);
  	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0);   //�ָ�������������
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR1,0xFF4600);//��ɫϵ
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR2,0x24786E);//��ɫϵ
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR3,0x008FFF);//��ɫϵ
		
	
}


void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData)
{

	control_Uart_Flag = 0;
	measure_Uart_Flag = 0;  
	int rxNum=0;																//�����յ��ֽ���
	int i=0;																	//�������֡��
	RxDataTypeDef RxData;
	RxData.rxStopSign=0x00;
    float rxIdmeasured=0;
	
	rxNum = GetInQLen(portNumber);  											//��ȡ�����з���������������
	if(rxNum>1024) rxNum=1024;													//��ֹ�����ڴ淶Χ
	rxNum-=rxNum%MEASURE_UART_RX_LEN;											//ֻ��ȡ�����ַ��������������ݣ�������ɢ����
	ComRd(portNumber, (char *)measUartRxBuf, rxNum);							//Read UART Buffer to local buffer at one time
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
		SetGraphX_Axis(hGraphPanel,GRAPHDISP_GRAPH1,&Graph1);
		switch(TestPara.testMode)
		{
			case NO_SWEEP_IT:
			case NO_SWEEP_RT:
			case SWEEP_IV:
			case ID_T:
				 if((RxData.rxStopSign==0x01) || (Graph1.pCurveArray->numOfTotalDots <= Graph1.pCurveArray->numOfPlotDots))//���ڵ���0��
				 {
					 TestStop(&RxData,portNumber);
				 }
				break;
			case SWEEP_DRAIN_VOL:
			case SWEEP_GATE_VOL:
				if((RxData.rxStopSign == 0x01)&&(Graph1.plotCurveIndex +1 == Graph1.numOfCurve))//ʵ�����
				{   
					AddGraphAnnotations(&RxData,rxIdmeasured); 
					TestStop(&RxData,portNumber);
				}
				else if(RxData.rxStopSign == 0x01)											 //һ�����߽���
				{   
					AddGraphAnnotations(&RxData,rxIdmeasured);  
					curveComplete=1; 				   //���ƶ�����ʱ�����߳�
					CountFlag=1;					   //ʵ���������ֹͣʱ��ֹ�ٴν����߳�       
					xAxis = 0;						   //it��rt��idt��ģʽ�µ�X��仯
					x2=0;							   //���ڻ������߲������
					rows=2;		                       //�ڶ������߿�ʼ ���ݴӵڶ��п�ʼд��
					graphrows=2;					   //����д�����ݴӳ��б�����ڶ��п�ʼ
					GraphDeinit(&Graph2); 
					GraphInit(hGraphPanel,0, 3, Graph1.pCurveArray->numOfTotalDots+3, &Graph2);//Graph1.pCurveArray->numOfTotalDots+3==��zhizheng 
					DiscardAsyncTimer(TimerID);       //��һ����֮���ÿ���߽���ʱ�رն�ʱ��
					CurveNums++; 
				}
				break;
		}  
	  control_Uart_Flag = 1;
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
		case SWEEP_DRAIN_VOL:   //һ���߶�Ӧ���� ���Դӵ����п�ʼ  
		case SWEEP_GATE_VOL :
		case NO_SWEEP_IT:
		case NO_SWEEP_RT:
			if(temp)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+4, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);  /
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+4, graphrows),(float)Rx_CGS_Data->heating_stage_temp) ;  //��������е�graphrows�е�����
	
			}
			if(hum)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+5, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);//���������õ�Ԫ����������Ϊ��ֵ��
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+5, graphrows),(float)Rx_CGS_Data->humidity); 
			}
			if(press)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+6, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); //������ 
		    	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+6, graphrows),(float)Rx_CGS_Data->pressure); 
			}
		break;
		case SWEEP_IV:   //һ���߶�Ӧ���� ���Դӵ����п�ʼ
			 if(temp)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, graphrows),(float)Rx_CGS_Data->heating_stage_temp) ;
	
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
		case ID_T:		 //һ���߶������� �ӵ����п�ʼ
			 if(temp)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+5, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+5, graphrows),(float)Rx_CGS_Data->heating_stage_temp) ;
	
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
	measure_Uart_Flag =0;
	control_Uart_Flag = 0;														//����ʱ���β�ѯ�����ڲ�ѯ����
	int rxNum;
	int i,j;
	Rx_CGS_DataTypeDef Rx_CGS_Data;
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
					/*	(Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots - x2;*/   //j=>����ȱ�ٵ���
					for(i = 0; i<=j; i++)
					{
						*(Graph2.pCurveArray->pDotX++) = x2;
						*((Graph2.pCurveArray +1)->pDotX++) = x2; 
						*((Graph2.pCurveArray +2)->pDotX++) = x2; 

						*(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 			//����ʪ��      
						*((Graph2.pCurveArray+1)->pDotY++) = Rx_CGS_Data.heating_stage_temp;	//��̨�¶�     
						*((Graph2.pCurveArray+2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		//ѹǿ

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
					j = (Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots - Graph2.pCurveArray->numOfPlotDots;   //j=>����ȱ�ٵ���    
					for(i = 0; i<=j; i++)
					{											 
						*(Graph2.pCurveArray->pDotX++) = xAxis* TestPara.timeStep*0.001;	
						*((Graph2.pCurveArray +1)->pDotX++) =xAxis* TestPara.timeStep*0.001;	 
						*((Graph2.pCurveArray +2)->pDotX++) =xAxis* TestPara.timeStep*0.001;	
						xAxis++;          
						*(Graph2.pCurveArray->pDotY++) = Rx_CGS_Data.humidity; 		 			 //����ʪ��      
						*((Graph2.pCurveArray+1)->pDotY++) = Rx_CGS_Data.heating_stage_temp;	 //��̨�¶�     
						*((Graph2.pCurveArray+2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //ѹǿ
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
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_TEMPERATURE, Rx_CGS_Data.heating_stage_temp);		//��̨�¶�   
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_HUMIDITY,  Rx_CGS_Data.humidity);					//��ʾʪ��     
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_PRESSURE, Rx_CGS_Data.pressure*0.001);		 		//��ʾѹǿ
										
	Graph2.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph2.graphIndex,Graph2.plotCurveIndex); 	//�õ����ߵ�����
	PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);//������2ͼ 
//	if(controlFlag==1 && controlComPort>0)
	SetGraphX_Axis(hGraphPanel,GRAPHDISP_GRAPH2,&Graph2);        
	control_Uart_Flag = 1;
	measure_Uart_Flag = 1;
}
void CheckCloseCom(int SA3102_UART_Status,unsigned char measureComPort,unsigned char controlComPort)
{
	if(SA3102_UART_Status==1)				//��������豸�򿪵Ļ����ر����ʱ��Ҫ�رն�Ӧ�Ĵ��ڡ��û���ʹ�û��������豸ʱ��û�д򿪣����ԾͲ��ùرա�
	{
		CloseCom(measureComPort);
	}
	if(SA3102_UART_Status==2)				//�����ѧ�豸�򿪵Ļ����ر����ʱ��Ҫ�رն�Ӧ�Ĵ��ڡ��û���ʹ�õ�ѧ�����豸ʱ��û�д򿪣����ԾͲ��ùرա�
	{
		CloseCom(controlComPort);
	}
	if(SA3102_UART_Status==3)				//�����ѧ�ͻ����Ĳ����豸���򿪵Ļ�������ʱ��Ҫͬʱ�ر�
	{
		CloseCom(controlComPort);
		CloseCom(measureComPort);
	}
}
int CheckOpenCom(unsigned char* measureComPort,unsigned char* controlComPort,unsigned char* measure_Uart_Flag,unsigned char* control_Uart_Flag)
{
	int Status = 0; 
	if(CheckPortStatus(*measureComPort, MEASURE_UART_RX_LEN, MeasureComCallback)<0)
	{
		Status=0;															//���ڴ�ʧ��
		*measure_Uart_Flag = 0;
		MessagePopup("Error","Failed to open the serial port of electrical measuring equipment"); 
		//Ҫ����������Ҫ���ô˴��ڵĲ�������
	}
	else 
	{
		Status=1;															//���ڴ򿪳ɹ� 
		*measure_Uart_Flag = 1;
	}
	if(CheckPortStatus(*controlComPort, 15, CtrlComCallback)<0)						//�жϻ��������豸��Ӧ�Ĵ����Ƿ����ӳɹ�
	{
		*control_Uart_Flag = 0;
		Status = Status + 0;     
		MessagePopup("Error","Failed to open the serial port of the environmental measuring equipment.Please check the communication line"); 
	}
	else
	{
		Status=Status + 2;
		*control_Uart_Flag = 1;
	}
	return Status;
}

int main (int argc, char *argv[])
{
	int SA11_UART_Status=0;																						//open comport status 
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	DeviceQuery();																								//�ж��豸��Ӧ�Ĵ����Ƿ����ӳɹ�
	SA11_UART_Status = CheckOpenCom(&measureComPort,&controlComPort,&measure_Uart_Flag,&control_Uart_Flag);	
	LoadInitPanel(); 
	RunUserInterface();
	CheckCloseCom(SA11_UART_Status,measureComPort,controlComPort);
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
	char USART_RX_Buffer1[40];   //����
	char USART_RX_Buffer2[40];   //����
	int b,strLen;
	for(i = 1; i<=10; i++)
		{
			SetBreakOnLibraryErrors (0);
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 30, 30);  //���úʹ򿪴��� 
		    if(b<0 )
			{
				
			}else
			{	
			    ComWrt(i, IDquery1, 30);							//���Ͳ�ѯָ��
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

				SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//��Ӳ������
			}
       }
	   
	   	for(i = 1; i<=10; i++)
		{
			SetBreakOnLibraryErrors (0);
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 30, 30);  //���úʹ򿪴��� 
		    if(b<0 )
			{
				
			}else
			{	
			    ComWrt(i, IDquery2, 8);							//���Ͳ�ѯָ��
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
				SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//��Ӳ������

			}
       }
	   Delay(1); 
}

