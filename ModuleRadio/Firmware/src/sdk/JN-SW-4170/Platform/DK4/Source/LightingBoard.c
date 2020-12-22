/****************************************************************************
 *
 * MODULE:             Demo board led controls
 *
 * DESCRIPTION:
 * Functions to make it easier to set Leds on the Lighting Expansion Board
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
#include <PCA9634.h>
#include "AppHardwareApi.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define RGB_RED_CHANNEL   2
#define RGB_GREEN_CHANNEL 1
#define RGB_BLUE_CHANNEL  0

#ifdef JENNIC_CHIP_FAMILY_JN516x
#define WHITE_LED_TIMER          E_AHI_TIMER_3
#else
#define WHITE_LED_TIMER          E_AHI_TIMER_1
#endif
#define PWM_COUNT                255
#define WHITE_LED_TIMER_PRESCALE 4


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
uint8 u8SetBlueLEDLevel, u8SetRedLEDLevel, u8SetGreenLEDLevel;
uint16 gu16PwmLastValue;
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME: bRGB_LED_Enable
 *
 * DESCRIPTION:
 * Enables JN516x DIO and NXP PCA9634 LED driver Chip
 *
 * PARAMETERS:      Name            RW  Usage
 *                  NONE
 *
 * RETURNS:			Boolean value indicates successful enable
 ****************************************************************************/
PUBLIC bool_t bRGB_LED_Enable(void)
{
    u8SetRedLEDLevel = 0;
	u8SetBlueLEDLevel = 0;
	u8SetGreenLEDLevel = 0;
	return bPCA9634_Init();
}


/****************************************************************************
 *
 * NAME: bRGB_LED_Disable
 *
 * DESCRIPTION:
 * Disables JN516x DIO and NXP PCA9634 LED driver Chip
 *
 * PARAMETERS:      Name            RW  Usage
 *                  NONE
 *
 * RETURNS:			Boolean value indicates successful disable
 ****************************************************************************/
PUBLIC bool_t bRGB_LED_Disable(void)
{
	return TRUE;
}


/****************************************************************************
 *
 * NAME: bRGB_LED_SetLevel
 *
 * DESCRIPTION:
 * Sets level of RGB LEDs
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8RedLevel		R	Level of RED LED
 *                  u8GreenLevel    R   Level of Green LED
 *                  u8BlueLevel     R   Level of Blue LED
 *
 * RETURNS:			Boolean value indicates successful change in LED level
 ****************************************************************************/
PUBLIC bool_t bRGB_LED_SetLevel(uint8 u8RedLevel, uint8 u8GreenLevel, uint8 u8BlueLevel)
{
	bool_t bROK, bGOK, bBOK;

	bROK = bPCA9634_SetChannelLevel(RGB_RED_CHANNEL, u8RedLevel);
	bGOK = bPCA9634_SetChannelLevel(RGB_GREEN_CHANNEL, u8GreenLevel);
	bBOK = bPCA9634_SetChannelLevel(RGB_BLUE_CHANNEL, u8BlueLevel);
	
	u8SetRedLEDLevel   =  u8RedLevel;
	u8SetBlueLEDLevel  =  u8BlueLevel;
	u8SetGreenLEDLevel =  u8GreenLevel;
	return (bROK && bGOK && bBOK);
}



/****************************************************************************
 *
 * NAME: bRGB_LED_SetGroupLevel
 *
 * DESCRIPTION:
 * Sets level of RGB LEDs
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Level         R   0-255
 *                  
 *
 * RETURNS: bool_t:	TRUE if the function completed successfully
 *			FALSE if there was an error
 ****************************************************************************/
PUBLIC bool_t bRGB_LED_SetGroupLevel(uint8 u8Level)
{
   return bPCA9634_SetGroupLevel(u8Level);
}



/****************************************************************************
 *
 * NAME: bRGB_LED_On
 *
 * DESCRIPTION:
 * Turns RGB LED on values at previous state
 *
 * PARAMETERS:      Name            RW  Usage
 *                  None
 *
 * RETURNS:			Boolean value indicates successful 
 ****************************************************************************/
PUBLIC bool_t bRGB_LED_On(void)
{
	return bRGB_LED_SetLevel(u8SetRedLEDLevel,u8SetGreenLEDLevel,u8SetBlueLEDLevel);
}



/****************************************************************************
 *
 * NAME: bRGB_LED_Off
 *
 * DESCRIPTION:
 * Turns RGB LED off
 *
 * PARAMETERS:      Name            RW  Usage
 *                  None
 *
 * RETURNS:			Boolean value indicates successful 
 ****************************************************************************/
