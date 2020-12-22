/****************************************************************************
 *
 * MODULE:             MAC Configuration File
 *
 * DESCRIPTION:
 * Sets the compile-time options for the various builds of the 802.15.4
 * stack.
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

#ifndef _mac_config_h_
#define _mac_config_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/
/************************/
/**** MACROS/DEFINES ****/
/************************/

/* Stack configuration options:
 * ENABLE_OPT_IN_MAKE                  If undefined, this file defines a
 *                                     default set of features
 * ENABLE_OPT_FFD                      Configures a default set of features for
 *                                     an FFD
 * ENABLE_OPT_RFD                      Configures a default set of features for
 *                                     an RFD
 * ENABLE_OPT_COORD                    Enables coordinator functionality
 * ENABLE_OPT_DEVICE                   Enables device sync & superframe
 *                                     capability
 * ENABLE_OPT_MLME_GTS_COORD           Enables GTS functionality for a
 *                                     coordinator
 * ENABLE_OPT_MLME_GTS_DEVICE          Enables GTS functionality for a device
 * ENABLE_OPT_MCPS_PURGE               Enables MPCS-Purge Request and Confirm
 * ENABLE_OPT_MLME_ASSOCIATE           Enables MLME-Associate Indication and
 *                                     Response (Request and Confirm are always
 *                                     enabled)
 * ENABLE_OPT_PROMISCUOUS              Enables promiscuous mode support
 * ENABLE_OPT_ED_SCAN                  Enables energy detection scan
 * ENABLE_OPT_ACTIVE_SCAN              Enables active scan
 * ENABLE_OPT_RXENABLE                 Enables RX enable functionality
 * REDUCED_ZIGBEE_MAC_BUILD            Disables regular beacons, security, Low
 *                                     Power Beacon tracking
 * ENABLE_OPT_REGULAR_BEACONS          Enables regular beacons
 * ENABLE_OPT_SECURITY                 Enables security features
 * ENABLE_LP_BEACON_TRACK              Enable Low Power Beacon tracking
 * ENABLE_OPT_MLME_ENABLE_DISASSOCIATE Enables MLME-Dissociate Indication and
 *                                     Response
 */

#ifndef ENABLE_OPT_IN_MAKE
 #define ENABLE_OPT_COORD           /* Enables coordinator functionality */
 #define ENABLE_OPT_DEVICE          /* Enables device sync & superframe capability */
 #define ENABLE_OPT_MCPS_PURGE      /* Enables MPCS-Purge Request and Confirm */
 #define ENABLE_OPT_MLME_ASSOCIATE  /* Enables MLME-Associate Indication and Response (Request and Confirm are always enabled) */
 #define ENABLE_OPT_PROMISCUOUS     /* Enables promiscuous mode */
 #define ENABLE_OPT_ED_SCAN         /* Enables energy detection scan */
 #define ENABLE_OPT_ACTIVE_SCAN     /* Enables active scan */
 #define ENABLE_OPT_RXENABLE        /* Enables RX enable functionality */
 #ifndef REDUCED_ZIGBEE_MAC_BUILD
  #define ENABLE_OPT_REGULAR_BEACONS /* Enables regular beacons */
  #define ENABLE_OPT_SECURITY        /* Enables security features */
  #define ENABLE_LP_BEACON_TRACK     /* Enable Low Power Beacon tracking*/
 #endif
#else
 #ifdef ENABLE_OPT_FFD
  /* Set options for FFD */
  #define ENABLE_OPT_COORD
  #define ENABLE_OPT_DEVICE
  #define ENABLE_OPT_MCPS_PURGE
  #define ENABLE_OPT_MLME_ASSOCIATE
  #define ENABLE_OPT_PROMISCUOUS
  #define ENABLE_OPT_ED_SCAN
  #define ENABLE_OPT_ACTIVE_SCAN
  #define ENABLE_OPT_RXENABLE
  #define ENABLE_OPT_ORPHAN_SCAN
  #ifndef REDUCED_ZIGBEE_MAC_BUILD
   #define ENABLE_OPT_SECURITY
   #define ENABLE_OPT_MLME_ENABLE_DISASSOCIATE
  #endif
 #endif
 #ifdef ENABLE_OPT_RFD
  /* Set options for RFD */
  #define ENABLE_OPT_ACTIVE_SCAN
  #define ENABLE_OPT_DEVICE
  #define ENABLE_OPT_RXENABLE
  #define ENABLE_OPT_ORPHAN_SCAN
  #ifndef REDUCED_ZIGBEE_MAC_BUILD
   #define ENABLE_OPT_SECURITY
   #define ENABLE_OPT_MLME_ENABLE_DISASSOCIATE
  #endif
 #endif
#endif

#ifdef ENABLE_OPT_SECURITY

#ifdef EMBEDDED
/** Maximum number of ACL entries */
#ifdef ENABLE_OPT_COORD
#define MAC_MAX_ACL_ENTRIES             16
#else
#define MAC_MAX_ACL_ENTRIES             2
#endif
#else /* !EMBEDDED */
/** Maximum number of ACL entries */
#define MAC_MAX_ACL_ENTRIES             255
#endif /* !EMBEDDED */

#if (MAC_MAX_ACL_ENTRIES > 16)
#define USE_HASH_TABLE_LOOKUP
#if (MAC_MAX_ACL_ENTRIES <= 127)
#define USE_SMALL_HASH_TABLE_LOOKUP
#endif
#endif

#else /* !ENABLE_OPT_SECURITY */

/* Need to keep one entry - not sure why at the moment */
#define MAC_MAX_ACL_ENTRIES             1

#endif /* !ENABLE_OPT_SECURITY */

/* Even with neither ENABLE_OPT_COORD or ENABLE_OPT_DEVICE enabled it is possible to
   send and receive frames on an ad-hoc basis using unslotted CSMA.
   An FFD will have all options defined, except some of the security options. An RFD
   may optionally undefine any or all options except ENABLE_OPT_DEVICE and
   ENABLE_OPT_SECURITY whilst remaining within the specification.
   ENABLE_OPT_DEVICE and ENABLE_OPT_SECURITY reduce the functionality below that of the
   specification but are still useful low-memory modes
 */

/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/

/****************************/
/**** EXPORTED VARIABLES ****/
/****************************/

/****************************/
/**** EXPORTED FUNCTIONS ****/
/****************************/

#ifdef __cplusplus
};
#endif

#endif /* _mac_config_h_ */

/* End of file $RCSfile: mac_config.h,v $ *******************************************/
