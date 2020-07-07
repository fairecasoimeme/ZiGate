/*****************************************************************************
 *
 * MODULE:             Develco VOC Measurement Cluster
 *
 * COMPONENT:          DevelcoVOCMeasurement.c
 *
 * AUTHOR:             schrodingersket
 *
 * DESCRIPTION:        Develco Volatile Organic Compounds (VOC) Measurement cluster definition
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPDEVELCO_VOC_MEASUREMENTE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LDEVELCO_VOC_MEASUREMENTS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * PDEVELCO_VOC_MEASUREMENTSIBILITY OF SUCH DAMAGE.
 *
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "zcl.h"
#include "DevelcoVOCMeasurement.h"
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
const tsZCL_AttributeDefinition asCLD_DevelcoVOCMeasurementClusterAttributeDefinitions[] = {
#ifdef DEVELCO_VOC_MEASUREMENT_SERVER
        {E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_MEASURED_VALUE,               (E_ZCL_AF_RD|E_ZCL_AF_RP|E_ZCL_AF_MS),        E_ZCL_UINT16,  (uint32)(&((tsCLD_DevelcoVOCMeasurement*)(0))->u16MeasuredValue),    0}, /* Mandatory */

        {E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_MIN_MEASURED_VALUE,           (E_ZCL_AF_RD|E_ZCL_AF_MS),                    E_ZCL_UINT16,  (uint32)(&((tsCLD_DevelcoVOCMeasurement*)(0))->u16MinMeasuredValue), 0}, /* Mandatory */

        {E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_MAX_MEASURED_VALUE,           (E_ZCL_AF_RD|E_ZCL_AF_MS),                    E_ZCL_UINT16,  (uint32)(&((tsCLD_DevelcoVOCMeasurement*)(0))->u16MaxMeasuredValue), 0}, /* Mandatory */


        {E_CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ID_RESOLUTION,                   (E_ZCL_AF_RD|E_ZCL_AF_RP|E_ZCL_AF_MS),        E_ZCL_UINT16,  (uint32)(&((tsCLD_DevelcoVOCMeasurement*)(0))->u16Tolerance),        0}, /* Mandatory */

#endif    
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                              (E_ZCL_AF_RD|E_ZCL_AF_GA|E_ZCL_AF_MS),        E_ZCL_UINT16,  (uint32)(&((tsCLD_DevelcoVOCMeasurement*)(0))->u16ClusterRevision),  0}, /* Mandatory  */

#if (defined DEVELCO_VOC_MEASUREMENT_SERVER) && (defined CLD_DEVELCO_VOC_MEASUREMENT_ATTR_ATTRIBUTE_REPORTING_STATUS)
    {E_CLD_GLOBAL_ATTR_ID_ATTRIBUTE_REPORTING_STATUS,      (E_ZCL_AF_RD|E_ZCL_AF_GA|E_ZCL_AF_MS),      E_ZCL_ENUM8,    (uint32)(&((tsCLD_DevelcoVOCMeasurement*)(0))->u8AttributeReportingStatus), 0},  /* Optional */
#endif
};

tsZCL_ClusterDefinition sCLD_DevelcoVOCMeasurement = {
        MEASUREMENT_AND_SENSING_CLUSTER_ID_DEVELCO_VOC_MEASUREMENT,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_DevelcoVOCMeasurementClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_DevelcoVOCMeasurementClusterAttributeDefinitions,
        NULL
};

uint8 au8DevelcoVOCMeasurementAttributeControlBits[(sizeof(asCLD_DevelcoVOCMeasurementClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 **
 ** NAME:       eCLD_DevelcoVOCMeasurementCreateDevelcoVOCMeasurement
 **
 ** DESCRIPTION:
 ** Creates a Develco VOC measurement cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance       *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_DevelcoVOCMeasurementCreateDevelcoVOCMeasurement(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits)
{
    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance == NULL) ||
           (psClusterDefinition == NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif


    /* Create an instance of a Develco VOC cluster */
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
        #ifdef DEVELCO_VOC_MEASUREMENT_SERVER
            /* Initializing these values to invalid as ZCL spec does not mention the defualt */
            ((tsCLD_DevelcoVOCMeasurement*)pvEndPointSharedStructPtr)->u16MinMeasuredValue = 0xFFFF;
            ((tsCLD_DevelcoVOCMeasurement*)pvEndPointSharedStructPtr)->u16MaxMeasuredValue = 0xFFFF;
        #endif
            ((tsCLD_DevelcoVOCMeasurement*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_DEVELCO_VOC_MEASUREMENT_CLUSTER_REVISION;
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

