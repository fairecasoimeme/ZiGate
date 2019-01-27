/****************************************************************************
 *
 * MODULE:             ZED-MAC
 *
 * DESCRIPTION:
 * ZED 802.15.4 Media Access Controller
 * SAP interface for MLME and MCPS
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

/**
 * @defgroup g_mac_sap MAC layer Service Access Point (SAP)
 */

/**
 * @defgroup g_mac_sap_pib PIB parameters
 *
 * Parameters associated with setting or getting PIB values
 * @ingroup g_mac_sap
 */

/**
 * @defgroup g_mac_sap_addr Addressing parameters
 *
 * Parameters associated with addressing
 * @ingroup g_mac_sap
 */

/**
 * @defgroup g_mac_sap_pdu PDU Framing parameters
 *
 * Parameters associated with PDU framing
 * @ingroup g_mac_sap
 */

/**
 * @defgroup g_mac_sap_sec Security parameters
 *
 * Parameters associated with security
 * @ingroup g_mac_sap
 */

/**
 * @defgroup g_mac_sap_scan Scanning parameters
 *
 * Parameters associated with scanning
 * @ingroup g_mac_sap
 */

/**
 * @defgroup g_mac_sap_bcn Beacon parameters
 *
 * Parameters associated with beaconing
 * @ingroup g_mac_sap
 */

/**
 * @defgroup g_mac_sap_mlme MAC SAP sublayer management entity (MLME)
 *
 * The MLME SAP API provides calls to conforming to the MLME SAP in [1]
 * @ingroup g_mac_sap
 */

/**
 * @defgroup g_mac_sap_mcps MAC SAP common part sublayer (MCPS)
 *
 * The MCPS SAP API provides calls to conforming to the MCPS SAP in [1]
 * @ingroup g_mac_sap
 */

/**
 * @defgroup g_mac_sap_vs Vendor-specific interface
 *
 * The vendor-specific SAP API provides calls which are in addition to those specified in the 802.15.4
 * specification. They are currently handled as additions to the MLME SAP interface.
 * @ingroup g_mac_sap
 */

/**
 * @mainpage Medium Access Control Layer Service Access Point Application Programmer's Interface
 *
 * @section p_mac_sap_intro Introduction
 * The Medium Access Control (MAC) Layer Service Access Point (SAP) Application Programmer's Interface (API)
 * provides the interface to the top of the MAC layer required by higher layer in the application programming.
 * The next layer up is typically the network layer.
 *
 * @section p_mac_sap_app Application interface
 * There is an Application interface which sits on top of the MAC SAP. It wraps the
 * initialisation and baseband interrupt handling, and provides a simple call/callback API
 * for access to the MAC SAP.
 *
 * See @link g_app_sap Application interface@endlink
 *
 * @section p_mac_sap_categories Categories within MAC SAP
 * - MCPS SAP API: See @link g_mac_sap_mcps MCPS SAP pages@endlink
 * - MLME SAP API: See @link g_mac_sap_mlme MLME SAP pages@endlink
 * - Vendor-specific SAP API: See @link g_mac_sap_vs Vendor-specific pages@endlink
 * - MAC PIB Direct Access: See @link g_mac_pib PIB direct access pages@endlink
 *
 * @section p_disclaimer Disclaimer
 * This document is subject to change. Please contact NXP for more information
 */

#ifndef _mac_sap_minimac_h_
#define _mac_sap_minimac_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/

#include "jendefs.h"
#include "MiniMac.h"

/************************/
/**** MACROS/DEFINES ****/
/************************/

/* Literals */

/**
 * @name PHY constants
 * @ingroup g_mac_sap
 * PHY constants 'used' by the MAC
 * @{
 */
/** Maximum PHY packet (PDU) size */
#define MAC_MAX_PHY_PKT_SIZE            127
/** PHY turnaround time */
#define MAC_PHY_TURNAROUND_TIME         12
/* @} */

/**
 * @name Address sizes
 * @ingroup g_mac_sap_addr
 * Sizes of address fields in SAP structures
 * @{
 */
/** PAN ID field size in octets */
#define MAC_PAN_ID_LEN                  2
/** Short address field size in octets */
#define MAC_SHORT_ADDR_LEN              2
/** Extended address field size in octets */
#define MAC_EXT_ADDR_LEN                8
/** Extended address field size in words (32 bit) */
#define MAC_EXT_ADDR_LEN_WORDS          2
/* @} */

/**
 * @name Frame overheads
 * @ingroup g_mac_sap_pdu
 * Header size overheads for frames
 * @{
 */
/** Minimum Data Frame overhead */
#define MAC_MIN_DATA_FRM_OVERHEAD       9
/** Maximum Data Frame overhead */
#define MAC_MAX_DATA_FRM_OVERHEAD       25
/** Minimum Beacon Frame overhead */
#define MAC_MIN_BEACON_FRM_OVERHEAD     9
/** Maximum Beacon Frame overhead */
#define MAC_MAX_BEACON_FRM_OVERHEAD     15
/* @} */

