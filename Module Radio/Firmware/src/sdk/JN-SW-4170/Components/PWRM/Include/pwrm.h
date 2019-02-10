/*****************************************************************************
 *
 * MODULE:             Power Manager
 *
 * COMPONENT:          pwrm.h
 *
 * AUTHOR:             MRW
 *
 * DESCRIPTION:        Manage the microcontrollers power and transition between
 *                     the various power states
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Cortex/Modules/PWRM/Branches/ZBPRO_R20_v2.0_NoRTOS/Include/pwrm.h $
 *
 * $Revision: 86357 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2017-01-20 18:35:37 +0000 (Fri, 20 Jan 2017) $
 *
 * $Id: pwrm.h 86357 2017-01-20 18:35:37Z nxp29741 $
 *
 *****************************************************************************
 *
 * This software is owned by Jennic and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on Jennic products. You, and any third parties must reproduce
 * the copyright and warranty notice and any other legend of ownership on each
 * copy or partial copy of the software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
 * ACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,
 * BE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.
 *
 * Copyright Jennic Ltd. 2008 All rights reserved
 *
 ****************************************************************************/

#ifndef PWRM_H_
#define PWRM_H_

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#if (defined JENNIC_CHIP_FAMILY_JN516x) || (defined JENNIC_CHIP_FAMILY_JN517x)
#include <AppHardwareApi.h>
#else
//#include "PWR_interface.h"
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#ifndef PWRM_INLINE
#define PWRM_INLINE INLINE
#endif

#ifndef PWRM_ALWAYS_INLINE
#define PWRM_ALWAYS_INLINE ALWAYS_INLINE
#endif
#if (defined JENNIC_CHIP_FAMILY_JN516x) || (defined JENNIC_CHIP_FAMILY_JN517x)
#if (JENNIC_CHIP_FAMILY == PC)
#undef PWRM_ALWAYS_INLINE /* stop inlining  for unit tests */
#define PWRM_ALWAYS_INLINE
#endif

#define PWRM_CALLBACK(name) void pwrm_##name(void)

#define PWRM_DECLARE_CALLBACK_DESCRIPTOR(name) \
    PWRM_CALLBACK(name); \
    pwrm_tsCallbackDescriptor pwrm_##name##_desc = { NULL, pwrm_##name }

#define PWRM_vRegisterWakeupCallback(name) pwrm_vRegisterWakeupCallback(&pwrm_##name##_desc)
#define PWRM_vRegisterPreSleepCallback(name) pwrm_vRegisterPreSleepCallback(&pwrm_##name##_desc)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef struct _pwrm_tsCallbackDescriptor {
    struct _pwrm_tsCallbackDescriptor *psNext;
    void (*prCallback)(void);
} pwrm_tsCallbackDescriptor;

typedef struct _sWakeTimerEvent {
    struct _sWakeTimerEvent  *psNext;
    uint32 u32TickDelta;
    void (*prCallbackfn)(void);
    uint8 u8Status;
} pwrm_tsWakeTimerEvent;

typedef enum {
    PWRM_E_OK,
    PWRM_E_ACTIVITY_OVERFLOW,
    PWRM_E_ACTIVITY_UNDERFLOW,
    PWRM_E_TIMER_RUNNING,
    PWRM_E_TIMER_FREE,
    PWRM_E_TIMER_INVALID
} PWRM_teStatus;

typedef teAHI_SleepMode PWRM_tePowerMode;

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC void PWRM_vInit(PWRM_tePowerMode ePowerMode);
#ifndef  PATCH_ENABLE
PUBLIC void PWRM_vManagePower(void);
#endif
PUBLIC PWRM_teStatus PWRM_eScheduleActivity(
        pwrm_tsWakeTimerEvent *psWake,
        uint32 u32Ticks,
        void (*prCallbackfn)(void));
PUBLIC void PWRM_vWakeInterruptCallback(void);
#if (JENNIC_CHIP_FAMILY == JN514x)
PUBLIC void PWRM_vSetupDozeMonitor(bool_t bUseIO, bool_t bUseTimers, bool_t b32uSec);
PUBLIC void PWRM_vResetDozeTimers(void);
PUBLIC uint32 PWRM_u32GetDozeTime(void);
PUBLIC uint32 PWRM_u32GetDozeElapsedTime(void);
#endif

#if (JENNIC_CHIP_FAMILY == JN516x)
// lpsw3603: No timers on a '68, only IO
PUBLIC void PWRM_vSetupDozeMonitor(bool_t bUseIO);
#endif

