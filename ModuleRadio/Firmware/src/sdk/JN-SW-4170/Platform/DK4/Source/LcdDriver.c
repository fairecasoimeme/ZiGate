/****************************************************************************
 *
 * MODULE:             Functions For LCD Expansion Board
 *
 * COMPONENT:          LcdDriver.c
 */
/****************************************************************************
*
* This software is owned by NXP B.V. and/or its supplier and is protected
* under applicable copyright laws. All rights are reserved. We grant You,
* and any third parties, a license to use this software solely and
* exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139].
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

* Copyright NXP B.V. 2012. All rights reserved
*
***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <string.h>
//#include "ST7565P.h"
#include "LcdDriver.h"
#include "LcdFont.h"
#include "AppHardwareApi.h"
#include "PeripheralRegs.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#if (defined JENNIC_CHIP_FAMILY_JN514x) || (defined JENNIC_CHIP_FAMILY_JN516x)
#define LCD_BOARD_BUTTON_S1_PIN_BIT        (11)
#define LCD_BOARD_BUTTON_S2_PIN_BIT        (12)
#define LCD_BOARD_BUTTON_S3_PIN_BIT        (17)
#define LCD_BOARD_BUTTON_S4_PIN_BIT        (1)
#else
#define LCD_BOARD_BUTTON_S1_PIN_BIT        (12)
#define LCD_BOARD_BUTTON_S2_PIN_BIT        (13)
#define LCD_BOARD_BUTTON_S3_PIN_BIT        (18)
#define LCD_BOARD_BUTTON_S4_PIN_BIT        (5)
#endif

#define LCD_BOARD_BUTTON_S1_PIN            (1UL << LCD_BOARD_BUTTON_S1_PIN_BIT)
#define LCD_BOARD_BUTTON_S2_PIN            (1UL << LCD_BOARD_BUTTON_S2_PIN_BIT)
#define LCD_BOARD_BUTTON_S3_PIN            (1UL << LCD_BOARD_BUTTON_S3_PIN_BIT)
#define LCD_BOARD_BUTTON_S4_PIN            (1UL << LCD_BOARD_BUTTON_S4_PIN_BIT)

#define LCD_BOARD_BUTTON_ALL_MASK_PIN (LCD_BOARD_BUTTON_S1_PIN | LCD_BOARD_BUTTON_S2_PIN | LCD_BOARD_BUTTON_S3_PIN | LCD_BOARD_BUTTON_S4_PIN)

#define CHIP_ID_REG (0x020010FC)
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/




/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

// Unexposed register level functions

PRIVATE void vLcdRESSelect(void);
PRIVATE void vLcdRSSelect(uint8 u8Status);

PRIVATE void vLcdST7565InitDisplayReg(uint8 u8Bias, uint8 u8Vol);
PRIVATE void vLcdInitDisplayReg(uint8 u8Bias, uint8 u8Vol);

PRIVATE void vWriteText(char *pcString, uint8 u8Row, uint8 u8Column, uint8 u8Mask);
PRIVATE void vLcdPowerOffSelect(void);
PRIVATE void vLcdPowerSavingModeSelect (uint8 u8ModeParam);
PRIVATE void vLcdContrastLevelSelect (uint8 u8Vol);

PRIVATE void vLcdSendData(uint8 u8Data);
PRIVATE void vLcdSendCommand(tLCD_Command eCommand, uint8 u8Payload);
PRIVATE void vLcdSendCommand_ST7565( uint8 u8Command);

PRIVATE void vLcdRefreshAll_LH155(void);
PRIVATE void vLcdRefreshAll_ST7565(void);



/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
PRIVATE bool_t bST7565 = FALSE;
PRIVATE bool_t bDisplayType = FALSE;

/****************************************************************************
 *
 * NAME: vLcdReset
 *
 * DESCRIPTION:
 * Initialises LCD screen
 * Sets DIO's, initialises backlight and starts SPI interface
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Bias          R   byte flag representing bias on or off
 *                                      actual representation is on=1/7, off=1/9
 *                                      only 1/7 seems usable
 *                  u8Gain          R   byte value representing lcd gain (0 - 15)
 *                                      (electronic vol).. only values of 12 -15
 *                                      seem usable
 ****************************************************************************/
PUBLIC void vLcdReset(uint8 u8Bias, uint8 u8Gain)
{
    uint8 u8Data;
    
#ifdef JENNIC_CHIP_FAMILY_JN517x
    /* JN517x has DIO3 pulled down by default which breaks LCD detection.
     * Set DIO3 to be pulled up instead. */
    vAHI_DioSetPullupDirection(LCD_TYPE_MASK, 0);
#endif
    
    // chip select, reset and command/data dio's
    // Read DIo14 to tell us the display type
    // Low = Winstar WO12864C2YFH#
    // High = Tri-T TMGG12864J17
    vAHI_DioSetDirection(LCD_TYPE_MASK, LCD_RES_BIT_MASK | LCD_RS_BIT_MASK);

    // Check if DIO14 is pulled low
    uint32 u32Dio = u32AHI_DioReadInput();
    bDisplayType = FALSE;
    if ((u32Dio & LCD_TYPE_MASK) != 0) {
        bDisplayType = TRUE;
    }
    
    // backlight dio
    vAHI_DioSetOutput(0,LCD_BACKLIGHT_MASK);
    vAHI_DioSetDirection(0, LCD_BACKLIGHT_MASK);
    
    // Set SPI master to use auto slave select at 16MHz
    vAHI_SpiConfigure(LCD_SS, FALSE, FALSE, FALSE, 1, FALSE, FALSE);
    
    // LCD A0 line lo
    vLcdRSSelect(0);
     
    // LCD reset toggle
    vLcdRESSelect();
    
    // Which LCD board is Connected?
    vLcdGrabSpiBus();

    vAHI_SpiStartTransfer8(0);
    
    vAHI_SpiWaitBusy();
    u8Data = u8AHI_SpiReadTransfer8();
    vLcdFreeSpiBus();

    if (u8Data == 0)
        bST7565 = TRUE;
    else
        bST7565 = FALSE;

    // LCD initialise display registers to switch on state
    // have to chain on bias/gain parameters to maintain encapsulation
    // Gain is electronic volume  on this lcd and changes as such
    
    if (bST7565)
        vLcdST7565InitDisplayReg(u8Bias, u8Gain);
    else
        vLcdInitDisplayReg(u8Bias, u8Gain);

}

