/*****************************************************************************
 *
 * MODULE:             Thermostat Cluster
 *
 * COMPONENT:          Thermostat.h
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        Header for Thermostat Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/HVAC/Include/Thermostat.h $
 *
 * $Revision: 73686 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-10-27 06:57:54 +0100 (Tue, 27 Oct 2015) $
 *
 * $Id: Thermostat.h 73686 2015-10-27 05:57:54Z nxp57621 $
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

#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "zcl_customcommand.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Cluster ID's */

#define HVAC_CLUSTER_ID_THERMOSTAT                                         0x0201

#ifndef CLD_THERMOSTAT_MIN_COOLING_SETPOINT
    #define CLD_THERMOSTAT_MIN_COOLING_SETPOINT                            0x954d
#endif
#ifndef CLD_THERMOSTAT_MAX_COOLING_SETPOINT
    #define CLD_THERMOSTAT_MAX_COOLING_SETPOINT                            0x7fff
#endif
#ifndef CLD_THERMOSTAT_MIN_HEATING_SETPOINT
    #define CLD_THERMOSTAT_MIN_HEATING_SETPOINT                            0x954d
#endif
#ifndef CLD_THERMOSTAT_MAX_HEATING_SETPOINT
    #define CLD_THERMOSTAT_MAX_HEATING_SETPOINT                            0x7fff
#endif

#ifndef CLD_THERMOSTAT_CLUSTER_REVISION
    #define CLD_THERMOSTAT_CLUSTER_REVISION                     1
#endif  

/****************************************************************************/
/*             Thermostat Cluster - Optional Attributes                     */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the cluster.                                               */
/****************************************************************************/

/* Enable the optional Outdoor Temperature attribute */
//#define CLD_THERMOSTAT_ATTR_OUTDOOR_TEMPERATURE

/* Enable the optional Occupancy attribute */
//#define CLD_THERMOSTAT_ATTR_OCCUPANCY

/* Enable the optional Minimum Heat Setpoint Limit attribute */
//#define CLD_THERMOSTAT_ATTR_ABS_MIN_HEAT_SETPOINT_LIMIT

/* Enable the optional Maximum Heat Setpoint Limit attribute */
//#define CLD_THERMOSTAT_ATTR_ABS_MAX_HEAT_SETPOINT_LIMIT

/* Enable the optional Minimum Cool Setpoint Limit attribute */
//#define CLD_THERMOSTAT_ATTR_ABS_MIN_COOL_SETPOINT_LIMIT

/* Enable the optional Maximum Cool Setpoint Limit attribute */
//#define CLD_THERMOSTAT_ATTR_ABS_MAX_COOL_SETPOINT_LIMIT

/* Enable the optional PI Cooling Demand attribute */
//#define CLD_THERMOSTAT_ATTR_PI_COOLING_DEMAND

/* Enable the optional PI Heating Demand attribute */
//#define CLD_THERMOSTAT_ATTR_PI_HEATING_DEMAND

/* Enable the optional Local Temperature Calibration attribute */
//#define CLD_THERMOSTAT_ATTR_LOCAL_TEMPERATURE_CALIBRATION

/* Enable the optional Unoccupied Cooling Setpoint attribute */
//#define CLD_THERMOSTAT_ATTR_UNOCCUPIED_COOLING_SETPOINT

/* Enable the optional Unoccupied Heating Setpoint attribute */
//#define CLD_THERMOSTAT_ATTR_UNOCCUPIED_HEATING_SETPOINT

/* Enable the optional Minimum Heat Setpoint Limit attribute */
//#define CLD_THERMOSTAT_ATTR_MIN_HEAT_SETPOINT_LIMIT

/* Enable the optional Maximum Heat Setpoint Limit attribute */
//#define CLD_THERMOSTAT_ATTR_MAX_HEAT_SETPOINT_LIMIT

/* Enable the optional Minimum Cool Setpoint Limit attribute */
//#define CLD_THERMOSTAT_ATTR_MIN_COOL_SETPOINT_LIMIT

/* Enable the optional Maximum Cool Setpoint Limit attribute */
//#define CLD_THERMOSTAT_ATTR_MAX_COOL_SETPOINT_LIMIT