PUBLIC void vAppMain(void);
PUBLIC void vAppRegisterPWRMCallbacks(void);

/****************************************************************************/
/***        Inline Functions                                              ***/
/****************************************************************************/

PWRM_INLINE PWRM_teStatus PWRM_eStartActivity(void) PWRM_ALWAYS_INLINE;
PWRM_INLINE PWRM_teStatus PWRM_eStartActivity(void) /* [I SP001262_fr 119] */
{
    /* [I SP001262_fr 120, 121, 122] */
    extern volatile uint16 s_u16ActivityCounter;
    return (0xffff != s_u16ActivityCounter) ? (s_u16ActivityCounter++, PWRM_E_OK) : PWRM_E_ACTIVITY_OVERFLOW;
}

PWRM_INLINE PWRM_teStatus PWRM_eFinishActivity(void) PWRM_ALWAYS_INLINE;
PWRM_INLINE PWRM_teStatus PWRM_eFinishActivity(void) /* [I SP001262_fr 123] */
{
    /* [I SP001262_fr 124, 125, 126] */
    extern volatile uint16 s_u16ActivityCounter;
    return (0 != s_u16ActivityCounter) ? ( s_u16ActivityCounter--, PWRM_E_OK) : PWRM_E_ACTIVITY_UNDERFLOW;
}

PWRM_INLINE uint16 PWRM_u16GetActivityCount(void) PWRM_ALWAYS_INLINE;
PWRM_INLINE uint16 PWRM_u16GetActivityCount(void) /* [I SP001262_fr 166] */
{
    extern volatile uint16 s_u16ActivityCounter;
    return s_u16ActivityCounter; /* [I SP001262_fr 167] */
}

#if (JENNIC_CHIP_FAMILY == JN513x)
PWRM_INLINE void PWRM_vTickTimerActivated(void) PWRM_ALWAYS_INLINE;
PWRM_INLINE void PWRM_vTickTimerActivated(void)
{
    extern volatile bool_t s_bTickTimerActive;
    s_bTickTimerActive = TRUE;  /* [I SP001262_fr 153] */
}

PWRM_INLINE void PWRM_vTickTimerDeactivated(void) PWRM_ALWAYS_INLINE;
PWRM_INLINE void PWRM_vTickTimerDeactivated(void)
{
    extern volatile bool_t s_bTickTimerActive;
    s_bTickTimerActive = FALSE; /* [I SP001262_fr 155] */
}
#endif

/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/

PUBLIC void pwrm_vRegisterWakeupCallback(pwrm_tsCallbackDescriptor *psCBDesc );
PUBLIC void pwrm_vRegisterPreSleepCallback(pwrm_tsCallbackDescriptor *psCBDesc );
#else

typedef enum {
    PWRM_E_OK
} PWRM_teStatus;

typedef uint8 PWRM_tePowerMode;

PWRM_INLINE void PWRM_vInit(PWRM_tePowerMode ePowerMode) PWRM_ALWAYS_INLINE;
PWRM_INLINE void PWRM_vInit(PWRM_tePowerMode ePowerMode) 
{
    //PWR_Init();
    //PWR_ChangeDeepSleepMode (ePowerMode);
}

PWRM_INLINE PWRM_teStatus PWRM_eStartActivity(void) PWRM_ALWAYS_INLINE;
PWRM_INLINE PWRM_teStatus PWRM_eStartActivity(void) 
{
    //PWR_DisallowDeviceToSleep();
    return PWRM_E_OK;
}

PWRM_INLINE PWRM_teStatus PWRM_eFinishActivity(void) PWRM_ALWAYS_INLINE;
PWRM_INLINE PWRM_teStatus PWRM_eFinishActivity(void) 
{
    //PWR_AllowDeviceToSleep();
    return PWRM_E_OK;
}

PWRM_INLINE uint16 PWRM_u16GetActivityCount(void) PWRM_ALWAYS_INLINE;
PWRM_INLINE uint16 PWRM_u16GetActivityCount(void) 
{
    return /*PWR_CheckIfDeviceCanGoToSleep()? 1 :*/ 0; 
}

PWRM_INLINE void PWRM_vManagePower(void) PWRM_ALWAYS_INLINE;
PWRM_INLINE void PWRM_vManagePower(void) 
{
  /*  if (PWR_CheckIfDeviceCanGoToSleep())
    {
        PWR_EnterLowPower();
    }*/
}

#endif
#endif /*PWRMAN_H_*/

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
