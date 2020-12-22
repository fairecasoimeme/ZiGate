/*****************************************************************************
 *
 * MODULE:             Pressure Measurement Cluster
 *
 * COMPONENT:          PressureMeasurement.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Pressure Measurement cluster definition
 *
 * $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Clusters/MeasurementAndSensing/Source/PressureMeasurement.c $
 *
 * $Revision: 21150 $
 *
 * $LastChangedBy: lmitch $
 *
 * $LastChangedDate: 2009-10-27 10:12:41 +0000 (Tue, 27 Oct 2009) $
 *
 * $Id: PressureMeasurement.c 21150 2009-10-27 10:12:41Z lmitch $
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPPRESSUREMEASE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LPRESSUREMEASS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * PPRESSUREMEASSIBILITY OF SUCH DAMAGE.
 *
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "zcl.h"
#include "PressureMeasurement.h"
#include "zcl_customcommand.h"
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
const tsZCL_AttributeDefinition asCLD_PressureMeasurementClusterAttributeDefinitions[] = {
#ifdef PRESSURE_MEASUREMENT_SERVER
        {E_CLD_PRESSUREMEAS_ATTR_ID_MEASURED_VALUE,                 (E_ZCL_AF_RD|E_ZCL_AF_RP),  E_ZCL_INT16,    (uint32)(&((tsCLD_PressureMeasurement*)(0))->i16MeasuredValue), 0},   /* Mandatory */

        {E_CLD_PRESSUREMEAS_ATTR_ID_MIN_MEASURED_VALUE,             E_ZCL_AF_RD,                E_ZCL_INT16,    (uint32)(&((tsCLD_PressureMeasurement*)(0))->i16MinMeasuredValue), 0},/* Mandatory */

        {E_CLD_PRESSUREMEAS_ATTR_ID_MAX_MEASURED_VALUE,             E_ZCL_AF_RD,                E_ZCL_INT16,    (uint32)(&((tsCLD_PressureMeasurement*)(0))->i16MaxMeasuredValue), 0},/* Mandatory */

        #ifdef CLD_PRESSUREMEAS_ATTR_TOLERANCE
            {E_CLD_PRESSUREMEAS_ATTR_ID_TOLERANCE,                  (E_ZCL_AF_RD|E_ZCL_AF_RP),  E_ZCL_UINT16,   (uint32)(&((tsCLD_PressureMeasurement*)(0))->u16Tolerance), 0},
        #endif

#endif        
            {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                 (E_ZCL_AF_RD|E_ZCL_AF_GA), E_ZCL_UINT16,   (uint32)(&((tsCLD_PressureMeasurement*)(0))->u16ClusterRevision),  0},   /* Mandatory  */
        
        #if (defined PRESSURE_MEASUREMENT_SERVER) && (defined CLD_PRESSUREMEAS_ATTR_ATTRIBUTE_REPORTING_STATUS)
            {E_CLD_GLOBAL_ATTR_ID_ATTRIBUTE_REPORTING_STATUS,       (E_ZCL_AF_RD|E_ZCL_AF_GA), E_ZCL_ENUM8,    (uint32)(&((tsCLD_PressureMeasurement*)(0))->u8AttributeReportingStatus), 0},  /* Optional */
        #endif
};

tsZCL_ClusterDefinition sCLD_PressureMeasurement = {
        MEASUREMENT_AND_SENSING_CLUSTER_ID_PRESSURE_MEASUREMENT,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_PressureMeasurementClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_PressureMeasurementClusterAttributeDefinitions,
        NULL
};

uint8 au8PressureMeasurementAttributeControlBits[(sizeof(asCLD_PressureMeasurementClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 **
 ** NAME:       eCLD_PressureMeasurementCreatePressureMeasurement
 **
 ** DESCRIPTION:
 ** Creates a Pressure measurement cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_PressureMeasurementCreatePressureMeasurement(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits)
{


    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL) )
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    /* Create an instance of a temperature measurement cluster */
    vZCL_InitializeClusterInstance(
                                   psClusterInstance, 
                                   bIsServer,
                                   psClusterDefinition,
                                   pvEndPointSharedStructPtr,
                                   pu8AttributeControlBits,
                                   NULL,
                                   NULL); 

                                  
    if(pvEndPointSharedStructPtr != NULL)
    {
        /* Initializing default values  to attributes */
        ((tsCLD_PressureMeasurement*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_PRESSUREMEAS_CLUSTER_REVISION;
    }
    
    /* As this cluster has reportable attributes enable default reporting */
    vZCL_SetDefaultReporting(psClusterInstance);
    
    return E_ZCL_SUCCESS;
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

