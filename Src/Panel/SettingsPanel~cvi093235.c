#include <cvintwrk.h>
#include <rs232.h>
#include "cvixml.h"
#include "Settings.h"
#include <userint.h>
#include "LoadPanel.h"
#include "SettingsPanel.h"
#include "Curve.h"
#include"main.h"
#define VAL_TEXTBG                        0xF0F0F0L    //未被选中背景色
#define VAL_TEXTBG_PRESSED                0x065279L    //被选中背景色
#define MAX_SIZE   1024
//char buf[800];
//int vertDivision;
CurveAttrTypeDef Graph1_CurveAttr1;
CurveAttrTypeDef Graph1_CurveAttr2;
CurveAttrTypeDef Graph1_CurveAttr3;


 CurveAttrTypeDef Graph2_CurveAttr1;
 CurveAttrTypeDef Graph2_CurveAttr2;
 CurveAttrTypeDef Graph2_CurveAttr3;

char ProjectSavePath[512]="C:\\Sinoagg\\SA6101\\Users\\";	   //本地工作目录Dir

static int ftp_handle = -1;
static int error; 
static char attrName[MAX_SIZE];
static char getProjectDir[MAX_PATHNAME_LEN];
static char getProjectDirs[MAX_PATHNAME_LEN]; 
static char updateInfoPath[MAX_PATHNAME_LEN];
static char localInfoPath[MAX_PATHNAME_LEN]; 
static char updateHardFilePath[MAX_PATHNAME_LEN];
static char updateSoftFilePath[MAX_PATHNAME_LEN];
static char *serversSoftVersion = NULL;
static char *currentSoftVersion = NULL;
static char *serversUpdateVersion = NULL;
static char *currentUpdateVersion = NULL;
static char *serversHardVersion = NULL;
static char *currentHardVersion = NULL;

const char defaultUpdateVersion[] = "0.0.0";
static CVIXMLDocument	 hLoDocument = 0;
static CVIXMLDocument    hUpDocument = 0;
static CVIXMLElement	 hRootElem = 0;
static CVIXMLElement    hChildElem = 0;
static CVIXMLAttribute  hSoftwareCurrAttr = 0;
static CVIXMLAttribute  hUpdateCurrAttr = 0; 
static CVIXMLAttribute  hHardCurrAttr = 0; 



static void GetSingleCurveAttr(CurveAttrTypeDef *pCurveAttr, int GraphIndex, int CurveIndex)
{
	GetCtrlVal(hSettingsGraphPanel, SETGRAPH_LINE_STYLE, &(pCurveAttr->lineStyle));
	GetCtrlVal(hSettingsGraphPanel, SETGRAPH_PLOT_STYLE, &(pCurveAttr->plotStyle));
	GetCtrlVal(hSettingsGraphPanel, SETGRAPH_POINT_STYLE,&(pCurveAttr->pointStyle));
	//根据index获取颜色
													                                                                                                                                                                                                                                  
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR1,&(Graph1_CurveAttr1.lineColor));
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR2,&(Graph1_CurveAttr2.lineColor));
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR3,&(Graph1_CurveAttr3.lineColor)); 
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH2CLR1,&(Graph2_CurveAttr1.lineColor));
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH2CLR2,&(Graph2_CurveAttr2.lineColor));
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH2CLR3,&(Graph2_CurveAttr3.lineColor));
}

