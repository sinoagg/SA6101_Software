#include <cvintwrk.h>
#include <rs232.h>
#include "cvixml.h"
#include "Settings.h"
#include <userint.h>
#include "LoadPanel.h"
#include "SettingsPanel.h"
 #include "progressbar.h"   
#include "Curve.h"
#include"main.h"
#define VAL_TEXTBG                        0xF0F0F0L    //δ��ѡ�б���ɫ
#define VAL_TEXTBG_PRESSED                0x065279L    //��ѡ�б���ɫ
#define MAX_SIZE   1024
CurveAttrTypeDef Graph1_CurveAttr1;
CurveAttrTypeDef Graph1_CurveAttr2;
CurveAttrTypeDef Graph1_CurveAttr3;


 CurveAttrTypeDef Graph2_CurveAttr1;
 CurveAttrTypeDef Graph2_CurveAttr2;
 CurveAttrTypeDef Graph2_CurveAttr3;

char ProjectSavePath[512]="C:\\Sinoagg\\SA6101\\Users\\";	   //���ع���Ŀ¼Dir

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

static char *currentSoftVersion1 = NULL; 
static char *serversUpdateVersion = NULL;
static char *currentUpdateVersion = NULL;
static char *serversHardVersion = NULL;
static char *currentHardVersion = NULL;

const char defaultUpdateVersion[] = "0.0.0";
static CVIXMLDocument	 hLoDocument = 0;
static CVIXMLDocument    hUpDocument = 0;
static CVIXMLElement	 hRootElem = 0;
static CVIXMLElement    hChildElem = 0;
static CVIXMLElement    hTestElem = 0;  
static CVIXMLAttribute  hSoftwareCurrAttr = 0;
static CVIXMLAttribute  hSoftwareCurrAttr1 = 0;
static CVIXMLAttribute  hUpdateCurrAttr = 0; 
static CVIXMLAttribute  hHardCurrAttr = 0; 
int MSGCTRL;

