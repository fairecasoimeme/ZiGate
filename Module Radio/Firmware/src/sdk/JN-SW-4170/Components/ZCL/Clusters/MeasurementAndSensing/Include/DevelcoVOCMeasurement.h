/*****************************************************************************
 *
 * MODULE:             Develco VOC Measurement Cluster
 *
 * COMPONENT:          DevelcoVOCMeasurement.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Develco VOC Measurement Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/MeasurementAndSensing/Include/DevelcoVOCMeasurement.h $
 *
 * $Revision: 72591 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2020-05-05 14:41:01 +0200 (Tue, 05 May 2020) $
 *
 * $Id: DevelcoVOCMeasurement.h 72591 2020-05-05 12:41:01Z nxp57621 $
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

#ifndef DEVELCO_VOC_MEASUREMENT_H
#define DEVELCO_VOC_MEASUREMENT_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef CLD_DEVELCO_VOC_MEASUREMENT_CLUSTER_REVISION
    #define CLD_DEVELCO_VOC_MEASUREMENT_CLUSTER_REVISION        1
#endif
/********************************************************************************************************/
/*      Develco Volatile Organic Compounds (VOC) Measurement Cluster - Optional Attributes              */
/*                                                                                                      */
/* Add the following #define's to your zcl_options.h file to add optional                               */
/* attributes to the Develco VOC measurement cluster.                                                   */
/********************************************************************************************************/

/* Enable the optional Tolerance attribute */
//#define CLD_DEVELCO_VOC_MEASUREMENT_ATTR_TOLERANCE

/* Enable the optional Attribute Reporting Status attribute */
//#define CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ATTRIBUTE_REPORTING_STATUS

/* End of optional attributes */


/* Cluster ID's */
#define MEASUREMENT_AND_SENSING_CLUSTER_ID_DEVELCO_VOC_MEASUREMENT  0xfc03


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* VOC Measurement Information attribute set attribute ID's (4.4.2.2.1) */
    E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_MEASURED_VALUE          = 0x0000,  /* Mandatory */
    E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_MIN_MEASURED_VALUE,                /* Mandatory */
    E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_MAX_MEASURED_VALUE,                /* Mandatory */
    E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_TOLERANCE,
} teCLD_DevelcoVOCMeasurement_AttributeID;

/* VOC Measurement Cluster */
typedef struct
{
#ifdef DEVELCO_VOC_MEASUREMENT_SERVER
    zint16                 i16MeasuredValue;

    zint16                 i16MinMeasuredValue;

    zint16                 i16MaxMeasuredValue;

#ifdef CLD_DEVELCO_VOC_MEASUREMENT_ATTR_TOLERANCE
    zuint16                u16Tolerance;
#endif

#ifdef CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ATTRIBUTE_REPORTING_STATUS
    zenum8                 u8AttributeReportingStatus;
#endif
#endif
    zuint16                u16ClusterRevision;
    
} tsCLD_DevelcoVOCMeasurement;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_DevelcoVOCMeasurementCreateDevelcoVOCMeasurement(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern const tsZCL_AttributeDefinition asCLD_DevelcoVOCMeasurementClusterAttributeDefinitions[];
extern tsZCL_ClusterDefinition sCLD_DevelcoVOCMeasurement;
extern uint8 au8DevelcoVOCMeasurementAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* DEVELCO_VOC_MEASUREMENT_H */
