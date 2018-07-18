//==============================================================================
//
// Title:		Curve.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/12 at 15:27:18 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Curve_H__
#define __Curve_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int curveIndex;
	int numOfDots;
	int numOfPlotDots;
	float* pDotX;
	float* pDotY;
}Curve_TypeDef;

typedef struct
{
	float x;										//x on X-Axis
	float y;										//y on Y-Axis
}Dot_TypeDef;
//==============================================================================
// External variables

//==============================================================================
// Global functions

int curveInit(int curveIndex, int numOfDots, Curve_TypeDef* pCurve);
int curveDeinit(Curve_TypeDef* pCurve);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Curve_H__ */
