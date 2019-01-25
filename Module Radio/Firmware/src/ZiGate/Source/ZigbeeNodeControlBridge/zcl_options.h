/*****************************************************************************
 *
 * MODULE:             ZigbeeNodeControlBridge
 *
 * COMPONENT:          zcl_options.h
 *
 * AUTHOR:             Faisal Bhaiyat
 *
 * DESCRIPTION:        Options Header for ZigBee Cluster Library functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Zigbee%20Protocol%20Stack/ZPS/Trunk/ZigbeeNodeControlBridge/Source/ZigbeeNodeControlBridge/zcl_options.h $
 *
 * $Revision: 54776 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2013-06-20 11:50:33 +0100 (Thu, 20 Jun 2013) $
 *
 * $Id: zcl_options.h 54776 2013-06-20 10:50:33Z nxp29741 $
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5164,
 * JN5161, JN5148, JN5142, JN5139].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
 ***************************************************************************/

#ifndef ZCL_OPTIONS_H
#define ZCL_OPTIONS_H

#include <jendefs.h>

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define ZCL_ALLOW_WILD_CARD_PROFILE
#define CLD_BAS_CMD_RESET_TO_FACTORY_DEFAULTS

/* Set this True to disable non error default responses from clusters */
#define ZCL_DISABLE_DEFAULT_RESPONSES                      (TRUE)
#define ZCL_DISABLE_APS_ACK                                (FALSE)
#define OTA_ACKS_ON                                        (TRUE)
#define OTA_CLIENT_DISABLE_DEFAULT_RESPONSE                (FALSE)

// Total number of group addresses required by all sub-device endpoints on the device
#define GROUPS_REQUIRED                                     ( 16 )
#define CLD_GROUPS_MAX_NUMBER_OF_GROUPS                     ( 5  )
/* Sets the number of endpoints that will be created by the ZCL library */
#define ZCL_NUMBER_OF_ENDPOINTS                             ( 20 )
#define ZCL_NUMBER_DEVICES                                  ( 3 )

#define ZCL_MANUFACTURER_CODE                               ( 0x1037 )

/* For GP proxy cluster*/
#define ZCL_NUMBER_OF_APPLICATION_TIMERS                    ( 1 )

#define TL_LEGACY_PROFILE_ID                                ( 0xc05e )
#define TL_LEGACY_DEVICE_ID                                 ( 0x0840 )
#define TL_LEGACY_VERSION_ID                                ( 2 )
#define ZCL_ATTRIBUTE_DISCOVERY_SERVER_SUPPORTED
#define ZCL_ATTRIBUTE_DISCOVERY_CLIENT_SUPPORTED

#define ZCL_ATTRIBUTE_DISCOVERY_EXTENDED_SERVER_SUPPORTED
#define ZCL_ATTRIBUTE_DISCOVERY_EXTENDED_CLIENT_SUPPORTED

#define ZCL_COMMAND_DISCOVERY_SUPPORTED
#define ZCL_COMMAND_RECEIVED_DISCOVERY_SERVER_SUPPORTED
#define ZCL_COMMAND_RECEIVED_DISCOVERY_CLIENT_SUPPORTED
#define ZCL_COMMAND_GENERATED_DISCOVERY_SERVER_SUPPORTED
#define ZCL_COMMAND_GENERATED_DISCOVERY_CLIENT_SUPPORTED

/* Clusters used by this application */
#define CLD_BASIC
#define BASIC_SERVER
#define BASIC_CLIENT

#ifdef FULL_FUNC_DEVICE
#define CLD_ZLL_COMMISSION
#define ZLL_COMMISSION_CLIENT
#define ZLL_COMMISSION_SERVER
#define CLD_ZLL_UTILITY
#define ZLL_UTILITY_SERVER
#define ZLL_UTILITY_CLIENT
#endif


#define CLD_IDENTIFY
#define CLD_IDENTIFY_CMD_TRIGGER_EFFECT
#define IDENTIFY_CLIENT
#define IDENTIFY_SERVER
#define CLD_IDENTIFY_TICKS_PER_SECOND   10
#define CLD_IDENTIFY_SUPPORT_ZLL_ENHANCED_COMMANDS

#define CLD_GROUPS
#define GROUPS_CLIENT
#define GROUPS_SERVER

#define CLD_ONOFF
#define CLD_ONOFF_CMD_OFF_WITH_EFFECT
#define CLD_ONOFF_CMD_ON_WITH_TIMED_OFF
#define ONOFF_CLIENT
#define ONOFF_SERVER

//#define ONOFF_SERVER
#define CLD_ONOFF_SUPPORT_ZLL_ENHANCED_COMMANDS

