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

#define  CALPANEL                         1
#define  CALPANEL_RANGESELECT             2       /* control type: ring, callback function: (none) */
#define  CALPANEL_RANG                    3       /* control type: pictButton, callback function: RangeCaliCallback */
#define  CALPANEL_ZEROCURCALI             4       /* control type: pictButton, callback function: ZeroCurrentCaliCallback */
#define  CALPANEL_OUTVOLCALI              5       /* control type: pictButton, callback function: OutputVoltageCaliCallback */
#define  CALPANEL_TEXTMSG                 6       /* control type: textMsg, callback function: (none) */
#define  CALPANEL_SAVECALI                7       /* control type: command, callback function: SaveCaliCallback */
#define  CALPANEL_TEXTMSG_2               8       /* control type: textMsg, callback function: (none) */

#define  TOOLSPANEL                       2       /* callback function: ToolsPanelCallback */
#define  TOOLSPANEL_CALIBRATION           2       /* control type: pictButton, callback function: CalibrationCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CalibrationCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OutputVoltageCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RangeCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ToolsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroCurrentCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
