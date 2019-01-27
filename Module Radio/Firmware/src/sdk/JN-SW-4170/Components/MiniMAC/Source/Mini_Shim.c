/****************************************************************************
 *
 * MODULE:             MiniMAC Shim
 *
 * DESCRIPTION:
 * Shim to make MiniMAC look like AppApi
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
 * Copyright NXP B.V. 2013. All rights reserved
 *
 ***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "AppApi.h"
#include "mac_sap.h"
#include "mac_pib.h"
#include "MiniMac.h"
#include "MiniMac_Pib.h"
#include "BbcAndPhyRegs.h"
#include "MicroSpecific.h"
#include "string.h"

extern PUBLIC uint8 u8MiniMac_RunTimeOptions;

extern PUBLIC void vMMAC_SetComplianceLimits(int8  i8TxMaxPower,
                                             int8  i8TxMaxPowerCh26,
                                             uint8 u8CcaThreshold);

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define MAX_TX_STORES (4)

/* Used by scan PAN descriptor store */
#define MAX_SCAN_BEACONS (MAC_MAX_SCAN_PAN_DESCRS)

#if !(defined WEAK)
#define WEAK              __attribute__ ((weak))
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE void **ppvGetBuffer(void ***pppvStore);
PRIVATE void vReturnBuffer(void **ppvBuffer, void ***pppvStore);
PRIVATE void vCopyFullAddrToNewFormat(MAC_Addr_s *psMacAddr, tsFullAddr *psMiniMacAddr);
PRIVATE void vCopyFullAddrToOldFormat(tsFullAddr *psMiniMacAddr, MAC_Addr_s *psMacAddr);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
PUBLIC WEAK uint8 const gMAC_u8MaxBuffers = MAX_TX_STORES;

#ifdef TOF_ENABLED
/* Handler for TOF extensions */
PUBLIC void (*prMAC_TofMlmeReqHandler)(void *pvMac,
                                       MAC_MlmeReqRsp_s *psMlmeReqRsp,
                                       MAC_MlmeSyncCfm_s *psMlmeSyncCfm);
#endif

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
PRIVATE PR_POST_CALLBACK prAppMlmeCallback;
PRIVATE PR_POST_CALLBACK prAppMcpsCallback;
PRIVATE PR_GET_BUFFER    prAppMlmeGetBuffer;
PRIVATE PR_GET_BUFFER    prAppMcpsGetBuffer;

PRIVATE tsTxFrameFormat asTxFrame[MAX_TX_STORES] MAC_BUFFER_SECTION;
PRIVATE tsRxFrameFormat sRxFrame MAC_BUFFER_SECTION;
PRIVATE void **pvTxStore;
PRIVATE void **pvRxStore;

PRIVATE tsExtAddr sReversedMacAddr;

/* Used by scan PAN descriptor store */
PRIVATE MAC_PanDescr_s asScanBeacons[MAX_SCAN_BEACONS];
PRIVATE uint8          u8ScanBeaconsSeen;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC uint32
u32AppApiInit(PR_GET_BUFFER prMlmeGetBuffer,
              PR_POST_CALLBACK prMlmeCallback,
              void *pvMlmeParam,
              PR_GET_BUFFER prMcpsGetBuffer,
              PR_POST_CALLBACK prMcpsCallback,
              void *pvMcpsParam)
{
    int i;

    /* Store callbacks */
    prAppMlmeCallback  = prMlmeCallback;
    prAppMcpsCallback  = prMcpsCallback;
    prAppMlmeGetBuffer = prMlmeGetBuffer;
    prAppMcpsGetBuffer = prMcpsGetBuffer;

    /* Set up TX and RX buffer queues */
    for (i = 0; i < (MAX_TX_STORES - 1); i++)
    {
        *(void **)&asTxFrame[i] = (void **)&asTxFrame[i + 1];
    }
    *(void **)&asTxFrame[MAX_TX_STORES - 1] = NULL;
    pvTxStore = (void **)&asTxFrame[0];
    *(void **)&sRxFrame = NULL;
    pvRxStore = (void **)&sRxFrame;

    /* Call MAC initialisation */
    vMiniMac_Init(E_MAC_RESET_PIB | E_MAC_RESET_INTERRUPT | E_MAC_RESET_STACK);

    /* Return value of 0 is reserved to indicate an error, so we return a
       non-0 value */
    return 1;
}

PUBLIC void *pvAppApiGetMacHandle(void)
{
    /* No MAC handle */
    return NULL;
}

