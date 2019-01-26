/*****************************************************************************
 *
 * MODULE:             Window Covering Cluster
 *
 * COMPONENT:          WindowCoveringCommands.c
 *
 * AUTHOR:             Vesa 'ISO-B' Ylikylä
 * DESCRIPTION:        Send a window covering cluster command
 *
 * $HeadURL:  $
 *
 * $Revision: 1 $
 *
 * $LastChangedBy: isob $
 *
 * $LastChangedDate: 2019-01-19 12:00:00 +0200 (Sat, 19 Jan 2018) $
 *
 * $Id: WindowCoveringCommands.c 1 2019-01-19 10:00:00Z isob $
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>

#include "zcl.h"
#include "zcl_customcommand.h"

#include "WindowCovering.h"
#include "WindowCovering_internal.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"


#include "dbg.h"

#ifdef DEBUG_CLD_WINDOWCOVERING
#define TRACE_WINDOWCOVERING    TRUE
#else
#define TRACE_WINDOWCOVERING    FALSE
#endif

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

/****************************************************************************/
/***        Public Functions                                              ***/
/****************************************************************************/
#ifdef WINDOWCOVERING_CLIENT
/****************************************************************************
 **
 ** NAME:       eCLD_WindowCoveringCommandOpenCloseStopRequestSend
 **
 ** DESCRIPTION:
 ** Builds and sends a open, close or stop Request command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_WindowCoveringCommandOpenCloseStopRequestSend(
                                        uint8              u8SourceEndPointId,
                                        uint8           u8DestinationEndPointId,
                                        tsZCL_Address   *psDestinationAddress,
                                        uint8           *pu8TransactionSequenceNumber,
                                        teCLD_WindowCovering_CommandID      eCommand)
{

    DBG_vPrintf(TRACE_WINDOWCOVERING, "\nWindow Covering cluster 1 CMD: %d\n", eCommand);
    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  CLOSURE_CLUSTER_ID_WINDOWCOVERING,
                                  FALSE,
                                  (uint8)eCommand,
                                  pu8TransactionSequenceNumber,
                                  0,
                                  FALSE,
                                  0,
                                  0);

}

/****************************************************************************
 **
 ** NAME:       eCLD_WindowCoveringCommandGotoValueResponseSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Go To (Lift|Tilt) value request command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status  eCLD_WindowCoveringCommandGotoValueRequestSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    teCLD_WindowCovering_CommandID     eCommand,
                    tsCLD_WindowCovering_GoToValueRequestPayload *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
        {1, E_ZCL_UINT16, &psPayload->u16Value},
    };

    DBG_vPrintf(TRACE_WINDOWCOVERING, "\nWindow Covering cluster 2 CMD: %d PL: %x\n", eCommand, psPayload->u16Value);
    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  CLOSURE_CLUSTER_ID_WINDOWCOVERING,
                                  TRUE,
                                  (uint8)eCommand,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
}

/****************************************************************************
 **
 ** NAME:       eCLD_WindowCoveringCommandGotoPercentageResponseSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Go To (Lift|Tilt) percentage request command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status  eCLD_WindowCoveringCommandGotoPercentageRequestSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    teCLD_WindowCovering_CommandID     eCommand,
                    tsCLD_WindowCovering_GoToPercentageRequestPayload *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
        {1, E_ZCL_UINT8, &psPayload->u8Percentage},
    };
    DBG_vPrintf(TRACE_WINDOWCOVERING, "\nWindow Covering cluster 3 CMD: %d PL: %x\n", eCommand, psPayload->u8Percentage);
    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  CLOSURE_CLUSTER_ID_WINDOWCOVERING,
                                  TRUE,
                                  (uint8)eCommand,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
}
#endif
