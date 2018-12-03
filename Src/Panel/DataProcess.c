//==============================================================================
//
// Title:		DataProcess.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/11/27 at 14:53:15 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
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
#include"Cgs_mt.h" 

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

const char IDquery1[] = {0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						 0x00, 0x00, 0x00, 0x00,0x00,0xFF};
const char IDquery2[] = {0x11, 0x03, 0x00, 0x02, 0x00, 0x05, 0x26, 0x99};
int TimerID; 

int rows;         //graph1 table��д���ݱ�־λ
int graphrows;    //graph2
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?


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
		//*measure_Uart_Flag = 1;
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
		//*control_Uart_Flag = 1;
	}
	return Status;
}


int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFunc)(int, int, void*))
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

void CheckCloseCom(int SA6101_UART_Status,unsigned char measureComPort,unsigned char controlComPort)
{
	if(SA6101_UART_Status==1)				//��������豸�򿪵Ļ����ر����ʱ��Ҫ�رն�Ӧ�Ĵ��ڡ��û���ʹ�û��������豸ʱ��û�д򿪣����ԾͲ��ùرա�
	{
		CloseCom(measureComPort);
	}
	if(SA6101_UART_Status==2)				//�����ѧ�豸�򿪵Ļ����ر����ʱ��Ҫ�رն�Ӧ�Ĵ��ڡ��û���ʹ�õ�ѧ�����豸ʱ��û�д򿪣����ԾͲ��ùرա�
	{
		CloseCom(controlComPort);
	}
	if(SA6101_UART_Status==3)				//�����ѧ�ͻ����Ĳ����豸���򿪵Ļ�������ʱ��Ҫͬʱ�ر�
	{
		CloseCom(controlComPort);
		CloseCom(measureComPort);
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
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 32, 32);  //���úʹ򿪴��� 
		    if(b<0 )
			{
				
			}else
			{	
			    ComWrt(i, IDquery1, 32);							//���Ͳ�ѯָ��
				Delay(3);
				strLen = GetInQLen (i);
				ComRd (i,USART_RX_Buffer1,strLen);
				if((USART_RX_Buffer1[1]== '6') && (USART_RX_Buffer1[2] == '1') && (USART_RX_Buffer1[3] == '0') && (USART_RX_Buffer1[4]== '1'))         
				{
					for(int i = 0;i < 24;i++)
					{
					  IDAddrress[i] = USART_RX_Buffer1[i];	
					}
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
			SetBreakOnLibraryErrors (0);			  //24 32
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 40, 40);  //���úʹ򿪴���    input  output
		    if(b<0 ){}								 //32  32
			else
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
 
void SetGraphAnnotation()
{
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, curveIndex+1, ATTR_ANNOTATION_CAPTION_BGCOLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor/*VAL_RED*/);   // ע�ͱ���ɫ
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, curveIndex+1, ATTR_ANNOTATION_CAPTION_COLOR,VAL_WHITE);  //  ע������ɫ
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, curveIndex+1, ATTR_ANNOTATION_LINE_COLOR,(Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor);//ע������ɫ
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, curveIndex+1, ATTR_ANNOTATION_CAPTION_FONT, VAL_MENU_FONT);
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, curveIndex+1, ATTR_ANNOTATION_GLYPH_STYLE, VAL_SOLID_CIRCLE);	//ʵ��Բ
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, curveIndex+1, ATTR_ANNOTATION_GLYPH_COLOR, (Graph1.pCurveArray+ Graph1.plotCurveIndex)->pCurveAttr->lineColor); //ע��Զ����ɫ
	 
}



