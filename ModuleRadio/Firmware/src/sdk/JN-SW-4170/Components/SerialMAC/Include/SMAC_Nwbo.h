/****************************************************************************
 *
 * MODULE:			SMAC_Nwbo.h
 *
 * COMPONENT:       SerialMAC
 *
 * REVISION:     	$Revision: 90052 $
 *
 * DATED:			$Date: 2017-08-31 14:09:02 +0100 (Thu, 31 Aug 2017) $
 *
 * AUTHOR:   		$Author: nxp29741 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_Nwbo.h $
 *
 * DESCRIPTION:		Implements the conversion to/from Network Byte order / MAC Structs for the
 * 					Serial MAC as defined in 802.15.4 MAC Serial Interface 
 *
 * $Id: SMAC_Nwbo.h 90052 2017-08-31 13:09:02Z nxp29741 $
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


#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <mac_sap.h>
#include <mac_pib.h>
#include "smac_common.h"

#ifndef  SMAC_NWBO_H_INCLUDED
#define  SMAC_NWBO_H_INCLUDED





/****************************************************************************/
/***        Network Byte Order                                            ***/
/****************************************************************************/
/* The Network Byte order is a method for converting the various MAC structs
 * into a byte stream. The format is type, length and params which 
 * corresponds to MAC_ReqRspHdr_s
 *
 *
 * Byte    Description
 * -------------------
 * 0       Type                 Request/Response type
 * 1       Param Length         Parameter length
 * 2-255   Params               Variable length of Parameters
 */


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
* GENERAL CONVERSIONS
****************************************************************************/
PUBLIC uint8 u8ToNWBO_uint64(uint64 u64Value, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_uint64(uint64 * const pu64Value, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_uint32(uint32 u32Value, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_uint32(uint32 * const pu32Value, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_uint16(uint16 u16Value, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_uint16(uint16 * const pu16Value, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_uint8(uint8 u8Value, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_uint8(uint8 * const pu8Value, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_au8(const uint8 *pau8Array, uint8 *pu8Data, uint8 u8Length);
PUBLIC uint8 u8FromNWBO_au8(uint8 *pau8Array, const uint8 *pu8Data, uint8 u8Length);
PUBLIC uint8 u8ToNWBO_MAC_ExtAddr_s(const MAC_ExtAddr_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_ExtAddr_s(MAC_ExtAddr_s *ps, const uint8 *pu8Data);


/****************************************************************************
* MLME / MCPS STRUCT CONVERSIONS
****************************************************************************/
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqRsp_s(const MAC_MlmeReqRsp_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqRsp_s(MAC_MlmeReqRsp_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeDcfmInd_s(const MAC_MlmeDcfmInd_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeDcfmInd_s(MAC_MlmeDcfmInd_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeSyncCfm_s(uint8 u8Type, const MAC_MlmeSyncCfm_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeSyncCfm_s(uint8 u8Type, MAC_MlmeSyncCfm_s *ps, const uint8 *pu8Data);

PUBLIC uint8 u8ToNWBO_MAC_McpsReqRsp_s(const MAC_McpsReqRsp_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_McpsReqRsp_s(MAC_McpsReqRsp_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_McpsDcfmInd_s(const MAC_McpsDcfmInd_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_McpsDcfmInd_s(MAC_McpsDcfmInd_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_McpsSyncCfm_s(uint8 u8Type, const MAC_McpsSyncCfm_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_McpsSyncCfm_s(uint8 u8Type, MAC_McpsSyncCfm_s *ps, const uint8 *pu8Data);

/****************************************************************************
* MLME REQ/RSP STRUCT CONVERSIONS
****************************************************************************/
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqAssociate_s(const MAC_MlmeReqAssociate_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqAssociate_s(MAC_MlmeReqAssociate_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqDisassociate_s(const MAC_MlmeReqDisassociate_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqDisassociate_s(MAC_MlmeReqDisassociate_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqGet_s(const  MAC_MlmeReqGet_s*ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqGet_s(MAC_MlmeReqGet_s *ps, const uint8 *pu8Data);

#ifdef SERIALMAC_FULL_MAC
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqGts_s(const  MAC_MlmeReqGts_s*ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqGts_s(MAC_MlmeReqGts_s *ps, const uint8 *pu8Data);
#endif

PUBLIC uint8 u8ToNWBO_MAC_MlmeReqReset_s(const MAC_MlmeReqReset_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqReset_s(MAC_MlmeReqReset_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqRxEnable_s(const  MAC_MlmeReqRxEnable_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqRxEnable_s(MAC_MlmeReqRxEnable_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqScan_s(const MAC_MlmeReqScan_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqScan_s(MAC_MlmeReqScan_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqSet_s(const MAC_MlmeReqSet_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqSet_s(MAC_MlmeReqSet_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqStart_s(const  MAC_MlmeReqStart_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqStart_s(MAC_MlmeReqStart_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqSync_s(const MAC_MlmeReqSync_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqSync_s(MAC_MlmeReqSync_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqPoll_s(const  MAC_MlmeReqPoll_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqPoll_s(MAC_MlmeReqPoll_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeReqVsExtAddr_s(const MAC_MlmeReqVsExtAddr_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeReqVsExtAddr_s(MAC_MlmeReqVsExtAddr_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeRspAssociate_s(const  MAC_MlmeRspAssociate_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeRspAssociate_s(MAC_MlmeRspAssociate_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeRspOrphan_s(const  MAC_MlmeRspOrphan_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeRspOrphan_s(MAC_MlmeRspOrphan_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeIndDutyCycleMode_s(const MAC_MlmeIndDutyCycleMode_s* ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeIndDutyCycleMode_s(MAC_MlmeIndDutyCycleMode_s* ps, const uint8 *pu8Data);

/****************************************************************************
* MLME CFM STRUCT CONVERSIONS
****************************************************************************/
PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmAssociate_s(const  MAC_MlmeCfmAssociate_s*ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmAssociate_s(MAC_MlmeCfmAssociate_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmDisassociate_s(const  MAC_MlmeCfmDisassociate_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmDisassociate_s(MAC_MlmeCfmDisassociate_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmGet_s(const  MAC_MlmeCfmGet_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmGet_s(MAC_MlmeCfmGet_s *ps, const uint8 *pu8Data);
#ifdef SERIALMAC_FULL_MAC
PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmGts_s(const  MAC_MlmeCfmGts_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmGts_s(MAC_MlmeCfmGts_s *ps, const uint8 *pu8Data);
#endif

PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmScan_s(const MAC_MlmeCfmScan_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmScan_s(MAC_MlmeCfmScan_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmSet_s(const  MAC_MlmeCfmSet_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmSet_s(MAC_MlmeCfmSet_s *ps, const uint8 *pu8Data); 
PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmStart_s(const  MAC_MlmeCfmStart_s *ps, uint8 *pu8Data); 
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmStart_s(MAC_MlmeCfmStart_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmPoll_s(const  MAC_MlmeCfmPoll_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmPoll_s(MAC_MlmeCfmPoll_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmReset_s(const  MAC_MlmeCfmReset_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmReset_s(MAC_MlmeCfmReset_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeCfmRxEnable_s(const  MAC_MlmeCfmRxEnable_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeCfmRxEnable_s(MAC_MlmeCfmRxEnable_s *ps, const uint8 *pu8Data); 

/****************************************************************************
* MLME IND/DCFM STRUCT CONVERSIONS
****************************************************************************/
PUBLIC uint8 u8ToNWBO_MAC_MlmeIndAssociate_s(const  MAC_MlmeIndAssociate_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeIndAssociate_s(MAC_MlmeIndAssociate_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeIndDisassociate_s(const  MAC_MlmeIndDisassociate_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeIndDisassociate_s(MAC_MlmeIndDisassociate_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeIndGts_s(const  MAC_MlmeIndGts_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeIndGts_s(MAC_MlmeIndGts_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeIndBeacon_s(const  MAC_MlmeIndBeacon_s*ps, uint8 *pu8Data); 
PUBLIC uint8 u8FromNWBO_MAC_MlmeIndBeacon_s(MAC_MlmeIndBeacon_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeIndSyncLoss_s(const MAC_MlmeIndSyncLoss_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeIndSyncLoss_s(MAC_MlmeIndSyncLoss_s*ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeIndCommStatus_s(const MAC_MlmeIndCommStatus_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeIndCommStatus_s(MAC_MlmeIndCommStatus_s*ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeIndOrphan_s(const MAC_MlmeIndOrphan_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeIndOrphan_s(MAC_MlmeIndOrphan_s*ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_MlmeIndUnRecnDataReq_s (const MAC_MlmeIndUnRecnDataReq_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_MlmeIndUnRecnDataReq_s(MAC_MlmeIndUnRecnDataReq_s *ps, const uint8 *pu8Data);

/****************************************************************************
* MCPS REQ/RSP STRUCT CONVERSIONS
****************************************************************************/
PUBLIC uint8 u8ToNWBO_MAC_McpsReqData_s(const MAC_McpsReqData_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_McpsReqData_s(MAC_McpsReqData_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_McpsReqPurge_s(const MAC_McpsReqPurge_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_McpsReqPurge_s(MAC_McpsReqPurge_s *ps, const uint8 *pu8Data);


/****************************************************************************
* MCPS CFM STRUCT CONVERSIONS
****************************************************************************/
PUBLIC uint8 u8ToNWBO_MAC_McpsCfmData_s(const MAC_McpsCfmData_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_McpsCfmData_s(MAC_McpsCfmData_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_McpsSyncCfmData_s(const MAC_McpsCfmData_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_McpsSyncCfmData_s(MAC_McpsCfmData_s *ps, const uint8 *pu8Data);
PUBLIC uint8 u8ToNWBO_MAC_McpsCfmPurge_s(const MAC_McpsCfmPurge_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_McpsCfmPurge_s(MAC_McpsCfmPurge_s *ps, const uint8 *pu8Data);

/****************************************************************************
* MCPS IND STRUCT CONVERSIONS
****************************************************************************/
PUBLIC uint8 u8ToNWBO_MAC_McpsIndData_s(const MAC_McpsIndData_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_McpsIndData_s(MAC_McpsIndData_s *ps, const uint8 *pu8Data);


/****************************************************************************
* MAC TX POWER CONVERSIONS
****************************************************************************/
PUBLIC uint8 u8ToNWBO_MAC_TxPower_s(const MAC_TxPower_s *ps, uint8 *pu8Data);
PUBLIC uint8 u8FromNWBO_MAC_TxPower_s(MAC_TxPower_s *ps, const uint8 *pu8Data);


#if defined __cplusplus
}
#endif

#endif  /* SMAC_NWBO_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
