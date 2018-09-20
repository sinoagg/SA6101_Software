#include "Tools.h"
#include <rs232.h>
#include "MainPanel.h"

//==============================================================================
//
// Title:		MainPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 15:58:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "LoadPanel.h"
#include <utility.h>
#include <formatio.h>
#include "asynctmr.h"
#include "MainPanelCb.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Protocol.h"
#include "Timer.h"
#include "SampleCfgPanel.h"
#include "main.h"
#include "ResultMenuPanel.h"
#include "SettingsPanel.h"
#include "File.h"
#include "TablePanel.h"

//==============================================================================
// Constants
#define VAL_TEXTBG                        0xF0F0F0L    //δ��ѡ�б���ɫ
#define VAL_TEXTBG_PRESSED                0x065279L    //��ѡ�б���ɫ
#define TWO_TERMINAL 0
#define EXP_I_T 1
#define EXP_R_T 2
#define EXP_I_V 3
#define FOUR_TERMINAL 4
#define EXP_ID_VDS 5
#define EXP_ID_VGS 6
#define EXP_ID_T 7
#define BGCOLOR 	0xFFFFFF
#define SEARCHCOLOR 0xA8BFCB //��������ɫ

#define ENV_NUM_OF_CURVE 3								//��������Ŀǰֻ��3��
#define DEV_ADDR 1										//�豸��ַ

//==============================================================================
// Types
 GraphTypeDef* pGraph; 

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
FileLableTypeDef *pFileLable[64];									//������FileLable��ָ�룬���ֻ�ܼ���һ���ļ����µ�64���ļ�
PrjHandleTypeDef SingleProject[64];	
char cellRange[] = "A1:Z65536"; 

CmtThreadFunctionID abnmDCThreadId;  //�쳣����ʱ���ݻ��溯�����߳�Id 

int TimerID;
char configSavePath[512]={0};
char table_title_IT[11][20]  ={ "t(s)","I(A)","Vd(mV)"};
char table_title_RT[11][20]  ={ "t(s)","R(Ohm)" ,"Vd(mV)"};
char table_title_IV[11][20]  ={"Vd(mV)","I(A)"};
char table_title_Idt[11][20] ={"t(s)" ,"Id(A)","Vd(mV)","Vg(mV)"}; 
char table_title_IdVd[11][20]={"Vd(mV)","Id(A)","Vg(mV)"};
char table_title_IdVg[11][20]={"Vg(mV)","Id(A)","Vd(mV)"};
int numOfCurve=0;

//==============================================================================
// Global functions
static void InitSingleProject(PrjHandleTypeDef *pSingleProject)
{
	int i;
	for(i=0;i<64;i++)
	{
		(pSingleProject+i)->index=-1;	
	}
}

int CVICALLBACK MAIN_PANEL_Callback (int panel, int event, void *callbackData,
									 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			    ShutDownExcelCB();
			    SaveSystemClose(0);  //��������ر�״̬Ϊ0
			   	QuitUserInterface(0); 
			break;
	}
	return 0;
}

static void DispResultMenu(void)
{
	SetPanelPos(hResultMenuPanel, 105, 305);  
 	//SetPanelSize(hResultMenuPanel, 65, 1293);      
	DisplayPanel(hResultMenuPanel);
}

static void DispResultNumber(void)
{
	SetPanelPos(hResultDispPanel, 105, 1600);
	//SetPanelSize(hResultDispPanel, 449, 320);
	DisplayPanel(hResultDispPanel);
}
static void DispRuntime(int display)
{ 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_SAMPLETIME,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TIME,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TIME_UNIT,ATTR_VISIBLE,display);

}

static void DispEnvironmentCfg(void)
{
	SetPanelPos(hEnvResultPanel, 556, 1600);
	//SetPanelSize(hEnvResultPanel, 449, 320);
	DisplayPanel(hEnvResultPanel);
}

int CVICALLBACK AnalyzeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK_UP:
			
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");   //��Analyze�����������ʱ,Analyzeͼ��ı䣬������������״̬
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
			int val;
	  	    GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
	        if(val)
			{	
		    	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
				DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico");                          
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");              
				SetPanelPos(hGraphPanel, 172, 305);  
				//SetPanelSize(hGraphPanel, 833, 1293);
				SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //���CheckBox��ѡ��״̬����ʾ����graph     
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
				DisplayPanel(hGraphPanel);
				
			}
			else
			{   	
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");//����AnalyzeĬ�ϵ�graphͼ��
				DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");
				SetPanelPos(hGraphPanel, 172, 305);  
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 750);
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
				DisplayPanel(hGraphPanel);
			}
			
			DispResultMenu(); 
			DispEnvironmentCfg();
			DispResultNumber();
		   
			break;
	}
	return 0;
}


