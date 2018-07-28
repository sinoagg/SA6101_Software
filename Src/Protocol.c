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

#include <userint.h>
#include "Protocol.h"
#include "IdVdsPanel.h"
#include "IdVgsPanel.h"
#include "SampleCfgPanel.h"
#include <rs232.h>
//==============================================================================
// Constants

//==============================================================================
// Types
enum MsgType
{
	MSG_TYPE_NULL=0,
	MSG_TYPE_SETTING=0x11,					
	MSG_TYPE_RUN=0x12,
	MSG_TYPE_STOP=0x13,
	MSG_TYPE_QUERY=0x14,
	MSG_TYPE_CALIBRATION=0x15,
	MSG_TYPE_REPORT_ID=0xFF
};
//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
TestParaTypeDef TestPara;
//==============================================================================
// Global functions
static void GetTestPara(ExpPanelTypeDef* pExpPanel, TestParaTypeDef* pTestPara)
{
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VdStartID, &(pTestPara->VdStart));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VdStopID, &(pTestPara->VdStop));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VdStepID, &(pTestPara->VdStep));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VgStartID, &(pTestPara->VgStart));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VgStopID, &(pTestPara->VgStop));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VgStepID, &(pTestPara->VgStep));

	GetCtrlVal(samplePanelHandle, SAMPLE_CFG_QUIETTIME, &(pTestPara->quietTime));   //所有采样配置都是兼容的
	GetCtrlVal(samplePanelHandle, SAMPLE_CFG_TIMESTEP, &(pTestPara->timeStep));
	GetCtrlVal(samplePanelHandle, SAMPLE_CFG_RUNTIME, &(pTestPara->runTime));
	GetCtrlVal(samplePanelHandle, SAMPLE_CFG_SAMPLERATE, &(pTestPara->sampleRate));
	GetCtrlVal(samplePanelHandle, SAMPLE_CFG_SAMPLENUMBER, &(pTestPara->sampleNumber));
	GetCtrlVal(samplePanelHandle, SAMPLE_CFG_RANGESETTING, &(pTestPara->rangeMode));

<<<<<<< HEAD
}

static unsigned char GetXorCheckVal(unsigned char* pUartBuf, unsigned char lenth)
{
	unsigned char i, xorCheck=0;
	for(i=0;i<lenth;i++)
		xorCheck^=*(pUartBuf+i);	
	return xorCheck;	
=======
>>>>>>> a0ab2d7488dc2715558bcf7b33d9ee1aa747214e
}

static void PrepareCfgTxData(TestParaTypeDef* pTestPara, unsigned char devAddr, unsigned char expType, unsigned char* pUartTxBuf)
{
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=MSG_TYPE_SETTING;     
	*(pUartTxBuf+2)=(unsigned char)expType;
	*(pUartTxBuf+4)=(unsigned char)((pTestPara->VdStart)>>8);
	*(pUartTxBuf+5)=(unsigned char)(pTestPara->VdStart&0xFF);
	*(pUartTxBuf+6)=(unsigned char)((pTestPara->VdStop)>>8);
	*(pUartTxBuf+7)=(unsigned char)(pTestPara->VdStop&0xFF);
	*(pUartTxBuf+8)=(unsigned char)((pTestPara->VdStep)>>8);
	*(pUartTxBuf+9)=(unsigned char)(pTestPara->VdStep&0xFF);
	*(pUartTxBuf+10)=(unsigned char)((pTestPara->VgStart)>>8);
	*(pUartTxBuf+11)=(unsigned char)(pTestPara->VgStart&0xFF);
	*(pUartTxBuf+12)=(unsigned char)((pTestPara->VgStop)>>8);
	*(pUartTxBuf+13)=(unsigned char)(pTestPara->VgStop&0xFF);
	*(pUartTxBuf+14)=(unsigned char)((pTestPara->VgStep)>>8);
	*(pUartTxBuf+15)=(unsigned char)(pTestPara->VgStep&0xFF);
	
	*(pUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pUartTxBuf, SA61_UART_TX_LEN-1); 
}


void ProtocolCfg(unsigned char comSelect, unsigned char devAddr, unsigned char expType, unsigned char* pUartTxBuf)
{
	unsigned char i, xorcheck=0;
	
	
	switch((enum ExpType)expType)
	{
		case SWEEP_DRAIN_VOL:
			GetTestPara(&IdVdPanel, &TestPara);
<<<<<<< HEAD
			break;
		case SWEEP_GATE_VOL:
			//GetTestPara(&IdVgPanel, &TestPara);
			break;
		case NO_SWEEP_IT:
			//GetTestPara(&IdVdPanel, &TestPara);
			break;
		case NO_SWEEP_RT:
			//GetTestPara(&IdVdPanel, &TestPara);
			break;
	}
	PrepareCfgTxData(&TestPara, devAddr, expType, pUartTxBuf);      
	ComWrt(comSelect, (const char*)pUartTxBuf, SA61_UART_TX_LEN);
}
=======
			PrepareCfgTxData(&TestPara, devAddr, expType, pUartTxBuf); 
			break;
	}
}

>>>>>>> a0ab2d7488dc2715558bcf7b33d9ee1aa747214e

void ProtocolRun(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf)
{
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=0x12;
	*(pUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pUartTxBuf, SA61_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pUartTxBuf, SA61_UART_TX_LEN);
}

void ProtocolStop(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf)
{
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=0x13;
	*(pUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pUartTxBuf, SA61_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pUartTxBuf, SA61_UART_TX_LEN);
}

void ProtocolQuery(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf)
{
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=0x14;
	*(pUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pUartTxBuf, SA61_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pUartTxBuf, SA61_UART_TX_LEN);
}

void ProtocolCalibrate(unsigned char comSelect, unsigned char devAddr, unsigned char* pUartTxBuf)
{
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=0x15;
	*(pUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pUartTxBuf, SA61_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pUartTxBuf, SA61_UART_TX_LEN);
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



























