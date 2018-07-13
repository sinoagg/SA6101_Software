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
#include "Enviroment.h "

int mainPanel;
int expListPanel;
int IdVdPanel;
int IdVgPanel;
int samplePanel;
int enviromentPanel;

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
	/*status = OpenComConfig(comSelect, "", 115200, 0, 8, 1, 512, 512);	   //Config and Connect serial port
	if(status != 0) 
	{
		MessagePopup("Error","Device unconnected!");
		return 0;
	}*/
	
	if ((mainPanel = LoadPanel (0, "MainPanel.uir", MAIN_PANEL)) < 0)	  //load main panel
		return -1;
	
	
	if ((expListPanel = LoadPanel (mainPanel, "Experiment List.uir", EXP_LIST)) < 0)		//load left panel
		return -1;
	
	
	if ((IdVdPanel = LoadPanel (mainPanel, "Id-Vds Configuration.uir", IDVDS_CFG)) < 0)		//load middle panel
		return -1;
	
	
	if ((IdVgPanel = LoadPanel (mainPanel, "Id-Vgs Configuration.uir", IDVGS_CFG)) < 0)		//load middle panel
		return -1;
	
	
	
	if ((samplePanel = LoadPanel (mainPanel, "Sample Configuration.uir", SAMPLE_CFG)) < 0)		//load right panel
		return -1;
	
	if ((enviromentPanel = LoadPanel (mainPanel, "Enviroment.uir", ENVIROMENT)) < 0)		//load Enviroment panel
		return -1;

	
	DisplayPanel (mainPanel); 
	
	SetPanelPos(expListPanel, 130, 3);  //�������λ�� ��,top,left��
	SetPanelSize(expListPanel, 880, 300);//��������С  (,height��width)
	//�ӹ�����847
	DisplayPanel(expListPanel);
	
	SetPanelPos(IdVdPanel, 130, 305);
	//SetPanelSize(IdVdPanel, 600, 1278);//�ӹ�����
	SetPanelSize(IdVdPanel, 880, 1293);
	DisplayPanel(IdVdPanel);
	
	SetPanelPos(samplePanel, 130, 1600);
	SetPanelSize(samplePanel, 440, 300);
	DisplayPanel(samplePanel);
	
	SetPanelPos(enviromentPanel, 570, 1600);
	SetPanelSize(enviromentPanel, 440, 300);
	DisplayPanel(enviromentPanel);
	
	RunUserInterface ();
	DiscardPanel (mainPanel);
	return 0;
}
//===================================================
//   MAIN_PANEL_CallBack

int CVICALLBACK MAIN_PANEL_CallBack (int panel, int event, void *callbackData,
									 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			   	QuitUserInterface(0); 
			break;
	}
	return 0;
}

//===================================================
//   Run_CallBack

int CVICALLBACK Run_CallBack (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

		case EVENT_LEFT_CLICK:	          //�����Runʱ

	       SetCtrlAttribute (mainPanel, MAIN_PANEL_Run, ATTR_DIMMED,1);         //���� ��ʼ��ť      
		   SetCtrlAttribute (mainPanel, MAIN_PANEL_Stop, ATTR_DIMMED, 0);       //�ָ� ֹͣ��ť
	       SetCtrlAttribute (mainPanel, MAIN_PANEL_Save, ATTR_DIMMED,1);        //���� ���水ť
	

			break;
			
			
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

//===================================================
//   Stop_CallBack

int CVICALLBACK Stop_CallBack (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			CommandStop(comSelect);
			break;
	   case EVENT_LEFT_CLICK:		     //�����Stopʱ

		     SetCtrlAttribute (mainPanel, MAIN_PANEL_Stop, ATTR_DIMMED,1);      //���� ֹͣ��ť      
		     SetCtrlAttribute (mainPanel, MAIN_PANEL_Run, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
			 SetCtrlAttribute (mainPanel, MAIN_PANEL_Save, ATTR_DIMMED, 0);     //�ָ� ���水ť
		

			break;
	}
	return 0;
}

//===================================================
//   Stop_CallBack

int CVICALLBACK Save_CallBack (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
		case EVENT_LEFT_CLICK:			    //��Save�����������ʱ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Save, "icon\\Save(b).png");
			
			break;
			
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ  
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Save, "icon\\Save(a).png");

			break;

			break;
	}
	return 0;
}

//===================================================
//   Select_CallBack

int CVICALLBACK Select_CallBack (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:			    //��Select�����������ʱ,Selectͼ��ı䣬������������״̬ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "icon\\Select(b).ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "icon\\Configure(a).png"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "icon\\Analyze(a).png");
			
			break;
	}
	return 0;
}

//===================================================
//   Configure_CallBack

int CVICALLBACK Configure_CallBack (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK:			    //��Configure�����������ʱ,Configureͼ��ı䣬������������״̬ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "icon\\Select(a).png");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "icon\\Configure(b).ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "icon\\Analyze(a).png");
			
			break;
	}
	return 0;
}

//===================================================
//   Analyze_CallBack

int CVICALLBACK Analyze_CallBack (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK:			    //��Analyze�����������ʱ,Analyzeͼ��ı䣬������������״̬ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "icon\\Select(a).png");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "icon\\Configure(a).png"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "icon\\Analyze(b).ico");
			
			break;
	}
	return 0;
}