int CVICALLBACK SelectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select_pressed.ico");//Select�����,Selectͼ��ı䣬������������״̬  
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");

	 		SetPanelPos(IdVgPanel.panelHandle, 104, 305);
	        DisplayPanel(IdVgPanel.panelHandle);
			HidePanel(hBasicSamplePanel);	 
			HidePanel(hResultDispPanel);
			HidePanel(hEnvResultPanel);
			HidePanel(hEnvCfgPanel);
			HidePanel(hResultDispPanel);
			HidePanel(hTwoTerminalPanel);
			HidePanel(hFourTerminalPanel);
			break;
	}
	return 0;
}

//===================================================
//   Configure_Callback
int CVICALLBACK ConfigureCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
		
	switch (event)
	{
 		case EVENT_LEFT_CLICK_UP:			    //��Configure�����������ʱ,Configureͼ��ı䣬������������״̬ 
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure_pressed.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
			break;
			
	}
		   	TreeCallback(panel, control , event,callbackData,  eventData1,  eventData2);//���� Experiment List��tree�ؼ��Ļص�����

	return 0;
}


static void RunActive()
{
 	SetPanelPos(hResultMenuPanel, 105, 305);  
    
 	DisplayPanel(hResultMenuPanel);  
			
	SetPanelPos(hGraphPanel, 172, 305);  
	SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 680);
	SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
 	DisplayPanel(hGraphPanel);
		   
	SetPanelPos(hResultDispPanel, 105, 1600);
	DisplayPanel(hResultDispPanel);
	SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,0);
	SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,0);
	SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME_UNIT,ATTR_VISIBLE,0);
	SetPanelPos(hEnvResultPanel, 556, 1600);
	DisplayPanel(hEnvResultPanel);
				    
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);				//������ͷ�ʱ, ���ÿ�ʼ��ť      
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       		//�ָ� ֹͣ��ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        		//���� ���水ť
	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
	DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
	DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,1);//���й����н�ֹ������������   
	
	int val;
	  	    GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
	        if(val)
			{	
		    	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
				DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico");                          
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");              
				SetPanelPos(hGraphPanel, 172, 305);  
				//SetPanelSize(hGraphPanel, 833, 1293);
				SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //���CheckBox��ѡ��״̬����ʾ����graph     
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
				DisplayPanel(hGraphPanel);
				
			}
			else
			{   	
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");//����AnalyzeĬ�ϵ�graphͼ��
				DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");
				SetPanelPos(hGraphPanel, 172, 305);  
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 680);
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
				DisplayPanel(hGraphPanel);
			}
	
	
}

int CVICALLBACK StepThreadFunction(void* temp)
{
	int numOfRxCurve=0;
	while(numOfRxCurve < numOfCurve-1)
	{
		if((curveComplete==1)&&(rows>0))															//һ���������ݽ������
		{
			curveComplete=0;
			rows=1;			     //table���еı�־������ÿ�����ߴ�1��ʼ�����һ����
			numOfRxCurve++;
			Graph1.plotCurveIndex++;
			switch(TestPara.testMode)
			{
				case SWEEP_DRAIN_VOL:
					TestPara.VgStart+=TestPara.VgStep;       
					break;
				case SWEEP_GATE_VOL:
					TestPara.VdStart+= TestPara.VdStep;
					break;
			}									   
			
			Delay(1);
			ProtocolCfgTxData(measureComPort, DEV_ADDR, measUartTxBuf);
			Delay(1);
			ProtocolRun(measureComPort, DEV_ADDR, measUartTxBuf);
			double temp=((double)TestPara.timeStep)/1000;
			if(temp<0.03) temp=0.03;													//�����ѯʱ����죬��������ݻ��ң���λ����Ӧ�жϹ���
			TimerID = NewAsyncTimer(temp, -1, 1, TimerCallback, 0);						//Create Asynchronous (Timer time interval according to sample interval, continue generating evernt, enabled, callback function name, passing no pointer)
		}
	
	}
     
	return 0;
}

