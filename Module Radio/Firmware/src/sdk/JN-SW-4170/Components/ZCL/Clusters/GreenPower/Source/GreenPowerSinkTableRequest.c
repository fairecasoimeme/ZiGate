/****************************************************************************
 *
 * MODULE:             ZGP Sink Table Request command send and receive functions
 *
 * COMPONENT:          GreenPowerSinkTableRequest.c
 *
 * AUTHOR:             Rajeena
 *
 * DESCRIPTION:        Sink table request send and receive functions
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

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define APP_ID_MASK_SINK_TABLE_REQ               (7)
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
 ** NAME:       eGP_SinkTableRequestSend
 **
 ** DESCRIPTION:
 ** Sends Sink Table request command
 **
 ** PARAMETERS:         Name                           Usage
 ** uint8               u8SourceEndPointId             Source EP Id
 ** uint8               u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address      *psDestinationAddress           Destination Address
 ** uint8              *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsGP_ZgpProxyCommissioningModeCmdPayload  *psZgpProxyCommissioningModeCmdPayload  command payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eGP_SinkTableRequestSend(
                        uint8                               u8SourceEndPointId,
                        uint8                               u8DestEndPointId,
                        tsZCL_Address                       sDestinationAddress,
                        tsGP_ZgpSinkTableRequestCmdPayload  *psZgpSinkTableRequestCmdPayload)
{

    zbmap8 b8Options;
    uint8 u8ItemsInPayload = 2;
    uint8 u8TransactionSequenceNumber;
    tsZCL_TxPayloadItem asPayloadDefinition[4] = { //size included for app id 2
     {1,  E_ZCL_BMAP8,   &psZgpSinkTableRequestCmdPayload->b8Options},
     {1,  E_ZCL_UINT32,  &psZgpSinkTableRequestCmdPayload->uZgpdDeviceAddr.u32ZgpdSrcId},
     {1,  E_ZCL_UINT8,  &psZgpSinkTableRequestCmdPayload->u8Index},
     {1,  E_ZCL_UINT8,  &psZgpSinkTableRequestCmdPayload->u8Index},

    };


    b8Options = psZgpSinkTableRequestCmdPayload->b8Options;

    if(( b8Options & APP_ID_MASK_SINK_TABLE_REQ) == GP_APPL_ID_8_BYTE)
    {
    	u8ItemsInPayload += 1;
    	asPayloadDefinition[1].eType = E_ZCL_UINT64;
		asPayloadDefinition[1].pvData = &psZgpSinkTableRequestCmdPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u64ZgpdIEEEAddr;
		asPayloadDefinition[2].eType = E_ZCL_UINT8;
		asPayloadDefinition[2].pvData = &psZgpSinkTableRequestCmdPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint;
		asPayloadDefinition[3].eType = E_ZCL_UINT8;
		asPayloadDefinition[3].pvData = &psZgpSinkTableRequestCmdPayload->u8Index;
    }
    if(b8Options & BIT_MAP_REQUEST_TYPE)
    {
    	u8ItemsInPayload = 2;
    	asPayloadDefinition[1].eType = E_ZCL_UINT8;
		asPayloadDefinition[1].pvData = &psZgpSinkTableRequestCmdPayload->u8Index;
    }
    return eZCL_CustomCommandSend(u8SourceEndPointId,
    						  u8DestEndPointId,
                              &sDestinationAddress,
                              GREENPOWER_CLUSTER_ID,
                              FALSE,
                              E_GP_ZGP_SINK_TABLE_REQUEST,
                              &u8TransactionSequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              u8ItemsInPayload);

}



/****************************************************************************
 **
 ** NAME:       eGP_SinkTableResponseReceive
 **
 ** DESCRIPTION:
 ** Handles SinkTable Response command
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent            *pZPSevent                     Zigbee stack event structure
 ** tsGP_ZgpProxyCommissioningModeCmdPayload *psZgpProxyCommissioningModeCmdPayload  command payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC teZCL_Status eGP_SinkTableRequestReceive(
                    ZPS_tsAfEvent                               *pZPSevent,
                    uint16                                      u16Offset,
                    tsGP_ZgpSinkTableRequestCmdPayload          *psZgpSinkTableRequestCmdPayload)
{

    uint8 u8TransactionSequenceNumber;
    uint16 u16ActualQuantity;
    zbmap8 b8Options;
    uint8 u8ItemsInPayload = 2;

    tsZCL_RxPayloadItem asPayloadDefinition[4] = { //maximum size considered
     {1, &u16ActualQuantity, E_ZCL_BMAP8,    &psZgpSinkTableRequestCmdPayload->b8Options},
     {1, &u16ActualQuantity, E_ZCL_UINT32,   &psZgpSinkTableRequestCmdPayload->uZgpdDeviceAddr.u32ZgpdSrcId},
     {1, &u16ActualQuantity, E_ZCL_UINT8,   &psZgpSinkTableRequestCmdPayload->u8Index},
     {1, &u16ActualQuantity, E_ZCL_UINT8,   &psZgpSinkTableRequestCmdPayload->u8Index}
    };
    /* Read Options field from received command */
    u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                               u16Offset,
                               E_ZCL_BMAP8,
                               &b8Options);


    if(( b8Options & APP_ID_MASK_SINK_TABLE_REQ) == GP_APPL_ID_8_BYTE)
    {
		u8ItemsInPayload += 1;
		asPayloadDefinition[1].eType = E_ZCL_UINT64;
		asPayloadDefinition[1].pvDestination = &psZgpSinkTableRequestCmdPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u64ZgpdIEEEAddr;
		asPayloadDefinition[2].eType = E_ZCL_UINT8;
		asPayloadDefinition[2].pvDestination = &psZgpSinkTableRequestCmdPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint;
		asPayloadDefinition[3].eType = E_ZCL_UINT8;
		asPayloadDefinition[3].pvDestination = &psZgpSinkTableRequestCmdPayload->u8Index;

    }
    if(b8Options & BIT_MAP_REQUEST_TYPE)
    {
    	u8ItemsInPayload = 2;
    	asPayloadDefinition[1].eType = E_ZCL_UINT8;
		asPayloadDefinition[1].pvDestination = &psZgpSinkTableRequestCmdPayload->u8Index;
    }
    return eZCL_CustomCommandReceive(pZPSevent,
                              &u8TransactionSequenceNumber,
                              asPayloadDefinition,
                              u8ItemsInPayload,
                              E_ZCL_ACCEPT_EXACT|E_ZCL_DISABLE_DEFAULT_RESPONSE);


}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
