/****************************************************************************
 *
 * MODULE:			SMAC_Uart.h
 *
 * COMPONENT:       SerialMAC
 *
 * REVISION:     	$Revision: 76246 $
 *
 * DATED:			$Date: 2016-01-20 16:05:01 +0000 (Wed, 20 Jan 2016) $
 *
 * AUTHOR:   		$Author: nxp97442 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_Uart.h $
 *
 * DESCRIPTION:		Implements the UART FIFO Serial interface as part of the
 * 					MAC-Host Serial Interface as defined in 802.15.4 MAC
 * 					Serial Interface V1.0 [doc142933]
 * 					2-Wire Mode. No Flow Control. 8 Data Bits. No parity.
 *
 * $Id: SMAC_Uart.h 76246 2016-01-20 16:05:01Z nxp97442 $
 *
 ****************************************************************************
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
 *
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ***************************************************************************/

#ifndef  SMAC_UART_H_INCLUDED
#define  SMAC_UART_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/


#define SMUART_TX_FIFO_SIZE					512ul
#define SMUART_RX_FIFO_SIZE				 	512ul
#define SMUART_RX_FIFO_THRESHOLD			400ul	/* 80% */




/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
/** Enumerated list of supported baud rates */
typedef enum eUF_BR_tag
{
	eBaud1M,
	eBaud9600,
	eBaudDefault
} eSMUart_BR;


typedef struct sUF_Buffer_tag
{
	uint8 *pu8Tx;
	uint8 *pu8Rx;
	uint16 u16TxSize;
	uint16 u16RxSize;

} sSMUart_Fifo;


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
PUBLIC bool bSMUart_FifoOpen(uint8 u8Uart, eSMUart_BR eBR);
PUBLIC void vSMUart_FifoConfigure(uint8 u8Uart, eSMUart_BR eBR);
PUBLIC void	vSMUart_FifoClose(uint8 u8Uart);
PUBLIC bool bSMUart_FifoWriteByte(uint8 u8Uart, uint8 u8Byte);
PUBLIC bool vSMUart_FifoWriteString(uint8 u8Uart, string pszText);
PUBLIC bool bSMUart_FifoRxPending(uint8 u8Uart);
PUBLIC void	vSMUart_FifoRxPurge(uint8 u8Uart);


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* SMAC_UART_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

