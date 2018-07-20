#include "GraphDisp.h"

//==============================================================================
//
// Title:		LoadPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 15:21:14 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <userint.h>
#include "toolbox.h"   
#include "Result Menu.h"
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

int CVICALLBACK TableCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	
	//点击table图标切换到table面板
	switch(event){
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table_pressed.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico");
			break;
		case EVENT_LEFT_CLICK:
			   	SetPanelPos(tablePanel, 176, 305);  
		     	SetPanelSize(tablePanel, 830, 1293);      
	 			DisplayPanel(tablePanel);
			break;
	
	}
	return 0;
}

int CVICALLBACK GraphCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
		//点击graph图标切换到graph面板
	switch(event){
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
				DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico"); 
				
			break;
		case EVENT_LEFT_CLICK:
			/*
			    SetPanelPos(graphDispPanel, 176, 305);  
		     	SetPanelSize(graphDispPanel, 830, 1293);
				DisplayPanel(graphDispPanel);*/
		
											                                          
			  	SetPanelPos(chPanel, 176, 1457);  
		     	SetPanelSize(chPanel, 26, 140);      
	 			DisplayPanel(chPanel);
			break;
	}	
	return 0;
}

int CVICALLBACK SaveDataCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)

{
	   switch(event){
		case EVENT_LEFT_CLICK_UP:
			
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico");
				DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData_pressed.ico"); 
		  
			break;
		 case EVENT_LEFT_CLICK:
			   //弹出savedata面板
			   InstallPopup(saveDataPanel);
			break;
	}	
	return 0;
}

int CVICALLBACK ExitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
		if (event == EVENT_COMMIT)
				{
	    		//移除、关闭savedata面板
				RemovePopup (saveDataPanel);
		        }
			return 0;
}


int CVICALLBACK BrowseSheetCallback (int panel, int control, int event,
								   	 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{			
		case EVENT_LEFT_CLICK_UP:
			
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
				SetCtrlVal(panel, SAVEDATA_GRAPH1PATH, graphSavePath);
			break;
	}
	return 0;
}


//=======================saveGraph1=====================
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
				if(SaveBitmapToFile(graphSavePath, bitmapID)<0)		 //need check the file format
					return -1;
				DiscardBitmap(bitmapID);
			}
			break;
	}
	return 0;
}

//======================saveSheet==========================
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

//=======================saveAll============================
int CVICALLBACK SaveAllCallback (int panel, int control, int event,
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
				if(SaveBitmapToFile(graphSavePath, bitmapID)<0)		 //need check the file format
					return -1;
				DiscardBitmap(bitmapID);
			}
			break;
	}
	return 0;
}


//======================Chose=================================
int CVICALLBACK ChoseCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int CheckValue;
	if( event == EVENT_VAL_CHANGED)
	{
		GetCtrlVal(panel, CHPANEL_CHECKBOX, &CheckValue);
				 if(CheckValue)
			 {	 //如果CheckBox是选中状态则显示两个graph
				SetPanelPos(doublePanel, 176, 305);
				SetPanelSize(doublePanel, 829, 1293);
				DisplayPanel(doublePanel);
			    HidePanel(tablePanel);
				//HidePanel(graphDispPanel);
			 }else{
				HidePanel(doublePanel); 
				
				 }
	  	      	
	}
	return 0;
}