/* MLME calls */
PUBLIC void
vAppApiMlmeRequest(MAC_MlmeReqRsp_s *psMlmeReqRsp,
                   MAC_MlmeSyncCfm_s *psMlmeSyncCfm)
{
    teMacStatus eMacStatus;

    /* Default value in case underlying code doesn't set it */
    psMlmeSyncCfm->u8ParamLength = 1;

    switch (psMlmeReqRsp->u8Type)
    {
    case MAC_MLME_REQ_ASSOCIATE:
        {
            MAC_MlmeReqAssociate_s *psMlmeReqRspAssoc = &psMlmeReqRsp->uParam.sReqAssociate;
            MAC_MlmeCfmAssociate_s *psMlmeSyncCfmAssoc = &psMlmeSyncCfm->uParam.sCfmAssociate;
            tsFullAddr sAddr;

            vCopyFullAddrToNewFormat(&psMlmeReqRspAssoc->sCoord, &sAddr);
            eMacStatus = eMiniMac_MLME_AssociateReq(
                             psMlmeReqRspAssoc->u8LogicalChan,
                             psMlmeReqRspAssoc->u8Capability,
                             &sAddr);

            psMlmeSyncCfm->u8ParamLength = sizeof(MAC_MlmeCfmAssociate_s);
            psMlmeSyncCfmAssoc->u8Status = eMacStatus;
            psMlmeSyncCfm->u8Status = (eMacStatus == MAC_ENUM_SUCCESS) ? MAC_MLME_CFM_DEFERRED : MAC_MLME_CFM_ERROR;
        }
        break;

    case MAC_MLME_REQ_DISASSOCIATE:
        {
            MAC_MlmeReqDisassociate_s *psMlmeReqRspDisass = &psMlmeReqRsp->uParam.sReqDisassociate;
            MAC_MlmeCfmDisassociate_s *psMlmeSyncCfmDisass = &psMlmeSyncCfm->uParam.sCfmDisassociate;
            tsFullAddr sAddr;

            vCopyFullAddrToNewFormat(&psMlmeReqRspDisass->sAddr, &sAddr);

            eMacStatus = eMiniMac_MLME_DisassociateReq(
                             &sAddr,
                             psMlmeReqRspDisass->u8Reason);

            psMlmeSyncCfm->u8ParamLength = sizeof(MAC_MlmeCfmDisassociate_s);
            psMlmeSyncCfmDisass->u8Status = eMacStatus;
            psMlmeSyncCfm->u8Status = (eMacStatus == MAC_ENUM_SUCCESS) ? MAC_MLME_CFM_DEFERRED : MAC_MLME_CFM_ERROR;
        }
        break;

    case MAC_MLME_REQ_RESET:
        vMiniMac_MLME_Reset(psMlmeReqRsp->uParam.sReqReset.u8SetDefaultPib);
        psMlmeSyncCfm->uParam.sCfmReset.u8Status = MAC_ENUM_SUCCESS;
        psMlmeSyncCfm->u8Status = MAC_MLME_CFM_OK;
        break;

    case MAC_MLME_REQ_RX_ENABLE:
        {
            MAC_MlmeReqRxEnable_s *psMlmeReqRx = &psMlmeReqRsp->uParam.sReqRxEnable;

            if (   (psMlmeReqRx->u8DeferPermit == FALSE)
                && (psMlmeReqRx->u32RxOnTime == 0)
               )
            {
                /* Parameters are valid for what we support */
                eMacStatus = eMiniMac_MLME_RxEnableReq(psMlmeReqRx->u32RxOnDuration);
            }
            else
            {
                /* Parameters not supported */
                eMacStatus = MAC_ENUM_INVALID_PARAMETER;
            }
            psMlmeSyncCfm->uParam.sCfmRxEnable.u8Status = eMacStatus;
            psMlmeSyncCfm->u8Status = (eMacStatus == MAC_ENUM_SUCCESS) ? MAC_MLME_CFM_OK : MAC_MLME_CFM_ERROR;
        }
        break;

    case MAC_MLME_REQ_SCAN:
        {
            MAC_MlmeReqScan_s *psMlmeReqScan = &psMlmeReqRsp->uParam.sReqScan;

            u8ScanBeaconsSeen = 0;

            eMacStatus = eMiniMac_MLME_ScanReq(
                             psMlmeReqScan->u32ScanChannels,
                             psMlmeReqScan->u8ScanType,
                             psMlmeReqScan->u8ScanDuration,
                             MAX_SCAN_BEACONS);

            psMlmeSyncCfm->uParam.sCfmScan.u8Status = eMacStatus;
            psMlmeSyncCfm->u8Status = (eMacStatus == MAC_ENUM_SUCCESS) ? MAC_MLME_CFM_DEFERRED : MAC_MLME_CFM_ERROR;
        }
        break;

    case MAC_MLME_REQ_START:
        {
            MAC_MlmeReqStart_s *psMlmeReqStart = &psMlmeReqRsp->uParam.sReqStart;
            MAC_MlmeCfmStart_s *psMlmeCfmStart = &psMlmeSyncCfm->uParam.sCfmStart;

            eMacStatus = eMiniMac_MLME_StartReq(
                             psMlmeReqStart->u16PanId,
                             psMlmeReqStart->u8Channel,
                             psMlmeReqStart->u8PanCoordinator,
                             psMlmeReqStart->u8Realignment);

            psMlmeCfmStart->u8Status = eMacStatus;
            psMlmeSyncCfm->u8Status = (eMacStatus == MAC_ENUM_SUCCESS) ? MAC_MLME_CFM_OK : MAC_MLME_CFM_ERROR;
        }
        break;

    case MAC_MLME_REQ_POLL:
        {
            MAC_MlmeReqPoll_s *psMlmeReqRspPoll = &psMlmeReqRsp->uParam.sReqPoll;
            MAC_MlmeCfmPoll_s *psMlmeSyncCfmPoll = &psMlmeSyncCfm->uParam.sCfmPoll;
            tuAddr uAddr;

            memcpy((uint8 *)&uAddr,
                   (uint8 *)&psMlmeReqRspPoll->sCoord.uAddr,
                   sizeof(tuAddr));

            eMacStatus = eMiniMac_MLME_DataReq(
                             psMlmeReqRspPoll->sCoord.u8AddrMode,
                             &uAddr);

            psMlmeSyncCfmPoll->u8Status = eMacStatus;
            psMlmeSyncCfm->u8Status = (eMacStatus == MAC_ENUM_SUCCESS) ? MAC_MLME_CFM_DEFERRED : MAC_MLME_CFM_ERROR;
        }
        break;

    case MAC_MLME_RSP_ASSOCIATE:
        {
            MAC_MlmeRspAssociate_s *psMlmeRspAssoc = &psMlmeReqRsp->uParam.sRspAssociate;
            tsExtAddr sAddr;

            sAddr.u32H = psMlmeRspAssoc->sDeviceAddr.u32H;
            sAddr.u32L = psMlmeRspAssoc->sDeviceAddr.u32L;

            psMlmeSyncCfm->u8Status = eMiniMac_MLME_AssociateResp(
                      psMlmeRspAssoc->u8Status,
                      psMlmeRspAssoc->u16AssocShortAddr,
                      &sAddr);
        }
        break;

    case MAC_MLME_RSP_ORPHAN:
        {
            MAC_MlmeRspOrphan_s *psMlmeRspOrphan = &psMlmeReqRsp->uParam.sRspOrphan;
            tsExtAddr sAddr;

            sAddr.u32H = psMlmeRspOrphan->sOrphanAddr.u32H;
            sAddr.u32L = psMlmeRspOrphan->sOrphanAddr.u32L;

            psMlmeSyncCfm->u8Status = eMiniMac_MLME_OrphanRsp(
                      &sAddr,
                      psMlmeRspOrphan->u16OrphanShortAddr);
        }
        break;

#ifdef TOF_ENABLED
    /* For time of flight */
    case MAC_MLME_REQ_TOFPOLL:
    case MAC_MLME_REQ_TOFPRIME:
    case MAC_MLME_REQ_TOFDATAPOLL:
    case MAC_MLME_REQ_TOFDATA:
        if (NULL != prMAC_TofMlmeReqHandler)
        {
            prMAC_TofMlmeReqHandler(NULL, psMlmeReqRsp, psMlmeSyncCfm);
        }
        break;
#endif


    default:
        /* ???? Unknown MLME Request ???? */
        psMlmeSyncCfm->u8Status = MAC_MLME_CFM_ERROR;
        psMlmeSyncCfm->u8ParamLength = 0;
        break;
    }
}

