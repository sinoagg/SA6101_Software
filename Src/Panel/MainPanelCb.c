#include <rs232.h>
#include "MainPanel.h"

//==============================================================================
//
// Title:		MainPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 15:58:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <utility.h>
#include <formatio.h>
#include "asynctmr.h"
#include "MainPanelCb.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "LoadPanel.h"
#include "Protocol.h"
#include "Timer.h"
#include "SampleCfgPanel.h"
#include "main.h"
#include "ResultMenuPanel.h"
#include "SettingsPanel.h"
#include "File.h"
#include "TablePanel.h"

//==============================================================================
// Constants
#define VAL_TEXTBG                        0xF0F0F0L    //未被选中背景色
#define VAL_TEXTBG_PRESSED                0x065279L    //被选中背景色
#define TWO_TERMINAL 0
#define EXP_I_T 1
#define EXP_R_T 2
#define EXP_I_V 3
#define FOUR_TERMINAL 4
#define EXP_ID_VDS 5
#define EXP_ID_VGS 6
#define EXP_ID_T 7

//==============================================================================
// Types
 GraphTypeDef* pGraph;   
//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int TimerID;
char configSavePath[512]={0};
FileLableTypeDef *pFileLable[64];									//存所有FileLable的指针，最多只能加载一个文件夹下的64个文件
PrjHandleTypeDef SingleProject[64];	

char table_title_IdVd[11][20] ={"Vd(mV)","Id(A)"};
char table_title_IdVg[11][20] ={"Vg(mV)","Id(A)"};
char table_title_IT[11][20] ={"t(ms)","I(mA)"};
char table_title_RT[11][20] ={"t(ms)","R(Ω)"};
char table_title_IV[11][20] ={"V(mV)","I(mA)"};
char table_title_Idt[11][20] ={"t(ms)","Id(A)"}; 

//==============================================================================
// Global functions
static void InitSingleProject(PrjHandleTypeDef *pSingleProject)
{
	int i;
	for(i=0;i<64;i++)
	{
		(pSingleProject+i)->index=-1;	
	}
}

int CVICALLBACK MAIN_PANEL_Callback (int panel, int event, void *callbackData,
									 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			   	QuitUserInterface(0); 
			break;
	}
	return 0;
}


