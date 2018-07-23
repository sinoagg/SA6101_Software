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
#define  IDVGS_CFG_VG_STEP                7       /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_VG_STOP                8       /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_VG_START               9       /* control type: numeric, callback function: (none) */
#define  IDVGS_CFG_RING_MODE              10      /* control type: ring, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_18             11      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_MODE               12      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_START              13      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_STOP               14      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_20             15      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_STEP               16      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_PIC_GATE               17      /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG_22             18      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_TXT_GATE               19      /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_DECORATION_GATE        20      /* control type: deco, callback function: GateCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK GateCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
