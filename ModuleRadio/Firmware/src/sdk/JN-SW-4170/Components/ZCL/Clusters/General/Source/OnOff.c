/*****************************************************************************
 *
 * MODULE:             On/Off Cluster
 *
 * COMPONENT:          OnOff.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        On/Off cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/OnOff.c $
 *
 * $Revision: 93644 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2018-05-16 12:15:44 +0100 (Wed, 16 May 2018) $
 *
 * $Id: OnOff.c 93644 2018-05-16 11:15:44Z nxp29741 $
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
#include "zcl_options.h"
#include "zcl_customcommand.h"
#include "OnOff.h"
#include "string.h"
#include "OnOff_internal.h"


#include "dbg.h"
#ifdef DEBUG_CLD_ONOFF
#define TRACE_ONOFF TRUE
#else
#define TRACE_ONOFF FALSE
#endif
#ifdef CLD_SCENES
#include "Scenes.h"
#endif
#ifdef CLD_ONOFF

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
#ifdef ONOFF_SERVER
PRIVATE teZCL_Status eCLD_OnOffSceneEventHandler(
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
#ifdef ONOFF_SERVER
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
    const tsZCL_CommandDefinition asCLD_OnOffClusterCommandDefinitions[] = {
        {E_CLD_ONOFF_CMD_OFF,                E_ZCL_CF_RX},     /* Mandatory */
        {E_CLD_ONOFF_CMD_ON,                 E_ZCL_CF_RX},     /* Mandatory */
        {E_CLD_ONOFF_CMD_TOGGLE,             E_ZCL_CF_RX}     /* Mandatory */    
        
    };
#endif