void CreateMonitorThread(int numOfCurve)
{
	int threadID;
	CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE, StepThreadFunction, NULL, &threadID);	
}

 int CVICALLBACK AbnmDCThreadFunction (void *functionData)
{ 
    int n = 1;   	 //ÿʮ��֮n����һ�λ���ȥ������   
	while(Graph1.pCurveArray->numOfPlotDots < Graph1.pCurveArray->numOfTotalDots)
	{
		if(Graph1.pCurveArray->numOfPlotDots > 0 && Graph1.pCurveArray->numOfPlotDots >= (Graph1.pCurveArray->numOfTotalDots * n) / 10)  //ÿʮ��֮һ���ܵ���ʱ����һ�λ�����
		{
			LaunchExcelCB();
			SaveExcelCB(hTablePanel, TABLE_DISTABLE, cellRange);
			n +=1;
		}
	}
	return 0;
}


int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)																							  
	{
		case EVENT_LEFT_CLICK_UP:
		    RunActive();
			int index;
			GetActiveTreeItem (hExpListPanel, EXP_LIST_TREE, &index);
			if(index==EXP_I_T||index==EXP_R_T||index==EXP_ID_T)
				DispRuntime(1);
			else 
				DispRuntime(0);
			
			FlushInQ(measureComPort);	   												//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(measureComPort);
			
			GraphDeinit(&Graph1);												//�ڴ��ͷ��ڻ�ͼ֮������ڻ�ͼ֮ǰ�ͷŵ��´���
			GraphDeinit(&Graph2);
			
			Graph1.plotCurveIndex=0; 													//ÿ��ʵ�鿪ʼ֮ǰ��ʼ��CurveIndex
			
			curveComplete=0;
			rows=1;
			curveIndex=1;                                                               //�������ע��
			int expType;
			int graphIndex=0;															//currently only deal with one graph circumstance
			int numOfDots=0;
			Table_ATTR.columnWidth= 90;  												//�п�
			DeleteTableRows (hTablePanel, TABLE_DISTABLE, 1, -1); 		
	 		DeleteTableColumns (hTablePanel, TABLE_DISTABLE, 1, -1);					//ÿ��ʵ������֮ǰ�����һ��ʵ���table����  
			DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1, -1, VAL_IMMEDIATE_DRAW); 	//�������ͼ�ϵ���������
			//RefreshGraph (hGraphPanel, GRAPHDISP_GRAPH1);   							 //ˢ������
			//SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH1,ATTR_ENABLE_ZOOM_AND_PAN,1);	//ʹ�ܿؼ������ź��϶�  
			DeleteGraphAnnotation (hGraphPanel, GRAPHDISP_GRAPH1,-1 );                  //����ϸ�ʵ������ע��
			if(GetCtrlVal(hExpListPanel, EXP_LIST_TREE, &expType)<0)
				return -1; 
			TestPara.testMode=(enum TestMode)expType;
			ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf);		//send config to instrument via UART 
			//ClearAxisItems(hGraphPanel, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS);				  
			switch(TestPara.testMode)
			{
			   	case SWEEP_DRAIN_VOL:				 
					if(TestPara.gateOutputMode==VOL_BIAS)
					{
						numOfCurve=1;
					}
					else if(TestPara.gateOutputMode==VOL_STEP)
					{
						numOfCurve=abs(TestPara.VgStart-TestPara.VgStop)/TestPara.VgStep+1; 
					}
					 													
					numOfDots=abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1;
					GraphInit(hGraphPanel, graphIndex, numOfCurve, numOfDots, &Graph1);  //graph set up     
					Table_ATTR.column = 3*numOfCurve;   //����      
					Table_ATTR.row =numOfDots+1; 
					Graph1.pGraphAttr->yAxisHead=1e-13;
	   				Graph1.pGraphAttr->yAxisTail=1.1e-13;
                    Table(table_title_IdVd, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);  	//������³�ʼ�� �����ò����йأ�Ӧ��д���ɺ�*/
					if (TestPara.VdStart>TestPara.VdStop)
					{
						Graph1.pGraphAttr->xAxisHead=TestPara.VdStop;
						Graph1.pGraphAttr->xAxisTail=TestPara.VdStart;
					}else
					{
						Graph1.pGraphAttr->xAxisHead=TestPara.VdStart;
						Graph1.pGraphAttr->xAxisTail=TestPara.VdStop;
					}
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "Vd(mV)");	 
				    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					//newThread
					CreateMonitorThread(numOfCurve);
					break;
				case SWEEP_GATE_VOL:
		      		if(TestPara.drainOutputMode==VOL_BIAS)
					{
						numOfCurve=1;
					 }
					 else if(TestPara.drainOutputMode==VOL_STEP)
					{
						numOfCurve = abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1; //����
					}
				 	
					numOfDots = abs(TestPara.VgStart-TestPara.VgStop)/TestPara.VgStep+1;	  //����  
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);   
					Table_ATTR.row =  numOfDots+1; 	
					Table_ATTR.column = 3*numOfCurve;  
					Graph1.pGraphAttr->yAxisHead=1e-13;
	   				Graph1.pGraphAttr->yAxisTail=1.1e-13; 
					Table(table_title_IdVg, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 	
					if (TestPara.VgStart>TestPara.VgStop)
					{
						Graph1.pGraphAttr->xAxisHead=TestPara.VgStop;
						Graph1.pGraphAttr->xAxisTail=TestPara.VgStart;
					}else
					{
						Graph1.pGraphAttr->xAxisHead=TestPara.VgStart;
						Graph1.pGraphAttr->xAxisTail=TestPara.VgStop;
					}
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "Vg(mV)");	 
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					CreateMonitorThread(numOfCurve);   
					break;
					
				case NO_SWEEP_IT:
					numOfCurve=1;
					numOfDots=TestPara.runTime/(TestPara.timeStep*0.001)+1;  					//��λs
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
					Graph1.pCurveArray->numOfTotalDots = numOfDots;
					Graph1.pCurveArray->time=0;  
					Table_ATTR.column = 3*numOfCurve;  
					Table_ATTR.row =  numOfDots+1;	
					Graph1.pGraphAttr->xAxisHead=0;
