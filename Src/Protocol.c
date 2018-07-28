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
#include "ExpListPanel.h"
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
void GetTestPara(ExpPanelTypeDef* pExpPanel, TestParaTypeDef* pTestPara)
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
	
	
}

void PrepareCfgTxData(TestParaTypeDef* pTestPara, unsigned char devAddr, unsigned char expType, unsigned char* pUartTxBuf)
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
}

void ProtocolCfg(unsigned char comSelect, unsigned char devAddr, unsigned char expType, unsigned char* pUartTxBuf)
{
	unsigned char i, xorcheck=0;
	
	
	switch((enum ExpType)expType)
	{
		case SWEEP_DRAIN_VOL:
			GetTestPara(&IdVdPanel, &TestPara);
			PrepareCfgTxData(&TestPara, devAddr, expType, pUartTxBuf); 
			break;
	}
}

/*void ProtocolCfg(unsigned char comSelect, unsigned char devAddr, unsigned char expType, unsigned char* pUartTxBuf)	//Make config info to UART Tx Buffer
{
	unsigned char i, xorcheck=0;
	*pUartTxBuf=devAddr;
	*(pUartTxBuf+1)=MSG_TYPE_SETTING;
	switch((enum ExpType)expType)
	{
		case SWEEP_DRAIN_VOL:
			*(pUartTxBuf+2)=(unsigned char)SWEEP_DRAIN_VOL;
			//GetTestPara(panelHandle, pTestPara);
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
		case SWEEP_GATE_VOL:
			*(pUartTxBuf+2)=(unsigned char)SWEEP_GATE_VOL;   
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

}*/

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



























