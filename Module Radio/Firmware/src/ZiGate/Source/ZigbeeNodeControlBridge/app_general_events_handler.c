/*****************************************************************************
 *
 * MODULE: ZigbeeNodeControlBridge
 *
 * COMPONENT: app_general_events_handler.c
 *
 * $AUTHOR: Faisal Bhaiyat$
 *
 * DESCRIPTION:
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy:  $
 *
 * $LastChangedDate:  $
 *
 * $Id: a $
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

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include "jendefs.h"
#include "string.h"
#include "pdum_apl.h"
#include "dbg.h"
#include "PDM.h"
#include "pdum_gen.h"
#include "zps_gen.h"
#include "zps_apl.h"
#include "zps_nwk_nib.h"
#include "zps_apl_aib.h"
#include "zps_apl_zdo.h"
#include "zps_apl_af.h"
#include "app_Znc_cmds.h"
#include "SerialLink.h"
#include "pwrm.h"
#include "uart.h"
#include "app_common.h"
#include "app_events.h"
#include "rnd_pub.h"
#include "Log.h"
#include "mac_sap.h"
#include "PDM_IDs.h"
#include "appZdpExtraction.h"
#include "bdb_DeviceCommissioning.h"

#ifdef CLD_OTA
#include "app_ota_server.h"
#endif

#ifdef CLD_GREENPOWER
#include "App_green_power.h"
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#ifndef TRACE_APP
#define TRACE_APP TRUE
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
#ifdef FULL_FUNC_DEVICE
PUBLIC bool bAddToEndpointTable ( APP_tsEventTouchLink*    psEndpointData );
PUBLIC void vAppIdentifyEffect ( teCLD_Identify_EffectId    eEffect );
PRIVATE uint8 u8SearchEndpointTable  ( APP_tsEventTouchLink*    psEndpointData,
                                       uint8*                   pu8Index );
#endif
extern void *ZPS_pvNwkSecGetNetworkKey ( void*    pvNwk );
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

uint32    sStorage;

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
#ifdef FULL_FUNC_DEVICE
PRIVATE bool_t    bAddrMode;
#endif
extern tsLedState    s_sLedState;
extern uint8         u8JoinedDevice;

/****************************************************************************/
/***        Exported Public Functions                                     ***/
/****************************************************************************/


/****************************************************************************/
/***        Exported Private Functions                                         */
/****************************************************************************/


/***************************************************************************/
/***          Local Private Functions                                      */
/***************************************************************************/


PRIVATE void APP_vWrite64Nbo ( uint64    u64dWord,
                               uint8*    pu8Payload );

/****************************************************************************
 *
 * NAME: APP_taskAtParser
 *
 * DESCRIPTION:
 *
 *
 ****************************************************************************/
void APP_vProcessRxData ( void )
{
    uint8    u8RxByte;

    if ( ZQ_bQueueReceive ( &APP_msgSerialRx, &u8RxByte ) ) {
        APP_vProcessIncomingSerialCommands ( u8RxByte);
    }

    vAHI_WatchdogRestart ( );

}

/****************************************************************************
 *
 * NAME: APP_vHandleAppEvents
 *
 * DESCRIPTION:
 *
 *
 ****************************************************************************/
