/*****************************************************************************
 *
 * MODULE:             Level Control Cluster
 *
 * COMPONENT:          LevelControlClientCommands.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Send and receive Level Control cluster commands
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/LevelControlClientCommands.c $
 *
 * $Revision: 74051 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-11-09 13:28:17 +0100 (Mon, 09 Nov 2015) $
 *
 * $Id: LevelControlClientCommands.c 74051 2015-11-09 12:28:17Z nxp57621 $
 *
 ****************************************************************************
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
#include "zcl_customcommand.h"

#include "LevelControl.h"
#include "LevelControl_internal.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"

#include "dbg.h"


#ifdef DEBUG_CLD_LEVEL_CONTROL
#define TRACE_LEVEL_CONTROL    TRUE
#else
#define TRACE_LEVEL_CONTROL    FALSE
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
/****************************************************************************
 **
 ** NAME:       eCLD_LevelControlCommandMoveToLevelCommandSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Level Control cluster command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 ** bool_t                      bWithOnOff                     With On/Off ?
 ** tsCLD_LevelControl_MoveToLevelCommandPayload *psPayload    Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_LevelControlCommandMoveToLevelCommandSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    bool_t                      bWithOnOff,
                    tsCLD_LevelControl_MoveToLevelCommandPayload *psPayload)
{
    uint8 u8CommandId;
    uint8 u8PayloadSize = 0;
    
    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1, E_ZCL_UINT8,   &psPayload->u8Level},
            {1, E_ZCL_UINT16,  &psPayload->u16TransitionTime},
            {1, E_ZCL_BMAP8,   &psPayload->u8OptionsMask},
            {1, E_ZCL_BMAP8,   &psPayload->u8OptionsOverride},
                                              };

    if(bWithOnOff == FALSE)
    {
        u8CommandId = E_CLD_LEVELCONTROL_CMD_MOVE_TO_LEVEL;
        u8PayloadSize = sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem);
    }
    else
    {
        u8CommandId = E_CLD_LEVELCONTROL_CMD_MOVE_TO_LEVEL_WITH_ON_OFF;
        /* As only first two parameters needs to be passed */
        u8PayloadSize = 2;
    }

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_LEVEL_CONTROL,
                                  FALSE,
                                  u8CommandId,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  u8PayloadSize);

}


/****************************************************************************
 **
 ** NAME:       eCLD_LevelControlCommandMoveToLevelCommandReceive
 **
 ** DESCRIPTION:
 ** handles rx a level control command
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent              *pZPSevent                   Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition          EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 ** uint8                    *pu8TransactionSequenceNumber  Sequence number Pointer
 ** tsCLD_LevelControl_MoveToLevelCommandPayload *psPayload Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_LevelControlCommandMoveToLevelCommandReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsCLD_LevelControl_MoveToLevelCommandPayload *psPayload)
{

    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
            {1, &u16ActualQuantity, E_ZCL_UINT8,   &psPayload->u8Level},
            {1, &u16ActualQuantity, E_ZCL_UINT16,  &psPayload->u16TransitionTime},
            {1, &u16ActualQuantity, E_ZCL_BMAP8,   &psPayload->u8OptionsMask},
            {1, &u16ActualQuantity, E_ZCL_BMAP8,   &psPayload->u8OptionsOverride},
                                                };

    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     asPayloadDefinition,
                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                     E_ZCL_ACCEPT_LESS|E_ZCL_DISABLE_DEFAULT_RESPONSE);

}

/****************************************************************************
 **
 ** NAME:       eCLD_LevelControlCommandMoveCommandSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Level Control cluster command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 ** bool_t                      bWithOnOff                     With On/Off ?
 ** tsCLD_LevelControl_MoveCommandPayload *psPayload           Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_LevelControlCommandMoveCommandSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    bool_t                      bWithOnOff,
                    tsCLD_LevelControl_MoveCommandPayload *psPayload)
{
    uint8 u8CommandId;
    uint8 u8PayloadSize = 0;
    
    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1, E_ZCL_UINT8,    &psPayload->u8MoveMode},
            {1, E_ZCL_UINT8,    &psPayload->u8Rate},
            {1, E_ZCL_BMAP8,    &psPayload->u8OptionsMask},
            {1, E_ZCL_BMAP8,    &psPayload->u8OptionsOverride},
                            };

    if(bWithOnOff == FALSE)
    {
        u8CommandId = E_CLD_LEVELCONTROL_CMD_MOVE;
        u8PayloadSize = sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem);
    }
    else
    {
        u8CommandId = E_CLD_LEVELCONTROL_CMD_MOVE_WITH_ON_OFF;
        /* As only first two parameters needs to be passed */
        u8PayloadSize = 2;
    }

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_LEVEL_CONTROL,
                                  FALSE,
                                  u8CommandId,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  u8PayloadSize);

}


