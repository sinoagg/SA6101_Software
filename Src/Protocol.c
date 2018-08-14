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
#include <rs232.h>
#include "LoadPanel.h"
#include "ItPanel.h"
#include "RtPanel.h"
#include "IvPanel.h"
#include "IdtPanel.h"

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
static void GetTestPara(ExpPanelTypeDef* pExpPanel, TestParaTypeDef* pTestPara) //读取数据
{
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VdStartID, &(pTestPara->VdStart));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VdStopID, &(pTestPara->VdStop));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VdStepID, &(pTestPara->VdStep));
	
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VgStartID, &(pTestPara->VgStart));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VgStopID, &(pTestPara->VgStop));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VgStepID, &(pTestPara->VgStep));
	
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->drainModeID, &(pTestPara->drainOutputMode));
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->gateModeID, &(pTestPara->gateOutputMode));
	
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_QUIETTIME, &(pTestPara->quietTime));   //所有采样配置都是兼容的
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, &(pTestPara->timeStep));
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, &(pTestPara->runTime));
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, &(pTestPara->sampleRate));
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_SAMPLENUMBER, &(pTestPara->sampleNumber));
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_RANGESETTING, &(pTestPara->rangeMode));
	GetCtrlVal(hAdvanceSamplePanel, SAMPLE_ADV_MAXRANGE, &(pTestPara->maxRange));
	GetCtrlVal(hAdvanceSamplePanel, SAMPLE_ADV_MINRANGE, &(pTestPara->minRange));
}

static unsigned char GetXorCheckVal(unsigned char* pUartBuf, unsigned char lenth)
{
	unsigned char i, xorCheck=0;
	for(i=0;i<lenth;i++)
		xorCheck^=*(pUartBuf+i);	
	return xorCheck;	
}

static void PrepareCfgTxData(TestParaTypeDef* pTestPara, unsigned char devAddr, unsigned char* pmeasUartTxBuf)
{
	*pmeasUartTxBuf=devAddr;
	*(pmeasUartTxBuf+1)=MSG_TYPE_SETTING;     
	*(pmeasUartTxBuf+2)=(unsigned char)(pTestPara->testMode);
	*(pmeasUartTxBuf+4)=(unsigned char)((pTestPara->VdStart)>>8);
	*(pmeasUartTxBuf+5)=(unsigned char)((pTestPara->VdStart)&0xFF);
	*(pmeasUartTxBuf+6)=(unsigned char)((pTestPara->VdStop)>>8);
	*(pmeasUartTxBuf+7)=(unsigned char)((pTestPara->VdStop)&0xFF);
	*(pmeasUartTxBuf+8)=(unsigned char)((pTestPara->VdStep)>>8);
	*(pmeasUartTxBuf+9)=(unsigned char)((pTestPara->VdStep)&0xFF);
	*(pmeasUartTxBuf+10)=(unsigned char)((pTestPara->VgStart)>>8);
	*(pmeasUartTxBuf+11)=(unsigned char)((pTestPara->VgStart)&0xFF);
	*(pmeasUartTxBuf+12)=(unsigned char)((pTestPara->VgStop)>>8);
	*(pmeasUartTxBuf+13)=(unsigned char)((pTestPara->VgStop)&0xFF);
	*(pmeasUartTxBuf+14)=(unsigned char)((pTestPara->VgStep)>>8);
	*(pmeasUartTxBuf+15)=(unsigned char)((pTestPara->VgStep)&0xFF);
	*(pmeasUartTxBuf+16)=(unsigned char)((pTestPara->quietTime)>>8);
	*(pmeasUartTxBuf+17)=(unsigned char)((pTestPara->quietTime)&0xFF);
	*(pmeasUartTxBuf+18)=(unsigned char)((pTestPara->timeStep)>>8);
	*(pmeasUartTxBuf+19)=(unsigned char)((pTestPara->timeStep)&0xFF);
	*(pmeasUartTxBuf+20)=(unsigned char)((pTestPara->runTime)>>8);
	*(pmeasUartTxBuf+21)=(unsigned char)((pTestPara->runTime)&0xFF);
	*(pmeasUartTxBuf+22)=(unsigned char)((pTestPara->sampleRate)>>8);
	*(pmeasUartTxBuf+23)=(unsigned char)((pTestPara->sampleRate)&0xFF);
	*(pmeasUartTxBuf+24)=(unsigned char)((pTestPara->sampleNumber)>>8);
	*(pmeasUartTxBuf+25)=(unsigned char)((pTestPara->sampleNumber)&0xFF);
	*(pmeasUartTxBuf+26)=(unsigned char)(pTestPara->rangeMode);
	*(pmeasUartTxBuf+27)=(unsigned char)(pTestPara->maxRange);
	*(pmeasUartTxBuf+28)=(unsigned char)(pTestPara->minRange);
	*(pmeasUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA61_UART_TX_LEN-1); 
}


