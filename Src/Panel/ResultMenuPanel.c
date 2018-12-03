//==============================================================================
// Include files
#include "Result Menu.h"
#include "excel2000.h"
#include "excelreport.h"
#include "GraphDisp.h"
#include <userint.h>
#include "toolbox.h"   
#include "ResultMenuPanel.h"
#include "Graph.h"
#include "LoadPanel.h"
#include <userint.h>  

int sheet = 0;
int graph1 = 0;
int graph2 = 0;
//==============================================================================
// Constants

//==============================================================================
// Types
enum ResultDispSelect
{
	DISP_TABLE=0,
	DISP_GRAPH=1
};

enum GraphDispSelect
{
	DISP_SINGLE_GRAPH=0,
	DISP_DOUBLE_GRAPH=1	
};
//==============================================================================
// Static global variables
char sheetSavePath[512];
char graph1SavePath[512];
char graph2SavePath[512];
char sheetPath[512] = " C:\\SINOAGG\SA6101\\UserData\\Sheet.xls";
char graph1Path[512] = "C:\\SINOAGG\SA6101\\UserData\\Graph1.jpg";
char graph2Path[512]= "C:\\SINOAGG\SA6101\\UserData\\Graph2.jpg";
//==============================================================================
// Static functions
static int SaveGraph(int panel, int control, int plotHandle, const char path[]); 
//==============================================================================
// Global variables
enum ResultDispSelect resultDispSelect=DISP_GRAPH;
enum GraphDispSelect graphDispSelect=DISP_SINGLE_GRAPH;
Rect rc;
int nBitmapID;
//==============================================================================
// Global functions	

static void DispTable(void)
{
	SetPanelPos(hTablePanel, 172, 305);  
	DisplayPanel(hTablePanel);
	SetCtrlAttribute ( hTablePanel,TABLE_DISTABLE,ATTR_VISIBLE,1 );  
	/*SetCtrlAttribute ( hGraphPanel,GRAPHDISP_GRAPH1,ATTR_VISIBLE,0);                
	SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);     */           
}

static void DispSingleGraph(void)
{
	
	SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 680);
	SetCtrlAttribute ( hGraphPanel,GRAPHDISP_GRAPH1,ATTR_VISIBLE,1 );                
	SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
	//SetPanelPos(hGraphPanel, 172, 305);    
	//DisplayPanel(hGraphPanel);
    HidePanel(hTablePanel); //隐藏table面板、table表格 提高速率
}

static void DispDoubleGraph(void)
{
	
	SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //如果CheckBox是选中状态则显示两个graph     
	SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
	SetCtrlAttribute ( hGraphPanel,GRAPHDISP_GRAPH1,ATTR_VISIBLE,1 );                
	SetCtrlAttribute (hGraphPanel,GRAPHDISP_GRAPH1 , ATTR_LEFT, 5);   
	SetCtrlAttribute (hGraphPanel, GRAPHDISP_GRAPH2 , ATTR_LEFT, 28); 
	//SetPanelPos(hGraphPanel, 172, 305);       
	//DisplayPanel(hGraphPanel);
	
	
}

static void DispGraphSelectCheckBox(void)
{
	if(graphDispSelect==DISP_SINGLE_GRAPH)
	{
		SetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, 0);
	}
	else{
		SetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, 1);
	 
	}
	SetPanelPos(hGraphSelectPanel, 172, 1457);  
 	DisplayPanel(hGraphSelectPanel);
}

void DispResultTableGraph(void)					//Display Result  Table
{
	if(resultDispSelect==DISP_TABLE)
		DispTable();
	else
	{
	  	if(graphDispSelect==DISP_SINGLE_GRAPH) 
		DispSingleGraph();
		else if(graphDispSelect==DISP_DOUBLE_GRAPH)
		DispDoubleGraph();
	}
}
int  ToNumberSystem(int tmp)
{
    char str;
    str = 65 + (char)tmp - 1;		//对应的ASCII码		   A==65     tmp = column % 26
    return str;
}


