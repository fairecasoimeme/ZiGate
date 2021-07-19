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

#ifndef  AHI_H_INCLUDED
#define  AHI_H_INCLUDED

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

/* System Controller RND Generator */
#define E_AHI_RND_SINGLE_SHOT           (TRUE)
#define E_AHI_RND_CONTINUOUS            (FALSE)
#define E_AHI_INTS_ENABLED              (TRUE)
#define E_AHI_INTS_DISABLED             (FALSE)

/* System Controller CPU clock control */
#define E_AHI_XTAL_OFF                  (TRUE)
#define E_AHI_XTAL_ON                   (FALSE)
#define E_AHI_XTAL_1MHZ                 (0x06)
#define E_AHI_XTAL_2MHZ                 (0x07)
#define E_AHI_XTAL_4MHZ                 (0x00)
#define E_AHI_XTAL_8MHZ                 (0x01)
#define E_AHI_XTAL_16MHZ                (0x02)
#define E_AHI_XTAL_32MHZ                (0x03)

/* System Controller crystal clock adjustment (use with vAHI_ClockXtalPull) */
#define E_AHI_XTAL_PULL_NONE            (0U)
#define E_AHI_XTAL_PULL_50PC            (1U)
#define E_AHI_XTAL_PULL_100PC           (3U)

/* System Controller 32Khz Clock Mode Control */
#define E_AHI_INTERNAL_RC               (0)
#define E_AHI_EXTERNAL_RC               (1)
#define E_AHI_XTAL                      (2)

/* Device enumerations */
#define E_AHI_WAKE_TIMER_0              (0)
#define E_AHI_WAKE_TIMER_1              (1)
#define E_AHI_AP_COMPARATOR_1           (0)
#define E_AHI_UART_0                    (0)
#define E_AHI_UART_1                    (1)
#define E_AHI_TIMER_0                   (0)
#define E_AHI_TIMER_1                   (1)
#define E_AHI_TIMER_2                   (2)
#define E_AHI_TIMER_3                   (3)
#define E_AHI_TIMER_4                   (4)

/* New style PWM timer enumerations */
#define E_PWM_TIMER1                    (1)
#define E_PWM_TIMER2                    (2)
#define E_PWM_TIMER3                    (3)
#define E_PWM_TIMER4                    (4)

/* Value enumerations: Pulse Counters */
#define E_AHI_PC_0                      (0)
#define E_AHI_PC_1                      (1)
#define E_AHI_PC_COMBINE_OFF            (0)
#define E_AHI_PC_COMBINE_ON0            (1)
#define E_AHI_PC_COMBINE_ON1            (2)

/* Value enumerations: VBO */
#define E_AHI_VBOREF_1V95               (0)
#define E_AHI_VBOREF_2V0                (1)
#define E_AHI_VBOREF_2V1                (2)
#define E_AHI_VBOREF_2V2                (3)
#define E_AHI_VBOREF_2V3                (4)
#define E_AHI_VBOREF_2V4                (5)
#define E_AHI_VBOREF_2V7                (6)
#define E_AHI_VBOREF_3V0                (7)

/* Value enumerations: Phy Controller (RF Power Settings) */
#define E_AHI_ZERO_dB                   (3)
#define E_AHI_MINUS_12_dB               (2)
#define E_AHI_MINUS_24_dB               (1)
#define E_AHI_MINUS_32_dB               (0)

/* Value enumerations: Wake Timer */
#define E_AHI_WAKE_TIMER_MASK_0         (1)
#define E_AHI_WAKE_TIMER_MASK_1         (2)

/* Value enumerations: Analogue Peripherals */
#define E_AHI_ADC_SRC_ADC_1             0
#define E_AHI_ADC_SRC_ADC_2             1
#define E_AHI_ADC_SRC_VREF              1
#define E_AHI_ADC_SRC_ADC_3             2
#define E_AHI_ADC_SRC_DIO0              2
#define E_AHI_ADC_SRC_ADC_4             3
#define E_AHI_ADC_SRC_DIO1              3
#define E_AHI_ADC_SRC_TEMP              4
#define E_AHI_ADC_SRC_VOLT              5
#define E_AHI_ADC_SRC_TEST_MODE0        6
#define E_AHI_ADC_SRC_TEST_MODE1        7

#define E_AHI_ADC_DMA_SRC_VOLT_MASK       (1 << E_AHI_ADC_SRC_VOLT)
#define E_AHI_ADC_DMA_SRC_TEMP_MASK       (1 << E_AHI_ADC_SRC_TEMP)
#define E_AHI_ADC_DMA_SRC_ADC_4_MASK      (1 << E_AHI_ADC_SRC_ADC_4)
#define E_AHI_ADC_DMA_SRC_ADC_3_MASK      (1 << E_AHI_ADC_SRC_ADC_3)
#define E_AHI_ADC_DMA_SRC_ADC_2_MASK      (1 << E_AHI_ADC_SRC_ADC_2)
#define E_AHI_ADC_DMA_SRC_ADC_1_MASK      (1 << E_AHI_ADC_SRC_ADC_1)
#define E_AHI_ADC_DMA_SRC_TEST_MODE0_MASK (1 << E_AHI_ADC_SRC_TEST_MODE0)
#define E_AHI_ADC_DMA_SRC_TEST_MODE1_MASK (1 << E_AHI_ADC_SRC_TEST_MODE1)

#define E_AHI_AP_REGULATOR_ENABLE       (TRUE)
#define E_AHI_AP_REGULATOR_DISABLE      (FALSE)
#define E_AHI_AP_SAMPLE_2               (0)
#define E_AHI_AP_SAMPLE_4               (1)
#define E_AHI_AP_SAMPLE_6               (2)
#define E_AHI_AP_SAMPLE_8               (3)
#define E_AHI_AP_CLOCKDIV_2MHZ          (0)
#define E_AHI_AP_CLOCKDIV_1MHZ          (1)
#define E_AHI_AP_CLOCKDIV_500KHZ        (2)
#define E_AHI_AP_CLOCKDIV_250KHZ        (3)
#define E_AHI_AP_INPUT_RANGE_2          (TRUE)
#define E_AHI_AP_INPUT_RANGE_1          (FALSE)
#define E_AHI_AP_GAIN_2                 (TRUE)
#define E_AHI_AP_GAIN_1                 (FALSE)
#define E_AHI_AP_EXTREF                 (TRUE)
#define E_AHI_AP_INTREF                 (FALSE)
#define E_AHI_ADC_CONVERT_ENABLE        (TRUE)
#define E_AHI_ADC_CONVERT_DISABLE       (FALSE)
#define E_AHI_ADC_CONTINUOUS            (TRUE)
#define E_AHI_ADC_SINGLE_SHOT           (FALSE)
#define E_AHI_AP_CAPT_INT_STATUS_MASK   (0x01)
#define E_AHI_AP_ACC_INT_STATUS_MASK    (0x2)
#define E_AHI_ADC_ACC_SAMPLE_2          (0x00)
#define E_AHI_ADC_ACC_SAMPLE_4          (0x01)
#define E_AHI_ADC_ACC_SAMPLE_8          (0x02)
#define E_AHI_ADC_ACC_SAMPLE_16         (0x03)
#define E_AHI_AP_ADCACC_INT_ENABLE      (0x2U)
#define E_AHI_AP_CAPT_INT_ENABLE        (0x1U)
#define E_AHI_AP_INT_ENABLE             (TRUE)
#define E_AHI_AP_INT_DISABLE            (FALSE)
#define E_AHI_AP_BANDGAP_ENABLE         (TRUE)
#define E_AHI_AP_BANDGAP_DISABLE        (FALSE)
#define E_AHI_AP_SLOW_CONVERSIONS_ENABLE  (TRUE)
#define E_AHI_AP_SLOW_CONVERSIONS_DISABLE (FALSE)

