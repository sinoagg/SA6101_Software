#include <cvirte.h>		
#include <userint.h>
#include "MainPanel.h"

static int mainPanel;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((mainPanel = LoadPanel (0, "MainPanel.uir", MAIN_PANEL)) < 0)
		return -1;
	DisplayPanel (mainPanel);
	RunUserInterface ();
	DiscardPanel (mainPanel);
	return 0;
}

int CVICALLBACK ExoListCallBack (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	
	int ExpSelVal;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, control, &ExpSelVal);
			
			break;
	}
	return 0;
}
