/****************************************************************************
 *
 * MODULE:             MAC
 *
 * DESCRIPTION:
 * MAC - 802.15.4 Media Access Controller
 * PHY Device interface
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

#ifndef _xcv_reg_h_
#define _xcv_reg_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/

/************************/
/**** MACROS/DEFINES ****/
/************************/

#ifndef JENNIC_HW_BBC_DMA
#error Build environment must define JENNIC_HW_BBC_DMA
#endif
#ifndef JENNIC_HW_BBC_ISA
#error Build environment must define JENNIC_HW_BBC_ISA
#endif

#ifndef BIT_W_1
#define BIT_W_1                         0x1
#define BIT_W_2                         0x3
#define BIT_W_3                         0x7
#define BIT_W_4                         0xF
#define BIT_W_5                         0x1F
#define BIT_W_6                         0x3F
#define BIT_W_7                         0x7F
#define BIT_W_8                         0xFF
#define BIT_W_12                        0xFFF
#define BIT_W_15                        0x7FFF
#define BIT_W_16                        0xFFFF
#define BIT_W_18                        0x3FFFF
#define BIT_W_20                        0xFFFFF
#define BIT_W_21                        0x1FFFFF
#define BIT_W_25                        0x01FFFFFFUL
#endif

/**** System controller: PWR_CTRL ****/
#define XCV_REG_SYSCTRL_PWRCTRL_PDR_BIT     0
#define XCV_REG_SYSCTRL_PWRCTRL_PDR_MASK    ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_PDR_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_DSS_BIT     1
#define XCV_REG_SYSCTRL_PWRCTRL_DSS_MASK    ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_DSS_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_PPDC_BIT    3
#define XCV_REG_SYSCTRL_PWRCTRL_PPDC_MASK   ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_PPDC_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_MHUP_BIT    5
#define XCV_REG_SYSCTRL_PWRCTRL_MHUP_MASK   ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_MHUP_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_MS_BIT      10
#define XCV_REG_SYSCTRL_PWRCTRL_MS_MASK     ((uint32)(BIT_W_2 << XCV_REG_SYSCTRL_PWRCTRL_MS_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_UEN0_BIT    12
#define XCV_REG_SYSCTRL_PWRCTRL_T0EN_BIT    14
#define XCV_REG_SYSCTRL_PWRCTRL_NASSEN_BIT  17
#if !(defined JENNIC_CHIP_JN5142) && !(defined JENNIC_CHIP_JN5142_HDK) && !(defined JENNIC_CHIP_JN5142J01) && !(defined JENNIC_CHIP_FAMILY_JN516x)
#define XCV_REG_SYSCTRL_PWRCTRL_NASSEN_MASK ((uint32)(BIT_W_3 << XCV_REG_SYSCTRL_PWRCTRL_NASSEN_BIT))
#else
#define XCV_REG_SYSCTRL_PWRCTRL_NASSEN_MASK ((uint32)(BIT_W_2 << XCV_REG_SYSCTRL_PWRCTRL_NASSEN_BIT))
#endif
#if !(defined JENNIC_CHIP_JN5142) && !(defined JENNIC_CHIP_JN5142_HDK) && !(defined JENNIC_CHIP_JN5142J01) && !(defined JENNIC_CHIP_FAMILY_JN516x)
#define XCV_REG_SYSCTRL_PWRCTRL_APDLY_BIT   20
#define XCV_REG_SYSCTRL_PWRCTRL_APDLY_MASK  ((uint32)(BIT_W_2 << XCV_REG_SYSCTRL_PWRCTRL_APDLY_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_APDLY1_BIT   21
#define XCV_REG_SYSCTRL_PWRCTRL_APDLY1_MASK  ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_APDLY1_BIT))
#endif
#define XCV_REG_SYSCTRL_PWRCTRL_APEN_BIT     22
#define XCV_REG_SYSCTRL_PWRCTRL_APEN_MASK    ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_APEN_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_ANTDIV1_BIT  23
#define XCV_REG_SYSCTRL_PWRCTRL_ANTDIV1_MASK ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_ANTDIV1_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_RFRXEN_BIT   24
#define XCV_REG_SYSCTRL_PWRCTRL_RFRXEN_MASK  ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_RFRXEN_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_RFTXEN_BIT   25
#define XCV_REG_SYSCTRL_PWRCTRL_RFTXEN_MASK  ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_RFTXEN_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_CTSRTSEN_BIT 27
#define XCV_REG_SYSCTRL_PWRCTRL_ANTDIV2_BIT  31
#define XCV_REG_SYSCTRL_PWRCTRL_ANTDIV2_MASK ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_ANTDIV2_BIT))

/**** System controller: PWR2_CTRL ****/
#define XCV_REG_SYSCTRL_PWRCTRL_SIF_SEL_BIT     0
#define XCV_REG_SYSCTRL_PWRCTRL_SIF_SEL_MASK    ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_SIF_SEL_BIT))
#define XCV_REG_SYSCTRL_PWRCTRL_U1RXD_BIT       1
#define XCV_REG_SYSCTRL_PWRCTRL_U1RXD_MASK      ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_PWRCTRL_U1RXD_BIT))

/*** System controller: GEN_CTRL ****/
#define XCV_REG_SYSCTRL_GENCTRL_EXT32KSRC_BIT   1
#define XCV_REG_SYSCTRL_GENCTRL_EXT32KSRC_MASK  ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_GENCTRL_EXT32KSRC_BIT))

/**** CPU CTRL******/
#define XCV_REG_SYSCTRL_CPUCTRL_DOZE_BIT         0
#define XCV_REG_SYSCTRL_CPUCTRL_DOZE_MASK        ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_CPUCTRL_DOZE_BIT ))
#define XCV_REG_SYSCTRL_CPUCTRL_CLKDOUBLER_BIT   1
#define XCV_REG_SYSCTRL_CPUTRL_CLKDOUBLER_MASK  ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_CPUCTRL_CLKDOUBLER_BIT))

/**** System controller: Status register ****/
#define XCV_REG_SYSCTRL_STAT_WUS_BIT        0
#define XCV_REG_SYSCTRL_STAT_WUS_MASK       ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_STAT_WUS_BIT))
#define XCV_REG_SYSCTRL_STAT_MS_BIT         1
#define XCV_REG_SYSCTRL_STAT_MS_MASK        ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_STAT_MS_BIT))
#define XCV_REG_SYSCTRL_STAT_APPS_BIT       2
#define XCV_REG_SYSCTRL_STAT_APPS_MASK      ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_STAT_APPS_BIT))
#define XCV_REG_SYSCTRL_STAT_PROPS_BIT      3
#define XCV_REG_SYSCTRL_STAT_PROPS_MASK     ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_STAT_PROPS_BIT))

/**** System controller: Wake event registers ****/
#define XCV_REG_SYSCTRL_WKE_GE_BIT          0

#if (defined JENNIC_CHIP_FAMILY_JN516x)
#define XCV_REG_SYSCTRL_WKE_GE_MASK         ((uint32)(BIT_W_20 << XCV_REG_SYSCTRL_WKE_GE_BIT))
#else
#if !(defined JENNIC_CHIP_JN5142) && !(defined JENNIC_CHIP_JN5142_HDK) && !(defined JENNIC_CHIP_JN5142J01)
#define XCV_REG_SYSCTRL_WKE_GE_MASK         ((uint32)(BIT_W_21 << XCV_REG_SYSCTRL_WKE_GE_BIT))
#else
#define XCV_REG_SYSCTRL_WKE_GE_MASK         ((uint32)(BIT_W_18 << XCV_REG_SYSCTRL_WKE_GE_BIT))
#endif
#endif
#define XCV_REG_SYSCTRL_WKE_WTE_BIT         26
#define XCV_REG_SYSCTRL_WKE_WTE_MASK        ((uint32)(BIT_W_2 << XCV_REG_SYSCTRL_WKE_WTE_BIT))
#define XCV_REG_SYSCTRL_WKE_CTRT_BIT        28
#define XCV_REG_SYSCTRL_WKE_CE_BIT          28
#if !(defined JENNIC_CHIP_JN5142) && !(defined JENNIC_CHIP_JN5142_HDK) && !(defined JENNIC_CHIP_JN5142J01) && !(defined JENNIC_CHIP_FAMILY_JN516x)
#define XCV_REG_SYSCTRL_WKE_CE_MASK         ((uint32)(BIT_W_2 << XCV_REG_SYSCTRL_WKE_CE_BIT))
#else
#define XCV_REG_SYSCTRL_WKE_CE_MASK         ((uint32)(BIT_W_1 << XCV_REG_SYSCTRL_WKE_CE_BIT))
#endif

/**** PHY mask registers ******************************/
#if (defined JENNIC_CHIP_FAMILY_JN516x)
#define XCV_REG_PHY_AD_EN_TX_EN_BIT         0
#define XCV_REG_PHY_AD_EN_TX_EN_MASK        ((uint8)(BIT_W_1 << XCV_REG_PHY_AD_EN_TX_EN_BIT))
#define XCV_REG_PHY_AD_EN_RX_EN_BIT         1
#define XCV_REG_PHY_AD_EN_RX_EN_MASK        ((uint8)(BIT_W_1 << XCV_REG_PHY_AD_EN_RX_EN_BIT))

#define XCV_REG_PHY_AD_STAT_TX_ANT_BIT      0
#define XCV_REG_PHY_AD_STAT_TX_ANT_MASK     ((uint8)(BIT_W_1 << XCV_REG_PHY_AD_STAT_TX_ANT_BIT))
#define XCV_REG_PHY_AD_STAT_RX_ANT_BIT      1
#define XCV_REG_PHY_AD_STAT_RX_ANT_MASK     ((uint8)(BIT_W_1 << XCV_REG_PHY_AD_STAT_RX_ANT_BIT))
#define XCV_REG_PHY_AD_STAT_ANT_BIT         2
#define XCV_REG_PHY_AD_STAT_ANT_MASK        ((uint8)(BIT_W_1 << XCV_REG_PHY_AD_STAT_ANT_BIT))

#define XCV_REG_PHY_AD_CTRL_RSSI_THR_BIT    0
#define XCV_REG_PHY_AD_CTRL_RSSI_THR_MASK   ((uint8)(BIT_W_5 << XCV_REG_PHY_AD_CTRL_RSSI_THR_BIT))
#define XCV_REG_PHY_AD_CTRL_SW_ANT_BIT      8
#define XCV_REG_PHY_AD_CTRL_SW_ANT_MASK     ((uint32)(BIT_W_1 << XCV_REG_PHY_AD_CTRL_SW_ANT_BIT))
#endif

/**** System controller: Wake event mask registers ****/
#define XCV_REG_SYSCTRL_WKM_GE_BIT          0
#if (defined JENNIC_CHIP_FAMILY_JN516x)
#define XCV_REG_SYSCTRL_WKM_GE_MASK         ((uint32)(BIT_W_20 << XCV_REG_SYSCTRL_WKM_GE_BIT))
#else
#if !(defined JENNIC_CHIP_JN5142) && !(defined JENNIC_CHIP_JN5142_HDK) && !(defined JENNIC_CHIP_JN5142J01)
#define XCV_REG_SYSCTRL_WKM_GE_MASK         ((uint32)(BIT_W_21 << XCV_REG_SYSCTRL_WKM_GE_BIT))
#else
#define XCV_REG_SYSCTRL_WKM_GE_MASK         ((uint32)(BIT_W_18 << XCV_REG_SYSCTRL_WKM_GE_BIT))
#endif
#endif
/**** UART: IER_DLM ****/
#define XCV_REG_UART_IERDLM_ERBFI_BIT       0
#define XCV_REG_UART_IERDLM_ERBFI_MASK      ((uint8)(BIT_W_1 << XCV_REG_UART_IERDLM_ERBFI_BIT))
#define XCV_REG_UART_IERDLM_ETBEI_BIT       1
#define XCV_REG_UART_IERDLM_ETBEI_MASK      ((uint8)(BIT_W_1 << XCV_REG_UART_IERDLM_ETBEI_BIT))
#define XCV_REG_UART_IERDLM_ELSI_BIT        2
#define XCV_REG_UART_IERDLM_ELSI_MASK       ((uint8)(BIT_W_1 << XCV_REG_UART_IERDLM_ELSI_BIT))
#define XCV_REG_UART_IERDLM_EDSSI_BIT       3
#define XCV_REG_UART_IERDLM_EDSSI_MASK      ((uint8)(BIT_W_1 << XCV_REG_UART_IERDLM_EDSSI_BIT))