/* Enable the optional Minimum Setpoint Dead Band attribute */
//#define CLD_THERMOSTAT_ATTR_MIN_SETPOINT_DEAD_BAND

/* Enable the optional Remote Sensing attribute */
//#define CLD_THERMOSTAT_ATTR_REMOTE_SENSING

/* Enable the optional Alarm Mask attribute */
//#define CLD_THERMOSTAT_ATTR_ALARM_MASK

/* Enable the optional Attribute Status Reporting */
//#define CLD_THERMOSTAT_ATTR_ATTRIBUTE_REPORTING_STATUS
/* End of optional attributes */


/* Occupancy */
#define CLD_THERMOSTAT_OCCUPANCY_OCCUPIED           (1 << 0)

/* Remote Sensing */
#define CLD_THERMOSTAT_LOCAL_TEMP_SENSED_REMOTELY   (1 << 0)
#define CLD_THERMOSTAT_OUTDOOR_TEMP_SENSED_REMOTELY (1 << 1)
#define CLD_THERMOSTAT_OCCUPANCY_SENSED_REMOTELY    (1 << 2)

/* Alarm Mask*/
#define CLD_THERMOSTAT_ALARM_INIT_FAIL              (1 << 0)
#define CLD_THERMOSTAT_ALARM_HARDWARE_FAIL          (1 << 1)
#define CLD_THERMOSTAT_ALARM_SELF_CAL_FAIL          (1 << 2)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* Thermostat Information attribute set attribute ID's (6.3.2.2.1) */
    E_CLD_THERMOSTAT_ATTR_ID_LOCAL_TEMPERATURE                  = 0x0000, /* Mandatory */
    E_CLD_THERMOSTAT_ATTR_ID_OUTDOOR_TEMPERATURE,
    E_CLD_THERMOSTAT_ATTR_ID_OCCUPANCY,
    E_CLD_THERMOSTAT_ATTR_ID_ABS_MIN_HEAT_SETPOINT_LIMIT,
    E_CLD_THERMOSTAT_ATTR_ID_ABS_MAX_HEAT_SETPOINT_LIMIT,
    E_CLD_THERMOSTAT_ATTR_ID_ABS_MIN_COOL_SETPOINT_LIMIT,
    E_CLD_THERMOSTAT_ATTR_ID_ABS_MAX_COOL_SETPOINT_LIMIT,
    E_CLD_THERMOSTAT_ATTR_ID_PI_COOLING_DEMAND,
    E_CLD_THERMOSTAT_ATTR_ID_PI_HEATING_DEMAND,

    /* Thermostat settings attribute set attribute ID's (6.3.2.2.2) */
    E_CLD_THERMOSTAT_ATTR_ID_LOCAL_TEMPERATURE_CALIBRATION  = 0x0010,
    E_CLD_THERMOSTAT_ATTR_ID_OCCUPIED_COOLING_SETPOINT,                 /* Mandatory */
    E_CLD_THERMOSTAT_ATTR_ID_OCCUPIED_HEATING_SETPOINT,                 /* Mandatory */
    E_CLD_THERMOSTAT_ATTR_ID_UNOCCUPIED_COOLING_SETPOINT,
    E_CLD_THERMOSTAT_ATTR_ID_UNOCCUPIED_HEATING_SETPOINT,
    E_CLD_THERMOSTAT_ATTR_ID_MIN_HEAT_SETPOINT_LIMIT,
    E_CLD_THERMOSTAT_ATTR_ID_MAX_HEAT_SETPOINT_LIMIT,
    E_CLD_THERMOSTAT_ATTR_ID_MIN_COOL_SETPOINT_LIMIT,
    E_CLD_THERMOSTAT_ATTR_ID_MAX_COOL_SETPOINT_LIMIT,
    E_CLD_THERMOSTAT_ATTR_ID_MIN_SETPOINT_DEAD_BAND,
    E_CLD_THERMOSTAT_ATTR_ID_REMOTE_SENSING,
    E_CLD_THERMOSTAT_ATTR_ID_CONTROL_SEQUENCE_OF_OPERATION,             /* Mandatory */
    E_CLD_THERMOSTAT_ATTR_ID_SYSTEM_MODE,                               /* Mandatory */
    E_CLD_THERMOSTAT_ATTR_ID_ALARM_MASK,
} teCLD_Thermostat_AttributeID;

