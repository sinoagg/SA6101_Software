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
//<<<<<<< HEAD
//=======
#include <formatio.h>
//>>>>>>> refs/remotes/origin/master
#include "asynctmr.h"
#include "MainPanelCb.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "LoadPanel.h"
#include "Protocol.h"
#include "Timer.h"

//==============================================================================
// Constants
#define DEFAULT_ADDR 0x01 

#define VAL_TEXTBG                        0xF0F0F0L    //δ��ѡ�б���ɫ
#define VAL_TEXTBG_PRESSED                0x065279L    //��ѡ�б���ɫ


//==============================================================================
// Types

//==============================================================================
// Static global variables
int ENVPanel;
int GRAPHPanel; 
int ABOUTPanel;
//==============================================================================
// Static functions

//==============================================================================
// Global variables
int TimerID;
extern unsigned char UartTxBuf[32];
extern unsigned char UartRxBuf[64];
char configSavePath[512]={0};
//==============================================================================
// Global functions


//===================================================
//   MAIN_PANEL_Callback

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

//===================================================
//   RunCallback

int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ
			SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);         //���� ��ʼ��ť      
		    SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       //�ָ� ֹͣ��ť
	        SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        //���� ���水ť
			if(!comSelect1)
			{
				MessagePopup ("Warning", "Instrument Unconnected");   //Lost serial Connection
			}
			else
			{
				int expType;
				int graphIndex=1;	//currently only deal with one graph circumstance
				int numOfCurve=1;
				int numOfDots=500;
				if(GetCtrlVal(expListPanel, EXP_LIST_TREE, &expType)<0)
					return -1;
				switch(expType)
				{
					case 0:
						GetIdVdCfg (IdVdPanel);
						//if((IdVgCfg.cfgVgstart==IdVdCfg.cfgVgstop)||IdVgCfg.cfgVgstep==0)	//�����ʼ��ѹ����ֹ��ѹ��ͬ
						numOfCurve=abs(IdVdCfg.cfgVgstart-IdVdCfg.cfgVgstop)/IdVdCfg.cfgVgstep;
						numOfDots=abs(IdVdCfg.cfgVdstart-IdVdCfg.cfgVdstop)/IdVdCfg.cfgVdstep;
						break;
					case 1:
						GetIdVgCfg (IdVgPanel);
						numOfCurve=abs(IdVgCfg.cfgVdstart-IdVgCfg.cfgVdstop)/IdVgCfg.cfgVdstep;
						numOfDots=abs(IdVgCfg.cfgVgstart-IdVgCfg.cfgVgstop)/IdVgCfg.cfgVgstep;
						break;
					case 2:
						//TODO
						break;
					case 3:
						//TODO
						break;
					default:
						break;
				}
				
				ProtocolCfg(comSelect1, DEFAULT_ADDR, (unsigned char)expType, UartTxBuf);		//send config to instrument via UART
				graphInit(graphIndex, numOfCurve, numOfDots, pGraph1); 	//graph set up 
				TimerID = NewAsyncTimer(1,-1, 1, TimerCallback, 0);		//Create Asynchronous (Timer time interval 1s, continue generating evernt, enabled, callback function name, passing no pointer)  
				ProtocolRun(comSelect1, DEFAULT_ADDR, UartTxBuf);		//send RUN command to instrument via UART
			}
			break;
	}
	return 0;
}

//===================================================
//   StopCallback

int CVICALLBACK StopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ
		  	 SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
		     SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
			 SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
			break;
	}
	return 0;
}

int CVICALLBACK SaveCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
			break;
		case EVENT_LEFT_CLICK:			    //��Save�����������ʱ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SAVE, "Resource\\Save_pressed.ico");
			
			break;
			
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ  
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SAVE, "Resource\\Save.ico");
			if(FileSelectPopupEx("C:\\SINOAGG\\SA6101\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1,  configSavePath)>0)
				SaveConfigToFile(configSavePath);
			break;
	}
	return 0;
}
//===================================================
//   SelectCallback