/* Value enumerations: Comparator */
#define E_AHI_COMP_HYSTERESIS_0MV       (0)
#define E_AHI_COMP_HYSTERESIS_10MV      (1)
#define E_AHI_COMP_HYSTERESIS_20MV      (2)
#define E_AHI_COMP_HYSTERESIS_40MV      (3)
#define E_AHI_AP_COMPARATOR_MASK_1      (1)

#define E_AHI_COMP_SEL_EXT              (0x00)
#define E_AHI_COMP_SEL_BANDGAP          (0x02)
#define E_AHI_COMP_SEL_EXT_INVERSE      (0x81)
#define E_AHI_COMP_SEL_BANDGAP_INVERSE  (0x82)

/* Value enumerations: UART */
#define E_AHI_UART_RATE_4800            (0)
#define E_AHI_UART_RATE_9600            (1)
#define E_AHI_UART_RATE_19200           (2)
#define E_AHI_UART_RATE_38400           (3)
#define E_AHI_UART_RATE_76800           (4)
#define E_AHI_UART_RATE_115200          (5)
#define E_AHI_UART_WORD_LEN_5           (0)
#define E_AHI_UART_WORD_LEN_6           (1)
#define E_AHI_UART_WORD_LEN_7           (2)
#define E_AHI_UART_WORD_LEN_8           (3)
#define E_AHI_UART_FIFO_LEVEL_1         (0)
#define E_AHI_UART_FIFO_LEVEL_4         (1)
#define E_AHI_UART_FIFO_LEVEL_8         (2)
#define E_AHI_UART_FIFO_LEVEL_14        (3)
#define E_AHI_UART_LS_ERROR             (0x80)
#define E_AHI_UART_LS_TEMT              (0x40)
#define E_AHI_UART_LS_THRE              (0x20)
#define E_AHI_UART_LS_BI                (0x10)
#define E_AHI_UART_LS_FE                (0x08)
#define E_AHI_UART_LS_PE                (0x04)
#define E_AHI_UART_LS_OE                (0x02)
#define E_AHI_UART_LS_DR                (0x01)
#define E_AHI_UART_MS_CTS               (0x10)
#define E_AHI_UART_MS_DCTS              (0x01)
#define E_AHI_UART_INT_MODEM            (0)
#define E_AHI_UART_INT_TX               (1)
#define E_AHI_UART_INT_RXDATA           (2)
#define E_AHI_UART_INT_RXLINE           (3)
#define E_AHI_UART_INT_TIMEOUT          (6)
#define E_AHI_UART_TX_RESET             (TRUE)
#define E_AHI_UART_RX_RESET             (TRUE)
#define E_AHI_UART_TX_ENABLE            (FALSE)
#define E_AHI_UART_RX_ENABLE            (FALSE)
#define E_AHI_UART_EVEN_PARITY          (TRUE)
#define E_AHI_UART_ODD_PARITY           (FALSE)
#define E_AHI_UART_PARITY_ENABLE        (TRUE)
#define E_AHI_UART_PARITY_DISABLE       (FALSE)
#define E_AHI_UART_1_STOP_BIT           (TRUE)
#define E_AHI_UART_2_STOP_BITS          (FALSE)
#define E_AHI_UART_RTS_HIGH             (TRUE)
#define E_AHI_UART_RTS_LOW              (FALSE)
#define E_AHI_UART_FIFO_ARTS_LEVEL_8    (0)
#define E_AHI_UART_FIFO_ARTS_LEVEL_11   (1)
#define E_AHI_UART_FIFO_ARTS_LEVEL_13   (2)
#define E_AHI_UART_FIFO_ARTS_LEVEL_15   (3)

/* Value enumerations: SPI Master */
#define E_AHI_SPIM_MSB_FIRST            (FALSE)
#define E_AHI_SPIM_LSB_FIRST            (TRUE)
#define E_AHI_SPIM_TXPOS_EDGE           (FALSE)
#define E_AHI_SPIM_TXNEG_EDGE           (TRUE)
#define E_AHI_SPIM_RXPOS_EDGE           (FALSE)
#define E_AHI_SPIM_RXNEG_EDGE           (TRUE)
#define E_AHI_SPIM_INT_ENABLE           (TRUE)
#define E_AHI_SPIM_INT_DISABLE          (FALSE)
#define E_AHI_SPIM_AUTOSLAVE_ENBL       (TRUE)
#define E_AHI_SPIM_AUTOSLAVE_DSABL      (FALSE)
#define E_AHI_SPIM_SLAVE_ENBLE_0        (0x1)
#define E_AHI_SPIM_SLAVE_ENBLE_1        (0x2)
#define E_AHI_SPIM_SLAVE_ENBLE_2        (0x4)
#define E_AHI_SPIM_SLAVE_ENBLE_3        (0x8)
#define E_AHI_SPISEL_1                  (1)
#define E_AHI_SPISEL_2                  (2)

/* Value enumerations: Serial Interface */
#define E_AHI_SI_INT_AL            0x20
#define E_AHI_SI_SLAVE_RW_SET      FALSE
#define E_AHI_SI_START_BIT         TRUE
#define E_AHI_SI_NO_START_BIT      FALSE
#define E_AHI_SI_STOP_BIT          TRUE
#define E_AHI_SI_NO_STOP_BIT       FALSE
#define E_AHI_SI_SLAVE_READ        TRUE
#define E_AHI_SI_NO_SLAVE_READ     FALSE
#define E_AHI_SI_SLAVE_WRITE       TRUE
#define E_AHI_SI_NO_SLAVE_WRITE    FALSE
#define E_AHI_SI_SEND_ACK          FALSE
#define E_AHI_SI_SEND_NACK         TRUE
#define E_AHI_SI_IRQ_ACK           TRUE
#define E_AHI_SI_NO_IRQ_ACK        FALSE

/* Value enumerations: Intelligent Peripheral */
#define E_AHI_IP_MAX_MSG_SIZE           (0x3E)
#define E_AHI_IP_TXPOS_EDGE             (FALSE)
#define E_AHI_IP_TXNEG_EDGE             (TRUE)
#define E_AHI_IP_RXPOS_EDGE             (FALSE)
#define E_AHI_IP_RXNEG_EDGE             (TRUE)
#define E_AHI_IP_BIG_ENDIAN             (TRUE)
#define E_AHI_IP_LITTLE_ENDIAN          (FALSE)

/* Value enumerations: Timer */
#define E_AHI_TIMER_INT_PERIOD            (1)
#define E_AHI_TIMER_INT_RISE              (2)
#define E_AHI_TIMER_PRESCALE_16MHZ        (0)  /* 16MHz */
#define E_AHI_TIMER_PRESCALE_8MHZ         (1)  /* 8MHz */
#define E_AHI_TIMER_PRESCALE_4MHZ         (2)  /* 4MHz */
#define E_AHI_TIMER_PRESCALE_2MHZ         (3)  /* 2MHz */
#define E_AHI_TIMER_PRESCALE_1MHZ         (4)  /* 1MHz */
#define E_AHI_TIMER_PRESCALE_500KHZ       (5)  /* 500kHz */
#define E_AHI_TIMER_PRESCALE_250KHZ       (6)  /* 250kHz */
#define E_AHI_TIMER_PRESCALE_125KHZ       (7)  /* 125kHz */
#define E_AHI_TIMER_PRESCALE_62500HZ      (8)  /* 62500Hz */
#define E_AHI_TIMER_PRESCALE_31250HZ      (9)  /* 31250Hz */
#define E_AHI_TIMER_PRESCALE_15625HZ      (10) /* 15625Hz */
#define E_AHI_TIMER_PRESCALE_7812HZ5      (11) /* 7812.5Hz */
#define E_AHI_TIMER_PRESCALE_3906HZ25     (12) /* 3906.25Hz */
#define E_AHI_TIMER_PRESCALE_1953HZ125    (13) /* 1953.125Hz */
#define E_AHI_TIMER_PRESCALE_976HZ5625    (14) /* 976.5625Hz */
#define E_AHI_TIMER_PRESCALE_488HZ28125   (15) /* 488.28125Hz */
#define E_AHI_TIMER_PRESCALE_244HZ140625  (16) /* 244.140625Hz */

