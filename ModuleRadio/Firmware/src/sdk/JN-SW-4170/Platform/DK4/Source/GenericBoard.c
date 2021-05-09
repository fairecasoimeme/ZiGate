/****************************************************************************
 *
 * MODULE:             generic expansion board controls
 *
 * DESCRIPTION:
 * Functions to make it easier to use functionality on generic expansion board
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

#include <jendefs.h>
#include "GenericBoard.h"
#include "AppHardwareApi.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define GEN_BOARD_BUTTON_S1_PIN_BIT        (11)
#define GEN_BOARD_BUTTON_S2_PIN_BIT        (12)
#define GEN_BOARD_BUTTON_S3_PIN_BIT     (17)
#define GEN_BOARD_BUTTON_S4_PIN_BIT        (1)

#define GEN_BOARD_BUTTON_S1_PIN            (1UL << GEN_BOARD_BUTTON_S1_PIN_BIT)
#define GEN_BOARD_BUTTON_S2_PIN            (1UL << GEN_BOARD_BUTTON_S2_PIN_BIT)
#define GEN_BOARD_BUTTON_S3_PIN            (1UL << GEN_BOARD_BUTTON_S3_PIN_BIT)
#define GEN_BOARD_BUTTON_S4_PIN            (1UL << GEN_BOARD_BUTTON_S4_PIN_BIT)

#define GEN_BOARD_BUTTON_ALL_MASK_PIN (GEN_BOARD_BUTTON_S1_PIN | GEN_BOARD_BUTTON_S2_PIN | GEN_BOARD_BUTTON_S3_PIN  | GEN_BOARD_BUTTON_S4_PIN)

#define GEN_BOARD_LED_D1_BIT               (16)
#define GEN_BOARD_LED_D2_BIT               (13)
#define GEN_BOARD_LED_D3_BIT               (0)

#define GEN_BOARD_LED_D1_PIN               (1UL << GEN_BOARD_LED_D1_BIT)
#define GEN_BOARD_LED_D2_PIN               (1UL << GEN_BOARD_LED_D2_BIT)
#define GEN_BOARD_LED_D3_PIN               (1UL << GEN_BOARD_LED_D3_BIT)

#define GEN_BOARD_LED_CTRL_MASK            (GEN_BOARD_LED_D1_PIN | GEN_BOARD_LED_D2_PIN | GEN_BOARD_LED_D3_PIN)

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
 * NAME: bPotEnable
 *
 * DESCRIPTION:
 * Enables Potentiometer - configure JN516x IO and ADCs to enable readings
 *
 * RETURNS
 * boot_t, success or failure.
 *
 ****************************************************************************/
PUBLIC bool_t bPotEnable(void)
{
    vAHI_ApConfigure(E_AHI_AP_REGULATOR_ENABLE,E_AHI_AP_INT_DISABLE,E_AHI_AP_SAMPLE_2,E_AHI_AP_CLOCKDIV_500KHZ,E_AHI_AP_INTREF);
#if (defined JENNIC_CHIP_FAMILY_JN514x) || (defined JENNIC_CHIP_FAMILY_JN516x)
    vAHI_AdcEnable(E_AHI_ADC_CONTINUOUS,E_AHI_AP_INPUT_RANGE_1,E_AHI_ADC_SRC_ADC_1);
#else
    vAHI_AdcEnable(E_AHI_ADC_CONTINUOUS,E_AHI_AP_INPUT_RANGE_1,E_AHI_ADC_SRC_ADC0_TEST1);
#endif
    vAHI_AdcStartSample();

    return TRUE;
}



/****************************************************************************
 *
 * NAME: u16ReadPotValue
 *
 * DESCRIPTION:
 * Reads the current potentiometer value
 *
 * RETURNS
 * uint16, value from the ADC.
 *
 ****************************************************************************/
PUBLIC uint16 u16ReadPotValue(void)
{
    return (u16AHI_AdcRead());
}


