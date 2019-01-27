/****************************************************************************
 *
 * MODULE:			SMAC_Protocol.h
 *
 * COMPONENT:       SerialMAC
 *
 * REVISION:     	$Revision: 69515 $
 *
 * DATED:			$Date: 2015-05-06 13:00:33 +0100 (Wed, 06 May 2015) $
 *
 * AUTHOR:   		$Author: nxp97442 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_Protocol.h $
 *
 * DESCRIPTION:		Implements the MAC-Host Serial protocol as defined
 * 					in 802.15.4 Serial MAC Interface V1.0 [doc142933]
 *
 * $Id: SMAC_Protocol.h 69515 2015-05-06 12:00:33Z nxp97442 $
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

#ifndef  SMAC_PROTOCOL_H_INCLUDED
#define  SMAC_PROTOCOL_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "SMAC_MsgTypes.h"

#define DEBUG_SERIALPROT	1

#if DEBUG_SERIALPROT
#define DEBUG_SP            TRUE
#else
#define DEBUG_SP            FALSE
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define SP_MAX_PACKET_SIZE				255
#define SP_MAX_DEBUG_STRING				64
#define SP_SYNC_TIMEOUT_MS				2000


#define SP_COMMS_ERROR_NONE				0
#define SP_COMMS_ERROR_CRC				1
#define SP_COMMS_ERROR_PARITY			2
#define SP_COMMS_ERROR_FRAMING			3




/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef void (*SP_COMMS_ERROR_CALLBACK)(uint32);

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

PUBLIC void vSP_SetCommsErrorCallback(SP_COMMS_ERROR_CALLBACK prCommsError);
PUBLIC bool bSP_Sync(uint8 u8Channel);
PUBLIC bool bSP_ProcessIncoming(uint8 u8Channel, uint8 *pu8Type, uint8 *pu8Payload, uint16 *pu16Length, uint16 u16MaxLength);
PUBLIC bool bSP_WriteMessage(uint8 u8Channel, uint8 u8Type, uint8 *pu8Data, uint8 u8Length);
PUBLIC void vSP_Trace(uint8 u8Channel, string pszMessage);
PUBLIC void vSP_Traceu32Val(uint8 u8Channel, string pszMessage, uint32 u32Data);


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* SMAC_PROTOCOL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