/* Value enumerations: Tick Timer */
#define E_AHI_TICK_TIMER_DISABLE        (0x00) /* Disable tick timer */
#define E_AHI_TICK_TIMER_RESTART        (0x01) /* Restart timer when match occurs */
#define E_AHI_TICK_TIMER_STOP           (0x02) /* Stop timer when match occurs */
#define E_AHI_TICK_TIMER_CONT           (0x03) /* Timer does not stop when match occurs */

/* Value enumerations: DIO */
#define E_AHI_DIO0_INT                  (0x00000001)
#define E_AHI_DIO1_INT                  (0x00000002)
#define E_AHI_DIO2_INT                  (0x00000004)
#define E_AHI_DIO3_INT                  (0x00000008)
#define E_AHI_DIO4_INT                  (0x00000010)
#define E_AHI_DIO5_INT                  (0x00000020)
#define E_AHI_DIO6_INT                  (0x00000040)
#define E_AHI_DIO7_INT                  (0x00000080)
#define E_AHI_DIO8_INT                  (0x00000100)
#define E_AHI_DIO9_INT                  (0x00000200)
#define E_AHI_DIO10_INT                 (0x00000400)
#define E_AHI_DIO11_INT                 (0x00000800)
#define E_AHI_DIO12_INT                 (0x00001000)
#define E_AHI_DIO13_INT                 (0x00002000)
#define E_AHI_DIO14_INT                 (0x00004000)
#define E_AHI_DIO15_INT                 (0x00008000)
#define E_AHI_DIO16_INT                 (0x00010000)
#define E_AHI_DIO17_INT                 (0x00020000)
#define E_AHI_DIO18_INT                 (0x00040000)
#define E_AHI_DIO19_INT                 (0x00080000)

/* Interrupt and Status Item Bitmap Masks */
    /* System Control */
#define E_AHI_SYSCTRL_CKEM_MASK         (1 << E_AHI_SYSCTRL_CKES)
#define E_AHI_SYSCTRL_RNDEM_MASK        (1 << E_AHI_SYSCTRL_RNDES)
#define E_AHI_SYSCTRL_FEC_MASK          (1 << E_AHI_SYSCTRL_FEC)
#define E_AHI_SYSCTRL_COMP0_MASK        (1 << E_AHI_SYSCTRL_COMP0)
#define E_AHI_SYSCTRL_WK1_MASK          (1 << E_AHI_SYSCTRL_WK1)
#define E_AHI_SYSCTRL_WK0_MASK          (1 << E_AHI_SYSCTRL_WK0)
#define E_AHI_SYSCTRL_VREM_MASK         (1 << E_AHI_SYSCTRL_VRES)
#define E_AHI_SYSCTRL_VFEM_MASK         (1 << E_AHI_SYSCTRL_VFES)
#define E_AHI_SYSCTRL_PC1_MASK          (1 << E_AHI_SYSCTRL_PC1)
#define E_AHI_SYSCTRL_PC0_MASK          (1 << E_AHI_SYSCTRL_PC0)
    /* UART */
#define E_AHI_UART_TIMEOUT_MASK         (1 << E_AHI_UART_INT_TIMEOUT)
#define E_AHI_UART_RXLINE_MASK          (1 << E_AHI_UART_INT_RXLINE)
#define E_AHI_UART_RXDATA_MASK          (1 << E_AHI_UART_INT_RXDATA)
#define E_AHI_UART_TX_MASK              (1 << E_AHI_UART_INT_TX)
#define E_AHI_UART_MODEM_MASK           (1 << E_AHI_UART_INT_MODEM)
    /* Timer */
#define E_AHI_TIMER_RISE_MASK           E_AHI_TIMER_INT_RISE
#define E_AHI_TIMER_PERIOD_MASK         E_AHI_TIMER_INT_PERIOD
    /* Serial Interface Master */
#define E_AHI_SIM_RXACK_MASK            (1 << 7)
#define E_AHI_SIM_BUSY_MASK             (1 << 6)
#define E_AHI_SIM_AL_MASK               (1 << 5)
#define E_AHI_SIM_ICMD_MASK             (1 << 2)
#define E_AHI_SIM_TIP_MASK              (1 << 1)
#define E_AHI_SIM_INT_STATUS_MASK       (1 << 0)
    /* Serial Interface Slave */
#define E_AHI_SIS_ERROR_MASK            (1 << 4)
#define E_AHI_SIS_LAST_DATA_MASK        (1 << 3)
#define E_AHI_SIS_DATA_WA_MASK          (1 << 2)
#define E_AHI_SIS_DATA_RTKN_MASK        (1 << 1)
#define E_AHI_SIS_DATA_RR_MASK          (1 << 0)
    /* SPI Master */
#define E_AHI_SPIM_TX_MASK              (1 << 0)
    /* SPI Slave */
#define E_AHI_SPIS_STAT_TX_ABOVE_MASK   (1 << 3)
#define E_AHI_SPIS_STAT_RX_ABOVE_MASK   (1 << 2)
#define E_AHI_SPIS_STAT_TX_PENDING_MASK (1 << 1)
#define E_AHI_SPIS_STAT_RX_AVAIL_MASK   (1 << 0)
#define E_AHI_SPIS_INT_RX_TIMEOUT_MASK  (1 << 8)
#define E_AHI_SPIS_INT_TX_UNDER_MASK    (1 << 7)
#define E_AHI_SPIS_INT_RX_UNDER_MASK    (1 << 6)
#define E_AHI_SPIS_INT_TX_OVER_MASK     (1 << 5)
#define E_AHI_SPIS_INT_RX_OVER_MASK     (1 << 4)
#define E_AHI_SPIS_INT_TX_FALL_MASK     (1 << 3)
#define E_AHI_SPIS_INT_RX_CLIMB_MASK    (1 << 2)
#define E_AHI_SPIS_INT_TX_LAST_MASK     (1 << 1)
#define E_AHI_SPIS_INT_RX_FIRST_MASK    (1 << 0)
    /* Analogue Peripherals */
#define E_AHI_AP_INT_DMA_OVER_MASK      (1 << 4)
#define E_AHI_AP_INT_DMA_END_MASK       (1 << 3)
#define E_AHI_AP_INT_DMA_MID_MASK       (1 << 2)
#define E_AHI_AP_INT_ADCACC_MASK        (1 << 1)
#define E_AHI_AP_INT_CAPT_MASK          (1 << 0)
    /* Infrared Remote Control Transmitter */
#define E_AHI_INFRARED_TX_MASK          (1 << 0)
    /* Antenna Diversity */
#define E_AHI_ANTDIV_STAT_ANT_MASK      (1 << 2)
#define E_AHI_ANTDIV_STAT_RX_MASK       (1 << 1)
#define E_AHI_ANTDIV_STAT_TX_MASK       (1 << 0)

/* Version number of module */
/*****************************************************************
[31:24] = Family : 4 (JN516x) / 3 (JN514x) / 0 (JN513x)
[23:16] = Part : 8 (JN5168) / 5 (JN5142) / 4 (JN5148) / 1 (JN5139)
[15: 0] = AHI Version (increment for each new release/patch)
******************************************************************/

#define AHI_VERSION                0x04080000

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

#ifndef AHI_DEVICE_ENUM
#define AHI_DEVICE_ENUM

