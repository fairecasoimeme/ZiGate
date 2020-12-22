/****************************************************************************
 *
 * MODULE:             ZGP Response command
 *
 * COMPONENT:          GreenPowerResponse.c
 *
 * AUTHOR:             Ramakrishna
 *
 * DESCRIPTION:        ZGP Response command send and receive functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/GreenPower/Source/GreenPowerResponse.c $
 *
 * $Revision: 74369 $
 *
 * $LastChangedBy: nxp58432 $
 *
 * $LastChangedDate: 2015-11-20 06:42:31 +0100 (Fri, 20 Nov 2015) $
 *
 * $Id: GreenPowerResponse.c 74369 2015-11-20 05:42:31Z nxp58432 $
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
#ifndef GP_DISABLE_ZGP_RESPONSE_CMD
/****************************************************************************
 **
 ** NAME:       eGP_ZgpResponseSend
 **
 ** DESCRIPTION:
 ** Sends ZGP Response command
 **
 ** PARAMETERS:                     Name                           Usage
 ** uint8                           u8SourceEndPointId             Source EP Id
 ** uint8                           u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address                   *psDestinationAddress           Destination Address
 ** uint8                           *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsGP_ZgpResponseCmdPayload      *psZgpResponseCmdPayload        Response Cmd Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC teZCL_Status eGP_ZgpResponseSend(
                    uint8                                  u8SourceEndPointId,
                    uint8                                  u8DestinationEndPointId,
                    tsZCL_Address                          *psDestinationAddress,
                    uint8                                  *pu8TransactionSequenceNumber,
                    tsGP_ZgpResponseCmdPayload             *psZgpResponseCmdPayload)
{
	 uint8  u8ItemsInPayload = 6;
	/* Payload with application id 2 will take an entry more */
    tsZCL_TxPayloadItem asPayloadDefinition[7] = {
            {1,  E_ZCL_BMAP8,    &psZgpResponseCmdPayload->b8Options}, //1
            {1,  E_ZCL_UINT16,   &psZgpResponseCmdPayload->u16TempMasterShortAddr}, //2
            {1,  E_ZCL_BMAP8,    &psZgpResponseCmdPayload->b8TempMasterTxChannel},//3
            {1,  E_ZCL_UINT32,   &psZgpResponseCmdPayload->uZgpdDeviceAddr.u32ZgpdSrcId},//4
            {1,  E_ZCL_UINT8,    &psZgpResponseCmdPayload->eZgpdCmdId},//5
            {1,  E_ZCL_OSTRING,  &psZgpResponseCmdPayload->sZgpdCommandPayload} //6
           };


#ifdef GP_IEEE_ADDR_SUPPORT
    if((psZgpResponseCmdPayload->b8Options & GP_APPLICATION_ID_MASK) == 2)
    {

        asPayloadDefinition[3].eType = E_ZCL_IEEE_ADDR;
        asPayloadDefinition[3].pvData = &psZgpResponseCmdPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u64ZgpdIEEEAddr;

        /* add Endpoint */
        asPayloadDefinition[4].eType = E_ZCL_UINT8;
        asPayloadDefinition[4].pvData = &psZgpResponseCmdPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint;

        asPayloadDefinition[5].eType = E_ZCL_UINT8;
        asPayloadDefinition[5].pvData = &psZgpResponseCmdPayload->eZgpdCmdId;


        asPayloadDefinition[6].eType = E_ZCL_OSTRING;
        asPayloadDefinition[6].pvData = &psZgpResponseCmdPayload->sZgpdCommandPayload;
        asPayloadDefinition[6].u16Quantity = 1;

        u8ItemsInPayload++;
    }
#else
    if((psZgpResponseCmdPayload->b8Options & GP_APPLICATION_ID_MASK) == 2)
    {
        return E_ZCL_ERR_INVALID_VALUE;
    }
#endif


    return eZCL_CustomCommandSend(u8SourceEndPointId,
                              u8DestinationEndPointId,
                              psDestinationAddress,
                              GREENPOWER_CLUSTER_ID,
                              TRUE,
                              E_GP_ZGP_RESPONSE,
                              pu8TransactionSequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              u8ItemsInPayload);

}

/****************************************************************************
 **
 ** NAME:       eGP_ZgpResponseReceive
 **
 ** DESCRIPTION:
 ** Handles ZGP response comamnd
 **
 ** PARAMETERS:                 Name                            Usage
 ** ZPS_tsAfEvent               *pZPSevent                      Zigbee stack event structure
 ** uint16                      u16Offset,                      Offset
 ** tsGP_ZgpResponseCmdPayload  *psZgpResponseCmdPayload        payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eGP_ZgpResponseReceive(
                    ZPS_tsAfEvent                          *pZPSevent,
                    uint16                                 u16Offset,
                    tsGP_ZgpResponseCmdPayload             *psZgpResponseCmdPayload)
{

    uint8 u8TransactionSequenceNumber;
    zbmap8 b8Options;
    uint16 u16ActualQuantity;
	 uint8  u8ItemsInPayload = 6;
    /* Payload with application id 2 will take an entry more */
    tsZCL_RxPayloadItem asPayloadDefinition[7] = {
            {1, &u16ActualQuantity, E_ZCL_BMAP8,    &psZgpResponseCmdPayload->b8Options}, //1
            {1, &u16ActualQuantity, E_ZCL_UINT16,   &psZgpResponseCmdPayload->u16TempMasterShortAddr},//2
            {1, &u16ActualQuantity, E_ZCL_BMAP8,    &psZgpResponseCmdPayload->b8TempMasterTxChannel},//3
            {1, &u16ActualQuantity, E_ZCL_UINT32,   &psZgpResponseCmdPayload->uZgpdDeviceAddr.u32ZgpdSrcId},//4
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psZgpResponseCmdPayload->eZgpdCmdId},//5
            {1, &u16ActualQuantity, E_ZCL_OSTRING,  &psZgpResponseCmdPayload->sZgpdCommandPayload},//6
            {1, &u16ActualQuantity, E_ZCL_OSTRING,  &psZgpResponseCmdPayload->sZgpdCommandPayload},//7 payload not correct. overwritten below
           };
    /* Get options field from payload */
    u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                               u16Offset,
                               E_ZCL_BMAP8,
                               &b8Options);

#ifdef GP_IEEE_ADDR_SUPPORT
    if((b8Options & GP_APPLICATION_ID_MASK) == 2)
    {
        asPayloadDefinition[3].eType = E_ZCL_IEEE_ADDR;
        asPayloadDefinition[3].pvDestination = &psZgpResponseCmdPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u64ZgpdIEEEAddr;

        /* add Endpoint */
        asPayloadDefinition[4].eType = E_ZCL_UINT8;
        asPayloadDefinition[4].pvDestination = &psZgpResponseCmdPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint;

        asPayloadDefinition[5].eType = E_ZCL_UINT8;
        asPayloadDefinition[5].pvDestination = &psZgpResponseCmdPayload->eZgpdCmdId;


        asPayloadDefinition[6].eType = E_ZCL_OSTRING;
        asPayloadDefinition[6].pvDestination = &psZgpResponseCmdPayload->sZgpdCommandPayload;
        asPayloadDefinition[6].u16MaxQuantity = 1;
        u8ItemsInPayload++;
    }
#else
    if((b8Options & GP_APPLICATION_ID_MASK) == 2)
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
