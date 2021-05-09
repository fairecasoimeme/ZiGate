/*****************************************************************************
 *
 * MODULE:             Basic Cluster
 *
 * COMPONENT:          Basic.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Basic Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Include/Basic.h $
 *
 * $Revision: 73733 $
 *
 * $LastChangedBy: nxp29772 $
 *
 * $LastChangedDate: 2015-10-28 12:30:13 +0100 (Wed, 28 Oct 2015) $
 *
 * $Id: Basic.h 73733 2015-10-28 11:30:13Z nxp29772 $
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

#ifndef BASIC_H
#define BASIC_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/*             Basic Cluster - Optional Attributes                          */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the basic cluster.                                         */
/****************************************************************************/

#ifdef CLD_SM_SUPPORT_MIRROR

#ifndef CLD_BAS_ATTR_PHYSICAL_ENVIRONMENT
    /*Required for maintaining the Mirror capability at ESI*/
    #define CLD_BAS_ATTR_PHYSICAL_ENVIRONMENT
#endif

#endif

/* Enable the optional Application Version attribute */
//#define   CLD_BAS_ATTR_APPLICATION_VERSION

/* Enable the optional Stack Version attribute*/
//#define   CLD_BAS_ATTR_STACK_VERSION

/* Enable the optional Hardware Version attribute */
//#define   CLD_BAS_ATTR_HARDWARE_VERSION

/* Enable the optional Manufacturer Name attribute */
//#define   CLD_BAS_ATTR_MANUFACTURER_NAME

/* Enable the optional Model Identifier attribute */
//#define   CLD_BAS_ATTR_MODEL_IDENTIFIER

/* Enable the optional Date Code attribute */
//#define   CLD_BAS_ATTR_DATE_CODE

/* Enable the optional Location Description attribute */
//#define   CLD_BAS_ATTR_LOCATION_DESCRIPTION

/* Enable the optional Physical Environment attribute */
//#define   CLD_BAS_ATTR_PHYSICAL_ENVIRONMENT

/* Enable the optional Device Enabled attribute */
//#define   CLD_BAS_ATTR_DEVICE_ENABLED

/* Enable the optional Alarm Mask attribute */
//#define   CLD_BAS_ATTR_ALARM_MASK

/* Enable the optional Disable Local Config attribute */
//#define CLD_BAS_ATTR_DISABLE_LOCAL_CONFIG

/* Enable the optional Software Build ID attribute */
//#define CLD_BAS_ATTR_SW_BUILD_ID

/* Enable the optional Generic Device Class attribute */
//#define CLD_BAS_ATTR_GENERIC_DEVICE_CLASS

/* Enable the optional Generic Device Type attribute */
//#define CLD_BAS_ATTR_GENERIC_DEVICE_TYPE

/* Enable the optional Product code attribute */
//#define CLD_BAS_ATTR_PRODUCT_CODE

/* Enable the optional Product URL attribute */
//#define CLD_BAS_ATTR_PRODUCT_URL

/* End of optional attributes */
#ifndef CLD_BAS_APP_VERSION
#define CLD_BAS_APP_VERSION         (0x00)
#endif
#ifndef CLD_BAS_STACK_VERSION
#define CLD_BAS_STACK_VERSION       (0x00)
#endif
#ifndef CLD_BAS_HARDWARE_VERSION
#define CLD_BAS_HARDWARE_VERSION    (0x00)
#endif
#ifndef CLD_BAS_MANUF_NAME_SIZE
#define CLD_BAS_MANUF_NAME_SIZE     (0)
#endif
#ifndef CLD_BAS_MODEL_ID_SIZE
#define CLD_BAS_MODEL_ID_SIZE       (0)
#endif
#ifndef CLD_BAS_DATE_SIZE
#define CLD_BAS_DATE_SIZE           (0)
#endif
#ifndef CLD_BAS_POWER_SOURCE
#define CLD_BAS_POWER_SOURCE        E_CLD_BAS_PS_UNKNOWN
#endif