/* Command codes */
typedef enum 
{
    E_CLD_THERMOSTAT_CMD_SETPOINT_RAISE_LOWER                     = 0x00,    /* Mandatory */
} teCLD_Thermostat_Command;

/* Control Sequence of Operation */
typedef enum 
{
    E_CLD_THERMOSTAT_CSOO_COOLING_ONLY                      = 0x00,
    E_CLD_THERMOSTAT_CSOO_COOLING_WITH_REHEAT,
    E_CLD_THERMOSTAT_CSOO_HEATING_ONLY,
    E_CLD_THERMOSTAT_CSOO_HEATING_WITH_REHEAT,
    E_CLD_THERMOSTAT_CSOO_COOLING_AND_HEATING_4_PIPES,
    E_CLD_THERMOSTAT_CSOO_COOLING_AND_HEATING_4_PIPES_WITH_REHEAT,
}teCLD_Thermostat_ControlSequenceOfOperation;

/* System Mode */
typedef enum 
{
    E_CLD_THERMOSTAT_SM_OFF                                 = 0x00,
    E_CLD_THERMOSTAT_SM_AUTO,
    E_CLD_THERMOSTAT_SM_COOL                                = 0x03,
    E_CLD_THERMOSTAT_SM_HEAT,
    E_CLD_THERMOSTAT_SM_EMERGENCY_HEATING,
    E_CLD_THERMOSTAT_SM_PRECOOLING,
    E_CLD_THERMOSTAT_SM_FAN_ONLY
}teCLD_Thermostat_SystemMode;

/* Setpoint Raise/Lower command modes */
typedef enum
{
    E_CLD_THERMOSTAT_SRLM_HEAT                             = 0x00,
    E_CLD_THERMOSTAT_SRLM_COOL,
    E_CLD_THERMOSTAT_SRLM_BOTH
}teCLD_Thermostat_SetpointRaiseOrLowerMode;

/* Thermostat Cluster */
typedef struct
{
#ifdef THERMOSTAT_SERVER    
    zint16                  i16LocalTemperature;

#ifdef CLD_THERMOSTAT_ATTR_OUTDOOR_TEMPERATURE
    zint16                  i16OutdoorTemperature;
#endif

#ifdef CLD_THERMOSTAT_ATTR_OCCUPANCY
    zbmap8                  u8Occupancy;
#endif

#ifdef CLD_THERMOSTAT_ATTR_ABS_MIN_HEAT_SETPOINT_LIMIT
    zint16                  i16AbsMinHeatSetpointLimit;
#endif

#ifdef CLD_THERMOSTAT_ATTR_ABS_MAX_HEAT_SETPOINT_LIMIT
    zint16                  i16AbsMaxHeatSetpointLimit;
#endif

#ifdef CLD_THERMOSTAT_ATTR_ABS_MIN_COOL_SETPOINT_LIMIT
    zint16                  i16AbsMinCoolSetpointLimit;
#endif

#ifdef CLD_THERMOSTAT_ATTR_ABS_MAX_COOL_SETPOINT_LIMIT
    zint16                  i16AbsMaxCoolSetpointLimit;
#endif

#ifdef CLD_THERMOSTAT_ATTR_PI_COOLING_DEMAND
    zuint8                  u8PICoolingDemand;
#endif

#ifdef CLD_THERMOSTAT_ATTR_PI_HEATING_DEMAND
    zuint8                  u8PIHeatingDemand;
#endif

    /* Thermostat settings attribute set attribute ID's (6.3.2.2.2) */
#ifdef CLD_THERMOSTAT_ATTR_LOCAL_TEMPERATURE_CALIBRATION
    zint8                   i8LocalTemperatureCalibration;
#endif
    zint16                  i16OccupiedCoolingSetpoint;

    zint16                  i16OccupiedHeatingSetpoint;
#ifdef CLD_THERMOSTAT_ATTR_UNOCCUPIED_COOLING_SETPOINT
    zint16                  i16UnoccupiedCoolingSetpoint;
#endif

#ifdef CLD_THERMOSTAT_ATTR_UNOCCUPIED_HEATING_SETPOINT
    zint16                  i16UnoccupiedHeatingSetpoint;
#endif

#ifdef CLD_THERMOSTAT_ATTR_MIN_HEAT_SETPOINT_LIMIT
    zint16                  i16MinHeatSetpointLimit;
#endif

#ifdef CLD_THERMOSTAT_ATTR_MAX_HEAT_SETPOINT_LIMIT
    zint16                  i16MaxHeatSetpointLimit;
#endif

#ifdef CLD_THERMOSTAT_ATTR_MIN_COOL_SETPOINT_LIMIT
    zint16                  i16MinCoolSetpointLimit;
#endif

#ifdef CLD_THERMOSTAT_ATTR_MAX_COOL_SETPOINT_LIMIT
    zint16                  i16MaxCoolSetpointLimit;
#endif

#ifdef CLD_THERMOSTAT_ATTR_MIN_SETPOINT_DEAD_BAND
    zint8                   i8MinSetpointDeadBand;
#endif

#ifdef CLD_THERMOSTAT_ATTR_REMOTE_SENSING
    zbmap8                  u8RemoteSensing;
#endif
    zenum8                  eControlSequenceOfOperation;
    
    zenum8                  eSystemMode;
#ifdef CLD_THERMOSTAT_ATTR_ALARM_MASK
    zbmap8                  u8AlarmMask;
#endif

#ifdef CLD_THERMOSTAT_ATTR_ATTRIBUTE_REPORTING_STATUS
    zenum8                  u8AttributeReportingStatus;
#endif

#endif
    zuint16                 u16ClusterRevision;
} tsCLD_Thermostat;

