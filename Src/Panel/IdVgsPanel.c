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
#define   val_pres_blue  0xA0B4DCL   // ���������ɫ
#define  val_gray 0xA9A9A9L	   //δ�����ɫ
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
int CVICALLBACK GateCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	//  Gate

		   switch(event){
		   case EVENT_LEFT_CLICK_UP:
			      //���Gateʱ������Ϊ��ɫ״̬
<<<<<<< HEAD
			      DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
				  
				  
				/*  DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg.ico"); 
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_color);
				  DisplayImageFile (panel, IDVGS_CFG_PIC_BULK, "Resource\\bg.ico");
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_BULK, ATTR_TEXT_BGCOLOR, val_color);
				  DisplayImageFile (panel, IDVGS_CFG_PIC_SOURCE, "Resource\\bg.ico"); 
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_SOURCE, ATTR_TEXT_BGCOLOR, val_color);*/
=======
			      DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
				  DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor
			
>>>>>>> c470c37cb1316d04d8132fad4521adc588b849fd
			   break;
	}
	   
	  
	return 0;
}


<<<<<<< HEAD
=======
int CVICALLBACK VGstartCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
if(event==EVENT_LEFT_CLICK_UP){

	              DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
				  DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor

	   
   }
	return 0;
}

int CVICALLBACK VGstopCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
if(event==EVENT_LEFT_CLICK_UP){


	    DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico");// change picture
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
	    DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor

	   
   }
	return 0;
}

int CVICALLBACK VGstepCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
if(event==EVENT_LEFT_CLICK_UP){

//=======
	DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico");// change picture
	SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
	DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
	SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor

	   
   }
	return 0;
}

int CVICALLBACK VgModeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK_UP){  

	  DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
	   DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor

   }
	return 0;
}

int CVICALLBACK VgSartCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{

	if(event==EVENT_LEFT_CLICK_UP){  

	   DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
	   DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor

   }
	return 0;
}

int CVICALLBACK VgStCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
	if(event==EVENT_LEFT_CLICK_UP){  

	   DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
	   DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor

	   							 
   }
	return 0;
}

int CVICALLBACK VgStepCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	
	if(event==EVENT_LEFT_CLICK_UP){  

	   DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
	   DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor

	   							 
   }
	return 0;
}

int CVICALLBACK VGmodeCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{

	switch(event){
		case  EVENT_LEFT_CLICK_UP:
	   			  DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg_pressed.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
				  DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg.ico");// change picture
				  SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor
			break;
	}
	
	         int RingValue;
	         GetCtrlVal(panel,IDVGS_CFG_RING_MODE,&RingValue);
			 if(event == EVENT_VAL_CHANGED ){
			 
				  if(RingValue==1){
		        		DisplayImageFile (panel, IDVGS_CFG_PIC_IDVD_DRAIN, "Resource\\V_Step.ico");
			
				  } else if(RingValue==2){
				    DisplayImageFile (panel, IDVGS_CFG_PIC_IDVD_DRAIN, "Resource\\V_Bias.ico");
					
				  } 
			 }
 
//>>>>>>> 8d2b85158ba46c70afb115b45e9d7b754e79c8f5
	return 0;
}

int CVICALLBACK VGDrainCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK_UP){  

	   DisplayImageFile (panel, IDVGS_CFG_PIC_GATE, "Resource\\bg_pressed.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, val_pres_blue);// change text bgcolor
	   DisplayImageFile (panel, IDVGS_CFG_PIC_DRAIN, "Resource\\bg.ico");// change picture
	   SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, val_gray);// change text bgcolor

   }
	
	return 0;
}
>>>>>>> c470c37cb1316d04d8132fad4521adc588b849fd
