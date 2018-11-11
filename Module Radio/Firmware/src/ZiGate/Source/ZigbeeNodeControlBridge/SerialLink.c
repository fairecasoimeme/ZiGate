/****************************************************************************
 *
 * MODULE:             ZigbeeNodeControlBridge
 *
 * COMPONENT:          Serial Link to Host
 *
 * VERSION:
 *
 * REVISION:           $$
 *
 * DATED:              $$
 *
 * STATUS:             $State: Exp $
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:
 *
 *
 * LAST MODIFIED BY:   $Author: nxp29741 $
 *                     $Modtime: $
 *
 ****************************************************************************
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
 *
 ****************************************************************************/

#ifdef DEBUG_SERIAL_LINK
#define DEBUG_SL            TRUE
#else
#define DEBUG_SL            FALSE
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <string.h>
#include <dbg.h>

#include "SerialLink.h"
#include "uart.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/** Enumerated list of states for receive state machine */
typedef enum
{
    E_STATE_RX_WAIT_START,
    E_STATE_RX_WAIT_TYPEMSB,
    E_STATE_RX_WAIT_TYPELSB,
    E_STATE_RX_WAIT_LENMSB,
    E_STATE_RX_WAIT_LENLSB,
    E_STATE_RX_WAIT_CRC,
    E_STATE_RX_WAIT_DATA,
}teSL_RxState;

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

PUBLIC uint8 u8SL_CalculateCRC(uint16 u16Type, uint16 u16Length, uint8 *pu8Data);

PRIVATE void vSL_TxByte(bool bSpecialCharacter, uint8 u8Data);
PRIVATE void vLogInit(void);
PRIVATE void vLogPutch(char c);
PRIVATE void vLogFlush(void);
PRIVATE void vLogAssert(void);
#ifdef CCITT_CRC
PRIVATE uint8 u8CCITT_CRC(uint8 u8CRCIn, uint8 u8Val);
#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

uint8     au8LogBuffer[256];
uint8     u8LogStart = 0;
uint8     u8LogEnd   = 0;
bool_t    bLogging = FALSE;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME: bSL_ReadMessage
 *
 * DESCRIPTION:
 * Attempt to read a complete message from the serial link
 *
 * PARAMETERS  Name                    RW  Usage
 *             pu16Type                W   Location to store incoming message type
 *             pu16Length              W   Location to store incoming message length
 *             u16MaxLength            R   Length of allocated message buffer
 *             pu8Message              W   Location to store message payload
 *
 * RETURNS:
 * TRUE if a complete valid message has been received
 *
 ****************************************************************************/
PUBLIC bool bSL_ReadMessage(uint16 *pu16Type, uint16 *pu16Length, uint16 u16MaxLength, uint8 *pu8Message,uint8 u8Data)
{

    static teSL_RxState eRxState = E_STATE_RX_WAIT_START;
    static uint8 u8CRC;
    static uint16 u16Bytes;
    static bool bInEsc = FALSE;

    switch(u8Data)
    {

        case SL_START_CHAR:
            // Reset state machine
            u16Bytes = 0;
            bInEsc = FALSE;
            DBG_vPrintf(DEBUG_SL, "\nRX Start ");
            eRxState = E_STATE_RX_WAIT_TYPEMSB;
            break;

        case SL_ESC_CHAR:
            // Escape next character
            bInEsc = TRUE;
            break;

        case SL_END_CHAR:
            // End message
            DBG_vPrintf(DEBUG_SL, "\nGot END");
            eRxState = E_STATE_RX_WAIT_START;
            if(*pu16Length < u16MaxLength)
            {
                if(u8CRC == u8SL_CalculateCRC(*pu16Type, *pu16Length, pu8Message))
                {
                    /* CRC matches - valid packet */
                    DBG_vPrintf(DEBUG_SL, "\nbSL_ReadMessage(%d, %d, %02x)", *pu16Type, *pu16Length, u8CRC);
                    return(TRUE);
                }
            }
            DBG_vPrintf(DEBUG_SL, "\nCRC BAD");
            break;

        default:
            if(bInEsc)
            {
                /* Unescape the character */
                u8Data ^= 0x10;
                bInEsc = FALSE;
            }
            DBG_vPrintf(DEBUG_SL, "\nData 0x%x", u8Data & 0xFF);

            switch(eRxState)
            {

            case E_STATE_RX_WAIT_START:
                break;

            case E_STATE_RX_WAIT_TYPEMSB:
                *pu16Type = (uint16)u8Data << 8;
                eRxState++;
                break;

            case E_STATE_RX_WAIT_TYPELSB:
                *pu16Type += (uint16)u8Data;
                DBG_vPrintf(DEBUG_SL, "\nType 0x%x", *pu16Type & 0xFFFF);
                eRxState++;
                break;

            case E_STATE_RX_WAIT_LENMSB:
                *pu16Length = (uint16)u8Data << 8;
                eRxState++;
                break;

            case E_STATE_RX_WAIT_LENLSB:
                *pu16Length += (uint16)u8Data;
                DBG_vPrintf(DEBUG_SL, "\nLength %d", *pu16Length);
                if(*pu16Length > u16MaxLength)
                {
                    DBG_vPrintf(DEBUG_SL, "\nLength > MaxLength");
                    eRxState = E_STATE_RX_WAIT_START;
                }
                else
                {
                    eRxState++;
                }
                break;

            case E_STATE_RX_WAIT_CRC:
                DBG_vPrintf(DEBUG_SL, "\nCRC %02x\n", u8Data);
                u8CRC = u8Data;
                eRxState++;
                break;

            case E_STATE_RX_WAIT_DATA:
                if(u16Bytes < *pu16Length)
                {
                    DBG_vPrintf(DEBUG_SL, "%02x ", u8Data);
                    pu8Message[u16Bytes++] = u8Data;
                }
                break;
            }
            break;
    }
    return(FALSE);
}


