/*****************************************************************************
 *
 * MODULE:             Over The Air Upgrade
 *
 * COMPONENT:          OTA_server.c
 *
 * AUTHOR:             Faisal Bhaiyat
 *
 * DESCRIPTION:        Over The Air Upgrade
 *
 * $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Clusters/OTA/Source/OTA_server.c $
 *
 * $Revision:  $
 *
 * $LastChangedBy: fbhai $
 *
 * $LastChangedDate: $
 *
 * $Id: ota_client.c  $
 *
 *****************************************************************************
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
#include "OTA.h"
#include "zcl_options.h"
#include "OTA_private.h"

#ifdef OTA_SERVER
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
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eOTA_ServerImageNotify
 **
 ** DESCRIPTION:
 ** sends image notify command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                     u8SourceEndPointId            Source EP Id
 ** uint8                     u8DestinationEndPointId       Destination EP Id
 ** tsZCL_Address            *psDestinationAddress          Destination Address
 ** tsOTA_ImageNotifyCommand *psImageNotifyCommand          command payload
 **
 ** RETURN:
 ** teZCL_Status
 ****************************************************************************/
PUBLIC  teZCL_Status eOTA_ServerImageNotify(
                    uint8                     u8SourceEndpoint,
                    uint8                     u8DestinationEndpoint,
                    tsZCL_Address            *psDestinationAddress,
                    tsOTA_ImageNotifyCommand *psImageNotifyCommand)
{
    teZCL_Status eZCL_Status;
    tsZCL_ClusterInstance *psClusterInstance;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsOTA_Common *psCustomData;
    uint8 u8SequenceNumber;
    if((eZCL_Status =
        eOtaFindCluster(u8SourceEndpoint,
                         &psEndPointDefinition,
                           &psClusterInstance,
                           &psCustomData,
                           TRUE))
                           == E_ZCL_SUCCESS)
    {
        if (!psClusterInstance->bIsServer)
        {
            eZCL_Status = E_ZCL_FAIL;
        }
        else
        {
            if(!OTA_IS_UNICAST(psDestinationAddress->eAddressMode,psDestinationAddress->uAddress.u16DestinationAddress))
            {
                psEndPointDefinition->bDisableDefaultResponse = TRUE;
            }
            if(psImageNotifyCommand->ePayloadType <= E_CLD_OTA_ITYPE_MDID_FVERSION_JITTER)
            {
                if(E_CLD_OTA_ITYPE_MDID_FVERSION_JITTER == psImageNotifyCommand->ePayloadType)
                {
                    tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT8,   &psImageNotifyCommand->ePayloadType},
                                                                {1, E_ZCL_UINT8,   &psImageNotifyCommand->u8QueryJitter},
                                                                {1, E_ZCL_UINT16,   &psImageNotifyCommand->u16ManufacturerCode},
                                                                {1, E_ZCL_UINT16,   &psImageNotifyCommand->u16ImageType},
                                                                {1, E_ZCL_UINT32,   &psImageNotifyCommand->u32NewFileVersion}
                                                };
                    eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                              u8DestinationEndpoint,
                              psDestinationAddress,
                              OTA_CLUSTER_ID,
                              TRUE,
                              E_CLD_OTA_COMMAND_IMAGE_NOTIFY,
                              &u8SequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
                }

                if(E_CLD_OTA_ITYPE_MDID_JITTER == psImageNotifyCommand->ePayloadType)
                {
                    tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT8,   &psImageNotifyCommand->ePayloadType},
                                                                {1, E_ZCL_UINT8,   &psImageNotifyCommand->u8QueryJitter},
                                                                {1, E_ZCL_UINT16,   &psImageNotifyCommand->u16ManufacturerCode},
                                                                {1, E_ZCL_UINT16,   &psImageNotifyCommand->u16ImageType}
                                                };
                    eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                              u8DestinationEndpoint,
                              psDestinationAddress,
                              OTA_CLUSTER_ID,
                              TRUE,
                              E_CLD_OTA_COMMAND_IMAGE_NOTIFY,
                              &u8SequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
                }

                if(E_CLD_OTA_MANUFACTURER_ID_AND_JITTER == psImageNotifyCommand->ePayloadType)
                {
                    tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT8,   &psImageNotifyCommand->ePayloadType},
                                                                {1, E_ZCL_UINT8,   &psImageNotifyCommand->u8QueryJitter},
                                                                {1, E_ZCL_UINT16,   &psImageNotifyCommand->u16ManufacturerCode},

                                                };
                    eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                              u8DestinationEndpoint,
                              psDestinationAddress,
                              OTA_CLUSTER_ID,
                              TRUE,
                              E_CLD_OTA_COMMAND_IMAGE_NOTIFY,
                              &u8SequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
                }

                if(E_CLD_OTA_QUERY_JITTER == psImageNotifyCommand->ePayloadType)
                {
                    tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT8,   &psImageNotifyCommand->ePayloadType},
                                                                  {1, E_ZCL_UINT8,   &psImageNotifyCommand->u8QueryJitter}};
                    eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                              u8DestinationEndpoint,
                              psDestinationAddress,
                              OTA_CLUSTER_ID,
                              TRUE,
                              E_CLD_OTA_COMMAND_IMAGE_NOTIFY,
                              &u8SequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
                }
            }
            else
            {
               eZCL_Status = E_ZCL_ERR_PARAMETER_RANGE;
            }
        }
    }
    return eZCL_Status;
}

