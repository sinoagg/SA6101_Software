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
		//SetPanelSize(hBasicSamplePanel, 450 ,320);
		DisplayPanel(hBasicSamplePanel);
		
		SetPanelPos(hEnvCfgPanel, 556, 1600);
		//SetPanelSize(hEnvCfgPanel, 449, 320);
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

static void RunStatus()
{
	int val;
	GetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,&val);
	if(val == 1)
	{
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,0);
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,0); //运行状态停止时可设置曲线属性 
	}
	else 
	{
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);
		
	}

	
}


int CVICALLBACK TreeCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			ChangeImg();
			int index;
			GetActiveTreeItem (hExpListPanel, EXP_LIST_TREE, &index);//获得当前点击项目值		   
			if(index==TWO_TERMINAL)
			{   
				DisplaySampleCfgPanel(0);
				SetPanelPos(hTwoTerminalPanel,124,1600);
				//SetPanelSize(hTwoTerminalPanel,881,320);
				DisplayPanel(hTwoTerminalPanel);
			}
			else if(index==EXP_I_T)	//加载I-T
			{ 
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "T(s)");	  //设置坐标轴
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
				SetPanelPos(hIT_Panel, 104, 305);
				//SetPanelSize(hIT_Panel, 901, 1293);
				DisplayPanel(hIT_Panel);
				RunStatus();
		        DisplaySampleCfgPanel(1);
				DisplayRunTime(1);
			}
			else if(index==EXP_R_T)	//加载R-T 
			{	
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "T(s)");	  
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "R(Ohm)");
				SetPanelPos(hRT_Panel, 104, 305);
				//SetPanelSize(hRT_Panel, 901, 1293);
				DisplayPanel(hRT_Panel);
				RunStatus();    
				DisplaySampleCfgPanel(1);
				DisplayRunTime(1);
			}
			else if(index==EXP_I_V)
			{
				
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "V(mV)");		  
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
				SetPanelPos(hIV_Panel, 104, 305);
				//SetPanelSize(hIV_Panel, 901, 1293);
				DisplayPanel(hIV_Panel);
				RunStatus();    
				DisplaySampleCfgPanel(1);
				DisplayRunTime(0);
			}
			else if(index==FOUR_TERMINAL) 
			{
				SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1); 
				DisplaySampleCfgPanel(0);
				SetPanelPos(hFourTerminalPanel,124,1600);
				//SetPanelSize(hFourTerminalPanel,881,320);
				DisplayPanel(hFourTerminalPanel);
				
			}
			else if(index==EXP_ID_VDS)// 加载Id_Vds Configuration   
			{
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "Vd(mV)");	 
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
				SetPanelPos(IdVdPanel.panelHandle, 104, 305);
				//SetPanelSize(IdVdPanel.panelHandle, 901, 1293);
				DisplayPanel(IdVdPanel.panelHandle);
				RunStatus();     
				DisplaySampleCfgPanel(1);
				DisplayRunTime(0);
			}
			else if(index==EXP_ID_VGS)//  加载Id_Vgs Configuration  
			{ 	
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "Vg(mV)");	 
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
				SetPanelPos(IdVgPanel.panelHandle, 104, 305);
				//SetPanelSize(IdVgPanel.panelHandle, 901, 1293);
				DisplayPanel(IdVgPanel.panelHandle);
				RunStatus();    
				DisplaySampleCfgPanel(1);
				DisplayRunTime(0);
			}else if(index==EXP_ID_T)//Id-T
			{
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	 
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "Id(A)");
			    SetPanelPos(hIdtPanel, 104, 305);
				//SetPanelSize(hIdtPanel, 901, 1293);
				DisplayPanel(hIdtPanel);
				RunStatus();    
				DisplaySampleCfgPanel(1);
				DisplayRunTime(1);
				
			}
			break;
	}  
	return 0;
}