PUBLIC void
vAppApiMcpsRequest(MAC_McpsReqRsp_s *psMcpsReqRsp,
                   MAC_McpsSyncCfm_s *psMcpsSyncCfm)
{
    teMacStatus eMacStatus;
    tsTxFrameFormat *psFrame;

    psMcpsSyncCfm->u8Status = MAC_MCPS_CFM_ERROR; /* Catchall */
    psMcpsSyncCfm->u8ParamLength = 0; /* Usual case */
    switch (psMcpsReqRsp->u8Type)
    {
    case MAC_MCPS_REQ_DATA:
    case MAC_MCPS_REQ_DATA_EXTENDED:
        {
            tsTxFrameFormat *psTxFrame;
            MAC_McpsReqData_s *psMcpsReqData = &psMcpsReqRsp->uParam.sReqData;

            psMcpsSyncCfm->u8ParamLength = sizeof(MAC_McpsCfmData_s);
            psMcpsSyncCfm->uParam.sCfmData.u8Handle = psMcpsReqData->u8Handle;

            /* Get frame buffer */
            psTxFrame = psGetTxFrameBuffer();
            if (psTxFrame == NULL)
            {
                eMacStatus = MAC_ENUM_TRANSACTION_OVERFLOW;
            }
            else
            {
                /* Convert from old to new frame format */
                psTxFrame->sFrameBody.u8PayloadLength    = psMcpsReqData->sFrame.u8SduLength;
                psTxFrame->sFrameBody.u16FCF             = FCF_PUT_DST_ADDR_MODE(psMcpsReqData->sFrame.sDstAddr.u8AddrMode)
                                                           | FCF_PUT_SRC_ADDR_MODE(psMcpsReqData->sFrame.sSrcAddr.u8AddrMode);
                psTxFrame->sFrameBody.u16DestPAN         = psMcpsReqData->sFrame.sDstAddr.u16PanId;
                psTxFrame->sFrameBody.u16SrcPAN          = psMcpsReqData->sFrame.sSrcAddr.u16PanId;
                if (psMcpsReqData->sFrame.u8TxOptions & MAC_TX_OPTION_SECURITY)
                {
                    psTxFrame->sSecurityData.u8SecurityLevel = psMcpsReqData->sFrame.sSecurityData.u8SecurityLevel;
                    psTxFrame->sSecurityData.u8KeyIdMode     = psMcpsReqData->sFrame.sSecurityData.u8KeyIdMode;
                    psTxFrame->sSecurityData.u8KeyIndex      = psMcpsReqData->sFrame.sSecurityData.u8KeyIndex;
                }
                psTxFrame->u8TxOptions                   = psMcpsReqData->sFrame.u8TxOptions;
                psTxFrame->u8Handle                      = psMcpsReqData->u8Handle;
                if (MAC_MCPS_REQ_DATA_EXTENDED == psMcpsReqRsp->u8Type)
                {
                    psTxFrame->u8Channel = psMcpsReqData->u8Channel;
                }
                memcpy((uint8 *)&psTxFrame->sFrameBody.uDestAddr,
                       (uint8 *)&psMcpsReqData->sFrame.sDstAddr.uAddr,
                       sizeof(tuAddr));
                memcpy((uint8 *)&psTxFrame->sFrameBody.uSrcAddr,
                       (uint8 *)&psMcpsReqData->sFrame.sSrcAddr.uAddr,
                       sizeof(tuAddr));
                memcpy(psTxFrame->sFrameBody.uPayload.au8Byte,
                       psMcpsReqData->sFrame.au8Sdu,
                       psMcpsReqData->sFrame.u8SduLength);

                eMacStatus = eMiniMac_MCPS_DataReq(psTxFrame,
                                                   E_RETURN_BUFFER_TO_POOL_ON_FAIL);
            }

            switch (eMacStatus)
            {
            case MAC_ENUM_SUCCESS:
                psMcpsSyncCfm->u8Status = MAC_MCPS_CFM_DEFERRED;
                psMcpsSyncCfm->uParam.sCfmData.u8Status = MAC_MCPS_CFM_DEFERRED;
                break;

            default:
                psMcpsSyncCfm->u8Status = MAC_MCPS_CFM_ERROR;
                psMcpsSyncCfm->uParam.sCfmData.u8Status = eMacStatus;
                break;
            }
        }
        break;

    case MAC_MCPS_REQ_PURGE:
        psMcpsSyncCfm->u8ParamLength = sizeof(MAC_McpsCfmPurge_s);
        psMcpsSyncCfm->uParam.sCfmPurge.u8Handle = psMcpsReqRsp->uParam.sReqPurge.u8Handle;

        if (MAC_ENUM_SUCCESS == eMiniMac_MCPS_PurgeReq(psMcpsReqRsp->uParam.sReqPurge.u8Handle, &psFrame))
        {
            /* Frame was found */
            psMcpsSyncCfm->uParam.sCfmPurge.u8Status = MAC_ENUM_SUCCESS;
            psMcpsSyncCfm->u8Status = MAC_MCPS_CFM_OK;

            /* If buffer no longer in use, free it */
            if (psFrame)
            {
                vMiniMac_ReturnTxBufferCallback(psFrame);
            }
        }
        else
        {
            /* Frame was not found */
            psMcpsSyncCfm->uParam.sCfmPurge.u8Status = MAC_ENUM_INVALID_HANDLE;
            psMcpsSyncCfm->u8Status = MAC_MCPS_CFM_ERROR;
        }
        break;

    default:
        /* ???? Unknown MCPS Request ???? */
        break;
    }
}

