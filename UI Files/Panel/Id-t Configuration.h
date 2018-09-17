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

#define  IDT_CFG                          1
#define  IDT_CFG_PIC_IDVD_DRAIN           2       /* control type: picture, callback function: (none) */
#define  IDT_CFG_PIC_IDVD_SOURCE          3       /* control type: picture, callback function: (none) */
#define  IDT_CFG_PIC_IDVD_BLUK            4       /* control type: picture, callback function: (none) */
#define  IDT_CFG_PIC_IDVD_GATE            5       /* control type: picture, callback function: (none) */
#define  IDT_CFG_PIC_FET                  6       /* control type: picture, callback function: (none) */
#define  IDT_CFG_VD_START                 7       /* control type: numeric, callback function: IdtDrainStartCallback */
#define  IDT_CFG_TEXTMSG_14               8       /* control type: textMsg, callback function: (none) */
#define  IDT_CFG_TEXTMSG                  9       /* control type: textMsg, callback function: (none) */
#define  IDT_CFG_DRAINMODE                10      /* control type: ring, callback function: IdtDrainModeCallback */
#define  IDT_CFG_TEXTMSG_18               11      /* control type: textMsg, callback function: (none) */
#define  IDT_CFG_TEXTMSG_19               12      /* control type: textMsg, callback function: (none) */
#define  IDT_CFG_PIC_DRAIN                13      /* control type: picture, callback function: (none) */
#define  IDT_CFG_TXT_DRAIN                14      /* control type: textMsg, callback function: (none) */
#define  IDT_CFG_VG_START                 15      /* control type: numeric, callback function: IdtGateStartCallback */
#define  IDT_CFG_TEXTMSG_8                16      /* control type: textMsg, callback function: (none) */
#define  IDT_CFG_GATEMODE                 17      /* control type: ring, callback function: IdtGateModeCallback */
#define  IDT_CFG_MV_START                 18      /* control type: textMsg, callback function: (none) */
#define  IDT_CFG_TXT_START                19      /* control type: textMsg, callback function: (none) */
#define  IDT_CFG_PIC_GATE                 20      /* control type: picture, callback function: (none) */
#define  IDT_CFG_TXT_GATE                 21      /* control type: textMsg, callback function: (none) */
#define  IDT_CFG_DECORATION_DRAIN         22      /* control type: deco, callback function: IdtDrainDecoCallback */
#define  IDT_CFG_DECORATION_GATE          23      /* control type: deco, callback function: IdtGateDecoCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK IdtDrainDecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdtDrainModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdtDrainStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdtGateDecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdtGateModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdtGateStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
