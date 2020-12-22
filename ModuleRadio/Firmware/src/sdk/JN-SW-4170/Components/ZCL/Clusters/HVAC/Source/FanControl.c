/*****************************************************************************
 *
 * MODULE:             Fan Control Cluster
 *
 * COMPONENT:          FanControl.c
 *
 * DESCRIPTION:        Fan Control Cluster Definition
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
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
 * Copyright NXP B.V. 2016. All rights reserved
 *
 ***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "zcl.h"
#include "FanControl.h"
#include "zcl_options.h"

#ifdef CLD_FAN_CONTROL

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
const tsZCL_AttributeDefinition asCLD_FanControlClusterAttributeDefinitions[] = {
#ifdef FAN_CONTROL_SERVER
    {E_CLD_FAN_CONTROL_ATTR_ID_FAN_MODE,          (E_ZCL_AF_RD|E_ZCL_AF_WR), E_ZCL_ENUM8,  (uint32)(&((tsCLD_FanControl*)(0))->e8FanMode), 0},          /* Mandatory */

    {E_CLD_FAN_CONTROL_ATTR_ID_FAN_MODE_SEQUENCE, (E_ZCL_AF_RD|E_ZCL_AF_WR), E_ZCL_ENUM8,  (uint32)(&((tsCLD_FanControl*)(0))->e8FanModeSequence), 0},  /* Mandatory */
#endif
    {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,       (E_ZCL_AF_RD|E_ZCL_AF_GA), E_ZCL_UINT16, (uint32)(&((tsCLD_FanControl*)(0))->u16ClusterRevision),0},   /* Mandatory  */
};

tsZCL_ClusterDefinition sCLD_FanControl = {
        HVAC_CLUSTER_ID_FAN_CONTROL,        // ClusterId
        FALSE,                              // bIsManufacturerSpecificCluster
        E_ZCL_SECURITY_NETWORK,             // Lower Nibble - SecurityInfo; Upper Nibble - ClusterType
        (sizeof(asCLD_FanControlClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),  // Number of Attributes
        (tsZCL_AttributeDefinition*)asCLD_FanControlClusterAttributeDefinitions,
        NULL                                // Pointer to SceneExtensionTable, if any
};

uint8 au8FanControlClusterAttributeControlBits[(sizeof(asCLD_FanControlClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 **
 ** NAME:       eCLD_CreateFanControl
 **
 ** DESCRIPTION:
 ** Creates a time cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_CreateFanControl(
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

    /* Create an instance of a Fan Control cluster */
    vZCL_InitializeClusterInstance(
                                   psClusterInstance, 
                                   bIsServer,
                                   psClusterDefinition,
                                   pvEndPointSharedStructPtr,
                                   pu8AttributeControlBits,
                                   NULL,
                                   NULL);    

    /* Initialise attributes defaults */
    if(pvEndPointSharedStructPtr != NULL)
    {
        #ifdef FAN_CONTROL_SERVER  
            ((tsCLD_FanControl*)pvEndPointSharedStructPtr)->e8FanMode = 0x05;           // Auto as per 6.4.2.2
            ((tsCLD_FanControl*)pvEndPointSharedStructPtr)->e8FanModeSequence = 0x02;   // as per 6.4.2.2
        #endif

        ((tsCLD_FanControl*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_FAN_CONTROL_CLUSTER_REVISION;
    }
    return E_ZCL_SUCCESS;

}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

