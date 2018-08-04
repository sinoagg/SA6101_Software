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
#include "LoadPanel.h"

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

//==============================================================================
// Global functions

 void ChangeImg(int panel, int control){
	DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
	DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure_pressed.ico"); 
	DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
	SetPanelPos(hResultDispPanel, 104, 1600);
	SetPanelSize(hResultDispPanel, 450 ,300);
	DisplayPanel(hResultDispPanel);

}
int CVICALLBACK TreeCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
		
			int index;
			GetActiveTreeItem (panel, control, &index);//获得当前点击项目值		   
			if(index==0)
			{
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TXT_MS,ATTR_VISIBLE,0);	
			}
			else if(index==1)	//加载I-T
			{ 
				SetPanelPos(hIT_Panel, 104, 305);
				SetPanelSize(hIT_Panel, 901, 1293);
				DisplayPanel(hIT_Panel);
				
		        SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TXT_MS,ATTR_VISIBLE,1);
				ChangeImg(panel,control);
			}
			else if(index==2)	//加载R-T 
			{	
				SetPanelPos(hRT_Panel, 104, 305);
				SetPanelSize(hRT_Panel, 901, 1293);
				DisplayPanel(hRT_Panel);	
		        SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TXT_MS,ATTR_VISIBLE,1);
				ChangeImg(panel,control);
			}else if(index==3)
			{
				SetPanelPos(hIV_Panel, 104, 305);
				SetPanelSize(hIV_Panel, 901, 1293);
				DisplayPanel(hIV_Panel);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TXT_MS,ATTR_VISIBLE,0);
				ChangeImg(panel,control);
			}
<<<<<<< HEAD
			else if(index==4) 
			{// 加载Id_Vds Configuration 
				SetPanelPos(IdVgPanel.panelHandle, 104, 305);
				SetPanelSize(IdVgPanel.panelHandle, 901, 1293);
				DisplayPanel(IdVgPanel.panelHandle);
=======
			else if(index==5)// 加载Id_Vds Configuration   
			{
				SetPanelPos(IdVdPanel.panelHandle, 104, 305);
				SetPanelSize(IdVdPanel.panelHandle, 901, 1293);
				DisplayPanel(IdVdPanel.panelHandle);
				SetCtrlAttribute(hBasicSamplePanel,SAMPLE_CFG_TXT_RUNTIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hBasicSamplePanel,SAMPLE_CFG_RUNTIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hBasicSamplePanel,SAMPLE_CFG_TXT_S,ATTR_VISIBLE,0);
			/*	ChangeImg(panel,control);*/
>>>>>>> c2968d55325049810faf6030f4c75b914f2bb4c4
			}
			else if(index==6)//  加载Id_Vgs Configuration  
			{ 	  
				SetPanelPos(IdVgPanel.panelHandle, 104, 305);
				SetPanelSize(IdVgPanel.panelHandle, 901, 1293);
				DisplayPanel(IdVgPanel.panelHandle);
				SetCtrlAttribute(hBasicSamplePanel,SAMPLE_CFG_TXT_RUNTIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hBasicSamplePanel,SAMPLE_CFG_RUNTIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hBasicSamplePanel,SAMPLE_CFG_TXT_S,ATTR_VISIBLE,0);
			/*	ChangeImg(panel,control);*/
			}else if(index==7)//Id-T
			{
			    SetPanelPos(hIdtPanel, 104, 305);
				SetPanelSize(hIdtPanel, 901, 1293);
				DisplayPanel(hIdtPanel);
				SetCtrlAttribute(hBasicSamplePanel,SAMPLE_CFG_TXT_RUNTIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hBasicSamplePanel,SAMPLE_CFG_RUNTIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hBasicSamplePanel,SAMPLE_CFG_TXT_S,ATTR_VISIBLE,1);
			/*	ChangeImg(panel,control);*/
			}
			
			break;
	}  
	return 0;
}
