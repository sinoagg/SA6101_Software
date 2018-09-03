//==============================================================================
//
// Title:		AbnormalDataCache.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/8/28 at 10:40:52 by Ma Hongwei.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __AbnormalDataCache_H__
#define __AbnormalDataCache_H__

#ifdef __cplusplus
    extern "C" {
#endif
//==============================================================================
// Include files
#include "excelreport.h"
#include <utility.h> 
#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions
int LaunchExcelCB ();
int ShowAndOpenExcelCB ();
int ShutDownExcelCB();
int SaveExcelCB(int panel, int control, char cellRange[]);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __AbnormalDataCache_H__ */
