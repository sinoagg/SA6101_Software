//==============================================================================
//
// Title:		Cgs_mt.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/31 at 15:52:21 by 斌 何.
// Copyright:	内蒙古民族大学. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "asynctmr.h"
#include "protocol.h"
#include "Plot.h"
#include <rs232.h>
#include "Cgs_mt.h"
#include "Graph.h"
#include "LoadPanel.h"

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
unsigned char meas_CGS_UartTxBuf[8] = {0x11,0x03,0x00,0x02,0x00,0x05,0x26,0x99};  //读取温控板数据命令

unsigned char meas_CGS_UartRxBuf[500];
GraphTypeDef Graph_Temp;  


//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?

//
void Read_CGS_Value(unsigned char comSelect)
{
	
   	ComWrt(comSelect, (const char*)meas_CGS_UartTxBuf, 8);
	
}
void ProtocolGet_CGS_Data(unsigned char* meas_CGS_UartRxBuf, Rx_CGS_DataTypeDef* Rx_CGS_Data)	//Get data from UART Rx Buffer
{
	
		Rx_CGS_Data->rxDevAddr = *meas_CGS_UartRxBuf;	   																						//地址
		
		Rx_CGS_Data->pressure = pow(10, (0.778*( ((*(meas_CGS_UartRxBuf+3) << 8)|(*(meas_CGS_UartRxBuf+4))) /1000.0 - 3.575)));  				//压力值
		
		if(*(meas_CGS_UartRxBuf+5) == 0xff)
		{
			Rx_CGS_Data->heating_stage_temp = ((int)(*(meas_CGS_UartRxBuf+5) << 8)|(*(meas_CGS_UartRxBuf+6))) - 65536; 							//热台温度  
		}
		else
		{
			Rx_CGS_Data->heating_stage_temp = (int)(*(meas_CGS_UartRxBuf+5) << 8)|(*(meas_CGS_UartRxBuf+6)); 									//热台温度
		}
		
		Rx_CGS_Data->Evaporation_temp = (unsigned int)(*(meas_CGS_UartRxBuf+7) << 8)|(*(meas_CGS_UartRxBuf+8)); 								//蒸发温度
		
		Rx_CGS_Data->humidity = (unsigned int)(*(meas_CGS_UartRxBuf+9) << 8)|(*(meas_CGS_UartRxBuf+10));  						//环境湿度
		
		
		if(*(meas_CGS_UartRxBuf+11) == 0xff)
		{
			Rx_CGS_Data->environment_temp = (int)(*(meas_CGS_UartRxBuf+11) << 8)|(*(meas_CGS_UartRxBuf+12)) - 65536;							//环境温度 	
		}
		else
		{
			Rx_CGS_Data->environment_temp = (int)(*(meas_CGS_UartRxBuf+11) << 8)|(*(meas_CGS_UartRxBuf+12));									//环境温度 	
		}
		
}