int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
		    SetPanelPos(hResultMenuPanel, 105, 305);  
	     	SetPanelSize(hResultMenuPanel, 65, 1293);      
 			DisplayPanel(hResultMenuPanel);  
			
			SetPanelPos(hGraphPanel, 172, 305);  
	     	SetPanelSize(hGraphPanel, 833, 1293);
			SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 680);
			SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
 			DisplayPanel(hGraphPanel);
		   
			SetPanelPos(hResultDispPanel, 105, 1600);
			SetPanelSize(hResultDispPanel, 449, 300);
			DisplayPanel(hResultDispPanel);
			SetCtrlAttribute(hResultDispPanel, RESULTDISP_SAMPLETIME,ATTR_VISIBLE,0);
			SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME,ATTR_VISIBLE,0);
			SetCtrlAttribute(hResultDispPanel, RESULTDISP_TIME_UNIT,ATTR_VISIBLE,0);
			SetPanelPos(hEnvResultPanel, 556, 1600);
			SetPanelSize(hEnvResultPanel, 449, 300);
			DisplayPanel(hEnvResultPanel);
				    
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);//当鼠标释放时         //禁用 开始按钮      
		    SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       //恢复 停止按钮
	        SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        //禁用 保存按钮
			DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1, -1, VAL_IMMEDIATE_DRAW); //清空曲线图上的所有曲线 
			
			FlushInQ(measureComPort);	   														//Clear input and output buffer,在测试开始之前还应该清楚一次
			FlushOutQ(measureComPort);
		
			int expType;
			int graphIndex=1;	//currently only deal with one graph circumstance
			int numOfCurve=1;
			int numOfDots=500;
		
			if(GetCtrlVal(hExpListPanel, EXP_LIST_TREE, &expType)<0)
				return -1; 
			TestPara.testMode=(enum TestMode)expType;
			ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf);		//send config to instrument via UART 
 			Table_ATTR.column = 2 ;   		//列数
			Table_ATTR.column_width = 290;  //列宽
			DeleteTableRows (hTablePanel, TABLE_DISTABLE, 1, -1); 		
	 		DeleteTableColumns (hTablePanel, TABLE_DISTABLE, 1, -1);	   	//每个实验运行之前清除上一个实验的table数据 
			int MaxRow;  
			
			
			switch(TestPara.testMode)
			{
			    
				case SWEEP_DRAIN_VOL:				 
					DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1,-1 , VAL_IMMEDIATE_DRAW); 
					

					Table_init(table_title_IdVd, Table_ATTR.column, Table_ATTR.column_width );
					GetNumTableRows(hTablePanel,TABLE_DISTABLE,&MaxRow);
					if(TestPara.gateOutputMode==VOL_BIAS)
					{
						numOfCurve=1;
					}
					else if(TestPara.gateOutputMode==VOL_STEP)
					{
						numOfCurve=abs(TestPara.VgStart-TestPara.VgStop)/TestPara.VgStep+1; 
					}
					numOfDots=abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1; 
					GraphInit(hGraphPanel, graphIndex, numOfCurve, numOfDots, &Graph1); 	//graph set up    
				    Graph1.pGraphAttr->xAxisHead=TestPara.VdStart;
					Graph1.pGraphAttr->xAxisTail=TestPara.VdStop; 
					Graph1.pGraphAttr->yAxisHead=0;
					Graph1.pGraphAttr->yAxisTail=2e-1;   
					SetCtrlAttribute(hGraphPanel, GRAPHDISP_GRAPH1, ATTR_ENABLE_ZOOM_AND_PAN, 1 );
					//SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead, Graph1.pGraphAttr->yAxisTail);//设置 X 轴的范围
				   	SetAxisScalingMode(hGraphPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead, Graph1.pGraphAttr->xAxisTail);//设置 X 轴的范围
					SetCtrlAttribute(hTablePanel,TABLE_DISTABLE,ATTR_FIRST_VISIBLE_ROW,MaxRow);//超出tanle高度后显示总能显示最后一行数据 
					break;
				case SWEEP_GATE_VOL:
				/*	GetIdVgCfg (IdVgPanel);
					numOfCurve=abs(IdVgCfg.cfgVdstart-IdVgCfg.cfgVdstop)/IdVgCfg.cfgVdstep;
					numOfDots=abs(IdVgCfg.cfgVgstart-IdVgCfg.cfgVgstop)/IdVgCfg.cfgVgstep;*/
					DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1,-1 , VAL_IMMEDIATE_DRAW);
					Table_init(table_title_IdVg, Table_ATTR.column, Table_ATTR.column_width );
		      		if(TestPara.drainOutputMode==VOL_BIAS)
					{
						numOfCurve=1;
					}else if(TestPara.drainOutputMode==VOL_STEP)
					{
						numOfCurve = abs(TestPara.VdStart-TestPara.VdStop)/TestPara.VdStep+1; //曲线
					}
					numOfDots = abs(TestPara.VgStart-TestPara.VgStop)/TestPara.VgStep+1;	  //点数
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
					Graph1.pGraphAttr->xAxisHead = TestPara.VgStart;
				    Graph1.pGraphAttr->xAxisTail = TestPara.VgStop;
					SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH1,ATTR_ENABLE_ZOOM_AND_PAN,1);//使能控件的缩放和拖动
					//SetAxisScalingMode(int PanelHandle,int ControlID,int Axis(变化轴),int AxisScaling(轴缩放模式),double min,double max);	//设置缩放模式和图形轴的范围或缩放模式以及条形图的X,Y轴范
					SetAxisScalingMode(hGraphPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
					 
					break;
				case NO_SWEEP_IT: 
					DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1,-1 , VAL_IMMEDIATE_DRAW);
					Table_init(table_title_IT, Table_ATTR.column, Table_ATTR.column_width ); 
					numOfDots=(TestPara.runTime*1000)/TestPara.timeStep;
					GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
					Graph1.pGraphAttr->xAxisHead=0;
					Graph1.pGraphAttr->xAxisTail=TestPara.runTime;
					SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH1,ATTR_ENABLE_ZOOM_AND_PAN,1);//使能控件的缩放和拖动
					SetAxisScalingMode(hGraphPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);//设置缩放模式和图形轴的范围或缩放模式以及条形图的X,Y轴范围  
					break;
				case  NO_SWEEP_RT:
				 	 DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1,-1 , VAL_IMMEDIATE_DRAW);
					 Table_init(table_title_RT, Table_ATTR.column, Table_ATTR.column_width ); 
					 numOfDots=TestPara.runTime*1000/TestPara.timeStep ;
					 GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
					 Graph1.pGraphAttr->xAxisHead=0;
					 Graph1.pGraphAttr->xAxisTail=TestPara.runTime;
					 SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH1,ATTR_ENABLE_ZOOM_AND_PAN,1);//使能控件的缩放和拖动
					 SetAxisScalingMode(hGraphPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);//设置缩放模式和图形轴的范围或缩放模式以及条形图的Y轴范
					break;
				case SWEEP_IV:
					 DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1,-1 , VAL_IMMEDIATE_DRAW);
					 Table_init(table_title_IV, Table_ATTR.column, Table_ATTR.column_width ); 
					 numOfDots = abs(TestPara.VgStart-TestPara.VgStop)/TestPara.VgStep+1;
					 GraphInit(hGraphPanel, graphIndex,numOfCurve,numOfDots,&Graph1);
					 Graph1.pGraphAttr->xAxisHead=TestPara.VgStart;
					 Graph1.pGraphAttr->xAxisTail=TestPara.VgStop;
					 SetCtrlAttribute(hGraphPanel,GRAPHDISP_GRAPH1,ATTR_ENABLE_ZOOM_AND_PAN,1);
					 SetAxisScalingMode(hGraphPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail);
				
					break;
			/*	case ID_T:
					 DeleteGraphPlot (hGraphPanel, GRAPHDISP_GRAPH1,-1 , VAL_IMMEDIATE_DRAW);
					 Table_init(table_title_Idt, Table_ATTR.column, Table_ATTR.column_width );  
					 printf("%c","fgff");
					break;*/
				default:
					break;
			}	
			GraphInit(hGraphPanel,graphIndex, 3, numOfDots, &Graph2);   
			Delay(0.2);
			ProtocolRun(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send RUN command to instrument via UART
			double temp=((double)TestPara.timeStep)/1000;
			if(temp<0.05) temp=0.05;
			TimerID = NewAsyncTimer(temp, -1, 1, TimerCallback, 0);		//Create Asynchronous (Timer time interval according to sample interval, continue generating evernt, enabled, callback function name, passing no pointer)
			break;
	}
	return 0;
}

