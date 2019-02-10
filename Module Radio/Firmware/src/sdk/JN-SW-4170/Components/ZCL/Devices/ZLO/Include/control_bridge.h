/*****************************************************************************
 *
 * MODULE:             Zigbee Lighting and Occupancy
 *
 * COMPONENT:          control_bridge.h
 *
 * AUTHOR:             fbhai
 *
 * DESCRIPTION:        Header for ZLO control bridge
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Devices/ZLO/Include/control_bridge.h $
 *
 * $Revision: 93829 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2018-05-25 11:58:19 +0100 (Fri, 25 May 2018) $
 *
 * $Id: control_bridge.h 93829 2018-05-25 10:58:19Z nxp29741 $
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

#ifndef CONTROL_BRIDGE_H
#define CONTROL_BRIDGE_H

#if defined __cplusplus
extern "C" {
#endif

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "zll_commission.h"
#include "zll_utility.h"
#include "Basic.h"
#include "PowerConfiguration.h"
#include "Identify.h"
#include "OnOff.h"
#include "LevelControl.h"
#include "ColourControl.h"
#include "Groups.h"
#include "Scenes.h"
#include "IlluminanceLevelSensing.h"
#include "Thermostat.h"
#include "ThermostatUIConfig.h"
#include "TemperatureMeasurement.h"
#include "PressureMeasurement.h"
#include "RelativeHumidityMeasurement.h"
#include "IlluminanceMeasurement.h"
#include "OccupancySensing.h"
#ifdef CLD_IASZONE
#include "IASZone.h"
#endif
#ifdef CLD_DOOR_LOCK
#include "DoorLock.h"
#endif
#ifdef CLD_WINDOWCOVERING
#include "WindowCovering.h"
#endif
#ifdef CLD_SIMPLE_METERING
#include "SimpleMetering.h"
#endif
#ifdef CLD_OTA
#include "OTA.h"
#endif
#include "ApplianceStatistics.h"
#ifdef CLD_DIAGNOSTICS
#include "Diagnostics.h"
#endif
#ifdef CLD_MULTISTATE_INPUT_BASIC
#include "MultistateInputBasic.h"
#endif
#ifdef CLD_ANALOG_INPUT_BASIC
#include "AnalogInputBasic.h"
#endif
#ifdef CLD_MULTISTATE_INPUT_BASIC
#include "BinaryInputBasic.h"
#endif
#ifdef CLD_TIME
#include "Time.h"
#endif
#ifdef CLD_ELECTRICAL_MEASUREMENT
#include "ElectricalMeasurement.h"
#endif
#ifdef CLD_PRIVATE_PHILIPS
#include "PrivatePhilips.h"
#endif


#ifdef CLD_GREENPOWER
#include "GreenPower.h"

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
    /*
     * All ZLO devices have following mandatory clusters
     */

    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        tsZCL_ClusterInstance sBasicServer;
    #endif


   #if (defined CLD_POWER_CONFIGURATION) && (defined POWER_CONFIGURATION_SERVER)
	   tsZCL_ClusterInstance sPowerConfigurationServer;
   #endif


    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
        tsZCL_ClusterInstance sIdentifyServer;
    #endif

	#if (defined CLD_BINARY_INPUT_BASIC) && (defined BINARY_INPUT_BASIC_SERVER)
		tsZCL_ClusterInstance sBinaryInputBasicServer;
	#endif

    /* Recommended Optional Server Cluster*/
    #if (defined CLD_ZLL_COMMISSION) && (defined ZLL_COMMISSION_SERVER)
        tsZCL_ClusterInstance sZllCommissionServer;
    #endif

    #if (defined CLD_OTA) && (defined OTA_SERVER)
        /* Add  server instance for the OTA cluster */
        tsZCL_ClusterInstance sOTAServer;    
    #endif

	#if (defined CLD_TIME) && (defined TIME_SERVER)
       /* Add  server instance for the OTA cluster */
       tsZCL_ClusterInstance sTimeServer;
    #endif

	#if (defined CLD_ELECTRICAL_MEASUREMENT) && (defined ELECTRICAL_MEASUREMENT_SERVER)
       tsZCL_ClusterInstance sElectricalMeasurementServer;
    #endif

    /*
     * Control Bridge Device has 7 other mandatory clusters for the client
     */
   
    #if (defined CLD_BASIC) && (defined BASIC_CLIENT)
        tsZCL_ClusterInstance sBasicClient;
    #endif
    
    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
        tsZCL_ClusterInstance sIdentifyClient;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_CLIENT)
        tsZCL_ClusterInstance sGroupsClient;
    #endif

    #if (defined CLD_SCENES) && (defined SCENES_CLIENT)
        tsZCL_ClusterInstance sScenesClient;
    #endif
    
    #if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
        tsZCL_ClusterInstance sOnOffClient;
    #endif
    
    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_CLIENT)
        tsZCL_ClusterInstance sLevelControlClient;
    #endif

	#if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_SERVER)
       tsZCL_ClusterInstance sLevelControlServer;
   #endif

    #if (defined CLD_COLOUR_CONTROL) && (defined COLOUR_CONTROL_CLIENT)
        tsZCL_ClusterInstance sColourControlClient;
    #endif

    /* Recommend Optional client clusters */
    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        tsZCL_ClusterInstance sOTAClient;
    #endif
    
    #if (defined CLD_ILLUMINANCE_MEASUREMENT) && (defined ILLUMINANCE_MEASUREMENT_CLIENT)
        tsZCL_ClusterInstance sIlluminanceMeasurementClient;
    #endif
    
    #if (defined CLD_ILLUMINANCE_LEVEL_SENSING) && (defined ILLUMINANCE_LEVEL_SENSING_CLIENT)
        tsZCL_ClusterInstance sIlluminanceLevelSensingClient;
    #endif

    #if (defined CLD_OCCUPANCY_SENSING) && (defined OCCUPANCY_SENSING_CLIENT)
        tsZCL_ClusterInstance sOccupancySensingClient;
    #endif

    #if (defined CLD_ZLL_COMMISSION) && (defined ZLL_COMMISSION_CLIENT)
        tsZCL_ClusterInstance sZllCommissionClient;
    #endif
    
    /* Extra server cluster */
    #if (defined CLD_ONOFF) && (defined ONOFF_SERVER)
        tsZCL_ClusterInstance sOnOffServer;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
        tsZCL_ClusterInstance sGroupsServer;
    #endif

    #if (defined CLD_APPLIANCE_STATISTICS) && (defined APPLIANCE_STATISTICS_SERVER)
        tsZCL_ClusterInstance sASCServer;
    #endif    
    
    /* Extra client cluster */
    #if (defined CLD_IASZONE) && (defined IASZONE_CLIENT)
        tsZCL_ClusterInstance sIASZoneClient;
    #endif

	#if (defined CLD_IASZONE) && (defined IASZONE_SERVER)
       tsZCL_ClusterInstance sIASZoneServer;
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
    
    #if (defined CLD_SIMPLE_METERING) && (defined SM_CLIENT)
        tsZCL_ClusterInstance sMeteringClient;
    #endif
    
    #if (defined CLD_TEMPERATURE_MEASUREMENT) && (defined TEMPERATURE_MEASUREMENT_CLIENT)
        tsZCL_ClusterInstance sTemperatureMeasurementClient;
    #endif

    #if (defined CLD_RELATIVE_HUMIDITY_MEASUREMENT) && (defined RELATIVE_HUMIDITY_MEASUREMENT_CLIENT)
        tsZCL_ClusterInstance sRelativeHumidityMeasurementClient;
    #endif
