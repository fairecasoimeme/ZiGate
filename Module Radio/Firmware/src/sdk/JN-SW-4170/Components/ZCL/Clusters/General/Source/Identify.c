/*****************************************************************************
 *
 * MODULE:             Identify Cluster
 *
 * COMPONENT:          Identify.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Identify cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/Identify.c $
 *
 * $Revision: 90669 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2017-10-17 18:21:47 +0200 (Tue, 17 Oct 2017) $
 *
 * $Id: Identify.c 90669 2017-10-17 16:21:47Z nxp29741 $
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
#include "Identify.h"
#include "Identify_internal.h"

#ifdef CLD_GROUPS
#include "Groups_internal.h"
#endif

#include "dbg.h"


#ifdef DEBUG_CLD_IDENTIFY
#define TRACE_IDENTIFY    TRUE
#else
#define TRACE_IDENTIFY    FALSE
#endif

#ifdef CLD_IDENTIFY

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
#ifdef IDENTIFY_SERVER
    PRIVATE void vCLD_IdentifyTimerClickCallback(tsZCL_CallBackEvent *psCallBackEvent);
    PRIVATE teZCL_Status eCLD_IdentifyUpdateTime(uint8 u8SourceEndPointId);
#endif
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
    const tsZCL_CommandDefinition asCLD_IdentifyClusterCommandDefinitions[] = {
        {E_CLD_IDENTIFY_CMD_IDENTIFY,                E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_IDENTIFY_CMD_IDENTIFY_QUERY,          E_ZCL_CF_RX},     /* Mandatory */
    #ifdef CLD_IDENTIFY_CMD_EZ_MODE_INVOKE    
        {E_CLD_IDENTIFY_CMD_EZ_MODE_INVOKE,          E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */ 
    #endif
    #ifdef CLD_IDENTIFY_ATTR_COMMISSION_STATE    
        {E_CLD_IDENTIFY_CMD_UPDATE_COMMISSION_STATE, E_ZCL_CF_RX},     /* Mandatory */
    #endif
    #ifdef  CLD_IDENTIFY_CMD_TRIGGER_EFFECT
        {E_CLD_IDENTIFY_CMD_TRIGGER_EFFECT,          E_ZCL_CF_RX}   
    #endif
    };
#endif

