#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>

#include "MainPanel.h"
#include "Experiment List.h"
#include "Id-Vds Configuration.h"
#include "Id-Vgs Configuration.h"
#include "Sample Configuration.h"

#include "SerialCommand.h"
#include "ExpListPanel.h"
#include "SampleCfgPanel.h"
#include "IdVdsPanel.h"
#include "IdVgsPanel.h"

int mainPanel;
int expListPanel;
int IdVdPanel;
int IdVgPanel;
int samplePanel;

static int comSelect;				//Serial Com Number

unsigned char UartTxBuf[32]={0};
unsigned char UartRxBuf[64]={0};

extern IdVdCfg_TypeDef IdVdCfg; 
extern IdVgCfg_TypeDef IdVgCfg;

int main (int argc, char *argv[])
{
	int status;
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	//comSelect=argc;		//pass comSelect variable 
	comSelect=1;
	status = OpenComConfig(comSelect, "", 115200, 0, 8, 1, 512, 512);	   //Config and Connect serial port
	if(status != 0) 
	{
		MessagePopup("Error","Device unconnected!");
		return 0;
	}
	
	if ((mainPanel = LoadPanel (0, "MainPanel.uir", MAIN_PANEL)) < 0)	  //load main panel
		return -1;
	
	
	if ((expListPanel = LoadPanel (mainPanel, "Experiment List.uir", EXP_LIST)) < 0)		//load left panel
		return -1;
	
	
	if ((IdVdPanel = LoadPanel (mainPanel, "Id-Vds Configuration.uir", IDVDS_CFG)) < 0)		//load middle panel
		return -1;
	
	
	if ((IdVgPanel = LoadPanel (mainPanel, "Id-Vgs Configuration.uir", IDVGS_CFG)) < 0)		//load middle panel
		return -1;
	
	
	
	if ((samplePanel = LoadPanel (mainPanel, "Experiment List.uir", SAMPLE_CFG)) < 0)		//load right panel
		return -1;
	
	DisplayPanel (mainPanel); 
	
	SetPanelPos(expListPanel, 0, 200);
	SetPanelSize(expListPanel, 600, 300);
	DisplayPanel(expListPanel);
	
	SetPanelPos(IdVdPanel, 300, 200);
	SetPanelSize(IdVdPanel, 600, 800);
	DisplayPanel(IdVdPanel);
	
	SetPanelPos(samplePanel, 1100, 200);
	SetPanelSize(samplePanel, 600, 300);
	DisplayPanel(samplePanel);
	
	RunUserInterface ();
	DiscardPanel (mainPanel);
	return 0;
}


int CVICALLBACK RunCallBack (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(!comSelect)
			{
				MessagePopup ("Warning", "Instrument Unconnected");//Lost serial Connection
			}
			else
			{
				int expSelVal;
				if(GetCtrlVal(expListPanel, EXP_LIST_LISTBOX, &expSelVal)<0)
					return -1;
				switch(expSelVal)
				{
					case 0:						//IdVd
						GetIdVdCfg (IdVdPanel);
						break;
					case 1:						//IdVg
						GetIdVgCfg(IdVgPanel);
						break;
					case 2:
												//I-t
						break;
					case 3:						//R-t
						break;
					default:
						break;
				}
				CommandConfig(comSelect);
				CommandRun(comSelect);  
			}
			break;
	}
	return 0;
}

int CVICALLBACK StopCallBack (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			CommandStop(comSelect);
			break;
	}
	return 0;
}

int CVICALLBACK SaveCallBack (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}
