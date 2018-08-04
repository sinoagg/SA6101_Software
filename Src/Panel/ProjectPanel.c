#include <userint.h>
#include "Project.h"
#include "LoadPanel.h"
//#include "ProjectPanel.h"

#define CHANGECOLOR 0x94CEFF//«≥¿∂
#define BGCOLOR 	0xFFFFFF
#define COLOR  		0x065279//…Ó¿∂

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

int CVICALLBACK PrjExitCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{	
	
	 if(event==EVENT_COMMIT)
			  RemovePopup (hPrjPanel);  

	return 0;
}

int CVICALLBACK DefaultCallback (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelAttribute (panel, ATTR_BACKCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_DATE, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_TIME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (hPrjPanel,PROPANEL_OPEN , ATTR_DIMMED, 0);
			SetCtrlAttribute (panel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, COLOR);
			break;
	}
	return 0;
}

int CVICALLBACK ImgCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	   int val;
	   GetCtrlVal(panel,PROPANEL_IMGBOX,&val);
	   if(event == EVENT_VAL_CHANGED){
	   
   			  if(val){
				   SetCtrlAttribute(hPrjListPanel, DEFPANEL_PICS, ATTR_VISIBLE,1);
				  
			  }else{
			  	 SetCtrlAttribute(hPrjListPanel, DEFPANEL_PICS, ATTR_VISIBLE,0);
			  }
   
   }
	return 0;
}

int CVICALLBACK DescCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
		 int val;
  		 GetCtrlVal(panel,PROPANEL_DESCBOX,&val);
  		 if(event == EVENT_VAL_CHANGED){
	   
   			  if(val){
				  SetCtrlAttribute(hPrjListPanel, DEFPANEL_DESC, ATTR_VISIBLE,1);
				   
			  }else{
			  	  SetCtrlAttribute (hPrjListPanel, DEFPANEL_DESC, ATTR_VISIBLE, 0);
			  }
   
   }
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