#define CLD_LEVEL_CONTROL
#define LEVEL_CONTROL_CLIENT
#define LEVEL_CONTROL_SERVER
#define CLD_LEVELCONTROL_TICKS_PER_SECOND                   10

#define CLD_SCENES
#define SCENES_CLIENT

#define CLD_COLOUR_CONTROL
#define COLOUR_CONTROL_CLIENT

#define CLD_IASZONE
#define IASZONE_CLIENT
//#define IASZONE_SERVER

//RAJOUT FRED
	//XIAOMI CUBE
#define CLD_MULTISTATE_INPUT_BASIC
#define MULTISTATE_INPUT_BASIC_SERVER
#define MULTISTATE_INPUT_BASIC_CLIENT

#define CLD_ANALOG_INPUT_BASIC
#define ANALOG_INPUT_BASIC_SERVER

#define CLD_POWER_CONFIGURATION
#define POWER_CONFIGURATION_SERVER

#define CLD_BINARY_INPUT_BASIC
#define BINARY_INPUT_BASIC_SERVER

#define CLD_TIME
#define TIME_SERVER

#define CLD_ELECTRICAL_MEASUREMENT
#define ELECTRICAL_MEASUREMENT_SERVER
#define CLD_ANALOG_INPUT_BASIC
#define CLD_ANALOG_INPUT_BASIC_SERVER
#define CLD_ANALOG_INPUT_BASIC_CLIENT
#define CLD_SIMPLE_METERING
#define SM_CLIENT

#define CLD_DIAGNOSTICS
#define DIAGNOSTICS_CLIENT
#define CLD_DIAGNOSTICS_ATTR_ID_AVERAGE_MAC_RETRY_PER_APS_MESSAGE_SENT
#define CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_LQI
#define CLD_DIAGNOSTICS_ATTR_ID_LAST_MESSAGE_RSSI

#define CLD_OTA
#define OTA_SERVER
#define OTA_MAX_BLOCK_SIZE                                    64
#define OTA_TIME_INTERVAL_BETWEEN_RETRIES                     5
#define OTA_COPY_MAC_ADDRESS
#define OTA_MAX_IMAGES_PER_ENDPOINT                           1
#define OTA_CLD_ATTR_CURRENT_FILE_VERSION
#define OTA_MAX_CO_PROCESSOR_IMAGES                           1

#define NUM_ENDPOINT_RECORDS                                  10
#define NUM_GROUP_RECORDS                                     10

/* Enable reports to be configured on remote servers and responses to be received */
#define ZCL_CONFIGURE_ATTRIBUTE_REPORTING_CLIENT_SUPPORTED
#define ZCL_ATTRIBUTE_REPORTING_CLIENT_SUPPORTED
#define ZCL_READ_ATTRIBUTE_REPORTING_CONFIGURATION_CLIENT_SUPPORTED

/****************************************************************************/
/*             Basic Cluster - Optional Attributes                          */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the basic cluster.                                         */
/****************************************************************************/

#define ZCL_ATTRIBUTE_READ_SERVER_SUPPORTED
#define ZCL_ATTRIBUTE_READ_CLIENT_SUPPORTED
#define ZCL_ATTRIBUTE_WRITE_SERVER_SUPPORTED
#define ZCL_ATTRIBUTE_WRITE_CLIENT_SUPPORTED


//#define   CLD_BAS_ATTR_LOCATION_DESCRIPTION
//#define   CLD_BAS_ATTR_PHYSICAL_ENVIRONMENT
//#define   CLD_BAS_ATTR_DEVICE_ENBLED
//#define   CLD_BAS_ATTR_ALARM_MASK

#define CLD_BAS_ATTR_APPLICATION_VERSION
#define CLD_BAS_ATTR_STACK_VERSION
#define CLD_BAS_ATTR_HARDWARE_VERSION
#define CLD_BAS_ATTR_MANUFACTURER_NAME
#define CLD_BAS_ATTR_MODEL_IDENTIFIER
#define CLD_BAS_ATTR_DATE_CODE
#define CLD_BAS_ATTR_SW_BUILD_ID
#define CLD_BAS_ATTR_CONFIG_MODEL_IDENTIFIER

//#define CLD_BAS_ATTR_ID_XIAOMI_FF01
//#define CLD_BAS_ATTR_ID_XIAOMI_FF02
#define CLD_BAS_ATTR_APPLICATION_LEGRAND


#define CLD_BAS_APP_VERSION             (1)
#define CLD_BAS_STACK_VERSION           (1)
#define CLD_BAS_HARDWARE_VERSION        (1)
#define CLD_BAS_MANUF_NAME_SIZE         (3)
#define CLD_BAS_MODEL_ID_SIZE           (17)
#define CLD_BAS_DATE_SIZE               (8)
#define CLD_BAS_POWER_SOURCE            E_CLD_BAS_PS_BATTERY
#define CLD_BAS_SW_BUILD_SIZE           (9)
#define CLD_BAS_CONFIG_MODEL_ID_SIZE    CLD_BAS_MODEL_ID_SIZE

