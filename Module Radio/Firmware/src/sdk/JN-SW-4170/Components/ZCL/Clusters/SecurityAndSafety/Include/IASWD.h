/*****************************************************************************
 *
 * MODULE:             IAS WD Cluster
 *
 * COMPONENT:          IASWD.h
 *
 * AUTHOR:             
 *
 * DESCRIPTION:        Header for IAS WD Cluster
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy:  $
 *
 * $LastChangedDate:  $
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

#ifndef IAS_WD_H
#define IAS_WD_H

#include <jendefs.h>
#include "dlist.h"
#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Cluster ID's */
#define SECURITY_AND_SAFETY_CLUSTER_ID_IASWD          0x0502

#ifndef CLD_IASWD_CLUSTER_REVISION
    #define CLD_IASWD_CLUSTER_REVISION               1
#endif

/****************************************************************************/
/*             IAS WD Cluster - Optional Attributes                */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the IAS WD cluster.                               */
/****************************************************************************/


/* End of Optional attribute dependencies */

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Attribute ID's */
typedef enum 
{
    E_CLD_IASWD_ATTR_ID_MAX_DURATION        = 0x0000,   /* Mandatory*/
} teCLD_IASWD_AttributeID;

typedef enum 
{
    E_CLD_IASWD_WARNING_STOP=0,
    E_CLD_IASWD_WARNING_BURGLAR,
    E_CLD_IASWD_WARNING_FIRE,
    E_CLD_IASWD_WARNING_EMERGENCY
}teCLD_IASWD_WarningMode;

typedef enum 
{
    E_CLD_IASWD_NO_STROBE_WITH_WARNING=0,
    E_CLD_IASWD_STROBE_WITH_WARNING
}teCLD_IASWD_WarningStrobe;

typedef enum 
{
    E_CLD_IASWD_SIREN_LOW_SOUND=0,
    E_CLD_IASWD_SIREN_MEDIUM_SOUND,
    E_CLD_IASWD_SIREN_HIGH_SOUND,
    E_CLD_IASWD_SIREN_VERY_HIGH_SOUND
}teCLD_IASWD_SirenLevel;

typedef enum 
{
    E_CLD_IASWD_STROBE_LOW=0,
    E_CLD_IASWD_STROBE_MEDIUM,
    E_CLD_IASWD_STROBE_HIGH,
    E_CLD_IASWD_STROBE_VERY_HIGH
}teCLD_IASWD_StrobeLevel;

typedef enum 
{
    E_CLD_IASWD_SQUAWK_SYSTEM_ARMED=0,
    E_CLD_IASWD_SQUAWK_SYSTEM_DISARMED
}teCLD_IASWD_SquawkMode;

typedef enum 
{
    E_CLD_IASWD_NO_STROBE_WITH_SQUAWK=0,
    E_CLD_IASWD_STROBE_WITH_SQUAWK
}teCLD_IASWD_SquawkStrobe;

typedef enum 
{
    E_CLD_IASWD_SQUAWK_LOW_SOUND=0,
    E_CLD_IASWD_SQUAWK_MEDIUM_SOUND,
    E_CLD_IASWD_SQUAWK_HIGH_SOUND,
    E_CLD_IASWD_SQUAWK_VERY_HIGH_SOUND
}teCLD_IASWD_SquawkLevel;

typedef enum 
{
    E_CLD_IASWD_CLUSTER_UPDATE_STROBE =0,
    E_CLD_IASWD_CLUSTER_UPDATE_WARNING
}teCLD_IASWD_ClusterUpdate;

/* Server Received command Id*/
typedef enum 
{
    E_CLD_IASWD_CMD_START_WARNING = 0x00,              /* Mandatory */
    E_CLD_IASWD_CMD_SQUAWK
} teCLD_IASWD_ServerReceivedCommandID;

/*IAS WD Cluster */
typedef struct
{
#ifdef IASWD_SERVER   
    zuint16     u16MaxDuration;  
#endif    
    zuint16     u16ClusterRevision;    
} tsCLD_IASWD; 

typedef struct
{
    uint8       u8WarningModeStrobeAndSirenLevel;
    uint16      u16WarningDuration;
    uint8       u8StrobeDutyCycle;
    zenum8      eStrobeLevel;
}tsCLD_IASWD_StartWarningReqPayload;

typedef struct
{
    uint8                         u8SquawkModeStrobeAndLevel ;  
}tsCLD_IASWD_SquawkReqPayload;

typedef struct
{
    bool_t      bStrobe;
    uint8       u8StrobeDutyCycle;
    zenum8      eStrobeLevel;
}tsCLD_IASWD_StrobeUpdate;

typedef struct
{
    uint8       u8WarningMode;
    uint8       u8SirenLevel;
    uint16      u16WarningDurationRemaining;

    uint8       u8StrobeWithWarning;
    bool_t      bStrobe;
    zenum8      eStrobeLevel;
}tsCLD_IASWD_WarningUpdate;

/* Definition of Call back Event Structure */
typedef struct
{
    uint8                           u8CommandId;
    union
    {
        tsCLD_IASWD_StartWarningReqPayload    *psWDStartWarningReqPayload;
        tsCLD_IASWD_SquawkReqPayload          *psWDSquawkReqPayload;
        tsCLD_IASWD_StrobeUpdate              *psStrobeUpdate;
        tsCLD_IASWD_WarningUpdate             *psWarningUpdate;

    } uMessage;
} tsCLD_IASWDCallBackMessage;

/* Custom data structure */
typedef struct
{
    tsCLD_IASWD_SquawkReqPayload          sSquawk;
    tsCLD_IASWD_StartWarningReqPayload    sWarning;
    uint32                                u32WarningDurationRemainingIn100MS;
    
    tsZCL_ReceiveEventAddress     sReceiveEventAddress;
    tsZCL_CallBackEvent           sCustomCallBackEvent;
    tsCLD_IASWDCallBackMessage    sCallBackMessage;   
} tsCLD_IASWD_CustomDataStructure;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_IASWDCreateIASWD (
                                tsZCL_ClusterInstance           *psClusterInstance,
                                bool_t                          bIsServer,
                                tsZCL_ClusterDefinition         *psClusterDefinition,
                                void                            *pvEndPointSharedStructPtr,
                                uint8                           *pu8AttributeControlBits,
                                tsCLD_IASWD_CustomDataStructure *psCustomDataStructure);
#ifdef IASWD_SERVER
PUBLIC teZCL_Status eCLD_IASWDUpdate (
                                uint8                             u8SourceEndPoint);
#endif

#ifdef IASWD_CLIENT
PUBLIC teZCL_Status eCLD_IASWDStartWarningReqSend (
                                uint8                              u8SourceEndPointId,
                                uint8                              u8DestinationEndPointId,
                                tsZCL_Address                      *psDestinationAddress,
                                uint8                              *pu8TransactionSequenceNumber,
                                tsCLD_IASWD_StartWarningReqPayload *psPayload);
PUBLIC teZCL_Status eCLD_IASWDSquawkReqSend (
                                uint8                              u8SourceEndPointId,
                                uint8                              u8DestinationEndPointId,
                                tsZCL_Address                      *psDestinationAddress,
                                uint8                              *pu8TransactionSequenceNumber,
                                tsCLD_IASWD_SquawkReqPayload       *psPayload); 
#endif                                
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_IASWD;
extern const tsZCL_AttributeDefinition asCLD_IASWDClusterAttributeDefinitions[];
extern uint8 au8IASWDAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* IAS_WD_H */
