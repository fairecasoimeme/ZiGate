/****************************************************************************
 *
 * MODULE:             Appilance Control Cluster
 *
 * COMPONENT:          ApplianceControlCommandHandler.c
 *
 * AUTHOR:             Shweta Chauhan
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Source/ApplianceControlCommandHandler.c $
 *
 * REVISION:           $Revision: 53395 $
 *
 * DATED:              $Date: 2013-04-19 10:56:55 +0530 (Fri, 19 Apr 2013) $
 *
 * $LastChangedDate: 2013-04-19 10:56:55 +0530 (Fri, 19 Apr 2013) $
 *
 * $Id: ApplianceControlCommandHandler.c 53395 2013-04-19 05:26:55Z nxp57621 $
 *
 * DESCRIPTION:
 * Message event handler functions
 *
 * LAST MODIFIED BY:   $Author: nxp57621 $
 *                     $Modtime: $
 *
 ****************************************************************************
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
#include <string.h>
//#include "zps_apl_aib.h"
#include "dlist.h"
#include "zcl.h"
#include "zcl_customcommand.h"

#include "ApplianceControl.h"
#include "ApplianceControl_internal.h"

#include "zcl_options.h"

#include "dbg.h"



#ifdef DEBUG_CLD_APPLIANCE_CONTROL
#define TRACE_APPLIANCE_CONTROL    TRUE
#else
#define TRACE_APPLIANCE_CONTROL    FALSE
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#if defined(CLD_APPLIANCE_CONTROL) && !defined(APPLIANCE_CONTROL_SERVER) && !defined(APPLIANCE_CONTROL_CLIENT)
#error You Must Have either APPLIANCE_CONTROL_SERVER and/or APPLIANCE_CONTROL_CLIENT defined zcl_options.h
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
#ifdef APPLIANCE_CONTROL_CLIENT
PRIVATE teZCL_Status eCLD_ACHandleSignalStateResponseORSignalStateNotification(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance);

#endif

#ifdef APPLIANCE_CONTROL_SERVER
PRIVATE teZCL_Status eCLD_ACHandleExecutionOfCommand(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance);
PRIVATE teZCL_Status eCLD_ACHandleSignalState(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance);
#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Public Functions                                              ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_ApplianceControlCommandHandler
 **
 ** DESCRIPTION:
 ** Handles Message Cluster custom commands
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ApplianceControlCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance)
{

	tsZCL_HeaderParams sZCL_HeaderParams;
    tsCLD_ApplianceControlCustomDataStructure *psCommon;

    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ApplianceControlCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Store return address details */
    eZCL_SetReceiveEventAddressStructure(pZPSevent, &psCommon->sReceiveEventAddress);

    // further error checking can only be done once we have interrogated the ZCL payload
	u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                             &sZCL_HeaderParams);

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif

    // fill in callback event structure
    eZCL_SetCustomCallBackEvent(&psCommon->sCustomCallBackEvent, pZPSevent, sZCL_HeaderParams.u8TransactionSequenceNumber, psEndPointDefinition->u8EndPointNumber);

    /* Fill in message */
    psCommon->sCallBackMessage.u8CommandId = sZCL_HeaderParams.u8CommandIdentifier; 

#ifdef APPLIANCE_CONTROL_SERVER
    /* Handle messages appropriate for the cluster type (Client/Server) */
    if(psClusterInstance->bIsServer == TRUE)
    {

        // SERVER
        switch(sZCL_HeaderParams.u8CommandIdentifier) 
        {

            case (E_CLD_APPLIANCE_CONTROL_CMD_EXECUTION_OF_COMMAND):
            {
                eCLD_ACHandleExecutionOfCommand(pZPSevent, psEndPointDefinition, psClusterInstance);
                break;

            }

            case (E_CLD_APPLIANCE_CONTROL_CMD_SIGNAL_STATE):
            {
                eCLD_ACHandleSignalState(pZPSevent, psEndPointDefinition, psClusterInstance);
                break;
            }

            default:
            {
                // unlock
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return(E_ZCL_ERR_CUSTOM_COMMAND_HANDLER_NULL_OR_RETURNED_ERROR);
                break;
            }
        }

    }
#endif

#ifdef APPLIANCE_CONTROL_CLIENT

    /* Handle messages appropriate for the cluster type (Client/Server) */
    if(psClusterInstance->bIsServer == FALSE)
    {

        // CLIENT
        if((sZCL_HeaderParams.u8CommandIdentifier == E_CLD_APPLIANCE_CONTROL_CMD_SIGNAL_STATE_RESPONSE) ||     
           (sZCL_HeaderParams.u8CommandIdentifier == E_CLD_APPLIANCE_CONTROL_CMD_SIGNAL_STATE_NOTIFICATION)) 
        {
            eCLD_ACHandleSignalStateResponseORSignalStateNotification(pZPSevent, psEndPointDefinition, psClusterInstance);
         }else{
                // unlock
            #ifndef COOPERATIVE
                eZCL_ReleaseMutex(psEndPointDefinition);
            #endif

            return(E_ZCL_ERR_CUSTOM_COMMAND_HANDLER_NULL_OR_RETURNED_ERROR);
        }
    }