#ifdef  CLD_GREENPOWER
    #define GP_IEEE_ADDR_SUPPORT
    #define GREENPOWER_END_POINT_ID                 2
    #define GP_NUMBER_OF_TRANSLATION_TABLE_ENTRIES  5
    #define GP_NUMBER_OF_PROXY_SINK_TABLE_ENTRIES       5
    #define CLD_GP_ATTR_ZGPS_COMMISSIONING_WINDOW
    #define CLD_GP_ATTR_ZGP_SHARED_SECURITY_KEY_TYPE
    #define CLD_GP_ATTR_ZGP_SHARED_SECURITY_KEY
    #define CLD_GP_ATTR_ZGP_LINK_KEY
    /* security level */
    #define GP_SECURITY_LEVEL E_GP_ENC_FULL_FC_FULL_MIC
    /* Possible values are  E_GP_NO_KEY, E_GP_ZIGBEE_NWK_KEY, E_GP_ZGPD_GROUP_KEY,
        E_GP_NWK_KEY_DERIVED_ZGPD_GROUP_KEY, E_GP_OUT_OF_THE_BOX_ZGPD_KEY, E_GP_DERIVED_INDIVIDUAL_ZGPD_KEY*/
    #define GP_KEYTPE              E_GP_ZGPD_GROUP_KEY
    #define GP_SHARED_KEY  { 0xC0 , 0xC1 , 0xC2 , 0xC3 , 0xC4 , 0xC5 , 0xC6 , 0xC7 , 0xC8 , 0xC9 , 0xCa , 0xCb , 0xCc , 0xCd , 0xCe , 0xCf}
#undef ZCL_NUMBER_OF_ENDPOINTS
#define ZCL_NUMBER_OF_ENDPOINTS                             2
#undef CLD_GROUPS_MAX_NUMBER_OF_GROUPS
#define CLD_GROUPS_MAX_NUMBER_OF_GROUPS                     4
#define GP_MAX_TRANS_ZB_CMD_PAYLOAD_LENGTH                   2
#endif


/****************************************************************************/
/*             Colour Control Cluster - Optional Attributes                 */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the time cluster.                                          */
/****************************************************************************/

/*
 * Colour attributes, Optional in ZCL spec but Mandatory for ZLL
 */
/* Colour information attribute set attribute ID's (5.2.2.2.1) */

#define CLD_COLOURCONTROL_ATTR_CURRENT_HUE
#define CLD_COLOURCONTROL_ATTR_CURRENT_SATURATION
#define CLD_COLOURCONTROL_ATTR_REMAINING_TIME
#define CLD_COLOURCONTROL_ATTR_COLOUR_MODE
#define CLD_COLOURCONTROL_ATTR_COLOUR_TEMPERATURE


/* Defined Primaries Information attribute attribute ID's set (5.2.2.2.2) */
#define CLD_COLOURCONTROL_ATTR_NUMBER_OF_PRIMARIES  3

/* Enable Primary (n) X, Y and Intensity attributes */
#define CLD_COLOURCONTROL_ATTR_PRIMARY_1
#define CLD_COLOURCONTROL_ATTR_PRIMARY_2
#define CLD_COLOURCONTROL_ATTR_PRIMARY_3
#define CLD_COLOURCONTROL_ATTR_PRIMARY_4
#define CLD_COLOURCONTROL_ATTR_PRIMARY_5
#define CLD_COLOURCONTROL_ATTR_PRIMARY_6

/* ZLL enhanced attributes */
#define CLD_COLOURCONTROL_ATTR_ENHANCED_CURRENT_HUE
#define CLD_COLOURCONTROL_ATTR_ENHANCED_COLOUR_MODE
#define CLD_COLOURCONTROL_ATTR_COLOUR_LOOP_ACTIVE
#define CLD_COLOURCONTROL_ATTR_COLOUR_LOOP_DIRECTION
#define CLD_COLOURCONTROL_ATTR_COLOUR_LOOP_TIME
#define CLD_COLOURCONTROL_ATTR_COLOUR_LOOP_START_ENHANCED_HUE
#define CLD_COLOURCONTROL_ATTR_COLOUR_LOOP_STORED_ENHANCED_HUE