//<<<<<<< HEAD
//					Graph1.pGraphAttr->xAxisTail=numOfDots*0.001;
//					Graph1.pGraphAttr->yAxisHead=5.0e-8;
//	   				Graph1.pGraphAttr->yAxisTail=5.08e-8; 
//=======
					Graph1.pGraphAttr->xAxisTail=10;								//X��ĳ�ʼ���̶�
					Graph1.pGraphAttr->yAxisHead=1.47e-5;
	   				Graph1.pGraphAttr->yAxisTail=1.48e-5; 

					Table(table_title_IT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 	
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
				    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
					//SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					//CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, AbnmDCThreadFunction, NULL, &abnmDCThreadId); //�����µ��߳�
					//Y����ɿؼ����ɿ���
					break;
					
				case NO_SWEEP_RT:
					 numOfCurve=1;
					 numOfDots=TestPara.runTime/(TestPara.timeStep*0.001)+1;
					 GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
					 Graph1.pCurveArray->numOfTotalDots  = numOfDots;
					 Table_ATTR.column = 3*numOfCurve;
					 Table_ATTR.row =  numOfDots+1;
					 Graph1.pGraphAttr->xAxisHead=0;
					 Graph1.pGraphAttr->xAxisTail=numOfDots*0.001;
					 Graph1.pGraphAttr->yAxisHead=5.51e+3;
	   				 Graph1.pGraphAttr->yAxisTail=5.55e+3;
					 Table(table_title_RT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 	
					 SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					 SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  
					 SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "R(Ohm)");
					//SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					 break;
					
				case SWEEP_IV:
					numOfCurve=1;  
					numOfDots = abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1;
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
					Table_ATTR.column = 2*numOfCurve;
					Table_ATTR.row =  numOfDots+1;
					Graph1.pGraphAttr->yAxisHead=1e-13;
	   				Graph1.pGraphAttr->yAxisTail=1.1e-13; 
					Table(table_title_IV, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
					if (TestPara.VgStart>TestPara.VgStop)
					{
						Graph1.pGraphAttr->xAxisHead=TestPara.VgStop;
						Graph1.pGraphAttr->xAxisTail=TestPara.VgStart;
					}else
					{
						Graph1.pGraphAttr->xAxisHead=TestPara.VgStart;
						Graph1.pGraphAttr->xAxisTail=TestPara.VgStop;
					}
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "V(mV)");		  
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					break;
					
				case ID_T:
					numOfCurve=1;
					numOfDots=TestPara.runTime/(TestPara.timeStep*0.001)+1; 
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
				 	Graph1.pCurveArray->numOfTotalDots  = numOfDots;
			    	Table_ATTR.column = 4*numOfCurve;
					Table_ATTR.row =  numOfDots+1;
				    Graph1.pGraphAttr->xAxisHead=0;
					Graph1.pGraphAttr->xAxisTail=numOfDots*0.001; 
					Graph1.pGraphAttr->yAxisHead=1.6e-3;
	   				Graph1.pGraphAttr->yAxisTail=1.64e-3; 
					Table(table_title_Idt, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 	
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	 
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					//SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					break;
			}
			
			SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH2,ATTR_ENABLE_ZOOM_AND_PAN,1);							//ʹ�ܿؼ������ź��϶�  
			DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH2, -1 , VAL_IMMEDIATE_DRAW); 							//����ϸ�ʵ���������
			
			GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+1, &Graph2); 							//��ʼ��ͼ2 
			Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 	//�õ����ߵ����� 
			Delay(0.2);												  											//�����ú���������֮�����λ��0.2�봦��
			ProtocolRun(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);										//send RUN command to instrument via UART
			double temp=((double)TestPara.timeStep)/1000;
			if(temp<0.03) temp=0.03;																			//�����ѯʱ����죬��������ݻ��ң���λ����Ӧ�жϹ���
			TimerID = NewAsyncTimer(temp, -1, 1, TimerCallback, 0);												//Create Asynchronous (Timer time interval according to sample interval, continue generating evernt, enabled, callback function name, passing no pointer)
			break;
	}
	return 0;
}

