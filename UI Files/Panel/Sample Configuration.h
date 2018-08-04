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

#define  SAMPLE_ADV                       1
#define  SAMPLE_ADV_PIC_SET               2       /* control type: picture, callback function: (none) */
#define  SAMPLE_ADV_BSCSET                3       /* control type: textMsg, callback function: BasicSetCallback */
#define  SAMPLE_ADV_MAXRANGE              4       /* control type: ring, callback function: (none) */
#define  SAMPLE_ADV_MINRANGE              5       /* control type: ring, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG_6             6       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG_7             7       /* control type: textMsg, callback function: (none) */

#define  SAMPLE_CFG                       2
#define  SAMPLE_CFG_RANGESETTING          2       /* control type: ring, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_2             3       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_4             4       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_6             5       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_5             6       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_PIC_SET               7       /* control type: picture, callback function: (none) */
#define  SAMPLE_CFG_ADVCSET               8       /* control type: textMsg, callback function: AdvancSetCallback */
#define  SAMPLE_CFG_SAMPLENUMBER          9       /* control type: numeric, callback function: IdVdGateStartCallback */
#define  SAMPLE_CFG_SAMPLERATE            10      /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_RUNTIME               11      /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_TIMESTEP              12      /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG               13      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_QUIETTIME             14      /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_7             15      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_8             16      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_10            17      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TXT_RUNTIME           18      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_RUNTIME_UNIT          19      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdGateStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
