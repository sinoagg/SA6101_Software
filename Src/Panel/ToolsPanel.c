#include <userint.h>
#include "Tools.h"

//==============================================================================
//
// Title:		ToolsPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/8/18 at 15:06:35 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "ToolsPanel.h"
#include "LoadPanel.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
#define TXTCOLOR 0xA9A9A9
//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?




int CVICALLBACK ToolsPanelCallback (int panel, int event, void *callbackData,
									int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			RemovePopup(hToolsPanel);
			break;
	}
	return 0;
}

int CVICALLBACK CalibrationCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelSize(hCalibrationPanel,279,386);
			SetPanelPos(hCalibrationPanel,250,920);
			InstallPopup (hCalibrationPanel);
			break;
	}
	return 0;
}

int CVICALLBACK OkCallback (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 HidePanel(hCalibrationPanel); 
			break;
	}
	return 0;
}


int CVICALLBACK OutVoltageCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 SetCtrlAttribute(panel,CALPANEL_OUTVOLCAL,ATTR_LABEL_BGCOLOR,TXTCOLOR);
			 SetCtrlAttribute (panel,CALPANEL_OUTVOLCAL, ATTR_IMAGE_FILE, "Resource\\bg.ico");
			break;
	}
	return 0;
}

int CVICALLBACK ZeroCurrentCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 SetCtrlAttribute(panel,CALPANEL_ZEROCURCAL,ATTR_LABEL_BGCOLOR,TXTCOLOR);
			 SetCtrlAttribute (panel,CALPANEL_ZEROCURCAL, ATTR_IMAGE_FILE, "Resource\\bg.ico");
			break;
	}
	return 0;
}

int CVICALLBACK DangCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 SetCtrlAttribute(panel,CALPANEL_DANG,ATTR_LABEL_BGCOLOR,TXTCOLOR);
			 SetCtrlAttribute (panel,CALPANEL_DANG, ATTR_IMAGE_FILE, "Resource\\bg.ico");
			break;
	}
	return 0;
}
