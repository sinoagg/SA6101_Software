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
#define  IDVDS_CFG_PIC_IDVD_SOURCE        2       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_IDVD_BLUK          3       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_IDVD_GATE          4       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_FET                5       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_VD_STEP                6       /* control type: numeric, callback function: IdVdDrainStepCallback */
#define  IDVDS_CFG_VD_STOP                7       /* control type: numeric, callback function: IdVdDrainStopCallback */
#define  IDVDS_CFG_VD_START               8       /* control type: numeric, callback function: IdVdDrainStartCallback */
#define  IDVDS_CFG_TEXTMSG_14             9       /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG                10      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_15             11      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_17             12      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_DRAINMODE              13      /* control type: ring, callback function: IdVdDrainModeCallback */
#define  IDVDS_CFG_TEXTMSG_18             14      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_19             15      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_20             16      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_PIC_DRAIN              17      /* control type: picture, callback function: IdVdDrainPicCallback */
#define  IDVDS_CFG_TEXTMSG_22             18      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_VG_STEP                19      /* control type: numeric, callback function: IdVdGateStepCallback */
#define  IDVDS_CFG_VG_STOP                20      /* control type: numeric, callback function: IdVdGateStopCallback */
#define  IDVDS_CFG_VG_START               21      /* control type: numeric, callback function: IdVdGateStartCallback */
#define  IDVDS_CFG_TEXTMSG_8              22      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_STOP               23      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_STEP               24      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_GATEMODE               25      /* control type: ring, callback function: IdVdGateModeCallback */
#define  IDVDS_CFG_MV_START               26      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_START              27      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_MV_STOP                28      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_PIC_GATE               29      /* control type: picture, callback function: IdVdGatePicCallback */
#define  IDVDS_CFG_MV_STEP                30      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_DECORATION_GATE        31      /* control type: deco, callback function: IdVdGateDecoCallback */
#define  IDVDS_CFG_PIC_IDVD_DRAIN         32      /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_DECORATION_DRAIN       33      /* control type: deco, callback function: IdVdDrainDecoCallback */
#define  IDVDS_CFG_TEXTMSG_2              34      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK IdVdDrainDecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdDrainModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdDrainPicCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdDrainStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdDrainStepCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdDrainStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdGateDecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdGateModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdGatePicCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdGateStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdGateStepCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdGateStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
