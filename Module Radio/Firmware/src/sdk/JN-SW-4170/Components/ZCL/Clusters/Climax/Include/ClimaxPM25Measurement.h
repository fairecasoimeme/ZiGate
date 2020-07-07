/*****************************************************************************
 *
 * MODULE:             Climax PM2.5 Measurement Cluster
 *
 * COMPONENT:          ClimaxPM25Measurement.h
 *
 * AUTHOR:             schrodingersket
 *
 * DESCRIPTION:        Header for Climax PM2.5 Cluster
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

#ifndef CLIMAX_PM25_MEASUREMENT_H
#define CLIMAX_PM25_MEASUREMENT_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef CLD_CLIMAX_PM25_MEASUREMENT_CLUSTER_REVISION
    #define CLD_CLIMAX_PM25_MEASUREMENT_CLUSTER_REVISION        1
#endif
/****************************************************************************/
/*       PM2.5 Measurement Cluster - Optional Attributes                    */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the Climax PM2.5 measurement cluster.                      */
/****************************************************************************/

/* Enable the optional Measured Value Air Quality Index (AQI) attribute */
//#define CLD_CLIMAX_PM25_MEASUREMENT_ATTR_MEASURED_VALUE_AQI

/* Enable the optional Attribute Reporting Status attribute */
//#define CLD_CLIMAX_PM25_MEASUREMENT_ATTR_STATUS

/* End of optional attributes */


/* Cluster ID's */
#define MEASUREMENT_AND_SENSING_CLUSTER_ID_CLIMAX_PM25_MEASUREMENT  0xFC02


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* Climax PM2.5 Information attribute set attribute IDs */
    E_CLD_CLIMAX_PM25_MEASUREMENT_ATTR_ID_MEASURED_VALUE          = 0x0000,  /* Mandatory */
    E_CLD_CLIMAX_PM25_MEASUREMENT_ATTR_ID_MIN_MEASURED_VALUE      = 0x0001,  /* Mandatory */
    E_CLD_CLIMAX_PM25_MEASUREMENT_ATTR_ID_MAX_MEASURED_VALUE      = 0x0002,  /* Mandatory */
    E_CLD_CLIMAX_PM25_MEASUREMENT_ATTR_ID_MEASURED_VALUE_AQI      = 0x0004,
    E_CLD_CLIMAX_PM25_MEASUREMENT_ATTR_ID_STATUS                  = 0x0005,
} teCLD_ClimaxPM25_AttributeID;

/* PM2.5 Measurement Cluster */
typedef struct
{
#ifdef CLIMAX_PM25_MEASUREMENT_SERVER
    zint16                 i16MeasuredValue;

    zint16                 i16MinMeasuredValue;

    zint16                 i16MaxMeasuredValue;

#ifdef CLD_CLIMAX_PM25_MEASUREMENT_ATTR_MEASURED_VALUE_AQI
    zint16                 i16MeasuredValueAQI;
#endif

#ifdef CLD_CLIMAX_PM25_MEASUREMENT_ATTR_STATUS
    zuint8                 u8Status;
#endif
#endif
    zuint16                u16ClusterRevision;
    
#ifdef CLD_CLIMAX_PM25_MEASUREMENT_ATTR_ATTRIBUTE_REPORTING_STATUS
    zenum8                 u8AttributeReportingStatus;
#endif

} tsCLD_ClimaxPM25Measurement;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_ClimaxPM25MeasurementCreateClimaxPM25Measurement(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern const tsZCL_AttributeDefinition asCLD_ClimaxPM25MeasurementClusterAttributeDefinitions[];
extern tsZCL_ClusterDefinition sCLD_ClimaxPM25Measurement;
extern uint8 au8ClimaxPM25MeasurementAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* CLIMAX_PM25_MEASUREMENT_H */
