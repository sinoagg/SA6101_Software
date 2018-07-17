#include <userint.h>
#include "Experiment List.h"

//==============================================================================
//
// Title:		ExperimentList.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/11 at 9:55:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "ExpListPanel.h"
#include "Id-Vds Configuration.h"
#include "Id-Vgs Configuration.h" 

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

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int CVICALLBACK ExpListCallBack (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	
	int ExpSelVal;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, control, &ExpSelVal);
			if(ExpSelVal==1)
			{
			
				/*SetPanelPos(IdVdPanel, 300, 200);
				SetPanelSize(IdVdPanel, 600, 800);
				DisplayPanel(IdVdPanel);*/
				
				SetPanelPos(IdVdPanel, 105, 305);
				SetPanelSize(IdVdPanel, 900, 1293);
				DisplayPanel(IdVdPanel);
			}
			else if(ExpSelVal==2)
			{/*
				SetPanelPos(IdVgPanel, 300, 200);
				SetPanelSize(IdVgPanel, 600, 800);
				DisplayPanel(IdVgPanel);*/
				
				SetPanelPos(IdVgPanel, 105, 305);
				SetPanelSize(IdVgPanel, 900, 1293);
				DisplayPanel(IdVgPanel);
			}
			else if(ExpSelVal==3)
			{
				//TODO  
			}
			else
			{
				//TODO  
			}
			break;
	}
	
	
	
	return 0;
}

//ListBox2   2-terminnal   
int CVICALLBACK ListBoxCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int ListIndex;
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, control, &ListIndex); 
			if(ListIndex==1){

					//º”‘ÿI-T
				SetPanelPos(IdVdPanel, 105, 305);
				SetPanelSize(IdVdPanel, 900, 1293);
				DisplayPanel(IdVdPanel);
					
					}
			else if(ListIndex==2){	 	
				
					//º”‘ÿR-T
				SetPanelPos(IdVgPanel, 105, 305);
				SetPanelSize(IdVgPanel, 900, 1293);
				DisplayPanel(IdVgPanel);
					}
			else{
				//
				
					}
			break;
	}
	return 0;
}
