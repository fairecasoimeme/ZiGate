/*****************************************************************************
 *
 * MODULE:             Groups Cluster
 *
 * COMPONENT:          Groups.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Groups Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Include/Groups.h $
 *
 * $Revision: 72692 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-09-14 11:22:51 +0200 (Mon, 14 Sep 2015) $
 *
 * $Id: Groups.h 72692 2015-09-14 09:22:51Z nxp57621 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products  [NXP Microcontrollers such as JN5168, JN5164,
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

#ifndef GROUPS_H
#define GROUPS_H

#include <jendefs.h>
#include "dlist.h"
#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Cluster ID's */
#define GENERAL_CLUSTER_ID_GROUPS                   0x0004

/* Set this to the size used for the group addressing table in the .zpscfg file */
#ifndef CLD_GROUPS_MAX_NUMBER_OF_GROUPS
#define CLD_GROUPS_MAX_NUMBER_OF_GROUPS             (8)
#endif

/* 3.6.2.2.1 */
/* Set this to configure the maximum length of the group name */
#ifndef CLD_GROUPS_MAX_GROUP_NAME_LENGTH
  #ifdef CLD_GROUPS_DISABLE_NAME_SUPPORT
    #define CLD_GROUPS_MAX_GROUP_NAME_LENGTH            (0)
  #else
    #define CLD_GROUPS_MAX_GROUP_NAME_LENGTH            (16)
  #endif
#endif

/* Name Support */
#ifndef CLD_GROUPS_DISABLE_NAME_SUPPORT
#define CLD_GROUPS_NAME_SUPPORT                     (1 << 7)
#else
#define CLD_GROUPS_NAME_SUPPORT                     (0)
#endif

#ifndef CLD_GROUPS_CLUSTER_REVISION
    #define CLD_GROUPS_CLUSTER_REVISION                         1
#endif 

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Return values - Extensions to teZCL_Status*/
typedef enum 
{
    E_CLD_GROUPS_TABLE_SIZE_MISMATCH = 0x80,
    E_CLD_GROUPS_DUPLICATE_EXISTS,
    E_CLD_GROUPS_GROUP_HAS_NO_TEXT
} teCLD_GroupsStatus;


/* Command codes */
typedef enum 
{
    E_CLD_GROUPS_CMD_ADD_GROUP               = 0x00,    /* Mandatory */
    E_CLD_GROUPS_CMD_VIEW_GROUP,                        /* Mandatory */
    E_CLD_GROUPS_CMD_GET_GROUP_MEMBERSHIP,              /* Mandatory */
    E_CLD_GROUPS_CMD_REMOVE_GROUP,                      /* Mandatory */
    E_CLD_GROUPS_CMD_REMOVE_ALL_GROUPS,                 /* Mandatory */
    E_CLD_GROUPS_CMD_ADD_GROUP_IF_IDENTIFYING           /* Mandatory */
} teCLD_Groups_Command;


/* Attribute ID's */
typedef enum 
{
    /* Groups attribute set attribute ID's (3.6.2.2) */
    E_CLD_GROUPS_ATTR_ID_NAME_SUPPORT        = 0x0000,   /* Mandatory */
} teCLD_Groups_ClusterID;


/* Command status values */
typedef enum 
{
    E_CLD_GROUPS_CMD_STATUS_SUCCESS             = 0x00,
    E_CLD_GROUPS_CMD_STATUS_FAILURE,
    E_CLD_GROUPS_CMD_STATUS_INVALID_FIELD       = 0x85,
    E_CLD_GROUPS_CMD_STATUS_INSUFFICIENT_SPACE  = 0x89,
    E_CLD_GROUPS_CMD_STATUS_DUPLICATE_EXISTS,
    E_CLD_GROUPS_CMD_STATUS_NOT_FOUND
} teCLD_Groups_ResponseStatus;


/* Groups Cluster */
typedef struct
{
#ifdef GROUPS_SERVER    
    zbmap8                  u8NameSupport;
#endif    
    zuint16                 u16ClusterRevision;
} tsCLD_Groups;


/* Payloads for custom commands */

/* Add Group Request Payload */
typedef struct
{
    zuint16                 u16GroupId;
    tsZCL_CharacterString   sGroupName;
} tsCLD_Groups_AddGroupRequestPayload;


/* Add Group Response Payload */
typedef struct
{
    zenum8                  eStatus;
    zuint16                 u16GroupId;
} tsCLD_Groups_AddGroupResponsePayload;


/* View Group Request Payload */
typedef struct
{
    zuint16                 u16GroupId;
} tsCLD_Groups_ViewGroupRequestPayload;


