#include <userint.h>
#include "LoadPanel.h"
#include "SettingsPanel.h"
#include "Curve.h"

#define VAL_TEXTBG                        0xF0F0F0L    //δ��ѡ�б���ɫ
#define VAL_TEXTBG_PRESSED                0x065279L    //��ѡ�б���ɫ

CurveAttrTypeDef Graph1_CurveAttr1;
CurveAttrTypeDef Graph1_CurveAttr2;
CurveAttrTypeDef Graph1_CurveAttr3;

CurveAttrTypeDef Graph2_CurveAttr1;
CurveAttrTypeDef Graph2_CurveAttr2;
CurveAttrTypeDef Graph2_CurveAttr3;

char ProjectSavePath[512];	   //���ع���Ŀ¼Dir 

CurveAttrTypeDef* GetSettingsCurveAttr(int GraphIndex, int CurveIndex)
{
	CurveAttrTypeDef* pCurveAttr;
	if(GraphIndex==GRAPH1)
	{
		switch(CurveIndex)
		{
			case CURVE1:
				pCurveAttr=&Graph1_CurveAttr1;
				break;
			case CURVE2:
				pCurveAttr=&Graph1_CurveAttr2;
				break;
			case CURVE3:
				pCurveAttr=&Graph1_CurveAttr3;
				break;
			default:
				pCurveAttr=&Graph1_CurveAttr1; 
		}
	}
	else
	{
		switch(CurveIndex%3)
		{
			case CURVE1:
				pCurveAttr=&Graph2_CurveAttr1;
				break;
			case CURVE2:
				pCurveAttr=&Graph2_CurveAttr2;
				break;
			case CURVE3:
				pCurveAttr=&Graph2_CurveAttr3;
				break;
			default:
				pCurveAttr=&Graph2_CurveAttr1; 
		}	
	}
	return pCurveAttr;
}

int CVICALLBACK PrjBtnCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hSettingsPrjPanel, 5, 170);
			SetPanelSize(hSettingsPrjPanel, 350, 650);
			DisplayPanel(hSettingsPrjPanel); 
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about�ı���ɫ
																								 
			break;

	}
	return 0;
}

int CVICALLBACK GraphBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hSettingsGraphPanel, 5, 170);
			SetPanelSize(hSettingsGraphPanel, 350, 650);
			DisplayPanel(hSettingsGraphPanel);
			HidePanel(hSettingsPrjPanel);
			HidePanel(hSettingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //graph����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //graph�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //about����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //about�ı���ɫ
			break;
	}
	return 0;
}

int CVICALLBACK AboutBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hSettingsAboutPanel, 5, 170);
			SetPanelSize(hSettingsAboutPanel, 350, 650);
			DisplayPanel(hSettingsAboutPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsPrjPanel);
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //about����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //about�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //graph����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //graph�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment�ı���ɫ
			break;
	}
	return 0;
}

int CVICALLBACK PrjDirCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
		
			if(DirSelectPopup ("C:\\Sinoagg\\SA6101\\Users", "Select Directory", 1, 1, ProjectSavePath)>0)     
			{
			 	SetCtrlVal(panel, ENVT_PROPATH, ProjectSavePath); 
			}
			else 
			{
				return -1;
			}
			break;
	}
	return 0;
}

int  CVICALLBACK SettingsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			   	RemovePopup(hSettingsPanel);
			break;
	}
	return 0;	
}

