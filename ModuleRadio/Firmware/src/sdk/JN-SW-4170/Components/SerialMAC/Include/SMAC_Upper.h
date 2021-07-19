/****************************************************************************
 *
 * MODULE:			SMAC_Upper.h
 *
 * COMPONENT:       SerialMAC
 *
 * REVISION:     	$Revision: 82027 $
 *
 * DATED:			$Date: 2016-08-03 08:27:45 +0100 (Wed, 03 Aug 2016) $
 *
 * AUTHOR:   		$Author: nxp71769 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_Upper.h $
 *
 * DESCRIPTION:		Implements the Serial MAC Upper Layer (Host Side) interface
 * 					as defined in 802.15.4 MAC Serial Interface V1.0 [doc142933]
 *					This provides the standard MAC API to the user while encapsulating
 *					the Remote Process Calls across the serial link to the Serial
 *					MAC Lower Layer (MAC Side) interface.
 *
 * $Id: SMAC_Upper.h 82027 2016-08-03 07:27:45Z nxp71769 $
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

#ifndef  SMAC_UPPER_H_INCLUDED
#define  SMAC_UPPER_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include "AppApi.h"
#include "mac_sap.h"
#include "SMAC_Common.h"
#include "SMAC_Stats.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/



/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/


/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/



/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/* APP API */
PUBLIC void 	vSMU_SetChannel(uint8 u8Channel);

PUBLIC uint32 	u32SMU_ApiInit(	PR_GET_BUFFER prMlmeGetBuffer,
								PR_POST_CALLBACK prMlmeCallback,
								void* pvMlmeParam,
								PR_GET_BUFFER prMcpsGetBuffer,
								PR_POST_CALLBACK prMcpsCallback,
								void* pvMcpsParam);
PUBLIC bool 	bSMU_ApiRun(void);

PUBLIC bool 	bSMU_ApiSync(void);

PUBLIC void 	vSMU_ApiErrorCallback(SMAC_API_ERROR_CALLBACK prCallback);


PUBLIC bool 	bSMU_ApiGetMACStatus(SMAC_Status_s *psSMUStatus,
								 SMAC_Status_s *psSMLStatus);

PUBLIC bool 	bSMU_ApiSleep(uint8 u8Mode, uint32 u32DurationMs);

PUBLIC bool 	bSMU_EnterProgrammingMode(void);

PUBLIC void 	vSMU_ApiMlmeRequest(MAC_MlmeReqRsp_s *psMlmeReqRsp,
                   	   	   	    MAC_MlmeSyncCfm_s *psMlmeSyncCfm);

PUBLIC void 	vSMU_ApiMcpsRequest(MAC_McpsReqRsp_s *psMcpsReqRsp,
                   	   	   	   	MAC_McpsSyncCfm_s *psMcpsSyncCfm);


PUBLIC void 			vSMU_ApiSetSecurityMode(MAC_SecutityMode_e eSecurityMode);
PUBLIC void 			vSMU_ApiSetHighPowerMode(uint8 u8ModuleID, bool_t bMode);
PUBLIC void  			vSMU_AppApiSaveMacSettings(void);

PUBLIC void 			vSMU_ApiRestoreMacSettings(void);
PUBLIC bool_t 			bSMU_AppApi_CurrentlyScanning(void);
PUBLIC void 			vSMU_MAC_vPibSetPromiscuousMode(void *pvMac, bool_t bNewState, bool_t bInReset);

/* PLME Accessors */
PUBLIC PHY_Enum_e 		eSMU_AppApiPlmeSet(PHY_PibAttr_e ePhyPibAttribute,
                                 uint32 u32PhyPibValue);
PUBLIC PHY_Enum_e 		eSMU_AppApiPlmeGet(PHY_PibAttr_e ePhyPibAttribute,
                                 uint32 *pu32PhyPibValue);

/* MAC PIB Accessors */
PUBLIC SMAC_PibEnum_e 	eSMU_AppApiMlmeSet(SMAC_PibAttr_e eMacPibAttribute, void* pvMacPibData, uint8 u8Len);
PUBLIC SMAC_PibEnum_e 	eSMU_AppApiMlmeGet(SMAC_PibAttr_e eMacPibAttribute, void* pvMacPibData, uint8* pu8Len);

/* MAC PIB Helpers */
PUBLIC SMAC_PibEnum_e 	eSMU_AppApiMlmeSetU8(SMAC_PibAttr_e eMacPibAttribute, uint8 u8Val);
PUBLIC SMAC_PibEnum_e 	eSMU_AppApiMlmeSetU16(SMAC_PibAttr_e eMacPibAttribute, uint16 u16Val);
PUBLIC SMAC_PibEnum_e 	eSMU_AppApiMlmeSetU32(SMAC_PibAttr_e eMacPibAttribute, uint32 u32Val);

PUBLIC uint8 			u8SMU_AppApiMlmeGetU8(SMAC_PibAttr_e eMacPibAttribute);
PUBLIC uint16 			u16SMU_AppApiMlmeGetU16(SMAC_PibAttr_e eMacPibAttribute);
PUBLIC uint32 			u32SMU_AppApiMlmeGetU32(SMAC_PibAttr_e eMacPibAttribute);

PUBLIC uint8			u8SMU_ApiTXPowerSet(MAC_ExtAddr_s *psExtAddr, MAC_TxPower_s *psMacTxPower);
PUBLIC uint8 			u8SMU_ApiTXPowerGet(MAC_ExtAddr_s *psExtAddr, MAC_TxPower_s *psMacTxPower);
PUBLIC uint8 			u8SMU_ApiTXPowerDelete(MAC_ExtAddr_s *psExtAddr);
PUBLIC uint8			u8SMU_ApiTXPowerSetTable(const MAC_TxPowerTableEntry *psEntries, uint8 u8Index, uint8 u8NumEntries);
PUBLIC uint8 			u8SMU_ApiTXPowerGetTable(MAC_TxPowerTableEntry *psEntries, uint8 u8Index, uint8 u8NumEntries);
PUBLIC uint8 			u8SMU_ApiTXPowerClearTable(void);


PUBLIC uint8			u8SMU_ApiMibIeeeSetPolicy(uint8 u8Policy);
PUBLIC uint8			u8SMU_ApiMibIeeeGetPolicy(uint8 *pu8Policy);
PUBLIC uint8			u8SMU_ApiMibIeeeGetCount(uint8 *pu8Count);
PUBLIC uint8			u8SMU_ApiMibIeeeAddDevice(uint64 u64Address, uint8* pu8Count);
PUBLIC uint8			u8SMU_ApiMibIeeeSetTable(uint8 u8Index, uint8 u8Count, uint64 *pu64Address);
PUBLIC uint8			u8SMU_ApiMibIeeeGetTable(uint8 u8Index, uint8 u8Count, uint64 *pu64Address);
PUBLIC SMAC_PibEnum_e   eSMU_ApiMacPibGetProtoInfo(SMAC_PibAttr_e eMacPibAttribute, void* pvMacPibData, uint8* pu8Len);

PUBLIC void				vSMU_ApiResetSerialStats(void);
PUBLIC void				vSMU_ApiGetSerialStats(SMAC_Stats_s *psStats);




#if defined __cplusplus
}
#endif

#endif  /* SMAC_UPPER_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

