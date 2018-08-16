#include <userint.h>
#include "Environment.h"
#include "Plot.h"
#include "GraphDisp.h"
#include  "LoadPanel.h"
#include "EnvironmentPanel.h"



int temp_flag;
int humidity_flag;
int pressure_flag;

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


int CVICALLBACK LegendCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	 if( event == EVENT_VAL_CHANGED) 
	{   
		int legendval;
		GetCtrlVal(hEnvResultPanel,ENVIRPANEL_LEGEND, &legendval);

		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_VISIBLE, legendval);
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_LEFT, 1070); 
		SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_TOP, 450);
	}
	return 0;
}

int CVICALLBACK TemperatureCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		DisplayEnvironmentGraph();              
			break;
	}
	return 0;
}


int CVICALLBACK HumidityCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		 	DisplayEnvironmentGraph();     
			break;
	}
	return 0;
}

int CVICALLBACK PressureCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		   	DisplayEnvironmentGraph();     
			break;
	}
	return 0;
}