/****************************************************************************
 **
 ** NAME:       eOTA_ServerQueryNextImageResponse
 **
 ** DESCRIPTION:
 ** sends query next image response command
 **
 ** PARAMETERS:                Name                           Usage
 ** uint8                     u8SourceEndPointId            Source EP Id
 ** uint8                     u8DestinationEndPointId       Destination EP Id
 ** tsZCL_Address            *psDestinationAddress          Destination Address
 ** tsOTA_QueryImageResponse *psQueryImageResponsePayload   command payload
 ** uint8                     u8TransactionSequenceNumber   transaction sequence number
 **
 ** RETURN:
 ** teZCL_Status
 ****************************************************************************/

PUBLIC  teZCL_Status eOTA_ServerQueryNextImageResponse(
                    uint8                     u8SourceEndpoint,
                    uint8                     u8DestinationEndpoint,
                    tsZCL_Address            *psDestinationAddress,
                    tsOTA_QueryImageResponse *psQueryImageResponsePayload,
                    uint8                     u8TransactionSequenceNumber)
{
    teZCL_Status eZCL_Status;
    tsZCL_ClusterInstance *psClusterInstance;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsOTA_Common *psCustomData;

    if((eZCL_Status =
        eOtaFindCluster(u8SourceEndpoint,
                         &psEndPointDefinition,
                           &psClusterInstance,
                           &psCustomData,
                           TRUE))
                           == E_ZCL_SUCCESS)
    {
        if (!psClusterInstance->bIsServer)
        {
            eZCL_Status = E_ZCL_FAIL;
        }
        else
        {
            psEndPointDefinition->bDisableDefaultResponse = TRUE;
            if(psQueryImageResponsePayload->u8Status == OTA_STATUS_SUCCESS)
            {
                tsZCL_TxPayloadItem asPayloadDefinition[] ={  {1, E_ZCL_UINT8,   &psQueryImageResponsePayload->u8Status},
                                                  {1, E_ZCL_UINT16,   &psQueryImageResponsePayload->u16ManufacturerCode},
                                                  {1, E_ZCL_UINT16,   &psQueryImageResponsePayload->u16ImageType},
                                                  {1, E_ZCL_UINT32,   &psQueryImageResponsePayload->u32FileVersion},
                                                  {1, E_ZCL_UINT32,   &psQueryImageResponsePayload->u32ImageSize}
                                                };

                eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                                        u8DestinationEndpoint,
                                        psDestinationAddress,
                                        OTA_CLUSTER_ID,
                                        TRUE,
                                        E_CLD_OTA_COMMAND_QUERY_NEXT_IMAGE_RESPONSE,
                                        &u8TransactionSequenceNumber,
                                        asPayloadDefinition,
                                        FALSE,
                                        0,
                                        sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

            }
            else
            {
                tsZCL_TxPayloadItem asPayloadDefinition[] ={  {1, E_ZCL_UINT8,   &psQueryImageResponsePayload->u8Status}
                                                };

                eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                                        u8DestinationEndpoint,
                                        psDestinationAddress,
                                        OTA_CLUSTER_ID,
                                        TRUE,
                                        E_CLD_OTA_COMMAND_QUERY_NEXT_IMAGE_RESPONSE,
                                        &u8TransactionSequenceNumber,
                                        asPayloadDefinition,
                                        FALSE,
                                        0,
                                        sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
            }
        }
    }
    return eZCL_Status;
}

