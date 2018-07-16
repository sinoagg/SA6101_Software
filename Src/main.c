#include "asynctmr.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>

#include "MainPanel.h"
#include "Experiment List.h"
#include "Id-Vds Configuration.h"
#include "Id-Vgs Configuration.h"
#include "Sample Configuration.h"
#include "GraphDisp.h"
#include "Environment.h"

#include "ExpListPanel.h"
#include "SampleCfgPanel.h"
#include "IdVdsPanel.h"
#include "IdVgsPanel.h"
#include "Protocol.h"
#include "Graph.h"
#include "Curve.h"

int mainPanel;
int expListPanel;
int IdVdPanel;
int IdVgPanel;
int samplePanel;
int graphDispPanel;
int environmentPanel;
<<<<<<< HEAD
=======
int resultPanel;
int graphDispPanel;
>>>>>>> f14a99b... SA6101 1.00

int TimerID;
Graph_TypeDef Graph;

#define DEFAULT_ADDR 0x01

unsigned char comSelect;				//Serial Com Number

unsigned char UartTxBuf[32]={0};
unsigned char UartRxBuf[64]={0};

extern IdVdCfg_TypeDef IdVdCfg; 
extern IdVgCfg_TypeDef IdVgCfg;

void CVICALLBACK ComCallback(int portNumber ,int eventMask, void * callbackData);
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);

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
	InstallComCallback (comSelect, LWRS_RECEIVE, 20, 0, ComCallback, 0);   //binding Callback function to serial input data		18 bytes received will calling for an interrupt
	SetCTSMode(comSelect, LWRS_HWHANDSHAKE_OFF);
	FlushInQ(comSelect);	   //Clear input and output buffer
	FlushOutQ(comSelect);
	
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
	
	if ((environmentPanel = LoadPanel (mainPanel, "Environment.uir", ENVIRONMENT)) < 0)		//load Enviroment panel
		return -1;
	
<<<<<<< HEAD
=======
	if ((resultPanel = LoadPanel (mainPanel, "Result Menu.uir", RESULTMENU)) < 0)		//load resultPanel panel
		return -1;
	
	if ((graphDispPanel = LoadPanel (mainPanel, "GraphDisp.uir", GRAPHDISP)) < 0)		//load GRAPHDISP panel
		return -1;
	
	
	
	
>>>>>>> f14a99b... SA6101 1.00
	DisplayPanel (mainPanel); 
	
	SetPanelPos(expListPanel, 130, 3);  //加载面板位置 （,top,left）
	SetPanelSize(expListPanel, 880, 300);//加载面板大小  (,height，width)
	//加滚动条847
	DisplayPanel(expListPanel);
	
	SetPanelPos(IdVdPanel, 130, 305);
	//SetPanelSize(IdVdPanel, 600, 1278);//加滚动条
	SetPanelSize(IdVdPanel, 880, 1293);
	DisplayPanel(IdVdPanel);
	
	SetPanelPos(samplePanel, 130, 1600);
	SetPanelSize(samplePanel, 440, 300);
	DisplayPanel(samplePanel);
	
	SetPanelPos(environmentPanel, 570, 1600);
	SetPanelSize(environmentPanel, 440, 300);
	DisplayPanel(environmentPanel);
	
	RunUserInterface ();
	CloseCom(comSelect);
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

int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
<<<<<<< HEAD
			SetCtrlAttribute (mainPanel, MAIN_PANEL_Run, ATTR_DIMMED,1);         //禁用 开始按钮      
		   SetCtrlAttribute (mainPanel, MAIN_PANEL_Stop, ATTR_DIMMED, 0);       //恢复 停止按钮
	       SetCtrlAttribute (mainPanel, MAIN_PANEL_Save, ATTR_DIMMED,1);        //禁用 保存按钮
=======
			break;
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时
			SetCtrlAttribute (mainPanel, MAIN_PANEL_Run, ATTR_DIMMED,1);         //禁用 开始按钮      
		    SetCtrlAttribute (mainPanel, MAIN_PANEL_Stop, ATTR_DIMMED, 0);       //恢复 停止按钮
	        SetCtrlAttribute (mainPanel, MAIN_PANEL_Save, ATTR_DIMMED,1);        //禁用 保存按钮
