#include <userint.h>
#include "ProjectPanel.h"
#include "LoadPanel.h"

#define CHANGECOLOR 0x94CEFF
#define BGCOLOR 0xFFFFFF
#define COLOR  0x065279

int CVICALLBACK OpenCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK ProExitCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{	
	
	 if(event==EVENT_COMMIT)
			  RemovePopup (proPanel);  

	return 0;
}

int CVICALLBACK DefaultCallback (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		case EVENT_LEFT_CLICK_UP:
			SetPanelAttribute (panel, ATTR_BACKCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_TXT, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_TXT_DESC, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (proPanel,PROPANEL_OPEN , ATTR_DIMMED, 0);
		    SetCtrlAttribute (panel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, COLOR);
			break;
	}
	return 0;
}

int CVICALLBACK ImgCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
   int boxValue;
   GetCtrlVal(panel,PROPANEL_IMGBOX,&boxValue);
   if(event == EVENT_VAL_CHANGED){
	   
   			  if(boxValue){
				   SetCtrlAttribute(defPanel, DEFPANEL_PICS, ATTR_VISIBLE,1);
				  
			  }else{
			  	 SetCtrlAttribute(defPanel, DEFPANEL_PICS, ATTR_VISIBLE,0);
				}
   
   }
	return 0;
}

int CVICALLBACK DescCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
int boxValue;
   GetCtrlVal(panel,PROPANEL_DESCBOX,&boxValue);
   if(event == EVENT_VAL_CHANGED){
	   
   			  if(boxValue){
				  
			SetCtrlAttribute(defPanel, DEFPANEL_TXT_DESC, ATTR_VISIBLE,1);
				   
			  }else{
			  	 
				 SetCtrlAttribute (defPanel, DEFPANEL_TXT_DESC, ATTR_VISIBLE, 0);
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
			SetPanelAttribute (defPanel, ATTR_BACKCOLOR,BGCOLOR );
			SetCtrlAttribute (defPanel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, BGCOLOR);
	
			SetCtrlAttribute (defPanel, DEFPANEL_TXT, ATTR_TEXT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (defPanel, DEFPANEL_TXT_DESC, ATTR_TEXT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (proPanel,PROPANEL_OPEN , ATTR_DIMMED, 1);
			break;
	}
	return 0;
}
