/*****************************************************************************
 *
 * MODULE:             Driver for LCD
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

#define LCD_SS           (1)            // chip select is same as slave select
#define LCD_SS_MASK      (1 << LCD_SS)  // ie dio0 is slave select 1 etc

#if (defined JENNIC_CHIP_FAMILY_JN514x) || (defined JENNIC_CHIP_FAMILY_JN516x)
#define LCD_RS_BIT_MASK    (1 << 15)      // rs (command or data) line  (AO on ST7565P)
#define LCD_RES_BIT_MASK   (1 << 13)      // reset line
#define LCD_TYPE_MASK      (1 << 14)      // type detect line
#define LCD_BACKLIGHT_MASK (1 << 16)      // backlight control line 
#else
#define LCD_RS_BIT_MASK    (1 << 2)       // rs (command or data) line  (AO on ST7565P)
#define LCD_RES_BIT_MASK   (1 << 14)      // reset line
#define LCD_TYPE_MASK      (1 << 3)       // type detect line
#define LCD_BACKLIGHT_MASK (1 << 8)       // backlight control line 
#endif


#define LCD_SHADOW_BUFFER_LOCATION(x,y) ((x * 128) + y)


/*LCD Expansion Board Values*/
#define LCD_BOARD_BUTTON_S1_VAL       (1)
#define LCD_BOARD_BUTTON_S2_VAL       (2)
#define LCD_BOARD_BUTTON_S3_VAL       (4)
#define LCD_BOARD_BUTTON_S4_VAL       (8)
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef struct
{

    uint8 *pu8Bitmap;
    uint8 u8Width;  /* Width in pixels (y in example above) */
    uint8 u8Height; /* Height in character rows (2 in example above) */

} tsBitmap;


// enumeration for ST7565P
#define CMD_SET_DISP_START_LINE  0x40
#define CMD_SET_PAGE             0xB0

#define CMD_SET_COLUMN_UPPER    0x10
#define CMD_SET_COLUMN_LOWER    0x00

#define CMD_SET_ADC_NORMAL      0xA0
#define CMD_SET_ADC_REVERSE     0xA1
#define CMD_SET_BIAS_9          0xA2
#define CMD_SET_BIAS_7          0xA3
#define CMD_SET_ALLPTS_NORMAL   0xA4
#define CMD_SET_ALLPTS_ON       0xA5
#define CMD_SET_DISP_NORMAL     0xA6
#define CMD_SET_DISP_REVERSE    0xA7
#define CMD_SET_STATIC_OFF      0xAC
#define CMD_SET_STATIC_ON       0xAD
#define CMD_DISPLAY_OFF         0xAE
#define CMD_DISPLAY_ON          0xAF

#define CMD_RMW                 0xE0
#define CMD_END                 0xEE
#define CMD_INTERNAL_RESET      0xE2
#define CMD_NOP                 0xE3

#define CMD_SET_BOOSTER_FIRST   0xF8

#define CMD_SET_COM_NORMAL      0xC0
#define CMD_SET_COM_REVERSE     0xC8
#define CMD_SET_RESISTOR_RATIO  0x20
#define CMD_SET_POWER_CONTROL   0x28

#define CMD_SET_VOLUME_FIRST    0x81


// enumeration for LH155. command table p.23
typedef enum
{
    LCD_COMMAND_DISPLAY_DATA_WRITE,
    LCD_COMMAND_DISPLAY_DATA_READ,
    LCD_COMMAND_X_ADDRESS_SET,
    LCD_COMMAND_Y_ADDRESS_SET_LO,
    LCD_COMMAND_Y_ADDRESS_SET_HI,
    LCD_COMMAND_DISPLAY_START_LO,
    LCD_COMMAND_DISPLAY_START_HI,
    LCD_COMMAND_DISPLAY_CONTROL_1_SET,
    LCD_COMMAND_DISPLAY_CONTROL_2_SET,
    LCD_COMMAND_INCREMENT_CONTROL_SET,
    LCD_COMMAND_POWER_CONTROL_1_SET,
    LCD_COMMAND_POWER_CONTROL_2_SET,
    LCD_COMMAND_POWER_CONTROL_3_SET,
} tLCD_Command;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void vLcdReset(uint8 u8Bias, uint8 u8Gain);
PUBLIC void vLcdResetDefault(void);
PUBLIC void vLcdBackLightEnable(uint8 u8Status);
PUBLIC void vLcdClear(void);
PUBLIC void vLcdRefreshAll(void);
PUBLIC void vLcdRefreshArea(uint8 u8LeftColumn, uint8 u8TopRow, uint8 u8Width, uint8 u8Height);

PUBLIC void vLcdWriteText(char *pcString, uint8 u8Row, uint8 u8Column);
PUBLIC void vLcdWriteInvertedText(char *pcString, uint8 u8Row, uint8 u8Column);
PUBLIC void vLcdWriteBitmap(tsBitmap *psBitmap, uint8 u8LeftColumn,
                            uint8 u8TopRow);

PUBLIC void vLcdGrabSpiBus(void);
PUBLIC void vLcdFreeSpiBus(void);

PUBLIC void vLcdPowerOff(void);
PUBLIC void vLcdPowerSavingMode(bool_t bSelectMode);

PUBLIC void vLcdButtonInit(void);
PUBLIC uint8 u8LcdButtonRead(void);

PUBLIC void vLcdContrastLevel(uint8 u8Gain);
PUBLIC uint8 u8LcdCalcContrastLevel(void);

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
