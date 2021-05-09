/*****************************************************************************
 *
 * MODULE:      ZPSAPL
 *
 * COMPONENT:   zps_apl_aib.h
 *
 * AUTHOR:      mwild
 *
 * DESCRIPTION:
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Zigbee%20Protocol%20Stack/Modules/APL/Trunk/Include/zps_apl_aib.h $
 *
 * $Revision: 90533 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2017-10-05 15:24:08 +0100 (Thu, 05 Oct 2017) $
 *
 * $Id: zps_apl_aib.h 90533 2017-10-05 14:24:08Z nxp29741 $
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

#ifndef ZPS_APL_AIB_H_
#define ZPS_APL_AIB_H_

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "zps_nwk_sec.h"
#ifndef ZPS_APL_OPT_MULTIPLE_INSTANCES
#include <zps_apl_zdo.h>
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#ifndef ZPS_AIB_INLINE
#define ZPS_AIB_INLINE  INLINE
#endif

#define ZPS_APL_AIB_MAX_ENDPOINTS   242

#define apsBindingTable             psAplApsmeAibBindingTable
#define apsDesignatedCoordinator    bApsDesignatedCoordinator
#define apsUseExtendedPANID         u64ApsUseExtendedPanid
#define apsGroupTable               psAplApsmeGroupTable
#define apsNonmemberRadius          u8ApsNonMemberRadius
#define apsPermissionsConfiguration /* not implemented */
#define apsUseInsecureJoin          bApsUseInsecureJoin
#define apsInterframeDelay          u8ApsInterframeDelay
#define apsLastChannelEnergy        u8ApsLastChannelEnergy
#define apsLastChannelFailureRate   u8ApsLastChannelFailureRate
#define apsChannelTimer             u8ApsChannelTimer
#define apsDeviceKeyPairTable       psAplDeviceKeyPairTable
#define apsDefaultTCApsLinkKey      psAplDefaultTCApsLinkKey
#define apsTrustCenterAddress       u64ApsTrustCenterAddress
#define apsSecurityTimeoutPeriod    u16ApsSecurityTimeOutPeriod

/* TODO - needs to be a table to support fragmentation */
#define apsMaxWindowSize            u8ApsMaxWindowSize

#define apscMaxDescriptorSize       (64UL)
#define apscMaxFrameRetries         (3UL)
//This for depth 7 #define apscAckWaitDuration         (50000UL)
// Trac #543 Set wait for Ack time for nwk depth of 15
//This for depth 15
#define apscAckWaitDuration         (100000UL)

#define apscMinDuplicateRejectionTableSize (1UL)
#define apscMinHeaderOverhead       (12UL)
#define apscapsParentAnnounceBaseTimer    10  // Usage in seconds
#define apsParentAnnounceJitterMax        10  // Usage in seconds




/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* [I SP001349_sfr 56]  */
typedef struct
{
    uint16  u16Groupid;
    uint8   au8Endpoint[(242 + 7)/8];
}ZPS_tsAplApsmeGroupTableEntry;

typedef struct
{
    ZPS_tsAplApsmeGroupTableEntry *psAplApsmeGroupTableId;
    uint32 u32SizeOfGroupTable;
}ZPS_tsAplApsmeAIBGroupTable;


typedef struct
{
    uint16  u16Groupid;
    uint16  u16BitMap;
}ZPS_tsAPdmGroupTableEntry;

typedef struct
{
	ZPS_tsAPdmGroupTableEntry *psAplApsmeGroupTableId;
    uint32 u32SizeOfGroupTable;
}ZPS_tsPdmGroupTable;

/* [I SP001349_sfr 50,54] */
typedef struct
{
    uint16  u16AddrOrLkUp;
    uint16  u16ClusterId;
    uint8   u8DstAddrMode;
    uint8   u8SourceEndpoint;
    uint8   u8DestinationEndPoint;
}ZPS_tsAplApsmeBindingTableStoreEntry;


typedef struct
{
	ZPS_tsAplApsmeBindingTableStoreEntry* pvAplApsmeBindingTableEntryForSpSrcAddr;
   uint32 u32SizeOfBindingTable;
}ZPS_tsAplApsmeBindingTable;


typedef struct
{
	ZPS_tuAddress  uDstAddress;
    uint16         u16ClusterId;
    uint8          u8DstAddrMode;
    uint8          u8SourceEndpoint;
    uint8          u8DestinationEndPoint;
}ZPS_tsAplApsmeBindingTableEntry;

