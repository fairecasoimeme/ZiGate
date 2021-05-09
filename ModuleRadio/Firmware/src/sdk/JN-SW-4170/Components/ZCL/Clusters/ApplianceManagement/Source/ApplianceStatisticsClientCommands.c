/*****************************************************************************
 *
 * MODULE:             Appliance Statistics Cluster
 *
 * COMPONENT:          ApplianceStatisticsClientCommands.c
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Appliance Statistics Cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Source/ApplianceStatisticsClientCommands.c $
 *
 * $Revision: 53376 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-04-18 17:44:23 +0530 (Thu, 18 Apr 2013) $
 *
 * $Id: ApplianceStatisticsClientCommands.c 53376 2013-04-18 12:14:23Z nxp57621 $
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

#include "ApplianceStatistics.h"
#include "ApplianceStatistics_internal.h"

#include "dbg.h"


#ifdef DEBUG_CLD_APPLIANCE_STATISTICS
#define TRACE_APPLIANCE_STATISTICS    TRUE
#else
#define TRACE_APPLIANCE_STATISTICS    FALSE
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

#ifdef APPLIANCE_STATISTICS_CLIENT
/****************************************************************************
 **
 ** NAME:       eCLD_ASCLogNotificationORLogResponseReceive
 **
 ** DESCRIPTION:
 ** Receives a Log notification & Log Response command
 **
 ** PARAMETERS:                                                     Name                               Usage
 ** uint8                                                           u8SourceEndPointId                 Source EP Id
 ** uint8                                                           u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                                                   *psDestinationAddress              Destination Address
 ** uint8                                                           *pu8TransactionSequenceNumber      Sequence number Pointer
 ** teCLD_ApplianceStatistics_ServerCommandId                       eCommandId                         Command Id 
 ** tsCLD_ASC_LogNotificationORLogResponsePayload                   *psPayload                         Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ASCLogNotificationORLogResponseReceive(
                                        ZPS_tsAfEvent                                               *pZPSevent,
                                        uint8                                                       *pu8TransactionSequenceNumber,
                                        tsCLD_ASC_LogNotificationORLogResponsePayload               *psPayload)
{

    uint16 u16ActualQuantity;
    tsZCL_RxPayloadItem asPayloadDefinition[] = {
            {1,                                                       &u16ActualQuantity,                  E_ZCL_UINT32,                       &(psPayload->utctTime)},
            {1,                                                       &u16ActualQuantity,                  E_ZCL_UINT32,                       &(psPayload->u32LogId)},
            {1,                                                       &u16ActualQuantity,                  E_ZCL_UINT32,                       &(psPayload->u32LogLength)},
            {CLD_APPLIANCE_STATISTICS_ATTR_LOG_MAX_SIZE,              &u16ActualQuantity,                  E_ZCL_UINT8,                        psPayload->pu8LogData},
                                                          };

    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     asPayloadDefinition,
                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                     E_ZCL_ACCEPT_LESS);

}

/****************************************************************************
 **
 ** NAME:       eCLD_ASCLogQueueResponseORStatisticsAvailableReceive
 **
 ** DESCRIPTION:
 ** Builds and sends a Log notification & Log Response command
 **
 ** PARAMETERS:                                                     Name                               Usage
 ** uint8                                                           u8SourceEndPointId                 Source EP Id
 ** uint8                                                           u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                                                   *psDestinationAddress              Destination Address
 ** uint8                                                           *pu8TransactionSequenceNumber      Sequence number Pointer
 ** tsCLD_ASC_LogQueueResponseORStatisticsAvailablePayload           *psPayload                         Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ASCLogQueueResponseORStatisticsAvailableReceive(
                                                        ZPS_tsAfEvent                                             *pZPSevent,
                                                        uint8                                                     *pu8TransactionSequenceNumber,
                                                        tsCLD_ASC_LogQueueResponseORStatisticsAvailablePayload    *psPayload)
{
    uint16 u16ActualQuantity;
    tsZCL_RxPayloadItem asPayloadDefinition[] = {
             {1,                                                     &u16ActualQuantity,             E_ZCL_UINT8,            &(psPayload->u8LogQueueSize)},
             {CLD_APPLIANCE_STATISTICS_ATTR_LOG_QUEUE_MAX_SIZE,      &u16ActualQuantity,             E_ZCL_UINT32,           psPayload->pu32LogId},
                                                          };
    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     asPayloadDefinition,
                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                     E_ZCL_ACCEPT_LESS);

}


/****************************************************************************
 **
 ** NAME:       eCLD_ASCLogRequestSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Log Request command
 **
 ** PARAMETERS:                                         Name                               Usage
 ** uint8                                               u8SourceEndPointId                 Source EP Id
 ** uint8                                               u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                                       *psDestinationAddress              Destination Address
 ** uint8                                               *pu8TransactionSequenceNumber      Sequence number Pointer
 ** tsCLD_ASC_LogRequestPayload                         *psPayload                         Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ASCLogRequestSend(
                    uint8                                                       u8SourceEndPointId,
                    uint8                                                       u8DestinationEndPointId,
                    tsZCL_Address                                               *psDestinationAddress,
                    uint8                                                       *pu8TransactionSequenceNumber,
                    tsCLD_ASC_LogRequestPayload                                 *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
    {1,                                     E_ZCL_UINT32,                               &psPayload->u32LogId},
                                                };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_STATISTICS,
                                  FALSE,
                                  E_CLD_APPLIANCE_STATISTICS_CMD_LOG_REQUEST,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
}

/****************************************************************************
 **
 ** NAME:       eCLD_ASCLogQueueRequestSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Log Queue Request command
 **
 ** PARAMETERS:                                         Name                               Usage
 ** uint8                                               u8SourceEndPointId                 Source EP Id
 ** uint8                                               u8DestinationEndPointId            Destination EP Id
 ** tsZCL_Address                                       *psDestinationAddress              Destination Address
 ** uint8                                               *pu8TransactionSequenceNumber      Sequence number Pointer
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ASCLogQueueRequestSend(
                    uint8                                                       u8SourceEndPointId,
                    uint8                                                       u8DestinationEndPointId,
                    tsZCL_Address                                               *psDestinationAddress,
                    uint8                                                       *pu8TransactionSequenceNumber)
{


    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_STATISTICS,
                                  FALSE,
                                  E_CLD_APPLIANCE_STATISTICS_CMD_LOG_QUEUE_REQUEST,
                                  pu8TransactionSequenceNumber,
                                  0,
                                  FALSE,
                                  0,
                                  0);
}
#endif
/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
