/*****************************************************************************
 *
 * MODULE:             Identify Cluster
 *
 * COMPONENT:          Identify.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Identify Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Include/Identify.h $
 *
 * $Revision: 72591 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-09-08 14:41:01 +0200 (Tue, 08 Sep 2015) $
 *
 * $Id: Identify.h 72591 2015-09-08 12:41:01Z nxp57621 $
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

#ifndef IDENTIFY_H
#define IDENTIFY_H

#include <jendefs.h>
#include "dlist.h"
#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Cluster ID's */
#define GENERAL_CLUSTER_ID_IDENTIFY                 0x0003


#define CLD_IDENTIFY_NUMBER_OF_MANDATORY_ATTRIBUTE  1 //u16IdentifyTime


#define CLD_IDENTIFY_NUMBER_OF_OPTIONAL_ATTRIBUTE   1

#define CLD_IDENTIFY_MAX_NUMBER_OF_ATTRIBUTE       \
    CLD_IDENTIFY_NUMBER_OF_OPTIONAL_ATTRIBUTE +    \
    CLD_IDENTIFY_NUMBER_OF_MANDATORY_ATTRIBUTE

/****************************************************************************/
/*             Identify Cluster - Optional Attributes                */
/*                                                                           */
/* Add the following #define's to your zcl_options.h file to add optional    */
/* attributes to the identify cluster.                                       */
/****************************************************************************/

/* Commission State attribute */
//#define CLD_IDENTIFY_ATTR_COMMISSION_STATE

/* EZ Mode Invoke Command */
//#define CLD_IDENTIFY_CMD_EZ_MODE_INVOKE

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Commission State - bit definitions and bit masks */
#define IDENTIFY_COMMISSION_STATE_NETWORK       (1 << 0)
#define IDENTIFY_COMMISSION_STATE_OPERATIONAL   (1 << 1)

/* EZMODE INVOKE  - bit definitions and bit masks */
#define IDENTIFY_CMD_EZMODE_INVOKE_ACTION_FACTOTY_FRESH             (1 << 0)
#define IDENTIFY_CMD_EZMODE_INVOKE_ACTION_NETWORK_STEERING          (1 << 1)
#define IDENTIFY_CMD_EZMODE_INVOKE_ACTION_FINDING_AND_BINDING       (1 << 2)

#ifndef CLD_IDENTIFY_CLUSTER_REVISION
    #define CLD_IDENTIFY_CLUSTER_REVISION                         1
#endif 


/* Command codes */
typedef enum 
{
    E_CLD_IDENTIFY_CMD_IDENTIFY                 = 0x00,    /* Mandatory */
    E_CLD_IDENTIFY_CMD_IDENTIFY_QUERY,                     /* Mandatory */
    E_CLD_IDENTIFY_CMD_EZ_MODE_INVOKE,
    E_CLD_IDENTIFY_CMD_UPDATE_COMMISSION_STATE,
    E_CLD_IDENTIFY_CMD_TRIGGER_EFFECT =             0x40   /* Optional*/
} teCLD_Identify_Command;

typedef enum 
{
    E_CLD_IDENTIFY_EFFECT_BLINK             = 0x00,
    E_CLD_IDENTIFY_EFFECT_BREATHE,
    E_CLD_IDENTIFY_EFFECT_OKAY,
    E_CLD_IDENTIFY_EFFECT_CHANNEL_CHANGE    = 0x0b,
    E_CLD_IDENTIFY_EFFECT_FINISH_EFFECT     = 0xfe,
    E_CLD_IDENTIFY_EFFECT_STOP_EFFECT       = 0xff
} teCLD_Identify_EffectId;

/* Attribute ID's */
typedef enum 
{
    /* Identify attribute set attribute ID's (3.5.2.2) */
    E_CLD_IDENTIFY_ATTR_ID_IDENTIFY_TIME     = 0x0000,   /* Mandatory */
    E_CLD_IDENTIFY_ATTR_ID_COMMISSION_STATE,             /* Optional */
} teCLD_Identify_ClusterID;


/* Identify Cluster */
typedef struct
{
#ifdef IDENTIFY_SERVER    
    zuint16                 u16IdentifyTime;
#ifdef CLD_IDENTIFY_ATTR_COMMISSION_STATE
    zbmap8                  u8CommissionState;
#endif  
#endif
    zuint16                 u16ClusterRevision;
} tsCLD_Identify;