char reverse(char strs[],char str[],int row)
{
	int i, j;
	i = 0;
	j = strlen(str)-1;
	while (i < j)
	{
		char tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	sprintf(strs,"%s%s%d","A1:",str,row);    
	return str;
	
	
}

static void SaveSheet(char path[])
{
	int row,column;
	char strs[80];
	static ExcelObj_App               ExcelAppHandle = 0;       
	static ExcelObj_Workbooks         ExcelWorkbooksHandle = 0; 
	static ExcelObj_Workbook          ExcelWorkbookHandle = 0;  
	static ExcelObj_Sheets            ExcelSheetsHandle = 0;    
	static ExcelObj_Worksheet         ExcelWorksheetHandle = 0;
	GetNumTableRows (hTablePanel,TABLE_DISTABLE,&row);
	GetNumTableColumns (hTablePanel,TABLE_DISTABLE,&column);
	int tmp;
	char mydata[1000];
	int k=0;
	while (column)					//将列int型转换为 对应的ASCII码 在转为int 计算 最后转为26进制显示
	{
		/*tmp = column;*/
		tmp = column % 26;	   
		mydata[k++] = ToNumberSystem(tmp);
		column = column / 26;
	}
	mydata[k] = '\0';
    reverse(strs,mydata,row); 
	Excel_NewApp (NULL, 1, LOCALE_NEUTRAL, 0, &ExcelAppHandle);	  //create a new Application object, and obtain a handle to the object.
	Excel_GetProperty (ExcelAppHandle, NULL, Excel_AppWorkbooks, CAVT_OBJHANDLE, &ExcelWorkbooksHandle);
	Excel_WorkbooksAdd (ExcelWorkbooksHandle, NULL, CA_DEFAULT_VAL,&ExcelWorkbookHandle);
	Excel_GetProperty (ExcelAppHandle, NULL, Excel_AppSheets,CAVT_OBJHANDLE, &ExcelSheetsHandle);
	Excel_SheetsItem (ExcelSheetsHandle, NULL, CA_VariantInt(1),&ExcelWorksheetHandle);
	Excel_WorksheetActivate (ExcelWorksheetHandle, NULL);	 
	ExcelRpt_WriteDataFromTableControl (ExcelWorksheetHandle, strs, hTablePanel, TABLE_DISTABLE);	//write data from table control
	ExcelRpt_WorkbookSave (ExcelWorkbookHandle, sheetSavePath,ExRConst_DefaultFileFormat );   //ExRConst_Excel2						 ExRConst_DefaultFileFormat
	Excel_AppQuit (ExcelAppHandle, NULL);
	CA_DiscardObjHandle(ExcelAppHandle);
	CA_DiscardObjHandle(ExcelWorkbooksHandle); 
	CA_DiscardObjHandle(ExcelWorkbookHandle); 
	CA_DiscardObjHandle(ExcelSheetsHandle); 
	CA_DiscardObjHandle(ExcelWorksheetHandle); 
}
 void SaveGraphs(char path[])
{
	GetPanelDisplayBitmap (hGraphPanel, VAL_FULL_PANEL,VAL_ENTIRE_OBJECT, &nBitmapID);		//截取整个屏幕
	SaveBitmapToJPEGFile (nBitmapID, path, JPEG_INTERLACE, 100);
	DiscardBitmap (nBitmapID);
	
}	
 void SaveGraph1(int control,char path[])
{
	GetCtrlAttribute (hGraphPanel, control, ATTR_TOP, &rc.top);		//得到所要截取的波形图表坐标  
	GetCtrlAttribute (hGraphPanel, control, ATTR_LEFT, &rc.left);
	GetCtrlAttribute (hGraphPanel, control, ATTR_HEIGHT, &rc.height);
	GetCtrlAttribute (hGraphPanel, control, ATTR_WIDTH, &rc.width);
	GetPanelDisplayBitmap (hGraphPanel, VAL_FULL_PANEL, rc, &nBitmapID);
	SaveBitmapToJPEGFile (nBitmapID, path, JPEG_INTERLACE, 100);
	DiscardBitmap (nBitmapID);
	
}							
int CVICALLBACK TableCallback (int panel, int control, int event,						//点击table图标切换到table面板     
							   void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
			DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico");
			DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table_pressed.ico"); 
			DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
			       
			resultDispSelect=DISP_TABLE;
			DispResultTableGraph();
			int val;
			GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
			if(val)
			{	
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\D-ouGraph.ico");
			}
			break;
	}
	return 0;
}

