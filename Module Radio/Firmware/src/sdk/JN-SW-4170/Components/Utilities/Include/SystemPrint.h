/****************************************************************************
 *
 * MODULE:             Printf Header
 *
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

#ifndef SYSTEMPRINT_H_INCLUDED
#define SYSTEMPRINT_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <Utilities.h>
#ifdef PRINT_LCD
#include <LcdDriver.h>
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* API Platform dependent DISPLAY MACRO'S */

/* UART PRINT option */
#if(defined PRINT_UART)
#define _PRINT_INIT()                                   vUTIL_UartInit()
#define _CLEAR()
#define _WRITE_TEXT_TO_CLEAR_LINE(string, row, col)     vUTIL_UartTextToNewLine(string)
#define _WRITE_TEXT_TO_LINE(string, row, col)           vUTIL_UartText(string)
#define _UPDATE_TEXT()
#define _CONVERT_NUM_TO_STR(num, str)                   vUTIL_NumToString(num, str)

/* LCD PRINT option */
#elif(defined PRINT_LCD)
#define _PRINT_INIT()                                   vLcdResetDefault()
#define _CLEAR()                                        vLcdClear()
#define _WRITE_TEXT_TO_CLEAR_LINE(string, row, col)     vLcdWriteTextToClearLine(string, row, col)
#define _WRITE_TEXT_TO_LINE(string, row, col)           vLcdWriteText(string, row, col)
#define _UPDATE_TEXT()                                  vLcdRefreshAll()
#define _CONVERT_NUM_TO_STR(num, str)                   vUTIL_NumToString(num, str)

/* No PRINT option */
#else
#define _PRINT_INIT()
#define _CLEAR()
#define _WRITE_TEXT_TO_CLEAR_LINE(string, row, col)
#define _WRITE_TEXT_TO_LINE(string, row, col)
#define _UPDATE_TEXT()
#define _CONVERT_NUM_TO_STR(num, str)

#endif
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif /* SYSTEMPRINT_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/