/* PLME calls */
PUBLIC WEAK PHY_Enum_e eAppApiPlmeSet(PHY_PibAttr_e ePhyPibAttribute,
                                      uint32 u32PhyPibValue)
{
    PHY_Enum_e eReturnCode = PHY_ENUM_SUCCESS;

    switch (ePhyPibAttribute)
    {
    case PHY_PIB_ATTR_CURRENT_CHANNEL:
        vMiniMac_PLME_SetReq_Channel((uint8)u32PhyPibValue);
        break;

    case PHY_PIB_ATTR_TX_POWER:
        vMiniMac_PLME_SetReq_Power((uint8)u32PhyPibValue);
        break;

    case PHY_PIB_ATTR_CCA_MODE:
        vMiniMac_PLME_SetReq_CcaMode((uint8)u32PhyPibValue);
        break;

    default:
        eReturnCode = PHY_ENUM_UNSUPPORTED_ATTRIBUTE;
        break;
    }

    return eReturnCode;
}

PUBLIC WEAK PHY_Enum_e eAppApiPlmeGet(PHY_PibAttr_e ePhyPibAttribute,
                                      uint32 *pu32PhyPibValue)
{
    PHY_Enum_e eReturnCode = PHY_ENUM_SUCCESS;

    switch (ePhyPibAttribute)
    {
        case PHY_PIB_ATTR_CURRENT_CHANNEL:
            *pu32PhyPibValue = (uint32)sMiniMacPhyPib.u8Channel;
            break;

        case PHY_PIB_ATTR_TX_POWER:
            *pu32PhyPibValue = (uint32)sMiniMacPhyPib.i8Power;
            break;

        case PHY_PIB_ATTR_CCA_MODE:
            *pu32PhyPibValue = (u32REG_PhyRead(REG_PHY_MCCA)
                                & REG_PHY_MCCA_CCAM_MASK)
                               >> REG_PHY_MCCA_CCAM_BIT;
            break;

        case PHY_PIB_ATTR_CHANNELS_SUPPORTED:
            *pu32PhyPibValue = PHY_PIB_CHANNELS_SUPPORTED_DEF;
            break;

        default:
            eReturnCode = PHY_ENUM_UNSUPPORTED_ATTRIBUTE;
            break;
    }

    return eReturnCode;
}

PUBLIC WEAK void *pvAppApiGetMacAddrLocation(void)
{
    sReversedMacAddr.u32L = sThisDeviceMacAddr.u32H;
    sReversedMacAddr.u32H = sThisDeviceMacAddr.u32L;
    return (void *)&sReversedMacAddr;
}

PUBLIC void  vAppApiSaveMacSettings(void)
{
    vMiniMac_SaveSettings();
}

PUBLIC void  vAppApiRestoreMacSettings(void)
{
    vMiniMac_Init(E_MAC_RESET_INTERRUPT);
}

PUBLIC WEAK void vAppApiEnableBeaconResponse(bool_t bEnable)
{
    /* Now using LQI threshold: to enable beacon response, set threshold to 0
       so all beacon requests are accepted. Conversely to disable beacon
       response set to 255 so all beacon requests with LQI <= 255 are
       discarded (which will be all of them, as LQI maximum is 255) */
    sMiniMacPib.u8BeaconRequestLqiThreshold = bEnable ? 0 : 255;
}

PUBLIC void vAppApiSetSecurityMode(MAC_SecutityMode_e eSecurityMode)
{
}

