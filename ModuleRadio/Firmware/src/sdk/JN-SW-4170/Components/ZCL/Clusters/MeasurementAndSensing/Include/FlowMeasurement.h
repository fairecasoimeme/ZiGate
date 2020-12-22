/*****************************************************************************
 *
 * MODULE:             Flow Measurement Cluster
 *
 * COMPONENT:          FlowMeasurement.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Flow Measurement Cluster
 *
 * $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Clusters/MeasurementAndSensing/Include/FlowMeasurement.h $
 *
 * $Revision: 15651 $
 *
 * $LastChangedBy: dgave $
 *
 * $LastChangedDate: 2009-07-02 12:56:52 +0100 (Thu, 02 Jul 2009) $
 *
 * $Id: FlowMeasurement.h 15651 2009-07-02 11:56:52Z dgave $
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

#ifndef FLOW_MEASUREMENT_H
#define FLOW_MEASUREMENT_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef CLD_FLOWMEAS_CLUSTER_REVISION
    #define CLD_FLOWMEAS_CLUSTER_REVISION        1
#endif 
/****************************************************************************/
/*          Flow Measurement Cluster - Optional Attributes                  */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the Flow measurement cluster.                       */
/****************************************************************************/

/* Enable the optional Tolerance attribute */
//#define CLD_FLOWMEAS_ATTR_TOLERANCE

/* Enable the optional Attribute Reporting Status attribute */
//#define CLD_FLOWMEAS_ATTR_ATTRIBUTE_REPORTING_STATUS

/* End of optional attributes */


/* Cluster ID's */
#define MEASUREMENT_AND_SENSING_CLUSTER_ID_FLOW_MEASUREMENT  0x0404


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* Flow Measurement Information attribute set attribute ID's (4.6.2.2.1) */
    E_CLD_FLOWMEAS_ATTR_ID_MEASURED_VALUE               = 0x0000,   /* Mandatory */
    E_CLD_FLOWMEAS_ATTR_ID_MIN_MEASURED_VALUE,                      /* Mandatory */
    E_CLD_FLOWMEAS_ATTR_ID_MAX_MEASURED_VALUE,                      /* Mandatory */
    E_CLD_FLOWMEAS_ATTR_ID_TOLERANCE,
} teCLD_FlowMeasurement_AttributeID;

/* Flow Measurement Cluster */
typedef struct
{
#ifdef FLOW_MEASUREMENT_SERVER    
    zint16                 i16MeasuredValue;

    zint16                 i16MinMeasuredValue;

    zint16                 i16MaxMeasuredValue;

#ifdef CLD_FLOWMEAS_ATTR_TOLERANCE
    zuint16                u16Tolerance;
#endif

#ifdef CLD_FLOWMEAS_ATTR_ATTRIBUTE_REPORTING_STATUS
    zenum8                 u8AttributeReportingStatus;
#endif
#endif
    zuint16                u16ClusterRevision;
   
} tsCLD_FlowMeasurement;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_FlowMeasurementCreateFlowMeasurement(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_FlowMeasurement;
extern uint8 au8FlowMeasurementAttributeControlBits[];
extern const tsZCL_AttributeDefinition asCLD_FlowMeasurementClusterAttributeDefinitions[];
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* FLOW_MEASUREMENT_H */
