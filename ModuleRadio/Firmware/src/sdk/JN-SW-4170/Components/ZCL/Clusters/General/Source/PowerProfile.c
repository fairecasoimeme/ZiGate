/*****************************************************************************
 *
 * MODULE:             Power Profile Cluster
 *
 * COMPONENT:          PowerProfile.c
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Power Profile cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA12_1v0/ZCL/Clusters/EnergyAtHome/Source/PowerProfile.c $
 *
 * $Revision: 55804 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-08-05 17:56:09 +0530 (Mon, 05 Aug 2013) $
 *
 * $Id: PowerProfile.c 55804 2013-08-05 12:26:09Z nxp57621 $
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

#include "zps_apl.h"
#include "zps_apl_aib.h"

#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_options.h"
#include "string.h"
#include "PowerProfile.h"
#include "PowerProfile_internal.h"


#include "dbg.h"

#ifdef DEBUG_CLD_PP
#define TRACE_PP    TRUE
#else
#define TRACE_PP    FALSE
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#if defined(CLD_PP) && !defined(PP_SERVER) && !defined(PP_CLIENT)
#error You Must Have either PP_SERVER and/or PP_CLIENT defined in zcl_options.h
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#ifdef CLD_PP
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
    const tsZCL_CommandDefinition asCLD_PPClusterCommandDefinitions[] = {
        {E_CLD_PP_CMD_POWER_PROFILE_REQ,                                   E_ZCL_CF_RX},
        {E_CLD_PP_CMD_POWER_PROFILE_STATE_REQ,                             E_ZCL_CF_RX},
        {E_CLD_PP_CMD_GET_POWER_PROFILE_PRICE_RSP,                         E_ZCL_CF_RX},
        {E_CLD_PP_CMD_GET_OVERALL_SCHEDULE_PRICE_RSP,                      E_ZCL_CF_RX},
        {E_CLD_PP_CMD_ENERGY_PHASES_SCHEDULE_NOTIFICATION,                 E_ZCL_CF_RX},
        {E_CLD_PP_CMD_ENERGY_PHASES_SCHEDULE_RSP,                          E_ZCL_CF_RX},
        {E_CLD_PP_CMD_POWER_PROFILE_SCHEDULE_CONSTRAINTS_REQ,              E_ZCL_CF_RX},
        {E_CLD_PP_CMD_ENERGY_PHASES_SCHEDULE_STATE_REQ,                    E_ZCL_CF_RX},
        {E_CLD_PP_CMD_GET_POWER_PROFILE_PRICE_EXTENDED_RSP,                E_ZCL_CF_RX},

        {E_CLD_PP_CMD_POWER_PROFILE_NOTIFICATION,                          E_ZCL_CF_TX},
        {E_CLD_PP_CMD_POWER_PROFILE_RSP,                                   E_ZCL_CF_TX},
        {E_CLD_PP_CMD_POWER_PROFILE_STATE_RSP,                             E_ZCL_CF_TX},
        {E_CLD_PP_CMD_GET_POWER_PROFILE_PRICE,                             E_ZCL_CF_TX},
        {E_CLD_PP_CMD_POWER_PROFILE_STATE_NOTIFICATION,                    E_ZCL_CF_TX},
        {E_CLD_PP_CMD_GET_OVERALL_SCHEDULE_PRICE,                          E_ZCL_CF_TX},
        {E_CLD_PP_CMD_ENERGY_PHASES_SCHEDULE_REQ,                          E_ZCL_CF_TX},       
        {E_CLD_PP_CMD_ENERGY_PHASES_SCHEDULE_STATE_RSP,                    E_ZCL_CF_TX},       
        {E_CLD_PP_CMD_ENERGY_PHASES_SCHEDULE_STATE_NOTIFICATION,           E_ZCL_CF_TX},
        {E_CLD_PP_CMD_GET_POWER_PROFILE_SCHEDULE_CONSTRAINTS_NOTIFICATION, E_ZCL_CF_TX},
        {E_CLD_PP_CMD_GET_POWER_PROFILE_SCHEDULE_CONSTRAINTS_RSP,          E_ZCL_CF_TX},
        {E_CLD_PP_CMD_GET_POWER_PROFILE_PRICE_EXTENDED,                    E_ZCL_CF_TX}                    
    };
#endif


const tsZCL_AttributeDefinition asCLD_PPClusterAttrDefs[] = {
#ifdef PP_SERVER
        {E_CLD_PP_ATTR_ID_TOTAL_PROFILE_NUM,                E_ZCL_AF_RD,                            E_ZCL_UINT8,    (uint32)(&((tsCLD_PP*)(0))->u8TotalProfileNum),      0},    /* Mandatory */

        {E_CLD_PP_ATTR_ID_MULTIPLE_SCHEDULING,              E_ZCL_AF_RD,                            E_ZCL_BOOL,     (uint32)(&((tsCLD_PP*)(0))->bMultipleScheduling),    0},     /* Mandatory */
        
        {E_CLD_PP_ATTR_ID_ENERGY_FORMATTING,                E_ZCL_AF_RD,                            E_ZCL_BMAP8,    (uint32)(&((tsCLD_PP*)(0))->u8EnergyFormatting),     0},     /* Mandatory */
        
        {E_CLD_PP_ATTR_ID_ENERGY_REMOTE,                   (E_ZCL_AF_RD|E_ZCL_AF_RP),               E_ZCL_BOOL,     (uint32)(&((tsCLD_PP*)(0))->bEnergyRemote),          0},     /* Mandatory */

        {E_CLD_PP_ATTR_ID_SCHEDULE_MODE,                   (E_ZCL_AF_RD|E_ZCL_AF_WR|E_ZCL_AF_RP),   E_ZCL_BMAP8,    (uint32)(&((tsCLD_PP*)(0))->u8ScheduleMode),         0},     /* Mandatory */
    
