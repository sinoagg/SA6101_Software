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
#define  IDVDS_CFG_VD_STEP                7       /* control type: numeric, callback function: IdVdDrainStepCallback */
#define  IDVDS_CFG_VD_STOP                8       /* control type: numeric, callback function: IdVdDrainStopCallback */
#define  IDVDS_CFG_VD_START               9       /* control type: numeric, callback function: IdVdDrainStartCallback */
#define  IDVDS_CFG_TEXTMSG_14             10      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG                11      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_15             12      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_17             13      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_DRAINMODE              14      /* control type: ring, callback function: IdVdDrainModeCallback */
#define  IDVDS_CFG_TEXTMSG_18             15      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_19             16      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_20             17      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_PIC_DRAIN              18      /* control type: picture, callback function: IdVdDrainPicCallback */
#define  IDVDS_CFG_TEXTMSG_22             19      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_DRAIN              20      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_VG_STEP                21      /* control type: numeric, callback function: IdVdGateStepCallback */
#define  IDVDS_CFG_VG_STOP                22      /* control type: numeric, callback function: IdVdGateStopCallback */
#define  IDVDS_CFG_VG_START               23      /* control type: numeric, callback function: IdVdGateStartCallback */
#define  IDVDS_CFG_TEXTMSG_8              24      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_STOP               25      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_STEP               26      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_GATEMODE               27      /* control type: ring, callback function: IdVdGateModeCallback */
#define  IDVDS_CFG_MV_START               28      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_START              29      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_MV_STOP                30      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_PIC_GATE               31      /* control type: picture, callback function: IdVdGatePicCallback */
#define  IDVDS_CFG_MV_STEP                32      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_GATE               33      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_DECORATION_DRAIN       34      /* control type: deco, callback function: IdVdDrainDecoCallback */
#define  IDVDS_CFG_DECORATION_GATE        35      /* control type: deco, callback function: IdVdGateDecoCallback */


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