/****************************************************************************
 *
 * NAME: vLcdResetDefault
 *
 * DESCRIPTION:
 * Initialises LCD screen
 * Sets DIO's, initialises backlight and starts SPI interface
 * Preserved for backward compatibility only
 *
 ****************************************************************************/
PUBLIC void vLcdResetDefault(void)
{
    //vLcdReset(1, 12);
    vLcdReset(0, 12);
}

/****************************************************************************
 * NAME: vLcdRESSelect
 *
 * DESCRIPTION: RESET LINE TOGGLE
 *
 * PARAMETERS:   None
  ****************************************************************************/
PUBLIC void vLcdRESSelect ()
{

    volatile uint32 u32i;

    // reset toggle with delays
    vAHI_DioSetOutput(LCD_RES_BIT_MASK, 0);
    for (u32i = 0; u32i < 10024; u32i++);

    vAHI_DioSetOutput(0, LCD_RES_BIT_MASK);
    for (u32i = 0; u32i < 10024; u32i++);

    vAHI_DioSetOutput(LCD_RES_BIT_MASK, 0);
    for (u32i = 0; u32i < 10024; u32i++);
}

/****************************************************************************
 * NAME: vLcdRSSelect
 *
 * DESCRIPTION:
 * Sets A0 Pin
 * PARAMETERS:      Name            RW  Usage
 *                  u8Status        R   byte flag representing on or off
 *
 ****************************************************************************/
PRIVATE void vLcdRSSelect(uint8 u8Status)
{
    if (u8Status == 1)  // ON required
    {
        vAHI_DioSetOutput(LCD_RS_BIT_MASK, 0);
    }
    else {
        vAHI_DioSetOutput(0, LCD_RS_BIT_MASK);
    }
}

/****************************************************************************
 * NAME: vLcdRESelect
 *
 * DESCRIPTION:
 * Sets RE (REGISTER select flag for command options)
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Status        R   byte flag representing on or off
 ****************************************************************************/
PRIVATE void vLcdRESelect (uint8 u8Status)
{

    vLcdRSSelect(1);        // set hi

    if (u8Status == 1)  // ON required
        {
            // enable RS Line is HI (ON)
            vLcdSendData(0xF1);
        }
        else if (u8Status == 0)
        {
            // disable RS Line LO(OFF)
            vLcdSendData(0xF0);
        }

}

/****************************************************************************
 * NAME: vLcdPowerSavingMode()
 *
 * DESCRIPTION:
 * Implements power saving mode.. register level not exposed thro API
 * PARAMETERS:  Name            RW  Usage
 *              bSelectMode     R   Logical toggle to enable/disable function
 *
 ****************************************************************************/
PUBLIC void vLcdPowerSavingMode(bool_t bSelectMode)
{

    // ie power saving mode defaults to OFF at lcdreset
    // .. ON/OFF must be set explicitly from this point

    if (bSelectMode == TRUE)            // power saving mode ON
    {
        vLcdPowerSavingModeSelect (0x04);
    }
    else if (bSelectMode == FALSE)
    {
        vLcdPowerSavingModeSelect (0x00);   // power saving mode OFF
    }
}


/****************************************************************************
* NAME: vLcdPowerSavingModeSelect()
*
* DESCRIPTION:
* Implements power saving mode..
* PARAMETERS:      None
*
****************************************************************************/
PRIVATE void vLcdPowerSavingModeSelect (uint8 u8ModeParam)
{
    if(bST7565){
        if( u8ModeParam==0)
            vLcdSendCommand_ST7565(CMD_DISPLAY_OFF); // pwr off
        else
            vLcdSendCommand_ST7565(CMD_DISPLAY_ON); // pwr on
    }
    else
        vLcdSendCommand(LCD_COMMAND_POWER_CONTROL_1_SET, u8ModeParam); // set ACL
}


/****************************************************************************
 * NAME: vLcdPowerOffSelect
 *
 * DESCRIPTION:
 * Implements power off function at register level.. not exposed thro API
 * PARAMETERS:      None
 *
 ****************************************************************************/
PRIVATE void vLcdPowerOffSelect()
{
    if(bST7565)
        vLcdSendCommand_ST7565(CMD_DISPLAY_OFF); // pwr off
    else
        vLcdSendCommand(LCD_COMMAND_POWER_CONTROL_1_SET, 0x00); // pwr off
}


