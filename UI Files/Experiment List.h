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

#define  EXP_LIST                         1
#define  EXP_LIST_LISTBOX                 2       /* control type: listBox, callback function: ExpListCallBack */
#define  EXP_LIST_LISTBOX_2               3       /* control type: listBox, callback function: (none) */
#define  EXP_LIST_TEXTMSG                 4       /* control type: textMsg, callback function: (none) */
#define  EXP_LIST_TEXTMSG_3               5       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ExpListCallBack(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