/**** UART: FC ****/
#define XCV_REG_UART_FC_RFEN_BIT            0
#define XCV_REG_UART_FC_RFEN_MASK           ((uint8)(BIT_W_1 << XCV_REG_UART_FC_RFEN_BIT))
#define XCV_REG_UART_FC_RFRST_BIT           1
#define XCV_REG_UART_FC_RFRST_MASK          ((uint8)(BIT_W_1 << XCV_REG_UART_FC_RFRST_BIT))
#define XCV_REG_UART_FC_TFRST_BIT           2
#define XCV_REG_UART_FC_TFRST_MASK          ((uint8)(BIT_W_1 << XCV_REG_UART_FC_TFRST_BIT))

/**** UART: FCR ****/
#define XCV_REG_UART_FCR_RFRST_BIT          1
#define XCV_REG_UART_FCR_RFRST_MASK         ((uint8)(BIT_W_1 << XCV_REG_UART_FCR_RFRST_BIT))
#define XCV_REG_UART_FCR_TFRST_BIT          2
#define XCV_REG_UART_FCR_TFRST_MASK         ((uint8)(BIT_W_1 << XCV_REG_UART_FCR_TFRST_BIT))
#define XCV_REG_UART_FCR_RINTRIG_BIT        6
#define XCV_REG_UART_FCR_RINTRIG_MASK       ((uint8)(BIT_W_2 << XCV_REG_UART_FCR_RINTRIG_BIT))

/**** UART: LCR ****/
#define XCV_REG_UART_LCR_WLS_BIT            0
#define XCV_REG_UART_LCR_WLS_MASK           ((uint8)(BIT_W_2 << XCV_REG_UART_LCR_WLS_BIT))
#define XCV_REG_UART_LCR_STB_BIT            2
#define XCV_REG_UART_LCR_STB_MASK           ((uint8)(BIT_W_1 << XCV_REG_UART_LCR_STB_BIT))
#define XCV_REG_UART_LCR_PEN_BIT            3
#define XCV_REG_UART_LCR_PEN_MASK           ((uint8)(BIT_W_1 << XCV_REG_UART_LCR_PEN_BIT))
#define XCV_REG_UART_LCR_EPS_BIT            4
#define XCV_REG_UART_LCR_EPS_MASK           ((uint8)(BIT_W_1 << XCV_REG_UART_LCR_EPS_BIT))
#define XCV_REG_UART_LCR_BREAK_BIT          6
#define XCV_REG_UART_LCR_BREAK_MASK         ((uint8)(BIT_W_1 << XCV_REG_UART_LCR_BREAK_BIT))
#define XCV_REG_UART_LCR_DLAB_BIT           7
#define XCV_REG_UART_LCR_DLAB_MASK          ((uint8)(BIT_W_1 << XCV_REG_UART_LCR_DLAB_BIT))

/**** UART: MCR ****/
#define XCV_REG_UART_MCR_RTS_BIT            1
#define XCV_REG_UART_MCR_RTS_MASK           ((uint8)(BIT_W_1 << XCV_REG_UART_MCR_RTS_BIT))

/**** Timer: T_CTRL ****/
#define XCV_REG_TMR_CTRL_EN_BIT             0
#define XCV_REG_TMR_CTRL_EN_MASK            ((uint8)(BIT_W_1 << XCV_REG_TMR_CTRL_EN_BIT))
#define XCV_REG_TMR_CTRL_ECLK_BIT           1
#define XCV_REG_TMR_CTRL_ECLK_MASK          ((uint8)(BIT_W_1 << XCV_REG_TMR_CTRL_ECLK_BIT))
#define XCV_REG_TMR_CTRL_NEC_BIT            2
#define XCV_REG_TMR_CTRL_NEC_MASK           ((uint8)(BIT_W_1 << XCV_REG_TMR_CTRL_NEC_BIT))
#define XCV_REG_TMR_CTRL_SINGLE_BIT         4
#define XCV_REG_TMR_CTRL_SINGLE_MASK        ((uint8)(BIT_W_1 << XCV_REG_TMR_CTRL_SINGLE_BIT))
#define XCV_REG_TMR_CTRL_CNTRRST_BIT        5
#define XCV_REG_TMR_CTRL_CNTRRST_MASK       ((uint8)(BIT_W_1 << XCV_REG_TMR_CTRL_CNTRRST_BIT))
#define XCV_REG_TMR_CTRL_CAPTE_BIT          6
#define XCV_REG_TMR_CTRL_CAPTE_MASK         ((uint8)(BIT_W_1 << XCV_REG_TMR_CTRL_CAPTE_BIT))
#define XCV_REG_TMR_CTRL_DSEN_BIT           7
#define XCV_REG_TMR_CTRL_DSEN_MASK          ((uint8)(BIT_W_1 << XCV_REG_TMR_CTRL_DSEN_BIT))
#define XCV_REG_TMR_CTRL_RZEN_BIT           8
#define XCV_REG_TMR_CTRL_RZEN_MASK          ((uint8)(BIT_W_1 << XCV_REG_TMR_CTRL_RZEN_BIT))

/**** SPI master: SPIM_CTRL ****/
#define XCV_REG_SPIM_CTRL_GOBSY_BIT         0
#define XCV_REG_SPIM_CTRL_GOBSY_MASK        ((uint16)(BIT_W_1 << XCV_REG_SPIM_CTRL_GOBSY_BIT))
#define XCV_REG_SPIM_CTRL_RXNEG_BIT         1
#define XCV_REG_SPIM_CTRL_RXNEG_MASK        ((uint16)(BIT_W_1 << XCV_REG_SPIM_CTRL_RXNEG_BIT))
#define XCV_REG_SPIM_CTRL_TXNEG_BIT         2
#define XCV_REG_SPIM_CTRL_TXNEG_MASK        ((uint16)(BIT_W_1 << XCV_REG_SPIM_CTRL_TXNEG_BIT))
#define XCV_REG_SPIM_CTRL_CHARLEN_BIT       3
#define XCV_REG_SPIM_CTRL_CHARLEN_MASK      ((uint16)(BIT_W_5 << XCV_REG_SPIM_CTRL_CHARLEN_BIT))
#define XCV_REG_SPIM_CTRL_LSB_BIT           10
#define XCV_REG_SPIM_CTRL_LSB_MASK          ((uint16)(BIT_W_1 << XCV_REG_SPIM_CTRL_LSB_BIT))
#define XCV_REG_SPIM_CTRL_CRM_BIT           11
#define XCV_REG_SPIM_CTRL_CRM_MASK          ((uint16)(BIT_W_1 << XCV_REG_SPIM_CTRL_CRM_BIT))
#define XCV_REG_SPIM_CTRL_ASS_BIT           12
#define XCV_REG_SPIM_CTRL_ASS_MASK          ((uint16)(BIT_W_1 << XCV_REG_SPIM_CTRL_ASS_BIT))
#define XCV_REG_SPIM_CTRL_DRE_BIT           13
#define XCV_REG_SPIM_CTRL_DRE_MASK          ((uint16)(BIT_W_1 << XCV_REG_SPIM_CTRL_DRE_BIT))


/**** Analogue: AP_CTRL ****/
#define XCV_REG_ANPER_CTRL_BATT_EN_BIT      25
#define XCV_REG_ANPER_CTRL_BATT_EN_MASK     ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_BATT_EN_BIT))
#define XCV_REG_ANPER_CTRL_TEMP_EN_BIT      24
#define XCV_REG_ANPER_CTRL_TEMP_EN_MASK     ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_TEMP_EN_BIT))
#define XCV_REG_ANPER_CTRL_RET_DAC_OUT2_BIT 23
#define XCV_REG_ANPER_CTRL_RET_DAC_OUT2_MASK ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_RET_DAC_OUT2_BIT))
#define XCV_REG_ANPER_CTRL_RET_DAC_OUT1_BIT 22
#define XCV_REG_ANPER_CTRL_RET_DAC_OUT1_MASK ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_RET_DAC_OUT1_BIT))
#define XCV_REG_ANPER_CTRL_SAMPLE_PERIOD_BIT 20
#define XCV_REG_ANPER_CTRL_SAMPLE_PERIOD_MASK ((uint32)(BIT_W_2 << XCV_REG_ANPER_CTRL_SAMPLE_PERIOD_BIT))
#define XCV_REG_ANPER_CTRL_CLOCK_DIV_BIT    18
#define XCV_REG_ANPER_CTRL_CLOCK_DIV_MASK   ((uint32)(BIT_W_2 << XCV_REG_ANPER_CTRL_CLOCK_DIV_BIT))
#define XCV_REG_ANPER_CTRL_CONVERT_BIT      16
#define XCV_REG_ANPER_CTRL_CONVERT_MASK     ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_CONVERT_BIT))
#define XCV_REG_ANPER_CTRL_D2EN_BIT         13
#define XCV_REG_ANPER_CTRL_D2EN_MASK        ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_D2EN_BIT))
#define XCV_REG_ANPER_CTRL_D1EN_BIT         12
#define XCV_REG_ANPER_CTRL_D1EN_MASK        ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_D1EN_BIT))
#define XCV_REG_ANPER_CTRL_AEN_BIT          11
#define XCV_REG_ANPER_CTRL_AEN_MASK         ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_AEN_BIT))
#define XCV_REG_ANPER_CTRL_ADCSEL_BIT       4
#define XCV_REG_ANPER_CTRL_ADCSEL_MASK      ((uint32)(BIT_W_3 << XCV_REG_ANPER_CTRL_ADCSEL_BIT))
#define XCV_REG_ANPER_CTRL_ADC_GAIN_BIT     3
#define XCV_REG_ANPER_CTRL_ADC_GAIN_MASK    ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_ADC_GAIN_BIT))
#define XCV_REG_ANPER_CTRL_DAC2_GAIN_BIT    2
#define XCV_REG_ANPER_CTRL_DAC2_GAIN_MASK   ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_DAC2_GAIN_BIT))
#define XCV_REG_ANPER_CTRL_DAC1_GAIN_BIT    1
#define XCV_REG_ANPER_CTRL_DAC1_GAIN_MASK   ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_DAC1_GAIN_BIT))
#define XCV_REG_ANPER_CTRL_REF_SEL_BIT      0
#define XCV_REG_ANPER_CTRL_REF_SEL_MASK     ((uint32)(BIT_W_1 << XCV_REG_ANPER_CTRL_REF_SEL_BIT))

/**** Analogue: AP_IS ****/
#define XCV_REG_ANPER_IS_CAPT_BIT        0
#define XCV_REG_ANPER_IS_CAPT_MASK       ((uint32)(BIT_W_1 << XCV_REG_ANPER_IS_CAPT_BIT))

#define XCV_REG_ANPER_IS_ADCACC_BIT      1
#define XCV_REG_ANPER_IS_ADCACC_MASK     ((uint32)(BIT_W_1 << XCV_REG_ANPER_IS_ADCACC_BIT))

/**** Analogue: AP_IE ****/
#define XCV_REG_ANPER_IE_CAPT_BIT        0
#define XCV_REG_ANPER_IE_CAPT_MASK       ((uint32)(BIT_W_1 << XCV_REG_ANPER_IE_CAPT_BIT))

#define XCV_REG_ANPER_IE_ADCACC_BIT      1
#define XCV_REG_ANPER_IE_ADCACC_MASK     ((uint32)(BIT_W_1 << XCV_REG_ANPER_IE_ADCACC_BIT))

/**** Analogue: AP_AVCTRL ****/
#define XCV_REG_ANPER_AVCTRL_AAS_BIT     0
#define XCV_REG_ANPER_AVCTRL_AAS_MASK    ((uint32)(BIT_W_2 << XCV_REG_ANPER_AVCTRL_AAS_BIT))

/**** Analogue: AP_AVVAL ****/
#define XCV_REG_ANPER_AVVAL_BIT          8
#define XCV_REG_ANPER_AVVAL_MASK         ((uint32)(BIT_W_16 << XCV_REG_ANPER_AVVAL_BIT))

/**** Analogue: AP_VAL ****/
#define XCV_REG_ANPER_VAL_C2_BIT         13
#define XCV_REG_ANPER_VAL_C2_MASK        ((uint32)(BIT_W_1 << XCV_REG_ANPER_VAL_C2_BIT))
#define XCV_REG_ANPER_VAL_C1_BIT         12
#define XCV_REG_ANPER_VAL_C1_MASK        ((uint32)(BIT_W_1 << XCV_REG_ANPER_VAL_C1_BIT))
#define XCV_REG_ANPER_VAL_ADC_BIT        0
#define XCV_REG_ANPER_VAL_ADC_MASK       ((uint32)(BIT_W_12 << XCV_REG_ANPER_VAL_ADC_BIT))