/****************************************************************************
 * NAME: vLcdvLcdPowerOff
 *
 * DESCRIPTION:
 * API wrapper implementation of  power off function
 * PARAMETERS:      None
 *
 ****************************************************************************/
PUBLIC void vLcdPowerOff()
{
    vLcdPowerOffSelect();
}


/****************************************************************************
 * NAME: vLcdST7565InitDisplayReg
 *
 * DESCRIPTION:
 * Implements display registers and command functions for ST7565P controller
 * PARAMETERS:      None
 *
 ****************************************************************************/
PRIVATE void vLcdST7565InitDisplayReg(uint8 u8Bias, uint8 u8Vol)
{
    // LCD bias select
    //vLcdSendCommand_ST7565(CMD_SET_BIAS_7);

    // ADC select
    vLcdSendCommand_ST7565(CMD_SET_ADC_NORMAL);

    vLcdSendCommand_ST7565(CMD_SET_COM_NORMAL);

    // Initial display line
    vLcdSendCommand_ST7565(CMD_SET_DISP_START_LINE);

    vLcdSendCommand_ST7565(CMD_SET_POWER_CONTROL | 0x7);

    vLcdSendCommand_ST7565(CMD_SET_VOLUME_FIRST);
    
    if(bDisplayType)
        vLcdSendCommand_ST7565(0x1C);   // TMG12864J-17
    else
        vLcdSendCommand_ST7565(0x30);   // WO12864C2YFH#

    vLcdSendCommand_ST7565(CMD_DISPLAY_ON);
    
    // Enable Back light
    vLcdBackLightEnable(0);
    
    // Initialise font
    vLcdFontReset();
    
    // Clear screen
    vLcdClear();
    
    // Refresh display
    vLcdRefreshAll();
}

/****************************************************************************
 * NAME: vLcdInitDisplayReg
 *
 * DESCRIPTION:
 * Implements display registers and command functions as page26 data sheet
 * PARAMETERS:      None
 *
 ****************************************************************************/
PRIVATE void vLcdInitDisplayReg(uint8 u8Bias, uint8 u8Vol)
{    
    //  initialisation command order
    vLcdSendCommand(LCD_COMMAND_POWER_CONTROL_1_SET, 0x01);     // acl reset on

    // set adjustable bias , 0 flag sets to 1/9.. otherwise default at 1/7
    // 1/9 merely dims screen .. included for completeness only
    if (u8Bias == 0)
        vLcdSendCommand(LCD_COMMAND_POWER_CONTROL_1_SET, 0x02); // pwr on .. bias 1/9
    else
        vLcdSendCommand(LCD_COMMAND_POWER_CONTROL_1_SET, 0x0A); // pwr on.. bias 1/7

    vLcdSendCommand(LCD_COMMAND_DISPLAY_CONTROL_1_SET, 0x09);       // shift/on
    vLcdSendCommand(LCD_COMMAND_POWER_CONTROL_2_SET, u8Vol);        // electronic vol

    vLcdSendCommand(LCD_COMMAND_DISPLAY_START_LO, 0x00);            // set y value lo byte
    vLcdSendCommand(LCD_COMMAND_DISPLAY_START_HI, 0x00);            // set y value hi byte
    
    // Enable Back light
    vLcdBackLightEnable(0);

    // Initialise font
    vLcdFontReset();

    // Clear screen
    vLcdClear();

    // Refresh display
    vLcdRefreshAll();

}


/****************************************************************************
 * NAME: vLcdSendCommand
 *
 * DESCRIPTION:
 * Initialise display registers and command functions as page26 data sheet
 * PARAMETERS:  Name            RW  Usage
 *              eCommand        r   command type enumeration
 *              u8Payload       r   data payload
 ****************************************************************************/
PUBLIC void vLcdSendCommand_ST7565(uint8 u8Command)
{
    vLcdGrabSpiBus();

    vLcdRSSelect(0);        // set low
    vLcdSendData(u8Command);

    vLcdFreeSpiBus();    
}

/****************************************************************************
 * NAME: vLcdSendCommand
 *
 * DESCRIPTION:
 * Initialise display registers and command functions as page26 data sheet
 * PARAMETERS:  Name            RW  Usage
 *              eCommand        r   command type enumeration
 *              u8Payload       r   data payload
 ****************************************************************************/
PUBLIC void vLcdSendCommand(tLCD_Command eCommand, uint8 u8Payload)
{
    uint8 u8Temp;

    vLcdGrabSpiBus();

    switch (eCommand)
    {
        case (LCD_COMMAND_DISPLAY_DATA_WRITE):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(0);        // set lo
            vLcdSendData(u8Payload);
            break;

        case (LCD_COMMAND_X_ADDRESS_SET):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0x00 | (u8Payload & 0x0F);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_Y_ADDRESS_SET_LO):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0x20 | (u8Payload & 0x0F);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_Y_ADDRESS_SET_HI):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0x30 | (u8Payload & 0x07);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_DISPLAY_START_LO):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0x40 | (u8Payload & 0x0F);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_DISPLAY_START_HI):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0x50 | (u8Payload & 0x0F);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_DISPLAY_CONTROL_1_SET):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0x80 | (u8Payload & 0x0F);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_DISPLAY_CONTROL_2_SET):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0x90 | (u8Payload & 0x0F);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_INCREMENT_CONTROL_SET):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0xA0 | (u8Payload & 0x07);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_POWER_CONTROL_1_SET):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0xB0 | (u8Payload & 0x0F);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_POWER_CONTROL_2_SET):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0xD0 | (u8Payload & 0x0F);
            vLcdSendData(u8Temp);
            break;

        case (LCD_COMMAND_POWER_CONTROL_3_SET):
            vLcdRESelect(0);        // set lo
            vLcdRSSelect(1);        // set hi
            u8Temp = 0xE0 | (u8Payload & 0x0F);
            vLcdSendData(u8Temp);

            // Send upper nibble of config when RE Regsister is selected
            vLcdRESelect(1);        // set hi
            vLcdRSSelect(1);        // set hi
            u8Temp = 0xE0 | ((u8Payload >> 4) & 0x0F);
            vLcdSendData(u8Temp);
            break;

        default:
            break;
    }

    vLcdFreeSpiBus();
}


