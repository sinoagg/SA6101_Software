//==============================================================================
//
// Title:		Curve.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/12 at 15:27:18 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <ansi_c.h>
#include "Curve.h"

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

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int curveInit(int curveIndex, int numOfDots, Curve_TypeDef* pCurve)
{
	float *pX = (float *)malloc(numOfDots * sizeof(float));
	if(pX == NULL) return -1;
	float *pY = (float *)malloc(numOfDots * sizeof(float));
	if(pY == NULL) return -1;
	pCurve->curveIndex=curveIndex;
	pCurve->numOfDots=numOfDots;
	pCurve->pDotX=pX;
	pCurve->pDotY=pY;
	pCurve->numOfPlotDots=0;
	
	return 0;
}

int curveDeinit(Curve_TypeDef* pCurve)
{
	free(pCurve->pDotX);
	free(pCurve->pDotY);
	
	return 0;
}