int CVICALLBACK StopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ
			DiscardAsyncTimer(TimerID);											//ֹͣquery��ʱ����ѯ
			Delay(0.1);															//�ڲ�ѯ��ֹͣ������0.1��
			ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send STOP command to instrument via UART 
			Delay(0.1);	
			FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(measureComPort);
		  	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
		    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0);   //�ָ�������������
			numOfCurve = 0;
 							
		break;
	}
	return 0;
}

int CVICALLBACK SaveCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ
			DisplayImageFile (hMainPanel, MAIN_PANEL_SAVE, "Resource\\Save_pressed.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_SAVE, "Resource\\Save.ico");
			if(FileSelectPopupEx("C:\\SINOAGG\\SA6101\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1,  configSavePath)>0)
				SaveConfigToFile(configSavePath);
			break;
	}
	return 0;
}




int CVICALLBACK SettingsCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
	        InstallPopup (hSettingsPanel);    //����hSettingsPanel 
			SetPanelPos(hSettingsPrjPanel, 5, 170);
			//SetPanelSize(hSettingsPrjPanel, 350, 650);
			DisplayPanel(hSettingsPrjPanel);

			break;
	}
	return 0;
}

static int SaveAllPanelState(char* pConfigSavePath)
{
	SavePanelState(IdVdPanel.panelHandle, pConfigSavePath, 1);						
	SavePanelState(IdVgPanel.panelHandle, pConfigSavePath, 2);						
	SavePanelState(hIT_Panel, pConfigSavePath, 3);
	SavePanelState(hRT_Panel, pConfigSavePath, 4);
	SavePanelState(hIV_Panel,pConfigSavePath, 5);
	SavePanelState(hIdtPanel, pConfigSavePath, 6);
	SavePanelState(hBasicSamplePanel, pConfigSavePath, 10);
	SavePanelState(hAdvanceSamplePanel, pConfigSavePath, 11);
	SavePanelState(hEnvCfgPanel, pConfigSavePath, 14);
	SavePanelState(hSettingsPrjPanel, pConfigSavePath, 15);
	SavePanelState(hSettingsGraphPanel, pConfigSavePath, 16);
	return 0;
}

