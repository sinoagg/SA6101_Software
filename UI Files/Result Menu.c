#include <cvirte.h>		
#include <userint.h>
#include "Result Menu.h"
int resultmenu;



int CVICALLBACK TableCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	
	
	//点击table图标切换到table面板
	switch(event){
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultmenu, RESULTMENU_Table, "Resource\\Table_pressed.ico");   
			break;
	
	}
	return 0;
}

int CVICALLBACK GraphCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	return 0;
}

int CVICALLBACK SaveDataCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	return 0;
}
