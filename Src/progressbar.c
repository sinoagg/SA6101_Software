/*============================================================================*/
/*                        L a b W i n d o w s / C V I                         */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 2009-2017.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:       progressbar.c                                                 */
/* Purpose:     Implements a progress bar control                             */
/*                                                                            */
/*============================================================================*/

#include <cvidef.h>
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)
#ifdef THREAD_BASE_PRIORITY_MIN
#undef THREAD_BASE_PRIORITY_MIN
#endif
#ifdef THREAD_BASE_PRIORITY_IDLE
#undef THREAD_BASE_PRIORITY_IDLE
#endif
#include <windows.h>
#if _MSC_VER >= 1900
#include <VersionHelpers.h>
#endif
#elif defined (_NI_linux_) && _NI_linux_
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#else
#error Platform not supported
#endif

#include "toolbox.h"
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)
#include <cviauto.h>
#endif
#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include "inifile.h"
#include "asynctmr.h"
#include "progressbar.h"

/// REGION START Window 7 Taskbar Button progress bar
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)
extern const IID IID_ITaskbarList4;

typedef enum TBPFLAG {
    TBPF_NOPROGRESS     = 0,
    TBPF_INDETERMINATE  = 0x1,
    TBPF_NORMAL         = 0x2,
    TBPF_ERROR          = 0x4,
    TBPF_PAUSED         = 0x8
} TBPFLAG;

typedef enum THUMBBUTTONFLAGS {   
    THBF_ENABLED        = 0,
    THBF_DISABLED       = 0x1,
    THBF_DISMISSONCLICK = 0x2,
    THBF_NOBACKGROUND   = 0x4,
    THBF_HIDDEN         = 0x8,
    THBF_NONINTERACTIVE = 0x10
} THUMBBUTTONFLAGS;

typedef enum THUMBBUTTONMASK {   
    THB_BITMAP  = 0x1,
    THB_ICON    = 0x2,
    THB_TOOLTIP = 0x4,
    THB_FLAGS   = 0x8
} THUMBBUTTONMASK;

typedef enum STPFLAG {
    STPF_NONE                       = 0,
    STPF_USEAPPTHUMBNAILALWAYS      = 0x1,
    STPF_USEAPPTHUMBNAILWHENACTIVE  = 0x2,
    STPF_USEAPPPEEKALWAYS           = 0x4,
    STPF_USEAPPPEEKWHENACTIVE       = 0x8
} STPFLAG;

#include <pshpack8.h>
typedef struct THUMBBUTTON {
    THUMBBUTTONMASK dwMask;
    UINT iId;
    UINT iBitmap;
    HICON hIcon;
    WCHAR szTip[260];
    THUMBBUTTONFLAGS dwFlags;
} THUMBBUTTON;
typedef struct THUMBBUTTON *LPTHUMBBUTTON;
#include <poppack.h>

typedef IUnknown *HIMAGELIST;
typedef interface tagITaskbarList4_Interface ITaskbarList4_Interface;

typedef struct ITaskbarList4_Interface_VTable
{
    HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( ITaskbarList4_Interface __RPC_FAR * This, 
                                                             REFIID riid, 
                                                             void __RPC_FAR *__RPC_FAR *ppvObject);

    ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( ITaskbarList4_Interface __RPC_FAR * This);

    ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( ITaskbarList4_Interface __RPC_FAR * This);

    HRESULT ( STDMETHODCALLTYPE *HrInit )( ITaskbarList4_Interface __RPC_FAR * This);
    
    HRESULT ( STDMETHODCALLTYPE *AddTab )( ITaskbarList4_Interface __RPC_FAR * This,
                                                            HWND hwnd);
    
    HRESULT ( STDMETHODCALLTYPE *DeleteTab )( ITaskbarList4_Interface __RPC_FAR * This,
                                                            HWND hwnd);
    
    HRESULT ( STDMETHODCALLTYPE *ActivateTab )( ITaskbarList4_Interface __RPC_FAR * This,
                                                            HWND hwnd);
    
    HRESULT ( STDMETHODCALLTYPE *SetActiveAlt )( ITaskbarList4_Interface __RPC_FAR * This,
                                                            HWND hwnd);
    
    HRESULT ( STDMETHODCALLTYPE *MarkFullscreenWindow )( ITaskbarList4_Interface __RPC_FAR * This,
                                                            HWND hwnd,
                                                            BOOL fFullscreen);
    
    HRESULT ( STDMETHODCALLTYPE *SetProgressValue )( ITaskbarList4_Interface __RPC_FAR * This,
                                                            HWND hwnd,
                                                            ULONGLONG ullCompleted,
                                                            ULONGLONG ullTotal);
    
    HRESULT ( STDMETHODCALLTYPE *SetProgressState )( ITaskbarList4_Interface __RPC_FAR * This,
                                                            HWND hwnd,
                                                            TBPFLAG tbpFlags);
    /* Additional interface methods exist, but are not needed. */
} ITaskbarList4_Interface_VTable;

typedef interface tagITaskbarList4_Interface
{
    CONST_VTBL ITaskbarList4_Interface_VTable __RPC_FAR *lpVtbl;
} ITaskbarList4_Interface;

#define ITaskbarList4_Release(This) \
    ( (This)->lpVtbl -> Release(This) )  

#define ITaskbarList4_SetProgressValue(This,hwnd,ullCompleted,ullTotal) \
    ( (This)->lpVtbl -> SetProgressValue(This,hwnd,ullCompleted,ullTotal) ) 

#define ITaskbarList4_SetProgressState(This,hwnd,tbpFlags)  \
    ( (This)->lpVtbl -> SetProgressState(This,hwnd,tbpFlags) )

typedef struct
{
    int addedRef;
    HWND hwnd;
    CAObjHandle TaskbarList;
    ITaskbarList4_Interface *ITaskbarList4;
} *TaskbarPBInfo;

static ListType pbHwndList = 0;
#endif
/// REGION END

typedef enum
{
    PROGRESSBAR_STATE_RUNNING,
    PROGRESSBAR_STATE_PAUSED,
    PROGRESSBAR_STATE_STOPPED,
    PROGRESSBAR_STATE_ABORTED
} ProgressBarSession;

typedef struct
{
    double  avgTime;
    int     count;
} TimeEstimate;

typedef struct
{
    double          percentMarker;
    TimeEstimate    interval;
} Milestone;

typedef union
{
    struct
    {
        long long   val;
        long long   dflt;
        long long   max;
        long long   min;
    } i64;
    struct
    {
        unsigned long long  val;
        unsigned long long  dflt;
        unsigned long long  max;
        unsigned long long  min;
    } u64;
    struct
    {
        long    val;
        long    dflt;
        long    max;
        long    min;
    } i32;
    struct
    {
        unsigned long   val;
        unsigned long   dflt;
        unsigned long   max;
        unsigned long   min;
    } u32;
    struct
    {
        short   val;
        short   dflt;
        short   max;
        short   min;
    } i16;
    struct
    {
        unsigned short  val;
        unsigned short  dflt;
        unsigned short  max;
        unsigned short  min;
    } u16;
    struct
    {
        char    val;
        char    dflt;
        char    max;
        char    min;
    } i8;
    struct
    {
        unsigned char   val;
        unsigned char   dflt;
        unsigned char   max;
        unsigned char   min;
    } u8;
    struct
    {
        double  val;
        double  dflt;
        double  max;
        double  min;
    } f64;
    struct
    {
        float   val;
        float   dflt;
        float   max;
        float   min;
    } f32;
} ValueUnion;

typedef struct
{
    int         progressBarStyle;
    int         mode;
    int         showDigDisp;
    int         showIncDec;
    int         markerStyle;
    int         tickStyle;
    int         fillOption;
    int         dataType;
    int         labelLeft;
    ValueUnion  values;
} SlideState;


#define LOCK_NAME           "NI_CVI_PROGRESSBARCTRL_LOCK"

#if defined (_NI_mswin_) && _NI_mswin_
#define LOCK EnterCriticalSection (&g_lock); locked = TRUE;
#define UNLOCK if (locked) { LeaveCriticalSection (&g_lock); locked = FALSE; }
#elif defined (_NI_linux_) && _NI_linux_
#define LOCK pthread_mutex_lock (&g_lock); locked = TRUE;
#define UNLOCK if (locked) { pthread_mutex_unlock (&g_lock); locked = FALSE; }
#endif

#define PROGRESSBAR_CTRL_TYPE       "ProgressBar Ctrl"  //  name of linked callback object
#define TIMER_INCREMENT             0.01        // number of seconds between timer ticks (for auto and marquee modes)
#define MARQUEE_SIZE                0.15        // marquee size as a fraction of the control length
#define INITIAL_TIME_INTERVAL       10.0        // default total time estimate of task
#define INITIAL_MARQUEE_SPEED       300.0       // default speed of marquee mode (pixels per second)
#define INITIAL_ABORT_COLOR         VAL_RED     // default abort color

#define kReverseFlagMask    (1<<0)      // whether or not the control advances in reverse mode (right-to-left, top-to-bottom)
#define kVerticalFlagMask   (1<<1)      // whether or not the control is vertical
#define kAutoAdjustFlagMask (1<<2)      // whether or not the control adjusts its milestones and time estimates based on actual measurements

