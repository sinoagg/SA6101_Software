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
	float xAxisHead;//
	float xAxisTail;
	float yAxisHead;
	float yAxisTail;
}GraphAttrTypeDef;		
		
typedef struct
{
	int plotHandle;									//graph handle 
	int graphIndex;									//graph Index
	int numOfCurve;									//number of Curves
	int graphHanle;
  
	GraphAttrTypeDef* pGraphAttr;
	CurveTypeDef* pCurveArray;						//pointer to curve array
}GraphTypeDef;
//==============================================================================
// External variables
extern GraphTypeDef Graph1;
extern GraphTypeDef Graph2;

//==============================================================================
// Global functions
int GraphInit(int graphIndex, int numOfCurve, int numOfDots, GraphTypeDef* pGraph);
int GraphDeinit(GraphTypeDef* pGraph);
void SetYAxis(int hGraphPanel,int currentY_val,GraphTypeDef* pGraph );

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Graph_H__ */