/****************************************************************************
 **
 ** NAME:       eOTA_ServerImageBlockResponse
 **
 ** DESCRIPTION:
 ** sends image block response command
 **
 ** PARAMETERS:                          Name                           Usage
 ** uint8                            u8SourceEndPointId            Source EP Id
 ** uint8                            u8DestinationEndPointId       Destination EP Id
 ** tsZCL_Address                   *psDestinationAddress          Destination Address
 ** tsOTA_ImageBlockResponsePayload *psImageBlockResponsePayload   command payload
 ** uint8                            u8SizeOfBlock                 Block size
 ** uint8                            u8TransactionSequenceNumber   transaction sequence number
 **
 ** RETURN:
 ** teZCL_Status
 ****************************************************************************/

PUBLIC  teZCL_Status eOTA_ServerImageBlockResponse(
                    uint8                            u8SourceEndpoint,
                    uint8                            u8DestinationEndpoint,
                    tsZCL_Address                   *psDestinationAddress,
                    tsOTA_ImageBlockResponsePayload *psImageBlockResponsePayload,
                    uint8                            u8SizeOfBlock,
                    uint8                            u8TransactionSequenceNumber)
{
    teZCL_Status eZCL_Status;
    tsZCL_ClusterInstance *psClusterInstance;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsOTA_Common *psCustomData;

    if((eZCL_Status =
        eOtaFindCluster(u8SourceEndpoint,
                         &psEndPointDefinition,
                           &psClusterInstance,
                           &psCustomData,
                           TRUE))
                           == E_ZCL_SUCCESS)
    {
        if (!psClusterInstance->bIsServer)
        {
            eZCL_Status = E_ZCL_FAIL;
        }
        else
        {
            psEndPointDefinition->bDisableDefaultResponse = TRUE;
            if(psImageBlockResponsePayload->u8Status == OTA_STATUS_SUCCESS)
            {
                tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT8,    &psImageBlockResponsePayload->u8Status},
                                                              {1, E_ZCL_UINT16,   &psImageBlockResponsePayload->uMessage.sBlockPayloadSuccess.u16ManufacturerCode},
                                                              {1, E_ZCL_UINT16,   &psImageBlockResponsePayload->uMessage.sBlockPayloadSuccess.u16ImageType},
                                                              {1, E_ZCL_UINT32,   &psImageBlockResponsePayload->uMessage.sBlockPayloadSuccess.u32FileVersion},
                                                              {1, E_ZCL_UINT32,   &psImageBlockResponsePayload->uMessage.sBlockPayloadSuccess.u32FileOffset},
                                                              {1, E_ZCL_UINT8,   &psImageBlockResponsePayload->uMessage.sBlockPayloadSuccess.u8DataSize},
                                                              {u8SizeOfBlock, E_ZCL_UINT8,  psImageBlockResponsePayload->uMessage.sBlockPayloadSuccess.pu8Data}
                                                            };

                eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                                                     u8DestinationEndpoint,
                                                     psDestinationAddress,
                                                     OTA_CLUSTER_ID,
                                                     TRUE,
                                                     E_CLD_OTA_COMMAND_BLOCK_RESPONSE,
                                                     &u8TransactionSequenceNumber,
                                                     asPayloadDefinition,
                                                     FALSE,
                                                     0,
                                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

            }
            else if(psImageBlockResponsePayload->u8Status == OTA_STATUS_WAIT_FOR_DATA)
            {
                tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT8,    &psImageBlockResponsePayload->u8Status},
                                                              {1, E_ZCL_UINT32,   &psImageBlockResponsePayload->uMessage.sWaitForData.u32CurrentTime},
                                                              {1, E_ZCL_UINT32,   &psImageBlockResponsePayload->uMessage.sWaitForData.u32RequestTime},
                                                              {1, E_ZCL_UINT16,   &psImageBlockResponsePayload->uMessage.sWaitForData.u16BlockRequestDelayMs}
                                                            };
                eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                                                     u8DestinationEndpoint,
                                                     psDestinationAddress,
                                                     OTA_CLUSTER_ID,
                                                     TRUE,
                                                     E_CLD_OTA_COMMAND_BLOCK_RESPONSE,
                                                     &u8TransactionSequenceNumber,
                                                     asPayloadDefinition,
                                                     FALSE,
                                                     0,
                                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
            }
            else
            {
                tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT8,    &psImageBlockResponsePayload->u8Status}
                                                            };
                eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                                                     u8DestinationEndpoint,
                                                     psDestinationAddress,
                                                     OTA_CLUSTER_ID,
                                                     TRUE,
                                                     E_CLD_OTA_COMMAND_BLOCK_RESPONSE,
                                                     &u8TransactionSequenceNumber,
                                                     asPayloadDefinition,
                                                     FALSE,
                                                     0,
                                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
            }
        }
    }
    return eZCL_Status;
}
/****************************************************************************
 **
 ** NAME:       eOTA_ServerUpgradeEndResponse
 **
 ** DESCRIPTION:
 ** sends upgrade end response command
 **
 ** PARAMETERS:                          Name                           Usage
 ** uint8                            u8SourceEndPointId            Source EP Id
 ** uint8                            u8DestinationEndPointId       Destination EP Id
 ** tsZCL_Address                   *psDestinationAddress          Destination Address
 ** tsOTA_UpgradeEndResponsePayload *psUpgradeResponsePayload      command payload
 ** uint8                            u8TransactionSequenceNumber   transaction sequence number
 **
 ** RETURN:
 ** teZCL_Status
 ****************************************************************************/
