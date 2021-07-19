/*****************************************************************************
 *
 * MODULE:             IAS Zone Cluster
 *
 * COMPONENT:          IASZone.h
 *
 * AUTHOR:             
 *
 * DESCRIPTION:        Header for IAS Zone Cluster
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

#ifndef IAS_ZONE_H
#define IAS_ZONE_H

#include <jendefs.h>
#include "dlist.h"
#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Cluster ID's */
#define SECURITY_AND_SAFETY_CLUSTER_ID_IASZONE          0x0500

/* Zone Status Bits */
#define CLD_IASZONE_STATUS_MASK_ALARM1                 (1 << 0)
#define CLD_IASZONE_STATUS_MASK_ALARM2                 (1 << 1)
#define CLD_IASZONE_STATUS_MASK_TAMPER                 (1 << 2)
#define CLD_IASZONE_STATUS_MASK_BATTERY                (1 << 3)
#define CLD_IASZONE_STATUS_MASK_SUPERVISION_REPORTS    (1 << 4)
#define CLD_IASZONE_STATUS_MASK_RESTORE_REPORTS        (1 << 5)
#define CLD_IASZONE_STATUS_MASK_TROUBLE                (1 << 6)
#define CLD_IASZONE_STATUS_MASK_AC_MAINS               (1 << 7)
#define CLD_IASZONE_STATUS_MASK_TEST                   (1 << 8)
#define CLD_IASZONE_STATUS_MASK_BATTERY_DEFECT         (1 << 9)

#define CLD_IASZONE_STATUS_MASK_SET                    1
#define CLD_IASZONE_STATUS_MASK_RESET                  0

#ifndef CLD_IASZONE_NUMBER_OF_ZONE_SENSITIVITY_LEVELS
#define CLD_IASZONE_NUMBER_OF_ZONE_SENSITIVITY_LEVELS           (0x02)
#endif

#ifndef CLD_IASZONE_CURRENT_ZONE_SENSITIVITY_LEVEL
#define CLD_IASZONE_CURRENT_ZONE_SENSITIVITY_LEVEL      (0x00)
#endif
#ifndef CLD_IASZONE_CLUSTER_REVISION
    #define CLD_IASZONE_CLUSTER_REVISION               1
#endif

/****************************************************************************/
/*             IAS Zone Cluster - Optional Attributes                */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the IAS Zone cluster.                               */
/****************************************************************************/


/* End of Optional attribute dependencies */

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Attribute ID's */
typedef enum 
{
    /* 8.2.2.2.1 Zone Information Attribute Set */
    E_CLD_IASZONE_ATTR_ID_ZONE_STATE = 0x0000,                 /* Mandatory */
    E_CLD_IASZONE_ATTR_ID_ZONE_TYPE,                           /* Mandatory */
    E_CLD_IASZONE_ATTR_ID_ZONE_STATUS,                         /* Mandatory */
    /* 8.2.2.2.2 Zone Settings Attribute Set */
    E_CLD_IASZONE_ATTR_ID_IAS_CIE_ADDRESS=0x0010,              /* Mandatory */
    E_CLD_IASZONE_ATTR_ID_ZONE_ID,                             /* Mandatory */
 
    E_CLD_IASZONE_ATTR_ID_NUMBER_OF_ZONE_SENSITIVITY_LEVELS,   /* Optional  */    
    E_CLD_IASZONE_ATTR_ID_CURRENT_ZONE_SENSITIVITY_LEVEL,      /* Optional  */
} teCLD_IASZone_AttributeID;


/* IAS Zone State */
typedef enum 
{
    E_CLD_IASZONE_STATE_NOT_ENROLLED= 0x00,
    E_CLD_IASZONE_STATE_ENROLLED   
} teCLD_IASZone_State;

/* IAS Zone Type */
typedef enum 
{
    E_CLD_IASZONE_TYPE_STANDARD_CIE             = 0x0000,
    E_CLD_IASZONE_TYPE_MOTION_SENSOR            = 0x000D,
    
    E_CLD_IASZONE_TYPE_CONTACT_SWITCH           = 0x0015,
    
    E_CLD_IASZONE_TYPE_FIRE_SENSOR              = 0x0028,
    E_CLD_IASZONE_TYPE_WATER_SENSOR             = 0x002A,
    E_CLD_IASZONE_TYPE_GAS_SENSOR               = 0x002B,
    E_CLD_IASZONE_TYPE_PERSONAL_EMERGENCY_DEVICE= 0x002C,
    E_CLD_IASZONE_TYPE_VIBRATION_MOVEMENT_SENSOR= 0x002D,
    
    E_CLD_IASZONE_TYPE_REMOTE_CONTROL           = 0x010F,
    E_CLD_IASZONE_TYPE_KEY_FOB                  = 0x0115,
    E_CLD_IASZONE_TYPE_KEYPAD                   = 0x021D,
    E_CLD_IASZONE_TYPE_STANDARD_WARNING_DEVICE  = 0x0225,
    E_CLD_IASZONE_TYPE_GLASS_BREAK_SENSOR       = 0x0226,
    E_CLD_IASZONE_TYPE_SECURITY_REPEATER        = 0x0229,

    E_CLD_IASZONE_TYPE_INVALID_ZONE             = 0xFFFF,
    
} teCLD_IASZone_Type;