/* Definition of Command Thermostat Setpoint Raise or lower Structure */
typedef struct
{
    zenum8                 eMode;
    zint8                  i8Amount;
}tsCLD_Thermostat_SetpointRaiseOrLowerPayload;


/* Definition of Thermostat Call back Event Structure */
typedef struct
{
    uint8                                               u8CommandId;
    union
    {
        tsCLD_Thermostat_SetpointRaiseOrLowerPayload    *psSetpointRaiseOrLowerPayload;
    } uMessage;
} tsCLD_ThermostatCallBackMessage;

/* Custom data structure */
typedef struct
{
    tsZCL_ReceiveEventAddress         sReceiveEventAddress;
    tsZCL_CallBackEvent               sCustomCallBackEvent;
    tsCLD_ThermostatCallBackMessage   sCallBackMessage;
} tsCLD_ThermostatCustomDataStructure;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_ThermostatCreateThermostat(
                tsZCL_ClusterInstance                   *psClusterInstance,
                bool_t                                  bIsServer,
                tsZCL_ClusterDefinition                 *psClusterDefinition,
                void                                    *pvEndPointSharedStructPtr,
                uint8                                   *pu8AttributeControlBits,
                tsCLD_ThermostatCustomDataStructure     *psCustomDataStructure);

#ifdef THERMOSTAT_SERVER
PUBLIC teZCL_Status eCLD_ThermostatSetAttribute(
                uint8                                   u8SourceEndPointId,
                uint8                                   u8AttributeId,
                int16                                   i16AttributeValue); 

PUBLIC teZCL_Status eCLD_ThermostatStartReportingLocalTemperature(
                uint8                                   u8SourceEndPointId,
                uint8                                   u8DstEndPointId,
                uint64                                  u64DstAddr,
                uint16                                  u16MinReportInterval,
                uint16                                  u16MaxReportInterval,
                int16                                   i16ReportableChange);
#endif       

#ifdef THERMOSTAT_CLIENT
PUBLIC teZCL_Status eCLD_ThermostatCommandSetpointRaiseOrLowerSend(
                    uint8                                           u8SourceEndPointId,
                    uint8                                           u8DestinationEndPointId,
                    tsZCL_Address                                   *psDestinationAddress,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_Thermostat_SetpointRaiseOrLowerPayload    *psPayload);
#endif       
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern const tsZCL_AttributeDefinition asCLD_ThermostatClusterAttributeDefinitions[];
extern tsZCL_ClusterDefinition sCLD_Thermostat;
extern uint8 au8ThermostatAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* THERMOSTAT_H */
