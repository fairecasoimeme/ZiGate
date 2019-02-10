/*****************************************************************************
 *
 * MODULE:             Appliance Control Cluster
 *
 * COMPONENT:          ApplianceControl.h
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Header for Appliance Control Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Include/ApplianceControl.h $
 *
 * $Revision: 53493 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-04-22 18:33:48 +0530 (Mon, 22 Apr 2013) $
 *
 * $Id: ApplianceControl.h 53493 2013-04-22 13:03:48Z nxp57621 $
 *
 *****************************************************************************
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

#ifndef APPLIANCE_CONTROL_H
#define APPLIANCE_CONTROL_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "zcl_customcommand.h"
#include "dlist.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/*             Appliance Control Cluster - Optional Attributes                          */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the Appliance Control  cluster.                                         */
/****************************************************************************/

/* Remaining Time attribute */
//#ifdef CLD_APPLIANCE_CONTROL_REMAINING_TIME

/* Optional Global Attribute Reporting Status */
//#ifdef CLD_APPLIANCE_CONTROL_ATTRIBUTE_REPORTING_STATUS

/* Cluster ID's */
#define APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_CONTROL                                 0x001b

#ifndef CLD_APPLIANCE_CONTROL_CLUSTER_REVISION
    #define CLD_APPLIANCE_CONTROL_CLUSTER_REVISION                     1
#endif   

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    E_CLD_APPLIANCE_CONTROL_ATTR_ID_START_TIME                           = 0x0000, /* Mandatory */
    E_CLD_APPLIANCE_CONTROL_ATTR_ID_FINISH_TIME,                                   /* Mandatory */
    E_CLD_APPLIANCE_CONTROL_ATTR_ID_REMAINING_TIME,                                /* Optional */
} teCLD_ApplianceControl_Cluster_AttrID;

/* Client Command codes */
typedef enum 
{
    E_CLD_APPLIANCE_CONTROL_CMD_EXECUTION_OF_COMMAND                = 0x00,     /* Mandatory */
    E_CLD_APPLIANCE_CONTROL_CMD_SIGNAL_STATE,                                   /* Mandatory */
} teCLD_ApplianceControl_ClientCommandId;

/* Server Command codes */
typedef enum 
{
    E_CLD_APPLIANCE_CONTROL_CMD_SIGNAL_STATE_RESPONSE                = 0x00,     /* Mandatory */
    E_CLD_APPLIANCE_CONTROL_CMD_SIGNAL_STATE_NOTIFICATION                        /* Mandatory */
} teCLD_ApplianceControl_ServerCommandId;

/* Appliance Control Cluster */
typedef struct
{
#ifdef APPLIANCE_CONTROL_SERVER    
    zuint16                         u16StartTime;
    zuint16                         u16FinishTime;
#ifdef CLD_APPLIANCE_CONTROL_REMAINING_TIME
    zuint16                         u16RemainingTime;
#endif
#ifdef CLD_APPLIANCE_CONTROL_ATTRIBUTE_REPORTING_STATUS
    zenum8                          u8AttributeReportingStatus;
#endif
#endif
    zuint16                         u16ClusterRevision; 
} tsCLD_ApplianceControl;

/* Execution of Command Payload */
typedef struct
{
    zenum8                         eExecutionCommandId;
} tsCLD_AC_ExecutionOfCommandPayload;

/* Signal State Response  & Signal State Notifivcation Payload */
typedef struct
{
    zenum8                         eApplianceStatus;
    zuint8                         u8RemoteEnableFlagAndDeviceStatusTwo;
    zuint24                        u24ApplianceStatusTwo;
} tsCLD_AC_SignalStateResponseORSignalStateNotificationPayload;

typedef struct
{
    uint8                                       u8CommandId;
    bool                                        *pbApplianceStatusTwoPresent;
    union
    {
        tsCLD_AC_ExecutionOfCommandPayload                               *psExecutionOfCommandPayload;
        tsCLD_AC_SignalStateResponseORSignalStateNotificationPayload     *psSignalStateResponseORSignalStateNotificationPayload;
    } uMessage;
} tsCLD_ApplianceControlCallBackMessage;

