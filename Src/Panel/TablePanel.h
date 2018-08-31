//==============================================================================
//
// Title:		TablePanel.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/8/10 at 19:13:58 by �� ��.
// Copyright:	���ɹ������ѧ. All Rights Reserved.
//
//==============================================================================

#ifndef __TablePanel_H__
#define __TablePanel_H__

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
	int column;									    //��
	int columnWidth;								//�п�  
	int row;										//��
	
}Table_TypeDef;


extern Table_TypeDef Table_Date;
extern Table_TypeDef Table_ATTR; 


//==============================================================================
// External variables

//==============================================================================
// Global functions
void Table_init(char table_title[][20], int column, columnWidth);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __TablePanel_H__ */
