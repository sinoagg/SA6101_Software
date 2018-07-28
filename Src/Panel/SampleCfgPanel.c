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
<<<<<<< HEAD
=======
#include "LoadPanel.h"
>>>>>>> a0ab2d7488dc2715558bcf7b33d9ee1aa747214e
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
int samplePanelHandle;
//==============================================================================
// Global functions


<<<<<<< HEAD
=======
int CVICALLBACK AdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(sampleBasicPanel, 105, 1600);
			SetPanelSize(sampleBasicPanel, 449, 300);
			DisplayPanel(sampleBasicPanel);
			break;
	}
	return 0;
}

int CVICALLBACK BasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(samplePanelHandle, 105, 1600);
				SetPanelSize(samplePanelHandle, 449, 300);
				DisplayPanel(samplePanelHandle);
			break;
	}
	return 0;
}
>>>>>>> a0ab2d7488dc2715558bcf7b33d9ee1aa747214e
