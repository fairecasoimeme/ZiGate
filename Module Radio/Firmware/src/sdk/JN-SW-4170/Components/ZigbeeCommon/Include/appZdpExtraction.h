/*****************************************************************************
 *
 * MODULE:      Utils
 *
 * COMPONENT:   appZdpExtractions.h
 *
 * AUTHOR:      nxp29741
 *
 * DESCRIPTION:
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: $
 *
 * $Id:  $
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

#ifndef APPZDPEXTRACTION_H_
#define APPZDPEXTRACTION_H_

#include <jendefs.h>
#include "zps_apl_zdp.h"
#include "zps_apl_af.h"
#include "pdum_apl.h"
#include "pdum_nwk.h"

typedef struct {
    union {
        ZPS_tsAplZdpDeviceAnnceReq sDeviceAnnce;
        ZPS_tsAplZdpMgmtNwkUpdateReq sMgmtNwkUpdateReq;
        ZPS_tsAplZdpMgmtNwkEnhanceUpdateReq sMgmtEnhancedUpdateReq;
        ZPS_tsAplZdpMgmtPermitJoiningReq sPermitJoiningReq;
        ZPS_tsAplZdpDiscoveryCacheRsp sDiscoveryCacheRsp;
        ZPS_tsAplZdpDiscoveryStoreRsp sDiscoveryStoreRsp;
        ZPS_tsAplZdpNodeDescStoreRsp sNodeDescStoreRsp;
        ZPS_tsAplZdpActiveEpStoreRsp sActiveEpStoreRsp;
        ZPS_tsAplZdpSimpleDescStoreRsp sSimpleDescStoreRsp;
        ZPS_tsAplZdpRemoveNodeCacheRsp sRemoveNodeCacheRsp;
        ZPS_tsAplZdpEndDeviceBindRsp sEndDeviceBindRsp;
        ZPS_tsAplZdpBindRsp sBindRsp;
        ZPS_tsAplZdpUnbindRsp sUnbindRsp;
        ZPS_tsAplZdpReplaceDeviceRsp sReplaceDeviceRsp;
        ZPS_tsAplZdpStoreBkupBindEntryRsp sStoreBkupBindEntryRsp;
        ZPS_tsAplZdpRemoveBkupBindEntryRsp sRemoveBkupBindEntryRsp;
        ZPS_tsAplZdpBackupSourceBindRsp sBackupSourceBindRsp;
        ZPS_tsAplZdpMgmtLeaveRsp sMgmtLeaveRsp;
        ZPS_tsAplZdpMgmtDirectJoinRsp sMgmtDirectJoinRsp;
        ZPS_tsAplZdpMgmtPermitJoiningRsp sPermitJoiningRsp;
        ZPS_tsAplZdpNodeDescRsp sNodeDescRsp;
        ZPS_tsAplZdpPowerDescRsp sPowerDescRsp;
        ZPS_tsAplZdpSimpleDescRsp sSimpleDescRsp;
        ZPS_tsAplZdpNwkAddrRsp sNwkAddrRsp;
        ZPS_tsAplZdpIeeeAddrRsp sIeeeAddrRsp;
        ZPS_tsAplZdpUserDescConf sUserDescConf;
        ZPS_tsAplZdpSystemServerDiscoveryRsp sSystemServerDiscoveryRsp;
        ZPS_tsAplZdpPowerDescStoreRsp sPowerDescStoreRsp;
        ZPS_tsAplZdpUserDescRsp sUserDescRsp;
        ZPS_tsAplZdpActiveEpRsp sActiveEpRsp;
        ZPS_tsAplZdpMatchDescRsp sMatchDescRsp;
        ZPS_tsAplZdpComplexDescRsp sComplexDescRsp;
        ZPS_tsAplZdpFindNodeCacheRsp sFindNodeCacheRsp;
        ZPS_tsAplZdpExtendedSimpleDescRsp sExtendedSimpleDescRsp;
        ZPS_tsAplZdpExtendedActiveEpRsp sExtendedActiveEpRsp;
        ZPS_tsAplZdpBindRegisterRsp sBindRegisterRsp;
        ZPS_tsAplZdpBackupBindTableRsp sBackupBindTableRsp;
        ZPS_tsAplZdpRecoverBindTableRsp sRecoverBindTableRsp;
        ZPS_tsAplZdpRecoverSourceBindRsp sRecoverSourceBindRsp;
        ZPS_tsAplZdpMgmtNwkDiscRsp sMgmtNwkDiscRsp;
        ZPS_tsAplZdpMgmtLqiRsp sMgmtLqiRsp;
        ZPS_tsAplZdpMgmtRtgRsp sRtgRsp;
        ZPS_tsAplZdpMgmtBindRsp sMgmtBindRsp;
        ZPS_tsAplZdpMgmtCacheRsp sMgmtCacheRsp;
        ZPS_tsAplZdpMgmtNwkUpdateNotify sMgmtNwkUpdateNotify;
        ZPS_tsAplZdpMgmtNwkUnSolictedUpdateNotify sMgmtNwkUnsolicitedUpdateNotify;
    }uZdpData;
    union {
        ZPS_tsAplZdpBindingTableEntry asBindingTable[5];
        ZPS_tsAplZdpNetworkDescr asNwkDescTable[5];
        ZPS_tsAplZdpNtListEntry asNtList[2];
        ZPS_tsAplDiscoveryCache aDiscCache[5];
        uint16 au16Data[34];
        uint8 au8Data[77];
        uint64 au64Data[9];
    }uLists;
    uint16 u16ClusterId;
    uint8 u8SequNumber;
}ZPS_tsAfZdpEvent;


PUBLIC bool zps_bAplZdpUnpackNwkAddressResponse(ZPS_tsAfEvent *psZdoServerEvent, 
                                                ZPS_tsAfZdpEvent* psReturnStruct);
                                                
PUBLIC bool zps_bAplZdpUnpackIeeeAddressResponse(ZPS_tsAfEvent *psZdoServerEvent, 
                                                ZPS_tsAfZdpEvent* psReturnStruct);
                                                
PUBLIC bool zps_bAplZdpUnpackNwkUpdateReq(ZPS_tsAfEvent *psZdoServerEvent, 
                                          ZPS_tsAfZdpEvent* psReturnStruct);

PUBLIC bool zps_bAplZdpUnpackEnhancedNwkUpdateReq(ZPS_tsAfEvent *psZdoServerEvent,
                                          ZPS_tsAfZdpEvent* psReturnStruct);
                                          
PUBLIC bool zps_bAplZdpUnpackPermitJoinReq(ZPS_tsAfEvent *psZdoServerEvent,
                                           ZPS_tsAfZdpEvent* psReturnStruct);
                                           
PUBLIC bool zps_bAplZdpUnpackDevicAnnounce(ZPS_tsAfEvent *psZdoServerEvent,
                                           ZPS_tsAfZdpEvent* psReturnStruct);
                                           
PUBLIC bool zps_bAplZdpUnpackNodeDescResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                              ZPS_tsAfZdpEvent* psReturnStruct);                                              
                                              
PUBLIC bool zps_bAplZdpUnpackPowerDescResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                               ZPS_tsAfZdpEvent* psReturnStruct);
                                               
PUBLIC bool zps_bAplZdpUnpackSimpleDescResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                ZPS_tsAfZdpEvent* psReturnStruct);
                                                
PUBLIC bool zps_bAplZdpUnpackActiveEpResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                              ZPS_tsAfZdpEvent* psReturnStruct);
                                              
PUBLIC bool zps_bAplZdpUnpackMatchDescResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                               ZPS_tsAfZdpEvent* psReturnStruct);
                                               
PUBLIC bool zps_bAplZdpUnpackDiscCacheResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                               ZPS_tsAfZdpEvent* psReturnStruct);
                                               
PUBLIC bool zps_bAplZdpUnpackDiscStoreResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                               ZPS_tsAfZdpEvent* psReturnStruct);
                                               
PUBLIC bool zps_bAplZdpUnpackNodeDescStoreResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                   ZPS_tsAfZdpEvent* psReturnStruct);
                                                   
PUBLIC bool zps_bAplZdpUnpackActiveEpStoreResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                   ZPS_tsAfZdpEvent* psReturnStruct);
                                                   
PUBLIC bool zps_bAplZdpUnpackSimpleDescStoreResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                     ZPS_tsAfZdpEvent* psReturnStruct);
                                                     
PUBLIC bool zps_bAplZdpUnpackRemoveNodeCacheResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                     ZPS_tsAfZdpEvent* psReturnStruct);
                                                     
PUBLIC bool zps_bAplZdpUnpackBackUpSourceBindResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                      ZPS_tsAfZdpEvent* psReturnStruct);
                                                                                                            
PUBLIC bool zps_bAplZdpUnpackMgmtLeaveResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                               ZPS_tsAfZdpEvent* psReturnStruct);
                                               
PUBLIC bool zps_bAplZdpUnpackMgmtDirectJoinResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                    ZPS_tsAfZdpEvent* psReturnStruct);
                                                    
PUBLIC bool zps_bAplZdpUnpackMgmtPermitJoinResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                    ZPS_tsAfZdpEvent* psReturnStruct);
                                                    
PUBLIC bool zps_bAplZdpUnpackEndDeviceBindResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                   ZPS_tsAfZdpEvent* psReturnStruct);
                                                   
PUBLIC bool zps_bAplZdpUnpackBindResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                          ZPS_tsAfZdpEvent* psReturnStruct);
                                          
PUBLIC bool zps_bAplZdpUnpackUnBindResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                            ZPS_tsAfZdpEvent* psReturnStruct);
                                            
PUBLIC bool zps_bAplZdpUnpackReplaceDeviceResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                   ZPS_tsAfZdpEvent* psReturnStruct);
                                                   
PUBLIC bool zps_bAplZdpUnpackStoreBkupBindResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                   ZPS_tsAfZdpEvent* psReturnStruct);
                                                   
PUBLIC bool zps_bAplZdpUnpackRemoveBkupBindResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                    ZPS_tsAfZdpEvent* psReturnStruct);
                                                    
PUBLIC bool zps_bAplZdpUnpackMgmtLqiResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                             ZPS_tsAfZdpEvent* psReturnStruct);
                                             
PUBLIC bool zps_bAplZdpUnpackMgmtRtgResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                             ZPS_tsAfZdpEvent* psReturnStruct);
                                             
PUBLIC bool zps_bAplZdpUnpackNwkUpdateNotifyResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                     ZPS_tsAfZdpEvent* psReturnStruct);

PUBLIC bool zps_bAplZdpUnpackNwkUnsolicitedUpdateNotify(ZPS_tsAfEvent *psZdoServerEvent,
                                                     ZPS_tsAfZdpEvent* psReturnStruct );
                                                     
PUBLIC bool zps_bAplZdpUnpackComplexDescResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                 ZPS_tsAfZdpEvent* psReturnStruct);
                                                 
PUBLIC bool zps_bAplZdpUnpackUserDescResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                              ZPS_tsAfZdpEvent* psReturnStruct);
                                              
PUBLIC bool zps_bAplZdpUnpackUserDescConfirmResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                     ZPS_tsAfZdpEvent* psReturnStruct);
                                                     
PUBLIC bool zps_bAplZdpUnpackSystemServerDiscResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                      ZPS_tsAfZdpEvent* psReturnStruct);
                                                      
PUBLIC bool zps_bAplZdpUnpackBkupBindTableResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                   ZPS_tsAfZdpEvent* psReturnStruct);
                                                   
PUBLIC bool zps_bAplZdpUnpackPowerDescStoreResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                    ZPS_tsAfZdpEvent* psReturnStruct);
                                                    
PUBLIC bool zps_bAplZdpUnpackFindNodeCacheResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                   ZPS_tsAfZdpEvent* psReturnStruct);
                                                   
PUBLIC bool zps_bAplZdpUnpackExtendedSimpleDescResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                        ZPS_tsAfZdpEvent* psReturnStruct);
                                                        
PUBLIC bool zps_bAplZdpUnpackExtendedActiveEndpointResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                            ZPS_tsAfZdpEvent* psReturnStruct);
                                                            
PUBLIC bool zps_bAplZdpUnpackBindRegisterResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                  ZPS_tsAfZdpEvent* psReturnStruct);
                                                  
PUBLIC bool zps_bAplZdpUnpackRecoverBindTableResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                      ZPS_tsAfZdpEvent* psReturnStruct);
                                                      
PUBLIC bool zps_bAplZdpUnpackRecoverSourceBindResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                       ZPS_tsAfZdpEvent* psReturnStruct);                                               

                                                  
PUBLIC bool zps_bAplZdpUnpackMgmtNwkDiscResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                                 ZPS_tsAfZdpEvent* psReturnStruct);
                                                 
PUBLIC bool zps_bAplZdpUnpackMgmtBindResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                              ZPS_tsAfZdpEvent* psReturnStruct);
                                              
PUBLIC bool zps_bAplZdpUnpackMgmtCacheResponse(ZPS_tsAfEvent *psZdoServerEvent,
                                               ZPS_tsAfZdpEvent* psReturnStruct);
                                               
PUBLIC bool zps_bAplZdpUnpackResponse (ZPS_tsAfEvent *psZdoServerEvent,
                                       ZPS_tsAfZdpEvent* psReturnStruct);


#endif /* APPZDPEXTRACTION_H_ */