/****************************************************************************
 *
 * NAME: vLcdSendData
 *
 * DESCRIPTION:
 * Sends 8 bits of data to LCD controller and waits for it to finish.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Data          R   8 bits of  'actual' data
 *
 ****************************************************************************/
PUBLIC void vLcdSendData(uint8 u8Data)
{
    volatile uint32 i;

    vAHI_SpiStartTransfer8(u8Data);
    vAHI_SpiWaitBusy();

    for (i = 0; i < 100; i++);
}

/****************************************************************************
 *
 * NAME: vLcdBackLightEnable
 *
 * DESCRIPTION:
 * Enables LCD backlight
 * PARAMETERS:      Name            RW  Usage
 *                  u8Status        R   byte flag representing on or off
 *
 * NOTES:
 * uses combination of redundant dio's (13,15, 17) from switch matrix
 *
 ****************************************************************************/
PUBLIC void vLcdBackLightEnable(uint8 u8Status)
{
    // backlight enable
    if (u8Status == 1)  // ON required
    {
        // enable backlight hi (ON)
        vAHI_DioSetOutput(LCD_BACKLIGHT_MASK, 0);
    }
    else if (u8Status == 0)
    {
        // enable backlight lo (OFF)
        vAHI_DioSetOutput(0,LCD_BACKLIGHT_MASK);
    }
}

/****************************************************************************
 *
 * NAME: vLcdClear
 *
 * DESCRIPTION:
 * Clears the LCD shadow memory area. Does not refresh the display itself
 * Works in the manner of a CRT backbuffer
 *
 ****************************************************************************/
PUBLIC void vLcdClear(void)
{
    // initialise shadow memory array
    memset(au8Shadow, 0, sizeof(au8Shadow));
}

/****************************************************************************
 *
 * NAME: vLcdStop
 *
 * DESCRIPTION:
 * Turns off LCD and allows it to power down correctly.
 *
 * NOTES:
 * Should be called before powering down LCD panel.
 *
 ****************************************************************************/
PUBLIC void vLcdStop(void)
{
    if (bST7565)
        vLcdSendCommand_ST7565(CMD_DISPLAY_OFF);
    else
        vLcdSendCommand(LCD_COMMAND_POWER_CONTROL_1_SET, 1);
}

/****************************************************************************
 *
 * NAME: u8Reverse
 *
 * DESCRIPTION:
 * Reverses the bits in a byte.
 *
 * NOTES:
 *
 ****************************************************************************/
#if 0
/* Currently unused */
PRIVATE uint8 u8Reverse(uint8 b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}
#endif

/****************************************************************************
 *
 * NAME: vLcdRefreshAll
 *
 * DESCRIPTION:
 * Copies the contents of the shadow memory to the LCD, rather like the standard
 * CRT back buffer method
 *
 * NOTES:
 * Takes a certain amount of time!
 *
 ****************************************************************************/
PUBLIC void vLcdRefreshAll(void)
{
    if (bST7565)
        vLcdRefreshAll_ST7565();
    else
        vLcdRefreshAll_LH155();
}

/****************************************************************************
 *
 * NAME: vLcdRefreshAll
 *
 * DESCRIPTION:
 * Copies the contents of the shadow memory to the LCD, rather like the standard
 * CRT back buffer method
 *
 * NOTES:
 * Takes a certain amount of time!
 *
 ****************************************************************************/
PRIVATE void vLcdRefreshAll_ST7565(void)
{
    uint8 u8CharRow, u8CharCol, u8CharPixelRow;

    for (u8CharRow = 0; u8CharRow < 8; u8CharRow++) /* 8 x 8 = 64 bits high */
    {
        for (u8CharCol = 0; u8CharCol <= 0x0F; u8CharCol++) /* 16 * 8 = 128 bits wide */
        {
            vLcdSendCommand_ST7565(CMD_SET_PAGE | u8CharRow);
            vLcdSendCommand_ST7565(CMD_SET_COLUMN_LOWER | ((u8CharCol*8) & 0x0F));
            vLcdSendCommand_ST7565(CMD_SET_COLUMN_UPPER | (((u8CharCol*8) >> 4) & 0x0F));

            vLcdRSSelect(1);        // set high
            vLcdGrabSpiBus();

            // Send data LSB first to save having to call Reverse to reverse the bits
            uint32 u32SpiCtrl = u32REG_SpiRead(REG_SPIM_CTRL);
            vREG_SpiWrite(REG_SPIM_CTRL, u32SpiCtrl | REG_SPIM_CTRL_LSB_MASK);
            for (u8CharPixelRow = 0; u8CharPixelRow < 0x8; u8CharPixelRow++) /* Each character 8 bits high */
            {
                /* Loop across each character */
                vAHI_SpiStartTransfer(7,(uint32) au8Shadow[((7-u8CharRow) * 128) + (u8CharCol * 8)+u8CharPixelRow]);
                vAHI_SpiWaitBusy();
            }
            // Restore afterwards
            vREG_SpiWrite(REG_SPIM_CTRL, u32SpiCtrl);
            vLcdFreeSpiBus();       // free spi bus
        }
    }

}