/* Custom data structure */
typedef struct
{
    tsZCL_ReceiveEventAddress                 sReceiveEventAddress;
    tsZCL_CallBackEvent                       sCustomCallBackEvent;
    tsCLD_ApplianceControlCallBackMessage     sCallBackMessage;
} tsCLD_ApplianceControlCustomDataStructure;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_ApplianceControlCreateApplianceControl(
                tsZCL_ClusterInstance                              *psClusterInstance,
                bool_t                                             bIsServer,
                tsZCL_ClusterDefinition                            *psClusterDefinition,
                void                                               *pvEndPointSharedStructPtr,
                uint8                                              *pu8AttributeControlBits,
                tsCLD_ApplianceControlCustomDataStructure          *psCustomDataStructure);
                
#ifdef APPLIANCE_CONTROL_SERVER
PUBLIC INLINE teZCL_Status eCLD_ACSignalStateNotificationSend(                
                uint8                                                         u8SourceEndPointId,
                uint8                                                         u8DestinationEndPointId,
                tsZCL_Address                                                 *psDestinationAddress,
                uint8                                                         *pu8TransactionSequenceNumber,
                bool                                                          bApplianceStatusTwoPresent,
                tsCLD_AC_SignalStateResponseORSignalStateNotificationPayload  *psPayload) ALWAYS_INLINE;
                
PUBLIC teZCL_Status eCLD_ACSignalStateResponseORSignalStateNotificationSend(
                uint8                                                               u8SourceEndPointId,
                uint8                                                               u8DestinationEndPointId,
                tsZCL_Address                                                       *psDestinationAddress,
                uint8                                                               *pu8TransactionSequenceNumber,
                teCLD_ApplianceControl_ServerCommandId                              eCommandId,
                bool                                                                bApplianceStatusTwoPresent,
                tsCLD_AC_SignalStateResponseORSignalStateNotificationPayload       *psPayload);

PUBLIC INLINE teZCL_Status eCLD_ACSignalStateNotificationSend(                
                uint8                                                         u8SourceEndPointId,
                uint8                                                         u8DestinationEndPointId,
                tsZCL_Address                                                 *psDestinationAddress,
                uint8                                                         *pu8TransactionSequenceNumber,
                bool                                                          bApplianceStatusTwoPresent,
                tsCLD_AC_SignalStateResponseORSignalStateNotificationPayload  *psPayload)
{
    // handle sequence number get a new sequence number
    if(pu8TransactionSequenceNumber != NULL)
        *pu8TransactionSequenceNumber = u8GetTransactionSequenceNumber();
    return eCLD_ACSignalStateResponseORSignalStateNotificationSend(
                                                     u8SourceEndPointId,
                                                u8DestinationEndPointId,
                                                   psDestinationAddress,
                                           pu8TransactionSequenceNumber,
                  E_CLD_APPLIANCE_CONTROL_CMD_SIGNAL_STATE_NOTIFICATION,
                                             bApplianceStatusTwoPresent,
                                                              psPayload);
}
                
PUBLIC teZCL_Status eCLD_ACChangeAttributeTime(
                uint8                                             u8SourceEndPointId,
                teCLD_ApplianceControl_Cluster_AttrID             eAttributeTimeId,
                uint16                                            u16TimeValue);        
#endif

#ifdef APPLIANCE_CONTROL_CLIENT                    
PUBLIC teZCL_Status eCLD_ACExecutionOfCommandSend(
                uint8                                               u8SourceEndPointId,
                uint8                                               u8DestinationEndPointId,
                tsZCL_Address                                       *psDestinationAddress,
                uint8                                               *pu8TransactionSequenceNumber,
                tsCLD_AC_ExecutionOfCommandPayload                  *psPayload);
                    
PUBLIC teZCL_Status eCLD_ACSignalStateSend(
                uint8                                               u8SourceEndPointId,
                uint8                                               u8DestinationEndPointId,
                tsZCL_Address                                       *psDestinationAddress,
                uint8                                               *pu8TransactionSequenceNumber);
#endif                    
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern tsZCL_ClusterDefinition sCLD_ApplianceControl;
extern const tsZCL_AttributeDefinition asCLD_ApplianceControlClusterAttributeDefinitions[];
extern uint8 au8ApplianceControlAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* APPLIANCE_CONTROL_H */
