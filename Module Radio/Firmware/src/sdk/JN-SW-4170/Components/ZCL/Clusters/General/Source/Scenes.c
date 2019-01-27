/*****************************************************************************
 *
 * MODULE:             Scenes Cluster
 *
 * COMPONENT:          Scenes.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Scenes cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/Scenes.c $
 *
 * $Revision: 87468 $
 *
 * $LastChangedBy: nxp29772 $
 *
 * $LastChangedDate: 2017-03-23 13:30:37 +0100 (Thu, 23 Mar 2017) $
 *
 * $Id: Scenes.c 87468 2017-03-23 12:30:37Z nxp29772 $
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
#include "Scenes.h"
#include "Scenes_internal.h"
#include "zcl_internal.h"

#include "dbg.h"


#ifdef DEBUG_CLD_SCENES
#define TRACE_SCENES    TRUE
#else
#define TRACE_SCENES    FALSE
#endif

#ifdef CLD_SCENES

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
extern bool_t bFlag_SaveScenesNVM;
/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
    const tsZCL_CommandDefinition asCLD_ScenesClusterCommandDefinitions[] = {
        {E_CLD_SCENES_CMD_ADD,                 E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_SCENES_CMD_VIEW,                E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_SCENES_CMD_REMOVE,              E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */  
        {E_CLD_SCENES_CMD_REMOVE_ALL,          E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_SCENES_CMD_STORE,               E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_SCENES_CMD_RECALL,              E_ZCL_CF_RX},                 /* Mandatory */     
        {E_CLD_SCENES_CMD_GET_SCENE_MEMBERSHIP,E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
    #ifdef  CLD_SCENES_CMD_ENHANCED_ADD_SCENE
        {E_CLD_SCENES_CMD_ENHANCED_ADD_SCENE,  E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Optional */
    #endif
    #ifdef CLD_SCENES_CMD_ENHANCED_VIEW_SCENE
        {E_CLD_SCENES_CMD_ENHANCED_VIEW_SCENE, E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Optional */     
    #endif
    #ifdef CLD_SCENES_CMD_COPY_SCENE
        {E_CLD_SCENES_CMD_COPY_SCENE,          E_ZCL_CF_RX|E_ZCL_CF_TX}      /* Optional */ 
    #endif    
    };
#endif

tsZCL_AttributeDefinition asCLD_ScenesClusterAttributeDefinitions[] = {
#ifdef SCENES_SERVER
        {E_CLD_SCENES_ATTR_ID_SCENE_COUNT,          E_ZCL_AF_RD,  E_ZCL_UINT8,      (uint32)(&((tsCLD_Scenes*)(0))->u8SceneCount), 0},         /* Mandatory */
        {E_CLD_SCENES_ATTR_ID_CURRENT_SCENE,        E_ZCL_AF_RD,  E_ZCL_UINT8,      (uint32)(&((tsCLD_Scenes*)(0))->u8CurrentScene), 0},       /* Mandatory */
        {E_CLD_SCENES_ATTR_ID_CURRENT_GROUP,        E_ZCL_AF_RD,  E_ZCL_UINT16,     (uint32)(&((tsCLD_Scenes*)(0))->u16CurrentGroup), 0},      /* Mandatory */
        {E_CLD_SCENES_ATTR_ID_SCENE_VALID,          E_ZCL_AF_RD,  E_ZCL_BOOL,       (uint32)(&((tsCLD_Scenes*)(0))->bSceneValid), 0},          /* Mandatory */
        {E_CLD_SCENES_ATTR_ID_NAME_SUPPORT,         E_ZCL_AF_RD,  E_ZCL_BMAP8,      (uint32)(&((tsCLD_Scenes*)(0))->u8NameSupport), 0},        /* Mandatory */

    #ifdef CLD_SCENES_ATTR_LAST_CONFIGURED_BY
        {E_CLD_SCENES_ATTR_ID_LAST_CONFIGURED_BY,   E_ZCL_AF_RD,  E_ZCL_IEEE_ADDR,  (uint32)(&((tsCLD_Scenes*)(0))->u64LastConfiguredBy), 0},   /* Optional  */
    #endif
#endif    
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,     E_ZCL_AF_RD|E_ZCL_AF_GA,  E_ZCL_UINT16,     (uint32)(&((tsCLD_Scenes*)(0))->u16ClusterRevision),0},   /* Mandatory  */
        
    };
tsZCL_ClusterDefinition sCLD_Scenes = {
        GENERAL_CLUSTER_ID_SCENES,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_ScenesClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_ScenesClusterAttributeDefinitions,
        NULL
        #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED        
            ,
            (sizeof(asCLD_ScenesClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
            (tsZCL_CommandDefinition*)asCLD_ScenesClusterCommandDefinitions         
        #endif        
};
uint8 au8ScenesAttributeControlBits[(sizeof(asCLD_ScenesClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_ScenesCreateScenes
 **
 ** DESCRIPTION:
 ** Creates an identify cluster
 **
 ** PARAMETERS:                     Name                        Usage
 ** tsZCL_ClusterInstance           *psClusterInstance          Cluster structure
 ** bool_t                          bIsServer                   Server Client flag
 ** tsZCL_ClusterDefinition         *psClusterDefinition        Cluster Definition
 ** void                            *pvEndPointSharedStructPtr  EndPoint Shared Structure
 ** uint8                           *pu8AttributeControlBits    Attribute Control Bits
 ** tsCLD_ScenesCustomDataStructure *psCustomDataStructure      Custom Data Structure
 ** tsZCL_EndPointDefinition        *psEndPointDefinition       EndPoint Definition
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ScenesCreateScenes(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits,
                tsCLD_ScenesCustomDataStructure    *psCustomDataStructure,
                tsZCL_EndPointDefinition           *psEndPointDefinition)
{

    #if (defined SCENES_SERVER) && (defined CLD_ONOFF) &&(defined ONOFF_SERVER) && (defined CLD_ONOFF_ATTR_GLOBAL_SCENE_CONTROL) && (defined CLD_ONOFF_CMD_OFF_WITH_EFFECT)
        tsCLD_ScenesTableEntry *psTableEntry;
        teZCL_Status eStatus;
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
                                   eCLD_ScenesCommandHandler);    

    psCustomDataStructure->sCustomCallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_CUSTOM;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId = psClusterDefinition->u16ClusterEnum;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.pvCustomData = (void *)&psCustomDataStructure->sCallBackMessage;
    psCustomDataStructure->sCustomCallBackEvent.psClusterInstance = psClusterInstance; 
  
        if(pvEndPointSharedStructPtr != NULL)
        {
    #ifdef SCENES_SERVER
            /* Initialise attributes */

            eCLD_ScenesCountScenes(psEndPointDefinition, psClusterInstance, &((tsCLD_Scenes*)pvEndPointSharedStructPtr)->u8SceneCount);
            DBG_vPrintf(TRACE_SCENES, "\n eCLD_ScenesCreateScenes: eCLD_ScenesCountScenes() u8SceneCount = %d",((tsCLD_Scenes*)pvEndPointSharedStructPtr)->u8SceneCount);

            if(((tsCLD_Scenes*)pvEndPointSharedStructPtr)->u8SceneCount == 0)
            {
                ((tsCLD_Scenes*)pvEndPointSharedStructPtr)->u8CurrentScene = 0;
                ((tsCLD_Scenes*)pvEndPointSharedStructPtr)->u16CurrentGroup = 0;
                ((tsCLD_Scenes*)pvEndPointSharedStructPtr)->bSceneValid = FALSE;
                ((tsCLD_Scenes*)pvEndPointSharedStructPtr)->u8NameSupport = CLD_SCENES_NAME_SUPPORT;

                #ifdef CLD_SCENES_ATTR_LAST_CONFIGURED_BY
                    ((tsCLD_Scenes*)pvEndPointSharedStructPtr)->u64LastConfiguredBy = (uint64)0xffffffffffffffffLL;
                #endif

                /* initialise lists */
                vDLISTinitialise(&((tsCLD_ScenesCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr)->lScenesAllocList);
                vDLISTinitialise(&((tsCLD_ScenesCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr)->lScenesDeAllocList);
                int n;
                for(n=0; n < CLD_SCENES_MAX_NUMBER_OF_SCENES; n++)
                {
                    /* add all header slots to the to free list */
                    vDLISTaddToTail(&psCustomDataStructure->lScenesDeAllocList, (DNODE *)&psCustomDataStructure->asScenesTableEntry[n]);
                }

                #if (defined CLD_ONOFF) &&(defined ONOFF_SERVER) && (defined CLD_ONOFF_ATTR_GLOBAL_SCENE_CONTROL) && (defined CLD_ONOFF_CMD_OFF_WITH_EFFECT)
                    /* Try and get a table entry for the global scene */
                    eStatus = eCLD_ScenesStoreScene(psEndPointDefinition,
                                                psClusterInstance,
                                                0,
                                                0,
                                                &psTableEntry);
                                                
                    /*Error check based on eStatus before vSaveScenesNVM() */
                    if(eStatus == E_ZCL_SUCCESS)
                        vSaveScenesNVM();
                #endif
            }
        #endif    
            ((tsCLD_Scenes*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_SCENES_CLUSTER_REVISION;
        }

    return E_ZCL_SUCCESS;

}

#ifdef SCENES_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_ScenesUpdate
 **
 ** DESCRIPTION:
 ** Updates scenes
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          Source EP Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ScenesUpdate(uint8 u8SourceEndPointId)
{

    uint8 u8Status;
    tsCLD_ScenesCustomDataStructure *psCustomDataStructure;

    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_ScenesTableEntry *psTableEntry;

    /* Find pointers to cluster */
    u8Status = eZCL_FindCluster(GENERAL_CLUSTER_ID_SCENES, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(u8Status != E_ZCL_SUCCESS)
    {
        return u8Status;
    }

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    /* See if there are any active scenes */
    u8Status = eCLD_ScenesFindActiveScene(psEndPointDefinition,
                                         psClusterInstance,
                                         &psTableEntry);
    /* If an active scene was found */
    if(u8Status == E_ZCL_SUCCESS)
    {

        if((psTableEntry->bActive == TRUE) && (psTableEntry->bInTransit == TRUE))
        {
#ifdef DEBUG_CLD_SCENES
            {
                int x;
                DBG_vPrintf(TRACE_SCENES, "\nUpdating scene GID%04x SID%02x Time%d Len%d ", psTableEntry->u16GroupId, psTableEntry->u8SceneId, psTableEntry->u16TransitionTime, psTableEntry->u16SceneDataLength);
                for(x = 0; x < psTableEntry->u8SceneNameLength; x++)
                {
                    DBG_vPrintf(TRACE_SCENES, "%c", psTableEntry->au8SceneName[x]);
                }

                for(x = 0; x < psTableEntry->u16SceneDataLength; x++)
                {
                    DBG_vPrintf(TRACE_SCENES, " %02x", psTableEntry->au8SceneData[x]);
                }

            }
#endif
            /* Restore scene extension data to clusters */
            u8Status = eCLD_ScenesRestoreClusters(psEndPointDefinition,
                                                 psTableEntry->u16SceneDataLength,
                                                 psTableEntry->au8SceneData,
                                                 psTableEntry->u32TransitionTimer);

            /* Check if transition complete */
            if(psTableEntry->u32TransitionTimer > 0)
            {
                /* Decrement transition timer */
                psTableEntry->u32TransitionTimer--;
            }
            else
            {
                /* Transition complete */
                psTableEntry->bInTransit = FALSE;
            }
        }

    }

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return(E_ZCL_SUCCESS);
}

/****************************************************************************
 **
 ** NAME:       vCLD_ScenesGenerateIndividualAttributeCallback
 **
 ** DESCRIPTION:
 ** Generates an individual attribute write callback event
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition       End point definition
 ** tsZCL_ClusterInstance       *psClusterInstance          Cluster instance
 ** uint8                       u8AttributeIndex            Index to attribute deinition
 **
 ** RETURN:
 ** void
 **
 ****************************************************************************/
PUBLIC  void vCLD_ScenesGenerateIndividualAttributeCallback(
                        tsZCL_EndPointDefinition    *psEndPointDefinition,
                        tsZCL_ClusterInstance       *psClusterInstance,
                        uint16 u16AttributeId)
{

    tsZCL_CallBackEvent sZCL_CallBackEvent;
    tsZCL_AttributeDefinition   *psAttributeDefinition;
    uint16 u16attributeIndex;
    // check if attribute is present
    if(eZCL_SearchForAttributeEntry(psEndPointDefinition->u8EndPointNumber, u16AttributeId, FALSE, FALSE, psClusterInstance, &psAttributeDefinition, &u16attributeIndex) != E_ZCL_SUCCESS)
    {
        return;
    }
    // fill in non-attribute specific values in callback event structure
    sZCL_CallBackEvent.u8EndPoint = psEndPointDefinition->u8EndPointNumber;
    sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
    sZCL_CallBackEvent.pZPSevent = NULL;
    sZCL_CallBackEvent.eEventType = E_ZCL_CBET_WRITE_INDIVIDUAL_ATTRIBUTE;

    // fill in attribute specific values in callback event structure
    sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.u16AttributeEnum = u16AttributeId;
    sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType = psAttributeDefinition->eAttributeDataType;
    sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeStatus = E_ZCL_CMDS_SUCCESS;
    sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.pvAttributeData = pvZCL_GetAttributePointer(psAttributeDefinition,
                                                                                             psClusterInstance,u16AttributeId);

    // call user for every attribute updated
    psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
}


/****************************************************************************
 **
 ** NAME:       eCLD_ScenesAdd
 **
 ** DESCRIPTION:
 ** Can be used by other clusters or the application to store scenes
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          End point id
 ** uint16                      u16GroupId                  Group ID
 ** uint8                       u8SceneId                   Scene ID
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ScenesAdd(
                        uint8                       u8SourceEndPointId,
                        uint16                      u16GroupId,
                        uint8                       u8SceneId)
{
    return eCLD_ScenesStore(u8SourceEndPointId, u16GroupId, u8SceneId);
}


/****************************************************************************
 **
 ** NAME:       eCLD_ScenesStore
 **
 ** DESCRIPTION:
 ** Can be used by other clusters or the application to store scenes
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          End point id
 ** uint16                      u16GroupId                  Group ID
 ** uint8                       u8SceneId                   Scene ID
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ScenesStore(
                        uint8                       u8SourceEndPointId,
                        uint16                      u16GroupId,
                        uint8                       u8SceneId)
{

    teZCL_Status eStatus = E_ZCL_FAIL;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_ScenesCustomDataStructure *psCustomDataStructure;
    #ifdef SCENES_SERVER
        tsCLD_ScenesTableEntry *psTableEntry;
    #endif

    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_SCENES, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_SCENES, "\nScenesStore: Error: Can't find cluster()");
        return eStatus;
    }

    /* Try and get a table entry for the scene */
    eStatus = eCLD_ScenesStoreScene(psEndPointDefinition,
                                    psClusterInstance,
                                    u16GroupId,
                                    u8SceneId,
                                    &psTableEntry);

    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }


    /* Save all clusters on this end point */
    eStatus =  eCLD_ScenesSaveClusters(psEndPointDefinition,
                                      sizeof(psTableEntry->au8SceneData),
                                      &psTableEntry->u16SceneDataLength,
                                      psTableEntry->au8SceneData,
                                      FALSE);

    if(bFlag_SaveScenesNVM)
    {
        DBG_vPrintf(TRACE_SCENES, "\neCLD_ScenesStore: calling vSaveScenesNVM");
        vSaveScenesNVM();
    }
    return eStatus;
}

/****************************************************************************
 **
 ** NAME:       eCLD_ScenesRecall
 **
 ** DESCRIPTION:
 ** Can be used by other clusters or the application to recall scenes
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          End point definition
 ** uint16                      u16GroupId                  Group ID
 ** uint8                       u8SceneId                   Scene ID
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ScenesRecall(
                        uint8                       u8SourceEndPointId,
                        uint16                      u16GroupId,
                        uint8                       u8SceneId)
{

    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_ScenesCustomDataStructure *psCustomDataStructure;
    tsCLD_ScenesTableEntry *psTableEntry;
    tsCLD_ScenesTableEntry *psOldActiveScene;

    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_SCENES, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_SCENES, "\nScenesRecall: Error: Can't find cluster()");
        return eStatus;
    }

    /* See if the scene exists */
    eStatus = eCLD_ScenesFindScene(psEndPointDefinition,
                                   psClusterInstance,
                                   u16GroupId,
                                   u8SceneId,
                                   &psTableEntry);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_SCENES, "\neCLD_ScenesFindScene returned %d", eStatus);
        return eStatus;
    }

    /* See if there are any active scenes */
    eStatus = eCLD_ScenesFindActiveScene(psEndPointDefinition,
                                         psClusterInstance,
                                         &psOldActiveScene);
    /* If an active scene was found, make it inactive and set transition timer to 0 */
    if(eStatus == E_ZCL_SUCCESS)
    {
        psOldActiveScene->bActive = FALSE;
        psOldActiveScene->u32TransitionTimer = 0;
    }

    /* Make new scene active */
    psTableEntry->u32TransitionTimer = psTableEntry->u16TransitionTime * 10;
    psTableEntry->bActive = TRUE;
    psTableEntry->bInTransit = TRUE;

    /* For GlobalScene, immediate update for OnOff attribute */
    if((u16GroupId == 0) && (u8SceneId == 0))
    {
        eCLD_ScenesUpdate(u8SourceEndPointId);
    }

    return eStatus;

}
#endif /* SCENES_SERVER */
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

