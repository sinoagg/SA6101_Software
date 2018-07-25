//==============================================================================
//
// Title:		MainPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/16 at 15:58:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __MainPanel_H__
#define __MainPanel_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "ExpListPanel.h"
#include "SampleCfgPanel.h"
#include "IdVdsPanel.h"
#include "IdVgsPanel.h"
#include "Protocol.h"
#include "Graph.h"
#include "Curve.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables
extern unsigned char comSelect1;
extern unsigned char comSelect2; 
//==============================================================================
//// Global functions
//<<<<<<< HEAD
static int SaveConfigToFile(char* pConfigSavePath);

//=======

static int SaveConfigToFile(char* pConfigSavePath);
//>>>>>>> refs/remotes/origin/master

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __MainPanel_H__ */
