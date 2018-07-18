#include "toolbox.h"
#include <userint.h>
#include "SaveData.h"

//==============================================================================
//
// Title:		SaveData.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/18 at 13:11:20 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "SaveData.h"
#include "Graph.h"
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
char sheetSavePath[512];
char graphSavePath[512];
//==============================================================================
// Global functions

int CVICALLBACK BrowseSheetCallback (int panel, int control, int event,
								   	 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\", ".xls", "*.xls", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, sheetSavePath)>0)
				SetCtrlVal(panel, SAVEDATA_SHEETPATH, sheetSavePath);
			break;
	}
	return 0;
}

int CVICALLBACK BrowseGraph1Callback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\", ".jpg", "*.jpg;*.png;*.bmp;*.tif", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, graphSavePath)>0)
				SetCtrlVal(panel, SAVEDATA_GRAPHPATH, graphSavePath);
			break;
	}
	return 0;
}

int CVICALLBACK SaveSheetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			break;
	}
	return 0;
}

int CVICALLBACK SaveGraph1Callback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int bitmapID;
			if(Graph.plotHandle<=0)		//no valid plot behavior
				MessagePopup ("Message", "No valod plot. Please run test first.");
			else
			{
				if(GetCtrlBitmap(graphDispPanel, GRAPHDISP_GRAPH1, Graph.plotHandle,&bitmapID)<0)
					return -1;
				if(SaveBitmapToFile(graphSavePath, bitmapID)<0)
					return -1;
				DiscardBitmap(bitmapID);
			}
			break;
	}
	return 0;
}

int CVICALLBACK SaveAllCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}