int CVICALLBACK StopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时
			DiscardAsyncTimer(TimerID);
			ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send RUN command to instrument via UART 
			FlushInQ(measureComPort);	   														//Clear input and output buffer,在测试开始之前还应该清楚一次
			FlushOutQ(measureComPort);
		  	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //禁用 停止按钮      
		    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //恢复 开始按钮
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //恢复 保存按钮
			break;
	}
	return 0;
}

int CVICALLBACK SaveCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时
			DisplayImageFile (hMainPanel, MAIN_PANEL_SAVE, "Resource\\Save_pressed.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_SAVE, "Resource\\Save.ico");
			if(FileSelectPopupEx("C:\\SINOAGG\\SA6101\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1,  configSavePath)>0)
				SaveConfigToFile(configSavePath);
			break;
	}
	return 0;
}

int CVICALLBACK SelectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //当Select被鼠标左键点击时,Select图标改变，其它两个正常状态 
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select_pressed.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");

	 		SetPanelPos(IdVgPanel.panelHandle, 104, 305);
	        SetPanelSize(IdVgPanel.panelHandle, 901, 1293);
	        DisplayPanel(IdVgPanel.panelHandle);

			HidePanel(hBasicSamplePanel);	 
			HidePanel(hResultDispPanel);
			HidePanel(hEnvResultPanel);
			HidePanel(hEnvCfgPanel);
			HidePanel(hResultDispPanel);  
			break;
	}
	return 0;
}