const tsZCL_AttributeDefinition asCLD_IdentifyClusterAttributeDefinitions[] = {
#ifdef IDENTIFY_SERVER
        {E_CLD_IDENTIFY_ATTR_ID_IDENTIFY_TIME,      (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT16,   (uint32)(&((tsCLD_Identify*)(0))->u16IdentifyTime),0},     /* Mandatory */

    #ifdef CLD_IDENTIFY_ATTR_COMMISSION_STATE
        {E_CLD_IDENTIFY_ATTR_ID_COMMISSION_STATE,    (E_ZCL_AF_RD),              E_ZCL_BMAP8,    (uint32)(&((tsCLD_Identify*)(0))->u8CommissionState),0},      /* Optional */
    #endif
#endif	
		{E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,  	 (E_ZCL_AF_RD|E_ZCL_AF_GA),  E_ZCL_UINT16,   (uint32)(&((tsCLD_Identify*)(0))->u16ClusterRevision),0},   /* Mandatory  */
};
tsZCL_ClusterDefinition sCLD_Identify = {
        GENERAL_CLUSTER_ID_IDENTIFY,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_IdentifyClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_IdentifyClusterAttributeDefinitions,
        NULL
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED        
        ,
        (sizeof(asCLD_IdentifyClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
        (tsZCL_CommandDefinition*)asCLD_IdentifyClusterCommandDefinitions          
#endif        
};
uint8 au8IdentifyAttributeControlBits[(sizeof(asCLD_IdentifyClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

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
 ** PARAMETERS:                         Name                        Usage
 ** tsZCL_ClusterInstance               *psClusterInstance          Cluster structure
 ** bool_t                               bIsServer                  Server Client flag
 ** tsZCL_ClusterDefinition             *psClusterDefinition        Cluster Definition
 ** void                                *pvEndPointSharedStructPtr  EndPoint Shared Structure
 ** uint8                               *pu8AttributeControlBits    Attribute Control Bits
 ** tsCLD_IdentifyCustomDataStructure   *psCustomDataStructure      Custom Data Structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_IdentifyCreateIdentify(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits,
                tsCLD_IdentifyCustomDataStructure  *psCustomDataStructure)
{

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
                                   eCLD_IdentifyCommandHandler);

    psCustomDataStructure->sCustomCallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_CUSTOM;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId = psClusterDefinition->u16ClusterEnum;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.pvCustomData = (void *)&psCustomDataStructure->sCallBackMessage;
    psCustomDataStructure->sCustomCallBackEvent.psClusterInstance = psClusterInstance; 

    if(pvEndPointSharedStructPtr != NULL)
    {
#ifdef IDENTIFY_SERVER        
        /* Set attribute defaults */
        ((tsCLD_Identify*)pvEndPointSharedStructPtr)->u16IdentifyTime = 0;
#endif        
        ((tsCLD_Identify*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_IDENTIFY_CLUSTER_REVISION ;
    }

#ifdef IDENTIFY_SERVER   
    /* Register time server only if cluster instance is server */
    if(bIsServer)
        eCLD_IdentifyRegisterTimeServer();
#endif
    //  register timer
    return E_ZCL_SUCCESS;

}
#ifdef IDENTIFY_SERVER  
/****************************************************************************
 **
 ** NAME:       eCLD_IdentifyRegisterTimeServer
 **
 ** DESCRIPTION:
 ** Registers Identify Time Server with ZCL
 **
 ** PARAMETERS:                         Name                          Usage
 ** none
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
#ifdef IDENTIFY_PC_BUILD
bool_t bTimerRegistered = FALSE;
#endif

PUBLIC teZCL_Status eCLD_IdentifyRegisterTimeServer(void)
{
#ifndef IDENTIFY_PC_BUILD
    static bool_t bTimerRegistered = FALSE;
#endif
    if(!bTimerRegistered)
    {
        // add timer click function to ZCL
        if(eZCL_TimerRegister(E_ZCL_TIMER_CLICK, 0, vCLD_IdentifyTimerClickCallback) != E_ZCL_SUCCESS)
            return(E_ZCL_FAIL);

        bTimerRegistered = TRUE;
    }

    return E_ZCL_SUCCESS;
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
/****************************************************************************
 **
 ** NAME:       vCLD_IdentifyTimerClickCallback
 **
 ** DESCRIPTION:
 ** Timer Callback registered with the ZCL
 **
 ** PARAMETERS:                 Name               Usage
 ** tsZCL_CallBackEvent        *psCallBackEvent    Timer Server Callback
 **
 ** RETURN:
 ** nothing
 **
 ****************************************************************************/
PRIVATE void vCLD_IdentifyTimerClickCallback(tsZCL_CallBackEvent *psCallBackEvent)
{
    int i;
    uint8 u8NumberOfendpoints;

    u8NumberOfendpoints = u8ZCL_GetNumberOfEndpointsRegistered();

    // find identify clusters on each EP - if any
    for(i = 0; i < u8NumberOfendpoints; i++)
    {
        // deliver time to any EP-server/client
        eCLD_IdentifyUpdateTime(u8ZCL_GetEPIdFromIndex(i));
    }

}

/****************************************************************************
 **
 ** NAME:       eCLD_IdentifyUpdateTime
 **
 ** DESCRIPTION:
 ** Updates the identify time in identify clusters
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          Source EP Id
 **
 ** RETURN:
 ** teCLD_Status
 **
 ****************************************************************************/
PRIVATE teZCL_Status eCLD_IdentifyUpdateTime(uint8 u8SourceEndPointId)
{

    teZCL_Status eStatus;
    tsCLD_IdentifyCustomDataStructure *psCustomDataStructure;

    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsZCL_CallBackEvent sZCL_CallBackEvent;
    tsCLD_Identify *psSharedStruct;

    /* Find pointers to cluster */
    eStatus = eZCL_FindCluster(GENERAL_CLUSTER_ID_IDENTIFY, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCustomDataStructure);
    if(eStatus != E_ZCL_SUCCESS)
    {
        return eStatus;
    }

    /* Get pointer to identify cluster shared struct */
    psSharedStruct = (tsCLD_Identify*)psClusterInstance->pvEndPointSharedStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    /* Decrement time */
    if(psSharedStruct->u16IdentifyTime > 0)
    {
        psSharedStruct->u16IdentifyTime--;
        DBG_vPrintf(TRACE_IDENTIFY, "\nIdentifyTime=%d", psSharedStruct->u16IdentifyTime);

        /* Generate a callback to let the user know that an update event occurred */
        sZCL_CallBackEvent.u8EndPoint = psEndPointDefinition->u8EndPointNumber;
        sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
        sZCL_CallBackEvent.pZPSevent = NULL;
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_UPDATE;
        psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
    }

#ifdef CLD_GROUPS
    if(psSharedStruct->u16IdentifyTime == 0)
    {
        eCLD_GroupsSetIdentifying(psEndPointDefinition->u8EndPointNumber, FALSE);
    }
#endif

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return(E_ZCL_SUCCESS);
}
#endif

#ifdef CLD_IDENTIFY_CMD_EZ_MODE_INVOKE
/****************************************************************************
 **
 ** NAME:       eCLD_IdentifyEZModeInvokeCommandSend
 **
 ** DESCRIPTION:
 ** Builds and sends an identify cluster command
 **
 ** PARAMETERS:                         Name                           Usage
 ** uint8                              u8SourceEndPointId              Source EP Id
 ** uint8                              u8DestinationEndPointId         Destination EP Id
 ** tsZCL_Address                      *psDestinationAddress           Destination Address
 ** uint8                              *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsCLD_Identify_EZModeInvokePayload *psPayload           Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_IdentifyEZModeInvokeCommandSend(
                                        uint8                               u8SourceEndPointId,
                                        uint8                               u8DestinationEndPointId,
                                        tsZCL_Address                       *psDestinationAddress,
                                        uint8                               *pu8TransactionSequenceNumber,
                                        bool                                bDirection,
                                        tsCLD_Identify_EZModeInvokePayload  *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1,                         E_ZCL_BMAP8,   &psPayload->u8Action},
                                              };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_IDENTIFY,
                                  bDirection,
                                  E_CLD_IDENTIFY_CMD_EZ_MODE_INVOKE,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}

/****************************************************************************
 **
 ** NAME:       eCLD_IdentifyEZModeInvokeCommandReceive
 **
 ** DESCRIPTION:
 ** Receives an Identify EZ Mode Invoke Command
 **
 ** PARAMETERS:                         Name                           Usage
 ** uint8                              u8SourceEndPointId              Source EP Id
 ** uint8                              u8DestinationEndPointId         Destination EP Id
 ** tsZCL_Address                      *psDestinationAddress           Destination Address
 ** uint8                              *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsCLD_Identify_EZModeInvokePayload *psPayload           Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_IdentifyEZModeInvokeCommandReceive(
                                        ZPS_tsAfEvent                               *pZPSevent,
                                        uint8                                       *pu8TransactionSequenceNumber,
                                        tsCLD_Identify_EZModeInvokePayload          *psPayload)
{

    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
    {1, &u16ActualQuantity, E_ZCL_BMAP8,   &psPayload->u8Action},
                                                };

    return eZCL_CustomCommandReceive(pZPSevent,
                                    pu8TransactionSequenceNumber,
                                    asPayloadDefinition,
                                    sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                    E_ZCL_ACCEPT_EXACT);

}
#endif

#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

