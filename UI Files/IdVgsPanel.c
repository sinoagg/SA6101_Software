#include <userint.h>
//==============================================================================
//
// Title:		IdVgsPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/11 at 13:36:34 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "IdVgsPanel.h"
#include "Id-Vgs Configuration.h"
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
IdVgCfg_TypeDef IdVgCfg; 
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int GetIdVgCfg (int panelHandle)
{
	/*int temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VD_START, &temp)<0)
		return -1;
	IdVgCfg.cfgVdstart=temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VD_STOP, &temp)<0)
		return -1;
	IdVgCfg.cfgVdstop=temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VD_STEP, &temp)<0)
		return -1;
	IdVgCfg.cfgVdstep=temp;*/
	
	
		int temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_BIAS, &temp)<0)
		return -1;
	IdVgCfg.cfgVdstart=temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_COMPL_2, &temp)<0)
		return -1;
	IdVgCfg.cfgVdstop=temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_BIAS_2, &temp)<0)
		return -1;
	IdVgCfg.cfgVdstep=temp;
	
	
	
	
	
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_START, &temp)<0)
		return -1;
	IdVgCfg.cfgVgstart=temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_STOP, &temp)<0)
		return -1;
	IdVgCfg.cfgVgstop=temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_STEP, &temp)<0)
		return -1;
	IdVgCfg.cfgVgstep=temp;
	
	return 0;
}


//----------------------------------------------------------------
int CVICALLBACK GateCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	int IdVgPanel;
	
	   switch(event){
		   case EVENT_LEFT_CLICK_UP:
			      DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg.ico");
				 
			   break;
	   
	   }
	return 0;
}

