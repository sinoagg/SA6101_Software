//==============================================================================
//
// Title:		Protocol.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/9 at 9:58:35 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "Protocol.h"
#include "IdVdsPanel.h"
#include "IdVgsPanel.h"
#include "SampleCfgPanel.h"
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
extern IdVdCfg_TypeDef IdVdCfg; 
extern IdVgCfg_TypeDef IdVgCfg; 
extern SampleCfg_TypeDef SampleCfg;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
void ProtocolCfg(unsigned char devAddr, unsigned char expType, unsigned char* pUART_TxBuf)	//Make config info to UART Tx Buffer
{
	unsigned char i, xorcheck=0;
	*pUART_TxBuf=devAddr;
	*(pUART_TxBuf+1)=0x11;
	*(pUART_TxBuf+2)=expType;
	switch(expType)
	{
		case 0:
			*(pUART_TxBuf+4)=(unsigned char)(IdVdCfg.cfgVdstart)>>8;
			*(pUART_TxBuf+5)=(unsigned char)(IdVdCfg.cfgVdstart&0xFF);
			*(pUART_TxBuf+6)=(unsigned char)(IdVdCfg.cfgVdstop)>>8;
			*(pUART_TxBuf+7)=(unsigned char)(IdVdCfg.cfgVdstop&0xFF);
			*(pUART_TxBuf+8)=(unsigned char)(IdVdCfg.cfgVdstep)>>8;
			*(pUART_TxBuf+9)=(unsigned char)(IdVdCfg.cfgVdstep&0xFF);
			*(pUART_TxBuf+10)=(unsigned char)(IdVdCfg.cfgVgstart)>>8;
			*(pUART_TxBuf+11)=(unsigned char)(IdVdCfg.cfgVgstart&0xFF);
			*(pUART_TxBuf+12)=(unsigned char)(IdVdCfg.cfgVgstop)>>8;
			*(pUART_TxBuf+13)=(unsigned char)(IdVdCfg.cfgVgstop&0xFF);
			*(pUART_TxBuf+14)=(unsigned char)(IdVdCfg.cfgVgstep)>>8;
			*(pUART_TxBuf+15)=(unsigned char)(IdVdCfg.cfgVgstep&0xFF);
			break;
		case 1:
			*(pUART_TxBuf+4)=(unsigned char)(IdVgCfg.cfgVdstart)>>8;
			*(pUART_TxBuf+5)=(unsigned char)(IdVgCfg.cfgVdstart&0xFF);
			*(pUART_TxBuf+6)=(unsigned char)(IdVgCfg.cfgVdstop)>>8;
			*(pUART_TxBuf+7)=(unsigned char)(IdVgCfg.cfgVdstop&0xFF);
			*(pUART_TxBuf+8)=(unsigned char)(IdVgCfg.cfgVdstep)>>8;
			*(pUART_TxBuf+9)=(unsigned char)(IdVgCfg.cfgVdstep&0xFF);
			*(pUART_TxBuf+10)=(unsigned char)(IdVgCfg.cfgVgstart)>>8;
			*(pUART_TxBuf+11)=(unsigned char)(IdVgCfg.cfgVgstart&0xFF);
			*(pUART_TxBuf+12)=(unsigned char)(IdVgCfg.cfgVgstop)>>8;
			*(pUART_TxBuf+13)=(unsigned char)(IdVgCfg.cfgVgstop&0xFF);
			*(pUART_TxBuf+14)=(unsigned char)(IdVgCfg.cfgVgstep)>>8;
			*(pUART_TxBuf+15)=(unsigned char)(IdVgCfg.cfgVgstep&0xFF);
			break;
		case 2:
			//TODO
			break; 
		case 3:
			//TODO
			break;
		default:
			break;
	}
	*(pUART_TxBuf+16)=(unsigned char)(SampleCfg.cfgQuiteTime)>>8;
	*(pUART_TxBuf+17)=(unsigned char)(SampleCfg.cfgQuiteTime&0xFF);
	*(pUART_TxBuf+18)=(unsigned char)(SampleCfg.cfgTimeInterval)>>8;
	*(pUART_TxBuf+19)=(unsigned char)(SampleCfg.cfgTimeInterval&0xFF);
	*(pUART_TxBuf+20)=(unsigned char)(SampleCfg.cfgRunTime)>>8;
	*(pUART_TxBuf+21)=(unsigned char)(SampleCfg.cfgRunTime&0xFF);
	*(pUART_TxBuf+22)=(unsigned char)(SampleCfg.cfgSampleRate)>>8;
	*(pUART_TxBuf+23)=(unsigned char)(SampleCfg.cfgSampleRate&0xFF);
	*(pUART_TxBuf+24)=(unsigned char)(SampleCfg.cfgSampleNum)>>8;
	*(pUART_TxBuf+25)=(unsigned char)(SampleCfg.cfgSampleNum&0xFF);
	*(pUART_TxBuf+26)=(unsigned char)(SampleCfg.cfgRangeSetting&0xFF);  
	
	for(i=0;i<27;i++)
		xorcheck^=*(pUART_TxBuf+i);	
	
	*(pUART_TxBuf+27)=xorcheck;

}

RxDataTypeDef* ProtocolGetData(unsigned char* pUART_RxBuf)	//Get data from UART Rx Buffer
{
	static RxDataTypeDef RxData;
	RxData.rxDevAddr=*pUART_RxBuf;
	RxData.rxStopSign=*(pUART_RxBuf+1);
	RxData.rxVdtest=((int)*(pUART_RxBuf+2))|*(pUART_RxBuf+3);
	RxData.rxVgtest=((int)*(pUART_RxBuf+3))|*(pUART_RxBuf+4);
	
	return &RxData;
}



























