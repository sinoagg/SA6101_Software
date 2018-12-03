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
void AutoSaveSheetAndGraph()   //�Զ�����Excel��Jpg�ļ�
{  
	
	if(flag == 0)  
	{
		GetProjectDir (AutoDataSavePath);//�õ�Project��ǰĿ¼�� 
		sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\Data");
		SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath); //���ѡ�񱣴�����·��        
  
	}
	else 
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);  //���ѡ�񱣴�����·�� 
	//========���ϵͳʱ��========
	int month, day, year;
	int hours, minutes, seconds;
	char Datetime[30]; 
	GetSystemDate (&month, &day, &year);
	GetSystemTime (&hours, &minutes, &seconds);
	Fmt(Datetime,"%d[w4p0]%d[w2p0]%d[w2p0]%d[w2p0]%d[w2p0]%d[w2p0]",year,month,day,hours,minutes,seconds);
    //���Ʋ������µ�excel ��ȡʵ��ͼƬ	
	char saveFileName[MAX_PATHNAME_LEN] = {0};
	char autoSaveXLSFileName[MAX_PATHNAME_LEN] = {0};
	char autoSaveJPGFileName[MAX_PATHNAME_LEN] = {0};
	int index;
	char tempFileName[512];
	char ch;
	GetActiveTreeItem (hExpListPanel, EXP_LIST_TREE, &index); //��õ�ǰ�����Ŀֵ
	sprintf(tempFileName,"%s%s%d", expName[index], "_test",i+1);
	sprintf(autoSaveXLSFileName ,"%s%s%s%s%s%s",AutoDataSavePath,"\\",tempFileName,"_",Datetime,".xls");                ;
	GetProjectDir (autoSavePathName);//�õ�Project��ǰĿ¼��    
	FILE *fpr = NULL;
	FILE *fpw = NULL;
	MakePathname (autoSavePathName,"abnormalDataCache.xls", saveFileName); 
	fpr = fopen(saveFileName, "r");
	fpw = fopen(autoSaveXLSFileName,"w");
	while ((ch=fgetc(fpr))!=EOF)//EOF���ļ�������־
	{
		fputc(ch,fpw);
	}
	fclose(fpr);	 //�ر�����ʹ��������ǵùرգ�����ռ����Դ   
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
		GetProjectDir (AutoDataSavePath);//�õ�Project��ǰĿ¼��  
		sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\Data"); 
		SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);
	}
	else 
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);  //���ѡ�񱣴�����·��      
	 LaunchError=ExcelRpt_ApplicationNew(1, &applicationHandle);
	//if (LaunchError<0)
	//{
	//	MessagePopup ("�Զ�����Excel����:", "ͨ���Զ��ӿ���ͼ����Excel��������");
	//}
    sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\");     
	strcat(AutoDataSavePath, label);//�ַ�������
	ExcelRpt_WorkbookOpen (applicationHandle, AutoDataSavePath, &workbookHandle); 	//�򿪸�·���µ�EXCEL�ļ�     			
	ExcelRpt_GetWorksheetFromIndex (workbookHandle, 1, &worksheetHandle);
	ExcelRpt_ActivateWorksheet (worksheetHandle); //����þ���ĵ��ӱ��sheet
	Delay(0.01);
	CA_DiscardObjHandle(applicationHandle);	
}

 void  DiaplayImgCallbacks (char labels[] )
{
	if(flag == 0)  
	{
		GetProjectDir (AutoDataSavePath);//�õ�Project��ǰĿ¼��   
		sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\Data"); 
		SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath); 
	}
	else 
		GetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, AutoDataSavePath);    //���ѡ�񱣴�����·�� 
	sprintf(AutoDataSavePath,"%s%s",AutoDataSavePath,"\\");   
	strcat(AutoDataSavePath, labels);//�ַ�������
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
			GetActiveTreeItem (hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, &index);					//��õ�ǰ�����Ŀֵ
			if((index+1)%3==0)	   //indexΪ:2��5��8��11��14��17.��������
			{
				GetValueFromIndex (hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, index, &imageValue);  
				GetLabelFromIndex (hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, index, images);     
				DiaplayImgCallbacks (images) ;   
			}
			else if ((index+2)%3==0)//indexΪ:1��4��7��10��13��16.��������   	   
			{   
				GetValueFromIndex (hAutoSavePanelPanel, AUTOPANEL_AUTOLIST, index, &excelValue);    //�ɵ����index��õ����ʵ������              
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
	GetProjectDir (autoSavePathName);//�õ�Project��ǰĿ¼��   
	switch (event)		   
	{													   
		case EVENT_COMMIT:		 															  //Settings�����ѡ���Զ�����·��
			if(DirSelectPopup ("C:\\Users\\", "Select Directory", 1, 1, DataSavePath)>0)
			{
				SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, DataSavePath);
				flag = 1;
			}
			else
			{
				sprintf(autoSavePathName,"%s%s",autoSavePathName,"\\Data"); 				//��ѡ����Ĭ����Ŀ·���µ�data·��Ϊ���ݱ���·��
				SetCtrlVal(hSettingsPrjPanel, ENVT_AUTOSAVEPATH, autoSavePathName);
				return -1;
			}
			break;
		}
	return 0;
}