#endif        
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,            (E_ZCL_AF_RD|E_ZCL_AF_GA),               E_ZCL_UINT16,   (uint32)(&((tsCLD_PP*)(0))->u16ClusterRevision),     0},     /* Mandatory  */   
                   
    #if (defined PP_SERVER) && (defined CLD_PP_ATTR_ATTRIBUTE_REPORTING_STATUS)
        {E_CLD_GLOBAL_ATTR_ID_ATTRIBUTE_REPORTING_STATUS,  (E_ZCL_AF_RD|E_ZCL_AF_GA),               E_ZCL_ENUM8,   (uint32)(&((tsCLD_PP*)(0))->u8AttributeReportingStatus), 0},  /* Optional */
    #endif
};

tsZCL_ClusterDefinition sCLD_PP = {
        GENERAL_CLUSTER_ID_PP,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_PPClusterAttrDefs) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_PPClusterAttrDefs,
        NULL
        #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED        
            ,
            (sizeof(asCLD_PPClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
            (tsZCL_CommandDefinition*)asCLD_PPClusterCommandDefinitions         
        #endif        
    };

uint8 au8PPAttributeControlBits[(sizeof(asCLD_PPClusterAttrDefs) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_PPCreatePP
 **
 ** DESCRIPTION:
 ** Creates a Poll Control cluster
 **
 ** PARAMETERS:                             Name                                Usage
 ** tsZCL_ClusterInstance                   *psClusterInstance                   Cluster structure
 ** bool_t                                  bIsServer                           Server Client flag
 ** tsZCL_ClusterDefinition                 *psClusterDefinition                 Cluster Definition
 ** void                                    *pvEndPointSharedStructPtr           EndPoint Shared Structure
 ** uint8                                   *pu8AttributeControlBits             Attribute Control Bits
 ** tsCLD_PPCustomDataStructure             *psCustomDataStructure               Pointer to Custom Data Structure
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_PPCreatePowerProfile(
                tsZCL_ClusterInstance                   *psClusterInstance,
                bool_t                                  bIsServer,
                tsZCL_ClusterDefinition                 *psClusterDefinition,
                void                                    *pvEndPointSharedStructPtr,
                uint8                                   *pu8AttributeControlBits,
                tsCLD_PPCustomDataStructure             *psCustomDataStructure)
{

    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
           if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL) ||
           (psCustomDataStructure==NULL))
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
                   eCLD_PPCommandHandler);
    
    psCustomDataStructure->sCustomCallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_CUSTOM;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId = psClusterDefinition->u16ClusterEnum;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.pvCustomData = (void *)&psCustomDataStructure->sCallBackMessage;
    psCustomDataStructure->sCustomCallBackEvent.psClusterInstance = psClusterInstance; 

    if(pvEndPointSharedStructPtr!=NULL)
	{
#ifdef PP_SERVER
        /* Set attribute default values */
		((tsCLD_PP*)pvEndPointSharedStructPtr)->u8TotalProfileNum       =       0;
		((tsCLD_PP*)pvEndPointSharedStructPtr)->bMultipleScheduling     =   FALSE;
		((tsCLD_PP*)pvEndPointSharedStructPtr)->u8EnergyFormatting      =   0x01;
		((tsCLD_PP*)pvEndPointSharedStructPtr)->bEnergyRemote           =   FALSE;
		((tsCLD_PP*)pvEndPointSharedStructPtr)->u8ScheduleMode          =   CLD_PP_ATTR_SCHEDULE_MODE_GREENEST;
#endif        
        ((tsCLD_PP*)pvEndPointSharedStructPtr)->u16ClusterRevision      =   CLD_PP_CLUSTER_REVISION;
	}

    /* As this cluster has reportable attributes enable default reporting */
    vZCL_SetDefaultReporting(psClusterInstance);
    
    return E_ZCL_SUCCESS;
}