#ifndef CLD_BAS_SW_BUILD_SIZE
#define CLD_BAS_SW_BUILD_SIZE       (0)
#endif
#ifndef CLD_BAS_URL_SIZE
#define CLD_BAS_URL_SIZE            (0)
#endif
#ifndef CLD_BAS_PCODE_SIZE
#define CLD_BAS_PCODE_SIZE          (0)
#endif

#ifndef CLD_BAS_DEVICE_CLASS
#define CLD_BAS_DEVICE_CLASS          (0xff)
#endif


/* Cluster ID's */
#define GENERAL_CLUSTER_ID_BASIC                            0x0000

/* Alarm Mask */
#define CLD_BAS_ALARM_MASK_GENERAL_HARDWARE_FAULT           (1 << 0)
#define CLD_BAS_ALARM_MASK_GENERAL_SOFTWARE_FAULT           (1 << 1)

/* Disable Local Config */
#define CLD_BAS_DISABLE_LOCAL_CFG_RESET                     (1 << 0)
#define CLD_BAS_DISABLE_LOCAL_CFG_DISABLED                  (1 << 1)

#define CLD_BASIC_NUMBER_OF_MANDATORY_ATTRIBUTE              3  //ePowerSource and u8ZCLVersion

#ifdef CLD_BAS_ATTR_APPLICATION_VERSION
    #define ATTR_APPLICATION_VERSION                         1
#else
    #define ATTR_APPLICATION_VERSION                         0
#endif

#ifdef CLD_BAS_ATTR_APPLICATION_LEGRAND
    #define ATTR_APPLICATION_LEGRAND                    	 1
#else
    #define ATTR_APPLICATION_LEGRAND                         0
#endif

#ifdef CLD_BAS_ATTR_STACK_VERSION
    #define ATTR_STACK_VERSION                               1
#else
    #define ATTR_STACK_VERSION                               0
#endif

#ifdef CLD_BAS_ATTR_HARDWARE_VERSION
    #define ATTR_HARDWARE_VERSION                            1
#else
    #define ATTR_HARDWARE_VERSION                            0
#endif

#ifdef CLD_BAS_ATTR_MANUFACTURER_NAME
    #define ATTR_MANUFACTURER_NAME                           1
#else
    #define ATTR_MANUFACTURER_NAME                           0
#endif
#ifdef CLD_BAS_ATTR_MODEL_IDENTIFIER
    #define ATTR_MODEL_IDENTIFIER                            1
#else
    #define ATTR_MODEL_IDENTIFIER                            0
#endif
#ifdef CLD_BAS_ATTR_DATE_CODE
    #define ATTR_DATE_CODE                                   1
#else
    #define ATTR_DATE_CODE                                   0
#endif
#ifdef CLD_BAS_ATTR_LOCATION_DESCRIPTION
    #define ATTR_LOCATION_DESCRIPTION                        1
#else
    #define ATTR_LOCATION_DESCRIPTION                        0
#endif
#ifdef CLD_BAS_ATTR_DEVICE_ENABLED
    #define ATTR_DEVICE_ENABLED                              1
#else
    #define ATTR_DEVICE_ENABLED                              0
#endif
#ifdef CLD_BAS_ATTR_PHYSICAL_ENVIRONMENT
    #define ATTR_PHYSICAL_ENVIRONMENT                        1
#else
    #define ATTR_PHYSICAL_ENVIRONMENT                        0
#endif


#ifdef CLD_BAS_ATTR_ALARM_MASK
    #define ATTR_ALARM_MASK                                  1
#else
    #define ATTR_ALARM_MASK                                  0
#endif
#ifdef CLD_BAS_ATTR_DISABLE_LOCAL_CONFIG
    #define ATTR_DISABLE_LOCAL_CONFIG                        1
#else
    #define ATTR_DISABLE_LOCAL_CONFIG                        0
#endif
#ifdef CLD_BAS_ATTR_SW_BUILD_ID
    #define ATTR_SW_BUILD_ID                                 1
#else
    #define ATTR_SW_BUILD_ID                                 0
#endif

