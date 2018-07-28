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
#include "IdVdsPanel.h"
#include "Id-Vds Configuration.h"
#include "Id-Vgs Configuration.h"
#include "I-T.h"
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

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?


int CVICALLBACK TreeCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
	int activeIndex;
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			GetActiveTreeItem (panel, control, &activeIndex);//获得当前点击项目值		   
			if(activeIndex==1){

				//加载I-T
				SetPanelPos(iTPanel, 105, 305);
				SetPanelSize(iTPanel, 900, 1293);
				DisplayPanel(iTPanel);
					
					}
			else if(activeIndex==2){	 	
				//加载R-T
				SetPanelPos(rTPanel, 105, 305);
				SetPanelSize(rTPanel, 900, 1293);
				DisplayPanel(rTPanel);
					}
			else if(activeIndex==4 ){
				// 加载Id_Vds Configuration
				SetPanelPos(IdVdPanel.panelHandle, 105, 305);
				SetPanelSize(IdVdPanel.panelHandle, 900, 1293);
				DisplayPanel(IdVdPanel.panelHandle);
					
					}
			else if(activeIndex==5){
				//  加载Id_Vgs Configuration
				SetPanelPos(IdVgPanel, 105, 305);
				SetPanelSize(IdVgPanel, 900, 1293);
				DisplayPanel(IdVgPanel);
					}
			
				else {
					//
					
					}
			break;
	}  
	return 0;
}