CurveAttrTypeDef* GetSettingsCurveAttr(int GraphIndex, int CurveIndex)
{
	
	if(GraphIndex==GRAPH1)  
	{
		switch(CurveIndex % 3)
		{
			case 0:
				GetSingleCurveAttr(&Graph1_CurveAttr1, GraphIndex, CurveIndex);
				pCurveAttr=&Graph1_CurveAttr1;
				break;
			case 1:
				GetSingleCurveAttr(&Graph1_CurveAttr2, GraphIndex, CurveIndex);       
				pCurveAttr=&Graph1_CurveAttr2;
				break;
			case 2:
				GetSingleCurveAttr(&Graph1_CurveAttr3, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph1_CurveAttr3;
				break;
			default:
				GetSingleCurveAttr(&Graph1_CurveAttr1, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph1_CurveAttr1;
				break;
		}
	}
	else if(GraphIndex==GRAPH2) 
	{
		switch(CurveIndex)
		{
			case CURVE1:
				GetSingleCurveAttr(&Graph2_CurveAttr1, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph2_CurveAttr1;
				break;
			case CURVE2:
				GetSingleCurveAttr(&Graph2_CurveAttr2, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph2_CurveAttr2;
				break;
			case CURVE3:
				GetSingleCurveAttr(&Graph2_CurveAttr3, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph2_CurveAttr3;
				break;
			default:
				GetSingleCurveAttr(&Graph2_CurveAttr1, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph2_CurveAttr1;
				break;
		}
	}
	return pCurveAttr;
}		   

int CVICALLBACK PrjBtnCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hSettingsPrjPanel, 5, 170);
			//SetPanelSize(hSettingsPrjPanel, 350, 650);
			DisplayPanel(hSettingsPrjPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment背景色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment文本颜色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph背景色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph文本颜色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about背景色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about文本颜色

			break;

	}
	return 0;
}

int CVICALLBACK GraphBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hSettingsGraphPanel, 5, 170);
			//SetPanelSize(hSettingsGraphPanel, 350, 650);
			DisplayPanel(hSettingsGraphPanel);
			HidePanel(hSettingsPrjPanel);
			HidePanel(hSettingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //graph背景色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //graph文本颜色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //about背景色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //about文本颜色
			break;
	}
	return 0;
}

int CVICALLBACK AboutBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hSettingsAboutPanel, 5, 170);
			//SetPanelSize(hSettingsAboutPanel, 350, 650);
			DisplayPanel(hSettingsAboutPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsPrjPanel);
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //about背景色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //about文本颜色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //graph背景色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //graph文本颜色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			break;
	}
	return 0;
}

int CVICALLBACK PrjDirCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:

			if(DirSelectPopup ("C:\\Sinoagg\\SA6101\\Users\\", "Select Directory", 1, 1, ProjectSavePath)>0)
			{
				SetCtrlVal(panel, ENVT_PROPATH, ProjectSavePath);
			}
			else
			{
				return -1;
			}
			break;
	}
	return 0;
}

int  CVICALLBACK SettingsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel(hSettingsPanel);  //恢复到第一个面板 并且所有界面效果在 Project Settings 上面
			SetPanelPos(hSettingsPrjPanel, 5, 170);
			//SetPanelSize(hSettingsPrjPanel, 350, 650);
			DisplayPanel(hSettingsPrjPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment背景色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment文本颜色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph背景色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph文本颜色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about背景色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about文本颜色
			break;
	}
	return 0;
}
int ReadFromConfigFile(char* temp,char* temp1)
{
	
	FILE* fp;
	char buf[40*1024]={0};
	int size;
	//temp1[0]=0X35;
	ComWrt(measureComPort,temp1, 30);
    Delay(1);
    temp1[0]='Y';
	fp=fopen(temp,"rb");
	if(fp!=NULL)
	{
		ComWrt(measureComPort,temp1, 1);
		Delay(0.1);
		size=fread(buf, 1,40*1024,fp);
		ComWrt(measureComPort,buf,size);
		Delay(3.5);
		*temp1 = 0;
		*(temp1+1) = 0; 
		*(temp1+29) = 0;
		ComWrt(measureComPort,temp1, 30);
		Delay(0.3); 
		ComWrt(measureComPort,temp1, 30);
		Delay(0.3);
		fclose(fp);
		MessagePopup ("Message", "Update successfully"); 
	}
	else
		MessagePopup ("Message", "File not found");	
	return 0;
}
//========================================小马哥写============================================================================
int HardwareSystemUpdate_Download()             //下载嵌入式硬件更新升级包 （下载文件）
{
	GetProjectDir (getProjectDir);
	if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)           //用户匿名登陆服务器
	{
		MessagePopup ("An Error Occurred", "Can't Connect To Server");
		return -1;
	}
	if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftp通信方式为主动模式
	{
		MessagePopup ("An Error Occurred", "Current communication mode is active mode");
		return -1;
	}
	if ((InetFTPChangeDir (ftp_handle, ".//SA6101//")) < 0)	
	{
		MessagePopup ("An Error Occurred", "Server current directory error");
		return -1;
	}
	MakePathname(getProjectDir, "..\\hardFileBackups\\SA6101.bin", updateHardFilePath);
	error = InetFTPRetrieveFile (ftp_handle, updateHardFilePath, ".//SA6101.bin", INET_FTP_FILE_TYPE_BINARY);
	if(error == -13)  
	{
		MessagePopup ("An Error Occurred", "Can't find the hardFileBackups file");
		return -2;	
	}
	if ( error < 0)  //下载服务器当前列表中的硬件文件
	{
		MessagePopup ("An Error Occurred", "Failed to download hardware file");
		return -1;
	}
	InetFTPClose(ftp_handle);
	return 0;
}

