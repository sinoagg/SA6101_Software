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

//==============================================================================
// Constants
#define MEASURE_DEV_ADDR 0x01
#define MEASURE_UART_RX_LEN 20
		
#define TXTCOLOR 0x3399FF
#define ANNOTATIONCOLOR 0x508EF4
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
extern int curveIndex ;
extern unsigned char measure_Uart_Flag; 					//��ѧ�������ڽ���ʱҪ�������ݲ�ѯ 
extern unsigned char control_Uart_Flag; 					//�����������ڽ���ʱҪ�������ݲ�ѯ
//==============================================================================
// Global functions

void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData);
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);

static int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen,void (*pFunc)(int, int, void*));
void DeviceQuery();
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __main_H__ */