/* Device types, used to identify interrupt source */
typedef enum
{
    E_AHI_DEVICE_TIMER1           = 0,    /* Timer 1 */
    E_AHI_DEVICE_TIMER2           = 1,    /* Timer 2 */
    E_AHI_DEVICE_SYSCTRL          = 2,    /* System controller */
    E_AHI_DEVICE_BBC              = 3,    /* Baseband controller */
    E_AHI_DEVICE_AES              = 4,    /* Encryption engine */
    E_AHI_DEVICE_PHYCTRL          = 5,    /* Phy controller */
    E_AHI_DEVICE_UART0            = 6,    /* UART 0 */
    E_AHI_DEVICE_UART1            = 7,    /* UART 1 */
    E_AHI_DEVICE_TIMER0           = 8,    /* Timer 0 */
    E_AHI_DEVICE_SI               = 10,   /* Serial Interface (2 wire) */
    E_AHI_DEVICE_SPIM             = 11,   /* SPI master */
    E_AHI_DEVICE_SPIS             = 12,   /* SPI slave */
    E_AHI_DEVICE_ANALOGUE         = 13,   /* Analogue peripherals */
    E_AHI_DEVICE_TIMER3           = 14,   /* Timer 3 */
    E_AHI_DEVICE_TICK_TIMER       = 15,   /* Tick timer */
    E_AHI_DEVICE_TIMER4           = 16,   /* Timer 4 */
    E_AHI_DEVICE_FEC              = 17,   /* Flash and EEPROM Controller */
    E_AHI_DEVICE_INFRARED         = 19    /* Infrared */
} teAHI_Device;

/* Individual interrupts. GPIO defined elswhere in this file */
typedef enum
{
    E_AHI_SYSCTRL_PC0   = 22,   /* Pulse Counter 0 */
    E_AHI_SYSCTRL_PC1   = 23,   /* Pulse Counter 1 */
    E_AHI_SYSCTRL_VFES  = 24,   /* VBO Falling  */
    E_AHI_SYSCTRL_VRES  = 25,   /* VBO Rising */
    E_AHI_SYSCTRL_WK0   = 26,   /* Wake timer 0 */
    E_AHI_SYSCTRL_WK1   = 27,   /* Wake timer 1 */
    E_AHI_SYSCTRL_COMP0 = 28,   /* Comparator 0 */
    E_AHI_SYSCTRL_FEC   = 29,   /* Flash and EEPROM Controller */
    E_AHI_SYSCTRL_RNDES = 30,   /* Random number generator */
    E_AHI_SYSCTRL_CKES  = 31    /* Clock change  */
} teAHI_Item;

#endif /* AHI_DEVICE_ENUM */

/* Application interrupt callback */
typedef void (*PR_HWINT_APPCALLBACK)(uint32 u32Device, uint32 u32ItemBitmap);

/* Spi Master Configuration */
typedef uint32 tSpiConfiguration;

/* Sleep Modes */
typedef enum
{
    E_AHI_SLEEP_OSCON_RAMON,     /*32Khz Osc on and Ram On*/
    E_AHI_SLEEP_OSCON_RAMOFF,    /*32Khz Osc on and Ram off*/
    E_AHI_SLEEP_OSCOFF_RAMON,    /*32Khz Osc off and Ram on*/
    E_AHI_SLEEP_OSCOFF_RAMOFF,   /*32Khz Osc off and Ram off*/
    E_AHI_SLEEP_DEEP,            /*Deep Sleep*/
} teAHI_SleepMode;


/*Flash Chips*/
typedef enum {
    E_FL_CHIP_ST_M25P10_A,
    E_FL_CHIP_SST_25VF010,
    E_FL_CHIP_ATMEL_AT25F512,
    E_FL_CHIP_ST_M25P40_A,
    E_FL_CHIP_ST_M25P05_A,
    E_FL_CHIP_ST_M25P20_A,
    E_FL_CHIP_CUSTOM,
    E_FL_CHIP_AUTO,
    E_FL_CHIP_INTERNAL
} teFlashChipType;


/* Type definitions for SPI Flash access functions */
typedef void    (*tpfvZSPIflashInit)(int iDivisor, uint8 u8SlaveSel);
typedef void    (*tpfvZSPIflashSetSlaveSel)(uint8 u8SlaveSel);
typedef void    (*tpfvZSPIflashWREN)(void);
typedef void    (*tpfvZSPIflashEWRSR)(void);
typedef uint8   (*tpfu8ZSPIflashRDSR)(void);
typedef uint16  (*tpfu16ZSPIflashRDID)(void);
typedef void    (*tpfvZSPIflashWRSR)(uint8 u8Data);
typedef void    (*tpfvZSPIflashPP)(uint32 u32Addr, uint16 u16Len, uint8* pu8Data);
typedef void    (*tpfvZSPIflashRead)(uint32 u32Addr,uint16 u16Len,uint8* pu8Data);
typedef void    (*tpfvZSPIflashBE)(void);
typedef void    (*tpfvZSPIflashSE)(uint8 u8Sector);

/* Table of SPI Flash access functions */
typedef struct tagSPIflashFncTable {
    uint32                      u32Signature;
    uint16                      u16FlashId;
    uint16                      u16Reserved;
    tpfvZSPIflashInit           vZSPIflashInit;
    tpfvZSPIflashSetSlaveSel    vZSPIflashSetSlaveSel;
    tpfvZSPIflashWREN           vZSPIflashWREN;
    tpfvZSPIflashEWRSR          vZSPIflashEWRSR;
    tpfu8ZSPIflashRDSR          u8ZSPIflashRDSR;
    tpfu16ZSPIflashRDID         u16ZSPIflashRDID;
    tpfvZSPIflashWRSR           vZSPIflashWRSR;
    tpfvZSPIflashPP             vZSPIflashPP;
    tpfvZSPIflashRead           vZSPIflashRead;
    tpfvZSPIflashBE             vZSPIflashBE;
    tpfvZSPIflashSE             vZSPIflashSE;
} tSPIflashFncTable;

/* Flash Powerdown */
typedef enum
{
    E_AHI_EE_POWERDOWN,
    E_AHI_FLASH_BANDGAP_ENABLE,
    E_AHI_FLASH_POWERDOWN
} AHI_FlashControl_e;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/* Initialisation */
PUBLIC uint32 u32AHI_Init(void);

PUBLIC void vAHI_ExtendedTemperatureOperation(
    bool_t      bEnable);

/* System controller */
PUBLIC void vAHI_SetJTAGdebugger(bool_t bEnable, bool_t bLocation);

PUBLIC void vAHI_ClearSystemEventStatus(
    uint32      u32BitMask);

PUBLIC void vAHI_SetStackOverflow(bool_t bStkOvfEn, uint32 u32Addr);

PUBLIC uint8 u8AHI_PowerStatus(void);

PUBLIC void vAHI_ProtocolPower(
    bool_t      bOnNotOff);

/*[I SP001340_sfr 5]*/ /*[PR984 ]*/
PUBLIC void vAHI_CpuDoze(void);

/* [PR379] */
PUBLIC void vAHI_Sleep(
    teAHI_SleepMode         eSleepMode);

PUBLIC void vAHI_ETSIHighPowerModuleEnable(
    bool_t      bOnNotOff);

PUBLIC void vAHI_HighPowerModuleEnable(
    bool_t      bRFTXEn,
    bool_t      bRFRXEn);

PUBLIC void vAHI_SysCtrlRegisterCallback(
    PR_HWINT_APPCALLBACK prSysCtrlCallback);

/*[I SP001340_sfr 1]*/ /*[PR202] */
PUBLIC void vAHI_BrownOutConfigure(
    uint8       const u8VboSelect,
    bool_t      const bVboRstEn,
    bool_t      const bVboEn,
    bool_t      const bVboIntEnFalling,
    bool_t      const bVboIntEnRising);

PUBLIC bool_t bAHI_BrownOutStatus(void);

PUBLIC bool_t bAHI_BrownOutEventResetStatus(void);

PUBLIC uint32 u32AHI_BrownOutPoll(void);

/*[I SP001340_sfr 6]*/
PUBLIC void vAHI_StartRandomNumberGenerator(
    bool_t      const bMode,
    bool_t      const bIntEn);

/*[I SP001340_sfr 7]*/
PUBLIC void vAHI_StopRandomNumberGenerator(void);

/*[I SP001340_sfr 8]*/
PUBLIC uint16 u16AHI_ReadRandomNumber(void);

/*[I SP001340_sfr 9]*/
PUBLIC bool_t bAHI_RndNumPoll(void);