/****************************************************************************
 *
 * NAME: vLcdRefreshAll
 *
 * DESCRIPTION:
 * Copies the contents of the shadow memory to the LCD, rather like the standard
 * CRT back buffer method
 *
 * NOTES:
 * Takes a certain amount of time!
 *
 ****************************************************************************/
PRIVATE void vLcdRefreshAll_LH155(void)
{

    vLcdGrabSpiBus();       // grab spi bus

    vLcdRSSelect(0);        // reset rs lo


    uint8 u8CharRow, u8CharCol, u8CharPixelRow;

    /* this routine reorganises pixel arrangement in order to maintain backward compatibility with the
    existing draw and font routines. the original UC1606 panel organised pixels in byte columns whereas
    the LH155 orders them in byte rows. we have to rearrange the array by taking bit 7 of the
    column and creating a new row 1, then all of the bit 6 for row 2 and so on, otherwise everything
    comes out side on */

    for (u8CharRow = 0; u8CharRow < 8; u8CharRow++) /* 8 x 8 = 64 bits high */
    {
        for (u8CharCol = 0; u8CharCol <= 0x0F; u8CharCol++) /* 16 * 8 = 128 bits wide */
        {
            vLcdSendCommand(LCD_COMMAND_INCREMENT_CONTROL_SET, 0x06);/* Autoincrement y */
            vLcdSendCommand(LCD_COMMAND_X_ADDRESS_SET, u8CharCol);
            vLcdSendCommand(LCD_COMMAND_Y_ADDRESS_SET_LO, (u8CharRow*8) & 0x0F);
            vLcdSendCommand(LCD_COMMAND_Y_ADDRESS_SET_HI, ((u8CharRow*8) >> 4) & 0x0F);

            for (u8CharPixelRow = 0; u8CharPixelRow < 0x8; u8CharPixelRow++) /* Each character 8 bits high */
            {
                /* Loop across each character */
                uint8 temp = 0;

                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 0] >> (u8CharPixelRow)) & 0x01) << 0;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 1] >> (u8CharPixelRow)) & 0x01) << 1;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 2] >> (u8CharPixelRow)) & 0x01) << 2;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 3] >> (u8CharPixelRow)) & 0x01) << 3;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 4] >> (u8CharPixelRow)) & 0x01) << 4;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 5] >> (u8CharPixelRow)) & 0x01) << 5;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 6] >> (u8CharPixelRow)) & 0x01) << 6;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 7] >> (u8CharPixelRow)) & 0x01) << 7;

                vLcdSendCommand(LCD_COMMAND_DISPLAY_DATA_WRITE, temp);

            }
        }
    }

    vLcdRSSelect(1);        // reset rs hi (command mode)

    vLcdFreeSpiBus();       // free spi bus
}

/****************************************************************************
 *
 * NAME: vLcdRefreshArea_ST7565
 *
 * DESCRIPTION:
 * Copies part of the shadow memory to the LCD
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8LeftColumn    R   Left column of refresh area (0-127)
 *                  u8TopRow        R   Top character row of refresh area (0-7)
 *                  u8Width         R   Number of columns (1-128)
 *                  u8Height        R   Number of character rows (1-8)
 *
 * NOTES:
 * Takes a certain amount of time!
 *
 ****************************************************************************/
PUBLIC void vLcdRefreshArea_ST7565(uint8 u8LeftColumn, uint8 u8TopRow, uint8 u8Width,
                            uint8 u8Height)
{
    uint8 u8CharRow, u8CharCol, u8ColStart, u8ColEnd, u8RowEnd, u8CharPixelRow;

    u8ColStart = u8LeftColumn>>3;

    // Bit of Error checking
    if (u8ColStart> 0x0F) u8ColStart = 0x0F;
    if (u8TopRow>7) u8TopRow=7;


    u8RowEnd = u8TopRow+u8Height;
    u8ColEnd = u8ColStart+(u8Width>>3);

    // Do we need to do an extra byte column?
    if ((u8Width&7)!=0) u8ColEnd++;

    // Bit of Error checking
    if (u8ColEnd> 0x0F) u8ColEnd = 0x0F;
    if (u8RowEnd>8) u8RowEnd=8;


    for (u8CharRow = u8TopRow; u8CharRow < u8RowEnd; u8CharRow++) /* 8 x 8 = 64 bits high */
    {
        for (u8CharCol=u8ColStart; u8CharCol<=u8ColEnd; u8CharCol++) /* 16 * 8 = 128 bits wide */
        {
            vLcdSendCommand_ST7565(CMD_SET_PAGE | (7-u8CharRow));
            vLcdSendCommand_ST7565(CMD_SET_COLUMN_LOWER | ((u8CharCol*8) & 0x0F));
            vLcdSendCommand_ST7565(CMD_SET_COLUMN_UPPER | (((u8CharCol*8) >> 4) & 0x0F));

            vLcdRSSelect(1);        // set high
            vLcdGrabSpiBus();

            // Send data LSB first to save having to call Reverse to reverse the bits
            uint32 u32SpiCtrl = u32REG_SpiRead(REG_SPIM_CTRL);
            vREG_SpiWrite(REG_SPIM_CTRL, u32SpiCtrl | REG_SPIM_CTRL_LSB_MASK);
            for (u8CharPixelRow = 0; u8CharPixelRow < 0x8; u8CharPixelRow++) /* Each character 8 bits high */
            {
                /* Loop across each character */
                vAHI_SpiStartTransfer(7,(uint32)au8Shadow[((u8CharRow) * 128) + (u8CharCol*8)+u8CharPixelRow ]);
                vAHI_SpiWaitBusy();
            }
            // Restore afterwards
            vREG_SpiWrite(REG_SPIM_CTRL, u32SpiCtrl);
            vLcdFreeSpiBus();       // free spi bus
        }
    }

}
/****************************************************************************
 *
 * NAME: vLcdRefreshArea_LH155
 *
 * DESCRIPTION:
 * Copies part of the shadow memory to the LCD
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8LeftColumn    R   Left column of refresh area (0-127)
 *                  u8TopRow        R   Top character row of refresh area (0-7)
 *                  u8Width         R   Number of columns (1-128)
 *                  u8Height        R   Number of character rows (1-8)
 *
 * NOTES:
 * Takes a certain amount of time!
 *
 ****************************************************************************/
