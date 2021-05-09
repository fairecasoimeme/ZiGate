/****************************************************************************
 *
 * MODULE:			SMAC_Rpc
 *
 * COMPONENT:       SerialMAC
 *
 * REVISION:     	$Revision: 71478 $
 *
 * DATED:			$Date: 2015-07-31 10:14:58 +0100 (Fri, 31 Jul 2015) $
 *
 * AUTHOR:   		$Author: nxp97442 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_Rpc.h $
 *
 * DESCRIPTION:		Implements the Host/MAC Layer Serial Remote Procedure call
 * 				 	interface as defined in 802.15.4 MAC Serial Interface V1.0 [doc142933]
 *					Allows user to make Remote procedure calls which cause
 *					serial message exchange with remote to pass/return parameters.
 *					And handle indications, confirms, delayed confirms and
 *					responses.
 * $Id: SMAC_Rpc.h 71478 2015-07-31 09:14:58Z nxp97442 $
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

#ifndef  SMAC_RPC_H_INCLUDED
#define  SMAC_RPC_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "SMAC_MsgTypes.h"
#include "SMAC_Protocol.h"


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef bool (*RPC_POST_CALLBACK)(uint8, void *, uint16);


/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define SRPC_MAX_PACKET_SIZE				SP_MAX_PACKET_SIZE

/* RPC Timeouts
 * ------------
 * Give the nature of RPC there is a call and a corresponding return. After
 * making an API call the RPC will wait for a response. In the case of
 * communication errors we set a maxium time to wait (in milliseconds).
 */
#define SRPC_CALL_DEFAULT_TIMEOUT_MS		1000 /* 1000 millisecond RPC timeout */



/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

PUBLIC bool 	bSRPC_Init(	uint8 u8Channel,
							uint8 *pu8Buffer,
							uint16 u16Size,
							RPC_POST_CALLBACK prCallBack);

PUBLIC bool 	bSRPC_Run(uint8 u8Channel);
PUBLIC void 	vSRPC_Close(uint8 u8Channel);

PUBLIC bool		bSRPC_Sync(uint8 u8Channel);

PUBLIC bool 	bSRPC_MakeCall(	uint8 u8Channel,
								uint8 u8RPCIDCall, uint8 u8RPCIDRet,
								void *pvInParam, uint16 u16InLen,
								void *pvOutParam, uint16 *pu16OutLen,
								uint16 u16MaxOutLen);

PUBLIC bool		bSRPC_SendEvent(uint8 u8Channel, uint8 u8RPCId, void *pvParam, uint16 u16ParamLen,  bool bISRDisable);


PUBLIC void		vSRPC_SendInfoMsg(uint8 u8Channel, string pszMsg);
PUBLIC void		vSRPC_SendAPINotSupportedMsg(uint8 u8Channel);


PUBLIC uint32 	vRPC_GetTimeout(void);
PUBLIC void		vRPC_SetTimeout(uint32 u32TimeoutMs);

PUBLIC void 	vRPC_SetErrorCallback(SP_COMMS_ERROR_CALLBACK prCommsError);




#if defined __cplusplus
}
#endif

#endif  /* SMAC_RPC_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

