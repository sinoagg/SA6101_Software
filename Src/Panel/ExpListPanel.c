#include <userint.h>
#include "Experiment List.h"

//==============================================================================
//
// Title:		ExperimentList.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/11 at 9:55:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "ExpListPanel.h"
#include "IdVdsPanel.h"
#include "IdVgsPanel.h"
#include "Id-Vds Configuration.h"
#include "Id-Vgs Configuration.h"
#include "I-T.h"
#include "ItPanel.h"
#include "LoadPanel.h"
#include "R-T.h"
#include "RtPanel.h"
#include "ResultDispPanel.h"

//==============================================================================
// Constants
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

//==============================================================================
// Global functions

static void ChangeImg(void)
{
	DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
	DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure_pressed.ico"); 
	DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
}

static void DisplaySampleCfgPanel(int display)
{
	if(display)
	{
		SetPanelPos(hBasicSamplePanel, 104, 1600);
		DisplayPanel(hBasicSamplePanel);
		
		SetPanelPos(hEnvCfgPanel, 556, 1600);
		DisplayPanel(hEnvCfgPanel);
		
	}
	else 
	{
		HidePanel(hBasicSamplePanel);
	    HidePanel(hEnvCfgPanel);
	}
}


static void DisplayRunTime(int display)
{
	SetCtrlAttribute(hBasicSamplePanel, SAMPLE_CFG_TXT_RUNTIME,ATTR_VISIBLE, display);
	SetCtrlAttribute(hBasicSamplePanel, SAMPLE_CFG_RUNTIME,ATTR_VISIBLE, display);
	SetCtrlAttribute(hBasicSamplePanel, SAMPLE_CFG_RUNTIME_UNIT,ATTR_VISIBLE, display);
}

static void DisplayOhm(int display)
{
   	SetCtrlAttribute(hResultDispPanel, RESULTDISP_TXT_R,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel, RESULTDISP_OHM,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel, RESULTDISP_OHM_UNIT,ATTR_VISIBLE,display);
	SetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_LINEAR, ATTR_DIMMED, display); 
}

static void StopBtnStatus()
{
	int val;
	GetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,&val);
	if(val == 1)
	{
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,0);
		//SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUNAGAIN, ATTR_DIMMED,0);   
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,0); //运行状态停止时可设置曲线属性 
	}
	else 
	{
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);
	//	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUNAGAIN, ATTR_DIMMED,1); 
	}
}
 
int CVICALLBACK TreeCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_ANALYZE, ATTR_DIMMED,0);  
			ChangeImg();
			int index;
			GetActiveTreeItem (hExpListPanel, EXP_LIST_TREE, &index);//获得当前点击项目值		   
			if(index==TWO_TERMINAL)
			{   
				//SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUNAGAIN, ATTR_DIMMED,1);
				SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);      
				DisplaySampleCfgPanel(0);
				SetPanelPos(hTwoTerminalPanel,124,1600);
				DisplayPanel(hTwoTerminalPanel);
				HidePanel(hResultMenuPanel); //影藏resultmenu面板     
			}
			else if(index==EXP_I_T)	//加载I-T
			{ 
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_VG, ATTR_DIMMED, 1);
				SetCtrlVal(hResultDispPanel, RESULTDISP_VG,0);     
				SetPanelPos(hIT_Panel, 104, 305);
				DisplayPanel(hIT_Panel);
				StopBtnStatus();
		        DisplaySampleCfgPanel(1);
				DisplayRunTime(1);
				DisplayOhm(0);
			
			}
			else if(index==EXP_R_T)	//加载R-T 
			{	
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_VG, ATTR_DIMMED, 1);         
				SetPanelPos(hRT_Panel, 104, 305);
				SetCtrlVal(hResultDispPanel, RESULTDISP_VG,0);
				SetCtrlAttribute (hAdvanceSamplePanel, SAMPLE_ADV_LINEAR, ATTR_CTRL_INDEX,0);  
				DisplayPanel(hRT_Panel);					  
				StopBtnStatus();    
				DisplaySampleCfgPanel(1);
				DisplayRunTime(1);
				DisplayOhm(1); 
			
			}
			else if(index==EXP_I_V)
			{

				SetCtrlVal(hResultDispPanel, RESULTDISP_VG,0);     
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_VG, ATTR_DIMMED, 1);         
				SetPanelPos(hIV_Panel, 104, 305);
				DisplayPanel(hIV_Panel);
				StopBtnStatus();    
				DisplaySampleCfgPanel(1);
				DisplayRunTime(0);
				DisplayOhm(0);  
			}
			else if(index==FOUR_TERMINAL) 
			{
				//SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUNAGAIN, ATTR_DIMMED,1); 
				SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);      
				DisplaySampleCfgPanel(0);
				SetPanelPos(hFourTerminalPanel,124,1600);
				DisplayPanel(hFourTerminalPanel);
			    HidePanel(hResultMenuPanel); //影藏resultmenu面板     
				
			}
			else if(index==EXP_ID_VDS)// 加载Id_Vds Configuration   
			{
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_VG, ATTR_DIMMED, 0);         
				SetPanelPos(IdVdPanel.panelHandle, 104, 305);
				DisplayPanel(IdVdPanel.panelHandle);
				StopBtnStatus();     
				DisplaySampleCfgPanel(1);
				DisplayRunTime(0);
				DisplayOhm(0);  
			}
			else if(index==EXP_ID_VGS)//  加载Id_Vgs Configuration  
			{ 	
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_VG, ATTR_DIMMED, 0);         
				SetPanelPos(IdVgPanel.panelHandle, 104, 305);
				DisplayPanel(IdVgPanel.panelHandle);
				StopBtnStatus();    
				DisplaySampleCfgPanel(1);
				DisplayRunTime(0);
				DisplayOhm(0);  
			}else if(index==EXP_ID_T)//Id-T
			{
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_VG, ATTR_DIMMED, 0);         
			    SetPanelPos(hIdtPanel, 104, 305);
				DisplayPanel(hIdtPanel);
				StopBtnStatus();    
				DisplaySampleCfgPanel(1);
				DisplayRunTime(1);
				DisplayOhm(0);  
				
			}
			break;
	}  
	return 0;
}

int CVICALLBACK TxtCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	
	return 0;
}
