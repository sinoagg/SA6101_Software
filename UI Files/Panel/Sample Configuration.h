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
#define  SAMPLE_ADV_TEXTMSG_4             3       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_ADV_BSCSET                4       /* control type: textMsg, callback function: BasicSetCallback */
#define  SAMPLE_ADV_SAMPLENUMBER          5       /* control type: numeric, callback function: (none) */
#define  SAMPLE_ADV_SAMPLERATE            6       /* control type: numeric, callback function: (none) */
#define  SAMPLE_ADV_MAXRANGE              7       /* control type: ring, callback function: (none) */
#define  SAMPLE_ADV_MINRANGE              8       /* control type: ring, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG_6             9       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG_7             10      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_ADV_LINEAR                11      /* control type: ring, callback function: (none) */
#define  SAMPLE_ADV_GATE                  12      /* control type: radioButton, callback function: (none) */
#define  SAMPLE_ADV_DRAIN                 13      /* control type: radioButton, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG_10            14      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG_2             15      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_ADV_DIRECTION             16      /* control type: ring, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG_26            17      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG_5             18      /* control type: textMsg, callback function: (none) */

#define  SAMPLE_CFG                       2
#define  SAMPLE_CFG_SAMPLERATE            2       /* control type: ring, callback function: RampleRateCallback */
#define  SAMPLE_CFG_RANGESETTING          3       /* control type: ring, callback function: (none) */
#define  SAMPLE_CFG_ADVCSET               4       /* control type: textMsg, callback function: AdvancSetCallback */
#define  SAMPLE_CFG_RUNTIME               5       /* control type: numeric, callback function: RunTimeCallback */
#define  SAMPLE_CFG_TEXTMSG               6       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_SAMPLEDELAY           7       /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_QUIETTIME             8       /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_7             9       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_RUNTIME_UNIT          10      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_PIC_SET               11      /* control type: picture, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_11            12      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_12            13      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TXT_RUNTIME           14      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_27            15      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_2             16      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RampleRateCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunTimeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
