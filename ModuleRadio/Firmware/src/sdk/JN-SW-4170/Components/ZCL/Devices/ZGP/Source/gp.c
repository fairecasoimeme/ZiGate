/*****************************************************************************
 *
 * MODULE:             Green Power Profile
 *
 * COMPONENT:          gp.c
 *
 * AUTHOR:             Ramakrishna
 *
 * DESCRIPTION:        The API for the Green Power End Point Registration
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Devices/ZGP/Source/gp.c $
 *
 * $Revision: 85828 $
 *
 * $LastChangedBy: nxp29757 $
 *
 * $LastChangedDate: 2016-12-14 14:07:03 +0100 (Wed, 14 Dec 2016) $
 *
 * $Id: gp.c 85828 2016-12-14 13:07:03Z nxp29757 $
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

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <string.h>
#include "zps_apl.h"
#include "zcl_heap.h"
#include "zcl.h"
#include "zcl_options.h"
#include "zcl_common.h"
#include "GreenPower.h"
#include "gp.h"

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
#ifdef GP_COMBO_BASIC_DEVICE
/****************************************************************************
 *
 * NAME: eGP_RegisterComboBasicEndPoint
 *
 * DESCRIPTION:
 * Registers a Green Power Cluster with the ZCL layer
 *
 * PARAMETERS:                    Name                            Usage
 * uint8                      u8EndPointIdentifier            Endpoint id
 * tfpZCL_ZCLCallBackFunction cbCallBack                      Pointer to endpoint callback
 * tsGP_GreenPowerDevice      psDeviceInfo                    Pointer to struct containing device info
 * uint16                     u16ProfileId                    Profile id of application
 * tsGP_TranslationTableEntry   psTranslationTableEntry              pointer of translation table
 *
 * RETURNS:
 * teZCL_Status
 *
 ****************************************************************************/
PUBLIC teZCL_Status eGP_RegisterComboBasicEndPoint(
                        uint8                               u8EndPointIdentifier,
                        tfpZCL_ZCLCallBackFunction          cbCallBack,
                        tsGP_GreenPowerDevice               *psDeviceInfo,
                        uint16                              u16ProfileId,
                        tsGP_TranslationTableEntry          *psTranslationTableEntry)
{

    /* Fill in end point details */
    psDeviceInfo->sEndPoint.u8EndPointNumber =                  u8EndPointIdentifier; //local proxy Endpoint
    psDeviceInfo->sEndPoint.u16ManufacturerCode =               GP_MANUFACTURER_CODE;
    psDeviceInfo->sEndPoint.u16ProfileEnum =                    GREENPOWER_PROFILE_ID; // Profile ID for Green Power Cluster
    psDeviceInfo->sEndPoint.bIsManufacturerSpecificProfile =    FALSE;
    psDeviceInfo->sEndPoint.u16NumberOfClusters =               sizeof(tsGP_GreenPowerClusterInstances) / sizeof(tsZCL_ClusterInstance);
    psDeviceInfo->sEndPoint.psClusterInstance =                 (tsZCL_ClusterInstance*)&psDeviceInfo->sClusterInstance;
    psDeviceInfo->sEndPoint.bDisableDefaultResponse =           ZCL_DISABLE_DEFAULT_RESPONSES;
    psDeviceInfo->sEndPoint.pCallBackFunctions =                cbCallBack;

#ifdef CLD_GREENPOWER
    /* Copy Green Power Mapped End-point in zcl_common structure */
    psZCL_Common->u8GreenPowerMappedEpId = u8EndPointIdentifier;
#endif

    /* Create Server Green Power Cluster Instance */
    if(eGP_CreateGreenPower(
            &psDeviceInfo->sClusterInstance.sGreenPowerServer,
            TRUE,
            &sCLD_GreenPowerServer,
            &psDeviceInfo->sServerGreenPowerCluster,
            &au8ServerGreenPowerClusterAttributeControlBits[0],
            &psDeviceInfo->sGreenPowerCustomDataStruct)
             != E_ZCL_SUCCESS)
    {
        return(E_ZCL_FAIL);
    }

    /* Create Client Green Power Cluster Instance */
    if(eGP_CreateGreenPower(
            &psDeviceInfo->sClusterInstance.sGreenPowerClient,
            FALSE,
            &sCLD_GreenPowerClient,
            &psDeviceInfo->sClientGreenPowerCluster,
            &au8ClientGreenPowerClusterAttributeControlBits[0],
            &psDeviceInfo->sGreenPowerCustomDataStruct)
             != E_ZCL_SUCCESS)
    {
        return(E_ZCL_FAIL);
    }

    /* Save Translation table address and No. Of Entries */
    psDeviceInfo->sGreenPowerCustomDataStruct.psZgpsTranslationTableEntry = psTranslationTableEntry;

    /* Set Default device operating mode */
    psDeviceInfo->sGreenPowerCustomDataStruct.eGreenPowerDeviceMode = E_GP_OPERATING_MODE;

    /* Set GP device type */
    psDeviceInfo->sGreenPowerCustomDataStruct.eGreenPowerDeviceType = E_GP_ZGP_COMBO_BASIC_DEVICE;

    /* Save Application Profile Id in GP custom data structure */
    psDeviceInfo->sGreenPowerCustomDataStruct.u16ProfileId = u16ProfileId;

    /* Set u16CommissionSetAddress */
    psDeviceInfo->sGreenPowerCustomDataStruct.u64CommissionSetAddress = 0x00;
    psDeviceInfo->sGreenPowerCustomDataStruct.bCommissionUnicast = 0;

    /* Register bGP_AliasPresent() with ZPS for alias address conflict */
    ZPS_vAfRegisterAliasPresentCallback(&bGP_AliasPresent);

    /* Ignore profile check for loopback */
    zps_vSetIgnoreProfileCheck();

    /* Register u8GP_SecurityProcessCallback() with ZPS for Process security of received GPDF when a callback is received from stack */
    ZPS_vRegisterSecRequestResponseCallback(&u8GP_SecurityProcessCallback);

    /* Set bitmap for Mandatory features: This will be updated in future releases */

    return eZCL_Register(&psDeviceInfo->sEndPoint);
}
#endif
#ifdef GP_PROXY_BASIC_DEVICE
/****************************************************************************
 *
 * NAME: eGP_RegisterProxyBasicEndPoint
 *
 * DESCRIPTION:
 * Registers a Green Power Cluster with the ZCL layer
 *
 * PARAMETERS:                    Name                            Usage
 * uint8                      u8EndPointIdentifier            Endpoint id
 * tfpZCL_ZCLCallBackFunction cbCallBack                      Pointer to endpoint callback
 * tsGP_GreenPowerDevice      psDeviceInfo                    Pointer to struct containing device info
 *
 * RETURNS:
 * teZCL_Status
 *
 ****************************************************************************/
