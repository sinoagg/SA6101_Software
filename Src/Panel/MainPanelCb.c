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
#include "time.h" 
//#include "SampleCfgPanel.h"
#include "Sample Configuration.h"  
#include "main.h"
#include "ResultMenuPanel.h"
#include "SettingsPanel.h"
#include "File.h"
#include "TablePanel.h"
#include "Plot.h"
#include "AutoSaveDataPanel.h" 
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
#define randFloat (double)rand()/RAND_MAX  
#define ENV_NUM_OF_CURVE 3								//��������Ŀǰֻ��3��
#define DEV_ADDR 1										//�豸��ַ

//==============================================================================
// Types
 GraphTypeDef* pGraph; 
 struct tm *tmp_ptr ;  
//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
FileLableTypeDef *pFileLable[64];									//������FileLable��ָ�룬���ֻ�ܼ���һ���ļ����µ�64���ļ�
PrjHandleTypeDef SingleProject[64];	
int threadFlag = 0;			 //�̱߳�־λ
int CurveNums=1; 
int CountFlag=0;
CmtThreadFunctionID abnmDCThreadId;  //�쳣����ʱ���ݻ��溯�����߳�Id 
int TimerID;
int  EvtTimerId;
char configSavePath[512]={0};
int numOfCurve=0;
int vdstart=0;
int vgstart=0;
unsigned int graphColor = 0;
unsigned int graphColor1 = 0;  
unsigned int graphColor2 = 0;  
float timeStep = 0;
int drain;
int gate;
char tableTitleLog_IT[11][20]  ={ "t(s)","log10(I)/A","Vd(mV)","t(s)","Temp(Celsius)","Hum(%RH)","Press(Pa)"};
char tableTitleLog_RT[11][20]  ={ "t(s)","R(Ohm)" ,"Vd(mV)","t(s)","Temp(Celsius)","Hum(%RH)","Press(Pa)"};
char tableTitleLog_IV[11][20]  ={"Vd(mV)","log10(I)/A","Temp(Celsius)","Hum(%RH)","Press(Pa)"};
char tableTitleLog_Idt[11][20] ={"t(s)" ,"log10(Id)/A","Vd(mV)","Vg(mV)","t(s)","Temp(Celsius)","Hum(%RH)","Press(Pa)"}; 
char tableTitleLog_IdVd[11][20]={"Vd(mV)","log10(Id)/A","Vg(mV)","Temp(Celsius)","Hum(%RH)","Press(Pa)"};
char tableTitleLog_IdVg[11][20]={"Vg(mV)","log10(Id)/A","Vd(mV)","Temp(Celsius)","Hum(%RH)","Press(Pa)"};
char table_title_IT[11][20]  ={ "t(s)","I(A)","Vd(mV)","t(s)","Temp(Celsius)","Hum(%RH)","Press(Pa)"};
char table_title_RT[11][20]  ={ "t(s)","R(Ohm)" ,"Vd(mV)","t(s)","Temp(Celsius)","Hum(%RH)","Press(Pa)"};
char table_title_IV[11][20]  ={"Vd(mV)","I(A)","Temp(Celsius)","Hum(%RH)","Press(Pa)"};
char table_title_Idt[11][20] ={"t(s)" ,"Id(A)","Vd(mV)","Vg(mV)","t(s)","Temp(Celsius)","Hum(%RH)","Press(Pa)"}; 
char table_title_IdVd[11][20]={"Vd(mV)","Id(A)","Vg(mV)","Temp(Celsius)","Hum(%RH)","Press(Pa)"};
char table_title_IdVg[11][20]={"Vg(mV)","Id(A)","Vd(mV)","Temp(Celsius)","Hum(%RH)","Press(Pa)"};

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
				SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //���CheckBox��ѡ��״̬����ʾ����graph     
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_VISIBLE,1); 
				DisplayPanel(hGraphPanel);
				
			}
			else
			{   	
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");//����AnalyzeĬ�ϵ�graphͼ��
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 750);
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_VISIBLE, 1);             
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
			
			}
			DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico");                          
			DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
			DisplayPanel(hGraphPanel);               
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
			HidePanel(hGraphPanel); //����graph����������    
			HidePanel(hTablePanel);
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
			HidePanel(hGraphPanel); //����graph����������    
			HidePanel(hTablePanel);
			break;
			
	}
		   	TreeCallback(panel, control , event,callbackData,  eventData1,  eventData2);//���� Experiment List��tree�ؼ��Ļص�����

	return 0;
}