PUBLIC void vLcdRefreshArea_LH155(uint8 u8LeftColumn, uint8 u8TopRow, uint8 u8Width,
                            uint8 u8Height)
{
    uint8 u8CharRow, u8CharCol, u8ColStart, u8ColEnd, u8RowEnd, u8CharPixelRow;

    vLcdGrabSpiBus();       // grab spi bus

    vLcdRSSelect(0);        // reset rs lo

    u8ColStart = u8LeftColumn>>3;

    // Bit of Error checking
    if (u8ColStart> 0x0F) u8ColStart = 0x0F;
    if (u8TopRow>7) u8TopRow=7;


    u8RowEnd = u8TopRow+u8Height;
    u8ColEnd = u8ColStart+(u8Width>>3);

    // Do we need to do an extra byte column?
    if ((u8Width&7)!=0) u8ColEnd++;

    // Bit of Error checking
    if (u8ColEnd> 0x0F) u8ColEnd = 0x0F;
    if (u8RowEnd>8) u8RowEnd=8;

    for (u8CharRow = u8TopRow; u8CharRow < u8RowEnd; u8CharRow++) /* 8 x 8 = 64 bits high */
    {
        for (u8CharCol=u8ColStart; u8CharCol<=u8ColEnd; u8CharCol++) /* 16 * 8 = 128 bits wide */
        {
            vLcdSendCommand(LCD_COMMAND_INCREMENT_CONTROL_SET, 0x06);/* Autoincrement y */
            vLcdSendCommand(LCD_COMMAND_X_ADDRESS_SET, u8CharCol);
            vLcdSendCommand(LCD_COMMAND_Y_ADDRESS_SET_LO, (u8CharRow*8) & 0x0F);
            vLcdSendCommand(LCD_COMMAND_Y_ADDRESS_SET_HI, ((u8CharRow*8) >> 4) & 0x0F);

            for (u8CharPixelRow = 0; u8CharPixelRow < 0x8; u8CharPixelRow++) /* Each character 8 bits high */
            {
                /* Loop across each character */
                uint8 temp = 0;

                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 0] >> (u8CharPixelRow)) & 0x01) << 0;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 1] >> (u8CharPixelRow)) & 0x01) << 1;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 2] >> (u8CharPixelRow)) & 0x01) << 2;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 3] >> (u8CharPixelRow)) & 0x01) << 3;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 4] >> (u8CharPixelRow)) & 0x01) << 4;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 5] >> (u8CharPixelRow)) & 0x01) << 5;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 6] >> (u8CharPixelRow)) & 0x01) << 6;
                temp |= ((au8Shadow[(u8CharRow * 128) + (u8CharCol * 8) + 7] >> (u8CharPixelRow)) & 0x01) << 7;

                vLcdSendCommand(LCD_COMMAND_DISPLAY_DATA_WRITE, temp);

            }
        }
    }

    vLcdRSSelect(1);        // reset rs hi (command mode)

    vLcdFreeSpiBus();       // free spi bus
}



/****************************************************************************
 *
 * NAME: vLcdRefreshArea
 *
 * DESCRIPTION:
 * Copies part of the shadow memory to the LCD
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8LeftColumn    R   Left column of refresh area (0-127)
 *                  u8TopRow        R   Top character row of refresh area (0-7)
 *                  u8Width         R   Number of columns (1-128)
 *                  u8Height        R   Number of character rows (1-8)
 *
 * NOTES:
 * Takes a certain amount of time!
 *
 ****************************************************************************/
 PUBLIC void vLcdRefreshArea(uint8 u8LeftColumn, uint8 u8TopRow, uint8 u8Width, uint8 u8Height)
{
    if (bST7565)
        vLcdRefreshArea_ST7565(u8LeftColumn, u8TopRow, u8Width, u8Height);
    else
        vLcdRefreshArea_LH155(u8LeftColumn, u8TopRow, u8Width, u8Height);
}


