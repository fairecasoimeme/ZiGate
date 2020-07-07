/*****************************************************************************
 *
 * MODULE:             Climax CO2 Concentration Cluster
 *
 * COMPONENT:          ClimaxCO2Concentration.h
 *
 * AUTHOR:             schrodingersket
 *
 * DESCRIPTION:        Header for Climax CO2 Concentration Cluster
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

#ifndef CLIMAX_CO2_CONCENTRATION_H
#define CLIMAX_CO2_CONCENTRATION_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef CLD_CLIMAX_CO2_CONCENTRATION_CLUSTER_REVISION
    #define CLD_CLIMAX_CO2_CONCENTRATION_CLUSTER_REVISION        1
#endif

/****************************************************************************/
/*      Climax CO2 Concentration Cluster - Optional Attributes              */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the Climax CO2 concentration cluster.                      */
/****************************************************************************/

/* Enable the optional Tolerance attribute */
//#define CLD_CLIMAX_CO2_CONCENTRATION_ATTR_TOLERANCE

/* End of optional attributes */

/* Cluster IDs */
#define MEASUREMENT_AND_SENSING_CLUSTER_ID_CLIMAX_CO2_CONCENTRATION  0xFC01


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* CO2 Concentration Information attribute set attribute IDs */
    E_CLD_CLIMAX_CO2_CONCENTRATION_ATTR_ID_MEASURED_VALUE          = 0x0000,  /* Mandatory */
    E_CLD_CLIMAX_CO2_CONCENTRATION_ATTR_ID_MIN_MEASURED_VALUE,                /* Mandatory */
    E_CLD_CLIMAX_CO2_CONCENTRATION_ATTR_ID_MAX_MEASURED_VALUE,                /* Mandatory */
    E_CLD_CLIMAX_CO2_CONCENTRATION_ATTR_ID_TOLERANCE,
} teCLD_ClimaxCO2Concentration_AttributeID;

/* CO2 Concentration Cluster */
typedef struct
{
#ifdef CLIMAX_CO2_CONCENTRATION_SERVER
    zint16                 i16MeasuredValue;

    zint16                 i16MinMeasuredValue;

    zint16                 i16MaxMeasuredValue;

#ifdef CLD_CLIMAX_CO2_CONCENTRATION_ATTR_TOLERANCE
    zuint16                u16Tolerance;
#endif

#ifdef CLD_CLIMAX_CO2_CONCENTRATION_ATTR_ATTRIBUTE_REPORTING_STATUS
    zenum8                 u8AttributeReportingStatus;
#endif

#endif
    zuint16                u16ClusterRevision;
    
} tsCLD_ClimaxCO2Concentration;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_ClimaxCO2ConcentrationCreateClimaxCO2Concentration(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern const tsZCL_AttributeDefinition asCLD_ClimaxCO2ConcentrationClusterAttributeDefinitions[];
extern tsZCL_ClusterDefinition sCLD_ClimaxCO2Concentration;
extern uint8 au8ClimaxCO2ConcentrationAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* CLIMAX_CO2_CONCENTRATION_H */
