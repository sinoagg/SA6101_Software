#include <userint.h>
#include "MainPanel.h"

#include "LoadPanel.h"
#define VAL_TEXTBG                        0xF0F0F0L    //δ��ѡ�б���ɫ
#define VAL_TEXTBG_PRESSED                0x065279L    //��ѡ�б���ɫ


int CVICALLBACK EnvBtnCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			SetPanelPos(hSettingsPrjPanel, 3 , 170);
			SetPanelSize(hSettingsPrjPanel, 350, 650);
			DisplayPanel(hSettingsPrjPanel); 
			
			HidePanel (hGraphPanel);
			HidePanel (hSettingsAboutPanel); 
			
			SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment�ı���ɫ
			
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
			
			HidePanel (hSettingsPrjPanel); 
			HidePanel (hSettingsAboutPanel);
			
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //graph����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //graph�ı���ɫ
			
			SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment�ı���ɫ
			
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
			
		    HidePanel (hSettingsPrjPanel); 
			HidePanel (hSettingsGraphPanel);
		
			
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //about����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //about�ı���ɫ
			
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //graph����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //graph�ı���ɫ
	
			SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment����ɫ
	     	SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment�ı���ɫ
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
			 	RemovePopup(hSettingsPanel);   
			break;
	}
	return 0;
}

//���ع���Ŀ¼
char projectSavePath[512];

int CVICALLBACK ProCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
		
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

