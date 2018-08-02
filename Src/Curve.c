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

int curveInit(CurveTypeDef* pCurve, int curveIndex, int numOfTotalDots, CurveAttrTypeDef* pCurveAttr)
{
	pCurve->pDotXHead = (float *)malloc(numOfTotalDots * sizeof(float));
	if(pCurve->pDotXHead == NULL) return -1;
	pCurve->pDotYHead = (float *)malloc(numOfTotalDots * sizeof(float));
	if(pCurve->pDotYHead == NULL) return -1;
	pCurve->curveIndex=curveIndex;
	pCurve->numOfTotalDots=numOfTotalDots;
	pCurve->pDotX=pCurve->pDotXHead;
	pCurve->pDotY=pCurve->pDotYHead;
	pCurve->numOfPlotDots=0;		
	pCurve->numOfDotsToPlot=0;
	pCurve->time=0;
	pCurve->pDotXPlot=pCurve->pDotX;				//画图的指针指向数据的指针
	pCurve->pDotYPlot=pCurve->pDotY;				//画图的指针指向数据的指针 	
	pCurve->pCurveAttr=pCurveAttr;					//直接把指针指向其他定义好的CurveAttr， 这里没有必要重新定义
	return 0;
}

int curveDeinit(CurveTypeDef* pCurve)
{
	free(pCurve->pDotXHead);
	free(pCurve->pDotYHead);
	
	return 0;
}
