/*****************************************************************************
 *
 * MODULE:              IO pin assignments for platform
 *
 * DESCRIPTION:
 * Provides #defines for the IO pins used on a specific board - enables the 
 * source code to be more generic.
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
#ifndef  PLATFORM_DIO_INCLUDED
#define  PLATFORM_DIO_INCLUDED

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
/* For buttons, have a separate entry for each (PIN_BUTTON0_BIT, 
   PIN_BUTTON1_BIT, etc.) plus a count of how many buttons there are */
#define PIN_BUTTON0_BIT       (8)
#define PIN_BUTTON_NUMBER     (1)
#define PIN_BUTTON_NUMBER_FFD (1)

/* For LEDs, assume they are all on consecutive IO pins, so just provide base
   pin and number of pins involved */
#define PIN_LED_BASE_BIT      (2)
#define PIN_LED_NUMBER        (2)
#define PIN_LED_NUMBER_FFD    (2)

/* TSL2550 is on SMbus, so no additional defines needed */

/* PCA9634 is on SMbus except for output enable pin */
#define PIN_PCA9634_OE        (16)

/* SHT1x (HTS) is on DIO12 (data) and DIO17 (clock) */
#define PIN_HTS_DATA          (12)
#define PIN_HTS_CLK           (17)

/* PWN driver for white LED cluster on DR1175: uses DIO13, but which timer to
   use for this depends on chip:
      JN5142-x01:PWM3
      JN5148-x01:PWM1
      JN516x    :PWM3 */

   
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

#endif  /* PLATFORM_DIO_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

