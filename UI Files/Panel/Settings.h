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
#define  ENVT_DIRECT                      3       /* control type: command, callback function: ProCallback */

#define  GRAPH                            3
#define  GRAPH_LINEWIDTH                  2       /* control type: ring, callback function: (none) */
#define  GRAPH_TEXTMSG                    3       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_2                  4       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_3                  5       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_4                  6       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_5                  7       /* control type: textMsg, callback function: (none) */
#define  GRAPH_TEXTMSG_6                  8       /* control type: textMsg, callback function: (none) */
#define  GRAPH_DATADISP                   9       /* control type: ring, callback function: (none) */
#define  GRAPH_COLORNUM_4                 10      /* control type: color, callback function: (none) */
#define  GRAPH_COLORNUM_3                 11      /* control type: color, callback function: (none) */
#define  GRAPH_COLORNUM_2                 12      /* control type: color, callback function: (none) */
#define  GRAPH_COLORNUM                   13      /* control type: color, callback function: (none) */
#define  GRAPH_Y2DATAUTO                  14      /* control type: radioButton, callback function: (none) */
#define  GRAPH_Y1DATAUTO                  15      /* control type: radioButton, callback function: (none) */

#define  SETTINGS                         4
#define  SETTINGS_CANVAS                  2       /* control type: canvas, callback function: (none) */
#define  SETTINGS_DECORATION              3       /* control type: deco, callback function: (none) */
#define  SETTINGS_ABOUTBTN                4       /* control type: textMsg, callback function: AboutBtnCallback */
#define  SETTINGS_GRAPHBTN                5       /* control type: textMsg, callback function: GraphBtnCallback */
#define  SETTINGS_ENVBTN                  6       /* control type: textMsg, callback function: EnvBtnCallback */
#define  SETTINGS_OK                      7       /* control type: command, callback function: (none) */
#define  SETTINGS_CANCEL                  8       /* control type: command, callback function: CancelCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AboutBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CancelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EnvBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GraphBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ProCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