/* Server Received command Id*/
typedef enum 
{
    E_CLD_IASZONE_CMD_ZONE_ENROLL_RESP = 0x00,              /* Mandatory */
    E_CLD_IASZONE_CMD_INITIATE_NORMAL_OPERATION_MODE,       /* Optional  */
    E_CLD_IASZONE_CMD_INITIATE_TEST_MODE                    /* Optional  */
} teCLD_IASZone_ServerReceivedCommandID;

/* Server Generated command Id*/
typedef enum 
{
    E_CLD_IASZONE_CMD_ZONE_STATUS_CHANGE_NOTIFICATION = 0x00, /* Mandatory */
    E_CLD_IASZONE_CMD_ZONE_ENROLL_REQUEST                     /* Mandatory */
} teCLD_IASZone_ServerGeneratedCommandID;

/* Enroll Response Code*/
typedef enum 
{
   E_CLD_IASZONE_ENROLL_RESP_SUCCESS = 0x00,
   E_CLD_IASZONE_ENROLL_RESP_NOT_SUPPORTED,
   E_CLD_IASZONE_ENROLL_RESP_NO_ENROLL_PERMIT,
   E_CLD_IASZONE_ENROLL_RESP_TOO_MANY_ZONES
} teCLD_IASZoneZoneEnrollRspCode;

typedef enum 
{
    E_CLD_IASZONE_TEST_MODE_ENDED=0x00,
    E_CLD_IASZONE_TEST_MODE_ENTERED
} teCLD_IASZoneTestModeUpdate;

/*IAS Zone Cluster */
typedef struct
{
#ifdef IASZONE_SERVER    
    zenum8     e8ZoneState;          
    zenum16    e16ZoneType;
    zbmap16    b16ZoneStatus;       
    zuint64    u64IASCIEAddress; 
    zuint8     u8ZoneId;  
  #ifdef CLD_IASZONE_ATTR_ID_NUMBER_OF_ZONE_SENSITIVITY_LEVELS    
    zuint8     u8NumberOfZoneSensitivityLevels;
  #endif

  #ifdef CLD_IASZONE_ATTR_ID_CURRENT_ZONE_SENSITIVITY_LEVEL    
    zuint8     u8CurrentZoneSensitivityLevel;           
  #endif   
#endif  
    zuint16    u16ClusterRevision;
} tsCLD_IASZone; 

/* Enroll Response Payload*/
typedef struct
{
    teCLD_IASZoneZoneEnrollRspCode    e8EnrollResponseCode;          
    uint8                             u8ZoneID;
}tsCLD_IASZone_EnrollResponsePayload;

/* Status Change Notification Payload*/
typedef struct
{
    zbmap16    b16ZoneStatus;            
    zbmap8     b8ExtendedStatus;
    zuint8     u8ZoneId;
    zuint16    u16Delay;
}tsCLD_IASZone_StatusChangeNotificationPayload;

/* Enroll Request Payload*/
typedef struct
{
    zenum16    e16ZoneType;          
    uint16     u16ManufacturerCode;
}tsCLD_IASZone_EnrollRequestPayload;

/* Initiate Test Mode request Payload*/
typedef struct
{
    uint8    u8TestModeDuration;          
    uint8    u8CurrentZoneSensitivityLevel;
}tsCLD_IASZone_InitiateTestModeRequestPayload;

/* Enroll Request Callback Payload */
typedef struct
{
    tsCLD_IASZone_EnrollResponsePayload sZoneEnrollResponsePayload;
    tsCLD_IASZone_EnrollRequestPayload  *psZoneEnrollRequestPayload;
}tsCLD_IASZone_EnrollRequestCallBackPayload;

/* Initiate Test Mode request Payload*/
typedef struct
{
    teCLD_IASZoneTestModeUpdate    e8TestMode;
}tsCLD_IASZone_TestModeUpdate;

