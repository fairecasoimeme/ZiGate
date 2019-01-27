/*****************************************************************************
 *
 * MODULE:             Commissioning Cluster
 *
 * COMPONENT:          CommissioningClientCommands.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Send an Commissioning cluster command
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/Commissioning/Source/CommissioningClientCommands.c $
 *
 * $Revision: 71852 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-08-12 11:00:24 +0200 (Wed, 12 Aug 2015) $
 *
 * $Id: CommissioningClientCommands.c 71852 2015-08-12 09:00:24Z nxp57621 $
 *
 ****************************************************************************
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
#include "zcl_customcommand.h"

#include "Commissioning.h"
#include "Commissioning_internal.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"

#include "dbg.h"

#ifdef DEBUG_CLD_COMMISSIONING
#define TRACE_COMMS    TRUE
#else
#define TRACE_COMMS    FALSE
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
#ifdef COMMISSIONING_CLIENT
/****************************************************************************
 **
 ** NAME:       eCLD_CommissioningCommandRestartDeviceSend
 **
 ** DESCRIPTION:
 ** Builds and sends a restart device cluster command
 **
 ** PARAMETERS:                                 Name                           Usage
 ** uint8                                       u8SourceEndPointId             Source EP Id
 ** uint8                                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address                               *psDestinationAddress          Destination Address
 ** uint8                                       *pu8TransactionSequenceNumber  Sequence number Pointer
 ** tsCLD_Commissioning_RestartDevicePayload    *psPayload                     Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_CommissioningCommandRestartDeviceSend(
                                        uint8                                       u8SourceEndPointId,
                                        uint8                                       u8DestinationEndPointId,
                                        tsZCL_Address                               *psDestinationAddress,
                                        uint8                                       *pu8TransactionSequenceNumber,
                                        tsCLD_Commissioning_RestartDevicePayload    *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1,                         E_ZCL_BMAP8,   &psPayload->u8Options},
            {1,                         E_ZCL_UINT8,   &psPayload->u8Delay},
            {1,                         E_ZCL_UINT8,   &psPayload->u8Jitter},
                                              };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  COMMISSIONING_CLUSTER_ID_COMMISSIONING,
                                  FALSE,
                                  E_CLD_COMMISSIONING_CMD_RESTART_DEVICE,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}

/****************************************************************************
 **
 ** NAME:       eCLD_CommissioningCommandModifyStartupParamsSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Save, restore and Reset start up parameters cluster command
 **
 ** PARAMETERS:                                         Name                           Usage
 ** uint8                                               u8SourceEndPointId             Source EP Id
 ** uint8                                               u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address                                       *psDestinationAddress          Destination Address
 ** uint8                                               *pu8TransactionSequenceNumber  Sequence number Pointer
 ** tsCLD_Commissioning_ModifyStartupParametersPayload  *psPayload                     Payload
 ** teCLD_Commissioning_Command                         eCLD_Commissioning_Command     CommandID
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_CommissioningCommandModifyStartupParamsSend(
                                        uint8                                               u8SourceEndPointId,
                                        uint8                                               u8DestinationEndPointId,
                                        tsZCL_Address                                       *psDestinationAddress,
                                        uint8                                               *pu8TransactionSequenceNumber,
                                        tsCLD_Commissioning_ModifyStartupParametersPayload  *psPayload,
                                        teCLD_Commissioning_Command                         eCLD_Commissioning_Command)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1,                         E_ZCL_BMAP8,   &psPayload->u8Options},
            {1,                         E_ZCL_UINT8,   &psPayload->u8Index},
                                              };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  COMMISSIONING_CLUSTER_ID_COMMISSIONING,
                                  FALSE,
                                  eCLD_Commissioning_Command,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}

/****************************************************************************
 **
 ** NAME:       eCLD_CommissioningCommandResponseReceive
 **
 ** DESCRIPTION:
 ** handles rx of commissioning response
 **
 ** PARAMETERS:                         Name                           Usage
 ** ZPS_tsAfEvent                       *pZPSevent                     Zigbee stack event structure
 ** tsZCL_EndPointDefinition            *psEndPointDefinition          EP structure
 ** tsZCL_ClusterInstance               *psClusterInstance             Cluster structure
 ** uint8                               *pu8TransactionSequenceNumber  Sequence number Pointer
 ** tsCLD_Commissioning_ResponsePayload *psPayload                     Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_CommissioningCommandResponseReceive(
                    ZPS_tsAfEvent                       *pZPSevent,
                    uint8                               *pu8TransactionSequenceNumber,
                    tsCLD_Commissioning_ResponsePayload *psPayload)
{

    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
    {1, &u16ActualQuantity, E_ZCL_ENUM8,   &psPayload->u8Status},
                                                };

    return eZCL_CustomCommandReceive(pZPSevent,
                                        pu8TransactionSequenceNumber,
                                        asPayloadDefinition,
                                        sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                        E_ZCL_ACCEPT_EXACT);

}
#endif /*COMMISSIONING_CLIENT*/
/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
