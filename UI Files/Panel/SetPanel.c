#include <userint.h>
#include "MainPanel.h"

#include "LoadPanel.h"
#define VAL_TEXTBG                        0xF0F0F0L    //未被选中背景色
#define VAL_TEXTBG_PRESSED                0x065279L    //被选中背景色


int CVICALLBACK EnvBtnCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			SetPanelPos(ENVTPanel, 3 , 170);
			SetPanelSize(ENVTPanel, 350, 650);
			DisplayPanel(ENVTPanel); 
			
			HidePanel (GRAPHPanel);
			HidePanel (ABOUTPanel); 
			
			SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment背景色
	     	SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment文本颜色
			
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph背景色
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph文本颜色
			
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about背景色
	     	SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about文本颜色
																								 
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
			
			SetPanelPos(GRAPHPanel, 5, 170);
			SetPanelSize(GRAPHPanel, 350, 650);
			DisplayPanel(GRAPHPanel);
			
			HidePanel (ENVTPanel); 
			HidePanel (ABOUTPanel);
			
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //graph背景色
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //graph文本颜色
			
			SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
	     	SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //about背景色
	     	SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //about文本颜色

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
			 
			SetPanelPos(ABOUTPanel, 5, 170);
			SetPanelSize(ABOUTPanel, 350, 650);
			DisplayPanel(ABOUTPanel);
			
		    HidePanel (ENVTPanel); 
			HidePanel (GRAPHPanel);
		
			
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //about背景色
	     	SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //about文本颜色
			
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //graph背景色
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //graph文本颜色
			
			SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
	     	SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			break;

	}
	return 0;
}


int CVICALLBACK CancelCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			 	RemovePopup(setPanel);   
			break;
	}
	return 0;
}

//本地工作目录
char projectSavePath[512];

int CVICALLBACK ProCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			/*if(FileSelectPopup ("E:\\GitWorkplace\\Sinoagg\\Software\\SA6101_Software\\", ".", "*.*", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 0, projectSavePath)>0)
			{
				SetCtrlVal(panel, ENVT_PROPATH, projectSavePath);
			}*/
			if(DirSelectPopup ("E:\\GitWorkplace\\Sinoagg\\Software\\", "Select Directory", 1, 1, projectSavePath)>0)     
			{
			 SetCtrlVal(panel, ENVT_PROPATH, projectSavePath); 
			}
			else 
			{
				return -1;
			}
			break;
	}
	return 0;
}

