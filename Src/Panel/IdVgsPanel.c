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
#define   COLOR_BLUE  0xA0B4DCL   // 点击激活蓝色
#define  COLOR_GREY 0xA9A9A9L	   //未点击灰色
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
IdVgCfg_TypeDef IdVgCfg; 
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int GetIdVgCfg (int panelHandle)
{
	int temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_START, &temp)<0)
		return -1;
	IdVgCfg.cfgVdstart=temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_STOP, &temp)<0)
		return -1;
	IdVgCfg.cfgVdstop=temp;
	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_STEP, &temp)<0)
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


static  void SetDrainDisp(int panel, char focus){
	if(focus==FOCUS){
		          DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, COLOR_BLUE);// change text bgcolor
	}else{
				  DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, COLOR_GREY);// change text bgcolor
	}
	
}

static  void SetGateDisp(int panel, char focus){
	if(focus==FOCUS){
		          DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, COLOR_BLUE);// change text bgcolor
	}else{
				  DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, COLOR_GREY);// change text bgcolor
	}
	
}
int CVICALLBACK VgDrainCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	//  DRAIN

		   switch(event){
		   case EVENT_LEFT_CLICK_UP:
			   SetGateDisp(panel,UNFOCUS);
			   SetDrainDisp(panel,FOCUS);
			
			   break;
	}
	   
	  
	return 0;
}


int CVICALLBACK VgDrainStartCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK_UP){  
	   
		 SetDrainDisp(panel, FOCUS);
		 SetGateDisp(panel, UNFOCUS);
	
   }
	return 0;
}

int CVICALLBACK VgDrainStopCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK_UP){  
	   
		 SetDrainDisp(panel, FOCUS);
		 SetGateDisp(panel, UNFOCUS);
	
   }
	return 0;
}

int CVICALLBACK VgDrainStepCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
       if(event==EVENT_LEFT_CLICK_UP){  
	   
		 SetDrainDisp(panel, FOCUS);
		 SetGateDisp(panel, UNFOCUS);
	
   }
	return 0;
}

int CVICALLBACK VgGateModeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK_UP){  
	   
			 SetDrainDisp(panel, UNFOCUS);
			 SetGateDisp(panel, FOCUS);
	
	   }
	return 0;
}

int CVICALLBACK VgGateSartCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{

	if(event==EVENT_LEFT_CLICK_UP){  
	   
		 SetDrainDisp(panel, UNFOCUS);
		 SetGateDisp(panel, FOCUS);
	
   }
	 /*  DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, COLOR_BLUE);// change text bgcolor
	   DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, COLOR_GREY);// change text bgcolor*/

	return 0;
}

int CVICALLBACK VgGateStopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
		if(event==EVENT_LEFT_CLICK_UP){  
	   
		 SetDrainDisp(panel, UNFOCUS);
		 SetGateDisp(panel, FOCUS);
	
   }
	return 0;
}

int CVICALLBACK VgGateStepCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	
	if(event==EVENT_LEFT_CLICK_UP){  
	   
		 SetDrainDisp(panel, UNFOCUS);
		 SetGateDisp(panel, FOCUS);
	
   }
	return 0;
}

int CVICALLBACK VgDrainModeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{

	switch(event){
	case EVENT_LEFT_CLICK_UP:
			SetDrainDisp(panel, FOCUS);
		  	SetGateDisp(panel, UNFOCUS);
			break;

	
	         
	case EVENT_VAL_CHANGED:
		    int RingValue;
	        GetCtrlVal(panel,IDVGS_CFG_VGDRING,&RingValue);
			if(RingValue==1){
		        DisplayImageFile (panel, IDVGS_CFG_PIC_IDVD_DRAIN, "Resource\\V_Step.ico");
			}else if(RingValue==2){
				DisplayImageFile (panel, IDVGS_CFG_PIC_IDVD_DRAIN, "Resource\\V_Bias.ico");
			} 
			break;
}
 
//>>>>>>> 8d2b85158ba46c70afb115b45e9d7b754e79c8f5
	return 0;
}

int CVICALLBACK VgGateDecoCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:  
			SetGateDisp(panel,FOCUS);  
	        SetDrainDisp(panel,UNFOCUS);
			break;
	}

	
	return 0;
}