void ProtocolCfg(unsigned char comSelect, unsigned char devAddr, enum TestMode expType, unsigned char* pmeasUartTxBuf)
{
	switch(expType)
	{
		case SWEEP_DRAIN_VOL:
			GetTestPara(&IdVdPanel, &TestPara);
			break;
		case SWEEP_GATE_VOL:
		    GetTestPara(&IdVgPanel, &TestPara);
			break;
		case NO_SWEEP_IT:
			GetTestPara(&ItPanel, &TestPara);
			break;
		case NO_SWEEP_RT:
			GetTestPara(&RtPanel, &TestPara);
			break;
		case SWEEP_IV:
			GetTestPara(&IvPanel,&TestPara);
			break;
		case ID_T:
			GetTestPara(&IdtPanel,&TestPara);
			break;
	}
	PrepareCfgTxData(&TestPara, devAddr, pmeasUartTxBuf);      
	ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA61_UART_TX_LEN);
}

void ProtocolRun(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)
{
	*pmeasUartTxBuf=devAddr;
	*(pmeasUartTxBuf+1)=MSG_TYPE_RUN;
	*(pmeasUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA61_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA61_UART_TX_LEN);
}

void ProtocolStop(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)
{
	*pmeasUartTxBuf=devAddr;
	*(pmeasUartTxBuf+1)=MSG_TYPE_STOP;
	*(pmeasUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA61_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA61_UART_TX_LEN);
}

void ProtocolQuery(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)
{
	*pmeasUartTxBuf=devAddr;
	*(pmeasUartTxBuf+1)=MSG_TYPE_QUERY;
	*(pmeasUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA61_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA61_UART_TX_LEN);
}

void ProtocolCalibrate(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)
{
	*pmeasUartTxBuf=devAddr;
	*(pmeasUartTxBuf+1)=MSG_TYPE_CALIBRATION;
	*(pmeasUartTxBuf+SA61_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA61_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA61_UART_TX_LEN);
}

void ProtocolGetData(unsigned char* pmeasUartRxBuf, RxDataTypeDef* pRxData)	//Get data from UART Rx Buffer
{																			//
	pRxData->rxDevAddr=*pmeasUartRxBuf;
	pRxData->rxStopSign=*(pmeasUartRxBuf+1);
	pRxData->rxVdtest=(((int)*(pmeasUartRxBuf+2))<<8)|*(pmeasUartRxBuf+3);
	pRxData->rxVgtest=(((int)*(pmeasUartRxBuf+4))<<8)|*(pmeasUartRxBuf+5);
	pRxData->rxIdmeasured.num_uchar[3]=*(pmeasUartRxBuf+6);
	pRxData->rxIdmeasured.num_uchar[2]=*(pmeasUartRxBuf+7); 
	pRxData->rxIdmeasured.num_uchar[1]=*(pmeasUartRxBuf+8); 
	pRxData->rxIdmeasured.num_uchar[0]=*(pmeasUartRxBuf+9);
	pRxData->rxVdmeasured.num_uchar[3]=*(pmeasUartRxBuf+10); 
	pRxData->rxVdmeasured.num_uchar[2]=*(pmeasUartRxBuf+11);
	pRxData->rxVdmeasured.num_uchar[1]=*(pmeasUartRxBuf+12);
	pRxData->rxVdmeasured.num_uchar[0]=*(pmeasUartRxBuf+13);
	pRxData->rxVgmeasured.num_uchar[3]=*(pmeasUartRxBuf+14); 
	pRxData->rxVgmeasured.num_uchar[2]=*(pmeasUartRxBuf+15);
	pRxData->rxVgmeasured.num_uchar[1]=*(pmeasUartRxBuf+16);
	pRxData->rxVgmeasured.num_uchar[0]=*(pmeasUartRxBuf+17);
	pRxData->rangeSelect=*(pmeasUartRxBuf+18);
}



