#if (defined CLD_PRESSURE_MEASUREMENT) && (defined PRESSURE_MEASUREMENT_CLIENT)
       tsZCL_ClusterInstance sCLD_PressureMeasurementClient;
   #endif

    #if (defined CLD_DIAGNOSTICS) && (defined DIAGNOSTICS_CLIENT)
        tsZCL_ClusterInstance sDiagnosticClient;
    #endif

    #if (defined CLD_APPLIANCE_STATISTICS) && (defined APPLIANCE_STATISTICS_CLIENT)
        tsZCL_ClusterInstance sASCClient;
    #endif

	//RAJOUT FRED
	#if (defined CLD_MULTISTATE_INPUT_BASIC) && (defined MULTISTATE_INPUT_BASIC_SERVER)
	   tsZCL_ClusterInstance sMultistateServer;
	#endif

	#if (defined CLD_MULTISTATE_INPUT_BASIC) && (defined MULTISTATE_INPUT_BASIC_CLIENT)
	   tsZCL_ClusterInstance sMultistateClient;
	#endif

	#if (defined CLD_ANALOG_INPUT_BASIC) && (defined CLD_ANALOG_INPUT_BASIC_CLIENT)
	   tsZCL_ClusterInstance sAnalogInputCLient;
	#endif

	#if (defined CLD_PRIVATE_PHILIPS) && (defined PRIVATE_PHILIPS_SERVER)
       tsZCL_ClusterInstance sPrivatePhilips;
    #endif


} tsZLO_ControlBridgeDeviceClusterInstances __attribute__ ((aligned(4)));




