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

int PlotCurve(GraphTypeDef* pGraph, int hGraphPanel, int control)
{
	int numOfDotsToPlot=pGraph->pCurveArray->numOfDotsToPlot;							//防止中断端去写入这个数据 
	
	if(numOfDotsToPlot>0)
	{
	   	if(pGraph->pCurveArray->numOfPlotDots >= 1)																//如果有需要画图的点
		{
			pGraph->plotHandle=PlotXY(hGraphPanel, control, pGraph->pCurveArray->pDotXPlot-1, pGraph->pCurveArray->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_DASH, 1, VAL_CYAN);
		}
		else
		{
			pGraph->plotHandle=PlotXY(hGraphPanel, control, pGraph->pCurveArray->pDotXPlot, pGraph->pCurveArray->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
		}
		pGraph->pCurveArray->numOfPlotDots+=numOfDotsToPlot;		//画图总点数递增
		pGraph->pCurveArray->pDotXPlot+=numOfDotsToPlot;			//画图点X坐标指针递增
		pGraph->pCurveArray->pDotYPlot+=numOfDotsToPlot;			//画图点Y坐标指针递增
		pGraph->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;		//防止中断端在画图期间接收到新的数据
	}
	if(pGraph->plotHandle<0)
		return -1;
	else
		return 0;
}