PUBLIC void vMAC_RestoreSettings(void)
{
    vMiniMac_Init(0);
}

PUBLIC bool_t bAppApi_CurrentlyScanning(void)
{
    return bMiniMac_CurrentlyScanning();
}

/* Note that this function is defiend for all JN516x derivatives, but only
   valid for the JN5169. Trying to use it with a JN5161/4/8 will cause a
   link-time error. Function is retained to avoid requiring a separate library
   file specifically for the JN5169 */
PUBLIC void vAppApiSetComplianceLimits(int8  i8TxMaxPower,
                                       int8  i8TxMaxPowerCh26,
                                       uint8 u8CcaThreshold)
{
    /* Simple wrapper for MMAC function */
    vMMAC_SetComplianceLimits(i8TxMaxPower,
                              i8TxMaxPowerCh26,
                              u8CcaThreshold);
}

PUBLIC void vAppApiSetHighPowerMode(uint8 u8ModuleID, bool_t bMode)
{
    vMiniMac_SetHighPowerMode(u8ModuleID);
}

PUBLIC MAC_Pib_s *MAC_psPibGetHandle(void *pvMac)
{
    return (MAC_Pib_s *)&sMiniMacPib;
}

PUBLIC WEAK void MAC_vPibSetShortAddr(void *pvMac, uint16 u16ShortAddr)
{
    vMiniMac_MLME_SetReq_ShortAddr(u16ShortAddr);
}

PUBLIC WEAK void MAC_vPibSetPanId(void *pvMac, uint16 u16PanId)
{
    vMiniMac_MLME_SetReq_PanId(u16PanId);
}

PUBLIC WEAK void MAC_vPibSetMinBe(void *pvMac, uint8 u8MinBe)
{
    vMiniMac_MLME_SetReq_MinBe(u8MinBe);
}

PUBLIC WEAK void MAC_vPibSetMaxBe(void *pvMac, uint8 u8MinBe)
{
    vMiniMac_MLME_SetReq_MaxBe(u8MinBe);
}

PUBLIC WEAK void MAC_vPibSetMaxCsmaBackoffs(void *pvMac, uint8 u8MaxCsmaBackoffs)
{
    vMiniMac_MLME_SetReq_MaxCsmaBackoffs(u8MaxCsmaBackoffs);
}

PUBLIC WEAK void MAC_vPibSetPromiscuousMode(void *pvMac, bool_t bNewState, bool_t bInReset)
{
    /* Does nothing */
}

PUBLIC WEAK void MAC_vPibSetRxOnWhenIdle(void *pvMac, bool_t bNewState, bool_t bInReset)
{
    vMiniMac_MLME_SetReq_RxOnWhenIdle(bNewState);
}

PUBLIC WEAK void MAC_vSetExtAddr(void *pvMac, MAC_ExtAddr_s *psExtAddr)
{
    sThisDeviceMacAddr.u32H = psExtAddr->u32H;
    sThisDeviceMacAddr.u32L = psExtAddr->u32L;

    /* Set address match registers by calling API function to set PAN ID to
       currently-set PAN ID, which has the side effect of setting the match
       registers */
    vMiniMac_MLME_SetReq_PanId(sMiniMacPib.u16PanId_ReadOnly);
}

PUBLIC bool_t bTACframeInProgress(void)
{
    if (E_FIP_NONE == eMiniMac_FrameInProgress())
    {
        return FALSE;
    }

    return TRUE;
}

PUBLIC WEAK void vTAM_MLME_RxInCca(bool_t bEnable)
{
    if (bEnable)
    {
        u8MiniMac_RunTimeOptions |= 1;
    }
    else
    {
        u8MiniMac_RunTimeOptions &= ~1;
    }
}

