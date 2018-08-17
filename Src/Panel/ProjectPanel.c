#include <ansi_c.h>
#include "Result Menu.h"
#include <userint.h>
#include "Project.h"
#include "LoadPanel.h"
#include "MainPanelCb.h"

#define CHANGECOLOR 0x94CEFF //浅蓝
#define BGCOLOR 	0xFFFFFF
#define COLOR  		0x065279 //深蓝
#define SEARCHCOLOR 0xA8BFCB //不可用颜色

int selectedPrjIndex=0;			//当前选中的项目序号
int selectPanel;   				//当前选中项目面板的句柄值
static void DiscardAllPrjPanel(PrjHandleTypeDef *pSingleProject)
{
	int i=0;
	while((pSingleProject+i)->index != -1)
	{
		DiscardPanel((pSingleProject+i)->hSinglePrjPanel);
		i++;
	}	 
}

static int RecallAllPanelState(char* pConfigSavePath)
{
	RecallPanelState(IdVdPanel.panelHandle, pConfigSavePath, 1);						
	RecallPanelState(IdVgPanel.panelHandle, pConfigSavePath, 2);						
	RecallPanelState(hIT_Panel, pConfigSavePath, 3);
	RecallPanelState(hRT_Panel, pConfigSavePath, 4);
	RecallPanelState(hIV_Panel, pConfigSavePath, 5);
	RecallPanelState(hIdtPanel, pConfigSavePath, 6);
	RecallPanelState(hBasicSamplePanel, pConfigSavePath, 10);
	RecallPanelState(hAdvanceSamplePanel, pConfigSavePath, 11);
	RecallPanelState(hEnvCfgPanel, pConfigSavePath, 14);
	RecallPanelState(hSettingsPrjPanel, pConfigSavePath, 15);
	RecallPanelState(hSettingsGraphPanel, pConfigSavePath, 16);
	return 0;
}

int CVICALLBACK TXT_OpenPrjCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			RecallAllPanelState(pFileLable[selectedPrjIndex]->pFileName);//load all panel and other parameters
			DiscardAllPrjPanel(SingleProject);
			RemovePopup (hPrjPanel);
			break;
	}
	return 0;
}

int CVICALLBACK PIC_OpenPrjCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			RecallAllPanelState(pFileLable[selectedPrjIndex]->pFileName);//load all panel and other parameters
			DiscardAllPrjPanel(SingleProject);
			RemovePopup (hPrjPanel);
			break;
	}
	return 0;
}

int CVICALLBACK TXT_ExitPrjCallback (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK)
	{
		DiscardAllPrjPanel(SingleProject);
		RemovePopup (hPrjPanel);  
	}
	return 0;
}

int CVICALLBACK PIC_ExitPrjCallback (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK)
	{
		DiscardAllPrjPanel(SingleProject);
		RemovePopup (hPrjPanel);  
	}
	return 0;
}

static void SelectProject(int panel, int select)
{
	
	selectPanel=GetActivePanel(); //获得当前选中项目面板的句柄值 
	if(select)
	{
		
		SetPanelAttribute(panel, ATTR_BACKCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DATE, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_TIME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, COLOR);	
	}
	else
	{
		SetPanelAttribute(panel, ATTR_BACKCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DATE, ATTR_TEXT_BGCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_TIME, ATTR_TEXT_BGCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, BGCOLOR);
	}
}

static char GetPanelIndex(int panel)
{
	int top;
	GetPanelAttribute(panel, ATTR_TOP, &top);
	return (char)((top)/117);								//减去偏置，除以单个高度
}

int CVICALLBACK PrjSelectCallback (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelAttribute(panel, ATTR_BACKCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_DATE, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_TIME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);

			SetCtrlAttribute (hPrjPanel, PROPANEL_PIC_OPENPRJ, ATTR_DIMMED, 0);
			SetCtrlAttribute (hPrjPanel, PROPANEL_TXT_OPENPRJ, ATTR_DIMMED, 0);
			SetCtrlAttribute (hPrjPanel, PROPANEL_TXT_OPENPRJ , ATTR_TEXT_BGCOLOR,COLOR ); 
			
			SelectProject(panel, 1);
			selectedPrjIndex=GetPanelIndex(panel);
			int i=0;		 
			while(SingleProject[i].index!=-1)
			{
				if(i!=selectedPrjIndex)
					SelectProject(SingleProject[i].hSinglePrjPanel, 0);
				i++;
			}
			break;
	}
	return 0;
}



int CVICALLBACK SearchCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			if(selectPanel)	
				SelectProject(selectPanel,0);				//取消当前选中状态  
			else
			{
				SetPanelAttribute(hPrjListPanel, ATTR_BACKCOLOR, BGCOLOR); 
				SetCtrlAttribute (hPrjPanel,PROPANEL_PIC_OPENPRJ , ATTR_DIMMED, 1);
				SetCtrlAttribute (hPrjPanel,PROPANEL_TXT_OPENPRJ , ATTR_TEXT_BGCOLOR,SEARCHCOLOR );
				SetCtrlAttribute (hPrjPanel,PROPANEL_TXT_OPENPRJ , ATTR_DIMMED, 1); 
			break;
			}
		
	}
	return 0;
}

int CVICALLBACK PrjPanelCallback (int panel, int event, void *callbackData,
								  int eventData1, int eventData2)
{
	switch (event)
	{
	
		case EVENT_CLOSE:										   
			RemovePopup(hPrjPanel);
			break;
	}
	return 0;
}
