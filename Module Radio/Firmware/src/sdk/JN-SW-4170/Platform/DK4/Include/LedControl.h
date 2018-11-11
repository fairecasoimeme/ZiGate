/*****************************************************************************
 *
 * MODULE:              Demo board LED controls
 *
 * COMPONENT:           $RCSfile: LedControl.h,v $
 *
 * VERSION:             $Name: JN514x_SDK_V0002_RC0 $
 *
 * REVISION:            $Revision: 1.5 $
 *
 * DATED:               $Date: 2008/10/22 12:28:15 $
 *
 * STATUS:              $State: Exp $
 *
 * AUTHOR:              CJG
 *
 * DESCRIPTION:
 * Macros to make it easier to drive LEDs on demo boards
 *
 * LAST MODIFIED BY:    $Author: pjtw $
 *                      $Modtime: $
 *
 ****************************************************************************
 *
 * This software is owned by Jennic and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on Jennic products. You, and any third parties must reproduce
 * the copyright and warranty notice and any other legend of ownership on
 * each copy or partial copy of the software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
 * ACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,
 * BE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.
 *
 * Copyright Jennic Ltd 2009. All rights reserved
 *
 ***************************************************************************/

#ifndef LED_CONTROL_INCLUDED
#define LED_CONTROL_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "AppHardwareApi.h"
#include "PlatformDIOAssignments.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#if (defined LED_CTRL_CARRIER_BOARD)

#define LED_CTRL_BASE_BIT PIN_LED_BASE_BIT
#define LED_CTRL_MASK_RFD ((1UL << PIN_LED_NUMBER) - 1)
#define LED_CTRL_MASK_FFD ((1UL << PIN_LED_NUMBER_FFD) - 1)

#define LED_CARRIER_D6 0
#define LED_CARRIER_D3 1

#define vLedInitRfd() \
            vAHI_DioSetDirection(0, (LED_CTRL_MASK_RFD << LED_CTRL_BASE_BIT))
#define vLedInitFfd() \
            vAHI_DioSetDirection(0, (LED_CTRL_MASK_FFD << LED_CTRL_BASE_BIT))
#define vLedControl(LED,ON) \
            vAHI_DioSetOutput((ON) ? 0 : (1 << (LED_CTRL_BASE_BIT + LED)), \
                              (ON) ? (1 << (LED_CTRL_BASE_BIT + LED)) : 0)


#else

#define LED_S0_BIT            (16)
#define LED_S1_BIT            (13)
#define LED_S2_BIT            (0)

#define LED_C3_BIT            (3)
#define LED_C6_BIT            (2)

#define LED_S0_PIN            (1UL << LED_S0_BIT)
#define LED_S0_VAL            (0) 
#define LED_S1_PIN            (1UL << LED_S1_BIT)
#define LED_S1_VAL            (1) 
#define LED_S2_PIN            (1UL << LED_S2_BIT)
#define LED_S2_VAL            (2)

#define LED_C6_PIN            (1UL << LED_C6_BIT)
#define LED_C6_VAL            (4) 
#define LED_C3_PIN            (1UL << LED_C3_BIT)
#define LED_C3_VAL            (5)

#define LED_GENERIC_D1        LED_S0_VAL
#define LED_GENERIC_D2        LED_S1_VAL
#define LED_GENERIC_D3        LED_S2_VAL

#define LED_CARRIER_D6        LED_C6_VAL
#define LED_CARRIER_D3        LED_C3_VAL

#define LED_CTRL_MASK_RFD     (LED_C3_PIN | LED_C6_PIN)
#define LED_CTRL_MASK_FFD     (LED_S0_PIN | LED_S1_PIN | LED_S2_PIN | LED_C3_PIN | LED_C6_PIN)

PUBLIC void vLedControl(uint8 LED, uint8 ON);
							  				
#define vLedInitFfd() \
            vAHI_DioSetDirection(0, LED_CTRL_MASK_FFD)

#define vLedInitRfd() \
            vAHI_DioSetDirection(0, LED_CTRL_MASK_RFD)
#endif
							  
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* LED_CONTROL_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

