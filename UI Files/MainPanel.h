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

#define  MAIN_PANEL                       1
#define  MAIN_PANEL_PICBUTTON_CONFIG_5    2       /* control type: pictButton, callback function: SaveCallBack */
#define  MAIN_PANEL_PICBUTTON_CONFIG_4    3       /* control type: pictButton, callback function: StopCallBack */
#define  MAIN_PANEL_PICBUTTON_RUN         4       /* control type: pictButton, callback function: RunCallBack */
#define  MAIN_PANEL_PICBUTTON_ANALYZE     5       /* control type: pictButton, callback function: (none) */
#define  MAIN_PANEL_PICBUTTON_CONFIG      6       /* control type: pictButton, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK RunCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StopCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
