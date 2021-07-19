/*****************************************************************************
 *
 * MODULE:             AES_SW
 *
 * COMPONENT:          AESSW_CCM.h
 *
 * AUTHOR:             Mark Shea
 *
 * DESCRIPTION:        Software Implementation of CCM Star.
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/AES_SW/Trunk/Include/aessw_ccm.h $
 *
 * $Revision: 86214 $
 *
 * $LastChangedBy: nxp29736 $
 *
 * $LastChangedDate: 2017-01-16 17:09:38 +0000 (Mon, 16 Jan 2017) $
 *
 * $Id: aessw_ccm.h 86214 2017-01-16 17:09:38Z nxp29736 $
 *
 *****************************************************************************
 *
 * This software is owned by Jennic and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on Jennic products. You, and any third parties must reproduce
 * the copyright and warranty notice and any other legend of ownership on each
 * copy or partial copy of the software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
 * ACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,
 * BE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.
 *
 * Copyright Jennic Ltd. 2008 All rights reserved
 *
 ****************************************************************************/

#ifndef  AESSW_CCM__H_INCLUDED
#define  AESSW_CCM__H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#if (defined JENNIC_CHIP_FAMILY_JN516x) || (defined JENNIC_CHIP_FAMILY_JN517x)
#include "AHI_AES.h"
#else
#include "fsl_aes.h"
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
/* AES Encryption Modes */
#define XCV_REG_AES_SET_MODE_CCM          (3)
#define XCV_REG_AES_SET_MODE_CCM_D        (4)
#define AESSW_BLK_SIZE                    (16)

#if !(defined JENNIC_CHIP_FAMILY_JN516x) && !(defined JENNIC_CHIP_FAMILY_JN517x)
/* HW CCM parameter limits */
#define M_MAX                               (16)
#define ALENGTH_MAX                         (31)
#define MLENGTH_MAX                         (127)
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#if !(defined JENNIC_CHIP_FAMILY_JN516x) && !(defined JENNIC_CHIP_FAMILY_JN517x)
/* 128-bit data and config data structure */
typedef struct
{
    uint32 u32register0;
    uint32 u32register1;
    uint32 u32register2;
    uint32 u32register3;
} tsReg128;

/* Security block definition */
typedef union
{
    uint8    au8[AES_BLOCK_SIZE];
    uint32   au32[AES_BLOCK_SIZE / 4];
} tuAES_Block;

/* For backwards compatibility with deprecated AES_CCM_SW_PATCH files */
typedef tuAES_Block AESSW_Block_u;
#endif

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/* CCM* Encode/Decode API Calls */
/* full CCM operation with authentication and Encryption/Decryption */
PUBLIC bool_t
AESSW_bCCMstar(AESSW_Block_u *puKeyData,
               bool_t    bLoadKey,
               uint8     u8AESmode,
               uint8     u8M,
               uint8     u8alength,
               uint8     u8mlength,
               AESSW_Block_u *puNonce,
               uint8    *pau8authenticationData,
               uint8    *pau8inputData,
               uint8    *pau8outputData,
               uint8    *pau8checksumData,
               bool_t   *pbChecksumVerify);

/* HMAC MMO required by security functions */
PUBLIC void
AESSW_vHMAC_MMO(uint8 *pu8Data,
                int iDataLen,
                AESSW_Block_u *puKeyData,
                AESSW_Block_u *puHash);

/* MMO required by HMAC and other security functions */
PUBLIC void
AESSW_vMMOBlockUpdate(AESSW_Block_u *puHash,
                      AESSW_Block_u *puBlock);

PUBLIC void
AESSW_vMMOFinalUpdate(AESSW_Block_u *puHash,
                      uint8 *pu8Data,
                      int iDataLen,
                      int iFinalLen);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* AESSW_CCM__H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