PUBLIC void vAHI_WriteNVData(
    uint8       u8Location,
    uint32      u32WriteData);

PUBLIC uint32 u32AHI_ReadNVData(
    uint8       u8Location);

PUBLIC void vAHI_Trim32Mhz(
        uint8 u8BiasCurrent
#if (defined JENNIC_CHIP_JN5169)
        ,
        uint8 u8BiasImpedence,
        uint8 u8CTrim
#endif
        );

PUBLIC void vAHI_Trim32KhzRC(
     uint8      u8Value);

PUBLIC bool_t bAHI_TrimHighSpeedRCOsc(void);

PUBLIC uint16 u16AHI_PowerStatus(void);

PUBLIC void vAHI_Init32KhzXtal(void);

PUBLIC void vAHI_ClockXtalPull(
    uint8       u8PullValue);

PUBLIC bool_t bAHI_Clock32MHzStable(void);

/* 32Khz Clock Mode selection*/
/*[I SP001340_sfr 4]*/ /*[PR835] */
PUBLIC bool_t bAHI_Set32KhzClockMode(
    uint8       const u8Mode);

/* Phy Controller */
/*[I SP001340_sfr 3]*/ /*[PR263]*/
PUBLIC bool_t bAHI_PhyRadioSetPower(
    uint8       const u8PowerLevel);

/* ADC/DAC */

PUBLIC void vAHI_ApSetBandGap(
    bool_t      bBandGapEnable); /* RefPR1488*/

PUBLIC void vAHI_ApSetSlowConversions(
    bool_t      bSlowConversionsEnable); /*Trac 385*/

/*[I SP001340_sfr 24] */ /* [PR833] */
PUBLIC void   vAHI_ApConfigure(
    bool_t      bAPRegulator,
    bool_t      bIntEnable,
    uint8       u8SampleSelect,
    uint8       u8ClockDivRatio,
    bool_t      bRefSelect);

/*[I SP001340_sfr 24] */ /* [PR833] */
PUBLIC void vAHI_AdcStartAccumulateSamples(
    uint8       const u8AccSamples);

PUBLIC bool_t bAHI_APRegulatorEnabled(void);

PUBLIC void   vAHI_APRegisterCallback(
    PR_HWINT_APPCALLBACK prApCallback);

/*[I SP001340_sfr 24] */ /* [PR833] */
PUBLIC void   vAHI_AdcEnable(
    bool_t      bContinuous,
    bool_t      bInputRange,
    uint8       u8Source);

PUBLIC void   vAHI_AdcDisable(void);

/*[I SP001340_sfr 24] */ /* [PR833] */
PUBLIC void   vAHI_AdcStartSample(void);

/*[I SP001340_sfr 24] */ /* [PR833] */
PUBLIC bool_t bAHI_AdcPoll(void);

PUBLIC uint16 u16AHI_AdcRead(void);

PUBLIC bool_t bAHI_AdcEnableSampleBuffer(
    bool_t      bInputRange,
    uint8       u8Timer,
    uint32      u32SourceBitmap,
    uint16     *pu16Buffer,
    uint16      u16BufferSize,
    bool_t      bBufferWrap,
    uint8       u8InterruptModes);

PUBLIC void vAHI_AdcDisableSampleBuffer(void);

PUBLIC uint16 u16AHI_AdcSampleBufferOffset(void);

/* Comparators */
PUBLIC void   vAHI_ComparatorEnable(
    uint8       u8Comparator,
    uint8       u8Hysteresis,
    uint8       u8SignalSelect);

 PUBLIC void vAHI_ComparatorLowPowerMode(
     bool_t     bLowPowerMode);

PUBLIC void   vAHI_ComparatorDisable(
    uint8       u8Comparator);

PUBLIC void   vAHI_ComparatorIntEnable(
    uint8       u8Comparator,
    bool_t      bIntEnable,
    bool_t      bRisingNotFalling);

PUBLIC uint8  u8AHI_ComparatorStatus(void);

PUBLIC uint8  u8AHI_ComparatorWakeStatus(void);

/* Comparator aliases */
#define vAHI_ComparatorWakeEnable(u8Comparator, bIntEnable, bRisingNotFalling) \
            vAHI_ComparatorIntEnable(u8Comparator, bIntEnable, bRisingNotFalling)

/* Wake timers */
PUBLIC void   vAHI_WakeTimerEnable(
    uint8       u8Timer,
    bool_t      bIntEnable);

PUBLIC void   vAHI_WakeTimerStart(
    uint8       u8Timer,
    uint32      u32Count);

PUBLIC void   vAHI_WakeTimerStop(
    uint8       u8Timer);

PUBLIC uint8  u8AHI_WakeTimerStatus(void);

/*[I SP001340_sfr 20]*/ /*[PR844] & [PR836]*/
PUBLIC uint32 u32AHI_WakeTimerCalibrate(void);

PUBLIC uint32 u32AHI_WakeTimerCalibrateEnhanced(
    uint16      u16CalValue);

PUBLIC uint8  u8AHI_WakeTimerFiredStatus(void);

PUBLIC uint32 u32AHI_WakeTimerRead(
    uint8       u8Timer);

/*[I SP001340_sfr 16]*/
PUBLIC uint64 u64AHI_WakeTimerReadLarge(
    uint8       u8Timer);

PUBLIC void vAHI_WakeTimerStartLarge(
    uint8       u8Timer,
    uint64      u64Count);

/* GPIO */
PUBLIC void   vAHI_DioSetDirection(
    uint32      u32Inputs,
    uint32      u32Outputs);

PUBLIC void   vAHI_DioSetOutput(
    uint32      u32On,
    uint32      u32Off);

PUBLIC void   vAHI_DioSetPullup(
    uint32      u32On,
    uint32      u32Off);

PUBLIC uint32 u32AHI_DioReadInput(void);

PUBLIC void   vAHI_DioWakeEdge(
    uint32      u32Rising,
    uint32      u32Falling);

PUBLIC void   vAHI_DioWakeEnable(
    uint32      u32Enable,
    uint32      u32Disable);

PUBLIC uint32 u32AHI_DioWakeStatus(void);

/*[I SP001340_sfr 27]*/ /*[PR400]*/
PUBLIC uint8 u8AHI_DioReadByte(
    bool_t      bDIOSelect);

/*[I SP001340_sfr 28]*/ /*[PR400] */
PUBLIC void vAHI_DioSetByte(
    bool_t      bDIOSelect,
    uint8       u8DataByte);

#define vAHI_DioInterruptEdge(u32Rising, u32Falling)    (vAHI_DioWakeEdge(u32Rising, u32Falling))
#define vAHI_DioInterruptEnable(u32Enable, u32Disable)  (vAHI_DioWakeEnable(u32Enable, u32Disable))
/*[I SP001340_sfr 29] */ /*[PR676 ] */
#define u32AHI_DioInterruptStatus()                     (u32AHI_DioWakeStatus())


PUBLIC bool_t bAHI_DoEnableOutputs(
    bool_t      bEnable);

PUBLIC void vAHI_DoSetDataOut(
    uint8       u8On,
    uint8       u8Off);

PUBLIC void vAHI_DoSetPullup(
    uint8       u8On,
    uint8       u8Off);

/* UARTs */
PUBLIC bool_t bAHI_UartEnable(
    uint8       u8Uart,
    uint8      *pu8TxBufAd,
    uint16      u16TxBufLen,
    uint8      *pu8RxBufAd,
    uint16      u16RxBufLen);

PUBLIC void   vAHI_UartEnable(
    uint8       u8Uart);

PUBLIC void   vAHI_UartDisable(
    uint8       u8Uart);

PUBLIC void   vAHI_UartSetBaudDivisor(
    uint8       u8Uart,
    uint16      u16Divisor);

PUBLIC void   vAHI_UartSetClockDivisor(
    uint8       u8Uart,
    uint8       u8BaudRate);