PUBLIC WEAK void vMiniMac_MlmeCallback(tsMlmeGeneric *psMlmeDcfmInd)
{
    MAC_MlmeDcfmInd_s *psOldInd;

    /* Get old-style event structure */
    psOldInd = (MAC_MlmeDcfmInd_s *)prAppMlmeGetBuffer(NULL);

    if (NULL == psOldInd)
    {
        /* No buffer: drop event */
        return;
    }

    psOldInd->u8Type = psMlmeDcfmInd->u8Type;

    /* Place event into old-style structure */
    switch (psMlmeDcfmInd->u8Type)
    {
    case MAC_MLME_DCFM_SCAN:
        {
            tsMlmeScanDcfm *psNewInd = (tsMlmeScanDcfm *)psMlmeDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_MlmeCfmScan_s);

            psOldInd->uParam.sDcfmScan.u8Status = psNewInd->u8Status;
            psOldInd->uParam.sDcfmScan.u8ScanType = psNewInd->u8ScanType;
            psOldInd->uParam.sDcfmScan.u8ResultListSize = psNewInd->u8ResultListSize;
            psOldInd->uParam.sDcfmScan.u32UnscannedChannels = psNewInd->u32UnscannedChannels;
            memcpy(psOldInd->uParam.sDcfmScan.uList.au8EnergyDetect,
                   psNewInd->au8EnergyDetect,
                   psNewInd->u8ResultListSize);

            if (   (psOldInd->uParam.sDcfmScan.u8ScanType == MAC_MLME_SCAN_TYPE_ACTIVE )
                || (psOldInd->uParam.sDcfmScan.u8ScanType == MAC_MLME_SCAN_TYPE_PASSIVE)
               )
            {
                /* Copy in beacons and unscanned channels that have been
                   stored by the shim layer */
                memcpy((uint8 *)psOldInd->uParam.sDcfmScan.uList.asPanDescr,
                       (uint8 *)asScanBeacons,
                       sizeof(MAC_PanDescr_s) * u8ScanBeaconsSeen);

                psOldInd->uParam.sDcfmScan.u8ResultListSize = u8ScanBeaconsSeen;
            }
        }
        break;

    case MAC_MLME_DCFM_ASSOCIATE:
        {
            tsMlmeAssocDcfm *psNewInd = (tsMlmeAssocDcfm *)psMlmeDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_MlmeCfmAssociate_s);

            psOldInd->uParam.sDcfmAssociate.u8Status = psNewInd->u8Status;
            psOldInd->uParam.sDcfmAssociate.u16AssocShortAddr = psNewInd->u16AssocShortAddr;
            psOldInd->uParam.sDcfmAssociate.sSecurityData.u8SecurityLevel = 0;
        }
        break;

    case MAC_MLME_DCFM_DISASSOCIATE:
        {
            tsMlmeDisassocDcfm *psNewInd = (tsMlmeDisassocDcfm *)psMlmeDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_MlmeCfmDisassociate_s);

            psOldInd->uParam.sDcfmDisassociate.u8Status = psNewInd->u8Status;
        }
        break;

    case MAC_MLME_DCFM_POLL:
        {
            tsMlmePollDcfm *psNewInd = (tsMlmePollDcfm *)psMlmeDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_MlmeCfmPoll_s);

            psOldInd->uParam.sDcfmPoll.u8Status = psNewInd->u8Status;
        }
        break;

    case MAC_MLME_IND_ASSOCIATE:
        {
            tsMlmeAssocInd *psNewInd = (tsMlmeAssocInd *)psMlmeDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_MlmeIndAssociate_s);

            psOldInd->uParam.sIndAssociate.sDeviceAddr.u32H = psNewInd->sDeviceAddr.u32H;
            psOldInd->uParam.sIndAssociate.sDeviceAddr.u32L = psNewInd->sDeviceAddr.u32L;
            psOldInd->uParam.sIndAssociate.u8Capability = psNewInd->u8Capability;
            psOldInd->uParam.sIndAssociate.u8SecurityUse = FALSE;
        }
        break;

    case MAC_MLME_IND_DISASSOCIATE:
        {
            tsMlmeDisassocInd *psNewInd = (tsMlmeDisassocInd *)psMlmeDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_MlmeIndDisassociate_s);

            psOldInd->uParam.sIndDisassociate.sDeviceAddr.u32H = psNewInd->sDeviceAddr.u32H;
            psOldInd->uParam.sIndDisassociate.sDeviceAddr.u32L = psNewInd->sDeviceAddr.u32L;
            psOldInd->uParam.sIndDisassociate.u8Reason = psNewInd->u8Reason;
            psOldInd->uParam.sIndDisassociate.u8SecurityUse = FALSE;
        }
        break;

    case MAC_MLME_IND_BEACON_NOTIFY:
        {
            tsMlmeBeaconNotifyInd *psNewInd = (tsMlmeBeaconNotifyInd *)psMlmeDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_MlmeIndBeacon_s);

            psOldInd->uParam.sIndBeacon.sPANdescriptor.sCoord.u8AddrMode = psNewInd->sPanDescriptor.u8CoordAddrMode;
            psOldInd->uParam.sIndBeacon.sPANdescriptor.sCoord.u16PanId = psNewInd->sPanDescriptor.u16CoordPanId;
            memcpy((uint8 *)&psOldInd->uParam.sIndBeacon.sPANdescriptor.sCoord.uAddr,
                   (uint8 *)&psNewInd->sPanDescriptor.uCoordAddr,
                   sizeof(tuAddr));
            psOldInd->uParam.sIndBeacon.sPANdescriptor.u8LogicalChan = psNewInd->sPanDescriptor.u8LogicalChan;
            psOldInd->uParam.sIndBeacon.sPANdescriptor.u8GtsPermit = psNewInd->sPanDescriptor.u8GtsPermit;
            psOldInd->uParam.sIndBeacon.sPANdescriptor.u8LinkQuality = psNewInd->sPanDescriptor.u8LinkQuality;
            psOldInd->uParam.sIndBeacon.sPANdescriptor.u8SecurityUse = FALSE;
            psOldInd->uParam.sIndBeacon.sPANdescriptor.u8AclEntry = 0;
            psOldInd->uParam.sIndBeacon.sPANdescriptor.u8SecurityFailure = FALSE;
            psOldInd->uParam.sIndBeacon.sPANdescriptor.u16SuperframeSpec = psNewInd->sPanDescriptor.u16SuperframeSpec;
            psOldInd->uParam.sIndBeacon.sPANdescriptor.u32TimeStamp = psNewInd->sPanDescriptor.u32TimeStamp;
            psOldInd->uParam.sIndBeacon.u8BSN = psNewInd->u8BSN;
            psOldInd->uParam.sIndBeacon.u8PendAddrSpec = psNewInd->u8PendAddrSpec;
            psOldInd->uParam.sIndBeacon.u8SDUlength = psNewInd->u8SDUlength;
            memcpy((uint8 *)psOldInd->uParam.sIndBeacon.uAddrList,
                   (uint8 *)psNewInd->auAddrList,
                   sizeof(tuAddr) * 7);
            memcpy(psOldInd->uParam.sIndBeacon.u8SDU,
                   psNewInd->au8SDU,
                   psNewInd->u8SDUlength);

            /* If scanning:
                  store result locally
                  if no more space for result, record channel list and reject
                  reject beacon notify if beacon payload length is 0
             */
            if (bAppApi_CurrentlyScanning())
            {
                /* This code effectively implements the case where
                   macAutoRequest=TRUE, storing the beacon notifications
                   locally to be returned with the Scan.Dcf and discarding
                   beacon notifications where the payload length is 0. The
                   MiniMAC itself implements scan with macAutoRequest=FALSE:
                   it always passes up all beacons and does not store them to
                   pass up with the Scan.Dcf */
                if (u8ScanBeaconsSeen < MAX_SCAN_BEACONS)
                {
                    asScanBeacons[u8ScanBeaconsSeen] = psOldInd->uParam.sIndBeacon.sPANdescriptor;
                    u8ScanBeaconsSeen++;

                    /* Reject indication if payload not present */
                    if (psOldInd->uParam.sIndBeacon.u8SDUlength == 0)
                    {
                        psOldInd->u8ParamLength = 0;
                        psOldInd->u8Type = MAC_MLME_REJECT;
                    }
                }
                else
                {
                    /* Reject beacon */
                    psOldInd->u8ParamLength = 0;
                    psOldInd->u8Type = MAC_MLME_REJECT;
                }
            }
        }
        break;

    case MAC_MLME_IND_COMM_STATUS:
        {
            tsMlmeCommStatusInd *psNewInd = (tsMlmeCommStatusInd *)psMlmeDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_MlmeIndCommStatus_s);

            vCopyFullAddrToOldFormat(&psNewInd->sSrcAddr, &psOldInd->uParam.sIndCommStatus.sSrcAddr);
            vCopyFullAddrToOldFormat(&psNewInd->sDstAddr, &psOldInd->uParam.sIndCommStatus.sDstAddr);
            psOldInd->uParam.sIndCommStatus.u8Status = psNewInd->u8Status;
            psOldInd->uParam.sIndCommStatus.sSecurityData.u8SecurityLevel = psNewInd->sSecurityData.u8SecurityLevel;
            psOldInd->uParam.sIndCommStatus.sSecurityData.u8KeyIdMode = psNewInd->sSecurityData.u8KeyIdMode;
            psOldInd->uParam.sIndCommStatus.sSecurityData.u8KeyIndex = psNewInd->sSecurityData.u8KeyIndex;
        }
        break;

    case MAC_MLME_IND_ORPHAN:
        {
            tsMlmeOrphanInd *psNewInd = (tsMlmeOrphanInd *)psMlmeDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_MlmeIndOrphan_s);

            psOldInd->uParam.sIndOrphan.sDeviceAddr.u32H = psNewInd->sDeviceAddr.u32H;
            psOldInd->uParam.sIndOrphan.sDeviceAddr.u32L = psNewInd->sDeviceAddr.u32L;
            psOldInd->uParam.sIndOrphan.u8SecurityUse = FALSE;
            psOldInd->uParam.sIndOrphan.u8AclEntry = 0;
        }
        break;

    default:
        psOldInd->u8ParamLength = 0;
        psOldInd->u8Type = MAC_MLME_INVALID;
        break;
    }

    /* Call higher layer callback */
    prAppMlmeCallback(NULL, (MAC_DcfmIndHdr_s *)psOldInd);
}