/**** Analogue: AP_COMPCTRL ****/
#define XCV_REG_ANPER_COMPCTRL_BCTRL_BIT    8
#define XCV_REG_ANPER_COMPCTRL_BCTRL_MASK   ((uint32)(BIT_W_1 << XCV_REG_ANPER_COMPCTRL_BCTRL_BIT))
#define XCV_REG_ANPER_COMPCTRL_HYS_BIT      6
#define XCV_REG_ANPER_COMPCTRL_HYS_MASK     ((uint32)(BIT_W_2 << XCV_REG_ANPER_COMPCTRL_HYS_BIT))
#define XCV_REG_ANPER_COMPCTRL_C2SEL_BIT    4
#define XCV_REG_ANPER_COMPCTRL_C2SEL_MASK   ((uint32)(BIT_W_2 << XCV_REG_ANPER_COMPCTRL_C2SEL_BIT))
#define XCV_REG_ANPER_COMPCTRL_C1SEL_BIT    2
#define XCV_REG_ANPER_COMPCTRL_C1SEL_MASK   ((uint32)(BIT_W_2 << XCV_REG_ANPER_COMPCTRL_C1SEL_BIT))
#define XCV_REG_ANPER_COMPCTRL_C2EN_BIT     1
#define XCV_REG_ANPER_COMPCTRL_C2EN_MASK    ((uint32)(BIT_W_1 << XCV_REG_ANPER_COMPCTRL_C2EN_BIT))
#define XCV_REG_ANPER_COMPCTRL_C1EN_BIT     0
#define XCV_REG_ANPER_COMPCTRL_C1EN_MASK    ((uint32)(BIT_W_1 << XCV_REG_ANPER_COMPCTRL_C1EN_BIT))

/**** Analogue: AP ****/
#define XCV_REG_ANPER_TRL_C2EN_BIT     1
#define XCV_REG_ANPER_COMPCTRL_C2EN_MASK    ((uint32)(BIT_W_1 << XCV_REG_ANPER_COMPCTRL_C2EN_BIT))
#define XCV_REG_ANPER_COMPCTRL_C1EN_BIT     0
#define XCV_REG_ANPER_COMPCTRL_C1EN_MASK    ((uint32)(BIT_W_1 << XCV_REG_ANPER_COMPCTRL_C1EN_BIT))


/**** Serial Interface: SIM_CTRL ****/
#define XCV_REG_SIM_CTRL_EN_BIT              7
#define XCV_REG_SIM_CTRL_EN_MASK             ((uint32)(BIT_W_1 << XCV_REG_SIM_CTRL_EN_BIT))
#define XCV_REG_SIM_CTRL_IE_BIT              6
#define XCV_REG_SIM_CTRL_IE_MASK             ((uint32)(BIT_W_1 << XCV_REG_SIM_CTRL_IE_BIT))
#define XCV_REG_SIM_CTRL_PSE_BIT             5
#define XCV_REG_SIM_CTRL_PSE_MASK            ((uint32)(BIT_W_1 << XCV_REG_SIM_CTRL_PSE_BIT))

/**** Serial Interface: SIS_CTRL ****/
#define XCV_REG_SIS_CTRL_WRFLMODE_BIT       12
#define XCV_REG_SIS_CTRL_WRFLMODE_MASK      ((uint32)(BIT_W_1 << XCV_REG_SIS_CTRL_WRFLMODE_BIT))
#define XCV_REG_SIS_CTRL_PSE_BIT            11
#define XCV_REG_SIS_CTRL_PSE_MASK           ((uint32)(BIT_W_1 << XCV_REG_SIS_CTRL_PSE_BIT))
#define XCV_REG_SIS_CTRL_EXTADDR_BIT        10
#define XCV_REG_SIS_CTRL_EXTADDR_MASK       ((uint32)(BIT_W_1 << XCV_REG_SIS_CTRL_EXTADDR_BIT))
#define XCV_REG_SIS_CTRL_SLAVEADDR_BIT      0
#define XCV_REG_SIS_CTRL_SLAVEADDR_MASK     ((uint32)(BIT_W_10 << XCV_REG_SIS_CTRL_SLAVEADDR_BIT))

/**** Serial Interface: SIM_CMD ****/
#define XCV_REG_SIM_CMD_STA_BIT              7
#define XCV_REG_SIM_CMD_STA_MASK             ((uint32)(BIT_W_1 << XCV_REG_SIM_CMD_STA_BIT))
#define XCV_REG_SIM_CMD_STO_BIT              6
#define XCV_REG_SIM_CMD_STO_MASK             ((uint32)(BIT_W_1 << XCV_REG_SIM_CMD_STO_BIT))
#define XCV_REG_SIM_CMD_RD_BIT               5
#define XCV_REG_SIM_CMD_RD_MASK              ((uint32)(BIT_W_1 << XCV_REG_SIM_CMD_RD_BIT))
#define XCV_REG_SIM_CMD_WR_BIT               4
#define XCV_REG_SIM_CMD_WR_MASK              ((uint32)(BIT_W_1 << XCV_REG_SIM_CMD_WR_BIT))
#define XCV_REG_SIM_CMD_ACK_BIT              3
#define XCV_REG_SIM_CMD_ACK_MASK             ((uint32)(BIT_W_1 << XCV_REG_SIM_CMD_ACK_BIT))
#define XCV_REG_SIM_CMD_IACK_BIT             0
#define XCV_REG_SIM_CMD_IACK_MASK            ((uint32)(BIT_W_1 << XCV_REG_SIM_CMD_IACK_BIT))

/**** Serial Interface: SIM_STAT ****/
#define XCV_REG_SIM_STAT_RXACK_BIT           7
#define XCV_REG_SIM_STAT_RXACK_MASK          ((uint32)(BIT_W_1 << XCV_REG_SIM_STAT_RXACK_BIT))
#define XCV_REG_SIM_STAT_BUSY_BIT            6
#define XCV_REG_SIM_STAT_BUSY_MASK           ((uint32)(BIT_W_1 << XCV_REG_SIM_STAT_BUSY_BIT))
#define XCV_REG_SIM_STAT_AL_BIT              5
#define XCV_REG_SIM_STAT_AL_MASK             ((uint32)(BIT_W_1 << XCV_REG_SIM_STAT_AL_BIT))
#define XCV_REG_SIM_STAT_ICMD_BIT            2
#define XCV_REG_SIM_STAT_ICMD_MASK           ((uint32)(BIT_W_1 << XCV_REG_SIM_STAT_ICMD_BIT))
#define XCV_REG_SIM_STAT_TIP_BIT             1
#define XCV_REG_SIM_STAT_TIP_MASK            ((uint32)(BIT_W_1 << XCV_REG_SIM_STAT_TIP_BIT))
#define XCV_REG_SIM_STAT_INT_BIT             0
#define XCV_REG_SIM_STAT_INT_MASK            ((uint32)(BIT_W_1 << XCV_REG_SIM_STAT_INT_BIT))

/**** Serial Interface: SIS_INT_STAT ****/
#define XCV_REG_SIS_INT_STAT_ERROR_BIT           4
#define XCV_REG_SIS_INT_STAT_ERROR_MASK          ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_ERROR_BIT))
#define XCV_REG_SIS_INT_STAT_LAST_DATA_BIT       3
#define XCV_REG_SIS_INT_STAT_LAST_DATA_MASK      ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_LAST_DATA_BIT))
#define XCV_REG_SIS_INT_STAT_DATA_WA_BIT         2
#define XCV_REG_SIS_INT_STAT_DATA_WA_MASK        ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_DATA_WA_BIT))
#define XCV_REG_SIS_INT_STAT_DATA_RTKN_BIT       1
#define XCV_REG_SIS_INT_STAT_DATA_RTKN_MASK      ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_DATA_RTKN_BIT))
#define XCV_REG_SIS_INT_STAT_DATA_RR_BIT         0
#define XCV_REG_SIS_INT_STAT_DATA_RR_MASK        ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_DATA_RR_BIT))

/**** Serial Interface: SIS_INT_ENABLE ****/
#define XCV_REG_SIS_INT_STAT_ERROR_IE_BIT           4
#define XCV_REG_SIS_INT_STAT_ERROR_IE_MASK          ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_ERROR_IE_BIT))
#define XCV_REG_SIS_INT_STAT_LAST_DATA_IE_BIT       3
#define XCV_REG_SIS_INT_STAT_LAST_DATA_IE_MASK      ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_LAST_DATA_IE_BIT))
#define XCV_REG_SIS_INT_STAT_DATA_WA_IE_BIT         2
#define XCV_REG_SIS_INT_INT_STAT_DATA_WA_IE_MASK    ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_DATA_WA_IE_BIT))
#define XCV_REG_SIS_INT_INT_STAT_DATA_RTKN_IE_BIT   1
#define XCV_REG_SIS_INT_STAT_DATA_RTKN_IE_MASK      ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_DATA_RTKN_IE_BIT))
#define XCV_REG_SIS_INT_STAT_DATA_RR_IE_BIT         0
#define XCV_REG_SIS_INT_STAT_DATA_RR_IE_MASK        ((uint32)(BIT_W_1 << XCV_REG_SIS_INT_STAT_DATA_RR_IE_BIT))

#ifdef JENNIC_CHIP_JN5169	
/**** Serial Interface: SIS_ADDR_MASK ****/
#define XCV_SIS_ADDR_MASK_PRIMARY_BIT				0
#define XCV_SIS_ADDR_MASK_PRIMARY_MASK          	((uint32)(BIT_W_1 << XCV_SIS_ADDR_MASK_PRIMARY_BIT))
#define XCV_SIS_ADDR_MASK_SECONDARY_BIT				1
#define XCV_SIS_ADDR_MASK_SECONDARY_MASK          	((uint32)(BIT_W_1 << XCV_SIS_ADDR_MASK_SECONDARY_BIT))
#define XCV_SIS_ADDR_MASK_GENERAL_CALL_BIT			2
#define XCV_SIS_ADDR_MASK_GENERAL_CALL_MASK         ((uint32)(BIT_W_1 << XCV_SIS_ADDR_MASK_GENERAL_CALL_BIT))

/**** Serial Interface: SIS_SLAVE_BUSY ****/
#define XCV_REG_SIS_SLAVE_BUSY_BIT         			0
#define XCV_REG_SIS_SLAVE_BUSY_MASK        			((uint32)(BIT_W_1 << XCV_REG_SIS_SLAVE_BUSY_BIT))
#endif

/**** Intelligent Peripheral: INTPER_CTRL ****/
#define XCV_REG_INTPER_CTRL_IE_BIT          7
#define XCV_REG_INTPER_CTRL_IE_MASK         ((uint32)(BIT_W_1 << XCV_REG_INTPER_CTRL_IE_BIT))
#define XCV_REG_INTPER_CTRL_IS_BIT          6
#define XCV_REG_INTPER_CTRL_IS_MASK         ((uint32)(BIT_W_1 << XCV_REG_INTPER_CTRL_IS_BIT))
#define XCV_REG_INTPER_CTRL_TX_NEG_BIT      5
#define XCV_REG_INTPER_CTRL_TX_NEG_MASK     ((uint32)(BIT_W_1 << XCV_REG_INTPER_CTRL_TX_NEG_BIT))
#define XCV_REG_INTPER_CTRL_RX_NEG_BIT      4
#define XCV_REG_INTPER_CTRL_RX_NEG_MASK     ((uint32)(BIT_W_1 << XCV_REG_INTPER_CTRL_RX_NEG_BIT))
#define XCV_REG_INTPER_CTRL_TXQ_BIT         3
#define XCV_REG_INTPER_CTRL_TXQ_MASK        ((uint32)(BIT_W_1 << XCV_REG_INTPER_CTRL_TXQ_BIT))
#define XCV_REG_INTPER_CTRL_RXQ_BIT         2
#define XCV_REG_INTPER_CTRL_RXQ_MASK        ((uint32)(BIT_W_1 << XCV_REG_INTPER_CTRL_RXQ_BIT))
#define XCV_REG_INTPER_CTRL_TXGO_BIT        1
#define XCV_REG_INTPER_CTRL_TXGO_MASK       ((uint32)(BIT_W_1 << XCV_REG_INTPER_CTRL_TXGO_BIT))
#define XCV_REG_INTPER_CTRL_RXGO_BIT        0
#define XCV_REG_INTPER_CTRL_RXGO_MASK       ((uint32)(BIT_W_1 << XCV_REG_INTPER_CTRL_RXGO_BIT))

/**** Intelligent Peripheral: RXADDR ****/
#define XCV_REG_INTPER_RXADDR_BIT           0
#define XCV_REG_INTPER_RXADDR_MASK          ((uint32)(BIT_W_1 << XCV_REG_INTPER_RXADDR_BIT))

