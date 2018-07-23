//==============================================================================
//
// Title:		main.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/23 at 13:28:04 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __main_H__
#define __main_H__

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

//==============================================================================
// External variables

//==============================================================================
// Global functions

void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData);
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);

static int CheckPortStatus(unsigned char portNumber);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __main_H__ */
