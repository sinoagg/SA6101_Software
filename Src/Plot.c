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
#include"LoadPanel.h"
#include "Environment.h"  
#include "EnvironmentPanel.h" 
#include "GraphDisp.h"

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
   	CurveAttrTypeDef* pCurveAttr;
//==============================================================================
// Global functions

int PlotCurve(GraphTypeDef* pGraph, int hGraphPanel, int control)
{

	//GetCtrlVal(hSettingsGraphPanel, SETGRAPH_LINE_STYLE, &(pCurveAttr->lineStyle));
	//GetCtrlVal(hSettingsGraphPanel, SETGRAPH_PLOT_STYLE, &(pCurveAttr->plotStyle)); 
	//GetCtrlVal(hSettingsGraphPanel, SETGRAPH_POINT_STYLE,&(pCurveAttr->pointStyle));
	//GetCtrlVal(hSettingsGraphPanel, SETGRAPH_GRAPH1CLR1, &(pCurveAttr->lineColor));
	int numOfDotsToPlot=pGraph->pCurveArray->numOfDotsToPlot;							//��ֹ�ж϶�ȥд��������� 
	   
	if(numOfDotsToPlot>0)
	{
	   	if(pGraph->pCurveArray->numOfPlotDots >= 1)																//�������Ҫ��ͼ�ĵ�
		{  			
			pGraph->plotHandle=PlotXY(hGraphPanel, control, pGraph->pCurveArray->pDotXPlot-1, pGraph->pCurveArray->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_DASH, 1, VAL_CYAN);

			//pGraph->plotHandle=PlotXY(hGraphPanel, control, pGraph->pCurveArray->pDotXPlot-1, pGraph->pCurveArray->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT, pCurveAttr->plotStyle, pCurveAttr->pointStyle, (pCurveAttr->lineStyle), 1, pCurveAttr->lineColor);
		}
		else
		{   		
			pGraph->plotHandle=PlotXY(hGraphPanel, control, pGraph->pCurveArray->pDotXPlot, pGraph->pCurveArray->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);

		//	pGraph->plotHandle=PlotXY(hGraphPanel, control, pGraph->pCurveArray->pDotXPlot, pGraph->pCurveArray->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT,pCurveAttr->plotStyle, pCurveAttr->pointStyle, (pCurveAttr->lineStyle), 1, pCurveAttr->lineColor);
		}
		pGraph->pCurveArray->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
		pGraph->pCurveArray->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
		pGraph->pCurveArray->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
		pGraph->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����
	}
	if(pGraph->plotHandle<0)
		return -1;
	else
		return 0;
}




//Temp
//void DisplayTempGraph()
//{
//   DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH2, -1, VAL_IMMEDIATE_DRAW); //ÿ�λ�֮ǰ�����������
//   GetCtrlVal(hGraphPanel,GRAPHDISP_GRAPH2,&temp_flag);
//   
//   if(temp_flag==1)
//   {
//        SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text����ɫ(��canvas��ɫ��ͬ)
//		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"Temperature"��ɫ
//		CanvasDrawText (hGraphPanel, GRAPHDISP_CANVAS, "T",VAL_APP_META_FONT, 
//							  MakeRect(40,15,15,70), VAL_CENTER);	                            //д"Temperature"
//		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_MAGENTA);			    //Temperatureͼ��
//		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //�ߵĿ��
//	    CanvasDrawLine (hGraphPanel, GRAPHDISP_CANVAS, MakePoint (110, 47), MakePoint (150, 47));		//canvas����

//		
//		PlotXY(hGraphPanel, GRAPHDISP_GRAPH2, Graph2.pCurveArray->pDotXHead, Graph2.pCurveArray->pDotYHead, Graph2.pCurveArray->numOfPlotDots, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_MAGENTA);
//	}
//	
//}




