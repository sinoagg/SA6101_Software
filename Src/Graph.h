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
	float xAxisHead;
	float xAxisTail;
	float yAxisHead;
	float yAxisTail;
}GraphAttrTypeDef;		
		
typedef struct
{
	int graphHandle;									//graph handle 
	int graphIndex;									//graph Index
	int numOfCurve;									//number of Curves
    int plotHandle;									//后期需要整改属于plot
	int plotCurveIndex;								//当前在画曲线
	GraphAttrTypeDef* pGraphAttr;
	CurveTypeDef* pCurveArray;						//pointer to curve array
}GraphTypeDef;
//==============================================================================
// External variables
extern GraphTypeDef Graph1;
extern GraphTypeDef Graph2;

//==============================================================================
// Global functions
int GraphInit(int hGraphPanel, int graphIndex, int numOfCurve, int numOfDots, GraphTypeDef* pGraph);
int GraphDeinit(GraphTypeDef* pGraph);

void SetGraphY_Axis(GraphTypeDef Graph1, float currentY_Val);  
void SetGraphX_Axis(GraphTypeDef* pGraph, float currentX_Val);  

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Graph_H__ */