static int testFlag = 0;
static void GetSingleCurveAttr(CurveAttrTypeDef *pCurveAttr, int GraphIndex, int CurveIndex)
{
	GetCtrlVal(hSettingsGraphPanel, SETGRAPH_LINE_STYLE, &(pCurveAttr->lineStyle));
	GetCtrlVal(hSettingsGraphPanel, SETGRAPH_PLOT_STYLE, &(pCurveAttr->plotStyle));
	GetCtrlVal(hSettingsGraphPanel, SETGRAPH_POINT_STYLE,&(pCurveAttr->pointStyle));
	//����index��ȡ��ɫ
													                                                                                                                                                                                                                                  
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
			DisplayPanel(hSettingsPrjPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment����ɫ
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph����ɫ
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about����ɫ
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about�ı���ɫ

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
			DisplayPanel(hSettingsGraphPanel);
			HidePanel(hSettingsPrjPanel);
			HidePanel(hSettingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //graph����ɫ
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //graph�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment����ɫ
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //about����ɫ
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //about�ı���ɫ
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
//===============================20181117������ʾ�汾�Ź��ܣ�С���д===================================================================================================
		/*	int hardwareCircuitVersions;	  //Ӳ����·
			int embeddedSoftwareVersions;	  //Ƕ��ʽ��� 
			int mechanicalPowerVersions;	  //��е��ǵ�Դ
			int testVersions;                 //�ڲ�汾
			int softwareVersions;
			int len = 0; 
			SetPanelPos(hSettingsAboutPanel, 5, 170);
			SetPanelSize(hSettingsAboutPanel, 350, 650);
		    hardwareCircuitVersions =  (IDAddrress[7] - '0') * 100 +  (IDAddrress[8] - '0') * 10 + (IDAddrress[9] - '0');
			embeddedSoftwareVersions =  (IDAddrress[10] - '0') * 100 +  (IDAddrress[11] - '0') * 10 + (IDAddrress[12] - '0');
			mechanicalPowerVersions =  (IDAddrress[13] - '0') * 100 +  (IDAddrress[14] - '0') * 10 + (IDAddrress[15] - '0');
			
			GetProjectDir (getProjectDir);  
			MakePathname(getProjectDir, "..\\updates\\", getProjectDirs);
			MakePathname(getProjectDirs, "localInfo.xml", localInfoPath);
			
		
			CVIXMLLoadDocument (localInfoPath, &hLoDocument);
			CVIXMLGetRootElement (hLoDocument, &hRootElem);
			CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //��ñ�ǩSoftwareVersion ��Ԫ��
			CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
			
			
			
			CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion ", &hTestElem); //��ñ�ǩSoftwareVersion ��Ԫ��         
			CVIXMLGetAttributeByIndex(hTestElem, 0, &hSoftwareCurrAttr1);
			
			
			CVIXMLGetAttributeNameLength(hSoftwareCurrAttr, &len);
			CVIXMLGetAttributeName(hSoftwareCurrAttr, attrName);
			CVIXMLGetAttributeValueLength (hSoftwareCurrAttr, &len);
			
			
			CVIXMLGetAttributeNameLength(hSoftwareCurrAttr1, &len);
			CVIXMLGetAttributeName(hSoftwareCurrAttr1, attrName);
			CVIXMLGetAttributeValueLength (hSoftwareCurrAttr1, &len);
			
			
			
			currentSoftVersion = malloc (len + 1); 
			currentSoftVersion1= malloc (len + 1);        
			
			
			CVIXMLGetAttributeValue(hSoftwareCurrAttr,currentSoftVersion);   //�ӱ���Ŀ¼��XML�ļ��л�ȡ�����ǰ�汾��
			
			CVIXMLGetAttributeValue(hSoftwareCurrAttr1,currentSoftVersion1);   //�ӱ���Ŀ¼��XML�ļ��л�ȡ�����ǰ�汾��    
			softwareVersions =  (currentSoftVersion[4] - '0') * 100 +  (currentSoftVersion[5]- '0') * 10 + (currentSoftVersion[6]- '0'); 
			testVersions =  (currentSoftVersion1[1] - '0') * 100 +  (currentSoftVersion1[2]- '0') * 10 + (currentSoftVersion1[3]- '0');      
			SetCtrlVal (hSettingsAboutPanel, ABOUT_NUMERIC_HCV, hardwareCircuitVersions);   //�޸�ABOUT������Ӳ����·�汾��
			SetCtrlVal (hSettingsAboutPanel, ABOUT_NUMERIC_ESV, embeddedSoftwareVersions);
			SetCtrlVal (hSettingsAboutPanel, ABOUT_NUMERIC_SV, softwareVersions);  
			SetCtrlVal (hSettingsAboutPanel, ABOUT_NUMERIC_MPV, testVersions);   //���԰汾                */
			int hardwareCircuitVersions;	  //Ӳ����·
			int embeddedSoftwareVersions;	  //Ƕ��ʽ��� 
			int mechanicalPowerVersions;	  //��е��ǵ�Դ
			int softwareVersions;
			int len = 0; 
			SetPanelPos(hSettingsAboutPanel, 5, 170);
			SetPanelSize(hSettingsAboutPanel, 350, 650);
		    hardwareCircuitVersions =  (IDAddrress[7] - '0') * 100 +  (IDAddrress[8] - '0') * 10 + (IDAddrress[9] - '0');
			embeddedSoftwareVersions =  (IDAddrress[10] - '0') * 100 +  (IDAddrress[11] - '0') * 10 + (IDAddrress[12] - '0');
			mechanicalPowerVersions =  (IDAddrress[13] - '0') * 100 +  (IDAddrress[14] - '0') * 10 + (IDAddrress[15] - '0');
			GetProjectDir (getProjectDir);  
			MakePathname(getProjectDir, "..\\updates\\", getProjectDirs);
			MakePathname(getProjectDirs, "localInfo.xml", localInfoPath);
			CVIXMLLoadDocument (localInfoPath, &hLoDocument);
			CVIXMLGetRootElement (hLoDocument, &hRootElem);
			CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //��ñ�ǩSoftwareVersion ��Ԫ��
			CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
			CVIXMLGetAttributeNameLength(hSoftwareCurrAttr, &len);
			CVIXMLGetAttributeName(hSoftwareCurrAttr, attrName);
			CVIXMLGetAttributeValueLength (hSoftwareCurrAttr, &len);
			currentSoftVersion = malloc (len + 1); 
			CVIXMLGetAttributeValue(hSoftwareCurrAttr,currentSoftVersion);   //�ӱ���Ŀ¼��XML�ļ��л�ȡ�����ǰ�汾��
			softwareVersions =  (currentSoftVersion[4] - '0') * 100 +  (currentSoftVersion[5]- '0') * 10 + (currentSoftVersion[6]- '0'); 
			SetCtrlVal (hSettingsAboutPanel, ABOUT_NUMERIC_HCV, hardwareCircuitVersions);   //�޸�ABOUT������Ӳ����·�汾��
			SetCtrlVal (hSettingsAboutPanel, ABOUT_NUMERIC_ESV, embeddedSoftwareVersions);
		//	SetCtrlVal (hSettingsAboutPanel, ABOUT_NUMERIC_MPV, mechanicalPowerVersions);
			SetCtrlVal (hSettingsAboutPanel, ABOUT_NUMERIC_SV, softwareVersions);  
//=======================================================================================================================================    
			DisplayPanel(hSettingsAboutPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsPrjPanel);
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //about����ɫ
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //about�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //graph����ɫ
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //graph�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment����ɫ
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment�ı���ɫ
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
			HidePanel(hSettingsPanel);  													   //�ָ�����һ����� �������н���Ч���� Project Settings ����
			SetPanelPos(hSettingsPrjPanel, 5, 170);
			DisplayPanel(hSettingsPrjPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment����ɫ
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph����ɫ
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph�ı���ɫ
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about����ɫ
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about�ı���ɫ
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
	ComWrt(measureComPort,temp1, 32);
    Delay(1);
    temp1[0]='Y';
	fp=fopen(temp,"rb");
	if(fp!=NULL)
	{
		ComWrt(measureComPort,temp1, 1);
		Delay(0.1);
		size=fread(buf, 1,40*1024,fp);
		ComWrt(measureComPort,buf,size);
		Delay(4);
		*temp1 = 0;
		*(temp1+1) = 0; 
		*(temp1+31) = 0;
		ComWrt(measureComPort,temp1, 32);
		Delay(0.3); 
		ComWrt(measureComPort,temp1, 32);
		Delay(0.3);
		fclose(fp);
		MessagePopup ("Message", "Update successfully"); 
	}
	else
		MessagePopup ("Message", "File not found");	
	return 0;
}
//========================================С���д============================================================================
int HardwareSystemUpdate_Download()             //����Ƕ��ʽӲ������������ �������ļ���
{
	GetProjectDir (getProjectDir);
	if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)           //�û�������½������
	{
		MessagePopup ("An Error Occurred", "Can't Connect To Server");
		return -1;
	}
	if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftpͨ�ŷ�ʽΪ����ģʽ
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
	SetCtrlVal (hSettingsAboutPanel, ABOUT_FILEDIS_TEXTMSG, updateHardFilePath);  
	error = InetFTPRetrieveFile (ftp_handle, updateHardFilePath, ".//SA6101.bin", INET_FTP_FILE_TYPE_BINARY);
	if(error == -13)  
	{
		MessagePopup ("An Error Occurred", "Can't find the hardFileBackups file");
		return -2;	
	}
	if ( error < 0)  //���ط�������ǰ�б��е�Ӳ���ļ�
	{
		MessagePopup ("An Error Occurred", "Failed to download hardware file");
		return -1;
	}
	ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 100, 0); 
	InetFTPClose(ftp_handle);
	return 0;
}

//============================================================================================================================  
void HardwareChange(int display)
{
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_TEXTMSG, ATTR_VISIBLE, display);    //�������С��ı���ʾ
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_FILEDIS_TEXTMSG, ATTR_VISIBLE, display);	  //��·�����ı���ʾ
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_PROGRESSBAR, ATTR_VISIBLE, display);	 //�����������ı���ʾ
}

