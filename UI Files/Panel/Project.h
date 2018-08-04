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
#define  PROPANEL_SPLITTER                2       /* control type: splitter, callback function: (none) */
#define  PROPANEL_DESCBOX                 3       /* control type: radioButton, callback function: DescCallback */
#define  PROPANEL_IMGBOX                  4       /* control type: radioButton, callback function: ImgCallback */
#define  PROPANEL_STRING                  5       /* control type: string, callback function: (none) */
#define  PROPANEL_SEARCH                  6       /* control type: command, callback function: SearchCallback */
#define  PROPANEL_OPENPROJECT             7       /* control type: picture, callback function: (none) */
#define  PROPANEL_TEXTMSG                 8       /* control type: textMsg, callback function: OpenPrjCallback */
#define  PROPANEL_PICTURE                 9       /* control type: picture, callback function: (none) */
#define  PROPANEL_MSG_EXIT                10      /* control type: textMsg, callback function: ExitPrjCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK DefaultCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DescCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ExitPrjCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ImgCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenPrjCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SearchCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
