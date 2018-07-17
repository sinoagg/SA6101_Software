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
int curveInit(int curveIndex, int numOfTotalDots, Curve_TypeDef* pCurve)
{
	pCurve->pDotX = (float *)malloc(numOfTotalDots * sizeof(float));
	if(pCurve->pDotX == NULL) return -1;
	pCurve->pDotY = (float *)malloc(numOfTotalDots * sizeof(float));
	if(pCurve->pDotY == NULL) return -1;
	pCurve->curveIndex=curveIndex;
	pCurve->numOfTotalDots=numOfTotalDots;
	pCurve->numOfPlotDots=0;		
	pCurve->numOfDotsToPlot=0;
	pCurve->pDotXPlot=pCurve->pDotX;				//��ͼ��ָ��ָ�����ݵ�ָ��
	pCurve->pDotYPlot=pCurve->pDotY;				//��ͼ��ָ��ָ�����ݵ�ָ�� 	
	
	return 0;
}

int curveDeinit(Curve_TypeDef* pCurve)
{
	free(pCurve->pDotX);
	free(pCurve->pDotY);
	
	return 0;
}
