/****************************************************************************
 *
 * MODULE:             ZGP Pairing Search command
 *
 * COMPONENT:          GreenPowerPairingSearch.c
 *
 * AUTHOR:             Ramakrishna
 *
 * DESCRIPTION:        ZGP pairing search command send and receive functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/GreenPower/Source/GreenPowerPairingSearch.c $
 *
 * $Revision: 72260 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-08-26 09:12:34 +0200 (Wed, 26 Aug 2015) $
 *
 * $Id: GreenPowerPairingSearch.c 72260 2015-08-26 07:12:34Z nxp57621 $
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
#ifndef GP_DISABLE_PAIRING_SEARCH_CMD
/****************************************************************************
 **
 ** NAME:       eGP_ZgpPairingSearchSend
 **
 ** DESCRIPTION:
 ** Sends ZGP pairing search command
 **
 ** PARAMETERS:         Name                           Usage
 ** uint8               u8SourceEndPointId             Source EP Id
 ** uint8               u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address      *psDestinationAddress           Destination Address
 ** uint8              *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsGP_ZgpPairingSearchCmdPayload *psZgpPairingSearchPayload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC teZCL_Status eGP_ZgpPairingSearchSend(
                    uint8                                  u8SourceEndPointId,
                    uint8                                  u8DestinationEndPointId,
                    tsZCL_Address                          *psDestinationAddress,
                    uint8                                  *pu8TransactionSequenceNumber,
                    tsGP_ZgpPairingSearchCmdPayload        *psZgpPairingSearchPayload)
{

    zbmap16 b16Options;
    uint8 u8ItemsInPayload;

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1,  E_ZCL_BMAP16,   &psZgpPairingSearchPayload->b16Options},
            {1,  E_ZCL_UINT32,   &psZgpPairingSearchPayload->uZgpdDeviceAddr.u32ZgpdSrcId},
#ifdef GP_IEEE_ADDR_SUPPORT
            {1,  E_ZCL_UINT8,   &psZgpPairingSearchPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint},
#endif
           };

    /* Get options field from payload */
    b16Options = psZgpPairingSearchPayload->b16Options;

    u8ItemsInPayload = 2; //  mandatory items in command payload
#ifdef GP_IEEE_ADDR_SUPPORT
    if((b16Options & GP_APPLICATION_ID_MASK) == 2)
    {
        asPayloadDefinition[1].eType = E_ZCL_IEEE_ADDR;
        asPayloadDefinition[1].pvData = &psZgpPairingSearchPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u64ZgpdIEEEAddr;
        u8ItemsInPayload++;
    }
#else
    if((b16Options & GP_APPLICATION_ID_MASK) == 2)
    {
        return E_ZCL_ERR_INVALID_VALUE;
    }
#endif

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                              u8DestinationEndPointId,
                              psDestinationAddress,
                              GREENPOWER_CLUSTER_ID,
                              FALSE,
                              E_GP_ZGP_PAIRING_SEARCH,
                              pu8TransactionSequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              u8ItemsInPayload);

}

/****************************************************************************
 **
 ** NAME:       eGP_ZgpPairingSearchReceive
 **
 ** DESCRIPTION:
 ** Handles ZGP Pairing Search comamnd
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent            *pZPSevent                     Zigbee stack event structure
 ** uint16                    u16Offset,                    Offset
 ** tsGP_ZgpPairingSearchCmdPayload *psZgpPairingSearchPayload payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC teZCL_Status eGP_ZgpPairingSearchReceive(
                    ZPS_tsAfEvent                          *pZPSevent,
                    uint16                                 u16Offset,
                    tsGP_ZgpPairingSearchCmdPayload        *psZgpPairingSearchPayload)
{

    uint8 u8TransactionSequenceNumber;
    uint16 u16ActualQuantity;
    zbmap16 b16Options;
    uint8  u8ItemsInPayload;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
            {1, &u16ActualQuantity, E_ZCL_BMAP16,   &psZgpPairingSearchPayload->b16Options},
            {1, &u16ActualQuantity, E_ZCL_UINT32,   &psZgpPairingSearchPayload->uZgpdDeviceAddr.u32ZgpdSrcId},
#ifdef GP_IEEE_ADDR_SUPPORT
            {1, &u16ActualQuantity, E_ZCL_UINT8,   &psZgpPairingSearchPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint},
#endif
           };
    /* Get options field from payload */
    u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                               u16Offset,
                               E_ZCL_BMAP16,
                               &b16Options);

    u8ItemsInPayload = 2; //  mandatory items in command payload
#ifdef GP_IEEE_ADDR_SUPPORT
    if((b16Options & GP_APPLICATION_ID_MASK) == 2)
    {
        asPayloadDefinition[1].eType = E_ZCL_IEEE_ADDR;
        asPayloadDefinition[1].pvDestination = &psZgpPairingSearchPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u64ZgpdIEEEAddr;
        u8ItemsInPayload++;
    }
#else
    if((b16Options & GP_APPLICATION_ID_MASK) == 2)
    {
        return E_ZCL_ERR_INVALID_VALUE;
    }
#endif

    return eZCL_CustomCommandReceive(pZPSevent,
                                 &u8TransactionSequenceNumber,
                                 asPayloadDefinition,
                                 u8ItemsInPayload,
                                 E_ZCL_ACCEPT_EXACT|E_ZCL_DISABLE_DEFAULT_RESPONSE);

}
#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
