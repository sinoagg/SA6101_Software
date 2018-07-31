#include <userint.h>
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
#include "LoadPanel.h"
#include "IdVdsPanel.h"
#include "IdVgsPanel.h"
#include "SampleCfgPanel.h"
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
int mainPanel;
int expListPanel;
int hGraphPanel;
int environmentPanel;
int resultPanel;
int tablePanel;
int saveDataPanel;
int ENVTPanel; 
int hGraphPanel;
int ABOUTPanel;
int iTPanel;
int rTPanel;
int chPanel;
int AnalyenvirPanel;
int setPanel;
int proPanel;
int defPanel;
int hResultDispPanel;
int sampleBasicPanel;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int LoadInitPanel (void)
{
	if ((mainPanel = LoadPanel (0, "MainPanel.uir", MAIN_PANEL)) < 0)	  //load main panel
		return -1;
	
	if ((expListPanel = LoadPanel (mainPanel, "Experiment List.uir", EXP_LIST)) < 0)		//load left panel
		return -1;
	
	if ((IdVdPanel.panelHandle = LoadPanel (mainPanel, "Id-Vds Configuration.uir", IDVDS_CFG)) < 0)		//load middle panel
		return -1;
	
	if ((IdVgPanel.panelHandle = LoadPanel (mainPanel, "Id-Vgs Configuration.uir", IDVGS_CFG)) < 0)		//load middle panel
		return -1;
	
	if ((samplePanelHandle = LoadPanel (mainPanel, "Sample Configuration.uir", SAMPLE_CFG)) < 0)		//load right panel

		return -1;	  
		
	if ((sampleBasicPanel = LoadPanel (mainPanel, "Sample Configuration.uir", SAMPLE_ADV)) < 0)		//load right panel
		return -1;
	if ((hResultDispPanel = LoadPanel (mainPanel, "ResultDispPanel.uir", RESULTDISP)) < 0)		//load right panel
		return -1;
	
	if ((environmentPanel = LoadPanel (mainPanel, "Environment.uir", ENVIRONMEN)) < 0)		//load Enviroment panel
		return -1;													 
	if ((AnalyenvirPanel = LoadPanel (mainPanel, "Environment.uir", ENVIRPANEL)) < 0)		//load Enviroment panel
		return -1;													 
	

	if ((resultPanel = LoadPanel (mainPanel, "Result Menu.uir", RESULTMENU)) < 0)		//load resultPanel panel
		return -1;
	
	 //用于弹出savedata面板
	if ((saveDataPanel = LoadPanel (mainPanel, "Result Menu.uir", SAVEDATA)) < 0)		//load savedata panel
		return -1;

		//用于弹出settings面板
	//if ((setPanel = LoadPanel (mainPanel, "Settings.uir", SETTINGS)) < 0)		//load settings panel
	//	return -1;	
	 //用于弹出Environment Settings面板

	//if ((ENVTPanel = LoadPanel (setPanel, "Settings.uir", ENVT)) < 0)		//load ENV panel
	//	return -1;
	//用于弹出Graph Defaults面板
	//if ((GRAPHPanel = LoadPanel (setPanel, "Settings.uir", GRAPH)) < 0)		//load graph panel
	//	return -1;  
	//用于弹出About面板
	//if ((ABOUTPanel = LoadPanel (setPanel, "Settings.uir", ABOUT)) < 0)		//load graph panel
	//	return -1;
 
	//选择
	if ((chPanel = LoadPanel (mainPanel, "Result Menu.uir", CHPANEL)) < 0)		//load chPanel panel
		return -1;
	
	
	if ((hGraphPanel = LoadPanel (mainPanel, "GraphDisp.uir", GRAPHDISP)) < 0)		//load GRAPHDISP panel
		return -1;
	
	if ((tablePanel = LoadPanel (mainPanel, "Table.uir", TABLE)) < 0)		//load TABLE panel
		return -1;
	
	if ((iTPanel = LoadPanel (mainPanel, "I-T.uir", ITPANEL)) < 0)		//load I-T  panel
		return -1;
	
	if ((rTPanel = LoadPanel (mainPanel, "R-T.uir", RTPANEL)) < 0)		//load R-T  panel
		return -1;
	
	//弹出projects		
	 if ((proPanel = LoadPanel (mainPanel, "ProjectPanel.uir", PROPANEL)) < 0)		//load projects panel
		return -1;
	 if ((defPanel = LoadPanel (proPanel, "ProjectPanel.uir", DEFPANEL)) < 0)		//load projects panel
		return -1;
	
	DisplayPanel (mainPanel); 
	
	SetPanelPos(expListPanel, 105, 3);  //加载面板位置 （,top,left）
	SetPanelSize(expListPanel, 900, 300);//加载面板大小  (,height，width)
	DisplayPanel(expListPanel);
	
	SetPanelPos(IdVdPanel.panelHandle, 105, 305);
	SetPanelSize(IdVdPanel.panelHandle, 900, 1293);
	DisplayPanel(IdVdPanel.panelHandle);
	
	SetPanelPos(samplePanelHandle, 105, 1600);
	SetPanelSize(samplePanelHandle, 449, 300);
	DisplayPanel(samplePanelHandle);
	
	SetPanelPos(environmentPanel, 556, 1600);
	SetPanelSize(environmentPanel, 449, 300);
	DisplayPanel(environmentPanel);
	
	return 0;
}
