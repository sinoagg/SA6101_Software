//==============================================================================
//
// Title:		IdtPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/8/13 at 19:20:06 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
 #include <userint.h>   
#include "IdtPanel.h"
#include "Id-t Configuration.h"
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
ExpPanelTypeDef IdtPanel={
	0, 
	IDT_CFG_VG_START, 
	IDT_CFG_GATEMODE, 
	IDT_CFG_VD_START, 
	IDT_CFG_DRAINMODE, 
	//IDVGS_CFG_VD_STEP, 
	//IDVGS_CFG_DRAINMODE, 
	//IDVGS_CFG_GATEMODE,
	
};
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
//int Define_Your_Functions_Here (int x)
//{
//	return x;
//}
