/*****************************************************************************
 *
 * MODULE:              Driver for LCD Driver-Controller
 *
 * DESCRIPTION:
 * Provides API for driving LCD panels using LCD Driver-Controller.
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
#define LCD_SS           (1)
#define LCD_SS_MASK      (1 << LCD_SS)
#define LCD_CD_BIT_MASK  (1 << 1)
#define LCD_RST_BIT_MASK (1 << 8)

#define LCD_DIO_BIT_MASK (LCD_CD_BIT_MASK | LCD_RST_BIT_MASK)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef struct
{
    /* Bitmap can be any number of columns but a multiple of eight bits high,
       will be aligned to a character row when displayed and is as follows:
       column   0  1  2    y-1
       row  0  aa ab ac .. ax
       row  1  ba bb bc .. bx
       row  2  ca cb cc .. cx
               .. .. .. .. ..
       row  7  ha hb hc .. hx
       row  8  ia ib ic .. ix
       row  9  ja jb jc .. jx
               .. .. .. .. ..
       row 15  pa pb pc .. px

       pu8Bitmap[0]   = (MSB) ha ga fa ea da ca ba aa (LSB)
       pu8Bitmap[1]   = (MSB) hb gb fb eb db cb bb ab (LSB)
       pu8Bitmap[y-1] = (MSB) hx gx fx ex dx cx bx ax (LSB)
       pu8Bitmap[y]   = (MSB) pa oa na ma la ka ja ia (LSB)
    */
    uint8 *pu8Bitmap;
    uint8 u8Width;  /* Width in pixels (y in example above) */
    uint8 u8Height; /* Height in character rows (2 in example above) */
} tsBitmap;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void vLcdResetDefault(void);
PUBLIC void vLcdReset(uint8 u8Bias, uint8 u8Gain);
PUBLIC void vLcdStop(void);
PUBLIC void vLcdClear(void);
PUBLIC void vLcdRefreshAll(void);
PUBLIC void vLcdRefreshArea(uint8 u8LeftColumn, uint8 u8TopRow, uint8 u8Width,
                            uint8 u8Height);
PUBLIC void vLcdWriteText(char *pcString, uint8 u8Row, uint8 u8Column);
PUBLIC void vLcdWriteTextRightJustified(char *pcString, uint8 u8Row,
                                        uint8 u8EndColumn);
PUBLIC void vLcdWriteInvertedText(char *pcString, uint8 u8Row, uint8 u8Column);
PUBLIC void vLcdWriteBitmap(tsBitmap *psBitmap, uint8 u8LeftColumn,
                            uint8 u8TopRow);
PUBLIC void vLcdScrollUp(uint8 u8Row);
PUBLIC void vLcdClearLine(uint8 u8Row);
PUBLIC void vLcdWriteTextToClearLine(char *pcString, uint8 u8Row, uint8 u8Column);

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

