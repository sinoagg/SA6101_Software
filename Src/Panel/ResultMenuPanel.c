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

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
char sheetSavePath[512];
char graph1SavePath[512];
char graph2SavePath[512];

//==============================================================================
// Global functions	

int CVICALLBACK TableCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	
	//���tableͼ���л���table���
	switch(event){
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table_pressed.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico");
			break;
		case EVENT_LEFT_CLICK:
			   	SetPanelPos(tablePanel, 172, 305);  
		     	SetPanelSize(tablePanel, 833, 1293);      
	 			DisplayPanel(tablePanel);
			break;
	
	}
	return 0;
}

int CVICALLBACK GraphCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
		//���graphͼ���л���graph���
	switch(event){
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
				DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico"); 
				
			break;
		case EVENT_LEFT_CLICK:
		
		
				HidePanel(tablePanel);  							                                          
			  	SetPanelPos(chPanel, 172, 1457);  
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
			   //����savedata���
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
	    		//�Ƴ����ر�savedata���
				RemovePopup(saveDataPanel);
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
			SaveGraph(doubleGraphDispPanel, GRAPHDISP_GRAPH2, Graph2.plotHandle, graph2SavePath); 
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


//======================Chose=================================
int CVICALLBACK ChoseCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int CheckValue;
	if( event == EVENT_VAL_CHANGED)
	{   HidePanel(chPanel);
		GetCtrlVal(panel, CHPANEL_CHECKBOX, &CheckValue);
		if(CheckValue)
		{	 //���CheckBox��ѡ��״̬����ʾ����graph
		
			SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400);
			SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
		
			HidePanel(chPanel);
		    HidePanel(tablePanel);
		
		}
		else
		{
			
			SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 680);
			SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0); 
		}
	}
	return 0;
}
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

//======================saveSheet==========================
//����ΪExcel���
static CAObjHandle applicationHandle = 0;
static CAObjHandle workbookHandle = 0;
static CAObjHandle worksheetHandle = 0;
static row=0;
static clomun=0;

static int SaveConfigToFiles(char* pConfigSavePaths)
{
	FILE * fp = NULL;							//��ʾ�򿪵��ļ�
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
 
		fclose(fp);//�ر��ļ�
	}
	return 0;
	
}
int CVICALLBACK SaveSheetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	
	
 /*   int error;
	char strBuf[20]={0};
	char strB[20]={0};

	char dataA[12]={"��һ�� "};
	char dataB[12]={"�ڶ��� "};
	char configSavePaths[512]={0};

	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			 	if(FileSelectPopupEx("C:\\SINOAGG\\SA6101\\", ".xls", "*.xls", "Select Path", VAL_OK_BUTTON, 1, 0,  configSavePaths)>0)
				SaveConfigToFiles(configSavePaths);
		
	//����Excel ExcelRpt_ApplicationNew   ExcelRpt_WorkbookNew
			
			error = ExcelRpt_ApplicationNew(VTRUE, &applicationHandle);  
			if (error<0) 
			{
        		MessagePopup ("����Excel����","�Զ������ӿڷ�������");
               
			}
	 		ExcelRpt_WorkbookNew(applicationHandle, &workbookHandle);
			
			
		//�����¹�����	
	    ExcelRpt_WorksheetNew(workbookHandle, -1, &worksheetHandle);
		
		SetCtrlAttribute(panel, SAVEDATA_SAVESHEET, ATTR_DIMMED, 1);
		//��table�е����ݶ�ȡ���洢��Excel��
		for(clomun;clomun<10;){
			
		  	for(row;row<=clomun;){
				
				sprintf(strBuf,"%s%d","A",++row); //��ʽ���ַ���
			
				ExcelRpt_SetCellValue(worksheetHandle,strBuf,CAVT_CSTRING,dataA);//��һ��
				  
			
			} 	
			sprintf(strB,"%s%d","B",++clomun);
			ExcelRpt_SetCellValue(worksheetHandle,strB,CAVT_CSTRING,dataB); //�ڶ���
		}
	
			//FileSelectPopupEx ;
		
			
		break; 
	
	}*/
   return 0;
}

