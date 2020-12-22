/*****************************************************************************
 *
 * MODULE:             Thermostat Cluster
 *
 * COMPONENT:          ThermostatCommandHandler.c
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Thermostat cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/HVAC/Source/ThermostatCommandHandler.c $
 *
 * $Revision: 65575 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2014-11-14 12:35:30 +0100 (Fri, 14 Nov 2014) $
 *
 * $Id: ThermostatCommandHandler.c 65575 2014-11-14 11:35:30Z nxp57621 $
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
#include "Thermostat.h"
#include "Thermostat_internal.h"

#include "dbg.h"

#ifdef DEBUG_CLD_THERMOSTAT
#define TRACE_THERMOSTAT    TRUE
#else
#define TRACE_THERMOSTAT    FALSE
#endif



/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#if defined(CLD_THERMOSTAT) && !defined(THERMOSTAT_SERVER) && !defined(THERMOSTAT_CLIENT)
#error You Must Have either THERMOSTAT_SERVER and/or THERMOSTAT_CLIENT defined in zcl_options.h
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#ifdef CLD_THERMOSTAT
/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
#ifdef THERMOSTAT_SERVER
PRIVATE teZCL_Status eCLD_ThermostatHandleSetpointRaiseOrLower(
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

/****************************************************************************
 **
 ** NAME:       eCLD_ThermostatCommandHandler
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
PUBLIC  teZCL_Status eCLD_ThermostatCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance)
{

	tsZCL_HeaderParams sZCL_HeaderParams;
    tsCLD_ThermostatCustomDataStructure *psCommon;

    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ThermostatCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

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

    /* Handle messages appropriate for the cluster type (Client/Server) */
    if(psClusterInstance->bIsServer)
    {
#ifdef THERMOSTAT_SERVER
       
            if(sZCL_HeaderParams.u8CommandIdentifier == E_CLD_THERMOSTAT_CMD_SETPOINT_RAISE_LOWER){
                eCLD_ThermostatHandleSetpointRaiseOrLower(pZPSevent, psEndPointDefinition, psClusterInstance);
            }else{
                // unlock
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif

                return(E_ZCL_ERR_CUSTOM_COMMAND_HANDLER_NULL_OR_RETURNED_ERROR);
            }
#endif
    }
#ifdef THERMOSTAT_CLIENT
    else
    {
        #ifndef COOPERATIVE
            eZCL_ReleaseMutex(psEndPointDefinition);
        #endif

        return(E_ZCL_ERR_CUSTOM_COMMAND_HANDLER_NULL_OR_RETURNED_ERROR);
    }
#endif


    // unlock
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    // delete the i/p buffer on return
    return(E_ZCL_SUCCESS);

}


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
#ifdef THERMOSTAT_SERVER

/****************************************************************************
 **
 ** NAME:       eCLD_ThermostatHandleSetpointRaiseOrLower
 **
 ** DESCRIPTION:
 ** Handles Thermostat Setpoint raise or lower command
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
PRIVATE  teZCL_Status eCLD_ThermostatHandleSetpointRaiseOrLower(
                            ZPS_tsAfEvent               *pZPSevent,
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance)
{

    teZCL_Status eStatus;
    tsCLD_Thermostat_SetpointRaiseOrLowerPayload sPayload;
    uint8   u8TransactionSequenceNumber;
    tsCLD_ThermostatCustomDataStructure *psCommon;

    /* Get pointer to custom data structure */
    psCommon = (tsCLD_ThermostatCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Receive the command */
    eStatus = eCLD_ThermostatCommandSetpointRaiseOrLowerReceive(
                                            pZPSevent,
                                            &u8TransactionSequenceNumber,
                                            &sPayload);
    if(eStatus != E_ZCL_SUCCESS)
    {
        DBG_vPrintf(TRACE_THERMOSTAT, "eCLD_ThermostatCommandSetpointRaiseOrLowerReceive Error: %d\r\n", eStatus);
        return eStatus;
    }

    /* Message data for callback */
    psCommon->sCallBackMessage.uMessage.psSetpointRaiseOrLowerPayload = &sPayload;

    /* call callback */
    psEndPointDefinition->pCallBackFunctions(&psCommon->sCustomCallBackEvent);
    
    /* Update attribute */
    if((sPayload.eMode == E_CLD_THERMOSTAT_SRLM_HEAT) || (sPayload.eMode == E_CLD_THERMOSTAT_SRLM_BOTH))
        ((tsCLD_Thermostat*)psClusterInstance->pvEndPointSharedStructPtr)->i16OccupiedHeatingSetpoint += (int16)sPayload.i8Amount;
    if((sPayload.eMode == E_CLD_THERMOSTAT_SRLM_COOL) || (sPayload.eMode == E_CLD_THERMOSTAT_SRLM_BOTH))
        ((tsCLD_Thermostat*)psClusterInstance->pvEndPointSharedStructPtr)->i16OccupiedCoolingSetpoint += (int16)sPayload.i8Amount;

    return E_ZCL_SUCCESS;
}

#endif /*#ifdef THERMOSTAT_SERVER */
#endif /*#ifdef  CLD_THERMOSTAT */
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

