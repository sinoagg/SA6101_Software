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
int controlTime=0; 
float envtTime=0;
float ohm;
float rxIdmeasured;
int CVICALLBACK TimerCallback (int panel, int control, int event,								//定时去查询
								void *callbackData, int eventData1, int eventData2)
{   
	ohm = (TestPara.VdStart*0.001/RxData.rxIdmeasured.num_float);     
	reTime = RxData.realTime*0.001;
	if(log==1)   //log or Linear
		rxIdmeasured=log10(RxData.rxIdmeasured.num_float);
	else
		rxIdmeasured = RxData.rxIdmeasured.num_float; 
	SetCtrlVal(hResultDispPanel, RESULTDISP_IDS,rxIdmeasured);  
	  
	switch (event)
	{
		case EVENT_TIMER_TICK:
				if(measure_Uart_Flag == 1)											//串口接收时要屏蔽数据查询
				{
					ProtocolQuery(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);
					if(measUartRxBuf[0]!=0x01)
					{
						FlushInQ(measureComPort);	   										//Clear input and output buffer,在测试开始之前还应该清楚一次
					}
					else
					{
						if(measUartRxBuf[1]!=0x03)PlotCurve1(&Graph1, hGraphPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex,rxIdmeasured,RxData.rxStopSign,ohm);
				        if(measUartRxBuf[1]!=0x03)SetGraphX_Axis(hGraphPanel,GRAPHDISP_GRAPH1,&Graph1,reTime); 	
					}
	}
	
			 if((TestPara.testMode==SWEEP_DRAIN_VOL)||(TestPara.testMode==SWEEP_GATE_VOL)||(TestPara.testMode==SWEEP_IV))
			 {
				if(control_Uart_Flag == 1)
				{
					 Read_CGS_Value(controlComPort);
				}
			 }
			break;
	}

	return 0;
}

 int CVICALLBACK EvtTimerCalback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
 {
	 switch (event)
	 {
		 case EVENT_TIMER_TICK:
			if(Graph1.pCurveArray->numOfPlotDots>0)
		   	  {
				if(control_Uart_Flag == 1)
				{
					 Read_CGS_Value(controlComPort);
					 envtTime++;
				}
			  }
			 break;
	 }
	 return 0;
 }