/****************************************************************************
 **
 ** NAME:       eCLD_LevelControlCommandMoveCommandReceive
 **
 ** DESCRIPTION:
 ** handles rx a level control command
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent            *pZPSevent                     Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition          EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 ** uint8                    *pu8TransactionSequenceNumber  Sequence number Pointer
 ** tsCLD_LevelControl_MoveCommandPayload *psPayload        Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_LevelControlCommandMoveCommandReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsCLD_LevelControl_MoveCommandPayload *psPayload)
{

    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psPayload->u8MoveMode},
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psPayload->u8Rate},
            {1, &u16ActualQuantity, E_ZCL_BMAP8,    &psPayload->u8OptionsMask},
            {1, &u16ActualQuantity, E_ZCL_BMAP8,    &psPayload->u8OptionsOverride},
                                                };

    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     asPayloadDefinition,
                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                     E_ZCL_ACCEPT_LESS|E_ZCL_DISABLE_DEFAULT_RESPONSE);

}


/****************************************************************************
 **
 ** NAME:       eCLD_LevelControlCommandStepCommandSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Level Control cluster command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 ** bool_t                      bWithOnOff                     With On/Off ?
 ** tsCLD_LevelControl_StepCommandPayload *psPayload           Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_LevelControlCommandStepCommandSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    bool_t                      bWithOnOff,
                    tsCLD_LevelControl_StepCommandPayload *psPayload)
{
    uint8 u8CommandId;
    uint8 u8PayloadSize = 0;
    
    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1, E_ZCL_UINT8,    &psPayload->u8StepMode},
            {1, E_ZCL_UINT8,    &psPayload->u8StepSize},
            {1, E_ZCL_UINT16,   &psPayload->u16TransitionTime},
            {1, E_ZCL_BMAP8,    &psPayload->u8OptionsMask},
            {1, E_ZCL_BMAP8,    &psPayload->u8OptionsOverride},
                                                };

    if(bWithOnOff == FALSE)
    {
        u8CommandId = E_CLD_LEVELCONTROL_CMD_STEP;
        u8PayloadSize = sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem);
    }
    else
    {
        u8CommandId = E_CLD_LEVELCONTROL_CMD_STEP_WITH_ON_OFF;
        /* As only first three parameters needs to be passed */
        u8PayloadSize = 3;
    }

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_LEVEL_CONTROL,
                                  FALSE,
                                  u8CommandId,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  u8PayloadSize);

}


/****************************************************************************
 **
 ** NAME:       eCLD_LevelControlCommandStepCommandReceive
 **
 ** DESCRIPTION:
 ** handles rx a level control command
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent            *pZPSevent                     Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition          EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 ** uint8                    *pu8TransactionSequenceNumber  Sequence number Pointer
 ** tsCLD_LevelControl_StepCommandPayload *psPayload        Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_LevelControlCommandStepCommandReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsCLD_LevelControl_StepCommandPayload *psPayload)
{

    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psPayload->u8StepMode},
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psPayload->u8StepSize},
            {1, &u16ActualQuantity, E_ZCL_UINT16,   &psPayload->u16TransitionTime},
            {1, &u16ActualQuantity, E_ZCL_BMAP8,    &psPayload->u8OptionsMask},
            {1, &u16ActualQuantity, E_ZCL_BMAP8,    &psPayload->u8OptionsOverride},
                                                };

    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     asPayloadDefinition,
                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                     E_ZCL_ACCEPT_LESS|E_ZCL_DISABLE_DEFAULT_RESPONSE);

}


/****************************************************************************
 **
 ** NAME:       eCLD_LevelControlCommandStopCommandSend
 **
 ** DESCRIPTION:
 ** Builds and sends a Level Control cluster command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsCLD_LevelControl_StopCommandPayload *psPayload           Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_LevelControlCommandStopCommandSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    bool_t                      bWithOnOff,
                    tsCLD_LevelControl_StopCommandPayload *psPayload)
{
    uint8 u8CommandId;
    uint8 u8PayloadSize = 0;
    
    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1, E_ZCL_BMAP8,    &psPayload->u8OptionsMask},
            {1, E_ZCL_BMAP8,    &psPayload->u8OptionsOverride},
                                                };

    if(bWithOnOff == FALSE)
    {
        u8CommandId = E_CLD_LEVELCONTROL_CMD_STOP;
        u8PayloadSize = sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem);
    }
    else
    {
        u8CommandId = E_CLD_LEVELCONTROL_CMD_STOP_WITH_ON_OFF;
        u8PayloadSize = 0;
    }

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_LEVEL_CONTROL,
                                  FALSE,
                                  u8CommandId,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  u8PayloadSize);
}

/****************************************************************************
 **
 ** NAME:       eCLD_LevelControlCommandStopCommandReceive
 **
 ** DESCRIPTION:
 ** handles rx a level control command
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent              *pZPSevent                   Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition          EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 ** uint8                    *pu8TransactionSequenceNumber  Sequence number Pointer
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_LevelControlCommandStopCommandReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsCLD_LevelControl_StopCommandPayload *psPayload)
{

    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
            {1, &u16ActualQuantity, E_ZCL_BMAP8,    &psPayload->u8OptionsMask},
            {1, &u16ActualQuantity, E_ZCL_BMAP8,    &psPayload->u8OptionsOverride},
                                                };

    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     asPayloadDefinition,
                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                     E_ZCL_ACCEPT_LESS|E_ZCL_DISABLE_DEFAULT_RESPONSE);
}


/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