const tsZCL_AttributeDefinition asCLD_OnOffClusterAttributeDefinitions[] = {
    {E_CLD_ONOFF_ATTR_ID_ONOFF,                 (E_ZCL_AF_RD|E_ZCL_AF_SE|E_ZCL_AF_RP),  E_ZCL_BOOL,     (uint32)(&((tsCLD_OnOff*)(0))->bOnOff),0},     /* Mandatory */
    
#ifdef CLD_ONOFF_ATTR_GLOBAL_SCENE_CONTROL
    {E_CLD_ONOFF_ATTR_ID_GLOBAL_SCENE_CONTROL,  (E_ZCL_AF_RD),                          E_ZCL_BOOL,     (uint32)(&((tsCLD_OnOff*)(0))->bGlobalSceneControl),0},     /* Optional */
#endif
#ifdef CLD_ONOFF_ATTR_ON_TIME
    {E_CLD_ONOFF_ATTR_ID_ON_TIME,               (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT16,   (uint32)(&((tsCLD_OnOff*)(0))->u16OnTime),0},     /* Optinal */
#endif
#ifdef CLD_ONOFF_ATTR_OFF_WAIT_TIME
    {E_CLD_ONOFF_ATTR_ID_OFF_WAIT_TIME,         (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT16,   (uint32)(&((tsCLD_OnOff*)(0))->u16OffWaitTime),0},     /* Optinal */
#endif

#ifdef CLD_ONOFF_ATTR_STARTUP_ONOFF
    /* ZLO extension for OnOff Cluster    */             
    {E_CLD_ONOFF_ATTR_ID_STARTUP_ONOFF,         (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_ENUM8,     (uint32)(&((tsCLD_OnOff*)(0))->eStartUpOnOff),0},     /* Optinal */
#endif

    {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,     (E_ZCL_AF_RD|E_ZCL_AF_GA),               E_ZCL_UINT16,   (uint32)(&((tsCLD_OnOff*)(0))->u16ClusterRevision),0},   /* Mandatory  */
    
#if (defined ONOFF_SERVER) && (defined CLD_ONOFF_ATTR_ATTRIBUTE_REPORTING_STATUS)
    {E_CLD_GLOBAL_ATTR_ID_ATTRIBUTE_REPORTING_STATUS,(E_ZCL_AF_RD|E_ZCL_AF_GA),          E_ZCL_ENUM8,    (uint32)(&((tsCLD_OnOff*)(0))->u8AttributeReportingStatus),0},  /* Optional */
#endif
};

    /* List of attributes in the scene extension table */
    tsZCL_SceneExtensionTable sCLD_OnOffSceneExtensionTable =
    {
            eCLD_OnOffSceneEventHandler,
            1,
            {E_CLD_ONOFF_ATTR_ID_ONOFF}
    };

    tsZCL_ClusterDefinition sCLD_OnOff = {
            GENERAL_CLUSTER_ID_ONOFF,
            FALSE,
            E_ZCL_SECURITY_NETWORK,
            (sizeof(asCLD_OnOffClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
            (tsZCL_AttributeDefinition*)asCLD_OnOffClusterAttributeDefinitions,
            &sCLD_OnOffSceneExtensionTable
    #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED        
            ,
            (sizeof(asCLD_OnOffClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
            (tsZCL_CommandDefinition*)asCLD_OnOffClusterCommandDefinitions        
    #endif        
    };
    uint8 au8OnOffAttributeControlBits[(sizeof(asCLD_OnOffClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
#endif

#ifdef ONOFF_CLIENT

const tsZCL_AttributeDefinition asCLD_OnOffClientClusterAttributeDefinitions[] = {
    {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,     (E_ZCL_AF_RD|E_ZCL_AF_GA),               E_ZCL_UINT16,   (uint32)(&((tsCLD_OnOffClient*)(0))->u16ClusterRevision),0},   /* Mandatory  */
};
    tsZCL_ClusterDefinition sCLD_OnOffClient = {
            GENERAL_CLUSTER_ID_ONOFF,
            FALSE,
            E_ZCL_SECURITY_NETWORK,
            (sizeof(asCLD_OnOffClientClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
            (tsZCL_AttributeDefinition*)asCLD_OnOffClientClusterAttributeDefinitions,
            NULL
    #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
            ,
            0,
            NULL
    #endif
    };
    uint8 au8OnOffClientAttributeControlBits[(sizeof(asCLD_OnOffClientClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
#endif


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_OnOffCreateOnOff
 **
 ** DESCRIPTION:
 ** Creates an on/off cluster
 **
 ** PARAMETERS:                     Name                        Usage
 ** tsZCL_ClusterInstance           *psClusterInstance          Cluster structure
 ** bool_t                          bIsServer                   Server Client flag
 ** tsZCL_ClusterDefinition         *psClusterDefinition        Cluster Definition
 ** void                            *pvEndPointSharedStructPtr  Endpoint shared structure
 ** uint8                           *pu8AttributeControlBits    Attribute control bits
 ** tsCLD_OnOffCustomDataStructure  *psCustomDataStructure      Custom data Structure
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_OnOffCreateOnOff(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits,
                tsCLD_OnOffCustomDataStructure     *psCustomDataStructure)
{

    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if(psClusterInstance==NULL)
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
           eCLD_OnOffCommandHandler);    
    
    if(psClusterInstance->pvEndPointSharedStructPtr != NULL)
    {
        if(bIsServer)
        {     
        #ifdef ONOFF_SERVER
            // set default state
            #ifdef CLD_ONOFF_ATTR_STARTUP_ONOFF
                switch(((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->eStartUpOnOff)
                {
                    case E_CLD_ONOFF_STARTUPONOFF_OFF:
                    case E_CLD_ONOFF_STARTUPONOFF_ON:
                        ((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->bOnOff = ((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->eStartUpOnOff;
                    break;
                
                    case E_CLD_ONOFF_STARTUPONOFF_TOGGLE:
                        ((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->bOnOff ^= 0x01; 
                    break;
                
                    case E_CLD_ONOFF_STARTUPONOFF_PREVIOUS_VALUE:
                        /* No action as it should reload the same OnOff value */
                    break;
                    
                    default:
                    break;
                }
            #else
                ((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->bOnOff = FALSE;
            #endif
            
            #ifdef CLD_ONOFF_ATTR_GLOBAL_SCENE_CONTROL
                ((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->bGlobalSceneControl = TRUE;
            #endif

            #ifdef CLD_ONOFF_ATTR_ON_TIME
                ((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->u16OnTime = 0;
            #endif

            #ifdef CLD_ONOFF_ATTR_OFF_WAIT_TIME
                ((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->u16OffWaitTime = 0;
            #endif
            
            ((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->u16ClusterRevision =  CLD_ONOFF_CLUSTER_REVISION;
        #endif
        }
        else
        {
        #ifdef ONOFF_CLIENT
            ((tsCLD_OnOffClient *)(psClusterInstance->pvEndPointSharedStructPtr))->u16ClusterRevision = CLD_ONOFF_CLUSTER_REVISION;
        #endif
        }
    }

    #ifdef ONOFF_SERVER
        if(bIsServer)
        {    
            /* As this cluster has reportable attributes enable default reporting */
            vZCL_SetDefaultReporting(psClusterInstance);
        }
    #endif
    return E_ZCL_SUCCESS;

}

#ifdef ONOFF_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_OnOffSetState
 **
 ** DESCRIPTION:
 ** Can be used by other clusters to set the state of the on/off attribute
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          EndPoint Id
 ** bool                        bOn                         On or Off
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_OnOffSetState(uint8 u8SourceEndPointId, bool bOn)
{

    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    void *psCustomDataStructure;
    tsZCL_CallBackEvent sZCL_CallBackEvent;
    tsCLD_OnOff *psSharedStruct;

    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_ONOFF, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }

    DBG_vPrintf(TRACE_ONOFF, "\neCLD_OnOffSetState(%d,%d)", u8SourceEndPointId, bOn);

    /* Point to shared struct */
    psSharedStruct = (tsCLD_OnOff *)psClusterInstance->pvEndPointSharedStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    /* Set attribute state */
    if(bOn == TRUE)
    {
        psSharedStruct->bOnOff = 1;

#if (defined CLD_ONOFF_ATTR_ON_TIME) && (defined CLD_ONOFF_ATTR_OFF_WAIT_TIME)
        /* See ZCL spec, 3.8.2.1.1 */
        if(psSharedStruct->u16OnTime == 0)
        {
            psSharedStruct->u16OffWaitTime = 0;
    }
#endif

    }
    else
    {
        psSharedStruct->bOnOff = 0;

#ifdef CLD_ONOFF_ATTR_ON_TIME
        /* See ZCL spec, 3.8.2.1.1 */
        psSharedStruct->u16OnTime = 0;
#endif

    }

    /* Generate a callback to let the user know that an update event occurred */
    sZCL_CallBackEvent.u8EndPoint           = psEndPointDefinition->u8EndPointNumber;
    sZCL_CallBackEvent.psClusterInstance    = psClusterInstance;
    sZCL_CallBackEvent.pZPSevent            = NULL;
    sZCL_CallBackEvent.eEventType           = E_ZCL_CBET_CLUSTER_UPDATE;
    psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

#if (defined CLD_SCENES) && (defined SCENES_SERVER)
    vCLD_ScenesUpdateSceneValid( psEndPointDefinition);
#endif

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return E_ZCL_SUCCESS;

}


/****************************************************************************
 **
 ** NAME:       eCLD_OnOffGetState
 **
 ** DESCRIPTION:
 ** Can be used by other clusters to get the state of the on/off attribute
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          EndPoint Id
 ** bool                        *pbOn                       On or Off
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_OnOffGetState(uint8 u8SourceEndPointId, bool* pbOn)
{

    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    void *psCustomDataStructure;

    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_ONOFF, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }

    /* Get attribute state */
    if(((tsCLD_OnOff *)(psClusterInstance->pvEndPointSharedStructPtr))->bOnOff == 1)
    {
        *pbOn = TRUE;
    }
    else
    {
        *pbOn = FALSE;
    }

    return E_ZCL_SUCCESS;

}

#ifdef CLD_ONOFF_CMD_ON_WITH_TIMED_OFF
/****************************************************************************
 **
 ** NAME:       eCLD_OnOffUpdate
 **
 ** DESCRIPTION:
 ** Updates the the state of an On/Off cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          Source EP Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_OnOffUpdate(uint8 u8SourceEndPointId)
{

    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsCLD_OnOffCustomDataStructure *psCustomDataStructure;
    tsZCL_ClusterInstance *psClusterInstance;

    tsZCL_CallBackEvent sZCL_CallBackEvent;
    tsCLD_OnOff *psSharedStruct;
    
    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_ONOFF, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }

    psSharedStruct = (tsCLD_OnOff*)psClusterInstance->pvEndPointSharedStructPtr;
    
    /* get EP mutex */
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif

    /*
     * If the values of the OnTime and OffWaitTime attributes are both less than 0xffff, the device shall then
     * update the device every 1/10th second until both the OnTime and OffWaitTime attributes are equal to
     * 0x0000, as follows:
     *
     * If the value of the OnOff attribute is equal to 0x01 (on) and the value of the OnTime attribute
     * is greater than zero, the device shall decrement the value of the OnTime attribute. If the value
     * of the OnTime attribute reaches 0x0000, the device shall set the OffWaitTime and OnOff
     * attributes to 0x0000 and 0x00, respectively.
     *
     * If the value of the OnOff attribute is equal to 0x00 (off) and the value of the OffWaitTime
     * attribute is greater than zero, the device shall decrement the value of the OffWaitTime
     * attribute. If the value of the OffWaitTime attribute reaches 0x0000, the device shall terminate
     * the update.
     */
    if((psSharedStruct->u16OnTime < 0xffff) && (psSharedStruct->u16OffWaitTime < 0xffff) &&
       ((psSharedStruct->u16OnTime != 0) || (psSharedStruct->u16OffWaitTime != 0)))
    {

        DBG_vPrintf(TRACE_ONOFF, "\neCLD_OnOffUpdate: ");

        if((psSharedStruct->bOnOff == 0x01) && (psSharedStruct->u16OnTime > 0))
        {
            psSharedStruct->u16OnTime--;
            if(psSharedStruct->u16OnTime == 0)
            {
                psSharedStruct->u16OffWaitTime = 0x0000;
                psSharedStruct->bOnOff = 0x00;
            }
        }
        else if((psSharedStruct->bOnOff == 0x00) && (psSharedStruct->u16OffWaitTime > 0))
        {
            psSharedStruct->u16OffWaitTime--;
        }

        DBG_vPrintf(TRACE_ONOFF, "OnTime=%d OffWaitTime=%d On=%d", psSharedStruct->u16OnTime, psSharedStruct->u16OffWaitTime, psSharedStruct->bOnOff);

        /* Generate a callback to let the user know that an update event occurred */
        sZCL_CallBackEvent.u8EndPoint           = psEndPointDefinition->u8EndPointNumber;
        sZCL_CallBackEvent.psClusterInstance    = psClusterInstance;
        sZCL_CallBackEvent.pZPSevent            = NULL;
        sZCL_CallBackEvent.eEventType           = E_ZCL_CBET_CLUSTER_UPDATE;
        psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

#if (defined CLD_SCENES) && (defined SCENES_SERVER)
    vCLD_ScenesUpdateSceneValid( psEndPointDefinition);
#endif

    }

    /* release EP mutex */
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return(E_ZCL_SUCCESS);
}
#endif

#ifdef CLD_ONOFF_ATTR_GLOBAL_SCENE_CONTROL
/****************************************************************************
 **
 ** NAME:       eCLD_OnOffSetGlobalSceneControl
 **
 ** DESCRIPTION:
 ** Can be used by other clusters to set the global scene control attribute
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          Source EP Id
 ** bool                        bGlobalSceneControl         Global Scene Control
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_OnOffSetGlobalSceneControl(uint8 u8SourceEndPointId, bool bGlobalSceneControl)
{

    teZCL_Status eStatus;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsCLD_OnOffCustomDataStructure *psCustomDataStructure;
    tsZCL_ClusterInstance *psClusterInstance;

    tsCLD_OnOff *psSharedStruct;

    DBG_vPrintf(TRACE_ONOFF, "\nONOFF: SetGlobalSceneControl %d", bGlobalSceneControl);

    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_ONOFF, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_ONOFF, "Err No Cluster");
        return eStatus;
    }

    psSharedStruct = (tsCLD_OnOff*)psClusterInstance->pvEndPointSharedStructPtr;

    /* get EP mutex */
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    if(bGlobalSceneControl == TRUE)
    {
        psSharedStruct->bGlobalSceneControl = 0x01;
    }
    else
    {
        psSharedStruct->bGlobalSceneControl = 0x00;
    }

    /* release EP mutex */
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    DBG_vPrintf(TRACE_ONOFF, "OK");

    return(E_ZCL_SUCCESS);
}

#endif

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_OnOffSceneEventHandler
 **
 ** DESCRIPTION:
 ** Handles events generated by a scenes cluster (if present)
 **
 ** PARAMETERS:                 Name                        Usage
 ** teZCL_SceneEvent            eEvent                      Scene Event
 ** tsZCL_EndPointDefinition    *psEndPointDefinition       End Point Definition
 ** tsZCL_ClusterInstance       *psClusterInstance          Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PRIVATE  teZCL_Status eCLD_OnOffSceneEventHandler(
                        teZCL_SceneEvent            eEvent,
                        tsZCL_EndPointDefinition   *psEndPointDefinition,
                        tsZCL_ClusterInstance      *psClusterInstance)
{

    tsZCL_CallBackEvent sZCL_CallBackEvent;
#ifdef CLD_ONOFF_ATTR_GLOBAL_SCENE_CONTROL
    tsCLD_OnOff *psSharedStruct = (tsCLD_OnOff *)psClusterInstance->pvEndPointSharedStructPtr;
#endif

    switch(eEvent)
    {

    case E_ZCL_SCENE_EVENT_SAVE:
        DBG_vPrintf(TRACE_ONOFF, "\nONOFF: Scene Event: Save");
        break;

    case E_ZCL_SCENE_EVENT_RECALL:
        DBG_vPrintf(TRACE_ONOFF, "\nONOFF: Scene Event: Recall");

        /* See ZCL specification 3.8.2.2.2 */
#ifdef CLD_ONOFF_ATTR_GLOBAL_SCENE_CONTROL
        psSharedStruct->bGlobalSceneControl = 1;
#endif

        /* Inform the application that the cluster has just been updated */
        sZCL_CallBackEvent.u8EndPoint = psEndPointDefinition->u8EndPointNumber;
        sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
        sZCL_CallBackEvent.pZPSevent = NULL;
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_UPDATE;

        // call user
        psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

#if (defined CLD_SCENES) && (defined SCENES_SERVER)
    vCLD_ScenesUpdateSceneValid( psEndPointDefinition);
#endif

        break;

    }

    return E_ZCL_SUCCESS;
}
#endif /* ONOFF_SERVER */
#endif /* CLD_ONOFF */
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

