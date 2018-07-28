//==============================================================================
//
// Title:		ExpListPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/11 at 9:55:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __ExpListPanel_H__
#define __ExpListPanel_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int panelHandle;
	int VdStartID;									//voltage drain start
	int VdStopID;									//voltage drain stop
	int VdStepID;									//voltage drain step
	int VgStartID;									//voltage gate start
	int VgStopID;									//voltage gate stop
	int VgStepID;									//voltage gate step
}ExpPanelTypeDef;
//==============================================================================
// External variables

//==============================================================================
// Global functions



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __ExpListPanel_H__ */
