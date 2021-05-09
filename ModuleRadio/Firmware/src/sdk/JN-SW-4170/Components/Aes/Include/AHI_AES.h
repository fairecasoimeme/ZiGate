/*****************************************************************************
 *
 * MODULE:              AHI AES engine
 *
 * DESCRIPTION:
 * AES coprocessor API bit masks, defines and function prototypes.
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139].
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
 * Copyright NXP B.V. 2012, 2018. All rights reserved
 *
 ***************************************************************************/

#ifndef  AHI_AES_H_INCLUDED
#define  AHI_AES_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include <jendefs.h>

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* HW CCM parameter limits */
#define M_MAX                               (16)
#define ALENGTH_MAX                         (31)
#define MLENGTH_MAX                         (127)
#if !(defined AES_BLOCK_SIZE)
#define AES_BLOCK_SIZE                      (16)
#endif

/* AES Encryption Modes */
#define XCV_REG_AES_SET_MODE_ECB          (0)
#if (defined JENNIC_HW_BBC_ISA) && (JENNIC_HW_BBC_ISA != 0)
/* Only JN5148 and older support this */
#define XCV_REG_AES_SET_MODE_CTR          (2)
#endif
#define XCV_REG_AES_SET_MODE_CCM          (3)
#define XCV_REG_AES_SET_MODE_CCM_D        (4)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

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

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/**************************/
/* ECB Encoding API Calls */
/**************************/
PUBLIC bool_t bACI_ECBencodeBuffer(
    tsReg128       *psKeyData,
    bool_t          bLoadKey,
    uint32          u32stripes,
    uint8          *pau8inputData,
    uint8          *pau8outputData,
    uint32         *pu32stripesComplete);

PUBLIC bool_t bACI_ECBencodeStripe(
    tsReg128       *psKeyData,
    bool_t          bLoadKey,
    tsReg128       *psInputData,
    tsReg128       *psOutputData);

PUBLIC void vACI_LoadKey(
    tsReg128       *psKeyData);

/********************************/
/* CCM* Encode/Decode API Calls */
/********************************/
/* There are several similar calls, for backwards compatibility across device
 * generations
 */

/* Full CCM operation with authentication and Encryption/Decryption. For older
 * devices with hardware ISA, supports CTR as well as CCM modes but a hardware
 * bug in some variants means that the output is non-standard. For newer
 * devices this is basically a wrapper for bAES_CCMstar so only CCM modes are
 * supported and the non-standard output is not supported.Input data size is
 * limited to 127 bytes as the function was mapped directly to the AES CCMstar
 * hardware.
 */
PUBLIC bool_t bACI_CCMstar(
    tsReg128       *psKeyData,
    bool_t          bLoadKey,
    uint8           u8AESmode,
    uint8           u8M,
    uint8           u8alength,
    uint8           u8mlength,
    tsReg128       *psNonce,
    uint8          *pau8authenticationData,
    uint8          *pau8inputData,
    uint8          *pau8outputData,
    uint8          *pau8checksumData,
    bool_t         *pbChecksumVerify);

/* Full CCM operation as above, but always uses software manipulation (from
 * deprecated AES_CCM_SW_PATCH API hence different module name) and hence
 * produces different results on older devices compared to bACI_CCMstar. This
 * function provides consistent output across all devices. Input data size is
 * limited to 127 bytes as the function was used patch the original CCMstar
 * hardware.
 */
PUBLIC bool_t bAES_CCMstar(
    tuAES_Block   *puKeyData,
    bool_t         bLoadKey,
    uint8          u8AESmode,
    uint8          u8M,
    uint8          u8alength,
    uint8          u8mlength,
    tuAES_Block   *puNonce,
    uint8         *pau8authenticationData,
    uint8         *pau8inputData,
    uint8         *pau8outputData,
    uint8         *pau8checksumData,
    bool_t        *pbChecksumVerify);

/* CCM* full operation (as bAES_CCMstar) but speed/memory optimised. Assumes:
 *   pau8authenticationData is word aligned
 *   pau8Data is word aligned
 *   puNonce has the first byte left free for the flags field to be added
 *   no more than 4096 bytes of data (256 blocks' worth)
 */
PUBLIC void vACI_OptimisedCcmStar(
    bool_t         bEncrypt,
    uint8          u8M,
    uint8          u8alength,
    uint8          u8mlength,
    tuAES_Block   *puNonce,
    uint8         *pau8authenticationData,
    uint8         *pau8Data,
    uint8         *pau8checksumData,
    bool_t        *pbChecksumVerify);

/*********************************/
/* CCM* Data Authentication only */
/*********************************/
PUBLIC bool_t bACI_CCMstarAuthenticateData(
    tsReg128      *psKeyData,
    bool_t         bLoadKey,
    uint8          u8AESmode,
    uint8          u8M,
    uint8          u8alength,
    tsReg128      *psNonce,
    uint8         *pau8authenticationData,
    uint8         *pau8checksumData,
    bool_t        *pbChecksumVerify);

/********************************/
/* CCM* Data Encode Decode Only */
/********************************/
PUBLIC bool_t bACI_CCMstarEncodeData(
    tsReg128     *psKeyData,
    bool_t        bLoadKey,
    uint8         u8mlength,
    tsReg128     *psNonce,
    uint8        *pau8inputData,
    uint8        *pau8outputData);

/************************************/
/* IEEE CTR Data Encode Decode Only */
/************************************/
PUBLIC bool_t bACI_IEEECTRencodeData(
    tsReg128     *psKeyData,
    bool_t        bLoadKey,
    uint8         u8mlength,
    tsReg128     *psNonce,
    uint8        *pau8inputData,
    uint8        *pau8outputData);

/***************************/
/* Miscellaneous functions */
/***************************/

PUBLIC void vACI_CmdWaitBusy(void);
PUBLIC bool_t bACI_WriteKey(tsReg128 *psKeyData);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* AHI_AES_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
