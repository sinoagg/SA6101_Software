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

#define  ENVT                             2
#define  ENVT_PROPATH                     2       /* control type: string, callback function: (none) */
#define  ENVT_DIRECT                      3       /* control type: command, callback function: PrjDirCallback */

#define  GRAPH                            3
#define  GRAPH_PLOT_STYLE                 2       /* control type: ring, callback function: (none) */
#define  GRAPH_PLOT_STYLE_2               3       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TXT_PLOT_STYLE             4       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_2                  5       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_3                  6       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_7                  7       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_4                  8       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_5                  9       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_8                  10      /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_6                  11      /* control type: textMsg, callback function: (none) */
#define  GRAPH_POINT_STYLE                12      /* control type: ring, callback function: (none) */
#define  GRAPH_LINE_STYLE                 13      /* control type: ring, callback function: (none) */
#define  GRAPH_GRAPH2CLR3                 14      /* control type: color, callback function: (none) */
#define  GRAPH_GRAPH2CLR2                 15      /* control type: color, callback function: (none) */
#define  GRAPH_GRAPH2CLR1                 16      /* control type: color, callback function: (none) */
#define  GRAPH_GRAPH1CLR3                 17      /* control type: color, callback function: (none) */
#define  GRAPH_GRAPH1CLR2                 18      /* control type: color, callback function: (none) */
#define  GRAPH_GRAPH1CLR1                 19      /* control type: color, callback function: (none) */
#define  GRAPH_CHECKBOX                   20      /* control type: radioButton, callback function: (none) */

#define  SETTINGS                         4       /* callback function: SettingsPanelCallback */
#define  SETTINGS_CANVAS                  2       /* control type: canvas, callback function: (none) */
#define  SETTINGS_DECORATION              3       /* control type: deco, callback function: (none) */
#define  SETTINGS_ABOUTBTN                4       /* control type: textMsg, callback function: AboutBtnCallback */
#define  SETTINGS_GRAPHBTN                5       /* control type: textMsg, callback function: GraphBtnCallback */
#define  SETTINGS_PRJBTN                  6       /* control type: textMsg, callback function: PrjBtnCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AboutBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GraphBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrjBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrjDirCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