/**** Intelligent Peripheral: TXADDR ****/
#define XCV_REG_INTPER_TXADDR_BIT           0
#define XCV_REG_INTPER_TXADDR_MASK          ((uint32)(BIT_W_1 << XCV_REG_INTPER_TXADDR_BIT))

/**** Intelligent Peripheral: RXLEN ****/
#define XCV_REG_INTPER_RXLEN_BIT            0
#define XCV_REG_INTPER_RXLEN_MASK           ((uint32)(BIT_W_6 << XCV_REG_INTPER_RXLEN_BIT))

/**** Intelligent Peripheral: TXLEN ****/
#define XCV_REG_INTPER_TXLEN_BIT            0
#define XCV_REG_INTPER_TXLEN_MASK           ((uint32)(BIT_W_6 << XCV_REG_INTPER_TXLEN_BIT))

/**** RXFCTL/TXFCTL ****/

/* Operations on Frame header */
#define XCV_REG_FCTL_TYPE_BIT           0
#define XCV_REG_FCTL_TYPE_MASK          ((uint32)(BIT_W_3/* << XCV_REG_FCTL_TYPE_BIT*/)) /* Optimised bit 0 */

#define XCV_REG_FCTL_SEC_BIT            3
#define XCV_REG_FCTL_SEC_MASK           ((uint32)(BIT_W_1 << XCV_REG_FCTL_SEC_BIT))

#define XCV_REG_FCTL_FP_BIT             4
#define XCV_REG_FCTL_FP_MASK            ((uint32)(BIT_W_1 << XCV_REG_FCTL_FP_BIT))

#define XCV_REG_FCTL_ACK_BIT            5
#define XCV_REG_FCTL_ACK_MASK           ((uint32)(BIT_W_1 << XCV_REG_FCTL_ACK_BIT))

#define XCV_REG_FCTL_IP_BIT             6
#define XCV_REG_FCTL_IP_MASK            ((uint32)(BIT_W_1 << XCV_REG_FCTL_IP_BIT))

#define XCV_REG_FCTL_DAM_BIT            10
#define XCV_REG_FCTL_DAM_MASK           ((uint32)(BIT_W_2 << XCV_REG_FCTL_DAM_BIT))
#define XCV_REG_FCTL_DAM(x)             (((x) & XCV_REG_FCTL_DAM_MASK) >> XCV_REG_FCTL_DAM_BIT)

#define XCV_REG_FCTL_SAM_BIT            14
#define XCV_REG_FCTL_SAM_MASK           ((uint32)(BIT_W_2 << XCV_REG_FCTL_SAM_BIT))
#define XCV_REG_FCTL_SAM(x)             (((x) & XCV_REG_FCTL_SAM_MASK) >> XCV_REG_FCTL_SAM_BIT)

/* Frame types */
#define XCV_REG_FCTL_TYPE_BEACON        0
#define XCV_REG_FCTL_TYPE_DATA          1
#define XCV_REG_FCTL_TYPE_ACK           2
#define XCV_REG_FCTL_TYPE_CMD           3

/* Addr modes */
#define XCV_REG_FCTL_AM_NONE            0
#define XCV_REG_FCTL_AM_RSVD            1
#define XCV_REG_FCTL_AM_SHORT           2
#define XCV_REG_FCTL_AM_EXT             3


#define XCV_REG_FCTL_FORMAT(type, sec, fp, ack, ip, dam, sam) \
    (((type) & BIT_W_3) | \
     (((sec) & BIT_W_1) << XCV_REG_FCTL_SEC_BIT) | \
     (((fp) & BIT_W_1) << XCV_REG_FCTL_FP_BIT) | \
     (((ack) & BIT_W_1) << XCV_REG_FCTL_ACK_BIT) | \
     (((ip) & BIT_W_1) << XCV_REG_FCTL_IP_BIT) | \
     (((dam) & BIT_W_2) << XCV_REG_FCTL_DAM_BIT) | \
     (((sam) & BIT_W_2) << XCV_REG_FCTL_SAM_BIT))

/**** SCTCR ****/

#define XCV_REG_SCTCR_E0_BIT    0
#define XCV_REG_SCTCR_E0_MASK   ((uint32)(BIT_W_1 << XCV_REG_SCTCR_E0_BIT))
#define XCV_REG_SCTCR_E1_BIT    1
#define XCV_REG_SCTCR_E1_MASK   ((uint32)(BIT_W_1 << XCV_REG_SCTCR_E1_BIT))
#if !(JENNIC_HW_BBC_DMA)
#define XCV_REG_SCTCR_E2_BIT    2
#define XCV_REG_SCTCR_E2_MASK   ((uint32)(BIT_W_1 << XCV_REG_SCTCR_E2_BIT))
#define XCV_REG_SCTCR_E3_BIT    3
#define XCV_REG_SCTCR_E3_MASK   ((uint32)(BIT_W_1 << XCV_REG_SCTCR_E3_BIT))
#endif

/**** RXCTL ****/

#define XCV_REG_RXCTL_SCH_BIT   0
#define XCV_REG_RXCTL_SCH_MASK  ((uint32)(BIT_W_1 << XCV_REG_RXCTL_SCH_BIT))
#define XCV_REG_RXCTL_SS_BIT    1
#define XCV_REG_RXCTL_SS_MASK   ((uint32)(BIT_W_1 << XCV_REG_RXCTL_SS_BIT))
#define XCV_REG_RXCTL_ICAP_BIT  2
#define XCV_REG_RXCTL_ICAP_MASK ((uint32)(BIT_W_1 << XCV_REG_RXCTL_ICAP_BIT))
#define XCV_REG_RXCTL_AA_BIT    3
#define XCV_REG_RXCTL_AA_MASK   ((uint32)(BIT_W_1 << XCV_REG_RXCTL_AA_BIT))
#define XCV_REG_RXCTL_PRSP_BIT  4
#define XCV_REG_RXCTL_PRSP_MASK ((uint32)(BIT_W_1 << XCV_REG_RXCTL_PRSP_BIT))

#define XCV_REG_RXCTL_FORMAT(sched_basis, sched_ss, in_cap, auto_ack) \
   (((sched_basis) & BIT_W_1) | \
    (((sched_ss)   & BIT_W_1) << XCV_REG_RXCTL_SS_BIT) | \
    (((in_cap)     & BIT_W_1) << XCV_REG_RXCTL_ICAP_BIT) | \
    (((auto_ack)   & BIT_W_1) << XCV_REG_RXCTL_AA_BIT))

/**** RXMPID ****/
#define XCV_REG_RXMPID_PAN_ID_BIT  0
#define XCV_REG_RXMPID_PAN_ID_MASK ((uint32)(BIT_W_16 << XCV_REG_RXMPID_PAN_ID_BIT))
#define XCV_REG_RXMPID_COORD_BIT   16
#define XCV_REG_RXMPID_COORD_MASK  ((uint32)(BIT_W_1 << XCV_REG_RXMPID_COORD_BIT))

/**** RXPROM ****/
#define XCV_REG_RXPROM_AM_BIT    0
#define XCV_REG_RXPROM_AM_MASK   ((uint32)(BIT_W_1 << XCV_REG_RXPROM_AM_BIT))
#ifndef CHIP_RELEASE_1
#define XCV_REG_RXPROM_FCSE_BIT  1
#define XCV_REG_RXPROM_FCSE_MASK ((uint32)(BIT_W_1 << XCV_REG_RXPROM_FCSE_BIT))
#endif
#if JENNIC_HW_BBC_DMA
#define XCV_REG_RXPROM_AMAL_BIT  2
#define XCV_REG_RXPROM_AMAL_MASK ((uint32)(BIT_W_1 << XCV_REG_RXPROM_AMAL_BIT))
#endif

/**** XCV_REG_RXSTAT ****/
#define XCV_REG_RXSTAT_FCSE_BIT   0
#define XCV_REG_RXSTAT_FCSE_MASK  ((uint32)(BIT_W_1 << XCV_REG_RXSTAT_FCSE_BIT))
#define XCV_REG_RXSTAT_ABORT_BIT  1
#define XCV_REG_RXSTAT_ABORT_MASK ((uint32)(BIT_W_1 << XCV_REG_RXSTAT_ABORT_BIT))
#if !(JENNIC_HW_BBC_DMA)
#define XCV_REG_RXSTAT_FSC_BIT    2
#define XCV_REG_RXSTAT_FSC_MASK   ((uint32)(BIT_W_1 << XCV_REG_RXSTAT_FSC_BIT))
#define XCV_REG_RXSTAT_FSF_BIT    3
#define XCV_REG_RXSTAT_FSF_MASK   ((uint32)(BIT_W_1 << XCV_REG_RXSTAT_FSF_BIT))
#else
#define XCV_REG_RXSTAT_INPKT_BIT  4
#define XCV_REG_RXSTAT_INPKT_MASK ((uint32)(BIT_W_1 << XCV_REG_RXSTAT_INPKT_BIT))
#define XCV_REG_RXSTAT_MAL_BIT    5
#define XCV_REG_RXSTAT_MAL_MASK   ((uint32)(BIT_W_1 << XCV_REG_RXSTAT_MAL_BIT))
#endif

/**** TXCTL ****/

#define XCV_REG_TXCTL_SCH_BIT   0
#define XCV_REG_TXCTL_SCH_MASK  ((uint32)(BIT_W_1 << XCV_REG_TXCTL_SCH_BIT))
#define XCV_REG_TXCTL_SS_BIT    1
#define XCV_REG_TXCTL_SS_MASK   ((uint32)(BIT_W_1 << XCV_REG_TXCTL_SS_BIT))
#define XCV_REG_TXCTL_SOVR_BIT  2
#define XCV_REG_TXCTL_SOVR_MASK ((uint32)(BIT_W_1 << XCV_REG_TXCTL_SOVR_BIT))
#define XCV_REG_TXCTL_AA_BIT    3
#define XCV_REG_TXCTL_AA_MASK   ((uint32)(BIT_W_1 << XCV_REG_TXCTL_AA_BIT))
#define XCV_REG_TXCTL_MODE_BIT  4
#define XCV_REG_TXCTL_MODE_MASK ((uint32)(BIT_W_2 << XCV_REG_TXCTL_MODE_BIT))

#define XCV_REG_TXCTL_VALUE(sched_basis, sched_ss, slot_override, auto_ack, mode) \
   (((sched_basis)    & BIT_W_1) | \
    (((sched_ss)      & BIT_W_1) << XCV_REG_TXCTL_SS_BIT) | \
    (((slot_override) & BIT_W_1) << XCV_REG_TXCTL_SOVR_BIT) | \
    (((auto_ack)      & BIT_W_1) << XCV_REG_TXCTL_AA_BIT) | \
    (((mode)          & BIT_W_2) << XCV_REG_TXCTL_MODE_BIT))

#define XCV_REG_TXCTL_SEND_AT(mode) XCV_REG_TXCTL_VALUE(1, 1, 0, 1, (mode))
#define XCV_REG_TXCTL_SEND_NOW(mode) XCV_REG_TXCTL_VALUE(0, 1, 0, 1, (mode))

/**** XCV_REG_TXSTAT ****/

#define XCV_REG_TXSTAT_CCAE_BIT   0
#define XCV_REG_TXSTAT_CCAE_MASK  ((uint32)(BIT_W_1 << XCV_REG_TXSTAT_CCAE_BIT))
#define XCV_REG_TXSTAT_ACKE_BIT   1
#define XCV_REG_TXSTAT_ACKE_MASK  ((uint32)(BIT_W_1 << XCV_REG_TXSTAT_ACKE_BIT))
#define XCV_REG_TXSTAT_OOTE_BIT   2
#define XCV_REG_TXSTAT_OOTE_MASK  ((uint32)(BIT_W_1 << XCV_REG_TXSTAT_OOTE_BIT))
#if JENNIC_HW_BBC_DMA
#define XCV_REG_TXSTAT_RXABT_BIT  3
#define XCV_REG_TXSTAT_RXABT_MASK ((uint32)(BIT_W_1 << XCV_REG_TXSTAT_RXABT_BIT))
#define XCV_REG_TXSTAT_RXFP_BIT   4
#define XCV_REG_TXSTAT_RXFP_MASK  ((uint32)(BIT_W_1 << XCV_REG_TXSTAT_RXFP_BIT))
#endif