/**
 * @name Payload maxima
 * @ingroup g_mac_sap_pdu
 * Maximum size of payloads
 * @{
 */
/** Maximum Data Frame payload */
#define MAC_MAX_DATA_PAYLOAD_LEN      (MAC_MAX_PHY_PKT_SIZE - MAC_MIN_DATA_FRM_OVERHEAD)
/** Maximum Beacon Frame payload */
#define MAC_MAX_BEACON_PAYLOAD_LEN    (MAC_MAX_PHY_PKT_SIZE - MAC_MIN_BEACON_FRM_OVERHEAD)
/* @} */

/**
 * @name PIB constants
 * @ingroup g_mac_sap_pib
 * PIB constant values
 * @{
 */
/** @a aNumSuperframeSlots: Maximum number of superframe slots */
#define MAC_NUM_SUPERFRAME_SLOTS        16
/** @a aMaxBeaconOverhead: Maximum beacon overhead */
#define MAC_MAX_BEACON_OVERHEAD         75
/** @a aBaseSlotDuration */
#define MAC_BASE_SLOT_DURATION          60
/** @a aBaseSuperframeDuration */
#define MAC_BASE_SUPERFRAME_DURATION    (MAC_BASE_SLOT_DURATION * MAC_NUM_SUPERFRAME_SLOTS)
/** @a aResponseWaitTime */
#define MAC_RESPONSE_WAIT_TIME          (32 * MAC_BASE_SUPERFRAME_DURATION)
/** @a aMinLIFSPeriod: Minimum number of symbols in a LIFS period */
#define MAC_MIN_LIFS_PERIOD             40
/** @a aMinSIFSPeriod: Minimum number of symbols in a SIFS period */
#define MAC_MIN_SIFS_PERIOD             12
/** @a aMinCAPLength: Minimum CAP length */
#define MAC_MIN_CAP_LENGTH              440
/** @a aMaxFrameResponseTime: Maximum frame response time */
#define MAC_MAX_FRAME_RESPONSE_TIME     1220
/** @a aUnitBackoffPeriod: Number of symbols for CSMA/CA backoff */
#define MAC_UNIT_BACKOFF_PERIOD         20
/** @a aMaxFrameRetries: Maximum number of CSMA/CA retries */
#define MAC_MAX_FRAME_RETRIES           3
/** @a aMaxLostBeacons: Maximum number of lost beacons before sync loss */
#define MAC_MAX_LOST_BEACONS            4
/** @a aGTSDescPersistenceTime: How many beacons a GTS descriptor persists for */
#define MAC_GTS_DESC_PERSISTENCE_TIME   4

/*2006 additions*/
/** @a aMinMPDUOverhead: Min number of octets added by the MAC sublayer to the PDSU */
#define MAC_MIN_MPDU_OVERHEAD              9
/** @a aMaxMACPayloadSize: Max number of octets that can be transmitted in the mac payload field */
#define MAC_MAX_PAYLOAD_SIZE               (MAC_MAX_PHY_PKT_SIZE-MAC_MIN_MPDU_OVERHEAD)
/** @a aMaxMPDUUnsecuredOverhead: Max number of octets added by the MAC sublayer to the PDSU without security */
#define MAC_MAX_MPDU_UNSECURED_OVERHEAD    25
/** @a aMaxMacSafePayloadSize: Max number of octets that can be transmitted in the MAC payload field
of an unsecured MAC frame that will be guaranteed not to exceed aMaxPHYPacketSize */
#define MAC_MAX_SAFE_PAYLOAD_SIZE          (MAC_MAX_PHY_PKT_SIZE-MAC_MAX_MPDU_UNSECURED_OVERHEAD)
/* @} */

/* Map old structures onto new ones: code will have to be rebuilt to use new
   structures, hopefully without mishaps */
typedef tsMcpsGeneric   MAC_McpsDcfmInd_s;
typedef tsMlmeGeneric   MAC_MlmeDcfmInd_s;
typedef tsFullAddr      MAC_Addr_s;
typedef tsExtAddr       MAC_ExtAddr_s;
typedef tuAddr          MAC_Addr_u;
typedef tsRxFrameFormat MAC_RxFrameData_s;
typedef tsSecurity      MAC_SecurityData_s;
typedef teMacStatus     MAC_MlmeSyncCfmStatus_e;
typedef tsPanDescriptor MAC_PanDescr_s;
typedef union
{
    tsMcpsGeneric sMcps;
    tsMlmeGeneric sMlme;
} MAC_DcfmIndHdr_s;
typedef tsMiniMacDeviceDescriptor MAC_DeviceDescriptor_s;

#ifdef __cplusplus
};
#endif

#endif /* _mac_sap_minimac_h_ */

/* End of file $RCSfile: mac_sap.h,v $ *******************************************/