void SoftwareChange(int display)
{
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_TEXTMSG, ATTR_VISIBLE, display);    //�������С��ı���ʾ
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_FILEDIS_TEXTMSG, ATTR_VISIBLE, display);	  //��·�����ı���ʾ
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_PROGRESSBAR, ATTR_VISIBLE, display);	 //�����������ı���ʾ
}
//========================20181117�����޸�ID�Ź���;С���д==================================================================================================== 
void SendVersion()
{
	char version[] = {0x00, 0xFE, 0x06, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00,
					  0x07, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x07, 0x01, 
					  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00};		  //6101 00 107 110 101 0017 1
	int embeddedSoftwareVersion; 
	embeddedSoftwareVersion = (serversHardVersion[4] - '0') * 100 +  (serversHardVersion[5] - '0') * 10 +  (serversHardVersion[6]  - '0');	
	version[11] =  embeddedSoftwareVersion / 100; 
	version[12] =  (embeddedSoftwareVersion / 10) % 10;
	version[13] =  embeddedSoftwareVersion % 100 % 10;
	int i;
	for(i=0;i<31;i++)
	{
		version[31]^=version[i];
	}
	ComWrt(measureComPort, version, 32);
}
//==============================================================================================================================================================
//============================================================================================================================
int CVICALLBACK UpdateHardware (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	char temp[MAX_PATHNAME_LEN]="..\\hardFileBackups\\SA6101.bin";
	char temp1[MAX_PATHNAME_LEN]={0x01,0x16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x17};
	char updateHard[MAX_PATHNAME_LEN]={0x01,0x17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x16}; 
	char USART_RX_Buffer[60];
	int i = 0;
	int strLen;
	switch (event)
	{
	   case EVENT_LEFT_CLICK_UP:
			HardwareChange(1);
			//=====================================201811091754����============================================================  
			ProgressBar_ConvertFromSlide (hSettingsAboutPanel, ABOUT_PROGRESSBAR);
			ProgressBar_SetAttribute (hSettingsAboutPanel, ABOUT_PROGRESSBAR, ATTR_PROGRESSBAR_UPDATE_MODE, VAL_PROGRESSBAR_MANUAL_MODE);
			ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 5, 0);
			//=================================================================================================
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
				ComWrt(measureComPort,updateHard,32);
				Delay(3);
				strLen = GetInQLen(measureComPort);
				ComRd(measureComPort,USART_RX_Buffer,strLen);
				if((USART_RX_Buffer[0] == 0x01) && (USART_RX_Buffer[1] == 0x17))
				{
				  	CVIXMLSetAttributeValue (hHardCurrAttr, serversHardVersion);  //���޸ı���xml�ļ��еİ汾��  
					CVIXMLSaveDocument (hLoDocument, 0, NULL);
					HardwareChange(0);
					ReadFromConfigFile(temp,temp1);
					SendVersion(); 
					FlushInQ(measureComPort);
					FlushOutQ(measureComPort);
					measure_Uart_Flag=0;       
				}
				else
				{
					MessagePopup ("Tips", "Update failed");                 
				  	FlushInQ(measureComPort);
					FlushOutQ(measureComPort);
				}
			}
		    break;
	}
	return 0;
}

