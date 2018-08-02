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


int CVICALLBACK TreeCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			int index;
			GetActiveTreeItem (panel, control, &index);//获得当前点击项目值		   
			if(index==1)
			{ 	//加载I-T
				SetPanelPos(hIT_Panel, 104, 305);
				SetPanelSize(hIT_Panel, 901, 1293);
				DisplayPanel(hIT_Panel);
				SetPanelPos(hResultDispPanel, 104, 1600);
			    SetPanelSize(hResultDispPanel, 450 ,300);
			    DisplayPanel(hResultDispPanel);
		        SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TXT_ms,ATTR_VISIBLE,1);
			}
			else if(index==2)
			{	//加载R-T 	
				SetPanelPos(hRT_Panel, 104, 305);
				SetPanelSize(hRT_Panel, 901, 1293);
				DisplayPanel(hRT_Panel);	
				SetPanelPos(hResultDispPanel, 104, 1600);
			    SetPanelSize(hResultDispPanel, 450, 300);
			    DisplayPanel(hResultDispPanel);
		        SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,1);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TXT_ms,ATTR_VISIBLE,1);
			}
			else if(index==4) 
			{// 加载Id_Vds Configuration 
				SetPanelPos(IdVdPanel.panelHandle, 104, 305);
				SetPanelSize(IdVdPanel.panelHandle, 901, 1293);
				DisplayPanel(IdVdPanel.panelHandle);
			}
			else if(index==5)
			{ 	//  加载Id_Vgs Configuration    
				SetPanelPos(IdVgPanel.panelHandle, 104, 305);
				SetPanelSize(IdVgPanel.panelHandle, 901, 1293);
				DisplayPanel(IdVgPanel.panelHandle);
			}
			else if(index==0||index==3||index==4||index==5)
			{
				//
			    SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,0);
				SetCtrlAttribute(hResultDispPanel, RESULTDISP_TXT_ms,ATTR_VISIBLE,0);
			}
			break;
	}  
	return 0;
}