/* Holds everything required to create an instance of a Control Bridge */
typedef struct
{
    tsZCL_EndPointDefinition sEndPoint;

    /* Cluster instances */
    tsZLO_ControlBridgeDeviceClusterInstances sClusterInstance;

    /* Mandatory server cluster */
    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        /* Basic Cluster - Server */
        tsCLD_Basic sBasicServerCluster;
    #endif


	#if (defined CLD_POWER_CONFIGURATION) && (defined POWER_CONFIGURATION_SERVER)
		/* Power Configuration Cluster - Server */
		tsCLD_PowerConfiguration sPowerConfigServerCluster;
	#endif

    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
        /* Identify Cluster - Server */
        tsCLD_Identify sIdentifyServerCluster;
        tsCLD_IdentifyCustomDataStructure sIdentifyServerCustomDataStructure;
    #endif

	#if (defined CLD_BINARY_INPUT_BASIC) && (defined BINARY_INPUT_BASIC_SERVER)
		/* Binary Input Basic Cluster - Server */
		tsCLD_BinaryInputBasic sBinaryInputBasicServerCluster;
	#endif

    /* Recommended Optional Server Cluster */
    
    #if (defined CLD_OTA) && (defined OTA_SERVER)
    /* OTA cluster */
        tsCLD_AS_Ota sCLD_ServerOTA;    
        tsOTA_Common sCLD_OTA_ServerCustomDataStruct;
    #endif
    
    #if (defined CLD_TIME) && (defined TIME_SERVER)
    /* Time cluster */
        tsCLD_Time sTimeServerCluster;

    #endif

	#if (defined CLD_ELECTRICAL_MEASUREMENT) && (defined ELECTRICAL_MEASUREMENT_SERVER)

		tsCLD_ElectricalMeasurement sCLD_ElectricalMeasurement;

	#endif

    #if (defined CLD_ZLL_COMMISSION) && (defined ZLL_COMMISSION_SERVER)
        tsCLD_ZllCommission                         sZllCommissionServerCluster;
        tsCLD_ZllCommissionCustomDataStructure      sZllCommissionServerCustomDataStructure;
    #endif
    
    /*
     * Mandatory client clusters
     */
     
    #if (defined CLD_BASIC) && (defined BASIC_CLIENT)
        /* Basic Cluster - Client */
        tsCLD_Basic sBasicClientCluster;
    #endif
    
    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
        /* Identify Cluster - Client */
        tsCLD_Identify sIdentifyClientCluster;
        tsCLD_IdentifyCustomDataStructure sIdentifyClientCustomDataStructure;
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
    
    #if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
        /* On/Off Cluster - Client */
        tsCLD_OnOffClient sOnOffClientCluster;
    #endif

    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_CLIENT)
        /* Level Control Cluster - Client */
        tsCLD_LevelControlClient sLevelControlClientCluster;
        tsCLD_LevelControlCustomDataStructure sLevelControlClientCustomDataStructure;
    #endif

    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_SERVER)
        /* Level Control Cluster - Server */
        tsCLD_LevelControl sLevelControlServerCluster;
        tsCLD_LevelControlCustomDataStructure sLevelControlServerCustomDataStructure;
    #endif

    #if (defined CLD_COLOUR_CONTROL) && (defined COLOUR_CONTROL_CLIENT)
        /* Colour Control Cluster - Client */
        tsCLD_ColourControl sColourControlClientCluster;    
        tsCLD_ColourControlCustomDataStructure sColourControlClientCustomDataStructure;
    #endif

        /* Recommended Optional client clusters */
        
    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        /* OTA cluster */
        tsCLD_AS_Ota sCLD_OTA;    
        tsOTA_Common sCLD_OTA_CustomDataStruct;
    #endif
    
    #if (defined CLD_ILLUMINANCE_MEASUREMENT) && (defined ILLUMINANCE_MEASUREMENT_CLIENT)
        /* Illuminance Measurement Cluster - Client */
        tsCLD_IlluminanceMeasurement sIlluminanceMeasurementClientCluster;
    #endif

    #if (defined CLD_ILLUMINANCE_LEVEL_SENSING) && (defined ILLUMINANCE_LEVEL_SENSING_CLIENT)
        tsCLD_IlluminanceLevelSensing sIlluminanceLevelSensingClientCluster;
    #endif

    #if (defined CLD_OCCUPANCY_SENSING) && (defined OCCUPANCY_SENSING_CLIENT)
        /* Occupancy Sensing Cluster - Client */
        tsCLD_OccupancySensing sOccupancySensingClientCluster;
    #endif

    #if (defined CLD_ZLL_COMMISSION) && (defined ZLL_COMMISSION_CLIENT)
        tsCLD_ZllCommission                         sZllCommissionClientCluster;
        tsCLD_ZllCommissionCustomDataStructure      sZllCommissionClientCustomDataStructure;
    #endif

    /*Optional Server cluster */
    #if (defined CLD_ONOFF) && (defined ONOFF_SERVER)
        /* On/Off Cluster - Client */
        tsCLD_OnOff sOnOffServerCluster;
        tsCLD_OnOffCustomDataStructure sOnOffServerCustomDataStructure;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
        /* Groups Cluster - Server */
        tsCLD_Groups sGroupsServerCluster;
        tsCLD_GroupsCustomDataStructure sGroupsServerCustomDataStructure;
    #endif
    
    #if (defined CLD_APPLIANCE_STATISTICS) && (defined APPLIANCE_STATISTICS_SERVER)
        tsZCL_ClusterInstance sASCServerCluster;
        tsCLD_ApplianceStatisticsCustomDataStructure sASCServerCustomDataStructure;
    #endif
    
    /* Optional client cluster */
    #if (defined CLD_IASZONE) && (defined IASZONE_CLIENT)
        /* IAS Zone - Client */
        tsCLD_IASZone sIASZoneClientCluster;    
        tsCLD_IASZone_CustomDataStructure sIASZoneClientCustomDataStructure;
    #endif

    #if (defined CLD_IASZONE) && (defined IASZONE_SERVER)
       /* IAS Zone - Server */
       tsCLD_IASZone sIASZoneServerCluster;
       tsCLD_IASZone_CustomDataStructure sIASZoneServerCustomDataStructure;
   #endif

    #if (defined CLD_DOOR_LOCK) && (defined DOOR_LOCK_CLIENT)
        /* door lock Cluster - Client */
        tsCLD_DoorLock sDoorLockClientCluster;
    #endif

    #if (defined CLD_WINDOWCOVERING) && (defined WINDOWCOVERING_CLIENT)
        /* Window Covering Cluster - Client */
        tsCLD_WindowCovering sWindowCoveringClientCluster;
    #endif
    
    #if (defined CLD_SIMPLE_METERING) && (defined SM_CLIENT)
        /* Simple Metering Cluster - Client */
        tsSM_CustomStruct sMeteringClientCustomDataStructure;
    #endif

    #if (defined CLD_THERMOSTAT) && (defined THERMOSTAT_CLIENT)
        tsCLD_Thermostat sThermostatClientCluster;        
        tsCLD_ThermostatCustomDataStructure sThermostatClientCustomDataStructure;
    #endif
    
    #if (defined CLD_TEMPERATURE_MEASUREMENT) && (defined TEMPERATURE_MEASUREMENT_CLIENT)
        tsCLD_TemperatureMeasurement sTemperatureMeasurementClientCluster;
    #endif

    #if (defined CLD_RELATIVE_HUMIDITY_MEASUREMENT) && (defined RELATIVE_HUMIDITY_MEASUREMENT_CLIENT)
        tsCLD_RelativeHumidityMeasurement sRelativeHumidityMeasurementClientCluster;
    #endif

	#if (defined CLD_PRESSURE_MEASUREMENT) && (defined PRESSURE_MEASUREMENT_CLIENT)
       tsCLD_PressureMeasurement sPressureMeasurementClientCluster;
   #endif

    #if (defined CLD_APPLIANCE_STATISTICS) && (defined APPLIANCE_STATISTICS_CLIENT)
        /* Basic Cluster - Client */
        tsCLD_ApplianceStatistics sASCClientCluster;
        tsCLD_ApplianceStatisticsCustomDataStructure sASCClientCustomDataStructure;
    #endif

    #if (defined CLD_DIAGNOSTICS) && (defined DIAGNOSTICS_CLIENT)
        tsZCL_ClusterInstance sDiagnosticClientCluster;
    #endif

	//RAJOUT FRED
	#if (defined CLD_MULTISTATE_INPUT_BASIC) && (defined MULTISTATE_INPUT_BASIC_SERVER)
		/* Multistate Cluster - Server */
		tsCLD_MultistateInputBasic sMultistateServerCluster;

	#endif

	#if (defined CLD_MULTISTATE_INPUT_BASIC) && (defined MULTISTATE_INPUT_BASIC_CLIENT)
		/* Multistate Cluster - Client */
		tsCLD_MultistateInputBasic sMultistateClientCluster;

	#endif
	#if (defined CLD_ANALOG_INPUT_BASIC) && (defined CLD_ANALOG_INPUT_BASIC_CLIENT)
		/* Multistate Cluster - Client */
		tsCLD_MultistateInputBasic sAnalogInputClientCluster;

	#endif

    #if (defined CLD_PRIVATE_PHILIPS) && (defined PRIVATE_PHILIPS_SERVER)
        tsCLD_PrivatePhilips sPrivatePhilipsCluster;
    #endif

} tsZLO_ControlBridgeDevice;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eZLO_RegisterControlBridgeEndPoint( uint8                         u8EndPointIdentifier,
                                                        tfpZCL_ZCLCallBackFunction    cbCallBack,
                                                        tsZLO_ControlBridgeDevice*    psDeviceInfo );

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* CONTROL_BRIDGE_H */