#endif

    // unlock
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    // delete the i/p buffer on return
    return(E_ZCL_SUCCESS);

}

#ifdef APPLIANCE_CONTROL_SERVER
/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_ACHandleExecutionOfCommand
 **
 ** DESCRIPTION:
 ** Handles Log request
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PRIVATE  teZCL_Status eCLD_ACHandleExecutionOfCommand(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance)
{

    teZCL_Status eStatus;
    tsCLD_AC_ExecutionOfCommandPayload sPayload;
    uint8   u8TransactionSequenceNumber;
    tsCLD_ApplianceControlCustomDataStructure *psCommon;

    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ApplianceControlCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Receive the command */
    eStatus = eCLD_ACExecutionOfCommandReceive(
                                            pZPSevent,
                                            &u8TransactionSequenceNumber,
                                            &sPayload);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_APPLIANCE_CONTROL, "\nErr:eCLD_ACExecutionOfCommandReceive:%d", eStatus);
        return eStatus;
    }

    /* Message data for callback */
    psCommon->sCallBackMessage.uMessage.psExecutionOfCommandPayload = &sPayload;

    /* call callback */
    psEndPointDefinition->pCallBackFunctions(&psCommon->sCustomCallBackEvent);

    return E_ZCL_SUCCESS;
}

/****************************************************************************
 **
 ** NAME:       eCLD_ACHandleSignalState
 **
 ** DESCRIPTION:
 ** Handles Signal State
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PRIVATE  teZCL_Status eCLD_ACHandleSignalState(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance)
{

    teZCL_Status eStatus;
    uint8   u8TransactionSequenceNumber;
    tsCLD_ApplianceControlCustomDataStructure *psCommon;
    tsCLD_AC_SignalStateResponseORSignalStateNotificationPayload    sResponse = {0};
    tsZCL_Address sZCL_Address;
    bool     bApplianceStatusTwoPresent = FALSE;

    DBG_vPrintf(TRACE_APPLIANCE_CONTROL, "eCLD_ACHandleSignalState\n");
    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ApplianceControlCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Receive the command */
    eStatus = eCLD_ACSignalStateReceive(    pZPSevent,
                                            &u8TransactionSequenceNumber);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_APPLIANCE_CONTROL, "\nErr:eCLD_ACSignalStateReceive:%d", eStatus);
        return eStatus;
    }

    /* call callback */
    psCommon->sCallBackMessage.uMessage.psSignalStateResponseORSignalStateNotificationPayload = &sResponse;
    psCommon->sCallBackMessage.pbApplianceStatusTwoPresent = &bApplianceStatusTwoPresent;
    psEndPointDefinition->pCallBackFunctions(&psCommon->sCustomCallBackEvent);
    // build address structure
    eZCL_BuildClientTransmitAddressStructure(&sZCL_Address, &psCommon->sReceiveEventAddress);

    eStatus = eCLD_ACSignalStateResponseORSignalStateNotificationSend(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                                                     pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,
                                                     &sZCL_Address,
                                                     &u8TransactionSequenceNumber,
                                                     E_CLD_APPLIANCE_CONTROL_CMD_SIGNAL_STATE_RESPONSE,
                                                     bApplianceStatusTwoPresent,
                                                     &sResponse);
    return eStatus;
}
#endif

#ifdef APPLIANCE_CONTROL_CLIENT
/****************************************************************************
 **
 ** NAME:       eCLD_ACHandleSignalStateResponseORSignalStateNotification
 **
 ** DESCRIPTION:
 ** Handles Log Notification
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PRIVATE  teZCL_Status eCLD_ACHandleSignalStateResponseORSignalStateNotification(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance)
{

    teZCL_Status eStatus;
    tsCLD_AC_SignalStateResponseORSignalStateNotificationPayload sPayload;
    uint8   u8TransactionSequenceNumber;
    tsCLD_ApplianceControlCustomDataStructure *psCommon;

    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ApplianceControlCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Receive the command */
    eStatus = eCLD_ACSignalStateResponseORSignalStateNotificationReceive(
                                            pZPSevent,
                                            &u8TransactionSequenceNumber,
                                            &sPayload);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_APPLIANCE_CONTROL, "\nErr:eCLD_ACSignalStateResponseORSignalStateNotificationReceive:%d", eStatus);
        return eStatus;
    }

    /* Message data for callback */
    psCommon->sCallBackMessage.uMessage.psSignalStateResponseORSignalStateNotificationPayload = &sPayload;
    
    /* call callback */
    psEndPointDefinition->pCallBackFunctions(&psCommon->sCustomCallBackEvent);

    return E_ZCL_SUCCESS;
}

#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
