/*****************************************************************************
 *
 * MODULE:             Groups Cluster
 *
 * COMPONENT:          Groups.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Groups cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/Groups.c $
 *
 * $Revision: 92972 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2018-03-30 12:21:27 +0100 (Fri, 30 Mar 2018) $
 *
 * $Id: Groups.c 92972 2018-03-30 11:21:27Z nxp29741 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139].
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
#include "dlist.h"
#include "OnOff.h"
#include "zcl_options.h"
#include "string.h"
#include "Groups_internal.h"


#ifdef CLD_GROUPS

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
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
    const tsZCL_CommandDefinition asCLD_GroupsClusterCommandDefinitions[] = {
        {E_CLD_GROUPS_CMD_ADD_GROUP,                E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_GROUPS_CMD_VIEW_GROUP,               E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_GROUPS_CMD_GET_GROUP_MEMBERSHIP,     E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_GROUPS_CMD_REMOVE_GROUP,             E_ZCL_CF_RX|E_ZCL_CF_TX},     /* Mandatory */
        {E_CLD_GROUPS_CMD_REMOVE_ALL_GROUPS,        E_ZCL_CF_RX},     /* Mandatory */
        {E_CLD_GROUPS_CMD_ADD_GROUP_IF_IDENTIFYING, E_ZCL_CF_RX}     /* Mandatory */

    };
#endif
const tsZCL_AttributeDefinition asCLD_GroupsClusterAttributeDefinitions[] = {
#ifdef GROUPS_SERVER
    {E_CLD_GROUPS_ATTR_ID_NAME_SUPPORT, 		E_ZCL_AF_RD,                E_ZCL_BMAP8,    (uint32)(&((tsCLD_Groups*)(0))->u8NameSupport),0},     /* Mandatory */
#endif    

	{E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,  	(E_ZCL_AF_RD|E_ZCL_AF_GA),	E_ZCL_UINT16,   (uint32)(&((tsCLD_Groups*)(0))->u16ClusterRevision),0},   /* Mandatory  */
};