>>>>>>> f14a99b... SA6101 1.00
			if(!comSelect)
			{
				MessagePopup ("Warning", "Instrument Unconnected");//Lost serial Connection
			}
			else
			{
				int expType;
				int graphIndex=1;	//currently only deal with one graph circumstance
				int numOfCurve=1;
				int numOfDots=500;
				if(GetCtrlVal(expListPanel, EXP_LIST_LISTBOX, &expType)<0)
					return -1;
				switch(expType)
				{
					case 0:
						GetIdVdCfg (IdVdPanel);
						numOfCurve=abs(IdVdCfg.cfgVgstart-IdVdCfg.cfgVgstop)/IdVdCfg.cfgVgstep;
						numOfDots=abs(IdVdCfg.cfgVdstart-IdVdCfg.cfgVdstop)/IdVdCfg.cfgVdstep;
						break;
					case 1:
						GetIdVgCfg (IdVgPanel);
						numOfCurve=abs(IdVgCfg.cfgVdstart-IdVgCfg.cfgVdstop)/IdVgCfg.cfgVdstep;
						numOfDots=abs(IdVgCfg.cfgVgstart-IdVgCfg.cfgVgstop)/IdVgCfg.cfgVgstep;
						break;
					case 2:
						//TODO
						break;
					case 3:
						//TODO
						break;
					default:
						break;
				}
				
				ProtocolCfg(comSelect, DEFAULT_ADDR, (unsigned char)expType, UartTxBuf);		//send config to instrument via UART
				graphInit(graphIndex, numOfCurve, numOfDots, &Graph); 	//graph set up 
				TimerID = NewAsyncTimer(1,-1, 1, TimerCallback, 0);		//Create Asynchronous (Timer time interval 1s, continue generating evernt, enabled, callback function name, passing no pointer)  
				ProtocolRun(comSelect, DEFAULT_ADDR, UartTxBuf);		//send RUN command to instrument via UART
			}
			break;
	}
	return 0;
}

int CVICALLBACK StopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
			SetCtrlAttribute (mainPanel, MAIN_PANEL_Stop, ATTR_DIMMED,1);      //禁用 停止按钮      
		     SetCtrlAttribute (mainPanel, MAIN_PANEL_Run, ATTR_DIMMED, 0);      //恢复 开始按钮
			 SetCtrlAttribute (mainPanel, MAIN_PANEL_Save, ATTR_DIMMED, 0);     //恢复 保存按钮
			break;
	}
	return 0;
}

int CVICALLBACK SaveCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
			break;
		case EVENT_LEFT_CLICK:			    //当Save被鼠标左键点击时 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Save, "icon\\Save(b).png");
			
			break;
			
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时  
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Save, "icon\\Save(a).png");

			break;
	}
	return 0;
}
//===================================================
//   Select_CallBack

int CVICALLBACK SelectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:			    //当Select被鼠标左键点击时,Select图标改变，其它两个正常状态 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "Resource\\Select(b).ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "Resource\\Configure(a).png"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "Resource\\Analyze(a).png");
			
			break;
	}
	return 0;
}

//===================================================
//   Configure_CallBack

int CVICALLBACK ConfigureCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK:			    //当Configure被鼠标左键点击时,Configure图标改变，其它两个正常状态 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "Resource\\Select(a).png");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "Resource\\Configure(b).ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "Resource\\Analyze(a).png");
			
			break;
	}
	return 0;
}

//===================================================
//   Analyze_CallBack

int CVICALLBACK AnalyzeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK:			    //当Analyze被鼠标左键点击时,Analyze图标改变，其它两个正常状态 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "Resource\\Select(a).png");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "Resource\\Configure(a).png"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "Resource\\Analyze(b).ico");
			
<<<<<<< HEAD
=======
	case EVENT_LEFT_CLICK:
		
				SetPanelPos(resultPanel, 125, 305);  
		     	SetPanelSize(resultPanel, 50, 1293);      
	 			DisplayPanel(resultPanel);
				
				
				SetPanelPos(graphDispPanel, 176, 305);  
		     	SetPanelSize(graphDispPanel, 830, 1293);      
	 			DisplayPanel(graphDispPanel);
			

		
>>>>>>> f14a99b... SA6101 1.00
			break;
	}
	return 0;
}

void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData)
{
	int status;
	int rxNum;
	RxDataTypeDef RxData;
	rxNum = GetInQLen(comSelect);  											//读取串口中发送来的数据数量
	while(rxNum>=20)
	{
		status = ComRd(comSelect, (char *)UartRxBuf, 20);					//Read UART Buffer to local buffer
		ProtocolGetData(UartRxBuf, &RxData);								//get data from uart buffer
		Graph.pCurveArray->numOfPlotDots++;									//number of plot dot increase
		*(Graph.pCurveArray->pDotX++)=RxData.rxVdtest;						//get x, set pointer to the next data
		*(Graph.pCurveArray->pDotY++)=RxData.rxIdmeasured.num_float;		//get y, set pointer to the next data
		if(RxData.rxStopSign==0x02)											//if complete the test, stop the timer
			DiscardAsyncTimer(TimerID);
		rxNum-=20;
		Graph.pCurveArray->numOfPlotDots++;
		rxNum = GetInQLen(comSelect);  										//读取串口中发送来的数据数量 
	}
	
}

int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	if(Graph.pCurveArray->numOfPlotDots>0)
		Graph.pCurveArray->plotHandle=PlotXY(graphDispPanel, GRAPHDISP_GRAPH1, Graph.pCurveArray->pDotX, Graph.pCurveArray->pDotY, Graph.pCurveArray->numOfPlotDots, VAL_FLOAT, VAL_FLOAT, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
	if(Graph.pCurveArray->plotHandle<0)
		return -1;
	else
		return 0;
}

