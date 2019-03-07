/*****************************************************************************
 *
 * MODULE: ZigbeeNodeControlBridge
 *
 * COMPONENT: app_zcl_event_handler.c
 *
 * $AUTHOR: Faisal Bhaiyat$
 *
 * DESCRIPTION:
 *
 * $HeadURL: $
 *
 * $Revision:  $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate:  $
 *
 * $Id:  $
 *
 ****************************************************************************
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

#include <jendefs.h>
#include <AppApi.h>
#include "zps_gen.h"
#include "pdum_apl.h"
#include "pdum_gen.h"
#include "PDM.h"
#include "dbg.h"
#include "pwrm.h"

#include "zps_apl_af.h"
#include "zps_apl_zdo.h"
#include "zps_apl_aib.h"
#include "zps_apl_zdp.h"
#include "rnd_pub.h"
#include "mac_pib.h"
#include "string.h"


#include "zcl_options.h"
#include "zll_commission.h"
#include "app_common.h"
#include "AHI_AES.h"
#include "app_events.h"
#include "Log.h"
#include "SerialLink.h"

#ifdef STACK_MEASURE
#include "StackMeasure.h"
#endif

#ifdef DEBUG_ZCL
#define TRACE_ZCL                     TRUE
#else
#define TRACE_ZCL                     FALSE
#endif

#ifdef DEBUG_ZB_CONTROLBRIDGE_TASK
#define TRACE_ZB_CONTROLBRIDGE_TASK   TRUE
#else
#define TRACE_ZB_CONTROLBRIDGE_TASK   FALSE
#endif

#ifdef CLD_GREENPOWER
#include "GreenPower.h"
#include "app_green_power.h"
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define ALIGN(n, v)     ( ((uint32)(v) + ((n) - 1)) & (~((n) - 1)) )
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/



/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PUBLIC uint16 App_u16BufferReadNBO ( uint8         *pu8Struct,
                                     const char    *szFormat,
                                     void          *pvData );
PRIVATE void APP_ZCL_cbGeneralCallback ( tsZCL_CallBackEvent*    psEvent );
PRIVATE void APP_ZCL_cbEndpointCallback ( tsZCL_CallBackEvent*    psEvent );
#ifdef FULL_FUNC_DEVICE
PRIVATE void APP_ZCL_cbZllUtilityCallback ( tsZCL_CallBackEvent*    psEvent );
#endif

teZCL_Status eApp_ZLO_RegisterEndpoint ( tfpZCL_ZCLCallBackFunction    fptr );
void vAPP_ZCL_DeviceSpecific_Init ( void );
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
tsZLO_ControlBridgeDevice    sControlBridge;
tsCLD_ZllDeviceTable         sDeviceTable =  { ZLO_NUMBER_DEVICES,
                                                 { { 0,
                                                    ZLO_PROFILE_ID,
                                                    CONTROL_BRIDGE_DEVICE_ID,
                                                    ZIGBEENODECONTROLBRIDGE_ZLO_ENDPOINT,
                                                    2,
                                                    GROUPS_REQUIRED,
                                                    0
                                                  }}
                                             };
#ifdef FULL_FUNC_DEVICE
tsZllEndpointInfoTable       sEndpointTable;
tsZllGroupInfoTable          sGroupTable;
#endif

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC void* psGetDeviceTable ( void )
{
    return &sDeviceTable;
}

/****************************************************************************
 *
 * NAME: APP_ZCL_vInitialise
 *
 * DESCRIPTION:
 * Initialises ZCL related functions
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void APP_ZCL_vInitialise ( void )
{
    teZCL_Status eZCL_Status;

    /* Initialise ZLL */
    eZCL_Status =  eZCL_Initialise ( &APP_ZCL_cbGeneralCallback, apduZDP );
    if ( eZCL_Status !=  E_ZCL_SUCCESS )
    {
        vLog_Printf ( TRACE_ZCL,LOG_CRIT, "Error: eZCL_Initialise returned %d\r\n", eZCL_Status );
        vSL_LogFlush ( );
    }

    /* Register Commission EndPoint */
    eZCL_Status =  eApp_ZLO_RegisterEndpoint ( &APP_ZCL_cbEndpointCallback );
    if ( eZCL_Status !=  E_ZCL_SUCCESS )
    {
        vLog_Printf ( TRACE_ZB_CONTROLBRIDGE_TASK,LOG_CRIT,"eApp_ZLO_RegisterEndpoint %x\n", eZCL_Status );
        vSL_LogFlush ( );
    }

    sDeviceTable.asDeviceRecords[0].u64IEEEAddr = ZPS_u64NwkNibGetExtAddr( ZPS_pvAplZdoGetNwkHandle() );

    vLog_Printf ( TRACE_ZB_CONTROLBRIDGE_TASK,LOG_DEBUG, "\ntsCLD_Groups %d", sizeof ( tsCLD_Groups ) );
    vLog_Printf ( TRACE_ZB_CONTROLBRIDGE_TASK,LOG_DEBUG, "\ntsCLD_GroupTableEntry %d", sizeof ( tsCLD_GroupTableEntry ) );
    vAPP_ZCL_DeviceSpecific_Init ( );

#ifdef CLD_GREENPOWER
    vApp_GP_RegisterDevice(&APP_ZCL_cbEndpointCallback);
    ZTIMER_eStart(u8GPTimerTick, GP_ZCL_TICK_TIME);
#endif

}

/****************************************************************************
 *
 * NAME: APP_vHandleZclEvents
 *
 * DESCRIPTION:
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
void APP_vHandleZclEvents ( ZPS_tsAfEvent*    psStackEvent )
{
    tsZCL_CallBackEvent    sCallBackEvent;
    uint16                 u16Length =  0;
    uint8                  au8LinkTxBuffer[256];
    uint8                  u8LinkQuality;
    u8LinkQuality=psStackEvent->uEvent.sApsDataIndEvent.u8LinkQuality;
    /*
     * If the 1 second tick timer has expired, restart it and pass
     * the event on to ZCL
     */


    if ( ZTIMER_eGetState( u8TickTimer ) ==  E_ZTIMER_STATE_EXPIRED )
    {

#ifdef STACK_MEASURE
        tsStackInfo    sStackInfo;

        vGetStackMeasure( &sStackInfo );

        DBG_vPrintf ( TRUE, "\r\n TotalSize: %d, uPeakMeasure: %d, Current: %d ",
                                                sStackInfo.u32TotalSize,
                                                sStackInfo.u32PeakMeasure,
                                                sStackInfo.u32CurrentMeasure );
#endif

    }

    vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "ZCL_Task got event %d\r\n",psStackEvent->eType );

    switch ( psStackEvent->eType )
    {

        case ZPS_EVENT_APS_DATA_INDICATION:
            vLog_Printf(TRACE_ZCL,LOG_DEBUG, "\nDATA: SEP=%d DEP=%d Profile=%04x Cluster=%04x\n",
                    psStackEvent->uEvent.sApsDataIndEvent.u8SrcEndpoint,
                    psStackEvent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                    psStackEvent->uEvent.sApsDataIndEvent.u16ProfileId,
                    psStackEvent->uEvent.sApsDataIndEvent.u16ClusterId);
            break;

        case ZPS_EVENT_APS_DATA_CONFIRM:
            vLog_Printf(TRACE_ZCL,LOG_DEBUG, "\nCFM: SEP=%d DEP=%d Status=%d\n",
                    psStackEvent->uEvent.sApsDataConfirmEvent.u8SrcEndpoint,
                    psStackEvent->uEvent.sApsDataConfirmEvent.u8DstEndpoint,
                    psStackEvent->uEvent.sApsDataConfirmEvent.u8Status);

            if ( psStackEvent->uEvent.sApsDataConfirmEvent.u8Status )
            {
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [0],         psStackEvent->uEvent.sApsDataConfirmEvent.u8Status,            u16Length );
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataConfirmEvent.u8SrcEndpoint,       u16Length );
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataConfirmEvent.u8DstEndpoint,       u16Length );
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataConfirmEvent.u8DstAddrMode,       u16Length );
                if (psStackEvent->uEvent.sApsDataConfirmEvent.u8DstAddrMode == 0x03)
                {
                    ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataConfirmEvent.uDstAddr.u64Addr, u16Length );
                }else
                {
                    ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataConfirmEvent.uDstAddr.u16Addr, u16Length );
                }
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], psStackEvent->uEvent.sApsDataConfirmEvent.u8SequenceNum,       u16Length );
                vSL_WriteMessage ( E_SL_MSG_APS_DATA_CONFIRM_FAILED,
                                   u16Length,
                                   au8LinkTxBuffer,
                                   u8LinkQuality);
            }
            break;

        case ZPS_EVENT_APS_DATA_ACK:
            vLog_Printf(TRACE_ZCL,LOG_DEBUG, "\nACK: SEP=%d DEP=%d Profile=%04x Cluster=%04x\n",
                    psStackEvent->uEvent.sApsDataAckEvent.u8SrcEndpoint,
                    psStackEvent->uEvent.sApsDataAckEvent.u8DstEndpoint,
                    psStackEvent->uEvent.sApsDataAckEvent.u16ProfileId,
                    psStackEvent->uEvent.sApsDataAckEvent.u16ClusterId);
            break;
        default:
            break;
    }

    sCallBackEvent.eEventType = E_ZCL_CBET_ZIGBEE_EVENT;
    sCallBackEvent.pZPSevent = psStackEvent;
    vZCL_EventHandler(&sCallBackEvent);

}


