#include "Result Menu.h"
#include "excel2000.h"
#include "excelreport.h"

#include "ProjectPanel.h"
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
#include "ResultMenuPanel.h"
#include "Graph.h"
#include "LoadPanel.h"
//==============================================================================
// Constants

//==============================================================================
// Types
enum ResultDispSelect
{
	DISP_TABLE=0,
	DISP_GRAPH=1
};

enum GraphDispSelect
{
	DISP_SINGLE_GRAPH=0,
	DISP_DOUBLE_GRAPH=1	
};
//==============================================================================
// Static global variables
char sheetSavePath[512];
char graph1SavePath[512];
char graph2SavePath[512];
//==============================================================================
// Static functions
static int SaveGraph(int panel, int control, int plotHandle, const char path[]); 
//==============================================================================
// Global variables
<<<<<<< HEAD
char sheetSavePath[512];
char graph1SavePath[512];
char graph2SavePath[512];

struct Img{

	
}img;
=======
enum ResultDispSelect resultDispSelect=DISP_GRAPH;
enum GraphDispSelect graphDispSelect=DISP_SINGLE_GRAPH;
>>>>>>> 5e089f0250bff32fee3367b5eafc24025e2a42f2
//==============================================================================
// Global functions	

static void DispTable(void)
{
	SetPanelPos(hTablePanel, 172, 305);  
 	SetPanelSize(hTablePanel, 833, 1293);      
	DisplayPanel(hTablePanel);
}

static void DispSingleGraph(void)
{
	SetPanelPos(hGraphPanel, 172, 305);  
	SetPanelSize(hGraphPanel, 833, 1293);
	SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 680);
	SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
	DisplayPanel(hGraphPanel);
	//HidePanel(hGraphSelectPanel);
    //HidePanel(hTablePanel);
}

static void DispDoubleGraph(void)
{
	SetPanelPos(hGraphPanel, 172, 305);  
	SetPanelSize(hGraphPanel, 833, 1293);
	SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //如果CheckBox是选中状态则显示两个graph     
	SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
	DisplayPanel(hGraphPanel);
}

static void DispGraphSelectCheckBox(void)
{
	//int val=0;
	if(graphDispSelect==DISP_SINGLE_GRAPH)
	{
		SetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, 0); 
	}
	else
		SetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, 1);
	SetPanelPos(hGraphSelectPanel, 172, 1457);  
	SetPanelSize(hGraphSelectPanel, 26, 140);      
 	DisplayPanel(hGraphSelectPanel);
}

void DispResultTableGraph(void)
{
	if(resultDispSelect==DISP_TABLE)
		DispTable();
	else
	{
	  	if(graphDispSelect==DISP_SINGLE_GRAPH) 
		DispSingleGraph();
		else if(graphDispSelect==DISP_DOUBLE_GRAPH)
		DispDoubleGraph();
	}
}

int CVICALLBACK TableCallback (int panel, int control, int event,						//点击table图标切换到table面板     
							   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK:
			DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table_pressed.ico"); 
			break;
		case EVENT_LEFT_CLICK_UP:
			DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
			resultDispSelect=DISP_TABLE;
			DispResultTableGraph();
			break;
	}
	
//	GetImageInfo (hResultMenuPanel, RESULTMENU_TABLE, 0, , , );
	return 0;
}

int CVICALLBACK GraphCallback (int panel, int control, int event,						//点击graph图标切换到graph面板    
							   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
<<<<<<< HEAD
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
				DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico");
				HidePanel(hTablePanel);  							                                          
			  	SetPanelPos(hGraphSelectPanel, 172, 1457);  
		     	SetPanelSize(hGraphSelectPanel, 26, 140);      
	 			DisplayPanel(hGraphSelectPanel);
				int val;
				GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
				if(val)
				{
			     	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
				}
			    else
				{
					DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico");
					DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
					DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico"); 
				 }
			    break;
	
=======
		case EVENT_LEFT_CLICK:
			DisplayImageFile(hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
			break;
		case EVENT_LEFT_CLICK_UP:
			DisplayImageFile(hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico");
			if(resultDispSelect==DISP_GRAPH)//如果此时在显示图的时候还去点击图的图标，则认为是想切换显示
		  		DispGraphSelectCheckBox();
			else
			{
				resultDispSelect=DISP_GRAPH;
				DispResultTableGraph();
			}
			break;
>>>>>>> 5e089f0250bff32fee3367b5eafc24025e2a42f2
	}	
	return 0;
}

int CVICALLBACK GraphSelectCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{  
	if( event == EVENT_COMMIT)
	{      	
		HidePanel(hGraphSelectPanel); 
		int val;
	  	GetCtrlVal(panel, CHPANEL_CHECKBOX, &val);
	    if(val)
		{	
			DispDoubleGraph();
			graphDispSelect=DISP_DOUBLE_GRAPH;
		}
		else
		{   	
			DispSingleGraph();
			graphDispSelect=DISP_SINGLE_GRAPH;
		}
	}
	return 0;
}

int CVICALLBACK SaveDataCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	   switch(event)
	   {
			case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico");
				DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\SaveData_pressed.ico"); 
				InstallPopup(hSaveDataPanel); 
		  		break;
	   }	
	return 0;
}