#define ATTR_PARTIAL_FILL_SIZE  20497   // undocumented UIL attribute for slides to fill a specific pixel delta, rather than filling to edge
#define ATTR_DRAW_ERROR_STATE   20498   // undocumented UIL attribute for slides to draw the progress bar visuals in an error state


#define sysChk(fCall) if (error = (fCall), error < 0) \
{error = ToolErr_UnknownSystemError; goto Error;} else

typedef struct
{
    int                 panel;          // the panel that the progress bar control resides on
    int                 control;        // the slide that the progress bar control is based on
    SlideState          slideConfig;    // the state of the slide that was converted into a progress bar
    int                 mode;           // the advance-mode of the progress bar
    ProgressBarSession  sessionState;   // the state of the progress bar
    double              percentage;     // the current percentage value of the progress bar
    size_t              milestoneIndex; // the current milestone index of the progress bar
    size_t              eventSent;      // used to prevent consecutive events from being sent without changing the percentage
    TimeEstimate        totalTime;      // the estimated total duration of the progress bar
    double              initialTimeStamp;       // the recorded time at the start of the session
    ListType            milestoneTimeStampList; // the recorded time for each milestone
    double              pausedTimeStamp;        // the recorded time at the start of a pause
    double              totalPausedTime;        // the total time for all pauses in the session
    double              marqueeSpeed;           // the rate at which the progress advances in marquee mode (pixels / sec)
    double              marqueeVal;     // the visible value of the progress bar in marquee mode
    ListType            milestoneList;  // the list of specified milestones
    int                 adjustmentType; // whether to adjust milestones percentages or advance rates
    int                 color;          // fill color in non-aborted state
    int                 abortColor;     // fill color in aborted state
    int                 timerObj;       // asynchronous timer for auto-advance and marquee modes
    int                 flags;          // boolean attributes (see flag masks above)
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)
    TaskbarPBInfo       taskbarPBInfo;  // used to store information regarding the taskbar button progress bar (Windows 7 and later only)
#endif  
} *ProgressBarInfo;

static int  CreateProgressBarInfo (int panel, int ctrl, int vertical,
                ProgressBarInfo *newProgressBarInfo);
static int  DiscardProgressBarInfo (ProgressBarInfo progressBarInfo);
static void AdjustProgressBarTimes (ProgressBarInfo progressBarInfo, double newTotalTime);
static int  CanShrinkMarquee (ProgressBarInfo progressBarInfo, double percentage, int *marqueeSize);
static int  ConfigureSlideCtrl (int panel, int slideCtrl, int vertical, ProgressBarInfo progressBarInfo);
static int  RevertSlideCtrl (int panel, int slideCtrl, ProgressBarInfo progressBarInfo);
static int  IsValidSlideControl (int panel, int ctrl, int *vertical);
static int  IsValidColor (int color);
static int  CVICALLBACK ProgressBarTimerCallback (int panel, int timerControl, int event,
                void *callbackData, int eventData1, int eventData2);
static int  CVICALLBACK ProgressBarCtrlCallback (int panel, int control, int event,
                void *callbackData, int eventData1, int eventData2);
static int  CVICALLBACK MilestoneCompare (Milestone *milestone1, Milestone *milestone2);

static int  InitializeITaskbarList4 (ProgressBarInfo progressBarInfo);
static void ITaskbarList4SetPercentage (ProgressBarInfo progressBarInfo, double percentage);
static void ITaskbarList4SetState (ProgressBarInfo progressBarInfo);
static void DisposeITaskbarList4 (ProgressBarInfo progressBarInfo);
static int  IsProgressBarSyncedWithTaskbar (ProgressBarInfo progressBarInfo);

#if defined (_NI_mswin_) && _NI_mswin_
static CRITICAL_SECTION     g_lock;
#elif defined (_NI_linux_) && _NI_linux_
static pthread_mutex_t      g_lock = PTHREAD_MUTEX_INITIALIZER;
#endif
static int                  g_bLockInited = 0;

/*****************************************************************************************/

int CVIFUNC ProgressBar_Create (int panel, const char *label, int top, int left, int vertical)
{
    int slide, error = UIENoError;

    errChk(slide = NewCtrl (panel,
        vertical ? CTRL_NUMERIC_LEVEL_VSLIDE_LS : CTRL_NUMERIC_LEVEL_HSLIDE_LS, label, top, left));

    errChk(ProgressBar_ConvertFromSlide (panel, slide));

Error:
    if (error < 0)
        DiscardCtrl (panel, slide);
    return (error < 0 ? error : slide);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_ConvertFromSlide (int panel, int slideCtrl)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError, vertical;

    if (!IsValidSlideControl (panel, slideCtrl, &vertical))
        errChk(UIEControlNotTypeExpectedByFunction);
    
    errChk(CreateProgressBarInfo (panel, slideCtrl, vertical, &progressBarInfo));
    LOCK;

    errChk(ConfigureSlideCtrl (panel, slideCtrl, vertical, progressBarInfo));
    
Error:
    if (error < 0)
        DiscardProgressBarInfo (progressBarInfo);
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_Revert (int panel, int progressBarCtrl)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    errChk(RevertSlideCtrl (panel, progressBarCtrl, progressBarInfo));
    DiscardProgressBarInfo (progressBarInfo);

Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC_C ProgressBar_SetAttribute (int panel, int progressBarCtrl, int attribute, ...)
{
    ProgressBarInfo progressBarInfo = NULL;
    va_list         parmInfo;
    double          percentage, doubleVal;
    int             locked = FALSE, error = UIENoError, vaStarted = FALSE, intVal, controlLength;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    va_start(parmInfo,attribute);
    vaStarted = TRUE;
    
    switch (attribute)
    {
        case ATTR_PROGRESSBAR_UPDATE_MODE:
            intVal = va_arg(parmInfo,int);
            switch (intVal)
            {
                case VAL_PROGRESSBAR_MANUAL_MODE:
                    if (progressBarInfo->timerObj > 0)
                    {
                        sysChk(DiscardAsyncTimer (progressBarInfo->timerObj));
                        progressBarInfo->timerObj = 0;
                    }
                    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                        ATTR_PARTIAL_FILL_SIZE, 0));
                    errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
                        progressBarInfo->flags & kReverseFlagMask ?
                        100.0 - progressBarInfo->percentage : progressBarInfo->percentage));
                    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_ABORTED)
                    {
                        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                            ATTR_DRAW_ERROR_STATE, TRUE));
                        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                            ATTR_FILL_COLOR, progressBarInfo->abortColor));
                    }
                    break;
                case VAL_PROGRESSBAR_AUTO_MODE:
                    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_RUNNING)
                        if (progressBarInfo->timerObj == 0)
                            sysChk(progressBarInfo->timerObj = NewAsyncTimer (TIMER_INCREMENT, -1, 1,
                                ProgressBarTimerCallback, (void *)progressBarInfo));
                    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                        ATTR_PARTIAL_FILL_SIZE, 0));
                    errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
                        progressBarInfo->flags & kReverseFlagMask ?
                        100.0 - progressBarInfo->percentage : progressBarInfo->percentage));
                    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_ABORTED)
                    {
                        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                            ATTR_DRAW_ERROR_STATE, TRUE));
                        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                            ATTR_FILL_COLOR, progressBarInfo->abortColor));
                    }
                    break;
                case VAL_PROGRESSBAR_MARQUEE_MODE:
                    errChk(GetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                        progressBarInfo->flags & kVerticalFlagMask ? ATTR_HEIGHT : ATTR_WIDTH,
                        &controlLength));
                    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_RUNNING ||
                        progressBarInfo->sessionState == PROGRESSBAR_STATE_PAUSED)
                    {
                        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                            ATTR_PARTIAL_FILL_SIZE, (int)(controlLength * MARQUEE_SIZE)));
                        if (progressBarInfo->sessionState == PROGRESSBAR_STATE_RUNNING)
                            if (progressBarInfo->timerObj == 0)
                                sysChk(progressBarInfo->timerObj = NewAsyncTimer (TIMER_INCREMENT, -1, 1,
                                    ProgressBarTimerCallback, (void *)progressBarInfo));
                    }
                    break;
                default:
                    errChk(UIEBadAttributeValue);
            }
            ProcessDrawEvents();    // needed for the possible invalidation in ATTR_PARTIAL_FILL_SIZE
            progressBarInfo->mode = intVal;
            break;
        case ATTR_PROGRESSBAR_BAR_COLOR:
            intVal = va_arg(parmInfo,int);
            if (!IsValidColor (intVal))
                errChk(UIEBadAttributeValue);
            if (progressBarInfo->sessionState != PROGRESSBAR_STATE_ABORTED)
                errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                    ATTR_FILL_COLOR, intVal));
            progressBarInfo->color = intVal;
            break;
        case ATTR_PROGRESSBAR_BAR_ABORT_COLOR:
            intVal = va_arg(parmInfo,int);
            if (!IsValidColor (intVal))
                errChk(UIEBadAttributeValue);
            if (progressBarInfo->mode != VAL_PROGRESSBAR_MARQUEE_MODE &&
                progressBarInfo->sessionState == PROGRESSBAR_STATE_ABORTED)
                errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                    ATTR_FILL_COLOR, intVal));
            progressBarInfo->abortColor = intVal;
            break;
        case ATTR_PROGRESSBAR_REVERSE_DIRECTION:
            errChk(GetCtrlVal (progressBarInfo->panel, progressBarInfo->control, &percentage));
            intVal = va_arg(parmInfo,int);
            if (intVal && ~progressBarInfo->flags & kReverseFlagMask)
            {
                progressBarInfo->flags |= kReverseFlagMask;
                if (progressBarInfo->flags & kVerticalFlagMask)
                {
                    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                        ATTR_FILL_OPTION, VAL_TOP_FILL));
                }
                else
                    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                        ATTR_FILL_OPTION, VAL_RIGHT_FILL));

                errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
                    100.0 - percentage));
            }
            if (!intVal && progressBarInfo->flags & kReverseFlagMask)
            {
                progressBarInfo->flags &= ~kReverseFlagMask;
                if (progressBarInfo->flags & kVerticalFlagMask)
                {
                    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                        ATTR_FILL_OPTION, VAL_BOTTOM_FILL));
                }
                else
                    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                        ATTR_FILL_OPTION, VAL_LEFT_FILL));
                errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
                    100.0 - percentage));
            }
            break;
        case ATTR_PROGRESSBAR_AUTO_ADJUST:
            intVal = va_arg(parmInfo,int);
            if (intVal)
                progressBarInfo->flags |= kAutoAdjustFlagMask;
            else
                progressBarInfo->flags &= ~kAutoAdjustFlagMask;
            break;
        case ATTR_PROGRESSBAR_ADJUSTMENT_TYPE:
            intVal = va_arg(parmInfo,int);
            switch (intVal)
            {
                case VAL_PROGRESSBAR_ADJUST_POSITION:
                case VAL_PROGRESSBAR_ADJUST_RATE:
                    break;
                default:
                    errChk(UIEBadAttributeValue);
            }
            progressBarInfo->adjustmentType = intVal;
            break;
        case ATTR_PROGRESSBAR_MARQUEE_SPEED:
            doubleVal = va_arg(parmInfo,double);
            progressBarInfo->marqueeSpeed = doubleVal;
            break;
        case ATTR_PROGRESSBAR_SYNC_TO_TASKBAR:
            intVal = va_arg(parmInfo,int);
            if (intVal) 
            {
                errChk(InitializeITaskbarList4 (progressBarInfo));
            } 
            else 
            {
                DisposeITaskbarList4 (progressBarInfo);
            }
            break;
        default:
            errChk(UIEInvalidAttribute);
            break;
    }
            
