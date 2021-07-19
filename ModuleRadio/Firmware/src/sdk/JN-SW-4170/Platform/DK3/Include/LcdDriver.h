/*****************************************************************************
 *
 * MODULE:             Driver for Sharp LH155BA LCD
 *
 * COMPONENT:          LcdDriver.h
 *
 * VERSION:            R and D Release 6 JAN 2011
 *
 * REVISION:           1.0
 *
 * DATED:              2011/01/07
 *
 * AUTHOR:             sbarf
 *
 * DESCRIPTION:
 * Header file exposing LH155 driver functions
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

#ifndef  LCD_DRIVER_INCLUDED
#define  LCD_DRIVER_INCLUDED

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

#define LCD_SS           (1) 			// chip select is same as slave select
#define LCD_SS_MASK      (1 << LCD_SS)	// ie dio0 is slave select 1 etc

#define LCD_RS_BIT_MASK  (1 << 2)		// rs (command or data) line
#define LCD_RES_BIT_MASK (1 << 1)		// reset line

#define LCD_DIO13_ENABLE_MASK (1 << 13)	//
#define LCD_DIO15_ENABLE_MASK (1 << 15)
#define LCD_DIO17_ENABLE_MASK (1 << 17)

#define LCD_SHADOW_BUFFER_LOCATION(x,y) ((x * 128) + y)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef struct
{

    uint8 *pu8Bitmap;
    uint8 u8Width;  /* Width in pixels (y in example above) */
    uint8 u8Height; /* Height in character rows (2 in example above) */

} tsBitmap;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void vLcdReset(uint8 u8Bias, uint8 u8Gain);
PUBLIC void vLcdBackLightEnable(uint8 u8Status);
PUBLIC void vLcdSetDisplay (uint8 u8writedata, uint8 u8xcoord, uint8 u8ycoord);
PUBLIC void vLcdClear(void);
PUBLIC void vLcdRefreshAll(void);

PUBLIC void vLcdWriteText(char *pcString, uint8 u8Row, uint8 u8Column);
PUBLIC void vLcdWriteInvertedText(char *pcString, uint8 u8Row, uint8 u8Column);
PUBLIC void vLcdWriteBitmap(tsBitmap *psBitmap, uint8 u8LeftColumn,
                            uint8 u8TopRow);

PUBLIC void vLcdGrabSpiBus(void);
PUBLIC void vLcdFreeSpiBus(void);

PUBLIC void vLcdPowerOff(void);
PUBLIC void vLcdPowerSavingMode(bool_t bSelectMode);

PUBLIC void vLcdContrastLevel(uint8 u8Gain);
PUBLIC uint8 u8CalcContrastLevel(void);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
PUBLIC uint8 au8Shadow[1024] __attribute__ ((aligned (4)));

#if defined __cplusplus
}
#endif

#endif  /* LCD_DRIVER_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