PUBLIC WEAK void vMiniMac_McpsCallback(tsMcpsGeneric *psMcpsDcfmInd)
{
    MAC_McpsDcfmInd_s *psOldInd;

    /* Get old-style event structure */
    psOldInd = (MAC_McpsDcfmInd_s *)prAppMcpsGetBuffer(NULL);

    if (NULL == psOldInd)
    {
        /* No buffer: drop event */
        return;
    }

    psOldInd->u8Type = psMcpsDcfmInd->u8Type;

    switch (psMcpsDcfmInd->u8Type)
    {
    case MAC_MCPS_DCFM_DATA:
        {
            tsMcpsDataDcfm *psNewInd = (tsMcpsDataDcfm *)psMcpsDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_McpsCfmData_s);

            psOldInd->uParam.sDcfmData.u8Handle = psNewInd->psFrame->u8Handle;
            psOldInd->uParam.sDcfmData.u8Status = psNewInd->u8Status;
            psOldInd->uParam.sDcfmData.u8TriesLeft = psNewInd->psFrame->u8TriesLeft;
            psOldInd->uParam.sDcfmData.u32Timestamp = psNewInd->u32Timestamp;

            if (MAC_ENUM_TRANSACTION_OVERFLOW == psNewInd->u8Status)
            {
                /* Actually a purged frame: should discard it */
                psOldInd->u8Type = MAC_MCPS_REJECT;
            }

            /* Return buffer to pool */
            vMiniMac_ReturnTxBufferCallback(psNewInd->psFrame);
        }
        break;

    case MAC_MCPS_IND_DATA:
        {
            tsMcpsDataInd *psNewInd = (tsMcpsDataInd *)psMcpsDcfmInd;

            psOldInd->u8ParamLength = sizeof(MAC_McpsIndData_s);

            psOldInd->uParam.sIndData.sFrame.sSrcAddr.u8AddrMode = FCF_GET_SRC_ADDR_MODE(psNewInd->psFrame->sFrameBody.u16FCF);
            psOldInd->uParam.sIndData.sFrame.sSrcAddr.u16PanId = psNewInd->psFrame->sFrameBody.u16SrcPAN;
            memcpy((uint8 *)&psOldInd->uParam.sIndData.sFrame.sSrcAddr.uAddr,
                   (uint8 *)&psNewInd->psFrame->sFrameBody.uSrcAddr,
                   sizeof(tuAddr));
            psOldInd->uParam.sIndData.sFrame.sDstAddr.u8AddrMode = FCF_GET_DST_ADDR_MODE(psNewInd->psFrame->sFrameBody.u16FCF);
            psOldInd->uParam.sIndData.sFrame.sDstAddr.u16PanId = psNewInd->psFrame->sFrameBody.u16DestPAN;
            memcpy((uint8 *)&psOldInd->uParam.sIndData.sFrame.sDstAddr.uAddr,
                   (uint8 *)&psNewInd->psFrame->sFrameBody.uDestAddr,
                   sizeof(tuAddr));
            psOldInd->uParam.sIndData.sFrame.u8LinkQuality = (uint8)psNewInd->psFrame->u8LinkQuality;
            psOldInd->uParam.sIndData.sFrame.u8SecurityUse = (psNewInd->psFrame->sSecurityData.u8SecurityLevel != 0) ? TRUE : FALSE;
            psOldInd->uParam.sIndData.sFrame.u8AclEntry = psNewInd->psFrame->sSecurityData.u8SecurityLevel;
            psOldInd->uParam.sIndData.sFrame.u8SduLength = psNewInd->psFrame->sFrameBody.u8PayloadLength;
            memcpy(psOldInd->uParam.sIndData.sFrame.au8Sdu,
                   psNewInd->psFrame->sFrameBody.uPayload.au8Byte,
                   psOldInd->uParam.sIndData.sFrame.u8SduLength);
            psOldInd->uParam.sIndData.sFrame.u8DSN = psNewInd->psFrame->sFrameBody.u8SequenceNum;
            psOldInd->uParam.sIndData.sFrame.u32Timestamp = psNewInd->psFrame->u32Timestamp;
            psOldInd->uParam.sIndData.sFrame.sSecurityData.u8SecurityLevel = psNewInd->psFrame->sSecurityData.u8SecurityLevel;
            psOldInd->uParam.sIndData.sFrame.sSecurityData.u8KeyIdMode = psNewInd->psFrame->sSecurityData.u8KeyIdMode;
            psOldInd->uParam.sIndData.sFrame.sSecurityData.u8KeyIndex = psNewInd->psFrame->sSecurityData.u8KeyIndex;

            vMiniMac_ReturnRxBufferCallback(psNewInd->psFrame);
        }
        break;

    /* Purge is dealt with directly */

    default:
        psOldInd->u8Type = MAC_MCPS_INVALID;
        psOldInd->u8ParamLength = 0;
        break;
    }

    /* Call higher layer callback */
    prAppMcpsCallback(NULL, (MAC_DcfmIndHdr_s *)psOldInd);
}