#ifdef PP_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_PPSchedule
 **
 ** DESCRIPTION:
 ** Used by cluster to update its attributes
 **
 **
 ** RETURN:
 ** teZCL_Status
 ** 
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_PPSchedule(void)
{
    teZCL_Status eStatus = E_ZCL_SUCCESS;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_PPCustomDataStructure *psCustomDataStructure;
    uint8 u8NumEndpoints,u8EntryPosition,i = 0;
    
    static uint32 u32CurrentTime;
    static bool bRunning,bCount,bProfileEnded;
    u8NumEndpoints = u8ZCL_GetNumberOfEndpointsRegistered();
    
    /* Update clusters on each end point if any */
    for(i = 0; i < u8NumEndpoints; i++)
    {
        eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_PP, u8ZCL_GetEPIdFromIndex(i), TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
        if(eStatus != E_ZCL_SUCCESS)
        {
            continue;
        }
                
        // get EP mutex
        #ifndef COOPERATIVE
            eZCL_GetMutex(psEndPointDefinition);
        #endif

        
        for(u8EntryPosition= 0 ; u8EntryPosition < CLD_PP_NUM_OF_POWER_PROFILES ; u8EntryPosition++ )
        {
            if(psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileId != 0)
            {
                if(bCount)
                {
                    if( u32CurrentTime > 0){
                        u32CurrentTime--;
                    }else
                    {
                        bCount = FALSE;
                        if(psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileState == E_CLD_PP_STATE_PROGRAMMED)
                        {
                            psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileState = E_CLD_PP_STATE_RUNNING;
                        }
                        else if(psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileState == E_CLD_PP_STATE_WAITING_TO_START)
                        {
                            if(psCustomDataStructure->bOverrideRunning)
                            {
                                psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileState = E_CLD_PP_STATE_RUNNING;
                                psCustomDataStructure->bOverrideRunning = FALSE;
                                bRunning = FALSE;
                            }else{
                                eCLD_PPSetPowerProfileState(u8ZCL_GetEPIdFromIndex(i),psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileId,E_CLD_PP_STATE_RUNNING);
                                bRunning = TRUE;
                            }
                        }else if(psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileState == E_CLD_PP_STATE_RUNNING && bProfileEnded)
                        {
                            psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8ActiveEnergyPhaseId = 0xFF;
                            psCustomDataStructure->u8ActSchPhaseIndex = 0;
                            bRunning = FALSE;
                            eCLD_PPSetPowerProfileState(u8ZCL_GetEPIdFromIndex(i),psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileId,E_CLD_PP_STATE_ENDED);
                        }
                    }
                }
                

                switch(psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileState)
                {
                    case E_CLD_PP_STATE_PROGRAMMED:
                            if(!(bCount))
                            {
                                u32CurrentTime = 60 * (psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u16StartAfter);
                                bCount = TRUE;
                            }
                            break;
                    case E_CLD_PP_STATE_RUNNING:
                            if(bRunning)
                            {
                                if( psCustomDataStructure->u8ActSchPhaseIndex   <   (psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8NumOfScheduledEnergyPhases)){
                                    u32CurrentTime = 60 * (psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].asEnergyPhaseInfo[psCustomDataStructure->u8ActSchPhaseIndex].u16ExpectedDuration);
                                    psCustomDataStructure->u8ActSchPhaseIndex++;
                                    bRunning = FALSE;
                                }
                            }else if(u32CurrentTime == 0)
                            {
                                if( psCustomDataStructure->u8ActSchPhaseIndex   <   (psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8NumOfScheduledEnergyPhases)){
                                    u32CurrentTime = 60 * (psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].asEnergyPhaseDelay[psCustomDataStructure->u8ActSchPhaseIndex].u16ScheduleTime);
                                    psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8ActiveEnergyPhaseId = psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].asEnergyPhaseDelay[psCustomDataStructure->u8ActSchPhaseIndex].u8EnergyPhaseId;
                                    eCLD_PPSetPowerProfileState(u8ZCL_GetEPIdFromIndex(i),psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileId,E_CLD_PP_STATE_WAITING_TO_START);
                                }else{
                                    bProfileEnded = TRUE;
                                }
                                if(psCustomDataStructure->bOverrideRunning)
                                {
                                    psCustomDataStructure->bOverrideRunning = FALSE;
                                }
                            }
                            bCount = TRUE;
                            break;
                    case E_CLD_PP_STATE_WAITING_TO_START:
                            if(psCustomDataStructure->bOverrideRunning)
                            {
                                u32CurrentTime = 0;
                            }
                            bCount = TRUE;
                            break;

                    default:    
                            bCount = FALSE; 
                            bProfileEnded = FALSE;                          
                            break;                                          
                }

            
            }
        
        }
        #ifndef COOPERATIVE
            eZCL_ReleaseMutex(psEndPointDefinition);
        #endif

    }
    
    return eStatus;

}

