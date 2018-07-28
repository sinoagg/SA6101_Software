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

<<<<<<< HEAD
#define  SAMPLE_CFG                       1
=======
#define  SAMPLE_BSC                       1
#define  SAMPLE_BSC_PIC_SET               2       /* control type: picture, callback function: (none) */
#define  SAMPLE_BSC_BSCSET                3       /* control type: textMsg, callback function: BasicSetCallback */
#define  SAMPLE_BSC_MINRANGE              4       /* control type: ring, callback function: (none) */
#define  SAMPLE_BSC_MAXRANGE              5       /* control type: ring, callback function: (none) */
#define  SAMPLE_BSC_TEXTMSG_6             6       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_BSC_TEXTMSG_7             7       /* control type: textMsg, callback function: (none) */

#define  SAMPLE_CFG                       2
>>>>>>> a0ab2d7488dc2715558bcf7b33d9ee1aa747214e
#define  SAMPLE_CFG_SAMPLENUMBER          2       /* control type: string, callback function: (none) */
#define  SAMPLE_CFG_SAMPLERATE            3       /* control type: string, callback function: (none) */
#define  SAMPLE_CFG_RANGESETTING          4       /* control type: ring, callback function: (none) */
#define  SAMPLE_CFG_RUNTIME               5       /* control type: string, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_3             6       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TIMESTEP              7       /* control type: string, callback function: (none) */
#define  SAMPLE_CFG_QUIETTIME             8       /* control type: string, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_2             9       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_4             10      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_6             11      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_5             12      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG               13      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_PIC_SET               14      /* control type: picture, callback function: (none) */
#define  SAMPLE_CFG_ADVCSET               15      /* control type: textMsg, callback function: AdvancSetCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
