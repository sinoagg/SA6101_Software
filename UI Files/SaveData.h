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

#define  SAVEDATA                         1
#define  SAVEDATA_TEXTMSG                 2       /* control type: textMsg, callback function: (none) */
#define  SAVEDATA_TEXTMSG_3               3       /* control type: textMsg, callback function: (none) */
#define  SAVEDATA_TEXTMSG_2               4       /* control type: textMsg, callback function: (none) */
#define  SAVEDATA_STRING_3                5       /* control type: string, callback function: (none) */
#define  SAVEDATA_GRAPHPATH               6       /* control type: string, callback function: (none) */
#define  SAVEDATA_SHEETPATH               7       /* control type: string, callback function: (none) */
#define  SAVEDATA_TEXTMSG_4               8       /* control type: textMsg, callback function: (none) */
#define  SAVEDATA_PICFORMAT               9       /* control type: ring, callback function: (none) */
#define  SAVEDATA_COMMANDBUTTON_3         10      /* control type: command, callback function: (none) */
#define  SAVEDATA_BROWSEGRAPH1            11      /* control type: command, callback function: BrowseGraph1Callback */
#define  SAVEDATA_COMMANDBUTTON_5         12      /* control type: command, callback function: (none) */
#define  SAVEDATA_COMMANDBUTTON_6         13      /* control type: command, callback function: (none) */
#define  SAVEDATA_COMMANDBUTTON_7         14      /* control type: command, callback function: (none) */
#define  SAVEDATA_COMMANDBUTTON_4         15      /* control type: command, callback function: (none) */
#define  SAVEDATA_BROWSESHEET             16      /* control type: command, callback function: BrowseSheetCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK BrowseGraph1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BrowseSheetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
