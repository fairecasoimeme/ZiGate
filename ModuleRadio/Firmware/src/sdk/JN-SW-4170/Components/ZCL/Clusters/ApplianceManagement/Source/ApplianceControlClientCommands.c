/*****************************************************************************
 *
 * MODULE:             Appliance Statistics Cluster
 *
 * COMPONENT:          ApplianceControlClientCommands.c
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Appliance Control Cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Source/ApplianceControlClientCommands.c $
 *
 * $Revision: 53387 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-04-18 20:07:02 +0530 (Thu, 18 Apr 2013) $
 *
 * $Id: ApplianceControlClientCommands.c 53387 2013-04-18 14:37:02Z nxp57621 $
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

#include "zcl.h"
#include "zcl_customcommand.h"

#include "ApplianceControl.h"
#include "ApplianceControl_internal.h"

#include "dbg.h"


#ifdef DEBUG_CLD_APPLIANCE_CONTROL
#define TRACE_APPLIANCE_CONTROL    TRUE
#else
#define TRACE_APPLIANCE_CONTROL    FALSE
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

/****************************************************************************/
/***        Public Functions                                              ***/
/****************************************************************************/

#ifdef APPLIANCE_CONTROL_CLIENT
/****************************************************************************
 **
 ** NAME:       eCLD_ACExecutionOfCommandSend
 **
 ** DESCRIPTION:
 ** Sends an Execution of command
 **
 ** PARAMETERS:                                     Name                               Usage
 ** uint8                                           8SourceEndPointId                 Source EP Id
 ** uint8                                           u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                                      *psDestinationAddress              Destination Address
 ** uint8                                              pu8TransactionSequenceNumber      Sequence number Pointer
 ** tsCLD_AC_ExecutionOfCommandPayload                 *psPayload                        Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ACExecutionOfCommandSend(
                    uint8                                                       u8SourceEndPointId,
                    uint8                                                       u8DestinationEndPointId,
                    tsZCL_Address                                               *psDestinationAddress,
                    uint8                                                       *pu8TransactionSequenceNumber,
                    tsCLD_AC_ExecutionOfCommandPayload                          *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
    {1,                                     E_ZCL_UINT8,                               &psPayload->eExecutionCommandId},
                                                };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_CONTROL,
                                  FALSE,
                                  E_CLD_APPLIANCE_CONTROL_CMD_EXECUTION_OF_COMMAND,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
}

/****************************************************************************
 **
 ** NAME:       eCLD_ACSignalStateSend
 **
 ** DESCRIPTION:
 ** Sends a Signal State Command
 **
 ** PARAMETERS:                     Name                               Usage
 ** uint8                           u8SourceEndPointId                 Source EP Id
 ** uint8                           u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                   *psDestinationAddress              Destination Address
 ** uint8                           *pu8TransactionSequenceNumber      Sequence number Pointer
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ACSignalStateSend(
                    uint8                                                       u8SourceEndPointId,
                    uint8                                                       u8DestinationEndPointId,
                    tsZCL_Address                                               *psDestinationAddress,
                    uint8                                                       *pu8TransactionSequenceNumber)
{

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_CONTROL,
                                  FALSE,
                                  E_CLD_APPLIANCE_CONTROL_CMD_SIGNAL_STATE,
                                  pu8TransactionSequenceNumber,
                                  0,
                                  FALSE,
                                  0,
                                  0);
}

/****************************************************************************
 **
 ** NAME:       eCLD_ACSignalStateResponseORSignalStateNotificationReceive
 **
 ** DESCRIPTION:
 ** Builds and sends a Log notification & Log Response command
 **
 ** PARAMETERS:                                                     Name                               Usage
 ** uint8                                                           u8SourceEndPointId                 Source EP Id
 ** uint8                                                           u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                                                   *psDestinationAddress              Destination Address
 ** uint8                                                           *pu8TransactionSequenceNumber      Sequence number Pointer
 **    teCLD_ApplianceControl_ServerCommandId                       eCommandId                        Command Id 
 ** tsCLD_AC_SignalStateResponseORSignalStateNotificationPayload    *psPayload                        Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ACSignalStateResponseORSignalStateNotificationReceive(
                                                    ZPS_tsAfEvent                                                       *pZPSevent,
                                                    uint8                                                               *pu8TransactionSequenceNumber,
                                                    tsCLD_AC_SignalStateResponseORSignalStateNotificationPayload        *psPayload)
{
    uint16 u16ActualQuantity;
    tsZCL_RxPayloadItem asPayloadDefinition[] = {
             {1,                                &u16ActualQuantity,         E_ZCL_UINT8,            &(psPayload->eApplianceStatus)},
             {1,                                &u16ActualQuantity,         E_ZCL_UINT8,            &(psPayload->u8RemoteEnableFlagAndDeviceStatusTwo)},
             {1,                                &u16ActualQuantity,         E_ZCL_UINT24,           &(psPayload->u24ApplianceStatusTwo)},
                                                          };
    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     asPayloadDefinition,
                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                     E_ZCL_ACCEPT_LESS);

}

#endif
/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
