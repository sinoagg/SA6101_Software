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
 #define FOCUS	0
#define UNFOCUS 1
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
	IDT_CFG_VG_START, 
	IDT_CFG_GATEMODE, 
	IDT_CFG_VD_START, 
	IDT_CFG_DRAINMODE,
	
};
//==============================================================================
// Global functions

static void SetDrainDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{							
		DisplayImageFile (panel, IDT_CFG_PIC_DRAIN, "Resource\\Drain_pressed.png");// change picture 
	}
	else
	{
		DisplayImageFile (panel, IDT_CFG_PIC_DRAIN, "Resource\\Drain.png");// change picture 
	}
}

static void SetGateDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		DisplayImageFile (panel, IDT_CFG_PIC_GATE, "Resource\\gate_pressed.png");// change picture 
	}
	else
	{
		DisplayImageFile (panel, IDT_CFG_PIC_GATE, "Resource\\gate.png");// change picture 
	}
}

int CVICALLBACK IdtGateDecoCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	   case EVENT_LEFT_CLICK_UP:
	      SetDrainDisp(panel, UNFOCUS);
		  SetGateDisp(panel, FOCUS);
		  break;
	}
	return 0;
}

int CVICALLBACK IdtGateModeCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
	   case EVENT_LEFT_CLICK_UP:
	      SetDrainDisp(panel, UNFOCUS);
		  SetGateDisp(panel, FOCUS);
		  break;
	}
	return 0;
}

int CVICALLBACK IdtGateStartCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
	   case EVENT_LEFT_CLICK_UP:
	      SetDrainDisp(panel, UNFOCUS);
		  SetGateDisp(panel, FOCUS);
		  break;
	}
	return 0;
}

int CVICALLBACK IdtDrainDecoCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
		switch(event){
	   case EVENT_LEFT_CLICK_UP:
	      SetDrainDisp(panel, FOCUS);
		  SetGateDisp(panel, UNFOCUS);
		  break;
	}
	return 0;
}

int CVICALLBACK IdtDrainModeCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
		switch(event){
	   case EVENT_LEFT_CLICK_UP:
	      SetDrainDisp(panel, FOCUS);
		  SetGateDisp(panel, UNFOCUS);
		  break;
	}
	return 0;
}

int CVICALLBACK IdtDrainStartCallback (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	   case EVENT_LEFT_CLICK_UP:
	      SetDrainDisp(panel, FOCUS);
		  SetGateDisp(panel, UNFOCUS);
		  break;
	}
	return 0;
}
