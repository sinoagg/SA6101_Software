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
#include "Result Menu.h"
#include "Table.h"

int mainPanel;
int expListPanel;
int IdVdPanel;
int IdVgPanel;
int samplePanel;
int graphDispPanel;
int environmentPanel;
int resultPanel;
int graphDispPanel;
int TimerID;
int tablePanel;
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
	
	if ((environmentPanel = LoadPanel (mainPanel, "Environment.uir", ENVIRONMEN)) < 0)		//load Enviroment panel
		return -1;
	

	if ((resultPanel = LoadPanel (mainPanel, "Result Menu.uir", RESULTMENU)) < 0)		//load resultPanel panel
		return -1;
	
	if ((graphDispPanel = LoadPanel (mainPanel, "GraphDisp.uir", GRAPHDISP)) < 0)		//load GRAPHDISP panel
		return -1;
	
	if ((tablePanel = LoadPanel (mainPanel, "Table.uir", TABLE)) < 0)		//load TABLE panel
		return -1;
	
	DisplayPanel (mainPanel); 
	
	SetPanelPos(expListPanel, 105, 3);  //加载面板位置 （,top,left）
	SetPanelSize(expListPanel, 900, 300);//加载面板大小  (,height，width)
	//加滚动条847
	DisplayPanel(expListPanel);
	
	SetPanelPos(IdVdPanel, 105, 305);
	//SetPanelSize(IdVdPanel, 600, 1278);//加滚动条
	SetPanelSize(IdVdPanel, 900, 1293);
	DisplayPanel(IdVdPanel);
	
	SetPanelPos(samplePanel, 105, 1600);
	SetPanelSize(samplePanel, 450, 300);
	DisplayPanel(samplePanel);
	
	SetPanelPos(environmentPanel, 555, 1600);
	SetPanelSize(environmentPanel, 450, 300);
	DisplayPanel(environmentPanel);
	
	RunUserInterface ();
	CloseCom(comSelect);
	DiscardPanel (mainPanel);
	return 0;
}

//===================================================
//   MAIN_PANEL_Callback

int CVICALLBACK MAIN_PANEL_Callback (int panel, int event, void *callbackData,
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
//   RunCallback

int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时
			SetCtrlAttribute (mainPanel, MAIN_PANEL_Run, ATTR_DIMMED,1);         //禁用 开始按钮      
		    SetCtrlAttribute (mainPanel, MAIN_PANEL_Stop, ATTR_DIMMED, 0);       //恢复 停止按钮
	        SetCtrlAttribute (mainPanel, MAIN_PANEL_Save, ATTR_DIMMED,1);        //禁用 保存按钮
			if(!comSelect)
			{
				MessagePopup ("Warning", "Instrument Unconnected");   //Lost serial Connection
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

//===================================================
//   StopCallback

int CVICALLBACK StopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时
		  	 SetCtrlAttribute (mainPanel, MAIN_PANEL_Stop, ATTR_DIMMED,1);      //禁用 停止按钮      
		     SetCtrlAttribute (mainPanel, MAIN_PANEL_Run, ATTR_DIMMED, 0);      //恢复 开始按钮
			 SetCtrlAttribute (mainPanel, MAIN_PANEL_Save, ATTR_DIMMED, 0);     //恢复 保存按钮
			break;
	}
	return 0;
}

//===================================================
//   SaveCallback

int CVICALLBACK SaveCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
			break;
		case EVENT_LEFT_CLICK:			    //当Save被鼠标左键点击时 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Save, "Resource\\Save_pressed.ico");
			
			break;
			
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时  
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Save, "Resource\\Save.ico");

			break;
	}
	return 0;
}
//===================================================
//   SelectCallback

int CVICALLBACK SelectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //当Select被鼠标左键点击时,Select图标改变，其它两个正常状态 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "Resource\\Select_pressed.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "Resource\\Analyze.ico");
			
			break;
	}
	return 0;
}

//===================================================
//   Configure_Callback

int CVICALLBACK ConfigureCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK_UP:			    //当Configure被鼠标左键点击时,Configure图标改变，其它两个正常状态 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "Resource\\Select.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "Resource\\Configure_pressed.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "Resource\\Analyze.ico");
			
			break;
	}
	return 0;
}

//===================================================
//   Analyze_Callback

int CVICALLBACK AnalyzeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
		
				SetPanelPos(resultPanel, 125, 305);  
		     	SetPanelSize(resultPanel, 50, 1293);      
	 			DisplayPanel(resultPanel);  
				
				

				SetPanelPos(graphDispPanel, 176, 305);  
		     	SetPanelSize(graphDispPanel, 830, 1293);      
	 			DisplayPanel(graphDispPanel);
			


			break;
 		case EVENT_LEFT_CLICK_UP:			    //当Analyze被鼠标左键点击时,Analyze图标改变，其它两个正常状态， 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "Resource\\Select.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "Resource\\Analyze_pressed.ico");
		
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