//===================================================
//   Configure_Callback
int CVICALLBACK ConfigureCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK_UP:			    //当Configure被鼠标左键点击时,Configure图标改变，其它两个正常状态 
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure_pressed.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
		
			//点击Configure图标回到Id_vds界面
			SetPanelPos(IdVgPanel.panelHandle, 104, 305);
			SetPanelSize(IdVgPanel.panelHandle, 901, 1293);
			DisplayPanel(IdVgPanel.panelHandle);
			
			SetPanelPos(hBasicSamplePanel, 105, 1600);
			SetPanelSize(hBasicSamplePanel, 449, 300);
			DisplayPanel(hBasicSamplePanel);
			
			SetPanelPos(hEnvCfgPanel, 556, 1600);
			SetPanelSize(hEnvCfgPanel, 449, 300);
			DisplayPanel(hEnvCfgPanel);
			break;
	}
	return 0;
}

static void DispResultMenu(void)
{
	SetPanelPos(hResultMenuPanel, 105, 305);  
 	SetPanelSize(hResultMenuPanel, 65, 1293);      
	DisplayPanel(hResultMenuPanel);
}

static void DispResultNumber(void)
{
	SetPanelPos(hResultDispPanel, 105, 1600);
	SetPanelSize(hResultDispPanel, 449, 300);
	DisplayPanel(hResultDispPanel);
}
static void DispRuntime(int display)
{ 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_SAMPLETIME,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TIME,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TIME_UNIT,ATTR_VISIBLE,display);

}

static void DispEnvironmentCfg(void)
{
	SetPanelPos(hEnvResultPanel, 556, 1600);
	SetPanelSize(hEnvResultPanel, 449, 300);
	DisplayPanel(hEnvResultPanel);
}

int CVICALLBACK AnalyzeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK_UP:			    //当Analyze被鼠标左键点击时,Analyze图标改变，其它两个正常状态， 
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
			
			DispResultMenu();
			DispResultTableGraph();
			DispResultNumber();

		    DispEnvironmentCfg();
			int index;
			GetActiveTreeItem (hExpListPanel, EXP_LIST_TREE, &index);
			if(index==EXP_I_T||index==EXP_R_T||index==EXP_ID_T)
				DispRuntime(1);
			else 
				DispRuntime(0);
		   	DispEnvironmentCfg();

			break;
	}
	return 0;
}

int CVICALLBACK SettingsCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
	         InstallPopup (hSettingsPanel);    //弹出hSettingsPanel 

			SetPanelPos(hSettingsPrjPanel, 5, 170);
			SetPanelSize(hSettingsPrjPanel, 350, 650);
			DisplayPanel(hSettingsPrjPanel);

			break;
	}
	return 0;
}

