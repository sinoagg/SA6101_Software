#include <userint.h>
#include "limits.h"
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
// Include files
#include <ansi_c.h>
#include "Curve.h"	  
#include "Protocol.h"
#include "Graph.h"
#include "SettingsPanel.h"
#include"Plot.h"
#include "Cgs_mt.h" 
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
Rx_CGS_DataTypeDef Rx_CGS_Data;  
//==============================================================================
// Global functions
float ohm;

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

 void SetGraphY_Axis(GraphTypeDef* pGraph, float currentY_Val,float ohm)  //curren  tY_ Val ==>Id
{
	 switch(TestPara.testMode)
	{   
		case SWEEP_GATE_VOL: 
		case SWEEP_DRAIN_VOL:
		case SWEEP_IV:
		if((Graph1.pCurveArray+Graph1.plotCurveIndex)->pointsIndex==1)   
		{
			if(currentY_Val >0)				 
			{
				if(currentY_Val >=Graph1.pGraphAttr->yAxisTail )
				{
					Graph1.pGraphAttr->yAxisHead = currentY_Val;
					Graph1.pGraphAttr->yAxisTail =  currentY_Val*1.1;
					SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
				} 		    
				else if(currentY_Val < Graph1.pGraphAttr->yAxisHead)
				{
				    Graph1.pGraphAttr->yAxisHead=currentY_Val;
					 Graph1.pGraphAttr->yAxisTail =  currentY_Val*1.1;  
					SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
				}
			}
		   else if(currentY_Val<0)            
			{
			   if(currentY_Val <= Graph1.pGraphAttr->yAxisHead) //
				{
					Graph1.pGraphAttr->yAxisHead = currentY_Val;
				    Graph1.pGraphAttr->yAxisTail=currentY_Val*0.9; 
				    SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
				}
				else if(currentY_Val > Graph1.pGraphAttr->yAxisTail )
				{

					Graph1.pGraphAttr->yAxisHead=currentY_Val;
					Graph1.pGraphAttr->yAxisTail=currentY_Val*0.9;  
					SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
				}
			}
		}
		else
		{
			if(currentY_Val > 0)
			{
				if(currentY_Val > Graph1.pGraphAttr->yAxisTail )
				{
					Graph1.pGraphAttr->yAxisTail=currentY_Val*1.1;
					SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
				} 		    
				else if(currentY_Val <= Graph1.pGraphAttr->yAxisHead)
				{
				    Graph1.pGraphAttr->yAxisHead=currentY_Val;   //currentY_Val*1.1
					SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
				}
			}
			 else if(currentY_Val<0)            
			{
			   if(currentY_Val <= Graph1.pGraphAttr->yAxisHead) //
				{
					Graph1.pGraphAttr->yAxisHead = currentY_Val;  //currentY_Val*0.9
				    SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
				}
				else if(currentY_Val >Graph1.pGraphAttr->yAxisTail )
				{
					Graph1.pGraphAttr->yAxisTail=currentY_Val*0.9;
					SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
				}
			}
	
        	}
		break;
		case NO_SWEEP_IT:			   //����Ϊ0ֹͣʱ���߻��ϴ�
		case ID_T:
			if(Graph1.pCurveArray->pointsIndex==1)
			{
				if(currentY_Val>0)
				{
					if(currentY_Val >= Graph1.pGraphAttr->yAxisTail )
					{
						Graph1.pGraphAttr->yAxisHead=currentY_Val*0.9999;
						Graph1.pGraphAttr->yAxisTail=currentY_Val*1.0001;   
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(currentY_Val <Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=currentY_Val*0.9999;
						Graph1.pGraphAttr->yAxisTail=currentY_Val*1.0001; 
					    SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
				 }
			    else if(currentY_Val<0)      
				{
				  	if(currentY_Val > Graph1.pGraphAttr->yAxisTail )
					{
						Graph1.pGraphAttr->yAxisTail=currentY_Val*0.9999;
						Graph1.pGraphAttr->yAxisHead=currentY_Val*1.0001;  
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(currentY_Val <= Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=currentY_Val*1.0001;
						Graph1.pGraphAttr->yAxisTail=currentY_Val*0.9999;     
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
			   }
			}
			else
			{
				if(currentY_Val >0)
				{
					if(currentY_Val >= Graph1.pGraphAttr->yAxisTail )
					{
						Graph1.pGraphAttr->yAxisTail=currentY_Val*1.0001;   
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(currentY_Val <Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=currentY_Val*0.9999;
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
				}
				 else if(currentY_Val<0)            
				{
				  	if(currentY_Val >= Graph1.pGraphAttr->yAxisTail )
					{
						Graph1.pGraphAttr->yAxisTail=currentY_Val*0.9999;
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(currentY_Val <Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=currentY_Val*1.0001;
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
				}
			}
			break;
		case NO_SWEEP_RT:
				if(Graph1.pCurveArray->pointsIndex==1)                  
				{  	
					if(ohm>0)
					{
						if(ohm>= Graph1.pGraphAttr->yAxisTail )
						{
							Graph1.pGraphAttr->yAxisTail=ohm*1.1;  //1.01
							Graph1.pGraphAttr->yAxisHead=ohm*0.9;  //0.99
							SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
						} 		    
						else if(ohm < Graph1.pGraphAttr->yAxisHead)
						{																			 
						    Graph1.pGraphAttr->yAxisHead=ohm*0.9;
							Graph1.pGraphAttr->yAxisTail=ohm*1.1; 
							SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
						}
					}
					else 
					{
						 if(ohm>= Graph1.pGraphAttr->yAxisTail )
						{
							Graph1.pGraphAttr->yAxisTail=ohm*0.9;
							Graph1.pGraphAttr->yAxisHead=ohm*1.1;
							SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
						} 		    
						else if(ohm < Graph1.pGraphAttr->yAxisHead)
						{
						    Graph1.pGraphAttr->yAxisHead=ohm*1.1;
							Graph1.pGraphAttr->yAxisTail=ohm*0.9; 
							SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
						}
					}
		   	 }
			 else
			 {
				if(ohm>0)
				{
					if(ohm>= Graph1.pGraphAttr->yAxisTail)
					{
						Graph1.pGraphAttr->yAxisTail=ohm*1.2;   
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(ohm < Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=ohm*0.8;
					    SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
				}
				else
				{
					if(ohm>= Graph1.pGraphAttr->yAxisTail)
					{
						Graph1.pGraphAttr->yAxisTail=ohm*0.8;   
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(ohm < Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=ohm*1.2;
					    SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
					
				}						    
				
			 
			}
		
			break;
	}
}
void SetGraphX_Axis(int graphDispPanel,int controlfloat,GraphTypeDef* pGraph,float reTime)//�������Զ�����  
{
	switch(TestPara.testMode)
	{  
		case NO_SWEEP_IT:
		case NO_SWEEP_RT:
		case ID_T:
    	
			if(pGraph->pGraphAttr->xAxisTail <=reTime) 
				{
					pGraph->pGraphAttr->xAxisTail=reTime*1.1; 
					SetAxisScalingMode(graphDispPanel, controlfloat, VAL_BOTTOM_XAXIS, VAL_MANUAL, pGraph->pGraphAttr->xAxisHead, pGraph->pGraphAttr->xAxisTail);//���� X  ��ķ�Χ
				}
			break;
	  }
}
float max = 0;
float a,b,c;
void SetGraph2_YAxis(int control,GraphTypeDef* pGraph)
{								//*(pGraph->pCurveArray->pDotY) 
	a=Rx_CGS_Data.humidity; 		 			//����ʪ��      
	b= Rx_CGS_Data.heating_stage_temp;				//��̨�¶�     
	c= Rx_CGS_Data.pressure*0.001;				//ѹǿ
	
	  
	max=(a>b?a:b)>(b>c?b:c)?(a>b?a:b):(b>c?b:c);
	if(pGraph->pGraphAttr->yAxisTail <= max)			//�¶�ֵ
	{
		pGraph->pGraphAttr->yAxisTail=pGraph->pGraphAttr->yAxisTail+50;
		SetAxisScalingMode(Graph2.graphHandle,control , VAL_LEFT_YAXIS  , VAL_MANUAL, 0, pGraph->pGraphAttr->yAxisTail);
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
	static int OldX = 0;	  //�ֲ���̬��������X������ֵ 
	static int OldY = 0;	
	switch (event)
	{
		case EVENT_MOUSE_POINTER_MOVE:
			GetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_LEFT, &CtrlLeft);
			GetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_TOP, &CtrlTop);
			GetGlobalMouseState (&panel, &x, &y, &LeftButtonDown, NULL, NULL);	     // ���������λ�á�����������
			if (LeftButtonDown == 1)	  // ������������ʱ
			{
				SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_LEFT, CtrlLeft + (x-OldX) );
				SetCtrlAttribute (panel, GRAPHDISP_CANVAS, ATTR_TOP, CtrlTop + (y-OldY) );
		
				OldX = x;
				OldY = y;				   // ����X��Y ����ֵ�Ե�ǰ��ֵ���� 
			
				if( ( CtrlTop + (y-OldY) )<420)			 //ͼ�����ܳ���graph2�ķ�Χ
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
			OldY = y;					  // ����X������ֵ�Ե�ǰ��ֵ����
			
		break;
	}
	return 0;
}