//============================================================================================================================  
void HardwareChange(int display)
{
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_TXTUPDATE, ATTR_VISIBLE, display);    //1文本显示
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_UPDATEHARD, ATTR_DIMMED, display);	  //1图片按钮不可点
}

void SoftwareChange(int display)
{
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_TXTUPDATE, ATTR_VISIBLE, display); 
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_UPDATESOFT, ATTR_DIMMED, display);
}
//============================================================================================================================
int CVICALLBACK UpdateHardware (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	char temp[MAX_PATHNAME_LEN]="..\\hardFileBackups\\SA6101.bin";
	char temp1[MAX_PATHNAME_LEN]={0x01,0x16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								  0,0,0,0,0,0,0,0,0,0,0x17};
	int i = 0;
	switch (event)
	{
	   case EVENT_LEFT_CLICK_UP:
			HardwareChange(1);
			int updateFlag = 0;
			updateFlag = GetVersions();
			if(updateFlag == -1)
			{
				MessagePopup ("Update failed", "Check your network connection");
				HardwareChange(0);     
				return 0;
			}
			if(updateFlag == -2) 
			{
				HardwareChange(0);        
				return 0;	
			}
		    i = CheckHardware();
			if(i == 1)
			{
				updateFlag = HardwareSystemUpdate_Download();
				if(updateFlag == -1)
				{
					MessagePopup ("Update failed", "Check your network connection");
					HardwareChange(0);        
					return 0;
				}
				if(updateFlag == -2)
				{
					HardwareChange(0);        
					return 0;	
				}
				CVIXMLSetAttributeValue (hHardCurrAttr, serversHardVersion);  //将修改本地xml文件中的版本号  
				CVIXMLSaveDocument (hLoDocument, 0, NULL);
				HardwareChange(0);        
				ReadFromConfigFile(temp,temp1);
			}
		    break;
	}
	return 0;
}

//============================================================================================================================  
 int SoftwareSystemUpdate_Download()             //下载软件更新升级包 （下载文件）
{
	int		num, i;
	char	**files = NULL;
	GetProjectDir (getProjectDir);
	if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)//用户匿名登陆服务器
	{
		MessagePopup ("An Error Occurred", "Can't Connect To Server");
		return -1;
	}
	if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftp通信方式为主动模式
	{
		MessagePopup ("An Error Occurred", "Current communication mode is active mode");
		return -1;
	}
	if ((InetFTPChangeDir (ftp_handle, ".//SA6101//SA6101//Resource//")) < 0)
	{
		MessagePopup ("An Error Occurred", "Server current directory error");
		return -1;
	}
	if (( InetFTPGetDirList (ftp_handle, &files, &num)) < 0) 
	{
		MessagePopup ("An Error Occurred", "Failed to get directory list");
		return -1;
	}
	MakePathname(getProjectDir, "..\\softwareFileBackups\\Resource\\", getProjectDirs);
	MakePathname(getProjectDirs, files[2], updateSoftFilePath);
	error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[2], INET_FTP_FILE_TYPE_BINARY);  //下载服务器当前列表中的软件文件
	if(error == -13)
	{
		MessagePopup ("An Error Occurred", "Can't find the softwareFileBackups\\Resource file");
			return -2;
	}
	for(i = 2;i<num;i++)
		{    
			 MakePathname(getProjectDir, "..\\softwareFileBackups\\Resource\\", getProjectDirs);
			 MakePathname(getProjectDirs, files[i], updateSoftFilePath);
		     if((InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[i], INET_FTP_FILE_TYPE_BINARY)) < 0)  //下载服务器当前列表中的软件文件
			 {
				 MessagePopup ("An Error Occurred", "Check the network");
				 return -1;
			 }
		}
	if ((InetFTPChangeDir (ftp_handle, "..//Uir//")) < 0)
	{
	   MessagePopup ("An Error Occurred", "Server current directory error");
	   return -1;
	}
	if ((InetFTPGetDirList (ftp_handle, &files, &num)) < 0)
	{
		MessagePopup ("An Error Occurred", "Failed to get directory list"); 
		return -1;
	}
	MakePathname(getProjectDir, "..\\softwareFileBackups\\Uir\\", getProjectDirs);
	MakePathname(getProjectDirs, files[2], updateSoftFilePath);
	error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[2], INET_FTP_FILE_TYPE_BINARY);  //下载服务器当前列表中的软件文件
	if(error == -13)
	{
		MessagePopup ("An Error Occurred", "Can't find the softwareFileBackups\\Uir file");
			return -2;
	}
	for(i = 2;i<num;i++)
		{    
			 MakePathname(getProjectDir, "..\\softwareFileBackups\\Uir\\", getProjectDirs);
			 MakePathname(getProjectDirs, files[i], updateSoftFilePath);
		     if((InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[i], INET_FTP_FILE_TYPE_BINARY)) < 0)   //下载服务器当前列表中的软件文件
		     {
				 MessagePopup ("An Error Occurred", "Check the network");
				 return -1;
			 } 
		}
	InetFTPClose(ftp_handle);
	return 0;
}
//============================================================================================================================  

