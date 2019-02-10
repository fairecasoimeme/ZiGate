/****************************************************************************
 *
 * MODULE:             ZGP Proxy Table response command send and receive functions
 *
 * COMPONENT:          GreenPowerProxyTableResponse.c
 *
 * AUTHOR:             Rajeena
 *
 * DESCRIPTION:        Proxy table response send and receive functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/GreenPower/Source/GreenPowerProxyCommissioningMode.c $
 *
 * $Revision: 72601 $
 *
 * $LastChangedBy: nxp58432 $
 *
 * $LastChangedDate: 2015-09-09 12:21:44 +0530 (Wed, 09 Sep 2015) $
 *
 * $Id: GreenPowerProxyCommissioningMode.c 72601 2015-09-09 06:51:44Z nxp58432 $
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5164,
 * JN5161, JN5148, JN5142, JN5139].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each  copy or partial copy of the software.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "GreenPower.h"
#include "GreenPower_internal.h"
#include "dbg.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef TRACE_GP_DEBUG
#define TRACE_GP_DEBUG FALSE
#endif
#define OFFSET_PROXYTABLE_ENTRY               (4)
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
/***        Public Functions                                              ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eGP_ProxyTableResponseSend
 **
 ** DESCRIPTION:
 ** Sends Proxy Table request command
 **
 ** PARAMETERS:         Name                           Usage
 ** uint8               u8SourceEndPointId             Source EP Id
 ** uint8               u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address      *psDestinationAddress           Destination Address
 ** uint8              *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsGP_ProxyTableRespCmdPayload  *psZgpProxyTableRespCmdPayload  command payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eGP_ProxyTableResponseSend(
                        uint8                               u8SourceEndPointId,
                        uint8                               u8DestEndPointId,
                        tsZCL_Address                       *psDestinationAddress,
                        tsGP_ProxyTableRespCmdPayload  *psZgpProxyTableRespCmdPayload)
{

    uint8 u8TransactionSequenceNumber;
    tsZCL_TxPayloadItem asPayloadDefinition[] = {
     {1,  E_ZCL_ENUM8,   &psZgpProxyTableRespCmdPayload->u8Status},
     {1,  E_ZCL_UINT8,   &psZgpProxyTableRespCmdPayload->u8TotalNoOfEntries},
     {1,  E_ZCL_UINT8,   &psZgpProxyTableRespCmdPayload->u8StartIndex},
     {1,  E_ZCL_UINT8,   &psZgpProxyTableRespCmdPayload->u8EntriesCount},
     {psZgpProxyTableRespCmdPayload->u16SizeOfProxyTableEntries,  E_ZCL_UINT8,   psZgpProxyTableRespCmdPayload->puProxyTableEntries}
    };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
    						  u8DestEndPointId,
    						  psDestinationAddress,
                              GREENPOWER_CLUSTER_ID,
                              FALSE,
                              E_GP_ZGP_PROXY_TABLE_RESPONSE,
                              &u8TransactionSequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              (sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem)));

}



/****************************************************************************
 **
 ** NAME:       eGP_ProxyTableResponseReceive
 **
 ** DESCRIPTION:
 ** Handles ProxyTable Response command
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent            *pZPSevent                     Zigbee stack event structure
 ** tsGP_ZgpProxyCommissioningModeCmdPayload *psZgpProxyCommissioningModeCmdPayload  command payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC teZCL_Status eGP_ProxyTableResponseReceive(
                    ZPS_tsAfEvent                               *pZPSevent,
                    uint16										u16Offset,
                    tsGP_ProxyTableRespCmdPayload                *psZgpProxyTableRespCmdPayload)
{

    uint8 u8TransactionSequenceNumber;
    uint16 u16ActualQuantity;
    uint16 u16ProxyTableLen = 0;
    uint8 u8NoOfItems= 4;
    u16ProxyTableLen = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);
    DBG_vPrintf(TRACE_GP_DEBUG, "\n u16ProxyTableLen 1 =%d\n", u16ProxyTableLen);
    if(u16ProxyTableLen > MAX_PROXY_TABLE_ENTRIES_LENGTH )
    {
    	return E_ZCL_ERR_INSUFFICIENT_SPACE;
    }
    /* */
    if(u16ProxyTableLen < (u16Offset + OFFSET_PROXYTABLE_ENTRY))
    {
    	return E_ZCL_ERR_MALFORMED_MESSAGE;
    }
    u16ProxyTableLen -= u16Offset;
    u16ProxyTableLen -= OFFSET_PROXYTABLE_ENTRY; // subtract length of sink table response till sink table entry offset
    {
		tsZCL_RxPayloadItem asPayloadDefinition[5] = {
		 {1,  &u16ActualQuantity,E_ZCL_ENUM8,   &psZgpProxyTableRespCmdPayload->u8Status},
		 {1,  &u16ActualQuantity,E_ZCL_UINT8,   &psZgpProxyTableRespCmdPayload->u8TotalNoOfEntries},
		 {1,  &u16ActualQuantity,E_ZCL_UINT8,   &psZgpProxyTableRespCmdPayload->u8StartIndex},
		 {1,  &u16ActualQuantity,E_ZCL_UINT8,   &psZgpProxyTableRespCmdPayload->u8EntriesCount},
		 {u16ProxyTableLen, &u16ActualQuantity, E_ZCL_UINT8,   psZgpProxyTableRespCmdPayload->puProxyTableEntries}
		};
		if(u16ProxyTableLen > 0)
		{
			u8NoOfItems++;
		}
		DBG_vPrintf(TRACE_GP_DEBUG, "\n u16ProxyTableLen =%d\n", u16ProxyTableLen);
		return eZCL_CustomCommandReceive(pZPSevent,
								  &u8TransactionSequenceNumber,
								  asPayloadDefinition,
								  u8NoOfItems,
								  E_ZCL_ACCEPT_EXACT|E_ZCL_DISABLE_DEFAULT_RESPONSE);
    }


}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
