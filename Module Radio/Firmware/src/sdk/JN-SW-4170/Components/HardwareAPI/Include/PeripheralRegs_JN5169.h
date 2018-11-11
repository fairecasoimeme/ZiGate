/*****************************************************************************
 *
 * MODULE:             Application Hardware API: peripheral registers
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

#include "PeripheralRegs_JN516x.h"

#ifndef _periph_reg_jn5169_h_
#define _periph_reg_jn5169_h_

#ifdef __cplusplus
extern "C" {
#endif

/*** FLASH_REMAP 2 ***/
#define REG_SYS_FLASH_REMAP2_8_BIT                      0
#define REG_SYS_FLASH_REMAP2_8_MASK                     ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP2_8_BIT))
#define REG_SYS_FLASH_REMAP2_9_BIT                      4
#define REG_SYS_FLASH_REMAP2_9_MASK                     ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP2_9_BIT))
#define REG_SYS_FLASH_REMAP2_10_BIT                     8
#define REG_SYS_FLASH_REMAP2_10_MASK                    ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP2_10_BIT))
#define REG_SYS_FLASH_REMAP2_11_BIT                     12
#define REG_SYS_FLASH_REMAP2_11_MASK                    ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP2_11_BIT))
#define REG_SYS_FLASH_REMAP2_12_BIT                     16
#define REG_SYS_FLASH_REMAP2_12_MASK                    ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP2_12_BIT))
#define REG_SYS_FLASH_REMAP2_13_BIT                     20
#define REG_SYS_FLASH_REMAP2_13_MASK                    ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP2_13_BIT))
#define REG_SYS_FLASH_REMAP2_14_BIT                     24
#define REG_SYS_FLASH_REMAP2_14_MASK                    ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP2_14_BIT))
#define REG_SYS_FLASH_REMAP2_15_BIT                     28
#define REG_SYS_FLASH_REMAP2_15_MASK                    ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP2_15_BIT))

/*** TEST 3V Additional Definitions ***/
#define REG_SYSCTRL_TEST_3V_TST_XTAL_BIAS_RTRIM_BIT     13
#define REG_SYSCTRL_TEST_3V_TST_XTAL_BIAS_RTRIM_MASK    ((uint32)(BIT_W_2 << REG_SYSCTRL_TEST_3V_TST_XTAL_BIAS_RTRIM_BIT))
// labelled as REG_SYSCTRL_TEST_3V_TST_XTAL_PULL_3V in 6x definitions
#define REG_SYSCTRL_TEST_3V_TST_XTAL_CTRIM_BIT          20
#define REG_SYSCTRL_TEST_3V_TST_XTAL_CTRIM_MASK         ((uint32)(BIT_W_2 << REG_SYSCTRL_TEST_3V_TST_XTAL_CTRIM_BIT))

/*** PWRCTRL2 Additional Definitions ***/
#define REG_SYSCTRL_PWRCTRL2_AD_LOC_BIT                 11
#define REG_SYSCTRL_PWRCTRL2_AD_LOC_MASK                ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_AD_LOC_BIT))

/*** REG_ANPER_CTRL_ADCSEL Mask now 4 bits wide - 6x version overwritten here  ***/
#undef REG_ANPER_CTRL_ADCSEL_MASK
#define REG_ANPER_CTRL_ADCSEL_MASK                      ((uint32)(BIT_W_4 << REG_ANPER_CTRL_ADCSEL_BIT))

typedef enum
{
    REG_SYS_FLASH_REMAP2  = 60,
} tePeriphReg_JN5169;

#ifdef __cplusplus
};
#endif

#endif // _periph_reg_jn5169_h_
