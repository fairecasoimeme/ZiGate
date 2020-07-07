/*****************************************************************************
 *
 * MODULE:             Develco Volatile Organic Compounds (VOC) Measurement Cluster
 *
 * COMPONENT:          VOCMeasurement.h
 *
 * AUTHOR:             schrodingersket
 *
 * DESCRIPTION:        Header for Develco VOC Measurement Cluster
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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

/* Cluster IDs */
#define MEASUREMENT_AND_SENSING_CLUSTER_ID_DEVELCO_VOC_MEASUREMENT  0xFC03


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* Develco VOC Measurement Information attribute set attribute IDs (https://www.develcoproducts.com/media/1674/aqszb-110-technical-manual-air-quality-sensor.pdf) */
    E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_MEASURED_VALUE          = 0x0000,  /* Mandatory */
    E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_MIN_MEASURED_VALUE,                /* Mandatory */
    E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_MAX_MEASURED_VALUE,                /* Mandatory */
    E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_RESOLUTION,                        /* Mandatory */
} teCLD_DVOCM_ClusterID;


/* Develco VOC Measurement Cluster */
typedef struct
{
#ifdef DEVELCO_VOC_MEASUREMENT_SERVER
    zuint16                u16MeasuredValue;

    zuint16                u16MinMeasuredValue;

    zuint16                u16MaxMeasuredValue;

    zuint16                u16Resolution;
#endif

    zuint16                u16ClusterRevision;

#ifdef CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ATTRIBUTE_REPORTING_STATUS
    zenum8                 u8AttributeReportingStatus;
#endif
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
extern tsZCL_ClusterDefinition sCLD_DevelcoVOCMeasurement;
extern uint8 au8DevelcoVOCMeasurementAttributeControlBits[];
extern const tsZCL_AttributeDefinition asCLD_DevelcoVOCMeasurementClusterAttributeDefinitions[];
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* DEVELCO_VOC_MEASUREMENT_H */
