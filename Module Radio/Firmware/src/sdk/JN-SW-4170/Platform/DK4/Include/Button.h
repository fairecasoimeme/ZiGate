/*****************************************************************************
 *
 * MODULE:              Demo board button controls
 *
 * COMPONENT:           $RCSfile: Button.h,v $
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
 * Macros to make it easier to read buttons on demo boards
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

#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED

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
/* Two schemes have been defined: BUTTON_x_MASK is used with u8ButtonReadXfd 
   and is aligned so that button 0 is indicated by bit 0. The other buttons 
   are represented by bit offsets based on their relative DIO pins to button
   0, which varies between platforms. Meanwhile, BUTTON_x_PIN is a bitmask on 
   the DIO pin itself */
   
/* Only define buttons that exist, so attempts by application to use buttons
   that are not present will generate a build error */
#if PIN_BUTTON_NUMBER_FFD > 0
 #define BUTTON_0_MASK           (1UL)
 #define BUTTON_0_PIN            (1UL << PIN_BUTTON0_BIT)
#endif 
#if PIN_BUTTON_NUMBER_FFD > 1
 #define BUTTON_1_MASK           (1UL << (PIN_BUTTON1_BIT - PIN_BUTTON0_BIT))
 #define BUTTON_1_PIN            (1UL << PIN_BUTTON1_BIT)
#endif
#if PIN_BUTTON_NUMBER_FFD > 2
 #define BUTTON_2_MASK           (1UL << (PIN_BUTTON2_BIT - PIN_BUTTON0_BIT))
 #define BUTTON_2_PIN            (1UL << PIN_BUTTON2_BIT)
#endif
#if PIN_BUTTON_NUMBER_FFD > 3
 #define BUTTON_3_MASK           (1UL << (PIN_BUTTON3_BIT - PIN_BUTTON0_BIT))
 #define BUTTON_3_PIN            (1UL << PIN_BUTTON3_BIT)
#endif

#if PIN_BUTTON_NUMBER == 4
 #define BUTTON_ALL_MASK_RFD     (BUTTON_0_MASK | BUTTON_1_MASK | BUTTON_2_MASK | BUTTON_3_MASK)
 #define BUTTON_ALL_MASK_RFD_PIN (BUTTON_0_PIN | BUTTON_1_PIN | BUTTON_2_PIN | BUTTON_3_PIN)
#elif PIN_BUTTON_NUMBER == 3
 #define BUTTON_ALL_MASK_RFD     (BUTTON_0_MASK | BUTTON_1_MASK | BUTTON_2_MASK)
 #define BUTTON_ALL_MASK_RFD_PIN (BUTTON_0_PIN | BUTTON_1_PIN | BUTTON_2_PIN)
#elif PIN_BUTTON_NUMBER == 2
 #define BUTTON_ALL_MASK_RFD     (BUTTON_0_MASK | BUTTON_1_MASK)
 #define BUTTON_ALL_MASK_RFD_PIN (BUTTON_0_PIN | BUTTON_1_PIN)
#elif PIN_BUTTON_NUMBER == 1
 #define BUTTON_ALL_MASK_RFD     (BUTTON_0_MASK)
 #define BUTTON_ALL_MASK_RFD_PIN (BUTTON_0_PIN)
#endif

#if PIN_BUTTON_NUMBER_FFD == 4
 #define BUTTON_ALL_MASK_FFD     (BUTTON_0_MASK | BUTTON_1_MASK | BUTTON_2_MASK | BUTTON_3_MASK)
 #define BUTTON_ALL_MASK_FFD_PIN (BUTTON_0_PIN | BUTTON_1_PIN | BUTTON_2_PIN | BUTTON_3_PIN)
#elif PIN_BUTTON_NUMBER_FFD == 3
 #define BUTTON_ALL_MASK_FFD     (BUTTON_0_MASK | BUTTON_1_MASK | BUTTON_2_MASK)
 #define BUTTON_ALL_MASK_FFD_PIN (BUTTON_0_PIN | BUTTON_1_PIN | BUTTON_2_PIN)
#elif PIN_BUTTON_NUMBER_FFD == 2
 #define BUTTON_ALL_MASK_FFD     (BUTTON_0_MASK | BUTTON_1_MASK)
 #define BUTTON_ALL_MASK_FFD_PIN (BUTTON_0_PIN | BUTTON_1_PIN)
#elif PIN_BUTTON_NUMBER_FFD == 1
 #define BUTTON_ALL_MASK_FFD     (BUTTON_0_MASK)
 #define BUTTON_ALL_MASK_FFD_PIN (BUTTON_0_PIN)
#endif

#define BUTTON_BASE_BIT          (0)


#define vButtonInitRfd() \
            vAHI_DioSetDirection(BUTTON_ALL_MASK_RFD_PIN, 0)
#define vButtonInitFfd() \
            vAHI_DioSetDirection(BUTTON_ALL_MASK_FFD_PIN, 0)

			
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC uint8 u8ButtonReadRfd(void);
PUBLIC uint8 u8ButtonReadFfd(void);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* BUTTON_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