void TestStop(RxDataTypeDef *pRxData,int portNumber)		  
{
	Delay(1);		                //�ȴ��쳣��������ݻ������
	threadFlag = 0;					//�������ݵ��߳�  
	reTime=0;
	envtTime=0;      
	CountFlag=0;       				//ֹͣ�߳��ж��η���ָ��
	CurveNums=0;					//���ڳ�������ʱ��������ɫ               
	curveComplete=0; 	  			//���ƶ���ģʽ���̱߳�־��                     
	pRxData->rxStopSign=0;    
	control_Uart_Flag = 0;			//ֹͣʱ��������Ҳֹͣ ��Ϊ����һֱ��ѯ������ 
	measure_Uart_Flag = 0;		 	//ֹͣʱ��ѯֹͣ��
	Graph1.plotCurveIndex=0; 
	Graph1.pCurveArray->plotIndex=0;   
	Graph1.pCurveArray->numOfPlotDots=0;
	Delay(0.1);															
	DiscardAsyncTimer(TimerID);			//ֹͣquery��ʱ����ѯ    	   EvtTimerId       
	FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
	FlushOutQ(measureComPort);
	FlushInQ(controlComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
	FlushOutQ(controlComPort);
  	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      	//���� ֹͣ��ť      
    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      	//�ָ� ��ʼ��ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     	//�ָ� ���水ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_PRINT, ATTR_DIMMED,0);     	//�ָ� ��ӡ��ť                   
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0); 	//�ָ�������������
	SetCtrlAttribute (hResultMenuPanel, RESULTMENU_SAVE, ATTR_DIMMED,0);	//�ָ��������ݰ�ť 
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUNAGAIN, ATTR_DIMMED, 0);	//�ָ����ߵ��Ӱ�ť 
	
	AutoSaveSheetAndGraph(); //�Զ���������

}

void TestStopActions(RxDataTypeDef *pRxData,int portNumber,float rxIdmeasured)
{   
	float j;
    switch(TestPara.testMode)
	{				  
		case NO_SWEEP_IT:
		case NO_SWEEP_RT:					 
		case ID_T:
			 if(RxData.rxStopSign==0x01)
			 {
				if((controlComPort>0)&&(temp_flag||humidity_flag ||pressure_flag))
				{
					 j=(float)TestPara.runTime - envtTime*timeSteps;
			         for(int i=0;i<=j;i++)
					 {
					   DisplayEnvtTime(); 
					 }
					 PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);//������2ͼ                                
				}
				 Delay(0.01);
				 TestStop(&RxData,portNumber);
			 }
			break;
		case SWEEP_DRAIN_VOL:
		case SWEEP_GATE_VOL:
			if((RxData.rxStopSign == 0x01)&&(Graph1.plotCurveIndex +1 == Graph1.numOfCurve))//ʵ�����
			{   
				if((controlComPort>0)&&(temp_flag||humidity_flag ||pressure_flag))
				{
					 j = (Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots - Graph2.pCurveArray->numOfPlotDots;                    
			         for(int i=0;i<j;i++)
					 {
					   DisplayEvntIv(); 
					 }
					 PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);//������2ͼ                                
				}
				AddGraphAnnotations(&RxData,rxIdmeasured); 
				TestStop(&RxData,portNumber);
			}
			else if(RxData.rxStopSign == 0x01)											 //һ�����߽���
			{   
				if((controlComPort>0)&&(temp_flag||humidity_flag ||pressure_flag))
				{
					 j = (Graph1.pCurveArray + Graph1.plotCurveIndex )->numOfPlotDots - Graph2.pCurveArray->numOfPlotDots;                    
			         for(int i=0;i<j;i++)
					 {
					   DisplayEvntIv(); 
					 }
					 PlotCurve2(&Graph2, hGraphPanel, GRAPHDISP_GRAPH2);//������2ͼ                                
				}
				AddGraphAnnotations(&RxData,rxIdmeasured);
				DiscardAsyncTimer(TimerID);		
				curveComplete=1; 				   //���ƶ�����ʱ�����߳�
				CountFlag=1;					   //ʵ���������ֹͣʱ��ֹ�ٴν����߳�       
				rows=2;		                       //�ڶ������߿�ʼ ���ݴӵڶ��п�ʼд��
				graphrows=2;					   //����д�����ݴӳ��б�����ڶ��п�ʼ
				GraphDeinit(&Graph2); 
				GraphInit(hGraphPanel,0, 3, Graph1.pCurveArray->numOfTotalDots+100, &Graph2);//Graph1.pCurveArray->numOfTotalDots+3==��zhizheng 
				CurveNums++;
			    (Graph1.pCurveArray+Graph1.plotCurveIndex)->plotIndex=2; //index=1����=0ʱ����ÿ�����ߴ�ͷ��β�ĵ���������                               
				if(TestPara.testMode==SWEEP_DRAIN_VOL)  TestPara.VdStart=vdstart;     
				else if(TestPara.testMode==SWEEP_GATE_VOL)TestPara.VgStart=vgstart;    
				}
			break;
			case SWEEP_IV:          
			if(RxData.rxStopSign == 0x01)
			{   
				TestStop(&RxData,portNumber);
			}
			break;
	}  
}
void AddGraphAnnotations(RxDataTypeDef *pRxData,float rxIdmeasured)
{   
	char curveVg[80];
	char curveVd[80];
	if(TestPara.testMode==SWEEP_DRAIN_VOL)   //idvd
	 {
		 TestPara.VdStart = vdstart;	     //��ӻ���������ע�����ұ�
		 sprintf(curveVg,"%s%d","Vg=",TestPara.VgStart);     
		 if (TestPara.VdStart>TestPara.VdStop)
		 	AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curveVg ,80,0); //ע��λ��
		 else
		 	AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curveVg ,-80,0);   
		 SetGraphAnnotation();
		 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1,curveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVdtest));	
	 } 
	 else if(TestPara.testMode==SWEEP_GATE_VOL)
	 {
	    TestPara.VgStart = vgstart;      
		sprintf(curveVd,"%s%d","Vd=",TestPara.VdStart);                   
		if (TestPara.VgStart>TestPara.VgStop)
			AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curveVd ,80,0);
		else
			AddGraphAnnotation(hGraphPanel,GRAPHDISP_GRAPH1,0.0,0.0,curveVd ,-80,0);  
		SetGraphAnnotation();
		SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1,curveIndex+1, ATTR_ANNOTATION_XVALUE,(double)(pRxData->rxVgtest));	
	 }
	 SetAnnotationAttribute (hGraphPanel, GRAPHDISP_GRAPH1, curveIndex+1, ATTR_ANNOTATION_YVALUE,(double)rxIdmeasured);
	 curveIndex++;
}

