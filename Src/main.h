//==============================================================================
//
// Title:		main.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/23 at 13:28:04 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __main_H__
#define __main_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include"Protocol.h"

//==============================================================================
// Constants
#define MEASURE_DEV_ADDR 0x01
#define MEASURE_UART_RX_LEN 24
		
#define TXTCOLOR 0x3399FF
#define ANNOTATIONCOLOR 0x508EF4
		
#define ONLYGATE  0x04
#define NOLYDRAIN 0x08
#define BOTH	  0x0c
#define BOTHNONE  0x00
//==============================================================================
// Types

//==============================================================================
// External variables
extern unsigned char measureComPort;				//Serial Com Number
extern unsigned char controlComPort;
extern unsigned char measUartTxBuf[];
extern unsigned char measUartRxBuf[];
extern unsigned char curveComplete;
extern  int rows; 
extern int graphrows;
extern float reTime;
extern int controlTime;
extern int plots;
extern unsigned char measure_Uart_Flag; 					//电学测量串口接收时要屏蔽数据查询 
extern unsigned char control_Uart_Flag; 					//环境参数串口接收时要屏蔽数据查询
extern char  IDAddrress[30];         //设备ID号 
extern RxDataTypeDef RxData;
extern int TimerID;
extern int EvtTimerId;
extern int threadFlag;			 //线程标志位 
extern int CountFlag;			 //标志在停止时不在进入多曲线线程
extern int CurveNums;   		 //曲线条数超出4时开始随机变化颜
//==============================================================================
// Global functions

void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData);
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
  
static int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen,void (*pFunc)(int, int, void*));

void RxDataToGraph(RxDataTypeDef *pRxData,float rxIdmeasured,float ohm);
void RxDataToTable(RxDataTypeDef *pRxData);

void DeviceQuery();
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __main_H__ */