PUBLIC teZCL_Status eGP_RegisterProxyBasicEndPoint(
                        uint8                               u8EndPointIdentifier,
                        tfpZCL_ZCLCallBackFunction          cbCallBack,
                        tsGP_GreenPowerDevice               *psDeviceInfo)
{

    /* Fill in end point details */
    psDeviceInfo->sEndPoint.u8EndPointNumber =                  u8EndPointIdentifier; //local proxy Endpoint
    psDeviceInfo->sEndPoint.u16ManufacturerCode =               GP_MANUFACTURER_CODE;
    psDeviceInfo->sEndPoint.u16ProfileEnum =                    GREENPOWER_PROFILE_ID; // Profile ID for Green Power Cluster
    psDeviceInfo->sEndPoint.bIsManufacturerSpecificProfile =    FALSE;
    psDeviceInfo->sEndPoint.u16NumberOfClusters =               sizeof(tsGP_GreenPowerClusterInstances) / sizeof(tsZCL_ClusterInstance);
    psDeviceInfo->sEndPoint.psClusterInstance =                 (tsZCL_ClusterInstance*)&psDeviceInfo->sClusterInstance;
    psDeviceInfo->sEndPoint.bDisableDefaultResponse =           ZCL_DISABLE_DEFAULT_RESPONSES;
    psDeviceInfo->sEndPoint.pCallBackFunctions =                cbCallBack;

#ifdef CLD_GREENPOWER
    /* Copy Green Power Mapped End-point in zcl_common structure */
    psZCL_Common->u8GreenPowerMappedEpId = u8EndPointIdentifier;
#endif


    /* Create Server Green Power Cluster Instance */
   /* if(eGP_CreateGreenPower(
            &psDeviceInfo->sClusterInstance.sGreenPowerServer,
            TRUE,
            &sCLD_GreenPowerClient,
            NULL,
            NULL,
            &psDeviceInfo->sGreenPowerCustomDataStruct)
             != E_ZCL_SUCCESS)
    {
        return(E_ZCL_FAIL);
    }
*/
    /* Create Client Green Power Cluster Instance */
    if(eGP_CreateGreenPower(
            &psDeviceInfo->sClusterInstance.sGreenPowerClient,
            FALSE,
            &sCLD_GreenPowerClient,
            &psDeviceInfo->sClientGreenPowerCluster,
            &au8ClientGreenPowerClusterAttributeControlBits[0],
            &psDeviceInfo->sGreenPowerCustomDataStruct)
             != E_ZCL_SUCCESS)
    {
        return(E_ZCL_FAIL);
    }

    /* Set Default device operating mode */
    psDeviceInfo->sGreenPowerCustomDataStruct.eGreenPowerDeviceMode = E_GP_OPERATING_MODE;

    /* Set GP device type */
    psDeviceInfo->sGreenPowerCustomDataStruct.eGreenPowerDeviceType = E_GP_ZGP_PROXY_BASIC_DEVICE;

    /* Set u16CommissionSetAddress */
    psDeviceInfo->sGreenPowerCustomDataStruct.u64CommissionSetAddress = 0x00;
    psDeviceInfo->sGreenPowerCustomDataStruct.bCommissionUnicast = 0;
    /* Register bGP_AliasPresent() with ZPS for alias address conflict */
    ZPS_vAfRegisterAliasPresentCallback(&bGP_AliasPresent);

    /* Ignore profile check for loopback */
    zps_vSetIgnoreProfileCheck();

    /* Register u8GP_SecurityProcessCallback() with ZPS for Process security of received GPDF when a callback is received from stack */
    ZPS_vRegisterSecRequestResponseCallback(&u8GP_SecurityProcessCallback);

    /* Set bitmap for Mandatory features: This will be updated in future releases */

    return eZCL_Register(&psDeviceInfo->sEndPoint);
}
#endif
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