int CVICALLBACK ExitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
<<<<<<< HEAD
{															  
		if (event == EVENT_COMMIT)
		{
			RemovePopup(hSaveDataPanel);  	//移除、关闭savedata面板  
			DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico"); 
		 }
			return 0;
=======
{
	if (event == EVENT_COMMIT)
	{
		RemovePopup(hSaveDataPanel);  	//移除、关闭savedata面板    
	}
	return 0;
>>>>>>> 5e089f0250bff32fee3367b5eafc24025e2a42f2
}

int CVICALLBACK BrowseSheetCallback (int panel, int control, int event,
								   	 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{			
		case EVENT_LEFT_CLICK_UP:
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\", ".xls", "*.xls", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, sheetSavePath)>0)
				SetCtrlVal(panel, SAVEDATA_SHEETPATH, sheetSavePath);
			else 
				return -1;
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
		     
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\UserData", ".jpg", "*.jpg;*.png;*.bmp;*.tif", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, graph1SavePath)>0)
				SetCtrlVal(panel, SAVEDATA_GRAPH1PATH, graph1SavePath);
			else 
				return -1;
			break;
	}
	return 0;
}

int CVICALLBACK BrowseGraph2Callback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\UserData", ".jpg", "*.jpg;*.png;*.bmp;*.tif", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, graph2SavePath)>0)
				SetCtrlVal(panel, SAVEDATA_GRAPH2PATH, graph2SavePath);
			else 
				return -1;
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
			SaveGraph(hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotHandle, graph1SavePath);
			break;
	}
	return 0;
}

 //=======================saveGraph2===================== 
int CVICALLBACK SaveGraph2Callback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SaveGraph(hGraphPanel, GRAPHDISP_GRAPH2, Graph2.plotHandle, graph2SavePath); 
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
			SaveGraph(hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotHandle, graph1SavePath);
			SaveGraph(hGraphPanel, GRAPHDISP_GRAPH2, Graph2.plotHandle, graph2SavePath);
			break;
	}
	return 0;
}

<<<<<<< HEAD

//======================Chose=================================
int CVICALLBACK ChoseCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{  

	switch(event)
	{
			
		case EVENT_VAL_CHANGED: 
			HidePanel(hGraphSelectPanel);
		    int val;
			GetCtrlVal(panel, CHPANEL_CHECKBOX, &val);
			if(val) 
			{	
				SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //如果CheckBox是选中状态则显示两个graph     
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico"); 
			    HidePanel(hTablePanel);
		 	}
			else
			{   	

				SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 680);
				SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0); 
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
		     }
		break;
    }
  	return 0;  
}

=======
>>>>>>> 5e089f0250bff32fee3367b5eafc24025e2a42f2
//===================saveGraph================
static int SaveGraph(int panel, int control, int plotHandle, const char path[])
{
	int bitmapID;
	if(plotHandle<=0)		//no valid plot behavior
		MessagePopup ("Message", "No valod plot. Please run test first.");
	else
	{
		if(GetCtrlBitmap(panel, control, plotHandle,&bitmapID)<0)
			return -1;
		if(SaveBitmapToFile(path, bitmapID)<0)		 //need check the file format
			return -1;
		DiscardBitmap(bitmapID);
	}
	return 0;
}

//======================saveConfiguration==========================
static int SaveConfigToFiles(char* pConfigSavePaths)
{
	FILE * fp = NULL;							//表示打开的文件
	fp = fopen(pConfigSavePaths, "w");
	if(fp == NULL)
	{
		MessagePopup ("Error", "Invalid Path, please select path to save configurations.");
		if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, pConfigSavePaths)<0)
			return -1;
	}
	else
	{
		int maxCommentSize=255;
		char comment[maxCommentSize];
 
		fclose(fp);//关闭文件
	}
	return 0;
	
}

int CVICALLBACK SaveSheetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	

   return 0;
}