/****************************************************************************
 *
 * NAME: vSL_WriteMessage
 *
 * DESCRIPTION:
 * Write message to the serial link
 *
 * PARAMETERS: Name                   RW  Usage
 *             u16Type                R   Message type
 *             u16Length              R   Message length
 *             pu8Data                R   Message payload
 *             u8LinkQuality          R   Message radio quality
 * RETURNS:
 * void
 ****************************************************************************/
PUBLIC void vSL_WriteMessage(uint16 u16Type, uint16 u16Length, uint8 *pu8Data, uint8 u8LinkQuality)
{
    int n;
    uint8 u8CRC;

    u16Length++;

    pu8Data[u16Length-1]=u8LinkQuality;
    u8CRC = u8SL_CalculateCRC(u16Type, u16Length, pu8Data);

    DBG_vPrintf(DEBUG_SL, "\nvSL_WriteMessage(%d, %d, %02x)", u16Type, u16Length, u8CRC);

    /* Send start character */
    vSL_TxByte(TRUE, SL_START_CHAR);

    /* Send message type */
    vSL_TxByte(FALSE, (u16Type >> 8) & 0xff);
    vSL_TxByte(FALSE, (u16Type >> 0) & 0xff);

    /* Send message length */

    vSL_TxByte(FALSE, (u16Length >> 8) & 0xff);
    vSL_TxByte(FALSE, (u16Length >> 0) & 0xff);


    /* Send message checksum */
    vSL_TxByte(FALSE, u8CRC);

    /* Send message payload */
    for(n = 0; n < u16Length; n++)
    {
        vSL_TxByte(FALSE, pu8Data[n]);
    }

    /* Send end character */
    vSL_TxByte(TRUE, SL_END_CHAR);
}


/****************************************************************************
 *
 * NAME: vSL_LogSend
 *
 * DESCRIPTION:
 * Send log messages from the log buffer to the host
 *
 * PARAMETERS: 	Name        		RW  Usage
 *
 * RETURNS:
 * void
 ****************************************************************************/
PUBLIC void vSL_LogSend(void)
{
    int n;
    uint8 u8CRC;
    uint8 u8Length;

    while (u8LogEnd - u8LogStart != 0)
    {
        /* Send start character */
        vSL_TxByte(TRUE, SL_START_CHAR);

        /* Send message type */
        vSL_TxByte(FALSE, (E_SL_MSG_LOG >> 8) & 0xff);
        vSL_TxByte(FALSE, (E_SL_MSG_LOG >> 0) & 0xff);

        u8CRC = ((E_SL_MSG_LOG >> 8) & 0xff) ^ ((E_SL_MSG_LOG >> 0) & 0xff);

        for (u8Length = 0; au8LogBuffer[(u8LogStart + u8Length) & 0xFF] != '\0'; u8Length++)
        {
            u8CRC ^= au8LogBuffer[(u8LogStart + u8Length) & 0xFF];
        }
        u8CRC ^= 0;
        u8CRC ^= u8Length;

        /* Send message length */
        vSL_TxByte(FALSE, 0);
        vSL_TxByte(FALSE, u8Length);

        /* Send message checksum */
        vSL_TxByte(FALSE, u8CRC);

        /* Send message payload */
        for(n = 0; n < u8Length; n++)
        {
            vSL_TxByte(FALSE, au8LogBuffer[u8LogStart]);
            u8LogStart++;
        }
        u8LogStart++;

        /* Send end character */
        vSL_TxByte(TRUE, SL_END_CHAR);
    }
}