static void RunActive()
{
 	SetPanelPos(hResultMenuPanel, 105, 305);  
 	DisplayPanel(hResultMenuPanel);  
	SetPanelPos(hResultDispPanel, 105, 1600);
	DisplayPanel(hResultDispPanel);
	SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,0);
	SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,0);
	SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME_UNIT,ATTR_VISIBLE,0);
	SetPanelPos(hEnvResultPanel, 556, 1600);
	DisplayPanel(hEnvResultPanel);
	DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");   //,Analyzeͼ��ı䣬������������״̬
	DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
	DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");	
	DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);				//������ͷ�ʱ, ���ÿ�ʼ��ť    RUNAGAIN  
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       		//�ָ� ֹͣ��ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_PRINT, ATTR_DIMMED,1);        		//���� ���������ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        		//���� ��ӡ��ť  
	SetCtrlAttribute (hResultMenuPanel, RESULTMENU_SAVE, ATTR_DIMMED,1); 		//���� �������ݰ�ť            
	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
	DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
	DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,1);//���й����н�ֹ������������  
	//��ʼʱ��Ϊ0
	float press = 0.00;
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_TEMPERATURE, 0);		//��̨�¶�   
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_HUMIDITY,  0);			//��ʾʪ��     
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_PRESSURE,press);		 	//��ʾѹǿ
	int val;	//	SetCtrlAttribute (hTablePanel, TABLE_DISTABLE, ATTR_VISIBLE,0 );   
    GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
    if(val)
			{	
		    	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
				SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //���CheckBox��ѡ��״̬����ʾ����graph     
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_VISIBLE,1); 
				DisplayPanel(hGraphPanel);
				
			}
			else
			{   	
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");//����AnalyzeĬ�ϵ�graphͼ��
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 750);
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_VISIBLE, 1);             
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
			
			}
			DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico");                          
			DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
			DisplayPanel(hGraphPanel);               
	
	int index;
	GetActiveTreeItem (hExpListPanel, EXP_LIST_TREE, &index);
	if(index==EXP_I_T||index==EXP_R_T||index==EXP_ID_T)
		DispRuntime(1);
	else 
		DispRuntime(0);
	FlushInQ(measureComPort);	   												//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
	FlushOutQ(measureComPort);
	FlushInQ(controlComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
    FlushOutQ(controlComPort);	
	//============ ��֤ǰ������ɫһ��==========
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR1,0xFF4600);//��ɫϵ
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR2,0x24786E);//��ɫϵ
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR3,0x008FFF);//��ɫϵ   	
   //=======================================================
  	
   
   

}
void SetGraph2DisplayData()
{
	int valMeasure; //Measure ��ѡ 
	int tempter;
	int hum;
	int press;
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_MEASURE,&valMeasure); //����֮ǰ��ѡ���Ƿ���ʾ����
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_TEMPTER,&tempter); 
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_HUMIDITY,&hum); 
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_PRESSURE,&press); 
	if(controlComPort>0)
	{
		if(valMeasure)
		{	
			control_Uart_Flag=1;
			SetCtrlVal(hEnvResultPanel,ENVIRPANEL_TEMP_BOX,valMeasure);//��ʼ����ʱ��Ӧ���������Ƿ�ѡ��
			SetCtrlVal(hEnvResultPanel,ENVIRPANEL_HUM_BOX,valMeasure);
			SetCtrlVal(hEnvResultPanel,ENVIRPANEL_PRESS_BOX,valMeasure);
		}
		else
		{
			control_Uart_Flag=0;      
			SetCtrlVal(hEnvResultPanel,ENVIRPANEL_TEMP_BOX,0);
			SetCtrlVal(hEnvResultPanel,ENVIRPANEL_HUM_BOX,0);
			SetCtrlVal(hEnvResultPanel,ENVIRPANEL_PRESS_BOX,0 );	
		}
		if(tempter)
		{
			control_Uart_Flag=1; 
			SetCtrlVal(hEnvResultPanel,ENVIRPANEL_TEMP_BOX,tempter); 
		}
		if(press)
		{
			control_Uart_Flag=1;
			SetCtrlVal(hEnvResultPanel,ENVIRPANEL_PRESS_BOX,press);
		}
		if(hum)
		{
			control_Uart_Flag=1;      
			SetCtrlVal(hEnvResultPanel,ENVIRPANEL_HUM_BOX,hum);	
		}
	}
	else 
	{
		control_Uart_Flag=0;
	}
}


void MakeColors()	  //�������������ɫ
{
	graphColor = MakeColor (randFloat * 255, randFloat * 255, randFloat * 255);//���������ͬ��������ɫ       
	graphColor1 = MakeColor (randFloat * 254, randFloat * 255, randFloat * 255);//���������ͬ��������ɫ        
	graphColor2 = MakeColor (randFloat * 255, randFloat * 255, randFloat * 254);//���������ͬ��������ɫ        
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR1,graphColor);
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR2,graphColor1);
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR3,graphColor2);
 }


