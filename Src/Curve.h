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
	int curveIndex;									//曲线序数
	int numOfTotalDots;								//理论计算总点数
	int numOfPlotDots;								//已画点数量
	int numOfDotsToPlot;							//将要画点数量
	float time;										//时间
	float* pDotXHead;								//点X坐标数组首地址   
	float* pDotYHead;								//点Y坐标数组首地址  
	float* pDotX;									//当前接收点X坐标地址
	float* pDotY;									//当前接收点Y坐标地址
	float* pDotXPlot;								//当前画线点X坐标
	float* pDotYPlot;								//当前画线点Y坐标
}Curve_TypeDef;

typedef struct
{
	float x;										//x on X-Axis
	float y;										//y on Y-Axis
}Dot_TypeDef;
//==============================================================================
// External variables

//==============================================================================
// Global functions

int curveInit(int curveIndex, int numOfDots, Curve_TypeDef* pCurve);
int curveDeinit(Curve_TypeDef* pCurve);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Curve_H__ */