/****************************************************************************
 *
 * NAME: APP_ZCL_cbGeneralCallback
 *
 * DESCRIPTION:
 * General callback for ZCL events
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void APP_ZCL_cbGeneralCallback ( tsZCL_CallBackEvent*    psEvent )
{
#if TRUE == TRACE_ZCL
    switch ( psEvent->eEventType )
    {
        case E_ZCL_CBET_LOCK_MUTEX:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG,"EVT: Lock Mutex\r\n" );
            break;

        case E_ZCL_CBET_UNLOCK_MUTEX:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EVT: Unlock Mutex\r\n" );
            break;

        case E_ZCL_CBET_UNHANDLED_EVENT:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EVT: Unhandled Event\r\n" );
            break;

        case E_ZCL_CBET_READ_ATTRIBUTES_RESPONSE:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EVT: Read attributes response\r\n" );
            break;

        case E_ZCL_CBET_READ_REQUEST:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EVT: Read request\r\n" );
            break;

        case E_ZCL_CBET_DEFAULT_RESPONSE:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EVT: Default response\r\n" );
            break;

        case E_ZCL_CBET_ERROR:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EVT: Error\r\n" );
            break;

        case E_ZCL_CBET_TIMER:
            break;

        case E_ZCL_CBET_ZIGBEE_EVENT:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EVT: ZigBee\r\n" );
            break;

        case E_ZCL_CBET_CLUSTER_CUSTOM:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EP EVT: Custom\r\n" );
            break;

        default:
            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "Invalid event type\r\n" );
            break;
    }
#endif
}


/****************************************************************************
 *
 * NAME: APP_ZCL_cbEndpointCallback
 *
 * DESCRIPTION:
 * Endpoint specific callback for ZCL events
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void APP_ZCL_cbEndpointCallback ( tsZCL_CallBackEvent*    psEvent )
{
    uint16                 u16Length =  0;
    uint8                  au8LinkTxBuffer[256];
    uint8     				u8LinkQuality;
    u8LinkQuality=psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8LinkQuality;

    
    //ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [0],         psEvent->pZPSevent->uEvent.sApsZgpDataIndEvent.u8Rssi,             u16Length );
   // ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsInterPanDataIndEvent.u8LinkQuality, u16Length );
    //ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8LinkQuality,         u16Length );
    //vSL_WriteMessage ( 0x9999, u16Length,au8LinkTxBuffer,u8LinkQuality);
    u16Length =  0;

    
    switch (psEvent->eEventType)
    {
        case E_ZCL_CBET_LOCK_MUTEX:
        case E_ZCL_CBET_UNLOCK_MUTEX:
        case E_ZCL_CBET_READ_ATTRIBUTES_RESPONSE:
        case E_ZCL_CBET_READ_REQUEST:
        case E_ZCL_CBET_TIMER:
        case E_ZCL_CBET_ZIGBEE_EVENT:
            //vLog_Printf(TRACE_ZCL, "EP EVT:No action\r\n");
            break;

        case E_ZCL_CBET_ERROR:
        {
            vLog_Printf (TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_ERROR) - Error: 0x%02x", psEvent->eZCL_Status );
        }
        break;

        case E_ZCL_CBET_UNHANDLED_EVENT:
        {
            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_UNHANDLED_EVENT)" );
        }
        break;

        case E_ZCL_CBET_DEFAULT_RESPONSE:
        {
            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_DEFAULT_RESPONSE)" );

            if( psEvent->psClusterInstance != NULL )
            {
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [0],          psEvent->u8TransactionSequenceNumber,                            u16Length );
                //ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr, u16Length );
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,       u16Length );
                //ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,       u16Length );
                ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId,        u16Length );
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->uMessage.sDefaultResponse.u8CommandId,                  u16Length );
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->uMessage.sDefaultResponse.u8StatusCode,                 u16Length );
                vSL_WriteMessage ( E_SL_MSG_DEFAULT_RESPONSE,
                                   u16Length,
                                   au8LinkTxBuffer,
                                   u8LinkQuality);
            }
        }
        break;


        case E_ZCL_CBET_WRITE_ATTRIBUTES_RESPONSE:
        case E_ZCL_CBET_REPORT_INDIVIDUAL_ATTRIBUTE:
        case E_ZCL_CBET_READ_INDIVIDUAL_ATTRIBUTE_RESPONSE:
        {
            uint16    u16SizeOfAttribute = 0;
            uint8     u16Elements =  0;
            uint16    i =  0;
            switch ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType )
            {
            case(E_ZCL_OSTRING):
            case(E_ZCL_CSTRING):
               if ( psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData != NULL )
               {
                   u16Elements =  ( (uint8*)psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData ) [ 0 ];
               }
               else
               {
                   u16Elements   =  0 ;
               }
            break;
            case(E_ZCL_LOSTRING):
            case(E_ZCL_LCSTRING):
            case(E_ZCL_STRUCT):

                if ( psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData != NULL )
                {
                    u16Elements =  ( (uint16*)psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData ) [ 0 ];
                }
                else
                {
                    u16Elements   =  0 ;
                }
            break;
            default:
                u16Elements   =  1;
                break;
            }
            u16SizeOfAttribute =  APP_u16GetAttributeActualSize ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType, u16Elements );
            vLog_Printf ( TRACE_ZB_CONTROLBRIDGE_TASK,LOG_DEBUG, " Read Attrib Rsp %d %02x\n", psEvent->uMessage.sIndividualAttributeResponse.eAttributeStatus,
                                                                                      * ( ( uint8* ) psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData ) );


            /* Send event upwards */
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [0],          psEvent->u8TransactionSequenceNumber,                               u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,          u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId,           u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->uMessage.sIndividualAttributeResponse.u16AttributeEnum,    u16Length );
          //  if (psEvent->eEventType != E_ZCL_CBET_REPORT_INDIVIDUAL_ATTRIBUTE)
          //  {
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->uMessage.sIndividualAttributeResponse.eAttributeStatus,    u16Length );
          //  }
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType,  u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  u16SizeOfAttribute,                                                 u16Length );
            if ( u16SizeOfAttribute !=  0 )
            {
                vLog_Printf(TRACE_ZB_CONTROLBRIDGE_TASK,LOG_DEBUG,"\nElément : %d\n",i);
                while ( i <  u16Elements )
                {
                    if( ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_OSTRING ) ||
                        ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_CSTRING ) )
                    {
                        tsZCL_OctetString sString = *( ( tsZCL_OctetString* ) psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],   ( ( uint8* ) sString.pu8Data )[i],    u16Length );
                    }
                    else if ( ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_LOSTRING ) ||
                              ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_LCSTRING ) )
                    {
                        tsZCL_LongOctetString sString =  *( ( tsZCL_LongOctetString* ) psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],   ( ( uint8* ) sString.pu8Data )[i],    u16Length );
                    }
                    else if ( ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_FLOAT_SINGLE ) ||
                            ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_FLOAT_DOUBLE ) ||
                            ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_UINT32 )||
                            ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_INT24 )||
                            ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_UINT24 )||
                            ( psEvent->uMessage.sIndividualAttributeResponse.eAttributeDataType ==  E_ZCL_UINT48 ))

                    {
                    	uint32    u32value =  *( ( uint32* ) psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData );
                    	ZNC_BUF_U32_UPD  ( &au8LinkTxBuffer [u16Length],   u32value,    u16Length );

                    }
                    else if ( u16SizeOfAttribute / u16Elements == sizeof(uint8) )
                    {
                        uint8    u8value =  *( ( uint8* ) psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],   u8value,    u16Length );
                    }

                    else if ( u16SizeOfAttribute / u16Elements == sizeof(uint16) )
                    {
                        App_u16BufferReadNBO ( &au8LinkTxBuffer [u16Length],  "h",  psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData);
                        u16Length += sizeof(uint16);
                    }

                    else if ( u16SizeOfAttribute / u16Elements == sizeof(uint32) )
                    {
                        App_u16BufferReadNBO ( &au8LinkTxBuffer [u16Length],  "w",  psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData);
                        u16Length += sizeof(uint32);
                    }

                    else if ( u16SizeOfAttribute / u16Elements == sizeof(uint64) )
                    {
                        App_u16BufferReadNBO ( &au8LinkTxBuffer [u16Length],  "l",  psEvent->uMessage.sIndividualAttributeResponse.pvAttributeData);
                        u16Length += sizeof(uint64);
                    }

                    i++;
                }
            }

            if((psEvent->eEventType == E_ZCL_CBET_READ_INDIVIDUAL_ATTRIBUTE_RESPONSE))
                vSL_WriteMessage ( E_SL_MSG_READ_ATTRIBUTE_RESPONSE,
                                   u16Length,
                                   au8LinkTxBuffer,
                                   u8LinkQuality );
            else if((psEvent->eEventType == E_ZCL_CBET_REPORT_INDIVIDUAL_ATTRIBUTE))
                vSL_WriteMessage ( E_SL_MSG_REPORT_IND_ATTR_RESPONSE,
                                   u16Length,
                                   au8LinkTxBuffer,
                                   u8LinkQuality );
            else if((psEvent->eEventType == E_ZCL_CBET_WRITE_ATTRIBUTES_RESPONSE))
                vSL_WriteMessage ( E_SL_MSG_WRITE_ATTRIBUTE_RESPONSE,
                                   u16Length,
                                   au8LinkTxBuffer,
                                   u8LinkQuality );

        }
        break;

        case E_ZCL_CBET_REPORT_ATTRIBUTES_CONFIGURE_RESPONSE:
        {
            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_REPORT_ATTRIBUTES_CONFIGURE_RESPONSE)" );

            /* Send event upwards */
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [0],          psEvent->u8TransactionSequenceNumber,                                        u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,             u16Length );
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,                   u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length], psEvent->psClusterInstance->psClusterDefinition->u16ClusterEnum,              u16Length );
            //FRED
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->uMessage.sAttributeReportingConfigurationResponse.sAttributeReportingConfigurationRecord.u16AttributeEnum,              u16Length );
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], psEvent->uMessage.sAttributeReportingConfigurationResponse.eCommandStatus,    u16Length );
            vSL_WriteMessage ( E_SL_MSG_CONFIG_REPORTING_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               u8LinkQuality );
        }
        break;

        case E_ZCL_CBET_REPORT_READ_INDIVIDUAL_ATTRIBUTE_CONFIGURATION_RESPONSE:
        {
            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_REPORT_READ_INDIVIDUAL_ATTRIBUTE_CONFIGURATION_RESPONSE)" );

            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [0],          psEvent->u8TransactionSequenceNumber,                                        u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,             u16Length );
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,                   u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->psClusterInstance->psClusterDefinition->u16ClusterEnum,              u16Length );
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->uMessage.sAttributeReportingConfigurationResponse.eCommandStatus,    u16Length );
            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],
                              psEvent->uMessage.sAttributeReportingConfigurationResponse.sAttributeReportingConfigurationRecord.eAttributeDataType,
                              u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],
                              psEvent->uMessage.sAttributeReportingConfigurationResponse.sAttributeReportingConfigurationRecord.u16AttributeEnum,
                              u16Length );
            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],
                              psEvent->uMessage.sAttributeReportingConfigurationResponse.sAttributeReportingConfigurationRecord.u16MaximumReportingInterval,
                              u16Length );

            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],
                              psEvent->uMessage.sAttributeReportingConfigurationResponse.sAttributeReportingConfigurationRecord.u16MinimumReportingInterval,
                              u16Length );

            vSL_WriteMessage ( E_SL_MSG_READ_REPORT_CONFIG_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               u8LinkQuality );
        }
        break;

        case E_ZCL_CBET_DISCOVER_INDIVIDUAL_ATTRIBUTE_RESPONSE:
        {
            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_DISCOVER_INDIVIDUAL_ATTRIBUTE_RESPONSE)" );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [0],         psEvent->uMessage.sAttributeDiscoveryResponse.bDiscoveryComplete,    u16Length );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psEvent->uMessage.sAttributeDiscoveryResponse.eAttributeDataType,    u16Length );
            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length], psEvent->uMessage.sAttributeDiscoveryResponse.u16AttributeEnum,      u16Length );
            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,          u16Length );
            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->psClusterInstance->psClusterDefinition->u16ClusterEnum,    u16Length );

            vSL_WriteMessage ( E_SL_MSG_ATTRIBUTE_DISCOVERY_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               u8LinkQuality );
        }
        break;

         case E_ZCL_CBET_DISCOVER_INDIVIDUAL_ATTRIBUTE_EXTENDED_RESPONSE:
        {
            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_DISCOVER_INDIVIDUAL_ATTRIBUTE_EXTENDED_RESPONSE)" );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [0],         psEvent->uMessage.sAttributeDiscoveryResponse.bDiscoveryComplete,         u16Length );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psEvent->uMessage.sAttributeDiscoveryResponse.eAttributeDataType,         u16Length );
            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length], psEvent->uMessage.sAttributeDiscoveryResponse.u16AttributeEnum,           u16Length );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psEvent->uMessage.sAttributeDiscoveryExtenedResponse.u8AttributeFlags,    u16Length );

            vSL_WriteMessage ( E_SL_MSG_ATTRIBUTE_EXT_DISCOVERY_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               u8LinkQuality );
        }
        break;

        case E_ZCL_CBET_DISCOVER_INDIVIDUAL_COMMAND_RECEIVED_RESPONSE:
        {
            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_DISCOVER_INDIVIDUAL_COMMAND_RECEIVED_RESPONSE)" );

            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [0],         psEvent->uMessage.sCommandsReceivedDiscoveryIndividualResponse.u8CommandEnum,     u16Length );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psEvent->uMessage.sCommandsReceivedDiscoveryIndividualResponse.u8CommandIndex,    u16Length );
            vSL_WriteMessage ( E_SL_MSG_COMMAND_RECEIVED_DISCOVERY_INDIVIDUAL_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               u8LinkQuality );
        }
        break;
        
        case E_ZCL_CBET_DISCOVER_COMMAND_RECEIVED_RESPONSE:
        {
            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_DISCOVER_COMMAND_RECEIVED_RESPONSE)" );
            ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [0],          psEvent->uMessage.sCommandsReceivedDiscoveryResponse.bDiscoveryComplete,    u16Length );
            ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->uMessage.sCommandsReceivedDiscoveryResponse.u8NumberOfCommands,    u16Length );

            vSL_WriteMessage ( E_SL_MSG_COMMAND_RECEIVED_DISCOVERY_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               u8LinkQuality );
        }
        break;

        case E_ZCL_CBET_DISCOVER_INDIVIDUAL_COMMAND_GENERATED_RESPONSE:
        {
            vLog_Printf(TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_DISCOVER_INDIVIDUAL_COMMAND_GENERATED_RESPONSE)");
            ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [0],          psEvent->uMessage.sCommandsGeneratedDiscoveryIndividualResponse.u8CommandEnum,    u16Length );
            ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [u16Length],  psEvent->uMessage.sCommandsGeneratedDiscoveryIndividualResponse.u8CommandIndex,   u16Length );
            vSL_WriteMessage ( E_SL_MSG_COMMAND_GENERATED_DISCOVERY_INDIVIDUAL_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               u8LinkQuality );
        }
        break;

        case E_ZCL_CBET_DISCOVER_COMMAND_GENERATED_RESPONSE:
        {
            vLog_Printf(TRACE_ZCL, LOG_DEBUG, " (E_ZCL_CBET_DISCOVER_INDIVIDUAL_COMMAND_GENERATED_RESPONSE)");
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [0],         psEvent->uMessage.sCommandsGeneratedDiscoveryResponse.bDiscoveryComplete,    u16Length );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length], psEvent->uMessage.sCommandsGeneratedDiscoveryResponse.u8NumberOfCommands,    u16Length );

            vSL_WriteMessage ( E_SL_MSG_COMMAND_GENERATED_DISCOVERY_RESPONSE,
                               u16Length,
                               au8LinkTxBuffer,
                               u8LinkQuality );
        }
        break;
        
        case E_ZCL_CBET_CLUSTER_CUSTOM:
        {
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [0],          psEvent->u8TransactionSequenceNumber,                               u16Length );
            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,          u16Length );
            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->psClusterInstance->psClusterDefinition->u16ClusterEnum,    u16Length );

            vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EP EVT: Custom %04x\r\n", psEvent->uMessage.sClusterCustomMessage.u16ClusterId );
            switch (psEvent->uMessage.sClusterCustomMessage.u16ClusterId)
            {
                case GENERAL_CLUSTER_ID_BASIC:
                {
                    tsCLD_BasicCallBackMessage *psCallBackMessage = (tsCLD_BasicCallBackMessage*)psEvent->uMessage.sClusterCustomMessage.pvCustomData;
                    if (psCallBackMessage->u8CommandId == E_CLD_BASIC_CMD_RESET_TO_FACTORY_DEFAULTS )
                    {
                        /*Clearing of cluster data*/
                        memset(&sControlBridge,0,sizeof(tsZLO_ControlBridgeDevice));
                        eApp_ZLO_RegisterEndpoint(&APP_ZCL_cbEndpointCallback);
                        vAPP_ZCL_DeviceSpecific_Init();
#ifdef CLD_GREENPOWER
                        vApp_GP_RegisterDevice(&APP_ZCL_cbEndpointCallback);
#endif
                     }
                 }
                 break;

#ifdef CLD_OTA
                case OTA_CLUSTER_ID:
                {
                    tsOTA_CallBackMessage*    psCallBackMessage =  ( tsOTA_CallBackMessage* ) psEvent->uMessage.sClusterCustomMessage.pvCustomData;

                    vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "OTA_CLUSTER_ID - Event ID: %d\r\n", psCallBackMessage->eEventId );

                    switch ( psCallBackMessage->eEventId )
                    {
                        case E_CLD_OTA_COMMAND_QUERY_NEXT_IMAGE_REQUEST:
                        {
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "E_CLD_OTA_COMMAND_QUERY_NEXT_IMAGE_REQUEST\r\n" );
                        }
                        break;

                        case E_CLD_OTA_COMMAND_BLOCK_REQUEST:
                        {

                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "E_CLD_OTA_COMMAND_BLOCK_REQUEST\r\n" );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "SrcAddress: %04x\r\n", psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "RequestNodeAddress: %016llx\r\n", psCallBackMessage->uMessage.sBlockRequestPayload.u64RequestNodeAddress );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "FileOffset: %08x\r\n", psCallBackMessage->uMessage.sBlockRequestPayload.u32FileOffset );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "FileVersion: %08x\r\n", psCallBackMessage->uMessage.sBlockRequestPayload.u32FileVersion );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "ImageType: %04x\r\n", psCallBackMessage->uMessage.sBlockRequestPayload.u16ImageType );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "ManufactureCode: %04x\r\n", psCallBackMessage->uMessage.sBlockRequestPayload.u16ManufactureCode );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "BlockRequestDelay: %04x\r\n", psCallBackMessage->uMessage.sBlockRequestPayload.u16BlockRequestDelay );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "MaxDataSize: %02x\r\n", psCallBackMessage->uMessage.sBlockRequestPayload.u8MaxDataSize );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "FieldControl: %02x\r\n", psCallBackMessage->uMessage.sBlockRequestPayload.u8FieldControl );

                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],          psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode,                 u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,           u16Length );
                            ZNC_BUF_U64_UPD  ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sBlockRequestPayload.u64RequestNodeAddress,    u16Length );
                            ZNC_BUF_U32_UPD  ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sBlockRequestPayload.u32FileOffset,            u16Length );
                            ZNC_BUF_U32_UPD  ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sBlockRequestPayload.u32FileVersion,           u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sBlockRequestPayload.u16ImageType,             u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sBlockRequestPayload.u16ManufactureCode,       u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sBlockRequestPayload.u16BlockRequestDelay,     u16Length );
                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sBlockRequestPayload.u8MaxDataSize,            u16Length );
                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sBlockRequestPayload.u8FieldControl,           u16Length );

                            vSL_WriteMessage ( E_SL_MSG_BLOCK_REQUEST,
                                               u16Length,
                                               au8LinkTxBuffer,
                                               u8LinkQuality );
                        }
                        break;

                        case E_CLD_OTA_COMMAND_UPGRADE_END_REQUEST:
                        {
                            tsCLD_PR_Ota    sOTAData;
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "E_CLD_OTA_COMMAND_UPGRADE_END_REQUEST\r\n" );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "SrcAddress: %04x\r\n", psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "FileVersion: %08x\r\n", psCallBackMessage->uMessage.sUpgradeEndRequestPayload.u32FileVersion );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "ImageType: %04x\r\n", psCallBackMessage->uMessage.sUpgradeEndRequestPayload.u16ImageType );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "ManufacturerCode: %04x\r\n", psCallBackMessage->uMessage.sUpgradeEndRequestPayload.u16ManufacturerCode );
                            vLog_Printf ( TRACE_ZCL, LOG_DEBUG, "Status: %02x\r\n", psCallBackMessage->uMessage.sUpgradeEndRequestPayload.u8Status );


                            (  void ) eOTA_GetServerData ( ZIGBEENODECONTROLBRIDGE_ZLO_ENDPOINT,  0,  &sOTAData );
                            sOTAData.u32RequestOrUpgradeTime =  sOTAData.u32CurrentTime + 5;
                            ( void ) eOTA_SetServerParams ( ZIGBEENODECONTROLBRIDGE_ZLO_ENDPOINT, 0, &sOTAData );

                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],          psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode,                    u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,              u16Length );
                            ZNC_BUF_U32_UPD  ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sUpgradeEndRequestPayload.u32FileVersion,         u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sUpgradeEndRequestPayload.u16ImageType,           u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sUpgradeEndRequestPayload.u16ManufacturerCode,    u16Length );
                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],  psCallBackMessage->uMessage.sUpgradeEndRequestPayload.u8Status,               u16Length );

                            vSL_WriteMessage ( E_SL_MSG_UPGRADE_END_REQUEST,
                                               u16Length,
                                               au8LinkTxBuffer,
                                               u8LinkQuality  );
                            uint32 i;
                            for (i=0;i<OTA_TOTAL_ACTIVE_IMAGES_ON_SERVER;i++)
                            {
                                psCallBackMessage->aServerPrams[i].u32CurrentTime=0;
                                psCallBackMessage->aServerPrams[i].u32RequestOrUpgradeTime=5;
                            }
                        }
                        break;

                        default:
                        {
                            /* Do nothing */
                        }
                        break;
                    }
                }
                break;