Error:
    if (vaStarted)
        va_end(parmInfo);
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_GetAttribute (int panel, int progressBarCtrl, int attribute, void *value)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!value)
        errChk(UIENullPointerPassed);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    switch (attribute)
    {
        case ATTR_PROGRESSBAR_UPDATE_MODE:
            *(int *)value = progressBarInfo->mode;
            break;
        case ATTR_PROGRESSBAR_BAR_COLOR:
            *(int *)value = progressBarInfo->color;
            break;
        case ATTR_PROGRESSBAR_BAR_ABORT_COLOR:
            *(int *)value = progressBarInfo->abortColor;
            break;
        case ATTR_PROGRESSBAR_REVERSE_DIRECTION:
            *(int *)value = progressBarInfo->flags & kReverseFlagMask ? TRUE : FALSE;
            break;
        case ATTR_PROGRESSBAR_AUTO_ADJUST:
            *(int *)value = progressBarInfo->flags & kAutoAdjustFlagMask ? TRUE : FALSE;
            break;
        case ATTR_PROGRESSBAR_ADJUSTMENT_TYPE:
            *(int *)value = progressBarInfo->adjustmentType;
            break;
        case ATTR_PROGRESSBAR_MARQUEE_SPEED:
            *(double *)value = progressBarInfo->marqueeSpeed;
            break;
        case ATTR_PROGRESSBAR_SYNC_TO_TASKBAR:
            *(int *)value = IsProgressBarSyncedWithTaskbar (progressBarInfo);
            break;
        default:
            errChk(UIEInvalidAttribute);
            break;
    }

Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/
    
