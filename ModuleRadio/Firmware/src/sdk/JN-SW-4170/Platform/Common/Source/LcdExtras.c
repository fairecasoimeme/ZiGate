/****************************************************************************
 *
 * MODULE:             Driver for UC1601 and UC1606 LCD Driver-Controller
 *
 * DESCRIPTION:
 * Provides API for driving LCD panels using UC1601 or UC1606 LCD
 * Driver-Controller.
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
#include "LcdDriver.h"
#include "LcdFont.h"
#include "AppHardwareApi.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define LCD_CMD_SET_BIAS                (0xe8)
#define LCD_CMD_SET_FRAME_RATE          (0xa0)
#define LCD_CMD_SYSTEM_RESET            (0xe2)
#define LCD_CMD_SET_DISPLAY             (0xae)
#define LCD_CMD_SET_RAM_ADDRESS_CONTROL (0x88)
#define LCD_CMD_SET_PAGE_ADDRESS        (0xb0)
#define LCD_CMD_SET_COLUMN_LSB          (0x00)
#define LCD_CMD_SET_COLUMN_MSB          (0x10)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/


/****************************************************************************
 *
 * NAME: vLcdClearLine
 *
 * DESCRIPTION:
 * Clears a specified line on the LCD Display
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Row           R   Character row (0-7)
 *
 * NOTES:
 * To see text, perform a refresh
 *
 ****************************************************************************/
PUBLIC void vLcdClearLine(uint8 u8Row)
{
    memset(&au8Shadow[128 * u8Row], 0, 128);
}

/****************************************************************************
 *
 * NAME: vLcdWriteTextToClearLine
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
 * To see text, perform a refresh
 *
 ****************************************************************************/

PUBLIC void vLcdWriteTextToClearLine(char *pcString, uint8 u8Row, uint8 u8Column)
{
    vLcdClearLine(u8Row);

    vLcdWriteText(pcString, u8Row, u8Column);
}

/****************************************************************************
 *
 * NAME: vLcdWriteTextRightJustified
 *
 * DESCRIPTION:
 * Puts text into shadow buffer. Text is aligned to a character row but can
 * be at any column. Characters are variable width but 8 pixels high. The text
 * is right justified, with the supplied column being the rightmost one.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  pcString        R   Pointer to zero-terminated string
 *                  u8Row           R   Character row (0-7)
 *                  u8EndColumn     R   End column (0-127)
 *
 * NOTES:
 * To see text, perform a refresh
 *
 ****************************************************************************/
PUBLIC void vLcdWriteTextRightJustified(char *pcString, uint8 u8Row,
                                        uint8 u8EndColumn)
{
    uint8 u8Columns = 0;
    uint8 *pu8CharMap;
    char *pcStringCopy = pcString;

    /* Work out how many columns we need */
    while (*pcStringCopy != 0)
    {
        pu8CharMap = pu8LcdFontGetChar(*pcStringCopy);
        u8Columns += *pu8CharMap;
        u8Columns += 1;
        pcStringCopy++;
    }

    /* Call normal text write function */
    vLcdWriteText(pcString, u8Row, u8EndColumn - u8Columns);
}


/****************************************************************************
 *
 * NAME: vLcdScrollUp
 *
 * DESCRIPTION:
 * Scrolls the shadow memory up by one row. Region scrolled is between
 * specified row and bottom of screen. Bottom row is left cleared.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Row           R   First row of scrolled region
 *
 ****************************************************************************/
PUBLIC void vLcdScrollUp(uint8 u8Row)
{
    if (u8Row < 8)
    {
        /* Move rows up */
        memmove(&au8Shadow[128 * u8Row], &au8Shadow[128 * (u8Row + 1)], (7 - u8Row) * 128);
        
        /* Clear row 7 */
        vLcdClearLine(7);
    }
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
