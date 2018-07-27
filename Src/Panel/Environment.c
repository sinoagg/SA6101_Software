#include <userint.h>
#include "Environment.h"

int CVICALLBACK MesaureCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{ int CheckValue;
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			//Measure ∂‡—°
			GetCtrlVal(panel,control,&CheckValue);
				   if(CheckValue){
					   SetCtrlVal(panel,ENVIRONMEN_TEMPTER,CheckValue);
					   SetCtrlVal(panel,ENVIRONMEN_HUMIDITY,CheckValue);
					   SetCtrlVal(panel,ENVIRONMEN_PRESSURE,CheckValue);
						 
				   } else{
				   	   SetCtrlVal(panel,ENVIRONMEN_TEMPTER,0);
					   SetCtrlVal(panel,ENVIRONMEN_HUMIDITY,0);
					   SetCtrlVal(panel,ENVIRONMEN_PRESSURE,0);
				   }
			break;
	}
	return 0;
}
