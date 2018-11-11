/****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
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
 *
 * Copyright NXP B.V. 2016. All rights reserved
 ****************************************************************************/


/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "SerialLink.h"
#include "app_common.h"
#include "AppHardwareApi.h"
#include "dbg.h"
#include "app_ahi_commands.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/


/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE void vAPP_DIOSetDirection(uint16 u16PacketLength, uint8 *pu8LinkRxBuffer, eAHI_Status *peAHIStatus);
PRIVATE void vAPP_DIOSetOutput(uint16 u16PacketLength, uint8 *pu8LinkRxBuffer, eAHI_Status *peAHIStatus);
PRIVATE void vAPP_DIOSetReadInput(uint16 u16PacketLength, uint8 *pu8LinkRxBuffer, eAHI_Status *peAHIStatus);
PRIVATE void vAPP_AHISetTxPower(uint16 u16PacketLength, uint8 *pu8LinkRxBuffer, eAHI_Status *peAHIStatus);
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
 * NAME: APP_vCMDHandleAHICommand
 *
 * DESCRIPTION:
 * The main function that figures out which AHI command is to be executed
 * and passes the data to the correct function.
 *
 *
 ****************************************************************************/
PUBLIC void APP_vCMDHandleAHICommand(uint16 u16PacketType,
                                     uint16 u16PacketLength,
                                     uint8 *pu8LinkRxBuffer,
                                     uint8 *peAHIStatus)
{
	eAHI_Status eAHI_Status;

    switch (u16PacketType)
    {
        case E_SL_MSG_AHI_DIO_SET_DIRECTION:
        {
            vAPP_DIOSetDirection(u16PacketLength, pu8LinkRxBuffer, &eAHI_Status);
            break;
        }
        case E_SL_MSG_AHI_DIO_SET_OUTPUT:
        {
            vAPP_DIOSetOutput(u16PacketLength, pu8LinkRxBuffer, &eAHI_Status);
            break;
        }
        case E_SL_MSG_AHI_DIO_READ_INPUT:
        {
            vAPP_DIOSetReadInput(u16PacketLength, pu8LinkRxBuffer, &eAHI_Status);
            break;
        }

        case E_SL_MSG_AHI_SET_TX_POWER:
        	vAPP_AHISetTxPower(u16PacketLength, pu8LinkRxBuffer, &eAHI_Status);
			break;

        default:
        	eAHI_Status = E_AHI_COMMAND_UNRECOGNISED;
            break;
    }

    *peAHIStatus = eAHI_Status;
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME: vAPP_DIOSetDirection
 *
 * DESCRIPTION:
 * Configures the DIO's to be inputs/outputs depending on the DIO masks passed.
 *
 * Params:
 * @pu8LinkRxBuffer: pointer to the DIO Set Direction message ready to be parsed.
 *
 *
 ****************************************************************************/
PRIVATE void vAPP_DIOSetDirection(uint16 u16PacketLength, uint8 *pu8LinkRxBuffer, eAHI_Status *peAHIStatus)
{
    uint32 u32DioInputPinMask;
    uint32 u32DioOutputPinMask;
    uint32 u32BytesRead = 0;

    *peAHIStatus = E_AHI_PARSE_ERROR;

    DBG_vPrintf(TRUE, "AHI: %s", __FUNCTION__);

    if (8 == u16PacketLength)
    {
        /* Parse the information out */
        u32DioInputPinMask = ZNC_RTN_U32( pu8LinkRxBuffer, u32BytesRead );
        u32BytesRead += sizeof(u32DioInputPinMask);
        u32DioOutputPinMask = ZNC_RTN_U32( pu8LinkRxBuffer, u32BytesRead );

        /* Configure the IPN */
        vAHI_DioSetOutput(u32DioInputPinMask, u32DioOutputPinMask);

        *peAHIStatus = E_AHI_SUCCESS;
    }
}

/****************************************************************************
 *
 * NAME: vAPP_DIOSetOutput
 *
 * DESCRIPTION:
 * Sets the DIOs to on or off depending on the DIO mask passed.
 *
 * Params:
 * @pu8LinkRxBuffer: pointer to the IPN message ready to be parsed.
 *
 *
 ****************************************************************************/
PRIVATE void vAPP_DIOSetOutput(uint16 u16PacketLength, uint8 *pu8LinkRxBuffer, eAHI_Status *peAHIStatus)
{
    uint32 u32DioOnPinMask;
    uint32 u32DioOffPinMask;
    uint32 u32BytesRead = 0;

    *peAHIStatus = E_AHI_PARSE_ERROR;

    DBG_vPrintf(TRUE, "AHI: %s", __FUNCTION__);

    if (8 == u16PacketLength)
    {
        /* Parse the information out */
        u32DioOnPinMask = ZNC_RTN_U32( pu8LinkRxBuffer, u32BytesRead );
        u32BytesRead += sizeof(u32DioOnPinMask);
        u32DioOffPinMask = ZNC_RTN_U32( pu8LinkRxBuffer, u32BytesRead );

        /* Configure the IPN */
        vAHI_DioSetDirection(u32DioOnPinMask, u32DioOffPinMask);

        *peAHIStatus = E_AHI_SUCCESS;
    }
}

/****************************************************************************
 *
 * NAME: vAPP_DIOSetReadInput
 *
 * DESCRIPTION:
 * Command to read the input pins on the DIO.
 *
 * Params:
 * @pu8LinkRxBuffer: pointer to the IPN message ready to be parsed.
 *
 *
 ****************************************************************************/
PRIVATE void vAPP_DIOSetReadInput(uint16 u16PacketLength, uint8 *pu8LinkRxBuffer, eAHI_Status *peAHIStatus)
{
    uint32 u32DioReadInput;
    *peAHIStatus = E_AHI_PARSE_ERROR;

    DBG_vPrintf(TRUE, "AHI: %s", __FUNCTION__);

    if (0 == u16PacketLength)
    {
        /* Read the input state */
        u32DioReadInput = u32AHI_DioReadInput();

        /* Need to figure out how to send this data back as the success needs to be sent first
         * if I send the read input data back now, the status message will return after this
         */
        *peAHIStatus = E_AHI_SUCCESS;
    }
}

/****************************************************************************
 *
 * NAME: vAPP_AHISetTxPower
 *
 * DESCRIPTION:
 * Command to set the Tx Power
 *
 * Params:
 * @pu8LinkRxBuffer: pointer to the message ready to be parsed.
 *
 *
 ****************************************************************************/
PRIVATE void vAPP_AHISetTxPower(uint16 u16PacketLength, uint8 *pu8LinkRxBuffer, eAHI_Status *peAHIStatus)
{
	uint8 u8TxPower;
	uint32 u32BytesRead = 0;
	*peAHIStatus = E_AHI_PARSE_ERROR;

	DBG_vPrintf(TRUE, "AHI: %s", __FUNCTION__);

	if (1 == u16PacketLength)
	{
		u8TxPower = pu8LinkRxBuffer[ u32BytesRead ];
		u32BytesRead += sizeof(u8TxPower);

		eAppApiPlmeSet(PHY_PIB_ATTR_TX_POWER, u8TxPower);
		*peAHIStatus = E_AHI_SUCCESS;
	}
}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
