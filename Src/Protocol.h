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
enum TestCmd
{
	CMD_START=0x11,
	CMD_PAUSE=0x12,
	CMD_STOP=0x13,
	CMD_CONTINUE=0x14
};		

typedef union										//float union
{
	unsigned char num_uchar[4]; 
	float num_float;
}Float_Union_Data;

enum TestMode
{
	CALIBRATION=0,
	SWEEP_DRAIN_VOL=1,
	SWEEP_GATE_VOL=2,
	NO_SWEEP_IT=3,
	NO_SWEEP_RT=4
};

typedef struct
{
	unsigned char devAddr;
	enum TestCmd testCmd;
	enum TestMode testMode;
	unsigned char outputConnection;
	int VdStart;									//voltage drain start
	int VdStop;									//voltage drain stop
	int VdStep;									//voltage drain step
	int VgStart;									//voltage gate start
	int VgStop;									//voltage gate stop
	int VgStep;									//voltage gate step
	unsigned int quietTime;
	unsigned int timeStep;
	unsigned int runTime;								//effective only under R-t and I-t mode
	unsigned int sampleRate;
	unsigned int sampleNumber;

	unsigned char rangeMode;
	unsigned char maxRange;
	unsigned char minRange;
}TestParaTypeDef;

typedef struct
{
	unsigned char rxDevAddr;						//received Device Address
	unsigned char rxStopSign;						//received Stop Sign 0x00 nonstop 0x01 curve stop 0x02 test stop
	int rxVdtest;									//voltage drain undertest
	int rxVgtest;									//voltage gate undertest
	Float_Union_Data rxIdmeasured;					//Id measured
	Float_Union_Data rxVdmeasured;					//Vd measured
	Float_Union_Data rxVgmeasured;					//Vg measured
	unsigned char rangeSelect;
}RxDataTypeDef;

//==============================================================================
// External variables

//==============================================================================
// Global functions

void ProtocolCfg(unsigned char comSelect, unsigned char devAddr, unsigned char expType, unsigned char* pUartTxBuf);
void ProtocolRun(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf);
void ProtocolStop(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf);  
void ProtocolQuery(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf);
void ProtocolCalibrate(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf);

void ProtocolGetData(unsigned char* pUartRxBuf, RxDataTypeDef* pRxData);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Protocol_H__ */