#ifndef CLD_BAS_CLUSTER_REVISION
    #define CLD_BAS_CLUSTER_REVISION                         1
#endif 

#define CLD_BASIC_NUMBER_OF_OPTIONAL_ATTRIBUTE  \
    ATTR_APPLICATION_VERSION        +           \
    ATTR_STACK_VERSION              +           \
    ATTR_HARDWARE_VERSION           +           \
    ATTR_MANUFACTURER_NAME          +           \
    ATTR_MODEL_IDENTIFIER           +           \
    ATTR_DATE_CODE                  +           \
    ATTR_LOCATION_DESCRIPTION       +           \
    ATTR_DEVICE_ENABLED             +           \
    ATTR_PHYSICAL_ENVIRONMENT       +           \
    ATTR_ALARM_MASK                 +           \
    ATTR_DISABLE_LOCAL_CONFIG       +           \
    ATTR_APPLICATION_LEGRAND        +			\
    ATTR_SW_BUILD_ID

#define CLD_BASIC_MAX_NUMBER_OF_ATTRIBUTE       \
    CLD_BASIC_NUMBER_OF_OPTIONAL_ATTRIBUTE +    \
    CLD_BASIC_NUMBER_OF_MANDATORY_ATTRIBUTE
    
#ifndef CLD_BASIC_MAX_NUMBER_OF_BYTES_PRODUCT_CODE
    #define CLD_BASIC_MAX_NUMBER_OF_BYTES_PRODUCT_CODE                    16
#endif
#ifndef CLD_BASIC_MAX_NUMBER_OF_BYTES_PRODUCT_URL
    #define CLD_BASIC_MAX_NUMBER_OF_BYTES_PRODUCT_URL                     32
#endif    
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Command codes */
typedef enum 
{
    E_CLD_BASIC_CMD_RESET_TO_FACTORY_DEFAULTS    = 0x00
} teCLD_Basic_Command;

typedef enum 
{
    /* Basic Device Information attribute set attribute ID's (3.2.2.2.1) */
    E_CLD_BAS_ATTR_ID_ZCL_VERSION                = 0x0000, /* Mandatory */
    E_CLD_BAS_ATTR_ID_APPLICATION_VERSION,
    E_CLD_BAS_ATTR_ID_STACK_VERSION,
    E_CLD_BAS_ATTR_ID_HARDWARE_VERSION,
    E_CLD_BAS_ATTR_ID_MANUFACTURER_NAME,
    E_CLD_BAS_ATTR_ID_MODEL_IDENTIFIER,
    E_CLD_BAS_ATTR_ID_DATE_CODE,
    E_CLD_BAS_ATTR_ID_POWER_SOURCE,                       /* Mandatory */
    
    /* ZLO extension to Basic cluster */
    E_CLD_BAS_ATTR_ID_GENERIC_DEVICE_CLASS,
    E_CLD_BAS_ATTR_ID_GENERIC_DEVICE_TYPE,
    E_CLD_BAS_ATTR_ID_PRODUCT_CODE,
    E_CLD_BAS_ATTR_ID_PRODUCT_URL,

    /* Basic Device Settings attribute set attribute ID's (3.2.2.2.10) */
    E_CLD_BAS_ATTR_ID_LOCATION_DESCRIPTION        = 0x0010,
    E_CLD_BAS_ATTR_ID_PHYSICAL_ENVIRONMENT,
    E_CLD_BAS_ATTR_ID_DEVICE_ENABLED,
    E_CLD_BAS_ATTR_ID_ALARM_MASK,
    E_CLD_BAS_ATTR_ID_DISABLE_LOCAL_CONFIG,
    E_CLD_BAS_ATTR_ID_SW_BUILD_ID               = 0x4000,
    E_CLD_BAS_ATTR_ID_LEGRAND                   = 0xF000,
    E_CLD_BAS_ATTR_ID_XIAOMI_FF01               = 0xFF01,
    E_CLD_BAS_ATTR_ID_XIAOMI_FF02               = 0xFF02,
} teCLD_BAS_ClusterID;


