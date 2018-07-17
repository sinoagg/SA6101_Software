#include <cvirte.h>		
#include <userint.h>
#include "Result Menu.h"
int resultPanel;
int tablePanel;
int graphDispPanel;
int saveDataPanel;

int CVICALLBACK TableCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	
	//点击table图标切换到table面板
	switch(event){
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultPanel, RESULTMENU_Table, "Resource\\Table_pressed.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_Graph, "Resource\\Graph.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_SaveData, "Resource\\SaveData.ico");
			break;
		case EVENT_LEFT_CLICK:
			   	SetPanelPos(tablePanel, 176, 305);  
		     	SetPanelSize(tablePanel, 830, 1293);      
	 			DisplayPanel(tablePanel);
			break;
	
	}
	return 0;
}

int CVICALLBACK GraphCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
		//点击graph图标切换到graph面板
	switch(event){
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultPanel, RESULTMENU_Graph, "Resource\\Graph_pressed.ico");
				DisplayImageFile (resultPanel, RESULTMENU_Table, "Resource\\Table.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_SaveData, "Resource\\SaveData.ico"); 
				
			break;
		case EVENT_LEFT_CLICK:
			   	SetPanelPos(graphDispPanel, 176, 305);  
		     	SetPanelSize(graphDispPanel, 830, 1293);      
	 			DisplayPanel(graphDispPanel);
			break;
	}	
	return 0;
}

int CVICALLBACK SaveDataCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)

{
	   switch(event){
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultPanel, RESULTMENU_Graph, "Resource\\Graph.ico");
				DisplayImageFile (resultPanel, RESULTMENU_Table, "Resource\\Table.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_SaveData, "Resource\\SaveData_pressed.ico"); 
			//选择要保存的数据形式：table/graph
				//MessagePopup ("Save Test Data As", "请保存数据");       
			break;
		 case EVENT_LEFT_CLICK:
			   	SetPanelPos(saveDataPanel, 300, 700);  
		     	SetPanelSize(saveDataPanel,250, 400);      
	 			DisplayPanel(saveDataPanel);
			break;
	}	
	return 0;
}
