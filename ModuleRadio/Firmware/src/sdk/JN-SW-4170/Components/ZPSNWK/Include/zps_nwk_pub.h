/*****************************************************************************
 *
 * MODULE:             ZPS NWK
 *
 * COMPONENT:          zps_nwk_pub.h
 *
 * AUTHOR:             RCC
 *
 * DESCRIPTION:        ZPS NWK Public exported API
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Zigbee%20Protocol%20Stack/Modules/NWK/Trunk/Include/zps_nwk_pub.h $
 *
 * $Revision: 90751 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2017-10-25 15:39:45 +0100 (Wed, 25 Oct 2017) $
 *
 * $Id: zps_nwk_pub.h 90751 2017-10-25 14:39:45Z nxp29741 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
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
 * Copyright NXP B.V. 2016. All rights reserved
 *
 ****************************************************************************/

/**
 * @defgroup g_zps_nwk ZPS Network Layer infrastructure
 */

#ifndef _zps_nwk_pub_h_
#define _zps_nwk_pub_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/
#include "jendefs.h"
#include "zps_nwk_config.h"
#include "zps_nwk_sap.h"

/************************/
/**** MACROS/DEFINES ****/
/************************/

/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/

/**
 * Device type.
 * What sort of device we are
 * @ingroup g_zps_nwk
 */
typedef enum
{
    ZPS_NWK_DT_UNKNOWN,
    ZPS_NWK_DT_COORDINATOR,
    ZPS_NWK_DT_ROUTER,
    ZPS_NWK_DT_END_DEVICE,
    NUM_ZPS_NWK_DT
} ZPS_teNwkDeviceType;



typedef enum ZPS_teExtendedStatus_tag
{
	ZPS_XS_OK = 0,

	ZPS_XS_E_FATAL,									// 0x01 Errors below are Fatal errors, retrying will cause the error again.
	ZPS_XS_E_LOOPBACK_BAD_ENDPOINT= ZPS_XS_E_FATAL,	// 0x01 The endpoint is not valid for loopback
	ZPS_XS_E_SIMPLE_DESCRIPTOR_NO_OUTPUT_CLUSTER, 	// 0x02 There is no output cluster in the simple descriptor for this endpoint / cluster.
    ZPS_XS_E_FRAG_NEEDS_ACK, 				 		// 0x03 Fragmented data requests must be sent with APS ACK
    ZPS_XS_E_COMMAND_MANAGER_BAD_PARAMETER, 		// 0x04 A bad parameter has been passed to the command manager
	ZPS_XS_E_INVALID_ADDRESS,                 		// 0x05 The address parameter is out of range (e.g. broadcast address when calling unicast API)
    ZPS_XS_E_INVALID_TX_ACK_FOR_LOCAL_EP, 			// 0x06 The TX ACK bit has been set when attempting to post to a local EP


    ZPS_XS_E_RESOURCE = 0x80,			            //  Errors below are due to resource shortage, retrying may succeed
    ZPS_XS_E_NO_FREE_NPDU = 0x80,  		            // 0x80 There are no free Network PDUs.  The number of NPDUs is set in the "Number of NPDUs" property of the "PDU Manager" section of the config editor
    ZPS_XS_E_NO_FREE_APDU = 0x81,  		            // 0x81 There are no free Application PDUs.  The number of APDUs is set in the "Instances" property of the appropriate "APDU" child of the "PDU Manager" section of the config editor
    ZPS_XS_E_NO_FREE_SIM_DATA_REQ,		            // 0x82 There are no free simultaneous data request handles.  The number of handles is set in the "Maximum Number of Simultaneous Data Requests" field of the "APS layer configuration" section of the config editor
    ZPS_XS_E_NO_FREE_APS_ACK,    	 	            // 0x83 There are no free APS acknowledgement handles.  The number of handles is set in the "Maximum Number of Simultaneous Data Requests with Acks" field of the "APS layer configuration" section of the config editor
    ZPS_XS_E_NO_FREE_FRAG_RECORD,		            // 0x84 There are no free fragment record handles.  The number of handles is set in the "Maximum Number of Transmitted Simultaneous Fragmented Messages" field of the "APS layer configuration" section of the config editor
    ZPS_XS_E_NO_FREE_MCPS_REQ,			            // 0x85 There are no free MCPS request descriptors.  There are 8 MCPS request descriptors.  These are only ever likely to be exhausted under very heavy network load or when trying to transmit too many frames too close together.
    ZPS_XS_E_NO_FREE_LOOPBACK,	                    // 0x86 The loop back send is currently busy.  There can be only one loopback request at a time.
    ZPS_XS_E_NO_FREE_EXTENDED_ADDR,		            // 0x87 There are no free entries in the extended address table.  The extended address table is configured in the config editor
    ZPS_XS_E_SIMPLE_DESCRIPTOR_NOT_FOUND, 	        // 0x88 The simple descriptor does not exist for this endpoint / cluster.
    ZPS_XS_E_BAD_PARAM_APSDE_REQ_RSP, 			 	// 0x89 A bad parameter has been found while processing an APSDE request or response
    ZPS_XS_E_NO_RT_ENTRY,                           // 0x8a No free Routing table entries left
    ZPS_XS_E_NO_BTR                                 // 0x8b No free BTR entries left.
} ZPS_teExtendedStatus;

