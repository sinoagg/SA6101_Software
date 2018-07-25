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
#define  IDVDS_CFG_VD_STEP_2              7       /* control type: numeric, callback function: VdStepCallback */
#define  IDVDS_CFG_VD_STOP_2              8       /* control type: numeric, callback function: VdStCallback */
#define  IDVDS_CFG_VD_START_2             9       /* control type: numeric, callback function: VdSartCallback */
#define  IDVDS_CFG_TEXTMSG_14             10      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_15             11      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_17             12      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_RING_3                 13      /* control type: ring, callback function: ModeCallback */
#define  IDVDS_CFG_TEXTMSG_18             14      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_19             15      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_20             16      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_PIC_DRAIN              17      /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_22             18      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_DRAIN              19      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_VD_STEP                20      /* control type: numeric, callback function: StepCallback */
#define  IDVDS_CFG_VD_STOP                21      /* control type: numeric, callback function: VdStopCallback */
#define  IDVDS_CFG_VD_START               22      /* control type: numeric, callback function: StartCallback */
#define  IDVDS_CFG_TEXTMSG_8              23      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_5              24      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_6              25      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_VDGATE                 26      /* control type: ring, callback function: VdmodeCallbzck */
#define  IDVDS_CFG_TEXTMSG_10             27      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_4              28      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_11             29      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_PIC_GATE               30      /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG_12             31      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_TXT_GATE               32      /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_DECORATION_GATE        33      /* control type: deco, callback function: VDGateCallback */
#define  IDVDS_CFG_DECORATION_DRAIN       34      /* control type: deco, callback function: VDDrainCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StepCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VDDrainCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VDGateCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VdmodeCallbzck(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VdSartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VdStCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VdStepCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VdStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
