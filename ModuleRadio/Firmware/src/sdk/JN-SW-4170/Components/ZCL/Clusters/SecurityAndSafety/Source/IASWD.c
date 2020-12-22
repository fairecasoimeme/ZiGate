/*****************************************************************************
 *
 * MODULE:             IAS WD Cluster
 *
 * COMPONENT:          IASWD.c
 *
 * AUTHOR:             
 *
 * DESCRIPTION:        IAS WD cluster definition
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy:  $
 *
 * $LastChangedDate:  $
 *
 * $Id: $
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
#include "dbg.h"
#include "IASWD.h"
#include "IASWD_internal.h"

#ifdef DEBUG_CLD_IASWD
#define TRACE_IASWD    TRUE
#else
#define TRACE_IASWD    FALSE
#endif

#ifdef CLD_IASWD

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#if !defined(IASWD_SERVER) && !defined(IASWD_CLIENT)
#error You Must Have either IASWD_SERVER and/or IASWD_CLIENT defined in zcl_options.h
#endif

#ifndef CLD_IASWD_ATTR_ID_MAX_DURATION
#define CLD_IASWD_ATTR_ID_MAX_DURATION 240
#endif

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
    const tsZCL_CommandDefinition asCLD_IASWDClusterCommandDefinitions[] = {

        {E_CLD_IASWD_CMD_START_WARNING,                   E_ZCL_CF_RX},/* Mandatory */
        {E_CLD_IASWD_CMD_SQUAWK,                          E_ZCL_CF_RX} /* Mandatory */

    };
#endif

const tsZCL_AttributeDefinition asCLD_IASWDClusterAttributeDefinitions[] = {
#ifdef IASWD_SERVER    
        {E_CLD_IASWD_ATTR_ID_MAX_DURATION,     (E_ZCL_AF_RD|E_ZCL_AF_WR), E_ZCL_UINT16,    (uint32)(&((tsCLD_IASWD*)(0))->u16MaxDuration),0},       /* Mandatory */
#endif        
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,(E_ZCL_AF_RD|E_ZCL_AF_GA), E_ZCL_UINT16,    (uint32)(&((tsCLD_IASWD*)(0))->u16ClusterRevision),0},   /* Mandatory  */
    };

