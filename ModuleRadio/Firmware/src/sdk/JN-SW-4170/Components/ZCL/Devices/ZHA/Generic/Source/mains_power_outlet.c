/*****************************************************************************
 *
 * MODULE:             Mains Power Outlet
 *
 * COMPONENT:          mains_power_outlet.c
 *
 * AUTHOR:             Ian Morris
 *
 * DESCRIPTION:        ZigBee Mains Power Outlet profile functions
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
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5164,
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
/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
/* Standard includes */
#include <jendefs.h>
#include <string.h>

/* Stack/profile includes */
#include "zps_apl.h"
#include "zcl_heap.h"
#include "zcl.h"
#include "zcl_options.h"
#include "mains_power_outlet.h"

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
 * NAME: eHA_RegisterMainsPowerOutletEndPoint
 *
 * DESCRIPTION:
 * Registers an On/Off Output device with the ZCL layer
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
PUBLIC teZCL_Status eHA_RegisterMainsPowerOutletEndPoint(uint8 u8EndPointIdentifier,
                                                         tfpZCL_ZCLCallBackFunction cbCallBack,
                                                         tsHA_MainsPowerOutletDevice *psDeviceInfo)
{
    /* Fill in end point details */
    psDeviceInfo->sEndPoint.u8EndPointNumber = u8EndPointIdentifier;
    psDeviceInfo->sEndPoint.u16ManufacturerCode = ZCL_MANUFACTURER_CODE;
    psDeviceInfo->sEndPoint.u16ProfileEnum = HA_PROFILE_ID;
    psDeviceInfo->sEndPoint.bIsManufacturerSpecificProfile = FALSE;
    psDeviceInfo->sEndPoint.u16NumberOfClusters = sizeof(tsHA_MainsPowerOutletDeviceClusterInstances) / sizeof(tsZCL_ClusterInstance);
    psDeviceInfo->sEndPoint.psClusterInstance = (tsZCL_ClusterInstance*)&psDeviceInfo->sClusterInstance;
    psDeviceInfo->sEndPoint.bDisableDefaultResponse = TRUE;
    psDeviceInfo->sEndPoint.pCallBackFunctions = cbCallBack;

    /* Mandatory server clusters */
    #if (defined CLD_BASIC) && (defined BASIC_SERVER)
        /* Create an instance of a Basic cluster as a server */
        if(eCLD_BasicCreateBasic(&psDeviceInfo->sClusterInstance.sBasicServer,
                              TRUE,
                              &sCLD_Basic,
                              &psDeviceInfo->sBasicServerCluster,
                              &au8BasicClusterAttributeControlBits[0]) != E_ZCL_SUCCESS)
        {
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
            return E_ZCL_FAIL;
        } 
    #endif

    #if (defined CLD_ONOFF) && (defined ONOFF_SERVER)
        /* Create an instance of a On/Off cluster as a server */
        if(eCLD_OnOffCreateOnOff(&psDeviceInfo->sClusterInstance.sOnOffServer,
                              TRUE,
                              &sCLD_OnOff,
                              &psDeviceInfo->sOnOffServerCluster,
                              &au8OnOffAttributeControlBits[0],
                              &psDeviceInfo->sOnOffServerCustomDataStructure) != E_ZCL_SUCCESS)
        {
            return E_ZCL_FAIL;
        } 
    #endif

    #if (defined CLD_SCENES) && (defined SCENES_SERVER)
        /* Create an instance of a Scenes cluster as a server */
        if(eCLD_ScenesCreateScenes(&psDeviceInfo->sClusterInstance.sScenesServer,
                                TRUE,
                                &sCLD_Scenes,
                                &psDeviceInfo->sScenesServerCluster,
                                &au8ScenesAttributeControlBits[0],
                                &psDeviceInfo->sScenesServerCustomDataStructure,
                                &psDeviceInfo->sEndPoint) != E_ZCL_SUCCESS)
        {
            return E_ZCL_FAIL;
        } 
    #endif

    #if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
        /* Create an instance of a Groups cluster as a server */
        if(eCLD_GroupsCreateGroups(&psDeviceInfo->sClusterInstance.sGroupsServer,
                                TRUE,
                                &sCLD_Groups,
                                &psDeviceInfo->sGroupsServerCluster,
                                &au8GroupsAttributeControlBits[0],
                                &psDeviceInfo->sGroupsServerCustomDataStructure,
                                &psDeviceInfo->sEndPoint) != E_ZCL_SUCCESS)
        {
            return E_ZCL_FAIL;
        } 
    #endif

    /* Optional server clusters */
    #if (defined CLD_POWER_CONFIGURATION) && (defined POWER_CONFIGURATION_SERVER)
        /* Create an instance of a Power Configuration cluster as a server */
        if(eCLD_PowerConfigurationCreatePowerConfiguration(&psDeviceInfo->sClusterInstance.sPowerConfigurationServer,
                                                        TRUE,
                                                        &sCLD_PowerConfiguration,
                                                        &psDeviceInfo->sPowerConfigServerCluster,
                                                        &au8PowerConfigurationAttributeControlBits[0]) != E_ZCL_SUCCESS)
        {
            return E_ZCL_FAIL;
        } 
    #endif

    #if (defined CLD_DEVICE_TEMPERATURE_CONFIGURATION) && (defined DEVICE_TEMPERATURE_CONFIGURATION_SERVER)
        /* Create an instance of a Device Temperature Configuration cluster as a server */
        if(eCLD_DeviceTemperatureConfigurationCreateDeviceTemperatureConfiguration(&psDeviceInfo->sClusterInstance.sDeviceTemperatureConfigurationServer,
                                                                                TRUE,
                                                                                &sCLD_DeviceTemperatureConfiguration,
                                                                                &psDeviceInfo->sDeviceTemperatureConfigurationServerCluster,
                                                                                &au8DeviceTempConfigClusterAttributeControlBits[0]) != E_ZCL_SUCCESS)
        {
            return E_ZCL_FAIL;
        } 
    #endif

    #if (defined CLD_ALARMS) && (defined ALARMS_SERVER)
        /* Create an instance of an Alarms cluster as a server */
        if(eCLD_AlarmsCreateAlarms(&psDeviceInfo->sClusterInstance.sAlarmsServer,
                                TRUE,
                                &sCLD_Alarms,
                                &psDeviceInfo->sAlarmsServerCluster,
                                &au8AlarmsAttributeControlBits[0],
                                &psDeviceInfo->sAlarmsServerCustomDataStructure) != E_ZCL_SUCCESS)
        {
            return E_ZCL_FAIL;
        } 
    #endif

    #if (defined CLD_POLL_CONTROL) && (defined POLL_CONTROL_SERVER)
        /* Create an instance of a Poll Control cluster as a server */
        if(eCLD_PollControlCreatePollControl(&psDeviceInfo->sClusterInstance.sPollControlServer,
                                          TRUE,
                                          &sCLD_PollControl,
                                          &psDeviceInfo->sPollControlServerCluster,
                                          &au8PollControlAttributeControlBits[0],
                                          &psDeviceInfo->sPollControlServerCustomDataStructure) != E_ZCL_SUCCESS)
        {
            return E_ZCL_FAIL;
        } 
    #endif

    #if (defined CLD_OTA) && (defined OTA_SERVER)
        if (eOTA_Create(&psDeviceInfo->sClusterInstance.sOTAServer,
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

    /* Optional client clusters */
    #if (defined CLD_POLL_CONTROL) && (defined POLL_CONTROL_CLIENT)
        /* Create an instance of a Poll Control cluster as a client */
        if(eCLD_PollControlCreatePollControl(&psDeviceInfo->sClusterInstance.sPollControlClient,
                                          FALSE,
                                          &sCLD_PollControl,
                                          &psDeviceInfo->sPollControlClientCluster,
                                          &au8PollControlAttributeControlBits[0],
                                          &psDeviceInfo->sPollControlClientCustomDataStructure) != E_ZCL_SUCCESS)
        {
            return E_ZCL_FAIL;
        } 
    #endif

    #if (defined CLD_OTA) && (defined OTA_CLIENT)
        if (eOTA_Create(&psDeviceInfo->sClusterInstance.sOTAClient,
                        FALSE,  /* client */
                        &sCLD_OTA,
                        &psDeviceInfo->sCLD_OTA,  /* cluster definition */
                        u8EndPointIdentifier,
                        NULL,
                        &psDeviceInfo->sCLD_OTA_CustomDataStruct
                        )!= E_ZCL_SUCCESS)
        {
            // Need to convert from cluster specific to ZCL return type so we lose the extra information of the return code
            return E_ZCL_FAIL;
        }
    #endif

    #if (defined CLD_TIME && defined TIME_CLIENT)
       if (eCLD_TimeCreateTime(
                    &psDeviceInfo->sClusterInstance.sTimeClient,
                    FALSE,
                    &sCLD_Time,
                    &psDeviceInfo->sTimeCluster,
                    &au8TimeClusterAttributeControlBits[0]) != E_ZCL_SUCCESS)
       {
           return E_ZCL_FAIL;
       }
    #endif

    return eZCL_Register(&psDeviceInfo->sEndPoint);
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