/****************************************************************************
 *
 * NAME: vLcdWriteText
 *
 * DESCRIPTION:
 * Puts text into shadow buffer. Text is aligned to a character row but can
 * be at any column. Characters are variable width but 8 pixels high.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  pcString        R   Pointer to zero-terminated string
 *                  u8Row           R   Character row (0-7)
 *                  u8Column        R   Start column (0-127)
 *
 * NOTES:
 * To see text, perform a refresh afterwards, otherwise charachters remain
 * in memory (on the 'backbuffer')
 *
 ****************************************************************************/
PUBLIC void vLcdWriteText(char *pcString, uint8 u8Row, uint8 u8Column)
{
    vWriteText(pcString, u8Row, u8Column, 0);
}


/****************************************************************************
 *
 * NAME: vLcdWriteInvertedText
 *
 * DESCRIPTION:
 * Puts text into shadow buffer. Text is aligned to a character row but can
 * be at any column. Characters are variable width but 8 pixels high. Text is
 * inverted (black <-> white).
 *
 * PARAMETERS:      Name            RW  Usage
 *                  pcString        R   Pointer to zero-terminated string
 *                  u8Row           R   Character row (0-7)
 *                  u8Column        R   Start column (0-127)
 *
 * NOTES:
 * To see text, perform a refresh
 *
 ****************************************************************************/
PUBLIC void vLcdWriteInvertedText(char *pcString, uint8 u8Row, uint8 u8Column)
{
    vWriteText(pcString, u8Row, u8Column, 0xff);
}

/****************************************************************************
 *
 * NAME: vLcdWriteBitmap
 *
 * DESCRIPTION:
 * Copies a bitmap to shadow memory
 *
 * PARAMETERS:      Name            RW  Usage
 *                  ps8Bitmap       R   Bitmap image: see .h file for details
 *                  u8LeftColumn    R   Left column to place bitmap (0-127)
 *                  u8TopRow        R   Top row of bitmap (0-7)
 *
 ****************************************************************************/
PUBLIC void vLcdWriteBitmap(tsBitmap *psBitmap, uint8 u8LeftColumn,
                            uint8 u8TopRow)
{
    uint8 u8Row;
    uint8 u8Col;
    uint8 u8EndRow;
    uint8 u8EndCol;
    uint8 *pu8Shadow;
    uint8 *pu8Bitmap;

    // Set ends so bitmap does not wrap around
    u8EndRow = psBitmap->u8Height;
    if ((u8TopRow + u8EndRow) > 8)
    {
        u8EndRow = 8 - u8TopRow;
    }

    u8EndCol = psBitmap->u8Width;
    if ((u8LeftColumn + u8EndCol) > 128)
    {
        u8EndCol = 128 - u8LeftColumn;
    }

    // Copy bitmap
    for (u8Row = 0; u8Row < u8EndRow; u8Row++)
    {
        pu8Shadow = &au8Shadow[(u8TopRow + u8Row) * 128 + u8LeftColumn];
        pu8Bitmap = &psBitmap->pu8Bitmap[u8Row * psBitmap->u8Width];

        for (u8Col = 0; u8Col < u8EndCol; u8Col++)
        {
            pu8Shadow[u8Col] = pu8Bitmap[u8Col];
        }
    }
}


/****************************************************************************
 *
 * NAME: vLcdGrabSpiBus
 *
 * DESCRIPTION:
 * Sets up the SPI bus for use by this driver. It sets it to automatic
 * slave select and then selects the correct slave, and also sets the clock
 * divider to give 4MHz
 *
 ****************************************************************************/
PUBLIC void vLcdGrabSpiBus(void)
{

    // Set slave select
    vAHI_SpiSelect(LCD_SS_MASK);
}

/****************************************************************************
 *
 * NAME: vLcdFreeSpiBus
 *
 * DESCRIPTION:
 * Performs any clear-up after LCD accesses. Currently a null function.
 *
 ****************************************************************************/
PUBLIC void vLcdFreeSpiBus(void)
{
    vAHI_SpiSelect(0);
}




/****************************************************************************
 *
 * NAME: vLcdButtonInit
 *
 * DESCRIPTION:
 * Initialises buttons on LCD Expansion Board
 *
 ****************************************************************************/
PUBLIC void vLcdButtonInit(void)
{
    vAHI_DioSetDirection(LCD_BOARD_BUTTON_ALL_MASK_PIN, 0);
}



/****************************************************************************
 *
 * NAME: u8LcdButtonRead
 *
 * DESCRIPTION:
 * Read current state of buttons on Expansion Board
 *
 * RETURNS
 * uint8, Bitmap of button state (4 buttons only bottom 4 bits are used)
 *
 ****************************************************************************/
PUBLIC uint8 u8LcdButtonRead(void)
{
    uint32 u32DioPins;
    uint8 u8RetVal = 0;

    u32DioPins = u32AHI_DioReadInput();
    if((u32DioPins & LCD_BOARD_BUTTON_S1_PIN)==0) u8RetVal += LCD_BOARD_BUTTON_S1_VAL;
    if((u32DioPins & LCD_BOARD_BUTTON_S2_PIN)==0) u8RetVal += LCD_BOARD_BUTTON_S2_VAL;
    if((u32DioPins & LCD_BOARD_BUTTON_S3_PIN)==0) u8RetVal += LCD_BOARD_BUTTON_S3_VAL;
    if((u32DioPins & LCD_BOARD_BUTTON_S4_PIN)==0) u8RetVal += LCD_BOARD_BUTTON_S4_VAL;
    return (u8RetVal);
}


