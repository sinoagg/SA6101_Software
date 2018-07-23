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

#define  TABLE                            1
#define  TABLE_DISTABLE                   2       /* control type: table, callback function: (none) */
#define  TABLE_DELETEROW                  3       /* control type: command, callback function: DeleteCalback */
#define  TABLE_ADDROW                     4       /* control type: command, callback function: AddRowCallback */
#define  TABLE_ADDTITLE                   5       /* control type: command, callback function: AddTitleCallback */
#define  TABLE_ADDBGCOLOR                 6       /* control type: radioButton, callback function: ColorCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AddRowCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AddTitleCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ColorCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DeleteCalback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