PUBLIC void APP_vHandleAppEvents ( void )
{
    APP_tsEvent              sAppEvent;
    uint8                    au8LinkTxBuffer[256];
    uint16                   u16Length =  0;
#ifdef FULL_FUNC_DEVICE
    uint8                    u8SeqNo =  0xaf;
#endif
    ZPS_tsNwkNib*            psNib =  ZPS_psAplZdoGetNib( );

    sAppEvent.eType = APP_E_EVENT_NONE;
    if ( ZQ_bQueueReceive ( &APP_msgAppEvents, &sAppEvent ) )
    {
#ifdef CLD_GREENPOWER
		if ( sAppEvent.eType == APP_EVENT_POR_RESET_GP_TABLES )
		{
			vAPP_GP_ResetData();
		}
#endif	

#ifdef FULL_FUNC_DEVICE
        if ( sAppEvent.eType == APP_E_EVENT_START_ROUTER )
        {
            APP_vForceStartRouter ( au8LinkTxBuffer );
        }
#endif
        if( sAppEvent.eType == APP_E_EVENT_TRANSPORT_HA_KEY )
        {
            ZPS_tuAddress    uDstAddress;

            uDstAddress.u64Addr =  sAppEvent.uEvent.u64TransportKeyAddress;
            ZPS_eAplAibSetApsTrustCenterAddress ( 0xffffffffffffffffULL );
            ZPS_eAplZdoTransportNwkKey ( ZPS_E_ADDR_MODE_IEEE,
                                         uDstAddress,
                                         psNib->sTbl.psSecMatSet[0].au8Key,
                                         psNib->sTbl.psSecMatSet[0].u8KeySeqNum,
                                         FALSE,
                                         0 );
            ZPS_eAplAibSetApsTrustCenterAddress ( ZPS_u64NwkNibGetExtAddr ( ZPS_pvAplZdoGetNwkHandle ( ) ) );
        }


        if(sAppEvent.eType == APP_E_EVENT_SEND_PERMIT_JOIN)
        {
            bool_t    bStatus =  ZPS_vNwkGetPermitJoiningStatus ( ZPS_pvAplZdoGetNwkHandle ( ) );
            ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [0], bStatus, u16Length );
            vSL_WriteMessage ( E_SL_MSG_GET_PERMIT_JOIN_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               0);
        }

        if(sAppEvent.eType == APP_E_EVENT_NETWORK_STATE)
        {
            extern uint32 u32Channel;
            uint16 u16NwkAddr;
            uint64 u64IeeeAddr;
            uint64 u64PANID;
            uint16 u16PANID;
            uint16 u16TxSize = 0;

            u16NwkAddr = ZPS_u16NwkNibGetNwkAddr(ZPS_pvAplZdoGetNwkHandle());
            u64IeeeAddr = ZPS_u64NwkNibGetExtAddr(ZPS_pvAplZdoGetNwkHandle());
            u64PANID = ZPS_u64NwkNibGetEpid(ZPS_pvAplZdoGetNwkHandle());
            u16PANID = ZPS_u16NwkNibGetMacPanId(ZPS_pvAplZdoGetNwkHandle());
            eAppApiPlmeGet(PHY_PIB_ATTR_CURRENT_CHANNEL, &u32Channel);

            ZNC_BUF_U16_UPD (&au8LinkTxBuffer[u16TxSize], u16NwkAddr,       u16TxSize);
            ZNC_BUF_U64_UPD (&au8LinkTxBuffer[u16TxSize], u64IeeeAddr,      u16TxSize);
            ZNC_BUF_U16_UPD (&au8LinkTxBuffer[u16TxSize], u16PANID,         u16TxSize);
            ZNC_BUF_U64_UPD (&au8LinkTxBuffer[u16TxSize], u64PANID,         u16TxSize);
            ZNC_BUF_U8_UPD (&au8LinkTxBuffer[u16TxSize], (uint8)u32Channel, u16TxSize);

			vSL_WriteMessage(E_SL_MSG_NETWORK_STATE_RSP, u16TxSize, au8LinkTxBuffer,0);
		}


        if(sAppEvent.eType == APP_E_EVENT_OOB_COMMISSIONING_DATA)
        {
            uint8                              u8Status = 0;
            BDB_tsOobWriteDataToAuthenticate   sAuthenticate;
            uint8                              au8DataEncrypted[52];
            uint16                             u16DataSize;
            uint16                             u16TxSize = 0;

            sAuthenticate.u64ExtAddr = sAppEvent.uEvent.sOOBCommissionData.u64Address;
            sAuthenticate.pu8InstallCode = sAppEvent.uEvent.sOOBCommissionData.au8InstallKey;

            u8Status = BDB_eOutOfBandCommissionGetDataEncrypted(&sAuthenticate,
                                                                au8DataEncrypted,
                                                                &u16DataSize);

            if (u8Status == BDB_E_SUCCESS)
            {
                uint64                             u64DeviceAddr;
                uint64                             u64TrustCenterAddr;
                uint16                             u16PanId;
                uint64                             u64ExtPanId;
                uint16                             u16ShortAddress;
                uint16                             u16DeviceId;
                ZPS_tsAplAfSimpleDescriptor        sDesc;

                /* Extract numerics provided in native endianess */
                memcpy((uint8 *) &u64DeviceAddr,      &au8DataEncrypted[0],  sizeof(uint64));
                memcpy((uint8 *) &u64TrustCenterAddr, &au8DataEncrypted[28], sizeof(uint64));
                memcpy((uint8 *) &u16PanId,           &au8DataEncrypted[38], sizeof(uint16));
                memcpy((uint8 *) &u64ExtPanId,        &au8DataEncrypted[40], sizeof(uint64));
                /* Valid extended PAN ID ? */
                if (u64ExtPanId != 0)
                {
                    /* Get short address */
                    u16ShortAddress = ZPS_u16AplZdoGetNwkAddr();
                    /* Default Device ID */
                    u16DeviceId = 0xffff;
                    /* Can we get the simple descriptor for the endpoint */
                    if (ZPS_eAplAfGetSimpleDescriptor(ZIGBEENODECONTROLBRIDGE_ZLO_ENDPOINT, &sDesc) == E_ZCL_SUCCESS)
                    {
                        /* Overwrite with correct id */
                        u16DeviceId = sDesc.u16DeviceId;
                    }
                    /* Transfer data to output buffer */
                    ZNC_BUF_U64_UPD (&au8LinkTxBuffer[u16TxSize], u64DeviceAddr,        u16TxSize);
                    memcpy(&au8LinkTxBuffer[u16TxSize], &au8DataEncrypted[8], 16);
                    u16TxSize += 16;
                    memcpy(&au8LinkTxBuffer[u16TxSize], &au8DataEncrypted[24], 4);
                    u16TxSize += 4;
                    ZNC_BUF_U64_UPD (&au8LinkTxBuffer[u16TxSize], u64TrustCenterAddr,   u16TxSize);
                    ZNC_BUF_U8_UPD  (&au8LinkTxBuffer[u16TxSize], au8DataEncrypted[36], u16TxSize);
                    ZNC_BUF_U8_UPD  (&au8LinkTxBuffer[u16TxSize], au8DataEncrypted[37], u16TxSize);
                    ZNC_BUF_U16_UPD (&au8LinkTxBuffer[u16TxSize], u16PanId,             u16TxSize);
                    ZNC_BUF_U64_UPD (&au8LinkTxBuffer[u16TxSize], u64ExtPanId,          u16TxSize);
                    ZNC_BUF_U16_UPD (&au8LinkTxBuffer[u16TxSize], u16ShortAddress,      u16TxSize);
                    ZNC_BUF_U16_UPD (&au8LinkTxBuffer[u16TxSize], u16DeviceId,          u16TxSize);
                }
                /* Invalid extended PAN ID ? */
                else
                {
                    /* Failed */
                    u8Status = BDB_E_FAILURE;
                }
            }
            /* Failed to get data ? */
            else
            {
                /* Failed */
                u8Status = BDB_E_FAILURE;
            }

            /* Add status and send */
            ZNC_BUF_U8_UPD  (&au8LinkTxBuffer[u16TxSize], u8Status,             u16TxSize);
            vSL_WriteMessage(E_SL_MSG_OUTOFBAND_COMMISSIONING_DATA_RSP,
                             u16TxSize,
                             au8LinkTxBuffer,
                             0);
        }

        if(sAppEvent.eType == APP_E_EVENT_ENCRYPT_SEND_KEY)
        {
            AESSW_Block_u    uNonce;
            uint8*           pu8MicLocation;
            uint8            bAesReturn;
            uint8*           pu8Key =  ( uint8* ) ZPS_pvNwkSecGetNetworkKey ( ZPS_pvAplZdoGetNwkHandle ( ) );
            uint64           u64Address =  ZPS_u64NwkNibGetExtAddr ( ZPS_pvAplZdoGetNwkHandle ( ) );
            uint8            i =  0;

            ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [ 0 ] ,  sAppEvent.uEvent.sEncSendMsg.u64Address, u16Length);

            while ( i < 16 )
            {
                ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [ u16Length ] ,  pu8Key [ i ] , u16Length);
                i++;
            }
            APP_vWrite64Nbo ( sAppEvent.uEvent.sEncSendMsg.u64Address,
                              &uNonce.au8[1] );
            memset( &uNonce.au8[9],
                    0,
                    ( sizeof ( uint8 ) * 8 ) );

            pu8MicLocation = & au8LinkTxBuffer [ u16Length ];
#ifdef LITTLE_ENDIAN_PROCESSOR
    tsReg128 sKeyRevIn;
    vSwipeEndian(&sAppEvent.uEvent.sEncSendMsg.uKey,&sKeyRevIn,TRUE);
    bAesReturn = bACI_WriteKey(&sKeyRevIn);
#else
    bAesReturn = bACI_WriteKey ( (tsReg128*) &sAppEvent.uEvent.sEncSendMsg.uKey );
