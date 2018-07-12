#include <userint.h>
//==============================================================================
//
// Title:		SampleCfgPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/10 at 20:38:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "SampleCfgPanel.h"
#include "Sample Configuration.h"
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
SampleCfg_TypeDef SampleCfg;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int GetSampleCfg (int panelHandle)
{
	int temp;
	if(GetCtrlVal(panelHandle, SAMPLE_CFG_QUIETTIME, &temp)<0)
		return -1;
	SampleCfg.cfgQuiteTime=temp;
	if(GetCtrlVal(panelHandle, SAMPLE_CFG_TIMEINTER, &temp)<0)
		return -1;
	SampleCfg.cfgTimeInterval=temp;
	if(GetCtrlVal(panelHandle, SAMPLE_CFG_RUNTIME, &temp)<0)
		return -1;
	SampleCfg.cfgRunTime=temp;
	if(GetCtrlVal(panelHandle, SAMPLE_CFG_SAMPLERATE, &temp)<0)
		return -1;
	SampleCfg.cfgSampleRate=temp;
	if(GetCtrlVal(panelHandle, SAMPLE_CFG_SAMPLENUM, &temp)<0)
		return -1;
	SampleCfg.cfgSampleNum=temp;
	if(GetCtrlVal(panelHandle, SAMPLE_CFG_RANGESET, &temp)<0)
		return -1;
	SampleCfg.cfgRangeSetting=temp;
	
	return 0;
	
}
