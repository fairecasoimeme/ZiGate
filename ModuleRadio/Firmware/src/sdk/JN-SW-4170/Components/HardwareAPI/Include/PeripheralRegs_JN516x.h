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

#ifndef _periph_reg_h_
#define _periph_reg_h_

#ifdef __cplusplus
extern "C" {
#endif

/************************/
/**** Includes       ****/
/************************/
#include "jendefs.h"
#include "AppHardwareApi.h"

/************************/
/**** MACROS/DEFINES ****/
/************************/
/* Macros to use r16 as offset into memory space
 * Register r16 is set to 0x02008000, so all peripheral register addresses
 * can be offset from this */

/* register access functions - use the NC versions where the address is Not Constant e.g. it changes within a loop */

#define R16_VALUE (0x02008000)

#define u32REG_Read(addr) \
     ({ uint32 __result; \
        asm volatile ("bg.lwz %[result], %[offset](r16);": [result] "=r" (__result): [offset] "i" ((addr) - R16_VALUE));  \
        __result; })

#define u32REG_ReadNC(addr)       \
     ({ uint32 __result, __u32Addr = (addr);   \
        asm volatile ("bn.lwz %[result], 0(%[address]);": [result] "=r" (__result): [address] "r" (__u32Addr));  \
        __result; })

#define vREG_Write(addr, u32Data) \
    asm volatile("bg.sw %[offset](r16), %[value];" : : [offset] "i" ((addr) - R16_VALUE), [value] "r" (u32Data) )

#define vREG_WriteNC(addr, u32Data) \
    { uint32 __u32Addr = (addr); \
      asm volatile("bn.sw 0(%[address]), %[value];" : : [address] "r" (__u32Addr), [value] "r" (u32Data) ); }



/* Bitfield definitions */
#ifndef BIT_W_1
#define BIT_W_1                         0x00000001UL
#define BIT_W_2                         0x00000003UL
#define BIT_W_3                         0x00000007UL
#define BIT_W_4                         0x0000000FUL
#define BIT_W_5                         0x0000001FUL
#define BIT_W_6                         0x0000003FUL
#define BIT_W_7                         0x0000007FUL
#define BIT_W_8                         0x000000FFUL
#define BIT_W_10                        0x00000BFFUL
#define BIT_W_12                        0x00000FFFUL
#define BIT_W_15                        0x00007FFFUL
#define BIT_W_16                        0x0000FFFFUL
#define BIT_W_18                        0x0003FFFFUL
#define BIT_W_20                        0x000FFFFFUL
#define BIT_W_21                        0x001FFFFFUL
#endif

/**** System controller: PWR_CTRL ****/
#define REG_SYSCTRL_PWRCTRL_PDR_BIT       0
#define REG_SYSCTRL_PWRCTRL_PDR_MASK      ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_PDR_BIT))
#define REG_SYSCTRL_PWRCTRL_DSS_BIT       1
#define REG_SYSCTRL_PWRCTRL_DSS_MASK      ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_DSS_BIT))
#define REG_SYSCTRL_PWRCTRL_PPDC_BIT      3
#define REG_SYSCTRL_PWRCTRL_PPDC_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_PPDC_BIT))
#define REG_SYSCTRL_PWRCTRL_SPIMEN_BIT    4
#define REG_SYSCTRL_PWRCTRL_SPIMEN_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_SPIMEN_BIT))
#define REG_SYSCTRL_PWRCTRL_MHUP_BIT      5
#define REG_SYSCTRL_PWRCTRL_MHUP_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_MHUP_BIT))
#define REG_SYSCTRL_PWRCTRL_UEN0_BIT      12
#define REG_SYSCTRL_PWRCTRL_UEN0_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_UEN0_BIT))
#define REG_SYSCTRL_PWRCTRL_UEN1_BIT      13
#define REG_SYSCTRL_PWRCTRL_UEN1_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_UEN1_BIT))
#define REG_SYSCTRL_PWRCTRL_T0EN_BIT      14
#define REG_SYSCTRL_PWRCTRL_T0EN_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_T0EN_BIT))
#define REG_SYSCTRL_PWRCTRL_SPISEN_BIT    15
#define REG_SYSCTRL_PWRCTRL_SPISEN_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_SPISEN_BIT))
#define REG_SYSCTRL_PWRCTRL_SIFEN_BIT     16
#define REG_SYSCTRL_PWRCTRL_SIFEN_MASK    ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_SIFEN_BIT))
#define REG_SYSCTRL_PWRCTRL_NASSEN_BIT    17
#define REG_SYSCTRL_PWRCTRL_NASSEN_MASK   ((uint32)(BIT_W_2 << REG_SYSCTRL_PWRCTRL_NASSEN_BIT))
#define REG_SYSCTRL_PWRCTRL_GPOSEN_BIT    19
#define REG_SYSCTRL_PWRCTRL_GPOSEN_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_GPOSEN_BIT))
#define REG_SYSCTRL_PWRCTRL_T4EN_BIT      20
#define REG_SYSCTRL_PWRCTRL_T4EN_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_T4EN_BIT))
#define REG_SYSCTRL_PWRCTRL_PD32K_BIT     21
#define REG_SYSCTRL_PWRCTRL_PD32K_MASK    ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_PD32K_BIT))
#define REG_SYSCTRL_PWRCTRL_APEN_BIT      22
#define REG_SYSCTRL_PWRCTRL_APEN_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_APEN_BIT))
#define REG_SYSCTRL_PWRCTRL_ADO_EN_BIT    23
#define REG_SYSCTRL_PWRCTRL_ADO_EN_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_ADO_EN_BIT))
#define REG_SYSCTRL_PWRCTRL_RFRXEN_BIT    24
#define REG_SYSCTRL_PWRCTRL_RFRXEN_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_RFRXEN_BIT))
#define REG_SYSCTRL_PWRCTRL_RFTXEN_BIT    25
#define REG_SYSCTRL_PWRCTRL_RFTXEN_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_RFTXEN_BIT))
#define REG_SYSCTRL_PWRCTRL_UARTFLOWEN_BIT 27
#define REG_SYSCTRL_PWRCTRL_UARTFLOWEN_MASK ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_UARTFLOWEN_BIT))
#define REG_SYSCTRL_PWRCTRL_T1EN_BIT      28
#define REG_SYSCTRL_PWRCTRL_T1EN_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_T1EN_BIT))
#define REG_SYSCTRL_PWRCTRL_T2EN_BIT      29
#define REG_SYSCTRL_PWRCTRL_T2EN_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_T2EN_BIT))
#define REG_SYSCTRL_PWRCTRL_T3EN_BIT      30
#define REG_SYSCTRL_PWRCTRL_T3EN_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_T3EN_BIT))
#define REG_SYSCTRL_PWRCTRL_ADE_EN_BIT    31
#define REG_SYSCTRL_PWRCTRL_ADE_EN_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_ADE_EN_BIT))

/**** New style definitions for PWM timers ****/
#define REG_SYSCTRL_PWRCTRL_PT1EN_BIT     28
#define REG_SYSCTRL_PWRCTRL_PT1EN_MASK    ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_PT1EN_BIT))
#define REG_SYSCTRL_PWRCTRL_PT2EN_BIT     29
#define REG_SYSCTRL_PWRCTRL_PT2EN_MASK    ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_PT2EN_BIT))
#define REG_SYSCTRL_PWRCTRL_PT3EN_BIT     30
#define REG_SYSCTRL_PWRCTRL_PT3EN_MASK    ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_PT3EN_BIT))
#define REG_SYSCTRL_PWRCTRL_PT4EN_BIT     20
#define REG_SYSCTRL_PWRCTRL_PT4EN_MASK    ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL_PT4EN_BIT))

/**** System controller: Pullup ****/
#define REG_SYSCTRL_PULLUP_D0PUDIS_BIT    22
#define REG_SYSCTRL_PULLUP_D0PUDIS_MASK ((uint32)(BIT_W_1 << REG_SYSCTRL_PULLUP_D0PUDIS_BIT))
#define REG_SYSCTRL_PULLUP_D1PUDIS_BIT    21
#define REG_SYSCTRL_PULLUP_D1PUDIS_MASK ((uint32)(BIT_W_1 << REG_SYSCTRL_PULLUP_D1PUDIS_BIT))

/**** System controller: PWR_CTRL2 ****/
#define REG_SYSCTRL_PWRCTRL2_SIFSEL_BIT       0
#define REG_SYSCTRL_PWRCTRL2_SIFSEL_MASK      ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_SIFSEL_BIT))
#define REG_SYSCTRL_PWRCTRL2_UART1_LOC_BIT    1
#define REG_SYSCTRL_PWRCTRL2_UART1_LOC_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_UART1_LOC_BIT))
#define REG_SYSCTRL_PWRCTRL2_U1RXD_BIT        2
#define REG_SYSCTRL_PWRCTRL2_U1RXD_MASK       ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_U1RXD_BIT))
#define REG_SYSCTRL_PWRCTRL2_SI_LOC_BIT       3
#define REG_SYSCTRL_PWRCTRL2_SI_LOC_MASK      ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_SI_LOC_BIT))
#define REG_SYSCTRL_PWRCTRL2_UART0_LOC_BIT    4
#define REG_SYSCTRL_PWRCTRL2_UART0_LOC_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_UART0_LOC_BIT))
#define REG_SYSCTRL_PWRCTRL2_PWM_LOC_BIT      5
#define REG_SYSCTRL_PWRCTRL2_PWM_LOC_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_PWM_LOC_BIT))
#define REG_SYSCTRL_PWRCTRL2_TIMER0_LOC_BIT   6
#define REG_SYSCTRL_PWRCTRL2_TIMER0_LOC_MASK  ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_TIMER0_LOC_BIT))
#define REG_SYSCTRL_PWRCTRL2_SPISEL1_LOC_BIT  7
#define REG_SYSCTRL_PWRCTRL2_SPISEL1_LOC_MASK ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_SPISEL1_LOC_BIT))
#define REG_SYSCTRL_PWRCTRL2_SPISEL2_LOC_BIT  8
#define REG_SYSCTRL_PWRCTRL2_SPISEL2_LOC_MASK ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_SPISEL2_LOC_BIT))
#define REG_SYSCTRL_PWRCTRL2_PWM_LOC2_BIT     9
#define REG_SYSCTRL_PWRCTRL2_PWM_LOC2_MASK    ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_PWM_LOC2_BIT))
#define REG_SYSCTRL_PWRCTRL2_SPIS_LOC_BIT     10
#define REG_SYSCTRL_PWRCTRL2_SPIS_LOC_MASK    ((uint32)(BIT_W_1 << REG_SYSCTRL_PWRCTRL2_SPIS_LOC_BIT))

/**** System controller: Status register ****/
#define REG_SYSCTRL_STAT_WUS_BIT        0
#define REG_SYSCTRL_STAT_WUS_MASK       ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_WUS_BIT))
#define REG_SYSCTRL_STAT_MS_BIT         1
#define REG_SYSCTRL_STAT_MS_MASK        ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_MS_BIT))
#define REG_SYSCTRL_STAT_APPS_BIT       2
#define REG_SYSCTRL_STAT_APPS_MASK      ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_APPS_BIT))
#define REG_SYSCTRL_STAT_PROPS_BIT      3
#define REG_SYSCTRL_STAT_PROPS_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_PROPS_BIT))
#define REG_SYSCTRL_STAT_MISOS_BIT      4
#define REG_SYSCTRL_STAT_MISOS_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_MISOS_BIT))
#define REG_SYSCTRL_STAT_VBO_BIT        5
#define REG_SYSCTRL_STAT_VBO_MASK       ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_VBO_BIT))
#define REG_SYSCTRL_STAT_VBO_VAL_BIT    6
#define REG_SYSCTRL_STAT_VBO_VAL_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_VBO_VAL_BIT))
#define REG_SYSCTRL_STAT_WD_RES_BIT     7
#define REG_SYSCTRL_STAT_WD_RES_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_WD_RES_BIT))
#define REG_SYSCTRL_STAT_VBO_RES_BIT    8
#define REG_SYSCTRL_STAT_VBO_RES_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_VBO_RES_BIT))
#define REG_SYSCTRL_STAT_CLK32K_BIT     9
#define REG_SYSCTRL_STAT_CLK32K_MASK    ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_CLK32K_BIT))
#define REG_SYSCTRL_STAT_CLK32K_RDY_BIT 10
#define REG_SYSCTRL_STAT_CLK32K_RDY_MASK ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_CLK32K_RDY_BIT))
#define REG_SYSCTRL_STAT_WDS_BIT        11
#define REG_SYSCTRL_STAT_WDS_MASK       ((uint32)(BIT_W_1 << REG_SYSCTRL_STAT_WDS_BIT))

/**** System controller: Wake event registers ****/
#define REG_SYSCTRL_WKE_GE_BIT          0
#define REG_SYSCTRL_WKE_GE_MASK         ((uint32)(BIT_W_20 << REG_SYSCTRL_WKE_GE_BIT))
#define REG_SYSCTRL_WKE_WTES_BIT        26
#define REG_SYSCTRL_WKE_WTES_MASK       ((uint32)(BIT_W_2 << REG_SYSCTRL_WKE_WTES_BIT))
#define REG_SYSCTRL_WKE_CTRT_BIT        28
#define REG_SYSCTRL_WKE_CE_BIT          28
#define REG_SYSCTRL_WKE_CE_MASK         ((uint32)(BIT_W_1 << REG_SYSCTRL_WKE_CE_BIT))

/**** System Interrupt Mask - SYS_IM (WK_EM) ****/
#define REG_SYSCTRL_WK_EM_PCEM_BIT      22
#define REG_SYSCTRL_WK_EM_PCEM_MASK     ((uint32)(BIT_W_2 << REG_SYSCTRL_WK_EM_PCEM_BIT))
#define REG_SYSCTRL_WK_EM_VFEM_BIT      24
#define REG_SYSCTRL_WK_EM_VFEM_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_WK_EM_VFEM_BIT))
#define REG_SYSCTRL_WK_EM_VREM_BIT      25
#define REG_SYSCTRL_WK_EM_VREM_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_WK_EM_VREM_BIT))
#define REG_SYSCTRL_WK_EM_WTEM_BIT      26
#define REG_SYSCTRL_WK_EM_WTEM_MASK     ((uint32)(BIT_W_2 << REG_SYSCTRL_WK_EM_WTEM_BIT))
#define REG_SYSCTRL_WK_EM_CEM_BIT       28
#define REG_SYSCTRL_WK_EM_CEM_MASK      ((uint32)(BIT_W_1 << REG_SYSCTRL_WK_EM_CEM_BIT))
#define REG_SYSCTRL_WK_EM_FLEM_BIT      29
#define REG_SYSCTRL_WK_EM_FLEM_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_WK_EM_FLEM_BIT))
#define REG_SYSCTRL_RNDEM_BIT           30
#define REG_SYSCTRL_RNDEM_MASK          ((uint32)(BIT_W_1 << REG_SYSCTRL_RNDEM_BIT))
#define REG_SYSCTRL_CKEM_BIT            31
#define REG_SYSCTRL_CKEM_MASK           ((uint32)(BIT_W_1 << REG_SYSCTRL_CKEM_BIT))

/**** System Interrupt Status - SYS_IS (WK_ES) ****/
#define REG_SYSCTRL_WK_ES_PCES_BIT      22
#define REG_SYSCTRL_WK_ES_PCES_MASK     ((uint32)(BIT_W_2 << REG_SYSCTRL_WK_ES_PCES_BIT))
#define REG_SYSCTRL_WK_ES_VFES_BIT      24
#define REG_SYSCTRL_WK_ES_VFES_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_WK_ES_VFES_BIT))
#define REG_SYSCTRL_WK_ES_VRES_BIT      25
#define REG_SYSCTRL_WK_ES_VRES_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_WK_ES_VRES_BIT))
#define REG_SYSCTRL_WK_ES_WTES_BIT      26
#define REG_SYSCTRL_WK_ES_WTES_MASK     ((uint32)(BIT_W_2 << REG_SYSCTRL_WK_ES_WTES_BIT))
#define REG_SYSCTRL_WK_ES_CES_BIT       28
#define REG_SYSCTRL_WK_ES_CES_MASK      ((uint32)(BIT_W_1 << REG_SYSCTRL_WK_ES_CES_BIT))
#define REG_SYSCTRL_WK_ES_FLES_BIT      29
#define REG_SYSCTRL_WK_ES_FLES_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_WK_ES_FLES_BIT))
#define REG_SYSCTRL_RNDES_BIT           30
#define REG_SYSCTRL_RNDES_MASK          ((uint32)(BIT_W_1 << REG_SYSCTRL_RNDES_BIT))
#define REG_SYSCTRL_CKES_BIT            31
#define REG_SYSCTRL_CKES_MASK           ((uint32)(BIT_W_1 << REG_SYSCTRL_CKES_BIT))

/**** System controller: VBO Control Register ****/
#define REG_SYSCTRL_VBO_EN_BIT          0
#define REG_SYSCTRL_VBO_EN_MASK         ((uint32)(BIT_W_1 << REG_SYSCTRL_VBO_EN_BIT))
#define REG_SYSCTRL_VBO_SEL_BIT         1
#define REG_SYSCTRL_VBO_SEL_MASK        ((uint32)(BIT_W_3 << REG_SYSCTRL_VBO_SEL_BIT))
#define REG_SYSCTRL_VBO_RST_EN_BIT      4
#define REG_SYSCTRL_VBO_RST_EN_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_VBO_RST_EN_BIT))

/**** System controller: Reset registers ****/
#define REG_SYSCTRL_RSTCTRL_CR_BIT      1
#define REG_SYSCTRL_RSTCTRL_CR_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_RSTCTRL_CR_BIT))

/**** System controller: voltage regulator registers ****/
#define REG_SYSCTRL_REGCTRL_DVCTRL_BIT   3
#define REG_SYSCTRL_REGCTRL_DVCTRL_MASK  ((uint32)(BIT_W_3 << REG_SYSCTRL_REGCTRL_DVCTRL_BIT))
#define REG_SYSCTRL_REGCTRL_RVCTRL_BIT   6
#define REG_SYSCTRL_REGCTRL_RVCTRL_MASK  ((uint32)(BIT_W_3 << REG_SYSCTRL_REGCTRL_RVCTRL_BIT))
#define REG_SYSCTRL_REGCTRL_RLVEN_BIT    9
#define REG_SYSCTRL_REGCTRL_RLVEN_MASK   ((uint32)(BIT_W_1 << REG_SYSCTRL_REGCTRL_RLVEN_BIT))
#define REG_SYSCTRL_REGCTRL_IBOOST_BIT   10
#define REG_SYSCTRL_REGCTRL_IBOOST_MASK  ((uint32)(BIT_W_1 << REG_SYSCTRL_REGCTRL_IBOOST_BIT))

/**** System controller: Debug registers ****/
#define REG_SYS_DEBUG_EN_DEBUG_EN_BIT    0
#define REG_SYS_DEBUG_EN_DEBUG_EN_MASK   ((uint32)(BIT_W_1 << REG_SYS_DEBUG_EN_DEBUG_EN_BIT))
#define REG_SYS_DEBUG_EN_DEBUG_PORT_BIT  1
#define REG_SYS_DEBUG_EN_DEBUG_PORT_MASK ((uint32)(BIT_W_1 << REG_SYS_DEBUG_EN_DEBUG_PORT_BIT))

/**** System controller:  Random Number Generator Control ****/
#define REG_SYSCTRL_RND_EN_BIT          0
#define REG_SYSCTRL_RND_EN_MASK         ((uint32)(BIT_W_1 << REG_SYSCTRL_RND_EN_BIT))
#define REG_SYSCTRL_RND_EN_CLR_BIT      1
#define REG_SYSCTRL_RND_EN_CLR_MASK     ((uint32)(BIT_W_1 << REG_SYSCTRL_RND_EN_CLR_BIT))

/**** System controller:  Random Number Generator Value ****/
#define REG_SYSCTRL_RND_NUM_BIT         0
#define REG_SYSCTRL_RND_NUM_MASK        ((uint32)(BIT_W_16 << REG_SYSCTRL_RND_NUM_BIT))

/*** TEST 3V ***/
#define REG_SYSCTRL_TEST_3V_TST_XTAL_BIAS_3V_BIT   0
#define REG_SYSCTRL_TEST_3V_TST_XTAL_BIAS_3V_MASK  ((uint32)(BIT_W_3 << REG_SYSCTRL_TEST_3V_TST_XTAL_BIAS_3V_BIT))
#define REG_SYSCTRL_TEST_3V_TST_XTAL_PULL_3V_BIT   20
#define REG_SYSCTRL_TEST_3V_TST_XTAL_PULL_3V_MASK  ((uint32)(BIT_W_2 << REG_SYSCTRL_TEST_3V_TST_XTAL_PULL_3V_BIT))

/*** CTRL_32KRC ***/
#define REG_SYSCTRL_CTRL_32KRC_BIT          0
#define REG_SYSCTRL_CTRL_32KRC_MASK         ((uint32)(BIT_W_2 << REG_SYSCTRL_CTRL_32KRC_BIT))

/*** RCOSC_CTRL ***/
#define REG_SYS_RCOSC_CTRL_RC_CODE_BIT      0
#define REG_SYS_RCOSC_CTRL_RC_CODE_MASK     ((uint32)(BIT_W_4 << REG_SYS_RCOSC_CTRL_RC_CODE_BIT))
#define REG_SYS_RCOSC_CTRL_LOWSPEED_BIT     4
#define REG_SYS_RCOSC_CTRL_LOWSPEED_MASK    ((uint32)(BIT_W_1 << REG_SYS_RCOSC_CTRL_LOWSPEED_BIT))

/*** FLASH_CTRL ***/
#define REG_SYS_FLASH_CTRL_FLASHPOWERDOWN_BIT   0
#define REG_SYS_FLASH_CTRL_FLASHPOWERDOWN_MASK  ((uint32)(BIT_W_1 << REG_SYS_FLASH_CTRL_FLASHPOWERDOWN_BIT))
#define REG_SYS_FLASH_CTRL_JTAG_ACC_PROT_BIT    2
#define REG_SYS_FLASH_CTRL_JTAG_ACC_PROT_MASK  ((uint32)(BIT_W_1 << REG_SYS_FLASH_CTRL_JTAG_ACC_PROT_BIT))
#define REG_SYS_FLASH_CTRL_BANDGAP_ENABLE_BIT   3
#define REG_SYS_FLASH_CTRL_BANDGAP_ENABLE_MASK  ((uint32)(BIT_W_1 << REG_SYS_FLASH_CTRL_BANDGAP_ENABLE_BIT))
#define REG_SYS_FLASH_CTRL_EEPOWERDOWN_BIT      8
#define REG_SYS_FLASH_CTRL_EEPOWERDOWN_MASK     ((uint32)(BIT_W_1 << REG_SYS_FLASH_CTRL_EEPOWERDOWN_BIT))

/*** FLASH_REMAP ***/
#define REG_SYS_FLASH_REMAP_MASK_WIDTH          4

#define REG_SYS_FLASH_REMAP_0_BIT               0
#define REG_SYS_FLASH_REMAP_0_MASK              ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP_0_BIT))
#define REG_SYS_FLASH_REMAP_1_BIT               4
#define REG_SYS_FLASH_REMAP_1_MASK              ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP_1_BIT))
#define REG_SYS_FLASH_REMAP_2_BIT               8
#define REG_SYS_FLASH_REMAP_2_MASK              ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP_2_BIT))
#define REG_SYS_FLASH_REMAP_3_BIT               12
#define REG_SYS_FLASH_REMAP_3_MASK              ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP_3_BIT))
#define REG_SYS_FLASH_REMAP_4_BIT               16
#define REG_SYS_FLASH_REMAP_4_MASK              ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP_4_BIT))
#define REG_SYS_FLASH_REMAP_5_BIT               20
#define REG_SYS_FLASH_REMAP_5_MASK              ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP_5_BIT))
#define REG_SYS_FLASH_REMAP_6_BIT               24
#define REG_SYS_FLASH_REMAP_6_MASK              ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP_6_BIT))
#define REG_SYS_FLASH_REMAP_7_BIT               28
#define REG_SYS_FLASH_REMAP_7_MASK              ((uint32)(BIT_W_4 << REG_SYS_FLASH_REMAP_7_BIT))

/**** System controller: Watchdog Restart ****/
#define REG_SYSCTRL_WDRESTART_RESTART_BIT       0
#define REG_SYSCTRL_WDRESTART_RESTART_MASK      ((uint32)(BIT_W_16 <<  REG_SYSCTRL_WDRESTART_RESTART_BIT ))

/**** System controller: Watchdog Control ****/
#define REG_SYSCTRL_WDCTRL_START_BIT            0
#define REG_SYSCTRL_WDCTRL_START_MASK           ((uint32)(BIT_W_16 <<  REG_SYSCTRL_WDCTRL_START_BIT ))
#define REG_SYSCTRL_WDCTRL_PRE_BIT              16
#define REG_SYSCTRL_WDCTRL_PRE_MASK             ((uint32)(BIT_W_4 <<  REG_SYSCTRL_WDCTRL_PRE_BIT ))
#define REG_SYSCTRL_WDCTRL_EXCEN_BIT            31
#define REG_SYSCTRL_WDCTRL_EXCEN_MASK           ((uint32)(BIT_W_1 <<  REG_SYSCTRL_WDCTRL_EXCEN_BIT ))

/**** System controller: Watchdog Status  ****/
#define REG_SYSCTRL_WDSTAT_WD_EN_BIT            4
#define REG_SYSCTRL_WDSTAT_WD_EN_MASK           ((uint32)(BIT_W_10 <<  REG_SYSCTRL_WDSTAT_WD_EN_BIT ))
#define REG_SYSCTRL_WDSTAT_WD_CNT_BIT           8
#define REG_SYSCTRL_WDSTAT_WD_CNT_MASK          ((uint32)(BIT_W_8 <<  REG_SYSCTRL_WDSTAT_WD_CNT_BIT ))
#define REG_SYSCTRL_WDSTAT_PRE_CNT_BIT          16
#define REG_SYSCTRL_WDSTAT_PRE_CNT_MASK         ((uint32)(BIT_W_10 <<  REG_SYSCTRL_WDSTAT_PRE_CNT_BIT ))


#define REG_SYS_FLASH_CTRL_ATETRIM_OFFSET       2
#define REG_SYS_FLASH_CTRL_ATETRIM_BIT          0
#define REG_SYS_FLASH_CTRL_ATETRIM_MASK         ((uint32)(BIT_W_3 <<  REG_SYS_FLASH_CTRL_ATETRIM_BIT ))

#define REG_SYS_VBOCTRL_VBO_EN_BIT              0
#define REG_SYS_VBOCTRL_VBO_EN_MASK             ((uint32)(BIT_W_1 <<  REG_SYS_VBOCTRL_VBO_EN_BIT))
#define REG_SYS_VBOCTRL_VBO_SEL_BIT             1
#define REG_SYS_VBOCTRL_VBO_SEL_MASK            ((uint32)(BIT_W_3 <<  REG_SYS_VBOCTRL_VBO_SEL_BIT))
#define REG_SYS_VBOCTRL_VBO_RST_EN_BIT          4
#define REG_SYS_VBOCTRL_VBO_RST_EN_MASK         ((uint32)(BIT_W_1 <<  REG_SYS_VBOCTRL_VBO_RST_EN_BIT))

/**** UART: IER_DLM ****/
#define REG_UART_IERDLM_ERBFI_BIT       0
#define REG_UART_IERDLM_ERBFI_MASK      ((uint8)(BIT_W_1 << REG_UART_IERDLM_ERBFI_BIT))
#define REG_UART_IERDLM_ETBEI_BIT       1
#define REG_UART_IERDLM_ETBEI_MASK      ((uint8)(BIT_W_1 << REG_UART_IERDLM_ETBEI_BIT))
#define REG_UART_IERDLM_ELSI_BIT        2
#define REG_UART_IERDLM_ELSI_MASK       ((uint8)(BIT_W_1 << REG_UART_IERDLM_ELSI_BIT))
#define REG_UART_IERDLM_EDSSI_BIT       3
#define REG_UART_IERDLM_EDSSI_MASK      ((uint8)(BIT_W_1 << REG_UART_IERDLM_EDSSI_BIT))

/**** UART: FC ****/
#define REG_UART_FC_RFEN_BIT            0
#define REG_UART_FC_RFEN_MASK           ((uint8)(BIT_W_1 << REG_UART_FC_RFEN_BIT))
#define REG_UART_FC_RFRST_BIT           1
#define REG_UART_FC_RFRST_MASK          ((uint8)(BIT_W_1 << REG_UART_FC_RFRST_BIT))
#define REG_UART_FC_TFRST_BIT           2
#define REG_UART_FC_TFRST_MASK          ((uint8)(BIT_W_1 << REG_UART_FC_TFRST_BIT))

/**** UART: FCR ****/
#define REG_UART_FCR_RFRST_BIT          1
#define REG_UART_FCR_RFRST_MASK         ((uint8)(BIT_W_1 << REG_UART_FCR_RFRST_BIT))
#define REG_UART_FCR_TFRST_BIT          2
#define REG_UART_FCR_TFRST_MASK         ((uint8)(BIT_W_1 << REG_UART_FCR_TFRST_BIT))
#define REG_UART_FCR_RINTRIG_BIT        6
#define REG_UART_FCR_RINTRIG_MASK       ((uint8)(BIT_W_2 << REG_UART_FCR_RINTRIG_BIT))

/**** UART: LCR ****/
#define REG_UART_LCR_WLS_BIT            0
#define REG_UART_LCR_WLS_MASK           ((uint8)(BIT_W_2 << REG_UART_LCR_WLS_BIT))
#define REG_UART_LCR_STB_BIT            2
#define REG_UART_LCR_STB_MASK           ((uint8)(BIT_W_1 << REG_UART_LCR_STB_BIT))
#define REG_UART_LCR_PEN_BIT            3
#define REG_UART_LCR_PEN_MASK           ((uint8)(BIT_W_1 << REG_UART_LCR_PEN_BIT))
#define REG_UART_LCR_EPS_BIT            4
#define REG_UART_LCR_EPS_MASK           ((uint8)(BIT_W_1 << REG_UART_LCR_EPS_BIT))
#define REG_UART_LCR_BREAK_BIT          6
#define REG_UART_LCR_BREAK_MASK         ((uint8)(BIT_W_1 << REG_UART_LCR_BREAK_BIT))
#define REG_UART_LCR_DLAB_BIT           7
#define REG_UART_LCR_DLAB_MASK          ((uint8)(BIT_W_1 << REG_UART_LCR_DLAB_BIT))

/**** UART: MCR ****/
#define REG_UART_MCR_RTS_BIT            1
#define REG_UART_MCR_RTS_MASK           ((uint8)(BIT_W_1 << REG_UART_MCR_RTS_BIT))

/**** UART: AFC ****/
#define REG_UART_AFC_ACTS_BIT           0
#define REG_UART_AFC_ACTS_MASK          ((uint8)(BIT_W_1 << REG_UART_AFC_ACTS_BIT))
#define REG_UART_AFC_ARTS_BIT           1
#define REG_UART_AFC_ARTS_MASK          ((uint8)(BIT_W_1 << REG_UART_AFC_ARTS_BIT))
#define REG_UART_AFC_FCP_BIT            2
#define REG_UART_AFC_FCP_MASK           ((uint8)(BIT_W_1 << REG_UART_AFC_FCP_BIT))
#define REG_UART_AFC_RFARTL_BIT         4
#define REG_UART_AFC_RFARTL_MASK        ((uint8)(BIT_W_2 << REG_UART_AFC_RFARTL_BIT))

/**** UART: LSR ****/
#define REG_UART_LSR_DR_BIT             0
#define REG_UART_LSR_DR_MASK            ((uint8)(BIT_W_1 << REG_UART_LSR_DR_BIT))
#define REG_UART_LSR_OE_BIT             1
#define REG_UART_LSR_OE_MASK            ((uint8)(BIT_W_1 << REG_UART_LSR_OE_BIT))
#define REG_UART_LSR_PE_BIT             2
#define REG_UART_LSR_PE_MASK            ((uint8)(BIT_W_1 << REG_UART_LSR_PE_BIT))
#define REG_UART_LSR_FE_BIT             3
#define REG_UART_LSR_FE_MASK            ((uint8)(BIT_W_1 << REG_UART_LSR_FE_BIT))
#define REG_UART_LSR_BI_BIT             4
#define REG_UART_LSR_BI_MASK            ((uint8)(BIT_W_1 << REG_UART_LSR_BI_BIT))
#define REG_UART_LSR_THRE_BIT           5
#define REG_UART_LSR_THRE_MASK          ((uint8)(BIT_W_1 << REG_UART_LSR_THRE_BIT))
#define REG_UART_LSR_TEMT_BIT           6
#define REG_UART_LSR_TEMT_MASK          ((uint8)(BIT_W_1 << REG_UART_LSR_TEMT_BIT))
#define REG_UART_LSR_ERROR_BIT          7
#define REG_UART_LSR_ERROR_MASK         ((uint8)(BIT_W_1 << REG_UART_LSR_ERROR_BIT))

/**** Timer: T_CTRL ****/
#define REG_TMR_CTRL_EN_BIT             0
#define REG_TMR_CTRL_EN_MASK            ((uint16)(BIT_W_1 << REG_TMR_CTRL_EN_BIT))
#define REG_TMR_CTRL_EEVENT_BIT         1
#define REG_TMR_CTRL_EEVENT_MASK        ((uint16)(BIT_W_1 << REG_TMR_CTRL_EEVENT_BIT))
#define REG_TMR_CTRL_INVCKGT_BIT        2
#define REG_TMR_CTRL_INVCKGT_MASK       ((uint16)(BIT_W_1 << REG_TMR_CTRL_INVCKGT_BIT))
#define REG_TMR_CTRL_OE_BIT             3
#define REG_TMR_CTRL_OE_MASK            ((uint16)(BIT_W_1 << REG_TMR_CTRL_OE_BIT))
#define REG_TMR_CTRL_SINGLE_BIT         4
#define REG_TMR_CTRL_SINGLE_MASK        ((uint16)(BIT_W_1 << REG_TMR_CTRL_SINGLE_BIT))
#define REG_TMR_CTRL_CTRRST_BIT         5
#define REG_TMR_CTRL_CTRRST_MASK        ((uint16)(BIT_W_1 << REG_TMR_CTRL_CTRRST_BIT))
#define REG_TMR_CTRL_CAPTE_BIT          6
#define REG_TMR_CTRL_CAPTE_MASK         ((uint16)(BIT_W_1 << REG_TMR_CTRL_CAPTE_BIT))
#define REG_TMR_CTRL_DSEN_BIT           7
#define REG_TMR_CTRL_DSEN_MASK          ((uint16)(BIT_W_1 << REG_TMR_CTRL_DSEN_BIT))
#define REG_TMR_CTRL_RZEN_BIT           8
#define REG_TMR_CTRL_RZEN_MASK          ((uint16)(BIT_W_1 << REG_TMR_CTRL_RZEN_BIT))
#define REG_TMR_CTRL_GDIS_BIT           9
#define REG_TMR_CTRL_GDIS_MASK          ((uint16)(BIT_W_1 << REG_TMR_CTRL_GDIS_BIT))
#define REG_TMR_CTRL_INVOUT_BIT         10
#define REG_TMR_CTRL_INVOUT_MASK        ((uint16)(BIT_W_1 << REG_TMR_CTRL_INVOUT_BIT))
#define REG_TMR_CTRL_INVCAPT_BIT        11
#define REG_TMR_CTRL_INVCAPT_MASK       ((uint16)(BIT_W_1 << REG_TMR_CTRL_INVCAPT_BIT))
#define REG_TMR_CTRL_EEDGE_BIT          12
#define REG_TMR_CTRL_EEDGE_MASK         ((uint16)(BIT_W_1 << REG_TMR_CTRL_EEDGE_BIT))
#define REG_TMR_CTRL_RCEN_BIT           13
#define REG_TMR_CTRL_RCEN_MASK          ((uint16)(BIT_W_1 << REG_TMR_CTRL_RCEN_BIT))

/**** Timer: T_INT and T_INTE ****/
#define REG_TMR_INT_P_EN_BIT            0
#define REG_TMR_INT_P_EN_MASK           ((uint8)(BIT_W_1 << REG_TMR_INT_P_EN_BIT))
#define REG_TMR_INT_L_EN_BIT            1
#define REG_TMR_INT_L_EN_MASK           ((uint8)(BIT_W_1 << REG_TMR_INT_L_EN_BIT))
#define REG_TMR_INT_RC_EN_BIT           2
#define REG_TMR_INT_RC_EN_MASK          ((uint8)(BIT_W_1 << REG_TMR_INT_RC_EN_BIT))

/**** Timer: T_RC_CTRL (PWM2 Only) ****/
#define REG_TMR_RCCTRL_GO_BIT           0
#define REG_TMR_RCCTRL_GO_MASK          ((uint8)(BIT_W_1 << REG_TMR_RCCTRL_GO_BIT))

/**** SPI master: SPIM_CTRL ****/
#define REG_SPIM_CTRL_GOBSY_BIT         0
#define REG_SPIM_CTRL_GOBSY_MASK        ((uint16)(BIT_W_1 << REG_SPIM_CTRL_GOBSY_BIT))
#define REG_SPIM_CTRL_PHA_BIT           1
#define REG_SPIM_CTRL_PHA_MASK          ((uint16)(BIT_W_1 << REG_SPIM_CTRL_PHA_BIT))
#define REG_SPIM_CTRL_POL_BIT           2
#define REG_SPIM_CTRL_POL_MASK          ((uint16)(BIT_W_1 << REG_SPIM_CTRL_POL_BIT))
#define REG_SPIM_CTRL_CHARLEN_BIT       3
#define REG_SPIM_CTRL_CHARLEN_MASK      ((uint16)(BIT_W_5 << REG_SPIM_CTRL_CHARLEN_BIT))
#define REG_SPIM_CTRL_LSB_BIT           10
#define REG_SPIM_CTRL_LSB_MASK          ((uint16)(BIT_W_1 << REG_SPIM_CTRL_LSB_BIT))
#define REG_SPIM_CTRL_CRM_BIT           11
#define REG_SPIM_CTRL_CRM_MASK          ((uint16)(BIT_W_1 << REG_SPIM_CTRL_CRM_BIT))
#define REG_SPIM_CTRL_ASS_BIT           12
#define REG_SPIM_CTRL_ASS_MASK          ((uint16)(BIT_W_1 << REG_SPIM_CTRL_ASS_BIT))
#define REG_SPIM_CTRL_DRE_BIT           13
#define REG_SPIM_CTRL_DRE_MASK          ((uint16)(BIT_W_1 << REG_SPIM_CTRL_DRE_BIT))

/**** SPI slave: SPIS_CTRL ****/
#define REG_SPIS_CTRL_RXWEN_BIT         0
#define REG_SPIS_CTRL_RXWEN_MASK        ((uint16)(BIT_W_1 << REG_SPIS_CTRL_RXWEN_BIT))
#define REG_SPIS_CTRL_TXWEN_BIT         1
#define REG_SPIS_CTRL_TXWEN_MASK        ((uint16)(BIT_W_1 << REG_SPIS_CTRL_TXWEN_BIT))
#define REG_SPIS_CTRL_RXFIFORST_BIT     2
#define REG_SPIS_CTRL_RXFIFORST_MASK    ((uint16)(BIT_W_1 << REG_SPIS_CTRL_RXFIFORST_BIT))
#define REG_SPIS_CTRL_TXFIFORST_BIT     3
#define REG_SPIS_CTRL_TXFIFORST_MASK    ((uint16)(BIT_W_1 << REG_SPIS_CTRL_TXFIFORST_BIT))
#define REG_SPIS_CTRL_LSB_BIT           4
#define REG_SPIS_CTRL_LSB_MASK          ((uint16)(BIT_W_1 << REG_SPIS_CTRL_LSB_BIT))

/**** SPI slave: SPIS_IE ****/
#define REG_SPIS_INT_RX_FIRST_BIT       0
#define REG_SPIS_INT_RX_FIRST_MASK      ((uint16)(BIT_W_1 << REG_SPIS_INT_RX_FIRST_BIT))
#define REG_SPIS_INT_TX_LAST_BIT        1
#define REG_SPIS_INT_TX_LAST_MASK       ((uint16)(BIT_W_1 << REG_SPIS_INT_TX_LAST_BIT))
#define REG_SPIS_INT_RX_CLIMB_BIT       2
#define REG_SPIS_INT_RX_CLIMB_MASK      ((uint16)(BIT_W_1 << REG_SPIS_INT_RX_CLIMB_BIT))
#define REG_SPIS_INT_TX_FALL_BIT        3
#define REG_SPIS_INT_TX_FALL_MASK       ((uint16)(BIT_W_1 << REG_SPIS_INT_TX_FALL_BIT))
#define REG_SPIS_INT_RX_OVER_BIT        4
#define REG_SPIS_INT_RX_OVER_MASK       ((uint16)(BIT_W_1 << REG_SPIS_INT_RX_OVER_BIT))
#define REG_SPIS_INT_TX_OVER_BIT        5
#define REG_SPIS_INT_TX_OVER_MASK       ((uint16)(BIT_W_1 << REG_SPIS_INT_TX_OVER_BIT))
#define REG_SPIS_INT_RX_UNDER_BIT       6
#define REG_SPIS_INT_RX_UNDER_MASK      ((uint16)(BIT_W_1 << REG_SPIS_INT_RX_UNDER_BIT))
#define REG_SPIS_INT_TX_UNDER_BIT       7
#define REG_SPIS_INT_TX_UNDER_MASK      ((uint16)(BIT_W_1 << REG_SPIS_INT_TX_UNDER_BIT))
#define REG_SPIS_INT_RX_TIMEOUT_BIT     8
#define REG_SPIS_INT_RX_TIMEOUT_MASK    ((uint16)(BIT_W_1 << REG_SPIS_INT_RX_TIMEOUT_BIT))

/**** Analogue: Bandgap control  ****/
#define REG_SYS_TEST_3V_BIT             4
#define REG_SYS_TEST_MASK               ((uint32)(BIT_W_1 << REG_SYS_TEST_3V_BIT))

/**** Analogue: AP_CTRL ****/
#define REG_ANPER_CTRL_BATT_EN_BIT          25
#define REG_ANPER_CTRL_BATT_EN_MASK         ((uint32)(BIT_W_1 << REG_ANPER_CTRL_BATT_EN_BIT))
#define REG_ANPER_CTRL_TEMP_EN_BIT          24
#define REG_ANPER_CTRL_TEMP_EN_MASK         ((uint32)(BIT_W_1 << REG_ANPER_CTRL_TEMP_EN_BIT))
#define REG_ANPER_CTRL_RET_DAC_OUT2_BIT     23
#define REG_ANPER_CTRL_RET_DAC_OUT2_MASK    ((uint32)(BIT_W_1 << REG_ANPER_CTRL_RET_DAC_OUT2_BIT))
#define REG_ANPER_CTRL_RET_DAC_OUT1_BIT     22
#define REG_ANPER_CTRL_RET_DAC_OUT1_MASK    ((uint32)(BIT_W_1 << REG_ANPER_CTRL_RET_DAC_OUT1_BIT))
#define REG_ANPER_CTRL_SAMPLE_PERIOD_BIT    20
#define REG_ANPER_CTRL_SAMPLE_PERIOD_MASK   ((uint32)(BIT_W_2 << REG_ANPER_CTRL_SAMPLE_PERIOD_BIT))
#define REG_ANPER_CTRL_CLOCK_DIV_BIT        18
#define REG_ANPER_CTRL_CLOCK_DIV_MASK       ((uint32)(BIT_W_2 << REG_ANPER_CTRL_CLOCK_DIV_BIT))
#define REG_ANPER_CTRL_CONVERT_BIT          16
#define REG_ANPER_CTRL_CONVERT_MASK         ((uint32)(BIT_W_1 << REG_ANPER_CTRL_CONVERT_BIT))
#define REG_ANPER_CTRL_CONV_SLOW_BIT        15
#define REG_ANPER_CTRL_CONV_SLOW_MASK       ((uint32)(BIT_W_1 << REG_ANPER_CTRL_CONV_SLOW_BIT))
#define REG_ANPER_CTRL_D2EN_BIT             13
#define REG_ANPER_CTRL_D2EN_MASK            ((uint32)(BIT_W_1 << REG_ANPER_CTRL_D2EN_BIT))
#define REG_ANPER_CTRL_D1EN_BIT             12
#define REG_ANPER_CTRL_D1EN_MASK            ((uint32)(BIT_W_1 << REG_ANPER_CTRL_D1EN_BIT))
#define REG_ANPER_CTRL_AEN_BIT              11
#define REG_ANPER_CTRL_AEN_MASK             ((uint32)(BIT_W_1 << REG_ANPER_CTRL_AEN_BIT))
#define REG_ANPER_CTRL_ADCSEL_BIT           4
#define REG_ANPER_CTRL_ADCSEL_MASK          ((uint32)(BIT_W_3 << REG_ANPER_CTRL_ADCSEL_BIT))
#define REG_ANPER_CTRL_ADC_GAIN_BIT         3
#define REG_ANPER_CTRL_ADC_GAIN_MASK        ((uint32)(BIT_W_1 << REG_ANPER_CTRL_ADC_GAIN_BIT))
#define REG_ANPER_CTRL_DAC2_GAIN_BIT        2
#define REG_ANPER_CTRL_DAC2_GAIN_MASK       ((uint32)(BIT_W_1 << REG_ANPER_CTRL_DAC2_GAIN_BIT))
#define REG_ANPER_CTRL_DAC1_GAIN_BIT        1
#define REG_ANPER_CTRL_DAC1_GAIN_MASK       ((uint32)(BIT_W_1 << REG_ANPER_CTRL_DAC1_GAIN_BIT))
#define REG_ANPER_CTRL_REF_SEL_BIT          0
#define REG_ANPER_CTRL_REF_SEL_MASK         ((uint32)(BIT_W_1 << REG_ANPER_CTRL_REF_SEL_BIT))

/**** Analogue: AP_VAL ****/
#define REG_ANPER_VAL_C1_BIT                12
#define REG_ANPER_VAL_C1_MASK               ((uint32)(BIT_W_1 << REG_ANPER_VAL_C1_BIT))
#define REG_ANPER_VAL_ADC_BIT               0
#define REG_ANPER_VAL_ADC_MASK              ((uint32)(BIT_W_12 << REG_ANPER_VAL_ADC_BIT))

/**** Analogue: AP_TEST ****/


/**** Analogue: AP_COMPCTRL ****/
#define REG_ANPER_COMPCTRL_C1IPSEL_BIT      9
#define REG_ANPER_COMPCTRL_C1IPSEL_MASK     ((uint32)(BIT_W_1 << REG_ANPER_COMPCTRL_C1IPSEL_BIT))
#define REG_ANPER_COMPCTRL_BCTRL_BIT        8
#define REG_ANPER_COMPCTRL_BCTRL_MASK       ((uint32)(BIT_W_1 << REG_ANPER_COMPCTRL_BCTRL_BIT))
#define REG_ANPER_COMPCTRL_HYS_BIT          6
#define REG_ANPER_COMPCTRL_HYS_MASK         ((uint32)(BIT_W_2 << REG_ANPER_COMPCTRL_HYS_BIT))
#define REG_ANPER_COMPCTRL_C1SEL_BIT        2
#define REG_ANPER_COMPCTRL_C1SEL_MASK       ((uint32)(BIT_W_2 << REG_ANPER_COMPCTRL_C1SEL_BIT))
#define REG_ANPER_COMPCTRL_C1EN_BIT         0
#define REG_ANPER_COMPCTRL_C1EN_MASK        ((uint32)(BIT_W_1 << REG_ANPER_COMPCTRL_C1EN_BIT))

#define REG_ANPER_CAPT_CAPT_BIT             0
#define REG_ANPER_CAPT_CAPT_MASK            ((uint32)(BIT_W_1 << REG_ANPER_CAPT_CAPT_BIT))

/**** Analogue: Interrupts ****/
#define REG_ANPER_INT_D_OVER_BIT            4
#define REG_ANPER_INT_D_OVER_MASK           ((uint32)(BIT_W_1 << REG_ANPER_INT_D_OVER_BIT))
#define REG_ANPER_INT_D_END_BIT             3
#define REG_ANPER_INT_D_END_MASK            ((uint32)(BIT_W_1 << REG_ANPER_INT_D_END_BIT))
#define REG_ANPER_INT_D_MID_BIT             2
#define REG_ANPER_INT_D_MID_MASK            ((uint32)(BIT_W_1 << REG_ANPER_INT_D_MID_BIT))
#define REG_ANPER_INT_ADCACC_BIT            1
#define REG_ANPER_INT_ADCACC_MASK           ((uint32)(BIT_W_1 << REG_ANPER_INT_ADCACC_BIT))
#define REG_ANPER_INT_CAPT_BIT              0
#define REG_ANPER_INT_CAPT_MASK             ((uint32)(BIT_W_1 << REG_ANPER_INT_CAPT_BIT))

#define REG_ANPER_AVVAL_BIT                 8
#define REG_ANPER_AVVAL_MASK                ((uint32)(BIT_W_16 << REG_ANPER_AVVAL_BIT))

#define REG_ANPER_AVVAL_CLEAR_MASK          (0x0U)    /* Starts sampling in continuous mode */

/**** Analogue: DMA Control ****/
#define REG_ANPER_DMACTRL_BYTESEL_BIT       3
#define REG_ANPER_DMACTRL_BYTESEL_MASK      ((uint32)(BIT_W_3 << REG_ANPER_DMACTRL_BYTESEL_BIT))
#define REG_ANPER_DMACTRL_BYTE_BIT          2
#define REG_ANPER_DMACTRL_BYTE_MASK         ((uint32)(BIT_W_1 << REG_ANPER_DMACTRL_BYTE_BIT))
#define REG_ANPER_DMACTRL_WRAP_BIT          1
#define REG_ANPER_DMACTRL_WRAP_MASK         ((uint32)(BIT_W_1 << REG_ANPER_DMACTRL_WRAP_BIT))
#define REG_ANPER_DMACTRL_DMAEN_BIT         0
#define REG_ANPER_DMACTRL_DMAEN_MASK        ((uint32)(BIT_W_1 << REG_ANPER_DMACTRL_DMAEN_BIT))

#define REG_ANPER_DMACTRL_BYTESEL_0_7       (0)
#define REG_ANPER_DMACTRL_BYTESEL_1_8       (1)
#define REG_ANPER_DMACTRL_BYTESEL_2_9       (2)
#define REG_ANPER_DMACTRL_BYTESEL_3_10      (3)
#define REG_ANPER_DMACTRL_BYTESEL_4_11      (4)

/**** Serial Interface: SI_CTRL ****/
#define REG_SI_CTRL_EN_BIT              7
#define REG_SI_CTRL_EN_MASK             ((uint32)(BIT_W_1 << REG_SI_CTRL_EN_BIT))
#define REG_SI_CTRL_IE_BIT              6
#define REG_SI_CTRL_IE_MASK             ((uint32)(BIT_W_1 << REG_SI_CTRL_IE_BIT))

/**** Serial Interface: SI_CMD ****/
#define REG_SI_CMD_STA_BIT              7
#define REG_SI_CMD_STA_MASK             ((uint32)(BIT_W_1 << REG_SI_CMD_STA_BIT))
#define REG_SI_CMD_STO_BIT              6
#define REG_SI_CMD_STO_MASK             ((uint32)(BIT_W_1 << REG_SI_CMD_STO_BIT))
#define REG_SI_CMD_RD_BIT               5
#define REG_SI_CMD_RD_MASK              ((uint32)(BIT_W_1 << REG_SI_CMD_RD_BIT))
#define REG_SI_CMD_WR_BIT               4
#define REG_SI_CMD_WR_MASK              ((uint32)(BIT_W_1 << REG_SI_CMD_WR_BIT))
#define REG_SI_CMD_ACK_BIT              3
#define REG_SI_CMD_ACK_MASK             ((uint32)(BIT_W_1 << REG_SI_CMD_ACK_BIT))
#define REG_SI_CMD_IACK_BIT             0
#define REG_SI_CMD_IACK_MASK            ((uint32)(BIT_W_1 << REG_SI_CMD_IACK_BIT))

/**** Serial Interface: SI_STAT ****/
#define REG_SI_STAT_RXACK_BIT           7
#define REG_SI_STAT_RXACK_MASK          ((uint32)(BIT_W_1 << REG_SI_STAT_RXACK_BIT))
#define REG_SI_STAT_BUSY_BIT            6
#define REG_SI_STAT_BUSY_MASK           ((uint32)(BIT_W_1 << REG_SI_STAT_BUSY_BIT))
#define REG_SI_STAT_AL_BIT              5
#define REG_SI_STAT_AL_MASK             ((uint32)(BIT_W_1 << REG_SI_STAT_AL_BIT))
#define REG_SI_STAT_TIP_BIT             1
#define REG_SI_STAT_TIP_MASK            ((uint32)(BIT_W_1 << REG_SI_STAT_TIP_BIT))
#define REG_SI_STAT_INT_BIT             0
#define REG_SI_STAT_INT_MASK            ((uint32)(BIT_W_1 << REG_SI_STAT_INT_BIT))

/**** AES ****/
/* AES command enumerations */
#define AES_COMMAND_SHIFT                           4
#define REG_AES_ACL_CMD_SET_MODE                    ((uint32)(( 0 << AES_COMMAND_SHIFT) | 1))
#define REG_AES_ACL_CMD_SET_KEY                     ((uint32)(( 1 << AES_COMMAND_SHIFT) | 1))
#define REG_AES_ACL_CMD_GO                          ((uint32)(( 5 << AES_COMMAND_SHIFT) | 1))
#define REG_AES_ACL_CMD_RESET                       ((uint32)((12 << AES_COMMAND_SHIFT) | 1))

/* AES command register bit masks */
#define REG_AES_ACL_CMD_DONE_MASK                   ((uint32)(1))
#define REG_AES_ACL_CMD_ERROR_MASK                  ((uint32)(2))
#define REG_AES_ACL_CMD_REJECT_MASK                 ((uint32)(4))
#define REG_AES_ACL_CMD_MUTEX_MASK                  ((uint32)(8))

/* AES interrupt register masks */
#define REG_AES_INT_CCMDA_VALID_MASK                ((uint32)(16))
#define REG_AES_INT_CHKSM_VALID_MASK                ((uint32)(8))
#define REG_AES_INT_MUTEX_MASK                      ((uint32)(4))
#define REG_AES_INT_CMD_REJECTED_MASK               ((uint32)(2))
#define REG_AES_INT_CMD_COM_MASK                    ((uint32)(1))

/* AES status register masks */
#define REG_AES_STATUS_AUTH_COMPLETE_MASK           ((uint32)(8))
#define REG_AES_STATUS_CHKSM_VALID_MASK             ((uint32)(4))
#define REG_AES_STATUS_CCMDA_VALID_MASK             ((uint32)(2))
#define REG_AES_STATUS_CCMDA_RESULT_MASK            ((uint32)(1))


/**** CPU CTRL******/
#define REG_CPUCTRL_DOZE_BIT            0
#define REG_CPUCTRL_DOZE_MASK           ((uint32)(BIT_W_1 << REG_CPUCTRL_DOZE_BIT))

/**** CPU CLK CTRL ****/
#define REG_CPUCLK_CTRL_SPEED_BIT       0
#define REG_CPUCLK_CTRL_SPEED_MASK      ((uint32)(BIT_W_3 << REG_CPUCLK_CTRL_SPEED_BIT))
#define REG_CPUCLK_CTRL_AUTO_BIT        4
#define REG_CPUCLK_CTRL_AUTO_MASK       ((uint32)(BIT_W_1 << REG_CPUCLK_CTRL_AUTO_BIT))
#define REG_CPUCLK_CTRL_SEL_RO_BIT      5
#define REG_CPUCLK_CTRL_SEL_RO_MASK     ((uint32)(BIT_W_1 << REG_CPUCLK_CTRL_SEL_RO_BIT))
#define REG_CPUCLK_CTRL_A_X_PD_BIT      12
#define REG_CPUCLK_CTRL_A_X_PD_MASK     ((uint32)(BIT_W_1 << REG_CPUCLK_CTRL_A_X_PD_BIT))

/**** CPU CLK STAT ****/
#define REG_CPUCLK_STAT_SPEED_BIT       0
#define REG_CPUCLK_STAT_SPEED_MASK      ((uint32)(BIT_W_3 << REG_CPUCLK_STAT_SPEED_BIT))
#define REG_CPUCLK_STAT_SEL_RO_BIT      5
#define REG_CPUCLK_STAT_SEL_RO_MASK     ((uint32)(BIT_W_1 << REG_CPUCLK_STAT_SEL_RO_BIT))
#define REG_CPUCLK_STAT_X_EN_BIT        7
#define REG_CPUCLK_STAT_X_EN_MASK       ((uint32)(BIT_W_1 << REG_CPUCLK_STAT_X_EN_BIT))
#define REG_CPUCLK_STAT_X_STAT_BIT      9
#define REG_CPUCLK_STAT_X_STAT_MASK     ((uint32)(BIT_W_1 << REG_CPUCLK_STAT_X_STAT_BIT))

/**** GEN CTRL******/
#define REG_GENCTRL_PD32K_BIT           0
#define REG_GENCTRL_PD32K_MASK          ((uint32)(BIT_W_1 << REG_GENCTRL_PD32K_BIT))
#define REG_GENCTRL_EXT32KSRC_BIT       1
#define REG_GENCTRL_EXT32KSRC_MASK      ((uint32)(BIT_W_1 << REG_GENCTRL_EXT32KSRC_BIT))
#define REG_GENCTRL_EN32KXTAL_BIT       2
#define REG_GENCTRL_EN32KXTAL_MASK      ((uint32)(BIT_W_1 << REG_GENCTRL_EN32KXTAL_BIT))
#define REG_GENCTRL_USE_AMP_OK_BIT      3
#define REG_GENCTRL_USE_AMP_OK_MASK     ((uint32)(BIT_W_1 << REG_GENCTRL_USE_AMP_OK_BIT))

/**** Timer IO Control Disables ******/
#define REG_SYS_TIM_IO_T4PDIS_BIT           (6)
#define REG_SYS_TIM_IO_T4PDIS_MASK          ((uint32)(BIT_W_1 << REG_SYS_TIM_IO_T4PDIS_BIT))
#define REG_SYS_TIM_IO_T3PDIS_BIT           (5)
#define REG_SYS_TIM_IO_T3PDIS_MASK          ((uint32)(BIT_W_1 << REG_SYS_TIM_IO_T3PDIS_BIT))
#define REG_SYS_TIM_IO_T2PDIS_BIT           (4)
#define REG_SYS_TIM_IO_T2PDIS_MASK          ((uint32)(BIT_W_1 << REG_SYS_TIM_IO_T2PDIS_BIT))
#define REG_SYS_TIM_IO_T1PDIS_BIT           (3)
#define REG_SYS_TIM_IO_T1PDIS_MASK          ((uint32)(BIT_W_1 << REG_SYS_TIM_IO_T1PDIS_BIT))
#define REG_SYS_TIM_IO_T0PDIS_BIT           (2)
#define REG_SYS_TIM_IO_T0PDIS_MASK          ((uint32)(BIT_W_1 << REG_SYS_TIM_IO_T0PDIS_BIT))
#define REG_SYS_TIM_IO_T0CDIS_BIT           (1)
#define REG_SYS_TIM_IO_T0CDIS_MASK          ((uint32)(BIT_W_1 << REG_SYS_TIM_IO_T0CDIS_BIT))
#define REG_SYS_TIM_IO_T0GDIS_BIT           (0)
#define REG_SYS_TIM_IO_T0GDIS_MASK          ((uint32)(BIT_W_1 << REG_SYS_TIM_IO_T0GDIS_BIT))

/**** GPIO ******/
#define REG_GPIO_SDOUT_D1_BIT               (1)
#define REG_GPIO_SDOUT_D1_MASK              ((uint32)(BIT_W_1 << REG_GPIO_SDOUT_D1_BIT))
#define REG_GPIO_SDOUT_D0_BIT               (0)
#define REG_GPIO_SDOUT_D0_MASK              ((uint32)(BIT_W_1 << REG_GPIO_SDOUT_D0_BIT))

/**** FEC ******/
#define REG_FEC_FBWST_WST_BIT               (0)
#define REG_FEC_FBWST_WST_MASK              ((uint32)(BIT_W_8 << REG_FEC_FBWST_WST_BIT))

#define REG_FEC_INT_EEC_ERROR_BIT           (3)
#define REG_FEC_INT_EEC_ERROR_MASK          ((uint32)(BIT_W_1 << REG_FEC_INT_EEC_ERROR_BIT))

/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/
typedef enum
{
    /* System controller: */
    REG_SYS_PWR_CTRL      = 0,
    REG_SYS_STAT          = 1,
    REG_SYS_WK_ET         = 2,
    REG_SYS_WK_EM         = 3,
    REG_SYS_WK_ES         = 4,
    REG_SYS_WK_T0         = 5,
    REG_SYS_WK_T1         = 6,
    REG_SYS_WK_TC         = 7,
    REG_SYS_WK_TS         = 8,
    REG_SYS_WK_CC         = 9,
    REG_SYS_WK_CRC        = 10,
    REG_SYS_CPU_CTRL      = 11,
    REG_SYS_WK_T0_MSB     = 12,
    REG_SYS_WK_T1_MSB     = 13,
    REG_SYS_GEN_CTRL      = 14,
    REG_SYS_PULLUP        = 15,
    REG_SYS_PWR_CTRL2     = 16,
    REG_SYS_VBOCTRL       = 17,
    REG_SYS_SYSCTRL_TEST  = 18,
    REG_SYS_RSTCTRL       = 19,
    REG_SYS_REGCNTRL      = 20,
    REG_SYS_CPUCLK_CTRL   = 23,
    /* No 25 to 35 */
    REG_SYS_CPUCLK_STAT   = 39,
    REG_SYS_DEBUG_EN      = 40,
    REG_SYS_WK_MES        = 41,
    REG_SYS_DZ_AN_CTRL    = 43,
    REG_SYS_POWER_TEST    = 44,
    REG_SYS_WD_RESTART    = 45,
    REG_SYS_WD_CONTROL    = 46,
    REG_SYS_WD_STAT       = 47,
    REG_SYS_RND_CTRL      = 48,
    REG_SYS_RND_VAL       = 49,
    REG_SYS_SCRATCH_TEST  = 50,
    REG_SYS_TEST_3V       = 50, /* Same register as above */
    REG_SYS_PC_CTRL       = 52,
    REG_SYS_PC_REF        = 53,
    REG_SYS_PC_CNT        = 54,
    REG_SYS_TIM_IO_CTRL   = 55,
    REG_SYS_CPU_STK_OVF   = 56,
    REG_SYS_RCOSC_CTRL    = 57,
    REG_SYS_FLASH_CTRL    = 58,
    REG_SYS_FLASH_REMAP   = 59,
    REG_SYS_CHIP_ID       = 63,

    /* System Controller Duplicated and Extended region */

    /* System Controller Flash registers  */
    REG_SYS_FL_INDEX0     = 64,
    REG_SYS_FL_INDEX1     = 65,
    REG_SYS_FL_INDEX2     = 66,
    REG_SYS_FL_INDEX3     = 67,
    REG_SYS_NV_STORE      = 80,
    REG_SYS_CTRL_32KRC    = 88,
    REG_SYS_RAMP0         = 89,

    /* AES */
    REG_AES_ACLKEY        = 0, /* 4 words in size, 128-bit key */
    REG_AES_ACL_CMD       = 5,
    REG_AES_DATA_IN       = 0,
    REG_AES_DATA_OUT      = 7,
    REG_AES_IV            = 0,
    REG_AES_CTR           = 0,
    REG_AES_RI_CCM_ML     = 3,
    REG_AES_RI_CCM_ALEN_0 = 2,
    REG_AES_RI_CCM_ALEN_1 = 3,
    REG_AES_RI_CCM_MLEN_0 = 2,
    REG_AES_RI_CCM_MLEN_1 = 3,
    REG_AES_BCMODE        = 3,
    REG_AES_RI_CCM_NONCE  = 0,
    REG_AES_CCM_AUTH      = 0,
    REG_AES_INT           = 4,
    REG_AES_INT_EN        = 6,
    REG_AES_MINT          = 16,

    /* GPIO */
    REG_GPIO_DIR          = 0,
    REG_GPIO_DOUT         = 1,
    REG_GPIO_DIN          = 2,
    REG_GPIO_SDOUT        = 3,

    /* UART: Repeated for each one */
    REG_UART_DATA         = 0,
    REG_UART_IER          = 1,
    REG_UART_IIR          = 2, /* Read only */
    REG_UART_FCR          = 2, /* Write only */
    REG_UART_LCR          = 3,
    REG_UART_MCR          = 4,
    REG_UART_LSR          = 5,
    REG_UART_MSR          = 6,
    REG_UART_SCR          = 7,
    REG_UART_EFR          = 8,
    REG_UART_TFC          = 9,
    REG_UART_RFC          = 10,
    REG_UART_AFC          = 11,
    REG_UART_FC           = 12,
    REG_UART_TFA          = 13,
    REG_UART_RFA          = 14,
    REG_UART_TFL          = 15,
    REG_UART_RFL          = 16,

    /* Timer: Repeated for each one */
    REG_TMR_CTR     = 0,/* REG_TMR_T_CTR  */
    REG_TMR_HI      = 1,/* REG_TMR_T_LO  */
    REG_TMR_LO      = 2,/* REG_TMR_T_PERIOD */
    REG_TMR_CTRL    = 3,/* REG_TMR_T_CTRL */
    REG_TMR_PRESC   = 4,/*REG_TMR_T_PRE_SEL */
    REG_TMR_INT     = 5,/*  REG_TMR_T_INT*/
    REG_TMR_INTE    = 6,/* REG_TMR_T_INTE */
    REG_TMR_MINT    = 7,/* REG_TMR_T_MINT */

    /* Infrared Registers on Timer 2 */
    REG_TMR_RCPERIOD = 8,/* REG_TMR_T_MINT */
    REG_TMR_RCLEN    = 9,/* REG_TMR_T_MINT */
    REG_TMR_RCBUFAD  = 10,/* REG_TMR_T_MINT */
    REG_TMR_RCCTRL   = 11,/* REG_TMR_T_MINT */

    /* Serial Interface (2 wire) */
    REG_SI_PS_L           = 0,
    REG_SI_PS_H           = 1,
    REG_SI_CTRL           = 2,
    REG_SI_TX             = 3,
    REG_SI_RX             = 3,
    REG_SI_CMD            = 4,
    REG_SI_STAT           = 4,

    /* SPI master */
    REG_SPIM_BUF          = 0,
    REG_SPIM_CTRL         = 1,
    REG_SPIM_DIV          = 2,
    REG_SPIM_SS           = 3,
    REG_SPIM_IE           = 4,
    REG_SPIM_IS           = 5,
    REG_SPIM_SCRAM        = 6,
    REG_SPIM_DXA          = 7,
    REG_SPIM_DXC          = 8,

    /* SPI slave */
    REG_SPIS_DATA_OUT     = 0,
    REG_SPIS_DATA_IN      = 1,
    REG_SPIS_STAT         = 2,
    REG_SPIS_IS           = 3,
    REG_SPIS_IE           = 4,
    REG_SPIS_MIS          = 5,
    REG_SPIS_CTRL         = 6,
    REG_SPIS_RXTO         = 7,
    REG_SPIS_TXBUFAD      = 8,
    REG_SPIS_TXBUFLEN     = 9,
    REG_SPIS_TXBUFTHR     = 10,
    REG_SPIS_TXBUFLVL     = 11,
    REG_SPIS_RXBUFAD      = 12,
    REG_SPIS_RXBUFLEN     = 13,
    REG_SPIS_RXBUFTHR     = 14,
    REG_SPIS_RXBUFLVL     = 15,

    /* Analogue peripherals */
    REG_ANPER_CTRL        = 0,
    REG_ANPER_VAL         = 1,
    REG_ANPER_CAPT        = 4,
    REG_ANPER_IS          = 5,
    REG_ANPER_IE          = 6,
    REG_ANPER_TEST        = 7,
    REG_ANPER_COMPCTRL    = 8,
    // ADC DMA
    REG_ANPER_ADCAVCTRL   = 9,
    REG_ANPER_ADCAVVAL    = 10,
    REG_ANPER_ADCDMACTRL  = 11,
    REG_ANPER_ADCDMAADDR  = 12,
    REG_ANPER_ADCDMALEN   = 13,
    REG_ANPER_ADCDMACOUNT = 14,
    REG_ANPER_ADCDMASRC   = 15,
    REG_ANPER_ADCTT       = 16,
    // Masked Interrupt
    REG_ANPER_MIS         = 17,

    REG_FEC_FCTR           = 0,
    REG_FEC_FSTAT          = 1,
    REG_FEC_FPTR           = 2,
    REG_FEC_FTCTR          = 3,
    REG_FEC_FBWST          = 4,
    // missing reg
    REG_FEC_FCHAR          = 6,
    REG_FEC_FCRA           = 7,

    REG_FEC_EECMD          = 32,
    REG_FEC_EEADDR         = 33,
    REG_FEC_EEWDATA        = 34,
    REG_FEC_EERDATA        = 35,
    REG_FEC_EEWSTATE       = 36,
    REG_FEC_EECLKDIV       = 37,

    REG_FEC_INT_CLR_ENABLE = 1014,
    REG_FEC_INT_SET_ENABLE = 1015,
    REG_FEC_INT_STATUS     = 1016,
    REG_FEC_INT_ENABLE     = 1017,
    REG_FEC_INT_CLR_STATUS = 1018,
    REG_FEC_INT_SET_STATUS = 1019,
} tePeriphReg;

#define REG_FEC_BASE        0x01000000UL
#define REG_SYS_BASE        0x02000000UL    /* Always use extended address space - no benefit in using legacy base address */
#define REG_AES_BASE        0x02001C00UL
#define REG_ANPER_BASE      0x02001F00UL
#define REG_GPIO_BASE       0x02002000UL
#define REG_UART0_BASE      0x02003000UL
#define REG_UART1_BASE      0x02004000UL
#define REG_TMR0_BASE       0x02005000UL
#define REG_I2C_M_BASE      0x02007000UL
#define REG_I2C_S_BASE      0x02007800UL
#define REG_SPIM_BASE       0x02008000UL
#define REG_SPIS_BASE       0x02009000UL
#define REG_TMR1_BASE       0x0200A000UL
#define REG_TMR2_BASE       0x0200B000UL
#define REG_TMR3_BASE       0x0200C000UL
#define REG_TMR4_BASE       0x0200E000UL

/* Flash EEPROM Ctrl */
#define u32REG_FECRead(eOffset)                 (*(volatile uint32 *)(((eOffset) << 2) + REG_FEC_BASE))
#define vREG_FECWrite(eOffset, u32Data)         *(volatile uint32 *)(((eOffset) << 2) + REG_FEC_BASE) = (u32Data)

/* System Ctrl - extended region */
#define u32REG_SysExtRead(eOffset)              u32REG_Read(((eOffset) << 2) + REG_SYS_BASE)
#define vREG_SysExtWrite(eOffset, u32Data)      vREG_Write(((eOffset) << 2) + REG_SYS_BASE, u32Data)
#define u32REG_SysExtReadNC(eOffset)            u32REG_ReadNC(((eOffset) << 2) + REG_SYS_BASE)
#define vREG_SysExtWriteNC(eOffset, u32Data)    vREG_WriteNC(((eOffset) << 2) + REG_SYS_BASE, u32Data)

/* System Ctrl */
#define u32REG_SysRead(eOffset)                 u32REG_Read(((eOffset) << 2) + REG_SYS_BASE)
#define vREG_SysWrite(eOffset, u32Data)         vREG_Write(((eOffset) << 2) + REG_SYS_BASE, u32Data)
#define u32REG_SysReadNC(eOffset)               u32REG_ReadNC(((eOffset) << 2) + REG_SYS_BASE)
#define vREG_SysWriteNC(eOffset, u32Data)       vREG_WriteNC(((eOffset) << 2) + REG_SYS_BASE, u32Data)

#define vREG_SysReadModWrite32(eOffset, u32Mask, u32Data) \
    vREG_SysWrite(eOffset, (((u32Mask) & (u32Data)) | (~(u32Mask) & (u32REG_SysRead(eOffset)))))

/* AES */
#define u32REG_AesRead(eOffset)                 u32REG_Read(((eOffset) << 2) + REG_AES_BASE)
#define vREG_AesWrite(eOffset, u32Data)         vREG_Write(((eOffset) << 2) + REG_AES_BASE, u32Data)
#define u32REG_AesReadNC(eOffset)               u32REG_ReadNC(((eOffset) << 2) + REG_AES_BASE)
#define vREG_AesWriteNC(eOffset, u32Data)       vREG_WriteNC(((eOffset) << 2) + REG_AES_BASE, u32Data)
#define vREG_AesReadModWrite32(eOffset, u32Mask, u32Data) \
    vREG_AesWrite(eOffset, (((u32Mask) & (u32Data)) | (~(u32Mask) & (u32REG_AesRead(eOffset)))))

/* GPIO */
#define u32REG_GpioRead(eOffset)                u32REG_Read(((eOffset) << 2) + REG_GPIO_BASE)
#define vREG_GpioWrite(eOffset, u32Data)        vREG_Write(((eOffset) << 2) + REG_GPIO_BASE, u32Data)

/* UARTs */
#define u32REG_Uart0Read(eOffset)               u32REG_Read(((eOffset) << 2) + REG_UART0_BASE)
#define vREG_Uart0Write(eOffset, u32Data)       vREG_Write(((eOffset) << 2) + REG_UART0_BASE, u32Data)
#define u32REG_Uart1Read(eOffset)               u32REG_Read(((eOffset) << 2) + REG_UART1_BASE)
#define vREG_Uart1Write(eOffset, u32Data)       vREG_Write(((eOffset) << 2) + REG_UART1_BASE, u32Data)

/* Timers */
#define u32REG_Timer0Read(eOffset)              u32REG_Read(((eOffset) << 2) + REG_TMR0_BASE)
#define u32REG_Timer0ReadNC(eOffset)            u32REG_ReadNC(((eOffset) << 2) + REG_TMR0_BASE)
#define vREG_Timer0Write(eOffset, u32Data)      vREG_Write(((eOffset) << 2) + REG_TMR0_BASE, u32Data)
#define u32REG_Timer1Read(eOffset)              u32REG_Read(((eOffset) << 2) + REG_TMR1_BASE)
#define u32REG_Timer1ReadNC(eOffset)            u32REG_ReadNC(((eOffset) << 2) + REG_TMR1_BASE)
#define vREG_Timer1Write(eOffset, u32Data)      vREG_Write(((eOffset) << 2) + REG_TMR1_BASE, u32Data)
#define u32REG_Timer2Read(eOffset)              u32REG_Read(((eOffset) << 2) + REG_TMR2_BASE)
#define u32REG_Timer2ReadNC(eOffset)            u32REG_ReadNC(((eOffset) << 2) + REG_TMR2_BASE)
#define vREG_Timer2Write(eOffset, u32Data)      vREG_Write(((eOffset) << 2) + REG_TMR2_BASE, u32Data)

#define u32REG_Timer3Read(eOffset)              u32REG_Read(((eOffset) << 2) + REG_TMR3_BASE)
#define u32REG_Timer3ReadNC(eOffset)            u32REG_ReadNC(((eOffset) << 2) + REG_TMR3_BASE)
#define vREG_Timer3Write(eOffset, u32Data)      vREG_Write(((eOffset) << 2) + REG_TMR3_BASE, u32Data)
#define u32REG_Timer3Read(eOffset)              u32REG_Read(((eOffset) << 2) + REG_TMR3_BASE)
#define u32REG_Timer3ReadNC(eOffset)            u32REG_ReadNC(((eOffset) << 2) + REG_TMR3_BASE)
#define u32REG_Timer4Read(eOffset)              u32REG_Read(((eOffset) << 2) + REG_TMR4_BASE)
#define u32REG_Timer4ReadNC(eOffset)            u32REG_ReadNC(((eOffset) << 2) + REG_TMR4_BASE)
#define vREG_Timer4Write(eOffset, u32Data)      vREG_Write(((eOffset) << 2) + REG_TMR4_BASE, u32Data)
#define u32REG_Timer4Read(eOffset)              u32REG_Read(((eOffset) << 2) + REG_TMR4_BASE)
#define u32REG_Timer4ReadNC(eOffset)            u32REG_ReadNC(((eOffset) << 2) + REG_TMR4_BASE)

/* Serial Interface */
#define u32REG_SiMasterRead(eOffset)            u32REG_Read(((eOffset) << 2) + REG_I2C_M_BASE)
#define vREG_SiMasterWrite(eOffset, u32Data)    vREG_Write(((eOffset) << 2) + REG_I2C_M_BASE, u32Data)

#define u32REG_SiSlaveRead(eOffset)            u32REG_Read(((eOffset) << 2) + REG_I2C_S_BASE)
#define vREG_SiSlaveWrite(eOffset, u32Data)    vREG_Write(((eOffset) << 2) + REG_I2C_S_BASE, u32Data)

/* SPI */
#define u32REG_SpiRead(eOffset)                 u32REG_Read(((eOffset) << 2) + REG_SPIM_BASE)
#define vREG_SpiWrite(eOffset, u32Data)         vREG_Write(((eOffset) << 2) + REG_SPIM_BASE, u32Data)
#define u32REG_SpiSlaveRead(eOffset)            u32REG_Read(((eOffset) << 2) + REG_SPIS_BASE)
#define vREG_SpiSlaveWrite(eOffset, u32Data)    vREG_Write(((eOffset) << 2) + REG_SPIS_BASE, u32Data)
#define vREG_SpiSlaveWriteNC(eOffset, u32Data)  vREG_WriteNC(((eOffset) << 2) + REG_SPIS_BASE, u32Data)

#define vREG_SpiReadModWrite32(eOffset, u32Mask, u32Data) \
    vREG_SpiWrite(eOffset, (((u32Mask) & (u32Data)) | (~(u32Mask) & (u32REG_SpiRead(eOffset)))))

/* Analogue */
#define u32REG_AnaRead(eOffset)                 u32REG_Read(((eOffset) << 2) + REG_ANPER_BASE)
#define vREG_AnaWrite(eOffset, u32Data)         vREG_Write(((eOffset) << 2) + REG_ANPER_BASE, u32Data)
#define u32REG_AnaReadNC(eOffset)               u32REG_ReadNC(((eOffset) << 2) + REG_ANPER_BASE)
#define vREG_AnaWriteNC(eOffset, u32Data)       vREG_WriteNC(((eOffset) << 2) + REG_ANPER_BASE, u32Data)

#define vREG_AnaReadModWrite32(eOffset, u32Mask, u32Data) \
    vREG_AnaWrite(eOffset, (((u32Mask) & (u32Data)) | (~(u32Mask) & (u32REG_AnaRead(eOffset)))))

#ifdef __cplusplus
};
#endif

#endif /* _periph_reg_h_ */