/****************************************************************************
 *
 * NAME: bPotDisable
 *
 * DESCRIPTION:
 * Diables Potentiometer
 *
 * RETURNS
 * boot_t, success or failure.
 *
 ****************************************************************************/
PUBLIC bool_t bPotDisable(void)
{
   vAHI_AdcDisable();

   return TRUE;
}

/****************************************************************************
 *
 * NAME: vGenericButtonInit
 *
 * DESCRIPTION:
 * Initialises buttons on Generic Expansion Board
 *
 ****************************************************************************/
PUBLIC void vGenericButtonInit(void)
{
    vAHI_DioSetDirection(GEN_BOARD_BUTTON_ALL_MASK_PIN, 0);
}


/****************************************************************************
 *
 * NAME: u8GenericButtonRead
 *
 * DESCRIPTION:
 * Read current state of buttons on generic Expansion Board
 *
 * RETURNS
 * uint8, Bitmap of button state (4 buttons only bottom 4 bits are used)
 *
 ****************************************************************************/
PUBLIC uint8 u8GenericButtonRead(void)
{
    uint32 u32DioPins;
    uint8 u8RetVal = 0;

    u32DioPins = u32AHI_DioReadInput();
    if((u32DioPins & GEN_BOARD_BUTTON_S1_PIN)==0) u8RetVal += GEN_BOARD_BUTTON_S1_VAL;
    if((u32DioPins & GEN_BOARD_BUTTON_S2_PIN)==0) u8RetVal += GEN_BOARD_BUTTON_S2_VAL;
    if((u32DioPins & GEN_BOARD_BUTTON_S3_PIN)==0) u8RetVal += GEN_BOARD_BUTTON_S3_VAL;
    if((u32DioPins & GEN_BOARD_BUTTON_S4_PIN)==0) u8RetVal += GEN_BOARD_BUTTON_S4_VAL;
    return (u8RetVal);
}



/****************************************************************************
 *
 * NAME: vGenericLEDInit
 *
 * DESCRIPTION:
 * Initialises LEDs on Generic Expansion Board
 *
 ****************************************************************************/
PUBLIC void vGenericLEDInit(void)
{
    vAHI_DioSetDirection(0, GEN_BOARD_LED_CTRL_MASK);
}

/****************************************************************************
 *
 * NAME: vGenericLEDSetOutput
 *
 * DESCRIPTION:
 * Set output of LEDs on generic Expansion Board
 *
 * PARAMETERS:      Name         RW  Usage
 *                  u8LEDBitmap  R   Bitmap of LEDs
 *                  bOn          R   Gives new state of those LEDs in the bitmap
 *
 * RETURNS
 * None
 *
 ****************************************************************************/
PUBLIC void vGenericLEDSetOutput(uint8 u8LEDBitmap, bool_t bOn)
{
    if (u8LEDBitmap & GEN_BOARD_LED_D1_VAL)
    {
        if (bOn)
        {
           vAHI_DioSetOutput(GEN_BOARD_LED_D1_PIN,0);
        }
        else
        {
           vAHI_DioSetOutput(0,GEN_BOARD_LED_D1_PIN);
        }
    }
    if (u8LEDBitmap & GEN_BOARD_LED_D2_VAL)
    {
        if (bOn)
        {
           vAHI_DioSetOutput(GEN_BOARD_LED_D2_PIN,0);
        }
        else
        {
           vAHI_DioSetOutput(0,GEN_BOARD_LED_D2_PIN);
        }
    }
    if (u8LEDBitmap & GEN_BOARD_LED_D3_VAL)
    {
        if (bOn)
        {
           vAHI_DioSetOutput(GEN_BOARD_LED_D3_PIN,0);
        }
        else
        {
           vAHI_DioSetOutput(0,GEN_BOARD_LED_D3_PIN);
        }
    }
}


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/


/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
