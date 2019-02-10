/*###############################################################################
#
# MODULE:      BDB
#
# COMPONENT:   bdb_start.h
#
# AUTHOR:
#
# DESCRIPTION: BDB Network Initialisation API
#
#
# $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/BDB/Trunk/Source/Common/bdb_start.h $
#
# $Revision: 86833 $
#
# $LastChangedBy: nxp29772 $
#
# $LastChangedDate: 2017-02-16 10:11:22 +0000 (Thu, 16 Feb 2017) $
#
# $Id: bdb_start.h 86833 2017-02-16 10:11:22Z nxp29772 $
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

#ifndef BDB_START_INCLUDED
#define BDB_START_INCLUDED

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
    E_INIT_IDLE,
    E_INIT_WAIT_REJOIN,
}teInitState;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void BDB_vInit(BDB_tsInitArgs *psInitArgs);
PUBLIC bool_t BDB_bIsBaseIdle(void);
PUBLIC void BDB_vStart(void);
PUBLIC void BDB_vInitStateMachine(BDB_tsZpsAfEvent *psZpsAfEvent);
PUBLIC uint8 BDB_u8PickChannel(uint32 u32ChannelMask);
PUBLIC void BDB_vRejoinCycle(bool_t bSkipDirectJoin);
PUBLIC void BDB_vRejoinSuccess(void);
PUBLIC void BDB_vRejoinTimerCb(void *pvParam);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern PUBLIC uint8 au8DefaultTCLinkKey[16];
extern PUBLIC uint8 au8DistributedLinkKey[16];
extern PUBLIC uint8 au8PreConfgLinkKey[16];
#if (defined JENNIC_CHIP_FAMILY_JN516x) || (defined JENNIC_CHIP_FAMILY_JN517x)
extern PUBLIC tsReg128 sTLMasterKey;
extern PUBLIC tsReg128 sTLCertKey;
#else
extern PUBLIC uint8 au8TLMasterKey[16];
extern PUBLIC uint8 au8TLCertKey[16];
#endif

extern PUBLIC teInitState eInitState;
extern PUBLIC bool_t bAssociationJoin;
extern PUBLIC uint8 u8RejoinCycles;
extern PUBLIC uint8 u8TimerBdbRejoin;

#if defined __cplusplus
}
#endif

#endif  /* BDB_START_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/






