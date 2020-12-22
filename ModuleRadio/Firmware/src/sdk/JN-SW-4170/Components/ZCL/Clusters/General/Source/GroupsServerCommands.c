/*****************************************************************************
 *
 * MODULE:             Groups Cluster
 *
 * COMPONENT:          GroupsServerCommands.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Send a groups cluster command
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/GroupsServerCommands.c $
 *
 * $Revision: 65024 $
 *
 * $LastChangedBy: nxp58432 $
 *
 * $LastChangedDate: 2014-11-05 12:09:36 +0100 (Wed, 05 Nov 2014) $
 *
 * $Id: GroupsServerCommands.c 65024 2014-11-05 11:09:36Z nxp58432 $
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

#include "Groups.h"
#include "Groups_internal.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"

#include "dbg.h"


#ifdef DEBUG_CLD_GROUPS
#define TRACE_GROUPS    TRUE
#else
#define TRACE_GROUPS    FALSE
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

#ifdef GROUPS_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_GroupsCommandAddGroupResponseSend
 **
 ** DESCRIPTION:
 ** Builds and sends a group cluster command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsCLD_Groups_AddGroupResponsePayload *psPayload            Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_GroupsCommandAddGroupResponseSend(
                                        uint8           u8SourceEndPointId,
                                        uint8           u8DestinationEndPointId,
                                        tsZCL_Address   *psDestinationAddress,
                                        uint8           *pu8TransactionSequenceNumber,
                                        tsCLD_Groups_AddGroupResponsePayload *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1,                                     E_ZCL_ENUM8,    &psPayload->eStatus},
            {1,                                     E_ZCL_UINT16,   &psPayload->u16GroupId},
                                              };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_GROUPS,
                                  TRUE,
                                  E_CLD_GROUPS_CMD_ADD_GROUP,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}
#endif



#ifdef GROUPS_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_GroupsCommandAddGroupRequestSend
 **
 ** DESCRIPTION:
 ** Builds and sends a group cluster command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsCLD_Groups_ViewGroupResponsePayload *psPayload           Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_GroupsCommandViewGroupResponseSend(
                                        uint8           u8SourceEndPointId,
                                        uint8           u8DestinationEndPointId,
                                        tsZCL_Address   *psDestinationAddress,
                                        uint8           *pu8TransactionSequenceNumber,
                                        tsCLD_Groups_ViewGroupResponsePayload *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1,                                     E_ZCL_ENUM8,    &psPayload->eStatus},
            {1,                                     E_ZCL_UINT16,   &psPayload->u16GroupId},
            {1,                                     E_ZCL_CSTRING,  &psPayload->sGroupName},
                                              };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_GROUPS,
                                  TRUE,
                                  E_CLD_GROUPS_CMD_VIEW_GROUP,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}
#endif



#ifdef GROUPS_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_GroupsCommandGetGroupMembershipResponseSend
 **
 ** DESCRIPTION:
 ** Builds and sends a group cluster command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsCLD_Groups_GetGroupMembershipResponsePayload *psPayload   Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_GroupsCommandGetGroupMembershipResponseSend(
                                        uint8           u8SourceEndPointId,
                                        uint8           u8DestinationEndPointId,
                                        tsZCL_Address   *psDestinationAddress,
                                        uint8           *pu8TransactionSequenceNumber,
                                        tsCLD_Groups_GetGroupMembershipResponsePayload *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1,                         E_ZCL_UINT8,    &psPayload->u8Capacity},
            {1,                         E_ZCL_UINT8,    &psPayload->u8GroupCount},
            {psPayload->u8GroupCount,   E_ZCL_UINT16,   psPayload->pi16GroupList},
                                              };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_GROUPS,
                                  TRUE,
                                  E_CLD_GROUPS_CMD_GET_GROUP_MEMBERSHIP,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}
#endif



#ifdef GROUPS_SERVER
/****************************************************************************
 **
 ** NAME:       eCLD_GroupsCommandRemoveGroupResponseSend
 **
 ** DESCRIPTION:
 ** Builds and sends a group cluster command
 **
 ** PARAMETERS:                 Name                           Usage
 ** uint8                       u8SourceEndPointId             Source EP Id
 ** uint8                       u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address              *psDestinationAddress           Destination Address
 ** uint8                      *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsCLD_Groups_RemoveGroupResponsePayload *psPayload            Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_GroupsCommandRemoveGroupResponseSend(
                                        uint8           u8SourceEndPointId,
                                        uint8           u8DestinationEndPointId,
                                        tsZCL_Address   *psDestinationAddress,
                                        uint8           *pu8TransactionSequenceNumber,
                                        tsCLD_Groups_RemoveGroupResponsePayload *psPayload)
{

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
            {1,                                     E_ZCL_ENUM8,    &psPayload->eStatus},
            {1,                                     E_ZCL_UINT16,   &psPayload->u16GroupId},
                                              };

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  GENERAL_CLUSTER_ID_GROUPS,
                                  TRUE,
                                  E_CLD_GROUPS_CMD_REMOVE_GROUP,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}
#endif



/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
