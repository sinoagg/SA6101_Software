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
#define  CALPANEL_RANGESETTING            2       /* control type: ring, callback function: (none) */
#define  CALPANEL_DANG                    3       /* control type: pictButton, callback function: DangCallback */
#define  CALPANEL_ZEROCURCAL              4       /* control type: pictButton, callback function: ZeroCurrentCallback */
#define  CALPANEL_OUTVOLCAL               5       /* control type: pictButton, callback function: OutVoltageCallback */
#define  CALPANEL_TEXTMSG                 6       /* control type: textMsg, callback function: (none) */
#define  CALPANEL_OK                      7       /* control type: command, callback function: OkCallback */
#define  CALPANEL_TEXTMSG_2               8       /* control type: textMsg, callback function: (none) */

#define  TOOLSPANEL                       2       /* callback function: ToolsPanelCallback */
#define  TOOLSPANEL_CALIBRATION           2       /* control type: pictButton, callback function: CalibrationCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CalibrationCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DangCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OutVoltageCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ToolsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroCurrentCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