/****************************/
/**** EXPORTED VARIABLES ****/
/****************************/

extern PUBLIC const uint32 ZPS_g_u32NwkVersion;



/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
typedef void (*tpfExtendedStatusCallBack)(ZPS_teExtendedStatus eExtendedStatus);
typedef void (*tpfTimerExpiredCallBack)(void);
typedef void (*tpfAgeEndDeviceCallback)(uint64);
/****************************/
/**** EXPORTED FUNCTIONS ****/
/****************************/

/* Initialise */
PUBLIC ZPS_teNwkEnum
ZPS_pvNwkCtor(void *pvNwk,
              void *pvMac,
              ZPS_teNwkDeviceType eDevType);

PUBLIC void *
ZPS_pvNwkGetHandle(void);
PUBLIC void zps_vLinkStatusSchedule(void *pvNwk, uint64 u64Addr, uint16 u16NwkAddr, uint8 u8Lqi);


PUBLIC bool_t ZPS_vNwkGetPermitJoiningStatus(void *pvNwk);
PUBLIC void ZPS_vSetInterDataInterval(uint32 u32Value);
PUBLIC void ZPS_vRegisterInterPanHandlers(void *pvNwk,void *pfIntPanDataInd, void *pfIntPanDcfm);
PUBLIC void ZPS_vRegistercStubGreenPower(void* pvNwk,void* pfInd, void* pfCfm);
PUBLIC void ZPS_vNwkSetDeviceType(void* pvNwk,ZPS_teNwkDeviceType eNwkDeviceType);
PUBLIC uint8 ZPS_vNwkCheckAndResolveConflict(void* pvNwk,uint16 u16Addr,uint64 u64Addr);
PUBLIC void ZPS_vNwkSaveAllRecords(void *pvNwk);
PUBLIC void ZPS_vExtendedStatusSetCallback(tpfExtendedStatusCallBack pfExtendedStatusCallBack);
PUBLIC void zps_vRegisterCallbackForSecondsTick(tpfTimerExpiredCallBack pfTimerExpiredCallback);
PUBLIC void *ZPS_pvNwkSecGetNetworkKey(void *pvNwk);
PUBLIC void ZPS_vSetOverrideLocalIeeeAddr(uint64 *pu64Address);
PUBLIC void ZPS_vMaxNumberOfBuffersPerChild( uint8 u8MaxBuffers );
PUBLIC void ZPS_vNwkAgeEndDeviceRegisterCallback (void* pvFn);
PUBLIC void ZPS_vNwkSetOneBeaconPerNetwork(bool_t bState);
#ifdef __cplusplus
};
#endif

#endif /* _mac_pub_h_ */

/* End of file $Id: zps_nwk_pub.h 90751 2017-10-25 14:39:45Z nxp29741 $ *******************************************/
