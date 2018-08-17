//==============================================================================
//
// Title:		Curve.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/12 at 15:27:18 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Curve_H__
#define __Curve_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int pointStyle;			//����ʽ
	int plotStyle;			//��ͼ��ʽ
	int lineStyle;			//������ʽ
	int lineColor;
}CurveAttrTypeDef;
		
typedef struct
{
	int curveIndex;									//��������
	int numOfTotalDots;								//���ۼ����ܵ���
	int numOfPlotDots;								//�ѻ�������
	int numOfDotsToPlot;							//��Ҫ��������
	float time;										//ʱ��
	float* pDotXHead;								//��X���������׵�ַ   
	float* pDotYHead;								//��Y���������׵�ַ  
	float* pDotX;									//��ǰ���յ�X�����ַ
	float* pDotY;									//��ǰ���յ�Y�����ַ
	float* pDotXPlot;								//��ǰ���ߵ�X����
	float* pDotYPlot;								//��ǰ���ߵ�Y����
	float Current;  //���յ���ֵ
	CurveAttrTypeDef* pCurveAttr;
}CurveTypeDef;

typedef struct
{
	float x;										//x on X-Axis
	float y;										//y on Y-Axis
}DotTypeDef;
//==============================================================================
// External variables

//==============================================================================
// Global functions

int curveInit(CurveTypeDef* pCurve, int curveIndex, int numOfTotalDots, CurveAttrTypeDef* pCurveAttr);
int curveDeinit(CurveTypeDef* pCurve);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Curve_H__ */
