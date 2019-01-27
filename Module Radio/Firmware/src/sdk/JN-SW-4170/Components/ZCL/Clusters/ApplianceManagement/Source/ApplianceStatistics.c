/*****************************************************************************
 *
 * MODULE:             Appliance Statistics Cluster
 *
 * COMPONENT:          ApplianceStatistics.c
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Appliance Statistics Cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Source/ApplianceStatistics.c $
 *
 * $Revision: 53726 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-05-06 15:55:33 +0530 (Mon, 06 May 2013) $
 *
 * $Id: ApplianceStatistics.c 53726 2013-05-06 10:25:33Z nxp57621 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139].
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
#include "ApplianceStatistics.h"
#include "ApplianceStatistics_internal.h"
#include "zcl_options.h"

#include "zcl.h"
#include "string.h"
#include "dbg.h"

#ifdef DEBUG_CLD_APPLIANCE_STATISTICS
#define TRACE_APPLIANCE_STATISTICS    TRUE
#else
#define TRACE_APPLIANCE_STATISTICS    FALSE
#endif

#ifdef CLD_APPLIANCE_STATISTICS

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
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
    const tsZCL_CommandDefinition asCLD_ApplianceStatisticsClusterCommandDefinitions[] = {
        {E_CLD_APPLIANCE_STATISTICS_CMD_LOG_NOTIFICATION,               E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_APPLIANCE_STATISTICS_CMD_LOG_RESPONSE,                   E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_APPLIANCE_STATISTICS_CMD_LOG_QUEUE_RESPONSE,             E_ZCL_CF_TX},     /* Mandatory */    
        {E_CLD_APPLIANCE_STATISTICS_CMD_STATISTICS_AVAILABLE,           E_ZCL_CF_TX},     /* Mandatory */ 
        {E_CLD_APPLIANCE_STATISTICS_CMD_LOG_REQUEST,                    E_ZCL_CF_RX},
        {E_CLD_APPLIANCE_STATISTICS_CMD_LOG_QUEUE_REQUEST,              E_ZCL_CF_RX}
    };
#endif
const tsZCL_AttributeDefinition asCLD_ApplianceStatisticsClusterAttributeDefinitions[] = {
#ifdef APPLIANCE_STATISTICS_SERVER
        /* ZigBee Cluster Library Version */
        {E_CLD_APPLIANCE_STATISTICS_ATTR_ID_LOG_MAX_SIZE ,                          E_ZCL_AF_RD,                E_ZCL_UINT32,    (uint32)(&((tsCLD_ApplianceStatistics*)(0))->u32LogMaxSize),            0},  /* Mandatory */

        {E_CLD_APPLIANCE_STATISTICS_ATTR_ID_LOG_QUEUE_MAX_SIZE ,                    E_ZCL_AF_RD,                E_ZCL_UINT8,     (uint32)(&((tsCLD_ApplianceStatistics*)(0))->u8LogQueueMaxSize),        0},    /* Mandatory */
#endif        
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                                     (E_ZCL_AF_RD|E_ZCL_AF_GA),   E_ZCL_UINT16,     (uint32)(&((tsCLD_ApplianceStatistics*)(0))->u16ClusterRevision),      0},   /* Mandatory  */    
};