/* Definition of Call back Event Structure */
typedef struct
{
    uint8                           u8CommandId;
    union
    {
        tsCLD_IASZone_TestModeUpdate                           *psTestModeUpdate;
        
        tsCLD_IASZone_EnrollRequestCallBackPayload             sZoneEnrollRequestCallbackPayload;
        
        tsCLD_IASZone_EnrollResponsePayload                    *psZoneEnrollResponsePayload;
        tsCLD_IASZone_StatusChangeNotificationPayload          *psZoneStatusNotificationPayload;
        tsCLD_IASZone_InitiateTestModeRequestPayload           *psZoneInitiateTestModeRequestPayload;
    } uMessage;
} tsCLD_IASZoneCallBackMessage;

/* Custom data structure */
typedef struct
{
    tsCLD_IASZone_InitiateTestModeRequestPayload sTestMode;
    
    tsZCL_ReceiveEventAddress     sReceiveEventAddress;
    tsZCL_CallBackEvent           sCustomCallBackEvent;
    tsCLD_IASZoneCallBackMessage  sCallBackMessage;   
} tsCLD_IASZone_CustomDataStructure;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_IASZoneCreateIASZone (
                                tsZCL_ClusterInstance             *psClusterInstance,
                                bool_t                            bIsServer,
                                tsZCL_ClusterDefinition           *psClusterDefinition,
                                void                              *pvEndPointSharedStructPtr,
                                uint8                             *pu8AttributeControlBits,
                                tsCLD_IASZone_CustomDataStructure *psCustomDataStructure);

PUBLIC teZCL_Status eCLD_IASZoneUpdate (
                                uint8                             u8SourceEndPoint);
                                
PUBLIC teZCL_Status eCLD_IASZoneUpdateZoneStatus (
                                uint8                             u8SourceEndPoint, 
                                uint16                            u16StatusBitMask, 
                                bool_t                            bStatusState);
                                
PUBLIC teZCL_Status eCLD_IASZoneUpdateZoneState (
                                uint8                             u8SourceEndPointId,
                                teCLD_IASZone_State               eZoneState);
                                
PUBLIC teZCL_Status eCLD_IASZoneUpdateZoneType (
                                uint8                             u8SourceEndPointId,
                                teCLD_IASZone_Type                eIASZoneType);
                                
PUBLIC teZCL_Status eCLD_IASZoneUpdateZoneID (
                                uint8                             u8SourceEndPointId,
                                uint8                             u8IASZoneId);

PUBLIC teZCL_Status eCLD_IASZoneUpdateCIEAddress (
                                uint8                             u8SourceEndPointId,
                                uint64                            u64CIEAddress );
                                
PUBLIC teZCL_Status eCLD_IASZoneEnrollRespSend (
                                uint8                             u8SourceEndPointId,
                                uint8                             u8DestinationEndPointId,
                                tsZCL_Address                     *psDestinationAddress,
                                uint8                             *pu8TransactionSequenceNumber,
                                tsCLD_IASZone_EnrollResponsePayload   *psPayload);

PUBLIC teZCL_Status eCLD_IASZoneStatusChangeNotificationSend (
                                uint8                             u8SourceEndPointId,
                                uint8                             u8DestinationEndPointId,
                                tsZCL_Address                     *psDestinationAddress,
                                uint8                             *pu8TransactionSequenceNumber,
                                tsCLD_IASZone_StatusChangeNotificationPayload   *psPayload);

PUBLIC teZCL_Status eCLD_IASZoneEnrollReqSend (
                                uint8                             u8SourceEndPointId,
                                uint8                             u8DestinationEndPointId,
                                tsZCL_Address                     *psDestinationAddress,
                                uint8                             *pu8TransactionSequenceNumber,
                                tsCLD_IASZone_EnrollRequestPayload   *psPayload);
                                
PUBLIC teZCL_Status eCLD_IASZoneNormalOperationModeReqSend (
                                uint8                             u8SourceEndPointId,
                                uint8                             u8DestinationEndPointId,
                                tsZCL_Address                     *psDestinationAddress,
                                uint8                             *pu8TransactionSequenceNumber);
                                
PUBLIC teZCL_Status eCLD_IASZoneTestModeReqSend (
                                uint8                             u8SourceEndPointId,
                                uint8                             u8DestinationEndPointId,
                                tsZCL_Address                     *psDestinationAddress,
                                uint8                             *pu8TransactionSequenceNumber,
                                tsCLD_IASZone_InitiateTestModeRequestPayload    *psPayload);
                                
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_IASZone;
extern const tsZCL_AttributeDefinition asCLD_IASWDClusterAttributeDefinitions[];
extern uint8 au8IASZoneAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* IAS_ZONE_H */
