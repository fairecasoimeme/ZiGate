/*****************************************************************************
 *
 * MODULE:             Climax PM2.5 Measurement Cluster
 *
 * COMPONENT:          ClimaxPM25Measurement.c
 *
 * AUTHOR:             schrodingersket
 *
 * DESCRIPTION:        Climax PM2.5 cluster definition
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSEE
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
#include "zcl.h"
#include "ClimaxPM25Measurement.h"
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
const tsZCL_AttributeDefinition asCLD_ClimaxPM25MeasurementClusterAttributeDefinitions[] = {
#ifdef CLIMAX_PM25_MEASUREMENT_SERVER
        {E_CLD_CLIMAX_PM25_ATTR_ID_MEASURED_VALUE,                 (E_ZCL_AF_RD|E_ZCL_AF_RP|E_ZCL_AF_MS),      E_ZCL_INT16,    (uint32)(&((tsCLD_ClimaxPM25Measurement*)(0))->i16MeasuredValue),           0}, /* Mandatory */

        {E_CLD_CLIMAX_PM25_ATTR_ID_MIN_MEASURED_VALUE,             (E_ZCL_AF_RD|E_ZCL_AF_MS),                  E_ZCL_INT16,    (uint32)(&((tsCLD_ClimaxPM25Measurement*)(0))->i16MinMeasuredValue),        0}, /* Mandatory */

        {E_CLD_CLIMAX_PM25_ATTR_ID_MAX_MEASURED_VALUE,             (E_ZCL_AF_RD|E_ZCL_AF_MS),                  E_ZCL_INT16,    (uint32)(&((tsCLD_ClimaxPM25Measurement*)(0))->i16MaxMeasuredValue),        0}, /* Mandatory */

        #ifdef CLD_CLIMAX_PM25_ATTR_MEASURED_VALUE_AQI
            {E_CLD_CLIMAX_PM25_ATTR_ID_MEASURED_VALUE_AQI,         (E_ZCL_AF_RD|E_ZCL_AF_RP|E_ZCL_AF_MS),      E_ZCL_INT16,    (uint32)(&((tsCLD_ClimaxPM25Measurement*)(0))->i16MeasuredValueAQI),        0},
        #endif

        #ifdef CLD_CLIMAX_PM25_ATTR_STATUS
            {E_CLD_CLIMAX_PM25_ATTR_ID_STATUS,                     (E_ZCL_AF_RD|E_ZCL_AF_MS),                  E_ZCL_UINT8,    (uint32)(&((tsCLD_ClimaxPM25Measurement*)(0))->u8Status),                   0},
        #endif
  
#endif    
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                    (E_ZCL_AF_RD|E_ZCL_AF_GA|E_ZCL_AF_MS),      E_ZCL_UINT16,   (uint32)(&((tsCLD_ClimaxPM25Measurement*)(0))->u16ClusterRevision),         0},   /* Mandatory  */
        
    #if (defined CLIMAX_PM25_MEASUREMENT_SERVER) && (defined CLD_CLIMAX_PM25_MEASUREMENT_ATTR_ATTRIBUTE_REPORTING_STATUS)
        {E_CLD_GLOBAL_ATTR_ID_ATTRIBUTE_REPORTING_STATUS,          (E_ZCL_AF_RD|E_ZCL_AF_GA|E_ZCL_AF_MS),      E_ZCL_ENUM8,    (uint32)(&((tsCLD_ClimaxPM25Measurement*)(0))->u8AttributeReportingStatus), 0},  /* Optional */
    #endif      
};

tsZCL_ClusterDefinition sCLD_ClimaxPM25Measurement = {
        MEASUREMENT_AND_SENSING_CLUSTER_ID_CLIMAX_PM25_MEASUREMENT,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_ClimaxPM25MeasurementClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_ClimaxPM25MeasurementClusterAttributeDefinitions,
        NULL
};

uint8 au8ClimaxPM25MeasurementAttributeControlBits[(sizeof(asCLD_ClimaxPM25MeasurementClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 **
 ** NAME:       eCLD_ClimaxPM25MeasurementCreateClimaxPM25Measurement
 **
 ** DESCRIPTION:
 ** Creates a Climax PM2.5 measurement cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_ClimaxPM25MeasurementCreateClimaxPM25Measurement(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits)
{
    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    /* Create an instance of a Climax PM2.5 measurement cluster */
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
        #ifdef CLIMAX_PM25_MEASUREMENT_SERVER
            /* Initializing these values to invalid as ZCL spec does not mention the defualt */
            ((tsCLD_ClimaxPM25Measurement*)pvEndPointSharedStructPtr)->i16MinMeasuredValue = 0x0000;
            ((tsCLD_ClimaxPM25Measurement*)pvEndPointSharedStructPtr)->i16MaxMeasuredValue = 0x7530; // 30000
        #endif
            ((tsCLD_ClimaxPM25Measurement*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_CLIMAX_PM25_MEASUREMENT_CLUSTER_REVISION;
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

