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
#define  IDVGS_CFG_VG_COMPL               6       /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_VG_COMPL_2             7       /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_VG_BIAS                8       /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_VG_COMPL_3             9       /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_36             10      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_37             11      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_VG_BIAS_2              12      /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_PIC_FET                13      /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_RING_9                 14      /* control type: ring, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_26             15      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_RING_10                16      /* control type: ring, callback function: (none) */
#define  IDVGS_CFG_CHECKBOX_7             17      /* control type: radioButton, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_38             18      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_CHECKBOX_8             19      /* control type: radioButton, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_39             20      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_40             21      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_28             22      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_PIC_DRAIN              23      /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_VG_STEP                24      /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_41             25      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_VG_STOP                26      /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_RING_7                 27      /* control type: ring, callback function: (none) */
#define  IDVGS_CFG_VG_START               28      /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_RING_8                 29      /* control type: ring, callback function: (none) */
#define  IDVGS_CFG_CHECKBOX_5             30      /* control type: radioButton, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_30             31      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_CHECKBOX_6             32      /* control type: radioButton, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_31             33      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_33             34      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_25             35      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_PIC_SOURCE             36      /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_RING_3                 37      /* control type: ring, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_35             38      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_RING_4                 39      /* control type: ring, callback function: (none) */
#define  IDVGS_CFG_CHECKBOX_3             40      /* control type: radioButton, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_18             41      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_14             42      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_RING_6                 43      /* control type: ring, callback function: (none) */
#define  IDVGS_CFG_RING_5                 44      /* control type: ring, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_19             45      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_15             46      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_20             47      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_16             48      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_21             49      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_17             50      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_PIC_GATE               51      /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_PIC_BULK               52      /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_22             53      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_24             54      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_23             55      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_DECORATION_Drain       56      /* control type: deco, callback function: (none) */
#define  IDVGS_CFG_DECORATION_Gate        57      /* control type: deco, callback function: GateCallback */
#define  IDVGS_CFG_CHECKBOX               58      /* control type: radioButton, callback function: (none) */
#define  IDVGS_CFG_DECORATION_Soure       59      /* control type: deco, callback function: (none) */
#define  IDVGS_CFG_DECORATION_Bulk        60      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK GateCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
