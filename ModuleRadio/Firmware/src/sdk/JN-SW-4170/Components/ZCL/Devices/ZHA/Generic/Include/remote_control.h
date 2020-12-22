/*****************************************************************************
 *
 * MODULE:             Remote Control
 *
 * COMPONENT:          remote_control.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for ZigBee Remote Control profile functions
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

#ifndef CONFIGURATION_TOOL_H
#define CONFIGURATION_TOOL_H

#if defined __cplusplus
extern "C" {
#endif

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "Basic.h"
#include "Identify.h"
#include "PowerConfiguration.h"
#include "DeviceTemperatureConfiguration.h"
#include "Alarms.h"
#include "OnOff.h"
#include "LevelControl.h"
#include "Groups.h"
#include "Scenes.h"
#include "ColourControl.h"
#include "OOSC.h"
#include "TemperatureMeasurement.h"
#include "IlluminanceLevelSensing.h"
#include "IlluminanceMeasurement.h"
#ifdef CLD_OTA
#include "OTA.h"
#endif
#include "Time.h"
#ifdef CLD_POLL_CONTROL
    #include "PollControl.h"
#endif
#ifdef CLD_DOOR_LOCK
    #include "DoorLock.h"
#endif
#ifdef CLD_WINDOWCOVERING
    #include "WindowCovering.h"
#endif
#ifdef CLD_THERMOSTAT
    #include "Thermostat.h"
#endif
#ifdef CLD_ELECTRICAL_MEASUREMENT
	#include "ElectricalMeasurement.h"
#endif
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define GENERIC_REMOTE_CONTROL_DEVICE_ID                                0x0006
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Holds cluster instances */
typedef struct
{
    /* All HA devices have 2 mandatory clusters - Basic(server) and Identify(server) */
#if (defined CLD_BASIC) && (defined BASIC_SERVER)
    tsZCL_ClusterInstance sBasicServer;
#endif

#if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
    tsZCL_ClusterInstance sIdentifyServer;
#endif

    /* Optional server clusters */
#if (defined CLD_POWER_CONFIGURATION) && (defined POWER_CONFIGURATION_SERVER)
    tsZCL_ClusterInstance sPowerConfigurationServer;
#endif

#if (defined CLD_DEVICE_TEMPERATURE_CONFIGURATION) && (defined DEVICE_TEMPERATURE_CONFIGURATION_SERVER)
    tsZCL_ClusterInstance sDeviceTemperatureConfigurationServer;
#endif

#if (defined CLD_ALARMS) && (defined ALARMS_SERVER)
    tsZCL_ClusterInstance sAlarmsServer;
#endif

#if (defined CLD_POLL_CONTROL) && (defined POLL_CONTROL_SERVER)
    tsZCL_ClusterInstance sPollControlServer;
#endif

    /* Mandatory client clusters */
#if (defined CLD_BASIC) && (defined BASIC_CLIENT)
    tsZCL_ClusterInstance sBasicClient;
#endif

#if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
    tsZCL_ClusterInstance sIdentifyClient;
#endif

#if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
    tsZCL_ClusterInstance sOnOffClient;
#endif

#if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_CLIENT)
    tsZCL_ClusterInstance sLevelControlClient;
#endif

#if (defined CLD_GROUPS) && (defined GROUPS_CLIENT)
    tsZCL_ClusterInstance sGroupsClient;
#endif

#if (defined CLD_SCENES) && (defined SCENES_CLIENT)
    tsZCL_ClusterInstance sScenesClient;
#endif

    /* Optional client clusters */
#if (defined CLD_POLL_CONTROL) && (defined POLL_CONTROL_CLIENT)
    tsZCL_ClusterInstance sPollControlClient;
#endif

#if (defined CLD_COLOUR_CONTROL) && (defined COLOUR_CONTROL_CLIENT)
    tsZCL_ClusterInstance sColourControlClient;
#endif

#if (defined CLD_OOSC) && (defined OOSC_CLIENT)
    tsZCL_ClusterInstance sOOSCClient;
#endif

#if (defined CLD_TEMPERATURE_MEASUREMENT) && (defined TEMPERATURE_MEASUREMENT_CLIENT)
    tsZCL_ClusterInstance sTemperatureMeasurementClient;
#endif

#if (defined CLD_ILLUMINANCE_LEVEL_SENSING) && (defined ILLUMINANCE_LEVEL_SENSING_CLIENT)
    tsZCL_ClusterInstance sIlluminanceLevelSensingClient;
#endif

#if (defined CLD_ILLUMINANCE_MEASUREMENT) && (defined ILLUMINANCE_MEASUREMENT_CLIENT)
    tsZCL_ClusterInstance sIlluminanceMeasurementClient;
#endif

#if (defined CLD_DOOR_LOCK) && (defined DOOR_LOCK_CLIENT)
    tsZCL_ClusterInstance sDoorLockClient;
#endif

#if (defined CLD_WINDOWCOVERING) && (defined WINDOWCOVERING_CLIENT)
    tsZCL_ClusterInstance sWindowCoveringClient;
#endif

#if (defined CLD_THERMOSTAT) && (defined THERMOSTAT_CLIENT)
    tsZCL_ClusterInstance sThermostatClient;
#endif

#ifdef CLD_OTA
    #ifdef OTA_CLIENT
    /* Add  cluster instance for the OTA cluster */
    tsZCL_ClusterInstance sOTAClient;
    #endif
    #ifdef OTA_SERVER
    /* Add  server instance for the OTA cluster */
    tsZCL_ClusterInstance sOTAServer;
    #endif
#endif
#if (defined CLD_TIME && defined TIME_CLIENT)
    tsZCL_ClusterInstance sTimeClient;
#endif

#if (defined CLD_ELECTRICAL_MEASUREMENT && defined ELECTRICAL_MEASUREMENT_SERVER)
    tsZCL_ClusterInstance sElectricalMeasurementServer;
#endif
} tsHA_RemoteControlDeviceClusterInstances __attribute__ ((aligned(4)));