/**** XCV_REG_TXMBEBT ****/
#define XCV_REG_TXMBEBT_MINBE_BIT     0
#define XCV_REG_TXMBEBT_MINBE_MASK    ((uint32)(BIT_W_4 << XCV_REG_TXMBEBT_MINBE_BIT))
#define XCV_REG_TXMBEBT_MAXBO_BIT     4
#define XCV_REG_TXMBEBT_MAXBO_MASK    ((uint32)(BIT_W_3 << XCV_REG_TXMBEBT_MAXBO_BIT))
#define XCV_REG_TXMBEBT_BLE_BIT       7
#define XCV_REG_TXMBEBT_MAXBE_BIT     8
#define XCV_REG_TXMBEBT_MAXBE_MASK    ((uint32)(BIT_W_4 << XCV_REG_TXMBEBT_MAXBE_BIT))
#define XCV_REG_TXMBEBT_CSMA_DLY_BIT  12
#define XCV_REG_TXMBEBT_CSMA_DLY_MASK ((uint32)(BIT_W_1 << XCV_REG_TXMBEBT_CSMA_DLY_BIT))

#define XCV_REG_TXMBEBT_FORMAT(min_be, ble, max_boffs, max_be) \
    (((min_be)     & BIT_W_4) | \
     (((ble)       & BIT_W_1) << XCV_REG_TXMBEBT_BLE_BIT) | \
     (((max_be)    & BIT_W_4) << XCV_REG_TXMBEBT_MAXBE_BIT) | \
     (((max_boffs) & BIT_W_3) << XCV_REG_TXMBEBT_MAXBO_BIT))

/**** IER ****/
#define XCV_REG_IER_TX_BIT      0
#define XCV_REG_IER_TX_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_TX_BIT))
#if JENNIC_HW_BBC_DMA
#define XCV_REG_IER_RX_H_BIT    1
#define XCV_REG_IER_RX_H_MASK   ((uint32)(BIT_W_1 << XCV_REG_IER_RX_H_BIT))
#define XCV_REG_IER_RX_BIT      2
#define XCV_REG_IER_RX_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_RX_BIT))
#else
#define XCV_REG_IER_RX_BIT      1
#define XCV_REG_IER_RX_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_RX_BIT))
#define XCV_REG_IER_RX_H_BIT    2
#define XCV_REG_IER_RX_H_MASK   ((uint32)(BIT_W_1 << XCV_REG_IER_RX_H_BIT))
#endif
#define XCV_REG_IER_M0_BIT      4
#define XCV_REG_IER_M0_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_M0_BIT))
#define XCV_REG_IER_M1_BIT      5
#define XCV_REG_IER_M1_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_M1_BIT))
#define XCV_REG_IER_M2_BIT      6
#define XCV_REG_IER_M2_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_M2_BIT))
#define XCV_REG_IER_M3_BIT      7
#define XCV_REG_IER_M3_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_M3_BIT))
#define XCV_REG_IER_T0_BIT      8
#define XCV_REG_IER_T0_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_T0_BIT))
#define XCV_REG_IER_T1_BIT      9
#define XCV_REG_IER_T1_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_T1_BIT))
#if !(JENNIC_HW_BBC_DMA)
#define XCV_REG_IER_T2_BIT      10
#define XCV_REG_IER_T2_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_T2_BIT))
#define XCV_REG_IER_T3_BIT      11
#define XCV_REG_IER_T3_MASK     ((uint32)(BIT_W_1 << XCV_REG_IER_T3_BIT))
#endif

/**** ISR ****/
/* FYI from CJG: M0, M3, T1, T2 and T3 are not used by the MAC software */
#define XCV_REG_ISR_TX_BIT      0
#define XCV_REG_ISR_TX_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_TX_BIT))
#if JENNIC_HW_BBC_DMA
#define XCV_REG_ISR_RX_H_BIT    1
#define XCV_REG_ISR_RX_H_MASK   ((uint32)(BIT_W_1 << XCV_REG_ISR_RX_H_BIT))
#define XCV_REG_ISR_RX_BIT      2
#define XCV_REG_ISR_RX_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_RX_BIT))
#else
#define XCV_REG_ISR_RX_BIT      1
#define XCV_REG_ISR_RX_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_RX_BIT))
#define XCV_REG_ISR_RX_H_BIT    2
#define XCV_REG_ISR_RX_H_MASK   ((uint32)(BIT_W_1 << XCV_REG_ISR_RX_H_BIT))
#endif
#define XCV_REG_ISR_CC_BIT      3
#define XCV_REG_ISR_CC_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_CC_BIT))
#define XCV_REG_ISR_M0_BIT      4
#define XCV_REG_ISR_M0_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_M0_BIT))
#define XCV_REG_ISR_M1_BIT      5
#define XCV_REG_ISR_M1_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_M1_BIT))
#define XCV_REG_ISR_M2_BIT      6
#define XCV_REG_ISR_M2_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_M2_BIT))
#define XCV_REG_ISR_M3_BIT      7
#define XCV_REG_ISR_M3_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_M3_BIT))
#define XCV_REG_ISR_T0_BIT      8
#define XCV_REG_ISR_T0_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_T0_BIT))
#define XCV_REG_ISR_T1_BIT      9
#define XCV_REG_ISR_T1_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_T1_BIT))
#if !(JENNIC_HW_BBC_DMA)
#define XCV_REG_ISR_T2_BIT      10
#define XCV_REG_ISR_T2_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_T2_BIT))
#define XCV_REG_ISR_T3_BIT      11
#define XCV_REG_ISR_T3_MASK     ((uint32)(BIT_W_1 << XCV_REG_ISR_T3_BIT))
#endif

#if JENNIC_HW_BBC_DMA
#define XCV_REG_ISR_TIMER_MASK  ((uint32)(BIT_W_6 << XCV_REG_ISR_M0_BIT))
#else
#define XCV_REG_ISR_TIMER_MASK  ((uint32)(BIT_W_8 << XCV_REG_ISR_M0_BIT))
#endif

/**** SM_STATE ****/
#define XCV_REG_SM_STATE_SUP_BIT   0
#define XCV_REG_SM_STATE_SUP_MASK  ((uint32)(BIT_W_4 << XCV_REG_SM_STATE_SUP_BIT))
#define XCV_REG_SM_STATE_CSMA_BIT  4
#define XCV_REG_SM_STATE_CSMA_MASK ((uint32)(BIT_W_3 << XCV_REG_SM_STATE_CSMA_BIT))
#define XCV_REG_SM_STATE_ISA_BIT   8
#define XCV_REG_SM_STATE_ISA_MASK  ((uint32)(BIT_W_5 << XCV_REG_SM_STATE_ISA_BIT))

/**** SCTL ****/
#define XCV_REG_SCTL_USE_BIT    0
#define XCV_REG_SCTL_USE_MASK   ((uint32)(BIT_W_1 << XCV_REG_SCTL_USE_BIT))
#define XCV_REG_SCTL_SNAP_BIT   1
#define XCV_REG_SCTL_SNAP_MASK  ((uint32)(BIT_W_1 << XCV_REG_SCTL_SNAP_BIT))
#define XCV_REG_SCTL_CO_BIT     2
#define XCV_REG_SCTL_CO_MASK    ((uint32)(BIT_W_1 << XCV_REG_SCTL_CO_BIT))
#define XCV_REG_SCTL_PHYON_BIT  3
#define XCV_REG_SCTL_PHYON_MASK ((uint32)(BIT_W_1 << XCV_REG_SCTL_PHYON_BIT))

/**** PHY_STAT ****/
#define XCV_REG_PHY_STAT_STATE_BIT  0
#define XCV_REG_PHY_STAT_STATE_MASK ((uint32)(BIT_W_4 << XCV_REG_PHY_STAT_STATE_BIT))
//#define XCV_REG_PHY_STAT_LCK_BIT    5
//#define XCV_REG_PHY_STAT_LCK_MASK   ((uint32)(BIT_W_1 << XCV_REG_PHY_STAT_LCK_BIT))
//#define XCV_REG_PHY_STAT_CALFN_BIT  6
//#define XCV_REG_PHY_STAT_CALFN_MASK ((uint32)(BIT_W_1 << XCV_REG_PHY_STAT_CALFN_BIT))

/* Phy states as found in XCV_REG_PHY_STAT_STATE_MASK (incomplete list) */
#define XCV_REG_PHY_STATE_SYNTH_LOCKED 3
#define XCV_REG_PHY_STATE_RX           10

/**** PHY_PA_CTRL ****/
#define XCV_REG_PHY_PA_CTRL_PAP_BIT         12
#define XCV_REG_PHY_PA_CTRL_PAP_MASK          ((uint32)(BIT_W_3 << XCV_REG_PHY_PA_CTRL_PAP_BIT ))

/**** PHY_MCTRL ****/
#define XCV_REG_PHY_MCTRL_RMI_BIT           0
#define XCV_REG_PHY_MCTRL_RMI_MASK          ((uint32)(BIT_W_1 << XCV_REG_PHY_MCTRL_RMI_BIT))
#define XCV_REG_PHY_MCTRL_MIOM_BIT          1
#define XCV_REG_PHY_MCTRL_MIOM_MASK         ((uint32)(BIT_W_1 << XCV_REG_PHY_MCTRL_MIOM_BIT))
#define XCV_REG_PHY_MCTRL_MPHYON_BIT        2
#define XCV_REG_PHY_MCTRL_MPHYON_MASK       ((uint32)(BIT_W_1 << XCV_REG_PHY_MCTRL_MPHYON_BIT))
#define XCV_REG_PHY_MCTRL_MPHYTX_BIT        3
#define XCV_REG_PHY_MCTRL_MPHYTX_MASK       ((uint32)(BIT_W_1 << XCV_REG_PHY_MCTRL_MPHYTX_BIT))
#define XCV_REG_PHY_MCTRL_MCCAT_BIT         4
#define XCV_REG_PHY_MCTRL_MCCAT_MASK        ((uint32)(BIT_W_1 << XCV_REG_PHY_MCTRL_MCCAT_BIT))
#define XCV_REG_PHY_MCTRL_MEDT_BIT          5
#define XCV_REG_PHY_MCTRL_MEDT_MASK         ((uint32)(BIT_W_1 << XCV_REG_PHY_MCTRL_MEDT_BIT))
//#define XCV_REG_PHY_MCTRL_MCCAM_BIT         6
//#define XCV_REG_PHY_MCTRL_MCCAM_MASK        ((uint32)(BIT_W_2 << XCV_REG_PHY_MCTRL_MCCAM_BIT))
//#define XCV_REG_PHY_MCTRL_CCA_THRESH_BIT    8
//#define XCV_REG_PHY_MCTRL_CCA_THRESH_MASK   ((uint32)(BIT_W_6 << XCV_REG_PHY_MCTRL_CCA_THRESH_BIT))
//#define XCV_REG_PHY_MCTRL_TX_TEST_MODE_BIT  14
//#define XCV_REG_PHY_MCTRL_TX_TEST_MODE_MASK ((uint32)(BIT_W_1 << XCV_REG_PHY_MCTRL_TX_TEST_MODE_BIT))
//#define XCV_REG_PHY_MCTRL_TX_TEST_SIG_BIT   15
//#define XCV_REG_PHY_MCTRL_TX_TEST_SIG_MASK  ((uint32)(BIT_W_1 << XCV_REG_PHY_MCTRL_TX_TEST_SIG_BIT))


/**** PHY_MCC *******/
#define XCV_REG_PHY_MCCA_CCAM_BIT           0
#define XCV_REG_PHY_MCCA_CCAM_MASK          ((uint32)(BIT_W_2 << XCV_REG_PHY_MCCA_CCAM_BIT))

/**** PHY_MSTAT ****/
//#define XCV_REG_PHY_MSTAT0_MED_BIT          0
//#define XCV_REG_PHY_MSTAT0_MED_MASK         ((uint32)(BIT_W_6 << XCV_REG_PHY_MSTAT0_MED_BIT))
#define XCV_REG_PHY_MSTAT_SQI_BIT          8
#define XCV_REG_PHY_MSTAT_SQI_MASK         ((uint32)(BIT_W_8 << XCV_REG_PHY_MSTAT_SQI_BIT))
#define XCV_REG_PHY_MSTAT0_MCCAS_BIT        16
#define XCV_REG_PHY_MSTAT0_MCCAS_MASK       ((uint32)(BIT_W_1 << XCV_REG_PHY_MSTAT0_MCCAS_BIT))
#define XCV_REG_PHY_MSTAT_ED_BIT           0
#define XCV_REG_PHY_MSTAT_ED_MASK          ((uint32)(BIT_W_8 << XCV_REG_PHY_MSTAT_ED_BIT))