typedef struct
{
   ZPS_tsAplApsmeBindingTableEntry* pvAplApsmeBindingTableForRemoteSrcAddr;
   uint32 u32SizeOfBindingCache;
   uint64* pu64RemoteDevicesList;
}ZPS_tsAplApsmeBindingTableCache;


typedef struct
{
    ZPS_tsAplApsmeBindingTableCache* psAplApsmeBindingTableCache;
    ZPS_tsAplApsmeBindingTable* psAplApsmeBindingTable;
}ZPS_tsAplApsmeBindingTableType;

typedef struct
{
    uint32 u32OutgoingFrameCounter;
    uint16 u16ExtAddrLkup;
    uint8  au8LinkKey[ZPS_SEC_KEY_LENGTH];
} ZPS_tsAplApsKeyDescriptorEntry;

typedef struct
{
uint16    u16CredOffset;
uint16    u16TclkRetries;
} ZPS_TclkDescriptorEntry;

typedef struct
{
    ZPS_tsAplApsKeyDescriptorEntry *psAplApsKeyDescriptorEntry;
    uint16  u16SizeOfKeyDescriptorTable;
} ZPS_tsAplApsKeyDescriptorTable;


/* [I SP001349_sfr 19]  */
typedef struct
{
    /* persisted to flash */
    uint64  u64ApsTrustCenterAddress;           /* [I SP001379_sr 17, 344] */
    uint64  u64ApsUseExtendedPanid;
    bool_t  bApsDesignatedCoordinator;
    bool_t  bApsUseInsecureJoin;
    bool_t  bDecryptInstallCode;
    uint8   u8KeyType;
    /* volatile */
    uint8   u8ApsNonMemberRadius;
    uint8   u8ApsInterframeDelay;
    uint8   u8ApsLastChannelEnergy;
    uint8   u8ApsLastChannelFailureRate;
    uint8   u8ApsChannelTimer;
    uint8   u8ApsMaxWindowSize;
    ZPS_tsAplApsmeBindingTableType *psAplApsmeAibBindingTable;
    ZPS_tsAplApsmeAIBGroupTable    *psAplApsmeGroupTable;
    ZPS_tsAplApsKeyDescriptorTable  *psAplDeviceKeyPairTable; /* [I SP001379_sr 344] */
    ZPS_tsAplApsKeyDescriptorEntry  *psAplDefaultTCAPSLinkKey;
    bool_t   bParentAnnouncePending;
    bool_t   bUseInstallCode;
    uint16   u16ApsSecurityTimeOutPeriod;        /* [I SP001379_sr 344] */
    uint32   *pu32IncomingFrameCounter;
    uint32 *pau32ApsChannelMask;
} ZPS_tsAplAib;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC ZPS_tsAplAib *zps_psAplAibGetAib(void *);
PUBLIC ZPS_teStatus zps_eAplAibSetApsUseExtendedPanId(void *pvApl, uint64 u64UseExtPanId);
PUBLIC ZPS_teStatus zps_eAplAibSetApsChannelMask(void *pvApl, uint32 u32ChannelMask);
PUBLIC ZPS_teStatus zps_eAplAibSetApsChannelMaskByMacID (void *pvApl, uint16 u16MacID, uint32 u32ChannelMask);
PUBLIC ZPS_teStatus zps_eAplAibSetApsDesignatedCoordinator(void *pvApl, bool bDesignatedCoordinator);
PUBLIC ZPS_teStatus zps_eAplAibSetApsUseInsecureJoin(void *pvApl, bool bUseInsecureJoin);
PUBLIC ZPS_teStatus zps_eAplAibSetApsTrustCenterAddress(void *pvApl, uint64 u64TcAddress);
PUBLIC uint64 zps_eAplAibGetApsTrustCenterAddress(void *pvApl);
PUBLIC ZPS_teStatus zps_eAplAibRemoveBindTableEntryForMacAddress( void *pvApl, uint64 u64MacAddress );

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern ZPS_tsAplApsKeyDescriptorEntry  *psAplDefaultDistributedAPSLinkKey;
extern ZPS_tsAplApsKeyDescriptorEntry  *psAplDefaultGlobalAPSLinkKey;

/****************************************************************************/
/***        Inlined Functions                                            ***/
/****************************************************************************/

#ifndef ZPS_APL_OPT_MULTIPLE_INSTANCES