PUBLIC  teZCL_Status eOTA_ServerUpgradeEndResponse(
                    uint8                            u8SourceEndpoint,
                    uint8                            u8DestinationEndpoint,
                    tsZCL_Address                   *psDestinationAddress,
                    tsOTA_UpgradeEndResponsePayload *psUpgradeResponsePayload,
                    uint8                            u8TransactionSequenceNumber)
{
    teZCL_Status eZCL_Status;
    tsZCL_ClusterInstance *psClusterInstance;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsOTA_Common *psCustomData;

    if((eZCL_Status =
        eOtaFindCluster(u8SourceEndpoint,
                          &psEndPointDefinition,
                           &psClusterInstance,
                           &psCustomData,
                           TRUE))
                           == E_ZCL_SUCCESS)
    {
        if (!psClusterInstance->bIsServer)
        {
            eZCL_Status = E_ZCL_FAIL;
        }
        else
        {

            tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT16,    &psUpgradeResponsePayload->u16ManufacturerCode},
                                                          {1, E_ZCL_UINT16,    &psUpgradeResponsePayload->u16ImageType},
                                                          {1, E_ZCL_UINT32,   &psUpgradeResponsePayload->u32FileVersion},
                                                          {1, E_ZCL_UINT32,   &psUpgradeResponsePayload->u32CurrentTime},
                                                          {1, E_ZCL_UINT32,   &psUpgradeResponsePayload->u32UpgradeTime}
                                                            };
            psEndPointDefinition->bDisableDefaultResponse = TRUE;
            eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                                                     u8DestinationEndpoint,
                                                     psDestinationAddress,
                                                     OTA_CLUSTER_ID,
                                                     TRUE,
                                                     E_CLD_OTA_COMMAND_UPGRADE_END_RESPONSE,
                                                     &u8TransactionSequenceNumber,
                                                     asPayloadDefinition,
                                                     FALSE,
                                                     0,
                                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
        }
    }
    return eZCL_Status;

}