PUBLIC void   vAHI_UartSetControl(
    uint8       u8Uart,
    bool_t      bEvenParity,
    bool_t      bEnableParity,
    uint8       u8WordLength,
    bool_t      bOneStopBit,
    bool_t      bRtsValue);

PUBLIC void   vAHI_UartSetInterrupt(
    uint8       u8Uart,
    bool_t      bEnableModemStatus,
    bool_t      bEnableRxLineStatus,
    bool_t      bEnableTxFifoEmpty,
    bool_t      bEnableRxData,
    uint8       u8FifoLevel);

PUBLIC void   vAHI_UartReset(
    uint8       u8Uart,
    bool_t      bTxReset,
    bool_t      bRxReset);

PUBLIC uint8  u8AHI_UartReadLineStatus(
    uint8       u8Uart);

PUBLIC uint8  u8AHI_UartReadModemStatus(
    uint8       u8Uart);

PUBLIC uint8  u8AHI_UartReadInterruptStatus(
    uint8       u8Uart);

PUBLIC void   vAHI_UartWriteData(
    uint8       u8Uart,
    uint8       u8Data);

PUBLIC uint8  u8AHI_UartReadData(
    uint8       u8Uart);

PUBLIC void   vAHI_UartSetRTSCTS(
    uint8       u8Uart,
    bool_t      bRTSCTSEn);

PUBLIC void   vAHI_Uart0RegisterCallback(
    PR_HWINT_APPCALLBACK    prUart0Callback);

PUBLIC void   vAHI_Uart1RegisterCallback(
    PR_HWINT_APPCALLBACK    prUart1Callback);

PUBLIC uint16 u16AHI_UartBlockWriteData(
    uint8       u8Uart,
    uint8      *pu8Data,
    uint16      u16DataLength);

PUBLIC uint16 u16AHI_UartBlockReadData(
    uint8       u8Uart,
    uint8      *pu8Data,
    uint16      u16DataLength);

PUBLIC void vAHI_UartTxOnly(uint8 u8Uart, bool_t bEnable);

/*[I SP001340_sfr 30]*/
PUBLIC void vAHI_UartSetAutoFlowCtrl(
    uint8       const u8Uart,
    uint8       const u8RxFifoLevel,
    bool_t      const bFlowCtrlPolarity,
    bool_t      const bAutoRts,
    bool_t      const bAutoCts);

PUBLIC void vAHI_UartSetClocksPerBit(
    uint8       u8Uart,
    uint8       u8Cpb);

#if (UART_BACKWARDS_COMPATIBLE_API==1)
PUBLIC uint8 u8AHI_UartReadRxFifoLevel(
    uint8       u8Uart);

PUBLIC uint8 u8AHI_UartReadTxFifoLevel(
    uint8       u8Uart);
#endif

PUBLIC uint16 u16AHI_UartReadRxFifoLevel(
    uint8       u8Uart);

PUBLIC uint16 u16AHI_UartReadTxFifoLevel(
    uint8       u8Uart);

PUBLIC void vAHI_UartSetRTS(
    uint8       u8Uart,
    bool_t      bRtsValue);

PUBLIC void vAHI_UartSetBreak(
    uint8       u8Uart,
    bool_t      bBreak);

#define vAHI_UartSetBaudRate(u8Uart, u8BaudRate) vAHI_UartSetClockDivisor(u8Uart, u8BaudRate)

PUBLIC void vAHI_UartSetLocation(uint8 u8Uart, bool_t bLocation);

/* Timers */
PUBLIC void vAHI_TimerConfigureInputs(
    uint8       u8Timer,
    bool_t      bInvCapt,
    bool_t      bEventEdge);

PUBLIC void vAHI_TimerConfigure(
    uint8       u8Timer,
    bool_t      bInvertPwmOutput,
    bool_t      bGateDisable);

#define vAHI_TimerConfigureOutputs(u8Timer, bInvertPwmOutput, bGateDisable) vAHI_TimerConfigure(u8Timer, bInvertPwmOutput, bGateDisable)

PUBLIC void  vAHI_TimerEnable(
    uint8       u8Timer,
    uint8       u8Prescale,
    bool_t      bIntRiseEnable,
    bool_t      bIntPeriodEnable,
    bool_t      bOutputEnable);

/*[I SP001340_sfr 33]*/
PUBLIC void  vAHI_TimerDisable(
    uint8       u8Timer);

/*[I SP001340_sfr 34]*/
PUBLIC void  vAHI_TimerClockSelect(
    uint8       u8Timer,
    bool_t      bExternalClock,
    bool_t      bInvertClock);

/*[I SP001340_sfr 35]*/
PUBLIC void  vAHI_TimerStartSingleShot(
    uint8       u8Timer,
    uint16      u16Hi,
    uint16      u16Lo);

/*[I SP001340_sfr 36]*/
PUBLIC void  vAHI_TimerStartRepeat(
    uint8       u8Timer,
    uint16      u16Hi,
    uint16      u16Lo);

/*[I SP001340_sfr 37]*/
PUBLIC void  vAHI_TimerStartDeltaSigma(
    uint8       u8Timer,
    uint16      u16Hi,
    uint16      u16Lo,
    bool_t      bRtzEnable);

/*[I SP001340_sfr 38]*/
PUBLIC void  vAHI_TimerStartCapture(
    uint8       u8Timer);

/*[I SP001340_sfr 39] */
PUBLIC void  vAHI_TimerReadCapture(
    uint8       u8Timer,
    uint16     *pu16Hi,
    uint16     *pu16Lo);

/*[I SP001340_sfr 39] */ /*[PR385] */
PUBLIC void vAHI_TimerReadCaptureFreeRunning(
    uint8       u8Timer,
    uint16     *pu16Hi,
    uint16     *pu16Lo);

/*[I SP001340_sfr 41]*/
PUBLIC void  vAHI_TimerStop(
    uint8       u8Timer);

/*[I SP001340_sfr 42]*/
PUBLIC uint8 u8AHI_TimerFired(
    uint8       u8Timer);

/*[I SP001340_sfr 40]*/ /* [PR469] */
PUBLIC uint16 u16AHI_TimerReadCount(
    uint8       u8Timer);

/*[I SP001340_sfr 43]*/
PUBLIC void vAHI_TimerDIOControl(
    uint8       u8Timer,
    bool_t      bDIOEnable);

PUBLIC void vAHI_TimerFineGrainDIOControl(
    uint8       const u8BitMask);

PUBLIC void  vAHI_Timer0RegisterCallback(
    PR_HWINT_APPCALLBACK        prTimer0Callback);

PUBLIC void  vAHI_Timer1RegisterCallback(
    PR_HWINT_APPCALLBACK        prTimer1Callback);

PUBLIC void vAHI_Timer2RegisterCallback(
    PR_HWINT_APPCALLBACK        prTimer2Callback);

PUBLIC void vAHI_Timer3RegisterCallback(
    PR_HWINT_APPCALLBACK        prTimer3Callback);

PUBLIC void vAHI_Timer4RegisterCallback(
    PR_HWINT_APPCALLBACK        prTimer4Callback);

/*[I SP001340_sfr 47]*/
PUBLIC void vAHI_IntHandlerTimer0(void);
/*[I SP001340_sfr 48]*/
PUBLIC void vAHI_IntHandlerTimer1(void);
/*[I SP001340_sfr 49]*/
PUBLIC void vAHI_IntHandlerTimer2(void);
PUBLIC void vAHI_IntHandlerTimer3(void);
PUBLIC void vAHI_IntHandlerTimer4(void);
PUBLIC void vAHI_TimerSetLocation(uint8 u8Timer, bool_t bLocation, bool_t bLocationOverridePWM3andPWM2);

/* Tick Timers */
PUBLIC uint32 u32AHI_TickTimerRead(void);

PUBLIC void   vAHI_TickTimerIntPendClr(void);

PUBLIC bool_t bAHI_TickTimerIntStatus(void);

PUBLIC void   vAHI_TickTimerWrite(uint32 u32Count);

PUBLIC void   vAHI_TickTimerConfigure(
    uint8       u8Mode);

