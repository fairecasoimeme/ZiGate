/*****************************************************************************
 *
 * MODULE:             Green Power Profile
 *
 * COMPONENT:          gp.h
 *
 * AUTHOR:             Ramakrishna
 *
 * DESCRIPTION:        The API for the Green Power End Point Registration
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Devices/ZGP/Include/gp.h $
 *
 * $Revision: 78915 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2016-04-27 08:35:35 +0200 (Wed, 27 Apr 2016) $
 *
 * $Id: gp.h 78915 2016-04-27 06:35:35Z nxp57621 $
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

#ifndef COMBOMIN_H
#define COMBOMIN_H

#if defined __cplusplus
extern "C" {
#endif

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "GreenPower.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef GP_MANUFACTURER_CODE
#define GP_MANUFACTURER_CODE                                        (0)
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

    /* Holds cluster instances */
typedef struct
{
#ifdef GP_COMBO_BASIC_DEVICE
    tsZCL_ClusterInstance                  sGreenPowerServer;
#endif
    tsZCL_ClusterInstance                  sGreenPowerClient;
} tsGP_GreenPowerClusterInstances __attribute__ ((aligned(4)));


/* Holds everything required to create an instance of an Green Power device */
typedef struct
{
    tsZCL_EndPointDefinition               sEndPoint;

    /* Cluster instances */
    tsGP_GreenPowerClusterInstances        sClusterInstance;
    /* Holds the attributes for the Green Power cluster server */
#ifdef GP_COMBO_BASIC_DEVICE
    tsCLD_GreenPower                       sServerGreenPowerCluster;
#endif
   /* Holds the attributes for the Green Power cluster Client */
    tsCLD_GreenPower                       sClientGreenPowerCluster;

    /*Event Address, Custom call back event, Custom call back message*/
    tsGP_GreenPowerCustomData              sGreenPowerCustomDataStruct;
} tsGP_GreenPowerDevice;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC teZCL_Status eGP_RegisterComboBasicEndPoint(
                        uint8                               u8EndPointIdentifier,
                        tfpZCL_ZCLCallBackFunction          cbCallBack,
                        tsGP_GreenPowerDevice               *psDeviceInfo,
                        uint16                              u16ProfileId,
                        tsGP_TranslationTableEntry          *psTranslationTableEntry);

PUBLIC teZCL_Status eGP_RegisterProxyBasicEndPoint(
                        uint8                               u8EndPointIdentifier,
                        tfpZCL_ZCLCallBackFunction          cbCallBack,
                        tsGP_GreenPowerDevice               *psDeviceInfo);
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern const tsZCL_AttributeDefinition  asCLD_GreenPowerClusterAttributeDefinitionsClient[];
extern tsZCL_ClusterDefinition          sCLD_GreenPowerClient;
extern uint8                            au8ClientGreenPowerClusterAttributeControlBits[];

#ifdef GP_COMBO_BASIC_DEVICE
extern const tsZCL_AttributeDefinition  asCLD_GreenPowerClusterAttributeDefinitionsServer[];
extern tsZCL_ClusterDefinition          sCLD_GreenPowerServer;

extern uint8                            au8ServerGreenPowerClusterAttributeControlBits[];

#endif
/****************************************************************************/
#if defined __cplusplus
}
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* COMBOMIN_H */
