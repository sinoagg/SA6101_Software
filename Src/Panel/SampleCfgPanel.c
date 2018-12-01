#include "Sample Configuration.h"
#include <userint.h>
//==============================================================================
//
// Title:		SampleCfgPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/10 at 20:38:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "SampleCfgPanel.h"
#include "LoadPanel.h"
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


#define CUSTOMIZE 0		   //自定义
#define HIGHEST_SPEED 1	   //最高档
#define HIGH_SPEED 2	   //高档
#define MEDIUM_SPEED 3	   //中速档
#define LOW_SPEED 4		   //低速挡
#define LOWEST_SPEED 5	   //最低速
//==============================================================================
// Global functions
int CVICALLBACK AdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hAdvanceSamplePanel, 105, 1600);
			//SetPanelSize(hAdvanceSamplePanel, 449, 300);
			DisplayPanel(hAdvanceSamplePanel);	
		
			break;
	}
	return 0;
}

int CVICALLBACK BasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(hBasicSamplePanel, 105, 1600);
				//SetPanelSize(hBasicSamplePanel, 449, 300);
				DisplayPanel(hBasicSamplePanel);
			break;
	}
	return 0;
}


int CVICALLBACK RampleRateCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
    
	switch (event)
	{
		case  EVENT_VAL_CHANGED:                            
			int sampleRate;  
			GetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, ATTR_CTRL_VAL,&sampleRate); 
			if(sampleRate == HIGHEST_SPEED)
			{
				SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE, ATTR_CTRL_VAL,2000 );
				SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER, ATTR_CTRL_VAL,80 );  
				SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE, ATTR_CTRL_MODE, VAL_INDICATOR);
				SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER, ATTR_CTRL_MODE, VAL_INDICATOR);  
			}else if(sampleRate == HIGH_SPEED)
			{
				SetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE,2000);
			    SetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER,200); 
				SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE, ATTR_CTRL_MODE, VAL_INDICATOR);
			   SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER, ATTR_CTRL_MODE, VAL_INDICATOR);  
			}
			else if(sampleRate == MEDIUM_SPEED) 
			{
				SetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE,2000);
			    SetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER,400); 
				SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE, ATTR_CTRL_MODE, VAL_INDICATOR);
			   SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER, ATTR_CTRL_MODE, VAL_INDICATOR);  
	
			}
			else if(sampleRate == LOW_SPEED)
			{
				SetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE,2000);
			    SetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER,1000);
				SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE, ATTR_CTRL_MODE, VAL_INDICATOR);
			   SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER, ATTR_CTRL_MODE, VAL_INDICATOR);  
			} 
			else if(sampleRate == LOWEST_SPEED)
			{
				 SetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE,2000);
			     SetCtrlVal(hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER,2000); 
				 SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE, ATTR_CTRL_MODE, VAL_INDICATOR);
			   SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER, ATTR_CTRL_MODE, VAL_INDICATOR);  
			}else if( sampleRate == CUSTOMIZE)
			{
			   SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLERATE, ATTR_CTRL_MODE, VAL_HOT);
			   SetCtrlAttribute (hAdvanceSamplePanel,SAMPLE_ADV_SAMPLENUMBER, ATTR_CTRL_MODE, VAL_HOT);   
			}
			break;
	}
	return 0;
}

int CVICALLBACK RunTimeCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	 unsigned int runTime;
	 GetCtrlAttribute (panel,control,ATTR_CTRL_VAL,&runTime );
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			if(runTime>65535)
			{
				MessagePopup ("Tips", "The maximum value is 65535");    
				SetCtrlAttribute(panel,control,ATTR_CTRL_VAL,65535);  
			}
			break;
	}
	return 0;
}