int CVIFUNC ProgressBar_SetPercentage (int panel, int progressBarCtrl, double percentage,
    char *label)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (percentage < 0.0 || percentage > 100.0)
        errChk(UIEValueIsInvalidOrOutOfRange);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    progressBarInfo->percentage = percentage;
    progressBarInfo->eventSent = FALSE;

    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_ABORTED)
    {
        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
            ATTR_DRAW_ERROR_STATE, FALSE));
        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control, ATTR_FILL_COLOR,
            progressBarInfo->color));
        progressBarInfo->sessionState = PROGRESSBAR_STATE_STOPPED;
    }
    
    if (progressBarInfo->mode != VAL_PROGRESSBAR_MARQUEE_MODE)
        errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
            progressBarInfo->flags & kReverseFlagMask ? 100.0 - percentage : percentage));
    if (label)
    {
        errChk(SetCtrlAttribute (panel, progressBarInfo->control, ATTR_LABEL_TEXT, label));
        errChk(ProcessDrawEvents());
    }
    ITaskbarList4SetPercentage (progressBarInfo, progressBarInfo->percentage);
    
Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_GetPercentage (int panel, int progressBarCtrl, double *percentage)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!percentage)
        errChk(UIENullPointerPassed);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    *percentage = progressBarInfo->percentage;
    
Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC_C ProgressBar_SetMilestones (int panel, int progressBarCtrl, ...)
{
    ProgressBarInfo progressBarInfo = NULL;
    ListType        newMilestoneList = NULL, markerList = NULL;
    Milestone       milestone;
    size_t          i, numMilestones;
    double          percentMarker, prevPercentMarker;
    int             locked = FALSE, error = UIENoError, vaStarted = FALSE;
    va_list         parmInfo;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    nullChk(newMilestoneList = ListCreate (sizeof (Milestone)));
    nullChk(markerList = ListCreate (sizeof (double)));
    
    va_start(parmInfo,progressBarCtrl);
    vaStarted = TRUE;

    percentMarker = va_arg(parmInfo,double);
    while (percentMarker != 0.0)
    {
        if (percentMarker < 0.0 || percentMarker > 100.0)
            errChk(UIEValueIsInvalidOrOutOfRange);

        if (ListFindItem (markerList, &percentMarker, FRONT_OF_LIST, DoubleCompare) != 0)
            errChk(UIEValueIsInvalidOrOutOfRange);

        nullChk(ListInsertItem (markerList, &percentMarker, END_OF_LIST));

        percentMarker = va_arg(parmInfo,double);
    }
    ListQuickSort (markerList, DoubleCompare);

    prevPercentMarker = 0.0;
    numMilestones = ListNumItems (markerList);
    for (i = 1; i <= numMilestones; i++)
    {
        ListGetItem (markerList, &percentMarker, i);
    
        milestone.percentMarker = percentMarker;
        milestone.interval.avgTime = progressBarInfo->totalTime.avgTime *
            (percentMarker - prevPercentMarker) / 100.0;
        milestone.interval.count = 1;

		nullChk(ListInsertItem (newMilestoneList, &milestone, END_OF_LIST));

        prevPercentMarker = percentMarker;
    }

Error:
    if (vaStarted)
        va_end(parmInfo);
    if (newMilestoneList)
        if (error < 0)
            ListDispose (newMilestoneList);
        else
        {
            ListDispose (progressBarInfo->milestoneList);
            progressBarInfo->milestoneList = newMilestoneList;
            progressBarInfo->milestoneIndex = 0;
            progressBarInfo->eventSent = FALSE;
            ListClear (progressBarInfo->milestoneTimeStampList);
        }
    if (markerList)
        ListDispose (markerList);
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_AddMilestone (int panel, int progressBarCtrl, double percentage)
{
    ProgressBarInfo progressBarInfo = NULL;
    Milestone       milestone, prevMilestone;
    size_t          pos, startPos;
    double          prevPercentage;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (percentage <= 0.0 || percentage > 100.0)
        errChk(UIEValueIsInvalidOrOutOfRange);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_RUNNING ||
        progressBarInfo->sessionState == PROGRESSBAR_STATE_PAUSED)
        errChk(ToolErr_OperationInProgress);

    milestone.percentMarker = percentage;
    milestone.interval.count = 0;

    if (ListFindItem (progressBarInfo->milestoneList, &milestone, FRONT_OF_LIST,
        (CompareFunction)MilestoneCompare) != 0)
        errChk(UIEValueIsInvalidOrOutOfRange);

	nullChk(ListInsertInOrder (progressBarInfo->milestoneList, &milestone,
        (CompareFunction)MilestoneCompare));

    startPos = 1;
    while (TRUE)    // find the index of the item we've just inserted, accounting for possible duplicates
    {
        pos = ListFindItem (progressBarInfo->milestoneList, &milestone, startPos,
            (CompareFunction)MilestoneCompare);
        if (pos != 0 && milestone.interval.count == 0)
            break;
        startPos = pos + 1;
    }
    if (pos > 1)
    {
        ListGetItem (progressBarInfo->milestoneList, &prevMilestone, pos - 1);
        prevPercentage = prevMilestone.percentMarker;
    }
    else
        prevPercentage = 0;     

    milestone.interval.avgTime = progressBarInfo->totalTime.avgTime *
        (percentage - prevPercentage) / 100.0;
    milestone.interval.count = 1;
    ListReplaceItem (progressBarInfo->milestoneList, &milestone, pos);

Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_LoadMilestones (int panel, int progressBarCtrl, char *dataFile,
    int includeTimeData)
{
    ProgressBarInfo progressBarInfo = NULL;
    IniText         iniObj = NULL;
    ListType        newMilestoneList = NULL;
    Milestone       milestone;
    double          prevPercentMarker;
    int             locked = FALSE, error = UIENoError, i;
    char            sectionName[256];

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!dataFile)
        errChk(UIENullPointerPassed);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;
    
    nullChk(newMilestoneList = ListCreate (sizeof (Milestone)));
    
    nullChk(iniObj = Ini_New (0));
    errChk(Ini_ReadFromFile (iniObj, dataFile));

    sprintf (sectionName, "Total_Time");
    if (includeTimeData && Ini_ItemExists (iniObj, sectionName, "interval"))
    {
        errChk(Ini_GetDouble (iniObj, sectionName, "interval",
            &progressBarInfo->totalTime.avgTime));
        errChk(Ini_GetInt (iniObj, sectionName, "occurrences", &progressBarInfo->totalTime.count));
    }
    
    i = 1;
    sprintf (sectionName, "Milestone_%03d", i);
    prevPercentMarker = 0.0;
    while (Ini_SectionExists (iniObj, sectionName))
    {
        errChk(Ini_GetDouble (iniObj, sectionName, "percentage", &milestone.percentMarker));
        if (includeTimeData && Ini_ItemExists (iniObj, sectionName, "interval"))
        {
            errChk(Ini_GetDouble (iniObj, sectionName, "interval",
                &milestone.interval.avgTime));
            errChk(Ini_GetInt (iniObj, sectionName, "occurrences", &milestone.interval.count));
        }
        else
        {
            milestone.interval.avgTime = progressBarInfo->totalTime.avgTime *
                (milestone.percentMarker - prevPercentMarker) / 100.0;
            milestone.interval.count = 1;
        }

		nullChk(ListInsertItem (newMilestoneList, &milestone, i));

        sprintf (sectionName, "Milestone_%03d", ++i);
        prevPercentMarker = milestone.percentMarker;
    }

Error:
    if (newMilestoneList)
        if (error < 0)
            ListDispose (newMilestoneList);
        else
        {
            ListDispose (progressBarInfo->milestoneList);
            progressBarInfo->milestoneList = newMilestoneList;
            progressBarInfo->milestoneIndex = 0;
            progressBarInfo->eventSent = FALSE;
            ListClear (progressBarInfo->milestoneTimeStampList);
        }
    if (iniObj)
        Ini_Dispose (iniObj);
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_SaveMilestones (int panel, int progressBarCtrl, char *dataFile,
    int includeTimeData)
{
    ProgressBarInfo progressBarInfo = NULL;
    IniText         iniObj = NULL;
    Milestone       milestone;
    size_t          i, numMilestones;
    int             locked = FALSE, error = UIENoError;
    char            sectionName[256];

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!dataFile)
        errChk(UIENullPointerPassed);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;
    
    nullChk(iniObj = Ini_New (0));

    sprintf (sectionName, "Total_Time");
    if (includeTimeData)
    {
        errChk(Ini_PutDouble (iniObj, sectionName, "interval",
            progressBarInfo->totalTime.avgTime));
        errChk(Ini_PutInt (iniObj, sectionName, "occurrences", progressBarInfo->totalTime.count));
    }
    
    numMilestones = ListNumItems (progressBarInfo->milestoneList);
    for (i = 1; i <= numMilestones; i++)
    {
        ListGetItem (progressBarInfo->milestoneList, &milestone, i);
        sprintf (sectionName, "Milestone_%03zd", i);
        errChk(Ini_PutDouble (iniObj, sectionName, "percentage", milestone.percentMarker));
        if (includeTimeData)
        {
            errChk(Ini_PutDouble (iniObj, sectionName, "interval", milestone.interval.avgTime));
            errChk(Ini_PutInt (iniObj, sectionName, "occurrences", milestone.interval.count));
        }
    }
    errChk(Ini_WriteToFile (iniObj, dataFile));

Error:
    if (iniObj)
        Ini_Dispose (iniObj);
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_ClearMilestones (int panel, int progressBarCtrl)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    ListClear (progressBarInfo->milestoneList);
    progressBarInfo->milestoneIndex = 0;
    progressBarInfo->eventSent = FALSE;
    ListClear (progressBarInfo->milestoneTimeStampList);
    
Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_GetNumMilestones (int panel, int progressBarCtrl, size_t *numMilestones)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!numMilestones)
        errChk(UIENullPointerPassed);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;
    
    *numMilestones = ListNumItems (progressBarInfo->milestoneList);

Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_GetMilestone (int panel, int progressBarCtrl, size_t milestoneIndex,
    double *percentage)
{
    ProgressBarInfo progressBarInfo = NULL;
    Milestone       milestone;
    size_t          numMilestones;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!percentage)
        errChk(UIENullPointerPassed);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    numMilestones = ListNumItems (progressBarInfo->milestoneList);
    if (milestoneIndex == 0 || milestoneIndex > numMilestones)
        errChk(UIEIndexOutOfRange);
    
    ListGetItem (progressBarInfo->milestoneList, &milestone, milestoneIndex);
    *percentage = milestone.percentMarker;

Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_GetCurrentMilestoneIndex (int panel, int progressBarCtrl,
    size_t *milestoneIndex)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!milestoneIndex)
        errChk(UIENullPointerPassed);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    *milestoneIndex = progressBarInfo->milestoneIndex;

Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_AdvanceMilestone (int panel, int progressBarCtrl, char *label)
{
    ProgressBarInfo progressBarInfo = NULL;
    Milestone       milestone;
    size_t          numMilestones;
    double          totalTime, timeStamp;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    numMilestones = ListNumItems (progressBarInfo->milestoneList);
    
    if (progressBarInfo->milestoneIndex == numMilestones)
    {
        errChk(ProgressBar_End (panel, progressBarCtrl, &totalTime, label));
    }
    else
    {
        progressBarInfo->milestoneIndex++;
        progressBarInfo->eventSent = FALSE;

        timeStamp = Timer();
        if (progressBarInfo->sessionState == PROGRESSBAR_STATE_PAUSED)
            timeStamp -= timeStamp - progressBarInfo->pausedTimeStamp;
        timeStamp -= progressBarInfo->totalPausedTime;
		nullChk(ListInsertItem (progressBarInfo->milestoneTimeStampList, &timeStamp,
            progressBarInfo->milestoneIndex));

        ListGetItem (progressBarInfo->milestoneList, &milestone, progressBarInfo->milestoneIndex);
        progressBarInfo->percentage = milestone.percentMarker;
        if (progressBarInfo->mode != VAL_PROGRESSBAR_MARQUEE_MODE)
            errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
                progressBarInfo->flags & kReverseFlagMask ?
                100.0 - milestone.percentMarker : milestone.percentMarker));

        if (progressBarInfo->sessionState == PROGRESSBAR_STATE_ABORTED)
        {
            errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                ATTR_DRAW_ERROR_STATE, FALSE));
            errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                ATTR_FILL_COLOR, progressBarInfo->color));
            progressBarInfo->sessionState = PROGRESSBAR_STATE_STOPPED;
        }
        
        if (label)
        {
            errChk(SetCtrlAttribute (panel, progressBarInfo->control, ATTR_LABEL_TEXT, label));
            errChk(ProcessDrawEvents());
        }
        ITaskbarList4SetPercentage (progressBarInfo, progressBarInfo->percentage);
    }

Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_SetTotalTimeEstimate (int panel, int progressBarCtrl, double expectedTime)
{
    ProgressBarInfo progressBarInfo = NULL;
    Milestone       milestone;
    size_t          i, numMilestones;
    double          prevPercentMarker;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (expectedTime <= 0.0)
        errChk(UIEValueIsInvalidOrOutOfRange);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_RUNNING ||
        progressBarInfo->sessionState == PROGRESSBAR_STATE_PAUSED)
        errChk(ToolErr_OperationInProgress);
    progressBarInfo->totalTime.avgTime = expectedTime;
    progressBarInfo->totalTime.count = 1;
    
    prevPercentMarker = 0.0;
    numMilestones = ListNumItems (progressBarInfo->milestoneList);
    for (i = 1; i < numMilestones; i++)
    {
        ListGetItem (progressBarInfo->milestoneList, &milestone, i);

        milestone.interval.avgTime = progressBarInfo->totalTime.avgTime *
            (milestone.percentMarker - prevPercentMarker) / 100.0;
        milestone.interval.count = 1;

        ListReplaceItem (progressBarInfo->milestoneList, &milestone, i);
        
        prevPercentMarker = milestone.percentMarker;
    }
    
Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_GetTotalTimeEstimate (int panel, int progressBarCtrl, double *expectedTime)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!expectedTime)
        errChk(UIENullPointerPassed);
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;
    
    *expectedTime = progressBarInfo->totalTime.avgTime;
    
Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_Start (int panel, int progressBarCtrl, char *label)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError, controlLength;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    progressBarInfo->milestoneIndex = 0;
    progressBarInfo->eventSent = FALSE;
    progressBarInfo->percentage = 0.0;
    errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
        progressBarInfo->flags & kReverseFlagMask ? 100.0 : 0.0));
    progressBarInfo->sessionState = PROGRESSBAR_STATE_RUNNING;

    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control, ATTR_DRAW_ERROR_STATE,
        FALSE));
    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control, ATTR_FILL_COLOR,
        progressBarInfo->color));
    
    if (progressBarInfo->mode == VAL_PROGRESSBAR_AUTO_MODE ||
        progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
    {
        if (progressBarInfo->timerObj == 0)
            sysChk(progressBarInfo->timerObj = NewAsyncTimer (TIMER_INCREMENT, -1, 1,
                ProgressBarTimerCallback, (void *)progressBarInfo));

        if (progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
        {
            errChk(GetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                progressBarInfo->flags & kVerticalFlagMask ? ATTR_HEIGHT : ATTR_WIDTH,
                &controlLength));
            errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                ATTR_PARTIAL_FILL_SIZE, (int)(controlLength * MARQUEE_SIZE)));
        }
    }

    if (label)
    {
        errChk(SetCtrlAttribute (panel, progressBarInfo->control, ATTR_LABEL_TEXT, label));
        errChk(ProcessDrawEvents());
    }

    progressBarInfo->totalPausedTime = 0.0;
    progressBarInfo->initialTimeStamp = Timer();
    ITaskbarList4SetState (progressBarInfo);
    