/****************************************************************************
 **
 ** NAME:       eOTA_ServerQuerySpecificFileResponse
 **
 ** DESCRIPTION:
 ** sends query specific file response command
 **
 ** PARAMETERS:                                  Name                                 Usage
 ** uint8                                   u8SourceEndPointId                       Source EP Id
 ** uint8                                   u8DestinationEndPointId                  Destination EP Id
 ** tsZCL_Address                          *psDestinationAddress                     Destination Address
 ** tsOTA_QuerySpecificFileResponsePayload *psQuerySpecificFileResponsePayload       command payload
 ** uint8                                   u8TransactionSequenceNumber              transaction sequence number
 **
 ** RETURN:
 ** teZCL_Status
 ****************************************************************************/
PUBLIC  teZCL_Status eOTA_ServerQuerySpecificFileResponse(
                    uint8                                   u8SourceEndpoint,
                    uint8                                   u8DestinationEndpoint,
                    tsZCL_Address                          *psDestinationAddress,
                    tsOTA_QuerySpecificFileResponsePayload *psQuerySpecificFileResponsePayload,
                    uint8                                   u8TransactionSequenceNumber)
{
    teZCL_Status eZCL_Status;
    tsZCL_ClusterInstance *psClusterInstance;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsOTA_Common *psCustomData;

    if((eZCL_Status =
        eOtaFindCluster(u8SourceEndpoint,
                         &psEndPointDefinition,
                         &psClusterInstance,
                           &psCustomData,
                           TRUE))
                           == E_ZCL_SUCCESS)
    {
        if (!psClusterInstance->bIsServer)
        {
            eZCL_Status = E_ZCL_FAIL;
        }
        else
        {
            psEndPointDefinition->bDisableDefaultResponse = TRUE;
            if(psQuerySpecificFileResponsePayload->u8Status == OTA_STATUS_SUCCESS)
            {
                tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT8,   &psQuerySpecificFileResponsePayload->u8Status},
                                                  {1, E_ZCL_UINT16,   &psQuerySpecificFileResponsePayload->u16ManufacturerCode},
                                                  {1, E_ZCL_UINT16,   &psQuerySpecificFileResponsePayload->u16ImageType},
                                                  {1, E_ZCL_UINT32,   &psQuerySpecificFileResponsePayload->u32FileVersion},
                                                  {1, E_ZCL_UINT32,   &psQuerySpecificFileResponsePayload->u32ImageSize}
                                                };
                eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                                                 u8DestinationEndpoint,
                                                 psDestinationAddress,
                                                 OTA_CLUSTER_ID,
                                                 TRUE,
                                                 E_CLD_OTA_COMMAND_QUERY_SPECIFIC_FILE_RESPONSE,
                                                 &u8TransactionSequenceNumber,
                                                 asPayloadDefinition,
                                                 FALSE,
                                                 0,
                                                 sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
            }
            else
            {
                tsZCL_TxPayloadItem asPayloadDefinition[] = { {1, E_ZCL_UINT8,   &psQuerySpecificFileResponsePayload->u8Status} };

                eZCL_Status = eZCL_CustomCommandSend(u8SourceEndpoint,
                                                 u8DestinationEndpoint,
                                                 psDestinationAddress,
                                                 OTA_CLUSTER_ID,
                                                 TRUE,
                                                 E_CLD_OTA_COMMAND_QUERY_SPECIFIC_FILE_RESPONSE,
                                                 &u8TransactionSequenceNumber,
                                                 asPayloadDefinition,
                                                 FALSE,
                                                 0,
                                                 sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
            }
        }
    }
    return eZCL_Status;
}
#endif
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