#endif
            if ( bAesReturn )
            {
                vACI_OptimisedCcmStar( TRUE,
                                       4,
                                       0,
                                       16,
                                       &uNonce,
                                       & au8LinkTxBuffer [ 8 ],
                                       & au8LinkTxBuffer [ 8 ],                // overwrite the i/p data
                                       pu8MicLocation,                         // append to the o/p data
                                       NULL);
            }
            u16Length +=  4;

            ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [ u16Length ] ,
                              u64Address,
                              u16Length );
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [ u16Length ] ,
                              psNib->sPersist.u8ActiveKeySeqNumber,
                              u16Length );
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [ u16Length ] ,
                              psNib->sPersist.u8VsChannel,
                              u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [ u16Length ] ,
                              psNib->sPersist.u16VsPanId,
                              u16Length );
            ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [ u16Length ] ,
                              psNib->sPersist.u64ExtPanId,
                              u16Length );

            vSL_WriteMessage ( E_SL_MSG_AUTHENTICATE_DEVICE_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               0 );
        }
        switch (sZllState.eNodeState)
        {
            case E_RUNNING:
#ifdef FULL_FUNC_DEVICE
                if (sAppEvent.eType == APP_E_EVENT_TOUCH_LINK)
                {

                    vLog_Printf ( TRACE_APP,LOG_DEBUG, "\nPicked Touch link command %x\n", sAppEvent.uEvent.sTouchLink.u16DeviceId );
                    if ( ( sAppEvent.uEvent.sTouchLink.u16DeviceId >=  COLOUR_REMOTE_DEVICE_ID ) &&
                         ( sAppEvent.uEvent.sTouchLink.u16DeviceId <=  CONTROL_BRIDGE_DEVICE_ID ) )
                    {
                        /*
                         * Just added a controller device, send endpoint info
                         */
                        tsCLD_ZllUtility_EndpointInformationCommandPayload     sPayload;
                        tsZCL_Address                                          sDestinationAddress;
                        tsCLD_ZllDeviceTable*                                  psDevTab =  ( tsCLD_ZllDeviceTable* ) psGetDeviceTable ( );

                        sPayload.u64IEEEAddr  =  psDevTab->asDeviceRecords[0].u64IEEEAddr;
                        sPayload.u16NwkAddr   =  ZPS_u16AplZdoGetNwkAddr();
                        sPayload.u16DeviceID  =  psDevTab->asDeviceRecords[0].u16DeviceId;
                        sPayload.u16ProfileID =  psDevTab->asDeviceRecords[0].u16ProfileId;
                        sPayload.u8Endpoint   =  psDevTab->asDeviceRecords[0].u8Endpoint;
                        sPayload.u8Version    =  psDevTab->asDeviceRecords[0].u8Version;

                        vLog_Printf ( TRACE_APP,LOG_DEBUG, "\nTell new controller about us %04x", sAppEvent.uEvent.sTouchLink.u16NwkAddr );

                        sDestinationAddress.eAddressMode                   =  E_ZCL_AM_SHORT_NO_ACK;
                        sDestinationAddress.uAddress.u16DestinationAddress =  sAppEvent.uEvent.sTouchLink.u16NwkAddr;
                        eCLD_ZllUtilityCommandEndpointInformationCommandSend ( sDeviceTable.asDeviceRecords[0].u8Endpoint,        // src ep
                                                                               sAppEvent.uEvent.sTouchLink.u8Endpoint,            // dst ep
                                                                               &sDestinationAddress,
                                                                               &u8SeqNo,
                                                                               &sPayload );
                    }
                    else
                    {
                        if ( (sAppEvent.uEvent.sTouchLink.u16DeviceId <= COLOUR_TEMPERATURE_LIGHT_DEVICE_ID ) )
                        {
                            /* Controlled device attempt to add to device endpoint table
                             *
                             */
                            if ( bAddToEndpointTable ( &sAppEvent.uEvent.sTouchLink ) )
                            {
                                /* Added new or updated old
                                 * ensure that it has our group address
                                 */
                                PDM_eSaveRecordData ( PDM_ID_APP_END_P_TABLE,
                                                      &sEndpointTable,
                                                      sizeof ( tsZllEndpointInfoTable ) );
                                                      bAddrMode =  FALSE;           // ensure not in group mode
                                vLog_Printf ( TRACE_APP,LOG_DEBUG, "\nNEW Send group add %d to %04x\n", sGroupTable.asGroupRecords[0].u16GroupId,
                                                               sEndpointTable.asEndpointRecords[sEndpointTable.u8CurrentLight].u16NwkAddr );
                                APP_vAppAddGroup ( sGroupTable.asGroupRecords[0].u16GroupId, FALSE );

                                vAppIdentifyEffect ( E_CLD_IDENTIFY_EFFECT_OKAY );
                            }
                            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [0],         sAppEvent.uEvent.sTouchLink.u16NwkAddr, u16Length );
                            ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [u16Length], sAppEvent.uEvent.sTouchLink.u64Address, u16Length );
                            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], sAppEvent.uEvent.sTouchLink.u8MacCap  , u16Length );
                            vSL_WriteMessage ( E_SL_MSG_DEVICE_ANNOUNCE,
                                               u16Length,
                                               au8LinkTxBuffer,
                                               0 );
                        }
                    }

                }

                break;
#endif
            default:
                break;

        }
    }
#ifdef CLD_GREENPOWER
	else if (ZQ_bQueueReceive(&APP_msgGPZCLTimerEvents, &u8GPZCLTimerEvent) == TRUE)
	{
		tsZCL_CallBackEvent sZCL_CallBackEvent;
		sZCL_CallBackEvent.eEventType =E_ZCL_CBET_TIMER_MS;
		vZCL_EventHandler(&sZCL_CallBackEvent);
	}
#endif
}

/****************************************************************************
 *
 * NAME: APP_vHandleStackEvents
 *
 * DESCRIPTION:
 *
 *
 ****************************************************************************/
