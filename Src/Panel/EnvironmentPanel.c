#include <userint.h>
#include "Environment.h"

int CVICALLBACK MesaureCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{ 	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			int val; //Measure ∂‡—°
			GetCtrlVal(panel,control,&val);
				   if(val)
				   {
					   SetCtrlVal(panel,ENVIRONMEN_TEMPTER,val);
					   SetCtrlVal(panel,ENVIRONMEN_HUMIDITY,val);
					   SetCtrlVal(panel,ENVIRONMEN_PRESSURE,val);
						 
				   } else{
				   	   SetCtrlVal(panel,ENVIRONMEN_TEMPTER,0);
					   SetCtrlVal(panel,ENVIRONMEN_HUMIDITY,0);
					   SetCtrlVal(panel,ENVIRONMEN_PRESSURE,0);
				   }
			break;
	}
	return 0;
}
