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
#include "SampleAnalyze.h"
#include "GraphDisp.h"
#include "Environment.h"
#include "Result Menu.h"
#include "Table.h"
#include "I-T.h"
#include "R-T.h"
#include "SetPanel.h"
#include "ProjectPanel.h"
		

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables
extern int mainPanel;
extern int expListPanel;
extern int sampleAnlzPanel;
extern int graphDispPanel;
extern int environmentPanel;
extern int resultPanel;	     //result menu panel
extern int tablePanel;
extern int saveDataPanel; 
extern int envtPanel;  
extern int setGraphPanel;
extern int aboutPanel;
extern int iTPanel;          //I-T panel
extern int rTPanel;          //R-T panel
extern int setPanel;
extern int chPanel;          //chose panel
extern int analyEnvtPanel;
extern int proPanel;
extern int defPanel;
extern int sampleAdvancePanel;

//==============================================================================
// Global functions

int LoadInitPanel (void);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __LoadPanel_H__ */