PUBLIC void APP_vHandleStackEvents ( ZPS_tsAfEvent*    psStackEvent )
{

    uint16                 u16Length =  0;
    static bool            bSecondDisc =  FALSE;
    tsBDB_ZCLEvent         sBdbEvent;
    tsZCL_CallBackEvent    sCallBackEvent;
    uint8                  au8LinkTxBuffer[256];
    uint8 				   u8LinkQuality;

    u8LinkQuality=psStackEvent->uEvent.sApsDataIndEvent.u8LinkQuality;

    vLog_Printf ( TRACE_APP,LOG_DEBUG, "Got stack event %d\n", psStackEvent->eType);

    switch (psStackEvent->eType)
    {
        case ZPS_EVENT_APS_DATA_INDICATION:
        {
            uint8*    dataPtr =  ( uint8* ) PDUM_pvAPduInstanceGetPayload ( psStackEvent->uEvent.sApsDataIndEvent.hAPduInst );
            uint8     u8Size  =  PDUM_u16APduInstanceGetPayloadSize ( psStackEvent->uEvent.sApsDataIndEvent.hAPduInst );

            if( psStackEvent->uEvent.sApsDataIndEvent.u8SrcEndpoint != 0  &&
                psStackEvent->uEvent.sApsDataIndEvent.u8DstEndpoint != 0 )
            {
                uint8    i =  0;
                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [0],          psStackEvent->uEvent.sApsDataIndEvent.eStatus,          u16Length );
                ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.u16ProfileId,     u16Length );
                ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.u16ClusterId,     u16Length );
                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.u8SrcEndpoint,    u16Length );
                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.u8DstEndpoint,    u16Length );
                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.u8SrcAddrMode,    u16Length );
                if(psStackEvent->uEvent.sApsDataIndEvent.u8SrcAddrMode == ZPS_E_ADDR_MODE_IEEE)
                {
                    ZNC_BUF_U64_UPD  ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.uSrcAddress.u64Addr,    u16Length );
                }
                else
                {
                    ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
                }
                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.u8DstAddrMode,    u16Length );
                if( psStackEvent->uEvent.sApsDataIndEvent.u8DstAddrMode == ZPS_E_ADDR_MODE_IEEE )
                {
                    ZNC_BUF_U64_UPD  ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.uDstAddress.u64Addr,    u16Length );
                }
                else
                {
                    ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.uDstAddress.u16Addr,    u16Length );
                }
                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  u8Size,    u16Length );
                while ( i < u8Size )
                {
                    ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  dataPtr [ i ],          u16Length );
                    i++;
                }

                vSL_WriteMessage ( E_SL_MSG_DATA_INDICATION,
                                   u16Length,
                                   au8LinkTxBuffer,
                                   u8LinkQuality);
                vLog_Printf ( TRACE_APP,LOG_ERR, "NPDU: Current %d Max %d\n", PDUM_u8GetNpduUse(), PDUM_u8GetMaxNpduUse() );
                vLog_Printf ( TRACE_APP,LOG_ERR, "APDU: Current %d Max %d\n", u8GetApduUse(), u8GetMaxApdu( ) );

            }
            else
            {
                ZPS_tsAfZdpEvent    sApsZdpEvent;

                zps_bAplZdpUnpackResponse ( psStackEvent,
                                            &sApsZdpEvent );

                ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [0] , sApsZdpEvent.u8SequNumber, u16Length );

                switch(sApsZdpEvent.u16ClusterId)
                {
                    case ZPS_ZDP_DEVICE_ANNCE_REQ_CLUSTER_ID:
                    {
                        u16Length =  0;
                        ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [0] , sApsZdpEvent.uZdpData.sDeviceAnnce.u16NwkAddr,             u16Length );
                        ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sDeviceAnnce.u64IeeeAddr,    u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sDeviceAnnce.u8Capability,   u16Length );

                        vSL_WriteMessage ( E_SL_MSG_DEVICE_ANNOUNCE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality);
                    }
                        break;

                    case ZPS_ZDP_COMPLEX_DESC_RSP_CLUSTER_ID:
                    {
                        uint8 i =  0;

                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sComplexDescRsp.u8Status,                           u16Length );
                        ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sComplexDescRsp.u16NwkAddrOfInterest,               u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sComplexDescRsp.u8Length,                           u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sComplexDescRsp.sComplexDescriptor.u8XMLTag,        u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sComplexDescRsp.sComplexDescriptor.u8FieldCount,    u16Length );
                        if( sApsZdpEvent.uZdpData.sComplexDescRsp.u8Status == ZPS_E_SUCCESS )
                        {
                            while ( i <  sApsZdpEvent.uZdpData.sComplexDescRsp.sComplexDescriptor.u8FieldCount )
                            {
                                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sComplexDescRsp.sComplexDescriptor.pu8CdData[ i ],    u16Length );
                                i++;
                            }
                        }

                        vSL_WriteMessage ( E_SL_MSG_COMPLEX_DESCRIPTOR_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality);
                    }
                        break;

                    case ZPS_ZDP_NODE_DESC_RSP_CLUSTER_ID:
                    {
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.u8Status,                                  u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.u16NwkAddrOfInterest,                      u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.sNodeDescriptor.u16ManufacturerCode,       u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.sNodeDescriptor.u16MaxRxSize,              u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.sNodeDescriptor.u16MaxTxSize,              u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.sNodeDescriptor.u16ServerMask,             u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.sNodeDescriptor.u8DescriptorCapability,    u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.sNodeDescriptor.u8MacFlags,                u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.sNodeDescriptor.u8MaxBufferSize,           u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sNodeDescRsp.sNodeDescriptor.uBitUnion.u16Value,        u16Length );

                        vSL_WriteMessage ( E_SL_MSG_NODE_DESCRIPTOR_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                    }
                        break;

                    case ZPS_ZDP_MATCH_DESC_RSP_CLUSTER_ID:
                    {
                        uint8    i =  0;
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMatchDescRsp.u8Status,                u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMatchDescRsp.u16NwkAddrOfInterest,    u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMatchDescRsp.u8MatchLength,           u16Length );

                        if( sApsZdpEvent.uZdpData.sMatchDescRsp.u8Status == ZPS_E_SUCCESS )
                        {
                            while ( i < sApsZdpEvent.uZdpData.sMatchDescRsp.u8MatchLength )
                            {
                                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.au8Data [ i ],         u16Length );
                                i++;
                            }
                         }

                        vSL_WriteMessage ( E_SL_MSG_MATCH_DESCRIPTOR_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                    }
                        break;

                    case ZPS_ZDP_SIMPLE_DESC_RSP_CLUSTER_ID:
                    {
                        uint8    i =  0;
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSimpleDescRsp.u8Status,                                     u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSimpleDescRsp.u16NwkAddrOfInterest,                         u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSimpleDescRsp.u8Length,                                     u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSimpleDescRsp.sSimpleDescriptor.u8Endpoint,                 u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSimpleDescRsp.sSimpleDescriptor.u16ApplicationProfileId,    u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSimpleDescRsp.sSimpleDescriptor.u16DeviceId,                u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSimpleDescRsp.sSimpleDescriptor.uBitUnion.u8Value,          u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSimpleDescRsp.sSimpleDescriptor.u8InClusterCount,           u16Length );
                        if( sApsZdpEvent.uZdpData.sSimpleDescRsp.u8Status == ZPS_E_SUCCESS )
                        {
                            while ( i < sApsZdpEvent.uZdpData.sSimpleDescRsp.sSimpleDescriptor.u8InClusterCount )
                            {
                                ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.au16Data [ i ],         u16Length );
                                i++;
                            }
                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSimpleDescRsp.sSimpleDescriptor.u8OutClusterCount,    u16Length );
                            i =  0;
                            while ( i < sApsZdpEvent.uZdpData.sSimpleDescRsp.sSimpleDescriptor.u8OutClusterCount )
                            {
                                ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.au16Data [ i  + sApsZdpEvent.uZdpData.sSimpleDescRsp.sSimpleDescriptor.u8InClusterCount],         u16Length );
                                i++;
                            }
                        }
                        vSL_WriteMessage ( E_SL_MSG_SIMPLE_DESCRIPTOR_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                    }
                        break;

                    case ZPS_ZDP_NWK_ADDR_RSP_CLUSTER_ID:
                    case ZPS_ZDP_IEEE_ADDR_RSP_CLUSTER_ID:
                    {
                        uint8    i =  0;
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sIeeeAddrRsp.u8Status,                u16Length );
                        ZNC_BUF_U64_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sIeeeAddrRsp.u64IeeeAddrRemoteDev,    u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sIeeeAddrRsp.u16NwkAddrRemoteDev,     u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sIeeeAddrRsp.u8NumAssocDev,           u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sIeeeAddrRsp.u8StartIndex,            u16Length );
                        if( sApsZdpEvent.uZdpData.sIeeeAddrRsp.u8Status == ZPS_E_SUCCESS )
                        {
                            while ( i < sApsZdpEvent.uZdpData.sIeeeAddrRsp.u8NumAssocDev )
                            {
                                ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sIeeeAddrRsp.pu16NwkAddrAssocDevList [ i ],    u16Length );
                                i++;
                            }
                        }

                        if( sApsZdpEvent.u16ClusterId == 0x8000 )
                        {
                            vSL_WriteMessage ( E_SL_MSG_NETWORK_ADDRESS_RESPONSE,
                                               u16Length,
                                               au8LinkTxBuffer,
                                               u8LinkQuality );
                        }
                        else
                        {
                            vSL_WriteMessage ( E_SL_MSG_IEEE_ADDRESS_RESPONSE,
                                               u16Length,
                                               au8LinkTxBuffer,
                                               u8LinkQuality );

                        }
                    }
                        break;

                    case ZPS_ZDP_MGMT_LEAVE_RSP_CLUSTER_ID:
                    {
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtLeaveRsp.u8Status,    u16Length );
                        vSL_WriteMessage ( E_SL_MSG_MANAGEMENT_LEAVE_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                    }
                    break;

                    case ZPS_ZDP_MGMT_LQI_RSP_CLUSTER_ID:
                    {
                        uint8    u8Values;
                        uint8    u8Bytes;
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtLqiRsp.u8Status,                    u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtLqiRsp.u8NeighborTableEntries,      u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtLqiRsp.u8NeighborTableListCount,    u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtLqiRsp.u8StartIndex,                u16Length );
                        if( sApsZdpEvent.uZdpData.sMgmtLqiRsp.u8Status == ZPS_E_SUCCESS )
                        {
                            for ( u8Values = 0; u8Values < sApsZdpEvent.uZdpData.sMgmtLqiRsp.u8NeighborTableListCount; u8Values++ )
                            {
                                ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.asNtList[u8Values].u16NwkAddr,            u16Length );
                                ZNC_BUF_U64_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.asNtList[u8Values].u64ExtPanId,           u16Length );
                                ZNC_BUF_U64_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.asNtList[u8Values].u64ExtendedAddress,    u16Length );
                                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.asNtList[u8Values].u8Depth,               u16Length );
                                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.asNtList[u8Values].u8LinkQuality,         u16Length );

                                u8Bytes  =  sApsZdpEvent.uLists.asNtList[u8Values].uAncAttrs.u2DeviceType;
                                u8Bytes |=  ( sApsZdpEvent.uLists.asNtList[u8Values].uAncAttrs.u2PermitJoining << 2 );
                                u8Bytes |=  ( sApsZdpEvent.uLists.asNtList[u8Values].uAncAttrs.u2Relationship << 4 );
                                u8Bytes |=  ( sApsZdpEvent.uLists.asNtList[u8Values].uAncAttrs.u2RxOnWhenIdle << 6 );
                                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , u8Bytes,    u16Length );
                            }
                        }
                        vSL_WriteMessage ( E_SL_MSG_MANAGEMENT_LQI_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                    }
                    break;

                    case ZPS_ZDP_POWER_DESC_RSP_CLUSTER_ID:
                    {
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sPowerDescRsp.u8Status,                               u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sPowerDescRsp.sPowerDescriptor.uBitUnion.u16Value,    u16Length );
                        vSL_WriteMessage ( E_SL_MSG_POWER_DESCRIPTOR_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality);
                    }
                    break;


                    case ZPS_ZDP_ACTIVE_EP_RSP_CLUSTER_ID:
                    {
                        uint8    i =  0;
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sActiveEpRsp.u8Status,                u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sActiveEpRsp.u16NwkAddrOfInterest,    u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sActiveEpRsp.u8ActiveEpCount,         u16Length );

                        if( sApsZdpEvent.uZdpData.sActiveEpRsp.u8Status == ZPS_E_SUCCESS )
                        {
                            while ( i < sApsZdpEvent.uZdpData.sActiveEpRsp.u8ActiveEpCount )
                            {
                                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.au8Data [ i ],    u16Length );
                                i++;
                            }
                        }
                        vSL_WriteMessage ( E_SL_MSG_ACTIVE_ENDPOINT_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                    }
                    break;

                    case ZPS_ZDP_MGMT_NWK_UPDATE_NOTIFY_CLUSTER_ID:
                    {
                        uint8    i =  0;
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtNwkUpdateNotify.u8Status,                     u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtNwkUpdateNotify.u16TotalTransmissions,        u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtNwkUpdateNotify.u16TransmissionFailures,      u16Length );
                        ZNC_BUF_U32_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtNwkUpdateNotify.u32ScannedChannels,           u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sMgmtNwkUpdateNotify.u8ScannedChannelListCount,    u16Length );
                        if( sApsZdpEvent.uZdpData.sMgmtNwkUpdateNotify.u8Status == ZPS_E_SUCCESS )
                        {
                            while ( i < sApsZdpEvent.uZdpData.sMgmtNwkUpdateNotify.u8ScannedChannelListCount )
                            {
                                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uLists.au8Data [ i ],    u16Length );
                                i++;
                            }
                        }
                        vSL_WriteMessage ( E_SL_MSG_MANAGEMENT_NETWORK_UPDATE_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                    }
                    break;

                    case ZPS_ZDP_SYSTEM_SERVER_DISCOVERY_RSP_CLUSTER_ID:
                    {
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSystemServerDiscoveryRsp.u8Status,         u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sSystemServerDiscoveryRsp.u16ServerMask,    u16Length );

                         vSL_WriteMessage ( E_SL_MSG_SYSTEM_SERVER_DISCOVERY_RESPONSE,
                                            u16Length,
                                            au8LinkTxBuffer,
                                            u8LinkQuality );
                    }
                    break;

                    case ZPS_ZDP_USER_DESC_RSP_CLUSTER_ID:
                    {
                        uint8    u8Length;
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sUserDescRsp.u8Status,                u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sUserDescRsp.u16NwkAddrOfInterest,    u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sUserDescRsp.u8Length,                u16Length );
                        if( sApsZdpEvent.uZdpData.sUserDescRsp.u8Status == ZPS_E_SUCCESS )
                        {
                            for( u8Length =  0 ;  u8Length < sApsZdpEvent.uZdpData.sUserDescRsp.u8Length; u8Length++ )
                            {
                                ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sUserDescRsp.szUserDescriptor[u8Length],    u16Length );
                            }
                        }
                        vSL_WriteMessage ( E_SL_MSG_USER_DESC_RSP,
                                            u16Length,
                                            au8LinkTxBuffer,
                                            u8LinkQuality );
                    }
                    break;

                    case ZPS_ZDP_USER_DESC_CONF_RSP_CLUSTER_ID:
                    {
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sUserDescConf.u8Status,                u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length] , sApsZdpEvent.uZdpData.sUserDescConf.u16NwkAddrOfInterest,    u16Length );

                        vSL_WriteMessage ( E_SL_MSG_USER_DESC_NOTIFY,
                                            u16Length,
                                            au8LinkTxBuffer,
                                            u8LinkQuality );
                    }
                    break;

                    case ZPS_ZDP_BIND_RSP_CLUSTER_ID:
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], sApsZdpEvent.uZdpData.sUnbindRsp.u8Status,    u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataIndEvent.u8SrcEndpoint, u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataIndEvent.u8SrcAddrMode, u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
                        vSL_WriteMessage ( E_SL_MSG_BIND_RESPONSE,
                                            u16Length,
                                            au8LinkTxBuffer,
                                            u8LinkQuality );
                    break;

                    case ZPS_ZDP_UNBIND_RSP_CLUSTER_ID:
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], sApsZdpEvent.uZdpData.sUnbindRsp.u8Status,    u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataIndEvent.u8SrcEndpoint, u16Length );
                        ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataIndEvent.u8SrcAddrMode, u16Length );
                        ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psStackEvent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
                        vSL_WriteMessage ( E_SL_MSG_UNBIND_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                    break;

                    case ZPS_ZDP_MGMT_PERMIT_JOINING_RSP_CLUSTER_ID:
                        ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [u16Length], sApsZdpEvent.uZdpData.sPermitJoiningRsp.u8Status,    u16Length );
                        vSL_WriteMessage ( E_SL_MSG_PERMIT_JOINING_RESPONSE,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                     break;

                    default:
                    break;
                    }
                }
            }
        break;

        case ZPS_EVENT_NWK_DISCOVERY_COMPLETE:
            sBdbEvent.eType = BDB_E_ZCL_EVENT_DISCOVERY_DONE;
            sBdbEvent.psCallBackEvent = &sCallBackEvent;
            sBdbEvent.psCallBackEvent->pZPSevent = psStackEvent;
            BDB_vZclEventHandler(&sBdbEvent);
        break;

        case ZPS_EVENT_NWK_ROUTE_DISCOVERY_CONFIRM:

            vLog_Printf(TRACE_APP,LOG_DEBUG, "\nDISC Confirm: Status=%d, NWK Status=%d\n",
                                     psStackEvent->uEvent.sNwkRouteDiscoveryConfirmEvent.u8Status,
                                     psStackEvent->uEvent.sNwkRouteDiscoveryConfirmEvent.u8NwkStatus);

            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [0], psStackEvent->uEvent.sNwkRouteDiscoveryConfirmEvent.u8Status,               u16Length );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sNwkRouteDiscoveryConfirmEvent.u8NwkStatus,    u16Length );
            vSL_WriteMessage ( E_SL_MSG_ROUTE_DISCOVERY_CONFIRM,
                                   u16Length,
                                   au8LinkTxBuffer,
                                   u8LinkQuality );
        break;

        case ZPS_EVENT_NWK_STATUS_INDICATION:
            vLog_Printf(TRACE_APP,LOG_DEBUG, "\nNwkStat: Addr:%x Status:%x",
                    psStackEvent->uEvent.sNwkStatusIndicationEvent.u16NwkAddr,
                    psStackEvent->uEvent.sNwkStatusIndicationEvent.u8Status);

         break;

         case ZPS_EVENT_NWK_STARTED:
         case ZPS_EVENT_NWK_FAILED_TO_START:
         case ZPS_EVENT_NWK_JOINED_AS_ROUTER:
         case ZPS_EVENT_NWK_FAILED_TO_JOIN:
         {
             uint8     u8FormJoin;
             bool_t    bSend =  TRUE;
             if(psStackEvent->eType == ZPS_EVENT_NWK_STARTED)
             {
                 u8FormJoin = 1; /* formed */
             }
             if( psStackEvent->eType == ZPS_EVENT_NWK_FAILED_TO_START )
             {
                 u8FormJoin =  0xC4; /* Startup failure */
             }
             if(psStackEvent->eType == ZPS_EVENT_NWK_JOINED_AS_ROUTER )
             {
                 u8FormJoin =  0; /* joined */
             }
             if( psStackEvent->eType == ZPS_EVENT_NWK_FAILED_TO_JOIN )
             {
                 if( !bSecondDisc )
                 {
                     bSend = FALSE;
                 }
                 else
                 {
                     u8FormJoin =  psStackEvent->uEvent.sNwkJoinFailedEvent.u8Status; /* failed reason */
                 }
             }
             if(bSend)
             {
                 APP_vSendJoinedFormEventToHost ( u8FormJoin,
                                                  au8LinkTxBuffer );
             }
         }
         break;

         case ZPS_EVENT_ERROR:
         {
             ZPS_tsAfErrorEvent*    psErrEvt =  &psStackEvent->uEvent.sAfErrorEvent;
             vLog_Printf ( TRACE_APP,LOG_ERR, "\nStack Err: %d", psErrEvt->eError );

             if( psErrEvt->eError == ZPS_ERROR_APDU_INSTANCES_EXHAUSTED )
             {
                 vLog_Printf ( TRACE_APP,LOG_ERR, "\nAPDU instance ran out : %x",
                                                         psErrEvt->uErrorData.sAfErrorApdu.hAPdu);
             }

             if( ZPS_ERROR_OS_MESSAGE_QUEUE_OVERRUN == psErrEvt->eError )
             {
                 vLog_Printf ( TRACE_APP,LOG_ERR, "\nHandle: %x", psErrEvt->uErrorData.sAfErrorOsMessageOverrun.hMessage );
             }

         }
         break;

         default:
         break;



    }


    switch (sZllState.eNodeState)
    {
        case E_RUNNING:

            if ( psStackEvent->eType !=  ZPS_EVENT_NONE )
            {
                if ( psStackEvent->eType ==  ZPS_EVENT_NWK_NEW_NODE_HAS_JOINED )
                {
				    //RAJOUT FRED
                	 u16Length =  0;
					ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [0] ,  psStackEvent->uEvent.sNwkJoinIndicationEvent.u16NwkAddr,  u16Length );
					ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [u16Length] ,  psStackEvent->uEvent.sNwkJoinIndicationEvent.u64ExtAddr,    u16Length );
					ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length] ,  psStackEvent->uEvent.sNwkJoinIndicationEvent.u8Capability,   u16Length );

					vSL_WriteMessage ( E_SL_MSG_DEVICE_ANNOUNCE,
									   u16Length,
									   au8LinkTxBuffer,
									   u8LinkQuality);

                    vLog_Printf ( TRACE_APP,LOG_DEBUG, "\nNode joined %04x",
                                                       psStackEvent->uEvent.sNwkJoinIndicationEvent.u16NwkAddr );
                    s_sLedState.u32LedToggleTime =  ZTIMER_TIME_MSEC ( 200 );
                    u8JoinedDevice =  0;
                }

                 if (psStackEvent->eType == ZPS_EVENT_NWK_LEAVE_INDICATION)
                 {
                    /* report to host */
                     ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [ 0 ] ,
                                       psStackEvent->uEvent.sNwkLeaveIndicationEvent.u64ExtAddr,
                                       u16Length );
                     ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [ u16Length ] ,
                                       psStackEvent->uEvent.sNwkLeaveIndicationEvent.u8Rejoin,
                                       u16Length );

                     vSL_WriteMessage ( E_SL_MSG_LEAVE_INDICATION,
                                        u16Length,
                                        au8LinkTxBuffer,
                                        u8LinkQuality );
                }
            }
            break;
        default:
            break;

    }

    /*
     * Global clean up to make sure any APDUs have been freed
     */

    if ( psStackEvent->eType ==  ZPS_EVENT_APS_DATA_INDICATION )
    {
        PDUM_eAPduFreeAPduInstance( psStackEvent->uEvent.sApsDataIndEvent.hAPduInst );
    }

}

