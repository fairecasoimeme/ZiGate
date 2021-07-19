/*****************************************************************************
 *
 * MODULE:             Window Covering Cluster
 *
 * COMPONENT:          WindowCovering.c
 *
 * AUTHOR:             Vesa 'ISO-B' Ylikylä
 * DESCRIPTION:        WindowCovering Client cluster definition
 *
 * $HeadURL:  $
 *
 * $Revision: 1 $
 *
 * $LastChangedBy: isob $
 *
 * $LastChangedDate: 2019-01-19 12:00:00 +0200 (Sat, 19 Jan 2018) $
 *
 * $Id: WindowCovering.c 1 2019-01-19 10:00:00Z isob $
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>

#include "zps_apl.h"
#include "zps_apl_aib.h"

#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_options.h"
#include "string.h"
#include "WindowCovering.h"
#include "WindowCovering_internal.h"


#include "dbg.h"

#ifdef DEBUG_CLD_WINDOWCOVERING
#define TRACE_WINDOWCOVERING    TRUE
#else
#define TRACE_WINDOWCOVERING    FALSE
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#if defined(CLD_WINDOWCOVERING) && !defined(WINDOWCOVERING_CLIENT)
#error You Must Have WINDOWCOVERING_CLIENT defined in zcl_options.h
#endif

#ifdef WINDOWCOVERING_SERVER
#error ZiGate does not support Window Covering Server Cluster
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#ifdef CLD_WINDOWCOVERING
/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
    const tsZCL_CommandDefinition asCLD_WindowCoveringClusterCommandDefinitions[] = {
        {E_CLD_WINDOWCOVERING_CMD_UP_OPEN,                E_ZCL_CF_RX},     /* Mandatory */
        {E_CLD_WINDOWCOVERING_CMD_DOWN_CLOSE,             E_ZCL_CF_RX},     /* Mandatory */
        {E_CLD_WINDOWCOVERING_CMD_STOP,                   E_ZCL_CF_RX},    /* Mandatory */
        {E_CLD_WINDOWCOVERING_CMD_GO_TO_LIFT_VALUE,       E_ZCL_CF_RX},
        {E_CLD_WINDOWCOVERING_CMD_GO_TO_LIFT_PERCENTAGE,  E_ZCL_CF_RX},
        {E_CLD_WINDOWCOVERING_CMD_GO_TO_TILT_VALUE,       E_ZCL_CF_RX},
        {E_CLD_WINDOWCOVERING_CMD_GO_TO_TILT_PERCENTAGE,  E_ZCL_CF_RX}
    };
#endif


const tsZCL_AttributeDefinition asCLD_WindowCoveringClusterAttributeDefinitions[] = {
    {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                     (E_ZCL_AF_RD|E_ZCL_AF_GA),             E_ZCL_UINT16,   (uint32)(&((tsCLD_WindowCovering*)(0))->u16ClusterRevision),0},   /* Mandatory  */
};

tsZCL_ClusterDefinition sCLD_WindowCovering = {
        CLOSURE_CLUSTER_ID_WINDOWCOVERING,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_WindowCoveringClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_WindowCoveringClusterAttributeDefinitions,
        NULL
        #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
            ,
            (sizeof(asCLD_WindowCoveringClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
            (tsZCL_CommandDefinition*)asCLD_WindowCoveringClusterCommandDefinitions
        #endif
};
uint8 au8WindowCoveringAttributeControlBits[(sizeof(asCLD_WindowCoveringClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_WindowCoveringCreateWindowCovering
 **
 ** DESCRIPTION:
 ** Creates a Window Covering cluster
 **
 ** PARAMETERS:                 Name                                Usage
 ** tsZCL_ClusterInstance      *psClusterInstance                   Cluster structure
 ** bool_t                      bIsServer                           Server Client flag
 ** tsZCL_ClusterDefinition    *psClusterDefinition                 Cluster Definition
 ** void                       *pvEndPointSharedStructPtr           EndPoint Shared Structure
 ** uint8                      *pu8AttributeControlBits             Attribute Control Bits
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_WindowCoveringCreateWindowCovering(
                tsZCL_ClusterInstance                   *psClusterInstance,
                bool_t                                  bIsServer,
                tsZCL_ClusterDefinition                 *psClusterDefinition,
                void                                    *pvEndPointSharedStructPtr,
                uint8                                   *pu8AttributeControlBits)
{

    #ifdef STRICT_PARAM_CHECK
        /* Parameter check */
           if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL)  )
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    // cluster data
    vZCL_InitializeClusterInstance(
                       psClusterInstance,
                       bIsServer,
                       psClusterDefinition,
                       pvEndPointSharedStructPtr,
                       pu8AttributeControlBits,
                       NULL,
                       eCLD_WindowCoveringCommandHandler);

        if(psClusterInstance->pvEndPointSharedStructPtr != NULL)
        {
            ((tsCLD_WindowCovering*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_WINDOWCOVERING_CLUSTER_REVISION;
        }

    /* As this cluster has reportable attributes enable default reporting */
    vZCL_SetDefaultReporting(psClusterInstance);

    return E_ZCL_SUCCESS;

}

#endif   /* #define CLD_WINDOWCOVERING */
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