tsZCL_ClusterDefinition sCLD_ApplianceStatistics = {
        APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_STATISTICS,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_ApplianceStatisticsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_ApplianceStatisticsClusterAttributeDefinitions,
        NULL
        #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED        
            ,
            (sizeof(asCLD_ApplianceStatisticsClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
            (tsZCL_CommandDefinition*)asCLD_ApplianceStatisticsClusterCommandDefinitions          
        #endif        
};
uint8 au8ApplianceStatisticsAttributeControlBits[(sizeof(asCLD_ApplianceStatisticsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME:       eCLD_ApplianceStatisticsCreateApplianceStatistics
 *
 * DESCRIPTION:
 * Creates a basic cluster
 *
 * PARAMETERS:  Name                         Usage
 *              psClusterInstance            Cluster structure
 *              bIsServer                    Server/Client Flag
 *              psClusterDefinition          Cluster Definitation
 *              pvEndPointSharedStructPtr    EndPoint Shared Structure Pointer
 *              pu8AttributeControlBits      Attribute Control Bits
 * RETURN:
 * teZCL_Status
 *
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ApplianceStatisticsCreateApplianceStatistics(
                tsZCL_ClusterInstance                              *psClusterInstance,
                bool_t                                             bIsServer,
                tsZCL_ClusterDefinition                            *psClusterDefinition,
                void                                               *pvEndPointSharedStructPtr,
                uint8                                              *pu8AttributeControlBits,
                tsCLD_ApplianceStatisticsCustomDataStructure       *psCustomDataStructure)
{


    #ifdef    APPLIANCE_STATISTICS_SERVER    
        uint8 u8LogCount = 0; 
    #endif
    
    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL) ||
           (psCustomDataStructure==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif


    /* Create an instance of Appliance Identification cluster */
    vZCL_InitializeClusterInstance(
                       psClusterInstance, 
                       bIsServer,
                       psClusterDefinition,
                       pvEndPointSharedStructPtr,
                       pu8AttributeControlBits,
                       psCustomDataStructure,
                       eCLD_ApplianceStatisticsCommandHandler);
                       
    psCustomDataStructure->sCustomCallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_CUSTOM;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId = psClusterDefinition->u16ClusterEnum;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.pvCustomData = (void *)&psCustomDataStructure->sCallBackMessage;
    psCustomDataStructure->sCustomCallBackEvent.psClusterInstance = psClusterInstance; 
    
#ifdef  APPLIANCE_STATISTICS_SERVER    
    for(u8LogCount = 0 ; u8LogCount < CLD_APPLIANCE_STATISTICS_ATTR_LOG_QUEUE_MAX_SIZE; u8LogCount++)
    {
        psCustomDataStructure->asLogTable[u8LogCount].u8LogLength = (CLD_APPLIANCE_STATISTICS_ATTR_LOG_MAX_SIZE + 1);
    }
#endif   
    /* Initialise attributes defaults */
    if(pvEndPointSharedStructPtr != NULL)
    {
#ifdef  APPLIANCE_STATISTICS_SERVER        
        ((tsCLD_ApplianceStatistics*)pvEndPointSharedStructPtr)->u32LogMaxSize = CLD_APPLIANCE_STATISTICS_ATTR_LOG_MAX_SIZE;
        ((tsCLD_ApplianceStatistics*)pvEndPointSharedStructPtr)->u8LogQueueMaxSize = CLD_APPLIANCE_STATISTICS_ATTR_LOG_QUEUE_MAX_SIZE;
#endif         
        ((tsCLD_ApplianceStatistics*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_APPLIANCE_STATISTICS_CLUSTER_REVISION;
    }
   
   return E_ZCL_SUCCESS;
}

#ifdef    APPLIANCE_STATISTICS_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_ASCAddLog
 **
 ** DESCRIPTION:
 ** Adds a Log
 **
 ** PARAMETERS:                 Name                    Usage
 ** uint8                       u8SourceEndPointId      Endpoint id
 ** uint32                      u32LogId                  Log Id
 ** uint8                       u8LogLength               Log Length
 ** uint8 *                     pu8LogData                Log Data
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_CommandStatus eCLD_ASCAddLog(uint8 u8SourceEndPointId,
                                                   uint32                     u32LogId,
                                                   uint8                      u8LogLength,
                                                   uint32                     u32Time,
                                                   uint8                      *pu8LogData)
{
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_ApplianceStatisticsCustomDataStructure *pCustomDataStructure;
    uint8 u8LogCount;
    tsCLD_LogTable *psLogTable;
    tsZCL_Address sZCL_Address = {0};
    uint8 u8TransactionSeqNumber = 0;
    tsCLD_ASC_LogNotificationORLogResponsePayload     sPayload;

    if(pu8LogData == NULL)
    {
        return E_ZCL_CMDS_INVALID_FIELD;
    }
    
    /* Find pointers to cluster */
    if(eZCL_FindCluster(APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_STATISTICS, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&pCustomDataStructure) != E_ZCL_SUCCESS)
    {
        return E_ZCL_CMDS_FAILURE;
    }
    
    if(u8LogLength    > CLD_APPLIANCE_STATISTICS_ATTR_LOG_MAX_SIZE)
    {
        return E_ZCL_CMDS_INVALID_VALUE;
    }

    if(eCLD_ASCGetLogEntry(u8SourceEndPointId,u32LogId,&psLogTable) == E_ZCL_CMDS_SUCCESS)
    {   
        psLogTable->utctTime = u32Time;
        psLogTable->u8LogLength = u8LogLength;
        psLogTable->pu8LogData = pu8LogData;
        return E_ZCL_CMDS_SUCCESS;
    }

    for( u8LogCount = 0 ; u8LogCount < CLD_APPLIANCE_STATISTICS_ATTR_LOG_QUEUE_MAX_SIZE; u8LogCount++)
    {
        if( pCustomDataStructure->asLogTable[u8LogCount].u8LogLength > CLD_APPLIANCE_STATISTICS_ATTR_LOG_MAX_SIZE )
            {
                pCustomDataStructure->asLogTable[u8LogCount].u32LogID = u32LogId;
                pCustomDataStructure->asLogTable[u8LogCount].u8LogLength = u8LogLength;
                pCustomDataStructure->asLogTable[u8LogCount].utctTime = u32Time;
                pCustomDataStructure->asLogTable[u8LogCount].pu8LogData = pu8LogData;
                memcpy(&sPayload,(tsCLD_LogTable *)&pCustomDataStructure->asLogTable[u8LogCount],sizeof(tsCLD_LogTable));
                sZCL_Address.eAddressMode = E_ZCL_AM_BOUND;
                eCLD_ASCLogNotificationSend(                
                                            u8SourceEndPointId,
                                            0,
                                            &sZCL_Address,
                                            &u8TransactionSeqNumber,
                                            &sPayload);
                return E_ZCL_CMDS_SUCCESS;
            }
    }

    return E_ZCL_CMDS_INSUFFICIENT_SPACE;

}

/****************************************************************************
 **
 ** NAME:       eCLD_ASCRemoveLog
 **
 ** DESCRIPTION:
 ** removes a Log
 **
 ** PARAMETERS:                 Name                    Usage
 ** uint8                       u8SourceEndPointId      Endpoint id
 ** uint32                      u32LogId                  Log Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_CommandStatus eCLD_ASCRemoveLog(uint8 u8SourceEndPointId,
                                                   uint32 u32LogId)
{
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_ApplianceStatisticsCustomDataStructure *pCustomDataStructure;
    uint8 u8LogCount;

    /* Find pointers to cluster */
    if(eZCL_FindCluster(APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_STATISTICS, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&pCustomDataStructure) != E_ZCL_SUCCESS)
    {
        return E_ZCL_CMDS_FAILURE;
    }

    for( u8LogCount = 0 ; u8LogCount < CLD_APPLIANCE_STATISTICS_ATTR_LOG_QUEUE_MAX_SIZE; u8LogCount++)
    {
        if( (pCustomDataStructure->asLogTable[u8LogCount].u32LogID == u32LogId) && (pCustomDataStructure->asLogTable[u8LogCount].u8LogLength <= CLD_APPLIANCE_STATISTICS_ATTR_LOG_MAX_SIZE))
            {
                pCustomDataStructure->asLogTable[u8LogCount].u8LogLength = (CLD_APPLIANCE_STATISTICS_ATTR_LOG_MAX_SIZE + 1);
                return E_ZCL_CMDS_SUCCESS;
            }
    }

    return E_ZCL_CMDS_NOT_FOUND;

}

/****************************************************************************
 **
 ** NAME:       eCLD_ASCGetLogEntry
 **
 ** DESCRIPTION:
 ** Gives the log entry
 **
 ** PARAMETERS:                 Name                    Usage
 ** uint8                       u8SourceEndPointId      Endpoint id
 ** uint32                      u32LogId                Log Id
 ** tsCLD_LogTable**            ppsLogTable             Pointer to Pointer to log entry
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_CommandStatus eCLD_ASCGetLogEntry(
                uint8                                             u8SourceEndPointId,
                uint32                                            u32LogId,
                tsCLD_LogTable                                    **ppsLogTable)
{
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_ApplianceStatisticsCustomDataStructure *pCustomDataStructure;
    uint8 u8LogCount;

    /* Find pointers to cluster */
    if(eZCL_FindCluster(APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_STATISTICS, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&pCustomDataStructure) != E_ZCL_SUCCESS)
    {
        return E_ZCL_CMDS_FAILURE;
    }

    for( u8LogCount = 0 ; u8LogCount < CLD_APPLIANCE_STATISTICS_ATTR_LOG_QUEUE_MAX_SIZE; u8LogCount++)
    {
        if( pCustomDataStructure->asLogTable[u8LogCount].u32LogID == u32LogId  && (pCustomDataStructure->asLogTable[u8LogCount].u8LogLength <= CLD_APPLIANCE_STATISTICS_ATTR_LOG_MAX_SIZE))
            {
                 *ppsLogTable = (tsCLD_LogTable *)(&(pCustomDataStructure->asLogTable[u8LogCount]));
                 DBG_vPrintf(TRACE_APPLIANCE_STATISTICS, "ADDR = %016lx = %016lx\n",ppsLogTable,(*ppsLogTable));
                 return E_ZCL_CMDS_SUCCESS;
            }
    }

    return E_ZCL_CMDS_NOT_FOUND;
}
/****************************************************************************
 **
 ** NAME:       eCLD_ASCGetLogsAvailable
 **
 ** DESCRIPTION:
 ** Check all the logs available
 **
 ** PARAMETERS:                 Name                    Usage
 ** uint8                       u8SourceEndPointId      Endpoint id
 ** uint32*                     pu32LogId                  Pointer to Log Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_CommandStatus eCLD_ASCGetLogsAvailable(uint8 u8SourceEndPointId,
                                                   uint32*     pu32LogId,
                                                   uint8*      pu8LogIdCount)
{
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_ApplianceStatisticsCustomDataStructure *pCustomDataStructure;
    uint8 u8LogCount,u8LogAvailbleCount = 0;

    /* Find pointers to cluster */
    if(eZCL_FindCluster(APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_STATISTICS, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&pCustomDataStructure) != E_ZCL_SUCCESS)
    {
        return E_ZCL_CMDS_FAILURE;
    }

    if(pu32LogId == NULL || pu8LogIdCount == NULL)
    {
        return E_ZCL_CMDS_INVALID_FIELD;
    }
    
    for( u8LogCount = 0 ; u8LogCount < CLD_APPLIANCE_STATISTICS_ATTR_LOG_QUEUE_MAX_SIZE; u8LogCount++)
    {
        if( pCustomDataStructure->asLogTable[u8LogCount].u8LogLength <= CLD_APPLIANCE_STATISTICS_ATTR_LOG_MAX_SIZE )
            {
                pu32LogId[u8LogAvailbleCount] = pCustomDataStructure->asLogTable[u8LogCount].u32LogID;
                (u8LogAvailbleCount)++;
                
                if(u8LogAvailbleCount >= (*pu8LogIdCount))
                {
                    *pu8LogIdCount = u8LogAvailbleCount;
                    return E_ZCL_CMDS_INSUFFICIENT_SPACE;
                }
            }
    }
    
    *pu8LogIdCount = u8LogAvailbleCount;
    return E_ZCL_CMDS_SUCCESS;

}
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
#endif                    
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