static int SaveAllPanelState(char* pConfigSavePath)
{
	SavePanelState(IdVgPanel.panelHandle, pConfigSavePath, 1);						
	SavePanelState(IdVgPanel.panelHandle, pConfigSavePath, 2);						
	SavePanelState(hIT_Panel, pConfigSavePath, 3);
	SavePanelState(hRT_Panel, pConfigSavePath, 4);
	SavePanelState(hBasicSamplePanel, pConfigSavePath, 10);
	SavePanelState(hAdvanceSamplePanel, pConfigSavePath, 11);
	SavePanelState(hEnvCfgPanel, pConfigSavePath, 14);
	SavePanelState(hSettingsPrjPanel, pConfigSavePath, 15);
	SavePanelState(hSettingsGraphPanel, pConfigSavePath, 16);
	return 0;
}

static int SaveConfigToFile(char* pConfigSavePath)
{
	FILE * fp = NULL;							//表示打开的文件
	fp = fopen(pConfigSavePath, "w");
	if(fp == NULL)
	{
		MessagePopup ("Error", "Invalid Path, please select path to save configurations.");
		if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\Users\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, pConfigSavePath)<0)
			return -1;
	}
	else
	{
		int maxCommentSize=255;
		char description[maxCommentSize];
		PromptPopup("Message", "Please enter description for this configuration:", description, maxCommentSize-1);
		//fprintf(fp, "Date:%s	Time:%s\r\n", DateStr(), TimeStr());
		SaveAllPanelState(pConfigSavePath);		//保存所有面板的数据 
		fp = fopen(pConfigSavePath, "a+");
		fprintf(fp, "\r\n%-61s\r\n", description);		//左对齐打满64字符
		fclose(fp);//关闭文件
		
	}
	return 0;
	
}													

static int LoadAndDispPrj(FileLableTypeDef *pFileLable, char index)						//index为prj所在位置排序
{
	int hSinglePrjPanel;
	if ((hSinglePrjPanel = LoadPanel (hPrjListPanel, "Project.uir", DEFPANEL)) < 0)		//load projects panel
		return -1;
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_NAME, pFileLable->FileName);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DATE, pFileLable->FileDate);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_TIME, pFileLable->FileTime);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DESC, pFileLable->FileDesc);
	SetPanelPos(hSinglePrjPanel, index*117, -10);
	SetPanelSize(hSinglePrjPanel, 115, 1425);
	DisplayPanel(hSinglePrjPanel);
	return hSinglePrjPanel;
}

static int LoadAllProject(char* pProjectSavePath)
{
	char tempFileName[512];
	char tempFilePath[512];
	char index=0;
	char tempPathToSearch[512];
	
	InitSingleProject(SingleProject);
	
	sprintf(tempPathToSearch, "%s%s", pProjectSavePath, "\\*.sac");
	if(0==GetFirstFile(tempPathToSearch, 1, 1, 1, 1, 1, 0, tempFileName))		//如果第一个文件获取成功
	{
		sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
		pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
		InitFileLable(pFileLable[index], tempFilePath); 				//读文件时间和文件名称及description，并展示
		SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
		SingleProject[index].index=index;
		index++;
		
		while(GetNextFile(tempFileName)==0)								//如果读取正确，持续读取
		{
			sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
			pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
			InitFileLable(pFileLable[index], tempFilePath); //读文件时间和文件名称及description
			SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
			SingleProject[index].index=index;
			index++;
			
		}
	}
	return 0;
}

int CVICALLBACK ProjectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			SetPanelSize(hPrjPanel,700,1400);
			SetPanelPos(hPrjPanel,150,300);
			InstallPopup (hPrjPanel);
			SetPanelSize(hPrjListPanel,550,1399);
			SetPanelPos(hPrjListPanel,90,0);
			DisplayPanel(hPrjListPanel); 
			
			LoadAllProject(ProjectSavePath);
//<<<<<<< HEAD
//			SetPanelPos(hPrjListPanel, 90, -10);
//			SetPanelSize(hPrjListPanel, 115, 1300);
//			DisplayPanel(hPrjListPanel);
//=======
//>>>>>>> e73900e378028359f1677ade8da974220349c79d
			break;
	}	 
	return 0;
}