/****************************************************************************
 **
 ** NAME:       eCLD_PPSetPowerProfileState
 **
 ** DESCRIPTION:
 ** Used by cluster to set state for a particular Power Profile Id
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          EndPoint Id
 ** uint8                       u8PowerProfileId            Power Profile Id
 ** teCLD_PP_PowerProfileState  ePowerProfileState          Power profile State to be moved
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_CommandStatus eCLD_PPSetPowerProfileState(
                                          uint8                         u8SourceEndPointId,
                                          uint8                         u8PowerProfileId,
                                          teCLD_PP_PowerProfileState    ePowerProfileState)
{
    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_PPCustomDataStructure *psCustomDataStructure;
    uint8 u8TransactionSeqNumber = 0;
    tsZCL_Address sZCL_Address = {0};
    tsCLD_PP_PowerProfileStatePayload sResponse;
    tsCLD_PPEntry   *psPPEntry;
    tsCLD_PP_PowerProfileRecord sPowerProfileRecord;
    
    sResponse.psPowerProfileRecord = &sPowerProfileRecord;
    
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_PP, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return E_ZCL_CMDS_FAILURE;
    }
    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif

    
    if((eCLD_PPGetPowerProfileEntry(u8SourceEndPointId,u8PowerProfileId,&psPPEntry) != E_ZCL_SUCCESS)){
        #ifndef COOPERATIVE
            eZCL_ReleaseMutex(psEndPointDefinition);
        #endif

        return E_ZCL_CMDS_NOT_FOUND;
    }
    
    switch(ePowerProfileState)
    {
        case E_CLD_PP_STATE_IDLE:
        {
            if(psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_ENDED){
                psPPEntry->u8PowerProfileState = E_CLD_PP_STATE_IDLE;
            }else{
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return E_ZCL_CMDS_INVALID_FIELD;
            }
            break;
        }
        case E_CLD_PP_STATE_PROGRAMMED:
        {
            /* Checks the last state of profile ID*/
            if(psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_IDLE){
                psPPEntry->u8PowerProfileState = E_CLD_PP_STATE_PROGRAMMED;
            }else{
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return E_ZCL_CMDS_INVALID_FIELD;
            }
        break;
        }
        case E_CLD_PP_STATE_RUNNING:
        {
            /* Checks the last state of profile ID*/
            if((psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_WAITING_TO_START) ||
               (psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_PROGRAMMED) || 
               (psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_PAUSED)){
                psPPEntry->u8PowerProfileState = E_CLD_PP_STATE_RUNNING;
            }else{
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return E_ZCL_CMDS_INVALID_FIELD;
            }
        break;
        }
        case E_CLD_PP_STATE_PAUSED:
        {
            /* Checks the last state of profile ID*/
            if((psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_RUNNING)){
                psPPEntry->u8PowerProfileState = E_CLD_PP_STATE_PAUSED;
            }else{
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return E_ZCL_CMDS_INVALID_FIELD;
            }
        break;
        }
        case E_CLD_PP_STATE_WAITING_TO_START:
        {
            /* Checks the last state of profile ID*/
            if((psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_RUNNING) ||
               (psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_PROGRAMMED) || 
               (psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_WAITING_PAUSED)){
                psPPEntry->u8PowerProfileState = E_CLD_PP_STATE_WAITING_TO_START;
            }else{
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return E_ZCL_CMDS_INVALID_FIELD;
            }
            break;
        }
        case E_CLD_PP_STATE_WAITING_PAUSED:
        {
            /* Checks the last state of profile ID*/
            if(psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_WAITING_TO_START) {
                psPPEntry->u8PowerProfileState = E_CLD_PP_STATE_WAITING_PAUSED;
            }else{
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return E_ZCL_CMDS_INVALID_FIELD;
            }
        break;
        }
        case E_CLD_PP_STATE_ENDED:
        {
            /* Checks the last state of profile ID*/
            if(psPPEntry->u8PowerProfileState == E_CLD_PP_STATE_RUNNING){
                psPPEntry->u8PowerProfileState = E_CLD_PP_STATE_ENDED;
            }else{
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return E_ZCL_CMDS_INVALID_FIELD;
            }
        break;
        }
        
        default:
            #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif

            return E_ZCL_CMDS_INVALID_VALUE;
            
    }

    #ifdef CLD_PP_BOUND_TX_WITH_APS_ACK_DISABLED
        sZCL_Address.eAddressMode = E_ZCL_AM_BOUND_NO_ACK;
    #else
        sZCL_Address.eAddressMode = E_ZCL_AM_BOUND;
    #endif    
    
    sResponse.u8PowerProfileCount = 1;
    sResponse.psPowerProfileRecord->u8PowerProfileId = psPPEntry->u8PowerProfileId;
    sResponse.psPowerProfileRecord->u8EnergyPhaseId = psPPEntry->u8ActiveEnergyPhaseId;
    sResponse.psPowerProfileRecord->bPowerProfileRemoteControl = psPPEntry->bPowerProfileRemoteControl;
    sResponse.psPowerProfileRecord->u8PowerProfileState = psPPEntry->u8PowerProfileState;
    
    eCLD_PPPowerProfileStateSend(u8SourceEndPointId,
                                0,
                                &sZCL_Address,
                                &u8TransactionSeqNumber,
                                E_CLD_PP_CMD_POWER_PROFILE_STATE_NOTIFICATION,
                                &sResponse);
    
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif

    return  E_ZCL_CMDS_SUCCESS;

}