Error:
    if (error < 0 && progressBarInfo)
    {
        progressBarInfo->sessionState = PROGRESSBAR_STATE_STOPPED;
        if (progressBarInfo->timerObj > 0)
        {
            DiscardAsyncTimer (progressBarInfo->timerObj);
            progressBarInfo->timerObj = 0;
        }
    }
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_End (int panel, int progressBarCtrl, double *totalTime, char *label)
{
    ProgressBarInfo progressBarInfo = NULL;
    double          timeStamp;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_PAUSED)
        errChk(ProgressBar_Resume (panel, progressBarCtrl, NULL));
    
    timeStamp = Timer();
    timeStamp -= progressBarInfo->totalPausedTime;
    
    progressBarInfo->milestoneIndex = 0;
    progressBarInfo->eventSent = FALSE;
    if (progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
        progressBarInfo->percentage = 0.0;
    else
        progressBarInfo->percentage = 100.0;

    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_ABORTED)
    {
        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
            ATTR_DRAW_ERROR_STATE, FALSE));
        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
            ATTR_FILL_COLOR, progressBarInfo->color));
        progressBarInfo->sessionState = PROGRESSBAR_STATE_STOPPED;
    }
    
    if (progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
            ATTR_PARTIAL_FILL_SIZE, 0));

    errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
        progressBarInfo->flags & kReverseFlagMask ?
        100.0 - progressBarInfo->percentage : progressBarInfo->percentage));
    
    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_RUNNING)
    {
        progressBarInfo->sessionState = PROGRESSBAR_STATE_STOPPED;
    
        if (progressBarInfo->timerObj > 0)
        {
            sysChk(DiscardAsyncTimer (progressBarInfo->timerObj));
            progressBarInfo->timerObj = 0;
        }

        if (progressBarInfo->flags & kAutoAdjustFlagMask)
            AdjustProgressBarTimes (progressBarInfo, timeStamp);
    
        if (totalTime)
            *totalTime = timeStamp - progressBarInfo->initialTimeStamp;
    }

    if (label)
    {
        errChk(SetCtrlAttribute (panel, progressBarInfo->control, ATTR_LABEL_TEXT, label));
        errChk(ProcessDrawEvents());
    }
    
    ITaskbarList4SetState (progressBarInfo);
    
Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_Abort (int panel, int progressBarCtrl, int fillToEnd, char *label)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;
    if (progressBarInfo->timerObj > 0)
    {
        sysChk(DiscardAsyncTimer (progressBarInfo->timerObj));
        progressBarInfo->timerObj = 0;
    }

    if (progressBarInfo->sessionState == PROGRESSBAR_STATE_PAUSED)
        errChk(ProgressBar_Resume (panel, progressBarCtrl, NULL));
    progressBarInfo->sessionState = PROGRESSBAR_STATE_ABORTED;

    progressBarInfo->milestoneIndex = 0;
    progressBarInfo->eventSent = FALSE;
    
    progressBarInfo->percentage = fillToEnd ? 100.0 : 0.0;

    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control, ATTR_FILL_COLOR,
        progressBarInfo->abortColor));
    if (progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
        errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
            ATTR_PARTIAL_FILL_SIZE, 0));
        
    errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control, ATTR_DRAW_ERROR_STATE,
        TRUE));
    errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
        progressBarInfo->flags & kReverseFlagMask ?
        100.0 - progressBarInfo->percentage : progressBarInfo->percentage));

    if (progressBarInfo->timerObj > 0)
    {
        sysChk(DiscardAsyncTimer (progressBarInfo->timerObj));
        progressBarInfo->timerObj = 0;
    }
    
    if (label)
    {
        errChk(SetCtrlAttribute (panel, progressBarInfo->control, ATTR_LABEL_TEXT, label));
        errChk(ProcessDrawEvents());
    }

    ITaskbarList4SetState (progressBarInfo);
    if (progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
        ITaskbarList4SetPercentage (progressBarInfo, 100.0);
    
Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_Pause (int panel, int progressBarCtrl, char *label)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    if (label)
    {
        errChk(SetCtrlAttribute (panel, progressBarInfo->control, ATTR_LABEL_TEXT, label));
        errChk(ProcessDrawEvents());
    }
    
    if (progressBarInfo->sessionState != PROGRESSBAR_STATE_RUNNING)
        goto Error;
    progressBarInfo->sessionState = PROGRESSBAR_STATE_PAUSED;

    if (progressBarInfo->timerObj > 0)
    {
        sysChk(DiscardAsyncTimer (progressBarInfo->timerObj));
        progressBarInfo->timerObj = 0;
    }

    progressBarInfo->pausedTimeStamp = Timer();
    
    ITaskbarList4SetState (progressBarInfo);
    if (progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
        ITaskbarList4SetPercentage (progressBarInfo, 100.0);
    
Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

int CVIFUNC ProgressBar_Resume (int panel, int progressBarCtrl, char *label)
{
    ProgressBarInfo progressBarInfo = NULL;
    double          timeStamp;
    int             locked = FALSE, error = UIENoError;

    errChk(GetChainedCallbackData (panel, progressBarCtrl, PROGRESSBAR_CTRL_TYPE,
        (void **)&progressBarInfo));
    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    if (label)
    {
        errChk(SetCtrlAttribute (panel, progressBarInfo->control, ATTR_LABEL_TEXT, label));
        errChk(ProcessDrawEvents());
    }
    
    if (progressBarInfo->sessionState != PROGRESSBAR_STATE_PAUSED)
        goto Error;

    timeStamp = Timer();
    
    if (progressBarInfo->mode == VAL_PROGRESSBAR_AUTO_MODE ||
        progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
        if (progressBarInfo->timerObj == 0)
            sysChk(progressBarInfo->timerObj = NewAsyncTimer (TIMER_INCREMENT, -1, 1,
                ProgressBarTimerCallback, (void *)progressBarInfo));

    progressBarInfo->totalPausedTime += timeStamp - progressBarInfo->pausedTimeStamp;
    
    progressBarInfo->sessionState = PROGRESSBAR_STATE_RUNNING;

    ITaskbarList4SetState (progressBarInfo);
    
Error:
    UNLOCK;
    return (error < 0 ? error : UIENoError);
}

/*****************************************************************************************/

static int CreateProgressBarInfo (int panel, int ctrl, int vertical,
    ProgressBarInfo *newProgressBarInfo)
{
    ProgressBarInfo progressBarInfo = NULL;
    int             error = UIENoError, locked = FALSE;

    // Create the global lock - will never be destroyed
    if (!g_bLockInited)
    {
#if defined (_NI_mswin_) && _NI_mswin_
        InitializeCriticalSection (&g_lock);
#elif defined (_NI_linux_) && _NI_linux_
        pthread_mutexattr_t attributes;
        pthread_mutexattr_init (&attributes);
        pthread_mutexattr_settype (&attributes, PTHREAD_MUTEX_RECURSIVE_NP);
        pthread_mutex_init (&g_lock, &attributes);
        pthread_mutexattr_destroy (&attributes);
#endif
        g_bLockInited = TRUE;
    }
    LOCK;

    nullChk(progressBarInfo = (ProgressBarInfo)calloc (sizeof (*progressBarInfo), 1));

    progressBarInfo->panel = panel;
    progressBarInfo->control = ctrl;

    nullChk(progressBarInfo->milestoneList = ListCreate (sizeof (Milestone)));
    nullChk(progressBarInfo->milestoneTimeStampList = ListCreate (sizeof (double)));
    
    progressBarInfo->totalTime.avgTime = INITIAL_TIME_INTERVAL;
    progressBarInfo->totalTime.count = 1;
    
    progressBarInfo->sessionState = PROGRESSBAR_STATE_STOPPED;
    progressBarInfo->mode = VAL_PROGRESSBAR_AUTO_MODE;
    progressBarInfo->adjustmentType = VAL_PROGRESSBAR_ADJUST_POSITION;
    
    progressBarInfo->percentage = 0.0;
    progressBarInfo->milestoneIndex = 0;
    progressBarInfo->eventSent = FALSE;
    
    progressBarInfo->marqueeSpeed = INITIAL_MARQUEE_SPEED;
    
    errChk(GetCtrlAttribute (panel, ctrl, ATTR_FILL_COLOR, &progressBarInfo->color));
    progressBarInfo->abortColor = INITIAL_ABORT_COLOR;
    
    progressBarInfo->flags |= kAutoAdjustFlagMask;
    if (vertical)
        progressBarInfo->flags |= kVerticalFlagMask;

    errChk(ChainCtrlCallback (panel, ctrl, ProgressBarCtrlCallback, (void *)progressBarInfo,
        PROGRESSBAR_CTRL_TYPE));

    if (newProgressBarInfo)
        *newProgressBarInfo = progressBarInfo;

Error:
    if (error < 0)
        if (newProgressBarInfo)
            *newProgressBarInfo = NULL;
    UNLOCK;
    return error;
}

/*****************************************************************************************/

static int DiscardProgressBarInfo (ProgressBarInfo progressBarInfo)
{
    int error = UIENoError, locked = FALSE;

    if (!g_bLockInited)
        errChk(UIEInvalidControlId);
    LOCK;

    if (progressBarInfo)
    {
        DisposeITaskbarList4 (progressBarInfo);
        if (progressBarInfo->milestoneList)
            ListDispose (progressBarInfo->milestoneList);
        if (progressBarInfo->milestoneList)
            ListDispose (progressBarInfo->milestoneTimeStampList);
        if (progressBarInfo->timerObj > 0)
            DiscardAsyncTimer (progressBarInfo->timerObj);
        if (progressBarInfo->panel && progressBarInfo->control)
            UnchainCtrlCallback (progressBarInfo->panel, progressBarInfo->control,
                PROGRESSBAR_CTRL_TYPE);
        free (progressBarInfo);
    }
    
Error:
    UNLOCK;
    return error;
}

/*****************************************************************************************/

static void AdjustProgressBarTimes (ProgressBarInfo progressBarInfo, double newTotalTime)
{
    Milestone   milestone;
    double      interval, timeStamp, prevTimeStamp, prevPercentage;
    int         weightedCount;
    size_t      i, numMilestones;

    /********************************************************************************************/
    /* instead of simply averaging all the historic times equally with the current time, we     */
    /* weigh the current time more heavily. The square root is an arbitrary choice, but it has  */
    /* roughly the desired proportion between the current time and historic times. It also has  */
    /* the desired property that at smaller counts, the bias towards the current time is higher */
    /********************************************************************************************/
    weightedCount = (int)ceil (sqrt (progressBarInfo->totalTime.count));
    progressBarInfo->totalTime.avgTime =
        (progressBarInfo->totalTime.avgTime * progressBarInfo->totalTime.count +
        (newTotalTime - progressBarInfo->initialTimeStamp) * weightedCount) /
        (progressBarInfo->totalTime.count + weightedCount);
    progressBarInfo->totalTime.count++;

    prevPercentage = 0.0;
    prevTimeStamp = progressBarInfo->initialTimeStamp;
    numMilestones = ListNumItems (progressBarInfo->milestoneTimeStampList);
    for (i = 1; i <= numMilestones; i++)
    {
        ListGetItem (progressBarInfo->milestoneTimeStampList, &timeStamp, i);
        interval = timeStamp - prevTimeStamp;

        ListGetItem (progressBarInfo->milestoneList, &milestone, i);

        weightedCount = (int)ceil (sqrt (milestone.interval.count));
        milestone.interval.avgTime = (milestone.interval.avgTime * milestone.interval.count +
            interval * weightedCount) / (milestone.interval.count + weightedCount);
        milestone.interval.count++;
        if (progressBarInfo->adjustmentType == VAL_PROGRESSBAR_ADJUST_POSITION)
            milestone.percentMarker = prevPercentage +
                milestone.interval.avgTime * 100.0 / progressBarInfo->totalTime.avgTime;

        ListReplaceItem (progressBarInfo->milestoneList, &milestone, i);
        
        prevPercentage = milestone.percentMarker;
        prevTimeStamp = timeStamp;
    }

    /********************************************************************************************/
    /* if there weren't as many time stamps as there are milestones (if, for example, the       */
    /* session ended prematurely), then ensure that the remaining milestones don't have lower   */
    /* values than the highest milestone that was adjusted                                      */
    /********************************************************************************************/
    prevPercentage = 0.0;
    numMilestones = ListNumItems (progressBarInfo->milestoneList);
    for (; i <= numMilestones; i++)
    {
        ListGetItem (progressBarInfo->milestoneList, &milestone, i);
        
        if (milestone.percentMarker < prevPercentage)
        {
            milestone.percentMarker = prevPercentage;
            ListReplaceItem (progressBarInfo->milestoneList, &milestone, i);
        }
    }
    
    return;
}

/*****************************************************************************************/

static int CanShrinkMarquee (ProgressBarInfo progressBarInfo, double percentage, int *marqueeSize)
{
    double  gap;
    int     error = UIENoError, canShrink = TRUE, controlLength, gapInPixels;

    errChk(GetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
        progressBarInfo->flags & kVerticalFlagMask ? ATTR_HEIGHT : ATTR_WIDTH, &controlLength));
    
    errChk(GetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
        ATTR_PARTIAL_FILL_SIZE, marqueeSize));
    
    if (percentage <= 100.0)
        goto Error;
    
    gap = percentage - 100.0;
    gapInPixels = controlLength * gap / 100.0;
    if (gapInPixels >= (int)(controlLength * MARQUEE_SIZE))
    {
        *marqueeSize = 0;
        canShrink = FALSE;
    }
    else
        *marqueeSize = (int)(controlLength * MARQUEE_SIZE) - gapInPixels;
    
Error:
    if (error != UIENoError)
        return FALSE;
    else
        return canShrink;
    
}

/*****************************************************************************************/

static int RevertSlideCtrl (int panel, int slideCtrl, ProgressBarInfo progressBarInfo)
{
    int error = UIENoError;

    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_PARTIAL_FILL_SIZE, 0));
    
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_USE_PROGRESS_BAR_VISUAL_STYLES, progressBarInfo->slideConfig.progressBarStyle));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_MODE, progressBarInfo->slideConfig.mode));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_SHOW_DIG_DISP, progressBarInfo->slideConfig.showDigDisp));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_SHOW_INCDEC_ARROWS, progressBarInfo->slideConfig.showIncDec));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MARKER_STYLE, progressBarInfo->slideConfig.markerStyle));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_TICK_STYLE, progressBarInfo->slideConfig.tickStyle));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_FILL_OPTION, progressBarInfo->slideConfig.fillOption));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_LABEL_LEFT, progressBarInfo->slideConfig.labelLeft));

    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DATA_TYPE, progressBarInfo->slideConfig.dataType));
    switch (progressBarInfo->slideConfig.dataType)
    {
        case VAL_CHAR:
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.i8.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.i8.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.i8.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.i8.dflt));
            break;
        case VAL_INTEGER:
