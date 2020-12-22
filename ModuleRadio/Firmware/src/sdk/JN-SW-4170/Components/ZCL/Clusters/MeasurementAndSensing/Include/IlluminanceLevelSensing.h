/*****************************************************************************
 *
 * MODULE:             Illuminance Level Sensing Cluster
 *
 * COMPONENT:          IlluminanceLevelSensing.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Illuminance Level Sensing Cluster
 *
 * $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Clusters/MeasurementAndSensing/Include/IlluminanceLevelSensing.h $
 *
 * $Revision: 15651 $
 *
 * $LastChangedBy: dgave $
 *
 * $LastChangedDate: 2009-07-02 12:56:52 +0100 (Thu, 02 Jul 2009) $
 *
 * $Id: IlluminanceLevelSensing.h 15651 2009-07-02 11:56:52Z dgave $
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

#ifndef ILLUMINANCE_LEVEL_SENSING_H
#define ILLUMINANCE_LEVEL_SENSING_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef CLD_ILS_CLUSTER_REVISION
    #define CLD_ILS_CLUSTER_REVISION        1
#endif
/****************************************************************************/
/*           Illuminance Level Sensing Cluster - Optional Attributes        */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the illuminance Level Sensing cluster.                     */
/****************************************************************************/

/* Enable the optional Light Sensor Type attribute */
//#define CLD_ILS_ATTR_LIGHT_SENSOR_TYPE

/* Enable the optional Attribute Reporting Status attribute */
//#define CLD_ILS_ATTR_ATTRIBUTE_REPORTING_STATUS

/* End of optional attributes */


/* Cluster ID's */
#define MEASUREMENT_AND_SENSING_CLUSTER_ID_ILLUMINANCE_LEVEL_SENSING  0x0401


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* Illuminance Level Sensing Information attribute set attribute ID's (4.3.2.3) */
    E_CLD_ILS_ATTR_ID_LEVEL_STATUS              = 0x0000,  /* Mandatory */
    E_CLD_ILS_ATTR_ID_LIGHT_SENSOR_TYPE,

    /* Illuminance Level Sensing Settings attribute set attribute ID's (4.3.2.4) */
    E_CLD_ILS_ATTR_ID_ILLUMINANCE_TARGET_LEVEL  = 0x0010,  /* Mandatory */
} teCLD_ILS_ClusterID;


/* Light sensor types */
typedef enum 
{
    E_CLD_ILS_LST_PHOTODIODE = 0,
    E_CLD_ILS_LST_CMOS
} teCLD_ILS_LightSensorType;


/* Light level status */
typedef enum 
{
    E_CLD_ILS_LLS_ON_TARGET,
    E_CLD_ILS_LLS_BELOW_TARGET,
    E_CLD_ILS_LLS_ABOVE_TARGET,
} teCLD_ILS_LightLevelStatus;


/* Illuminance Level Sensing Cluster */
typedef struct
{
#ifdef ILLUMINANCE_LEVEL_SENSING_SERVER    
    zenum8      u8LevelStatus;

#ifdef CLD_ILS_ATTR_LIGHT_SENSOR_TYPE
    zenum8      eLightSensorType;
#endif

    zuint16     u16IlluminanceTargetLevel;
    
#ifdef CLD_ILS_ATTR_ATTRIBUTE_REPORTING_STATUS
    zenum8      u8AttributeReportingStatus;
#endif
#endif
 
    zuint16     u16ClusterRevision;    
} tsCLD_IlluminanceLevelSensing;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_IlluminanceLevelSensingCreateIlluminanceLevelSensing(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_IlluminanceLevelSensing;
extern uint8 au8IlluminanceLevelSensingAttributeControlBits[];
extern const tsZCL_AttributeDefinition asCLD_IlluminanceLevelSensingClusterAttributeDefinitions[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* ILLUMINANCE_LEVEL_SENSING_H */
