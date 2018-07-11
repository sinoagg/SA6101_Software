#include <userint.h>
//==============================================================================
//
// Title:		IdVdsPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/10 at 18:10:32 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "IdVdsPanel.h"
#include "Id-Vds Configuration.h"
//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int cfgVdstart;									//voltage drain start
	int cfgVdstop;									//voltage drain stop
	int cfgVdstep;									//voltage drain step
	int cfgVgstart;									//voltage gate start
	int cfgVgstop;									//voltage gate stop
	int cfgVgstep;									//voltage gate step
}IdVdCfg_TypeDef;

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
IdVdCfg_TypeDef IdVdCfg;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int GetIdVdCfg (int panelHandle)
{
	int temp;
	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_START, &temp)<0)
		return -1;
	IdVdCfg.cfgVdstart=temp;
	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_STOP, &temp)<0)
		return -1;
	IdVdCfg.cfgVdstop=temp;
	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_STEP, &temp)<0)
		return -1;
	IdVdCfg.cfgVdstep=temp;
	
	if(GetCtrlVal(panelHandle, IDVDS_CFG_VG_START, &temp)<0)
		return -1;
	IdVdCfg.cfgVgstart=temp;
	if(GetCtrlVal(panelHandle, IDVDS_CFG_VG_STOP, &temp)<0)
		return -1;
	IdVdCfg.cfgVgstop=temp;
	if(GetCtrlVal(panelHandle, IDVDS_CFG_VG_STEP, &temp)<0)
		return -1;
	IdVdCfg.cfgVgstep=temp;
	
	return 0;
}




















