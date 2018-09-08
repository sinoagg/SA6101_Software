//==============================================================================
//
// Title:		AbnormalDataCache.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/8/28 at 10:40:52 by Ma Hongwei.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "AbnormalDataCache.h"
//==============================================================================
// Constants

//==============================================================================
// Types
#define MAX_PATHNAME_LEN  512
#define MAX_FILENAME_LEN  512
//==============================================================================
// Static global variables
static CAObjHandle  applicationHandle;
static CAObjHandle  workbookHandle;
static CAObjHandle  worksheetHandle;
//==============================================================================
// Static functions

//==============================================================================
// Global variables
char ExcelPathName[MAX_PATHNAME_LEN] = {0};
char ExcelFileName[MAX_FILENAME_LEN] = {0};
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int LaunchExcelCB ()
{   
	HRESULT hrStatus;
	int LaunchError = ExcelRpt_ApplicationNew(0, &applicationHandle);  //启动一个新的Excel应用程序实例 1显示 0隐藏
	if (LaunchError<0)
	{
		MessagePopup ("Excel", "Excel error");
		return -1;
	}
	GetProjectDir (ExcelPathName);  								 //得到Project当前目录名
	MakePathname (ExcelPathName, "abnormalDataCache", ExcelFileName);
	hrStatus = ExcelRpt_WorkbookOpen (applicationHandle, ExcelFileName, &workbookHandle);
	if(hrStatus < 0)
		ExcelRpt_WorkbookNew (applicationHandle, &workbookHandle);
	//ExcelRpt_WorkbookOpen (applicationHandle, ExcelFileName, &workbookHandle);
	return 0; 
}

int ShutDownExcelCB()
{
	ExcelRpt_ApplicationQuit (applicationHandle);
	CA_DiscardObjHandle (worksheetHandle);  
	CA_DiscardObjHandle (workbookHandle);
	CA_DiscardObjHandle (applicationHandle);
	return 0;
}

int ShowAndOpenExcelCB()
{
	ExcelRpt_SetApplicationAttribute (applicationHandle, ER_AP_ATTR_VISIBLE, ExRConst_True);
	ExcelRpt_WorkbookOpen (applicationHandle, ExcelFileName, &workbookHandle);
	return 0;
}

int SaveExcelCB(int panel, int control, char cellRange[])
{   
	ExcelRpt_GetWorksheetFromIndex (workbookHandle, 1, &worksheetHandle); 
	ExcelRpt_ActivateWorksheet (worksheetHandle);
	ExcelRpt_WriteDataFromTableControl (worksheetHandle, cellRange, panel, control);//将数据从CVI表控件中写到Excel中的单元范围
	ExcelRpt_WorkbookClose (workbookHandle, 1);
	ExcelRpt_ApplicationQuit (applicationHandle);
	/*CA_DiscardObjHandle (applicationHandle);*/
	return 0;
}
