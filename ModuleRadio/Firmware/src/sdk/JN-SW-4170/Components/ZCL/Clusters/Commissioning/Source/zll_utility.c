/*****************************************************************************
 *
 * MODULE:             Light Link Profile
 *
 * COMPONENT:          zll_utility.c
 *
 * AUTHOR:
 *
 * DESCRIPTION:        ZigBee Light Link profile functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/Commissioning/Source/zll_utility.c $
 *
 * $Revision: 82880 $
 *
 * $LastChangedBy: nxp46755 $
 *
 * $LastChangedDate: 2016-09-08 08:37:04 +0200 (Thu, 08 Sep 2016) $
 *
 * $Id: zll_utility.c 82880 2016-09-08 06:37:04Z nxp46755 $
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
#include "zps_apl.h"
#include "zcl_heap.h"
#include "zcl.h"
#include "zcl_options.h"
#include "zll_utility.h"
#include "dbg.h"

extern PUBLIC tsZllGroupInfoTable * psGetGroupRecordTable(void);
extern PUBLIC tsZllEndpointInfoTable * psGetEndpointRecordTable(void);
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
const tsZCL_AttributeDefinition asCLD_ZllUtilityClusterAttributeDefinitions[] = {
    {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,  (E_ZCL_AF_RD|E_ZCL_AF_GA),        E_ZCL_UINT16,    (uint32)(&((tsCLD_ZllUtility*)(0))->u16ClusterRevision),0},   /* Mandatory  */
};

tsZCL_ClusterDefinition sCLD_ZllUtility = {
        ZLL_CLUSTER_ID_UTILITY,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_ZllUtilityClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_ZllUtilityClusterAttributeDefinitions,
        NULL
};

