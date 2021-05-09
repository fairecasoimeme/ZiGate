/*****************************************************************************
 *
 * MODULE:             Alarms Cluster
 *
 * COMPONENT:          Alarms.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Alarms Cluster
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
 * exclusively on NXP products  [NXP Microcontrollers such as JN5168, JN5164,
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

#ifndef ALARMS_H
#define ALARMS_H

#include <jendefs.h>
#include "dlist.h"
#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Cluster ID's */
#define GENERAL_CLUSTER_ID_ALARMS                 0x0009

/****************************************************************************/
/*             Alarms Cluster - Optional Attributes                         */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the cluster.                                               */
/****************************************************************************/

/* Enable the optional Alarm Count attribute */
//#define   CLD_ALARMS_ATTR_ALARM_COUNT

/* Configure the maximum number of alarms */
#ifndef CLD_ALARMS_MAX_NUMBER_OF_ALARMS
#define CLD_ALARMS_MAX_NUMBER_OF_ALARMS         (10)
#endif

#ifndef CLD_ALARMS_CLUSTER_REVISION
    #define CLD_ALARMS_CLUSTER_REVISION                     1
#endif    

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Command codes - Client */
typedef enum 
{
    E_CLD_ALARMS_CMD_RESET_ALARM        = 0x00,         /* Mandatory */
    E_CLD_ALARMS_CMD_RESET_ALL_ALARMS,                  /* Mandatory */
    E_CLD_ALARMS_CMD_GET_ALARM,
    E_CLD_ALARMS_CMD_RESET_ALARM_LOG,
} teCLD_Alarms_ClientCommands;


/* Command codes - Server */
typedef enum 
{
    E_CLD_ALARMS_CMD_ALARM              = 0x00,         /* Mandatory */
    E_CLD_ALARMS_CMD_GET_ALARM_RESPONSE,
} teCLD_Alarms_ServerCommands;


/* Attribute ID's */
typedef enum 
{
    /* Alarms attribute set attribute ID's (3.11.2.1) */
    E_CLD_ALARMS_ATTR_ID_ALARM_COUNT            = 0x0000,  /* Optional */
} teCLD_Alarms_AttributeID;


/* Alarms Cluster */
typedef struct
{
#ifdef ALARMS_SERVER
    #ifdef CLD_ALARMS_ATTR_ALARM_COUNT
        zuint16                 u16AlarmCount;
    #endif
#endif
    zuint16                 u16ClusterRevision;

} tsCLD_Alarms;


/* Attribute Status */
typedef struct
{
    uint8                       u8AlarmCode;
    uint16                      u16ClusterId;
} tsCLD_AlarmsResetAlarmCommandPayload;


/* Payload for alarm command */
typedef struct
{
    uint8                       u8AlarmCode;
    uint16                      u16ClusterId;
} tsCLD_AlarmsAlarmCommandPayload;


/* Response for Get Alarm command */
typedef struct
{
    uint8                       u8Status;
    uint8                       u8AlarmCode;
    uint16                      u16ClusterId;
    uint32                      u32TimeStamp;
} tsCLD_AlarmsGetAlarmResponsePayload;


/* Alarms table entry */
typedef struct
{
    DNODE                       dllAlarmsNode;

    uint8                       u8AlarmCode;
    uint16                      u16ClusterId;
    uint32                      u32TimeStamp;
} tsCLD_AlarmsTableEntry;


/* Definition of Call back Event Structure */
typedef struct
{
    uint8                                               u8CommandId;
    union
    {
        tsCLD_AlarmsResetAlarmCommandPayload            *psResetAlarmCommandPayload;
        tsCLD_AlarmsAlarmCommandPayload                 *psAlarmCommandPayload;
        tsCLD_AlarmsGetAlarmResponsePayload             *psGetAlarmResponse;
    } uMessage;
} tsCLD_AlarmsCallBackMessage;


/* Custom data structure */
typedef struct
{
#ifdef ALARMS_SERVER    
    DLIST   lAlarmsAllocList;
    DLIST   lAlarmsDeAllocList;
#endif
    tsZCL_ReceiveEventAddress       sReceiveEventAddress;
    tsZCL_CallBackEvent             sCustomCallBackEvent;
    tsCLD_AlarmsCallBackMessage     sCallBackMessage;
#ifdef ALARMS_SERVER    
    tsCLD_AlarmsTableEntry          asAlarmsTableEntry[CLD_ALARMS_MAX_NUMBER_OF_ALARMS];
#endif    
} tsCLD_AlarmsCustomDataStructure;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_AlarmsCreateAlarms(
                    tsZCL_ClusterInstance       *psClusterInstance,
                    bool_t                      bIsServer,
                    tsZCL_ClusterDefinition     *psClusterDefinition,
                    void                        *pvEndPointSharedStructPtr,
                    uint8                       *pu8AttributeControlBits,
                    tsCLD_AlarmsCustomDataStructure *psCustomDataStructure);

#ifdef ALARMS_CLIENT                    
PUBLIC teZCL_Status eCLD_AlarmsCommandResetAlarmCommandSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsCLD_AlarmsResetAlarmCommandPayload *psPayload);

PUBLIC teZCL_Status eCLD_AlarmsCommandResetAllAlarmsCommandSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber);

PUBLIC teZCL_Status eCLD_AlarmsCommandGetAlarmCommandSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber);

PUBLIC teZCL_Status eCLD_AlarmsCommandResetAlarmLogCommandSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber);
#endif

#ifdef ALARMS_SERVER
PUBLIC teZCL_Status eCLD_AlarmsResetAlarmLog(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC teZCL_Status eCLD_AlarmsAddAlarmToLog(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance,
                    uint8                       u8AlarmCode,
                    uint16                      u16ClusterId);

PUBLIC teZCL_Status eCLD_AlarmsGetAlarmFromLog(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance,
                    uint8                       *pu8AlarmCode,
                    uint16                      *pu16ClusterId,
                    uint32                      *pu32TimeStamp);

PUBLIC teZCL_Status eCLD_AlarmsSignalAlarm(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint8                       u8AlarmCode,
                    uint16                      u16ClusterId);
#endif                    
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern tsZCL_ClusterDefinition sCLD_Alarms;
extern const tsZCL_AttributeDefinition asCLD_AlarmsClusterAttributeDefinitions[];
extern uint8 au8AlarmsAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* ALARMS_H */