/****************************************************************************
 *
 * NAME: bPutChar
 *
 * DESCRIPTION:
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/

PUBLIC bool_t bPutChar ( uint8    u8TxByte )
{
    bool    bSent =  TRUE;

    ZPS_eEnterCriticalSection ( NULL, &sStorage);

    if ( UART_bTxReady ( ) && ZQ_bQueueIsEmpty ( &APP_msgSerialTx ) )
    {
        /* send byte now and enable irq */
        UART_vSetTxInterrupt(TRUE);
        UART_vTxChar(u8TxByte);
    }
    else
    {
        bSent = ( ZQ_bQueueSend (&APP_msgSerialTx, &u8TxByte ) );

    }

    ZPS_eExitCriticalSection ( NULL, &sStorage);

    return bSent;
}

#ifdef FULL_FUNC_DEVICE

/****************************************************************************
 *
 * NAME: vAppIdentifyEffect
 *
 * DESCRIPTION:
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vAppIdentifyEffect ( teCLD_Identify_EffectId    eEffect )
{
    uint8            u8Seq;
    tsZCL_Address    sAddress;

    APP_vSetAddress ( &sAddress, FALSE );

    eCLD_IdentifyCommandTriggerEffectSend ( sDeviceTable.asDeviceRecords[0].u8Endpoint,
                                            sEndpointTable.asEndpointRecords[sEndpointTable.u8CurrentLight].u8Endpoint,
                                            &sAddress,
                                            &u8Seq,
                                            eEffect,
                                            0  /* Effect varient */);
}

