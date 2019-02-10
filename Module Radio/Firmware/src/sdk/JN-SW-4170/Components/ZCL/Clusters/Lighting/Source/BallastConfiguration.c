/*****************************************************************************
 *
 * MODULE:             Ballast Configuration Cluster
 *
 * COMPONENT:          BallastConfiguration.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Ballast Configuration cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/Lighting/Source/BallastConfiguration.c $
 *
 * $Revision: 72591 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-09-08 14:41:01 +0200 (Tue, 08 Sep 2015) $
 *
 * $Id: BallastConfiguration.c 72591 2015-09-08 12:41:01Z nxp57621 $
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
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>

#include "zps_apl.h"
#include "zps_apl_aib.h"

#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_options.h"
#include "string.h"
#include "BallastConfiguration.h"


#include "dbg.h"

#ifdef DEBUG_CLD_BALLAST_CONFIGURATION
#define TRACE_BALLAST_CONFIGURATION TRUE
#else
#define TRACE_BALLAST_CONFIGURATION FALSE
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#if defined(CLD_BALLAST_CONFIGURATION) && !defined(BALLAST_CONFIGURATION_SERVER) && !defined(BALLAST_CONFIGURATION_CLIENT)
#error You Must Have either BALLAST_CONFIGURATION_SERVER and/or BALLAST_CONFIGURATION_CLIENT defined in zcl_options.h
#endif

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
const tsZCL_AttributeDefinition asCLD_BallastConfigurationClusterAttributeDefinitions[] = {
#ifdef BALLAST_CONFIGURATION_SERVER    
    /* Ballast Information attribute set attribute ID's (5.3.2.2.1) */
    #ifdef CLD_BALLASTCONFIGURATION_ATTR_PHYSICAL_MIN_LEVEL
        {E_CLD_BALLASTCONFIGURATION_ATTR_PHYSICAL_MIN_LEVEL,        E_ZCL_AF_RD,                E_ZCL_UINT8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8PhysicalMinLevel), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_PHYSICAL_MAX_LEVEL
        {E_CLD_BALLASTCONFIGURATION_ATTR_PHYSICAL_MAX_LEVEL,        E_ZCL_AF_RD,                E_ZCL_UINT8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8PhysicalMaxLevel), 0},
    #endif

        {E_CLD_BALLASTCONFIGURATION_ATTR_BALLAST_STATUS,            E_ZCL_AF_RD,                E_ZCL_BMAP8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8BallastStatus), 0},

        /* Ballast Settings attribute attribute ID's set (5.3.2.2.2) */
    #ifdef CLD_BALLASTCONFIGURATION_ATTR_MIN_LEVEL
        {E_CLD_BALLASTCONFIGURATION_ATTR_MIN_LEVEL,                 (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8MinLevel), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_MAX_LEVEL
        {E_CLD_BALLASTCONFIGURATION_ATTR_MAX_LEVEL,                 (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8MaxLevel), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_POWER_ON_LEVEL
        {E_CLD_BALLASTCONFIGURATION_ATTR_POWER_ON_LEVEL,            (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8PowerOnLevel), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_POWER_ON_FADE_TIME
        {E_CLD_BALLASTCONFIGURATION_ATTR_POWER_ON_FADE_TIME,        (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT16,  (uint32)(&((tsCLD_BallastConfiguration*)(0))->u16PowerOnFadeTime), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_INTRINSIC_BALLAST_FACTOR
        {E_CLD_BALLASTCONFIGURATION_ATTR_INTRINSIC_BALLAST_FACTOR,  (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8IntrinsicBallastFactor), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_BALLAST_FACTOR_ADJUSTMENT
        {E_CLD_BALLASTCONFIGURATION_ATTR_BALLAST_FACTOR_ADJUSTMENT, (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8BallastFactorAdjustment), 0},
    #endif

        /* Lamp Information attribute attribute ID's set (5.3.2.2.3) */
    #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_QUANTITY
        {E_CLD_BALLASTCONFIGURATION_ATTR_LAMP_QUANTITY,             E_ZCL_AF_RD,                E_ZCL_UINT8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8LampQuantity), 0},
    #endif

        /* Lamp Settings attribute ID's set (5.3.2.2.4) */
    #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_TYPE
        {E_CLD_BALLASTCONFIGURATION_ATTR_LAMP_TYPE,                 (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_CSTRING, (uint32)(&((tsCLD_BallastConfiguration*)(0))->sLampType), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_MANUFACTURER
        {E_CLD_BALLASTCONFIGURATION_ATTR_LAMP_MANUFACTURER,         (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_CSTRING, (uint32)(&((tsCLD_BallastConfiguration*)(0))->sLampManufacturer), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_RATED_HOURS
        {E_CLD_BALLASTCONFIGURATION_ATTR_LAMP_RATED_HOURS,          (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT24,  (uint32)(&((tsCLD_BallastConfiguration*)(0))->u32LampRatedHours), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_BURN_HOURS
        {E_CLD_BALLASTCONFIGURATION_ATTR_LAMP_BURN_HOURS,           (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT24,  (uint32)(&((tsCLD_BallastConfiguration*)(0))->u32LampBurnHours), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_ALARM_MODE
        {E_CLD_BALLASTCONFIGURATION_ATTR_LAMP_ALARM_MODE,           (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_BMAP8,   (uint32)(&((tsCLD_BallastConfiguration*)(0))->u8LampAlarmMode), 0},
    #endif

    #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_BURN_HOURS_TRIP_POINT
        {E_CLD_BALLASTCONFIGURATION_ATTR_LAMP_BURN_HOURS_TRIP_POINT,(E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT24,  (uint32)(&((tsCLD_BallastConfiguration*)(0))->u32LampBurnHoursTripPoint), 0},
    #endif
#endif    
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                     (E_ZCL_AF_RD|E_ZCL_AF_GA),  E_ZCL_UINT16,  (uint32)(&((tsCLD_BallastConfiguration*)(0))->u16ClusterRevision),0},   /* Mandatory  */

};

tsZCL_ClusterDefinition sCLD_BallastConfiguration = {
        LIGHTING_CLUSTER_ID_BALLAST_CONFIGURATION,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_BallastConfigurationClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_BallastConfigurationClusterAttributeDefinitions,
        NULL
};

uint8 au8BallastConfigurationAttributeControlBits[(sizeof(asCLD_BallastConfigurationClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_BallastConfigurationCreateBallastConfiguration
 **
 ** DESCRIPTION:
 ** Creates a Ballast Configuration cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_BallastConfigurationCreateBallastConfiguration(
        tsZCL_ClusterInstance                   *psClusterInstance,
        bool_t                                  bIsServer,
        tsZCL_ClusterDefinition                 *psClusterDefinition,
        void                                    *pvEndPointSharedStructPtr,
        uint8                                   *pu8AttributeControlBits)
{

#ifdef STRICT_PARAM_CHECK
	/* Parameter check */
	if((psClusterInstance==NULL) ||
	   (psClusterDefinition==NULL))
	{
		return E_ZCL_ERR_PARAMETER_NULL;
	}
#endif

    /* Create an instance of a ballast configuration cluster */
    vZCL_InitializeClusterInstance(
                                   psClusterInstance, 
                                   bIsServer,
                                   psClusterDefinition,
                                   pvEndPointSharedStructPtr,
                                   pu8AttributeControlBits,
                                   NULL,
                                   NULL);  
    /* Set default values */
        if(pvEndPointSharedStructPtr != NULL)
        {
    #ifdef BALLAST_CONFIGURATION_SERVER            
            #ifdef CLD_BALLASTCONFIGURATION_ATTR_PHYSICAL_MIN_LEVEL
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8PhysicalMinLevel = 0x01;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_PHYSICAL_MAX_LEVEL
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8PhysicalMaxLevel = 0xfe;
            #endif

                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8BallastStatus = 0x00;

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_MIN_LEVEL
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8MinLevel = ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8PhysicalMinLevel;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_MAX_LEVEL
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8MaxLevel = ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8PhysicalMaxLevel;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_POWER_ON_LEVEL
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8PowerOnLevel = ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8PhysicalMaxLevel;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_POWER_ON_FADE_TIME
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u16PowerOnFadeTime = 0x0000;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_INTRINSIC_BALLAST_FACTOR
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_BALLAST_FACTOR_ADJUSTMENT
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8BallastFactorAdjustment = 0xff;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_QUANTITY
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_TYPE
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->sLampType.u8MaxLength = sizeof(((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->au8LampType);
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->sLampType.u8Length = 0;
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->sLampType.pu8Data = ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->au8LampType;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_MANUFACTURER
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->sLampManufacturer.u8MaxLength = sizeof(((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->au8LampManufacturer);
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->sLampManufacturer.u8Length = 0;
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->sLampManufacturer.pu8Data = ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->au8LampManufacturer;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_RATED_HOURS
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u32LampRatedHours = 0x00ffffff;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_BURN_HOURS
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u32LampBurnHours = 0x00;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_ALARM_MODE
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u8LampAlarmMode = 0x00;
            #endif

            #ifdef CLD_BALLASTCONFIGURATION_ATTR_LAMP_BURN_HOURS_TRIP_POINT
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u32LampBurnHoursTripPoint = 0x00ffffff;
            #endif
    #endif    
                ((tsCLD_BallastConfiguration*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_BALLASTCONFIGURATION_CLUSTER_REVISION;
        }
    return E_ZCL_SUCCESS;
}


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

