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

#define  MAIN_PANEL                       1       /* callback function: MAIN_PANEL_Callback */
#define  MAIN_PANEL_PICTURE_3             2       /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_PICTURE_8             3       /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_3             4       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_2             5       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG               6       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_5             7       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_4             8       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_CANVAS                9       /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_6             10      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_PICTURE_10            11      /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_PICTURE_9             12      /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_PICTURE_11            13      /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_8             14      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_9             15      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_7             16      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_CANVAS_3              17      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_Stop                  18      /* control type: picture, callback function: StopCallback */
#define  MAIN_PANEL_Run                   19      /* control type: picture, callback function: RunCallback */
#define  MAIN_PANEL_Select                20      /* control type: picture, callback function: SelectCallback */
#define  MAIN_PANEL_Configure             21      /* control type: picture, callback function: ConfigureCallback */
#define  MAIN_PANEL_Analyze               22      /* control type: picture, callback function: AnalyzeCallback */
#define  MAIN_PANEL_CANVAS_2              23      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_Save                  24      /* control type: picture, callback function: SaveCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AnalyzeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ConfigureCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAIN_PANEL_Callback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SelectCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