void RxDataToGraph(RxDataTypeDef *pRxData,float rxIdmeasured,float ohm)

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

		 
		SetCtrlVal(hResultDispPanel, RESULTDISP_TIME,(pRxData->realTime)*0.001);              
		*(Graph1.pCurveArray->pDotX++)=(pRxData->realTime)*0.001;							//get x, set pointer to the next data
		*(Graph1.pCurveArray->pDotY++)=rxIdmeasured;
	
	}
	else if(TestPara.testMode == NO_SWEEP_RT)
	{
	    SetCtrlVal(hResultDispPanel, RESULTDISP_TIME,(pRxData->realTime)*0.001);              
		*(Graph1.pCurveArray->pDotX++)=(pRxData->realTime)*0.001;
		*(Graph1.pCurveArray->pDotY++)=ohm;   
		SetCtrlVal(hResultDispPanel, RESULTDISP_OHM,ohm);
	}
	else if(TestPara.testMode==ID_T)
	{
		SetCtrlVal(hResultDispPanel, RESULTDISP_VG, pRxData->rxVgtest);  
		SetCtrlVal(hResultDispPanel, RESULTDISP_TIME,(pRxData->realTime)*0.001);              
		*(Graph1.pCurveArray->pDotX++)=(pRxData->realTime)*0.001;	
		*(Graph1.pCurveArray->pDotY++)=rxIdmeasured;  
	}
	
} 		