int CVICALLBACK StepThreadFunction(void* temp)
{
	int direction;
	GetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_DIRECTION, ATTR_CTRL_VAL,&direction); 
	int numOfRxCurve=0;
	  
		while(numOfRxCurve < numOfCurve-1)
		{
			if((curveComplete==1)&&(rows>0))															//һ���������ݽ������
			{
				curveComplete=0;
				rows=2;			     //table���еı�־������ÿ�����ߴӵڶ��п�ʼ�����һ����
				graphrows=2;		 //table�л�������д��ı�ʾ��
				numOfRxCurve++;
				Graph1.plotCurveIndex++;
				DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH2, -1, VAL_IMMEDIATE_DRAW); 	//�������ͼ�ϵ��������� 
				if(CurveNums>2) 
				{
					MakeColors();
				}
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 	//�õ����ߵ����� 
				switch(TestPara.testMode)
					{
						case SWEEP_DRAIN_VOL:			//idvd  =>vg
							TestPara.VgStart+=TestPara.VgStep;      
						break;
						  								//idvg  =>vd
						case SWEEP_GATE_VOL:
							TestPara.VdStart+=TestPara.VdStep;   
						break;
					}
				Delay(0.5);    
				if((drain==0)&&(gate==1))
				{ 																								  //0x04 
					ProtocolCfgTxData(measureComPort, DEV_ADDR, measUartTxBuf,ONLYGATE); 
				}
				else if(drain && gate)
				{  																								  //0x0c
				    ProtocolCfgTxData(measureComPort, DEV_ADDR, measUartTxBuf,BOTH); 	//send config to instrument via UART               	
				}
				else if((drain==1)&&(gate==0))
				{																								   //0x08      
					 ProtocolCfgTxData(measureComPort, DEV_ADDR, measUartTxBuf,NOLYDRAIN); 
				}
				else  if((drain==0)&&(gate==0))
				{																								   //0x00
					ProtocolCfgTxData(measureComPort, DEV_ADDR, measUartTxBuf,BOTHNONE);       
				}
				Delay(0.5);    
				if(CountFlag==1)
					{
						ProtocolRun(measureComPort, DEV_ADDR, measUartTxBuf);
						/*double temp = TestPara.timeStep*0.001;
						if(temp<0.03) temp=0.03;*/													//�����ѯʱ����죬��������ݻ��ң���λ����Ӧ�жϹ���
						double temp=0.05;        
						TimerID = NewAsyncTimer(temp, -1, 1, TimerCallback, 0);						//Create Asynchronous (Timer time interval according to sample interval, continue generating evernt, enabled, callback function name, passing no pointer)
					}
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
   /* int n = 1;  */ 	  
	while(threadFlag == 1)
	{
		if(Graph1.pCurveArray->numOfPlotDots > 0)  //ÿʮ��֮һ���ܵ���ʱ����һ�λ�����
		{
		    WriteAndSaveExcel(hTablePanel, TABLE_DISTABLE);
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
			threadFlag = 0; 
			CountFlag = 0;	  													//��־��ֹͣʱ���ڽ���������߳�   
			CurveNums=1;														//��������������ɫ
			GraphDeinit(&Graph1);												//�ڴ��ͷ��ڻ�ͼ֮������ڻ�ͼ֮ǰ�ͷŵ��´���
			GraphDeinit(&Graph2);
			FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(measureComPort);
			FlushInQ(controlComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(controlComPort);	
			Graph1.plotCurveIndex=0; 											//ÿ��ʵ�鿪ʼ֮ǰ��ʼ��CurveIndex
			curveComplete=0;
			rows=2;
			graphrows=2;
			controlTime=0;
			int expType;
			int log;
			int graphIndex=0;															//currently only deal with one graph circumstance
			int numOfDots=0;
			int direction; //�Ƿ�Ϊdouble
			GetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_DIRECTION, ATTR_CTRL_VAL,&direction); 
			reTime=0;
			measure_Uart_Flag=1; 	 //������ѯ
			Table_ATTR.columnWidth= 90;  												//�п�
			DeleteTableRows (hTablePanel, TABLE_DISTABLE, 1, -1); 		
	 		DeleteTableColumns (hTablePanel, TABLE_DISTABLE, 1, -1);					//ÿ��ʵ������֮ǰ�����һ��ʵ���table����  
			DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1, -1, VAL_IMMEDIATE_DRAW); 	//�������ͼ�ϵ���������
			DeleteGraphAnnotation (hGraphPanel, GRAPHDISP_GRAPH1,-1 );                  //����ϸ�ʵ������ע��
			SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH2,ATTR_ENABLE_ZOOM_AND_PAN,1);							//ʹ�ܿؼ������ź��϶�  
			DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH2, -1 , VAL_IMMEDIATE_DRAW); 							//����ϸ�ʵ���������
			GetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE,&TestPara.sampleRate);
			GetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER,&TestPara.sampleNumber); 
			GetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_LINEAR, ATTR_CTRL_INDEX,&log); 
			if(GetCtrlVal(hExpListPanel, EXP_LIST_TREE, &expType)<0)
				return -1; 
			TestPara.testMode=(enum TestMode)expType;
			GetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_DRAIN,&drain);
			GetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_GATE,&gate);    
			if((drain==0)&&(gate==1))
			{ 																								  //0x04 
			    ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf,ONLYGATE);		//send config to instrument via UART               	
			}
			else if(drain && gate)
			{  																								  //0x0c
			    ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf,BOTH);		//send config to instrument via UART               	
			}else if((drain==1)&&(gate==0))
			{																								   //0x08      
				 ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf,NOLYDRAIN);
			}
			else  if((drain==0)&&(gate==0))
			{
				 ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf,BOTHNONE);   
			}
			timeStep =  TestPara.sampleNumber*1.0/TestPara.sampleRate*1.0 + TestPara.SampleDelay/1000.0;    //����ʱ���� 
			switch(TestPara.testMode)
			{
			   	case SWEEP_DRAIN_VOL:				 
					if(TestPara.gateOutputMode==VOL_BIAS)
					   	numOfCurve=1;
					else if(TestPara.gateOutputMode==VOL_STEP)
						numOfCurve=abs(TestPara.VgStart-TestPara.VgStop)/TestPara.VgStep+1; 
					numOfDots=abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1;            
					GraphInit(hGraphPanel, graphIndex, numOfCurve, numOfDots, &Graph1);  //graph set up 
					Table_ATTR.column =6*numOfCurve ;
					Table_ATTR.row =  numOfDots; 
					Graph1.pGraphAttr->yAxisHead=1e-12;
	   				Graph1.pGraphAttr->yAxisTail=1.1e-12; 
					if(log) 
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(Id)/A");  
						Table(tableTitleLog_IdVd, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(Id)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT,22);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
                    	Table(table_title_IdVd, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);  	//������³�ʼ�� �����ò����йأ�Ӧ��д���ɺ�*/
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "Id");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 90);
					}
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
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+50, &Graph2); 							//��ʼ��ͼ2       
					if (TestPara.VdStart>TestPara.VdStop)
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VdStop;
						Graph2.pGraphAttr->xAxisTail=TestPara.VdStart;
					}else
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VdStart;
						Graph2.pGraphAttr->xAxisTail=TestPara.VdStop;
					} vdstart  = TestPara.VdStart;   
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail); 
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
					Table_ATTR.row =  numOfDots; 	
					Table_ATTR.column =6*numOfCurve ;          
					Graph1.pGraphAttr->yAxisHead=1e-12; 
	   				Graph1.pGraphAttr->yAxisTail=1.1e-12; 
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
					if(log)
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(Id)/A"); 
						Table(tableTitleLog_IdVg, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(Id)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 22);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
						Table(table_title_IdVg, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "Id");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT,90);
					}
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+50, &Graph2); 							//��ʼ��ͼ2       
					Graph2.pGraphAttr->xAxisHead=0;
					Graph2.pGraphAttr->xAxisTail=10;
					if (TestPara.VgStart>TestPara.VgStop)
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VgStop;
						Graph2.pGraphAttr->xAxisTail=TestPara.VgStart;
					}else
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VgStart;
						Graph2.pGraphAttr->xAxisTail=TestPara.VgStop;
					}
					vgstart  = TestPara.VgStart;    
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail); 
					CreateMonitorThread(numOfCurve);    
					break;
				   case NO_SWEEP_IT:
					numOfCurve=1;
					numOfDots=TestPara.runTime/timeStep+100; 					
					GraphInit(hGraphPanel,graphIndex,numOfCurve,numOfDots,&Graph1); 
					Graph1.pCurveArray->numOfTotalDots = numOfDots;
					Graph1.pCurveArray->time=0;  
					Table_ATTR.column =7*numOfCurve ;
					Table_ATTR.row =  numOfDots+100;
					Graph1.pGraphAttr->xAxisHead=0;
					Graph1.pGraphAttr->xAxisTail=10;	
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					if(log)
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(I)/A");     
						Table(tableTitleLog_IT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(I)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 30);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
						Table(table_title_IT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "I");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
					}
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+500, &Graph2);          
					Graph2.pGraphAttr->xAxisHead=0;
					Graph2.pGraphAttr->xAxisTail=10; 
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail);
					EvtTimerId = NewAsyncTimer((double)timeStep, -1, 1, EvtTimerCalback, 0);	 
					break;
				case NO_SWEEP_RT:
					numOfCurve=1;
					numOfDots=TestPara.runTime/timeStep+100; 				
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1); 
					Graph1.pCurveArray->numOfTotalDots = numOfDots;
					Graph1.pCurveArray->time=0;  
					Table_ATTR.column =7*numOfCurve; 
					Table_ATTR.row =  numOfDots+100 ;
					Graph1.pGraphAttr->xAxisHead=0;
					Graph1.pGraphAttr->xAxisTail=10;	
					 Table(table_title_RT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
					 SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					 SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  
					 SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "R(Ohm)");
					 SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "I");
	    			 SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95); 
					 GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+500, &Graph2); 
					 Graph2.pGraphAttr->xAxisHead=0;
					 Graph2.pGraphAttr->xAxisTail=10; 
					 SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail);       
					 EvtTimerId = NewAsyncTimer(timeStep, -1, 1, EvtTimerCalback, 0);	 
					 break;
				case SWEEP_IV:
					numOfCurve=1;  
					numOfDots = abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1;
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
					Table_ATTR.column =5*numOfCurve ;          
					Table_ATTR.row =  numOfDots;
					Graph1.pGraphAttr->yAxisHead=1e-13;
	   				Graph1.pGraphAttr->yAxisTail=1.1e-13; 
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
					if(log)
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(I)/A");
						Table(tableTitleLog_IV, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(I)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 30);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
						Table(table_title_IV, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);  
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "I");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
					}
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+50, &Graph2); 							//��ʼ��ͼ2       
					if (TestPara.VdStart>TestPara.VdStop)
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VdStop;
						Graph2.pGraphAttr->xAxisTail=TestPara.VdStart;
					}else
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VdStart;
						Graph2.pGraphAttr->xAxisTail=TestPara.VdStop;
					} vdstart  = TestPara.VdStart;      
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail);  
				
					break;
				
				case ID_T:
					numOfCurve=1;
					numOfDots=TestPara.runTime/timeStep+100; 			
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1); 
					Graph1.pCurveArray->numOfTotalDots = numOfDots;
					Graph1.pCurveArray->time=0;  
					Table_ATTR.column =7*numOfCurve; 
					Table_ATTR.row =  numOfDots+100 ;   ;
					Graph1.pGraphAttr->xAxisHead=0;
					Graph1.pGraphAttr->xAxisTail=10;	
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");
					if(log)
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(Id)/A");     
						Table(tableTitleLog_Idt, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(Id)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 22);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
						Table(table_title_Idt, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "Id");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 90);
					}
					  
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);  
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+500, &Graph2);  
					Graph2.pGraphAttr->xAxisHead=0;
					Graph2.pGraphAttr->xAxisTail=10; 
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail); 
					EvtTimerId = NewAsyncTimer(timeStep, -1, 1, EvtTimerCalback, 0);	 
					break;																																		 
			}
			
			threadFlag = 1;
			CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, AbnmDCThreadFunction, NULL, &abnmDCThreadId);//�����µ��̻߳���ʵ������
	   		Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
			Graph2.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph2.graphIndex,Graph2.plotCurveIndex); 		//�õ����ߵ�����     
			SetGraph2DisplayData();																					//�����Ƿ���ƻ������ߣ������ѡ�����ӻ����˿ڣ���򿪻�����ѯ																				//����֮ǰѡ��Ҫ���뱣��Ļ�������
			DisplayEnvtGraph();																						//��ʾѡ�������   
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			Delay(1);												  												//�����ú���������֮�����λ��0.2�봦��
			ProtocolRun(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);											//send RUN command to instrument via UART
			double temp=0.05;        
			TimerID = NewAsyncTimer(temp, -1, 1, TimerCallback, 0);	
			  
		break;
		}
	return 0;
}
/*
*ֹͣʱ���еı�־������Ϊ0��1
*/
void TestStopAction()
{
	measure_Uart_Flag=0;
	control_Uart_Flag=0; 
	FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
	FlushOutQ(measureComPort);
	FlushInQ(controlComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
	FlushOutQ(controlComPort);	
	CountFlag=0;  
	envtTime=0;
	curveComplete=0;
	threadFlag = 0;
	controlTime=0;
	CurveNums=1;
	numOfCurve = 0;  
	plots=0;
	Graph1.pCurveArray->numOfPlotDots=0;	 
	//ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);
	DiscardAsyncTimer(TimerID);			//ֹͣquery��ʱ����ѯ    	   EvtTimerId
	DiscardAsyncTimer(EvtTimerId);	
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_PRINT, ATTR_DIMMED,0);      //�ָ� ��ӡ��ť
	//SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUNAGAIN, ATTR_DIMMED, 0);      //�ָ����ߵ��Ӱ�ť    
	SetCtrlAttribute (hResultMenuPanel, RESULTMENU_SAVE, ATTR_DIMMED,0); 		//�ָ�  �������ݰ�ť        
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0); //�ָ�������������


}