/* Identify request command payload */
typedef struct
{
    zuint16                 u16IdentifyTime;
} tsCLD_Identify_IdentifyRequestPayload;


/* Identify query response command payload */
typedef struct
{
    zuint16                 u16Timeout;
} tsCLD_Identify_IdentifyQueryResponsePayload;

/* trigger effect command payload */
typedef struct
{
    teCLD_Identify_EffectId     eEffectId;
    zuint8                      u8EffectVarient;
} tsCLD_Identify_TriggerEffectRequestPayload;

#ifdef CLD_IDENTIFY_CMD_EZ_MODE_INVOKE
/* Identify EZ mode Invoke command payload */
typedef struct
{
    zbmap8                u8Action;
} tsCLD_Identify_EZModeInvokePayload;
#endif

#ifdef CLD_IDENTIFY_ATTR_COMMISSION_STATE
/* Identify Update Commission State command payload */
typedef struct
{
    zenum8                u8Action;
    zbmap8                u8CommissionStateMask;
} tsCLD_Identify_UpdateCommissionStatePayload;
#endif

/* Definition of Identify Call back Event Structure */
typedef struct
{
    uint8                                       u8CommandId;
    union
    {
        tsCLD_Identify_IdentifyRequestPayload           *psIdentifyRequestPayload;
        tsCLD_Identify_IdentifyQueryResponsePayload     *psIdentifyQueryResponsePayload;
        tsCLD_Identify_TriggerEffectRequestPayload      *psTriggerEffectRequestPayload;
#ifdef CLD_IDENTIFY_CMD_EZ_MODE_INVOKE      
        tsCLD_Identify_EZModeInvokePayload              *psEZModeInvokePayload;
#endif
#ifdef CLD_IDENTIFY_ATTR_COMMISSION_STATE
        tsCLD_Identify_UpdateCommissionStatePayload     *psUpdateCommissionStatePayload;
#endif      
    } uMessage;
} tsCLD_IdentifyCallBackMessage;


/* Custom data structure */
typedef struct
{
    tsZCL_ReceiveEventAddress         sReceiveEventAddress;
    tsZCL_CallBackEvent               sCustomCallBackEvent;
    tsCLD_IdentifyCallBackMessage     sCallBackMessage;
} tsCLD_IdentifyCustomDataStructure;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_IdentifyCreateIdentify(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits,
                tsCLD_IdentifyCustomDataStructure  *psCustomDataStructure);

PUBLIC teZCL_Status eCLD_IdentifyRegisterTimeServer(void);

#ifdef IDENTIFY_CLIENT
PUBLIC teZCL_Status eCLD_IdentifyCommandIdentifyRequestSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber,
                tsCLD_Identify_IdentifyRequestPayload *psPayload);

PUBLIC teZCL_Status eCLD_IdentifyCommandIdentifyQueryRequestSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber);
#ifdef CLD_IDENTIFY_ATTR_COMMISSION_STATE
PUBLIC teZCL_Status eCLD_IdentifyUpdateCommissionStateCommandSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber,
                tsCLD_Identify_UpdateCommissionStatePayload *psPayload);
                
#endif              
                
#ifdef  CLD_IDENTIFY_CMD_TRIGGER_EFFECT
PUBLIC teZCL_Status eCLD_IdentifyCommandTriggerEffectSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber,
                teCLD_Identify_EffectId     eEffectId,
                uint8   u8EffectVarient);
#endif
#endif /*IDENTIFY_CLIENT*/      
          
#ifdef CLD_IDENTIFY_CMD_EZ_MODE_INVOKE
PUBLIC teZCL_Status eCLD_IdentifyEZModeInvokeCommandSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber,
                bool            bDirection,
                tsCLD_Identify_EZModeInvokePayload *psPayload);
                
#endif              

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern tsZCL_ClusterDefinition sCLD_Identify;
extern const tsZCL_AttributeDefinition asCLD_IdentifyClusterAttributeDefinitions[];
extern uint8 au8IdentifyAttributeControlBits[];
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* IDENTIFY_H */
