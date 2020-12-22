/*****************************************************************************
 *
 * MODULE:             Door Lock Cluster
 *
 * COMPONENT:          DoorLock.c
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Door Lock cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Source/DoorLock.c $
 *
 * $Revision: 53274 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-04-16 11:39:09 +0530 (Tue, 16 Apr 2013) $
 *
 * $Id: DoorLock.c 53274 2013-04-16 06:09:09Z nxp57621 $
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
#include "DoorLock.h"
#include "DoorLock_internal.h"


#include "dbg.h"

#ifdef DEBUG_CLD_DOOR_LOCK
#define TRACE_DOOR_LOCK    TRUE
#else
#define TRACE_DOOR_LOCK    FALSE
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#if defined(CLD_DOOR_LOCK) && !defined(DOOR_LOCK_SERVER) && !defined(DOOR_LOCK_CLIENT)
#error You Must Have either DOOR_LOCK_SERVER and/or DOOR_LOCK_CLIENT defined in zcl_options.h
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#ifdef CLD_DOOR_LOCK
/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
#ifdef DOOR_LOCK_SERVER
PRIVATE teZCL_Status  eCLD_DoorLockSceneEventHandler(
                        teZCL_SceneEvent            eEvent,
                        tsZCL_EndPointDefinition   *psEndPointDefinition,
                        tsZCL_ClusterInstance      *psClusterInstance);
#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
    const tsZCL_CommandDefinition asCLD_DoorLockClusterCommandDefinitions[] = {
        {E_CLD_DOOR_LOCK_CMD_LOCK,                E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_DOOR_LOCK_CMD_UNLOCK,              E_ZCL_CF_RX|E_ZCL_CF_TX}    
    };
#endif


const tsZCL_AttributeDefinition asCLD_DoorLockClusterAttributeDefinitions[] = {
#ifdef DOOR_LOCK_SERVER
        {E_CLD_DOOR_LOCK_ATTR_ID_LOCK_STATE,                       (E_ZCL_AF_RD|E_ZCL_AF_RP|E_ZCL_AF_SE),   E_ZCL_ENUM8,   (uint32)(&((tsCLD_DoorLock*)(0))->eLockState),0},    /* Mandatory */

        {E_CLD_DOOR_LOCK_ATTR_ID_LOCK_TYPE,                         E_ZCL_AF_RD,                            E_ZCL_ENUM8,   (uint32)(&((tsCLD_DoorLock*)(0))->eLockType),0},    /* Mandatory */
        
        {E_CLD_DOOR_LOCK_ATTR_ID_ACTUATOR_ENABLED,                  E_ZCL_AF_RD,                            E_ZCL_BOOL,    (uint32)(&((tsCLD_DoorLock*)(0))->bActuatorEnabled),0},    /* Mandatory */
        
    #ifdef CLD_DOOR_LOCK_ATTR_DOOR_STATE
        {E_CLD_DOOR_LOCK_ATTR_ID_DOOR_STATE,                        (E_ZCL_AF_RD|E_ZCL_AF_RP),              E_ZCL_ENUM8,   (uint32)(&((tsCLD_DoorLock*)(0))->eDoorState),0},        /* Optional */
    #endif

    #ifdef CLD_DOOR_LOCK_ATTR_NUMBER_OF_DOOR_OPEN_EVENTS
        {E_CLD_DOOR_LOCK_ATTR_ID_NUMBER_OF_DOOR_OPEN_EVENTS,        (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT32,  (uint32)(&((tsCLD_DoorLock*)(0))->u32NumberOfDoorOpenEvent),0},    /* Optional */
    #endif

    #ifdef CLD_DOOR_LOCK_ATTR_NUMBER_OF_DOOR_CLOSED_EVENTS
        {E_CLD_DOOR_LOCK_ATTR_ID_NUMBER_OF_DOOR_CLOSED_EVENTS,      (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT32,   (uint32)(&((tsCLD_DoorLock*)(0))->u32NumberOfDoorClosedEvent),0},   /* Optional */
    #endif

    #ifdef CLD_DOOR_LOCK_ATTR_NUMBER_OF_MINUTES_DOOR_OPENED
        {E_CLD_DOOR_LOCK_ATTR_ID_NUMBER_OF_MINUTES_DOOR_OPENED,     (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT16,   (uint32)(&((tsCLD_DoorLock*)(0))->u16NumberOfMinutesDoorOpened),0},  /* Optional */
    #endif

    #ifdef CLD_DOOR_LOCK_ZIGBEE_SECUTRITY_LEVEL
        {E_CLD_DOOR_LOCK_ATTR_ID_ZIGBEE_SECURITY_LEVEL,              E_ZCL_AF_RD,                           E_ZCL_UINT8,    (uint32)(&((tsCLD_DoorLock*)(0))->u8ZigbeeSecurityLevel),0},        /* Optional */
    #endif
   
#endif    
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                     (E_ZCL_AF_RD|E_ZCL_AF_GA),             E_ZCL_UINT16,   (uint32)(&((tsCLD_DoorLock*)(0))->u16ClusterRevision),0},   /* Mandatory  */
    
    #if (defined DOOR_LOCK_SERVER) && (defined CLD_DOOR_LOCK_ATTRIBUTE_REPORTING_STATUS)
        {E_CLD_GLOBAL_ATTR_ID_ATTRIBUTE_REPORTING_STATUS,         (E_ZCL_AF_RD|E_ZCL_AF_GA),             E_ZCL_ENUM8,     (uint32)(&((tsCLD_DoorLock*)(0))->u8AttributeReportingStatus), 0},  /* Optional */
    #endif 
    };

#ifdef DOOR_LOCK_SERVER
    /* List of attributes in the scene extension table */
    tsZCL_SceneExtensionTable sCLD_DoorLockSceneExtensionTable =
    {
            eCLD_DoorLockSceneEventHandler,
            1,
            {E_CLD_DOOR_LOCK_ATTR_ID_LOCK_STATE}
    };

    tsZCL_ClusterDefinition sCLD_DoorLock = {
            CLOSURE_CLUSTER_ID_DOOR_LOCK,
            FALSE,
            E_ZCL_SECURITY_NETWORK,
            (sizeof(asCLD_DoorLockClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
            (tsZCL_AttributeDefinition*)asCLD_DoorLockClusterAttributeDefinitions,
            &sCLD_DoorLockSceneExtensionTable
            #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
                ,
                (sizeof(asCLD_DoorLockClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
                (tsZCL_CommandDefinition*)asCLD_DoorLockClusterCommandDefinitions
            #endif
    };
#else
    tsZCL_ClusterDefinition sCLD_DoorLock = {
            CLOSURE_CLUSTER_ID_DOOR_LOCK,
            FALSE,
            E_ZCL_SECURITY_NETWORK,
            (sizeof(asCLD_DoorLockClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
            (tsZCL_AttributeDefinition*)asCLD_DoorLockClusterAttributeDefinitions,
            NULL
            #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
                ,
                (sizeof(asCLD_DoorLockClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
                (tsZCL_CommandDefinition*)asCLD_DoorLockClusterCommandDefinitions
            #endif
    };
#endif
uint8 au8DoorLockAttributeControlBits[(sizeof(asCLD_DoorLockClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_DoorLockCreateDoorLock
 **
 ** DESCRIPTION:
 ** Creates a Door Lock cluster
 **
 ** PARAMETERS:                 Name                                Usage
 ** tsZCL_ClusterInstance      *psClusterInstance                   Cluster structure
 ** bool_t                      bIsServer                           Server Client flag
 ** tsZCL_ClusterDefinition    *psClusterDefinition                 Cluster Definition
 ** void                       *pvEndPointSharedStructPtr           EndPoint Shared Structure
 ** uint8                      *pu8AttributeControlBits             Attribute Control Bits
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_DoorLockCreateDoorLock(
                tsZCL_ClusterInstance                   *psClusterInstance,
                bool_t                                  bIsServer,
                tsZCL_ClusterDefinition                 *psClusterDefinition,
                void                                    *pvEndPointSharedStructPtr,
                uint8                                   *pu8AttributeControlBits)
{

    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
           if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL)  )
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
                       NULL,
                       eCLD_DoorLockCommandHandler);

        if(psClusterInstance->pvEndPointSharedStructPtr != NULL)
        {
#ifdef DOOR_LOCK_SERVER
            /* Set attribute default values */
            ((tsCLD_DoorLock*)pvEndPointSharedStructPtr)->eLockState = 0;
            ((tsCLD_DoorLock*)pvEndPointSharedStructPtr)->eLockType = 0;
            ((tsCLD_DoorLock*)pvEndPointSharedStructPtr)->bActuatorEnabled = FALSE;

        #ifdef CLD_DOOR_LOCK_ATTR_DOOR_STATE
            ((tsCLD_DoorLock*)pvEndPointSharedStructPtr)->eDoorState = 0;
        #endif

        #ifdef CLD_DOOR_LOCK_ATTR_NUMBER_OF_DOOR_OPEN_EVENTS
            ((tsCLD_DoorLock*)pvEndPointSharedStructPtr)->u32NumberOfDoorOpenEvent = 0;
        #endif

        #ifdef CLD_DOOR_LOCK_ATTR_NUMBER_OF_DOOR_CLOSED_EVENTS
            ((tsCLD_DoorLock*)pvEndPointSharedStructPtr)->u32NumberOfDoorClosedEvent = 0;
        #endif

        #ifdef CLD_DOOR_LOCK_ATTR_NUMBER_OF_MINUTES_DOOR_OPENED
            ((tsCLD_DoorLock*)pvEndPointSharedStructPtr)->u16NumberOfMinutesDoorOpened = 0;
        #endif

        #ifdef CLD_DOOR_LOCK_ZIGBEE_SECUTRITY_LEVEL
            ((tsCLD_DoorLock*)pvEndPointSharedStructPtr)->u8ZigbeeSecurityLevel = 0;
        #endif
#endif       
            ((tsCLD_DoorLock*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_DOOR_LOCK_CLUSTER_REVISION;
        }

    /* As this cluster has reportable attributes enable default reporting */
    vZCL_SetDefaultReporting(psClusterInstance);

    return E_ZCL_SUCCESS;

}

#ifdef DOOR_LOCK_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_DoorLockSetLockState
 **
 ** DESCRIPTION:
 ** Can be used by cluster to set the state of the Lock State attribute
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          EndPoint Id
 ** teCLD_DoorLock_LockState    eLock                       Different lock states like Lock or Unlock
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_DoorLockSetLockState(uint8 u8SourceEndPointId, teCLD_DoorLock_LockState eLock)
{

    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    void *psCustomDataStructure;
    tsZCL_CallBackEvent sZCL_CallBackEvent;
    tsCLD_DoorLock *psSharedStruct;

    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(CLOSURE_CLUSTER_ID_DOOR_LOCK, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }

    DBG_vPrintf(TRACE_DOOR_LOCK, "\neCLD_DoorLockSetLockState(%d,%d)", u8SourceEndPointId, eLock);

    /* Point to shared struct */
    psSharedStruct = (tsCLD_DoorLock *)psClusterInstance->pvEndPointSharedStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    /* Set attribute state */
    psSharedStruct->eLockState =  eLock;
   
    /* Generate a callback to let the user know that an update event occurred */
    sZCL_CallBackEvent.u8EndPoint           = psEndPointDefinition->u8EndPointNumber;
    sZCL_CallBackEvent.psClusterInstance    = psClusterInstance;
    sZCL_CallBackEvent.pZPSevent            = NULL;
    sZCL_CallBackEvent.eEventType           = E_ZCL_CBET_CLUSTER_UPDATE;
    psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return E_ZCL_SUCCESS;

}


/****************************************************************************
 **
 ** NAME:       eCLD_DoorLockGetLockState
 **
 ** DESCRIPTION:
 ** Can be used by other clusters to get the state of the Lock state attribute
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          EndPoint Id
 ** teCLD_DoorLock_LockState    *eLock                      Pointer to Lock state
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_DoorLockGetLockState(uint8 u8SourceEndPointId, teCLD_DoorLock_LockState *peLock)
{

    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    void *psCustomDataStructure;

    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(CLOSURE_CLUSTER_ID_DOOR_LOCK, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }

    /* Get attribute state */
    *peLock = ((tsCLD_DoorLock *)(psClusterInstance->pvEndPointSharedStructPtr))->eLockState;
    

    return E_ZCL_SUCCESS;

}
#endif   /*#define DOOR_LOCK_SERVER */
#ifdef DOOR_LOCK_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_DoorLockSceneEventHandler
 **
 ** DESCRIPTION:
 ** Handles events generated by a door lock cluster (if present)
 **
 ** PARAMETERS:               Name                        Usage
 ** teZCL_SceneEvent          eEvent                      Scene Event
 ** tsZCL_EndPointDefinition *psEndPointDefinition        End Point Definition
 ** tsZCL_ClusterInstance    *psClusterInstance           Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PRIVATE  teZCL_Status eCLD_DoorLockSceneEventHandler(
                        teZCL_SceneEvent            eEvent,
                        tsZCL_EndPointDefinition   *psEndPointDefinition,
                        tsZCL_ClusterInstance      *psClusterInstance)
{

    tsZCL_CallBackEvent sZCL_CallBackEvent;

    switch(eEvent)
    {

    case E_ZCL_SCENE_EVENT_SAVE:
        DBG_vPrintf(TRACE_DOOR_LOCK, "\nLC: Scene Event: Save");
        break;

    case E_ZCL_SCENE_EVENT_RECALL:
        DBG_vPrintf(TRACE_DOOR_LOCK, "\nLC: Scene Event: Recall");

        /* Inform the application that the cluster has just been updated */
        sZCL_CallBackEvent.u8EndPoint = psEndPointDefinition->u8EndPointNumber;
        sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
        sZCL_CallBackEvent.pZPSevent = NULL;
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_UPDATE;

        // call user
        psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

        break;

    }

    return E_ZCL_SUCCESS;
}

#endif
#ifdef CLD_DOOR_LOCK_ZIGBEE_SECUTRITY_LEVEL
/****************************************************************************
 **
 ** NAME:       eCLD_DoorLockSetSecurityLevel
 **
 ** DESCRIPTION:
 ** Can be used by cluster to set the security level
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          EndPoint Id
 ** uint8                        u8SecurityLevel             Security Level
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_DoorLockSetSecurityLevel(uint8 u8SourceEndPointId,bool bServer,uint8 u8SecurityLevel)
{

    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    void *psCustomDataStructure;
    tsZCL_CallBackEvent sZCL_CallBackEvent;
    #ifdef DOOR_LOCK_SERVER
        tsCLD_DoorLock *psSharedStruct;
    #endif
    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(CLOSURE_CLUSTER_ID_DOOR_LOCK, u8SourceEndPointId, bServer, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }

    DBG_vPrintf(TRACE_DOOR_LOCK, "\neCLD_DoorLockSetLockState(%d,%d)", u8SourceEndPointId, u8SecurityLevel);

    #ifdef DOOR_LOCK_SERVER
        /* Point to shared struct */
        psSharedStruct = (tsCLD_DoorLock *)psClusterInstance->pvEndPointSharedStructPtr;
    #endif
    
    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    if(u8SecurityLevel)
    {
        eZCL_SetSupportedSecurity(E_ZCL_SECURITY_APPLINK);
        psClusterInstance->psClusterDefinition->u8ClusterControlFlags = E_ZCL_SECURITY_APPLINK;
    }else{
        eZCL_SetSupportedSecurity(E_ZCL_SECURITY_NETWORK);
        psClusterInstance->psClusterDefinition->u8ClusterControlFlags = E_ZCL_SECURITY_NETWORK;
    }
    
    #ifdef DOOR_LOCK_SERVER
        /* Set attribute state */
        psSharedStruct->u8ZigbeeSecurityLevel =  u8SecurityLevel;
    #endif
    
    /* Generate a callback to let the user know that an update event occurred */
    sZCL_CallBackEvent.u8EndPoint           = psEndPointDefinition->u8EndPointNumber;
    sZCL_CallBackEvent.psClusterInstance    = psClusterInstance;
    sZCL_CallBackEvent.pZPSevent            = NULL;
    sZCL_CallBackEvent.eEventType           = E_ZCL_CBET_CLUSTER_UPDATE;
    psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return E_ZCL_SUCCESS;

}
#endif
#endif   /* #define CLD_DOOR_LOCK */
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

