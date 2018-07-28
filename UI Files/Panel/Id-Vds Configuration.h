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

#define  IDVDS_CFG                        1
#define  IDVDS_CFG_PIC_IDVD_DRAIN         2       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_IDVD_SOURCE        3       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_IDVD_BLUK          4       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_IDVD_GATE          5       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_FET                6       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_VD_STEP                7       /* control type: numeric, callback function: DrainStepCallback */
#define  IDVDS_CFG_VD_STOP                8       /* control type: numeric, callback function: DrainStopCallback */
#define  IDVDS_CFG_VD_START               9       /* control type: numeric, callback function: DrainStartCallback */
#define  IDVDS_CFG_TEXTMSG_14             10      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_15             11      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_17             12      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_DRAINMODE              13      /* control type: ring, callback function: DrainModeCallback */
#define  IDVDS_CFG_TEXTMSG_18             14      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_19             15      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_20             16      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_PIC_DRAIN              17      /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_22             18      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_DRAIN              19      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_VG_STEP                20      /* control type: numeric, callback function: GateStepCallback */
#define  IDVDS_CFG_VG_STOP                21      /* control type: numeric, callback function: GateStopCallback */
#define  IDVDS_CFG_VG_START               22      /* control type: numeric, callback function: GateStartCallback */
#define  IDVDS_CFG_TEXTMSG_8              23      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_5              24      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_6              25      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_GATEMODE               26      /* control type: ring, callback function: GateModeCallback */
#define  IDVDS_CFG_TEXTMSG_10             27      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_4              28      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_11             29      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_PIC_GATE               30      /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_12             31      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_GATE               32      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_DECORATION_GATE        33      /* control type: deco, callback function: GateDecoCallback */
#define  IDVDS_CFG_DECORATION_DRAIN       34      /* control type: deco, callback function: DrainDecoCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK DrainDecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DrainModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DrainStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DrainStepCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DrainStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GateDecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GateModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GateStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GateStepCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GateStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
