/*****************************************************************************
 *
 * MODULE:             Application Hardware API
 *
 * DESCRIPTION:        Abstraction of the hardware peripherals available on the
 *                     802.15.4 chip that are not used directly for 802.15.4,
 *                     such as UARTs and timers.
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
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ***************************************************************************/

#ifndef  AHI_JN5169_H_INCLUDED
#define  AHI_JN5169_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include <jendefs.h>

#include "AppHardwareApi_JN516x.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Version number of module */
/*****************************************************************
[31:24] = Family : 4 (JN516x) / 3 (JN514x) / 0 (JN513x)
[23:16] = Part : 0x0b (JN5169) /8 (JN5168) / 5 (JN5142) / 4 (JN5148) / 1 (JN5139)
[15: 0] = AHI Version (increment for each new release/patch)
******************************************************************/
#undef AHI_VERSION
#define AHI_VERSION                0x040b0000

/* Extra E_AHI_ADC_SRC_x values are defined in AppHardwareApi_JN516x.h */
#define E_AHI_ADC_SRC_ADC_5            8
#define E_AHI_ADC_SRC_ADC_6            9
#define E_AHI_ADC_SRC_VTUNE            10

#define E_AHI_ADC_DMA_SRC_ADC_5_MASK        (1 << E_AHI_ADC_SRC_ADC_5)
#define E_AHI_ADC_DMA_SRC_ADC_6_MASK        (1 << E_AHI_ADC_SRC_ADC_6)
#define E_AHI_ADC_DMA_SRC_VTUNE_MASK        (1 << E_AHI_ADC_SRC_VTUNE)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum
{
    SIS_ADDR_STATUS_PRIMARY_WR_TRANSFER=0,
    SIS_ADDR_STATUS_SECONDARY_WR_TRANSFER=2,
    SIS_ADDR_STATUS_GENERAL_CALL_WR_TRANSFER=4,
    SIS_ADDR_STATUS_PRIMARY_RD_TRANSFER=8,
    SIS_ADDR_STATUS_SECONDARY_RD_TRANSFER=16
} teSISAddrStatus;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC bool_t bAHI_SiSlavePollBusy(void);

PUBLIC void vAHI_SiSlaveWriteSlaveSecondryAddr(
    uint8       u8SlaveSecondryAddress);

PUBLIC teSISAddrStatus eAHI_SiSlaveAddressStatus(void);

PUBLIC void vAHI_SiSlaveAddressMask(
    bool_t      bGeneralCall,
    bool_t      bSecondryAddress,
    bool_t      bPrimaryAddress);

PUBLIC void vAHI_AntennaDiversitySetPinLocation(
    bool_t      bLocationDIO0_1);

PUBLIC void vAHI_RadioSetReducedInputPower(bool_t bReduced);
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* AHI_JN5169_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
