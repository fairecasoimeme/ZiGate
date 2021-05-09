/*****************************************************************************
 *
 * MODULE:             Poll Control Cluster
 *
 * COMPONENT:          PollControlServerCommands.c
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Poll Control Cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Source/PollControlServerCommands.c $
 *
 * $Revision: 53586 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-04-25 14:18:53 +0530 (Thu, 25 Apr 2013) $
 *
 * $Id: PollControlServerCommands.c 53586 2013-04-25 08:48:53Z nxp57621 $
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

#include "PollControl.h"
#include "PollControl_internal.h"

#include "dbg.h"


#ifdef DEBUG_CLD_POLL_CONTROL
#define TRACE_POLL_CONTROL    TRUE
#else
#define TRACE_POLL_CONTROL    FALSE
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

#ifdef POLL_CONTROL_CLIENT

/****************************************************************************
 **
 ** NAME:       eCLD_PollControlCheckinReceive
 **
 ** DESCRIPTION:
 ** handles rx of Check in 
 **
 ** PARAMETERS:                                      Name                           Usage
 ** ZPS_tsAfEvent                                    *pZPSevent                     Zigbee stack event structure
 ** tsZCL_EndPointDefinition                         *psEndPointDefinition          EP structure
 ** tsZCL_ClusterInstance                            *psClusterInstance             Cluster structure
 ** uint8                                            *pu8TransactionSequenceNumber  Sequence number Pointer
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_PollControlCheckinReceive(
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber)
{

    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     0,
                                     0,
                                     E_ZCL_ACCEPT_EXACT|E_ZCL_DISABLE_DEFAULT_RESPONSE);

}

/****************************************************************************
 **
 ** NAME:       eCLD_PollControlCheckinResponseSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Checkin Response Command
 **
 ** PARAMETERS:                                           Name                               Usage
 ** uint8                                                 u8SourceEndPointId                 Source EP Id
 ** uint8                                                 u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                                         *psDestinationAddress              Destination Address
 ** uint8                                                 *pu8TransactionSequenceNumber      Sequence number Pointer
 ** tsCLD_PollControl_CheckinResponsePayload              *psPayload                         Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_PollControlCheckinResponseSend(
                                        uint8                                                       u8SourceEndPointId,
                                        uint8                                                       u8DestinationEndPointId,
                                        tsZCL_Address                                               *psDestinationAddress,
                                        uint8                                                       *pu8TransactionSequenceNumber,
                                        tsCLD_PollControl_CheckinResponsePayload                    *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
    
        {1,                              E_ZCL_BOOL,                &psPayload->bStartFastPolling},
        {1,                              E_ZCL_UINT16,              &psPayload->u16FastPollTimeout},
                                                 };
                                                 
        return eZCL_CustomCommandSend(u8SourceEndPointId,
                                      u8DestinationEndPointId,
                                      psDestinationAddress,
                                      GENERAL_CLUSTER_ID_POLL_CONTROL,
                                      FALSE,
                                      E_CLD_POLL_CONTROL_CMD_CHECKIN,
                                      pu8TransactionSequenceNumber,
                                      asPayloadDefinition,
                                      FALSE,
                                      0,
                                      sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem)
                                     );

}

/****************************************************************************
 **
 ** NAME:       eCLD_PollControlFastPollStopSend
 **
 ** DESCRIPTION:
 ** handles sending of Fast Poll Stop
 **
 ** PARAMETERS:                                Name                               Usage
 ** uint8                                      u8SourceEndPointId                 Source EP Id
 ** uint8                                      u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                              *psDestinationAddress              Destination Address
 ** uint8                                      *pu8TransactionSequenceNumber      Sequence number Pointer
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_PollControlFastPollStopSend(
                                        uint8                                                       u8SourceEndPointId,
                                        uint8                                                       u8DestinationEndPointId,
                                        tsZCL_Address                                               *psDestinationAddress,
                                        uint8                                                       *pu8TransactionSequenceNumber)
{

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_POLL_CONTROL,
                                  FALSE,
                                  E_CLD_POLL_CONTROL_CMD_FAST_POLL_STOP,
                                  pu8TransactionSequenceNumber,
                                  0,
                                  FALSE,
                                  0,
                                  0);

}

#ifdef CLD_POLL_CONTROL_CMD_SET_LONG_POLL_INTERVAL
/****************************************************************************
 **
 ** NAME:       eCLD_PollControlSetLongPollIntervalSend
 **
 ** DESCRIPTION:
 ** Sends Set Long Poll Interval
 **
 ** PARAMETERS:                                      Name                               Usage
 ** uint8                                            u8SourceEndPointId                 Source EP Id
 ** uint8                                            u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                                    *psDestinationAddress              Destination Address
 ** uint8                                            *pu8TransactionSequenceNumber      Sequence number Pointer
 ** tsCLD_PollControl_SetLongPollIntervalPayload     *psPayload                         Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_PollControlSetLongPollIntervalSend(
                                        uint8                                                       u8SourceEndPointId,
                                        uint8                                                       u8DestinationEndPointId,
                                        tsZCL_Address                                               *psDestinationAddress,
                                        uint8                                                       *pu8TransactionSequenceNumber,
                                        tsCLD_PollControl_SetLongPollIntervalPayload                *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
    
        {1,                              E_ZCL_UINT32,              &psPayload->u32NewLongPollInterval},
                                                 };
                                                 
        return eZCL_CustomCommandSend(u8SourceEndPointId,
                                      u8DestinationEndPointId,
                                      psDestinationAddress,
                                      GENERAL_CLUSTER_ID_POLL_CONTROL,
                                      FALSE,
                                      E_CLD_POLL_CONTROL_CMD_SET_LONG_POLL_INTERVAL,
                                      pu8TransactionSequenceNumber,
                                      asPayloadDefinition,
                                      FALSE,
                                      0,
                                      sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem)
                                     );

}
#endif

#ifdef CLD_POLL_CONTROL_CMD_SET_SHORT_POLL_INTERVAL
/****************************************************************************
 **
 ** NAME:       eCLD_PollControlSetShortPollIntervalSend
 **
 ** DESCRIPTION:
 ** Sends Set Long Poll Interval
 **
 ** PARAMETERS:                                      Name                               Usage
 ** uint8                                            u8SourceEndPointId                 Source EP Id
 ** uint8                                            u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                                    *psDestinationAddress              Destination Address
 ** uint8                                            *pu8TransactionSequenceNumber      Sequence number Pointer
 ** tsCLD_PollControl_SetShortPollIntervalPayload     *psPayload                        Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_PollControlSetShortPollIntervalSend(
                                        uint8                                                       u8SourceEndPointId,
                                        uint8                                                       u8DestinationEndPointId,
                                        tsZCL_Address                                               *psDestinationAddress,
                                        uint8                                                       *pu8TransactionSequenceNumber,
                                        tsCLD_PollControl_SetShortPollIntervalPayload               *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
    
        {1,                              E_ZCL_UINT16,              &psPayload->u16NewShortPollInterval},
                                                 };
                                                 
        return eZCL_CustomCommandSend(u8SourceEndPointId,
                                      u8DestinationEndPointId,
                                      psDestinationAddress,
                                      GENERAL_CLUSTER_ID_POLL_CONTROL,
                                      FALSE,
                                      E_CLD_POLL_CONTROL_CMD_SET_SHORT_POLL_INTERVAL,
                                      pu8TransactionSequenceNumber,
                                      asPayloadDefinition,
                                      FALSE,
                                      0,
                                      sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem)
                                     );

}
#endif

#endif
/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
