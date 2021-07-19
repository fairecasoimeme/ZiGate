/*****************************************************************************
 *
 * MODULE:      Zigbee Protocol Stack Application Layer
 *
 * COMPONENT:   zps_apl_zdo.h
 *
 * AUTHOR:      MRW
 *
 * DESCRIPTION: Interface to the ZDO
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Zigbee%20Protocol%20Stack/Modules/APL/Trunk/Include/zps_apl_zdo.h $
 *
 * $Revision: 92939 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2018-03-27 12:52:13 +0100 (Tue, 27 Mar 2018) $
 *
 * $Id: zps_apl_zdo.h 92939 2018-03-27 11:52:13Z nxp29741 $
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

#ifndef ZPS_APL_ZDO_H_
#define ZPS_APL_ZDO_H_

#include <zps_nwk_nib.h>
#include <zps_nwk_sec.h>
#include <zps_apl_aps.h>
#include <zps_nwk_pub.h>
#include <pdum_apl.h>
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#ifndef ZPS_APL_INLINE
#define ZPS_APL_INLINE  INLINE
#endif

#ifndef ZPS_ZDO_ALWAYS_INLINE
#define ZPS_ZDO_ALWAYS_INLINE  ALWAYS_INLINE
#endif
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum
{
    ZPS_ZDO_DEVICE_COORD     = 0,
    ZPS_ZDO_DEVICE_ROUTER    = 1,
    ZPS_ZDO_DEVICE_ENDDEVICE = 2
} PACK ZPS_teZdoDeviceType;

typedef enum
{
    ZPS_ZDO_NO_NETWORK_KEY,
    ZPS_ZDO_PRECONFIGURED_LINK_KEY,
    ZPS_ZDO_DISTRIBUTED_LINK_KEY,
    ZPS_ZDO_PRCONFIGURED_INSTALLATION_CODE
} PACK ZPS_teZdoNwkKeyState;

typedef enum
{
    ZPS_DEVICE_PERMISSIONS_ALL_PERMITED = 0,
    ZPS_DEVICE_PERMISSIONS_JOIN_DISALLOWED = 1,
    ZPS_DEVICE_PERMISSIONS_DATA_REQUEST_DISALLOWED = 2,
    ZPS_DEVICE_PERMISSIONS_REJOIN_DISALLOWED = 4,
} PACK ZPS_teDevicePermissions;


typedef enum {
    ZPS_APS_UNIQUE_LINK_KEY = 0x00,
    ZPS_APS_GLOBAL_LINK_KEY = 0x01
}ZPS_teApsLinkKeyType;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Private Functions (must not be called by ZPS user)     */
/****************************************************************************/

PUBLIC ZPS_teStatus zps_eAplZdoStartStack(void *);
#ifdef ZPS_MULTIMASK_SUPPORT
PUBLIC ZPS_teStatus zps_eAplZdoStartStackMM(void *);
#endif
PUBLIC void zps_eAplSetConcentrator(void *);
PUBLIC ZPS_teStatus zps_eAplZdoRejoinNetwork(void *,bool_t,bool_t);
PUBLIC ZPS_teStatus zps_eAplZdoPermitJoining(void *, uint8 );
PUBLIC ZPS_teStatus zps_eAplZdoLeaveNetwork(void *, uint64 , bool , bool );
PUBLIC ZPS_teStatus zps_eAplZdoPoll(void *);
PUBLIC ZPS_teStatus zps_eAplZdoGroupEndpointAdd(void *, uint16 , uint8 );
PUBLIC ZPS_teStatus zps_eAplZdoGroupEndpointRemove(void *, uint16, uint8 );
PUBLIC ZPS_teStatus zps_eAplZdoGroupAllEndpointRemove(void *, uint8 );
PUBLIC ZPS_teStatus zps_eAplZdoBind(void *, uint32 , uint8 , uint16 , uint64);
PUBLIC ZPS_teStatus zps_eAplZdoUnbind(void *, uint32 , uint8 , uint16 , uint64);
PUBLIC ZPS_teStatus zps_eAplZdoDiscoverNetworks(void *, uint32 );
PUBLIC ZPS_teStatus zps_eAplZdoJoinNetwork(void * , ZPS_tsNwkNetworkDescr *);
PUBLIC ZPS_teZdoDeviceType zps_eAplZdoGetDeviceType(void *);
PUBLIC uint8 zps_eAplZdoGetMacCapability(void *);
PUBLIC ZPS_tsNwkNib *zps_psAplZdoGetNib(void *);
PUBLIC void *zps_pvAplZdoGetNwkHandle(void *);
PUBLIC ZPS_teStatus zps_vAplSecSetInitialSecurityState( void *, ZPS_teZdoNwkKeyState, uint8 *, uint8, ZPS_teApsLinkKeyType );
PUBLIC ZPS_teStatus zps_eAplZdoTransportNwkKey (
    void *pvApl,
    uint8 u8DstAddrMode,
    ZPS_tuAddress uDstAddress,
    uint8 au8Key[ZPS_SEC_KEY_LENGTH],
    uint8 u8KeySeqNum,
    bool bUseParent,
    uint64 u64ParentAddr
);
PUBLIC ZPS_teStatus zps_eAplZdoRemoveDeviceReq(void *, uint64, uint64 );
PUBLIC ZPS_teStatus zps_eAplZdoSwitchKeyReq(void *, uint8, ZPS_tuAddress, uint8 );
PUBLIC ZPS_teStatus zps_eAplZdoRequestKeyReq(void *, uint8 , uint64 );
PUBLIC ZPS_teStatus zps_bAplZdoTrustCenterSetDevicePermissions(void *, uint64 , ZPS_teDevicePermissions );
PUBLIC ZPS_teStatus zps_bAplZdoTrustCenterGetDevicePermissions(void *, uint64 , ZPS_teDevicePermissions *);
PUBLIC ZPS_teStatus zps_eAplZdoAddReplaceLinkKey(void *, uint64 , uint8 [ZPS_SEC_KEY_LENGTH], ZPS_teApsLinkKeyType);
PUBLIC ZPS_teStatus zps_eAplZdoRemoveLinkKey(void *, uint64 );
PUBLIC ZPS_teStatus zps_eAplZdoManyToOneRouteRequest(void *, bool , uint8 );
PUBLIC ZPS_teStatus zps_eAplZdoRouteRequest(void *, uint16 , uint8 );
PUBLIC ZPS_teDevicePermissions zps_eAplTrustCenterFindDevice(void *pvApl, uint64 u64DeviceAddr);
PUBLIC void zps_eAplZdoSetDevicePermission(void* pvApl, ZPS_teDevicePermissions ePermissions);
PUBLIC void zps_eAplZdoRegisterZdoFilterCallback(void* pvApl, void* fnPtr);
PUBLIC ZPS_teStatus zps_eAplZdoDirectJoinNetwork( void *, uint64 ,uint16, uint8 );
PUBLIC ZPS_teStatus zps_eAplZdoOrphanRejoinNetwork( void * );
PUBLIC void ZPS_vAplZdoRegisterZdoLeaveActionCallback(void* fnPtr);
PUBLIC bool_t zps_bAplZdoTrustCenterRemoveDevice(void *pvApl, uint64 u64DeviceAddr );
PUBLIC uint8 ZPS_u8NwkManagerState(void);
PUBLIC uint8* ZPS_pu8KeyTableAccess(uint8 u8KeySeq);
PUBLIC void zps_vRegisterAliasPresentCallback (void* pvfCallbackFunction);
PUBLIC void zps_vSetZdoDeviceType(void *pvApl,uint8 u8DeviceType);
PUBLIC ZPS_teStatus zps_eAplZdoAddReplaceInstallCodes (void *pvApl,
                                                  uint64 u64IeeeAddr,
                                                  uint8 au8Key[ZPS_SEC_KEY_LENGTH],
                                                  uint8 u8Size,
                                                  ZPS_teApsLinkKeyType eKeyType);
