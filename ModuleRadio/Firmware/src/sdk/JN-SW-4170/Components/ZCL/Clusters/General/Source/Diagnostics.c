/*****************************************************************************
 *
 * MODULE:             Diagnostics Cluster
 *
 * COMPONENT:          Diagnostics.c
 *
 * AUTHOR:             Gyanaranjan Jena
 *
 * DESCRIPTION:        Diagnostics Cluster
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy:  $
 *
 * $LastChangedDate:  $
 *
 * $Id:  $
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
#include "Diagnostics.h"
#include "zcl_options.h"
#ifdef CLD_DIAGNOSTICS_ATTR_ID_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT
#include "zps_mac_if_table.h"
#endif
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
/***        Exported Function Variables                                            ***/
/****************************************************************************/
extern void MAC_vInitBbcTxTries(void);
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#ifdef CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_LQI
extern uint8 u8LastLqi;
#endif
#ifdef CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_RSSI
extern int8 i8LastRssi;
#endif
/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
const tsZCL_AttributeDefinition asCLD_DiagnosticsClusterAttributeDefinitions[] = {
#ifdef DIAGNOSTICS_SERVER
            /* Hardware Information attribute set attribute ID's (ZCL Spec r6 3.15.2.2.1) */
    #ifdef CLD_DIAGNOSTICS_ATTR_ID_NUMBER_OF_RESETS
            {E_CLD_DIAGNOSTICS_ATTR_ID_NUMBER_OF_RESETS,          E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16NumberOfResets),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_PERSISTENT_MEMORY_WRITES
            {E_CLD_DIAGNOSTICS_ATTR_ID_PERSISTENT_MEMORY_WRITES,  E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16PersistentMemoryWrites),0},
    #endif

            /* Stack/Network Information attribute set attribute ID's (ZCL Spec r6 3.15.2.2.2) */
    #ifdef CLD_DIAGNOSTICS_ATTR_ID_MAC_RX_BCAST
            {E_CLD_DIAGNOSTICS_ATTR_ID_MAC_RX_BCAST,              E_ZCL_AF_RD,                E_ZCL_UINT32,   (uint32)(&((tsCLD_Diagnostics*)(0))->u32MacRxBcast),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_MAC_TX_BCAST
            {E_CLD_DIAGNOSTICS_ATTR_ID_MAC_TX_BCAST,              E_ZCL_AF_RD,                E_ZCL_UINT32,   (uint32)(&((tsCLD_Diagnostics*)(0))->u32MacTxBcast),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_MAC_RX_UCAST
            {E_CLD_DIAGNOSTICS_ATTR_ID_MAC_RX_UCAST,              E_ZCL_AF_RD,                E_ZCL_UINT32,   (uint32)(&((tsCLD_Diagnostics*)(0))->u32MacRxUcast),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_MAC_TX_UCAST
            {E_CLD_DIAGNOSTICS_ATTR_ID_MAC_TX_UCAST,              E_ZCL_AF_RD,                E_ZCL_UINT32,   (uint32)(&((tsCLD_Diagnostics*)(0))->u32MacTxUcast),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_MAC_TX_UCAST_RETRY
            {E_CLD_DIAGNOSTICS_ATTR_ID_MAC_TX_UCAST_RETRY,        E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16MacTxUcastRetry),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_MAC_TX_UCAST_FAIL
            {E_CLD_DIAGNOSTICS_ATTR_ID_MAC_TX_UCAST_FAIL,         E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16MacTxUcastFail),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_APS_RX_BCAST
            {E_CLD_DIAGNOSTICS_ATTR_ID_APS_RX_BCAST,              E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16ApsRxBcast),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_APS_TX_BCAST
            {E_CLD_DIAGNOSTICS_ATTR_ID_APS_TX_BCAST,              E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16ApsTxBcast),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_APS_RX_UCAST
            {E_CLD_DIAGNOSTICS_ATTR_ID_APS_RX_UCAST,              E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16ApsRxUcast),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_APS_TX_UCAST_SUCCESS
            {E_CLD_DIAGNOSTICS_ATTR_ID_APS_TX_UCAST_SUCCESS,      E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16ApsTxUcastSuccess),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_APS_TX_UCAST_RETRY
            {E_CLD_DIAGNOSTICS_ATTR_ID_APS_TX_UCAST_RETRY,         E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16ApsTxUcastRetry),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_APS_TX_UCAST_FAIL
            {E_CLD_DIAGNOSTICS_ATTR_ID_APS_TX_UCAST_FAIL,          E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16ApsTxUcastFail),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_ROUTE_DISC_INITIATED
            {E_CLD_DIAGNOSTICS_ATTR_ID_ROUTE_DISC_INITIATED,       E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16RouteDiscInitiated),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_NEIGHBOR_ADDED
            {E_CLD_DIAGNOSTICS_ATTR_ID_NEIGHBOR_ADDED,             E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16NeighborAdded),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_NEIGHBOR_REMOVED
            {E_CLD_DIAGNOSTICS_ATTR_ID_NEIGHBOR_REMOVED,           E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16NeighborRemoved),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_NEIGHBOR_STALE
            {E_CLD_DIAGNOSTICS_ATTR_ID_NEIGHBOR_STALE,             E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16NeighborStale),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_JOIN_INDICATION
            {E_CLD_DIAGNOSTICS_ATTR_ID_JOIN_INDICATION,            E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16JoinIndication),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_CHILD_MOVED
            {E_CLD_DIAGNOSTICS_ATTR_ID_CHILD_MOVED,                E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16ChildMoved),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_NWK_FC_FAILURE
            {E_CLD_DIAGNOSTICS_ATTR_ID_NWK_FC_FAILURE,             E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16NWKFCFailure),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_APS_FC_FAILURE
            {E_CLD_DIAGNOSTICS_ATTR_ID_APS_FC_FAILURE,             E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16APSFCFailure),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_APS_UNAUTHORIZED_KEY
            {E_CLD_DIAGNOSTICS_ATTR_ID_APS_UNAUTHORIZED_KEY,       E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16APSUnauthorizedKey),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_NWK_DECRYPT_FAILURE
            {E_CLD_DIAGNOSTICS_ATTR_ID_NWK_DECRYPT_FAILURE,        E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16NWKDecryptFailure),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_APS_DECRYPT_FAILURE
            {E_CLD_DIAGNOSTICS_ATTR_ID_APS_DECRYPT_FAILURE,        E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16APSDecryptFailure),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_PACKET_BUFFER_ALLOCATE_FAILURE
            {E_CLD_DIAGNOSTICS_ATTR_ID_PACKET_BUFFER_ALLOCATE_FAILURE,E_ZCL_AF_RD,             E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16PacketBufferAllocateFailure),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_RELAYED_UCAST
            {E_CLD_DIAGNOSTICS_ATTR_ID_RELAYED_UCAST,              E_ZCL_AF_RD,                E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16RelayedUcast),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_PHY_TO_MAC_QUEUE_LIMIT_REACHED
            {E_CLD_DIAGNOSTICS_ATTR_ID_PHY_TO_MAC_QUEUE_LIMIT_REACHED,E_ZCL_AF_RD,             E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16PhyToMACQueueLimitReached),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_PACKET_VALIDATE_DROP_COUNT
            {E_CLD_DIAGNOSTICS_ATTR_ID_PACKET_VALIDATE_DROP_COUNT,  E_ZCL_AF_RD,               E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16PacketValidateDropCount),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT
            {E_CLD_DIAGNOSTICS_ATTR_ID_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT,  E_ZCL_AF_RD,   E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16AverageMACRetryPerAPSMessageSent),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_LQI
            {E_CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_LQI,            E_ZCL_AF_RD,               E_ZCL_UINT8,   (uint32)(&((tsCLD_Diagnostics*)(0))->u8LastMessageLQI),0},
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_RSSI
            {E_CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_RSSI,            E_ZCL_AF_RD,              E_ZCL_INT8,   (uint32)(&((tsCLD_Diagnostics*)(0))->i8LastMessageRSSI),0},
    #endif
#endif    
            {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                 (E_ZCL_AF_RD|E_ZCL_AF_GA), E_ZCL_UINT16,   (uint32)(&((tsCLD_Diagnostics*)(0))->u16ClusterRevision),0},   /* Mandatory  */
 };

tsZCL_ClusterDefinition sCLD_Diagnostics = {
        GENERAL_CLUSTER_ID_DIAGNOSTICS,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_DiagnosticsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_DiagnosticsClusterAttributeDefinitions,
        NULL
};

uint8 au8DiagnosticsClusterAttributeControlBits[(sizeof(asCLD_DiagnosticsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_DiagnosticsCreateDiagnostics
 **
 ** DESCRIPTION:
 ** Creates a diagnostic cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_DiagnosticsCreateDiagnostics(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits)
{

    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif
    
    /* Create an instance of a diagnostics cluster */
    vZCL_InitializeClusterInstance(
                           psClusterInstance, 
                           bIsServer,
                           psClusterDefinition,
                           pvEndPointSharedStructPtr,
                           pu8AttributeControlBits,
                           NULL,
                           NULL);

    if(psClusterInstance->pvEndPointSharedStructPtr != NULL)
    {
        /* Initialise attribute defaults */
        ((tsCLD_Diagnostics*)psClusterInstance->pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_DIAGNOSTICS_CLUSTER_REVISION ;
    }
    
    /* Initialise attribute defaults */
    /* All the deafult values are zero for this cluster hence no need to initialise explicly - save some code */
#ifndef JENNIC_MAC_MiniMacShim

    /*Initialise Stack/NWK to provide the attribute values */
    MAC_vInitBbcTxTries();
#endif
    return E_ZCL_SUCCESS;

}

#ifdef DIAGNOSTICS_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_DiagnosticsUpdate
 **
 ** DESCRIPTION:
 ** Updates the the state of an Diagnostic cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          Source EP Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_DiagnosticsUpdate(uint8 u8SourceEndPointId)
{

    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsCLD_DiagnosticsCustomDataStructure *psCustomDataStructure;
#if defined( CLD_DIAGNOSTICS_ATTR_ID_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT) || defined (CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_LQI)
    tsCLD_Diagnostics *psSharedStruct;
#endif
    tsZCL_ClusterInstance *psClusterInstance;/* Find pointers to cluster */
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_DIAGNOSTICS, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }

    /* get EP mutex */
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif
    
    #if defined( CLD_DIAGNOSTICS_ATTR_ID_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT) || defined (CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_LQI)
         psSharedStruct = (tsCLD_Diagnostics*)psClusterInstance->pvEndPointSharedStructPtr;
    #endif
    /*
     * Get all the Attributes Updated from the stack/nwk layer
     */
    #ifdef CLD_DIAGNOSTICS_ATTR_ID_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT
        psSharedStruct->u16AverageMACRetryPerAPSMessageSent=ZPS_psMacIFTGetTable()->pu32MacTxUcastAvgRetry[0];
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_LQI
        psSharedStruct->u8LastMessageLQI = u8LastLqi;
    #endif

    #ifdef CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_RSSI
        psSharedStruct->i8LastMessageRSSI = i8LastRssi;
    #endif

     /* release EP mutex */
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return(E_ZCL_SUCCESS);
}
#endif
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

