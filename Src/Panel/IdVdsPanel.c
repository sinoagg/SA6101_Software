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
#include "ExpListPanel.h"

#define val_gray 0xA9A9A9L
#define   val_pres_blue  0xA0B4DCL   // 点击激活蓝色   
//==============================================================================
// Constants
ExpPanelTypeDef IdVdExpPanel={0, IDVDS_CFG_VD_START, IDVDS_CFG_VD_STOP, IDVDS_CFG_VD_STEP, IDVDS_CFG_VD_START, IDVDS_CFG_VD_STOP, IDVDS_CFG_VD_STEP};
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
int CVICALLBACK VDGateCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	   case EVENT_LEFT_CLICK_UP:
	      DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture 点击Gate时，其他为灰色状态 
		  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor together with picture
		  
		  DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg.ico"); 
		  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);
		  break;
	}
	return 0;
}

int CVICALLBACK VDDrainCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	   case EVENT_LEFT_CLICK_UP:
	      DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico"); 
		  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);
		  
		  DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
		  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor together with picture
		  break;
	}
	return 0;
}





int CVICALLBACK VdmodeCallbzck (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{	   
	
	
	 switch(event){
		 case EVENT_LEFT_CLICK_UP:
			      DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor together with picture
				  DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);
			 	  
			 break;
		 }  
		     int RingValue;
	              GetCtrlVal(panel,IDVDS_CFG_VDGATE,&RingValue);
			 if(event == EVENT_VAL_CHANGED ){
			 
				  if(RingValue==1){
		        	DisplayImageFile (panel, IDVDS_CFG_PIC_IDVD_GATE, "Resource\\V_Step.ico");
			
				  } else if(RingValue==2){
				    DisplayImageFile (panel, IDVDS_CFG_PIC_IDVD_GATE, "Resource\\V_Bias.ico");
					
				  } 
			 }
		
	

	return 0;
}


int CVICALLBACK StartCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	 if(event==EVENT_LEFT_CLICK_UP){
		       DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
				  
				  
				  DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);
		 }
	return 0;
}



int CVICALLBACK StepCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK_UP){
		        DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
				  
				  
				  DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);
		 }
	return 0;
}

int CVICALLBACK VdStopCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
		       if(event==EVENT_LEFT_CLICK_UP){
		        DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
				 SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
				  
				  
				  DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);
		 }
	return 0;
}

int CVICALLBACK ModeCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{				 if(event==EVENT_LEFT_CLICK_UP){ 
	              DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);
				  
				  DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor
}
				  return 0;
}

int CVICALLBACK VdSartCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{				   if(event==EVENT_LEFT_CLICK_UP){ 
	               DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);
				  
				  DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor
}
	return 0;
}

int CVICALLBACK VdStepCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{				if(event==EVENT_LEFT_CLICK_UP){ 
                 DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);
				  
				  DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor
	
}
				  return 0;
}

int CVICALLBACK VdStCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{			   if(event==EVENT_LEFT_CLICK_UP){ 
   				  DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);
				  
				  DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor
}
				  return 0;
}