tsZCL_ClusterDefinition sCLD_IASWD = {
        SECURITY_AND_SAFETY_CLUSTER_ID_IASWD,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_IASWDClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_IASWDClusterAttributeDefinitions,
        NULL
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED        
        ,
        (sizeof(asCLD_IASWDClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
        (tsZCL_CommandDefinition*)asCLD_IASWDClusterCommandDefinitions 
#endif        
};
uint8 au8IASWDAttributeControlBits[(sizeof(asCLD_IASWDClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_IASWDCreateIASWD
 **
 ** DESCRIPTION:
 ** Creates a IAS Warning Device Cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_IASWDCreateIASWD(
        tsZCL_ClusterInstance                   *psClusterInstance,
        bool_t                                  bIsServer,
        tsZCL_ClusterDefinition                 *psClusterDefinition,
        void                                    *pvEndPointSharedStructPtr,
        uint8                                   *pu8AttributeControlBits,
        tsCLD_IASWD_CustomDataStructure         *psCustomDataStructure)
{

    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) || (psCustomDataStructure==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif
    
    /* Zero everything */
    memset(pvEndPointSharedStructPtr, 0, sizeof(tsCLD_IASWD));
    memset(psCustomDataStructure, 0, sizeof(tsCLD_IASWD_CustomDataStructure));

    // cluster data
    vZCL_InitializeClusterInstance(
                                   psClusterInstance, 
                                   bIsServer,
                                   psClusterDefinition,
                                   pvEndPointSharedStructPtr,
                                   pu8AttributeControlBits,
                                   psCustomDataStructure,
                                   eCLD_IASWDCommandHandler);   
                                   
    psCustomDataStructure->sCustomCallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_CUSTOM;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId = psClusterDefinition->u16ClusterEnum;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.pvCustomData = (void *)&psCustomDataStructure->sCallBackMessage;
    psCustomDataStructure->sCustomCallBackEvent.psClusterInstance = psClusterInstance; 
    if(pvEndPointSharedStructPtr != NULL)
    {
        #ifdef IASWD_SERVER
            /* Set Default Values */
            ((tsCLD_IASWD*)pvEndPointSharedStructPtr)->u16MaxDuration=CLD_IASWD_ATTR_ID_MAX_DURATION;
        #endif
            ((tsCLD_IASWD*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_IASWD_CLUSTER_REVISION;
    }
    return E_ZCL_SUCCESS;
}

#ifdef IASWD_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_IASWDUpdate
 **
 ** DESCRIPTION:
 ** Update function to be called at 100msec
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8               u8EndPointId             EndPoint Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_IASWDUpdate(uint8 u8SourceEndPointId)
{
    teZCL_Status eStatus = E_ZCL_SUCCESS;

    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_IASWD_CustomDataStructure *pCustomDataStructure;
    tsZCL_CallBackEvent sZCL_CallBackEvent;

    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(SECURITY_AND_SAFETY_CLUSTER_ID_IASWD, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&pCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }
    
    if( NULL == pCustomDataStructure)
    {
        return E_ZCL_ERR_CUSTOM_DATA_NULL;
    }
    
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif

    
    /*Subtract the time Loaded for Warning or Stobe at 50msec */
    uint8 u8WarningMode         =  pCustomDataStructure->sWarning.u8WarningModeStrobeAndSirenLevel >> 4;
    uint8 u8StrobeWithWarning   =  (pCustomDataStructure->sWarning.u8WarningModeStrobeAndSirenLevel & 0x0F) >> 2;
    uint8 u8SirenLevel          =  pCustomDataStructure->sWarning.u8WarningModeStrobeAndSirenLevel & 0x03;
    uint8 u8DutyCycle           =  pCustomDataStructure->sWarning.u8StrobeDutyCycle/10;

    
    /* Warning Mode is Set*/
    if(  u8WarningMode )
    {
        /*Warning is still on */
        if(pCustomDataStructure->u32WarningDurationRemainingIn100MS > 0)
        {
            tsCLD_IASWD_WarningUpdate sWarningUpdate;
            
            pCustomDataStructure->u32WarningDurationRemainingIn100MS -= 1;
            
            sWarningUpdate.u8WarningMode= u8WarningMode;
            sWarningUpdate.u8SirenLevel = u8SirenLevel;
            sWarningUpdate.u16WarningDurationRemaining = pCustomDataStructure->u32WarningDurationRemainingIn100MS/10;
            
            sWarningUpdate.u8StrobeWithWarning = u8StrobeWithWarning;
            
            if(u8StrobeWithWarning)
            {
                sWarningUpdate.eStrobeLevel =pCustomDataStructure->sWarning.eStrobeLevel;
                
                uint32 u32CurrentCycleRemainingTime = pCustomDataStructure->u32WarningDurationRemainingIn100MS - ((uint32)sWarningUpdate.u16WarningDurationRemaining*10) ;
                /*Reverse Logic*/
                if(u32CurrentCycleRemainingTime >= (10-u8DutyCycle))
                {
                    sWarningUpdate.bStrobe=TRUE;
                }
                else
                {
                    sWarningUpdate.bStrobe=FALSE;
                }
            }

            pCustomDataStructure->sCallBackMessage.uMessage.psWarningUpdate=&sWarningUpdate; 

            /* Generate a callback to let the user know that an update event occurred */        
    
            sZCL_CallBackEvent.u8EndPoint           = psEndPointDefinition->u8EndPointNumber;
            sZCL_CallBackEvent.psClusterInstance    = psClusterInstance;
            sZCL_CallBackEvent.pZPSevent            = NULL;
            sZCL_CallBackEvent.eEventType           = E_ZCL_CBET_CLUSTER_UPDATE;
            psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
 
        }
        
    }

    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif
 
    return eStatus;
}
/****************************************************************************
 **
 ** NAME:       eCLD_IASWDUpdateMaxDuration
 **
 ** DESCRIPTION:
 ** Update the Max Duration attribute
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8               u8EndPointId             EndPoint Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_IASWDUpdateMaxDuration (uint8 u8SourceEndPointId, uint16 u16MaxDuration)
{
    teZCL_Status eStatus;
    
               
    eStatus = eZCL_WriteLocalAttributeValue(
                     u8SourceEndPointId,                  //uint8                      u8SrcEndpoint,
                     SECURITY_AND_SAFETY_CLUSTER_ID_IASWD, //uint16                     u16ClusterId,
                     TRUE,                                //bool                       bIsServerClusterInstance,
                     FALSE,                               //bool                       bManufacturerSpecific,
                     FALSE,                               //bool_t                     bIsClientAttribute,
                     E_CLD_IASWD_ATTR_ID_MAX_DURATION,    //uint16                     u16AttributeId,
                     &u16MaxDuration                      //void                      *pvAttributeValue
                     );

    return eStatus;
}
#endif
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#endif          // ifdef CLD_IASWD

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

