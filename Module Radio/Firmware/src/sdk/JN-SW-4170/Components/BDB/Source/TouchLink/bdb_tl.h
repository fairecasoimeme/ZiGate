/*###############################################################################
#
# MODULE:      BDB
#
# COMPONENT:   bdb_tl.h
#
# AUTHOR:      
#
# DESCRIPTION: BDB Touchlink API 
#              
#
# $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/BDB/Trunk/Source/TouchLink/bdb_tl.h $
#
# $Revision: 86278 $
#
# $LastChangedBy: nxp29741 $
#
# $LastChangedDate: 2017-01-18 10:35:23 +0000 (Wed, 18 Jan 2017) $
#
# $Id: bdb_tl.h 86278 2017-01-18 10:35:23Z nxp29741 $
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

#ifndef BDB_TL_INCLUDED
#define BDB_TL_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define ADJUST_POWER   TRUE

#if JENNIC_CHIP==JN5169
#define TX_POWER_NORMAL     ((uint32)(8))
#define TX_POWER_LOW        ((uint32)(0))
#else
#define TX_POWER_NORMAL     ((uint32)(3))
#define TX_POWER_LOW        ((uint32)(-9))
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/



/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void BDB_vTlInit(void);
PUBLIC bool BDB_bTlTouchLinkInProgress( void);
PUBLIC bool bIsTlStarted(void);
PUBLIC void BDB_vTlStateMachine( tsBDB_ZCLEvent *psEvent);

PUBLIC uint8 BDB_u8TlEncryptKey( uint8* au8InData,
                                  uint8* au8OutData,
                                  uint32 u32TransId,
                                  uint32 u32ResponseId,
                                  uint8 u8KeyIndex);
PUBLIC uint8 BDB_eTlDecryptKey( uint8* au8InData,
                                  uint8* au8OutData,
                                  uint32 u32TransId,
                                  uint32 u32ResponseId,
                                  uint8 u8KeyIndex);
PUBLIC bool BDB_bTlIsKeySupported(uint8 u8KeyIndex);
PUBLIC uint8 BDB_u8TlGetRandomPrimary(void);
PUBLIC uint8 BDB_u8TlNewUpdateID(uint8 u8ID1, uint8 u8ID2 );
#if (defined JENNIC_CHIP_FAMILY_JN516x) || (defined JENNIC_CHIP_FAMILY_JN517x)
PUBLIC void vECB_Decrypt(uint8* au8Key,
                         uint8* au8InData,
                         uint8* au8OutData);
#endif
PUBLIC void BDB_vTlTimerCb(void *pvParam);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern PUBLIC uint8 u8TimerBdbTl;

#if defined __cplusplus
}
#endif

#endif  /* BDB_TL_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/






