/*****************************************************************************
 *
 * MODULE:              Production Test API - Header
 *
 * DESCRIPTION:
 * Provides an API for access to functions to aid in the test of products
 * based upon Jennic wireless microcontroller IC's.
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

#ifndef  JPT_H_INCLUDED
#define  JPT_H_INCLUDED

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

/* Value enumerations: Radio Initialisation */
#define E_JPT_MODE_LOPOWER          (0)
#define E_JPT_MODE_BOOST            (1)
#define E_JPT_MODE_HIPOWER          (2)
#define E_JPT_MODE_0DBM             (3) /* LP JN5148 Only           */

#define E_JPT_MODE_ETSI             (4) /* HP JN5148 Only (M04)     */
#define E_JPT_MODE_ETSIM06          (5) /* HP JN5148 Only (M06)     */

#define E_JPT_MODE_IGNORE_RFTX_RFRX (1UL << 31) /* OR with other values to
                                                   stop RFRX and RFTX being
                                                   altered by bJPT_InitRadio */

/* Value enumerations: Xtal Oscillator Test */
#define E_JPT_XOT_DIO10                     0
#define E_JPT_XOT_STOP                      1

/* Value enumerations: Tx Power Test */
#define E_JPT_TXPT_RUN_CW                   0
#define E_JPT_TXPT_RUN_PRBS                 1
#define E_JPT_TXPT_STOP                     2

/* Value enumerations: Site Survey Per Test */
#define E_JPT_SSPT_MODE_LOCATE              1
#define E_JPT_SSPT_MODE_STOPPED             2
#define E_JPT_SSPT_MODE_RUNNING_ACKS        3
#define E_JPT_SSPT_MODE_RUNNING_NO_ACKS     4
#define E_JPT_SSPT_MODE_RESTART             5

/* Value enumerations: Clear Channel Assesment Test */
#define E_JPT_CCA_MODE_ENERGY               1
#define E_JPT_CCA_MODE_CARRIER              2
#define E_JPT_CCA_MODE_CARRIER_OR_ENERGY    3
#define E_JPT_CCA_MODE_CARRIER_AND_ENERGY   4

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef struct {
    uint8 u8Mode;
    uint8 u8Channel;
    uint8 u8Retries;
    uint32 u32Total;
    uint32 u32Seen;
    uint32 u32Errors;
    uint8 u8Lqi;
} tsJPT_SSPT_MasterState;

typedef struct {
    uint8 u8Mode;
    uint8 u8Channel;
} tsJPT_SSPT_SlaveState;

typedef struct {
    bool_t bPacketGood;
    uint16 u16FrameControl;
    uint16 u16SourceShortAddress;
    uint16 u16DestinationShortAddress;
    uint64 u64SourceExtendedAddress;
    uint64 u64DestinationExtendedAddress;
    uint16 u16SourcePanID;
    uint16 u16DestinationPanID;
    uint8 u8PayloadLength;
    uint8 u8Payload[127] __attribute__ ((aligned (4)));
    uint8 u8Energy;
    uint8 u8SQI;
    uint8 u8SequenceNumber;
    uint8 u8LQI;
    uint8 u8RSSI;
} tsJPT_PT_Packet ;

typedef enum {
    JPT_MTPT_SLAVE_ISR,
    JPT_SSPT_MASTER_ISR,
    JPT_SSPT_SLAVE_ISR
} teISRTestType;

#if (defined RXPOWERADJUST_SUPPORT)
typedef enum
{
	E_MAX_INP_LEVEL_0dB = 0x00,
	E_MAX_INP_LEVEL_10dB = 0x01
} teMaxInpLevel;
#endif

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/* Misc functions */
PUBLIC uint32 u32JPT_Init(void);

/* Radio initialisation */
PUBLIC uint32 u32JPT_RadioModesAvailable(void);
PUBLIC bool_t bJPT_RadioInit(uint32 u32RadioMode);
PUBLIC void vJPT_RadioDeInit(void);
#if (defined JN5169)
PUBLIC void vJPT_GetRadioConfig(uint32 *u32RadioParams);
#endif

