/*****************************************************************************
 *
 * MODULE:             Lighting and occupancy
 *
 * COMPONENT:
 *
 * AUTHOR:
 *
 * DESCRIPTION:        Zigbee Control bridge functions.
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Devices/ZLO/Source/control_bridge.c $
 *
 * $Revision: 93829 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2018-05-25 11:58:19 +0100 (Fri, 25 May 2018) $
 *
 * $Id: control_bridge.c 93829 2018-05-25 10:58:19Z nxp29741 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5164,
 * JN5161, JN5148, JN5142, JN5139]. 
 * You, and any third parties must reproduce the copyright and warranty notice 
 * and any other legend of ownership on each  copy or partial copy of the software. 
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
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "zps_apl.h"
#include "zcl_heap.h"
#include "control_bridge.h"
#include "Log.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: eZLO_RegisterControlBridgeEndPoint
 *
 * DESCRIPTION:
 * Registers a control bridge device with the ZCL layer
 *
 * PARAMETERS:  Name                            Usage
 *              u8EndPointIdentifier            Endpoint being registered
 *              cbCallBack                      Pointer to endpoint callback
 *              psDeviceInfo                    Pointer to struct containing
 *                                              data for endpoint
 *
 * RETURNS:
 * teZCL_Status
 *
 ****************************************************************************/

