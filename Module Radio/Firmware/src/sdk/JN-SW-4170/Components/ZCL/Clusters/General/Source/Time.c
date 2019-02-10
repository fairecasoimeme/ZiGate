/*****************************************************************************
 *
 * MODULE:             Time Cluster
 *
 * COMPONENT:          Time.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Time cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/Time.c $
 *
 * $Revision: 72591 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-09-08 14:41:01 +0200 (Tue, 08 Sep 2015) $
 *
 * $Id: Time.c 72591 2015-09-08 12:41:01Z nxp57621 $
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
#include "Time.h"
#include "zcl_options.h"

#ifdef CLD_TIME

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
const tsZCL_AttributeDefinition asCLD_TimeClusterAttributeDefinitions[] = {
#ifdef TIME_SERVER
        {E_CLD_TIME_ATTR_ID_TIME,           (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UTCT,     (uint32)(&((tsCLD_Time*)(0))->utctTime),0},     /* Mandatory */

        {E_CLD_TIME_ATTR_ID_TIME_STATUS,    (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_BMAP8,    (uint32)(&((tsCLD_Time*)(0))->u8TimeStatus),0}, /* Mandatory */

    #ifdef CLD_TIME_ATTR_TIME_ZONE
        {E_CLD_TIME_ATTR_ID_TIME_ZONE,      (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_INT32,    (uint32)(&((tsCLD_Time*)(0))->i32TimeZone),0},
    #endif

    #ifdef CLD_TIME_ATTR_DST_START
        {E_CLD_TIME_ATTR_ID_DST_START,      (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT32,   (uint32)(&((tsCLD_Time*)(0))->u32DstStart),0},
    #endif

    #ifdef CLD_TIME_ATTR_DST_END
        {E_CLD_TIME_ATTR_ID_DST_END,        (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UINT32,   (uint32)(&((tsCLD_Time*)(0))->u32DstEnd),0},
    #endif

    #ifdef CLD_TIME_ATTR_DST_SHIFT
        {E_CLD_TIME_ATTR_ID_DST_SHIFT,      (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_INT32,    (uint32)(&((tsCLD_Time*)(0))->i32DstShift),0},
    #endif

    #ifdef CLD_TIME_ATTR_STANDARD_TIME
        {E_CLD_TIME_ATTR_ID_STANDARD_TIME,  (E_ZCL_AF_RD),  E_ZCL_UINT32,   (uint32)(&((tsCLD_Time*)(0))->u32StandardTime),0},
    #endif

    #ifdef CLD_TIME_ATTR_LOCAL_TIME
        {E_CLD_TIME_ATTR_ID_LOCAL_TIME,     (E_ZCL_AF_RD),  E_ZCL_UINT32,   (uint32)(&((tsCLD_Time*)(0))->u32LocalTime),0},
    #endif

    #ifdef CLD_TIME_ATTR_LAST_SET_TIME
        {E_CLD_TIME_ATTR_ID_LAST_SET_TIME,     (E_ZCL_AF_RD),  E_ZCL_UTCT,   (uint32)(&((tsCLD_Time*)(0))->u32LastSetTime),0},
    #endif

    #ifdef CLD_TIME_ATTR_VALID_UNTIL_TIME
        {E_CLD_TIME_ATTR_ID_VALID_UNTIL_TIME,     (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_UTCT,   (uint32)(&((tsCLD_Time*)(0))->u32ValidUntilTime),0},
    #endif
#endif    
        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,   (E_ZCL_AF_RD|E_ZCL_AF_GA),  E_ZCL_UINT16,     (uint32)(&((tsCLD_Time*)(0))->u16ClusterRevision),0},   /* Mandatory  */

    };

tsZCL_ClusterDefinition sCLD_Time = {
        GENERAL_CLUSTER_ID_TIME,
        FALSE,
#ifndef TIME_USE_NWK_SECURITY
        E_ZCL_SECURITY_APPLINK,
#else
        E_ZCL_SECURITY_NETWORK,
#endif
        (sizeof(asCLD_TimeClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_TimeClusterAttributeDefinitions,
        NULL
};

uint8 au8TimeClusterAttributeControlBits[(sizeof(asCLD_TimeClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 **
 ** NAME:       eCLD_TimeCreateTime
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
PUBLIC  teZCL_Status eCLD_TimeCreateTime(
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

    /* Create an instance of a time cluster */
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
#ifdef TIME_SERVER        
        #ifdef CLD_TIME_ATTR_LAST_SET_TIME
            ((tsCLD_Time*)pvEndPointSharedStructPtr)->u32LastSetTime = 0xFFFFFFFFUL;
        #endif

        #ifdef CLD_TIME_ATTR_VALID_UNTIL_TIME
            ((tsCLD_Time*)pvEndPointSharedStructPtr)->u32ValidUntilTime = 0xFFFFFFFFUL;
        #endif
#endif        
        ((tsCLD_Time*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_TIME_CLUSTER_REVISION;
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