/****************************************************************************
 **
 ** NAME:       eCLD_PPAddPowerProfileEntry
 **
 ** DESCRIPTION:
 ** Used by cluster to add an entry to Power profile 
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          EndPoint Id
 ** tsCLD_PowerProfileEntry     *psPowerProfileEntry        Pointer to Power Profile Entry
 **
 ** RETURN:
 ** teZCL_Status
 ** 
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_PPAddPowerProfileEntry(
                                            uint8                           u8SourceEndPointId,
                                            tsCLD_PPEntry                   *psPowerProfileEntry)   
{
    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_PPCustomDataStructure *psCustomDataStructure;
    uint8 u8EntryPosition;
    tsCLD_PPEntry   *psPPEntry;
    
    if(psPowerProfileEntry == NULL)
    {
        return E_ZCL_ERR_PARAMETER_NULL;
    }
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_PP, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }
        
    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif

    
    if((eCLD_PPGetPowerProfileEntry(u8SourceEndPointId,psPowerProfileEntry->u8PowerProfileId,&psPPEntry) == E_ZCL_SUCCESS)){
        memcpy(psPPEntry,psPowerProfileEntry,sizeof(tsCLD_PPEntry));
    }else if(((tsCLD_PP *)(psClusterInstance->pvEndPointSharedStructPtr))->u8TotalProfileNum == CLD_PP_NUM_OF_POWER_PROFILES)
    {
        #ifndef COOPERATIVE
            eZCL_ReleaseMutex(psEndPointDefinition);
        #endif

        return E_ZCL_ERR_INSUFFICIENT_SPACE;
    }else{
    for(u8EntryPosition = 0 ; u8EntryPosition < CLD_PP_NUM_OF_POWER_PROFILES; u8EntryPosition++)
    {    
        if(psCustomDataStructure->asPowerProfileEntry[u8EntryPosition].u8PowerProfileId == 0) {
            psPPEntry = (tsCLD_PPEntry *)&(psCustomDataStructure->asPowerProfileEntry[u8EntryPosition]);
            memcpy(&(psCustomDataStructure->asPowerProfileEntry[u8EntryPosition]),psPowerProfileEntry,sizeof(tsCLD_PPEntry));
            ((tsCLD_PP *)(psClusterInstance->pvEndPointSharedStructPtr))->u8TotalProfileNum++;
            break;
        }
    }
    }
    
    if(psPPEntry->u8NumOfScheduledEnergyPhases > 1 )
    {
        ((tsCLD_PP *)(psClusterInstance->pvEndPointSharedStructPtr))->bMultipleScheduling = TRUE;
    }else{
        ((tsCLD_PP *)(psClusterInstance->pvEndPointSharedStructPtr))->bMultipleScheduling = FALSE;
    }
    
    ((tsCLD_PP *)(psClusterInstance->pvEndPointSharedStructPtr))->bEnergyRemote = psPPEntry->bPowerProfileRemoteControl;

    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif

    
    return eStatus;

}

/****************************************************************************
 **
 ** NAME:       eCLD_PPRemovePowerProfileEntry
 **
 ** DESCRIPTION:
 ** Used by cluster to remove an entry to Power profile 
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          EndPoint Id
 ** uint8                       u8PowerProfileId            Power Profile Id
 **
 ** RETURN:
 ** teZCL_Status
 ** 
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_PPRemovePowerProfileEntry(
                                            uint8                           u8SourceEndPointId,
                                            uint8                           u8PowerProfileId)   
{
    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_PPCustomDataStructure *psCustomDataStructure;
    tsCLD_PPEntry   *psPPEntry;

    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_PP, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }
        
    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    if((eCLD_PPGetPowerProfileEntry(u8SourceEndPointId,u8PowerProfileId,&psPPEntry) == E_ZCL_SUCCESS)){
        psPPEntry->u8PowerProfileId = 0;
        ((tsCLD_PP *)(psClusterInstance->pvEndPointSharedStructPtr))->u8TotalProfileNum--;
    }
        
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif

    
    return eStatus;

}

/****************************************************************************
 **
 ** NAME:       eCLD_PPGetPowerProfileEntry
 **
 ** DESCRIPTION:
 ** Used by cluster to find an entry from Power profile 
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          EndPoint Id
 ** uint8                       u8PowerProfileId            Power Profile Id
 ** uint8                       *pu8EntryPosition           Holder to get location of entry
 **
 ** RETURN:
 ** teZCL_Status
 ** 
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_PPGetPowerProfileEntry(
                                            uint8                           u8SourceEndPointId,
                                            uint8                           u8PowerProfileId,
                                            tsCLD_PPEntry                   **ppsPowerProfileEntry) 
{
    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_PPCustomDataStructure *psCustomDataStructure;
    uint8 i;

    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_PP, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }
        
    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    for(i = 0 ; i < CLD_PP_NUM_OF_POWER_PROFILES; i++)
    { 
        if(psCustomDataStructure->asPowerProfileEntry[i].u8PowerProfileId == u8PowerProfileId) {
            *ppsPowerProfileEntry = (tsCLD_PPEntry *)(&(psCustomDataStructure->asPowerProfileEntry[i]));
            #ifndef COOPERATIVE
                eZCL_ReleaseMutex(psEndPointDefinition);
            #endif

            return E_ZCL_SUCCESS;
        }
    }
    
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif

    
    return E_ZCL_ERR_INVALID_VALUE;

}
#endif
#endif   /*#define PP_SERVER */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

