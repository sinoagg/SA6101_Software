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

#include <ansi_c.h>
#include "Plot.h"
#include <userint.h>
#include "Graph.h"
#include"LoadPanel.h"
#include "EnvironmentPanel.h" 
#include "GraphDisp.h"
#include "SettingsPanel.h"
#include "Protocol.h"	  


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
int graph2tempclr;
int graph2humclr; 
int graph2preclr;
//==============================================================================
// Global functions
int PlotCurve1(GraphTypeDef* pGraph, int graphDispPanel, int control, int plotCurveIndex,float rxIdmeasured)       
{   
     	
  		
		int numOfDotsToPlot=(pGraph->pCurveArray + plotCurveIndex)->numOfDotsToPlot;		//防止中断端去写入这个数据 
		if((numOfDotsToPlot + plotCurveIndex) >0)
		{
			if((pGraph->pCurveArray+plotCurveIndex)->numOfPlotDots >= 1)	//如果已经画了一个点，从上一个点开始画进行连线
			{

				pGraph->plotHandle=PlotXY(hGraphPanel, control, (pGraph->pCurveArray + plotCurveIndex)->pDotXPlot-1, (pGraph->pCurveArray + plotCurveIndex)->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT,
									pGraph->pCurveArray->pCurveAttr->plotStyle,
									pGraph->pCurveArray->pCurveAttr->pointStyle,
									pGraph->pCurveArray->pCurveAttr->lineStyle, 1,
									pGraph->pCurveArray->pCurveAttr->lineColor);
			}
			else											//如果一个点没画，只画一个点
			{
				pGraph->plotHandle=PlotXY(hGraphPanel, control, (pGraph->pCurveArray + plotCurveIndex)->pDotXPlot, (pGraph->pCurveArray + plotCurveIndex)->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT,
									pGraph->pCurveArray->pCurveAttr->plotStyle,
									pGraph->pCurveArray->pCurveAttr->pointStyle,
									pGraph->pCurveArray->pCurveAttr->lineStyle, 1,
									pGraph->pCurveArray->pCurveAttr->lineColor);
			}
			(pGraph->pCurveArray + plotCurveIndex)->numOfPlotDots+=numOfDotsToPlot;		//画图总点数递增
			(pGraph->pCurveArray + plotCurveIndex)->pDotXPlot+=numOfDotsToPlot;			//画图点X坐标指针递增
			(pGraph->pCurveArray + plotCurveIndex)->pDotYPlot+=numOfDotsToPlot;			//画图点Y坐标指针递增
			(pGraph->pCurveArray + plotCurveIndex)->numOfDotsToPlot-=numOfDotsToPlot;	//防止中断端在画图期间接收到新的数据.
			//SetGraphX_Axis(pGraph,pGraph->pCurveArray->numOfPlotDots);
			SetGraphY_Axis(pGraph,rxIdmeasured);              
			 
			    
	}
	if(pGraph->plotHandle<0)
		return -1;
	else
		return 0;
}	



 int PlotCurve2(GraphTypeDef* pGraph2, int hGraphPanel, int control)
{						
	int numOfDotsToPlot=pGraph2->pCurveArray->numOfDotsToPlot;							//防止中断端去写入这个数据
	
	if(pGraph2->pCurveArray->numOfPlotDots >=1 )	//画 第二个 点
	{
			if(numOfDotsToPlot>0)																
			{															  
				if(temp_flag == 1)  
				{
 					pGraph2->plotHandle=PlotXY(hGraphPanel, control, (pGraph2->pCurveArray +1)->pDotXPlot-1, (pGraph2->pCurveArray +1)->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT,
											   pCurveAttr->plotStyle,
									  		   pCurveAttr->pointStyle,
									  		   pCurveAttr->lineStyle, 1,
											   graph2tempclr);
				}
				if(humidity_flag == 1)
				{
					pGraph2->plotHandle=PlotXY(hGraphPanel, control, pGraph2->pCurveArray->pDotXPlot-1, pGraph2->pCurveArray->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT, 
											   pCurveAttr->plotStyle,
									  		   pCurveAttr->pointStyle,
									  		   pCurveAttr->lineStyle, 1,
											   graph2humclr);
				}
				if(pressure_flag == 1)
				{
					pGraph2->plotHandle=PlotXY(hGraphPanel, control, (pGraph2->pCurveArray +2)->pDotXPlot-1, (pGraph2->pCurveArray +2)->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT,
											   pCurveAttr->plotStyle,
									  		   pCurveAttr->pointStyle,
									  		   pCurveAttr->lineStyle, 1, 
											   graph2preclr);
				}
				
				pGraph2->pCurveArray->numOfPlotDots+=numOfDotsToPlot;				//画图总点数递增
				pGraph2->pCurveArray->pDotXPlot+=numOfDotsToPlot;					//画图点X坐标指针递增
				pGraph2->pCurveArray->pDotYPlot+=numOfDotsToPlot;					//画图点Y坐标指针递增
				pGraph2->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;				//防止中断端在画图期间接收到新的数据.
				
				(pGraph2->pCurveArray + 1)->numOfPlotDots+=numOfDotsToPlot;			//画图总点数递增
				(pGraph2->pCurveArray + 1)->pDotXPlot+=numOfDotsToPlot;				//画图点X坐标指针递增
				(pGraph2->pCurveArray + 1)->pDotYPlot+=numOfDotsToPlot;				//画图点Y坐标指针递增
				(pGraph2->pCurveArray + 1)->numOfDotsToPlot-=numOfDotsToPlot;		//防止中断端在画图期间接收到新的数据.
				
				(pGraph2->pCurveArray + 2)->numOfPlotDots+=numOfDotsToPlot;			//画图总点数递增
				(pGraph2->pCurveArray + 2)->pDotXPlot+=numOfDotsToPlot;				//画图点X坐标指针递增
				(pGraph2->pCurveArray + 2)->pDotYPlot+=numOfDotsToPlot;				//画图点Y坐标指针递增
				(pGraph2->pCurveArray + 2)->numOfDotsToPlot-=numOfDotsToPlot;		//防止中断端在画图期间接收到新的数据.
			}
    }
	else //画第一个点
	{
			if(numOfDotsToPlot>0)																//如果有需要画图的点
			{	
					if(temp_flag == 1)
				{
					Graph2.plotHandle=PlotXY(hGraphPanel, control, (Graph2.pCurveArray +1)->pDotXPlot, (Graph2.pCurveArray +1)->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT,
											 pCurveAttr->plotStyle,
									  		 pCurveAttr->pointStyle,
									  		 pCurveAttr->lineStyle, 1, 
											 graph2tempclr);
				}
				
				if(humidity_flag == 1) 
				{
					Graph2.plotHandle=PlotXY(hGraphPanel, control, Graph2.pCurveArray->pDotXPlot, Graph2.pCurveArray->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT,
											 pCurveAttr->plotStyle,
									  		 pCurveAttr->pointStyle,
									  		 pCurveAttr->lineStyle, 1, 
											 graph2humclr);
				}
				if(pressure_flag == 1)
				{
					Graph2.plotHandle=PlotXY(hGraphPanel, control, (Graph2.pCurveArray +2)->pDotXPlot, (Graph2.pCurveArray +2)->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT,
											 pCurveAttr->plotStyle,
									  		 pCurveAttr->pointStyle,
									  		 pCurveAttr->lineStyle,1, 
											 graph2preclr);
				}
				pGraph2->pCurveArray->numOfPlotDots+=numOfDotsToPlot;		//画图总点数递增
				pGraph2->pCurveArray->pDotXPlot+=numOfDotsToPlot;			//画图点X坐标指针递增
				pGraph2->pCurveArray->pDotYPlot+=numOfDotsToPlot;			//画图点Y坐标指针递增
				pGraph2->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;		//防止中断端在画图期间接收到新的数据.
				
				(pGraph2->pCurveArray + 1)->numOfPlotDots+=numOfDotsToPlot;		//画图总点数递增
				(pGraph2->pCurveArray + 1)->pDotXPlot+=numOfDotsToPlot;			//画图点X坐标指针递增
				(pGraph2->pCurveArray + 1)->pDotYPlot+=numOfDotsToPlot;			//画图点Y坐标指针递增
				(pGraph2->pCurveArray + 1)->numOfDotsToPlot-=numOfDotsToPlot;		//防止中断端在画图期间接收到新的数据.
				
				(pGraph2->pCurveArray + 2)->numOfPlotDots+=numOfDotsToPlot;		//画图总点数递增
				(pGraph2->pCurveArray + 2)->pDotXPlot+=numOfDotsToPlot;			//画图点X坐标指针递增
				(pGraph2->pCurveArray + 2)->pDotYPlot+=numOfDotsToPlot;			//画图点Y坐标指针递增
				(pGraph2->pCurveArray + 2)->numOfDotsToPlot-=numOfDotsToPlot;		//防止中断端在画图期间接收到新的数据.
			}
	}
	if(pGraph2->plotHandle<0)
		return -1;
	else
		return 0;
}

