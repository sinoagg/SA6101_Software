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
#include "SettingsPanel.h"

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
GraphTypeDef Graph1;
GraphTypeDef Graph2;
 
//==============================================================================
// Global functions


int GraphInit(int hGraphPanel, int graphIndex, int numOfCurve, int numOfDots, GraphTypeDef* pGraph)
{

	int i;
	pGraph->graphHandle=hGraphPanel;
	pGraph->graphIndex=graphIndex;	 
	pGraph->numOfCurve=numOfCurve;
	CurveTypeDef* pCurveArray = (CurveTypeDef *)malloc(numOfCurve * sizeof(CurveTypeDef)); 	//Curve Array Saving pointers to curve structure
	if(pCurveArray==NULL) return -1;
	pGraph->pCurveArray=pCurveArray;
	
	for(i=0;i<numOfCurve;i++)		//init curve
	{
		if(curveInit(pCurveArray+i, i, numOfDots, GetSettingsCurveAttr(graphIndex, i))==-1) return -1;
	}
	
	GraphAttrTypeDef* pGraphAttr = (GraphAttrTypeDef *)malloc(sizeof(CurveTypeDef));
	
	if(pGraphAttr==NULL) return -1;
	
	pGraph->pGraphAttr=pGraphAttr;

	return 0;
}

int GraphDeinit(GraphTypeDef* pGraph)
{
	int i=0;
	for(i=0;i<(pGraph->numOfCurve);i++)
	{
		curveDeinit(pGraph->pCurveArray++); 	
	}
	return 0;
}

void SetGraphY_Axis(GraphTypeDef* pGraph, float currentY_Val)
{
	//if(pGraph->pGraphAttr->yAxisTail < currentY_Val &&  pGraph->pGraphAttr->yAxisHead >=0)
	//{
	//	pGraph->pGraphAttr->yAxisTail = currentY_Val*2;
	//	SetAxisScalingMode(pGraph->graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, pGraph->pGraphAttr->yAxisHead, pGraph->pGraphAttr->yAxisTail);//设置 Y  轴的范围

	//}
    // else if(pGraph->pGraphAttr->yAxisHead > currentY_Val && pGraph->pGraphAttr->yAxisHead >=0)
	//{
	//	pGraph->pGraphAttr->yAxisHead = currentY_Val/2;	
	//	SetAxisScalingMode(pGraph->graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, pGraph->pGraphAttr->yAxisHead, pGraph->pGraphAttr->yAxisTail);//设置 Y  轴的范围

	//}
}

void SetGraphX_Axis(GraphTypeDef* pGraph, float currentX_Val)
{
	if(pGraph->pGraphAttr->xAxisTail < currentX_Val)
	{
		Graph1.pGraphAttr->xAxisTail = currentX_Val*2;
		SetAxisScalingMode(pGraph->graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead, Graph1.pGraphAttr->xAxisTail);//设置 X  轴的范围
	}
	else if(pGraph->pGraphAttr->yAxisHead > currentX_Val)
	{
		Graph1.pGraphAttr->yAxisTail = currentX_Val/2;
		SetAxisScalingMode(pGraph->graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead, Graph1.pGraphAttr->xAxisTail);//设置 X  轴的范围

	}	 
}

int CVICALLBACK CanvasCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	int LeftButtonDown;
	int x;
	int y;
	int CtrlTop;
	int CtrlLeft;


	static int OldX = 0;	  //局部静态变量，旧X、坐标值 
	static int OldY = 0;	
	switch (event)
	{
		case EVENT_MOUSE_POINTER_MOVE:
			
			GetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_LEFT, &CtrlLeft);
			GetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_TOP, &CtrlTop);
			GetGlobalMouseState (&panel, &x, &y, &LeftButtonDown, NULL, NULL);	     // 获得鼠标绝对位置、按键等属性
		
			if (LeftButtonDown == 1)	  // 当鼠标左键按下时
			{
				SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_LEFT, CtrlLeft + (x-OldX) );
				SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_TOP, CtrlTop + (y-OldY) );
		
				OldX = x;
				OldY = y;				   // 将旧X、Y 坐标值以当前新值代替 
			
				if( ( CtrlTop + (y-OldY) )<420)			 //图例不能超出graph2的范围
				{
					SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_LEFT, CtrlLeft + (x-OldX) );
					SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_TOP, 420 );
				}
				if( ( CtrlTop + (y-OldY) )>670)
				{
					SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_LEFT, CtrlLeft + (x-OldX) );
					SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_TOP, 670 );
				}
				if( (CtrlLeft + (x-OldX) )<15)
				{
					SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_LEFT, 15 );
					SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_TOP, CtrlTop + (y-OldY) );
				}
				if( (CtrlLeft + (x-OldX) )>1010)
				{
					SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_LEFT, 1010 );
					SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_TOP, CtrlTop + (y-OldY) );
				}
			
			}
		 
			OldX = x;
			OldY = y;					  // 将旧X、坐标值以当前新值代替
			
		break;
	}
	return 0;
}