#endif

                case GENERAL_CLUSTER_ID_ONOFF:
                {
                    tsCLD_OnOffCallBackMessage*    psCallBackMessage =  ( tsCLD_OnOffCallBackMessage* ) psEvent->uMessage.sClusterCustomMessage.pvCustomData;

                    vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "- for onoff cluster\r\n" );
                    vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "\r\nCMD: 0x%02x\r\n", psCallBackMessage->u8CommandId );

                    ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],          psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode,    u16Length );
                    if ( psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode ==  0x03 )
                    {
                        ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u64Addr,    u16Length );
                    }
                    else
                    {
                        ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
                    }

                    ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [u16Length], psCallBackMessage->u8CommandId,    u16Length );

                    if (psCallBackMessage->u8CommandId ==0x40)
					{
						ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [u16Length], psCallBackMessage->uMessage.psOffWithEffectRequestPayload->u8EffectId,    u16Length );
						ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [u16Length], psCallBackMessage->uMessage.psOffWithEffectRequestPayload->u8EffectVariant,    u16Length );
					}

                    vSL_WriteMessage ( E_SL_MSG_ONOFF_UPDATE,
                                       u16Length,
                                       au8LinkTxBuffer,
                                       u8LinkQuality );
                }
                break;
                case GENERAL_CLUSTER_ID_LEVEL_CONTROL:
				{
					tsCLD_LevelControlCallBackMessage*    psCallBackMessage =  ( tsCLD_LevelControlCallBackMessage* ) psEvent->uMessage.sClusterCustomMessage.pvCustomData;

					vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "- for levelcontrol cluster\r\n" );
					vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "\r\nCMD: 0x%02x\r\n", psCallBackMessage->u8CommandId );

					ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],          psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode,    u16Length );
					if ( psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode ==  0x03 )
					{
						ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u64Addr,    u16Length );
					}
					else
					{
						ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
					}

					ZNC_BUF_U8_UPD ( &au8LinkTxBuffer [u16Length], psCallBackMessage->u8CommandId,    u16Length );
					if (psCallBackMessage->u8CommandId == 0x04)
					{
						ZNC_BUF_U8_UPD(&au8LinkTxBuffer [u16Length], psCallBackMessage->uMessage.psMoveToLevelCommandPayload->u8Level,    u16Length );
						ZNC_BUF_U16_UPD(&au8LinkTxBuffer [u16Length], psCallBackMessage->uMessage.psMoveToLevelCommandPayload->u16TransitionTime,    u16Length );

					}else if (psCallBackMessage->u8CommandId == 0x02)
					{
						ZNC_BUF_U8_UPD(&au8LinkTxBuffer [u16Length], psCallBackMessage->uMessage.psStepCommandPayload->u8StepMode,    u16Length );
						ZNC_BUF_U8_UPD(&au8LinkTxBuffer [u16Length], psCallBackMessage->uMessage.psStepCommandPayload->u8StepSize,    u16Length );
						ZNC_BUF_U16_UPD(&au8LinkTxBuffer [u16Length], psCallBackMessage->uMessage.psStepCommandPayload->u16TransitionTime,    u16Length );

					}
					vSL_WriteMessage ( E_SL_MSG_MOVE_TO_LEVEL_UPDATE,
									   u16Length,
									   au8LinkTxBuffer,
									   u8LinkQuality );
				}
				break;
                case GENERAL_CLUSTER_ID_IDENTIFY:
                    vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "- for identify cluster\r\n" );
                break;

                //FCSM
                case GENERAL_CLUSTER_ID_MULTISTATE_INPUT_BASIC:
					vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "- GENERAL_CLUSTER_ID_MULTISTATE_INPUT_BASIC\r\n" );

				break;

                case GENERAL_CLUSTER_ID_GROUPS:
                {
                    uint16                          u16Command =  0;
                    tsCLD_GroupsCallBackMessage*    pCustom    =  ( ( tsCLD_GroupsCallBackMessage* ) psEvent->uMessage.sClusterCustomMessage.pvCustomData );
                    vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "- for groups cluster\r\n" );


                    switch(pCustom->u8CommandId)
                    {
                        case (E_CLD_GROUPS_CMD_ADD_GROUP):
                        {
                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],          pCustom->uMessage.psAddGroupResponsePayload->eStatus,       u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],          pCustom->uMessage.psAddGroupResponsePayload->u16GroupId,    u16Length );
                            u16Command = E_SL_MSG_ADD_GROUP_RESPONSE;
                        }
                        break;

                        case (E_CLD_GROUPS_CMD_VIEW_GROUP):
                        {
                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],         pCustom->uMessage.psViewGroupResponsePayload->eStatus,       u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],         pCustom->uMessage.psViewGroupResponsePayload->u16GroupId,    u16Length );
                            u16Command =  E_SL_MSG_VIEW_GROUP_RESPONSE;
                        }
                        break;

                        case (E_CLD_GROUPS_CMD_GET_GROUP_MEMBERSHIP):
                        {
                            uint8    groupCount =  pCustom->uMessage.psGetGroupMembershipResponsePayload->u8GroupCount;
                            uint8    i          =  0;
                            if (groupCount>CLD_GROUPS_MAX_NUMBER_OF_GROUPS)
                            {
                            	groupCount=CLD_GROUPS_MAX_NUMBER_OF_GROUPS;
                            }

                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],          pCustom->uMessage.psGetGroupMembershipResponsePayload->u8Capacity,    u16Length );
                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],          groupCount,                                                           u16Length );

                            while ( i <  groupCount )
                            {
                                ZNC_BUF_U16_UPD   ( &au8LinkTxBuffer [u16Length],     pCustom->uMessage.psGetGroupMembershipResponsePayload->pi16GroupList [i],    u16Length );
                                i++;
                            }
                            u16Command =  E_SL_MSG_GET_GROUP_MEMBERSHIP_RESPONSE;

                        }
                        break;

                        case (E_CLD_GROUPS_CMD_REMOVE_GROUP):
                        {

                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],         pCustom->uMessage.psRemoveGroupResponsePayload->eStatus,       u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length], pCustom->uMessage.psRemoveGroupResponsePayload->u16GroupId,    u16Length );

                            u16Command =  E_SL_MSG_REMOVE_GROUP_RESPONSE;
                        }
                        break;

                        default:
                        break;
                    }
                    //FRED Rajout srcAddr https://github.com/fairecasoimeme/ZiGate/issues/123
                    ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
                    vSL_WriteMessage ( u16Command,
                                       u16Length,
                                       au8LinkTxBuffer,
                                       u8LinkQuality );

                }//General Group cluster id
                break;