/****************************************************************************
 *
 * NAME: APP_vSetAddressMode
 *
 * DESCRIPTION:
 *
 * RETURNS:
 * bool
 *
 ****************************************************************************/

PUBLIC void APP_vSetAddressMode ( void )
{
    bAddrMode =  !bAddrMode;
    if ( bAddrMode )
    {
        vLog_Printf ( TRACE_APP,LOG_DEBUG, "\nG_CAST\n" );
    } else
    {
        vLog_Printf (TRACE_APP,LOG_DEBUG, "\nU_CAST\n" );
    }
}

/****************************************************************************
 *
 * NAME: bAddToEndpointTable
 *
 * DESCRIPTION:
 *
 * RETURNS:
 * bool
 *
 ****************************************************************************/
PUBLIC bool bAddToEndpointTable ( APP_tsEventTouchLink*    psEndpointData )
{
    uint8     u8Index =  0xff;
    bool_t    bPresent;

    bPresent =  u8SearchEndpointTable ( psEndpointData,
                                        &u8Index );
    if ( u8Index < 0xff )
    {
        /* There is space for a new entry
         * or it is already there
         */
        if ( !bPresent )
        {
            /* new entry, increment device count
             *
             */
            sEndpointTable.u8NumRecords++;
        }
        /* Add or update details at the slot indicated
         *
         */
        sEndpointTable.asEndpointRecords[u8Index].u16NwkAddr   =  psEndpointData->u16NwkAddr;
        sEndpointTable.asEndpointRecords[u8Index].u16ProfileId =  psEndpointData->u16ProfileId;
        sEndpointTable.asEndpointRecords[u8Index].u16DeviceId  =  psEndpointData->u16DeviceId;
        sEndpointTable.asEndpointRecords[u8Index].u8Endpoint   =  psEndpointData->u8Endpoint;
        sEndpointTable.asEndpointRecords[u8Index].u8Version    =  psEndpointData->u8Version;

        vLog_Printf ( TRACE_APP,LOG_DEBUG, "\nAdd idx %d Addr %04x Ep %d Dev %04x", u8Index,
                                        sEndpointTable.asEndpointRecords[u8Index].u16NwkAddr,
                                        sEndpointTable.asEndpointRecords[u8Index].u8Endpoint,
                                        sEndpointTable.asEndpointRecords[u8Index].u16DeviceId );

        sEndpointTable.u8CurrentLight =  u8Index;
        return TRUE;
    }

    /* no room in the table */
    return FALSE;
}