int CVICALLBACK GraphCallback (int panel, int control, int event,						//点击graph图标切换到graph面板    
							   void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		
		case EVENT_LEFT_CLICK_UP:
			DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
			DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
			DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
			SetCtrlAttribute (hTablePanel, TABLE_DISTABLE, ATTR_VISIBLE,0 ); 
			HidePanel(hTablePanel);           //隐藏table面板、table表格 提高速率       
			if(resultDispSelect==DISP_GRAPH)  //如果此时在显示图的时候还去点击图的图标，则认为是想切换显示
		  		DispGraphSelectCheckBox();
			else
			{
				resultDispSelect=DISP_GRAPH;
				DispResultTableGraph();
			}
			
			int val;
	  	    GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
			if(val)
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
			 else
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico"); 
			break;
	}	
	return 0;
}

int CVICALLBACK GraphSelectCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{  
	if(event == EVENT_LEFT_CLICK_UP)
	{      	
		HidePanel(hGraphSelectPanel); 
		int val;
	  	GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
	    if(val)
		{	
		    DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
			DispDoubleGraph();
			graphDispSelect=DISP_DOUBLE_GRAPH;
			SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_VISIBLE, 1);
			SetCtrlAttribute (hEnvResultPanel, ENVIRPANEL_LEGEND, ATTR_VISIBLE, 1);
			//SetCtrlAttribute (hEnvResultPanel, ENVIRPANEL_TXT_LEGEND, ATTR_VISIBLE, 1);
			SetCtrlVal(hEnvResultPanel, ENVIRPANEL_LEGEND,1);
		
		}
		else
		{   
			DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
			DispSingleGraph();
			graphDispSelect=DISP_SINGLE_GRAPH;
			SetCtrlAttribute (hGraphPanel, GRAPHDISP_CANVAS, ATTR_VISIBLE, 0);
		    SetCtrlAttribute (hEnvResultPanel, ENVIRPANEL_LEGEND, ATTR_VISIBLE,0); 
		
		}
	}
	return 0;
}

int CVICALLBACK SaveDataCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	   switch(event){
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData_pressed.ico"); 
		  		//弹出savedata面板 
			   InstallPopup(hSaveDataPanel);
			   break;
		 
	}	
	return 0;
}

int CVICALLBACK ExitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_LEFT_CLICK_UP)
	{
		RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
		DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");
		
	}
	return 0;
}

int CVICALLBACK BrowseSheetCallback (int panel, int control, int event,
								   	 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{			
		case EVENT_LEFT_CLICK_UP:
			sheet = 1;
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\", ".xlsx", "*.xls;*.xlsx", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, sheetSavePath)>0)
				SetCtrlVal(panel, SAVEDATA_SHEETPATH, sheetSavePath);
			else 
				return -1;
			break;
	}
	return 0;
}
		 
int CVICALLBACK BrowseGraph1Callback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
		    graph1=1; 
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\UserData", ".jpg", "*.jpg;*.png;*.bmp;*.tif", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, graph1SavePath)>0)
				SetCtrlVal(panel, SAVEDATA_GRAPH1PATH, graph1SavePath);
			else 
				return -1;
			break;
	}
	return 0;
}

int CVICALLBACK BrowseGraph2Callback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			graph2 =1;
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\UserData", ".jpg", "*.jpg;*.png;*.bmp;*.tif", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, graph2SavePath)>0)
				SetCtrlVal(panel, SAVEDATA_GRAPH2PATH, graph2SavePath);
			else 
				return -1;
			break;
	}
	return 0;
}


int CVICALLBACK SaveGraph1Callback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
   	int exist;  
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, SAVEDATA_GRAPH1PATH, graph1SavePath);
			exist =  FileExists(graph1SavePath,0);
			if(exist)
			{
			 	MessagePopup ("Tips", "The Picture file already exists, please choose a different path");   
		   	 } 
			else
			{
				if(graph1SavePath[0]=='\0')
					MessagePopup ("Message", "Please select a valod plot");
				else
				{
					InstallPopup(hSaveDataTipPanel);  
					SaveGraph1(GRAPHDISP_GRAPH1,graph1SavePath);
					HidePanel(hSaveDataTipPanel);
					MessagePopup ("Tips", "Saved successfully");
					RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
					DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
				}
			}
			
			break;
	}
	return 0;
}