/* Generic Device Class */
typedef enum 
{
    E_CLD_BAS_GENERIC_DEVICE_CLASS_LIGHTING         = 0x00,
} teCLD_BAS_GenericDeviceClass;

/* Generic Device Type */
typedef enum 
{
    E_CLD_BAS_GENERIC_DEVICE_TYPE_INCANDESCENT       = 0x00,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_SPOTLIGHT_HALOGEN,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_HALOGEN_BULB,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_CFL,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_LINEAR_FLUORESCENT,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_LED_BULB,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_SPOTLIGHT_LED,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_LED_STRIP,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_LED_TUBE,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_INDOOR_LUMINAIRE,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_OUTDOOR_LUMINAIRE,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_PENDANT_LUMINAIRE,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_FLOOR_STANDING_LUMINAIRE,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_CONTROLLER        = 0xE0,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_WALL_SWITCH,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_PORTABLE_REMOTE_CONTROLLER,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_MOTION_OR_LIGHT_SENSOR,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_ACTUATOR         = 0xF0,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_WALL_SOCKET,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_GATEWAY_OR_BRIDGE,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_PLUG_IN_UNIT,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_RETROFIT_ACTUATOR,
    E_CLD_BAS_GENERIC_DEVICE_TYPE_UNSPECIFIED     = 0xFF
} teCLD_BAS_GenericDeviceType;

/* Power source */
typedef enum 
{
    E_CLD_BAS_PS_UNKNOWN                                            = 0x00,
    E_CLD_BAS_PS_SINGLE_PHASE_MAINS,
    E_CLD_BAS_PS_THREE_PHASE_MAINS,
    E_CLD_BAS_PS_BATTERY,
    E_CLD_BAS_PS_DC_SOURCE,
    E_CLD_BAS_PS_EMERGENCY_MAINS_CONSTANTLY_POWERED,
    E_CLD_BAS_PS_EMERGENCY_MAINS_AND_TRANSFER_SWITCH,
    E_CLD_BAS_PS_UNKNOWN_BATTERY_BACKED                                = 0x80,
    E_CLD_BAS_PS_SINGLE_PHASE_MAINS_BATTERY_BACKED,
    E_CLD_BAS_PS_THREE_PHASE_MAINS_BATTERY_BACKED,
    E_CLD_BAS_PS_BATTERY_BATTERY_BACKED,
    E_CLD_BAS_PS_DC_SOURCE_BATTERY_BACKED,
    E_CLD_BAS_PS_EMERGENCY_MAINS_CONSTANTLY_POWERED_BATTERY_BACKED,
    E_CLD_BAS_PS_EMERGENCY_MAINS_AND_TRANSFER_SWITCH_BATTERY_BACKED,
} teCLD_BAS_PowerSource;