/* View Group Response Payload */
typedef struct
{
    zenum8                  eStatus;
    zuint16                 u16GroupId;
    tsZCL_CharacterString   sGroupName;
} tsCLD_Groups_ViewGroupResponsePayload;


/* Get Group Membership Request Payload */
typedef struct
{
    zuint8                  u8GroupCount;
    zint16                 *pi16GroupList;
} tsCLD_Groups_GetGroupMembershipRequestPayload;


/* Get Group Membership Response Payload */
typedef struct
{
    zuint8                  u8Capacity;
    zuint8                  u8GroupCount;
    zint16                 *pi16GroupList;
} tsCLD_Groups_GetGroupMembershipResponsePayload;


/* Remove Group Request Payload */
typedef struct
{
    zuint16                 u16GroupId;
} tsCLD_Groups_RemoveGroupRequestPayload;


/* Remove Group Response Payload */
typedef struct
{
    zenum8                  eStatus;
    zuint16                 u16GroupId;
} tsCLD_Groups_RemoveGroupResponsePayload;


/* Definition of On-Off Call back Event Structure */
typedef struct
{
    uint8                                       u8CommandId;
    union
    {
        tsCLD_Groups_AddGroupRequestPayload             *psAddGroupRequestPayload;
        tsCLD_Groups_AddGroupResponsePayload            *psAddGroupResponsePayload;
        tsCLD_Groups_ViewGroupRequestPayload            *psViewGroupRequestPayload;
        tsCLD_Groups_ViewGroupResponsePayload           *psViewGroupResponsePayload;
        tsCLD_Groups_GetGroupMembershipRequestPayload   *psGetGroupMembershipRequestPayload;
        tsCLD_Groups_GetGroupMembershipResponsePayload  *psGetGroupMembershipResponsePayload;
        tsCLD_Groups_RemoveGroupRequestPayload          *psRemoveGroupRequestPayload;
        tsCLD_Groups_RemoveGroupResponsePayload         *psRemoveGroupResponsePayload;
    } uMessage;
} tsCLD_GroupsCallBackMessage;


/* Group entry */
typedef struct
{
    DNODE   dllGroupNode;
    uint16  u16GroupId;
    uint8   au8GroupName[CLD_GROUPS_MAX_GROUP_NAME_LENGTH + 1];
} tsCLD_GroupTableEntry;


/* Custom data structure */
typedef struct
{
    DLIST   lGroupsAllocList;
    DLIST   lGroupsDeAllocList;
    bool    bIdentifying;
    tsZCL_ReceiveEventAddress sReceiveEventAddress;
    tsZCL_CallBackEvent sCustomCallBackEvent;
    tsCLD_GroupsCallBackMessage sCallBackMessage;
#if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
    tsCLD_GroupTableEntry asGroupTableEntry[CLD_GROUPS_MAX_NUMBER_OF_GROUPS];
#endif
} tsCLD_GroupsCustomDataStructure;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_GroupsCreateGroups(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits,
                tsCLD_GroupsCustomDataStructure    *psCustomDataStructure,
                tsZCL_EndPointDefinition           *psEndPointDefinition);

PUBLIC teZCL_Status eCLD_GroupsAdd(uint8 u8SourceEndPointId,
                                   uint16 u16GroupId,
                                   uint8 *pu8GroupName);

PUBLIC teZCL_Status eCLD_GroupsCommandAddGroupRequestSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber,
                tsCLD_Groups_AddGroupRequestPayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsCommandViewGroupRequestSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber,
                tsCLD_Groups_ViewGroupRequestPayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsCommandGetGroupMembershipRequestSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber,
                tsCLD_Groups_GetGroupMembershipRequestPayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsCommandRemoveGroupRequestSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber,
                tsCLD_Groups_RemoveGroupRequestPayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsCommandRemoveAllGroupsRequestSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber);

PUBLIC teZCL_Status eCLD_GroupsCommandAddGroupIfIdentifyingRequestSend(
                uint8           u8SourceEndPointId,
                uint8           u8DestinationEndPointId,
                tsZCL_Address   *psDestinationAddress,
                uint8           *pu8TransactionSequenceNumber,
                tsCLD_Groups_AddGroupRequestPayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsCheckGroupExists(
                tsZCL_EndPointDefinition    *psEndPointDefinition,
                uint16                      u16GroupId);
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern tsZCL_ClusterDefinition sCLD_Groups;
extern const tsZCL_AttributeDefinition asCLD_GroupsClusterAttributeDefinitions[];
extern uint8 au8GroupsAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* GROUPS_H */
