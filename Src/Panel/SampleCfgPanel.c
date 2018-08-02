#include "Sample Configuration.h"
#include <userint.h>
//==============================================================================
//
// Title:		SampleCfgPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/10 at 20:38:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "SampleCfgPanel.h"
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
int CVICALLBACK AdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hAdvanceSamplePanel, 105, 1600);
			SetPanelSize(hAdvanceSamplePanel, 449, 300);
			DisplayPanel(hAdvanceSamplePanel);
			break;
	}
	return 0;
}

int CVICALLBACK BasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(hBasicSamplePanel, 105, 1600);
				SetPanelSize(hBasicSamplePanel, 449, 300);
				DisplayPanel(hBasicSamplePanel);
			break;
	}
	return 0;
}

