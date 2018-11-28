/*============================================================================*/
/*                        L a b W i n d o w s / C V I                         */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 2009-2017.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:       progressbar.h                                                 */
/* Purpose:     Implements a progress bar control                             */
/*                                                                            */
/*============================================================================*/


#ifndef PROGRESSBAR_CTRL_HEADER
#define PROGRESSBAR_CTRL_HEADER

#include <cvidef.h>
#include <userint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ATTR_PROGRESSBAR_UPDATE_MODE		1	// Update Mode
#define ATTR_PROGRESSBAR_BAR_COLOR			2	// Color
#define ATTR_PROGRESSBAR_BAR_ABORT_COLOR	3	// Abort Color
#define ATTR_PROGRESSBAR_REVERSE_DIRECTION	4	// Reverse Direction
#define ATTR_PROGRESSBAR_AUTO_ADJUST		5	// Auto Adjust
#define ATTR_PROGRESSBAR_ADJUSTMENT_TYPE	6	// Adjustment Type
#define ATTR_PROGRESSBAR_MARQUEE_SPEED		7	// Marquee Speed
#define ATTR_PROGRESSBAR_SYNC_TO_TASKBAR    8   // Show Windows 7 taskbar button progress bar

#define EVENT_PROGRESSBAR_MILESTONE_REACHED	3500	// reached milestone when auto-advancing

#define VAL_PROGRESSBAR_MANUAL_MODE			1	// manual update mode
#define VAL_PROGRESSBAR_AUTO_MODE			2	// auto update mode
#define VAL_PROGRESSBAR_MARQUEE_MODE		3	// marquee update mode

#define VAL_PROGRESSBAR_ADJUST_POSITION		1	// auto adjust milestone position
#define VAL_PROGRESSBAR_ADJUST_RATE			2	// auto adjust milestone auto-advance rate


int CVIFUNC		ProgressBar_Create (int panel, const char *label, int top, int left, int vertical);
int CVIFUNC		ProgressBar_ConvertFromSlide (int panel, int slideCtrl);
int CVIFUNC		ProgressBar_Revert (int panel, int progressBarCtrl);
int CVIFUNC_C	ProgressBar_SetAttribute (int panel, int progressBarCtrl, int attribute, ...);
int CVIFUNC		ProgressBar_GetAttribute (int panel, int progressBarCtrl, int attribute, void *value);
int CVIFUNC		ProgressBar_SetPercentage (int panel, int progressBarCtrl, double percentage,
					char *label);
int CVIFUNC		ProgressBar_GetPercentage (int panel, int progressBarCtrl, double *percentage);
int CVIFUNC		ProgressBar_SetTotalTimeEstimate (int panel, int progressBarCtrl, double expectedTime);
int CVIFUNC		ProgressBar_GetTotalTimeEstimate (int panel, int progressBarCtrl, double *expectedTime);

int CVIFUNC		ProgressBar_Start (int panel, int progressBarCtrl, char *label);
int CVIFUNC		ProgressBar_End (int panel, int progressBarCtrl, double *totalTime, char *label);
int CVIFUNC		ProgressBar_Abort (int panel, int progressBarCtrl, int fillToEnd, char *label);
int CVIFUNC		ProgressBar_Pause (int panel, int progressBarCtrl, char *label);
int CVIFUNC		ProgressBar_Resume (int panel, int progressBarCtrl, char *label);

int CVIFUNC_C	ProgressBar_SetMilestones (int panel, int progressBarCtrl, ...);
int CVIFUNC		ProgressBar_AddMilestone (int panel, int progressBarCtrl, double percentage);
int CVIFUNC		ProgressBar_LoadMilestones (int panel, int progressBarCtrl, char *dataFile,
					int includeTimeData);
int CVIFUNC		ProgressBar_SaveMilestones (int panel, int progressBarCtrl, char *dataFile,
					int includeTimeData);
int CVIFUNC		ProgressBar_ClearMilestones (int panel, int progressBarCtrl);
int CVIFUNC		ProgressBar_GetNumMilestones (int panel, int progressBarCtrl, size_t *numMilestones);
int CVIFUNC		ProgressBar_GetMilestone (int panel, int progressBarCtrl, size_t milestoneIndex,
					double *percentage);
int CVIFUNC		ProgressBar_GetCurrentMilestoneIndex (int panel, int progressBarCtrl,
					size_t *milestoneIndex);
int CVIFUNC 	ProgressBar_AdvanceMilestone (int panel, int progressBarCtrl, char *label);

#ifdef __cplusplus
}
#endif

#endif // PROGRESSBAR_CTRL_HEADER