/**** PHY_IS ****/
#define XCV_REG_PHY_IS_CAL_BIT              0
#define XCV_REG_PHY_IS_CAL_MASK             ((uint32)(BIT_W_1 << XCV_REG_PHY_IS_CAL_BIT))
#define XCV_REG_PHY_IS_PHYRDY_BIT           1
#define XCV_REG_PHY_IS_PHYRDY_MASK          ((uint32)(BIT_W_1 << XCV_REG_PHY_IS_PHYRDY_BIT))
#define XCV_REG_PHY_IS_ED_BIT               2
#define XCV_REG_PHY_IS_ED_MASK              ((uint32)(BIT_W_1 << XCV_REG_PHY_IS_ED_BIT))
#define XCV_REG_PHY_IS_CCA_BIT              3
#define XCV_REG_PHY_IS_CCA_MASK             ((uint32)(BIT_W_1 << XCV_REG_PHY_IS_CCA_BIT))
#define XCV_REG_PHY_IS_VCO_CAL_BIT          7
#define XCV_REG_PHY_IS_VCO_CAL_MASK         ((uint32)(BIT_W_1 << XCV_REG_PHY_IS_VCO_CAL_BIT))

/**** PHY_IE ****/
#define XCV_REG_PHY_IE_CAL_BIT              0
#define XCV_REG_PHY_IE_CAL_MASK             ((uint32)(BIT_W_1 << XCV_REG_PHY_IE_CAL_BIT))
#define XCV_REG_PHY_IE_PHYRDY_BIT           1
#define XCV_REG_PHY_IE_PHYRDY_MASK          ((uint32)(BIT_W_1 << XCV_REG_PHY_IE_PHYRDY_BIT))
#define XCV_REG_PHY_IE_ED_BIT               2
#define XCV_REG_PHY_IE_ED_MASK              ((uint32)(BIT_W_1 << XCV_REG_PHY_IE_ED_BIT))
#define XCV_REG_PHY_IE_CCA_BIT              3
#define XCV_REG_PHY_IE_CCA_MASK             ((uint32)(BIT_W_1 << XCV_REG_PHY_IE_CCA_BIT))
#define XCV_REG_PHY_IE_VCO_CAL_BIT          7
#define XCV_REG_PHY_IE_VCO_CAL_MASK         ((uint32)(BIT_W_1 << XCV_REG_PHY_IE_VCO_CAL_BIT))

/**** AES ****/
#define AES_COMMAND_SHIFT 4
#define XCV_REG_AES_SET_KEY_CMD       ((1 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_GO_CMD            ((5 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_RESET_CMD         ((12 << AES_COMMAND_SHIFT) | 1)
#if JENNIC_HW_BBC_ISA
#define XCV_REG_AES_SET_MODE_CMD      ((0 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_LOAD_CTR_CMD      ((3 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_LOAD_IV_CMD       ((4 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_LOAD_ALENGTH_CMD  ((6 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_LOAD_MLENGTH_CMD  ((7 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_LOAD_ML_CMD       ((8 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_LOAD_NONCE_CMD    ((9 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_INIT_CCM_AUTH_CMD ((10 << AES_COMMAND_SHIFT) | 1)
#define XCV_REG_AES_GEN_CCM_AUTH_CMD  ((11 << AES_COMMAND_SHIFT) | 1)
#endif

#define XCV_REG_AES_ACL_CMD_DONE_MASK (1)

/**** ISA ****/
#define XCV_REG_ISA_XFORM_GOBUSY_BIT   0
#define XCV_REG_ISA_XFORM_GOBUSY_MASK  ((uint32)(BIT_W_1 << XCV_REG_ISA_XFORM_GOBUSY_BIT))
#define XCV_REG_ISA_XFORM_ABORTED_BIT  1
#define XCV_REG_ISA_XFORM_ABORTED_MASK ((uint32)(BIT_W_1 << XCV_REG_ISA_XFORM_ABORTED_BIT))
#define XCV_REG_ISA_XFORM_TXNOTRX_BIT  2
#define XCV_REG_ISA_XFORM_TXNOTRX_MASK ((uint32)(BIT_W_1 << XCV_REG_ISA_XFORM_TXNOTRX_BIT))
#define XCV_REG_ISA_XFORM_USEHDR_BIT   3
#define XCV_REG_ISA_XFORM_USEHDR_MASK  ((uint32)(BIT_W_1 << XCV_REG_ISA_XFORM_USEHDR_BIT))
#define XCV_REG_ISA_XFORM_STATUS_BIT   4
#define XCV_REG_ISA_XFORM_STATUS_MASK  ((uint32)(BIT_W_1 << XCV_REG_ISA_XFORM_STATUS_BIT))
#define XCV_REG_ISA_XFORM_SWAP_BIT     5
#define XCV_REG_ISA_XFORM_SWAP_MASK    ((uint32)(BIT_W_1 << XCV_REG_ISA_XFORM_SWAP_BIT))
#define XCV_REG_ISA_XFORM_INLINE_BIT   6
#define XCV_REG_ISA_XFORM_INLINE_MASK  ((uint32)(BIT_W_1 << XCV_REG_ISA_XFORM_INLINE_BIT))
#define XCV_REG_ISA_XFORM_MODE_BIT     8
#define XCV_REG_ISA_XFORM_MODE_MASK    ((uint32)(BIT_W_3 << XCV_REG_ISA_XFORM_MODE_BIT))

/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/

/* Register addresses. All offsets are the actual values shifted right by 2 bits
   (i.e. take actual address and divide by 4). XCV_EXT_OFFSET is for integration
   testing only and does not map onto valid hardware. */
#define XCV_BASE_ADDR 0x2001000UL

#define XCV_SYS_OFFSET    0x000
#define XCV_TX_REV_OFFSET 0x080
#define XCV_RX_REV_OFFSET 0x0c0
#define XCV_TI_OFFSET     0x100
#define XCV_TX_OFFSET     0x140
#define XCV_RX_OFFSET     0x180
#define XCV_SEC_OFFSET    0x200
#define XCV_AES_OFFSET    0x300
#define XCV_PHY_OFFSET    0x380
#define XCV_EXT_OFFSET    0x400

#define XCV_GPIO_OFFSET   ((0x2002000UL - XCV_BASE_ADDR) >> 2)
#define XCV_UART0_OFFSET  ((0x2003000UL - XCV_BASE_ADDR) >> 2)
#define XCV_UART1_OFFSET  ((0x2004000UL - XCV_BASE_ADDR) >> 2)
#define XCV_TMR0_OFFSET   ((0x2005000UL - XCV_BASE_ADDR) >> 2)
#if !(defined JENNIC_CHIP_JN5142) && !(defined JENNIC_CHIP_JN5142_HDK) && !(defined JENNIC_CHIP_JN5142J01) && !(defined JENNIC_CHIP_FAMILY_JN516x)
#define XCV_TMR1_OFFSET   ((0x2006000UL - XCV_BASE_ADDR) >> 2)
#define XCV_TMR2_OFFSET   ((0x200A000UL - XCV_BASE_ADDR) >> 2)
#else
#define XCV_TMR1_OFFSET   ((0x200A000UL - XCV_BASE_ADDR) >> 2)
#define XCV_TMR2_OFFSET   ((0x200B000UL - XCV_BASE_ADDR) >> 2)
#endif
#define XCV_I2C_M_OFFSET  ((0x2007000UL - XCV_BASE_ADDR) >> 2)
#define XCV_I2C_S_OFFSET  ((0x2007800UL - XCV_BASE_ADDR) >> 2)
#define XCV_SPIM_OFFSET   ((0x2008000UL - XCV_BASE_ADDR) >> 2)
#define XCV_INTPER_OFFSET ((0x2009000UL - XCV_BASE_ADDR) >> 2)
#define XCV_INTPER_MEM_OFFSET ((0x2009800UL - XCV_BASE_ADDR) >> 2)
#define XCV_ANPER_OFFSET ((0x2001F00UL - XCV_BASE_ADDR) >> 2)
#define XCV_DAI_OFFSET   ((0x200B000UL - XCV_BASE_ADDR) >> 2)
#define XCV_FIFO_OFFSET  ((0x200C000UL - XCV_BASE_ADDR) >> 2)

/**
 * Registers
 * The register offsets from the base as indices
 * @ingroup grp_XCV
 */
