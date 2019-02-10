/*****************************************************************************
 *
 * MODULE:             Zigbee Demand Response And Load Control Cluster
 *
 * COMPONENT:          DRLC.c
 *
 * AUTHOR:             Wayne Ellis
 *
 * DESCRIPTION:        Zigbee Demand Response And Load Control Cluster Definition
 *
 * $HeadURL: $
 *
 * $Revision: $
 *
 * $LastChangedBy: $
 *
 * $LastChangedDate: $
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
#include <string.h>
#include "dlist.h"
#include "zcl.h"
#include "DRLC.h"
#include "DRLC_internal.h"


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

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/* Define the attributes in the DRLC cluster */
const tsZCL_AttributeDefinition asCLD_DRLCClusterAttributeDefinitions[] = {
    {E_CLD_DRLC_UTILITY_ENROLMENT_GROUP,   (E_ZCL_AF_CA|E_ZCL_AF_WR|E_ZCL_AF_RD),   E_ZCL_UINT8,    (uint32)(&((tsCLD_DRLC*)(0))->u8UtilityEnrolmentGroup), 0},
    {E_CLD_DRLC_START_RANDOMIZE_MINUTES,   (E_ZCL_AF_CA|E_ZCL_AF_WR|E_ZCL_AF_RD),   E_ZCL_UINT8,    (uint32)(&((tsCLD_DRLC*)(0))->u8StartRandomizeMinutes), 0},
    {E_CLD_DRLC_STOP_RANDOMIZE_MINUTES,    (E_ZCL_AF_CA|E_ZCL_AF_WR|E_ZCL_AF_RD),   E_ZCL_UINT8,    (uint32)(&((tsCLD_DRLC*)(0))->u8StopRandomizeMinutes), 0},
    {E_CLD_DRLC_DEVICE_CLASS_VALUE,        (E_ZCL_AF_CA|E_ZCL_AF_WR|E_ZCL_AF_RD),   E_ZCL_UINT16,   (uint32)(&((tsCLD_DRLC*)(0))->u16DeviceClassValue), 0}
};
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
const tsZCL_CommandDefinition asCLD_DRLCClusterCommandDefinitions[] = {
    {SE_DRLC_REPORT_EVENT_STATUS,               E_ZCL_CF_RX},     /* Mandatory */
    {SE_DRLC_GET_SCHEDULED_EVENTS,              E_ZCL_CF_RX},     /* Mandatory */
    {SE_DRLC_LOAD_CONTROL_EVENT,                E_ZCL_CF_TX},     /* Mandatory */
    {SE_DRLC_LOAD_CONTROL_EVENT_CANCEL,         E_ZCL_CF_TX},     /* Mandatory */
    {SE_DRLC_LOAD_CONTROL_EVENT_CANCEL_ALL,     E_ZCL_CF_TX}     /* Mandatory */    
};
#endif
tsZCL_ClusterDefinition sCLD_DRLC = {
    SE_CLUSTER_ID_DEMAND_RESPONSE_AND_LOAD_CONTROL,
    FALSE,
    E_ZCL_SECURITY_NETWORK,
    (sizeof(asCLD_DRLCClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
    (tsZCL_AttributeDefinition*)asCLD_DRLCClusterAttributeDefinitions,
    NULL
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED    
    ,
    (sizeof(asCLD_DRLCClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
    (tsZCL_CommandDefinition*)asCLD_DRLCClusterCommandDefinitions         
#endif    
};

uint8 au8DRLCClusterAttributeControlBits[(sizeof(asCLD_DRLCClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************
 **
 ** NAME:       eSE_DRLCCreate
 **
 ** DESCRIPTION:
 ** Creates DRLC cluster instance either server or client
 **
 ** PARAMETERS:                         Name                                Usage
 ** bool_t                              bIsServer                           TRUE or FALSE
 ** uint8                               u8NumberOfRecordEntries             Number of Load Record Entries
 ** uint8                               *pu8AttributeControlBits            Attribute Control Bits
 ** tsZCL_ClusterInstance               *psClusterInstance                  Cluster structure
 ** tsZCL_ClusterDefinition             *psClusterDefinition                Cluster Definition Structure
 ** tsSE_DRLCCustomDataStructure        *psCustomDataStructure              Custom Data Structure
 ** tsSE_DRLCLoadControlEventRecord     *psDRLCLoadControlEventRecord       DRLC Load Control Event Records
 ** void                                *pvEndPointSharedStructPtr          EndPoint Shared Structure
 **
 ** RETURN:
 ** teSE_DRLCStatus
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eSE_DRLCCreate(
                bool_t                              bIsServer,
                uint8                               u8NumberOfRecordEntries,
                uint8                              *pu8AttributeControlBits,
                tsZCL_ClusterInstance              *psClusterInstance,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                tsSE_DRLCCustomDataStructure       *psCustomDataStructure,
                tsSE_DRLCLoadControlEventRecord    *psDRLCLoadControlEventRecord,
                void                               *pvEndPointSharedStructPtr)
{
    tsDRLC_Common *psDRLC_Common;
    int i;

    #ifdef STRICT_PARAM_CHECK 
        if((psClusterInstance==NULL)            ||
           (psClusterDefinition==NULL)          ||
           (psCustomDataStructure==NULL)        ||
           (psDRLCLoadControlEventRecord==NULL)
        )
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif
    
    if((bIsServer)&&(SE_DRLC_NUMBER_OF_SERVER_LOAD_CONTROL_ENTRIES < u8NumberOfRecordEntries))
    {
        return E_ZCL_ERR_PARAMETER_RANGE;
    }
    else if((!bIsServer)&&(SE_DRLC_NUMBER_OF_CLIENT_LOAD_CONTROL_ENTRIES < u8NumberOfRecordEntries))
    {
        return E_ZCL_ERR_PARAMETER_RANGE;
    }
    // cluster data
    vZCL_InitializeClusterInstance(
                                   psClusterInstance, 
                                   bIsServer,
                                   psClusterDefinition,
                                   pvEndPointSharedStructPtr,
                                   pu8AttributeControlBits,
                                   NULL,
                                   eSE_DRLCCommandHandler);    

    psClusterInstance->pvEndPointCustomStructPtr = (void *)psCustomDataStructure;

    // initialise pointer
    psDRLC_Common = &((tsSE_DRLCCustomDataStructure *)psClusterInstance->pvEndPointCustomStructPtr)->sDRLC_Common;

    // clear
    memset(psDRLC_Common, 0, sizeof(tsDRLC_Common));
    psDRLC_Common->sReceiveEventAddress.bInitialised = FALSE;

    // initialise the c/b structures
    psDRLC_Common->sDRLCCustomCallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_CUSTOM;
    psDRLC_Common->sDRLCCustomCallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId = psClusterInstance->psClusterDefinition->u16ClusterEnum;
    psDRLC_Common->sDRLCCustomCallBackEvent.uMessage.sClusterCustomMessage.pvCustomData = (void *)&psDRLC_Common->sDRLCCallBackMessage;
    psDRLC_Common->sDRLCCustomCallBackEvent.psClusterInstance = psClusterInstance;

    // add custom data
    psCustomDataStructure->u8NumberOfRecordEntries = u8NumberOfRecordEntries;
    psCustomDataStructure->psLoadControlEventRecord =  psDRLCLoadControlEventRecord;

    /* initialise lists */
    vDLISTinitialise(&psCustomDataStructure->lLoadControlEventActiveList);
    vDLISTinitialise(&psCustomDataStructure->lLoadControlEventScheduledList);
    vDLISTinitialise(&psCustomDataStructure->lLoadControlEventCancelledList);
    vDLISTinitialise(&psCustomDataStructure->lLoadControlEventDeAllocList);

    for(i=0; i< u8NumberOfRecordEntries; i++)
    {
        /* add all header slots to the to free list */
        vDLISTaddToTail(&psCustomDataStructure->lLoadControlEventDeAllocList, (DNODE *)&psCustomDataStructure->psLoadControlEventRecord[i]);
    }
    // Client attributes set default values
    if(bIsServer==FALSE)
    {
        ((tsCLD_DRLC *)(pvEndPointSharedStructPtr))->u8UtilityEnrolmentGroup = 0;
        ((tsCLD_DRLC *)(pvEndPointSharedStructPtr))->u8StartRandomizeMinutes = 0x1e;
        ((tsCLD_DRLC *)(pvEndPointSharedStructPtr))->u8StopRandomizeMinutes = 0x1e;
    }
    //  register timer

    return eSE_DRLCRegisterTimeServer();

}

/****************************************************************************
 **
 ** NAME:       eDRLC_SetCallBackMessage
 **
 ** DESCRIPTION:
 ** Sets Values in DRLC Callback Message
 **
 ** PARAMETERS:                     Name                        Usage
 ** tsDRLC_Common                   *psDRLC_Common              DRLC common structure
 ** teSE_DRLCCallBackEventType      eEventType                  Event type
 ** uint8                           u8CommandId                 Command
 ** teSE_DRLCStatus                 eDRLCStatus                 status
 **
 ** RETURN:
 ** teSE_DRLCStatus
 **
 ****************************************************************************/

PUBLIC  teSE_DRLCStatus eDRLC_SetCallBackMessage(
                       tsDRLC_Common                        *psDRLC_Common,
                       teSE_DRLCCallBackEventType           eEventType,
                       uint8                                u8CommandId,
                       teSE_DRLCStatus                      eDRLCStatus)
{
    #ifdef STRICT_PARAM_CHECK
        if(psDRLC_Common == NULL)
        {
            return(E_ZCL_ERR_PARAMETER_NULL);
        }
    #endif
    // fill in callback event structure
    psDRLC_Common->sDRLCCallBackMessage.eEventType = eEventType;
    psDRLC_Common->sDRLCCallBackMessage.u8CommandId = u8CommandId;
    psDRLC_Common->sDRLCCallBackMessage.u32CurrentTime = u32ZCL_GetUTCTime();
    psDRLC_Common->sDRLCCallBackMessage.eDRLCStatus = eDRLCStatus;

    return(E_ZCL_SUCCESS);
}
