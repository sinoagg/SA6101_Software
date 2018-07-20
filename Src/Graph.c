#include <userint.h>
#include "GraphDisp.h"

//==============================================================================
//
// Title:		Graph.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/12 at 13:50:53 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <ansi_c.h>
#include "Curve.h"
#include "Graph.h"
#include"LoadPanel.h"

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
Graph_TypeDef* pGraph;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int graphInit(int graphIndex, int numOfCurve, int numOfDots, Graph_TypeDef* pGraph)
{
	int i;
	pGraph->graphIndex=graphIndex;
	pGraph->numOfCurve=numOfCurve;
	Curve_TypeDef* pCurveArray = (Curve_TypeDef *)malloc(numOfCurve * sizeof(Curve_TypeDef)); 	//Curve Array Saving pointers to curve structure
	if(pCurveArray==NULL) return -1;
	pGraph->pCurveArray=pCurveArray;
	
	for(i=0;i<numOfCurve;i++)		//init curve
	{
		if(curveInit(i, numOfDots, pCurveArray+i)==-1) return -1;
	}
	return 0;
}