int CVICALLBACK UpdateSoftware (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{   	
	int updateFlag = 0;
	int temp = 0; 
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			 
			SoftwareChange(1);
			updateFlag = GetVersions();
			if(updateFlag == -1)
			{
				MessagePopup ("Update failed", "Check your network connection");
				/*SoftwareChange(0);      */
				return 0;
			}
			if(updateFlag == -2)
			{
			/*	SoftwareChange(0);  */
				return 0;
				
				
			}
			
			       
			temp = CheckSoftware();//检车软件是否为最新
			if(temp == 1)
			{
				updateFlag = SoftwareSystemUpdate_Download();
				if(updateFlag == -1)
				{
					MessagePopup ("Update failed", "Check your network connection");
				/*	SoftwareChange(0);  */
					return 0;
				}
				if(updateFlag == -2)
				{
				/*	SoftwareChange(0);  */
					return 0;
				}
				CVIXMLLoadDocument (localInfoPath, &hLoDocument);
				CVIXMLGetRootElement (hLoDocument, &hRootElem);
				CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //获得标签SoftwareVersion 子元素
				CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
				CVIXMLSetAttributeValue (hSoftwareCurrAttr, serversSoftVersion);  //将修改本地xml文件中的版本号  
				CVIXMLSaveDocument (hLoDocument, 0, NULL);
				SoftwareChange(0);  
				MessagePopup ("Warning", "Update successfully");
				QuitUserInterface (0);
				LaunchExecutableEx ("..\\updates\\replace.exe", LE_HIDE, &ftp_handle);
			} 
			
		break;
	}
	return 0;
}
//============================================================================================================================  
int GetVersions()
{
	int		num, i;
	char	**files = NULL;
	int len;
	
    if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)           //用户匿名登陆服务器
	{
		MessagePopup ("An Error Occurred", "Can't Connect To Server");
		return -1;
	}
	if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftp通信方式为主动模式
	{
		MessagePopup ("An Error Occurred", "Current communication mode is active mode");
		return -1;
	}
	if ((InetFTPChangeDir (ftp_handle, ".//SA6101//updates")) < 0)			
	{
		MessagePopup ("An Error Occurred", "Server current directory error");
		return -1;
	}
	if (( InetFTPGetDirList (ftp_handle, &files, &num)) < 0) 
	{
		MessagePopup ("An Error Occurred", "Failed to get directory list");
		return -1;
	}
	GetProjectDir (getProjectDir);  
	MakePathname(getProjectDir, "..\\updates\\", getProjectDirs);
	MakePathname(getProjectDirs, files[4], updateSoftFilePath); 
	error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[4], INET_FTP_FILE_TYPE_BINARY);
	if(error == -13)  
	{
		MessagePopup ("An Error Occurred", "Can't find the updates file");
		return -2;	
	}
	for(i = 3;i<num;i++)
	{    
		MakePathname(getProjectDirs, files[i], updateSoftFilePath);
		error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[i], INET_FTP_FILE_TYPE_BINARY);
		if(error < 0)
		{
			MessagePopup ("An Error Occurred", "Can't Connect To Server");
			return -1;	
		}
	}
	InetFTPClose(ftp_handle); 
	GetProjectDir (getProjectDir);  
	MakePathname(getProjectDir, "..\\updates\\", getProjectDirs);
	MakePathname(getProjectDirs, "updateInfo.xml", updateInfoPath);
	MakePathname(getProjectDirs, "localInfo.xml", localInfoPath);
	
	CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
	CVIXMLGetRootElement (hUpDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //获得标签UpdateVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
	CVIXMLGetAttributeNameLength(hUpdateCurrAttr, &len);
	CVIXMLGetAttributeValueLength (hUpdateCurrAttr, &len);
	serversUpdateVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hUpdateCurrAttr,serversUpdateVersion);   //从服务器下载.xml文件到本地目录下，再从该XML文件中获取最新更新版本号
     
    CVIXMLLoadDocument (localInfoPath, &hLoDocument);
	CVIXMLGetRootElement (hLoDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //获得标签UpdateVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
	CVIXMLGetAttributeNameLength(hUpdateCurrAttr, &len);
	CVIXMLGetAttributeValueLength (hUpdateCurrAttr, &len);
	currentUpdateVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hUpdateCurrAttr,currentUpdateVersion);   //从本地目录下XML文件中获取软件当前版本号
	
	CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
	CVIXMLGetRootElement (hUpDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //获得标签SoftwareVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
	CVIXMLGetAttributeNameLength(hSoftwareCurrAttr, &len);
	CVIXMLGetAttributeName(hSoftwareCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hSoftwareCurrAttr, &len);
	serversSoftVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hSoftwareCurrAttr,serversSoftVersion);   //从服务器下载.xml文件到本地目录下，再从该XML文件中获取最新软件版本号
    
	
    CVIXMLLoadDocument (localInfoPath, &hLoDocument);
	CVIXMLGetRootElement (hLoDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //获得标签SoftwareVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
	CVIXMLGetAttributeNameLength(hSoftwareCurrAttr, &len);
	CVIXMLGetAttributeName(hSoftwareCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hSoftwareCurrAttr, &len);
	currentSoftVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hSoftwareCurrAttr,currentSoftVersion);   //从本地目录下XML文件中获取软件当前版本号

	CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
	CVIXMLGetRootElement (hUpDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "HardwareVersion", &hChildElem); //获得标签HardwareVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hHardCurrAttr);
	CVIXMLGetAttributeNameLength(hHardCurrAttr, &len);
	CVIXMLGetAttributeName(hHardCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hHardCurrAttr, &len);
	serversHardVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hHardCurrAttr,serversHardVersion);   //从服务器下载.xml文件到本地目录下，再从该XML文件中获取最新硬件版本号
	
	CVIXMLLoadDocument (localInfoPath, &hLoDocument);
	CVIXMLGetRootElement (hLoDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "HardwareVersion", &hChildElem); //获得标签HardwareVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hHardCurrAttr);
	CVIXMLGetAttributeNameLength(hHardCurrAttr, &len);
	CVIXMLGetAttributeName(hHardCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hHardCurrAttr, &len);
	currentHardVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hHardCurrAttr,currentHardVersion);   //从本地目录下XML文件中获取硬件当前版本号
	
	return 0;
}

