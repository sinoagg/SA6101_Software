//==============================================================================
//
// Title:		SettingsPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/10 at 18:10:32 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __SettingsPanel_H__
#define __SettingsPanel_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files
#include "cvidef.h"
#include "Settings.h"
#include "Curve.h"
//==============================================================================
// Constants
#define GRAPH1 0
#define GRAPH2 1
#define CURVE1 0
#define CURVE2 1  
#define CURVE3 2  
//==============================================================================
// Types

//==============================================================================
// External variables
extern char ProjectSavePath[512];	   //本地工作目录Dir 
extern CurveAttrTypeDef* pCurveAttr;
extern CurveAttrTypeDef Graph2_CurveAttr1;
extern CurveAttrTypeDef Graph2_CurveAttr2;
extern CurveAttrTypeDef Graph2_CurveAttr3;
//==============================================================================
// Global functions
CurveAttrTypeDef* GetSettingsCurveAttr(int GraphIndex, int CurveIndex);
int GetVersions();
int CheckUpdate();
int CheckSoftware();
int CheckHardware();

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __IdVdsPanel_H__ */
