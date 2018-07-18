//==============================================================================
//
// Title:		Plot.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:35:20 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "Plot.h"
#include <userint.h>
#include "Graph.h"
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

int PlotCurve(Graph_TypeDef* pGraph, int graphDispPanel, int control)
{
		if(pGraph->pCurveArray->numOfPlotDots>0)
		pGraph->plotHandle=PlotXY(graphDispPanel, control, pGraph->pCurveArray->pDotX, pGraph->pCurveArray->pDotY, pGraph->pCurveArray->numOfPlotDots, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
	if(pGraph->plotHandle<0)
		return -1;
	else
		return 0;
}