//============================================================================================================================  
 int SoftwareSystemUpdate_Download()             //����������������� �������ļ���
{
	int		num, i;
	double j = 1.0; 
	char	**files = NULL;
	GetProjectDir (getProjectDir);
	if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)//�û�������½������
	{
		MessagePopup ("An Error Occurred", "Can't Connect To Server");
		return -1;
	}
	if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftpͨ�ŷ�ʽΪ����ģʽ
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
	error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[2], INET_FTP_FILE_TYPE_BINARY);  //���ط�������ǰ�б��е�����ļ�
	if(error == -13)
	{
		MessagePopup ("An Error Occurred", "Can't find the softwareFileBackups\\Resource file");
			return -2;
	}
	for(i = 2;i<num;i++)
		{    
			 MakePathname(getProjectDir, "..\\softwareFileBackups\\Resource\\", getProjectDirs);
			 MakePathname(getProjectDirs, files[i], updateSoftFilePath);
			 SetCtrlVal (hSettingsAboutPanel, ABOUT_FILEDIS_TEXTMSG, updateSoftFilePath);
		     if((InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[i], INET_FTP_FILE_TYPE_BINARY)) < 0)  //���ط�������ǰ�б��е�����ļ�
			 {
				 MessagePopup ("An Error Occurred", "Check the network");
				 return -1;
			 }
			 ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 20+j, 0); 
			 j+=(40.0/(num - 2));
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
	error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[2], INET_FTP_FILE_TYPE_BINARY);  //���ط�������ǰ�б��е�����ļ�
	if(error == -13)
	{
		MessagePopup ("An Error Occurred", "Can't find the softwareFileBackups\\Uir file");
			return -2;
	}
	j = 1.0;
	for(i = 2;i<num;i++)
		{    
			 MakePathname(getProjectDir, "..\\softwareFileBackups\\Uir\\", getProjectDirs);
			 MakePathname(getProjectDirs, files[i], updateSoftFilePath);
			 SetCtrlVal (hSettingsAboutPanel, ABOUT_FILEDIS_TEXTMSG, updateSoftFilePath); 
		     if((InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[i], INET_FTP_FILE_TYPE_BINARY)) < 0)   //���ط�������ǰ�б��е�����ļ�
		     {
				 MessagePopup ("An Error Occurred", "Check the network");
				 return -1;
			 } 
			 ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 60+j, 0);
			 j+=(40.0/(num - 2));
		}
	ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR,100.0, 0); 
	InetFTPClose(ftp_handle);
	return 0;
}
//============================================================================================================================  
int	CheckTestSoftware()   //�쳵����Ƿ�Ϊ����  
{
	int i;
	int len = strlen(serversUpdateVersion);
	for(i=0;i<=len;i++)
	{
	 if(serversUpdateVersion[i] != currentUpdateVersion[i])
	 { 	int temp = ConfirmPopup ("Version update", "Whether to update to the latest Software version");  //��������汾����              
		if(temp  == 1)		//ok
		{ 	
			return 1;
		}else				//ȡ��
		{
			MessagePopup ("Warning", "Please update");
			SoftwareChange(0);      
			return 0;
		}
	 }
	if(i == len)
	 {
		MessagePopup ("Warning", "It is the latest Software version");
		SoftwareChange(0);  
	  }
	}
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
		case EVENT_LEFT_CLICK_UP:
			SoftwareChange(1);
			//=====================================201811091754����============================================================   
			ProgressBar_ConvertFromSlide (hSettingsAboutPanel, ABOUT_PROGRESSBAR);
			ProgressBar_SetAttribute (hSettingsAboutPanel, ABOUT_PROGRESSBAR, ATTR_PROGRESSBAR_UPDATE_MODE, VAL_PROGRESSBAR_MANUAL_MODE);
			ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 5, 0);
			//=================================================================================================
			updateFlag = GetVersions();
			if(updateFlag == -1)
			{
				MessagePopup ("Update failed", "Check your network connection");
				SoftwareChange(0);      
				return 0;
			}
			if(updateFlag == -2)
			{
	 			SoftwareChange(0);
				return 0;
			}
			if(testFlag==1)
			{
				temp = CheckTestSoftware();//�쳵����Ƿ�Ϊ����  
			}
			else
			{
				temp = CheckSoftware();//�쳵����Ƿ�Ϊ����  	
			}
			if(temp == 1)
			{
				updateFlag = SoftwareSystemUpdate_Download();
				if(updateFlag == -1)
				{
					MessagePopup ("Update failed", "Check your network connection");
					SoftwareChange(0);  
					return 0;
				}
				if(updateFlag == -2)
				{
					SoftwareChange(0);
					return 0;
				}
				CVIXMLLoadDocument (localInfoPath, &hLoDocument);
				CVIXMLGetRootElement (hLoDocument, &hRootElem);
				CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //��ñ�ǩSoftwareVersion ��Ԫ��
				CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
				CVIXMLSetAttributeValue (hSoftwareCurrAttr, serversSoftVersion);  //���޸ı���xml�ļ��еİ汾��  
				
				CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //��ñ�ǩUpdateVersion ��Ԫ��
				CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
				CVIXMLSetAttributeValue (hUpdateCurrAttr, serversUpdateVersion);  //���޸ı���xml�ļ��еİ汾��  
				
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
	double j = 1.0;
	char	**files = NULL;
	int len;
	
    if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)           //�û�������½������
	{
		MessagePopup ("An Error Occurred", "Can't Connect To Server");
		return -1;
	}
	if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftpͨ�ŷ�ʽΪ����ģʽ
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
		SetCtrlVal (hSettingsAboutPanel, ABOUT_FILEDIS_TEXTMSG, updateSoftFilePath); 
		error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[i], INET_FTP_FILE_TYPE_BINARY);
		if(error < 0)
		{
			MessagePopup ("An Error Occurred", "Can't Connect To Server");
			return -1;	
		}
		ProgressBar_SetPercentage (hSettingsAboutPanel, ABOUT_PROGRESSBAR, 5+j, 0); 
		j+=(5.0/(num - 2));
	}
	InetFTPClose(ftp_handle); 
	GetProjectDir (getProjectDir);  
	MakePathname(getProjectDir, "..\\updates\\", getProjectDirs);
	MakePathname(getProjectDirs, "updateInfo.xml", updateInfoPath);
	MakePathname(getProjectDirs, "localInfo.xml", localInfoPath);
	
	CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
	CVIXMLGetRootElement (hUpDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //��ñ�ǩUpdateVersion ��Ԫ��
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
	CVIXMLGetAttributeNameLength(hUpdateCurrAttr, &len);
	CVIXMLGetAttributeValueLength (hUpdateCurrAttr, &len);
	serversUpdateVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hUpdateCurrAttr,serversUpdateVersion);   //�ӷ���������.xml�ļ�������Ŀ¼�£��ٴӸ�XML�ļ��л�ȡ���¸��°汾��
     
    CVIXMLLoadDocument (localInfoPath, &hLoDocument);
	CVIXMLGetRootElement (hLoDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //��ñ�ǩUpdateVersion ��Ԫ��
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
	CVIXMLGetAttributeNameLength(hUpdateCurrAttr, &len);
	CVIXMLGetAttributeValueLength (hUpdateCurrAttr, &len);
	currentUpdateVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hUpdateCurrAttr,currentUpdateVersion);   //�ӱ���Ŀ¼��XML�ļ��л�ȡ�����ǰ�汾��
	
	CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
	CVIXMLGetRootElement (hUpDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //��ñ�ǩSoftwareVersion ��Ԫ��
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
	CVIXMLGetAttributeNameLength(hSoftwareCurrAttr, &len);
	CVIXMLGetAttributeName(hSoftwareCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hSoftwareCurrAttr, &len);
	serversSoftVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hSoftwareCurrAttr,serversSoftVersion);   //�ӷ���������.xml�ļ�������Ŀ¼�£��ٴӸ�XML�ļ��л�ȡ��������汾��
    
	
    CVIXMLLoadDocument (localInfoPath, &hLoDocument);
	CVIXMLGetRootElement (hLoDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //��ñ�ǩSoftwareVersion ��Ԫ��
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
	CVIXMLGetAttributeNameLength(hSoftwareCurrAttr, &len);
	CVIXMLGetAttributeName(hSoftwareCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hSoftwareCurrAttr, &len);
	currentSoftVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hSoftwareCurrAttr,currentSoftVersion);   //�ӱ���Ŀ¼��XML�ļ��л�ȡ�����ǰ�汾��

	CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
	CVIXMLGetRootElement (hUpDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "HardwareVersion", &hChildElem); //��ñ�ǩHardwareVersion ��Ԫ��
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hHardCurrAttr);
	CVIXMLGetAttributeNameLength(hHardCurrAttr, &len);
	CVIXMLGetAttributeName(hHardCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hHardCurrAttr, &len);
	serversHardVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hHardCurrAttr,serversHardVersion);   //�ӷ���������.xml�ļ�������Ŀ¼�£��ٴӸ�XML�ļ��л�ȡ����Ӳ���汾��
	
	CVIXMLLoadDocument (localInfoPath, &hLoDocument);
	CVIXMLGetRootElement (hLoDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "HardwareVersion", &hChildElem); //��ñ�ǩHardwareVersion ��Ԫ��
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hHardCurrAttr);
	CVIXMLGetAttributeNameLength(hHardCurrAttr, &len);
	CVIXMLGetAttributeName(hHardCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hHardCurrAttr, &len);
	currentHardVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hHardCurrAttr,currentHardVersion);   //�ӱ���Ŀ¼��XML�ļ��л�ȡӲ����ǰ�汾��
	return 0;
}
//============================================================================================================================  
int	CheckSoftware()   //�쳵����Ƿ�Ϊ����  
{
	int i;
	int len = strlen(serversSoftVersion);
	for(i=0;i<=len;i++)
	{
	 if(serversSoftVersion[i] != currentSoftVersion[i])
	 { 	int temp = ConfirmPopup ("Version update", "Whether to update to the latest Software version");  //��������汾����              
		if(temp  == 1)		//ok
		{ 	
			return 1;
		}else				//ȡ��
		{
			MessagePopup ("Warning", "Please update");
			SoftwareChange(0);      
			return 0;
		}
	 }
	if(i == len)
	 {
		MessagePopup ("Warning", "It is the latest Software version");
		SoftwareChange(0);  
	  }
	}
	return 0;
}
//============================================================================================================================  
int	CheckHardware()   //�쳵Ӳ���Ƿ�Ϊ����
{
	int	j;
	int len = strlen(serversHardVersion);
	for(j=0;j<=len;j++)
	{
		 if(serversHardVersion[j] != currentHardVersion[j])
		 {
			int temp = ConfirmPopup ("Version update", "Whether to update to the latest hard version");  //��������汾����
			if(temp  == 1)return 1;
			else
			{
				MessagePopup ("Warning", "Please update");
				HardwareChange(0);        
				return 0;
			}
		 }
		if(j == len)
		{
			MessagePopup ("Warning", "It is the latest hard version");
			HardwareChange(0);
		 }
	}
	return 0;
}
//============================================================================================================================  
int	ComponeyCheckSoftware()   //��˾�ڲ��쳵����Ƿ�Ϊ����  
{
	int i, len;
	len = strlen(serversUpdateVersion);
	for(i=0;i<=len;i++)
	{
	 if(serversUpdateVersion[i] != currentUpdateVersion[i])
	 { 	int temp = ConfirmPopup ("Version update", "Whether to update to the latest Software version");  //��������汾����              
		if(temp  == 1)		//ok
		{ 	
			return 1;
		}else				//ȡ��
		{
			MessagePopup ("Warning", "Please update");
			SoftwareChange(0);      
			return 0;
		}
	 }
	if(i == len)
	 {
		MessagePopup ("Warning", "It is the latest Software version");
		SoftwareChange(0);  
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
		case EVENT_LEFT_CLICK_UP:
			UpdateSoftware ( panel,control, event,callbackData, eventData1, eventData2);
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
			break;
		case EVENT_RIGHT_DOUBLE_CLICK:
				SoftwareChange(0);          
			break;
			
	}
	return 0;
}

int CVICALLBACK UpdateTestCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetCtrlAttribute (panel, ABOUT_UPDATE, ATTR_OFF_COLOR, VAL_DK_RED);
			
			testFlag = 1;
			break;
	}
	return 0;
}