typedef enum
{
    /* Receive MPDU Ancillary */
    XCV_REG_RXTSTP  = XCV_TI_OFFSET + 13,
#if !(JENNIC_HW_BBC_DMA)
    XCV_REG_RXLEN   = XCV_RX_OFFSET + 0,
    /* Receive MPDU */
    XCV_REG_RXFCTL  = XCV_RX_OFFSET + 1,
    XCV_REG_RXSEQ   = XCV_RX_OFFSET + 2,
    XCV_REG_RXDPID  = XCV_RX_OFFSET + 3,
    XCV_REG_RXDSAD  = XCV_RX_OFFSET + 4,
    XCV_REG_RXDEADL = XCV_RX_OFFSET + 5,
    XCV_REG_RXDEADH = XCV_RX_OFFSET + 6,
    XCV_REG_RXSPID  = XCV_RX_OFFSET + 7,
    XCV_REG_RXSSAD  = XCV_RX_OFFSET + 8,
    XCV_REG_RXSEADL = XCV_RX_OFFSET + 9,
    XCV_REG_RXSEADH = XCV_RX_OFFSET + 10,
    XCV_REG_RXMSDU  = XCV_RX_OFFSET + 11, /* 32 words in size */
    XCV_REG_RXMSDU_REV  = XCV_RX_REV_OFFSET + 11, /* 32 words in size */
#endif
    /* Receive Control/Status */
    XCV_REG_RXCTL   = XCV_RX_OFFSET + 48,
    XCV_REG_RXETST  = XCV_TI_OFFSET + 12,
    XCV_REG_RXSTAT  = XCV_RX_OFFSET + 49,
    XCV_REG_RXMPID  = XCV_RX_OFFSET + 50,
    XCV_REG_RXMSAD  = XCV_RX_OFFSET + 51,
    XCV_REG_RXMEADL = XCV_RX_OFFSET + 52,
    XCV_REG_RXMEADH = XCV_RX_OFFSET + 53,
#if JENNIC_HW_BBC_DMA
    XCV_REG_RXBUFAD = XCV_RX_OFFSET + 55,
#endif
    XCV_REG_RXPROM  = XCV_RX_OFFSET + 56,
#if !(JENNIC_HW_BBC_DMA)
    XCV_REG_RXHOFST = XCV_RX_OFFSET + 57,
#endif

    /* Transmit MPDU Ancillary */
    XCV_REG_TXTSTP  = XCV_TI_OFFSET + 14,
#if !(JENNIC_HW_BBC_DMA)
    XCV_REG_TXLEN   = XCV_TX_OFFSET + 0,
    /* Transmit MPDU */
    XCV_REG_TXFCTL  = XCV_TX_OFFSET + 1,
    XCV_REG_TXSEQ   = XCV_TX_OFFSET + 2,
    XCV_REG_TXDPID  = XCV_TX_OFFSET + 3,
    XCV_REG_TXDSAD  = XCV_TX_OFFSET + 4,
    XCV_REG_TXDEADL = XCV_TX_OFFSET + 5,
    XCV_REG_TXDEADH = XCV_TX_OFFSET + 6,
    XCV_REG_TXSPID  = XCV_TX_OFFSET + 7,
    XCV_REG_TXSSAD  = XCV_TX_OFFSET + 8,
    XCV_REG_TXSEADL = XCV_TX_OFFSET + 9,
    XCV_REG_TXSEADH = XCV_TX_OFFSET + 10,
    XCV_REG_TXMSDU  = XCV_TX_OFFSET + 11, /* 32 words in size */
    XCV_REG_TXMSDU_REV  = XCV_TX_REV_OFFSET + 11, /* 32 words in size */
#endif
    /* Transmit Control/Status */
    XCV_REG_TXCTL   = XCV_TX_OFFSET + 48,
    XCV_REG_TXSTAT  = XCV_TX_OFFSET + 49,
    XCV_REG_TXMBEBT = XCV_TX_OFFSET + 50,
    XCV_REG_TXCSMAC = XCV_TX_OFFSET + 51,
    XCV_REG_TXRETRY = XCV_TX_OFFSET + 52,
    XCV_REG_TXPEND  = XCV_TX_OFFSET + 53,
#if JENNIC_HW_BBC_DMA
    XCV_REG_TXBUFAD = XCV_TX_OFFSET + 55,
#endif

    /* Superframe Control/Status */
    XCV_REG_SCTL    = XCV_TI_OFFSET + 17,
    XCV_REG_SCFRC   = XCV_TI_OFFSET + 9,
    XCV_REG_SCSSR   = XCV_TI_OFFSET + 10,
    XCV_REG_SCESL   = XCV_TI_OFFSET + 11,
    XCV_REG_PTTT    = XCV_TI_OFFSET + 18, /* PHY Tx tune time */
    XCV_REG_PRTT    = XCV_TI_OFFSET + 19, /* PHY Rx tune time */
#if !(JENNIC_HW_BBC_DMA)
    XCV_REG_POFT    = XCV_TI_OFFSET + 20, /* PHY Off time */
#endif
    XCV_REG_TAT     = XCV_TI_OFFSET + 21, /* Turnaround time */
    XCV_REG_BOT     = XCV_TI_OFFSET + 22, /* Backoff time */
#if !(JENNIC_HW_BBC_DMA)
    XCV_REG_CTID    = XCV_TI_OFFSET + 23, /* Cold-to-idle time */
    XCV_REG_RXNOT   = XCV_TI_OFFSET + 24, /* Latency fine tune */
    XCV_REG_RX      = XCV_TI_OFFSET + 25, /* Latency fine tune */
    XCV_REG_TXPOST  = XCV_TI_OFFSET + 26, /* Latency fine tune */
    XCV_REG_TXPRE   = XCV_TI_OFFSET + 27, /* Latency fine tune */
#endif
    XCV_REG_PRBSS   = XCV_TI_OFFSET + 28, /* PRBS seed */
    XCV_REG_SM_STATE= XCV_TI_OFFSET + 31, /* Supervisor state */
    /* Symbol Clock Match */
    XCV_REG_SCMR0   = XCV_TI_OFFSET + 0,
    XCV_REG_SCMR1   = XCV_TI_OFFSET + 1,
    XCV_REG_SCMR2   = XCV_TI_OFFSET + 2,
    XCV_REG_SCMR3   = XCV_TI_OFFSET + 3,
    /* Symbol Clock Timers */
    XCV_REG_SCTR0   = XCV_TI_OFFSET + 4,
    XCV_REG_SCTR1   = XCV_TI_OFFSET + 5,
#if !(JENNIC_HW_BBC_DMA)
    XCV_REG_SCTR2   = XCV_TI_OFFSET + 6,
    XCV_REG_SCTR3   = XCV_TI_OFFSET + 7,
#endif
    XCV_REG_SCTCR   = XCV_TI_OFFSET + 8,
    /* Interrupt */
    XCV_REG_IER     = XCV_TI_OFFSET + 15,
    XCV_REG_ISR     = XCV_TI_OFFSET + 16,
#if JENNIC_HW_BBC_DMA
    XCV_REG_MISR    = XCV_TI_OFFSET + 34,
#endif

#if JENNIC_HW_BBC_ISA
    /* Security - ISA */
    XCV_REG_ISA_ADL   = XCV_SEC_OFFSET,     /* Address low */
    XCV_REG_ISA_ADH   = XCV_SEC_OFFSET + 1, /* Address high */
    XCV_REG_ISA_FCT   = XCV_SEC_OFFSET + 2, /* Frame count */
    XCV_REG_ISA_KSC   = XCV_SEC_OFFSET + 3, /* Key sequence count/security level */
    XCV_REG_ISA_ADPTR = XCV_SEC_OFFSET + 5,
    XCV_REG_ISA_ADLEN = XCV_SEC_OFFSET + 6,
    XCV_REG_ISA_MDPTR = XCV_SEC_OFFSET + 7,
    XCV_REG_ISA_MDLEN = XCV_SEC_OFFSET + 8,
    XCV_REG_ISA_XFORM = XCV_SEC_OFFSET + 9,
    XCV_REG_ISA_RXCNT = XCV_SEC_OFFSET + 10,
    XCV_REG_ISA_FLIP  = XCV_SEC_OFFSET + 11,
#endif

    /* AES */
    XCV_REG_AES_ACLKEY        = XCV_AES_OFFSET, /* 4 words in size, 128-bit key */
    XCV_REG_AES_ACL_CMD       = XCV_AES_OFFSET + 5,
    XCV_REG_AES_DATA_IN       = XCV_AES_OFFSET + 0,
    XCV_REG_AES_DATA_OUT      = XCV_AES_OFFSET + 7,
    XCV_REG_AES_IV            = XCV_AES_OFFSET + 0,
    XCV_REG_AES_CTR           = XCV_AES_OFFSET + 0,
    XCV_REG_AES_RI_CCM_ML     = XCV_AES_OFFSET + 3,
    XCV_REG_AES_RI_CCM_ALEN_0 = XCV_AES_OFFSET + 2,
    XCV_REG_AES_RI_CCM_ALEN_1 = XCV_AES_OFFSET + 3,
    XCV_REG_AES_RI_CCM_MLEN_0 = XCV_AES_OFFSET + 2,
    XCV_REG_AES_RI_CCM_MLEN_1 = XCV_AES_OFFSET + 3,
    XCV_REG_AES_BCMODE        = XCV_AES_OFFSET + 3,
    XCV_REG_AES_RI_CCM_NONCE  = XCV_AES_OFFSET + 0,
    XCV_REG_AES_CCM_AUTH      = XCV_AES_OFFSET + 0,
    XCV_REG_AES_STATUS        = XCV_AES_OFFSET + 15,
    XCV_REG_AES_CCM_CHK_0     = XCV_AES_OFFSET + 11,
    XCV_REG_AES_CCM_CHK_1     = XCV_AES_OFFSET + 12,
    XCV_REG_AES_CCM_CHK_2     = XCV_AES_OFFSET + 13,
    XCV_REG_AES_CCM_CHK_3     = XCV_AES_OFFSET + 14,
    XCV_REG_AES_INT           = XCV_AES_OFFSET + 4,
    XCV_REG_AES_INT_EN        = XCV_AES_OFFSET + 6,

//    /* Phy */
//    XCV_REG_PHY_CTRL  = XCV_PHY_OFFSET,
//    XCV_REG_PHY_STAT  = XCV_PHY_OFFSET + 1,
//    XCV_REG_PHY_CHAN  = XCV_PHY_OFFSET + 2,
//    XCV_REG_PHY_CTRL1 = XCV_PHY_OFFSET + 3,
//    XCV_REG_PHY_CTRL2 = XCV_PHY_OFFSET + 4,
//    XCV_REG_PHY_CTRL3 = XCV_PHY_OFFSET + 5,
//    XCV_REG_PHY_CTRL4 = XCV_PHY_OFFSET + 6,
//    XCV_REG_PHY_RADTST0 = XCV_PHY_OFFSET + 7,
//    XCV_REG_PHY_RADTST1 = XCV_PHY_OFFSET + 8,
//    XCV_REG_PHY_RADTST2 = XCV_PHY_OFFSET + 9,
//    XCV_REG_PHY_MCTRL  = XCV_PHY_OFFSET + 10,
//    XCV_REG_PHY_MSTAT0 = XCV_PHY_OFFSET + 11,
//    XCV_REG_PHY_MCTRL2 = XCV_PHY_OFFSET + 12,
//    XCV_REG_PHY_MCTRL3 = XCV_PHY_OFFSET + 13,
//    XCV_REG_PHY_MCTRL4 = XCV_PHY_OFFSET + 14,
//    XCV_REG_PHY_MCTRL5 = XCV_PHY_OFFSET + 15,
//    XCV_REG_PHY_MSTAT1 = XCV_PHY_OFFSET + 16,
//    XCV_REG_PHY_MSTAT2 = XCV_PHY_OFFSET + 17,
//#ifdef CHIP_RELEASE_1
//    XCV_REG_PHY_MSTAT3 = XCV_PHY_OFFSET + 18,
//#else
//    XCV_REG_PHY_RADTST_B = XCV_PHY_OFFSET + 18,
//#endif
//    XCV_REG_PHY_IS = XCV_PHY_OFFSET + 19,
//    XCV_REG_PHY_IE = XCV_PHY_OFFSET + 20,
//    XCV_REG_PHY_CAL = XCV_PHY_OFFSET + 21,

    //XCV_REG_PHY_CTRL         = XCV_PHY_OFFSET,
    XCV_REG_PHY_STAT         = XCV_PHY_OFFSET + 1,
    //XCV_REG_PHY_CHAN         = XCV_PHY_OFFSET + 2,
    XCV_REG_PHY_PA_CTRL         = XCV_PHY_OFFSET + 3,
    //XCV_REG_PHY_VCO_AUTO_CAL = XCV_PHY_OFFSET + 4,
    //XCV_REG_PHY_VCO_CAL_CTRL = XCV_PHY_OFFSET + 5,
    //XCV_REG_PHY_VCO_CAL_STAT = XCV_PHY_OFFSET + 6,
    //XCV_REG_PHY_VCO_CHO0     = XCV_PHY_OFFSET + 7,
    //XCV_REG_PHY_VCO_CHO1     = XCV_PHY_OFFSET + 8,
    //XCV_REG_PHY_VCO_CHO2     = XCV_PHY_OFFSET + 9,
    XCV_REG_PHY_VCO_FTO        = XCV_PHY_OFFSET + 9,
    XCV_REG_PHY_VCO_TXO      = XCV_PHY_OFFSET + 10,
    //XCV_REG_PHY_VCO_RXO      = XCV_PHY_OFFSET + 11,
    XCV_REG_PHY_MCTRL         = XCV_PHY_OFFSET + 12,
    XCV_REG_PHY_MSTAT         = XCV_PHY_OFFSET + 13,
    XCV_REG_PHY_MCCA          = XCV_PHY_OFFSET + 14,
    //XCV_REG_PHY_MRX_CTRL     = XCV_PHY_OFFSET + 15,
    //XCV_REG_PHY_MTX_CTRL     = XCV_PHY_OFFSET + 16,
    //XCV_REG_PHY_MTX_TST_SEQ  = XCV_PHY_OFFSET + 17,
    //XCV_REG_PHY_MRST_STAT    = XCV_PHY_OFFSET + 18,
    XCV_REG_PHY_IS           = XCV_PHY_OFFSET + 19,
    XCV_REG_PHY_IE           = XCV_PHY_OFFSET + 20,
    //XCV_REG_PHY_RC_CAL       = XCV_PHY_OFFSET + 21,
    //XCV_REG_PHY_RC_CAL0      = XCV_PHY_OFFSET + 22,
    //XCV_REG_PHY_LOCK_DET     = XCV_PHY_OFFSET + 23,
    //XCV_REG_PHY_SYNTH_CTRL   = XCV_PHY_OFFSET + 24,
    XCV_REG_PHY_TST_SIG_CTRL   = XCV_PHY_OFFSET + 26,
    XCV_REG_PHY_TST0         = XCV_PHY_OFFSET + 28,
#if JENNIC_HW_BBC_DMA
    XCV_REG_PHY_MISR          = XCV_PHY_OFFSET + 18,
#endif
#if (defined JENNIC_CHIP_FAMILY_JN516x)
    XCV_REG_PHY_AD_EN          = XCV_PHY_OFFSET + 32,
    XCV_REG_PHY_AD_STAT        = XCV_PHY_OFFSET + 33,
    XCV_REG_PHY_AD_CTRL        = XCV_PHY_OFFSET + 34,
#endif
    /* System controller */
    XCV_REG_SYS_PWR_CTRL = XCV_SYS_OFFSET,
    XCV_REG_SYS_STAT     = XCV_SYS_OFFSET + 1,
    XCV_REG_SYS_WK_ET    = XCV_SYS_OFFSET + 2,
    XCV_REG_SYS_WK_EM    = XCV_SYS_OFFSET + 3,
    XCV_REG_SYS_WK_ES    = XCV_SYS_OFFSET + 4,
    XCV_REG_SYS_WK_T0    = XCV_SYS_OFFSET + 5,
    XCV_REG_SYS_WK_T1    = XCV_SYS_OFFSET + 6,
    XCV_REG_SYS_WK_TC    = XCV_SYS_OFFSET + 7,
    XCV_REG_SYS_WK_TS    = XCV_SYS_OFFSET + 8,
    XCV_REG_SYS_WK_CC    = XCV_SYS_OFFSET + 9,
    XCV_REG_SYS_WK_CRC   = XCV_SYS_OFFSET + 10,
    XCV_REG_SYS_CPU_CTRL = XCV_SYS_OFFSET + 11,
    XCV_REG_SYS_WK_T0_MSB= XCV_SYS_OFFSET + 12,
    XCV_REG_SYS_WK_T1_MSB= XCV_SYS_OFFSET + 13,
    XCV_REG_SYS_GEN_CTRL     = XCV_SYS_OFFSET + 14,
    XCV_REG_SYS_PULLUP       = XCV_SYS_OFFSET + 15,
    XCV_REG_SYS_PWR_CTRL2    = XCV_SYS_OFFSET + 16,
    XCV_REG_SYS_VBOCTRL      = XCV_SYS_OFFSET + 17,
    XCV_REG_SYS_SYSCTRL_TEST = XCV_SYS_OFFSET + 18,
    XCV_REG_SYS_RSTCTRL      = XCV_SYS_OFFSET + 19,
    XCV_REG_SYS_TIM_IO_CTRL  = XCV_SYS_OFFSET + 55,
    XCV_REG_SYS_CHIP_ID      = XCV_SYS_OFFSET + 63,

    /* GPIO */
    XCV_REG_GPIO_DIR  = XCV_GPIO_OFFSET,
    XCV_REG_GPIO_DOUT = XCV_GPIO_OFFSET + 1,
    XCV_REG_GPIO_DIN  = XCV_GPIO_OFFSET + 2,

    /* UART: Repeated for each one */
    XCV_REG_UART0_DATA = XCV_UART0_OFFSET,
    XCV_REG_UART0_IER  = XCV_UART0_OFFSET + 1,
    XCV_REG_UART0_IIR  = XCV_UART0_OFFSET + 2, /* Read only */
    XCV_REG_UART0_FCR  = XCV_UART0_OFFSET + 2, /* Write only */
    XCV_REG_UART0_LCR  = XCV_UART0_OFFSET + 3,
    XCV_REG_UART0_MCR  = XCV_UART0_OFFSET + 4,
    XCV_REG_UART0_LSR  = XCV_UART0_OFFSET + 5,
    XCV_REG_UART0_MSR  = XCV_UART0_OFFSET + 6,
    XCV_REG_UART0_SCR  = XCV_UART0_OFFSET + 7,
    XCV_REG_UART0_EFR  = XCV_UART0_OFFSET + 8,
    XCV_REG_UART0_TFC  = XCV_UART0_OFFSET + 9,
    XCV_REG_UART0_RFC  = XCV_UART0_OFFSET + 10,
    XCV_REG_UART0_AFC  = XCV_UART0_OFFSET + 11,
    XCV_REG_UART0_FC   = XCV_UART0_OFFSET + 12,
    XCV_REG_UART0_TFA  = XCV_UART0_OFFSET + 13,
    XCV_REG_UART0_RFA  = XCV_UART0_OFFSET + 14,
    XCV_REG_UART0_TFL  = XCV_UART0_OFFSET + 15,
    XCV_REG_UART0_RFL  = XCV_UART0_OFFSET + 16,
    XCV_REG_UART1_DATA = XCV_UART1_OFFSET,
    XCV_REG_UART1_IER  = XCV_UART1_OFFSET + 1,
    XCV_REG_UART1_IIR  = XCV_UART1_OFFSET + 2, /* Read only */
    XCV_REG_UART1_FCR  = XCV_UART1_OFFSET + 2, /* Write only */
    XCV_REG_UART1_LCR  = XCV_UART1_OFFSET + 3,
    XCV_REG_UART1_MCR  = XCV_UART1_OFFSET + 4,
    XCV_REG_UART1_LSR  = XCV_UART1_OFFSET + 5,
    XCV_REG_UART1_MSR  = XCV_UART1_OFFSET + 6,
    XCV_REG_UART1_SCR  = XCV_UART1_OFFSET + 7,
    XCV_REG_UART1_EFR  = XCV_UART1_OFFSET + 8,
    XCV_REG_UART1_TFC  = XCV_UART1_OFFSET + 9,
    XCV_REG_UART1_RFC  = XCV_UART1_OFFSET + 10,
    XCV_REG_UART1_AFC  = XCV_UART1_OFFSET + 11,
    XCV_REG_UART1_FC   = XCV_UART1_OFFSET + 12,
    XCV_REG_UART1_TFA  = XCV_UART1_OFFSET + 13,
    XCV_REG_UART1_RFA  = XCV_UART1_OFFSET + 14,
    XCV_REG_UART1_TFL  = XCV_UART1_OFFSET + 15,
    XCV_REG_UART1_RFL  = XCV_UART1_OFFSET + 16,
    /* Timer: Repeated for each one. Timer 2 is not in next release so ignore it */
    XCV_REG_TMR0_CTR   = XCV_TMR0_OFFSET,
    XCV_REG_TMR0_HI    = XCV_TMR0_OFFSET + 1,
    XCV_REG_TMR0_LO    = XCV_TMR0_OFFSET + 2,
    XCV_REG_TMR0_CTRL  = XCV_TMR0_OFFSET + 3,
    XCV_REG_TMR0_PRESC = XCV_TMR0_OFFSET + 4,
    XCV_REG_TMR0_INT   = XCV_TMR0_OFFSET + 5,
    XCV_REG_TMR0_INTE  = XCV_TMR0_OFFSET + 6,

    XCV_REG_TMR1_CTR   = XCV_TMR1_OFFSET,
    XCV_REG_TMR1_HI    = XCV_TMR1_OFFSET + 1,
    XCV_REG_TMR1_LO    = XCV_TMR1_OFFSET + 2,
    XCV_REG_TMR1_CTRL  = XCV_TMR1_OFFSET + 3,
    XCV_REG_TMR1_PRESC = XCV_TMR1_OFFSET + 4,
    XCV_REG_TMR1_INT   = XCV_TMR1_OFFSET + 5,
    XCV_REG_TMR1_INTE  = XCV_TMR1_OFFSET + 6,

    /* Serial Interface MASTER (2 wire) */
    XCV_REG_SIM_CLK_PS  = XCV_I2C_M_OFFSET,
    XCV_REG_SIM_CTRL    = XCV_I2C_M_OFFSET + 2,
    XCV_REG_SIM_TX      = XCV_I2C_M_OFFSET + 3,
    XCV_REG_SIM_RX      = XCV_I2C_M_OFFSET + 3,
    XCV_REG_SIM_CMD     = XCV_I2C_M_OFFSET + 4,
    XCV_REG_SIM_STAT    = XCV_I2C_M_OFFSET + 4,

    /* Serial Interface SLAVE (2 wire) */
    XCV_REG_SIS_DATA     = XCV_I2C_S_OFFSET,
    XCV_REG_SIS_INT_STAT = XCV_I2C_S_OFFSET + 1,
    XCV_REG_SIS_INT_EN   = XCV_I2C_S_OFFSET + 2,
    XCV_REG_SIS_CTRL     = XCV_I2C_S_OFFSET + 3,
    XCV_REG_SIS_MINT	 = XCV_I2C_S_OFFSET + 4,
#ifdef JENNIC_CHIP_JN5169	
    /* Serial Interface SLAVE extension registers */
    XCV_REG_SIS_SLAVE_ADDR2 = XCV_I2C_S_OFFSET + 5,
    XCV_REG_SIS_ADDR_MASK   = XCV_I2C_S_OFFSET + 6,
    XCV_REG_SIS_ADDR_STATUS = XCV_I2C_S_OFFSET + 7,
	XCV_REG_SIS_SLAVE_BUSY  = XCV_I2C_M_OFFSET + 8,
#endif

    /* SPI master */
    XCV_REG_SPIM_BUF  = XCV_SPIM_OFFSET,
    XCV_REG_SPIM_CTRL = XCV_SPIM_OFFSET + 1,
    XCV_REG_SPIM_DIV  = XCV_SPIM_OFFSET + 2,
    XCV_REG_SPIM_SS   = XCV_SPIM_OFFSET + 3,
    XCV_REG_SPIM_IE   = XCV_SPIM_OFFSET + 4,
    XCV_REG_SPIM_IS   = XCV_SPIM_OFFSET + 5,

    /* SPI-IP */
    XCV_REG_INTPER_RXADDR = XCV_INTPER_OFFSET,
    XCV_REG_INTPER_TXADDR = XCV_INTPER_OFFSET + 1,
    XCV_REG_INTPER_RXLEN  = XCV_INTPER_OFFSET + 2,
    XCV_REG_INTPER_TXLEN  = XCV_INTPER_OFFSET + 3,
    XCV_REG_INTPER_CTRL   = XCV_INTPER_OFFSET + 4,

    XCV_REG_INTPER_LOBLK  = XCV_INTPER_MEM_OFFSET,
    XCV_REG_INTPER_HIBLK  = XCV_INTPER_MEM_OFFSET + 64,

    /* Analogue peripherals */
    XCV_REG_ANPER_CTRL = XCV_ANPER_OFFSET,
    XCV_REG_ANPER_VAL  = XCV_ANPER_OFFSET + 1,
    XCV_REG_ANPER_DAC1 = XCV_ANPER_OFFSET + 2,
    XCV_REG_ANPER_DAC2 = XCV_ANPER_OFFSET + 3,
    XCV_REG_ANPER_CAPT = XCV_ANPER_OFFSET + 4,
    XCV_REG_ANPER_IS   = XCV_ANPER_OFFSET + 5,
    XCV_REG_ANPER_IE   = XCV_ANPER_OFFSET + 6,
    XCV_REG_ANPER_TEST      = XCV_ANPER_OFFSET + 7,
    XCV_REG_ANPER_COMPCTRL  = XCV_ANPER_OFFSET + 8,
    XCV_REG_ANPER_AVCTRL    = XCV_ANPER_OFFSET + 9,
    XCV_REG_ANPER_AVVAL     = XCV_ANPER_OFFSET + 10,

    XCV_REG_ANPER_DMA_CTRL = XCV_ANPER_OFFSET + 11,
    XCV_REG_ANPER_DMA_ADDR = XCV_ANPER_OFFSET + 12,
    XCV_REG_ANPER_DMA_LEN = XCV_ANPER_OFFSET + 13,
    XCV_REG_ANPER_DMA_COUNT = XCV_ANPER_OFFSET + 14,
    XCV_REG_ANPER_DMA_SRC = XCV_ANPER_OFFSET + 15,
    XCV_REG_ANPER_TT = XCV_ANPER_OFFSET + 16,
    XCV_REG_ANPER_MIS = XCV_ANPER_OFFSET + 17,

    NUM_XCV_REG,

    XCV_REG_EXTADDRL = XCV_EXT_OFFSET, /* These will be memory locations, not baseband registers */
    XCV_REG_EXTADDRH = XCV_EXT_OFFSET + 1  /* These are placeholder values for integration testing   */

} XCV_Reg_e;