uint8 au8ZllUtilityAttributeControlBits[(sizeof(asCLD_ZllUtilityClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:     eCLD_ZllUtilityCommandEndpointInformationCommandSend
 **
 ** DESCRIPTION:
 **
 ** PARAMETERS:                 Name                      Usage
 ** uint8                       u8SrcEndpoint
 ** uint8                       u8DstEndpoint
 ** ZPS_tsInterPanAddress       *psDestinationAddress
 ** uint8                       *pu8TransactionSequenceNumber
 ** tsCLD_ZllCommission_ScanReqCommandPayload  *psPayload
 **
 ** RETURN:
 ** status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ZllUtilityCommandEndpointInformationCommandSend(
                    uint8 u8SrcEndpoint,
                    uint8 u8DstEndpoint,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsCLD_ZllUtility_EndpointInformationCommandPayload *psPayload)
{
    teZCL_Status eStatus;
    /* NOT inter pan */
    tsZCL_TxPayloadItem asPayloadDefinition[] = {
                                    {1, E_ZCL_UINT64,   &psPayload->u64IEEEAddr},
                                    {1, E_ZCL_UINT16,  &psPayload->u16NwkAddr},
                                    {1, E_ZCL_UINT8,   &psPayload->u8Endpoint},
                                    {1, E_ZCL_UINT16,  &psPayload->u16ProfileID},
                                    {1, E_ZCL_UINT16,  &psPayload->u16DeviceID},
                                    {1, E_ZCL_UINT8,  &psPayload->u8Version} };

    /* Check end point is registered */
    tsZCL_EndPointDefinition    *psEndPointDefinition;
    if(eZCL_SearchForEPentry(u8SrcEndpoint, &psEndPointDefinition) != E_ZCL_SUCCESS)
    {
        return(E_ZCL_ERR_EP_UNKNOWN);
    }
    bool_t  bDefaultRsp = psEndPointDefinition->bDisableDefaultResponse;

    /* ensure default response is requested
     * see spec sec 7.1.2.3.6
     */
    psEndPointDefinition->bDisableDefaultResponse = FALSE;

    eStatus = eZCL_CustomCommandSend(u8SrcEndpoint,
                           u8DstEndpoint,
                           psDestinationAddress,
                           ZLL_CLUSTER_ID_UTILITY,
                           TRUE,                                // server to client
                           E_CLD_UTILITY_CMD_ENDPOINT_INFO,
                           pu8TransactionSequenceNumber,
                           asPayloadDefinition,
                           FALSE,
                           0,
                           sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

    /* restore the default response state */
    psEndPointDefinition->bDisableDefaultResponse = bDefaultRsp;


    return eStatus;


}

/****************************************************************************
 **
 ** NAME:     eCLD_ZllUtilityCommandGetGroupIdReqCommandSend
 **
 ** DESCRIPTION:
 **
 **
 ** PARAMETERS:                 Name                      Usage
 ** ZPS_tsInterPanAddress       *psDestinationAddress
 ** uint8                       *pu8TransactionSequenceNumber
 ** tsCLD_ZllCommission_ScanReqCommandPayload  *psPayload
 **
 ** RETURN:
 ** status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ZllUtilityCommandGetGroupIdReqCommandSend(
                    uint8   u8SrcEndpoint,
                    uint8   u8DstEndpoint,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint8                       u8StartIndex)
{
    /* NOT inter pan */
    tsZCL_TxPayloadItem asPayloadDefinition[] = {
                                   {1, E_ZCL_UINT8,   &u8StartIndex} };

    return eZCL_CustomCommandSend(u8SrcEndpoint,
                          u8DstEndpoint,
                          psDestinationAddress,
                          ZLL_CLUSTER_ID_UTILITY,
                          FALSE,                                        // client to server
                          E_CLD_UTILITY_CMD_GET_GROUP_ID_REQ_RSP,
                          pu8TransactionSequenceNumber,
                          asPayloadDefinition,
                          FALSE,
                          0,
                          sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}

/****************************************************************************
 **
 ** NAME:     eCLD_ZllUtilityCommandGetGroupIdRspCommandSend
 **
 ** DESCRIPTION:
 **
 **
 ** PARAMETERS:                 Name                      Usage
 ** uint8                       u8SrcEndpoint
 ** uint8                       u8DstEndpoint
 ** ZPS_tsInterPanAddress       *psDestinationAddress
 ** uint8                       *pu8TransactionSequenceNumber
 ** tsCLD_ZllCommission_ScanReqCommandPayload  *psPayload
 ** uint8                       u8StartIndex
 **
 ** RETURN:
 ** status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ZllUtilityCommandGetGroupIdRspCommandSend(
                    uint8 u8SrcEndpoint,
                    uint8 u8DstEndpoint,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint8                       u8StartIndex)
{
    tsZllGroupInfoTable* psGroupTable = psGetGroupRecordTable();
    uint8 u8Count = 0;

    tsZCL_TxPayloadItem asPayloadDefinition[3+(TL_MAX_GROUP_RECORDS*3)] = {
                            {1, E_ZCL_UINT8,   &psGroupTable->u8NumRecords},
                            {1, E_ZCL_UINT8,   &u8StartIndex},
                            {1, E_ZCL_UINT8,   &u8Count}  };

    int i, j=3;
    for (i=u8StartIndex;  i<psGroupTable->u8NumRecords && u8Count<8; i++) {
        asPayloadDefinition[j].u16Quantity = 1;
        asPayloadDefinition[j].eType = E_ZCL_UINT16;
        asPayloadDefinition[j++].pvData = &psGroupTable->asGroupRecords[i].u16GroupId;
        asPayloadDefinition[j].u16Quantity = 1;
        asPayloadDefinition[j].eType = E_ZCL_UINT8;
        asPayloadDefinition[j++].pvData = &psGroupTable->asGroupRecords[i].u8GroupType;
        u8Count++;
    }


    return eZCL_CustomCommandSend(u8SrcEndpoint,
                              u8DstEndpoint,
                              psDestinationAddress,
                              ZLL_CLUSTER_ID_UTILITY,
                              TRUE,                                        // server to client
                              E_CLD_UTILITY_CMD_GET_GROUP_ID_REQ_RSP,
                              pu8TransactionSequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              j);
}

/****************************************************************************
 **
 ** NAME:     eCLD_ZllUtilityCommandGetEndpointListReqCommandSend
 **
 ** DESCRIPTION:
 **
 ** PARAMETERS:                 Name                      Usage
 ** uint8                       u8SrcEndpoint
 ** uint8                       u8DstEndpoint
 ** ZPS_tsInterPanAddress       *psDestinationAddress
 ** uint8                       *pu8TransactionSequenceNumber
 ** tsCLD_ZllCommission_ScanReqCommandPayload  *psPayload
 ** uint8                       u8StartIndex
 **
 ** RETURN:
 ** status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ZllUtilityCommandGetEndpointListReqCommandSend(
                    uint8                       u8SrcEndpoint,
                    uint8                       u8DstEndpoint,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint8                       u8StartIndex)
{
    /* NOT inter pan */
    tsZCL_TxPayloadItem asPayloadDefinition[] = {
                                   {1, E_ZCL_UINT8,   &u8StartIndex} };
   return eZCL_CustomCommandSend(u8SrcEndpoint,
                          u8DstEndpoint,
                          psDestinationAddress,
                          ZLL_CLUSTER_ID_UTILITY,
                          FALSE /*bDirection*/,
                          E_CLD_UTILITY_CMD_GET_ENDPOINT_LIST_REQ_RSP,
                          pu8TransactionSequenceNumber,
                          asPayloadDefinition,
                          FALSE,                                        // client to server
                          0,
                          sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));


}

/****************************************************************************
 **
 ** NAME:     eCLD_ZllUtilityCommandGetEndpointListRspCommandSend
 **
 ** DESCRIPTION:
 **
 ** PARAMETERS:                 Name                      Usage
 ** uint8                       u8SrcEndpoint
 ** uint8                       u8DstEndpoint
 ** ZPS_tsInterPanAddress       *psDestinationAddress
 ** uint8                       *pu8TransactionSequenceNumber
 ** tsCLD_ZllCommission_ScanReqCommandPayload  *psPayload
 ** uint8                       u8StartIndex
 **
 ** RETURN:
 ** status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ZllUtilityCommandGetEndpointListRspCommandSend(
                    uint8                       u8SrcEndpoint,
                    uint8                       u8DstEndpoint,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint8                       u8StartIndex)
{
    /* Worst APS payload = 70 (assume no source route) */
    /* ZCL header = 3 */
    /* So usable payload = 67 */
    /* Msg = 3 + 8n, so max n = 8 */

    tsZllEndpointInfoTable* psEndpointTable = psGetEndpointRecordTable();
    uint8 u8Count = 0;

    tsZCL_TxPayloadItem asPayloadDefinition[3+(ZLL_MAX_ENDPOINT_RECORDS*5)] = {
                            {1, E_ZCL_UINT8,   &psEndpointTable->u8NumRecords},
                            {1, E_ZCL_UINT8,   &u8StartIndex},
                            {1, E_ZCL_UINT8,   &u8Count}  };

    int i, j=3;
    for (i=u8StartIndex;  i<psEndpointTable->u8NumRecords && u8Count<8; i++) {
        asPayloadDefinition[j].u16Quantity = 1;
        asPayloadDefinition[j].eType = E_ZCL_UINT16;
        asPayloadDefinition[j++].pvData = &psEndpointTable->asEndpointRecords[i].u16NwkAddr;
        asPayloadDefinition[j].u16Quantity = 1;
        asPayloadDefinition[j].eType = E_ZCL_UINT8;
        asPayloadDefinition[j++].pvData = &psEndpointTable->asEndpointRecords[i].u8Endpoint;
        asPayloadDefinition[j].u16Quantity = 1;
        asPayloadDefinition[j].eType = E_ZCL_UINT16;
        asPayloadDefinition[j++].pvData = &psEndpointTable->asEndpointRecords[i].u16ProfileId;
        asPayloadDefinition[j].u16Quantity = 1;
        asPayloadDefinition[j].eType = E_ZCL_UINT16;
        asPayloadDefinition[j++].pvData = &psEndpointTable->asEndpointRecords[i].u16DeviceId;
        asPayloadDefinition[j].u16Quantity = 1;
        asPayloadDefinition[j].eType = E_ZCL_UINT8;
        asPayloadDefinition[j++].pvData = &psEndpointTable->asEndpointRecords[i].u8Version;
        u8Count++;
    }

    return eZCL_CustomCommandSend(u8SrcEndpoint,
                                  u8DstEndpoint,
                                  psDestinationAddress,
                                  ZLL_CLUSTER_ID_UTILITY,
                                  TRUE,                                                 // Sever to client
                                  E_CLD_UTILITY_CMD_GET_ENDPOINT_LIST_REQ_RSP,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,                                        // server to client
                                  0,
                                  j);
}





/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

