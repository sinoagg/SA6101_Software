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
int hMainPanel;
int hExpListPanel;
int hGraphPanel;
int hBasicSamplePanel;
int hAdvanceSamplePanel;
int hEnvCfgPanel;
int hResultMenuPanel;
int hTablePanel;
int hSaveDataPanel;
int hSettingsPrjPanel; 
int hGraphSelectPanel;
int hSettingsAboutPanel;
int hIT_Panel;
int hRT_Panel;
int hIV_Panel;
int hSettingsGraphPanel;
int hEnvResultPanel;
int hSettingsPanel;
int hPrjPanel;
int hPrjListPanel;
int hResultDispPanel;
int hIdtPanel;

//==============================================================================
// Global functions

int LoadInitPanel (void)
{
	if ((hMainPanel = LoadPanel (0, "MainPanel.uir", MAIN_PANEL)) < 0)	  //load main panel
		return -1;
	
	if ((hExpListPanel = LoadPanel (hMainPanel, "Experiment List.uir", EXP_LIST)) < 0)		//load left panel
		return -1;
	
	if ((IdVdPanel.panelHandle = LoadPanel (hMainPanel, "Id-Vds Configuration.uir", IDVDS_CFG)) < 0)		//load middle panel
		return -1;
	
	if ((IdVgPanel.panelHandle = LoadPanel (hMainPanel, "Id-Vgs Configuration.uir", IDVGS_CFG)) < 0)		//load middle panel
		return -1;
	
	if((hIdtPanel = LoadPanel(hMainPanel,"Id-t Configuration.uir",IDT_CFG))<0) //load Id-t panel
		return -1;
	
	if ((hBasicSamplePanel = LoadPanel (hMainPanel, "Sample Configuration.uir", SAMPLE_CFG)) < 0)		//load right panel
		return -1;	  

	if ((hAdvanceSamplePanel = LoadPanel (hMainPanel, "Sample Configuration.uir", SAMPLE_ADV)) < 0)		//load right panel
		return -1;
	
	if ((hResultDispPanel = LoadPanel (hMainPanel, "ResultDispPanel.uir", RESULTDISP)) < 0)		//load right panel
		return -1;
	
	if ((hEnvCfgPanel = LoadPanel (hMainPanel, "Environment.uir", ENVIRONMEN)) < 0)		//load Enviroment panel
		return -1;	
	
	if ((hEnvResultPanel = LoadPanel (hMainPanel, "Environment.uir", ENVIRPANEL)) < 0)		//load Enviroment panel
		return -1;													 

	if ((hResultMenuPanel = LoadPanel (hMainPanel, "Result Menu.uir", RESULTMENU)) < 0)		//load hResultMenuPanel panel
		return -1;
	
	if ((hSaveDataPanel = LoadPanel (hMainPanel, "Result Menu.uir", SAVEDATA)) < 0)		//用于弹出savedata面板   
		return -1;
		
	if ((hSettingsPanel = LoadPanel (hMainPanel, "Settings.uir", SETTINGS)) < 0)		//用于弹出settings面板 
		return -1;	

	if ((hSettingsPrjPanel = LoadPanel (hSettingsPanel, "Settings.uir", ENVT)) < 0)		//用于弹出Project Settings面板
		return -1;
	
	if ((hSettingsGraphPanel = LoadPanel (hSettingsPanel, "Settings.uir", GRAPH)) < 0)		//用于弹出Settings->Graph面板  
		return -1;  
	
	if ((hSettingsAboutPanel = LoadPanel (hSettingsPanel, "Settings.uir", ABOUT)) < 0)		//用于弹出Settings->About面板
		return -1;

	if ((hGraphSelectPanel = LoadPanel (hMainPanel, "Result Menu.uir", CHPANEL)) < 0)		//load hGraphSelectPanel panel
		return -1;
	
	
	if ((hGraphPanel = LoadPanel (hMainPanel, "GraphDisp.uir", GRAPHDISP)) < 0)		//load GRAPHDISP panel
		return -1;
	
	if ((hTablePanel = LoadPanel (hMainPanel, "Table.uir", TABLE)) < 0)		//load TABLE panel
		return -1;
	
	if ((hIT_Panel = LoadPanel (hMainPanel, "I-T.uir", ITPANEL)) < 0)		//load I-T  panel
		return -1;
	
	if ((hRT_Panel = LoadPanel (hMainPanel, "R-T.uir", RTPANEL)) < 0)		//load R-T  panel
		return -1;
<<<<<<< HEAD
		
	if ((hPrjPanel = LoadPanel (hMainPanel, "Project.uir", PROPANEL)) < 0)		//load projects panel
=======
	
	if ((hIV_Panel = LoadPanel (hMainPanel, "I-V.uir", IVPANEL))<0)
		return -1;
	
	//弹出projects		
	 if ((hPrjPanel = LoadPanel (hMainPanel, "ProjectPanel.uir", PROPANEL)) < 0)		//load projects panel
		return -1;
	 if ((hPrjListPanel = LoadPanel (hPrjPanel, "ProjectPanel.uir", DEFPANEL)) < 0)		//load projects panel
>>>>>>> c2968d55325049810faf6030f4c75b914f2bb4c4
		return -1;
	
	DisplayPanel (hMainPanel); 
	
	SetPanelPos(hExpListPanel, 105, 3);  //加载面板位置 （,top,left）
	SetPanelSize(hExpListPanel, 900, 300);//加载面板大小  (,height，width)
	DisplayPanel(hExpListPanel);
	
	SetPanelPos(IdVdPanel.panelHandle, 105, 305);
	SetPanelSize(IdVdPanel.panelHandle, 900, 1293);
	DisplayPanel(IdVdPanel.panelHandle);

	return 0;
}
