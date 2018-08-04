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

#define  DEFPANEL                         1       /* callback function: DefaultCallback */
#define  DEFPANEL_NAME                    2       /* control type: textMsg, callback function: (none) */
#define  DEFPANEL_CANVAS                  3       /* control type: canvas, callback function: (none) */
#define  DEFPANEL_TIME                    4       /* control type: textMsg, callback function: (none) */
#define  DEFPANEL_DATE                    5       /* control type: textMsg, callback function: (none) */
#define  DEFPANEL_DESC                    6       /* control type: textMsg, callback function: (none) */
#define  DEFPANEL_PICS                    7       /* control type: picture, callback function: (none) */

#define  PROPANEL                         2
#define  PROPANEL_OPEN                    2       /* control type: command, callback function: OpenPrjCallback */
#define  PROPANEL_EXIT                    3       /* control type: command, callback function: PrjExitCallback */
#define  PROPANEL_SPLITTER                4       /* control type: splitter, callback function: (none) */
#define  PROPANEL_DESCBOX                 5       /* control type: radioButton, callback function: DescCallback */
#define  PROPANEL_IMGBOX                  6       /* control type: radioButton, callback function: ImgCallback */
#define  PROPANEL_STRING                  7       /* control type: string, callback function: (none) */
#define  PROPANEL_SEARCH                  8       /* control type: command, callback function: SearchCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK DefaultCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DescCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ImgCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenPrjCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrjExitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SearchCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