PUBLIC bool_t bRGB_LED_Off(void)
{
	bool_t bROK, bGOK, bBOK;

	bROK = bPCA9634_SetChannelLevel(RGB_RED_CHANNEL, 0);
	bGOK = bPCA9634_SetChannelLevel(RGB_GREEN_CHANNEL, 0);
	bBOK = bPCA9634_SetChannelLevel(RGB_BLUE_CHANNEL, 0);

	return (bROK && bGOK && bBOK);
}


/****************************************************************************
 *
 * NAME: bWhite_LED_Enable
 *
 * DESCRIPTION:
 * Enables White LED
 *
 * PARAMETERS:      Name            RW  Usage
 *                  None
 *
 * RETURNS:			Boolean value indicates successful 
 ****************************************************************************/
PUBLIC bool_t bWhite_LED_Enable(void)
{
  /* Configure timer 0 to generate a PWM output on its output pin */
  vAHI_TimerEnable(WHITE_LED_TIMER, WHITE_LED_TIMER_PRESCALE, FALSE, FALSE, TRUE);
  vAHI_TimerConfigureOutputs(WHITE_LED_TIMER, FALSE, TRUE);
  vAHI_TimerClockSelect(WHITE_LED_TIMER, FALSE, TRUE);

  return TRUE;
}



/****************************************************************************
 *
 * NAME: bWhite_LED_Disable
 *
 * DESCRIPTION:
 * Diables White LED
 *
 * PARAMETERS:      Name            RW  Usage
 *                  None
 *
 * RETURNS:			Boolean value indicates successful 
 ****************************************************************************/
PUBLIC bool_t bWhite_LED_Disable(void)
{
	 vAHI_TimerDisable(WHITE_LED_TIMER);
	return TRUE;
}



/****************************************************************************
 *
 * NAME: bWhite_LED_SetLevel
 *
 * DESCRIPTION:
 * Sets brightness level of white led
 *
 * PARAMETERS:      Name               RW   Usage
 *                  u8BrightnessLevel  R    0-255
 *
 * RETURNS:			Boolean value indicates successful 
 ****************************************************************************/
PUBLIC bool_t bWhite_LED_SetLevel(uint8 u8BrightnessLevel)
{
	vAHI_TimerStartRepeat(WHITE_LED_TIMER, (PWM_COUNT-u8BrightnessLevel), PWM_COUNT );
    gu16PwmLastValue = PWM_COUNT-u8BrightnessLevel;

	return TRUE;
}


/****************************************************************************
 *
 * NAME: bWhite_LED_On
 *
 * DESCRIPTION:
 * Turns White LED on at previouslt set brightness level
 *
 * PARAMETERS:      Name               RW   Usage
 *
 * RETURNS:			Boolean value indicates successful 
 ****************************************************************************/
PUBLIC bool_t bWhite_LED_On(void)
{
	vAHI_TimerStartRepeat(WHITE_LED_TIMER, gu16PwmLastValue , PWM_COUNT );
	return TRUE;
}


/****************************************************************************
 *
 * NAME: bWhite_LED_Off
 *
 * DESCRIPTION:
 * Turns White LED off, brightness level is stored
 *
 * PARAMETERS:      Name               RW   Usage
 *
 * RETURNS:			Boolean value indicates successful 
 ****************************************************************************/
PUBLIC bool_t bWhite_LED_Off(void)
{
	vAHI_TimerStartRepeat(WHITE_LED_TIMER, PWM_COUNT, PWM_COUNT );
	return TRUE;
}



/****************************************************************************
 *
 * NAME:            vUpdateDriverState
 *
 * DESCRIPTION:     Sequences the off-bleeder-on control logic
 *
 * PARAMETERS:      Name         RW  Usage
 *                  eDriverEvent R   Internal Driver Events
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
//
//PRIVATE void vUpdateDriverState(teDriverEvents eDriverEvent)
//{
//    static teDriverStates eDriverState = E_STATE_LAMP_OFF;
//
//    switch (eDriverState)
//    {
//        case E_STATE_LAMP_OFF:
//            if (eDriverEvent == E_EVENT_ON)
//            {
//                eDriverState = E_STATE_LAMP_ON;
//                vAHI_TimerStartRepeat(LAMP_TIMER, 0, PWM_COUNT );
//                bIsOn=TRUE;
//            }
//            break;
//
//        case    E_STATE_LAMP_ON:
//           if (eDriverEvent == E_EVENT_OFF)
//           {
//               eDriverState = E_STATE_LAMP_OFF;
//               vAHI_TimerStartRepeat(LAMP_TIMER, PWM_COUNT, PWM_COUNT );
//               bIsOn = FALSE;
//           }
//           break;
//
//        default : break;
//   }
//}


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/


/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
