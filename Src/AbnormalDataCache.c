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
char cellRange[] = "A1:D5";
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
	SetWaitCursor (1);
	int LaunchError = ExcelRpt_ApplicationNew(0, &applicationHandle);  //启动一个新的Excel应用程序实例 1显示 0隐藏
	SetWaitCursor (0);
	if (LaunchError<0)
	{
		MessagePopup ("Excel", "Excel error");
		return -1;
	}
	GetProjectDir (ExcelPathName);   //得到Project当前目录名
	MakePathname (ExcelPathName, "abnormalDataCache", ExcelFileName);
	if (ExcelRpt_WorkbookOpen (applicationHandle, ExcelFileName, &workbookHandle) < 0)
		ExcelRpt_WorkbookNew (applicationHandle, &workbookHandle);
	return 0; 
}

int ShutDownExcelCB()
{
	 ExcelRpt_WorkbookClose (workbookHandle, 1);
	 SetWaitCursor (1);
	 ExcelRpt_ApplicationQuit (applicationHandle);
	 SetWaitCursor (0);
	 return 0;
}

int ShowAndOpenExcelCB()
{
	ExcelRpt_SetApplicationAttribute (applicationHandle, ER_AP_ATTR_VISIBLE, ExRConst_True);
	ExcelRpt_WorkbookOpen (applicationHandle, ExcelFileName, &workbookHandle);
	return 0;
}

int InitExcelCB ()
{
	 ExcelRpt_GetWorksheetFromIndex (workbookHandle, 1, &worksheetHandle);
	 ExcelRpt_WorksheetNew (workbookHandle, 1, &worksheetHandle);//在工作簿中创建一个新的工作表
	 //ExcelRpt_InsertRow (worksheetHandle , -1, numberOfRows);//将新的行插入到工作表中。
	 //ExcelRpt_InsertColumn (worksheetHandle, -1, numberOfColumns);//将新的列插入到工作表中。
	 return 0;
}

int SaveExcelCB(int panel, int control)
{
	ExcelRpt_WriteDataFromTableControl (worksheetHandle, cellRange, panel, control);//将数据从CVI表控件中写到Excel中的单元范围
	ExcelRpt_WorkbookSave (workbookHandle,ExcelFileName,0);
	return 0;
}
