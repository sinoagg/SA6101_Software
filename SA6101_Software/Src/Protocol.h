//==============================================================================
//
// Title:		Protocol.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/9 at 9:58:35 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Protocol_H__
#define __Protocol_H__

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
typedef struct
{
	unsigned char rxDevAddr;									//received Device Address
	unsigned char rxStopSign;									//received Stop Sign 0x00 nonstop 0x01 curve stop 0x02 test stop
	int rxVdtest;									//voltage drain undertest
	int rxVgtest;									//voltage gate undertest
	int rxIdmeasured;								//Id measured
	float rxVdmeasured;								//Vd measured
	float rxVgmeasured;								//Vg measured
}RxDataTypeDef;
//==============================================================================
// External variables

//==============================================================================
// Global functions

void ProtocolCfg(unsigned char devAddr, unsigned char expType, unsigned char* pUART_TxBuf);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Protocol_H__ */