#ifndef _WIN64
		case VAL_INTPTR_T:
#endif
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.i32.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.i32.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.i32.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.i32.dflt));
            break;
        case VAL_SHORT_INTEGER:
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.i16.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.i16.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.i16.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.i16.dflt));
            break;
        case VAL_FLOAT:
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.f32.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.f32.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.f32.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.f32.dflt));
            break;
        case VAL_DOUBLE:
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.f64.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.f64.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.f64.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.f64.dflt));
            break;
        case VAL_UNSIGNED_SHORT_INTEGER:
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.u16.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.u16.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.u16.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.u16.dflt));
            break;
        case VAL_UNSIGNED_INTEGER:
#ifndef _WIN64
		case VAL_UINTPTR_T:
#endif
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.u32.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.u32.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.u32.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.u32.dflt));
            break;
        case VAL_UNSIGNED_CHAR:
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.u8.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.u8.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.u8.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.u8.dflt));
            break;
        case VAL_64BIT_INTEGER:
#ifdef _WIN64
		case VAL_INTPTR_T:
#endif
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.i64.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.i64.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.i64.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.i64.dflt));
            break;
        case VAL_UNSIGNED_64BIT_INTEGER:
#ifdef _WIN64
		case VAL_UINTPTR_T:
#endif
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, progressBarInfo->slideConfig.values.u64.max));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, progressBarInfo->slideConfig.values.u64.min));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, progressBarInfo->slideConfig.values.u64.val));
            errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, progressBarInfo->slideConfig.values.u64.dflt));
            break;
    }

Error:
    return error;
}

/*****************************************************************************************/

