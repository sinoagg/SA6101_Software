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
int graphDispPanel;
int environmentPanel;
int resultPanel;
int tablePanel;
int saveDataPanel;
int envtPanel; 
int setGraphPanel;
int aboutPanel;
int iTPanel;
int rTPanel;
int chPanel;
int analyEnvtPanel;
int setPanel;
int proPanel;
int defPanel;
int sampleAnlzPanel;
int sampleAdvancePanel;
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
	
	
	 
	if ((samplePanelHandle = LoadPanel (mainPanel, "Sample Configuration.uir", SAMPLE_CFG)) < 0) //load SampleBasicPanel panel 
	   	return -1;	  
	
	if ((sampleAdvancePanel = LoadPanel (mainPanel, "Sample Configuration.uir", SAMPLE_ADV)) < 0)	//AdvanceSettings Panel 	
		return -1;
	if ((sampleAnlzPanel = LoadPanel (mainPanel, "Sample Analyze.uir", SMALZPANEL)) < 0)		//load right panel
		return -1;
	
	
	if ((environmentPanel = LoadPanel (mainPanel, "Environment.uir", ENVIRONMEN)) < 0)		//load Enviroment panel
		return -1;													 
	if ((analyEnvtPanel = LoadPanel (mainPanel, "Environment.uir", ENVIRPANEL)) < 0)		//load Enviroment panel
		return -1;													 
	

	if ((resultPanel = LoadPanel (mainPanel, "Result Menu.uir", RESULTMENU)) < 0)		//load resultPanel panel
		return -1;
	if ((saveDataPanel = LoadPanel (mainPanel, "Result Menu.uir", SAVEDATA)) < 0)		//load savedata panel
		return -1;
	if ((chPanel = LoadPanel (mainPanel, "Result Menu.uir", CHPANEL)) < 0)		//load chPanel panel	选择 
		return -1;
	
	

	if ((setPanel = LoadPanel (mainPanel, "Settings.uir", SETTINGS)) < 0)		//load settings panel
		return -1;	
	if ((envtPanel = LoadPanel (setPanel, "Settings.uir", ENVT)) < 0)		//load Environment Settings panel
		return -1;
	if ((setGraphPanel = LoadPanel (setPanel, "Settings.uir", GRAPH)) < 0)		//load Graph Defaults panel
		return -1;  
	if ((aboutPanel = LoadPanel (setPanel, "Settings.uir", ABOUT)) < 0)		//load About panel
		return -1;
 
	if ((graphDispPanel = LoadPanel (mainPanel, "GraphDisp.uir", GRAPHDISP)) < 0)		//load GRAPHDISP panel
		return -1;
	
	if ((tablePanel = LoadPanel (mainPanel, "Table.uir", TABLE)) < 0)		//load TABLE panel
		return -1;
	
	if ((iTPanel = LoadPanel (mainPanel, "I-T.uir", ITPANEL)) < 0)		//load I-T  panel
		return -1;
	
	if ((rTPanel = LoadPanel (mainPanel, "R-T.uir", RTPANEL)) < 0)		//load R-T  panel
		return -1;
	
		
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