/****************************************************************************
 *
 * NAME: APP_vAppAddGroup
 *
 * DESCRIPTION:
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void APP_vAppAddGroup ( uint16    u16GroupId,
                               bool_t    bBroadcast )
{

    tsCLD_Groups_AddGroupRequestPayload    sPayload;
    uint8                                  u8Seq;
    tsZCL_Address                          sAddress;

    APP_vSetAddress ( &sAddress,
                      bBroadcast );

    sPayload.sGroupName.pu8Data     =  (uint8*)"";
    sPayload.sGroupName.u8Length    =  0;
    sPayload.sGroupName.u8MaxLength =  0;
    sPayload.u16GroupId             =  u16GroupId;

    eCLD_GroupsCommandAddGroupRequestSend ( sDeviceTable.asDeviceRecords[0].u8Endpoint,
                                            sEndpointTable.asEndpointRecords[sEndpointTable.u8CurrentLight].u8Endpoint   /* don't care group addr */,
                                            &sAddress,
                                            &u8Seq,
                                            &sPayload );

}

/****************************************************************************
 *
 * NAME: u8SearchEndpointTable
 *
 * DESCRIPTION:
 *
 * RETURNS:
 * uint8
 *
 ****************************************************************************/
PRIVATE uint8 u8SearchEndpointTable ( APP_tsEventTouchLink*    psEndpointData,
                                      uint8*                   pu8Index )
{
    int      i;
    bool     bGotFree =  FALSE;

    *pu8Index =  0xff;

    for ( i=0; i < NUM_ENDPOINT_RECORDS; i++ )
    {
        if ( ( psEndpointData->u16NwkAddr == sEndpointTable.asEndpointRecords[i].u16NwkAddr ) &&
             ( psEndpointData->u8Endpoint == sEndpointTable.asEndpointRecords[i].u8Endpoint ) )
        {
            /* same ep on same device already known about */
            *pu8Index =  i;
            vLog_Printf ( TRACE_APP,LOG_DEBUG, "\nPresent" );
            return 1;
        }

        if ( ( sEndpointTable.asEndpointRecords[i].u16NwkAddr == 0 ) &&
               !bGotFree )
        {
            *pu8Index =  i;
            bGotFree  =  TRUE;
            vLog_Printf (TRACE_APP,LOG_DEBUG, "\nFree slot %d", *pu8Index );
        }

    }

    vLog_Printf ( TRACE_APP,LOG_DEBUG, "\nNot found" );
    return ( bGotFree ) ? 0 : 3  ;
}
/****************************************************************************
 *
 * NAME: APP_vSetAddress
 *
 * DESCRIPTION:
 *
 * RETURNS:
 * uint8
 *
 ****************************************************************************/