PUBLIC void   vAHI_TickTimerInterval(
    uint32      u32Interval);

PUBLIC void   vAHI_TickTimerIntEnable(
    bool_t      bIntEnable);

PUBLIC void   vAHI_TickTimerInit(
    PR_HWINT_APPCALLBACK prTickTimerCallback);

#define  vAHI_TickTimerRegisterCallback(prTickTimerCallback) (vAHI_TickTimerInit(prTickTimerCallback))

/* SPI master */
PUBLIC void   vAHI_SpiConfigure(
    uint8       u8SlaveEnable,
    bool_t      bLsbFirst,
    bool_t      bTxNegEdge,
    bool_t      bRxNegEdge,
    uint8       u8ClockDivider,
    bool_t      bInterruptEnable,
    bool_t      bAutoSlaveSelect);

PUBLIC void   vAHI_SpiReadConfiguration(
    tSpiConfiguration *ptConfiguration);

PUBLIC void   vAHI_SpiRestoreConfiguration(
    tSpiConfiguration *ptConfiguration);

PUBLIC void   vAHI_SpiSelect(
    uint8       u8SlaveMask);

PUBLIC void   vAHI_SpiStop(void);

/*[I SP001340_sfr 60]*/
PUBLIC void   vAHI_SpiStartTransfer32(
    uint32      u32Out);

PUBLIC uint32 u32AHI_SpiReadTransfer32(void);

/*[I SP001340_sfr 60]*/
PUBLIC void   vAHI_SpiStartTransfer16(
    uint16      u16Out);

PUBLIC uint16 u16AHI_SpiReadTransfer16(void);

/*[I SP001340_sfr 60]*/
PUBLIC void   vAHI_SpiStartTransfer8(
    uint8       u8Out);

PUBLIC uint8  u8AHI_SpiReadTransfer8(void);

PUBLIC bool_t bAHI_SpiPollBusy(void);

PUBLIC void   vAHI_SpiWaitBusy(void);

PUBLIC void   vAHI_SpiRegisterCallback(
    PR_HWINT_APPCALLBACK        prSpiCallback);

PUBLIC void   vAHI_SpiSetContinuousMode(
    bool_t      bEnable);

/*[I SP001340_sfr 59]*/
PUBLIC void vAHI_SpiSetDelayReadEdge(
    bool_t      const bSetDreBit);

PUBLIC void vAHI_SpiStartTransfer(
    uint8       u8CharLen,
    uint32      u32Out);

PUBLIC void vAHI_SpiContinuous(
    bool_t      bEnable,
    uint8       u8CharLen);

PUBLIC void vAHI_SpiSelSetLocation(uint8 u8SpiSel, bool_t bLocation);

PUBLIC void vAHI_SpiDisable(void);

PUBLIC bool_t bAHI_EnableD0andD1Outputs(
    bool_t      bEnable);

/* SPI Slave */
PUBLIC bool_t bAHI_SpiSlaveEnable(
    bool_t bPinLocation,
    bool_t bLsbFirst,
    uint8  *pu8TxBuffer,
    uint8  u8TxBufferLength,
    uint8  u8TxBufferThreshold,
    uint8  *pu8RxBuffer,
    uint8  u8RxBufferLength,
    uint8  u8RxBufferThreshold,
    uint16 u16RxTimeOut,
    uint16 u16InterruptEnableMask);

PUBLIC void vAHI_SpiSlaveDisable(void);

PUBLIC void vAHI_SpiSlaveReset(
    bool_t      bTxReset,
    bool_t      bRxReset);

PUBLIC void vAHI_SpiSlaveTxWriteByte(
    uint8       u8Byte);

PUBLIC uint8 u8AHI_SpiSlaveRxReadByte(void);

PUBLIC uint8 u8AHI_SpiSlaveTxFillLevel(void);

PUBLIC uint8 u8AHI_SpiSlaveRxFillLevel(void);

PUBLIC uint8 u8AHI_SpiSlaveStatus(void);

PUBLIC void vAHI_IntHandlerSpiSlave(void);

PUBLIC void vAHI_SpiSlaveRegisterCallback(
    PR_HWINT_APPCALLBACK        prSpiCallback);

/* Serial 2-wire interface Master */
PUBLIC void vAHI_SiMasterConfigure( bool_t bPulseSuppressionEnable,
                                    bool_t bInterruptEnable,
                                    uint8 u8PreScaler);
PUBLIC void vAHI_SiMasterSetCmdReg( bool_t bSetSTA,
                                    bool_t bSetSTO,
                                    bool_t bSetRD,
                                    bool_t bSetWR,
                                    bool_t bSetAckCtrl,
                                    bool_t bSetIACK);
PUBLIC bool_t bAHI_SiMasterSetCmdReg( bool_t bSetSTA,
                                    bool_t bSetSTO,
                                    bool_t bSetRD,
                                    bool_t bSetWR,
                                    bool_t bSetAckCtrl,
                                    bool_t bSetIACK);
PUBLIC void   vAHI_SiMasterWriteData8(uint8 u8Out);
PUBLIC void vAHI_SiMasterWriteSlaveAddrExtended(uint16 u16SlaveAddress,
                                                bool_t bReadStatus,
                                                bool_t bExtendAddress );
PUBLIC void   vAHI_SiMasterWriteSlaveAddr(uint8 u8SlaveAddress,bool_t bReadStatus);
PUBLIC uint8  u8AHI_SiMasterReadData8(void);
PUBLIC bool_t bAHI_SiMasterPollBusy(void);
PUBLIC bool_t bAHI_SiMasterPollTransferInProgress(void);
PUBLIC bool_t bAHI_SiMasterPollRxNack(void);
PUBLIC bool_t bAHI_SiMasterPollArbitrationLost(void);
PUBLIC void vAHI_SiMasterDisable(void);
PUBLIC bool_t bAHI_SiMasterCheckRxNack(void);
PUBLIC void vAHI_SiSetLocation(bool_t bLocation);

#define vAHI_SiSlaveDisable() vAHI_SiMasterDisable()

/* Serial 2-wire interface Master wrappers for backwards compatability */
#define  bAHI_SiPollArbitrationLost()       bAHI_SiMasterPollArbitrationLost()
#define  bAHI_SiCheckRxNack()               bAHI_SiMasterCheckRxNack()
#define  bAHI_SiPollRxNack()                bAHI_SiMasterCheckRxNack()
#define  bAHI_SiPollTransferInProgress()    bAHI_SiMasterPollTransferInProgress()
#define  bAHI_SiPollBusy()                  bAHI_SiMasterPollBusy()
#define  vAHI_SiWriteSlaveAddr(u8SlaveAddress, bReadStatus) vAHI_SiMasterWriteSlaveAddr(u8SlaveAddress, bReadStatus)
#define  u8AHI_SiReadData8()                u8AHI_SiMasterReadData8()
#define  vAHI_SiWriteData8(u8Out)           vAHI_SiMasterWriteData8(u8Out)
#define  vAHI_SiSetCmdReg(bSetSTA, bSetSTO, bSetRD, bSetWR, bSetAckCtrl, bSetIACK) \
            vAHI_SiMasterSetCmdReg(bSetSTA, bSetSTO, bSetRD, bSetWR, bSetAckCtrl, bSetIACK)
#define  vAHI_SiConfigure(bPulseSuppressionEnable, bInterruptEnable, u8PreScaler) \
            vAHI_SiMasterConfigure(bPulseSuppressionEnable, bInterruptEnable, u8PreScaler)

/* Serial 2-wire interface Slave */
PUBLIC void vAHI_SiSlaveConfigure(  uint16 u16SlaveAddress,
                                    bool_t bExtendAddr,
                                    bool_t bPulseSuppressionEnable,
                                    uint8 u8InMaskEnable,
                                    bool_t bFlowCtrlMode);
PUBLIC void vAHI_SiSlaveWriteData8(uint8 u8Out);
PUBLIC uint8 u8AHI_SiSlaveReadData8(void);

