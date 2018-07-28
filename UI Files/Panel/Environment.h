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

#define  ENVIRONMEN                       1
#define  ENVIRONMEN_PRESSURE              2       /* control type: radioButton, callback function: (none) */
#define  ENVIRONMEN_HUMIDITY              3       /* control type: radioButton, callback function: (none) */
#define  ENVIRONMEN_TEMPTER               4       /* control type: radioButton, callback function: (none) */
#define  ENVIRONMEN_MEASURE               5       /* control type: radioButton, callback function: MesaureCallback */
#define  ENVIRONMEN_TEX_MEAS              6       /* control type: textMsg, callback function: (none) */
#define  ENVIRONMEN_TXT_HUM               7       /* control type: textMsg, callback function: (none) */
#define  ENVIRONMEN_TXT_TEMP              8       /* control type: textMsg, callback function: (none) */
#define  ENVIRONMEN_TXT_PRESS             9       /* control type: textMsg, callback function: (none) */

#define  ENVIRPANEL                       2
#define  ENVIRPANEL_TXT_HUM               2       /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_TXT_PRESS             3       /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_STR_PRES              4       /* control type: string, callback function: (none) */
#define  ENVIRPANEL_STR_HUM               5       /* control type: string, callback function: (none) */
#define  ENVIRPANEL_TXT_TEMP              6       /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_STR_TEMP              7       /* control type: string, callback function: (none) */
#define  ENVIRPANEL_TEXTMSG_2             8       /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_TEXTMSG               9       /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_PRESSURE              10      /* control type: radioButton, callback function: (none) */
#define  ENVIRPANEL_HUMIDITY              11      /* control type: radioButton, callback function: (none) */
#define  ENVIRPANEL_TEMPTER               12      /* control type: radioButton, callback function: (none) */
#define  ENVIRPANEL_TEXTMSG_3             13      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK MesaureCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
