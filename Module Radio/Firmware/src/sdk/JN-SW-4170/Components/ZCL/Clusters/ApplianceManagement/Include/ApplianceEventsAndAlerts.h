/*****************************************************************************
 *
 * MODULE:             Appliance Events and Alerts Cluster
 *
 * COMPONENT:          ApplianceEventsAndAlerts.h
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Header for Appliance Event and Alert Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Include/ApplianceEventsAndAlerts.h $
 *
 * $Revision: 53725 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-05-06 15:51:34 +0530 (Mon, 06 May 2013) $
 *
 * $Id: ApplianceEventsAndAlerts.h 53725 2013-05-06 10:21:34Z nxp57621 $
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

#ifndef APPLIANCE_EVENTS_AND_ALERTS_H
#define APPLIANCE_EVENTS_AND_ALERTS_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "zcl_customcommand.h"
#include "dlist.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/*             Appliance Events And Alerts Cluster - Optional Attributes    */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the Appliance events and alert cluster.                    */
/****************************************************************************/

/* Cluster ID's */
#define APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_EVENTS_AND_ALERTS                     0x0b02

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#ifndef CLD_APPLIANCE_EVENTS_AND_ALERTS_MAXIMUM_NUM_OF_ALERTS    
    #define CLD_APPLIANCE_EVENTS_AND_ALERTS_MAXIMUM_NUM_OF_ALERTS       16
#else
    #if (CLD_APPLIANCE_EVENTS_AND_ALERTS_MAXIMUM_NUM_OF_ALERTS > 16)
        #error Number of alerts in Alerts response or notification can not be more than 16
    #endif
#endif

#ifndef CLD_APPLIANCE_EVENTS_AND_ALERTS_CLUSTER_REVISION
    #define CLD_APPLIANCE_EVENTS_AND_ALERTS_CLUSTER_REVISION                     1
#endif   

/* Command codes */
typedef enum 
{
    E_CLD_APPLIANCE_EVENTS_AND_ALERTS_CMD_GET_ALERTS                               = 0x00,    /* Mandatory */
    E_CLD_APPLIANCE_EVENTS_AND_ALERTS_CMD_ALERTS_NOTIFICATION,                                /* Mandatory */
    E_CLD_APPLIANCE_EVENTS_AND_ALERTS_CMD_EVENT_NOTIFICATION                                  /* Mandatory */
} teCLD_ApplianceEventsAndAlerts_CommandId;

/* Appliance Events & Alerts Cluster */
typedef struct
{
    zuint16                         u16ClusterRevision;
} tsCLD_ApplianceEventsAndAlerts;


/* Get Alerts Response & Alerts Notification  Payload */
typedef struct
{
    zuint8                    u8AlertsCount;
    zuint24                   au24AlertStructure[CLD_APPLIANCE_EVENTS_AND_ALERTS_MAXIMUM_NUM_OF_ALERTS];
} tsCLD_AEAA_GetAlertsResponseORAlertsNotificationPayload;

/* Events Notification Payload */
typedef struct
{
      zuint8                    u8EventHeader;
      zuint8                    u8EventIdentification;
} tsCLD_AEAA_EventNotificationPayload;

typedef struct
{
    uint8                                       u8CommandId;
    union
    {
        tsCLD_AEAA_GetAlertsResponseORAlertsNotificationPayload            *psGetAlertsResponseORAlertsNotificationPayload;
        tsCLD_AEAA_EventNotificationPayload                                *psEventNotificationPayload;
    } uMessage;
} tsCLD_ApplianceEventsAndAlertsCallBackMessage;

/* Custom data structure */
typedef struct
{
    tsZCL_ReceiveEventAddress sReceiveEventAddress;
    tsZCL_CallBackEvent sCustomCallBackEvent;
    tsCLD_ApplianceEventsAndAlertsCallBackMessage sCallBackMessage;
} tsCLD_ApplianceEventsAndAlertsCustomDataStructure;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_ApplianceEventsAndAlertsCreateApplianceEventsAndAlerts(
                tsZCL_ClusterInstance                                  *psClusterInstance,
                bool_t                                                 bIsServer,
                tsZCL_ClusterDefinition                                *psClusterDefinition,
                void                                                   *pvEndPointSharedStructPtr,
                uint8                                                  *pu8AttributeControlBits,
                tsCLD_ApplianceEventsAndAlertsCustomDataStructure      *psCustomDataStructure);
         
#ifdef APPLIANCE_EVENTS_AND_ALERTS_SERVER
PUBLIC INLINE teZCL_Status eCLD_AEAAAlertsNotificationSend(                
                uint8                                                         u8SourceEndPointId,
                uint8                                                         u8DestinationEndPointId,
                tsZCL_Address                                                 *psDestinationAddress,
                uint8                                                         *pu8TransactionSequenceNumber,
                tsCLD_AEAA_GetAlertsResponseORAlertsNotificationPayload       *psPayload) ALWAYS_INLINE;
                
PUBLIC teZCL_Status eCLD_AEAAGetAlertsResponseORAlertsNotificationSend(
                uint8                                                                       u8SourceEndPointId,
                uint8                                                                       u8DestinationEndPointId,
                tsZCL_Address                                                               *psDestinationAddress,
                uint8                                                                       *pu8TransactionSequenceNumber,
                teCLD_ApplianceEventsAndAlerts_CommandId                                    eCommandId,
                tsCLD_AEAA_GetAlertsResponseORAlertsNotificationPayload                     *psPayload);

PUBLIC INLINE teZCL_Status eCLD_AEAAAlertsNotificationSend(                
                uint8                                                         u8SourceEndPointId,
                uint8                                                         u8DestinationEndPointId,
                tsZCL_Address                                                 *psDestinationAddress,
                uint8                                                         *pu8TransactionSequenceNumber,
                tsCLD_AEAA_GetAlertsResponseORAlertsNotificationPayload       *psPayload)
{
    // handle sequence number get a new sequence number
    if(pu8TransactionSequenceNumber != NULL)
        *pu8TransactionSequenceNumber = u8GetTransactionSequenceNumber();
        
    return eCLD_AEAAGetAlertsResponseORAlertsNotificationSend(
                                                     u8SourceEndPointId,
                                                u8DestinationEndPointId,
                                                   psDestinationAddress,
                                           pu8TransactionSequenceNumber,
              E_CLD_APPLIANCE_EVENTS_AND_ALERTS_CMD_ALERTS_NOTIFICATION,
                                                              psPayload);
}
                
PUBLIC teZCL_Status eCLD_AEAAEventNotificationSend(
                uint8                                                                       u8SourceEndPointId,
                uint8                                                                       u8DestinationEndPointId,
                tsZCL_Address                                                               *psDestinationAddress,
                uint8                                                                       *pu8TransactionSequenceNumber,
                tsCLD_AEAA_EventNotificationPayload                                         *psPayload);
#endif        

#ifdef APPLIANCE_EVENTS_AND_ALERTS_CLIENT    
PUBLIC teZCL_Status eCLD_AEAAGetAlertsSend(
                uint8                                                       u8SourceEndPointId,
                uint8                                                       u8DestinationEndPointId,
                tsZCL_Address                                               *psDestinationAddress,
                uint8                                                       *pu8TransactionSequenceNumber);
#endif    
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_ApplianceEventsAndAlerts;
extern const tsZCL_AttributeDefinition asCLD_ApplianceEventsAndAlertsClusterAttributeDefinitions[];
extern uint8 au8ApplianceEventsAndAlertsAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* APPLIANCE_EVENTS_AND_ALERTS_H */