#ifdef FULL_FUNC_DEVICE
                case 0x1000:
                    vLog_Printf(TRACE_ZCL,LOG_DEBUG, "\n    - for 0x1000");
                    if ( psEvent->pZPSevent->eType == ZPS_EVENT_APS_INTERPAN_DATA_INDICATION  &&
                         psEvent->pZPSevent->uEvent.sApsInterPanDataIndEvent.u16ProfileId ==  ZLL_PROFILE_ID )
                    {
                        tsBDB_ZCLEvent sEvent;
                        sEvent.eType = BDB_E_ZCL_EVENT_TL_IPAN_MSG;
                        sEvent.psCallBackEvent = psEvent;

                        BDB_vZclEventHandler(&sEvent);
                    } else if ( psEvent->pZPSevent->eType == ZPS_EVENT_APS_DATA_INDICATION  &&
                            psEvent->pZPSevent->uEvent.sApsDataIndEvent.u16ProfileId == ZLO_PROFILE_ID )
                    {
                        APP_ZCL_cbZllUtilityCallback(psEvent);
                    }

                    break;
#endif
                case GENERAL_CLUSTER_ID_SCENES:
                {

                    uint16                          u16Command =  0;
                    tsCLD_ScenesCallBackMessage*    pCustom =  ( ( tsCLD_ScenesCallBackMessage* ) psEvent->uMessage.sClusterCustomMessage.pvCustomData );
                    vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "- for groups cluster\r\n" );
                    switch( pCustom->u8CommandId )
                    {
                        case (E_CLD_SCENES_CMD_ADD):
                        {
                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],            pCustom->uMessage.psAddSceneResponsePayload->eStatus,              u16Length );
                            ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psAddSceneResponsePayload->u16GroupId,           u16Length );
                            ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psAddSceneResponsePayload->u8SceneId,    u16Length );
                            u16Command = E_SL_MSG_ADD_SCENE_RESPONSE;
                        }
                        break;//ADD SCENE

                        case (E_CLD_SCENES_CMD_VIEW):
                        {
                            uint16    i =  0;
                            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psViewSceneResponsePayload->eStatus,                   u16Length );
                            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psViewSceneResponsePayload->u16GroupId,                u16Length );
                            ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psAddSceneResponsePayload->u8SceneId,                  u16Length );

                            /* Consider remaining items only if Status field in the ViewSceneRespone command is 0x00 = SUCCESS */
                            if( E_ZCL_SUCCESS == pCustom->uMessage.psViewSceneResponsePayload->eStatus)
                            {
                                ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psViewSceneResponsePayload->u16TransitionTime,         u16Length );
                                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psViewSceneResponsePayload->sSceneName.u8Length,       u16Length );
                                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psViewSceneResponsePayload->sSceneName.u8MaxLength,    u16Length );

                                while ( i <  pCustom->uMessage.psViewSceneResponsePayload->sSceneName.u8Length )
                                {
                                    ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psViewSceneResponsePayload->sSceneName.pu8Data [i] ,    u16Length );
                                    i++;
                                }
                                ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psViewSceneResponsePayload->sExtensionField.u16Length,    u16Length );
                                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psViewSceneResponsePayload->sSceneName.u8MaxLength,       u16Length );

                                i =  0;
                                while ( i <  pCustom->uMessage.psViewSceneResponsePayload->sExtensionField.u16Length )
                                {
                                    ZNC_BUF_U8_UPD   ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psViewSceneResponsePayload->sExtensionField.pu8Data [i] ,    u16Length );
                                    i++;
                                }
                            }

                            u16Command =  E_SL_MSG_VIEW_SCENE_RESPONSE;
                    }
                    break; // VIEW SCENE

                    case (E_CLD_SCENES_CMD_REMOVE):
                    {
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],            pCustom->uMessage.psRemoveSceneResponsePayload->eStatus,       u16Length );
                        ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psRemoveSceneResponsePayload->u16GroupId,    u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psRemoveSceneResponsePayload->u8SceneId,     u16Length );
                        u16Command =  E_SL_MSG_REMOVE_SCENE_RESPONSE;
                    }
                    break; // REMOVE SCENE

                    case (E_CLD_SCENES_CMD_REMOVE_ALL):
                    {
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],            pCustom->uMessage.psRemoveAllScenesResponsePayload->eStatus,       u16Length );
                        ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psRemoveAllScenesResponsePayload->u16GroupId,    u16Length );
                        u16Command =  E_SL_MSG_REMOVE_ALL_SCENES_RESPONSE;
                    }
                    break; // REMOVE ALL SCENES

                    case (E_CLD_SCENES_CMD_STORE):
                    {

                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],            pCustom->uMessage.psStoreSceneResponsePayload->eStatus,       u16Length );
                        ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psStoreSceneResponsePayload->u16GroupId,    u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psStoreSceneResponsePayload->u8SceneId,     u16Length );
                        u16Command =  E_SL_MSG_STORE_SCENE_RESPONSE;
                    }
                    break; // STORE SCENE

                    case (E_CLD_SCENES_CMD_GET_SCENE_MEMBERSHIP):
                    {
                        uint8    i =  0;
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],            pCustom->uMessage.psGetSceneMembershipResponsePayload->eStatus,         u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psGetSceneMembershipResponsePayload->u8Capacity,      u16Length );
                        ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psGetSceneMembershipResponsePayload->u16GroupId,      u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psGetSceneMembershipResponsePayload->u8SceneCount,    u16Length );

                        while ( i <  pCustom->uMessage.psGetSceneMembershipResponsePayload->u8SceneCount )
                        {
                           ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], pCustom->uMessage.psGetSceneMembershipResponsePayload->pu8SceneList [ i ] ,    u16Length );
                           i++;
                        }
                        u16Command =  E_SL_MSG_SCENE_MEMBERSHIP_RESPONSE;
                    }
                    break; // SCENE MEMBERSHIP RESPONSE

                    case (E_CLD_SCENES_CMD_IKEA_REMOTE_SHORT_CLICK):
                    case (E_CLD_SCENES_CMD_IKEA_REMOTE_BUTTON_DOWN):
                    case (E_CLD_SCENES_CMD_IKEA_REMOTE_BUTTON_UP):
                    {
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], pCustom->u8CommandId,                                           u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], pCustom->uMessage.psIkeaRemoteSceneCustomPayload->u8Direction,  u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], pCustom->uMessage.psIkeaRemoteSceneCustomPayload->u8Attr1,      u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], pCustom->uMessage.psIkeaRemoteSceneCustomPayload->u8Attr2,      u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], pCustom->uMessage.psIkeaRemoteSceneCustomPayload->u8Attr3,      u16Length );
                        u16Command = E_SL_MSG_SCENE_IKEA_REMOTE_BUTTON_PRESS;
                    }
                    break;//IKEA REMOTE CUSTOM

                    default:
                    break;
                }
                //FRED Rajout de srcAddr https://github.com/fairecasoimeme/ZiGate/issues/123
                ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
                vSL_WriteMessage( u16Command,
                                  u16Length,
                                  au8LinkTxBuffer,
                                  u8LinkQuality );
            }
            break;

            case SECURITY_AND_SAFETY_CLUSTER_ID_IASZONE:
            {
                tsCLD_IASZoneCallBackMessage*    psCallBackMessage =  ( tsCLD_IASZoneCallBackMessage* ) psEvent->uMessage.sClusterCustomMessage.pvCustomData;
                vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "- for IASZone cluster\r\n" );
                vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "\r\nCMD: 0x%02x\r\n", psCallBackMessage->u8CommandId );

                switch ( psCallBackMessage->u8CommandId )
                {
                    case E_CLD_IASZONE_CMD_ZONE_ENROLL_REQUEST:
                    {
                    }
                    break;

                    case E_CLD_IASZONE_CMD_ZONE_STATUS_CHANGE_NOTIFICATION:
                    {
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode,    u16Length );

                        if ( psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode ==  0x03 )
                        {
                            ZNC_BUF_U64_UPD ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u64Addr,    u16Length );
                        }
                        else
                        {
                            ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length], psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr,    u16Length );
                        }
                        ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],    psCallBackMessage->uMessage.psZoneStatusNotificationPayload->b16ZoneStatus,    u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    psCallBackMessage->uMessage.psZoneStatusNotificationPayload->b8ExtendedStatus,    u16Length );
                        ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    psCallBackMessage->uMessage.psZoneStatusNotificationPayload->u8ZoneId,    u16Length );
                        ZNC_BUF_U16_UPD ( &au8LinkTxBuffer [u16Length],    psCallBackMessage->uMessage.psZoneStatusNotificationPayload->u16Delay,    u16Length );

                        vSL_WriteMessage ( E_SL_MSG_IAS_ZONE_STATUS_CHANGE_NOTIFY,
                                           u16Length,
                                           au8LinkTxBuffer,
                                           u8LinkQuality );
                    }
                    break; //IAS ZONE CHANGE NOTIFY

                    default:
                    {
                    }
                    break;
                }
            }
            break;
            case APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_STATISTICS:
            {
                tsCLD_ApplianceStatisticsCallBackMessage*    pCustom =  ( tsCLD_ApplianceStatisticsCallBackMessage* ) psEvent->uMessage.sClusterCustomMessage.pvCustomData;
                uint32                                        i      =  0;
                ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],            pCustom->u8CommandId,    u16Length );
                ZNC_BUF_U32_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psLogNotificationORLogResponsePayload->utctTime,        u16Length );
                ZNC_BUF_U32_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psLogNotificationORLogResponsePayload->u32LogId,        u16Length );
                ZNC_BUF_U32_UPD ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psLogNotificationORLogResponsePayload->u32LogLength,    u16Length );

                while ( i <  pCustom->uMessage.psLogNotificationORLogResponsePayload->u32LogLength )
                {
                    ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [u16Length],    pCustom->uMessage.psLogNotificationORLogResponsePayload->pu8LogData [ i ],    u16Length );
                    i++;
                }

                vSL_WriteMessage ( E_SL_MSG_ASC_LOG_MSG_RESPONSE,
                                   u16Length,
                                   au8LinkTxBuffer,
                                   u8LinkQuality );
            }
            break;