PUBLIC WEAK void vMiniMac_DataRequestCallback(tsRxFrameFormat *psFrame)
{
    /* Does nothing */
}

PUBLIC WEAK tsTxFrameFormat *psMiniMac_GetTxBufferCallback(void)
{
    return (tsTxFrameFormat *)ppvGetBuffer(&pvTxStore);
}

PUBLIC WEAK tsRxFrameFormat *psMiniMac_GetRxBufferCallback(void)
{
    return (tsRxFrameFormat *)ppvGetBuffer(&pvRxStore);
}

PUBLIC WEAK void vMiniMac_ReturnTxBufferCallback(tsTxFrameFormat *psBuffer)
{
    vReturnBuffer((void **)psBuffer, &pvTxStore);
}

PUBLIC WEAK void vMiniMac_ReturnRxBufferCallback(tsRxFrameFormat *psBuffer)
{
    vReturnBuffer((void **)psBuffer, &pvRxStore);
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
PRIVATE void **ppvGetBuffer(void ***pppvStore)
{
    void **ppvBuffer;
    uint32 u32Store;

    MICRO_DISABLE_AND_SAVE_INTERRUPTS(u32Store);
    if (*pppvStore)
    {
        ppvBuffer = *pppvStore;
        *pppvStore = (void **)(*ppvBuffer);
    }
    else
    {
        ppvBuffer = NULL;
    }
    MICRO_RESTORE_INTERRUPTS(u32Store);

    return ppvBuffer;
}

PRIVATE void vReturnBuffer(void **ppvBuffer, void ***pppvStore)
{
    uint32 u32Store;

    MICRO_DISABLE_AND_SAVE_INTERRUPTS(u32Store);
    *ppvBuffer = (void *)*pppvStore;
    *pppvStore = ppvBuffer;
    MICRO_RESTORE_INTERRUPTS(u32Store);
}

PRIVATE void vCopyFullAddrToNewFormat(MAC_Addr_s *psMacAddr, tsFullAddr *psMiniMacAddr)
{
    psMiniMacAddr->u16PanId = psMacAddr->u16PanId;
    psMiniMacAddr->u8AddrMode = psMacAddr->u8AddrMode;
    memcpy((uint8 *)&psMiniMacAddr->uAddr,
           (uint8 *)&psMacAddr->uAddr,
           sizeof(tuAddr));
}

PRIVATE void vCopyFullAddrToOldFormat(tsFullAddr *psMiniMacAddr, MAC_Addr_s *psMacAddr)
{
    psMacAddr->u16PanId = psMiniMacAddr->u16PanId;
    psMacAddr->u8AddrMode = psMiniMacAddr->u8AddrMode;
    memcpy((uint8 *)&psMacAddr->uAddr,
           (uint8 *)&psMiniMacAddr->uAddr,
           sizeof(tuAddr));
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