int CVICALLBACK SaveAllCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{  
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, SAVEDATA_GRAPH2PATH, graph2SavePath);   
			GetCtrlVal(panel, SAVEDATA_GRAPH1PATH, graph1SavePath);  
			GetCtrlVal(panel, SAVEDATA_SHEETPATH, sheetSavePath); 
			if((sheetSavePath[0]=='\0') || (graph1SavePath[0]=='\0') ||(graph2SavePath[0]=='\0') )
				 MessagePopup ("Message", "Please select a valod plot");   
			else
			{
				if(sheet == 1 && graph1==1 && graph2 ==1)
				{
					if(graphDispSelect==DISP_DOUBLE_GRAPH)	   //保存graph2时只有在选中双图模式才能
					{   
						InstallPopup(hSaveDataTipPanel);    
						SaveSheet(sheetSavePath); 
						if(FileExists(graph1SavePath,0)||FileExists(graph2SavePath,0))
							MessagePopup ("Tips", "The Picture file already exists, please choose a different path");   
					   	 else
						 {
							SaveGraph1(GRAPHDISP_GRAPH1,graph1SavePath);
							SaveGraphs(graph2SavePath);
							MessagePopup ("Tips", " successfully");     
						 }
						HidePanel(hSaveDataTipPanel);
						RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
						DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
					} 
					else
						MessagePopup ("Message", " Please select the 'Double Graph' mode.");  
				  }
				else if(sheet==1 && graph1==1)
				{   
					InstallPopup(hSaveDataTipPanel);     
					SaveSheet(sheetSavePath); 
					if(FileExists(graph1SavePath,0))
							MessagePopup ("Tips", "The Picture file already exists, please choose a different path");   
						else
						{
						 	SaveGraph1(GRAPHDISP_GRAPH1,graph1SavePath);     
							MessagePopup ("Tips", " successfully");                    
						}
					HidePanel(hSaveDataTipPanel);
					RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
					DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
				}
				else if(sheet==1 && graph2==1)			//保存graph2时默认保存两张图到一张图片上
				{
					if(graphDispSelect==DISP_DOUBLE_GRAPH)
					{  
						InstallPopup(hSaveDataTipPanel);                   
						SaveSheet(sheetSavePath); 
						if(FileExists(graph2SavePath,0))
							MessagePopup ("Tips", "The Picture file already exists, please choose a different path");   
						else
						{
						 	SaveGraphs(graph2SavePath);
							MessagePopup ("Tips", " successfully");                    
						}
						HidePanel(hSaveDataTipPanel);
						RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
						DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
					} 
					else
						MessagePopup ("Message", " Please select the 'Double Graph' mode.");  
				}
				else if(graph1==1 && graph2==1)
				{
					if(graphDispSelect==DISP_DOUBLE_GRAPH)
					{
						InstallPopup(hSaveDataTipPanel);  
						if(FileExists(graph1SavePath,0)||FileExists(graph2SavePath,0))
							MessagePopup ("Tips", "The Picture file already exists, please choose a different path");   
					   	 else
						 {
							SaveGraph1(GRAPHDISP_GRAPH1,graph1SavePath);     
							SaveGraphs(graph2SavePath);
							MessagePopup ("Tips", " successfully");           
						 }
						HidePanel(hSaveDataTipPanel);
						RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
						DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
					}
					else
						MessagePopup ("Message", " Please select the 'Double Graph' mode.");  
				 }
	 		   DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");  
		}
		break;
	}
	return 0;
}

//static int SaveGraph(int panel, int control, int plotHandle, const char path[])
//{
//	int bitmapID;
//	if(plotHandle<=0)		//no valid plot behavior
//		MessagePopup ("Message", "No valod plot. Please run test first.");
//	else
//	{
//		if(GetCtrlBitmap(panel, control, plotHandle,&bitmapID)<0)
//			return -1;
//		if(SaveBitmapToFile(path, bitmapID)<0)		 //need check the file format
//			return -1;
//		DiscardBitmap(bitmapID);
//	}
//	return 0;
//}


int CVICALLBACK SaveSheetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{	 
																		  
	switch (event)
	{									          
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, SAVEDATA_SHEETPATH, sheetSavePath);  
			if(sheetSavePath[0]=='\0')
				MessagePopup ("Message", "Please select a valod plot"); 
			else
			{
				InstallPopup(hSaveDataTipPanel);
				SaveSheet(sheetSavePath);
				HidePanel(hSaveDataTipPanel);
				MessagePopup ("Tips", "successfully");
				RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
			}
			break;
	}
   return 0;
}

int CVICALLBACK SaveDatePanelCallback (int panel, int event, void *callbackData,
									   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			RemovePopup(hSaveDataPanel);
			DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");     
			break;
	}
	return 0;
}

