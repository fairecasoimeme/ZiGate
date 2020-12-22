/*****************************************************************************
 *
 * MODULE:             Groups Cluster
 *
 * COMPONENT:          Groups_internal.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        The internal API for the Groups Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/Groups_internal.h $
 *
 * $Revision: 65741 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2014-11-19 08:04:45 +0100 (Wed, 19 Nov 2014) $
 *
 * $Id: Groups_internal.h 65741 2014-11-19 07:04:45Z nxp57621 $
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

#ifndef  GROUPS_INTERNAL_H_INCLUDED
#define  GROUPS_INTERNAL_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "jendefs.h"

#include "zcl.h"
#include "Groups.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_GroupsCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC teZCL_Status eCLD_GroupsSetIdentifying(
                    uint8 u8SourceEndPointId,
                    bool_t bIsIdentifying);

PUBLIC teZCL_Status eCLD_GroupsCommandAddGroupResponseSend(
                    uint8           u8SourceEndPointId,
                    uint8           u8DestinationEndPointId,
                    tsZCL_Address   *psDestinationAddress,
                    uint8           *pu8TransactionSequenceNumber,
                    tsCLD_Groups_AddGroupResponsePayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsCommandViewGroupResponseSend(
                    uint8           u8SourceEndPointId,
                    uint8           u8DestinationEndPointId,
                    tsZCL_Address   *psDestinationAddress,
                    uint8           *pu8TransactionSequenceNumber,
                    tsCLD_Groups_ViewGroupResponsePayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsCommandViewGroupResponseReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsCLD_Groups_ViewGroupResponsePayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsCommandGetGroupMembershipResponseSend(
                    uint8           u8SourceEndPointId,
                    uint8           u8DestinationEndPointId,
                    tsZCL_Address   *psDestinationAddress,
                    uint8           *pu8TransactionSequenceNumber,
                    tsCLD_Groups_GetGroupMembershipResponsePayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsCommandRemoveGroupResponseSend(
                    uint8           u8SourceEndPointId,
                    uint8           u8DestinationEndPointId,
                    tsZCL_Address   *psDestinationAddress,
                    uint8           *pu8TransactionSequenceNumber,
                    tsCLD_Groups_RemoveGroupResponsePayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsAddGroup(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance,
                    tsCLD_Groups_AddGroupRequestPayload *psPayload);

PUBLIC teZCL_Status eCLD_GroupsFindGroup(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance,
                    uint16                      u16GroupId,
                    tsCLD_GroupTableEntry       **ppsGroupTableEntry);

PUBLIC int iCLD_GroupsListGroups(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    int16 *pai16List);

PUBLIC int iCLD_GroupsCountGroups(tsZCL_EndPointDefinition    *psEndPointDefinition);

PUBLIC int iCLD_GroupsListMatchingGroups(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    int16 *pai16MatchList,
                    uint8 u8ItemsInMatchList,
                    int16 *pai16List);

PUBLIC teZCL_Status eCLD_GroupsRemoveGroup(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance,
                    tsCLD_Groups_RemoveGroupRequestPayload *psPayload,
                    uint64                      u64SrcIEEEAddress);

PUBLIC teZCL_Status eCLD_GroupsRemoveAllGroups(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance,
                    uint64                      u64SrcIEEEAddress);


/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* GROUPS_INTERNAL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