ZPS_AIB_INLINE ZPS_tsAplAib *ZPS_psAplAibGetAib(void) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_tsAplAib *ZPS_psAplAibGetAib(void)
{
    return zps_psAplAibGetAib(ZPS_pvAplZdoGetAplHandle());
}

ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsUseExtendedPanId(uint64 u64UseExtPanId) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsUseExtendedPanId(uint64 u64UseExtPanId)
{
    return zps_eAplAibSetApsUseExtendedPanId(ZPS_pvAplZdoGetAplHandle(), u64UseExtPanId);
}


ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsChannelMask(uint32 u32ChannelMask) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsChannelMask(uint32 u32ChannelMask)
{
    return zps_eAplAibSetApsChannelMask(ZPS_pvAplZdoGetAplHandle(), u32ChannelMask);
}


ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsChannelMaskByMacID(uint16 u16MacID, uint32 u32ChannelMask) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsChannelMaskByMacID(uint16 u16MacID, uint32 u32ChannelMask)
{
    return zps_eAplAibSetApsChannelMaskByMacID(ZPS_pvAplZdoGetAplHandle(), u16MacID, u32ChannelMask);
}

ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsDesignatedCoordinator(bool bDesignatedCoordinator) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsDesignatedCoordinator(bool bDesignatedCoordinator)
{
    return zps_eAplAibSetApsDesignatedCoordinator(ZPS_pvAplZdoGetAplHandle(), bDesignatedCoordinator);
}


ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsUseInsecureJoin(bool bUseInsecureJoin) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsUseInsecureJoin(bool bUseInsecureJoin)
{
    return zps_eAplAibSetApsUseInsecureJoin(ZPS_pvAplZdoGetAplHandle(), bUseInsecureJoin);
}

ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsTrustCenterAddress(uint64 u64TcAddress) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsTrustCenterAddress(uint64 u64TcAddress)
{
    return zps_eAplAibSetApsTrustCenterAddress(ZPS_pvAplZdoGetAplHandle(), u64TcAddress);
}

ZPS_AIB_INLINE uint64 ZPS_eAplAibGetApsTrustCenterAddress( void) ALWAYS_INLINE;
ZPS_AIB_INLINE uint64 ZPS_eAplAibGetApsTrustCenterAddress( void)
{
    return zps_eAplAibGetApsTrustCenterAddress(ZPS_pvAplZdoGetAplHandle());
}

ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibRemoveBindTableEntryForMacAddress( uint64    u64MacAddress) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibRemoveBindTableEntryForMacAddress( uint64    u64MacAddress)
{
    return zps_eAplAibRemoveBindTableEntryForMacAddress( ZPS_pvAplZdoGetAplHandle() , u64MacAddress );
}

#else

ZPS_AIB_INLINE ZPS_tsAplAib *ZPS_psAplAibGetAib(void *pvApl) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_tsAplAib *ZPS_psAplAibGetAib(void *pvApl)
{
    return zps_psAplAibGetAib(pvApl);
}

ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsUseExtendedPanId(void *pvApl, uint64 u64UseExtPanId) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsUseExtendedPanId(void *pvApl, uint64 u64UseExtPanId)
{
    return zps_eAplAibSetApsUseExtendedPanId(pvApl, u64UseExtPanId);
}

ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsChannelMask(void *pvApl,uint32 u32ChannelMask) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsChannelMask(void *pvApl,uint32 u32ChannelMask)
{
    return zps_eAplAibSetApsChannelMask(pvApl, u32ChannelMask);
}

ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsChannelMaskByMacID(void *pvApl, uint16 u16MacID, uint32 u32ChannelMask) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsChannelMaskByMacID(void *pvApl, uint16 u16MacID, uint32 u32ChannelMask)
{
    return zps_eAplAibSetApsChannelMaskByMacID(pvApl, u16MacID, u32ChannelMask);
}

ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsDesignatedCoordinator(void *pvApl, bool bDesignatedCoordinator) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsDesignatedCoordinator(void *pvApl, bool bDesignatedCoordinator)
{
    return zps_eAplAibSetApsDesignatedCoordinator(pvApl, bDesignatedCoordinator);
}


ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsUseInsecureJoin(void *pvApl, bool bUseInsecureJoin) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsUseInsecureJoin(void *pvApl, bool bUseInsecureJoin)
{
    return zps_eAplAibSetApsUseInsecureJoin(pvApl, bUseInsecureJoin);
}

ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsTrustCenterAddress(void *pvApl, uint64 u64TcAddress) ALWAYS_INLINE;
ZPS_AIB_INLINE ZPS_teStatus ZPS_eAplAibSetApsTrustCenterAddress(void *pvApl, uint64 u64TcAddress)
{
    return zps_eAplAibSetApsTrustCenterAddress(pvApl, u64TcAddress);
}
#endif

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#endif /* ZPS_APL_AIB_H_ */