/* Debug */
#ifdef JPT_DEBUG
PUBLIC void vRadioSettingsDump(void);
#endif


/* Radio manipulation functions */
PUBLIC bool_t bJPT_RadioSetChannel(uint8 u8Channel);
PUBLIC uint8 u8JPT_RadioGetChannel(void);
PUBLIC void vJPT_RadioSetPower(uint8 u8PowerLevel);
PUBLIC uint8 u8JPT_RadioGetPower(void);
PUBLIC void vJPT_RadioSetPowerFine(uint8 u8PowerLevel);
PUBLIC uint8 u8JPT_RadioGetPowerFine(void);

/* Energy detect functions */
PUBLIC bool bJPT_CCA(uint8 u8Channel, uint8 u8Mode, uint8 u8Threshold);
PUBLIC uint8 u8JPT_EnergyDetect(uint8 u8Channel, uint32 u32Samples);
PUBLIC uint8 u8JPT_FineTuneEnergyDetect(uint32 u32Frequency, uint32 u32Samples);
PUBLIC int16 i16JPT_ConvertEnergyTodBm(uint8 u8Energy);
PUBLIC uint8 u8JPT_GetLQIfromRSSI(uint8 u8RSSI);


/* TX power test functions */
PUBLIC void vJPT_TxPowerTest(uint32 u32Mode);
PUBLIC void vJPT_TxPowerAdjust(uint8 u8PowerAdj, uint8 u8Att3db, uint8 u8Channel);
#if !(defined JENNIC_CHIP_FAMILY_JN516x) || (defined JENNIC_CHIP_JN5169)
PUBLIC void vJPT_CustomBmodTable(const uint8 (*pcau8CustomBmodTable)[4][16]);
#endif

/* Crystal oscillator test functions */
PUBLIC void vJPT_XtalOscillatorTest(uint32 u32Mode);

/* Module Test PER test functions */
PUBLIC void vJPT_MTPT_MasterStart(uint8 u8PayloadLength);
PUBLIC void vJPT_MTPT_MasterTxPacket(uint32 *pu32Acks);
PUBLIC void vJPT_MTPT_MasterTxPacketSend(bool_t bCSMA, uint8 u8SeqNum);
PUBLIC void vJPT_MTPT_MasterStop(void);

PUBLIC void vJPT_MTPT_SlaveStart(void);
PUBLIC void vJPT_MTPT_SlavePoll(uint32 *pu32HeadersSeen, uint32 *pu32FramesSeen, uint32 *pu32ErrorsSeen);
PUBLIC void vJPT_MTPT_SlaveStop(void);

/* Trigger packet test functions */
PUBLIC void vJPT_TPT_Start(void);
PUBLIC uint32 u32JPT_TPT_WaitPacket(uint32 u32Timeout, uint32 *pu32Total,
                                    uint32 *pu32Seen, uint32 *pu32ChipErrors);
PUBLIC void vJPT_TPT_Stop(void);

/* Site Survey PER Test functions */
PUBLIC void vJPT_SSPT_MasterInit(void);
PUBLIC bool_t bJPT_SSPT_MasterSetState(tsJPT_SSPT_MasterState *psState);
PUBLIC void vJPT_SSPT_MasterGetState(tsJPT_SSPT_MasterState *psState);
PUBLIC void vJPT_SSPT_SlaveInit(void);
PUBLIC void vJPT_SSPT_SlaveGetState(tsJPT_SSPT_SlaveState *psState);

/* Packet RX / TX Test Functions */
PUBLIC bool_t bJPT_PacketRx(uint8 u8Channel, tsJPT_PT_Packet *psPacket);
PUBLIC void vJPT_PacketTx(uint8 u8Channel, tsJPT_PT_Packet *psPacket);

/* Antenna diversity functions */
PUBLIC void vJPT_AntennaDiversityEnable(bool bEnabled);

#if (defined RXPOWERADJUST_SUPPORT)
PUBLIC void vJPT_SetMaxInputLevel(teMaxInpLevel eInLevel);
#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

extern teISRTestType ISRMode;
extern uint64 u64JPT_MacAddress;


#if defined __cplusplus
}
#endif

#endif  /* JPT_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