static int ConfigureSlideCtrl (int panel, int slideCtrl, int vertical, ProgressBarInfo progressBarInfo)
{
    int error = UIENoError, top, labelTop, labelHeight;

    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_USE_PROGRESS_BAR_VISUAL_STYLES, &progressBarInfo->slideConfig.progressBarStyle));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_USE_PROGRESS_BAR_VISUAL_STYLES, TRUE));

    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_MODE, &progressBarInfo->slideConfig.mode));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_MODE, VAL_INDICATOR));
    
    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_SHOW_DIG_DISP, &progressBarInfo->slideConfig.showDigDisp));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_SHOW_DIG_DISP, FALSE));
    
    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_SHOW_INCDEC_ARROWS, &progressBarInfo->slideConfig.showIncDec));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_SHOW_INCDEC_ARROWS, FALSE));
    
    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MARKER_STYLE, &progressBarInfo->slideConfig.markerStyle));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MARKER_STYLE, VAL_NO_MARKERS));
    
    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_TICK_STYLE, &progressBarInfo->slideConfig.tickStyle));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_TICK_STYLE, VAL_NO_TICKS));
    
    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_FILL_OPTION, &progressBarInfo->slideConfig.fillOption));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_FILL_OPTION,
        vertical ? VAL_BOTTOM_FILL : VAL_LEFT_FILL));
    
    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_LABEL_LEFT, &progressBarInfo->slideConfig.labelLeft));
    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_TOP, &top));
    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_LABEL_TOP, &labelTop));
    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_LABEL_HEIGHT, &labelHeight));
    if (labelTop + labelHeight < top)   // flush the label to the left of the control, only if it's above the control
        errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_LABEL_LEFT, VAL_LEFT_ANCHOR));

    errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DATA_TYPE, &progressBarInfo->slideConfig.dataType));
    switch (progressBarInfo->slideConfig.dataType)
    {
        case VAL_CHAR:
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.i8.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.i8.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.i8.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.i8.dflt));
            break;
        case VAL_INTEGER:
#ifndef _WIN64
		case VAL_INTPTR_T:
#endif
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.i32.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.i32.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.i32.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.i32.dflt));
            break;
        case VAL_SHORT_INTEGER:
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.i16.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.i16.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.i16.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.i16.dflt));
            break;
        case VAL_FLOAT:
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.f32.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.f32.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.f32.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.f32.dflt));
            break;
        case VAL_DOUBLE:
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.f64.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.f64.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.f64.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.f64.dflt));
            break;
        case VAL_UNSIGNED_SHORT_INTEGER:
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.u16.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.u16.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.u16.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.u16.dflt));
            break;
        case VAL_UNSIGNED_INTEGER:
#ifndef _WIN64
		case VAL_UINTPTR_T:
#endif
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.u32.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.u32.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.u32.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.u32.dflt));
            break;
        case VAL_UNSIGNED_CHAR:
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.u8.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.u8.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.u8.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.u8.dflt));
            break;
        case VAL_64BIT_INTEGER:
#ifdef _WIN64
		case VAL_INTPTR_T:
#endif
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.i64.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.i64.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.i64.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.i64.dflt));
            break;
        case VAL_UNSIGNED_64BIT_INTEGER:
#ifdef _WIN64
		case VAL_UINTPTR_T:
#endif
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, &progressBarInfo->slideConfig.values.u64.max));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, &progressBarInfo->slideConfig.values.u64.min));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, &progressBarInfo->slideConfig.values.u64.val));
            errChk(GetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, &progressBarInfo->slideConfig.values.u64.dflt));
            break;
    }

    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DATA_TYPE, VAL_DOUBLE));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MAX_VALUE, 100.0));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_MIN_VALUE, 0.0));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_CTRL_VAL, 0.0));
    errChk(SetCtrlAttribute (panel, slideCtrl, ATTR_DFLT_VALUE, 0.0));

Error:
    return error;
}

/*****************************************************************************************/

static int IsValidSlideControl (int panel, int ctrl, int *vertical)
{
    int ctrlStyle, valid = TRUE;

    GetCtrlAttribute (panel, ctrl, ATTR_CTRL_STYLE, &ctrlStyle);
    
    if (ctrlStyle == CTRL_NUMERIC_LEVEL_VSLIDE || ctrlStyle == CTRL_NUMERIC_LEVEL_VSLIDE_LS ||
        ctrlStyle == CTRL_NUMERIC_FLAT_VSLIDE)
        *vertical = TRUE;
    else if (ctrlStyle == CTRL_NUMERIC_LEVEL_HSLIDE || ctrlStyle == CTRL_NUMERIC_LEVEL_HSLIDE_LS ||
        ctrlStyle == CTRL_NUMERIC_FLAT_HSLIDE)
        *vertical = FALSE;
    else
        valid = FALSE;
    
    return valid;
}

/*****************************************************************************************/

static int IsValidColor (int color)
{
    return (color >=0 && color <= 0x1000000);
}

/*****************************************************************************************/

static int CVICALLBACK MilestoneCompare (Milestone *milestone1, Milestone *milestone2)
{
    if (milestone1->percentMarker < milestone2->percentMarker)
        return -1;
    else if (milestone1->percentMarker > milestone2->percentMarker)
        return 1;
    else
        return 0;
}

/*****************************************************************************************/

static int CVICALLBACK ProgressBarCtrlCallback (int panel, int control, int event,
    void *callbackData, int eventData1, int eventData2)
{
    ProgressBarInfo progressBarInfo = (ProgressBarInfo)callbackData;

    switch (event)
    {
        case EVENT_DISCARD:
            DiscardProgressBarInfo (progressBarInfo);
            break;
    }

    return 0;
}

/*****************************************************************************************/

static int CVICALLBACK ProgressBarTimerCallback (int reserved, int timerId, int event,
    void *callbackData, int eventData1, int eventData2)
{
    ProgressBarInfo progressBarInfo = (ProgressBarInfo)callbackData;
    Milestone       milestone;
    size_t          numMilestones;
    double          increment, percentage, prevPercentage, numPixels, timerInc;
    int             locked = FALSE, error = UIENoError, controlLength, marqueeSize;

    if (!g_bLockInited)
        errChk (UIEInvalidControlId);
    LOCK;

    if (event != EVENT_TIMER_TICK)
        goto Error;
    
    if (progressBarInfo->timerObj == 0)
        goto Error; // another thread might have discarded the timer while this thread waited at the lock
    
    if (progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
    {
        errChk(GetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
            progressBarInfo->flags & kVerticalFlagMask ? ATTR_HEIGHT : ATTR_WIDTH, &controlLength));

        GetAsyncTimerAttribute (timerId, ASYNC_ATTR_DELTA_TIME, &timerInc);

        numPixels = timerInc * progressBarInfo->marqueeSpeed;
        increment = numPixels * 100.0 / controlLength;

        progressBarInfo->marqueeVal += increment;
        percentage = progressBarInfo->marqueeVal;
        
        if (percentage > 100.0)
        {
            if (CanShrinkMarquee (progressBarInfo, percentage, &marqueeSize))
            {       // shrink the marquee so that the value can remain at 100.0, but the motion appear to continue
                percentage = 100.0;
                errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                    ATTR_PARTIAL_FILL_SIZE, marqueeSize));
            }
            else    // ran out of room: wrap the marquee back to the beginning. No need to shrink the marquee, since it will be clipped by the control
            {
                percentage -= 100.0;
                progressBarInfo->marqueeVal = percentage;
                errChk(SetCtrlAttribute (progressBarInfo->panel, progressBarInfo->control,
                    ATTR_PARTIAL_FILL_SIZE, (int)(controlLength * MARQUEE_SIZE)));
            }
        }
        errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
            progressBarInfo->flags & kReverseFlagMask ? 100.0 - percentage : percentage));
    }
    else
    {
        percentage = progressBarInfo->percentage;
        
        prevPercentage = 0.0;
        numMilestones = ListNumItems (progressBarInfo->milestoneList);
        if (numMilestones > progressBarInfo->milestoneIndex)
        {
            if (progressBarInfo->milestoneIndex > 0)
            {
                ListGetItem (progressBarInfo->milestoneList, &milestone,
                    progressBarInfo->milestoneIndex);
                prevPercentage = milestone.percentMarker;
            }
            ListGetItem (progressBarInfo->milestoneList, &milestone,
                progressBarInfo->milestoneIndex + 1);
            increment = (milestone.percentMarker - prevPercentage) * TIMER_INCREMENT /
                milestone.interval.avgTime;
            if (percentage + increment > milestone.percentMarker)
            {
                if (!progressBarInfo->eventSent)
                {
                    errChk(CallCtrlCallback (progressBarInfo->panel, progressBarInfo->control,
                        EVENT_PROGRESSBAR_MILESTONE_REACHED, (int)progressBarInfo->milestoneIndex + 1, 0,
                        NULL));
                    progressBarInfo->eventSent = TRUE;
                }
                increment = Max(0,milestone.percentMarker-percentage);
            }
        }
        else
        {
            increment = (100.0 * TIMER_INCREMENT) / progressBarInfo->totalTime.avgTime;
            if (percentage + increment > 100.0)
            {
                if (!progressBarInfo->eventSent)
                {
                    errChk(CallCtrlCallback (progressBarInfo->panel, progressBarInfo->control,
                        EVENT_PROGRESSBAR_MILESTONE_REACHED, 0, 0, NULL));
                    progressBarInfo->eventSent = TRUE;
                }
                increment = Max(0,100.0-percentage);
            }
        }

        if (increment > 0.0)
        {
            percentage += increment;
            errChk(SetCtrlVal (progressBarInfo->panel, progressBarInfo->control,
                progressBarInfo->flags & kReverseFlagMask ? 100.0 - percentage : percentage));
        
            progressBarInfo->percentage = percentage;
            ITaskbarList4SetPercentage (progressBarInfo, progressBarInfo->percentage);
        }
    }


