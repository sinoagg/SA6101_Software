//==============================================================================
//
// Title:		AutoSaveDataPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/10/22 at 16:14:52 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __AutoSaveDataPanel_H__
#define __AutoSaveDataPanel_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "ResultMenuPanel.h"
//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	char FileName[512];
	char FileDate[16];
	char FileTime[16];
	char *pFileName;
	char *pFileDate;
	char *pFileTime;
}FileNameTypeDef;		
//==============================================================================
// External variables
  
//==============================================================================
// Global functions
int  CVICALLBACK AUTOSAVECB(int panel, int event, void *callbackData, int eventData1, int eventData2);  

void AutoSaveSheetAndGraph();
void SaveGraphs(char path[]);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __AutoSavePanel_H__ */
