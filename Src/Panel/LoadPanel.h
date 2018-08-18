//==============================================================================
//
// Title:		LoadPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/16 at 15:21:14 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __LoadPanel_H__
#define __LoadPanel_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "MainPanel.h"
#include "Experiment List.h"
#include "Id-Vds Configuration.h"
#include "Id-Vgs Configuration.h"
#include "Sample Configuration.h"
#include "GraphDisp.h"
#include "Environment.h"
#include "Result Menu.h"
#include "Table.h"
#include "I-T.h"
#include "R-T.h" 
#include "I-V.h"  
#include "SettingsPanel.h"
#include "Project.h"
#include "ResultDispPanel.h"
#include "Id-t Configuration.h"
#include "Terminal.h"


		

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables
extern int hMainPanel;
extern int hExpListPanel;
extern int hGraphPanel;
extern int hBasicSamplePanel;  
extern int hAdvanceSamplePanel;
extern int hEnvCfgPanel;
extern int hResultMenuPanel;	     //result menu panel
extern int hTablePanel;
extern int hResultDispPanel;
extern int hSaveDataPanel; 
extern int hSettingsPrjPanel;  
extern int hSettingsGraphPanel;
extern int hSettingsAboutPanel;
extern int hIdVgPanel;
extern int hIT_Panel;          //I-T panel
extern int hRT_Panel;          //R-T panel
extern int hIV_Panel;          //I-V panel
extern int hSettingsPanel;
extern int hGraphSelectPanel;          //chose panel
extern int hEnvResultPanel;
extern int hPrjPanel;
extern int hPrjListPanel;
extern int hIdtPanel;
extern int hTwoTerminalPanel;
extern int hFourTerminalPanel;


//==============================================================================
// Global functions

int LoadInitPanel (void);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __LoadPanel_H__ */