PUBLIC void zps_vRegisterZdpEventCallback ( uint16*    pu16ClusterList,
                                            uint8      u8SizeOfList,
                                            void*      pvCallback );



PUBLIC void zps_vAplZdoSetVsOUI(void *, uint8* pu8VsOUI);
PUBLIC uint8* zps_pu8AplZdoGetVsOUI(void *);
PUBLIC void ZPS_vResetBoundServerContext (void);
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

#ifndef ZPS_APL_OPT_MULTIPLE_INSTANCES
extern const void *zps_g_pvApl;
#endif

/****************************************************************************/
/***        In-line Functions                                            ***/
/****************************************************************************/

#ifndef ZPS_APL_OPT_MULTIPLE_INSTANCES
ZPS_APL_INLINE void *ZPS_pvAplZdoGetAplHandle(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void *ZPS_pvAplZdoGetAplHandle(void)
{
    return (void*)zps_g_pvApl;
}

ZPS_APL_INLINE void ZPS_eAplSetConcentrator(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_eAplSetConcentrator(void)
{
    zps_eAplSetConcentrator(ZPS_pvAplZdoGetAplHandle());
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoStartStack(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoStartStack(void)
{

#ifdef ZPS_MULTIMASK_SUPPORT
    return zps_eAplZdoStartStackMM(ZPS_pvAplZdoGetAplHandle());
#else
    return zps_eAplZdoStartStack(ZPS_pvAplZdoGetAplHandle());
#endif
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoTCRejoinNetwork(bool_t bWithDiscovery) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoTCRejoinNetwork(bool_t bWithDiscovery)
{
    return zps_eAplZdoRejoinNetwork(ZPS_pvAplZdoGetAplHandle(),bWithDiscovery,FALSE);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRejoinNetwork(bool_t bWithDiscovery) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRejoinNetwork(bool_t bWithDiscovery)
{
    return zps_eAplZdoRejoinNetwork(ZPS_pvAplZdoGetAplHandle(),bWithDiscovery,TRUE);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoPermitJoining(uint8 u8PermitDuration) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoPermitJoining(uint8 u8PermitDuration)
{
    return zps_eAplZdoPermitJoining(ZPS_pvAplZdoGetAplHandle(), u8PermitDuration);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoLeaveNetwork(uint64 u64Addr, bool bRemoveChildren, bool bRejoin) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoLeaveNetwork(uint64 u64Addr, bool bRemoveChildren, bool bRejoin)
{
    return zps_eAplZdoLeaveNetwork(ZPS_pvAplZdoGetAplHandle(), u64Addr, bRemoveChildren, bRejoin);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoPoll(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoPoll(void)
{
    return zps_eAplZdoPoll(ZPS_pvAplZdoGetAplHandle());
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupEndpointAdd(uint16 u16GroupAddr, uint8 u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupEndpointAdd(uint16 u16GroupAddr, uint8 u8DstEndpoint)
{
    return zps_eAplZdoGroupEndpointAdd(ZPS_pvAplZdoGetAplHandle(), u16GroupAddr, u8DstEndpoint);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupEndpointRemove(uint16 u16GroupAddr, uint8 u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupEndpointRemove(uint16 u16GroupAddr, uint8 u8DstEndpoint)
{
    return zps_eAplZdoGroupEndpointRemove(ZPS_pvAplZdoGetAplHandle(), u16GroupAddr, u8DstEndpoint);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupAllEndpointRemove(uint8 u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupAllEndpointRemove(uint8 u8DstEndpoint)
{
    return zps_eAplZdoGroupAllEndpointRemove(ZPS_pvAplZdoGetAplHandle(), u8DstEndpoint);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoBind(
    uint16       u16ClusterId,
    uint8        u8SrcEndpoint,
    uint16       u16DstAddr,
    uint64       u64DstIeeeAddr,
    uint8        u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoBind(
    uint16 u16ClusterId,
    uint8  u8SrcEndpoint,
    uint16 u16DstAddr,
    uint64 u64DstIeeeAddr,
    uint8  u8DstEndpoint)
{
    return zps_eAplZdoBind(ZPS_pvAplZdoGetAplHandle(), (u16ClusterId << 16) | (u8DstEndpoint << 8) | u8SrcEndpoint, ZPS_E_ADDR_MODE_IEEE, u16DstAddr, u64DstIeeeAddr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoBindGroup(uint16 u16ClusterId, uint8 u8SrcEndpoint, uint16 u16DstGrpAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoBindGroup(uint16 u16ClusterId, uint8 u8SrcEndpoint, uint16 u16DstGrpAddr)
{
    return zps_eAplZdoBind(ZPS_pvAplZdoGetAplHandle(), (u16ClusterId << 16) | u8SrcEndpoint, ZPS_E_ADDR_MODE_GROUP, u16DstGrpAddr, 0);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoUnbind(
    uint16       u16ClusterId,
    uint8        u8SrcEndpoint,
    uint16       u16DstAddr,
    uint64       u64DstIeeeAddr,
    uint8        u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoUnbind(
    uint16 u16ClusterId,
    uint8  u8SrcEndpoint,
    uint16 u16DstAddr,
    uint64 u64DstIeeeAddr,
    uint8  u8DstEndpoint)
{
    return zps_eAplZdoUnbind(ZPS_pvAplZdoGetAplHandle(), (u16ClusterId << 16) | (u8DstEndpoint << 8) | u8SrcEndpoint, ZPS_E_ADDR_MODE_IEEE, u16DstAddr, u64DstIeeeAddr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoUnbindGroup(uint16 u16ClusterId, uint8 u8SrcEndpoint, uint16 u16DstGrpAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoUnbindGroup(uint16 u16ClusterId, uint8 u8SrcEndpoint, uint16 u16DstGrpAddr)
{
    return zps_eAplZdoUnbind(ZPS_pvAplZdoGetAplHandle(), (u16ClusterId << 16) | u8SrcEndpoint, ZPS_E_ADDR_MODE_GROUP, u16DstGrpAddr, 0);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoDiscoverNetworks(uint32 u32ChannelMask) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoDiscoverNetworks(uint32 u32ChannelMask)
{
    return zps_eAplZdoDiscoverNetworks(ZPS_pvAplZdoGetAplHandle(), u32ChannelMask);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoJoinNetwork(ZPS_tsNwkNetworkDescr *psNetworkDescr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoJoinNetwork(ZPS_tsNwkNetworkDescr *psNetworkDescr)
{
    return zps_eAplZdoJoinNetwork(ZPS_pvAplZdoGetAplHandle(), psNetworkDescr);
}

ZPS_APL_INLINE ZPS_tsNwkNib *ZPS_psAplZdoGetNib(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_tsNwkNib *ZPS_psAplZdoGetNib(void)
{
    return zps_psAplZdoGetNib(ZPS_pvAplZdoGetAplHandle());
}

ZPS_APL_INLINE ZPS_teZdoDeviceType ZPS_eAplZdoGetDeviceType(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teZdoDeviceType ZPS_eAplZdoGetDeviceType(void)
{
    return zps_eAplZdoGetDeviceType(ZPS_pvAplZdoGetAplHandle());
}

ZPS_APL_INLINE uint8 ZPS_eAplZdoGetMacCapability(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint8 ZPS_eAplZdoGetMacCapability(void)
{
    return zps_eAplZdoGetMacCapability(ZPS_pvAplZdoGetAplHandle());
}

ZPS_APL_INLINE void *ZPS_pvAplZdoGetNwkHandle(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void *ZPS_pvAplZdoGetNwkHandle(void)
{
    return zps_pvAplZdoGetNwkHandle(ZPS_pvAplZdoGetAplHandle());
}


ZPS_APL_INLINE ZPS_teStatus ZPS_vAplSecSetInitialSecurityState(ZPS_teZdoNwkKeyState eState, uint8 *pu8Key, uint8 u8KeyLength, ZPS_teApsLinkKeyType eKeyType ) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_vAplSecSetInitialSecurityState(ZPS_teZdoNwkKeyState eState, uint8 *pu8Key, uint8 u8KeyLength, ZPS_teApsLinkKeyType eKeyType)
{
    return zps_vAplSecSetInitialSecurityState(ZPS_pvAplZdoGetAplHandle(), eState, pu8Key, u8KeyLength, eKeyType);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoTransportNwkKey (
    uint8 u8DstAddrMode,
    ZPS_tuAddress uDstAddress,
    uint8 au8Key[ZPS_SEC_KEY_LENGTH],
    uint8 u8KeySeqNum,
    bool bUseParent,
    uint64 u64ParentAddr
) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoTransportNwkKey (
    uint8 u8DstAddrMode,
    ZPS_tuAddress uDstAddress,
    uint8 au8Key[ZPS_SEC_KEY_LENGTH],
    uint8 u8KeySeqNum,
    bool bUseParent,
    uint64 u64ParentAddr
)
{
    return zps_eAplZdoTransportNwkKey(ZPS_pvAplZdoGetAplHandle(), u8DstAddrMode, uDstAddress, au8Key, u8KeySeqNum, bUseParent, u64ParentAddr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRemoveDeviceReq(uint64 u64ParentAddr, uint64 u64ChildAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRemoveDeviceReq(uint64 u64ParentAddr, uint64 u64ChildAddr)
{
    return zps_eAplZdoRemoveDeviceReq(ZPS_pvAplZdoGetAplHandle(), u64ParentAddr, u64ChildAddr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoSwitchKeyReq(uint8 u8DstAddrMode, ZPS_tuAddress uDstAddress, uint8 u8KeySeqNum) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoSwitchKeyReq(uint8 u8DstAddrMode, ZPS_tuAddress uDstAddress, uint8 u8KeySeqNum)
{
    return zps_eAplZdoSwitchKeyReq(ZPS_pvAplZdoGetAplHandle(), u8DstAddrMode, uDstAddress, u8KeySeqNum);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRequestKeyReq(uint8 u8KeyType, uint64 u64IeeePartnerAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRequestKeyReq(uint8 u8KeyType, uint64 u64IeeePartnerAddr)
{
    return zps_eAplZdoRequestKeyReq(ZPS_pvAplZdoGetAplHandle(), u8KeyType, u64IeeePartnerAddr);
}


ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterSetDevicePermissions(uint64 u64DeviceAddr, ZPS_teDevicePermissions u8DevicePermissions) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterSetDevicePermissions(uint64 u64DeviceAddr, ZPS_teDevicePermissions u8DevicePermissions)
{
    return zps_bAplZdoTrustCenterSetDevicePermissions(ZPS_pvAplZdoGetAplHandle(), u64DeviceAddr, u8DevicePermissions);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterGetDevicePermissions(uint64 u64DeviceAddr, ZPS_teDevicePermissions *pu8DevicePermissions) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterGetDevicePermissions(uint64 u64DeviceAddr, ZPS_teDevicePermissions *pu8DevicePermissions)
{
    return zps_bAplZdoTrustCenterGetDevicePermissions(ZPS_pvAplZdoGetAplHandle(), u64DeviceAddr, pu8DevicePermissions);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddReplaceLinkKey(uint64 u64IeeeAddr, uint8 au8Key[ZPS_SEC_KEY_LENGTH], ZPS_teApsLinkKeyType eKeyType) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddReplaceLinkKey(uint64 u64IeeeAddr, uint8 au8Key[ZPS_SEC_KEY_LENGTH], ZPS_teApsLinkKeyType eKeyType)
{
    return zps_eAplZdoAddReplaceLinkKey(ZPS_pvAplZdoGetAplHandle(), u64IeeeAddr, au8Key, eKeyType);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRemoveLinkKey(uint64 u64IeeeAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRemoveLinkKey(uint64 u64IeeeAddr)
{
    return zps_eAplZdoRemoveLinkKey(ZPS_pvAplZdoGetAplHandle(), u64IeeeAddr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoManyToOneRouteRequest(bool bCacheRoute, uint8 u8Radius) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoManyToOneRouteRequest(bool bCacheRoute, uint8 u8Radius)
{
    return zps_eAplZdoManyToOneRouteRequest(ZPS_pvAplZdoGetAplHandle(), bCacheRoute, u8Radius);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRouteRequest(uint16 u16DstAddr, uint8 u8Radius) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRouteRequest(uint16 u16DstAddr, uint8 u8Radius)
{
    return zps_eAplZdoRouteRequest(ZPS_pvAplZdoGetAplHandle(), u16DstAddr, u8Radius);
}

/* Network layer fn wrappers */

ZPS_APL_INLINE uint16 ZPS_u16AplZdoGetNwkAddr(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint16 ZPS_u16AplZdoGetNwkAddr(void)
{
    return ZPS_u16NwkNibGetNwkAddr(zps_pvAplZdoGetNwkHandle(ZPS_pvAplZdoGetAplHandle()));
}

ZPS_APL_INLINE uint64 ZPS_u64AplZdoGetIeeeAddr(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint64 ZPS_u64AplZdoGetIeeeAddr(void)
{
    return ZPS_u64NwkNibGetExtAddr(zps_pvAplZdoGetNwkHandle(ZPS_pvAplZdoGetAplHandle()));
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddAddrMapEntry(uint16 u16NwkAddr, uint64 u64ExtAddr, bool_t bCheckNeighborTable) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddAddrMapEntry(uint16 u16NwkAddr, uint64 u64ExtAddr, bool_t bCheckNeighborTable)
{
    return ZPS_bNwkNibAddrMapAddEntry(zps_pvAplZdoGetNwkHandle(ZPS_pvAplZdoGetAplHandle()), u16NwkAddr, u64ExtAddr,bCheckNeighborTable) ?
            ZPS_E_SUCCESS : ZPS_APL_APS_E_TABLE_FULL;
}

ZPS_APL_INLINE uint64 ZPS_u64AplZdoLookupIeeeAddr(uint16 u16NwkAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint64 ZPS_u64AplZdoLookupIeeeAddr(uint16 u16NwkAddr)
{
    return ZPS_u64NwkNibFindExtAddr(zps_pvAplZdoGetNwkHandle(ZPS_pvAplZdoGetAplHandle()), u16NwkAddr);
}

ZPS_APL_INLINE uint16 ZPS_u16AplZdoLookupAddr(uint64 u64ExtAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint16 ZPS_u16AplZdoLookupAddr(uint64 u64ExtAddr)
{
    return ZPS_u16NwkNibFindNwkAddr(zps_pvAplZdoGetNwkHandle(ZPS_pvAplZdoGetAplHandle()), u64ExtAddr);
}

ZPS_APL_INLINE uint8 ZPS_u8AplZdoGetRadioChannel(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint8 ZPS_u8AplZdoGetRadioChannel(void)
{
    return zps_psAplZdoGetNib(ZPS_pvAplZdoGetAplHandle())->sPersist.u8VsChannel;
}

ZPS_APL_INLINE uint8 ZPS_u8AplZdoGetAuxRadioChannel(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint8 ZPS_u8AplZdoGetAuxRadioChannel(void)
{
    return zps_psAplZdoGetNib(ZPS_pvAplZdoGetAplHandle())->sPersist.u8VsAuxChannel;
}

ZPS_APL_INLINE uint16 ZPS_u16AplZdoGetNetworkPanId(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint16 ZPS_u16AplZdoGetNetworkPanId(void)
{
    return zps_psAplZdoGetNib(ZPS_pvAplZdoGetAplHandle())->sPersist.u16VsPanId;
}

ZPS_APL_INLINE uint64 ZPS_u64AplZdoGetNetworkExtendedPanId(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint64 ZPS_u64AplZdoGetNetworkExtendedPanId(void)
{
    return ZPS_u64NwkNibGetEpid(zps_pvAplZdoGetNwkHandle(ZPS_pvAplZdoGetAplHandle()));
}


ZPS_APL_INLINE ZPS_teDevicePermissions ZPS_eAplTrustCenterFindDevice(uint64 u64ExtendedAddress) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teDevicePermissions ZPS_eAplTrustCenterFindDevice(uint64 u64ExtendedAddress)
{
    return zps_eAplTrustCenterFindDevice(ZPS_pvAplZdoGetAplHandle(), u64ExtendedAddress);
}

ZPS_APL_INLINE void ZPS_eAplZdoSetDevicePermission(ZPS_teDevicePermissions u8DevicePermissions) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_eAplZdoSetDevicePermission(ZPS_teDevicePermissions u8DevicePermissions)
{
    zps_eAplZdoSetDevicePermission(ZPS_pvAplZdoGetAplHandle(), u8DevicePermissions);
}


ZPS_APL_INLINE void ZPS_eAplZdoRegisterZdoFilterCallback(void* fnPtr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_eAplZdoRegisterZdoFilterCallback(void* fnPtr)
{
    zps_eAplZdoRegisterZdoFilterCallback(ZPS_pvAplZdoGetAplHandle(), fnPtr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoDirectJoinNetwork(uint64 u64Addr, uint16 u16Addr, uint8 u8Capability) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoDirectJoinNetwork(uint64 u64Addr,uint16 u16Addr, uint8 u8Capability)
{
    return zps_eAplZdoDirectJoinNetwork(ZPS_pvAplZdoGetAplHandle(), u64Addr, u16Addr, u8Capability);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoOrphanRejoinNetwork(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoOrphanRejoinNetwork(void)
{
    return zps_eAplZdoOrphanRejoinNetwork(ZPS_pvAplZdoGetAplHandle());
}

ZPS_APL_INLINE bool ZPS_bGetPermitJoiningStatus(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE bool ZPS_bGetPermitJoiningStatus(void)
{
    return ZPS_vNwkGetPermitJoiningStatus(zps_pvAplZdoGetNwkHandle(ZPS_pvAplZdoGetAplHandle()));
}


ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterRemoveDevice(uint64 u64DeviceAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterRemoveDevice(uint64 u64DeviceAddr)
{
    return zps_bAplZdoTrustCenterRemoveDevice(ZPS_pvAplZdoGetAplHandle(),u64DeviceAddr );
}

ZPS_APL_INLINE void ZPS_vAfRegisterAliasPresentCallback(void* pvfCallbackFunction) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_vAfRegisterAliasPresentCallback(void* pvfCallbackFunction)
{
	zps_vRegisterAliasPresentCallback(pvfCallbackFunction);
}

ZPS_APL_INLINE  void ZPS_vSetZdoDeviceType(uint8 u8DeviceType) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE  void ZPS_vSetZdoDeviceType(uint8 u8DeviceType)
{
	zps_vSetZdoDeviceType(ZPS_pvAplZdoGetAplHandle(),u8DeviceType);
}


ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddReplaceInstallCodes(uint64 u64IeeeAddr, uint8 au8Key[ZPS_SEC_KEY_LENGTH], uint8 u8InstallCodeSize, ZPS_teApsLinkKeyType eKeyType) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddReplaceInstallCodes(uint64 u64IeeeAddr, uint8 au8Key[ZPS_SEC_KEY_LENGTH], uint8 u8InstallCodeSize, ZPS_teApsLinkKeyType eKeyType)
{
    return zps_eAplZdoAddReplaceInstallCodes(ZPS_pvAplZdoGetAplHandle(), u64IeeeAddr, au8Key, u8InstallCodeSize, eKeyType);
}


ZPS_APL_INLINE void ZPS_vAplZdoSetVsOUI(uint8 *pu8VsOUI) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_vAplZdoSetVsOUI(uint8 *pu8VsOUI)
{
    return zps_vAplZdoSetVsOUI(ZPS_pvAplZdoGetAplHandle(), pu8VsOUI);
}

ZPS_APL_INLINE uint8* ZPS_pu8AplZdoGetVsOUI(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint8* ZPS_pu8AplZdoGetVsOUI(void)
{
    return zps_pu8AplZdoGetVsOUI(ZPS_pvAplZdoGetAplHandle());
}


#else

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoStartStack(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoStartStack(void *pvApl)
{
#ifdef ZPS_MULTIMASK_SUPPORT
    return zps_eAplZdoStartStackMM(pvApl);
#else
    return zps_eAplZdoStartStack(pvApl);
#endif
}

ZPS_APL_INLINE void ZPS_eAplSetConcentrator(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_eAplSetConcentrator(void *pvApl)
{
    zps_eAplSetConcentrator(pvApl);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRejoinNetwork(void *pvApl,bool_t bWithDiscovery) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRejoinNetwork(void *pvApl,bool_t bWithDiscovery)
{
    return zps_eAplZdoRejoinNetwork(pvApl);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoPermitJoining(void *pvApl, uint8 u8PermitDuration) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoPermitJoining(void *pvApl, uint8 u8PermitDuration)
{
    return zps_eAplZdoPermitJoining(pvApl, u8PermitDuration);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoLeaveNetwork(void *pvApl, uint64 u64Addr, bool bRemoveChildren, bool bRejoin) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoLeaveNetwork(void *pvApl, uint64 u64Addr, bool bRemoveChildren, bool bRejoin)
{
    return zps_eAplZdoLeaveNetwork(pvApl, u64Addr, bRemoveChildren, bRejoin);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoPoll(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoPoll(void *pvApl)
{
    return zps_eAplZdoPoll(pvApl);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupEndpointAdd(void *pvApl, uint16 u16GroupAddr, uint8 u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupEndpointAdd(void *pvApl, uint16 u16GroupAddr, uint8 u8DstEndpoint)
{
    return zps_eAplZdoGroupEndpointAdd(pvApl, u16GroupAddr, u8DstEndpoint);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupEndpointRemove(void *pvApl, uint16 u16GroupAddr, uint8 u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupEndpointRemove(void *pvApl, uint16 u16GroupAddr, uint8 u8DstEndpoint)
{
    return zps_eAplZdoGroupEndpointRemove(pvApl, u16GroupAddr, u8DstEndpoint);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupAllEndpointRemove(void *pvApl, uint8 u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoGroupAllEndpointRemove(void *pvApl, uint8 u8DstEndpoint)
{
    return zps_eAplZdoGroupAllEndpointRemove(pvApl, u8DstEndpoint);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoBind(
    void         *pvApl,
    uint16       u16ClusterId,
    uint64       u64SrcAddr,
    uint8        u8SrcEndpoint,
    uint8        u8DstAddrMode,
    ZPS_tuAddress *puDstAddr,
    uint8        u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoBind(
    void         *pvApl,
    uint16       u16ClusterId,
    uint64       u64SrcAddr,
    uint8        u8SrcEndpoint,
    uint8        u8DstAddrMode,
    ZPS_tuAddress *puDstAddr,
    uint8        u8DstEndpoint)
{
    // TODO compress parameters to 6
    return zps_eAplZdoBind(pvApl, u16ClusterId, u64SrcAddr, u8SrcEndpoint, u8DstAddrMode, puDstAddr, u8DstEndpoint);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoUnbind(
    void         *pvApl,
    uint16       u16ClusterId,
    uint64       u64SrcAddr,
    uint8        u8SrcEndpoint,
    uint8        u8DstAddrMode,
    ZPS_tuAddress *puDstAddr,
    uint8        u8DstEndpoint) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoUnbind(
    void         *pvApl,
    uint16       u16ClusterId,
    uint64       u64SrcAddr,
    uint8        u8SrcEndpoint,
    uint8        u8DstAddrMode,
    ZPS_tuAddress *puDstAddr,
    uint8        u8DstEndpoint)
{
    // TODO compress parameters to 6
    return zps_eAplZdoUnbind(pvApl, u16ClusterId, u64SrcAddr, u8SrcEndpoint, u8DstAddrMode, puDstAddr, u8DstEndpoint);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoDiscoverNetworks(void *pvApl, uint32 u32ChannelMask) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoDiscoverNetworks(void *pvApl, uint32 u32ChannelMask)
{
    return zps_eAplZdoDiscoverNetworks(pvApl, u32ChannelMask);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoJoinNetwork(void *pvApl, ZPS_tsNwkNetworkDescr *psNetworkDescr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoJoinNetwork(void *pvApl, ZPS_tsNwkNetworkDescr *psNetworkDescr)
{
    return zps_eAplZdoJoinNetwork(pvApl, psNetworkDescr);
}

ZPS_APL_INLINE ZPS_tsNwkNib *ZPS_psAplZdoGetNib(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_tsNwkNib *ZPS_psAplZdoGetNib(void *pvApl)
{
    return zps_psAplZdoGetNib(pvApl);
}

ZPS_APL_INLINE ZPS_teZdoDeviceType ZPS_eAplZdoGetDeviceType(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teZdoDeviceType ZPS_eAplZdoGetDeviceType(void *pvApl)
{
    return zps_eAplZdoGetDeviceType(pvApl);
}

ZPS_APL_INLINE void *ZPS_pvAplZdoGetNwkHandle(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void *ZPS_pvAplZdoGetNwkHandle(void *pvApl)
{
    return zps_pvAplZdoGetNwkHandle(pvApl);
}


ZPS_APL_INLINE ZPS_teStatus ZPS_vAplSecSetInitialSecurityState(void *pvApl, ZPS_teZdoNwkKeyState eState, uint8 *pu8Key, uint8 u8KeySeqNum ) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_vAplSecSetInitialSecurityState(void *pvApl, ZPS_teZdoNwkKeyState eState, uint8 *pu8Key, uint8 u8KeySeqNum)
{
    return zps_vAplSecSetInitialSecurityState(pvApl, eState, pu8Key, u8KeySeqNum);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoTransportNwkKey( void *pvApl, uint8 u8DstAddrMode, ZPS_tuAddress uDstAddress, uint8 au8Key[ZPS_SEC_KEY_LENGTH], uint8 u8KeySeqNum, bool bUseParent, uint64 u64ParentAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoTransportNwkKey( void *pvApl, uint8 u8DstAddrMode, ZPS_tuAddress uDstAddress, uint8 au8Key[ZPS_SEC_KEY_LENGTH], uint8 u8KeySeqNum, bool bUseParent, uint64 u64ParentAddr)
{
    return zps_eAplZdoTransportNwkKey(pvApl, u8DstAddrMode, uDstAddress, au8Key, u8KeySeqNum, bUseParent, u64ParentAddr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRemoveDeviceReq( void *pvApl, uint64 u64ParentAddr, uint64 u64ChildAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRemoveDeviceReq( void *pvApl, uint64 u64ParentAddr, uint64 u64ChildAddr)
{
    return zps_eAplZdoRemoveDeviceReq(pvApl, u64ParentAddr, u64ChildAddr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoSwitchKeyReq( void *pvApl, uint8 u8DstAddrMode, ZPS_tuAddress uDstAddress, uint8 u8KeySeqNum) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoSwitchKeyReq( void *pvApl, uint8 u8DstAddrMode, ZPS_tuAddress uDstAddress, uint8 u8KeySeqNum)
{
    return zps_eAplZdoSwitchKeyReq(pvApl, u8DstAddrMode, uDstAddress, u8KeySeqNum);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRequestKeyReq( void *pvApl, uint8 u8KeyType, uint64 u64IeeePartnerAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRequestKeyReq( void *pvApl, uint8 u8KeyType, uint64 u64IeeePartnerAddr)
{
    return zps_eAplZdoRequestKeyReq(pvApl, u8KeyType, u64IeeePartnerAddr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterSetDevicePermissions(void *pvApl, uint64 u64DeviceAddr, ZPS_teDevicePermissions u8DevicePermissions) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterSetDevicePermissions(void *pvApl, uint64 u64DeviceAddr, ZPS_teDevicePermissions u8DevicePermissions)
{
    return zps_bAplZdoTrustCenterSetDevicePermissions(pvApl, u64DeviceAddr, u8DevicePermissions);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterGetDevicePermissions(void *pvApl, uint64 u64DeviceAddr, ZPS_teDevicePermissions *pu8DevicePermissions) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterGetDevicePermissions(void *pvApl, uint64 u64DeviceAddr, ZPS_teDevicePermissions *pu8DevicePermissions)
{
    return zps_bAplZdoTrustCenterGetDevicePermissions(pvApl, u64DeviceAddr, pu8DevicePermissions);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddReplaceLinkKey(void *pvApl, uint64 u64IeeeAddr, uint8 au8Key[ZPS_SEC_KEY_LENGTH]) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddReplaceLinkKey(void *pvApl, uint64 u64IeeeAddr, uint8 au8Key[ZPS_SEC_KEY_LENGTH])
{
    return zps_eAplZdoAddReplaceLinkKey(pvApl, u64IeeeAddr, au8Key);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRemoveLinkKey(void *pvApl, uint64 u64IeeeAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRemoveLinkKey(void *pvApl, uint64 u64IeeeAddr)
{
    return zps_eAplZdoRemoveLinkKey(pvApl, u64IeeeAddr);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoManyToOneRouteRequest(void *pvApl, bool bCacheRoute, uint8 u8Radius) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoManyToOneRouteRequest(void *pvApl, bool bCacheRoute, uint8 u8Radius)
{
    return zps_eAplZdoManyToOneRouteRequest(pvApl, bCacheRoute, u8Radius);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRouteRequest(void *pvApl, uint16 u16DstAddr, uint8 u8Radius) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoRouteRequest(void *pvApl, uint16 u16DstAddr, uint8 u8Radius)
{
    return zps_eAplZdoRouteRequest(pvApl, u16DstAddr, u8Radius);
}

/* Network layer fn wrappers */

ZPS_APL_INLINE uint16 ZPS_u16AplZdoGetNwkAddr(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint16 ZPS_u16AplZdoGetNwkAddr(void *pvApl)
{
    return ZPS_u16NwkNibGetNwkAddr(zps_pvAplZdoGetNwkHandle(pvApl));
}

ZPS_APL_INLINE uint64 ZPS_u64AplZdoGetIeeeAddr(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint64 ZPS_u64AplZdoGetIeeeAddr(void *pvApl)
{
    return ZPS_u64NwkNibGetExtAddr(zps_pvAplZdoGetNwkHandle(pvApl));
}

ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddAddrMapEntry(void *pvApl, uint16 u16NwkAddr, uint64 u64ExtAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_eAplZdoAddAddrMapEntry(void *pvApl, uint16 u16NwkAddr, uint64 u64ExtAddr)
{
    return ZPS_bNwkNibAddrMapAddEntry(zps_pvAplZdoGetNwkHandle(pvApl), u16NwkAddr, u64ExtAddr,TRUE) ?
            ZPS_E_SUCCESS : ZPS_APL_APS_E_TABLE_FULL;
}

ZPS_APL_INLINE uint64 ZPS_u64AplZdoLookupIeeeAddr(void *pvApl, uint16 u16NwkAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint64 ZPS_u64AplZdoLookupIeeeAddr(void *pvApl, uint16 u16NwkAddr)
{
    return ZPS_u64NwkNibFindExtAddr(zps_pvAplZdoGetNwkHandle(pvApl), u16NwkAddr);
}

ZPS_APL_INLINE uint16 ZPS_u16AplZdoLookupAddr(void *pvApl, uint64 u64ExtAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint16 ZPS_u16AplZdoLookupAddr(void *pvApl, uint64 u64ExtAddr)
{
    return ZPS_u16NwkNibFindNwkAddr(zps_pvAplZdoGetNwkHandle(pvApl), u64ExtAddr);
}

ZPS_APL_INLINE uint8 ZPS_u8AplZdoGetRadioChannel(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint8 ZPS_u8AplZdoGetRadioChannel(void *pvApl)
{
    return zps_psAplZdoGetNib(pvApl)->sPersist.u8VsChannel;
}

ZPS_APL_INLINE uint8 ZPS_u8AplZdoGetAuxRadioChannel(void) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint8 ZPS_u8AplZdoGetAuxRadioChannel(void)
{
    return zps_psAplZdoGetNib(ZPS_pvAplZdoGetAplHandle())->sPersist.u8VsAuxChannel;
}

ZPS_APL_INLINE uint16 ZPS_u8AplZdoGetNetworkPanId(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint16 ZPS_u8AplZdoGetNetworkPanId(void *pvApl)
{
    return zps_psAplZdoGetNib(pvApl)->sPersist.u16VsPanId;
}

ZPS_APL_INLINE uint64 ZPS_u64AplZdoGetNetworkExtendedPanId(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint64 ZPS_u64AplZdoGetNetworkExtendedPanId(void *pvApl)
{
    return ZPS_u64NwkNibGetEpid(zps_pvAplZdoGetNwkHandle(pvApl));
}
ZPS_APL_INLINE ZPS_teDevicePermissions ZPS_eAplTrustCenterFindDevice(void *pvApl, uint64 u64ExtendedAddress) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teDevicePermissions ZPS_eAplTrustCenterFindDevice(void *pvApl, uint64 u64ExtendedAddress)
{
    return zps_eAplTrustCenterFindDevice(pvApl, u64ExtendedAddress);
}


ZPS_APL_INLINE void ZPS_eAplZdoSetDevicePermission(void *pvApl, ZPS_teDevicePermissions u8DevicePermissions) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_eAplZdoSetDevicePermission(void *pvApl, ZPS_teDevicePermissions u8DevicePermissions)
{
    zps_eAplZdoSetDevicePermission(pvApl, u8DevicePermissions);
}


ZPS_APL_INLINE void ZPS_eAplZdoRegisterZdoFilterCallback(void *pvApl,void* fnPtr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_eAplZdoRegisterZdoFilterCallback(void *pvApl,void* fnPtr)
{
    zps_eAplZdoRegisterZdoFilterCallback(pvApl, fnPtr);
}

ZPS_APL_INLINE bool ZPS_bGetPermitJoiningStatus(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE bool ZPS_bGetPermitJoiningStatus(void *pvApl)
{
    return ZPS_vNwkGetPermitJoiningStatus(zps_pvAplZdoGetNwkHandle(pvApl));
}

ZPS_APL_INLINE void ZPS_eAplZdoEnableProxyTcCapability(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_eAplZdoEnableProxyTcCapability(void *pvApl)
{
    zps_eAplZdoEnableProxyTcCapability(pvApl);
}

ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterRemoveDevice(uint64 u64DeviceAddr) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE ZPS_teStatus ZPS_bAplZdoTrustCenterRemoveDevice(uint64 u64DeviceAddr)
{
    return zps_bAplZdoTrustCenterRemoveDevice(pvApl,u64DeviceAddr );
}



ZPS_APL_INLINE void ZPS_vAplZdoSetVsOUI(void *pvApl, uint8 *pu8VsOUI) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE void ZPS_vAplZdoSetVsOUI(void *pvApl, uint8 *pu8VsOUI)
{
    return zps_vAplZdoSetVsOUI(pvApl, pu8VsOUI);
}

ZPS_APL_INLINE uint8* ZPS_pu8AplZdoGetVsOUI(void *pvApl) ZPS_ZDO_ALWAYS_INLINE;
ZPS_APL_INLINE uint8* ZPS_pu8AplZdoGetVsOUI(void *pvApl)
{
    return zps_pu8AplZdoGetVsOUI(pvApl);
}

#endif

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#endif /*ZPS_APL_ZDO_H_*/