void RxDataToTable(RxDataTypeDef *pRxData)
{   
	 if(pRxData->rxStopSign!=0x03)
	{
		switch(TestPara.testMode)  	//rows  table���еı�־������ÿ�����ߴ�(rows=2��ʼ�����һ����;һ�����߽���ʱ��2    
		{   
			case SWEEP_IV:
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //д��Xֵ
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //д��Yֵ 
				break;
			case SWEEP_DRAIN_VOL:
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //д��Xֵ
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //д��Yֵ 
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); //���õ�Ԫ����������
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint(Graph1.plotCurveIndex*6+3, rows),(float)pRxData->rxVgtest);  //д��vgֵ������  
				break;
			case SWEEP_GATE_VOL:
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //д��Xֵ
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //д��Yֵ 
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); 
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+3, rows),(float)pRxData->rxVdtest);  //д��vdֵ  
				break;
			case NO_SWEEP_IT:
			case NO_SWEEP_RT:
				//InsertTableRows (hTablePanel, TABLE_DISTABLE,-1 ,1 , VAL_CELL_STRING);
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE, MakeRect(1,1,rows,1), ATTR_PRECISION, 3);	  //ʱ�䱣����λС��
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //д��Xֵ
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //д��Yֵ 
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows),(float)pRxData->rxVdtest);  //д��vdֵ ������
			//	SetCtrlAttribute(hTablePanel,TABLE_DISTABLE, ATTR_FIRST_VISIBLE_ROW,rows);	 
				break;
			case ID_T:
				InsertTableRows (hTablePanel, TABLE_DISTABLE,-1 ,1 , VAL_CELL_STRING);
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE, MakeRect(1,1,rows,1), ATTR_PRECISION, 3);	  //ʱ�䱣����λС�� 
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+1, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //д��Xֵ
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+2, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //д��Yֵ 
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+3, rows),(float)pRxData->rxVdtest);  //д��vdֵ ������
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+4, rows),(float)pRxData->rxVgtest);  //д��vgֵ ����������
			/*	SetCtrlAttribute(hTablePanel,TABLE_DISTABLE, ATTR_FIRST_VISIBLE_ROW,rows);	 */
				break;
	  	} 
		rows++;     
   }
}


void Rx_CGS_DataToTable(Rx_CGS_DataTypeDef* Rx_CGS_Data,float reTime)
{
	int temp,hum,press;
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_TEMPTER,&temp); 
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_HUMIDITY,&hum); 
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_PRESSURE,&press); 
	switch(TestPara.testMode)
	{
		case SWEEP_DRAIN_VOL:   //һ���߶�Ӧ���� ���Դӵ����п�ʼ  
		case SWEEP_GATE_VOL :
			if(temp)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*6+4, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);  //���õ����е�graphrows��Ԫ�����������
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
		case NO_SWEEP_IT:
		case NO_SWEEP_RT:
			SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*8+4, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);  //���õ����е�graphrows��Ԫ�����������
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*8+4, graphrows),reTime) ;  //��������е�graphrows�е�����
			SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE, MakeRect(1,1,rows,4), ATTR_PRECISION, 3);
			/* SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*7+4, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);  //���õ����е�graphrows��Ԫ�����������
			 SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*7+4, graphrows),(float)Rx_CGS_Data->heating_stage_temp) ;  //��������е�graphrows�е�����
			*/
			 if(temp)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*7+5, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);  //���õ����е�graphrows��Ԫ�����������
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*7+5, graphrows),(float)Rx_CGS_Data->heating_stage_temp) ;  //��������е�graphrows�е�����
			}
			if(hum)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*7+6, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);//���������õ�Ԫ����������Ϊ��ֵ��
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*7+6, graphrows),(float)Rx_CGS_Data->humidity); 
			}
			if(press)
			{
			  SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*7+7, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC); //������ 
		    	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*7+7, graphrows),(float)Rx_CGS_Data->pressure); 
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
		    SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*8+5, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);  //���õ����е�graphrows��Ԫ�����������
			SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*8+5, graphrows),reTime) ;  //��������е�graphrows�е�����
			SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE, MakeRect(1,1,rows,5), ATTR_PRECISION, 3);
			 if(temp)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+6, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+6, graphrows),(float)Rx_CGS_Data->heating_stage_temp) ;
	
			}
			if(hum)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+7, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+7, graphrows),(float)Rx_CGS_Data->humidity); 
			}
			if(press)
			{
				SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+8, graphrows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
		    	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*3+8, graphrows),(float)Rx_CGS_Data->pressure); 
			}
			break;
	} 
		graphrows++; 

}