PUBLIC void APP_vSetAddress ( tsZCL_Address*    psAddress,
                              bool_t            bBroadcast )
{

    if (bBroadcast)
    {
        psAddress->eAddressMode            =  E_ZCL_AM_BROADCAST;
        psAddress->uAddress.eBroadcastMode =  ZPS_E_APL_AF_BROADCAST_RX_ON;
    }
    else if (bAddrMode)
    {
        psAddress->eAddressMode                   =  E_ZCL_AM_GROUP;
        psAddress->uAddress.u16DestinationAddress =  sGroupTable.asGroupRecords[0].u16GroupId;
    }
    else
    {
        psAddress->eAddressMode                   =  E_ZCL_AM_SHORT_NO_ACK;
        psAddress->uAddress.u16DestinationAddress =  sEndpointTable.asEndpointRecords[sEndpointTable.u8CurrentLight].u16NwkAddr;
    }
}

#endif
/****************************************************************************
 *
 * NAME: App_TransportKeyCallback
 *
 * DESCRIPTION:
 *
 * RETURNS:
 * uint8
 *
 ****************************************************************************/

PUBLIC void App_TransportKeyCallback ( void*   pvParam )
{
    APP_tsEvent    sAppEvent;

    sAppEvent.eType                         =  APP_E_EVENT_TRANSPORT_HA_KEY;
    sAppEvent.uEvent.u64TransportKeyAddress =  *( ( uint64* ) pvParam );
    ZQ_bQueueSend ( &APP_msgAppEvents, &sAppEvent );

}


/****************************************************************************
 *
 * NAME:       APP_vWrite64Nbo
 */
/* @ingroup
 *
 * @param
 *
 * @return
 *
 * @note
 *
 ****************************************************************************/
PRIVATE void APP_vWrite64Nbo( uint64    u64dWord,
                              uint8*    pu8Payload )
{
    pu8Payload[0] =  u64dWord;
    pu8Payload[1] =  u64dWord >> 8;
    pu8Payload[2] =  u64dWord >> 16;
    pu8Payload[3] =  u64dWord >> 24;
    pu8Payload[4] =  u64dWord >> 32;
    pu8Payload[5] =  u64dWord >> 40;
    pu8Payload[6] =  u64dWord >> 48;
    pu8Payload[7] =  u64dWord >> 56;
}

/****************************************************************************
 *
 * NAME:       Znc_vSendDataIndicationToHost
 */
/* @ingroup
 *
 * @param
 *
 * @return
 *
 * @note
 *
 ****************************************************************************/
PUBLIC void Znc_vSendDataIndicationToHost ( ZPS_tsAfEvent*    psStackEvent,
                                            uint8*            pau8LinkTxBuffer )
{
    uint16    u16Length =  0;
    uint16    i         =  0;
    uint8*    dataPtr   =  ( uint8* ) PDUM_pvAPduInstanceGetPayload ( psStackEvent->uEvent.sApsDataIndEvent.hAPduInst );
    uint8     u8Size    =  PDUM_u16APduInstanceGetPayloadSize( psStackEvent->uEvent.sApsDataIndEvent.hAPduInst);
    uint8     u8LinkQuality;
    u8LinkQuality=psStackEvent->uEvent.sApsDataIndEvent.u8LinkQuality;
    ZNC_BUF_U8_UPD  ( &pau8LinkTxBuffer[u16Length] ,
                      psStackEvent->uEvent.sApsDataIndEvent.eStatus,
                      u16Length );
    ZNC_BUF_U16_UPD ( &pau8LinkTxBuffer[u16Length] ,
                      psStackEvent->uEvent.sApsDataIndEvent.u16ProfileId,
                      u16Length );
    ZNC_BUF_U16_UPD ( &pau8LinkTxBuffer[u16Length] ,
                      psStackEvent->uEvent.sApsDataIndEvent.u16ClusterId,
                      u16Length );
    ZNC_BUF_U8_UPD  ( &pau8LinkTxBuffer[u16Length] ,
                      psStackEvent->uEvent.sApsDataIndEvent.u8SrcEndpoint,
                      u16Length );
    ZNC_BUF_U8_UPD  ( &pau8LinkTxBuffer[u16Length] ,
                      psStackEvent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                      u16Length );
    ZNC_BUF_U8_UPD  ( &pau8LinkTxBuffer[u16Length] ,
                      psStackEvent->uEvent.sApsDataIndEvent.u8SrcAddrMode,
                      u16Length );

    if ( psStackEvent->uEvent.sApsDataIndEvent.u8SrcAddrMode ==  ZPS_E_ADDR_MODE_IEEE )
    {
        ZNC_BUF_U64_UPD ( &pau8LinkTxBuffer[u16Length] ,
                          psStackEvent->uEvent.sApsDataIndEvent.uSrcAddress.u64Addr,
                          u16Length );
    }
    else
    {
        ZNC_BUF_U16_UPD ( &pau8LinkTxBuffer[u16Length] ,
                          psStackEvent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,
                          u16Length );
    }
    ZNC_BUF_U8_UPD  ( &pau8LinkTxBuffer[u16Length] ,
                      psStackEvent->uEvent.sApsDataIndEvent.u8DstAddrMode,
                      u16Length );


    if ( psStackEvent->uEvent.sApsDataIndEvent.u8DstAddrMode ==  ZPS_E_ADDR_MODE_IEEE )
    {
        ZNC_BUF_U64_UPD ( &pau8LinkTxBuffer[u16Length] ,
                          psStackEvent->uEvent.sApsDataIndEvent.uDstAddress.u64Addr,
                          u16Length );
    }
    else
    {
        ZNC_BUF_U16_UPD ( &pau8LinkTxBuffer[u16Length] ,
                          psStackEvent->uEvent.sApsDataIndEvent.uDstAddress.u16Addr,
                          u16Length );
    }
    while ( i < u8Size )
    {
        ZNC_BUF_U8_UPD  ( &pau8LinkTxBuffer[u16Length] ,
                          dataPtr [ i ],
                          u16Length );
        i++;
    }

    vSL_WriteMessage ( E_SL_MSG_DATA_INDICATION,
                       u16Length,
                       pau8LinkTxBuffer,
                       u8LinkQuality);
}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
