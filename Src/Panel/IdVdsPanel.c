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

#define val_gray 0xA9A9A9L
#define   val_pres_blue  0xA0B4DCL   // 点击激活蓝色   
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
IdVdCfg_TypeDef IdVdCfg;
//==============================================================================
// Global functions

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
	
	
	
	//
	//if(GetCtrlVal(panelHandle, IDVDS_CFG_VG_START, &temp)<0)
	//	return -1;
	//IdVdCfg.cfgVgstart=temp;
	//if(GetCtrlVal(panelHandle, IDVDS_CFG_VG_STOP, &temp)<0)
	//	return -1;
	//IdVdCfg.cfgVgstop=temp;
	//if(GetCtrlVal(panelHandle, IDVDS_CFG_VG_STEP, &temp)<0)
	//	return -1;
	//IdVdCfg.cfgVgstep=temp;
	
		
	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_START, &temp)<0)
		return -1;
	IdVdCfg.cfgVgstart=temp;
	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_STOP, &temp)<0)
		return -1;
	IdVdCfg.cfgVgstop=temp;
	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_STEP, &temp)<0)
		return -1;
	IdVdCfg.cfgVgstep=temp;
	
	
	
	return 0;
}






int CVICALLBACK VDGateCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
		//  Gate

		   switch(event){
		   case EVENT_LEFT_CLICK_UP:
			      //点击Gate时，其他为灰色状态
			      DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
				  
				  
				  DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);
				  
				  
				  
 
			   break;
	}
	
	return 0;
}

int CVICALLBACK VDDrainCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
		  
	
		  //Drain
	switch(event){
		   case EVENT_LEFT_CLICK_UP:
			      DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);
				  
				  DisplayImageFile (panel, IDVDS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor
				  
				  
 
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
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
				  DisplayImageFile (panel, IDVDS_CFG_PIC_DRAIN, "Resource\\bg.ico"); 
				  SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);
			 	  
			 break;
		 }  
		     int RingValue;
	              GetCtrlVal(panel,IDVDS_CFG_VDGRING,&RingValue);
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
