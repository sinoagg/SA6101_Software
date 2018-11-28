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

#define  CALPANEL                         1       /* callback function: CaliPanelCallback */
#define  CALPANEL_OUTVOLCALI              2       /* control type: picture, callback function: OutputVoltageCaliCallback */
#define  CALPANEL_RANGESELECT             3       /* control type: ring, callback function: RangeSelectCallback */
#define  CALPANEL_TEXTMSG                 4       /* control type: textMsg, callback function: (none) */
#define  CALPANEL_SAVECALI_2              5       /* control type: command, callback function: CancelCaliCallback */
#define  CALPANEL_SAVECALI                6       /* control type: command, callback function: SaveCaliCallback */
#define  CALPANEL_TEXTMSG_2               7       /* control type: textMsg, callback function: (none) */
#define  CALPANEL_VOLTAGERUN              8       /* control type: textMsg, callback function: TXTOutputVoltageCaliCallback */
#define  CALPANEL_ZEROCURCALI             9       /* control type: picture, callback function: ZeroCurrentCaliCallback */
#define  CALPANEL_RANG                    10      /* control type: picture, callback function: RangeCaliCallback */
#define  CALPANEL_CURRENTRUN              11      /* control type: textMsg, callback function: TXTZeroCurrentCaliCallback */
#define  CALPANEL_RANGERUN                12      /* control type: textMsg, callback function: TXTRangeCaliCallback */

#define  TOOLSPANEL                       2       /* callback function: ToolsPanelCallback */
#define  TOOLSPANEL_PICCALIB              2       /* control type: picture, callback function: CalibrationCallback */
#define  TOOLSPANEL_TXTCALIB              3       /* control type: textMsg, callback function: TxTCalibrationCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CalibrationCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CaliPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CancelCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OutputVoltageCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RangeCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RangeSelectCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ToolsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TxTCalibrationCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TXTOutputVoltageCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TXTRangeCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TXTZeroCurrentCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroCurrentCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
