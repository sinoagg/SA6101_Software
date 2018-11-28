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
#define  MAIN_PANEL_PRINT                 2       /* control type: picture, callback function: PrintCallback */
#define  MAIN_PANEL_PIC                   3       /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_PIC_1                 4       /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_TXT_ANALYZE           5       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_CONFIG            6       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_SELECT            7       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_STOP              8       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_RUN_2             9       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_RUN               10      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_CANVAS                11      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_TXT_SAVE_2            12      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_SAVE              13      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_PROJECTS              14      /* control type: picture, callback function: ProjectCallback */
#define  MAIN_PANEL_TOOLS                 15      /* control type: picture, callback function: ToolsCallback */
#define  MAIN_PANEL_SETTINGS              16      /* control type: picture, callback function: SettingsCallback */
#define  MAIN_PANEL_TXT_PROJECTS          17      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_SET               18      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TXT_TOOLS             19      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_CANVAS_3              20      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_STOP                  21      /* control type: picture, callback function: StopCallback */
#define  MAIN_PANEL_RUNAGAIN              22      /* control type: picture, callback function: RunAgainCallback */
#define  MAIN_PANEL_RUN                   23      /* control type: picture, callback function: RunCallback */
#define  MAIN_PANEL_SELECT                24      /* control type: picture, callback function: SelectCallback */
#define  MAIN_PANEL_CONFIGURE             25      /* control type: picture, callback function: ConfigureCallback */
#define  MAIN_PANEL_ANALYZE               26      /* control type: picture, callback function: AnalyzeCallback */
#define  MAIN_PANEL_CANVAS_2              27      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_SAVE                  28      /* control type: picture, callback function: SaveCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AnalyzeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ConfigureCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAIN_PANEL_Callback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrintCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ProjectCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunAgainCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SelectCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingsCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ToolsCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
