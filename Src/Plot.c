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
	int numOfDotsToPlot=pGraph->pCurveArray->numOfDotsToPlot;							//��ֹ�ж϶�ȥд��������� 
	if(numOfDotsToPlot>0)																//�������Ҫ��ͼ�ĵ�
	{
		pGraph->pCurveArray->plotHandle=PlotXY(graphDispPanel, control, pGraph->pCurveArray->pDotXPlot, pGraph->pCurveArray->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
		pGraph->pCurveArray->numOfPlotDots+=numOfDotsToPlot;		//��ͼ��������
		pGraph->pCurveArray->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
		pGraph->pCurveArray->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
		pGraph->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����
	}
	if(pGraph->pCurveArray->plotHandle<0)
		return -1;
	else
		return 0;
}