/**
 * Enumeration of interrupts as events
 * @ingroup grp_XCV
 */
typedef enum
{
    XCV_EVT_BBC_TX_FINISHED,
#if JENNIC_HW_BBC_DMA
    XCV_EVT_BBC_RX_HEADER,
    XCV_EVT_BBC_RX_FINISHED,
#else
    XCV_EVT_BBC_RX_FINISHED,
    XCV_EVT_BBC_RX_HEADER,
#endif
    XCV_EVT_BBC_UNASSIGNED_0,
    XCV_EVT_BBC_SCMR0_EXPIRED,
    XCV_EVT_BBC_SCMR1_EXPIRED,
    XCV_EVT_BBC_SCMR2_EXPIRED,
    XCV_EVT_BBC_SCMR3_EXPIRED,
    XCV_EVT_BBC_SCTR0_EXPIRED,
    XCV_EVT_BBC_SCTR1_EXPIRED,
#if !(JENNIC_HW_BBC_DMA)
    XCV_EVT_BBC_SCTR2_EXPIRED,
    XCV_EVT_BBC_SCTR3_EXPIRED,
#endif
    NUM_XCV_BBC_EVT
} XCV_BbcEvt_e;

/**
 * Enumeration of PHY interrupts as events
 * @ingroup grp_XCV
 */
typedef enum
{
    XCV_EVT_PHY_CAL,
    XCV_EVT_PHY_PHYRDY,
    XCV_EVT_PHY_ED,
    XCV_EVT_PHY_CCA,
    XCV_EVT_PHY_CHAN, /* Channel changed - This is not a interrupt signalled event */
    XCV_EVT_PHY_RMI, /* Request modem interface done - This is not a interrupt signalled event */
    NUM_XCV_PHY_EVT
} XCV_PhyEvt_e;

#define NUM_XCV_PHY_ISR_EVT (XCV_EVT_PHY_CCA + 1)

/****************************/
/**** EXPORTED VARIABLES ****/
/****************************/

/****************************/
/**** EXPORTED FUNCTIONS ****/
/****************************/

#ifdef __cplusplus
};
#endif

#endif /* _xcv_reg_h_ */

/* End of file $RCSfile: xcv_reg.h,v $ *******************************************/