/* Holds everything required to create an instance of a remote control */
typedef struct
{
    tsZCL_EndPointDefinition sEndPoint;

    /* Cluster instances */
    tsHA_RemoteControlDeviceClusterInstances sClusterInstance;

    /* Mandatory server clusters */
#if (defined CLD_BASIC) && (defined BASIC_SERVER)
    /* Basic Cluster - Server */
    tsCLD_Basic sBasicServerCluster;
#endif

#if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
    /* Identify Cluster - Server */
    tsCLD_Identify sIdentifyServerCluster;
    tsCLD_IdentifyCustomDataStructure sIdentifyServerCustomDataStructure;
#endif

    /* Optional server clusters */
#if (defined CLD_POWER_CONFIGURATION) && (defined POWER_CONFIGURATION_SERVER)
    /* Power Configuration Cluster - Server */
    tsCLD_PowerConfiguration sPowerConfigServerCluster;
#endif

#if (defined CLD_DEVICE_TEMPERATURE_CONFIGURATION) && (defined DEVICE_TEMPERATURE_CONFIGURATION_SERVER)
    /* Device Temperature Configuration Cluster - Server */
    tsCLD_DeviceTemperatureConfiguration sDeviceTemperatureConfigurationServerCluster;
#endif

#if (defined CLD_ALARMS) && (defined ALARMS_SERVER)
    /* Alarms Cluster - Server */
    tsCLD_Alarms sAlarmsServerCluster;
    tsCLD_AlarmsCustomDataStructure sAlarmsServerCustomDataStructure;
#endif

#if (defined CLD_POLL_CONTROL) && (defined POLL_CONTROL_SERVER)
    tsCLD_PollControl sPollControlServerCluster;
    tsCLD_PollControlCustomDataStructure sPollControlServerCustomDataStructure;
#endif

    /* Mandatory client clusters */
#if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
    tsCLD_OnOffClient sOnOffClientCluster;
#endif

#if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
    /* Identify Cluster - Client */
    tsCLD_Identify sIdentifyClientCluster;
    tsCLD_IdentifyCustomDataStructure sIdentifyClientCustomDataStructure;
#endif

#if (defined CLD_BASIC) && (defined BASIC_CLIENT)
    /* Basic Cluster - Client */
    tsCLD_Basic sBasicClientCluster;
#endif

#if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_CLIENT)
    /* Level Control Cluster - Client */
    tsCLD_LevelControlClient sLevelControlClientCluster;
    tsCLD_LevelControlCustomDataStructure sLevelControlClientCustomDataStructure;
#endif

#if (defined CLD_GROUPS) && (defined GROUPS_CLIENT)
    /* Groups Cluster - Client */
    tsCLD_Groups sGroupsClientCluster;
    tsCLD_GroupsCustomDataStructure sGroupsClientCustomDataStructure;
#endif

#if (defined CLD_SCENES) && (defined SCENES_CLIENT)
    /* Scenes Cluster - Client */
    tsCLD_Scenes sScenesClientCluster;
    tsCLD_ScenesCustomDataStructure sScenesClientCustomDataStructure;
#endif

#if (defined CLD_POLL_CONTROL) && (defined POLL_CONTROL_CLIENT)
    tsCLD_PollControl sPollControlClientCluster;
    tsCLD_PollControlCustomDataStructure sPollControlClientCustomDataStructure;
#endif

#if (defined CLD_COLOUR_CONTROL) && (defined COLOUR_CONTROL_CLIENT)
    /* Colour Control Cluster - Client */
    tsCLD_ColourControl sColourControlClientCluster;
    tsCLD_ColourControlCustomDataStructure sColourControlClientCustomDataStructure;
#endif

#if (defined CLD_THERMOSTAT) && (defined THERMOSTAT_CLIENT)
    tsCLD_Thermostat sThermostatClientCluster;
    tsCLD_ThermostatCustomDataStructure sThermostatClientCustomDataStructure;
#endif

#if (defined CLD_OOSC) && (defined OOSC_CLIENT)
    /* On/Off Switch Configuration Cluster - Client */
    tsCLD_OOSC sOOSCClientCluster;
#endif

#if (defined CLD_ILLUMINANCE_MEASUREMENT) && (defined ILLUMINANCE_MEASUREMENT_CLIENT)
    /* Illuminance Measurement Cluster - Client */
    tsCLD_IlluminanceMeasurement sIlluminanceMeasurementClientCluster;
#endif

#if (defined CLD_ILLUMINANCE_LEVEL_SENSING) && (defined ILLUMINANCE_LEVEL_SENSING_CLIENT)
    tsCLD_IlluminanceLevelSensing sIlluminanceLevelSensingClientCluster;
#endif

#if (defined CLD_TEMPERATURE_MEASUREMENT) && (defined TEMPERATURE_MEASUREMENT_CLIENT)
    tsCLD_TemperatureMeasurement sTemperatureMeasurementClientCluster;
#endif

#ifdef CLD_OTA
    /* OTA cluster */
    #ifdef OTA_CLIENT
        tsCLD_AS_Ota sCLD_OTA;
        tsOTA_Common sCLD_OTA_CustomDataStruct;
    #endif

    #ifdef OTA_SERVER
        tsCLD_AS_Ota sCLD_ServerOTA;
        tsOTA_Common sCLD_OTA_ServerCustomDataStruct;
    #endif
#endif
#if (defined CLD_ELECTRICAL_MEASUREMENT && defined ELECTRICAL_MEASUREMENT_SERVER)
        tsCLD_ElectricalMeasurement sCLD_ElectricalMeasurement;
#endif

#if (defined CLD_TIME) && (defined TIME_CLIENT)
    tsCLD_Time sTimeClientCluster;
#endif

#if (defined CLD_DOOR_LOCK) && (defined DOOR_LOCK_CLIENT)
    /* door lock Cluster - Client */
    tsCLD_DoorLock sDoorLockClientCluster;
#endif

#if (defined CLD_WINDOWCOVERING) && (defined WINDOWCOVERING_CLIENT)
    /* Widnow Covering Cluster - Client */
    tsCLD_WindowCovering sWindowCoveringClientCluster;
#endif

} tsHA_RemoteControlDevice;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eHA_RegisterRemoteControlEndPoint(uint8 u8EndPointIdentifier,
                                              tfpZCL_ZCLCallBackFunction cbCallBack,
                                              tsHA_RemoteControlDevice *psDeviceInfo);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* CONFIGURATION_TOOL_H */
