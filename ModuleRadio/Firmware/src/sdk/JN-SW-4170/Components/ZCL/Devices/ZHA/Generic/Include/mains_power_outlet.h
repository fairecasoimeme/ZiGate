/*****************************************************************************
 *
 * MODULE:             Mains Power Outlet
 *
 * COMPONENT:          mains_power_outlet.h
 *
 * AUTHOR:             Ian Morris
 *
 * DESCRIPTION:        Header for ZigBee mains power outlet profile functions
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
 * Copyright NXP B.V. 2015. All rights reserved
 *
 ****************************************************************************/
#ifndef MAINS_POWER_OUTLET_H
#define MAINS_POWER_OUTLET_H

#if defined __cplusplus
extern "C" {
#endif

/* Standard includes */
#include <jendefs.h>

/* Stack/profile includes */
#include "zcl.h"
#include "zcl_options.h"
#include "Basic.h"
#include "Identify.h"
#include "OnOff.h"
#include "Scenes.h"
#include "Groups.h"

#ifdef CLD_POWER_CONFIGURATION
    #include "PowerConfiguration.h"
#endif

#ifdef CLD_DEVICE_TEMPERATURE_CONFIGURATION
    #include "DeviceTemperatureConfiguration.h"
#endif

#ifdef CLD_ALARMS
    #include "Alarms.h"
#endif

#ifdef CLD_POLL_CONTROL
    #include "PollControl.h"
#endif

#ifdef CLD_OTA
    #include "OTA.h"
#endif

#ifdef CLD_TIME
    #include "Time.h"
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

    /* Mains Power Outlet has three additional mandatory (server) clusters */
    #if (defined CLD_ONOFF) && (defined ONOFF_SERVER)
        tsZCL_ClusterInstance sOnOffServer;
    #endif

    #if (defined CLD_SCENES) && (defined SCENES_SERVER)
        tsZCL_ClusterInstance sScenesServer;
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
        tsZCL_ClusterInstance sGroupsServer;
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

    /* Optional client clusters */
    #if (defined CLD_POLL_CONTROL) && (defined POLL_CONTROL_CLIENT)
        tsZCL_ClusterInstance sPollControlClient;
    #endif

    #ifdef CLD_TIME
        tsZCL_ClusterInstance sTimeClient;
    #endif
} tsHA_MainsPowerOutletDeviceClusterInstances __attribute__ ((aligned(4)));


/* Holds everything required to create an instance of an main power outlet */
typedef struct
{
    tsZCL_EndPointDefinition sEndPoint;

    /* Cluster instances */
    tsHA_MainsPowerOutletDeviceClusterInstances sClusterInstance;

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

    #if (defined CLD_ONOFF) && (defined ONOFF_SERVER)
        /* On/Off Cluster - Server */
        tsCLD_OnOff sOnOffServerCluster;
        tsCLD_OnOffCustomDataStructure     sOnOffServerCustomDataStructure;
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

    /* Optional client clusters */
    #if (defined CLD_POLL_CONTROL) && (defined POLL_CONTROL_CLIENT)
        tsCLD_PollControl sPollControlClientCluster;
        tsCLD_PollControlCustomDataStructure sPollControlClientCustomDataStructure;
    #endif

    #ifdef CLD_TIME
        tsCLD_Time sTimeCluster;
    #endif

} tsHA_MainsPowerOutletDevice;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC teZCL_Status eHA_RegisterMainsPowerOutletEndPoint(uint8 u8EndPointIdentifier,
                                                         tfpZCL_ZCLCallBackFunction cbCallBack,
                                                         tsHA_MainsPowerOutletDevice *psDeviceInfo);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* MAINS_POWER_OUTLET_H */
