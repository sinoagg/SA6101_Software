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
#include <rs232.h>
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
void ProtocolCfg(unsigned char comSelect, unsigned char devAddr, unsigned char expType, unsigned char* pUartTxBuf)	//Make config info to UART Tx Buffer
{
	unsigned char i, xorcheck=0;
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=0x11;
	*(pUartTxBuf+2)=expType;
	switch(expType)
	{
		case 0:
			*(pUartTxBuf+4)=(unsigned char)(IdVdCfg.cfgVdstart)>>8;
			*(pUartTxBuf+5)=(unsigned char)(IdVdCfg.cfgVdstart&0xFF);
			*(pUartTxBuf+6)=(unsigned char)(IdVdCfg.cfgVdstop)>>8;
			*(pUartTxBuf+7)=(unsigned char)(IdVdCfg.cfgVdstop&0xFF);
			*(pUartTxBuf+8)=(unsigned char)(IdVdCfg.cfgVdstep)>>8;
			*(pUartTxBuf+9)=(unsigned char)(IdVdCfg.cfgVdstep&0xFF);
			*(pUartTxBuf+10)=(unsigned char)(IdVdCfg.cfgVgstart)>>8;
			*(pUartTxBuf+11)=(unsigned char)(IdVdCfg.cfgVgstart&0xFF);
			*(pUartTxBuf+12)=(unsigned char)(IdVdCfg.cfgVgstop)>>8;
			*(pUartTxBuf+13)=(unsigned char)(IdVdCfg.cfgVgstop&0xFF);
			*(pUartTxBuf+14)=(unsigned char)(IdVdCfg.cfgVgstep)>>8;
			*(pUartTxBuf+15)=(unsigned char)(IdVdCfg.cfgVgstep&0xFF);
			break;
		case 1:
			*(pUartTxBuf+4)=(unsigned char)(IdVgCfg.cfgVdstart)>>8;
			*(pUartTxBuf+5)=(unsigned char)(IdVgCfg.cfgVdstart&0xFF);
			*(pUartTxBuf+6)=(unsigned char)(IdVgCfg.cfgVdstop)>>8;
			*(pUartTxBuf+7)=(unsigned char)(IdVgCfg.cfgVdstop&0xFF);
			*(pUartTxBuf+8)=(unsigned char)(IdVgCfg.cfgVdstep)>>8;
			*(pUartTxBuf+9)=(unsigned char)(IdVgCfg.cfgVdstep&0xFF);
			*(pUartTxBuf+10)=(unsigned char)(IdVgCfg.cfgVgstart)>>8;
			*(pUartTxBuf+11)=(unsigned char)(IdVgCfg.cfgVgstart&0xFF);
			*(pUartTxBuf+12)=(unsigned char)(IdVgCfg.cfgVgstop)>>8;
			*(pUartTxBuf+13)=(unsigned char)(IdVgCfg.cfgVgstop&0xFF);
			*(pUartTxBuf+14)=(unsigned char)(IdVgCfg.cfgVgstep)>>8;
			*(pUartTxBuf+15)=(unsigned char)(IdVgCfg.cfgVgstep&0xFF);
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
	*(pUartTxBuf+16)=(unsigned char)(SampleCfg.cfgQuiteTime)>>8;
	*(pUartTxBuf+17)=(unsigned char)(SampleCfg.cfgQuiteTime&0xFF);
	*(pUartTxBuf+18)=(unsigned char)(SampleCfg.cfgTimeInterval)>>8;
	*(pUartTxBuf+19)=(unsigned char)(SampleCfg.cfgTimeInterval&0xFF);
	*(pUartTxBuf+20)=(unsigned char)(SampleCfg.cfgRunTime)>>8;
	*(pUartTxBuf+21)=(unsigned char)(SampleCfg.cfgRunTime&0xFF);
	*(pUartTxBuf+22)=(unsigned char)(SampleCfg.cfgSampleRate)>>8;
	*(pUartTxBuf+23)=(unsigned char)(SampleCfg.cfgSampleRate&0xFF);
	*(pUartTxBuf+24)=(unsigned char)(SampleCfg.cfgSampleNum)>>8;
	*(pUartTxBuf+25)=(unsigned char)(SampleCfg.cfgSampleNum&0xFF);
	*(pUartTxBuf+26)=(unsigned char)(SampleCfg.cfgRangeSetting&0xFF);  
	
	for(i=0;i<27;i++)
		xorcheck^=*(pUartTxBuf+i);	
	
	*(pUartTxBuf+27)=xorcheck;
	
	ComWrt(comSelect, (const char*)pUartTxBuf, 28);

}

void ProtocolRun(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf)
{
	unsigned char i, xorcheck=0;
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=0x12;
	for(i=0;i<27;i++)
		xorcheck^=*(pUartTxBuf+i);	
	
	*(pUartTxBuf+27)=xorcheck;
	
	ComWrt(comSelect, (const char*)pUartTxBuf, 28);
}

void ProtocolStop(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf)
{
	unsigned char i, xorcheck=0;
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=0x13;
	for(i=0;i<27;i++)
		xorcheck^=*(pUartTxBuf+i);	
	
	*(pUartTxBuf+27)=xorcheck;
	
	ComWrt(comSelect, (const char*)pUartTxBuf, 28);
}

void ProtocolQuery(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf)
{
	unsigned char i, xorcheck=0;
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=0x14;
	for(i=0;i<27;i++)
		xorcheck^=*(pUartTxBuf+i);	
	
	*(pUartTxBuf+27)=xorcheck;
	
	ComWrt(comSelect, (const char*)pUartTxBuf, 28);
}

void ProtocolCalibrate(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf)
{
	unsigned char i, xorcheck=0;
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=0x15;
	for(i=0;i<27;i++)
		xorcheck^=*(pUartTxBuf+i);	
	
	*(pUartTxBuf+27)=xorcheck;
	
	ComWrt(comSelect, (const char*)pUartTxBuf, 28);
}

void ProtocolGetData(unsigned char* pUartRxBuf, RxDataTypeDef* pRxData)	//Get data from UART Rx Buffer
{
	pRxData->rxDevAddr=*pUartRxBuf;
	pRxData->rxStopSign=*(pUartRxBuf+1);
	pRxData->rxVdtest=((int)*(pUartRxBuf+2))|*(pUartRxBuf+3);
	pRxData->rxVgtest=((int)*(pUartRxBuf+4))|*(pUartRxBuf+5);
	pRxData->rxIdmeasured.num_uchar[0]=*(pUartRxBuf+6);
	pRxData->rxIdmeasured.num_uchar[1]=*(pUartRxBuf+7); 
	pRxData->rxIdmeasured.num_uchar[2]=*(pUartRxBuf+8); 
	pRxData->rxIdmeasured.num_uchar[3]=*(pUartRxBuf+9);
	pRxData->rxVdmeasured.num_uchar[0]=*(pUartRxBuf+10); 
	pRxData->rxVdmeasured.num_uchar[1]=*(pUartRxBuf+11);
	pRxData->rxVdmeasured.num_uchar[2]=*(pUartRxBuf+12);
	pRxData->rxVdmeasured.num_uchar[3]=*(pUartRxBuf+13);
	pRxData->rxVgmeasured.num_uchar[0]=*(pUartRxBuf+14); 
	pRxData->rxVgmeasured.num_uchar[1]=*(pUartRxBuf+15);
	pRxData->rxVgmeasured.num_uchar[2]=*(pUartRxBuf+16);
	pRxData->rxVgmeasured.num_uchar[3]=*(pUartRxBuf+17);
	pRxData->rangeSelect=*(pUartRxBuf+18);
}



























