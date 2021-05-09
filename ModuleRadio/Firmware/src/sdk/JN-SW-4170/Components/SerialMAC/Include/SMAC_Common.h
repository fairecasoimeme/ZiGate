/****************************************************************************
 *
 * MODULE:			SMAC_Common.h
 *
 * COMPONENT:       SerialMAC
 *
 * REVISION:     	$Revision: 85103 $
 *
 * DATED:			$Date: 2016-11-22 07:35:48 +0000 (Tue, 22 Nov 2016) $
 *
 * AUTHOR:   		$Author: nxp71769 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_Common.h $
 *
 * DESCRIPTION:		Common includes for the Serial MAC Upper (SMU) and the
 * 					Serial MAC Lower (SML) modules.
 *
 * $Id: SMAC_Common.h 85103 2016-11-22 07:35:48Z nxp71769 $
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

#ifndef  SMAC_COMMON_H_INCLUDED
#define  SMAC_COMMON_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include "mac_sap.h"
#include "mac_pib.h"



#ifndef SERIALMAC_MINI_MAC
	#ifdef SERIALMAC_FULL_MAC
	#else
		#define SERIALMAC_MINI_MAC
	#endif
#endif


/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define SMAC_EXCEPTION_NOT_INITIALISED				10
#define SMAC_EXCEPTION_RPC_LOCK_FAIL				11
#define SMAC_EXCEPTION_RPC_TIMEOUT					12
#define MAC_MIB_LIST_SIZE							16 		/* Number of addresses in MIBJoin List */
#define MAC_TX_POWER_TABLE_SIZE						16 		/* Number of addresses in MAC Tx Power Table List */


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef void (*SMAC_API_ERROR_CALLBACK)(uint32);



typedef struct
{
	uint8 	u8Type;				/* SMAC_API_HEADER_MIN */
	uint8	u8ParamLength;		/* SMAC_API_HEADER_MIN */
	uint8	u8Params[16];		/* Variable */

} SMAC_ApiHeader_s;

typedef struct
{
	uint8 	u8Type;				/* SMAC_API_HEADER_MIN */
	uint8	u8ParamLength;		/* SMAC_API_HEADER_MIN */
	uint8	u8Params[200];		/* Variable */

} SMAC_ApiHeader_MacTable_s;

typedef struct
{
	uint8 	u8Type;				/* SMAC_API_HEADER_MIN */
	uint8	u8ParamLength;		/* SMAC_API_HEADER_MIN */
	uint8	u8Params[140];		/* Variable */

} SMAC_ApiHeader_MibIeeeTable_s;

typedef struct
{
	uint8 	u8Type;				/* SMAC_API_HEADER_MIN */
	uint8	u8ParamLength;		/* SMAC_API_HEADER_MIN */
	uint8	u8Params[100u];		/* Variable */

} SMAC_ApiHeader_ProtoInfo_s;


#define SMAC_API_HEADER_MIN		2		/* u8Type + u8PayloadLen */


typedef enum SMAC_Type_e				/* Indicates MAC Type */
{
	E_SMAC_TYPE_UNKNOWN=0,
	E_SMAC_TYPE_NXP_MAC_2400=1,
	E_SMAC_TYPE_NXP_MINIMAC_2400=2,
	E_SMAC_TYPE_NXP_MAC_868=3,
	E_SMAC_TYPE_NXP_MAC_915=4,

}SMAC_Type_e;



typedef struct sSMAC_Status				/* Used to exchange info between SML and SMU */
{
	uint32 		u32Version;
	SMAC_Type_e	u8Type;
	uint8		u8Status;
	uint8 		u8Rsvd1;
	uint8 		u8Rsvd2;

}SMAC_Status_s;


