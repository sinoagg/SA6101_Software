//==============================================================================
//
// Title:		DataProcess.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/11/27 at 14:53:15 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __DataProcess_H__
#define __DataProcess_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables
 extern Rx_CGS_DataTypeDef Rx_CGS_Data;  
//==============================================================================
// Global functions
void Rx_CGS_DataToTable(Rx_CGS_DataTypeDef* Rx_CGS_Data,float reTime);   

int CheckOpenCom(unsigned char* measureComPort,unsigned char* controlComPort,unsigned char* measure_Uart_Flag,unsigned char* control_Uart_Flag)  ;
int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFunc)(int, int, void*));

void CVICALLBACK CtrlComCallback(int portNumber, int eventMask, void * callbackData); 
void CVICALLBACK MeasureComCallback(int portNumber, int eventMask, void* callbackData);
void CheckCloseCom(int SA6101_UART_Status,unsigned char measureComPort,unsigned char controlComPort) ;
void AddGraphAnnotations(RxDataTypeDef *pRxData,float rxIdmeasured) ;
void TestStopActions(RxDataTypeDef *pRxData,int portNumber,float rxIdmeasured);
void DeviceQuery();
/*
void  GetData(Rx_CGS_DataTypeDef* Rx_CGS_Data);    */ 
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __DataProcess_H__ */
