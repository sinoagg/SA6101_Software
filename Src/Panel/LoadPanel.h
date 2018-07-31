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
#include "SettingsPanel.h"
#include "ProjectPanel.h"
#include "ResultDispPanel.h"
		

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables
extern int mainPanel;
extern int expListPanel;
extern int samplePanel;
extern int hGraphPanel;
extern int environmentPanel;
extern int resultPanel;	     //result menu panel
extern int tablePanel;
extern int hResultDispPanel;
extern int saveDataPanel; 
extern int ENVTPanel;  
extern int GRAPHPanel;
extern int ABOUTPanel;
extern int iTPanel;          //I-T panel
extern int rTPanel;          //R-T panel
extern int setPanel;
extern int doubleGraphDispPanel;      // double graph panel 
extern int chPanel;          //chose panel
extern int AnalyenvirPanel;
extern int proPanel;
extern int defPanel;
extern int sampleBasicPanel;

//==============================================================================
// Global functions

int LoadInitPanel (void);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __LoadPanel_H__ */