//============================================================================================================================  
int	CheckSoftware()   //检车软件是否为最新  
{
	int i, len = 5;
	for(i=0;i<=len;i++)
	{
	 if(serversSoftVersion[i] != currentSoftVersion[i])
	 {
		int temp = ConfirmPopup ("Version update", "Whether to update to the latest Software version");  //更新软件版本提醒
		if(temp  == 1)
		{
			return 1;
		}else
		{
			MessagePopup ("Warning", "Please update");
			SoftwareChange(0);  
			return 0;
		}
	 }
	if(i == 5)
	 {
		MessagePopup ("Warning", "It is the latest Software version");
		SoftwareChange(0);  
	  }
	}
	return 0;
}
//============================================================================================================================  
int	CheckHardware()   //检车硬件是否为最新
{
	int	len = 5,j;
	for(j=0;j<=len;j++)
	{
		 if(serversHardVersion[j] != currentHardVersion[j])
		 {
			int temp = ConfirmPopup ("Version update", "Whether to update to the latest hard version");  //更新软件版本提醒
			if(temp  == 1)return 1;
			else
			{
				MessagePopup ("Warning", "Please update");
				HardwareChange(0);        
				return 0;
			}
		 }
		if(j == 5)
		{
			MessagePopup ("Warning", "It is the latest hard version");
			HardwareChange(0);
		 }
	}
	return 0;
}
//============================================================================================================================  

int CVICALLBACK TxtSoftwareCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
				SoftwareChange(1); 
			//UpdateSoftware ( panel,control, event,callbackData, eventData1, eventData2);
			break;
	}
	return 0;
}
int CVICALLBACK TxtHardwareCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			UpdateHardware (panel,  control, event,callbackData,  eventData1, eventData2) ;
			break;
	}
	return 0;
}

int CVICALLBACK testCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
				SoftwareChange(1);  
				//UpdateHardware (panel,  control, event,callbackData,  eventData1, eventData2) ;      
			break;
		case EVENT_RIGHT_DOUBLE_CLICK:
				SoftwareChange(0);          
			break;
			
	}
	return 0;
}