#ifdef CLD_GREENPOWER
			case GREENPOWER_CLUSTER_ID:
			{
				tsGP_GreenPowerCallBackMessage *psCallBackMessage = (tsGP_GreenPowerCallBackMessage *)psEvent->uMessage.sClusterCustomMessage.pvCustomData;
				vHandleGreenPowerEvent(psCallBackMessage);
			}
			break;
#endif

            default:
                break;
        }// CUSTOM CLUSTER SWITCH STATEMENT
        }// CUSTOM CASE
        break;
        default:
           // vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "EP EVT: Invalid event type %d \r\n",psEvent->eEventType );
        break;
    }//Switch of event

}
#ifdef FULL_FUNC_DEVICE
/****************************************************************************
 *
 * NAME: APP_ZCL_cbZllUtilityCallback
 *
 * DESCRIPTION:
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void APP_ZCL_cbZllUtilityCallback ( tsZCL_CallBackEvent*    psEvent )
{
    APP_tsEvent   sEvent;

    vLog_Printf ( TRACE_ZB_CONTROLBRIDGE_TASK,LOG_DEBUG, "\nRx Util Cmd %02x",
                 ( ( tsCLD_ZllCommissionCustomDataStructure* ) psEvent->psClusterInstance->pvEndPointCustomStructPtr)->sCallBackMessage.u8CommandId );

    switch ( ( ( tsCLD_ZllCommissionCustomDataStructure* ) psEvent->psClusterInstance->pvEndPointCustomStructPtr)->sCallBackMessage.u8CommandId )
    {
        case E_CLD_UTILITY_CMD_ENDPOINT_INFO:
            sEvent.eType                        =  APP_E_EVENT_EP_INFO_MSG;
            sEvent.uEvent.sEpInfoMsg.u16SrcAddr =  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr;
            memcpy ( &sEvent.uEvent.sEpInfoMsg.sPayload,
                   ( ( tsCLD_ZllCommissionCustomDataStructure* )psEvent->psClusterInstance->pvEndPointCustomStructPtr)->sCallBackMessage.uMessage.psEndpointInfoPayload,
                    sizeof ( tsCLD_ZllUtility_EndpointInformationCommandPayload ) );
            ZQ_bQueueSend ( &APP_msgAppEvents, &sEvent );
            break;

        case E_CLD_UTILITY_CMD_GET_ENDPOINT_LIST_REQ_RSP:
            vLog_Printf ( TRACE_ZB_CONTROLBRIDGE_TASK,LOG_DEBUG, "\ngot ep list" );
            sEvent.eType                        =  APP_E_EVENT_EP_LIST_MSG;
            sEvent.uEvent.sEpListMsg.u8SrcEp    =  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint;
            sEvent.uEvent.sEpListMsg.u16SrcAddr =  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr;
            memcpy( &sEvent.uEvent.sEpListMsg.sPayload,
                    ( ( tsCLD_ZllCommissionCustomDataStructure* )psEvent->psClusterInstance->pvEndPointCustomStructPtr)->sCallBackMessage.uMessage.psGetEndpointListRspPayload,
                    sizeof ( tsCLD_ZllUtility_GetEndpointListRspCommandPayload ) );
            ZQ_bQueueSend ( &APP_msgAppEvents, &sEvent );
            break;
        case E_CLD_UTILITY_CMD_GET_GROUP_ID_REQ_RSP:
            vLog_Printf ( TRACE_ZB_CONTROLBRIDGE_TASK,LOG_DEBUG, "\ngot group list" );
            sEvent.eType                           =  APP_E_EVENT_GROUP_LIST_MSG;
            sEvent.uEvent.sGroupListMsg.u8SrcEp    =  psEvent->pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint;
            sEvent.uEvent.sGroupListMsg.u16SrcAddr =  psEvent->pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr;
            memcpy( &sEvent.uEvent.sEpListMsg.sPayload,
                    ( ( tsCLD_ZllCommissionCustomDataStructure* )psEvent->psClusterInstance->pvEndPointCustomStructPtr)->sCallBackMessage.uMessage.psGetGroupIdRspPayload,
                    sizeof ( tsCLD_ZllUtility_GetGroupIdRspCommandPayload ) );
            ZQ_bQueueSend ( &APP_msgAppEvents, &sEvent );
            break;
    }
}
#endif

/****************************************************************************
 *
 * NAME: vAPP_ZCL_DeviceSpecific_Init
 *
 * DESCRIPTION:
 * ZLL Device Specific initialization
 *
 * PARAMETER: void
 *
 * RETURNS: void
 *
 ****************************************************************************/
