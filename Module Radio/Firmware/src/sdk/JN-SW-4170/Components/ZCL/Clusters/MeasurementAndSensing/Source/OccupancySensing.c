/*****************************************************************************
 *
 * MODULE:             Occupancy Sensing Cluster
 *
 * COMPONENT:          OccupancySensingMeasurement.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Occupancy Sensing cluster definition
 *
 * $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Clusters/MeasurementAndSensing/Source/OccupancySensing.c $
 *
 * $Revision: 21151 $
 *
 * $LastChangedBy: lmitch $
 *
 * $LastChangedDate: 2009-10-27 10:26:55 +0000 (Tue, 27 Oct 2009) $
 *
 * $Id: OccupancySensing.c 21151 2009-10-27 10:26:55Z lmitch $
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
#include "zcl.h"
#include "OccupancySensing.h"
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
const tsZCL_AttributeDefinition asCLD_OccupancySensingClusterAttributeDefinitions[] = {
#ifdef OCCUPANCY_SENSING_SERVER
        {E_CLD_OS_ATTR_ID_OCCUPANCY,                                    (E_ZCL_AF_RD|E_ZCL_AF_RP),  E_ZCL_BMAP8,    (uint32)(&((tsCLD_OccupancySensing*)(0))->u8Occupancy), 0},            /* Mandatory */

        {E_CLD_OS_ATTR_ID_OCCUPANCY_SENSOR_TYPE,                        E_ZCL_AF_RD,                    E_ZCL_ENUM8,    (uint32)(&((tsCLD_OccupancySensing*)(0))->eOccupancySensorType), 0},   /* Mandatory */

    #ifdef CLD_OS_ATTR_PIR_OCCUPIED_TO_UNOCCUPIED_DELAY
        {E_CLD_OS_ATTR_ID_PIR_OCCUPIED_TO_UNOCCUPIED_DELAY,             (E_ZCL_AF_RD|E_ZCL_AF_WR),      E_ZCL_UINT16,   (uint32)(&((tsCLD_OccupancySensing*)(0))->u16PIROccupiedToUnoccupiedDelay), 0},
    #endif

    #ifdef CLD_OS_ATTR_PIR_UNOCCUPIED_TO_OCCUPIED_DELAY
        {E_CLD_OS_ATTR_ID_PIR_UNOCCUPIED_TO_OCCUPIED_DELAY,             (E_ZCL_AF_RD|E_ZCL_AF_WR),      E_ZCL_UINT8,    (uint32)(&((tsCLD_OccupancySensing*)(0))->u8PIRUnoccupiedToOccupiedDelay), 0},
    #endif

    #ifdef CLD_OS_ATTR_PIR_UNOCCUPIED_TO_OCCUPIED_THRESHOLD
        {E_CLD_OS_ATTR_ID_PIR_UNOCCUPIED_TO_OCCUPIED_THRESHOLD,         (E_ZCL_AF_RD|E_ZCL_AF_WR),      E_ZCL_UINT8,    (uint32)(&((tsCLD_OccupancySensing*)(0))->u8PIRUnoccupiedToOccupiedThreshold), 0},
    #endif

    #ifdef CLD_OS_ATTR_ULTRASONIC_OCCUPIED_TO_UNOCCUPIED_DELAY
        {E_CLD_OS_ATTR_ID_ULTRASONIC_OCCUPIED_TO_UNOCCUPIED_DELAY,      (E_ZCL_AF_RD|E_ZCL_AF_WR),      E_ZCL_UINT16,   (uint32)(&((tsCLD_OccupancySensing*)(0))->u16UltrasonicOccupiedToUnoccupiedDelay), 0},
    #endif

    #ifdef CLD_OS_ATTR_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_DELAY
        {E_CLD_OS_ATTR_ID_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_DELAY,      (E_ZCL_AF_RD|E_ZCL_AF_WR),      E_ZCL_UINT8,    (uint32)(&((tsCLD_OccupancySensing*)(0))->u8UltrasonicUnoccupiedToOccupiedDelay), 0},
    #endif

    #ifdef CLD_OS_ATTR_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_THRESHOLD
        {E_CLD_OS_ATTR_ID_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_THRESHOLD,  (E_ZCL_AF_RD|E_ZCL_AF_WR),      E_ZCL_UINT8,    (uint32)(&((tsCLD_OccupancySensing*)(0))->u8UltrasonicUnoccupiedToOccupiedThreshold), 0},
    #endif

#endif    
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                        (E_ZCL_AF_RD|E_ZCL_AF_GA),      E_ZCL_UINT16,   (uint32)(&((tsCLD_OccupancySensing*)(0))->u16ClusterRevision),  0},   /* Mandatory  */

    #if (defined OCCUPANCY_SENSING_SERVER) && (defined CLD_OS_ATTR_ATTRIBUTE_REPORTING_STATUS)
        {E_CLD_GLOBAL_ATTR_ID_ATTRIBUTE_REPORTING_STATUS,              (E_ZCL_AF_RD|E_ZCL_AF_GA),      E_ZCL_ENUM8,    (uint32)(&((tsCLD_OccupancySensing*)(0))->u8AttributeReportingStatus), 0},  /* Optional */
    #endif
};

tsZCL_ClusterDefinition sCLD_OccupancySensing = {
        MEASUREMENT_AND_SENSING_CLUSTER_ID_OCCUPANCY_SENSING,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_OccupancySensingClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_OccupancySensingClusterAttributeDefinitions,
        NULL
};
uint8 au8OccupancySensingAttributeControlBits[(sizeof(asCLD_OccupancySensingClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 **
 ** NAME:       eCLD_OccupancySensingCreateOccupancySensing
 **
 ** DESCRIPTION:
 ** Creates an occupancy sensing cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_OccupancySensingCreateOccupancySensing(
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
        #ifdef OCCUPANCY_SENSING_SERVER         
            #ifdef CLD_OS_ATTR_PIR_UNOCCUPIED_TO_OCCUPIED_THRESHOLD
                ((tsCLD_OccupancySensing*)pvEndPointSharedStructPtr)->u8PIRUnoccupiedToOccupiedThreshold        = 0x1;
            #endif
            #ifdef CLD_OS_ATTR_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_THRESHOLD
                ((tsCLD_OccupancySensing*)pvEndPointSharedStructPtr)->u8UltrasonicUnoccupiedToOccupiedThreshold = 0x1;
            #endif
        #endif    
                ((tsCLD_OccupancySensing*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_OS_CLUSTER_REVISION;
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

