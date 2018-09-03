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
#include "Protocol.h"
#include "main.h"
#include "Tools.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
#define TXTCOLOR 0xA9A9A9  //点击变灰色
#define TXTBGCOLOR 	0x065279L	 //结束恢复颜色

#define CALI_TYPE_OUTPUT 0x00
#define CALI_TYPE_ZERO_CURRENT 0x01  
#define CALI_TYPE_RANGE_CURRENT 0x02
#define CALI_SAVE 0xFF
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
			SetPanelPos(hCalibrationPanel,250,920);
			InstallPopup (hCalibrationPanel);
			break;
	}
	return 0;
}


int CVICALLBACK OutputVoltageCaliCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{

	 switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 SetCtrlAttribute(panel,CALPANEL_OUTVOLCALI,ATTR_LABEL_BGCOLOR,TXTCOLOR);
			 SetCtrlAttribute (panel,CALPANEL_OUTVOLCALI, ATTR_IMAGE_FILE, "Resource\\bg_press.ico");
			 ProtocolCalibrate(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf, CALI_TYPE_OUTPUT, 0);				//send RUN command to instrument via UART 	  
			break;
	}
	return 0;
}

int CVICALLBACK ZeroCurrentCaliCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 SetCtrlAttribute(panel,CALPANEL_ZEROCURCALI,ATTR_LABEL_BGCOLOR,TXTCOLOR);
			 SetCtrlAttribute (panel,CALPANEL_ZEROCURCALI, ATTR_IMAGE_FILE, "Resource\\bg_press.ico");
			 ProtocolCalibrate(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf, CALI_TYPE_ZERO_CURRENT, 0);
			break;
	}
	return 0;
}

int CVICALLBACK RangeCaliCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 unsigned char temp;
			 SetCtrlAttribute(panel,CALPANEL_RANG,ATTR_LABEL_BGCOLOR,TXTCOLOR);
			 SetCtrlAttribute (panel,CALPANEL_RANG, ATTR_IMAGE_FILE, "Resource\\bg_press.ico");
			 GetCtrlAttribute(panel, CALPANEL_RANGESELECT, ATTR_CTRL_VAL, &temp);
			 ProtocolCalibrate(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf, CALI_TYPE_RANGE_CURRENT, temp);
			break;
	}
	return 0;
}


int CVICALLBACK SaveCaliCallback (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			  HidePanel(hCalibrationPanel); 
			  ProtocolCalibrate(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf, CALI_SAVE, 0);  
			 
			break;
	}
	return 0;
}

int CVICALLBACK CancelCaliCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(hCalibrationPanel);								//取消--恢复状态  
			SetCtrlAttribute (panel,CALPANEL_OUTVOLCALI, ATTR_IMAGE_FILE, "Resource\\bg.ico");
			SetCtrlAttribute (panel,CALPANEL_OUTVOLCALI,ATTR_LABEL_BGCOLOR,TXTBGCOLOR); 
			SetCtrlAttribute (panel,CALPANEL_ZEROCURCALI, ATTR_IMAGE_FILE, "Resource\\bg.ico");
			SetCtrlAttribute (panel,CALPANEL_ZEROCURCALI,ATTR_LABEL_BGCOLOR,TXTBGCOLOR); 
			SetCtrlAttribute (panel,CALPANEL_RANG, ATTR_IMAGE_FILE, "Resource\\bg.ico");
			SetCtrlAttribute (panel,CALPANEL_RANG,ATTR_LABEL_BGCOLOR,TXTBGCOLOR); 
			break;
	}
	return 0;
}

int CVICALLBACK RangeSelectCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED: 						//切换档位，更改run状态 
			SetCtrlAttribute(panel,CALPANEL_RANG,ATTR_LABEL_BGCOLOR,TXTBGCOLOR);
			SetCtrlAttribute (panel,CALPANEL_RANG, ATTR_IMAGE_FILE, "Resource\\bg.ico");
			break;
	}
	return 0;
}