/****************************************************************************
 *
 * NAME: vLcdContrastLevel
 *
 * DESCRIPTION:
 * public interface to screen contrast adjustment function
 *
 *
 ****************************************************************************/
PUBLIC void vLcdContrastLevel(uint8 u8Gain)
{
    vLcdContrastLevelSelect (u8Gain);

}

/****************************************************************************
 *
 * NAME: vLcdContrastLevelSelect
 *
 * DESCRIPTION:
 * register level adjustment of screen contrast
 *
 ****************************************************************************/

PRIVATE void vLcdContrastLevelSelect (uint8 u8Vol)
{

//  vLcdSendCommand(LCD_COMMAND_POWER_CONTROL_2_SET, u8Vol);    // electronic vol

}


/****************************************************************************
 *
 * NAME: u8CalcContrastLevel
 *
 * DESCRIPTION:
 * Calculates correct contrast level dependent upon voltage level of power source
 *
 * PARAMETERS:      Name
 *                  u8u8CalcContrastLevel   r   contrast level to be set 0-15
 *                                              in practice only 11-15 are usable
  ****************************************************************************/

PUBLIC uint8 u8LcdCalcContrastLevel(void)
{

    // local value placeholders
    uint8 u8ContrastValue;
    uint16 u16BattVoltage;
    uint32 u32BattVoltage;

    /* Initialise the hardware API */
    u32AHI_Init();

    vAHI_ApConfigure(E_AHI_AP_REGULATOR_ENABLE,
                 E_AHI_AP_INT_DISABLE,
                 E_AHI_AP_SAMPLE_8,
                 E_AHI_AP_CLOCKDIV_500KHZ,
                 E_AHI_AP_INTREF);

    while (!bAHI_APRegulatorEnabled());   /* spin on reg not enabled */

    vAHI_AdcEnable(E_AHI_ADC_SINGLE_SHOT, E_AHI_AP_INPUT_RANGE_2, E_AHI_ADC_SRC_VOLT);  //enable adc

    vAHI_AdcStartSample();      // start sampling adc

    while(bAHI_AdcPoll());      // keep polling until we get a value

    u16BattVoltage = 0;

#if (defined JENNIC_CHIP_FAMILY_JN514x)
    {
    uint32 u32PartId;       // placeholder for chip id

    u32PartId = ((*((uint32*)CHIP_ID_REG))&0x1F000)>>12;

    //Mask Off Part ID
    if(u32PartId == 5)
    {
        //JN5142
        u16BattVoltage = u16AHI_AdcRead();
    }
    else if (u32PartId == 4)
    {
        //JN5148
        u16BattVoltage = u16AHI_AdcRead() >> 4;
    }
    }

#elif (defined JENNIC_CHIP_FAMILY_JN516x)
        u16BattVoltage = u16AHI_AdcRead() >> 2;

#endif



    u32BattVoltage = (u16BattVoltage *3600) >> 8;  /*  in Millivolts */

    vAHI_AdcDisable();

    // calculate correct contrast value
    if ( u32BattVoltage <= 2600)
    {   // <=2.6v needs high setting

        u8ContrastValue = 14;       // contrast 14
    }

    else if (( u32BattVoltage > 2600) && ( u32BattVoltage <= 2800))
    {       // 2.6 <> 2.8

        u8ContrastValue = 13;       // 13
    }

    else if (( u32BattVoltage  > 2800) && ( u32BattVoltage  <= 2900))
    {       // 2.8 <> 2.9

        u8ContrastValue = 12;       // 12
    }

    else
    {                       // contrast value greater than 2.9

        u8ContrastValue = 11;       // 11
    }

    return u8ContrastValue;


}

/****************************************************************************
 *
 * NAME: vLcdWriteText
 *
 * DESCRIPTION:
 * Puts text into shadow buffer. Text is aligned to a character row but can
 * be at any column. Characters are variable width but 8 pixels high.
 *
 * PARAMETERS:      Name       RW  Usage
 *                  pcString   R   Pointer to zero-terminated string
 *                  u8Row      R   Character row (0-7)
 *                  u8Column   R   Start column (0-127)
 *                  u8Mask     R   Mask to XOR with (0:normal, 0xff:invert)
 *
 * NOTES:
 * To see text, perform a refresh
 *
 ****************************************************************************/

PRIVATE void vWriteText(char *pcString, uint8 u8Row, uint8 u8Column, uint8 u8Mask)
{
    uint8 u8Columns;
    uint8 *pu8CharMap;
    uint8 *pu8Shadow = &au8Shadow[u8Row * 128 + u8Column];

    // Column before first character
    *pu8Shadow = u8Mask;
    pu8Shadow++;

    while ((*pcString != 0) && (pu8Shadow < &au8Shadow[1024]))
    {
        pu8CharMap = pu8LcdFontGetChar(*pcString);
        u8Columns = *pu8CharMap;

        /* Copy character bitmap to shadow memory */
        do
        {
            pu8CharMap++;
            *pu8Shadow = (*pu8CharMap) ^ u8Mask;
            pu8Shadow++;
            u8Columns--;
        } while ((u8Columns > 0) && (pu8Shadow < &au8Shadow[1024]));

        /* Add a column spacing */
        *pu8Shadow = u8Mask;
        pu8Shadow++;

        pcString++;
    }
}



/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/


