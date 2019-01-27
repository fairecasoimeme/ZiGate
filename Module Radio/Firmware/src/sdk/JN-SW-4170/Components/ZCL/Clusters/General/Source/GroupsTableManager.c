/*****************************************************************************
 *
 * MODULE:             Groups Cluster
 *
 * COMPONENT:          GroupsTableManager.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Table management functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/GroupsTableManager.c $
 *
 * $Revision: 74903 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-12-07 10:42:36 +0100 (Mon, 07 Dec 2015) $
 *
 * $Id: GroupsTableManager.c 74903 2015-12-07 09:42:36Z nxp57621 $
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

#include "zps_apl.h"
#include "zps_apl_aib.h"

#include "zcl.h"
#include "zcl_customcommand.h"

#include "Groups.h"
#include "Groups_internal.h"

#ifdef CLD_SCENES
#include "Scenes_internal.h"
#endif

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"

#include "string.h"



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

PRIVATE bool bCLD_GroupsSearchForGroup(void *pvSearchParam, void *psNodeUnderTest);

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
 ** NAME:       eCLD_GroupsAddGroup
 **
 ** DESCRIPTION:
 ** Adds a group to the table
 **
 ** PARAMETERS:                 Name                    Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** tsZCL_ClusterInstance       *psClusterInstance
 ** tsCLD_Groups_AddGroupRequestPayload *psPayload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_GroupsAddGroup(
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance,
                            tsCLD_Groups_AddGroupRequestPayload *psPayload)
{
    
    tsCLD_GroupTableEntry *psTableEntry;
    tsCLD_GroupsCustomDataStructure *psCommon;
    
    ZPS_teStatus eZpsStatus;
    #ifdef STRICT_PARAM_CHECK
        /* Parameter check */
        if((psEndPointDefinition==NULL) || (psClusterInstance==NULL) || (psPayload==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif
    psCommon = (tsCLD_GroupsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif

    /* group range is 1 - fff7 */
    if((psPayload->u16GroupId < 1) || (psPayload->u16GroupId > 0xfff7))
    {
        return E_CLD_GROUPS_CMD_STATUS_INVALID_FIELD;
    }
    /* Search list for any existing entry to avoid duplication */
    psTableEntry = (tsCLD_GroupTableEntry*)psDLISTsearchFromHead(&psCommon->lGroupsAllocList, bCLD_GroupsSearchForGroup, (void*)&psPayload->u16GroupId);
    if(psTableEntry != NULL)
    {
        DBG_vPrintf(TRACE_GROUPS, "Existing group entry in table\r\n");

        // release EP
        #ifndef COOPERATIVE
            eZCL_ReleaseMutex(psEndPointDefinition);
        #endif


        return E_CLD_GROUPS_DUPLICATE_EXISTS;
    }

    if(eCLD_GroupsCheckGroupExists(psEndPointDefinition, psPayload->u16GroupId) == E_ZCL_SUCCESS)
    {
        // release EP
        #ifndef COOPERATIVE
            eZCL_ReleaseMutex(psEndPointDefinition);
        #endif
        return E_CLD_GROUPS_DUPLICATE_EXISTS;
    }
 


    // Add group to zigbee stack
    DBG_vPrintf(TRACE_GROUPS, "Adding group %04x to endpoint %d\r\n", psPayload->u16GroupId, psEndPointDefinition->u8EndPointNumber);

    eZpsStatus = ZPS_eAplZdoGroupEndpointAdd(psPayload->u16GroupId, psEndPointDefinition->u8EndPointNumber);
    if(eZpsStatus != ZPS_E_SUCCESS)
    {
        DBG_vPrintf(TRACE_GROUPS, "Error: Failed to add group\r\n");
    }

    /* Get a free table entry */
    psTableEntry = (tsCLD_GroupTableEntry*)psDLISTgetHead(&psCommon->lGroupsDeAllocList);
    if(psTableEntry == NULL)
    {
        /* Delete the group we just added */
        ZPS_eAplZdoGroupEndpointRemove(psPayload->u16GroupId, psEndPointDefinition->u8EndPointNumber);

        // release EP
        #ifndef COOPERATIVE
            eZCL_ReleaseMutex(psEndPointDefinition);
        #endif


        DBG_vPrintf(TRACE_GROUPS, "Error: Insufficient space\r\n");

        return E_ZCL_ERR_INSUFFICIENT_SPACE;
    }

    /* Remove from list of free table entries */
    psDLISTremove(&psCommon->lGroupsDeAllocList, (DNODE*)psTableEntry);

    /* Add to allocated list */
    vDLISTaddToTail(&psCommon->lGroupsAllocList, (DNODE*)psTableEntry);

    /* Fill in table entry */
    psTableEntry->u16GroupId = psPayload->u16GroupId;
    memset(psTableEntry->au8GroupName, 0, sizeof(psTableEntry->au8GroupName));
    strncpy((char*)psTableEntry->au8GroupName, (char*)psPayload->sGroupName.pu8Data, psPayload->sGroupName.u8Length);

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return E_ZCL_SUCCESS;

}

/****************************************************************************
 **
 ** NAME:       PUBLIC eCLD_GroupsFindGroup
 **
 ** DESCRIPTION:
 ** Searches both tables for a matching group
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** tsZCL_ClusterInstance       *psClusterInstance
 ** uint16                      *u16GroupId                     group entry to find
 ** tsCLD_GroupTableEntry       **ppsGroupTableEntry            Returned pointer
 **                                                             to matching group
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_GroupsFindGroup(
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance,
                            uint16                      u16GroupId,
                            tsCLD_GroupTableEntry       **ppsGroupTableEntry)
{

    tsCLD_GroupTableEntry *psTableEntry;
    tsCLD_GroupsCustomDataStructure *psCommon;

    teZCL_Status eStatus = E_ZCL_FAIL;

    #ifdef STRICT_PARAM_CHECK
        /* Parameter check */
        if((psEndPointDefinition==NULL) || (psClusterInstance==NULL) || (ppsGroupTableEntry==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    psCommon = (tsCLD_GroupsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


	eStatus = eCLD_GroupsCheckGroupExists(psEndPointDefinition, u16GroupId);


    /* Search table for an entry containing text */
    psTableEntry = (tsCLD_GroupTableEntry*)psDLISTsearchFromHead(&psCommon->lGroupsAllocList, bCLD_GroupsSearchForGroup, (void*)&u16GroupId);
    if(psTableEntry != NULL)
    {
        DBG_vPrintf(TRACE_GROUPS, "Found matching group entry in table\r\n");
        *ppsGroupTableEntry = psTableEntry;
    }

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return eStatus;

}


/****************************************************************************
 **
 ** NAME:       PUBLIC iCLD_GroupsListGroups
 **
 ** DESCRIPTION:
 ** Generates a list of groups
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** int16                       *pai16List
 **
 ** RETURN:
 ** int
 **
 ****************************************************************************/
PUBLIC  int iCLD_GroupsListGroups(tsZCL_EndPointDefinition    *psEndPointDefinition,
                                 int16 *pai16List)
{
    uint32 n;
    int iNumGroups = 0;
    ZPS_tsAplAib *psAib;
    uint8 u8ByteOffset;
    uint8 u8BitOffset;

    /* Calculate endpoint bit position in group table array */
    u8ByteOffset = (psEndPointDefinition->u8EndPointNumber - 1) / 8;
    u8BitOffset  = (psEndPointDefinition->u8EndPointNumber - 1) % 8;

    /* Get AIB and search group table for group entries */
    psAib = ZPS_psAplAibGetAib();

    for(n = 0; n < psAib->psAplApsmeGroupTable->u32SizeOfGroupTable; n++)
    {
        if((psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].au8Endpoint[u8ByteOffset] & (1 << u8BitOffset)) != 0)
        {
            pai16List[iNumGroups] = psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].u16Groupid;
            iNumGroups++;
        }
    }

    return iNumGroups;

}

/****************************************************************************
 **
 ** NAME:       PUBLIC iCLD_GroupsCountGroups
 **
 ** DESCRIPTION:
 ** Returns the number of groups
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 **
 ** RETURN:
 ** int
 **
 ****************************************************************************/
PUBLIC  int iCLD_GroupsCountGroups(tsZCL_EndPointDefinition    *psEndPointDefinition)
{
    uint32 n;
    int iNumGroups = 0;
    ZPS_tsAplAib *psAib;
    uint8 u8ByteOffset;
    uint8 u8BitOffset;

    /* Calculate endpoint bit position in group table array */
    u8ByteOffset = (psEndPointDefinition->u8EndPointNumber - 1) / 8;
    u8BitOffset  = (psEndPointDefinition->u8EndPointNumber - 1) % 8;

    /* Get AIB and search group table for group entries */
    psAib = ZPS_psAplAibGetAib();

    for(n = 0; n < psAib->psAplApsmeGroupTable->u32SizeOfGroupTable; n++)
    {
        if((psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].au8Endpoint[u8ByteOffset] & (1 << u8BitOffset)) != 0)
        {
            iNumGroups++;
        }
    }

    return iNumGroups;

}


/****************************************************************************
 **
 ** NAME:       PUBLIC iCLD_GroupsListMatchingGroups
 **
 ** DESCRIPTION:
 ** Searches both tables for a matching group
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** int16                       *pai16MatchList,
 ** uint8                       u8ItemsInMatchList,
 ** int16                       *pai16List
 **
 ** RETURN:
 ** int
 **
 ****************************************************************************/
PUBLIC  int iCLD_GroupsListMatchingGroups(tsZCL_EndPointDefinition    *psEndPointDefinition,
                                                         int16 *pai16MatchList,
                                                         uint8 u8ItemsInMatchList,
                                                         int16 *pai16List)
{
    uint32 n, x;
    int iNumGroups = 0;
    ZPS_tsAplAib *psAib;
    uint8 u8ByteOffset;
    uint8 u8BitOffset;

    /* Parameter check */
    if(pai16List==NULL)
    {
        return 0;
    }

    /* Calculate endpoint bit position in group table array */
    u8ByteOffset = (psEndPointDefinition->u8EndPointNumber - 1) / 8;
    u8BitOffset  = (psEndPointDefinition->u8EndPointNumber - 1) % 8;

    /* Get AIB and search group table for a matching group entry */
    psAib = ZPS_psAplAibGetAib();

    for(x = 0; x < u8ItemsInMatchList; x++)
    {

        for(n = 0; n < psAib->psAplApsmeGroupTable->u32SizeOfGroupTable; n++)
        {
            if((psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].u16Groupid == (uint16)pai16MatchList[x]) &&
               ((psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].au8Endpoint[u8ByteOffset] & (1 << u8BitOffset)) != 0)
              )
            {
                DBG_vPrintf(TRACE_GROUPS, "\nMatch: Group %d", psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].u16Groupid);
                pai16List[iNumGroups] = psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].u16Groupid;
                iNumGroups++;
            }
        }

    }

    DBG_vPrintf(TRACE_GROUPS, "\nNumGroups %d", iNumGroups);

    return iNumGroups;

}

