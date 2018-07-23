//==============================================================================
//
// Title:		Graph.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/12 at 13:50:53 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Graph_H__
#define __Graph_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "curve.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int plotHandle;									//graph handle 
	int graphIndex;									//graph Index
	int numOfCurve;									//number of Curves
	Curve_TypeDef* pCurveArray;						//pointer to curve array
}GraphTypeDef;

//==============================================================================
// External variables
extern GraphTypeDef* pGraph1;
extern GraphTypeDef* pGraph2;

//==============================================================================
// Global functions
int graphInit(int graphIndex, int numOfCurve, int numOfDots, GraphTypeDef* pGraph);
int graphDeinit(GraphTypeDef* pGraph);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Graph_H__ */