/****************************************************************************
 *
 * NAME: vSL_LogFlush
 *
 * DESCRIPTION:
 * Flush any log messages from the outoing queue
 *
 * PARAMETERS: 	Name        		RW  Usage
 *
 * RETURNS:
 * void
 ****************************************************************************/
PUBLIC void vSL_LogFlush(void)
{
    /* Copy log buffer to the UART buffer for transmission */
    /* flush hardware buffer */
    vSL_LogSend();
}


/****************************************************************************
 *
 * NAME: vSL_LogInit
 *
 * DESCRIPTION:
 * Initialise Serial Link logging
 * Set up DBG module to use serial link functions for its output
 *
 * PARAMETERS: 	Name        		RW  Usage
 *
 * RETURNS:
 * void
 ****************************************************************************/
PUBLIC void vSL_LogInit(void)
{
    tsDBG_FunctionTbl sFunctionTbl;

    sFunctionTbl.prInitHardwareCb	= vLogInit;
    sFunctionTbl.prPutchCb			= vLogPutch;
    sFunctionTbl.prFlushCb 			= vLogFlush;
    sFunctionTbl.prFailedAssertCb	= vLogAssert;

    DBG_vInit(&sFunctionTbl);
}


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#ifndef CCITT_CRC
/****************************************************************************
 *
 * NAME: u8SL_CalculateCRC
 *
 * DESCRIPTION:
 * Calculate CRC of packet
 *
 * PARAMETERS: Name                   RW  Usage
 *             u8Type                 R   Message type
 *             u16Length              R   Message length
 *             pu8Data                R   Message payload
 * RETURNS:
 * CRC of packet
 ****************************************************************************/
PUBLIC uint8 u8SL_CalculateCRC(uint16 u16Type, uint16 u16Length, uint8 *pu8Data)
{

    int n;
    uint8 u8CRC;

    u8CRC  = (u16Type   >> 0) & 0xff;
    u8CRC ^= (u16Type   >> 8) & 0xff;
    u8CRC ^= (u16Length >> 0) & 0xff;
    u8CRC ^= (u16Length >> 8) & 0xff;

    for(n = 0; n < u16Length; n++)
    {
        u8CRC ^= pu8Data[n];
    }

    return(u8CRC);
}

#endif

/****************************************************************************
 *
 * NAME: vSL_TxByte
 *
 * DESCRIPTION:
 * Send, escaping if required, a byte to the serial link
 *
 * PARAMETERS: 	Name        		RW  Usage
 *              bSpecialCharacter   R   TRUE if this byte should not be escaped
 *              u8Data              R   Character to send
 *
 * RETURNS:
 * void
 ****************************************************************************/
PRIVATE void vSL_TxByte(bool bSpecialCharacter, uint8 u8Data)
{
    if(!bSpecialCharacter && u8Data < 0x10)
    {
        /* Send escape character and escape byte */
        u8Data ^= 0x10;
        SL_WRITE(SL_ESC_CHAR);
    }
    SL_WRITE(u8Data);
}


/****************************************************************************
 *
 * NAME: vLogInit
 *
 * DESCRIPTION:
 * Callback function for DBG module to initialise output
 *
 * PARAMETERS: 	Name        		RW  Usage
 *
 * RETURNS:
 * void
 ****************************************************************************/
PRIVATE void vLogInit(void)
{

}


/****************************************************************************
 *
 * NAME: vLogPutch
 *
 * DESCRIPTION:
 * Callback function for DBG module to write out characters
 *
 * PARAMETERS: 	Name        		RW  Usage
 *
 * RETURNS:
 * void
 ****************************************************************************/
