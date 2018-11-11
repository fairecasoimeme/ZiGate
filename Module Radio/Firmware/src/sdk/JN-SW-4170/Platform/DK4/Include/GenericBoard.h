/*****************************************************************************
 *
 * MODULE:             Generic Expansion Board
 *
 * COMPONENT:          GenericBoard.h
 *
 * VERSION:            
 *
 * REVISION:           1.0
 *
 * DATED:              2012/10/29
 *
 * AUTHOR:             dclar
 *
 * DESCRIPTION:
 * Header file exposing api for peripherals on the generic expansion board
 *
 * LAST MODIFIED BY:    $Author: SBARF $
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
 * Copyright Jennic Ltd 2011. All rights reserved
 *
 ***************************************************************************/

#ifndef  GENERIC_BOARD_INCLUDED
#define  GENERIC_BOARD_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include "jendefs.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/*Switches*/
#define GEN_BOARD_BUTTON_S1_VAL       (1)
#define GEN_BOARD_BUTTON_S2_VAL       (2)
#define GEN_BOARD_BUTTON_S3_VAL       (4)
#define GEN_BOARD_BUTTON_S4_VAL       (8)

/*LEDs*/
#define GEN_BOARD_LED_D1_VAL          (1)
#define GEN_BOARD_LED_D2_VAL          (2)
#define GEN_BOARD_LED_D3_VAL          (4) 
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC bool_t bPotEnable(void);
PUBLIC uint16 u16ReadPotValue(void);
PUBLIC bool_t bPotDisable(void);
PUBLIC void vGenericButtonInit(void);
PUBLIC uint8 u8GenericButtonRead(void);
void vGenericLEDInit(void);
PUBLIC void vGenericLEDSetOutput(uint8 u8LEDBitmap, bool_t bOn);
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* GENERIC_BOARD_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

