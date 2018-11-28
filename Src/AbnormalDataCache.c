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
#include <ansi_c.h>
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
char ExcelPathsName[MAX_PATHNAME_LEN] = {0};
char ExcelFileName[MAX_FILENAME_LEN] = {0};
//==============================================================================
// Global functions

int LaunchExcelCBShow ()
{   
	int LaunchError = ExcelRpt_ApplicationNew(1, &applicationHandle);  //����һ���µ�ExcelӦ�ó���ʵ�� 1��ʾ 0����
	if (LaunchError<0)
	{
		MessagePopup ("Excel", "Excel error");
		return -1;
	}
	GetProjectDir (ExcelPathName);//�õ�Project��ǰĿ¼��
	MakePathname (ExcelPathName, "abnormalDataCache", ExcelFileName);
    ExcelRpt_WorkbookOpen (applicationHandle, ExcelFileName, &workbookHandle);
	CA_DiscardObjHandle (worksheetHandle);  
	CA_DiscardObjHandle (workbookHandle);
	CA_DiscardObjHandle (applicationHandle);
	return 0; 
}

int WriteAndSaveExcel(int panelHandle, int controlID)
{
	int i, j;
	int attributeValue;
	int numberOfColumns;
	int numberOfRows;
	double value;
    GetProjectDir (ExcelPathName);//�õ�Project��ǰĿ¼��
	MakePathname (ExcelPathName, "abnormalDataCache.xls", ExcelFileName);
	FILE *fp = NULL;
    fp = fopen(ExcelFileName, "w");
	GetNumTableColumns (panelHandle, controlID, &numberOfColumns);   // ����
	GetNumTableRows (panelHandle, controlID, &numberOfRows);		 //����
	char table_title[3000][20];   
	for(j =1; j<=numberOfColumns; j++)
	{
	   GetTableCellVal (panelHandle, controlID, MakePoint(j,1), table_title[j]);  //��ȡtable_title����	
	   fprintf(fp, "%s\t", table_title[j]);	
	}
	fprintf(fp, "\n");
	
	
	for(i = 2;i<=numberOfRows;i++)	  //+1 
	{
		for(j =1; j<=numberOfColumns; j++)
		{
			GetTableCellAttribute (panelHandle, controlID, MakePoint(j,i),ATTR_CELL_TYPE , &attributeValue);
			if(attributeValue == 0)
			{
				GetTableCellVal (panelHandle, controlID, MakePoint(j,i), &value); //��ȡ����
				fprintf(fp, "%le\t", value);	
			}
			else
			{
				fprintf(fp,"\t");	
			}
		}
		fprintf(fp, "\n"); 
		j = 1;
	}
	fclose(fp);
	return 0;
}

