/*****************************************************************************
 *
 * MODULE:             Alarms Cluster
 *
 * COMPONENT:          AlarmsTableManager.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Alarm management functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/AlarmsTableManager.c $
 *
 * $Revision: 72260 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-08-26 09:12:34 +0200 (Wed, 26 Aug 2015) $
 *
 * $Id: AlarmsTableManager.c 72260 2015-08-26 07:12:34Z nxp57621 $
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

#include "Alarms.h"
#include "Alarms_internal.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"

#include "string.h"

#include "dbg.h"

#ifdef DEBUG_CLD_ALARMS
#define TRACE_ALARMS    TRUE
#else
#define TRACE_ALARMS    FALSE
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#ifdef ALARMS_SERVER

typedef struct
{
    uint8   u8AlarmCode;
    uint16  u16ClusterId;
    uint32  u32TimeStamp;
} tsCLD_AlarmsMatch;

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

PRIVATE tsCLD_AlarmsTableEntry *psCLD_AlarmsGetEarliestEntry(tsZCL_ClusterInstance *psClusterInstance);
PRIVATE bool bCLD_AlarmsSearchForAlarm(void *pvSearchParam, void *psNodeUnderTest);

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
 ** NAME:       eCLD_AlarmsResetAlarmLog
 **
 ** DESCRIPTION:
 ** Clears the alarm log
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** tsZCL_ClusterInstance       *psClusterInstance
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_AlarmsResetAlarmLog(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance)
{
    int n;
    tsCLD_AlarmsTableEntry *psTableEntry;
    tsCLD_AlarmsCustomDataStructure *psCommon;

    /* Parameter check */
    #ifdef STRICT_PARAM_CHECK
        if((psEndPointDefinition == NULL)           ||
           (psClusterInstance == NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif
    psCommon = (tsCLD_AlarmsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    /* Move all allocated table entries to the unallocated list */
    for(n = 0; n < CLD_ALARMS_MAX_NUMBER_OF_ALARMS; n++)
    {
        /* Get an entry from the allocated list, exit if there are none */
        psTableEntry = (tsCLD_AlarmsTableEntry*)psDLISTgetHead(&psCommon->lAlarmsAllocList);
        if(psTableEntry == NULL)
        {
            break;
        }

        /* Remove from list of allocated table entries */
        psDLISTremove(&psCommon->lAlarmsAllocList, (DNODE*)psTableEntry);

        /* Add to deallocated list */
        vDLISTaddToTail(&psCommon->lAlarmsDeAllocList, (DNODE*)psTableEntry);
    }

#ifdef CLD_ALARMS_ATTR_ALARM_COUNT
        ((tsCLD_Alarms*)psClusterInstance->pvEndPointSharedStructPtr)->u16AlarmCount = 0;
#endif

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return E_ZCL_SUCCESS;

}

/****************************************************************************
 **
 ** NAME:       eCLD_AlarmsAddAlarm
 **
 ** DESCRIPTION:
 ** Adds an alarm to the table
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** tsZCL_ClusterInstance       *psClusterInstance
 ** uint8                       u8AlarmCode                     Alarm Code
 ** uint16                      u16ClusterId                    Cluster Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_AlarmsAddAlarmToLog(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance,
                    uint8                       u8AlarmCode,
                    uint16                      u16ClusterId)
{
    tsCLD_AlarmsTableEntry *psTableEntry;
    tsCLD_AlarmsCustomDataStructure *psCommon;
    tsCLD_AlarmsMatch sSearchParameter;
    uint32 u32TimeStamp = u32ZCL_GetUTCTime();

    /* Parameter check */
    #ifdef STRICT_PARAM_CHECK
        if((psEndPointDefinition == NULL)           ||
           (psClusterInstance == NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif
    
    psCommon = (tsCLD_AlarmsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    /* Search list for any existing entry to avoid duplication */
    sSearchParameter.u8AlarmCode  = u8AlarmCode;
    sSearchParameter.u16ClusterId = u16ClusterId;
    sSearchParameter.u32TimeStamp = u32TimeStamp;
    psTableEntry = (tsCLD_AlarmsTableEntry*)psDLISTsearchFromHead(&psCommon->lAlarmsAllocList, bCLD_AlarmsSearchForAlarm, (void*)&sSearchParameter);

    /* If no matching entry is found that we can update, try and get a free table entry */
    if(psTableEntry == NULL)
    {
        DBG_vPrintf(TRACE_ALARMS, "No Existing alarm entry in table\r\n");

        /* Get a free table entry */
        psTableEntry = (tsCLD_AlarmsTableEntry*)psDLISTgetHead(&psCommon->lAlarmsDeAllocList);

        /* If no free entries, we need to expire the oldest entry and then try again */
        if(psTableEntry == NULL)
        {
            /* Get earliest entry and use that instead */
            psTableEntry = psCLD_AlarmsGetEarliestEntry(psClusterInstance);
            if(psTableEntry == NULL)
            {
                #ifndef COOPERATIVE
                    eZCL_ReleaseMutex(psEndPointDefinition);
                #endif


                DBG_vPrintf(TRACE_ALARMS, "Error: Insufficient space\r\n");

                return E_ZCL_ERR_INSUFFICIENT_SPACE;
            }
        }

        /* Remove from list of free table entries */
        psDLISTremove(&psCommon->lAlarmsDeAllocList, (DNODE*)psTableEntry);

        /* Add to allocated list */
        vDLISTaddToTail(&psCommon->lAlarmsAllocList, (DNODE*)psTableEntry);

#ifdef CLD_ALARMS_ATTR_ALARM_COUNT
        if(((tsCLD_Alarms*)psClusterInstance->pvEndPointSharedStructPtr)->u16AlarmCount < CLD_ALARMS_MAX_NUMBER_OF_ALARMS)
        {
            ((tsCLD_Alarms*)psClusterInstance->pvEndPointSharedStructPtr)->u16AlarmCount++;
        }
#endif

    }

    /* Fill in table entry */
    psTableEntry->u8AlarmCode           = u8AlarmCode;
    psTableEntry->u16ClusterId          = u16ClusterId;
    psTableEntry->u32TimeStamp          = u32TimeStamp;

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return E_ZCL_SUCCESS;

}


/****************************************************************************
 **
 ** NAME:       eCLD_AlarmsGetAlarmFromLog
 **
 ** DESCRIPTION:
 ** Gets an alarm from the table. This also deletes the log entry.
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** tsZCL_ClusterInstance       *psClusterInstance
 ** uint8                       *pu8AlarmCode                  Alarm Code
 ** uint16                      *pu16ClusterId                 Cluster Id
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_AlarmsGetAlarmFromLog(
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance,
                    uint8                       *pu8AlarmCode,
                    uint16                      *pu16ClusterId,
                    uint32                      *pu32TimeStamp)
{

    tsCLD_AlarmsTableEntry *psTableEntry;
    tsCLD_AlarmsCustomDataStructure *psCommon;

    /* Parameter check */
    #ifdef STRICT_PARAM_CHECK
        if((psEndPointDefinition == NULL)           ||
           (psClusterInstance == NULL))
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    psCommon = (tsCLD_AlarmsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif


    /* Get earliest entry in the log */
    psTableEntry = psCLD_AlarmsGetEarliestEntry(psClusterInstance);
    if(psTableEntry == NULL)
    {
        #ifndef COOPERATIVE
            eZCL_ReleaseMutex(psEndPointDefinition);
        #endif


        DBG_vPrintf(TRACE_ALARMS, "Error: Log empty\r\n");

        return E_ZCL_FAIL;
    }

    *pu8AlarmCode = psTableEntry->u8AlarmCode;
    *pu16ClusterId = psTableEntry->u16ClusterId;
    *pu32TimeStamp = psTableEntry->u32TimeStamp;

    /* Remove from list of allocated table entries */
    psDLISTremove(&psCommon->lAlarmsAllocList, (DNODE*)psTableEntry);

    /* Add to unallocated list */
    vDLISTaddToTail(&psCommon->lAlarmsDeAllocList, (DNODE*)psTableEntry);

#ifdef CLD_ALARMS_ATTR_ALARM_COUNT
        ((tsCLD_Alarms*)psClusterInstance->pvEndPointSharedStructPtr)->u16AlarmCount--;
#endif

    // release EP
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return E_ZCL_SUCCESS;

}

/****************************************************************************
 **
 ** NAME:       PUBLIC eCLD_AlarmsCountAlarms
 **
 ** DESCRIPTION:
 ** Returns the number of alarms
 **
 ** PARAMETERS:                 Name                           Usage
 ** tsZCL_EndPointDefinition    *psEndPointDefinition
 ** tsZCL_ClusterInstance       *psClusterInstance
 ** uint16                      *pu16NumberOfScenes
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eCLD_AlarmsCountAlarms(
                            tsZCL_EndPointDefinition    *psEndPointDefinition,
                            tsZCL_ClusterInstance       *psClusterInstance,
                            uint8                       *pu8NumberOfAlarms)
{

    tsCLD_AlarmsCustomDataStructure *psCommon;
    
    #ifdef STRICT_PARAM_CHECK	
        /* Parameter check */
        if((psEndPointDefinition == NULL)   ||
           (psClusterInstance == NULL)      ||
           (pu8NumberOfAlarms == NULL))
        {   
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif
    psCommon = (tsCLD_AlarmsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    *pu8NumberOfAlarms = (uint8)iDLISTnumberOfNodes(&psCommon->lAlarmsAllocList);

    return E_ZCL_SUCCESS;

}

/****************************************************************************/
/***        Private Functions                                             ***/
/****************************************************************************/

PRIVATE tsCLD_AlarmsTableEntry *psCLD_AlarmsGetEarliestEntry(tsZCL_ClusterInstance *psClusterInstance)
{

    int n;
    tsCLD_AlarmsTableEntry *psTableEntry;
    tsCLD_AlarmsTableEntry *psEarliestTableEntry;
    tsCLD_AlarmsCustomDataStructure *psCommon;

    psCommon = (tsCLD_AlarmsCustomDataStructure*)psClusterInstance->pvEndPointCustomStructPtr;

    /* Point to start of list */
    psTableEntry = (tsCLD_AlarmsTableEntry*)psDLISTgetHead(&psCommon->lAlarmsAllocList);
    psEarliestTableEntry = psTableEntry;

    for(n = 0; n < iDLISTnumberOfNodes(&psCommon->lAlarmsAllocList); n++)
    {

        /* If entry is valid and older than last one we looked at, mark this as oldest */
        if((psTableEntry != NULL) && (psTableEntry->u32TimeStamp < psEarliestTableEntry->u32TimeStamp))
        {
            psEarliestTableEntry = psTableEntry;
        }

        psTableEntry = (tsCLD_AlarmsTableEntry*)psDLISTgetNext((DNODE*)psTableEntry);
    }

    return psEarliestTableEntry;

}


PRIVATE bool bCLD_AlarmsSearchForAlarm(void *pvSearchParam, void *psNodeUnderTest)
{

    tsCLD_AlarmsMatch sSearchParameter;
    tsCLD_AlarmsTableEntry sSearchEntry;

    memcpy(&sSearchParameter, pvSearchParam, sizeof(tsCLD_AlarmsMatch));
    memcpy(&sSearchEntry, psNodeUnderTest, sizeof(tsCLD_AlarmsTableEntry));

    DBG_vPrintf(TRACE_ALARMS, "Search: A%04x C%02x:A%04x C%02x\r\n", sSearchParameter.u8AlarmCode,
                                                                     sSearchParameter.u16ClusterId,
                                                                     sSearchEntry.u8AlarmCode,
                                                                     sSearchEntry.u16ClusterId);

    if((sSearchParameter.u8AlarmCode == sSearchEntry.u8AlarmCode) &&
       (sSearchParameter.u16ClusterId == sSearchEntry.u16ClusterId))
    {
        return TRUE;
    }

    return FALSE;

}
#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
