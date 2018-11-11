/*****************************************************************************
 *
 * MODULE:              Demo board LED controls
 *
 * DESCRIPTION:
 * Macros to make it easier to drive LEDs on demo boards
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


#ifndef LED_CONTROL_INCLUDED
#define LED_CONTROL_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "AppHardwareApi.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define LED_CTRL_BASE_BIT 16
#define LED_CTRL_MASK_RFD 0x03
#define LED_CTRL_MASK_FFD 0x0f
#define LED_CTRL_MASK_NTS 0x03


#define vLedInitRfd() \
            vAHI_DioSetDirection(0, (LED_CTRL_MASK_RFD << LED_CTRL_BASE_BIT))
#define vLedInitFfd() \
            vAHI_DioSetDirection(0, (LED_CTRL_MASK_FFD << LED_CTRL_BASE_BIT))
#define vLedControl(LED,ON) \
            vAHI_DioSetOutput((ON) ? 0 : (1 << (LED_CTRL_BASE_BIT + LED)), \
                              (ON) ? (1 << (LED_CTRL_BASE_BIT + LED)) : 0)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* LED_CONTROL_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