typedef enum SMAC_MACPibAttribute		/* Used in the PIB Get/Set */
{
    E_SMAC_PIB_ATTR_COORDSHORT_ADDRESS=0,			// 0
    E_SMAC_PIB_ATTR_MAX_FRAME_TOTAL_WAIT_TIME,		// 1
    E_SMAC_PIB_ATTR_TRANSACTION_PERSISTENCE_TIME,	// 2
    E_SMAC_PIB_ATTR_MAXFRAMERETRIES,				// 3
    E_SMAC_PIB_ATTR_RESPONSEWAITTIME,				// 4
    E_SMAC_PIB_ATTR_PANID,							// 5
    E_SMAC_PIB_ATTR_SHORTADDR,						// 6
    E_SMAC_PIB_ATTR_MINBE,							// 7
    E_SMAC_PIB_ATTR_MAXBE,							// 8
    E_SMAC_PIB_ATTR_MAXCSMABACKOFFS,				// 9
    E_SMAC_PIB_ATTR_RXONWHENIDLE,					// 10
    E_SMAC_PIB_ATTR_COORDEXTADDR,					// 11
    E_SMAC_PIB_ATTR_MACFRAMECOUNTER,				// 12
    E_SMAC_PIB_ATTR_ASSOCIATIONPERMIT,				// 13
    E_SMAC_PIB_ATTR_BEACONPAYLOADLENGTH,			// 14
    E_SMAC_PIB_ATTR_BEACONPAYLOAD,					// 15
    E_SMAC_PIB_ATTR_BSN,							// 16
    E_SMAC_PIB_ATTR_DSN,							// 17
    E_SMAC_PIB_ATTR_PANCOORDINATOR,					// 18
    E_SMAC_PIB_ATTR_BEACONREQUESTLQITHRESHOLD,		// 19
    E_SMAC_PIB_ATTR_MAX_CONCURRENT_ASSOC_RESPONSES,	// 20
    E_SMAC_PIB_ATTR_EXTADDR,						// 21
    E_SMAC_PIB_ATTR_RX_IN_CCA,						// 22
    E_SMAC_PIB_ATTR_EBSN,							// 23
    E_SMAC_PIB_ATTR_EB_FILTERING_ENABLE,			// 24
    E_SMAC_PIB_ATTR_EBREQUEST_PAYLOAD,				// 24
    E_SMAC_PIB_ATTR_EBREQUEST_PAYLOAD_LENGTH,		// 26
    E_SMAC_PIB_ATTR_DUTY_CYCLE_MEAS,				// 27
    E_SMAC_PIB_ATTR_OVERWRITE_TX_POWER_IE,			// 28
    E_SMAC_PIB_ATTR_DUTY_CYCLE_MODE,				// 29
    E_SMAC_PIB_ATTR_MIBIEEE_EXPIRY,					// 30
    E_SMAC_PIB_ATTR_DUTY_CYCLE_REGULATED, 			// 31
    E_SMAC_PIB_ATTR_DUTY_CYCLE_WARNING_THRESHOLD, 	// 32
    E_SMAC_PIB_ATTR_DUTY_CYCLE_CRITICAL_THRESHOLD,	// 33
    E_SMAC_PIB_ATTR_LBT_ENABLE, 					// 34
    E_SMAC_PIB_ATTR_VS_OUI,                         // 35
    E_SMAC_PIB_ATTR_PROTOCOL_INFO,					// 36
    E_SMAC_PIB_NUM_ATTRIBS

}SMAC_PibAttr_e;

typedef enum
{
	E_SMAC_PIB_SUCCESS = 0,
	E_SMAC_PIB_ERROR,
	E_SMAC_PIB_INVALID_PARAMETER,
	E_SMAC_PIB_UNSUPPORTED_ATTRIBUTE,

} SMAC_PibEnum_e;





typedef  void (*PR_RELEASE_BUFFER)(MAC_DcfmIndHdr_s *);


/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void vSMAC_OnTx(bool bOn);
PUBLIC void vSMAC_OnRx(bool bOn);
PUBLIC void vSMAC_Heartbeat(void);
PUBLIC void DEBUG_ASSERT(uint32 u32Exp, string szDbgMsg);
PUBLIC void DEBUG_TRACE(string szDbgMsg);


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* SMAC_COMMON_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

