/*****************************************************************************
 *
 * MODULE:              Driver for UC1606 LCD Driver-Controller
 * DESCRIPTION:
 * Provides API for driving LCD panels using UC1606 LCD Driver-Controller.
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
/***        Include Files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "LcdFont.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

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
PRIVATE const uint8 au8LcdFont[75][6] = {
    {5, 0x3E, 0x41, 0x41, 0x41, 0x3E}, /* 0 */
    {3, 0x42, 0x7F, 0x40, 0x00, 0x00}, /* 1 */
    {5, 0x42, 0x61, 0x51, 0x49, 0x46}, /* 2 */
    {5, 0x22, 0x41, 0x49, 0x49, 0x36}, /* 3 */
    {5, 0x18, 0x14, 0x12, 0x7F, 0x10}, /* 4 */
    {5, 0x27, 0x45, 0x45, 0x45, 0x39}, /* 5 */
    {5, 0x3C, 0x4A, 0x49, 0x49, 0x30}, /* 6 */
    {5, 0x01, 0x71, 0x09, 0x05, 0x03}, /* 7 */
    {5, 0x36, 0x49, 0x49, 0x49, 0x36}, /* 8 */
    {5, 0x06, 0x49, 0x49, 0x29, 0x1E}, /* 9 */
    {3, 0x00, 0x24, 0x00, 0x00, 0x00}, /* : */
    {4, 0x00, 0x40, 0x24, 0x00, 0x00}, /* ; */
    {3, 0x08, 0x0c, 0x08, 0x00, 0x00}, /* < (as up arrow) */
    {5, 0x14, 0x14, 0x14, 0x14, 0x14}, /* = */
    {3, 0x08, 0x18, 0x08, 0x00, 0x00}, /* > (as down arrow) */
    {5, 0x02, 0x01, 0x51, 0x09, 0x06}, /* ? */
    {5, 0x32, 0x49, 0x79, 0x41, 0x3E}, /* @ */
    {5, 0x7E, 0x09, 0x09, 0x09, 0x7E}, /* A */
    {5, 0x7F, 0x49, 0x49, 0x49, 0x36}, /* B */
    {5, 0x3E, 0x41, 0x41, 0x41, 0x22}, /* C */
    {5, 0x7F, 0x41, 0x41, 0x22, 0x1C}, /* D */
    {5, 0x7F, 0x49, 0x49, 0x49, 0x41}, /* E */
    {5, 0x7F, 0x09, 0x09, 0x09, 0x01}, /* F */
    {5, 0x3E, 0x41, 0x41, 0x49, 0x3A}, /* G */
    {5, 0x7F, 0x08, 0x08, 0x08, 0x7F}, /* H */
    {3, 0x41, 0x7F, 0x41, 0x00, 0x00}, /* I */
    {5, 0x20, 0x41, 0x41, 0x3F, 0x01}, /* J */
    {5, 0x7F, 0x08, 0x14, 0x22, 0x41}, /* K */
    {5, 0x7F, 0x40, 0x40, 0x40, 0x40}, /* L */
    {5, 0x7F, 0x02, 0x1C, 0x02, 0x7F}, /* M */
    {5, 0x7F, 0x04, 0x08, 0x10, 0x7F}, /* N */
    {5, 0x3E, 0x41, 0x41, 0x41, 0x3E}, /* O */
    {5, 0x7F, 0x09, 0x09, 0x09, 0x06}, /* P */
    {5, 0x3E, 0x41, 0x41, 0x31, 0x4E}, /* Q */
    {5, 0x7F, 0x09, 0x09, 0x19, 0x66}, /* R */
    {5, 0x26, 0x49, 0x49, 0x49, 0x32}, /* S */
    {5, 0x01, 0x01, 0x7F, 0x01, 0x01}, /* T */
    {5, 0x3F, 0x40, 0x40, 0x40, 0x3F}, /* U */
    {5, 0x1F, 0x20, 0x40, 0x20, 0x1F}, /* V */
    {5, 0x3F, 0x40, 0x38, 0x40, 0x3F}, /* W */
    {5, 0x63, 0x14, 0x08, 0x14, 0x63}, /* X */
    {5, 0x07, 0x08, 0x78, 0x08, 0x07}, /* Y */
    {5, 0x61, 0x51, 0x49, 0x45, 0x43}, /* Z */
    {3, 0x07, 0x05, 0x07, 0x00, 0x00}, /* [ (as degrees) */
    {5, 0x08, 0x08, 0x3e, 0x08, 0x08}, /* \ (as plus) */
    {5, 0x08, 0x08, 0x08, 0x08, 0x08}, /* ] (as minus) */
    {3, 0x00, 0x00, 0x00, 0x00, 0x00}, /* ^ (as space) */
    {3, 0x40, 0x40, 0x40, 0x00, 0x00}, /* _ */
    {1, 0x40, 0x00, 0x00, 0x00, 0x00}, /* ` (as full stop) */
    {5, 0x20, 0x54, 0x54, 0x54, 0x78}, /* a */
    {5, 0x7F, 0x44, 0x44, 0x44, 0x38}, /* b */
    {5, 0x38, 0x44, 0x44, 0x44, 0x28}, /* c */
    {5, 0x38, 0x44, 0x44, 0x44, 0x7F}, /* d */
    {5, 0x38, 0x54, 0x54, 0x54, 0x18}, /* e */
    {4, 0x08, 0x7E, 0x09, 0x09, 0x00}, /* f */
    {5, 0x18, 0xA4, 0xA4, 0xA4, 0x7C}, /* g */
    {5, 0x7F, 0x04, 0x04, 0x04, 0x78}, /* h */
    {1, 0x7D, 0x00, 0x00, 0x00, 0x00}, /* i */
    {2, 0x80, 0x7D, 0x00, 0x00, 0x00}, /* j */
    {5, 0x7F, 0x10, 0x10, 0x28, 0x44}, /* k */
    {1, 0x7F, 0x00, 0x00, 0x00, 0x00}, /* l */
    {5, 0x78, 0x04, 0x18, 0x04, 0x78}, /* m */
    {5, 0x7C, 0x04, 0x04, 0x04, 0x78}, /* n */
    {5, 0x38, 0x44, 0x44, 0x44, 0x38}, /* o */
    {5, 0xFC, 0x24, 0x24, 0x24, 0x18}, /* p */
    {5, 0x18, 0x24, 0x24, 0x24, 0xFC}, /* q */
    {5, 0x7C, 0x08, 0x04, 0x04, 0x08}, /* r */
    {5, 0x48, 0x54, 0x54, 0x54, 0x24}, /* s */
    {4, 0x04, 0x3F, 0x44, 0x44, 0x00}, /* t */
    {5, 0x3C, 0x40, 0x40, 0x40, 0x7C}, /* u */
    {5, 0x1C, 0x20, 0x40, 0x20, 0x1C}, /* v */
    {5, 0x3C, 0x40, 0x30, 0x40, 0x3C}, /* w */
    {5, 0x44, 0x28, 0x10, 0x28, 0x44}, /* x */
    {5, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C}, /* y */
    {5, 0x44, 0x64, 0x54, 0x4C, 0x44}, /* z */
};

