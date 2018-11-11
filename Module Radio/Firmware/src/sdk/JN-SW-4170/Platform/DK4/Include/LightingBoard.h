/*****************************************************************************
 *
 * MODULE:             Lighting Expansion Board
 *
 * COMPONENT:          RGB_LED.h
 *
 * VERSION:            R and D Release 25 OCT 2012
 *
 * REVISION:           1.0
 *
 * DATED:              2011/01/07
 *
 * AUTHOR:             dclar
 *
 * DESCRIPTION:
 * Header file functions for RGB LED on Lighting Expansion Board
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

#ifndef  LIGHTING_BOARD_INCLUDED
#define  LIGHTING_BOARD_INCLUDED

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

// DIO line values



/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC bool_t bRGB_LED_Enable(void);
PUBLIC bool_t bRGB_LED_Disable(void);
PUBLIC bool_t bRGB_LED_SetLevel(uint8 u8RedLevel, uint8 u8GreenLevel, uint8 u8BlueLevel);
PUBLIC bool_t bRGB_LED_On(void);
PUBLIC bool_t bRGB_LED_Off(void);
PUBLIC bool_t bWhite_LED_Enable(void);
PUBLIC bool_t bWhite_LED_Disable(void);
PUBLIC bool_t bWhite_LED_SetLevel(uint8 u8BrightnessLevel);
PUBLIC bool_t bWhite_LED_On(void);
PUBLIC bool_t bWhite_LED_Off(void);
PUBLIC bool_t bRGB_LED_SetGroupLevel(uint8 u8Level);


/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/


#if defined __cplusplus
}
#endif

#endif  /* LCD_DRIVER_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