Error:
    UNLOCK;
    return 0;
}

/// REGION START Window 7 Taskbar Button progress bar
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)            
static int GetParentHwnd (int panel, intptr_t *hwnd)
{
    int parent, panelHasTaskbarButton, cvirteHasButton, error = UIENoError;
    intptr_t tempHwnd;
    
    errChk (GetPanelAttribute (panel, ATTR_PANEL_PARENT, &parent));
    if (parent) 
    {
        errChk (GetParentHwnd (parent, hwnd));
    }
    else 
    {
        errChk (GetPanelAttribute (panel, ATTR_HAS_TASKBAR_BUTTON, &panelHasTaskbarButton));
        errChk (GetPanelAttribute (panel, ATTR_SYSTEM_WINDOW_HANDLE, &tempHwnd));
        errChk (GetSystemAttribute (ATTR_TASKBAR_BUTTON_VISIBLE, &cvirteHasButton));
        if (panelHasTaskbarButton) 
            *hwnd = tempHwnd;
        else if (cvirteHasButton)
            *hwnd = (intptr_t)GetWindow ((HWND)tempHwnd, GW_OWNER); // get the cvirte hwnd, which owns panels without taskbar buttons
        else
            *hwnd = 0;
    }
    
Error:
    return error;
}

static int CVICALLBACK SearchForExistingPBHwnd (void *item1, void *item2)
{
    HWND hwndToFind = *(HWND *)item1;
    ProgressBarInfo listItem = *(ProgressBarInfo *)item2;
    
    if (listItem->taskbarPBInfo->hwnd == hwndToFind)
        return 0;

    return 1;
}
#endif // mswin

static int InitializeITaskbarList4 (ProgressBarInfo progressBarInfo)
{
    int error = UIENoError;
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)
#if _MSC_VER < 1900
	OSVERSIONINFO osversion = {sizeof (OSVERSIONINFO)};
#endif
    size_t idx;
    TaskbarPBInfo taskbarPBInfo = NULL;
    ProgressBarInfo tempPBInfo;
    HRESULT hr = S_OK;
    GUID clsid = {0x56FDF344, 0xFD6D, 
                  0X11D0, 
                  0x95, 0x8A, 
                  0x00, 0x60, 0x97, 0xC9, 0xA0, 0x90};

    /* Check the version of the OS - ensure Windows 7 or later */
#if _MSC_VER < 1900
	GetVersionEx (&osversion);
	if ((osversion.dwMajorVersion < 6) || ((osversion.dwMajorVersion == 6) && (osversion.dwMinorVersion < 1)))
#else
    if (!IsWindows7OrGreater ())
#endif
        return UIENoError;
    
    nullChk (taskbarPBInfo = calloc (1, sizeof (*taskbarPBInfo)));
    errChk (GetParentHwnd (progressBarInfo->panel, (intptr_t *)&taskbarPBInfo->hwnd));
    if (!taskbarPBInfo->hwnd)
    {
        /* if we were unable to get a parent HWND, fail silently */
        free (taskbarPBInfo);
        return UIENoError;
    }
    /* Check if a taskbar progress bar is already associated with this hwnd.
       If so, return an error */
    if ((pbHwndList != 0) && ((idx = ListFindItem (pbHwndList, &taskbarPBInfo->hwnd, FRONT_OF_LIST, SearchForExistingPBHwnd)) != 0))
    {
        /* free the temporary progress bar info structure, we never need it again in here */
        free (taskbarPBInfo);
        ListGetItem (pbHwndList, &tempPBInfo, idx);
        /* Don't return an error if the taskbar progress bar owner is this progress bar */
        if (tempPBInfo != progressBarInfo)
        {
            errChk (UIEBadAttributeValue);
        }
        else
        {
            return UIENoError;
        }
    }
    else
    {
        if (pbHwndList == 0)
            nullChk (pbHwndList = ListCreate (sizeof (ProgressBarInfo)));
		nullChk(ListInsertItem (pbHwndList, &progressBarInfo, END_OF_LIST));
    }

    hr = CA_CreateObjectByClassIdEx (&clsid, NULL, &IID_ITaskbarList4, 0, LOCALE_NEUTRAL, 0, &taskbarPBInfo->TaskbarList);
    if (FAILED (hr))
        errChk (E_CVIAUTO_SERVER_INITIALIZATION);
    hr = CA_GetInterfaceFromObjHandle (taskbarPBInfo->TaskbarList, &IID_ITaskbarList4, 0, &taskbarPBInfo->ITaskbarList4, &taskbarPBInfo->addedRef);
    if (FAILED (hr))
        errChk (E_CVIAUTO_SERVER_INITIALIZATION);

    progressBarInfo->taskbarPBInfo = taskbarPBInfo;
    ITaskbarList4SetState (progressBarInfo);
    
Error:
    // if we couldn't obtain the COM object, just pretend like nothing ever happened...
    if (error == E_CVIAUTO_SERVER_INITIALIZATION && taskbarPBInfo)
    {
        free (taskbarPBInfo);
        progressBarInfo->taskbarPBInfo = NULL;
        error = UIENoError;
    }
#endif // mswin
    return error;
}

static void ITaskbarList4SetPercentage (ProgressBarInfo progressBarInfo, double percentage)
{
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)
    TaskbarPBInfo taskbarPBInfo = progressBarInfo->taskbarPBInfo;
    unsigned long long total = 1000000;
    unsigned long long done;
    
    if (!taskbarPBInfo)
        return;
    
    done = (double)total * (percentage / 100.0);
    if (progressBarInfo->mode != VAL_PROGRESSBAR_MARQUEE_MODE ||
        (progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE && progressBarInfo->sessionState != PROGRESSBAR_STATE_RUNNING))
        ITaskbarList4_SetProgressValue (taskbarPBInfo->ITaskbarList4, taskbarPBInfo->hwnd, done, total);
#endif // mswin
}

static void ITaskbarList4SetState (ProgressBarInfo progressBarInfo)
{
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)
    TaskbarPBInfo taskbarPBInfo = progressBarInfo->taskbarPBInfo;
    TBPFLAG tbpFlag = PROGRESSBAR_STATE_STOPPED;
    
    if (!taskbarPBInfo)
        return;
    
    switch (progressBarInfo->sessionState)
    {
        case PROGRESSBAR_STATE_RUNNING:
            if (progressBarInfo->mode == VAL_PROGRESSBAR_MARQUEE_MODE)
                tbpFlag = TBPF_INDETERMINATE;
            else
                tbpFlag = TBPF_NORMAL;
            break;
        case PROGRESSBAR_STATE_PAUSED:
            tbpFlag = TBPF_PAUSED;
            break;
        case PROGRESSBAR_STATE_STOPPED:
			tbpFlag = TBPF_NOPROGRESS;
            break;
        case PROGRESSBAR_STATE_ABORTED:
            tbpFlag = TBPF_ERROR;
			ITaskbarList4SetPercentage(progressBarInfo, progressBarInfo->percentage);
            break;
        default:
            assert (0);
    }
    
    ITaskbarList4_SetProgressState (taskbarPBInfo->ITaskbarList4, taskbarPBInfo->hwnd, tbpFlag);
#endif // mswin
}

static void DisposeITaskbarList4 (ProgressBarInfo progressBarInfo)
{
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)
    TaskbarPBInfo taskbarPBInfo;
    ProgressBarInfo tempPBInfo;
    size_t idx, numItems;
    
    assert (progressBarInfo);
    taskbarPBInfo = progressBarInfo->taskbarPBInfo;
    
    if (taskbarPBInfo)
    {
        progressBarInfo->sessionState = PROGRESSBAR_STATE_STOPPED;
        ITaskbarList4SetState (progressBarInfo);
        if (pbHwndList != 0)
        {
            idx = ListFindItem (pbHwndList, &taskbarPBInfo->hwnd, FRONT_OF_LIST, SearchForExistingPBHwnd);
            if (idx != 0)
            {
                ListGetItem (pbHwndList, &tempPBInfo, idx);
                if (tempPBInfo == progressBarInfo)
                    ListRemoveItem (pbHwndList, 0, idx);
                numItems = ListNumItems (pbHwndList);
                if (numItems == 0)
                {
                    ListDispose (pbHwndList);
                    pbHwndList = 0;
                }
            }
        }
        if (taskbarPBInfo->addedRef)
            ITaskbarList4_Release (taskbarPBInfo->ITaskbarList4);
        if (taskbarPBInfo->TaskbarList)
            CA_DiscardObjHandle (taskbarPBInfo->TaskbarList);
        free (taskbarPBInfo);
        progressBarInfo->taskbarPBInfo = NULL;
    }
#endif // mswin
}

static int IsProgressBarSyncedWithTaskbar (ProgressBarInfo progressBarInfo)
{
#if (defined (_NI_mswin32_) && _NI_mswin32_) || (defined (_NI_mswin64_) && _NI_mswin64_)
    return progressBarInfo->taskbarPBInfo ? 1 : 0;
#else
    return 0;
#endif // mswin
}
/// REGION END