int CVICALLBACK SelectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //��Select�����������ʱ,Selectͼ��ı䣬������������״̬ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select_pressed.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
			HidePanel( samplePanel  );	 
			HidePanel( smPanel  );
			HidePanel( environmentPanel);
			HidePanel(AnalyenvirPanel);
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
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure_pressed.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
			
			break;
			
			
		case EVENT_LEFT_CLICK:
			//���Configureͼ��ص�Id_vds����
				SetPanelPos(IdVdPanel, 105, 305);
				SetPanelSize(IdVdPanel, 900, 1293);
				DisplayPanel(IdVdPanel);
				
				SetPanelPos(samplePanel, 105, 1600);
				SetPanelSize(samplePanel, 450, 300);
				DisplayPanel(samplePanel);
				
				SetPanelPos(environmentPanel, 557, 1600);
				SetPanelSize(environmentPanel, 450, 300);
				DisplayPanel(environmentPanel);
			break;
	}
	return 0;
}

//===================================================
//   Analyze_Callback

int CVICALLBACK AnalyzeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
		
				SetPanelPos(resultPanel, 105, 305);  
		     	SetPanelSize(resultPanel, 65, 1293);      
	 			DisplayPanel(resultPanel);  
				
				

				SetPanelPos(graphDispPanel, 172, 305);  
		     	SetPanelSize(graphDispPanel, 834, 1293);      
	 			DisplayPanel(graphDispPanel);
			   
				SetPanelPos(smPanel, 105, 1600);
				SetPanelSize(smPanel, 450, 300);
				DisplayPanel(smPanel);
				
				SetPanelPos(AnalyenvirPanel, 557, 1600);
				SetPanelSize(AnalyenvirPanel, 450, 300);
				DisplayPanel(AnalyenvirPanel);


			break;
 		case EVENT_LEFT_CLICK_UP:			    //��Analyze�����������ʱ,Analyzeͼ��ı䣬������������״̬�� 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
		
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
	         InstallPopup (setPanel);    //����setPanel 
	
			SetPanelPos(ENVTPanel, 5, 170);
			SetPanelSize(ENVTPanel, 350, 650);
			DisplayPanel(ENVTPanel);
			
		
			
			break;

	}
	return 0;
}




//int CVICALLBACK GraphBtnCallback (int panel, int control, int event,
//								  void *callbackData, int eventData1, int eventData2)
//{
//	
//}

//int CVICALLBACK AboutBtnCallback (int panel, int control, int event,
//								  void *callbackData, int eventData1, int eventData2)
//{
//	
//}
//=======

//=======
//>>>>>>> refs/remotes/origin/master
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
		char comment[maxCommentSize];
		GetIdVdCfg(IdVdPanel);						//��ȡIdVd�������
		GetIdVgCfg(IdVgPanel);						//��ȡIdVg�������
		//GetITCfg(iTPanel);
		//GetRTCfg(rTPanel);
		GetSampleCfg(samplePanel);
		//GetEnvironmentCfg(environmentPanel);
		PromptPopup("Message", "Please enter comment for this configuration:", comment, maxCommentSize-1);
		fprintf(fp, "Date:%s	Time:%s\r\n", DateStr(), TimeStr());
		fprintf(fp, "Comment: %s", comment);
		
		fclose(fp);//�ر��ļ�
	}
	return 0;
	
}
//<<<<<<< HEAD


//>>>>>>> 8d2b85158ba46c70afb115b45e9d7b754e79c8f5
//=======
//>>>>>>> refs/remotes/origin/master

//����projects����
int CVICALLBACK ProjectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
		
			InstallPopup (proPanel); 
			SetPanelPos(defPanel, 90, -10);
			SetPanelSize(defPanel, 115, 1300);
			DisplayPanel(defPanel);  
			break;
		    
	}	 
	 
	return 0;
}
