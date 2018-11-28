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

#define  IDVGS_CFG                        1
#define  IDVGS_CFG_PIC_IDVD_DRAIN         2       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_PIC_IDVD_SOURCE        3       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_PIC_IDVD_BLUK          4       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_PIC_IDVD_GATE          5       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_PIC_FET                6       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_VG_STEP                7       /* control type: numeric, callback function: IdVgGateStepCallback */
#define  IDVGS_CFG_VG_STOP                8       /* control type: numeric, callback function: IdVgGateStopCallback */
#define  IDVGS_CFG_VG_START               9       /* control type: numeric, callback function: IdVgGateStartCallback */
#define  IDVGS_CFG_TEXTMSG_14             10      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG                11      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_15             12      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_17             13      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_GATEMODE               14      /* control type: ring, callback function: IdVgGateModeCallback */
#define  IDVGS_CFG_TEXTMSG_23             15      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_19             16      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_24             17      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_PIC_GATE               18      /* control type: picture, callback function: IdVgGatePicCallback */
#define  IDVGS_CFG_TEXTMSG_25             19      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_VD_STEP                20      /* control type: numeric, callback function: IdVgDrainStepCallback */
#define  IDVGS_CFG_VD_STOP                21      /* control type: numeric, callback function: IdVgDrainStopCallback */
#define  IDVGS_CFG_VD_START               22      /* control type: numeric, callback function: IdVgDrainStartCallback */
#define  IDVGS_CFG_DRAINMODE              23      /* control type: ring, callback function: IdVgDrainModeCallback */
#define  IDVGS_CFG_MV_START               24      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_MODE               25      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_START              26      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_STOP               27      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_MV_STOP                28      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_STEP               29      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_PIC_DRAIN              30      /* control type: picture, callback function: IdVgDrainPicCallback */
#define  IDVGS_CFG_MV_STEP                31      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_DECORATION_GATE        32      /* control type: deco, callback function: IdVgDrainDecoCallback */
#define  IDVGS_CFG_DECORATION_DRAIN       33      /* control type: deco, callback function: IdVgGateDecoCallback */
#define  IDVGS_CFG_TEXTMSG_2              34      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK IdVgDrainDecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgDrainModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgDrainPicCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgDrainStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgDrainStepCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgDrainStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgGateDecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgGateModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgGatePicCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgGateStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgGateStepCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgGateStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