PRIVATE void vLogPutch(char c)
{
    if (!bLogging)
    {
        /* Handle first character being the log level */
        if (c < 7)
        {
            /* Ensure log level is LOG_INFO or higher */
            au8LogBuffer[u8LogEnd] = c;
        }
        else
        {
            au8LogBuffer[u8LogEnd] = 6;
        }
        u8LogEnd++;
    }

    if (c >= 0x20 && c < 0x7F)
    {
        /* Add ASCII characters to the output buffer */
        au8LogBuffer[u8LogEnd] = c;
        u8LogEnd++;
    }

    bLogging = TRUE;
}


/****************************************************************************
 *
 * NAME: vLogFlush
 *
 * DESCRIPTION:
 * Callback function for DBG module to flush output buffer - used to terminate
 * an entry in the logbuffer
 *
 * PARAMETERS: 	Name        		RW  Usage
 *
 * RETURNS:
 * void
 ****************************************************************************/
PRIVATE void vLogFlush(void)
{
    au8LogBuffer[u8LogEnd] = '\0';
    u8LogEnd++;
    bLogging = FALSE;
    vSL_LogSend();
}


/****************************************************************************
 *
 * NAME: vLogAssert
 *
 * DESCRIPTION:
 * Callback function for DBG module to assert - not used
 *
 * PARAMETERS: 	Name        		RW  Usage
 *
 * RETURNS:
 * void
 ****************************************************************************/
PRIVATE void vLogAssert(void)
{

}


#ifdef CCITT_CRC
/****************************************************************************
 *
 * NAME: u8CCITT_CRC
 *
 * DESCRIPTION:
 * Calculate CCITT CRC8 of the supplied data.
 * Polynomial: x^8 + x^2 + x + 1 (0x07).
 *
 * CRC Calculation. Polynomial =  x^8 + x^2 + x + 1. Initial Value = 00, Terms = 8
 *
 * Example
 * -------
 * Val = 0x11, CRC = 0x77
 * Val = 0x22, CRC = 0xac
 * Val = 0x33, CRC = 0xd4
 * Val = 0x44, CRC = 0xf9
 * Val = 0x55, CRC = 0x4d
 * Val = 0x66, CRC = 0xd1
 * Val = 0x77, CRC = 0x7b
 * Val = 0x88, CRC = 0xd7 (Calculated result)
 *
 * PARAMETERS: Name                   RW  Usage
 *             u8CRCIn                R   Seed
 *             u8Val              	  R   Value to apply CRC polynomial to
 * RETURNS:
 * CCITT CRC8
 *
 * NOTES:
 *
 ****************************************************************************/
PRIVATE uint8 u8CCITT_CRC(uint8 u8CRCIn, uint8 u8Val)
{
	uint8 i=8;							/* test all 8 bits */
	uint8 u8CRCOut = u8CRCIn ^ u8Val;	/* x^8 is set */

	while(i--)
	{
		if(u8CRCOut & 0x80)				/* test next bit */
		{
			u8CRCOut <<= 1;
			u8CRCOut ^= 0x07; 			/* add polynomial x^2 x^1 x^0 */
		}
		else
		{								/* don't add polynomial */
			u8CRCOut <<=1 ;
		}
	}
	return u8CRCOut;
}

/****************************************************************************
 *
 * NAME: u8SL_CalculateCRC
 *
 * DESCRIPTION:
 * Calculate CRC of packet. Includes Length, Type then Data.
 *
 * PARAMETERS: Name                  RW  Usage
 *             u8Length              R   Message length
 *             u8Type                R   Message type
 *             pu8Data               R   Message payload
 * RETURNS:
 * CRC of packet
 ****************************************************************************/
PUBLIC uint8 u8SL_CalculateCRC(uint16 u16Type, uint16 u16Length,  uint8 *pu8Data)
{
    uint16 n;
    uint8 u8CRC=0;

    u8CRC = 0;		/* 	seed with zero */
    u8CRC  = u8CCITT_CRC(u8CRC, ((u16Type   >> 0) & 0xff));
    u8CRC  = u8CCITT_CRC(u8CRC, ((u16Type   >> 8) & 0xff));
    u8CRC  = u8CCITT_CRC(u8CRC, ((u16Length >> 0) & 0xff));
    u8CRC  = u8CCITT_CRC(u8CRC, ((u16Length >> 8) & 0xff));

    for(n = 0; n < u16Length; n++)
    {
        u8CRC = u8CCITT_CRC(u8CRC, pu8Data[n]);
    }
    return u8CRC;
}


#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

