/*****************************************************************************
 *
 * MODULE:             ZTimer
 *
 * COMPONENT:          ZTimer.h
 *
 * DESCRIPTION:        Zigbee Timer Module
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright NXP B.V. 2016. All rights reserved
 *
 ***************************************************************************/

#ifndef ZTIMER_H_
#define ZTIMER_H_

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define ZTIMER_TIME_SEC(v) ((uint32)(v) * 1000UL)
#define ZTIMER_TIME_MSEC(v) ((uint32)(v) * 1UL)

/* Flags for timer configuration */
#define ZTIMER_FLAG_ALLOW_SLEEP     0
#define ZTIMER_FLAG_PREVENT_SLEEP   (1 << 0)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef enum
{
    E_ZTIMER_STATE_CLOSED,
    E_ZTIMER_STATE_STOPPED,
    E_ZTIMER_STATE_RUNNING,
    E_ZTIMER_STATE_EXPIRED,    
} ZTIMER_teState;

typedef void (*ZTIMER_tpfCallback)(void *pvParam);

typedef struct
{
    uint8               u8Flags;
    ZTIMER_teState      eState;
    uint32                u32Time;
    void                *pvParameters;
    ZTIMER_tpfCallback    pfCallback;
} ZTIMER_tsTimer;

typedef enum
{
    E_ZTIMER_OK,
    E_ZTIMER_FAIL
} ZTIMER_teStatus;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC ZTIMER_teStatus ZTIMER_eInit(ZTIMER_tsTimer *psTimers, uint8 u8NumTimers);
#if (JENNIC_CHIP_FAMILY == JN516x)
PUBLIC void ISR_vTickTimer(void);
#else
PUBLIC void ZTIMER_vAhiCallback ( uint32 u32Device, uint32 u32ItemBitmap);
#endif
PUBLIC void ZTIMER_vSleep(void);
PUBLIC void ZTIMER_vWake(void);
PUBLIC void ZTIMER_vTask(void);
PUBLIC ZTIMER_teStatus ZTIMER_eOpen(uint8 *pu8TimerIndex, ZTIMER_tpfCallback pfCallback, void *pvParams, uint8 u8Flags);
PUBLIC ZTIMER_teStatus ZTIMER_eClose(uint8 u8TimerIndex);
PUBLIC ZTIMER_teStatus ZTIMER_eStart(uint8 u8TimerIndex, uint32 u32Time);
PUBLIC ZTIMER_teStatus ZTIMER_eStop(uint8 u8TimerIndex);
PUBLIC ZTIMER_teState ZTIMER_eGetState(uint8 u8TimerIndex);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#endif /*ZTIMER_H_*/
