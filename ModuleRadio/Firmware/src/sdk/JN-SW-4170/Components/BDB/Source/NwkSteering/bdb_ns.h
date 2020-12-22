/*###############################################################################
#
# MODULE:      BDB
#
# COMPONENT:   bdb_ns.h
#
# AUTHOR:      
#
# DESCRIPTION: BDB NetworkSteering API 
#              
#
# $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/BDB/Trunk/Source/NwkSteering/bdb_ns.h $
#
# $Revision: 77426 $
#
# $LastChangedBy: nxp46755 $
#
# $LastChangedDate: 2016-02-29 10:51:44 +0000 (Mon, 29 Feb 2016) $
#
# $Id: bdb_ns.h 77426 2016-02-29 10:51:44Z nxp46755 $
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

#ifndef BDB_NS_INCLUDED
#define BDB_NS_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include "bdb_api.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef enum
{
    E_NS_IDLE,
    E_NS_WAIT_DISCOVERY,
    E_NS_WAIT_JOIN,
    E_NS_TCLK_WAIT_NODE_DESC_RES,
    E_NS_WAIT_AFTER_NWK_JOIN,
    E_NS_TCLK_WAIT_SEND_REQ_KEY,
    E_NS_TCLK_WAIT_LEAVE_CFM,
}teNS_State;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC BDB_teStatus BDB_eNsStartNwkSteering(void);
PUBLIC void BDB_vNsStateMachine(BDB_tsZpsAfEvent *psZpsAfEvent);
PUBLIC void BDB_vNsTimerCb(void *pvParam);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern PUBLIC teNS_State eNS_State;
extern PUBLIC uint8 u8TimerBdbNs;

#if defined __cplusplus
}
#endif

#endif  /* BDB_NS_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/