PUBLIC teZCL_Status eZLO_RegisterControlBridgeEndPoint ( uint8                         u8EndPointIdentifier,
                                                         tfpZCL_ZCLCallBackFunction    cbCallBack,
                                                         tsZLO_ControlBridgeDevice     *psDeviceInfo )
{
    /* Fill in end point details */
    psDeviceInfo->sEndPoint.u8EndPointNumber               =  u8EndPointIdentifier;
    psDeviceInfo->sEndPoint.u16ManufacturerCode            =  ZCL_MANUFACTURER_CODE;
    psDeviceInfo->sEndPoint.u16ProfileEnum                 =  HA_PROFILE_ID;
    psDeviceInfo->sEndPoint.bIsManufacturerSpecificProfile =  FALSE;
    psDeviceInfo->sEndPoint.u16NumberOfClusters            =  sizeof( tsZLO_ControlBridgeDeviceClusterInstances ) / sizeof ( tsZCL_ClusterInstance );
    psDeviceInfo->sEndPoint.psClusterInstance              =  (tsZCL_ClusterInstance*)&psDeviceInfo->sClusterInstance;
    psDeviceInfo->sEndPoint.bDisableDefaultResponse        =  ZCL_DISABLE_DEFAULT_RESPONSES;
    psDeviceInfo->sEndPoint.pCallBackFunctions             =  cbCallBack;


    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        /* Create an instance of a Basic cluster as a server */
        if ( eCLD_BasicCreateBasic( &psDeviceInfo->sClusterInstance.sBasicServer,
                               TRUE,
                               &sCLD_Basic,
                               &psDeviceInfo->sBasicServerCluster,
                               &au8BasicClusterAttributeControlBits [ 0 ] ) != E_ZCL_SUCCESS )
        {
        // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }

    #endif

	#if (defined CLD_POWER_CONFIGURATION) && (defined POWER_CONFIGURATION_SERVER)
        /* Create an instance of a Power Configuration cluster as a server */
        if(eCLD_PowerConfigurationCreatePowerConfiguration(&psDeviceInfo->sClusterInstance.sPowerConfigurationServer,
                              TRUE,
                              &sCLD_PowerConfiguration,
                              &psDeviceInfo->sPowerConfigServerCluster,
                              &au8PowerConfigurationAttributeControlBits[0]) != E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_SERVER)
        /* Create an instance of an Identify cluster as a server */
        if(eCLD_IdentifyCreateIdentify(&psDeviceInfo->sClusterInstance.sIdentifyServer,
                              TRUE,
                              &sCLD_Identify,
                              &psDeviceInfo->sIdentifyServerCluster,
                              &au8IdentifyAttributeControlBits[0],
                              &psDeviceInfo->sIdentifyServerCustomDataStructure) != E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }     
    #endif

	#if (defined CLD_BINARY_INPUT_BASIC) && (defined BINARY_INPUT_BASIC_SERVER)
		/* Create an instance of a bianry input basic cluster as a server */
		if(eCLD_BinaryInputBasicCreateBinaryInputBasic(&psDeviceInfo->sClusterInstance.sBinaryInputBasicServer,
							  TRUE,
							  &sCLD_BinaryInputBasic,
							  &psDeviceInfo->sBinaryInputBasicServerCluster,
							  &au8BinaryInputBasicAttributeControlBits[0]) != E_ZCL_SUCCESS)
		{
			return E_ZCL_FAIL;
		}

	#endif
    
    /* Recommended Optional Server Cluster */
    #if (defined CLD_ZLL_COMMISSION) && (defined ZLL_COMMISSION_SERVER)
        /* Create an instance of a basic cluster as a server */
        if(eCLD_ZllCommissionCreateCommission(&psDeviceInfo->sClusterInstance.sZllCommissionServer,
                              TRUE,
                              &sCLD_ZllCommission,
                              &psDeviceInfo->sZllCommissionServerCluster,
                              &au8ZllCommissionAttributeControlBits[0],
                              &psDeviceInfo->sZllCommissionServerCustomDataStructure) != E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif
    
    #if (defined CLD_OTA) && (defined OTA_SERVER)
       if (eOTA_Create(
           &psDeviceInfo->sClusterInstance.sOTAServer,
           TRUE,  /* Server */
           &sCLD_OTA,
           &psDeviceInfo->sCLD_ServerOTA,  /* cluster definition */
           u8EndPointIdentifier,
           NULL,
           &psDeviceInfo->sCLD_OTA_ServerCustomDataStruct
           )!= E_ZCL_SUCCESS)

        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif 
    
    /*
     * Mandatory client clusters
     */
     
    #if (defined CLD_BASIC) && (defined BASIC_CLIENT)
        /* Create an instance of a Basic cluster as a client */
        if(eCLD_BasicCreateBasic(&psDeviceInfo->sClusterInstance.sBasicClient,
                              FALSE,
                              &sCLD_Basic,
                              &psDeviceInfo->sBasicClientCluster,
                              &au8BasicClusterAttributeControlBits[0]) != E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }    
    #endif
    
    #if (defined CLD_IDENTIFY) && (defined IDENTIFY_CLIENT)
        /* Create an instance of an Identify cluster as a client */
        if ( eCLD_IdentifyCreateIdentify ( &psDeviceInfo->sClusterInstance.sIdentifyClient,
                                      FALSE,
                                      &sCLD_Identify,
                                      &psDeviceInfo->sIdentifyClientCluster,
                                      &au8IdentifyAttributeControlBits[0],
                                      &psDeviceInfo->sIdentifyClientCustomDataStructure ) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif
    
    #if (defined CLD_GROUPS) && (defined GROUPS_CLIENT)
        /* Create an instance of a Groups cluster as a client */
        if ( eCLD_GroupsCreateGroups ( &psDeviceInfo->sClusterInstance.sGroupsClient,
                                  FALSE,
                                  &sCLD_Groups,
                                  &psDeviceInfo->sGroupsClientCluster,
                                  &au8GroupsAttributeControlBits[0],
                                  &psDeviceInfo->sGroupsClientCustomDataStructure,
                                  &psDeviceInfo->sEndPoint ) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif
    
    #if (defined CLD_SCENES) && (defined SCENES_CLIENT)
        /* Create an instance of a Scenes cluster as a client */
        if ( eCLD_ScenesCreateScenes ( &psDeviceInfo->sClusterInstance.sScenesClient,
                                  FALSE,
                                  &sCLD_Scenes,
                                  &psDeviceInfo->sScenesClientCluster,
                                  &au8ScenesAttributeControlBits[0],
                                  &psDeviceInfo->sScenesClientCustomDataStructure,
                                  &psDeviceInfo->sEndPoint ) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif
    
    #if (defined CLD_ONOFF) && (defined ONOFF_CLIENT)
        /* Create an instance of an On/Off cluster as a client */
        if ( eCLD_OnOffCreateOnOff ( &psDeviceInfo->sClusterInstance.sOnOffClient,
                                FALSE,
                                &sCLD_OnOffClient,
                                &psDeviceInfo->sOnOffClientCluster,
                                &au8OnOffClientAttributeControlBits[0],
                                NULL  /* no cust data struct for client */ )!= E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif


    #if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_CLIENT)
        /* Create an instance of a Level Control cluster as a client */
        if ( eCLD_LevelControlCreateLevelControl ( &psDeviceInfo->sClusterInstance.sLevelControlClient,
                                              FALSE,
                                              &sCLD_LevelControlClient,
                                              &psDeviceInfo->sLevelControlClientCluster,
                                              &au8LevelControlClientAttributeControlBits[0],
                                              &psDeviceInfo->sLevelControlClientCustomDataStructure ) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_COLOUR_CONTROL) && (defined COLOUR_CONTROL_CLIENT)
        /* Create an instance of a Colour Control cluster as a client */
        if(eCLD_ColourControlCreateColourControl(
                              &psDeviceInfo->sClusterInstance.sColourControlClient,
                              FALSE,
                              &sCLD_ColourControl,
                              &psDeviceInfo->sColourControlClientCluster,
                              &au8ColourControlAttributeControlBits[0],
                              &psDeviceInfo->sColourControlClientCustomDataStructure) != E_ZCL_SUCCESS)
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif

    
    /* Recommended optional client */
    
    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        /* Create an instance of an OTA cluster as a client */
       if(eOTA_Create(&psDeviceInfo->sClusterInstance.sOTAClient,
                      FALSE,  /* client */
                      &sCLD_OTA,
                      &psDeviceInfo->sCLD_OTA,  /* cluster definition */
                      u8EndPointIdentifier,
                      NULL,
                      &psDeviceInfo->sCLD_OTA_CustomDataStruct)!= E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif
    
    #if (defined CLD_ILLUMINANCE_MEASUREMENT) && (defined ILLUMINANCE_MEASUREMENT_CLIENT)
        /* Create an instance of an Illuminance Measurement cluster as a client */
        if(eCLD_IlluminanceMeasurementCreateIlluminanceMeasurement(
                              &psDeviceInfo->sClusterInstance.sIlluminanceMeasurementClient,
                              FALSE,
                              &sCLD_IlluminanceMeasurement,
                              &psDeviceInfo->sIlluminanceMeasurementClientCluster,
                              &au8IlluminanceMeasurementAttributeControlBits[0])!= E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif
    
    #if (defined CLD_ILLUMINANCE_LEVEL_SENSING) && (defined ILLUMINANCE_LEVEL_SENSING_CLIENT)
        /* Create an instance of an Illuminance Level Sensing  cluster as a client */
        if(eCLD_IlluminanceLevelSensingCreateIlluminanceLevelSensing(
                              &psDeviceInfo->sClusterInstance.sIlluminanceLevelSensingClient,
                              FALSE,
                              &sCLD_IlluminanceLevelSensing,
                              &psDeviceInfo->sIlluminanceLevelSensingClientCluster,
                              &au8IlluminanceLevelSensingAttributeControlBits[0])!= E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif
    
    #if (defined CLD_OCCUPANCY_SENSING) && (defined OCCUPANCY_SENSING_CLIENT)
        /* Create an instance of an Occupancy Sensing cluster as a client */
        if(eCLD_OccupancySensingCreateOccupancySensing(
                              &psDeviceInfo->sClusterInstance.sOccupancySensingClient,
                              FALSE,
                              &sCLD_OccupancySensing,
                              &psDeviceInfo->sOccupancySensingClientCluster,
                              &au8OccupancySensingAttributeControlBits[0])!= E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_ZLL_COMMISSION) && (defined ZLL_COMMISSION_CLIENT)
        /* Create an instance of a zll commissioning cluster as a client */
        if(eCLD_ZllCommissionCreateCommission(&psDeviceInfo->sClusterInstance.sZllCommissionClient,
                              FALSE,
                              &sCLD_ZllCommission,
                              &psDeviceInfo->sZllCommissionClientCluster,
                              &au8ZllCommissionAttributeControlBits[0],
                              &psDeviceInfo->sZllCommissionClientCustomDataStructure) != E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif
    
    /* Optional server */
    #if (defined CLD_ONOFF) && (defined ONOFF_SERVER)
        /* Create an instance of an On/Off cluster as a server */
        if ( eCLD_OnOffCreateOnOff ( &psDeviceInfo->sClusterInstance.sOnOffServer,
                                TRUE,
                                &sCLD_OnOff,
                                &psDeviceInfo->sOnOffServerCluster,
                                &au8OnOffAttributeControlBits[0],
                                &psDeviceInfo->sOnOffServerCustomDataStructure )!= E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif

	#if (defined CLD_LEVEL_CONTROL) && (defined LEVEL_CONTROL_SERVER)
        /* Create an instance of a Level Control cluster as a server */
        if(eCLD_LevelControlCreateLevelControl(&psDeviceInfo->sClusterInstance.sLevelControlServer,
                              TRUE,
                              &sCLD_LevelControl,
                              &psDeviceInfo->sLevelControlServerCluster,
                              &au8LevelControlAttributeControlBits[0],
                              &psDeviceInfo->sLevelControlServerCustomDataStructure) != E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
        /* Create an instance of a Groups cluster as a server */
        if ( eCLD_GroupsCreateGroups ( &psDeviceInfo->sClusterInstance.sGroupsServer,
                                  TRUE,
                                  &sCLD_Groups,
                                  &psDeviceInfo->sGroupsServerCluster,
                                  &au8GroupsAttributeControlBits[0],
                                  &psDeviceInfo->sGroupsServerCustomDataStructure,
                                  &psDeviceInfo->sEndPoint ) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_APPLIANCE_STATISTICS) && (defined APPLIANCE_STATISTICS_SERVER)
        /* Create an instance of a appliance statistics cluster as a server */
        if ( eCLD_ApplianceStatisticsCreateApplianceStatistics ( &psDeviceInfo->sClusterInstance.sASCServer,
                                                            TRUE,
                                                            &sCLD_ApplianceStatistics,
                                                            &psDeviceInfo->sASCServerCluster,
                                                            &au8ApplianceStatisticsAttributeControlBits[0],
                                                            &psDeviceInfo->sASCServerCustomDataStructure ) != E_ZCL_SUCCESS )
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif

	#if (defined CLD_TIME) && (defined TIME_SERVER)
	   /* Create an instance of a Basic cluster as a server */
	   if ( eCLD_TimeCreateTime(&psDeviceInfo->sClusterInstance.sTimeServer,
							  TRUE,
							  &sCLD_Time,
							  &psDeviceInfo->sTimeServerCluster,
							  &au8TimeClusterAttributeControlBits [ 0 ] ) != E_ZCL_SUCCESS )
	   {
	   // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
		   return E_ZCL_FAIL;
	   }

    #endif

	#if (defined CLD_ELECTRICAL_MEASUREMENT && defined ELECTRICAL_MEASUREMENT_SERVER)
		if (eCLD_ElectricalMeasurementCreateElectricalMeasurement(
				&psDeviceInfo->sClusterInstance.sElectricalMeasurementServer,
				TRUE,
				&sCLD_ElectricalMeasurement,
				&psDeviceInfo->sCLD_ElectricalMeasurement,
				au8ElectricalMeasurementAttributeControlBits)!= E_ZCL_SUCCESS)
		{
			return E_ZCL_FAIL;
		}
	#endif

    /* Optional CLient */
    #if (defined CLD_IASZONE) && (defined IASZONE_CLIENT)
        /* Create an instance of a IAS Zone cluster as a client */
        if( eCLD_IASZoneCreateIASZone ( &psDeviceInfo->sClusterInstance.sIASZoneClient,
                                    FALSE,
                                    &sCLD_IASZone,
                                    &psDeviceInfo->sIASZoneClientCluster,
                                    &au8IASZoneAttributeControlBits[0],
                                    &psDeviceInfo->sIASZoneClientCustomDataStructure ) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif

	#if (defined CLD_IASZONE) && (defined IASZONE_SERVER)
        /* Create an instance of a IAS Zone cluster as a client */
        if( eCLD_IASZoneCreateIASZone ( &psDeviceInfo->sClusterInstance.sIASZoneServer,
                                    FALSE,
                                    &sCLD_IASZone,
                                    &psDeviceInfo->sIASZoneServerCluster,
                                    &au8IASZoneAttributeControlBits[0],
                                    &psDeviceInfo->sIASZoneServerCustomDataStructure ) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif
    
    #if (defined CLD_DOOR_LOCK) && (defined DOOR_LOCK_CLIENT)
        /* Create an instance of a Door Lock cluster as a client */
        if( eCLD_DoorLockCreateDoorLock ( &psDeviceInfo->sClusterInstance.sDoorLockClient,
                                      FALSE,
                                      &sCLD_DoorLock,
                                      &psDeviceInfo->sDoorLockClientCluster,
                                      &au8DoorLockAttributeControlBits[0] ) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_WINDOWCOVERING) && (defined WINDOWCOVERING_CLIENT)
        /* Create an instance of a Window Covering cluster as a client */
        if( eCLD_WindowCoveringCreateWindowCovering ( &psDeviceInfo->sClusterInstance.sWindowCoveringClient,
                                                      FALSE,
                                                      &sCLD_WindowCovering,
                                                      &psDeviceInfo->sWindowCoveringClientCluster,
                                                      &au8WindowCoveringAttributeControlBits[0] ) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_SIMPLE_METERING) && (defined SM_CLIENT)
        /* Create an instance of a Simple Metering cluster as a client */
        if( eSE_SMCreate( u8EndPointIdentifier,                                    // uint8 u8Endpoint
                      FALSE,                                                       // bool_t bIsServer
                      NULL,                                                        // uint8 *pu8AttributeControlBits
                      &psDeviceInfo->sClusterInstance.sMeteringClient,             // tsZCL_ClusterInstance *psClusterInstance
                      &sCLD_SimpleMetering,                                        // tsZCL_ClusterDefinition *psClusterDefinition
                      &psDeviceInfo->sMeteringClientCustomDataStructure,           // tsSM_CustomStruct *psCustomDataStruct
                      NULL ) != E_ZCL_SUCCESS )                                     // void *pvEndPointSharedStructPtr
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }

        /* By default the SM cluster uses APS layer security, we don't need this for HA applications */
        psDeviceInfo->sClusterInstance.sMeteringClient.psClusterDefinition->u8ClusterControlFlags = E_ZCL_SECURITY_NETWORK;
    #endif



    #if (defined CLD_TEMPERATURE_MEASUREMENT) && (defined TEMPERATURE_MEASUREMENT_CLIENT)
        /* Create an instance of a Temperature Measurement cluster as a client */
        if ( eCLD_TemperatureMeasurementCreateTemperatureMeasurement ( &psDeviceInfo->sClusterInstance.sTemperatureMeasurementClient,
                                                                  FALSE,
                                                                  &sCLD_TemperatureMeasurement,
                                                                  &psDeviceInfo->sTemperatureMeasurementClientCluster,
                                                                  &au8TemperatureMeasurementAttributeControlBits[0]) != E_ZCL_SUCCESS )
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_RELATIVE_HUMIDITY_MEASUREMENT) && (defined RELATIVE_HUMIDITY_MEASUREMENT_CLIENT)
        /* Create an instance of a Relative Humidity Measurement cluster as a client */
        if ( eCLD_RelativeHumidityMeasurementCreateRelativeHumidityMeasurement ( &psDeviceInfo->sClusterInstance.sRelativeHumidityMeasurementClient,
                                                                           FALSE,
                                                                           &sCLD_RelativeHumidityMeasurement,
                                                                           &psDeviceInfo->sRelativeHumidityMeasurementClientCluster,
                                                                           &au8RelativeHumidityMeasurementAttributeControlBits[0]) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif

	#if (defined CLD_PRESSURE_MEASUREMENT) && (defined PRESSURE_MEASUREMENT_CLIENT)
        /* Create an instance of a Relative Humidity Measurement cluster as a client */
        if ( eCLD_PressureMeasurementCreatePressureMeasurement( &psDeviceInfo->sClusterInstance.sCLD_PressureMeasurementClient,
                                                                           FALSE,
                                                                           &sCLD_PressureMeasurement,
                                                                           &psDeviceInfo->sPressureMeasurementClientCluster,
                                                                           &au8PressureMeasurementAttributeControlBits[0]) != E_ZCL_SUCCESS )
        {
           // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_THERMOSTAT) && (defined THERMOSTAT_CLIENT)
        /* Create an instance of a Thermostat cluster as a client */
        if ( eCLD_ThermostatCreateThermostat ( &psDeviceInfo->sClusterInstance.sThermostatClient,
                                          FALSE,
                                          &sCLD_Thermostat,
                                          &psDeviceInfo->sThermostatClientCluster,
                                          &au8ThermostatAttributeControlBits[0],
                                          &psDeviceInfo->sThermostatClientCustomDataStructure ) != E_ZCL_SUCCESS )
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif
    
    #if (defined CLD_APPLIANCE_STATISTICS) && (defined APPLIANCE_STATISTICS_CLIENT)
        /* Create an instance of a appliance statistics cluster as a server */
        if ( eCLD_ApplianceStatisticsCreateApplianceStatistics ( &psDeviceInfo->sClusterInstance.sASCClient,
                                                            FALSE,
                                                            &sCLD_ApplianceStatistics,
                                                            &psDeviceInfo->sASCClientCluster,
                                                            &au8ApplianceStatisticsAttributeControlBits[0],
                                                            &psDeviceInfo->sASCClientCustomDataStructure ) != E_ZCL_SUCCESS )
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_DIAGNOSTICS) && (defined DIAGNOSTICS_CLIENT)
        /* Create an instance of a Diagnostic cluster as a client */
        if ( eCLD_DiagnosticsCreateDiagnostics ( &psDeviceInfo->sClusterInstance.sDiagnosticClient,
                                              FALSE,
                                              &sCLD_Diagnostics,
                                              &psDeviceInfo->sDiagnosticClientCluster,
                                              &au8DiagnosticsClusterAttributeControlBits[0] ) != E_ZCL_SUCCESS )
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif


//RAJOUT FRED
	#if (defined CLD_MULTISTATE_INPUT_BASIC) && (defined MULTISTATE_INPUT_BASIC_SERVER)
       /* Create an instance of a Basic cluster as a server */
       if ( eCLD_MultistateInputBasicCreateMultistateInputBasic( &psDeviceInfo->sClusterInstance.sMultistateServer,
                              TRUE,
                              &sCLD_MultistateInputBasic,
                              &psDeviceInfo->sMultistateServerCluster,
                              &au8MultistateInputBasicAttributeControlBits [ 0 ] ) != E_ZCL_SUCCESS )
       {
       // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
       }
     //  psDeviceInfo->sClusterInstance.sMultistateServer.psClusterDefinition->u8ClusterControlFlags = (E_ZCL_SECURITY_NETWORK | CLUSTER_MIRROR_BIT) ;
   #endif

	#if (defined CLD_MULTISTATE_INPUT_BASIC) && (defined MULTISTATE_INPUT_BASIC_CLIENT)
       /* Create an instance of a Basic cluster as a server */
       if ( eCLD_MultistateInputBasicCreateMultistateInputBasic( &psDeviceInfo->sClusterInstance.sMultistateClient,
                              TRUE,
                              &sCLD_MultistateInputBasic,
                              &psDeviceInfo->sMultistateClientCluster,
                              &au8MultistateInputBasicAttributeControlBits [ 0 ] ) != E_ZCL_SUCCESS )
       {
       // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
           return E_ZCL_FAIL;
       }
      // psDeviceInfo->sClusterInstance.sMultistateClient.psClusterDefinition->u8ClusterControlFlags = (E_ZCL_SECURITY_NETWORK | CLUSTER_MIRROR_BIT) ;
   #endif

	#if (defined CLD_ANALOG_INPUT_BASIC) && (defined CLD_ANALOG_INPUT_BASIC_CLIENT)
		   /* Create an instance of a Basic cluster as a server */
		   if ( eCLD_AnalogInputBasicCreateAnalogInputBasic(&psDeviceInfo->sClusterInstance.sAnalogInputCLient,
								  TRUE,
								  &sCLD_AnalogInputBasic,
								  &psDeviceInfo->sAnalogInputClientCluster,
								  &au8AnalogInputBasicAttributeControlBits [ 0 ] ) != E_ZCL_SUCCESS )
		   {
		   // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
			   return E_ZCL_FAIL;
		   }
		  // psDeviceInfo->sClusterInstance.sMultistateClient.psClusterDefinition->u8ClusterControlFlags = (E_ZCL_SECURITY_NETWORK | CLUSTER_MIRROR_BIT) ;
	   #endif
	#if (defined CLD_PRIVATE_PHILIPS) && (defined PRIVATE_PHILIPS_SERVER)
        /* Create an instance of a Temperature Measurement cluster as a client */
        if ( eCLD_PrivatePhilipsCreate ( &psDeviceInfo->sClusterInstance.sPrivatePhilips,
                                                                  FALSE,
                                                                  &sCLD_PrivatePhilips,
                                                                  &psDeviceInfo->sPrivatePhilipsCluster,
                                                                  &au8PrivatePhilipsAttributeControlBits[0]) != E_ZCL_SUCCESS )
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif

     teZCL_Status status;
   status= eZCL_Register(&psDeviceInfo->sEndPoint);
    vLog_Printf(1,LOG_DEBUG,"\n Status : %d\n",status);
    return status;

}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

