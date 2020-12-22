/*****************************************************************************
 *
 * MODULE:             Window Covering Cluster
 *
 * COMPONENT:          WindowCovering_internal.h
 *
 * AUTHOR:             Vesa 'ISO-B' Ylikylä
 * DESCRIPTION:        Header for WindowCovering Client Cluster
 *
 * $HeadURL:  $
 *
 * $Revision: 1 $
 *
 * $LastChangedBy: isob $
 *
 * $LastChangedDate: 2019-01-19 12:00:00 +0200 (Sat, 19 Jan 2018) $
 *
 * $Id: WindowCovering_internal.h 1 2019-01-19 10:00:00Z isob $
 *
 ****************************************************************************/

#ifndef  WINDOWCOVERING_INTERNAL_H_INCLUDED
#define  WINDOWCOVERING_INTERNAL_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "jendefs.h"

#include "zcl.h"
#include "WindowCovering.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_WindowCoveringCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* WINDOWCOVERING_INTERNAL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