void vAPP_ZCL_DeviceSpecific_Init ( void )
{
    /* Initialise the strings in Basic */
    memcpy ( sControlBridge.sBasicServerCluster.au8ManufacturerName, "NXP", CLD_BAS_MANUF_NAME_SIZE );
    memcpy ( sControlBridge.sBasicServerCluster.au8ModelIdentifier, "ZLL-ControlBridge", CLD_BAS_MODEL_ID_SIZE );
    memcpy ( sControlBridge.sBasicServerCluster.au8DateCode, "20121212", CLD_BAS_DATE_SIZE );
    memcpy ( sControlBridge.sBasicServerCluster.au8SWBuildID, "2000-0001", CLD_BAS_SW_BUILD_SIZE );
}

/****************************************************************************
 *
 * NAME: eApp_ZLO_RegisterEndpoint
 *
 * DESCRIPTION:
 * Register ZLL endpoints
 *
 * PARAMETER
 * Type                                Name                    Descirption
 * tfpZCL_ZCLCallBackFunction          fptr                    Pointer to ZCL Callback function
 * tsZLL_CommissionEndpoint            psCommissionEndpoint    Pointer to Commission Endpoint
 *
 * RETURNS:
 * teZCL_Status
 *
 ****************************************************************************/
teZCL_Status eApp_ZLO_RegisterEndpoint ( tfpZCL_ZCLCallBackFunction    fptr )
{

	eZLO_RegisterControlBridgeEndPoint ( ZIGBEENODECONTROLBRIDGE_ORVIBO_ENDPOINT,
	                                                fptr,
	                                                &sControlBridge );
    return eZLO_RegisterControlBridgeEndPoint ( ZIGBEENODECONTROLBRIDGE_ZLO_ENDPOINT,
                                                fptr,
                                                &sControlBridge );
}


