#include <userint.h>
#include "Environment.h"
#include "Plot.h"
#include "GraphDisp.h"
#include  "LoadPanel.h"
#include "EnvironmentPanel.h"
#include "main.h"
 
int CVICALLBACK MesaureCallback (int panel, int control, int event,void *callbackData, int eventData1, int eventData2)
{ 	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			int val; //Measure ¶àÑ¡
			GetCtrlVal(panel,control,&val);
				   if(val)
				   {  
					   SetCtrlVal(panel,ENVIRONMEN_TEMPTER,val);
					   SetCtrlVal(panel,ENVIRONMEN_HUMIDITY,val);
					   SetCtrlVal(panel,ENVIRONMEN_PRESSURE,val);
					   SetCtrlVal(hEnvResultPanel,ENVIRPANEL_TEMP_BOX,val);
		  			   SetCtrlVal(hEnvResultPanel,ENVIRPANEL_HUM_BOX,val);
					   SetCtrlVal(hEnvResultPanel,ENVIRPANEL_PRESS_BOX,val );	
					}
				   else
				   {
				   	   SetCtrlVal(panel,ENVIRONMEN_TEMPTER,0);
					   SetCtrlVal(panel,ENVIRONMEN_HUMIDITY,0);
					   SetCtrlVal(panel,ENVIRONMEN_PRESSURE,0);
					   SetCtrlVal(hEnvResultPanel,ENVIRPANEL_TEMP_BOX,0);
		  			   SetCtrlVal(hEnvResultPanel,ENVIRPANEL_HUM_BOX,0);
					   SetCtrlVal(hEnvResultPanel,ENVIRPANEL_PRESS_BOX,0 );
				   }
			break;
	}
	return 0;
}


//Í¼Àý
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
{   int temp;
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_TEMPTER,&temp); 
	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			if(temp &&(control_Uart_Flag>0))DisplayEnvtGraph(); 
			break;
	}
	return 0;
}


int CVICALLBACK HumidityCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{   int Hum;
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_HUMIDITY,&Hum); 
	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			if(Hum &&(control_Uart_Flag>0))DisplayEnvtGraph();     
			break;
	}
	return 0;
}

int CVICALLBACK PressureCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{   int press;
	GetCtrlVal(hEnvCfgPanel,ENVIRONMEN_PRESSURE,&press);          
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			if(press && (control_Uart_Flag>0))DisplayEnvtGraph();     
			break;
	}
	return 0;
}





