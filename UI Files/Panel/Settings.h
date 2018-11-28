/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  ABOUT                            1
#define  ABOUT_PICTURE                    2       /* control type: picture, callback function: (none) */
#define  ABOUT_TXTHARD                    3       /* control type: textMsg, callback function: TxtHardwareCallback */
#define  ABOUT_UPDATEHARD                 4       /* control type: picture, callback function: UpdateHardware */
#define  ABOUT_TXTSOFT                    5       /* control type: textMsg, callback function: TxtSoftwareCallback */
#define  ABOUT_UPDATESOFT                 6       /* control type: picture, callback function: UpdateSoftware */
#define  ABOUT_PROGRESSBAR                7       /* control type: scale, callback function: (none) */
#define  ABOUT_TEXTMSG                    8       /* control type: textMsg, callback function: (none) */
#define  ABOUT_FILEDIS_TEXTMSG            9       /* control type: textMsg, callback function: (none) */
#define  ABOUT_NUMERIC_SV                 10      /* control type: numeric, callback function: (none) */
#define  ABOUT_NUMERIC_MPV                11      /* control type: numeric, callback function: (none) */
#define  ABOUT_NUMERIC_ESV                12      /* control type: numeric, callback function: (none) */
#define  ABOUT_NUMERIC_HCV                13      /* control type: numeric, callback function: (none) */
#define  ABOUT_UPDATE                     14      /* control type: LED, callback function: UpdateTestCallback */
#define  ABOUT_TEXTMSG_6                  15      /* control type: textMsg, callback function: (none) */
#define  ABOUT_TEXTMSG_2                  16      /* control type: textMsg, callback function: (none) */
#define  ABOUT_TEXTMSG_3                  17      /* control type: textMsg, callback function: (none) */
#define  ABOUT_TEXTMSG_5                  18      /* control type: textMsg, callback function: (none) */
#define  ABOUT_TEXTMSG_4                  19      /* control type: textMsg, callback function: (none) */

#define  ENVT                             2
#define  ENVT_AUTOSAVEPATH                2       /* control type: string, callback function: (none) */
#define  ENVT_ATUPPATH                    3       /* control type: command, callback function: AutoSaveCallback */
#define  ENVT_PROPATH                     4       /* control type: string, callback function: (none) */
#define  ENVT_DIRECT                      5       /* control type: command, callback function: PrjDirCallback */

#define  SETGRAPH                         3
#define  SETGRAPH_PLOT_STYLE              2       /* control type: ring, callback function: (none) */
#define  SETGRAPH_PLOT_STYLE_2            3       /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TXT_PLOT_STYLE          4       /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_2               5       /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_3               6       /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_7               7       /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_4               8       /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_5               9       /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_8               10      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_6               11      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_POINT_STYLE             12      /* control type: ring, callback function: (none) */
#define  SETGRAPH_LINE_STYLE              13      /* control type: ring, callback function: (none) */
#define  SETGRAPH_GRAPH2CLR3              14      /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH2CLR2              15      /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH2CLR1              16      /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH1CLR3              17      /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH1CLR2              18      /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH1CLR1              19      /* control type: color, callback function: (none) */
#define  SETGRAPH_CHECKBOX                20      /* control type: radioButton, callback function: (none) */

#define  SETTINGS                         4       /* callback function: SettingsPanelCallback */
#define  SETTINGS_CANVAS                  2       /* control type: canvas, callback function: (none) */
#define  SETTINGS_DECORATION              3       /* control type: deco, callback function: (none) */
#define  SETTINGS_ABOUTBTN                4       /* control type: textMsg, callback function: AboutBtnCallback */
#define  SETTINGS_PRJBTN                  5       /* control type: textMsg, callback function: PrjBtnCallback */
#define  SETTINGS_GRAPHBTN                6       /* control type: textMsg, callback function: GraphBtnCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AboutBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AutoSaveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GraphBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrjBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrjDirCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TxtHardwareCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TxtSoftwareCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK UpdateHardware(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK UpdateSoftware(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK UpdateTestCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