/* Serial 2-wire interface common */
PUBLIC void   vAHI_SiRegisterCallback(PR_HWINT_APPCALLBACK prSiCallback);

/* Flash access */
/* [I SP001340_sfr 72]   */ /*[PR748] */
PUBLIC bool_t bAHI_FlashInit(
    teFlashChipType         flashType,
    tSPIflashFncTable      *pCustomFncTable);

PUBLIC bool_t bAHI_FlashEraseSector(
    uint8       u8Sector);

/*[I SP001340_sfr 70] */ /*[PR566]  */
PUBLIC bool_t bAHI_FullFlashProgram(
    uint32      u32Addr,
    uint16      u16Len,
    uint8      *pu8Data);

/*[I SP001340_sfr 70] */ /*[PR566]  */
PUBLIC bool_t bAHI_FullFlashRead(
    uint32      u32Addr,
    uint16      u16Len,
    uint8      *pu8Data);

/*[I SP001340_sfr 71] */ /*[PR379]  */
PUBLIC void vAHI_FlashPowerUp(void);

/*[I SP001340_sfr 71] */ /*[PR379]  */
PUBLIC void vAHI_FlashPowerDown(void);

PUBLIC bool_t bAHI_FlashControl(
    AHI_FlashControl_e      eFlashControl,
    bool_t                  bSet);

PUBLIC bool_t bAHI_FlashEECerrorInterruptSet(
    bool_t                  bEnable,
    PR_HWINT_APPCALLBACK    prFlashEECCallback);

PUBLIC void vAHI_FlashAndEEPROMControllerIntHandler(void);

PUBLIC bool_t bAHI_FlashInternalMultiSectorErase(
    uint8       u8SectorBitmap);

/* Reset functions */
PUBLIC void vAHI_SwReset(void);

/*Watchdog functions*/
/*[I SP001340_sfr 12]*/
PUBLIC void vAHI_WatchdogStart(
    uint8       u8Prescale);

/*[I SP001340_sfr 13]*/
PUBLIC void vAHI_WatchdogStop(void);

/*[I SP001340_sfr 14]*/
PUBLIC void vAHI_WatchdogRestart(void);

/*[I SP001340_sfr 15]*/
PUBLIC bool_t bAHI_WatchdogResetEvent(void);

PUBLIC uint16 u16AHI_WatchdogReadValue(void);

PUBLIC void vAHI_WatchdogException(
    bool_t bEnable);

/* Pulse Counter Prototypes */
/*[I SP001340_sfr 50] */
PUBLIC bool_t bAHI_PulseCounterConfigure(
    uint8       const u8Counter,
    bool_t      const bEdgeType,
    uint8       const u8Debounce,
    /* This is backwards compatable with bool_t if users have used TRUE, FALSE as arguments */
    uint8       const u8Combine,
    bool_t      const bIntEnable);

/*[I SP001340_sfr 51] */
PUBLIC bool_t bAHI_StartPulseCounter(
    uint8       const u8Counter);

/*[I SP001340_sfr 52] */
PUBLIC bool_t bAHI_StopPulseCounter(
    uint8       const u8Counter);

/*[I SP001340_sfr 53] */
PUBLIC bool_t bAHI_Read16BitCounter(
    uint8       const u8Counter,
    volatile    uint16 * pu16Count);

/*[I SP001340_sfr 54] */
PUBLIC bool_t bAHI_Clear16BitPulseCounter(
    uint8       const u8Counter);

/*[I SP001340_sfr 55] */
PUBLIC bool_t bAHI_Read32BitCounter(
    volatile uint32        *pu32Count);

/*[I SP001340_sfr 56] */
PUBLIC bool_t bAHI_Clear32BitPulseCounter(void);

/*[I SP001340_sfr 57] */
PUBLIC bool_t bAHI_SetPulseCounterRef(
    uint8       const u8Counter,
    uint32      u32RefValue);

PUBLIC uint32 u32AHI_PulseCounterStatus(void);

PUBLIC void vAHI_PulseCounterSetLocation(uint8 const u8Counter, bool_t bLocation);

/* Sys Ctrl - CPU Clock  */
/*[I SP001340_sfr 110] */ /*[PR983] */
PUBLIC  bool_t bAHI_SetClockRate(uint8 u8Speed);
/*[I SP001340_sfr 111]*/ /*[PR983] */
PUBLIC  void vAHI_SelectClockSource(
    bool_t      const bClkSource,
    bool_t      const bPowerDown);

/*[I SP001340_sfr 112]*/ /*[PR983] */
PUBLIC  void vAHI_EnableFastStartUp(
    bool_t      const bMode,
    bool_t      const bIsPowerDown);

/*[I SP001340_sfr 113]*/ /*[PR983] */
PUBLIC  void vAHI_PowerXTAL(bool_t const bIsOn);
/*[I SP001340_sfr 114]*/ /*[PR983] */
PUBLIC bool_t bAHI_GetClkSource(void);
/*[I SP001340_sfr 115]*/ /*[PR983] */
PUBLIC  uint8 u8AHI_GetSystemClkSpeed(void);
#define u8AHI_GetSystemClkRate() u8AHI_GetSystemClkSpeed()
#define u8AHI_GetClockRate() u8AHI_GetSystemClkSpeed()
/*[I SP001340_sfr 117]*/
PUBLIC void vAHI_OptimiseWaitStates(void);

/* Antenna Diversity */
PUBLIC void vAHI_AntennaDiversityOutputEnable(bool_t bOddRetryOutEn, bool_t bEvenRetryOutEn); /* API documentation refers to parameters as bOddOutEn and bEvenOutEn for clarity */

PUBLIC void vAHI_AntennaDiversityEnable(
    bool_t      bRxDiversity,
    bool_t      bTxDiversity);

PUBLIC void vAHI_AntennaDiversityControl(
    uint8       u8RxRssiThreshold,
    uint8       u8RxCorrThreshold);

PUBLIC void vAHI_AntennaDiversitySwitch(void);

PUBLIC uint8 u8AHI_AntennaDiversityStatus(void);

/* Infrared RC Transmitter */
PUBLIC bool_t bAHI_InfraredEnable(
    uint8       u8Prescale,
    uint16      u16Hi,
    uint16      u16Lo,
    uint16      u16BitPeriodInCarrierPeriods,
    bool_t      bInvertOutput,
    bool_t      bInterruptEnable);

PUBLIC void vAHI_InfraredDisable(void);

PUBLIC bool_t bAHI_InfraredStart(
    uint32     *pu32BufferAddress,
    uint16      u16TransmissionLengthInBits);

PUBLIC bool_t bAHI_InfraredStatus(void);

PUBLIC void vAHI_InfraredRegisterCallback(
    PR_HWINT_APPCALLBACK prInfraredCallback);

PUBLIC void vAHI_IntHandlerInfrared(void);

/* EEPROM API */
PUBLIC uint16 u16AHI_InitialiseEEP(
    uint8      *pu8SegmentDatalength);

PUBLIC int iAHI_WriteDataIntoEEPROMsegment(
    uint16      u16SegmentIndex,
    uint8       u8SegmentByteAddress,
    uint8      *pu8DataBuffer,
    uint8       u8Datalength);

PUBLIC int iAHI_ReadDataFromEEPROMsegment(
    uint16      u16SegmentIndex,
    uint8       u8SegmentByteAddress,
    uint8      *pu8DataBuffer,
    uint8       u8Datalength);

PUBLIC int iAHI_EraseEEPROMsegment(
    uint16      u16SegmentIndex);

/* Functions to store / restore debug control registers when sleeping */

/** Number of registers to store. Storage must be allocated for this number of uint32 registers. */
#define AHI_STORE_DEBUG_REGISTER_COUNT (22)

/** Save the debug unit registers into pRegStorage */
PUBLIC void vAHI_StoreDebug(uint32 *pRegStorage);
/** Restore debug unit registers from pRegStorage */
PUBLIC void vAHI_RestoreDebug(uint32 *pRegStorage);


/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* AHI_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