const uint8 au8LcdFontWide[8][9] = {
    {7, 0x47, 0x25, 0x13, 0x08, 0x64, 0x52, 0x71, 0x00}, /* % */
    {8, 0x1c, 0x3E, 0x7F, 0x7F, 0x7F, 0x7F, 0x3E, 0x1c}, /* Full dark */
    {8, 0x1c, 0x3E, 0x7F, 0x7F, 0x7F, 0x7F, 0x22, 0x1c},
    {8, 0x1c, 0x3E, 0x7F, 0x7F, 0x7F, 0x41, 0x22, 0x1c},
    {8, 0x1c, 0x3E, 0x7F, 0x7F, 0x41, 0x41, 0x22, 0x1c},
    {8, 0x1c, 0x3E, 0x7F, 0x41, 0x41, 0x41, 0x22, 0x1c},
    {8, 0x1c, 0x3E, 0x41, 0x41, 0x41, 0x41, 0x22, 0x1c},
    {8, 0x1c, 0x22, 0x41, 0x41, 0x41, 0x41, 0x22, 0x1c}, /* Full light */
};

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: vLcdFontReset
 *
 * DESCRIPTION:
 * Sets up font store. Font needs converting from horizontal to vertical
 * strips.
 *
 ****************************************************************************/
PUBLIC void vLcdFontReset(void)
{
}

/****************************************************************************
 *
 * NAME: pu8LcdFontGetChar
 *
 * DESCRIPTION:
 * Returns pointer to x bytes containing a character map, first byte contains
 * number of valid subsequent bytes.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Char          R   Ascii value of character
 *
 * RETURNS:
 * Pointer to character map.
 *
 ****************************************************************************/
PUBLIC uint8 *pu8LcdFontGetChar(uint8 u8Char)
{
    if ((u8Char >= '0') && (u8Char <= 'z'))
    {
        return (uint8 *)au8LcdFont[u8Char - '0'];
    }

    if ((u8Char >= '%') && (u8Char <= ','))
    {
        return (uint8 *)au8LcdFontWide[u8Char - '%'];
    }

    /* Default is to return a space character */
    return (uint8 *)au8LcdFont[46];
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

