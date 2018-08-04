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
#include <utility.h>
#include <formatio.h>
#include "asynctmr.h"
#include "MainPanelCb.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "LoadPanel.h"
#include "Protocol.h"
#include "Timer.h"
#include "SampleCfgPanel.h"
#include "main.h"
#include "ResultMenuPanel.h"
#include "SettingsPanel.h"
#include "File.h"

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

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int TimerID;
char configSavePath[512]={0};
FileLableTypeDef *pFileLable[64];									//������FileLable��ָ��
//==============================================================================
// Global functions

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
			   	QuitUserInterface(0); 
			break;
	}
	return 0;
}

int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	//int ControlID;
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
		    SetPanelPos(hResultMenuPanel, 105, 305);  
	     	SetPanelSize(hResultMenuPanel, 65, 1293);      
 			DisplayPanel(hResultMenuPanel);  
			
			SetPanelPos(hGraphPanel, 172, 305);  
	     	SetPanelSize(hGraphPanel, 833, 1293);
			SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 680);
			SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
 			DisplayPanel(hGraphPanel);
		   
			SetPanelPos(hResultDispPanel, 105, 1600);
			SetPanelSize(hResultDispPanel, 449, 300);
			DisplayPanel(hResultDispPanel);
			SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,0);
			SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,0);
			SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME_UNIT,ATTR_VISIBLE,0);
			SetPanelPos(hEnvResultPanel, 556, 1600);
			SetPanelSize(hEnvResultPanel, 449, 300);
			DisplayPanel(hEnvResultPanel);
				    
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);//������ͷ�ʱ         //���� ��ʼ��ť      
		    SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       //�ָ� ֹͣ��ť
	        SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        //���� ���水ť
			DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1, -1, VAL_IMMEDIATE_DRAW); //�������ͼ�ϵ��������� 
			
			int expType;
			int graphIndex=1;	//currently only deal with one graph circumstance
			int numOfCurve=1;
			int numOfDots=500;
			if(GetCtrlVal(hExpListPanel, EXP_LIST_TREE, &expType)<0)
				return -1; 
			//curveInit(&Graph1,grapIndex,pCurveAttr.pointStyle );
			TestPara.testMode=(enum TestMode)expType;
			ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf);		//send config to instrument via UART 
 			
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
					GraphInit(graphIndex, numOfCurve, numOfDots, &Graph1); 	//graph set up    
					Graph1.pGraphAttr->xAxisHead=TestPara.VdStart;
					Graph1.pGraphAttr->xAxisTail=TestPara.VdStop;
					SetCtrlAttribute(hGraphPanel, GRAPHDISP_GRAPH1, ATTR_ENABLE_ZOOM_AND_PAN, 1 );
					SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead, Graph1.pGraphAttr->xAxisTail);//���� X ��ķ�Χ
					break;
				case SWEEP_GATE_VOL:
				/*	GetIdVgCfg (IdVgPanel);
					numOfCurve=abs(IdVgCfg.cfgVdstart-IdVgCfg.cfgVdstop)/IdVgCfg.cfgVdstep;
					numOfDots=abs(IdVgCfg.cfgVgstart-IdVgCfg.cfgVgstop)/IdVgCfg.cfgVgstep;*/
		      		if(TestPara.drainOutputMode==VOL_BIAS)
					{
						numOfCurve=1;
					}else if(TestPara.drainOutputMode==VOL_STEP)
					{
						numOfCurve = abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1; //����
					}
					numOfDots = abs(TestPara.VgStart-TestPara.VgStop)/TestPara.VgStep+1;	  //����
					GraphInit(graphIndex,numOfCurve,numOfDots,&Graph1);
					Graph1.pGraphAttr->xAxisHead = TestPara.VgStart;
				    Graph1.pGraphAttr->xAxisTail = TestPara.VgStop;
					SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH1,ATTR_ENABLE_ZOOM_AND_PAN,1);//ʹ�ܿؼ������ź��϶�
					//��������ģʽ��ͼ����ķ�Χ������ģʽ�Լ�����ͼ��y�᷶Χ
					//SetAxisScalingMode(int PanelHandle,int ControlID,int Axis(�仯��),int AxisScaling(������ģʽ),double min,double max);
					SetAxisScalingMode(hGraphPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					break;
				case NO_SWEEP_IT:
					if(TestPara.gateOutputMode==VOL_BIAS)
					{
						numOfCurve=1;
						numOfDots=TestPara.VgStart;
						SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH1,ATTR_ENABLE_ZOOM_AND_PAN,1);//ʹ�ܿؼ������ź��϶�
					//��������ģʽ��ͼ����ķ�Χ������ģʽ�Լ�����ͼ��y�᷶Χ
					//SetAxisScalingMode(int PanelHandle,int ControlID,int Axis,int AxisScaling,double min,double max);
					SetAxisScalingMode(hGraphPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					}
					//TODO
					break;
				case  NO_SWEEP_RT:
					//TODO
					break;
				default:
					break;
			}	
			
			Delay(1);
			ProtocolRun(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send RUN command to instrument via UART
			TimerID = NewAsyncTimer(1,-1, 1, TimerCallback, 0);		//Create Asynchronous (Timer time interval 1s, continue generating evernt, enabled, callback function name, passing no pointer)
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
			DiscardAsyncTimer(TimerID);
			ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send RUN command to instrument via UART 
		  	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
		    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
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

int CVICALLBACK SelectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //��Select�����������ʱ,Selectͼ��ı䣬������������״̬ 
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select_pressed.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");

	 		SetPanelPos(IdVgPanel.panelHandle, 104, 305);
	        SetPanelSize(IdVgPanel.panelHandle, 901, 1293);
	        DisplayPanel(IdVgPanel.panelHandle);

			HidePanel(hBasicSamplePanel);	 
			HidePanel(hResultDispPanel);
			HidePanel(hEnvResultPanel);
			HidePanel(hEnvCfgPanel);
			HidePanel(hResultDispPanel);  
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
		
			//���Configureͼ��ص�Id_vds����
			SetPanelPos(IdVgPanel.panelHandle, 104, 305);
			SetPanelSize(IdVgPanel.panelHandle, 901, 1293);
			DisplayPanel(IdVgPanel.panelHandle);
			
			SetPanelPos(hBasicSamplePanel, 105, 1600);
			SetPanelSize(hBasicSamplePanel, 449, 300);
			DisplayPanel(hBasicSamplePanel);
			
			SetPanelPos(hEnvCfgPanel, 556, 1600);
			SetPanelSize(hEnvCfgPanel, 449, 300);
			DisplayPanel(hEnvCfgPanel);
			break;
	}
	return 0;
}