tsZCL_ClusterDefinition sCLD_Groups = {
        GENERAL_CLUSTER_ID_GROUPS,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_GroupsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_GroupsClusterAttributeDefinitions,
        NULL
        #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED        
            ,
            (sizeof(asCLD_GroupsClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
            (tsZCL_CommandDefinition*)asCLD_GroupsClusterCommandDefinitions         
        #endif        
};
uint8 au8GroupsAttributeControlBits[(sizeof(asCLD_GroupsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME:       eCLD_GroupsCreateGroups
 *
 * DESCRIPTION:
 * Creates an on/off cluster
 *
 * PARAMETERS:  Name                        Usage
 *              psClusterInstance           Cluster structure
 *              bIsServer                   Server Client Flag
 *              psClusterDefinition         Pointer to Cluster Definition
 *              pvEndPointSharedStructPtr   Pointer to EndPoint Shared Structure
 *              pu8AttributeControlBits     Pointer to Attribute Control Bits
 *              psCustomDataStructure       Pointer to Custom Data Structure
 * RETURN:
 * teZCL_Status
 *
 ****************************************************************************/

PUBLIC  teZCL_Status eCLD_GroupsCreateGroups(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits,
                tsCLD_GroupsCustomDataStructure    *psCustomDataStructure,
                tsZCL_EndPointDefinition           *psEndPointDefinition)
{

    #if (defined CLD_GROUPS) && (defined GROUPS_SERVER)
    tsCLD_GroupTableEntry *psTableEntry;
    uint8 u8ByteOffset, u8BitOffset;
    uint32 n;
    #endif
    
    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) || (psCustomDataStructure==NULL))
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
               psCustomDataStructure,
               eCLD_GroupsCommandHandler);
                   
    psCustomDataStructure->sCustomCallBackEvent.eEventType = E_ZCL_CBET_CLUSTER_CUSTOM;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId = psClusterDefinition->u16ClusterEnum;
    psCustomDataStructure->sCustomCallBackEvent.uMessage.sClusterCustomMessage.pvCustomData = (void *)&psCustomDataStructure->sCallBackMessage;
    psCustomDataStructure->sCustomCallBackEvent.psClusterInstance = psClusterInstance;                    

    psCustomDataStructure->bIdentifying = FALSE;

    /* initialise lists */
    vDLISTinitialise(&((tsCLD_GroupsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr)->lGroupsAllocList);
    vDLISTinitialise(&((tsCLD_GroupsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr)->lGroupsDeAllocList);
    #ifdef GROUPS_SERVER
	    ZPS_tsAplAib *psAib;
        for(n=0; n < CLD_GROUPS_MAX_NUMBER_OF_GROUPS; n++)
        {
            /* add all header slots to the to free list */
            vDLISTaddToTail(&psCustomDataStructure->lGroupsDeAllocList, (DNODE *)&psCustomDataStructure->asGroupTableEntry[n]);
        }
        
        /* Get AIB find out group table capacity */
        psAib = ZPS_psAplAibGetAib();

        if(psAib->psAplApsmeGroupTable->u32SizeOfGroupTable < CLD_GROUPS_MAX_NUMBER_OF_GROUPS)
        {
            return E_CLD_GROUPS_TABLE_SIZE_MISMATCH;
        }

        /* Check psAplApsmeGroupTable and update lGroupsDeAllocList and lGroupsAllocList */
        /* Calculate endpoint bit position in group table array */
        u8ByteOffset = (psEndPointDefinition->u8EndPointNumber - 1) / 8;
        u8BitOffset  = (psEndPointDefinition->u8EndPointNumber - 1) % 8;

        for(n = 0; n < psAib->psAplApsmeGroupTable->u32SizeOfGroupTable; n++)
        {
            if((psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].au8Endpoint[u8ByteOffset] & (1 << u8BitOffset)) != 0)
            {
                /* Get a free table entry */
                psTableEntry = (tsCLD_GroupTableEntry*)psDLISTgetHead(&psCustomDataStructure->lGroupsDeAllocList);
                if(psTableEntry == NULL)
                {
                    return E_ZCL_ERR_INSUFFICIENT_SPACE;
                }
                /* Remove from list of free table entries */
                psDLISTremove(&psCustomDataStructure->lGroupsDeAllocList, (DNODE*)psTableEntry);
                /* Add to allocated list */
                vDLISTaddToTail(&psCustomDataStructure->lGroupsAllocList, (DNODE*)psTableEntry);

                /* Fill in table entry */
                psTableEntry->u16GroupId = psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].u16Groupid;
                memset(psTableEntry->au8GroupName, 0, sizeof(psTableEntry->au8GroupName));
            }
        }
    #endif    
        /* Initialise attributes */
        if(pvEndPointSharedStructPtr != NULL)
        {
            #ifdef GROUPS_SERVER    
                ((tsCLD_Groups*)pvEndPointSharedStructPtr)->u8NameSupport = CLD_GROUPS_NAME_SUPPORT;
            #endif
            ((tsCLD_Groups*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_GROUPS_CLUSTER_REVISION ;
        }


    return E_ZCL_SUCCESS;

}


/****************************************************************************
 **
 ** NAME:       eCLD_GroupsSetIdentifying
 **
 ** DESCRIPTION:
 **
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          Endpoint id
 ** bool_t                      bIsIdentifying              Identify state
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_GroupsSetIdentifying(uint8 u8SourceEndPointId,
                                                              bool_t bIsIdentifying)
{
    uint8 u8Status;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_GroupsCustomDataStructure *psCommon;

    /* Find pointers to cluster */
    u8Status = eZCL_FindCluster(GENERAL_CLUSTER_ID_GROUPS, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCommon);
    if(u8Status != E_ZCL_SUCCESS)
    {
        return u8Status;
    }

    psCommon->bIdentifying = bIsIdentifying;

    return E_ZCL_SUCCESS;

}

/****************************************************************************
 **
 ** NAME:       eCLD_GroupsAdd
 **
 ** DESCRIPTION:
 ** Adds a group
 **
 ** PARAMETERS:                 Name                    Usage
 ** uint8                       u8SourceEndPointId      Endpoint id
 ** uint16                      u16GroupId              Group Id
 ** uint8 *                     pu8GroupName            Pointer to group name
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_GroupsAdd(uint8 u8SourceEndPointId,
                                                   uint16 u16GroupId,
                                                   uint8 *pu8GroupName)
{
    uint8 u8Status;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;
    tsCLD_GroupsCustomDataStructure *psCommon;
    tsCLD_Groups_AddGroupRequestPayload sPayload;

    /* Find pointers to cluster */
    u8Status = eZCL_FindCluster(GENERAL_CLUSTER_ID_GROUPS, u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, (void*)&psCommon);
    if(u8Status != E_ZCL_SUCCESS)
    {
        return u8Status;
    }

    sPayload.u16GroupId = u16GroupId;
    sPayload.sGroupName.pu8Data = pu8GroupName;
    sPayload.sGroupName.u8Length = strlen((char*)pu8GroupName);
    sPayload.sGroupName.u8MaxLength = sPayload.sGroupName.u8Length;

    return eCLD_GroupsAddGroup(psEndPointDefinition, psClusterInstance, &sPayload);

}

/****************************************************************************
 **
 ** NAME:       eCLD_GroupsCheckGroupExists
 **
 ** DESCRIPTION:
 ** Search a group in Group Table
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** uint16                      u16GroupId
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_GroupsCheckGroupExists(
                                                tsZCL_EndPointDefinition    *psEndPointDefinition,
                                                uint16                      u16GroupId)
{

    ZPS_tsAplAib *psAib;
    uint8 u8ByteOffset;
    uint8 u8BitOffset;
    uint32 n;
    
    /* Parameter check */
    #ifdef STRICT_PARAM_CHECK
        if(psEndPointDefinition == NULL)
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    /* Calculate endpoint bit position in group table array */
    u8ByteOffset = (psEndPointDefinition->u8EndPointNumber - 1) / 8;
    u8BitOffset  = (psEndPointDefinition->u8EndPointNumber - 1) % 8;

    /* Get AIB and search group table for a matching group entry */
    psAib = ZPS_psAplAibGetAib();

    for(n = 0; n < psAib->psAplApsmeGroupTable->u32SizeOfGroupTable; n++)
    {
        if((psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].u16Groupid == u16GroupId) &&
           ((psAib->psAplApsmeGroupTable->psAplApsmeGroupTableId[n].au8Endpoint[u8ByteOffset] & (1 << u8BitOffset)) != 0)
          )
        {
            return E_ZCL_SUCCESS;
        }
    }
    return E_ZCL_ERR_INVALID_VALUE;
}
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

