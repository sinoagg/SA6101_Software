#include <userint.h>
#include "Project.h"
#include "LoadPanel.h"
#include "MainPanelCb.h"

#define CHANGECOLOR 0x94CEFF//浅蓝
#define BGCOLOR 	0xFFFFFF
#define COLOR  		0x065279//深蓝

static void DiscardAllPrjPanel(PrjHandleTypeDef *pSingleProject)
{
	int i=0;
	while((pSingleProject+i)->index != -1)
	{
		DiscardPanel(pSingleProject->hSinglePrjPanel);
	}
}

int CVICALLBACK OpenPrjCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK ExitPrjCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{	
	
	 if(event==EVENT_COMMIT)
			  RemovePopup (hPrjPanel);  

	return 0;
}


static void SelectProject(int panel, int select)
{
	if(select)
	{
		SetPanelAttribute (panel, ATTR_BACKCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DATE, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_TIME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, COLOR);	
	}
	else
	{
		SetPanelAttribute (panel, ATTR_BACKCOLOR, BGCOLOR);
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
	return (char)((top-90)/117);								//减去偏置，除以单个高度
}

int CVICALLBACK PrjSelectCallback (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
<<<<<<< HEAD
			SetPanelAttribute (panel, ATTR_BACKCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_DATE, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_TIME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
=======
>>>>>>> e73900e378028359f1677ade8da974220349c79d
			SetCtrlAttribute (hPrjPanel,PROPANEL_OPEN , ATTR_DIMMED, 0);
			SelectProject(panel, 1);
			int selectIndex=GetPanelIndex(panel);
			int i=0;
			while(SingleProject[i].index!=-1)
			{
				if(i!=selectIndex)
					SelectProject(SingleProject[i].hSinglePrjPanel, 0);
				i++;
			}
			break;
	}
	return 0;
}

int CVICALLBACK ImgCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	   /*int val;
	   GetCtrlVal(panel,PROPANEL_IMGBOX,&val);
	   if(event == EVENT_VAL_CHANGED){
	   
   			  if(val){
				   SetCtrlAttribute(hPrjListPanel, DEFPANEL_PICS, ATTR_VISIBLE,1);
				  
			  }else{
			  	 SetCtrlAttribute(hPrjListPanel, DEFPANEL_PICS, ATTR_VISIBLE,0);
			  }
   
   }*/
	return 0;
}

int CVICALLBACK DescCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
		 /*int val;
  		 GetCtrlVal(panel,PROPANEL_DESCBOX,&val);
  		 if(event == EVENT_VAL_CHANGED){
	   
   			  if(val){
				  SetCtrlAttribute(hPrjListPanel, DEFPANEL_DESC, ATTR_VISIBLE,1);
				   
			  }else{
			  	  SetCtrlAttribute (hPrjListPanel, DEFPANEL_DESC, ATTR_VISIBLE, 0);
			  }
   
   }*/
	return 0;
}

int CVICALLBACK SearchCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelAttribute (hPrjListPanel, ATTR_BACKCOLOR, BGCOLOR);
			SetCtrlAttribute (hPrjListPanel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (hPrjListPanel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (hPrjListPanel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (hPrjPanel,PROPANEL_OPEN , ATTR_DIMMED, 1);
			break;
	}
	return 0;
}
