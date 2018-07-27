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
#define  IDVGS_CFG_VG_STEP                7       /* control type: numeric, callback function: VgStepCallback */
#define  IDVGS_CFG_VG_STOP                8       /* control type: numeric, callback function: VgStCallback */
#define  IDVGS_CFG_VG_START               9       /* control type: numeric, callback function: VgSartCallback */
#define  IDVGS_CFG_TEXTMSG_14             10      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_15             11      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_17             12      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_VGRING                 13      /* control type: ring, callback function: VgModeCallback */
#define  IDVGS_CFG_TEXTMSG_23             14      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_19             15      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_24             16      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_PIC_GATE               17      /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_25             18      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_GATE               19      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_VD_STEP                20      /* control type: numeric, callback function: VGstepCallback */
#define  IDVGS_CFG_VD_STOP                21      /* control type: numeric, callback function: VGstopCallback */
#define  IDVGS_CFG_VD_START               22      /* control type: numeric, callback function: VGstartCallback */
#define  IDVGS_CFG_VGDRING                23      /* control type: ring, callback function: VGmodeCallback */
#define  IDVGS_CFG_TEXTMSG_18             24      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_MODE               25      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_START              26      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_STOP               27      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_20             28      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_STEP               29      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_PIC_DRAIN              30      /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_22             31      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_DRAIN              32      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_DECORATION_GATE        33      /* control type: deco, callback function: VGDrainCallback */
#define  IDVGS_CFG_DECORATION_DRAIN       34      /* control type: deco, callback function: VdgateCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK VdgateCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VGDrainCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VgModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VgSartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VGstartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VgStCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VgStepCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VGstopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