#define CLD_COLOURCONTROL_ATTR_COLOUR_CAPABILITIES
#define CLD_COLOURCONTROL_ATTR_COLOUR_TEMPERATURE_PHY_MIN
#define CLD_COLOURCONTROL_ATTR_COLOUR_TEMPERATURE_PHY_MAX
#define CLD_COLOURCONTROL_ATTR_COLOUR_TEMPERATURE_MIRED
/* Max & Min Limits for colour temperature */
#define CLD_COLOURCONTROL_COLOUR_TEMPERATURE_PHY_MIN    0x0001
#define CLD_COLOURCONTROL_COLOUR_TEMPERATURE_PHY_MAX    0xfef8

#define CLD_COLOURCONTROL_RED_X     (0.68)
#define CLD_COLOURCONTROL_RED_Y     (0.31)
#define CLD_COLOURCONTROL_GREEN_X   (0.11)
#define CLD_COLOURCONTROL_GREEN_Y   (0.82)
#define CLD_COLOURCONTROL_BLUE_X    (0.13)
#define CLD_COLOURCONTROL_BLUE_Y    (0.04)
#define CLD_COLOURCONTROL_WHITE_X   (0.33)
#define CLD_COLOURCONTROL_WHITE_Y   (0.33)


#define CLD_COLOURCONTROL_PRIMARY_1_X           CLD_COLOURCONTROL_RED_X
#define CLD_COLOURCONTROL_PRIMARY_1_Y           CLD_COLOURCONTROL_RED_Y
#define CLD_COLOURCONTROL_PRIMARY_1_INTENSITY   (254 / 3)

#define CLD_COLOURCONTROL_PRIMARY_2_X           CLD_COLOURCONTROL_GREEN_X
#define CLD_COLOURCONTROL_PRIMARY_2_Y           CLD_COLOURCONTROL_GREEN_Y
#define CLD_COLOURCONTROL_PRIMARY_2_INTENSITY   (254 / 3)

#define CLD_COLOURCONTROL_PRIMARY_3_X           CLD_COLOURCONTROL_BLUE_X
#define CLD_COLOURCONTROL_PRIMARY_3_Y           CLD_COLOURCONTROL_BLUE_Y
#define CLD_COLOURCONTROL_PRIMARY_3_INTENSITY   (254 / 3)

#define CLD_COLOURCONTROL_PRIMARY_4_X           (0)
#define CLD_COLOURCONTROL_PRIMARY_4_Y           (0)
#define CLD_COLOURCONTROL_PRIMARY_4_INTENSITY   (0xff)

#define CLD_COLOURCONTROL_PRIMARY_5_X           (0)
#define CLD_COLOURCONTROL_PRIMARY_5_Y           (0)
#define CLD_COLOURCONTROL_PRIMARY_5_INTENSITY   (0xff)

#define CLD_COLOURCONTROL_PRIMARY_6_X           (0)
#define CLD_COLOURCONTROL_PRIMARY_6_Y           (0)
#define CLD_COLOURCONTROL_PRIMARY_6_INTENSITY   (0xff)


#define  CLD_COLOUR_CONTROL_SUPPORT_ZLL_ENHANCED_COMMANDS
#define  CLD_COLOUR_CONTROL_SUPPORT_ZLL_COLOUR_TEMPERATURE_COMMANDS

/* ZLL attribute in on off cluster */
//#define CLD_ONOFF_ATTR_GLOBAL_SCENE_CONTROL
#define CLD_ONOFF_ATTR_ON_TIME
#define CLD_ONOFF_ATTR_OFF_WAIT_TIME

#define ZLL_DISABLE_DEFAULT_RESPONSES FALSE
/* WARNING -- Need to setup bugger apdus and fragmentation to enable ASC */
//#define CLD_ASC_LOG
#define CLD_DOOR_LOCK
#define DOOR_LOCK_CLIENT
#define CLD_THERMOSTAT
#define THERMOSTAT_CLIENT
#define CLD_TEMPERATURE_MEASUREMENT
#define TEMPERATURE_MEASUREMENT_CLIENT
#define CLD_RELATIVE_HUMIDITY_MEASUREMENT
#define RELATIVE_HUMIDITY_MEASUREMENT_CLIENT
#define CLD_PRESSURE_MEASUREMENT
#define PRESSURE_MEASUREMENT_CLIENT
#define CLD_ILLUMINANCE_MEASUREMENT
#define ILLUMINANCE_MEASUREMENT_CLIENT

#define CLD_WINDOWCOVERING
#define WINDOWCOVERING_CLIENT


#define CLD_PRIVATE_PHILIPS
#define PRIVATE_PHILIPS_SERVER

//#define CLD_APPLIANCE_STATISTICS
//#define APPLIANCE_STATISTICS_SERVER
//#define APPLIANCE_STATISTICS_CLIENT
#define CLD_SM_ATTR_INSTANTANEOUS_DEMAND
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void* psGetDeviceTable(void);
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* ZCL_OPTIONS_H */