static int SaveConfigToFile(char* pConfigSavePath)
{
	FILE * fp = NULL;							//��ʾ�򿪵��ļ�
	fp = fopen(pConfigSavePath, "w");
	if(fp == NULL)
	{
		MessagePopup ("Error", "Invalid Path, please select path to save configurations.");
		if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\Users\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, pConfigSavePath)<0)
			return -1;
	}
	else
	{
		int maxCommentSize=255;
		char description[maxCommentSize];
		PromptPopup("Message", "Please enter description for this configuration:", description, maxCommentSize-1);
		//fprintf(fp, "Date:%s	Time:%s\r\n", DateStr(), TimeStr());
		SaveAllPanelState(pConfigSavePath);		//���������������� 
		fp = fopen(pConfigSavePath, "a+");
		fprintf(fp, "\r\n%-61s\r\n", description);		//��������64�ַ�
		fclose(fp);//�ر��ļ�
		
	}
	return 0;
	
}													

static int LoadAndDispPrj(FileLableTypeDef *pFileLable, char index)						//indexΪprj����λ������
{
	int hSinglePrjPanel;
	if ((hSinglePrjPanel = LoadPanel (hPrjListPanel, "Project.uir", DEFPANEL)) < 0)		//load projects panel
		return -1;
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_NAME, pFileLable->FileName);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DATE, pFileLable->FileDate);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_TIME, pFileLable->FileTime);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DESC, pFileLable->FileDesc);
	SetPanelPos(hSinglePrjPanel, index*117, -10);
	SetPanelSize(hSinglePrjPanel, 115, 1425);
	DisplayPanel(hSinglePrjPanel);
	return hSinglePrjPanel;
}

static int LoadAllProject(char* pProjectSavePath)
{
	char tempFileName[512];
	char tempFilePath[512];
	char index=0;
	char tempPathToSearch[512];
	
	InitSingleProject(SingleProject);
	
	sprintf(tempPathToSearch, "%s%s", pProjectSavePath, "\\*.sac");
	if(0==GetFirstFile(tempPathToSearch, 1, 1, 1, 1, 1, 0, tempFileName))		//�����һ���ļ���ȡ�ɹ�
	{
		sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
		pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
		InitFileLable(pFileLable[index], tempFilePath); 				//���ļ�ʱ����ļ����Ƽ�description����չʾ
		SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
		SingleProject[index].index=index;
		index++;
		
		while(GetNextFile(tempFileName)==0)								//�����ȡ��ȷ��������ȡ
		{
			sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
			pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
			InitFileLable(pFileLable[index], tempFilePath); //���ļ�ʱ����ļ����Ƽ�description
			SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
			SingleProject[index].index=index;
			index++;
			
		}
	}
	return 0;
}

int CVICALLBACK ProjectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
		/*	//SetPanelSize(hPrjPanel,700,1400);
			char ProSavePath[512];
			GetCtrlVal(hSettingsPrjPanel, ENVT_PROPATH, &ProSavePath[0]); 
			Delay(0.1);
			//printf("%s",ProSavePath);
			SetPanelPos(hPrjPanel,150,300);
			InstallPopup (hPrjPanel);
			SetCtrlAttribute(hPrjPanel,PROPANEL_PIC_OPENPRJ , ATTR_DIMMED, 1);
			SetCtrlAttribute(hPrjPanel,PROPANEL_TXT_OPENPRJ , ATTR_TEXT_BGCOLOR,SEARCHCOLOR );
			SetCtrlAttribute(hPrjPanel,PROPANEL_TXT_OPENPRJ , ATTR_DIMMED, 1);
			//SetPanelSize(hPrjListPanel,550,1399);
			SetPanelPos(hPrjListPanel,90,0);
			DisplayPanel(hPrjListPanel); 
			LoadAllProject(ProSavePath);*/
			/*InstallPopup (proPanel);
			SetPanelPos(projectPanel, 85, 0);
			SetPanelSize(projectPanel, 380, 1250);
			DisplayPanel(projectPanel);
			*/
			
			
			InstallPopup (hPrjPanel);
		    SetPanelPos(hPrjListPanel,90,0); 
			SetPanelSize(hPrjListPanel, 700, 1400);
			DisplayPanel(hPrjListPanel);
			LoadAllProject(ProjectSavePath);

			break;
	}	 
	return 0;
}

int CVICALLBACK ToolsCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	
	
		switch(event){
		case EVENT_LEFT_CLICK_UP:
			//SetPanelSize(hToolsPanel,500,500);
			SetPanelPos(hToolsPanel,250,400);
			InstallPopup (hToolsPanel);
		    break;
	}
	return 0;
}


