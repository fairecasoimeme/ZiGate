/*****************************************************************************
 *
 * MODULE:             ZPS NWK
 *
 * COMPONENT:          zps_nwk_sec.h
 *
 * AUTHOR:             Mark SHea
 *
 * DESCRIPTION:        ZPS NWK Security defines
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Zigbee%20Protocol%20Stack/Modules/NWK/Trunk/Include/zps_nwk_sec.h $
 *
 * $Revision: 90751 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2017-10-25 15:39:45 +0100 (Wed, 25 Oct 2017) $
 *
 * $Id: zps_nwk_sec.h 90751 2017-10-25 14:39:45Z nxp29741 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
 * Copyright NXP B.V. 2016. All rights reserved
 *
 ****************************************************************************/

/**
 * @defgroup g_zps_nwk ZPS Network Layer infrastructure
 */

#ifndef _zps_nwk_sec_h_
#define _zps_nwk_sec_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/
#include "jendefs.h"
#if (defined JENNIC_CHIP_FAMILY_JN516x) || (defined JENNIC_CHIP_FAMILY_JN517x)
#include "AHI_AES.h"
#else
#include "aessw_ccm.h"
#endif
#include "pdum_nwk.h"

/************************/
/**** MACROS/DEFINES ****/
/************************/

#define ZPS_SEC_KEY_LENGTH                  16

/* Security Levels */
#define ZPS_NWK_SEC_SECURITY_LEVEL_0        0       /* No Security */
#define ZPS_NWK_SEC_SECURITY_LEVEL_1        1       /* MIC-32 */
#define ZPS_NWK_SEC_SECURITY_LEVEL_2        2       /* MIC-64 */
#define ZPS_NWK_SEC_SECURITY_LEVEL_3        3       /* MIC-128 */
#define ZPS_NWK_SEC_SECURITY_LEVEL_4        4       /* ENC */
#define ZPS_NWK_SEC_SECURITY_LEVEL_5        5       /* ENC-MIC-32 */
#define ZPS_NWK_SEC_SECURITY_LEVEL_6        6       /* ENC-MIC-64 */
#define ZPS_NWK_SEC_SECURITY_LEVEL_7        7       /* ENC-MIC-128 */

#define ZPS_NWK_SEC_SECURITY_LEVEL_MASK     0x07

/* Key Identifiers */
#define ZPS_NWK_SEC_DATA_KEY                0
#define ZPS_NWK_SEC_NETWORK_KEY             1
#define ZPS_NWK_SEC_KEY_TRANSPORT_KEY       2
#define ZPS_NWK_SEC_KEY_KOAD_KEY            3
#define ZPS_NWK_SEC_KEY_INVALID_KEY         0xFF

extern const uint32 g_u32NwkFcSaveCountBitShift;

/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/

typedef struct
{
    uint8 u8SecCtrl;
    uint32 u32FrameCounter;
    uint64 u64SrcAddr;
    uint8 u8KeySeqNum;
} ZPS_tsSecAuxHdr;

typedef void (*pfnCommandCallback) (uint8 u8CommandId, uint8 *pu8Buffer, uint8 u8Size);
/****************************/
/**** EXPORTED VARIABLES ****/
/****************************/


/****************************/
/**** EXPORTED FUNCTIONS ****/
/****************************/
#ifdef ZPS_NWK_OPT_FS_DYNAMIC_SEC_LVL
PUBLIC uint8 ZPS_u8NwkSecGetMicLen( uint8 u8SecurityLevel );
#endif
PUBLIC bool_t ZPS_bNwkSecFindMatSet( void *pvNwk, uint8 u8ActiveKSN, uint8 *u8SecMatIndex );
PUBLIC bool_t ZPS_bNwkSecCheckFC( void *pvNwk, uint64 u64SrcAddr, uint32 u32RecFC);
PUBLIC bool_t ZPS_bNwkSecHaveNetworkKey( void *pvNwk );
PUBLIC bool_t ZPS_bNwkSecCheckMatSet( void *pvNwk, uint8 u8ActiveKSN );
PUBLIC void ZPS_vNwkSecResetDevice(void *pvNwk,uint64 u64DevAddr);
PUBLIC bool_t ZPS_bSecEncrypt(void *pvNwk,
                              uint8 *pu8CurrHdr,
                              uint32 u32OutgoingFrameCounter,
                              bool_t bExtNonce,
                              AESSW_Block_u *puKey,
                              uint8 u8KeyId,
                              uint8 u8KeySeqNum,
                              PDUM_thNPdu hNPdu);
PUBLIC bool_t ZPS_bSecDecrypt(void *pvNwk,
                              ZPS_tsSecAuxHdr *psAuxSecHdr,
                              uint8 *pu8AuxSecHdr,
                              AESSW_Block_u *puKey,
                              PDUM_thNPdu hNPdu);

PUBLIC void ZPS_vNwkResetOutgoingFrameCounter(void *pvNwk);

PUBLIC void ZPS_vRegisterCommandCallback(void* pvFnCallback);
PUBLIC void ZPS_vSetBufferCommandCallback(uint8 *pu8Buffer);
#ifdef __cplusplus
};
#endif

#endif /* _zps_nwk_sec_h_ */

/* End of file $Id: zps_nwk_sec.h 90751 2017-10-25 14:39:45Z nxp29741 $ *******************************************/