int CVICALLBACK StopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	unsigned char counter=10;    //�ڲ�ѯ��ֹͣ������0.1�� 
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:		         //������ͷ�ʱ 
			measure_Uart_Flag=0;
			control_Uart_Flag=0; 
			FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(measureComPort);
			FlushInQ(controlComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(controlComPort);	
			CountFlag=0;  
			envtTime=0;
			curveComplete=0;
		    threadFlag = 0;
			controlTime=0;
			CurveNums=1;
			numOfCurve = 0;  
			plots=0;
			Graph1.pCurveArray->numOfPlotDots=0;	 
			ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf); //send STOP command to instrument via UART		  ///0x03 �豸ֹͣ�ɹ�   
			
			while(counter>0)
			{
				Delay(0.1);
			 	if(TestPara.StopSign == 0x03)
				{
					counter = 0;
				}
			 	else 
				{
					 ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf); //send STOP command to instrument via UART		  ///0x03 �豸ֹͣ�ɹ�  
					 counter--;
				}
			}
			measure_Uart_Flag=0;
			control_Uart_Flag=0; 
			FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(measureComPort);
			FlushInQ(controlComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(controlComPort);	
			DiscardAsyncTimer(TimerID);			//ֹͣquery��ʱ����ѯ    	   EvtTimerId
			DiscardAsyncTimer(EvtTimerId);	
		  	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
		    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_PRINT, ATTR_DIMMED,0);      //�ָ� ��ӡ��ť
			//SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUNAGAIN, ATTR_DIMMED, 0);      //�ָ����ߵ��Ӱ�ť    
			SetCtrlAttribute (hResultMenuPanel, RESULTMENU_SAVE, ATTR_DIMMED,0); 		//�ָ�  �������ݰ�ť        
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0); //�ָ�������������
		    //=================�����Զ�����===================
		   AutoSaveSheetAndGraph();
		
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
		   if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\users\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, configSavePath)>0)
			    SaveConfigToFile(configSavePath);
		   DisplayImageFile (hMainPanel, MAIN_PANEL_SAVE, "Resource\\Save.ico");  
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
	SavePanelState(hExpListPanel, pConfigSavePath, 2);  
	SavePanelState(IdVgPanel.panelHandle, pConfigSavePath, 7);						
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
			SetPanelPos(hPrjPanel,150,300);
			InstallPopup (hPrjPanel);
			SetCtrlAttribute(hPrjPanel,PROPANEL_PIC_OPENPRJ , ATTR_DIMMED, 1);
			//SetCtrlAttribute(hPrjPanel,PROPANEL_TXT_OPENPRJ , ATTR_TEXT_BGCOLOR,SEARCHCOLOR );
			SetCtrlAttribute(hPrjPanel,PROPANEL_TXT_OPENPRJ , ATTR_DIMMED, 1);
			InstallPopup (hPrjPanel);
		    SetPanelPos(hPrjListPanel,90,0); 
			SetPanelSize(hPrjListPanel, 500, 1400);
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
			SetPanelPos(hToolsPanel,250,500);
			InstallPopup (hToolsPanel);
		    break;
	}
	return 0;
}


