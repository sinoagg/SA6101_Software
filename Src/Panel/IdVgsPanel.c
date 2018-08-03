#include "Id-Vds Configuration.h"
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
#define COLOR_BLUE 0xA0B4DCL   // 点击激活蓝色
#define COLOR_GREY 0xA9A9A9L	   //未点击灰色
#define FOCUS	0
#define UNFOCUS 1
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
ExpPanelTypeDef IdVgPanel={0, IDVGS_CFG_VG_START, IDVGS_CFG_VG_STOP, IDVGS_CFG_VG_STEP, IDVGS_CFG_VD_START, IDVGS_CFG_VD_STOP, IDVGS_CFG_VD_STEP, IDVDS_CFG_DRAINMODE, IDVGS_CFG_GATEMODE};  
//==============================================================================
// Global functions
static  void SetDrainDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico");// change picture
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, COLOR_BLUE);// change text bgcolor
	}
	else
	{
		DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg.ico");// change picture
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, COLOR_GREY);// change text bgcolor
	}
}

static  void SetGateDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, COLOR_BLUE);// change text bgcolor
	}
	else
	{
		DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, COLOR_GREY);// change text bgcolor
	}
}

int CVICALLBACK IdVgGateDecoCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:  
			SetGateDisp(panel,FOCUS);  
		    SetDrainDisp(panel,UNFOCUS);
			break;
	}
	return 0;
}

int CVICALLBACK IdVgDrainDecoCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
		switch(event)
		{
		  case EVENT_LEFT_CLICK_UP:
	  	 	  SetGateDisp(panel,UNFOCUS);
	  	 	  SetDrainDisp(panel,FOCUS);
	  	      break;
     	}
	return 0;
}

int CVICALLBACK IdVgGateModeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
		if(event==EVENT_LEFT_CLICK_UP){  
			SetDrainDisp(panel, UNFOCUS);
			SetGateDisp(panel, FOCUS);
		   }
	return 0;
}

int CVICALLBACK IdVgDrainModeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{

	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetDrainDisp(panel, FOCUS);
			SetGateDisp(panel, UNFOCUS);
			break;
		case EVENT_VAL_CHANGED:
		    int valu;
		    GetCtrlVal(panel,IDVGS_CFG_DRAINMODE,&valu);
			if(valu==1)
			{
		        DisplayImageFile (panel, IDVGS_CFG_PIC_IDVD_DRAIN, "Resource\\V_Step.ico");
				SetCtrlAttribute(panel, IDVGS_CFG_VD_STOP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVGS_CFG_TXT_STOP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVGS_CFG_MV_STOP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVGS_CFG_VD_STEP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVGS_CFG_TXT_STEP,ATTR_VISIBLE,1);
				SetCtrlAttribute(panel, IDVGS_CFG_MV_STEP,ATTR_VISIBLE,1);
			}
			else if(valu==2)
			{
				DisplayImageFile (panel, IDVGS_CFG_PIC_IDVD_DRAIN, "Resource\\V_Bias.ico");
				SetCtrlAttribute(panel, IDVGS_CFG_VD_STOP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVGS_CFG_TXT_STOP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVGS_CFG_MV_STOP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVGS_CFG_VD_STEP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVGS_CFG_TXT_STEP,ATTR_VISIBLE,0);
				SetCtrlAttribute(panel, IDVGS_CFG_MV_STEP,ATTR_VISIBLE,0);
			
			
			} 
			break;
		}
	return 0;
}

int CVICALLBACK IdVgDrainStartCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
		if(event==EVENT_LEFT_CLICK_UP)
		{  
			SetDrainDisp(panel, FOCUS);
			SetGateDisp(panel, UNFOCUS);
	    }
	return 0;
}

int CVICALLBACK IdVgDrainStopCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
		if(event==EVENT_LEFT_CLICK_UP)
		{  
			SetDrainDisp(panel, FOCUS);
			SetGateDisp(panel, UNFOCUS);
	    }
	return 0;
}

int CVICALLBACK IdVgDrainStepCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
		if(event==EVENT_LEFT_CLICK_UP)
		{  
			SetDrainDisp(panel, FOCUS);
			SetGateDisp(panel, UNFOCUS);
	    }
	return 0;
}

int CVICALLBACK IdVgGateStartCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
		if(event==EVENT_LEFT_CLICK_UP)
		{  
			SetDrainDisp(panel, UNFOCUS);
			SetGateDisp(panel, FOCUS);
	    }
	return 0;
}

int CVICALLBACK IdVgGateStopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
		if(event==EVENT_LEFT_CLICK_UP)
		{  
			SetDrainDisp(panel, UNFOCUS);
			SetGateDisp(panel, FOCUS);
	    }
	return 0;
}

int CVICALLBACK IdVgGateStepCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
		if(event==EVENT_LEFT_CLICK_UP)
		{  
			SetDrainDisp(panel, UNFOCUS);
			SetGateDisp(panel, FOCUS);
	     }
	return 0;
}

 int CVICALLBACK IdVgGatePicCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK_UP)
		{  
			SetDrainDisp(panel, UNFOCUS);
			SetGateDisp(panel, FOCUS);
	    }
	return 0;
}

int CVICALLBACK IdVgDrainPicCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK_UP)
		{  
			  SetGateDisp(panel,UNFOCUS);
	  	 	  SetDrainDisp(panel,FOCUS);
	    }
	return 0;
}
