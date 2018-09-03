#include "Id-Vgs Configuration.h"
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

#include "IdVdsPanel.h"
#include "Id-Vds Configuration.h"

#define COLOR_GREY 0xA9A9A9L
#define COLOR_BLUE 0xA0B4DCL   // µã»÷¼¤»îÀ¶É« 
#define FOCUS	0
#define UNFOCUS 1
#define BIAS 0
#define STEP 2
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
ExpPanelTypeDef IdVdPanel={
	0,
	IDVDS_CFG_VD_START, 
	IDVDS_CFG_VD_STOP, 
	IDVDS_CFG_VD_STEP, 
	IDVDS_CFG_VG_START, 
	IDVDS_CFG_VG_STOP, 
	IDVDS_CFG_VG_STEP,
	IDVDS_CFG_DRAINMODE,
	IDVDS_CFG_GATEMODE,
	}; 


//==============================================================================
// Global functions
static void SetDrainDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\Drain_pressed.png");// change picture 
	}
	else
	{
		DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\Drain.png");// change picture 
	}
}

static void SetGateDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\gate_pressed.png");// change picture 
	}
	else
	{
		DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\gate.png");// change picture 
	}
}

int CVICALLBACK IdVdGateDecoCallback (int panel, int control, int event,
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

int CVICALLBACK IdVdDrainDecoCallback (int panel, int control, int event,
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

int CVICALLBACK IdVdGateModeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{	   
	 switch(event){

		case EVENT_LEFT_CLICK_UP:
			SetDrainDisp(panel, UNFOCUS);
		  	SetGateDisp(panel, FOCUS);
		 	break;
		case EVENT_VAL_CHANGED:
			int val;
			GetCtrlVal(panel,IDVDS_CFG_GATEMODE,&val);	    
			if(val==STEP)
			{
		    	DisplayImageFile (panel, IDVDS_CFG_PIC_IDVD_GATE, "Resource\\V_Step.ico");
				SetCtrlAttribute(panel, IDVDS_CFG_VG_STOP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVDS_CFG_TXT_STOP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVDS_CFG_MV_STOP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVDS_CFG_VG_STEP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVDS_CFG_TXT_STEP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVDS_CFG_MV_STEP,ATTR_VISIBLE,1);
			}
			else if(val==BIAS)
			{
				DisplayImageFile (panel, IDVDS_CFG_PIC_IDVD_GATE, "Resource\\V_Bias.ico");
				SetCtrlAttribute(panel, IDVDS_CFG_VG_STOP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVDS_CFG_TXT_STOP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVDS_CFG_MV_STOP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVDS_CFG_VG_STEP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVDS_CFG_TXT_STEP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVDS_CFG_MV_STEP,ATTR_VISIBLE,0);
			}
			break;
		 }  
	return 0;
}

int CVICALLBACK IdVdDrainModeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{	   
	 switch(event)
	 {
		case EVENT_LEFT_CLICK_UP:
			SetDrainDisp(panel, FOCUS);
		  	SetGateDisp(panel, UNFOCUS);
			break;
		 }  
	return 0;
}

int CVICALLBACK IdVdGateStartCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	 if(event==EVENT_LEFT_CLICK_UP)
	 {
		 SetDrainDisp(panel, UNFOCUS);
		 SetGateDisp(panel, FOCUS);
     }
	return 0;
}

int CVICALLBACK IdVdGateStopCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	 if(event==EVENT_LEFT_CLICK_UP)
	 {
		 SetDrainDisp(panel, UNFOCUS);
		 SetGateDisp(panel, FOCUS);
	 }
	return 0;
}

int CVICALLBACK IdVdGateStepCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	 if(event==EVENT_LEFT_CLICK_UP)
	 {
		 SetDrainDisp(panel, UNFOCUS);
		 SetGateDisp(panel, FOCUS);
	 }
	return 0;
}

int CVICALLBACK IdVdDrainStartCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	 if(event==EVENT_LEFT_CLICK_UP)
	 {
		 SetDrainDisp(panel, FOCUS);
		 SetGateDisp(panel, UNFOCUS);
	 }
	return 0;
}

int CVICALLBACK IdVdDrainStopCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	 if(event==EVENT_LEFT_CLICK_UP)
	 {
		 SetDrainDisp(panel, FOCUS);
		 SetGateDisp(panel, UNFOCUS);
	 }
	return 0;
}

int CVICALLBACK IdVdDrainStepCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	 if(event==EVENT_LEFT_CLICK_UP)
	 {
		 SetDrainDisp(panel, FOCUS);
		 SetGateDisp(panel, UNFOCUS);
	 }
	return 0;
}


int CVICALLBACK IdVdDrainPicCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
 if(event==EVENT_LEFT_CLICK_UP)
	 {
		 SetDrainDisp(panel, FOCUS);
		 SetGateDisp(panel, UNFOCUS);
	 }
	return 0;
}

int CVICALLBACK IdVdGatePicCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK_UP)
	 {
		 SetDrainDisp(panel, UNFOCUS);
		 SetGateDisp(panel, FOCUS);
	 }
	return 0;
}