int CVICALLBACK RunAgainCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)																							  
	{
		case EVENT_LEFT_CLICK_UP:
		    RunActive();
		//	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUNAGAIN, ATTR_DIMMED,1);				//������ͷ�ʱ, ���ÿ�ʼ��ť            
			threadFlag = 0; 
			CountFlag = 0;	  													//��־��ֹͣʱ���ڽ���������߳�   
			CurveNums=1;														//��������������ɫ
			GraphDeinit(&Graph1);												//�ڴ��ͷ��ڻ�ͼ֮������ڻ�ͼ֮ǰ�ͷŵ��´���
			GraphDeinit(&Graph2);/*
			FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(measureComPort);
			FlushInQ(controlComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			FlushOutQ(controlComPort);	*/
			Graph1.plotCurveIndex=0; 											//ÿ��ʵ�鿪ʼ֮ǰ��ʼ��CurveIndex
			curveComplete=0;
			rows=2;
			graphrows=2;
			controlTime=0;
		/*	x2 = 1;*/
		/*	curveIndex=1;   */                                                            //�������ע��
			int expType;
			int log;
			int graphIndex=0;															//currently only deal with one graph circumstance
			int numOfDots=0;
			int direction; //�Ƿ�Ϊdouble
			GetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_DIRECTION, ATTR_CTRL_VAL,&direction); 
			//xAxis = 0;
			reTime=0;
			measure_Uart_Flag=1; 	 //������ѯ
			Table_ATTR.columnWidth= 90;  												//�п�
			DeleteTableRows (hTablePanel, TABLE_DISTABLE, 1, -1); 		
	 		DeleteTableColumns (hTablePanel, TABLE_DISTABLE, 1, -1);					//ÿ��ʵ������֮ǰ�����һ��ʵ���table����  
			//DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1, -1, VAL_IMMEDIATE_DRAW); 	//�������ͼ�ϵ���������
			//DeleteGraphAnnotation (hGraphPanel, GRAPHDISP_GRAPH1,-1 );                  //����ϸ�ʵ������ע��
			SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH2,ATTR_ENABLE_ZOOM_AND_PAN,1);							//ʹ�ܿؼ������ź��϶�  
			//DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH2, -1 , VAL_IMMEDIATE_DRAW); 							//����ϸ�ʵ���������
			GetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE,&TestPara.sampleRate);
			GetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER,&TestPara.sampleNumber); 
			GetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_LINEAR, ATTR_CTRL_INDEX,&log); 
			if(GetCtrlVal(hExpListPanel, EXP_LIST_TREE, &expType)<0)
				return -1; 
			TestPara.testMode=(enum TestMode)expType;
			
			if((drain==0)&&(gate==1))
				{ 																								  //0x04 
					ProtocolCfgTxData(measureComPort, DEV_ADDR, measUartTxBuf,ONLYGATE); 
				}
				else if(drain && gate)
				{  																								  //0x0c
				    ProtocolCfgTxData(measureComPort, DEV_ADDR, measUartTxBuf,BOTH); 	//send config to instrument via UART               	
				}
				else if((drain==1)&&(gate==0))
				{																								   //0x08      
					 ProtocolCfgTxData(measureComPort, DEV_ADDR, measUartTxBuf,NOLYDRAIN); 
				}
				else  if((drain==0)&&(gate==0))
				{																								   //0x00
					ProtocolCfgTxData(measureComPort, DEV_ADDR, measUartTxBuf,BOTHNONE);       
				}
		//	ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf,);		//send config to instrument via UART 
				switch(TestPara.testMode)
			{
			   	case SWEEP_DRAIN_VOL:				 
					if(TestPara.gateOutputMode==VOL_BIAS)
					   	numOfCurve=1;
					else if(TestPara.gateOutputMode==VOL_STEP)
						numOfCurve=abs(TestPara.VgStart-TestPara.VgStop)/TestPara.VgStep+1; 
					numOfDots=abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1;            
					GraphInit(hGraphPanel, graphIndex, numOfCurve, numOfDots, &Graph1);  //graph set up 
					Table_ATTR.column =6*numOfCurve ;
					Table_ATTR.row =  numOfDots; 
					Graph1.pGraphAttr->yAxisHead=1e-12;
	   				Graph1.pGraphAttr->yAxisTail=1.1e-12; 
					if(log) 
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(Id)/A");  
						Table(tableTitleLog_IdVd, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(Id)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT,22);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
                    	Table(table_title_IdVd, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);  	//������³�ʼ�� �����ò����йأ�Ӧ��д���ɺ�*/
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "Id");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 90);
					}
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
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+50, &Graph2); 							//��ʼ��ͼ2       
					if (TestPara.VdStart>TestPara.VdStop)
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VdStop;
						Graph2.pGraphAttr->xAxisTail=TestPara.VdStart;
					}else
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VdStart;
						Graph2.pGraphAttr->xAxisTail=TestPara.VdStop;
					} vdstart  = TestPara.VdStart;   
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail); 
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
					Table_ATTR.row =  numOfDots; 	
					Table_ATTR.column =6*numOfCurve ;          
					Graph1.pGraphAttr->yAxisHead=1e-12; 
	   				Graph1.pGraphAttr->yAxisTail=1.1e-12; 
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
					if(log)
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(Id)/A"); 
						Table(tableTitleLog_IdVg, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(Id)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 22);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
						Table(table_title_IdVg, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "Id");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT,90);
					}
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+50, &Graph2); 							//��ʼ��ͼ2       
					Graph2.pGraphAttr->xAxisHead=0;
					Graph2.pGraphAttr->xAxisTail=10;
					if (TestPara.VgStart>TestPara.VgStop)
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VgStop;
						Graph2.pGraphAttr->xAxisTail=TestPara.VgStart;
					}else
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VgStart;
						Graph2.pGraphAttr->xAxisTail=TestPara.VgStop;
					}
					vgstart  = TestPara.VgStart;    
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail); 
					CreateMonitorThread(numOfCurve);    
					break;
				   case NO_SWEEP_IT:
					numOfCurve=1;
					numOfDots=TestPara.runTime/timeStep+100; 					
					GraphInit(hGraphPanel,graphIndex,numOfCurve,numOfDots,&Graph1); 
					Graph1.pCurveArray->numOfTotalDots = numOfDots;
					Graph1.pCurveArray->time=0;  
					Table_ATTR.column =7*numOfCurve ;
					Table_ATTR.row =  numOfDots+100;
					Graph1.pGraphAttr->xAxisHead=0;
					Graph1.pGraphAttr->xAxisTail=10;	
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					if(log)
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(I)/A");     
						Table(tableTitleLog_IT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(I)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 30);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
						Table(table_title_IT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "I");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
					}
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+500, &Graph2);          
					Graph2.pGraphAttr->xAxisHead=0;
					Graph2.pGraphAttr->xAxisTail=10; 
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail);
					break;
				case NO_SWEEP_RT:
					numOfCurve=1;
					numOfDots=TestPara.runTime/timeStep+100; 				
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1); 
					Graph1.pCurveArray->numOfTotalDots = numOfDots;
					Graph1.pCurveArray->time=0;  
					Table_ATTR.column =7*numOfCurve; 
					Table_ATTR.row =  numOfDots+100 ;
					Graph1.pGraphAttr->xAxisHead=0;
					Graph1.pGraphAttr->xAxisTail=10;	
					 Table(table_title_RT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
					 SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					 SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  
					 SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "R(Ohm)");
					 SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "I");
	    			 SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95); 
					 GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+500, &Graph2); 
					 Graph2.pGraphAttr->xAxisHead=0;
					 Graph2.pGraphAttr->xAxisTail=10; 
					 SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail);       
					 break;
				case SWEEP_IV:
					numOfCurve=1;  
					numOfDots = abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1;
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
					Table_ATTR.column =5*numOfCurve ;          
					Table_ATTR.row =  numOfDots;
					Graph1.pGraphAttr->yAxisHead=1e-13;
	   				Graph1.pGraphAttr->yAxisTail=1.1e-13; 
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
					if(log)
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(I)/A");
						Table(tableTitleLog_IV, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(I)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 30);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
						Table(table_title_IV, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);  
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "I");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
					}
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+50, &Graph2); 							//��ʼ��ͼ2       
					if (TestPara.VdStart>TestPara.VdStop)
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VdStop;
						Graph2.pGraphAttr->xAxisTail=TestPara.VdStart;
					}else
					{
						Graph2.pGraphAttr->xAxisHead=TestPara.VdStart;
						Graph2.pGraphAttr->xAxisTail=TestPara.VdStop;
					} vdstart  = TestPara.VdStart;      
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail);  
					break;
				
				case ID_T:
					numOfCurve=1;
					numOfDots=TestPara.runTime/timeStep+100; 			
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1); 
					Graph1.pCurveArray->numOfTotalDots = numOfDots;
					Graph1.pCurveArray->time=0;  
					Table_ATTR.column =7*numOfCurve; 
					Table_ATTR.row =  numOfDots+100 ; 
					Graph1.pGraphAttr->xAxisHead=0;
					Graph1.pGraphAttr->xAxisTail=10;	
					SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");
					if(log)
					{
						SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "log10(Id)/A");     
						Table(tableTitleLog_Idt, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "log10(Id)");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 22);
					}
					else
					{
				   	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
						Table(table_title_Idt, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row); 
						SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "Id");
	    				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 90);
					}
					  
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);  
					GraphInit(hGraphPanel,graphIndex, ENV_NUM_OF_CURVE, numOfDots+500, &Graph2);  
					Graph2.pGraphAttr->xAxisHead=0;
					Graph2.pGraphAttr->xAxisTail=10; 
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail); 
					break;																																		 
			}
			
			//xAxis = Graph2.pGraphAttr->xAxisHead;      
			threadFlag = 1;
			CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, AbnmDCThreadFunction, NULL, &abnmDCThreadId);//�����µ��̻߳���ʵ������
			Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
			Graph2.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph2.graphIndex,Graph2.plotCurveIndex); 		//�õ����ߵ�����     
			SetGraph2DisplayData();																					//����֮ǰѡ��Ҫ���뱣��Ļ�������
			DisplayEnvtGraph();	//��ʾѡ�������   
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			//GetSampleRate();
			Delay(0.2);												  												//�����ú���������֮�����λ��0.2�봦��
		
			
			ProtocolRun(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);											//send RUN command to instrument via UART
			double temp=0.05;
			//if(temp<0.03) temp=0.03;																				//�����ѯʱ����죬��������ݻ��ң���λ����Ӧ�жϹ���
			TimerID = NewAsyncTimer(temp, -1, 1, TimerCallback, 0);	
		break;
		}
		
		
	return 0;

}

int CVICALLBACK PrintCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
			DisplayImageFile (hMainPanel, MAIN_PANEL_PRINT, "Resource\\print_pressed.ico");  
			PrintPanel (hMainPanel, "", 1, VAL_VISIBLE_AREA, 1);
			DisplayImageFile (hMainPanel, MAIN_PANEL_PRINT, "Resource\\print.ico");    
			break;
	}
	return 0;
}

