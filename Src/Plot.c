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
     	
  		
		int numOfDotsToPlot=(pGraph->pCurveArray + plotCurveIndex)->numOfDotsToPlot;		//��ֹ�ж϶�ȥд��������� 
		if((numOfDotsToPlot + plotCurveIndex) >0)
		{
			if((pGraph->pCurveArray+plotCurveIndex)->numOfPlotDots >= 1)	//����Ѿ�����һ���㣬����һ���㿪ʼ����������
			{

				pGraph->plotHandle=PlotXY(hGraphPanel, control, (pGraph->pCurveArray + plotCurveIndex)->pDotXPlot-1, (pGraph->pCurveArray + plotCurveIndex)->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT,
									pGraph->pCurveArray->pCurveAttr->plotStyle,
									pGraph->pCurveArray->pCurveAttr->pointStyle,
									pGraph->pCurveArray->pCurveAttr->lineStyle, 1,
									pGraph->pCurveArray->pCurveAttr->lineColor);
			}
			else											//���һ����û����ֻ��һ����
			{
				pGraph->plotHandle=PlotXY(hGraphPanel, control, (pGraph->pCurveArray + plotCurveIndex)->pDotXPlot, (pGraph->pCurveArray + plotCurveIndex)->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT,
									pGraph->pCurveArray->pCurveAttr->plotStyle,
									pGraph->pCurveArray->pCurveAttr->pointStyle,
									pGraph->pCurveArray->pCurveAttr->lineStyle, 1,
									pGraph->pCurveArray->pCurveAttr->lineColor);
			}
			(pGraph->pCurveArray + plotCurveIndex)->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
			(pGraph->pCurveArray + plotCurveIndex)->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
			(pGraph->pCurveArray + plotCurveIndex)->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
			(pGraph->pCurveArray + plotCurveIndex)->numOfDotsToPlot-=numOfDotsToPlot;	//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
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
	int numOfDotsToPlot=pGraph2->pCurveArray->numOfDotsToPlot;							//��ֹ�ж϶�ȥд���������
	
	if(pGraph2->pCurveArray->numOfPlotDots >=1 )	//�� �ڶ��� ��
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
				
				pGraph2->pCurveArray->numOfPlotDots+=numOfDotsToPlot;				//��ͼ�ܵ�������
				pGraph2->pCurveArray->pDotXPlot+=numOfDotsToPlot;					//��ͼ��X����ָ�����
				pGraph2->pCurveArray->pDotYPlot+=numOfDotsToPlot;					//��ͼ��Y����ָ�����
				pGraph2->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;				//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
				
				(pGraph2->pCurveArray + 1)->numOfPlotDots+=numOfDotsToPlot;			//��ͼ�ܵ�������
				(pGraph2->pCurveArray + 1)->pDotXPlot+=numOfDotsToPlot;				//��ͼ��X����ָ�����
				(pGraph2->pCurveArray + 1)->pDotYPlot+=numOfDotsToPlot;				//��ͼ��Y����ָ�����
				(pGraph2->pCurveArray + 1)->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
				
				(pGraph2->pCurveArray + 2)->numOfPlotDots+=numOfDotsToPlot;			//��ͼ�ܵ�������
				(pGraph2->pCurveArray + 2)->pDotXPlot+=numOfDotsToPlot;				//��ͼ��X����ָ�����
				(pGraph2->pCurveArray + 2)->pDotYPlot+=numOfDotsToPlot;				//��ͼ��Y����ָ�����
				(pGraph2->pCurveArray + 2)->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
			}
    }
	else //����һ����
	{
			if(numOfDotsToPlot>0)																//�������Ҫ��ͼ�ĵ�
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
				pGraph2->pCurveArray->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
				pGraph2->pCurveArray->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
				pGraph2->pCurveArray->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
				pGraph2->pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
				
				(pGraph2->pCurveArray + 1)->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
				(pGraph2->pCurveArray + 1)->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
				(pGraph2->pCurveArray + 1)->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
				(pGraph2->pCurveArray + 1)->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
				
				(pGraph2->pCurveArray + 2)->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
				(pGraph2->pCurveArray + 2)->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
				(pGraph2->pCurveArray + 2)->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
				(pGraph2->pCurveArray + 2)->numOfDotsToPlot-=numOfDotsToPlot;		//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
			}
	}
	if(pGraph2->plotHandle<0)
		return -1;
	else
		return 0;
}

void DisplayEnvtGraph()
{

	DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH2, -1, VAL_IMMEDIATE_DRAW);	//�����������������ͼ�е���������
	 
	GetCtrlVal(hEnvResultPanel,ENVIRPANEL_TEMP_BOX,&temp_flag);		//Ȼ���ȡ�û�Ҫѡ�е�����
	GetCtrlVal(hEnvResultPanel,ENVIRPANEL_HUM_BOX,&humidity_flag); 
	GetCtrlVal(hEnvResultPanel,ENVIRPANEL_PRESS_BOX,&pressure_flag);
	
	//
	GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR1, &graph2tempclr);
	GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR2, &graph2humclr);
	GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR3, &graph2preclr);

	if((temp_flag == 1)&&((Graph2.pCurveArray  + 1)->numOfPlotDots>0))  
	{
		
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text����ɫ(��canvas��ɫ��ͬ)
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"Temperature"��ɫ
		CanvasDrawText (hGraphPanel, GRAPHDISP_CANVAS, "T",VAL_APP_META_FONT,MakeRect(40,15,15,70), VAL_CENTER);	                            //д"Temperature"
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR,graph2tempclr); 			    //Temperatureͼ��
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //�ߵĿ��
		CanvasDrawLine (hGraphPanel, GRAPHDISP_CANVAS, MakePoint (110,47), MakePoint (150, 47));		//canvas����
																				   
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
		
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text����ɫ(��canvas��ɫ��ͬ)
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"humidity"��ɫ
		CanvasDrawText (hGraphPanel, GRAPHDISP_CANVAS, "H",VAL_APP_META_FONT,MakeRect(60,15,15,70), VAL_CENTER);	                            //д"humidity"
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, graph2humclr);   		    //humidityͼ��
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //�ߵĿ��
		CanvasDrawLine (hGraphPanel, GRAPHDISP_CANVAS, MakePoint (110, 67), MakePoint (150, 67));		//canvas����

		
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
		
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);    //text����ɫ(��canvas��ɫ��ͬ)
	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);		 //"pressure"��ɫ
	    CanvasDrawText (hGraphPanel, GRAPHDISP_CANVAS, "P",VAL_APP_META_FONT,MakeRect(80,15,15,70), VAL_CENTER);	                            //д"pressure"
	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_COLOR,graph2preclr);   		    //pressureͼ��
	    SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_PEN_WIDTH, 2);			        //�ߵĿ��
	    CanvasDrawLine (hGraphPanel, GRAPHDISP_CANVAS, MakePoint (110, 87), MakePoint (150, 87));		//canvas����
		
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
	

