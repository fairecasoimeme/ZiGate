/*****************************************************************************
 *
 * MODULE:
 *
 * COMPONENT:          PlugControl.h
 *
 * AUTHOR:
 *
 * DESCRIPTION:
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
 * Copyright NXP B.V. 2013. All rights reserved
 *
 ****************************************************************************/

#ifndef PLUG_CONTROL_H
#define PLUG_CONTROL_H

#if defined __cplusplus
extern "C" {
#endif

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "Basic.h"
#include "Identify.h"
#include "PowerConfiguration.h"
#include "Alarms.h"
#include "Groups.h"
#include "Scenes.h"
#include "OnOff.h"
#include "SimpleMetering.h"
#include "Thermostat.h"
#include "ApplianceStatistics.h"
#include "ElectricalMeasurement.h"
#ifdef CLD_OTA
#include "OTA.h"
#endif
#include "Time.h"
#ifdef CLD_POLL_CONTROL
#include "PollControl.h"
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

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

/* Optional Clusters Common to All HA Server Devices */
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

#if (defined CLD_SCENES) && (defined SCENES_SERVER)
    tsZCL_ClusterInstance sScenesServer;
#endif

#if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
    tsZCL_ClusterInstance sGroupsServer;
#endif

    /* Optional Clusters Common to All HA Client Devices */
#if (defined CLD_SCENES) && (defined SCENES_CLIENT)
    tsZCL_ClusterInstance sScenesClient;
#endif

#if (defined CLD_GROUPS) && (defined GROUPS_CLIENT)
    tsZCL_ClusterInstance sGroupsClient;
#endif

/* Mandatory Clusters supported by Plug Control Client Device */
#if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
    tsZCL_ClusterInstance sIdentifyClient;
#endif

#if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
    tsZCL_ClusterInstance sOnOffClient;
#endif

#if (defined CLD_SIMPLE_METERING) && (defined SM_CLIENT)
    tsZCL_ClusterInstance sSimpleMeteringClient;
#endif

#if (defined CLD_ELECTRICAL_MEASUREMENT) && (defined ELECTRICAL_MEASUREMENT_CLIENT)
    tsZCL_ClusterInstance sElectricalMeasurementClient;
#endif

} tsHA_PlugControlDeviceClusterInstances;


typedef struct
{
    tsZCL_EndPointDefinition sEndPoint;

    tsHA_PlugControlDeviceClusterInstances sClusterInstance;

#if (defined CLD_BASIC) && (defined BASIC_SERVER)
    tsCLD_Basic sBasicServerCluster;
#endif

#if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
    tsCLD_Identify sIdentifyServerCluster;
    tsCLD_IdentifyCustomDataStructure sIdentifyServerCustomDataStructure;
#endif

/* Optional Clusters Common to All HA Server Devices */
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

#if (defined CLD_SCENES) && (defined SCENES_SERVER)
    /* Scenes Cluster - Server */
    tsCLD_Scenes sScenesServerCluster;
    tsCLD_ScenesCustomDataStructure sScenesServerCustomDataStructure;
#endif

#if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
    /* Groups Cluster - Server */
    tsCLD_Groups sGroupsServerCluster;
    tsCLD_GroupsCustomDataStructure sGroupsServerCustomDataStructure;
#endif

    /* Optional Clusters Common to All HA Client Devices */
#if (defined CLD_SCENES) && (defined SCENES_CLIENT)
    /* Scenes Cluster - Client */
    tsCLD_ScenesCustomDataStructure sScenesClientCustomDataStructure;
#endif

#if (defined CLD_GROUPS) && (defined GROUPS_CLIENT)
    /* Groups Cluster - Client */
    tsCLD_GroupsCustomDataStructure sGroupsClientCustomDataStructure;
#endif

	/* Mandatory Clusters supported by Plug Control Client Device */
#if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
    tsCLD_Identify sIdentifyClientCluster;
    tsCLD_IdentifyCustomDataStructure sIdentifyClientCustomDataStructure;
#endif

#if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
    tsCLD_OnOffClient sOnOffClientCluster;
#endif

#if (defined CLD_SIMPLE_METERING) && (defined SM_CLIENT)
    tsCLD_SimpleMetering sSimpleMeteringClientCluster;
    tsSM_CustomStruct sSimpleMeteringClientCustomDataStructure;
#endif

#if (defined CLD_ELECTRICAL_MEASUREMENT) && (defined ELECTRICAL_MEASUREMENT_CLIENT)
    tsCLD_ElectricalMeasurement sCLD_ElectricalMeasurementClient;
#endif

} tsHA_PlugControlDevice;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eHA_RegisterPlugControlEndPoint(uint8 u8EndPointIdentifier,
                                                       tfpZCL_ZCLCallBackFunction cbCallBack,
                                                       tsHA_PlugControlDevice *psDeviceInfo);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* PLUG_CONTROL_H */
