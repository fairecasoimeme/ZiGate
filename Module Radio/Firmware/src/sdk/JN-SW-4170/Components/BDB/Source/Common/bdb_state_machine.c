/*###############################################################################
#
# MODULE:      BDB
#
# COMPONENT:   bdb_state_machine.c
#
# AUTHOR:      
#
# DESCRIPTION: BDB handling of APP_vGenCallback and bdb_taskBDB
#              
#
# $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/BDB/Trunk/Source/Common/bdb_state_machine.c $
#
# $Revision: 81673 $
#
# $LastChangedBy: nxp29772 $
#
# $LastChangedDate: 2016-07-19 15:58:31 +0100 (Tue, 19 Jul 2016) $
#
# $Id: bdb_state_machine.c 81673 2016-07-19 14:58:31Z nxp29772 $
#
###############################################################################
#
# This software is owned by NXP B.V. and/or its supplier and is protected
# under applicable copyright laws. All rights are reserved. We grant You,
# and any third parties, a license to use this software solely and
# exclusively on NXP products [NXP Microcontrollers such as JN514x, JN516x, JN517x].
# You, and any third parties must reproduce the copyright and warranty notice 
# and any other legend of ownership on each  copy or partial copy of the software.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
# POSSIBILITY OF SUCH DAMAGE. 
# 
# Copyright NXP B.V. 2015-2016. All rights reserved
#
###############################################################################*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "bdb_api.h"
#include "bdb_start.h"
#if ((defined BDB_SUPPORT_FIND_AND_BIND_INITIATOR) || (defined BDB_SUPPORT_FIND_AND_BIND_TARGET))
#include "bdb_fb_api.h"
#endif
#if (defined BDB_SUPPORT_TOUCHLINK)
#include "bdb_tl.h"
#endif
#if (defined BDB_SUPPORT_NWK_STEERING)
#include "bdb_ns.h"
#endif
#if (defined BDB_SUPPORT_NWK_FORMATION)
#include "bdb_nf.h"
#endif
#if (defined BDB_SUPPORT_OOBC)
#include "bdb_DeviceCommissioning.h"
#endif
#include "dbg.h"
#include "bdb_fr.h"
#include <string.h>
#include <stdlib.h>
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
PUBLIC tsBDB sBDB;

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME: APP_vGenCallback
 *
 * DESCRIPTION:
 * Event handler called by ZigBee PRO Stack
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void APP_vGenCallback(uint8 u8Endpoint, ZPS_tsAfEvent *psStackEvent)
{
    BDB_tsZpsAfEvent sZpsAfEvent;

    DBG_vPrintf(TRACE_BDB, "BDB: APP_vGenCallback [%d %d] \n", u8Endpoint, psStackEvent->eType);

    /* Before passing to queue; copy is required to combine two arguments from stack */
    sZpsAfEvent.u8EndPoint = u8Endpoint;
    memcpy(&sZpsAfEvent.sStackEvent, psStackEvent, sizeof(ZPS_tsAfEvent));

    /* Post the task to break stack context */
    if(ZQ_bQueueSend(sBDB.hBdbEventsMsgQ, &sZpsAfEvent) == FALSE)
    {
        DBG_vPrintf(TRACE_BDB, "BDB: Failed to post zpsEvent %d \n", psStackEvent->eType);
    }
}
/****************************************************************************
 *
 * NAME: bdb_taskBDB
 *
 * DESCRIPTION:
 * Processes events from the bdb event queue
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void bdb_taskBDB(void)
{
    BDB_tsZpsAfEvent sZpsAfEvent;
    BDB_tsBdbEvent sBDBEvent = {0};

    while(ZQ_bQueueReceive(sBDB.hBdbEventsMsgQ, &sZpsAfEvent))
    {
        /* Do not transmit link key for know node rejoins and BDB_JOIN_USES_INSTALL_CODE_KEY is TRUE */
        #if ((BDB_SET_DEFAULT_TC_POLICY == TRUE) &&  (BDB_JOIN_USES_INSTALL_CODE_KEY == TRUE))
            if((ZPS_ZDO_DEVICE_COORD == ZPS_eAplZdoGetDeviceType()) &&
               (ZPS_EVENT_TC_STATUS == sZpsAfEvent.sStackEvent.eType) &&
               (0x00 == sZpsAfEvent.sStackEvent.uEvent.sApsTcEvent.u8Status))
            {
                uint64 u64DeviceAddr;

                u64DeviceAddr = ZPS_u64NwkNibGetMappedIeeeAddr(ZPS_pvAplZdoGetNwkHandle(),
                                                               sZpsAfEvent.sStackEvent.uEvent.sApsTcEvent.uTcData.pKeyDesc->u16ExtAddrLkup);
                DBG_vPrintf(TRACE_BDB,"ZPS_EVENT_TC_STATUS %016llx \n",u64DeviceAddr);
                ZPS_bAplZdoTrustCenterSetDevicePermissions(u64DeviceAddr,
                                                           ZPS_DEVICE_PERMISSIONS_JOIN_DISALLOWED);
            }
        #endif
        /* Call BDB state machines */
        BDB_vFrStateMachine(&sZpsAfEvent); // Failure Recovery

        BDB_vInitStateMachine(&sZpsAfEvent);

        #if (defined BDB_SUPPORT_NWK_STEERING)
            BDB_vNsStateMachine(&sZpsAfEvent);
        #endif

        #if (defined BDB_SUPPORT_NWK_FORMATION)
            BDB_vNfStateMachine(&sZpsAfEvent);
        #endif

        #if (defined BDB_SUPPORT_FIND_AND_BIND_INITIATOR)
            vFbZdpHandler(&sZpsAfEvent.sStackEvent);
        #endif

        #if (defined BDB_SUPPORT_OOBC)
            BDB_vOutOfBandCommissionHandleEvent(&sZpsAfEvent);
        #endif

        /* Call application */
        sBDBEvent.eEventType = BDB_EVENT_ZPSAF;
        memcpy(&sBDBEvent.uEventData.sZpsAfEvent,&sZpsAfEvent,sizeof(BDB_tsZpsAfEvent));
        APP_vBdbCallback(&sBDBEvent);
    }
}

/****************************************************************************
 *
 * NAME: BDB_vZclEventHandler
 *
 * DESCRIPTION:
 *
 *
 * PARAMETERS:      Name            RW  Usage
 *
 *
 * RETURNS:
 *
 *
 * NOTES:
 *
 ****************************************************************************/
PUBLIC void BDB_vZclEventHandler(tsBDB_ZCLEvent *psEvent)
{
    DBG_vPrintf(TRACE_BDB, "BDB ZCL Event %d\n", psEvent->eType);
    if ( (psEvent->eType > BDB_E_ZCL_EVENT_NONE)  &&
         (psEvent->eType < BDB_E_ZCL_EVENT_IDENTIFY_QUERY))
    {
        #if (defined BDB_SUPPORT_TOUCHLINK)
            BDB_vTlStateMachine(psEvent);
        #endif
    }
    else if (psEvent->eType >= BDB_E_ZCL_EVENT_IDENTIFY_QUERY)
    {
        #if ((defined BDB_SUPPORT_FIND_AND_BIND_INITIATOR) || (defined BDB_SUPPORT_FIND_AND_BIND_TARGET))
            BDB_vFbZclHandler(psEvent->eType,psEvent->psCallBackEvent);// identify query response or identify
        #endif
    }
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/


/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