void DisplayEnvtGraph()
{

	DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH2, -1, VAL_IMMEDIATE_DRAW);	//先清除环境测量曲线图中的所有曲线
	 
	GetCtrlVal(hEnvResultPanel,ENVIRPANEL_TEMP_BOX,&temp_flag);		//然后读取用户要选中的曲线
	GetCtrlVal(hEnvResultPanel,ENVIRPANEL_HUM_BOX,&humidity_flag); 
	GetCtrlVal(hEnvResultPanel,ENVIRPANEL_PRESS_BOX,&pressure_flag);
	
	//
	GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR1, &graph2tempclr);
	GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR2, &graph2humclr);
	GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR3, &graph2preclr);

	if((temp_flag == 1)&&((Graph2.pCurveArray  + 1)->numOfPlotDots>0))  
	{
		
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text背景色(与canvas颜色相同)
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"Temperature"颜色
		CanvasDrawText (hGraphPanel, GRAPHDISP_CANVAS, "T",VAL_APP_META_FONT,MakeRect(40,15,15,70), VAL_CENTER);	                            //写"Temperature"
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR,graph2tempclr); 			    //Temperature图例
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //线的宽度
		CanvasDrawLine (hGraphPanel, GRAPHDISP_CANVAS, MakePoint (110,47), MakePoint (150, 47));		//canvas画线
																				   
		PlotXY(hGraphPanel, GRAPHDISP_GRAPH2, (Graph2.pCurveArray  + 1)->pDotXHead, (Graph2.pCurveArray  + 1)->pDotYHead, (Graph2.pCurveArray  + 1)->numOfPlotDots, VAL_FLOAT, VAL_FLOAT, 
			   pCurveAttr->plotStyle,
			   pCurveAttr->pointStyle,
			   pCurveAttr->lineStyle, 1,
			   graph2tempclr);
	}
	else
	{
	  CanvasClear (hGraphPanel, GRAPHDISP_CANVAS, MakeRect(40,15,15,140));
	}
	
	if((humidity_flag == 1)&&(Graph2.pCurveArray->numOfPlotDots>0))
	{						 
		
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text背景色(与canvas颜色相同)
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"humidity"颜色
		CanvasDrawText (hGraphPanel, GRAPHDISP_CANVAS, "H",VAL_APP_META_FONT,MakeRect(60,15,15,70), VAL_CENTER);	                            //写"humidity"
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, graph2humclr);   		    //humidity图例
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //线的宽度
		CanvasDrawLine (hGraphPanel, GRAPHDISP_CANVAS, MakePoint (110, 67), MakePoint (150, 67));		//canvas画线

		
		PlotXY(hGraphPanel, GRAPHDISP_GRAPH2, Graph2.pCurveArray->pDotXHead, Graph2.pCurveArray->pDotYHead, Graph2.pCurveArray->numOfPlotDots, VAL_FLOAT, VAL_FLOAT,
			   pCurveAttr->plotStyle,
			   pCurveAttr->pointStyle,
			   pCurveAttr->lineStyle, 1, 
			   graph2humclr);

	}
	else									
	{
	  CanvasClear (hGraphPanel, GRAPHDISP_CANVAS, MakeRect(60,15,15,140));
	}
	
	if((pressure_flag == 1)&&((Graph2.pCurveArray  + 2)->numOfPlotDots>0)) 
	{
		
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text背景色(与canvas颜色相同)
	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"pressure"颜色
	    CanvasDrawText (hGraphPanel, GRAPHDISP_CANVAS, "P",VAL_APP_META_FONT,MakeRect(80,15,15,70), VAL_CENTER);	                            //写"pressure"
	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR,graph2preclr);   		    //pressure图例
	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //线的宽度
	    CanvasDrawLine (hGraphPanel, GRAPHDISP_CANVAS, MakePoint (110, 87), MakePoint (150, 87));		//canvas画线
		
		PlotXY(hGraphPanel, GRAPHDISP_GRAPH2, (Graph2.pCurveArray  + 2)->pDotXHead, (Graph2.pCurveArray  + 2)->pDotYHead, (Graph2.pCurveArray  + 2)->numOfPlotDots, VAL_FLOAT, VAL_FLOAT, 
			  pCurveAttr->plotStyle,
			  pCurveAttr->pointStyle,
			  pCurveAttr->lineStyle,1, 
			  graph2preclr);

	}
	else
	
	{
	
	 CanvasClear (hGraphPanel, GRAPHDISP_CANVAS, MakeRect(80,15,15,140)); 

	}
}
	

