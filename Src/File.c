#include <formatio.h>
#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include "Result Menu.h" 

//==============================================================================
//
// Title:		File.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/10 at 18:02:54 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "File.h"

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


//==============================================================================
// Global functions

void InitFileLable(FileLableTypeDef* pFileLable, char* pFileName)
{
	int fileHandle;
	int month, day, year;
	int hours, minutes, seconds;
	pFileLable->pFileName=pFileLable->FileName;
	pFileLable->pFileDate=pFileLable->FileDate;
	pFileLable->pFileTime=pFileLable->FileTime;
	pFileLable->pFileDesc=pFileLable->FileDesc;
	strcpy (pFileLable->pFileName, pFileName);
	//pFileLable->pFileName=pFileName;
	GetFileDate (pFileName, &month, &day, &year);
	sprintf(pFileLable->pFileDate, "%02d/%02d/%4d", month, day, year);
	GetFileTime (pFileName, &hours, &minutes, &seconds);
	sprintf(pFileLable->pFileTime, "%02d:%02d:%02d", hours, minutes, seconds);
	//FILE * fp = NULL;							//表示打开的文件
	fileHandle=OpenFile (pFileName, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	ReadFile (fileHandle, pFileLable->pFileDesc, 63);
	CloseFile (fileHandle);
	//fp = fopen(pFileName, "r");
	//fread (pFileLable->pFileDesc, 64, 64, fp);
	//fclose(fp);//关闭文件  
	
}