/* Physical Environment */
typedef enum 
{
    E_CLD_BAS_PE_UNSPECIFIED                                       = 0x00,
    E_CLD_BAS_PE_MIRROR,
    E_CLD_BAS_PE_ATRIUM,
    E_CLD_BAS_PE_BAR,
    E_CLD_BAS_PE_COURTYARD,
    E_CLD_BAS_PE_BATHROOM,
    E_CLD_BAS_PE_BEDROOM,
    E_CLD_BAS_PE_BILLIARD_ROOM,
    E_CLD_BAS_PE_UTILITY_ROOM,
    E_CLD_BAS_PE_CELLAR,
    E_CLD_BAS_PE_STORAGE_CLOSET,
    E_CLD_BAS_PE_THREATER,
    E_CLD_BAS_PE_OFFICE_0x0B,
    E_CLD_BAS_PE_DECK,
    E_CLD_BAS_PE_DEN,
    E_CLD_BAS_PE_DINNING_ROOM,
    E_CLD_BAS_PE_ELECTRICAL_ROOM,
    E_CLD_BAS_PE_ELEVATOR,
    E_CLD_BAS_PE_ENTRY,
    E_CLD_BAS_PE_FAMILY_ROOM,
    E_CLD_BAS_PE_MAIN_FLOOR,
    E_CLD_BAS_PE_UPSTAIRS,
    E_CLD_BAS_PE_DOWNSTAIRS,
    E_CLD_BAS_PE_BASEMENT_LOWER_LEVEL,
    E_CLD_BAS_PE_GALLERY,
    E_CLD_BAS_PE_GAME_ROOM,
    E_CLD_BAS_PE_GARAGE,
    E_CLD_BAS_PE_GYM,
    E_CLD_BAS_PE_HALLWAY,
    E_CLD_BAS_PE_HOUSE,
    E_CLD_BAS_PE_KITCHEN,
    E_CLD_BAS_PE_LAUNDRY_ROOM,
    E_CLD_BAS_PE_LIBRARY,
    E_CLD_BAS_PE_MASTER_BEDROOM,
    E_CLD_BAS_PE_MUD_ROOM,
    E_CLD_BAS_PE_NURSERY,
    E_CLD_BAS_PE_PANTRY,
    E_CLD_BAS_PE_OFFICE_0X24,
    E_CLD_BAS_PE_OUTSIDE,
    E_CLD_BAS_PE_POOL,
    E_CLD_BAS_PE_PORCH,
    E_CLD_BAS_PE_SEWING_ROOM,
    E_CLD_BAS_PE_SITTING_ROOM,
    E_CLD_BAS_PE_STAIRWAY,
    E_CLD_BAS_PE_YARD,
    E_CLD_BAS_PE_ATTIC,
    E_CLD_BAS_PE_HOT_TUB,
    E_CLD_BAS_PE_LIVING_ROOM_0X2E,
    E_CLD_BAS_PE_SAUNA,
    E_CLD_BAS_PE_SHOP_WORKSHOP,
    E_CLD_BAS_PE_GUEST_BEDROOM,
    E_CLD_BAS_PE_GUEST_BATH,
    E_CLD_BAS_PE_POWDER_ROOM,
    E_CLD_BAS_PE_BACK_YARD,
    E_CLD_BAS_PE_FRONT_YARD,
    E_CLD_BAS_PE_PATIO,
    E_CLD_BAS_PE_DRIVEWAY,
    E_CLD_BAS_PE_SUN_ROOM,
    E_CLD_BAS_PE_LIVING_ROOM_0X39,
    E_CLD_BAS_PE_SPA,
    E_CLD_BAS_PE_WHIRLPOOL,
    E_CLD_BAS_PE_SHED,
    E_CLD_BAS_PE_EQUIPMENT_STORAGE,
    E_CLD_BAS_PE_HOBBY_CRAFT_ROOM,
    E_CLD_BAS_PE_FOUNTAIN,
    E_CLD_BAS_PE_POND,
    E_CLD_BAS_PE_RECEPTION_ROOM,
    E_CLD_BAS_PE_BREAKFAST_ROOM,
    E_CLD_BAS_PE_NOOK,
    E_CLD_BAS_PE_GARDEN,
    E_CLD_BAS_PE_PANIC_ROOM,
    E_CLD_BAS_PE_TERRACE,
    E_CLD_BAS_PE_ROOF,
    E_CLD_BAS_PE_TOILET,
    E_CLD_BAS_PE_TOILET_MAIN,
    E_CLD_BAS_PE_OUTSIDE_TOILET,
    E_CLD_BAS_PE_SHOWER_ROOM,
    E_CLD_BAS_PE_STUDY,
    E_CLD_BAS_PE_FRONT_GARDEN,
    E_CLD_BAS_PE_BACK_GARDEN,
    E_CLD_BAS_PE_KETTLE,
    E_CLD_BAS_PE_TELEVISION,
    E_CLD_BAS_PE_STOVE,
    E_CLD_BAS_PE_MICROWAVE,
    E_CLD_BAS_PE_TOASTER,
    E_CLD_BAS_PE_VACUMM,
    E_CLD_BAS_PE_APPLIANCE,
    E_CLD_BAS_PE_FRONT_DOOR,
    E_CLD_BAS_PE_BACK_DOOR,
    E_CLD_BAS_PE_FRIDGE_DOOR,
    E_CLD_BAS_PE_MEDICATION_CABINET_DOOR,
    E_CLD_BAS_PE_WARDROBE_DOOR,
    E_CLD_BAS_PE_FRONT_CUPBOARD_DOOR,
    E_CLD_BAS_PE_OTHER_DOOR,
    E_CLD_BAS_PE_WAITING_ROOM,
    E_CLD_BAS_PE_TRIAGE_ROOM,
    E_CLD_BAS_PE_DOCTOR_OFFICE,
    E_CLD_BAS_PE_PATIENT_PRIVATE_ROOM,
    E_CLD_BAS_PE_CONSULTATION_ROOM,
    E_CLD_BAS_PE_NURSE_STATION,
    E_CLD_BAS_PE_WARD,
    E_CLD_BAS_PE_COORIDOR,
    E_CLD_BAS_PE_OPERATING_THREATER,
    E_CLD_BAS_PE_DENTAL_SURGERY_ROOM,
    E_CLD_BAS_PE_MEDICAL_IMAGING_ROOM,
    E_CLD_BAS_PE_DECONTAMINATION_ROOM,
    E_CLD_BAS_PE_UNKNOWN_ENVIRONMENT
} teCLD_BAS_PhysicalEnvironment;

