//==============================================================================
//
// Title:		MainPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/16 at 15:58:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __MainPanel_H__
#define __MainPanel_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "ExpListPanel.h"
#include "SampleCfgPanel.h"
#include "IdVdsPanel.h"
#include "IdVgsPanel.h"
#include "Protocol.h"
#include "Graph.h"
#include "Curve.h"
#include "File.h"
#include "ItPanel.h"
#include "RtPanel.h"
#include "TablePanel.h"
#include "AutoSaveDataPanel.h"  
//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int hSinglePrjPanel;				//���غ�ÿ����Ŀ��panel���
	int index;							//�Զ����Ŀ¼��������λ�ú���ʾ
}PrjHandleTypeDef;
//==============================================================================
// External variables
extern unsigned char measureComPort;
extern unsigned char controlComPort; 
extern FileLableTypeDef *pFileLable[];
extern PrjHandleTypeDef SingleProject[];
//extern int x2;
//extern int xAxis;
extern int vdstart;
extern int vgstart;
//==============================================================================
//// Global functions
static int SaveConfigToFile(char* pConfigSavePath);
int CVICALLBACK AbnmDCThreadFunction (void *functionData);		 //�������̻߳ص�����

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __MainPanel_H__ */