/****************************************************************************
 *
 * NAME: APP_u16GetAttributeActualSize
 *
 * DESCRIPTION:
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/

PUBLIC uint16 APP_u16GetAttributeActualSize ( uint32    u32Type,
                                              uint16    u16NumberOfItems )
{
    uint16    u16Size =  0;

    switch(u32Type)
    {
        case(E_ZCL_GINT8):
        case(E_ZCL_UINT8):
        case(E_ZCL_INT8):
        case(E_ZCL_ENUM8):
        case(E_ZCL_BMAP8):
        case(E_ZCL_BOOL):
        case(E_ZCL_OSTRING):
        case(E_ZCL_CSTRING):
           u16Size = sizeof(uint8);
        break;

        case(E_ZCL_LOSTRING):
        case(E_ZCL_LCSTRING):
        case(E_ZCL_STRUCT):
        case (E_ZCL_INT16):
        case (E_ZCL_UINT16):
        case (E_ZCL_ENUM16):
        case (E_ZCL_CLUSTER_ID):
        case (E_ZCL_ATTRIBUTE_ID):
           u16Size = sizeof(uint16);
        break;


        case E_ZCL_UINT24:
        case E_ZCL_UINT32:
        case E_ZCL_TOD:
        case E_ZCL_DATE:
        case E_ZCL_UTCT:
        case E_ZCL_BACNET_OID:
        case E_ZCL_INT24:
        case E_ZCL_FLOAT_SINGLE:
        case E_ZCL_BMAP32:
           u16Size = sizeof(uint32);
        break;

        case E_ZCL_UINT40:
        case E_ZCL_UINT48:
        case E_ZCL_UINT56:
        case E_ZCL_UINT64:
        case E_ZCL_IEEE_ADDR:
           u16Size = sizeof(uint64);
        break;

        default:
           u16Size = 0;
        break;
    }

    return ( u16Size * u16NumberOfItems );
}


/****************************************************************************
 *
 * NAME: APP_u16ZncWriteDataPattern
 *
 * DESCRIPTION:
 *
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC uint16 APP_u16ZncWriteDataPattern ( uint8*                    pu8Data,
                                           teZCL_ZCLAttributeType    eAttributeDataType,
                                           uint8*                    pu8Struct,
                                           uint32                    u32Size )
{
    switch ( eAttributeDataType )
    {
        /* 8 bit integer value */
        case(E_ZCL_GINT8):
        case(E_ZCL_UINT8):
        case(E_ZCL_INT8):
        case(E_ZCL_ENUM8):
        case(E_ZCL_BMAP8):
        case(E_ZCL_BOOL):
        {
            *( uint8 * ) pu8Data =  *pu8Struct++;
            break;
        }

        /* 16 bit integer value */
        case(E_ZCL_GINT16):
        case(E_ZCL_UINT16):
        case(E_ZCL_ENUM16):
        case(E_ZCL_INT16):
        case(E_ZCL_CLUSTER_ID):
        case(E_ZCL_ATTRIBUTE_ID):
        case(E_ZCL_BMAP16):
        case(E_ZCL_FLOAT_SEMI):
        {
            uint16 u16Val = *pu8Struct++;
            u16Val |= (*pu8Struct++) << 8;
            // Unsafe due to alignment issues - replaced by memcpy
            //*(uint16 *)(pu8Struct) = u16Val;
            memcpy(pu8Data, &u16Val, sizeof(uint16));
            break;
        }
        /* 32 bit integer value */
        case(E_ZCL_UINT32):
        case(E_ZCL_INT32):
        case(E_ZCL_GINT32):
        case(E_ZCL_BMAP32):
        case(E_ZCL_UTCT):
        case(E_ZCL_TOD):
        case(E_ZCL_DATE):
        case(E_ZCL_FLOAT_SINGLE):
        {
            uint32 u32Val = *pu8Struct++;
            u32Val |= (*pu8Struct++) << 8;
            u32Val |= (*pu8Struct++) << 16;
            u32Val |= (*pu8Struct++) << 24;
            memcpy(pu8Data, &u32Val, sizeof(uint32));
            break;
        }
        /* 64 bit integer value */
        case(E_ZCL_GINT64):
        case(E_ZCL_UINT64):
        case(E_ZCL_INT64):
        case(E_ZCL_BMAP64):
        case(E_ZCL_IEEE_ADDR):
        case(E_ZCL_FLOAT_DOUBLE):
        {
            uint64 u64Val = (uint32)*pu8Struct++;
            u64Val |= (uint64)(*pu8Struct++) << 8;
            u64Val |= (uint64)(*pu8Struct++) << 16;
            u64Val |= (uint64)(*pu8Struct++) << 24;
            u64Val |= (uint64)(*pu8Struct++) << 32;
            u64Val |= (uint64)(*pu8Struct++) << 40;
            u64Val |= (uint64)(*pu8Struct++) << 48;
            u64Val |= (uint64)(*pu8Struct++) << 56;
            memcpy(pu8Data, &u64Val, sizeof(uint64));
            break;
        }

        /* 24-bit stored as 32 bit integer value */
        case(E_ZCL_GINT24):
        case(E_ZCL_UINT24):
        case(E_ZCL_INT24):
        case(E_ZCL_BMAP24):
        {
            uint32 u32Val = *pu8Struct++;
            u32Val |= (*pu8Struct++) << 8;
            u32Val |= (*pu8Struct)   << 16;
            // account for signed-ness
            if(eAttributeDataType == E_ZCL_INT24)
            {
                // sign extend if top bit set
                if(*pu8Struct &0x80)
                {
                    u32Val |= (0xff << 24);
                }
            }
            memcpy(pu8Data, &u32Val, sizeof(uint32));
            // increment ptr to keep size calculation correct
            pu8Struct++;
            break;
        }

        /* 40-bit stored as 64 bit integer value */
        case(E_ZCL_GINT40):
        case(E_ZCL_UINT40):
        case(E_ZCL_INT40):
        case(E_ZCL_BMAP40):
        {
            uint64 u64Val = (uint32)*pu8Struct++;
            u64Val |= (uint64)(*pu8Struct++) << 8;
            u64Val |= (uint64)(*pu8Struct++) << 16;
            u64Val |= (uint64)(*pu8Struct++) << 24;
            u64Val |= (uint64)(*pu8Struct) << 32;
            // account for signed-ness
            if(eAttributeDataType == E_ZCL_INT40)
            {
                // sign extend if top bit set
                if(*pu8Struct &0x80)
                {
                    u64Val |= ((uint64)(0xffffff) << 40);
                }
            }
            memcpy(pu8Data, &u64Val, sizeof(uint64));
            // increment ptr to keep size calculation correct
            pu8Struct++;
            break;
        }

        /* 48-bit stored as 64 bit integer value */
        case(E_ZCL_GINT48):
        case(E_ZCL_UINT48):
        case(E_ZCL_INT48):
        case(E_ZCL_BMAP48):
        {
            uint64 u64Val = (uint32)*pu8Struct++;
            u64Val |= (uint64)(*pu8Struct++) << 8;
            u64Val |= (uint64)(*pu8Struct++) << 16;
            u64Val |= (uint64)(*pu8Struct++) << 24;
            u64Val |= (uint64)(*pu8Struct++) << 32;
            u64Val |= (uint64)(*pu8Struct) << 40;
            // account for signed-ness
            if(eAttributeDataType == E_ZCL_INT48)
            {
                // sign extend if top bit set
                if(*pu8Struct &0x80)
                {
                    u64Val |= ((uint64)(0xffff) << 48);
                }
            }
            memcpy(pu8Data, &u64Val, sizeof(uint64));
            // increment ptr to keep size calculation correct
            pu8Struct++;
            break;
        }

        /* 56-bit stored as 64 bit integer value */
        case(E_ZCL_GINT56):
        case(E_ZCL_UINT56):
        case(E_ZCL_INT56):
        case(E_ZCL_BMAP56):
        {
            uint64 u64Val = (uint32)*pu8Struct++;
            u64Val |= (uint64)(*pu8Struct++) << 8;
            u64Val |= (uint64)(*pu8Struct++) << 16;
            u64Val |= (uint64)(*pu8Struct++) << 24;
            u64Val |= (uint64)(*pu8Struct++) << 32;
            u64Val |= (uint64)(*pu8Struct++) << 40;
            u64Val |= (uint64)(*pu8Struct) << 48;
            // account for signed-ness
            if(eAttributeDataType == E_ZCL_INT56)
            {
                // sign extend if top bit set
                if(*pu8Data &0x80)
                {
                    u64Val |= ((uint64)(0xff) << 56);
                }
            }
            memcpy(pu8Data, &u64Val, sizeof(uint64));
            // increment ptr to keep size calculation correct
            pu8Struct++;
            break;
        }
        case(E_ZCL_KEY_128):
            memcpy(pu8Data, pu8Struct, E_ZCL_KEY_128_SIZE);
            // increment ptr to keep size calculation correct
            pu8Struct += E_ZCL_KEY_128_SIZE;
            break;
        case (E_ZCL_NULL):
        // unrecognised
        default:
        {
            return 0;
        }
    }

    return (uint16)( u32Size);
}