/* Basic Cluster */
typedef struct
{
#ifdef BASIC_SERVER
    zuint8                      u8ZCLVersion;

#ifdef CLD_BAS_ATTR_APPLICATION_VERSION
    zuint8                      u8ApplicationVersion;
#endif

#ifdef CLD_BAS_ATTR_STACK_VERSION
    zuint8                      u8StackVersion;
#endif

#ifdef CLD_BAS_ATTR_HARDWARE_VERSION
    zuint8                      u8HardwareVersion;
#endif

#ifdef CLD_BAS_ATTR_MANUFACTURER_NAME
    tsZCL_CharacterString       sManufacturerName;
    uint8                       au8ManufacturerName[32];
#endif

#ifdef CLD_BAS_ATTR_MODEL_IDENTIFIER
    tsZCL_CharacterString       sModelIdentifier;
    uint8                       au8ModelIdentifier[32];
#endif

#ifdef CLD_BAS_ATTR_DATE_CODE
    tsZCL_CharacterString       sDateCode;
    uint8                       au8DateCode[16];
#endif

#ifdef CLD_BAS_ATTR_APPLICATION_LEGRAND
    zuint32                      u32PrivateLegrand;
#endif

    zenum8                      ePowerSource;

#ifdef CLD_BAS_ATTR_GENERIC_DEVICE_CLASS    
    zenum8                      eGenericDeviceClass;
#endif

#ifdef CLD_BAS_ATTR_GENERIC_DEVICE_TYPE    
    zenum8                      eGenericDeviceType;
#endif
 
#ifdef CLD_BAS_ATTR_PRODUCT_CODE    
    tsZCL_OctetString           sProductCode;
    uint8                       au8ProductCode[CLD_BASIC_MAX_NUMBER_OF_BYTES_PRODUCT_CODE];
#endif

#ifdef CLD_BAS_ATTR_PRODUCT_URL   
    tsZCL_CharacterString       sProductURL;
    uint8                       au8ProductURL[CLD_BASIC_MAX_NUMBER_OF_BYTES_PRODUCT_URL];
#endif
    
#ifdef CLD_BAS_ATTR_LOCATION_DESCRIPTION
    tsZCL_CharacterString       sLocationDescription;
    uint8                       au8LocationDescription[16];
#endif

#ifdef CLD_BAS_ATTR_PHYSICAL_ENVIRONMENT
    zenum8                      u8PhysicalEnvironment;
#endif

#ifdef CLD_BAS_ATTR_DEVICE_ENABLED
    zbool                       bDeviceEnabled;
#endif

#ifdef CLD_BAS_ATTR_ALARM_MASK
    zbmap8                      u8AlarmMask;
#endif

#ifdef CLD_BAS_ATTR_DISABLE_LOCAL_CONFIG
    zbmap8                      u8DisableLocalConfig;
#endif

#ifdef CLD_BAS_ATTR_SW_BUILD_ID
    tsZCL_CharacterString       sSWBuildID;
    uint8                       au8SWBuildID[16];
#endif

#ifdef CLD_BAS_ATTR_ID_XIAOMI_FF01
    tsZCL_CharacterString		sDataXiaomiConfig;
    uint8                       au8DataXiaomiConfig[32];
#endif

#ifdef CLD_BAS_ATTR_ID_XIAOMI_FF02
    tsZCL_CharacterString       sDataXiaomiConfig2;
    uint8                     au8DataXiaomiConfig2[32];
#endif

#endif


    zuint16                      u16ClusterRevision;
} tsCLD_Basic;


