/*****************************************************************************
 *
 * MODULE:             Window Covering Cluster
 *
 * COMPONENT:          WindowCoveringCommandHandler.c
 *
 * AUTHOR:             Vesa 'ISO-B' Ylikylä
 * DESCRIPTION:        Message event handler functions
 *
 * $HeadURL:  $
 *
 * $Revision: 1 $
 *
 * $LastChangedBy: isob $
 *
 * $LastChangedDate: 2019-01-19 12:00:00 +0200 (Sat, 19 Jan 2018) $
 *
 * $Id: WindowCoveringCommandHandler.c 1 2019-01-19 10:00:00Z isob $
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <string.h>

#include "zcl.h"
#include "zcl_customcommand.h"

#include "WindowCovering.h"
#include "WindowCovering_internal.h"

#include "zcl_options.h"


#include "dbg.h"
#ifdef DEBUG_CLD_WINDOWCOVERING
#define TRACE_WINDOWCOVERING TRUE
#else
#define TRACE_WINDOWCOVERING FALSE
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

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Public Functions                                              ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_WindowCoveringCommandHandler
 **
 ** DESCRIPTION:
 ** Handles Message Cluster custom commands
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_WindowCoveringCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance)
{

    tsZCL_HeaderParams sZCL_HeaderParams;
    DBG_vPrintf(TRACE_WINDOWCOVERING, "\nWINDOW COVERING: ");
    DBG_vPrintf(TRACE_WINDOWCOVERING, "ONLY RESPONSE SHOULD BE DEFAULT RESPONSE ");

    // further error checking can only be done once we have interrogated the ZCL payload
    u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                             &sZCL_HeaderParams);

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif

    return(E_ZCL_ERR_CUSTOM_COMMAND_HANDLER_NULL_OR_RETURNED_ERROR);

    // unlock
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    // delete the i/p buffer on return
    return(E_ZCL_SUCCESS);

}

/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