/****************************************************************************
 **
 ** NAME:       eCLD_GroupsRemoveGroup
 **
 ** DESCRIPTION:
 ** Removes a group from the table
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** tsZCL_ClusterInstance       *psClusterInstance
 ** tsCLD_Groups_AddGroupRequestPayload *psPayload
 ** uint64                      u64SrcIEEEAddress
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_GroupsRemoveGroup(
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance,
                            tsCLD_Groups_RemoveGroupRequestPayload *psPayload,
                            uint64                       u64SrcIEEEAddress)
{
    teZCL_Status eStatus = E_ZCL_SUCCESS;
    tsCLD_GroupTableEntry *psTableEntry;
    tsCLD_GroupsCustomDataStructure *psCommon;
    ZPS_teStatus eZpsStatus;
    #ifdef STRICT_PARAM_CHECK
        /* Parameter check */
        if((psEndPointDefinition==NULL) || (psClusterInstance==NULL) || (psPayload==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif
    psCommon = (tsCLD_GroupsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    DBG_vPrintf(TRACE_GROUPS, "Removing group %04x from endpoint %d\r\n", psPayload->u16GroupId, psEndPointDefinition->u8EndPointNumber);

    /* Search list for a matching entry */
    psTableEntry = (tsCLD_GroupTableEntry*)psDLISTsearchFromHead(&psCommon->lGroupsAllocList, bCLD_GroupsSearchForGroup, (void*)&psPayload->u16GroupId);
    if(psTableEntry != NULL)
    {
        DBG_vPrintf(TRACE_GROUPS, "Found matching entry in group table\r\n");

        /* Remove Scenes if associated with this group. */
        #ifdef SCENES_SERVER
            eStatus = eCLD_ScenesRemoveAllScenes(psEndPointDefinition->u8EndPointNumber,
                                                 psTableEntry->u16GroupId,
                                                 u64SrcIEEEAddress);
            if(eStatus == E_ZCL_SUCCESS)
            {
                 vSaveScenesNVM();
            }
        #endif  // SCENES_SERVER

        /* Remove from list of allocated table entries */
        psDLISTremove(&psCommon->lGroupsAllocList, (DNODE*)psTableEntry);

        /* Add to deallocated list */
        vDLISTaddToTail(&psCommon->lGroupsDeAllocList, (DNODE*)psTableEntry);

    }

    // Remove group from zigbee stack
    eZpsStatus = ZPS_eAplZdoGroupEndpointRemove(psPayload->u16GroupId, psEndPointDefinition->u8EndPointNumber);
    if(eZpsStatus != ZPS_E_SUCCESS)
    {
        DBG_vPrintf(TRACE_GROUPS, "Error: Failed to remove group\r\n");
        eStatus = E_ZCL_FAIL;
    }

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return eStatus;

}


/****************************************************************************
 **
 ** NAME:       eCLD_GroupsRemoveAllGroups
 **
 ** DESCRIPTION:
 ** Removes all groups from the table
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** tsZCL_ClusterInstance       *psClusterInstance
 ** uint64                      u64SrcIEEEAddress
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_GroupsRemoveAllGroups(
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance,
                            uint64                      u64SrcIEEEAddress)
{
    int n;
    teZCL_Status eStatus = E_ZCL_SUCCESS;
    tsCLD_GroupTableEntry *psTableEntry;
    tsCLD_GroupsCustomDataStructure *psCommon;
    ZPS_teStatus eZpsStatus;

    /* Parameter check */
    #ifdef STRICT_PARAM_CHECK
        if((psEndPointDefinition==NULL) || (psClusterInstance==NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif
    
    psCommon = (tsCLD_GroupsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    DBG_vPrintf(TRACE_GROUPS, "Removing all groups from endpoint %d\r\n", psEndPointDefinition->u8EndPointNumber);

    /* Move all allocated table entries to the unallocated list */
    for(n = 0; n < CLD_GROUPS_MAX_NUMBER_OF_GROUPS; n++)
    {
        /* Get an entry from the allocated list, exit if there are none */
        psTableEntry = (tsCLD_GroupTableEntry*)psDLISTgetHead(&psCommon->lGroupsAllocList);
        if(psTableEntry == NULL)
        {
            break;
        }

        /* Remove All Scenes if associated with this group. */
        #ifdef SCENES_SERVER
            eStatus = eCLD_ScenesRemoveAllScenes(psEndPointDefinition->u8EndPointNumber,
                                                 psTableEntry->u16GroupId,
                                                 u64SrcIEEEAddress);
            if(eStatus == E_ZCL_SUCCESS)
            {
                 vSaveScenesNVM();
            }
        #endif  // SCENES_SERVER

        /* Remove from list of allocated table entries */
        psDLISTremove(&psCommon->lGroupsAllocList, (DNODE*)psTableEntry);

        /* Add to deallocated list */
        vDLISTaddToTail(&psCommon->lGroupsDeAllocList, (DNODE*)psTableEntry);
    }

    // Remove group from zigbee stack

    eZpsStatus = ZPS_eAplZdoGroupAllEndpointRemove(psEndPointDefinition->u8EndPointNumber);
    if(eZpsStatus != ZPS_E_SUCCESS)
    {
        DBG_vPrintf(TRACE_GROUPS, "Error: Failed to remove all groups (zps error %x\r\n", eZpsStatus);
        eStatus = E_ZCL_FAIL;
    }

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return eStatus;

}

/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       bCLD_GroupsSearchForGroup
 **
 ** DESCRIPTION:
 ** This function checks if group id in node under test is same as search parameter.
 **
 ** PARAMETERS:                 Name                           Usage
 ** void                        *pvSearchParam
 ** DNODE                       *psNodeUnderTest
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PRIVATE  bool bCLD_GroupsSearchForGroup(void *pvSearchParam, void *psNodeUnderTest)
{
    uint16 u16SearchParameter;
    uint16 u16GroupId;

    memcpy(&u16SearchParameter, pvSearchParam, sizeof(uint16));
    memcpy(&u16GroupId, &((tsCLD_GroupTableEntry*)psNodeUnderTest)->u16GroupId, sizeof(uint16));

    DBG_vPrintf(TRACE_GROUPS, "Search: %04x:%04x\r\n", u16GroupId, u16SearchParameter);

    if(u16SearchParameter == u16GroupId)
    {
        return TRUE;
    }

    return FALSE;

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