#ifdef CLD_SM_SUPPORT_MIRROR

/* Basic Cluster */
typedef struct
{
    zuint8                      u8ZCLVersion;

#ifdef CLD_BAS_MIRROR_ATTR_APPLICATION_VERSION
    zuint8                      u8ApplicationVersion;
#endif

#ifdef CLD_BAS_MIRROR_ATTR_STACK_VERSION
    zuint8                      u8StackVersion;
#endif

#ifdef CLD_BAS_MIRROR_ATTR_HARDWARE_VERSION
    zuint8                      u8HardwareVersion;
#endif

#ifdef CLD_BAS_MIRROR_ATTR_MANUFACTURER_NAME
    tsZCL_CharacterString       sManufacturerName;
    uint8                       au8ManufacturerName[32];
#endif

#ifdef CLD_BAS_MIRROR_ATTR_MODEL_IDENTIFIER
    tsZCL_CharacterString       sModelIdentifier;
    uint8                       au8ModelIdentifier[32];
#endif

#ifdef CLD_BAS_MIRROR_ATTR_DATE_CODE
    tsZCL_CharacterString       sDateCode;
    uint8                       au8DateCode[16];
#endif

    zenum8                      ePowerSource;
   
#ifdef CLD_BAS_MIRROR_ATTR_LOCATION_DESCRIPTION
    tsZCL_CharacterString       sLocationDescription;
    uint8                       au8LocationDescription[16];
#endif

#ifdef CLD_BAS_MIRROR_ATTR_PHYSICAL_ENVIRONMENT
    zenum8                      u8PhysicalEnvironment;
#endif

#ifdef CLD_BAS_MIRROR_ATTR_DEVICE_ENABLED
    zbool                       bDeviceEnabled;
#endif

#ifdef CLD_BAS_MIRROR_ATTR_ALARM_MASK
    zbmap8                      u8AlarmMask;
#endif

#ifdef CLD_BAS_MIRROR_ATTR_DISABLE_LOCAL_CONFIG
    zbmap8                      u8DisableLocalConfig;
#endif

    zuint16                      u16ClusterRevision;
    
} tsCLD_BasicMirror;


#endif


/* Definition of Basic Callback Event Structure */
typedef struct
{
    uint8                           u8CommandId;
} tsCLD_BasicCallBackMessage;


#ifdef CLD_SM_SUPPORT_MIRROR
tsZCL_ClusterDefinition sCLD_BasicMirror[CLD_SM_NUMBER_OF_MIRRORS];
#endif
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_BasicCreateBasic(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits);

PUBLIC teZCL_Status eCLD_BasicCommandResetToFactoryDefaultsSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber);

#ifdef CLD_SM_SUPPORT_MIRROR
teZCL_Status eSE_RegisterMirroredBasicCluster(uint8 u8MirrorNum,
        tsZCL_ClusterInstance              *psClusterInstance,
        void                  *pvEndPointSharedStructPtr);
#endif

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_Basic;
extern const tsZCL_AttributeDefinition asCLD_BasicClusterAttributeDefinitions[];
extern uint8 au8BasicClusterAttributeControlBits[];
    
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* BASIC_H */
