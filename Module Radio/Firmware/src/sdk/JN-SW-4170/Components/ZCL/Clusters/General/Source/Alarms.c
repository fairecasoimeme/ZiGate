/*****************************************************************************
 *
 * MODULE:             Alarms Cluster
 *
 * COMPONENT:          Alarms.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Alarms cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/Alarms.c $
 *
 * $Revision: 90669 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2017-10-17 18:21:47 +0200 (Tue, 17 Oct 2017) $
 *
 * $Id: Alarms.c 90669 2017-10-17 16:21:47Z nxp29741 $
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
#include "zps_apl_aib.h"

#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_options.h"
#include "string.h"
#include "Alarms.h"
#include "Alarms_internal.h"

#include "dbg.h"

#ifdef DEBUG_CLD_ALARMS
#define TRACE_ALARMS    TRUE
#else
#define TRACE_ALARMS    FALSE
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
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
    const tsZCL_CommandDefinition asCLD_AlarmClusterCommandDefinitions[] = {
        {E_CLD_ALARMS_CMD_RESET_ALARM,           E_ZCL_CF_RX},     /* Mandatory */
        {E_CLD_ALARMS_CMD_RESET_ALL_ALARMS,      E_ZCL_CF_RX},     /* Mandatory */
        {E_CLD_ALARMS_CMD_GET_ALARM,             E_ZCL_CF_RX},     /* Mandatory */    
        {E_CLD_ALARMS_CMD_RESET_ALARM_LOG,       E_ZCL_CF_RX}, 
        
        {E_CLD_ALARMS_CMD_ALARM,                 E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_ALARMS_CMD_GET_ALARM_RESPONSE,    E_ZCL_CF_TX},     /* Mandatory */    
    };
#endif
const tsZCL_AttributeDefinition asCLD_AlarmsClusterAttributeDefinitions[] = {
#ifdef ALARMS_SERVER
    #ifdef CLD_ALARMS_ATTR_ALARM_COUNT
        {E_CLD_ALARMS_ATTR_ID_ALARM_COUNT,          E_ZCL_AF_RD,                E_ZCL_UINT16,  (uint32)(&((tsCLD_Alarms*)(0))->u16AlarmCount),0},   /* Optional  */
    #endif
#endif
    {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,         (E_ZCL_AF_RD|E_ZCL_AF_GA),  E_ZCL_UINT16,  (uint32)(&((tsCLD_Alarms*)(0))->u16ClusterRevision),0},   /* Mandatory  */

};

tsZCL_ClusterDefinition sCLD_Alarms = {
        GENERAL_CLUSTER_ID_ALARMS,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_AlarmsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_AlarmsClusterAttributeDefinitions,
        NULL
        #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED        
            ,
            (sizeof(asCLD_AlarmClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
            (tsZCL_CommandDefinition*)asCLD_AlarmClusterCommandDefinitions         
        #endif        
};

uint8 au8AlarmsAttributeControlBits[(sizeof(asCLD_AlarmsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_IdentifyCreateIdentify
 **
 ** DESCRIPTION:
 ** Creates an identify cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teCLD_IdentifyStatus
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_AlarmsCreateAlarms(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits,
                tsCLD_AlarmsCustomDataStructure    *psCustomDataStructure)
{

    #ifdef ALARMS_SERVER
        int n;
    #endif  
    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) || (psCustomDataStructure==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    // cluster data
    vZCL_InitializeClusterInstance(
               psClusterInstance, 
               bIsServer,
               psClusterDefinition,
               pvEndPointSharedStructPtr,
               pu8AttributeControlBits,
               psCustomDataStructure,
               eCLD_AlarmsCommandHandler);

    psCustomDataStructure->sCustomCallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_CUSTOM;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId = psClusterDefinition->u16ClusterEnum;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.pvCustomData = (void *)&psCustomDataStructure->sCallBackMessage;
    psCustomDataStructure->sCustomCallBackEvent.psClusterInstance = psClusterInstance; 
    
    /* Initialise attributes */
    #ifdef ALARMS_SERVER
        #ifdef CLD_ALARMS_ATTR_ALARM_COUNT
            ((tsCLD_Alarms*)pvEndPointSharedStructPtr)->u16AlarmCount = 0;
        #endif

         /* initialise lists */
        vDLISTinitialise(&((tsCLD_AlarmsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr)->lAlarmsAllocList);
        vDLISTinitialise(&((tsCLD_AlarmsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr)->lAlarmsDeAllocList);

        for(n=0; n < CLD_ALARMS_MAX_NUMBER_OF_ALARMS; n++)
        {
            /* add all header slots to the to free list */
            vDLISTaddToTail(&psCustomDataStructure->lAlarmsDeAllocList, (DNODE *)&psCustomDataStructure->asAlarmsTableEntry[n]);
        }
    #endif
        
    ((tsCLD_Alarms*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_ALARMS_CLUSTER_REVISION;
    
    //  register timer
    return E_ZCL_SUCCESS;

}

#ifdef ALARMS_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_AlarmsSignalAlarm
 **
 ** DESCRIPTION:
 ** Should be called by clusters wishing to signal an alarm condition
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 ** uint8                       u8AlarmCode                    Alarm Code
 ** uint16                      u16ClusterId                   Cluster Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_AlarmsSignalAlarm(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint8                       u8AlarmCode,
                    uint16                      u16ClusterId)
{
    tsZCL_ClusterInstance       *psClusterInstance;
    tsZCL_EndPointDefinition    *psEndPointDefinition;

    teZCL_Status eStatus;
    tsCLD_AlarmsAlarmCommandPayload sPayload;

    sPayload.u8AlarmCode = u8AlarmCode;
    sPayload.u16ClusterId = u16ClusterId;

    if((psDestinationAddress == NULL) || (pu8TransactionSequenceNumber == NULL))
    {
        return E_ZCL_ERR_PARAMETER_NULL;
    }

    /* Check end point is registered and cluster is present in the send device */
    eStatus = eZCL_SearchForEPentry(u8SourceEndPointId, &psEndPointDefinition);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return(eStatus);
    }

    eStatus = eZCL_SearchForClusterEntry(u8SourceEndPointId, GENERAL_CLUSTER_ID_ALARMS, TRUE, &psClusterInstance);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return(eStatus);
    }

    /* Add alarm to log */
    eStatus = eCLD_AlarmsAddAlarmToLog(psEndPointDefinition,
                                       psClusterInstance,
                                       u8AlarmCode,
                                       u16ClusterId);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_ALARMS, "eCLD_AlarmsAddAlarmToLog Error: %d\r\n", eStatus);
        return eStatus;
    }

    /* Send alarm message */
    eStatus = eCLD_AlarmsCommandAlarmCommandSend(u8SourceEndPointId,
                                                 u8DestinationEndPointId,
                                                 psDestinationAddress,
                                                 pu8TransactionSequenceNumber,
                                                 &sPayload);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_ALARMS, "eCLD_AlarmsCommandAlarmCommandSend Error: %d\r\n", eStatus);
        return eStatus;
    }

    return E_ZCL_SUCCESS;

}
#endif
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