static void DispResultMenu(void)
{
	SetPanelPos(hResultMenuPanel, 105, 305);  
 	SetPanelSize(hResultMenuPanel, 65, 1293);      
	DisplayPanel(hResultMenuPanel);
}

static void DispResultNumber(void)
{
	SetPanelPos(hResultDispPanel, 105, 1600);
	SetPanelSize(hResultDispPanel, 449, 300);
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
	SetPanelSize(hEnvResultPanel, 449, 300);
	DisplayPanel(hEnvResultPanel);
}

int CVICALLBACK AnalyzeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK_UP:			    //��Analyze�����������ʱ,Analyzeͼ��ı䣬������������״̬�� 
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
			
			DispResultMenu();
			DispResultTableGraph();
			DispResultNumber();
		    DispEnvironmentCfg();
			int index;
			GetActiveTreeItem (hExpListPanel, EXP_LIST_TREE, &index);
			if(index==EXP_I_T||index==EXP_R_T||index==EXP_ID_T)
				DispRuntime(1);
			else 
				DispRuntime(0);
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
			SetPanelSize(hSettingsPrjPanel, 350, 650);
			DisplayPanel(hSettingsPrjPanel);

			break;
	}
	return 0;
}

static int SaveAllPanelState(char* pConfigSavePath)
{
	SavePanelState(IdVgPanel.panelHandle, pConfigSavePath, 0);						
	SavePanelState(IdVgPanel.panelHandle, pConfigSavePath, 1);						
	SavePanelState(hIT_Panel, pConfigSavePath, 2);
	SavePanelState(hRT_Panel, pConfigSavePath, 3);
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
		if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, pConfigSavePath)<0)
			return -1;
	}
	else
	{
		int maxCommentSize=255;
		char description[maxCommentSize];
		PromptPopup("Message", "Please enter comment for this configuration:", description, maxCommentSize-1);
		//fprintf(fp, "Date:%s	Time:%s\r\n", DateStr(), TimeStr());
		fprintf(fp, "%s\r\n", description);
		SaveAllPanelState(pConfigSavePath);		//����������������
		
		fclose(fp);//�ر��ļ�
	}
	return 0;
	
}

static int LoadAndDispPrj(FileLableTypeDef *pFileLable, char sequence)						//sequenceΪprj����λ������
{
	int hTempPanel;
	if ((hTempPanel = LoadPanel (hPrjPanel, "Project.uir", DEFPANEL)) < 0)		//load projects panel
		return -1;
	SetCtrlVal(hTempPanel, DEFPANEL_NAME, pFileLable->FileName);
	SetCtrlVal(hTempPanel, DEFPANEL_DATE, pFileLable->FileDate);
	SetCtrlVal(hTempPanel, DEFPANEL_TIME, pFileLable->FileTime);
	SetCtrlVal(hTempPanel, DEFPANEL_DESC, pFileLable->FileDesc);
	SetPanelPos(hTempPanel, 90+sequence*117, -10);
	SetPanelSize(hTempPanel, 115, 1300);
	DisplayPanel(hTempPanel);
	return 0;
}

static int LoadAllProject(char* pProjectSavePath)
{
	char tempFileName[512];
	char tempFilePath[512];
	char i=0;
	char tempPathToSearch[512];
	sprintf(tempPathToSearch, "%s%s", pProjectSavePath, "\\*.sac");
	if(0==GetFirstFile(tempPathToSearch, 1, 1, 1, 1, 1, 0, tempFileName))		//�����һ���ļ���ȡ�ɹ�
	{
		sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
		pFileLable[i] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
		InitFileLable(pFileLable[i], tempFilePath); 				//���ļ�ʱ����ļ����Ƽ�description����չʾ
		LoadAndDispPrj(pFileLable[i], i);
		i++;
		
		while(GetNextFile(tempFileName)==0)								//�����ȡ��ȷ��������ȡ
		{
			sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
			pFileLable[i] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
			InitFileLable(pFileLable[i], tempFilePath); //���ļ�ʱ����ļ����Ƽ�description
			LoadAndDispPrj(pFileLable[i], i);
			i++;
		}
	}
	return 0;
}

int CVICALLBACK ProjectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			InstallPopup (hPrjPanel);
			LoadAllProject(ProjectSavePath);
			SetPanelPos(hPrjListPanel, 90, -10);
			SetPanelSize(hPrjListPanel, 115, 1300);
			DisplayPanel(hPrjListPanel);
			break;
	}	 
	return 0;
}
