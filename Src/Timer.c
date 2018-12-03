#include <rs232.h>
#include <userint.h>

//==============================================================================
//
// Title:		Timer.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:33:45 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "Timer.h"
#include "Graph.h"  `
#include "GraphDisp.h"
#include "Graph.h"
#include "File.h"
#include "Plot.h"
#include "Protocol.h"
#include "Timer.h"
#include "main.h"
#include "ExpListPanel.h"
#include "Result Menu.h"
#include "GraphDisp.h"
 #include "Experiment List.h"
#include "I-T.h"
#include "Id-Vds Configuration.h"
#include "Id-Vgs Configuration.h"
#include "MainPanel.h"
#include "R-T.h"
#include "Sample Configuration.h"
#include "Table.h"
#include "LoadPanel.h"
#include "Plot.h"
#include "LoadPanel.h"
#include "Cgs_mt.h"
#include"MainPanelCb.h"
#include"DataProcess.h"
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

int numTime=0;
float envtTime;   
float ohm;
float rxIdmeasured;
int controlTime=0;
int CVICALLBACK TimerCallback (int panel, int control, int event,								//��ʱȥ��ѯ
								void *callbackData, int eventData1, int eventData2)
{   
	switch (event)
	{
		case EVENT_TIMER_TICK:
		
		
				if(measure_Uart_Flag == 1)											//���ڽ���ʱҪ�������ݲ�ѯ
				{
					ProtocolQuery(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);
				}
				if(control_Uart_Flag == 1)                
				{
					Read_CGS_Value(controlComPort);
					SetGraph2_YAxis(GRAPHDISP_GRAPH2,&Graph2);   
					SetCtrlVal (hEnvResultPanel, ENVIRPANEL_TEMPERATURE, Rx_CGS_Data.heating_stage_temp);		//��̨�¶�   
					SetCtrlVal (hEnvResultPanel, ENVIRPANEL_HUMIDITY,  Rx_CGS_Data.humidity);					//��ʾʪ��     
					SetCtrlVal (hEnvResultPanel, ENVIRPANEL_PRESSURE, Rx_CGS_Data.pressure*0.001);		 		//��ʾѹǿ		  

				}
		
			break;
	}
	
	return 0;
}


