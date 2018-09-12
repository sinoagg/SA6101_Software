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
#define  MAIN_PANEL_PIC                   2       /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_PIC_1                 3       /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_TXT_ANALYZE           4       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_CONFIG            5       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_SELECT            6       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_STOP              7       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_RUN_2             8       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_RUN               9       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_CANVAS                10      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_TXT_SAVE              11      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_PROJECTS              12      /* control type: picture, callback function: ProjectCallback */
#define  MAIN_PANEL_TOOLS                 13      /* control type: picture, callback function: ToolsCallback */
#define  MAIN_PANEL_SETTINGS              14      /* control type: picture, callback function: SettingsCallback */
#define  MAIN_PANEL_TXT_PROJECTS          15      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_SET               16      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_TOOLS             17      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_CANVAS_3              18      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_RERUN                 19      /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_STOP                  20      /* control type: picture, callback function: StopCallback */
#define  MAIN_PANEL_RUN                   21      /* control type: picture, callback function: RunCallback */
#define  MAIN_PANEL_SELECT                22      /* control type: picture, callback function: SelectCallback */
#define  MAIN_PANEL_CONFIGURE             23      /* control type: picture, callback function: ConfigureCallback */
#define  MAIN_PANEL_ANALYZE               24      /* control type: picture, callback function: AnalyzeCallback */
#define  MAIN_PANEL_CANVAS_2              25      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_SAVE                  26      /* control type: picture, callback function: SaveCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AnalyzeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ConfigureCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAIN_PANEL_Callback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ProjectCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SelectCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingsCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ToolsCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