/****************************************************************************
 *
 * NAME: APP_vBdbCallback
 *
 * DESCRIPTION:
 * Callbak from the BDB
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void APP_vBdbCallback(BDB_tsBdbEvent *psBdbEvent)
{
    uint8 au8Buffer[20];

    vLog_Printf ( TRACE_ZCL,LOG_DEBUG, "Got bdb event %d\n", psBdbEvent->eEventType);

    switch(psBdbEvent->eEventType)
    {
        case BDB_EVENT_NONE:
            break;
        case BDB_EVENT_ZPSAF:                // Use with BDB_tsZpsAfEvent
            if ( psBdbEvent->uEventData.sZpsAfEvent.u8EndPoint ==  0 )
            {
                APP_vHandleStackEvents ( &psBdbEvent->uEventData.sZpsAfEvent.sStackEvent );
            }
            else
            {
                APP_vHandleZclEvents ( &psBdbEvent->uEventData.sZpsAfEvent.sStackEvent );
            }
            break;

        case BDB_EVENT_INIT_SUCCESS:
            break;

#ifdef FULL_FUNC_DEVICE
        case BDB_EVENT_NWK_STEERING_SUCCESS:
            sZllState.eState     =  NOT_FACTORY_NEW;
            sZllState.eNodeState =  E_RUNNING;
            PDM_eSaveRecordData ( PDM_ID_APP_ZLL_CMSSION,
                                  &sZllState,
                                  sizeof ( tsZllState ) );
            break;

        case BDB_EVENT_NO_NETWORK:
            if( sZllState.eState == FACTORY_NEW &&
                sBDB.sAttrib.u8bdbCommissioningMode & BDB_COMMISSIONING_MODE_NWK_FORMATION)
            {
                BDB_eNfStartNwkFormation();
            }
            break;
#endif

        case BDB_EVENT_NWK_FORMATION_SUCCESS:
            sZllState.eState     =  NOT_FACTORY_NEW;
            sZllState.eNodeState =  E_RUNNING;
            PDM_eSaveRecordData ( PDM_ID_APP_ZLL_CMSSION,
                                  &sZllState,
                                  sizeof ( tsZllState ) );
            APP_vSendJoinedFormEventToHost(1,au8Buffer);
            break;

        case BDB_EVENT_NWK_FORMATION_FAILURE:
            break;

        default:
            break;
    }
}

PUBLIC uint16 App_u16BufferReadNBO ( uint8         *pu8Struct,
                                     const char    *szFormat,
                                     void          *pvData)
{
    uint8 *pu8Start = (uint8*)pvData;
    uint32 u32Offset = 0;

    if(!pu8Struct || !szFormat || !pvData)
    {
        return 0;
    }

    for(; *szFormat != '\0'; szFormat++)
    {
        if(*szFormat == 'b') {
            pu8Struct[u32Offset++] = *(uint8*)pvData++;
        } else if (*szFormat == 'h') {
            uint16 u16Val = *( uint8* )pvData++ << 8;
            u16Val |= *( uint8* )pvData;

            /* align to half-word boundary */
            u32Offset = ALIGN( sizeof(uint16), u32Offset );

            memcpy(pu8Struct + u32Offset, &u16Val, sizeof(uint16));

            u32Offset += sizeof(uint16);
        } else if (*szFormat == 'w') {
            uint32 u32Val = *( uint8* )pvData << 24;
            u32Val |= *( uint8* )pvData << 16;
            u32Val |= *( uint8* )pvData << 8;
            u32Val |= *( uint8* )pvData;

            /* align to word (32 bit) boundary */
            u32Offset = ALIGN(sizeof(uint32), u32Offset);

            memcpy(pu8Struct + u32Offset, &u32Val, sizeof(uint32));

            u32Offset += sizeof(uint32);
        } else if (*szFormat == 'l') {
        	uint64 u64Val;
            u64Val =  (uint64) *( uint8* )pvData << 56;
            u64Val |= (uint64) *( uint8* )pvData << 48;
            u64Val |= (uint64) *( uint8* )pvData << 40;
            u64Val |= (uint64) *( uint8* )pvData << 32;
            u64Val |= (uint64) *( uint8* )pvData << 24;
            u64Val |= (uint64) *( uint8* )pvData << 16;
            u64Val |= (uint64) *( uint8* )pvData << 8;
            u64Val |= (uint64) *( uint8* )pvData ;


            /*
             *  align to long long word (64 bit) boundary
             *  but relative to structure start
             */
            u32Offset = ALIGN(sizeof(uint64), u32Offset);

            memcpy(pu8Struct + u32Offset, &u64Val, sizeof(uint64));

            u32Offset += sizeof(uint64);

        } else if (*szFormat == 'a') {
            uint8 u8Size = *++szFormat;
            unsigned int i;

            for (i = 0; i < u8Size; i++) {
                *(pu8Struct + u32Offset) = *( uint8* )pvData;
                u32Offset++;
            }
        } else if (*szFormat == 'p') {
            pvData += *++szFormat;
        }
    }

    return (uint16)((uint8*)pvData - pu8Start);
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
