//==============================================================================
//
// Title:		AutoSaveDataPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/10/22 at 16:14:52 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "LoadPanel.h" 
#include "AutoSaveDataPanel.h"
#include "AutoSaveData.h"   
#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include <formatio.h> 
#include "Experiment List.h"
#include "GraphDisp.h" 

//==============================================================================
// Constants

static CAObjHandle applicationHandle ;
static CAObjHandle workbookHandle ;
static CAObjHandle worksheetHandle; 
char autoSavePathName[MAX_PATHNAME_LEN] = {0};
char autoSaveFileName[MAX_PATHNAME_LEN] = {0};
char SavePathName[MAX_PATHNAME_LEN] = {0};
char SaveFileName[MAX_PATHNAME_LEN] = {0};
char excelstr[80]; 
char imgpatn[80];   
//==============================================================================
// Types							  
#define MAX_PATHNAME_LEN 1024
//==============================================================================
// Static global variables
static char expName[10][20] = {"Two","I-t", "R-t", "I-V","Four", "Id-Vds", "Id-Vgs", "Id-t"};   
static int i = 0;    
static int flag = 0;
char AutoDataSavePath[512];
 //==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
//==============================================================================================================================================
void AutoSaveSheetAndGraph()   //自动保存Excel和Jpg文件
{  
	
	if(flag == 0)  
	{
		GetProjectDir (AutoDataSavePath);//得到Project当前目录名 
		sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\Data");
		SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath); //获得选择保存数据路径        
  
	}
	else 
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);  //获得选择保存数据路径 
	//========获得系统时间========
	int month, day, year;
	int hours, minutes, seconds;
	char Datetime[30]; 
	GetSystemDate (&month, &day, &year);
	GetSystemTime (&hours, &minutes, &seconds);
	Fmt(Datetime,"%d[w4p0]%d[w2p0]%d[w2p0]%d[w2p0]%d[w2p0]%d[w2p0]",year,month,day,hours,minutes,seconds);
    //复制并命名新的excel 截取实验图片	
	char saveFileName[MAX_PATHNAME_LEN] = {0};
	char autoSaveXLSFileName[MAX_PATHNAME_LEN] = {0};
	char autoSaveJPGFileName[MAX_PATHNAME_LEN] = {0};
	int index;
	char tempFileName[512];
	char ch;
	GetActiveTreeItem (hExpListPanel, EXP_LIST_TREE, &index); //获得当前点击项目值
	sprintf(tempFileName,"%s%s%d", expName[index], "_test",i+1);
	sprintf(autoSaveXLSFileName ,"%s%s%s%s%s%s",AutoDataSavePath,"\\",tempFileName,"_",Datetime,".xls");                ;
	GetProjectDir (autoSavePathName);//得到Project当前目录名    
	FILE *fpr = NULL;
	FILE *fpw = NULL;
	MakePathname (autoSavePathName,"abnormalDataCache.xls", saveFileName); 
	fpr = fopen(saveFileName, "r");
	fpw = fopen(autoSaveXLSFileName,"w");
	while ((ch=fgetc(fpr))!=EOF)//EOF是文件结束标志
	{
		fputc(ch,fpw);
	}
	fclose(fpr);	 //关闭流，使用完流后记得关闭，避免占用资源   
	fclose(fpw);
	fpr = NULL;
	fpw = NULL;	
	char str[80]; 
	sprintf(str,"%s%s%s%s",tempFileName,"_",Datetime,".xls");
	sprintf(autoSaveJPGFileName,"%s%s%s%s%s%s",AutoDataSavePath,"\\",tempFileName,"_",Datetime,".jpg");         
	char img[80];
	sprintf(img,"%s%s%s%s",tempFileName,"_", Datetime,".jpg");
	SaveGraphs(autoSaveJPGFileName);	
    char item[30];
    sprintf(item,"%s%d","Test ",i+1);
	InsertTreeItem (hAutoSavePanelPanel,AUTOPANEL_AUTOLIST , VAL_SIBLING,0 , VAL_LAST, item, item, 0,-1);
	InsertTreeItem(hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, VAL_CHILD,i*3, VAL_LAST, str, str, 0, 0);
	InsertTreeItem(hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, VAL_CHILD,i*3,VAL_LAST, img, img, 0, 0);
    i++;
}
//==============================================================================================================================================  
void OpenExcelCallbacks(char label[])
{
	int LaunchError; 
	            
	if(flag == 0)  
	{
		GetProjectDir (AutoDataSavePath);//得到Project当前目录名  
		sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\Data"); 
		SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);
	}
	else 
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);  //获得选择保存数据路径      
	 LaunchError=ExcelRpt_ApplicationNew(1, &applicationHandle);
	//if (LaunchError<0)
	//{
	//	MessagePopup ("自动启动Excel错误:", "通过自动接口试图启动Excel发生错误。");
	//}
    sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\");     
	strcat(AutoDataSavePath, label);//字符串连接
	ExcelRpt_WorkbookOpen (applicationHandle, AutoDataSavePath, &workbookHandle); 	//打开该路经下的EXCEL文件     			
	ExcelRpt_GetWorksheetFromIndex (workbookHandle, 1, &worksheetHandle);
	ExcelRpt_ActivateWorksheet (worksheetHandle); //激活该句柄的电子表格sheet
	Delay(0.01);
	CA_DiscardObjHandle(applicationHandle);	
}

 void  DiaplayImgCallbacks (char labels[] )
{
	if(flag == 0)  
	{
		GetProjectDir (AutoDataSavePath);//得到Project当前目录名   
		sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\Data"); 
		SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath); 
	}
	else 
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);    //获得选择保存数据路径 
	sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\");   
	strcat(AutoDataSavePath, labels);//字符串连接
	DisplayImageFile (hImgPanel, IMGPANEL_PICTURE, AutoDataSavePath);         
	SetPanelPos(hImgPanel, 160, 305);  
	//SetPanelSize(hImgPanel,834, 1253);
	InstallPopup(hImgPanel);         

}

