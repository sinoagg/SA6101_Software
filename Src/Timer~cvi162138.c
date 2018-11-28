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
int CVICALLBACK TimerCallback (int panel, int control, int event,								//定时去查询
								void *callbackData, int eventData1, int eventData2)
{
		switch (event)
	{
		case EVENT_TIMER_TICK:

			
			if(measure_Uart_Flag == 1)											//串口接收时要屏蔽数据查询

			{
				ProtocolQuery(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);
				Delay(0.020);
			}
			
			if(control_Uart_Flag == 1)
			{
				Read_CGS_Value(controlComPort);
				Delay(0.020);
			}
			break;
	}

	return 0;
}


