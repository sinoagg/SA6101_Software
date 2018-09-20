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

#define  GRAPHDISP                        1
#define  GRAPHDISP_GRAPH10                2       /* control type: graph, callback function: (none) */
#define  GRAPHDISP_GRAPH1                 3       /* control type: graph, callback function: (none) */
#define  GRAPHDISP_GRAPH2                 4       /* control type: graph, callback function: (none) */
#define  GRAPHDISP_CANVAS                 5       /* control type: canvas, callback function: CanvasCallback */
#define  GRAPHDISP_DECORATION_GRAPH       6       /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CanvasCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