int CVICALLBACK ImgCallback (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			 HidePanel(hImgPanel);      
			break;
	}
	return 0;
}

int CVICALLBACK DisplayAutoSaveDataCallback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{	
	int excelValue;
	int imageValue;
	char excel[512]; 
	char images[512]; 
	switch (event)
	{
		case EVENT_LEFT_DOUBLE_CLICK:
			int index;
			GetActiveTreeItem (hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, &index);					//获得当前点击项目值
			if((index+1)%3==0)	   //index为:2、5、8、11、14、17.。。。。
			{
				GetValueFromIndex (hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, index, &imageValue);  
				GetLabelFromIndex (hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, index, images);     
				DiaplayImgCallbacks (images) ;   
			}
			else if ((index+2)%3==0)//index为:1、4、7、10、13、16.。。。。   	   
			{   
				GetValueFromIndex (hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, index, &excelValue);    //由点击的index获得点击的实验名称              
                GetLabelFromIndex (hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, index, excel);
				OpenExcelCallbacks (excel);             
			}
			break;
	}
	return 0;
}

char DataSavePath[512];
int CVICALLBACK AutoSaveCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{   
	GetProjectDir (autoSavePathName);//得到Project当前目录名   
	switch (event)		   
	{													   
		case EVENT_COMMIT:		 															  //Settings面板中选择自动保存路径
			if(DirSelectPopup ("C:\\Users\\", "Select Directory", 1, 1, DataSavePath)>0)
			{
				SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, DataSavePath);
				flag = 1;
			}
			else
			{
				sprintf(autoSavePathName,"%s%s",autoSavePathName,"\\Data"); 				//不选择则默认项目路径下的data路径为数据保存路径
				SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, autoSavePathName);
				return -1;
			}
			break;
		}
	return 0;
}
