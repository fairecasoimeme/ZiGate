/*****************************************************************************
 *
 * MODULE:             Smart Energy
 *
 * COMPONENT:          zcl_event.c
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:       ZCL event handler functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Branches/Zigbee_3_0/Source/zcl_event.c $
 *
 * $Revision: 71388 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-07-29 11:23:38 +0530 (Wed, 29 Jul 2015) $
 *
 * $Id: zcl_event.c 71388 2015-07-29 05:53:38Z nxp57621 $
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
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <string.h>

#include "zcl.h"
#include "zcl_common.h"
#include "zcl_internal.h"
#include "zcl_customcommand.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"
#include "zps_nwk_pub.h"
#include "dbg.h"

#include "zcl_options.h"
#include "app_common.h"

#include "Log.h"

#ifdef CLD_GREENPOWER
#include "GreenPower.h"
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE void vZCL_HandleDataIndication(ZPS_tsAfEvent *pZPSevent);
PRIVATE void vZCL_ZigbeeEventHandler(ZPS_tsAfEvent *pZPSevent);
PRIVATE void vZCL_HandleDataAcknowledgement(ZPS_tsAfEvent *pZPSevent);
PRIVATE void vZCL_HandleDefaultResponse(ZPS_tsAfEvent *pZPSevent);
PRIVATE void vSetAddressUnion(
                ZPS_tsAfEvent              *pZPSevent,
                ZPS_tuAddress              *puAddress,
                bool_t                      bSource);
#if 1
PRIVATE void vZCL_HandleInterPanIndication(ZPS_tsAfEvent *pZPSevent);
#endif
PRIVATE bool_t bZCL_OverrideHandlingEntireProfileCmd(uint16 u16ClusterId);
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
PRIVATE bool_t (*prfnbZCLOverrideHandlingEntireProfileCommand)(uint16)  = NULL;
/****************************************************************************/
/***        Public Functions                                              ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       vZCL_EventHandler
 **
 ** DESCRIPTION:
 ** handles ZCL stack events
 **
 ** PARAMETERS:               Name                    Usage
 ** tsZCL_CallBackEvent      *psZCLcallBackEvent      ZCL event structure
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/
PUBLIC void vZCL_EventHandler(tsZCL_CallBackEvent *psZCLcallBackEvent)
{

    if(psZCLcallBackEvent==NULL)
    {
        return;
    }

    switch(psZCLcallBackEvent->eEventType)
    {
        case(E_ZCL_CBET_TIMER_MS):
        case(E_ZCL_CBET_TIMER):
        {
            vZCL_TimerSchedulerUpdate(psZCLcallBackEvent);
            break;
        }
        break;

        default:
        {
        	vLog_Printf(TRACE_DEBUG,LOG_DEBUG,"\n\n----------------Event-------------------");

            vZCL_ZigbeeEventHandler(psZCLcallBackEvent->pZPSevent);
            break;
        }
    }

}

/****************************************************************************
 **
 ** NAME:       eZCL_SetReceiveEventAddressStructure
 **
 ** DESCRIPTION:
 ** Stores the receive events address details
 **
 ** PARAMETERS:                 Name                      Usage
 ** ZPS_tsAfEvent               *pZPSevent                Zigbee stack event structure
 ** tsZCL_ReceiveEventAddress   *psReceiveEventAddress    Address structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC teZCL_Status eZCL_SetReceiveEventAddressStructure(
                 ZPS_tsAfEvent              *pZPSevent,
                 tsZCL_ReceiveEventAddress  *psReceiveEventAddress)
{
    if((pZPSevent==NULL) || (psReceiveEventAddress==NULL))
    {
        return(E_ZCL_FAIL);
    }

    // initial clear - allows memcmp compares to work reliably
    memset(psReceiveEventAddress, 0, sizeof(tsZCL_ReceiveEventAddress));

    // update Server address details
    psReceiveEventAddress->bInitialised = TRUE;

    psReceiveEventAddress->u8DstAddrMode = pZPSevent->uEvent.sApsDataIndEvent.u8DstAddrMode;
    vSetAddressUnion(pZPSevent, &psReceiveEventAddress->uDstAddress, FALSE);
    psReceiveEventAddress->u8DstEndpoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;

    psReceiveEventAddress->u8SrcAddrMode = pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode;
    vSetAddressUnion(pZPSevent, &psReceiveEventAddress->uSrcAddress, TRUE);
    psReceiveEventAddress->u8SrcEndpoint = pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint;

    return(E_ZCL_SUCCESS);
}

/****************************************************************************
 **
 ** NAME:       vSetAddressUnion
 **
 ** DESCRIPTION:
 ** sets address, based on Mode
 **
 ** PARAMETERS:                 Name                      Usage
 ** ZPS_tsAfEvent               *pZPSevent                Zigbee stack event structure
 ** tsZCL_ReceiveEventAddress   *psReceiveEventAddress    Address structure
 ** bool_t                       bSource                  Source or Dest data
 **
 ** RETURN:
 ** Nothing
 **
 ****************************************************************************/

PRIVATE void vSetAddressUnion(
                ZPS_tsAfEvent              *pZPSevent,
                ZPS_tuAddress              *puAddress,
                bool_t                      bSource)
{
    ZPS_teAplApsdeAddressMode   eAplApsdeAddressMode;
    ZPS_tuAddress              *puEventAddress;

    eAplApsdeAddressMode = pZPSevent->uEvent.sApsDataIndEvent.u8DstAddrMode;
    puEventAddress = &pZPSevent->uEvent.sApsDataIndEvent.uDstAddress;

    if(bSource==TRUE)
    {
        eAplApsdeAddressMode = pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode;
        puEventAddress = &pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress;
    }

    switch(eAplApsdeAddressMode)
    {
        case(ZPS_E_ADDR_MODE_GROUP):
        case(ZPS_E_ADDR_MODE_SHORT):
        {
            puAddress->u16Addr = puEventAddress->u16Addr;
            break;
        }

        case(ZPS_E_ADDR_MODE_IEEE):
        {
            puAddress->u64Addr = puEventAddress->u64Addr;
            break;
        }
        case(ZPS_E_ADDR_MODE_BOUND):
        default:
        {
            // nothing
            break;
        }
    }
}

/****************************************************************************
 **
 ** NAME:       eZCL_BuildClientTransmitAddressStructure
 **
 ** DESCRIPTION:
 ** Build address structure using the psReceiveEventAddress structure
 **
 ** PARAMETERS:               Name                    Usage
 ** ZPS_tsAfEvent            *pZPSevent               Zigbee stack event structure
 ** tsZCL_ReceiveEventAddress  *psReceiveEventAddress Address Structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC teZCL_Status eZCL_BuildClientTransmitAddressStructure(
                        tsZCL_Address              *psZCL_Address,
                        tsZCL_ReceiveEventAddress  *psReceiveEventAddress)
{

    if((psZCL_Address==NULL) || (psReceiveEventAddress==NULL) || (psReceiveEventAddress->bInitialised==FALSE))
    {
        return(E_ZCL_FAIL);
    }

    psZCL_Address->eAddressMode = psReceiveEventAddress->u8SrcAddrMode;

    switch(psZCL_Address->eAddressMode)
    {
        case(E_ZCL_AM_SHORT):
        case(E_ZCL_AM_SHORT_NO_ACK):
        {
            psZCL_Address->uAddress.u16DestinationAddress = psReceiveEventAddress->uSrcAddress.u16Addr;
            break;
        }

        // not supported yet
        case(E_ZCL_AM_IEEE):
        case(E_ZCL_AM_BOUND):
        case(E_ZCL_AM_GROUP):
        case(E_ZCL_AM_BROADCAST):
        case(E_ZCL_AM_IEEE_NO_ACK):
        case(E_ZCL_AM_BOUND_NO_ACK):
        default:
        {
        	vLog_Printf ( TRACE_DEBUG,LOG_DEBUG, " psZCL_Address->eAddressMode : %d\n", psZCL_Address->eAddressMode);
            return(E_ZCL_FAIL);
            break;
        }
    }

    return(E_ZCL_SUCCESS);
}
/****************************************************************************
 **
 ** NAME:       vZCL_PassEventToUser
 **
 ** DESCRIPTION:
 ** Pass an unhandled ZPS event to the user callback.  Use the EP callback if it
 ** can be found, otherwise use the unhandled callback.
 **
 ** PARAMETERS:               Name                    Usage
 ** tsZCL_CallBackEvent       *psZCL_CallBackEvent    ZCL event that has the end point, event type and pZpsEvent filled in by caller
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/
void vZCL_PassEventToUser(tsZCL_CallBackEvent *psZCL_CallBackEvent)
{
    tsZCL_EndPointDefinition *psZCL_EndPointDefinition;

    // Fill in unused fields
    psZCL_CallBackEvent->u8TransactionSequenceNumber = 0;
    psZCL_CallBackEvent->psClusterInstance = NULL;

    // find and post to endpoint
    if(eZCL_SearchForEPentry(psZCL_CallBackEvent->u8EndPoint, &psZCL_EndPointDefinition) == E_ZCL_SUCCESS)
    {
        psZCL_EndPointDefinition->pCallBackFunctions(psZCL_CallBackEvent);
    }
    else
    {
        psZCL_Common->pfZCLinternalCallBackFunction(psZCL_CallBackEvent);
    }
}

/****************************************************************************
 **
 ** NAME:       eZCL_ZigbeeEventHandler
 **
 ** DESCRIPTION:
 ** handles Zigbee stack events
 **
 ** PARAMETERS:               Name                    Usage
 ** ZPS_tsAfEvent              *pZPSevent               Zigbee stack event structure
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/
PRIVATE void vZCL_ZigbeeEventHandler(ZPS_tsAfEvent *pZPSevent)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent;

    if(pZPSevent==NULL)
    {
        return;
    }

    // fill in default parts of callback event
    sZCL_CallBackEvent.pZPSevent = pZPSevent;

    vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n pZPSevent->eType: %d\n",pZPSevent->eType);

    // parse event structure
    switch(pZPSevent->eType)
    {
    case(ZPS_EVENT_APS_DATA_INDICATION):
        {
            if(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint != 0 &&
               pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint != 0 )
            {
#ifdef CLD_GREENPOWER
                if(ZCL_GP_PROXY_ENDPOINT_ID == pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint)
                {
                    pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint = psZCL_Common->u8GreenPowerMappedEpId;
                }

                if(psZCL_Common->u8GreenPowerMappedEpId != pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint &&
                        ZCL_GP_PROXY_ENDPOINT_ID == pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint)
                {
                    tsZCL_ClusterInstance       *psClusterInstance;
#ifndef PC_PLATFORM_BUILD
                    ZPS_tsAplAfSimpleDescriptor sAplAfSimpleDescriptor;

                    /* As this loopback packet, change profile id to destination ep's proifle id */
                    if(ZPS_eAplAfGetSimpleDescriptor(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                            &sAplAfSimpleDescriptor) == E_ZCL_SUCCESS)
                    {
                        pZPSevent->uEvent.sApsDataIndEvent.u16ProfileId = sAplAfSimpleDescriptor.u16ApplicationProfileId;
                    }
#endif

                    /* Change Cluster security */
                    if(eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                                                                    pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId,
                                                                    TRUE,
                                                                    &psClusterInstance) == E_ZCL_SUCCESS)
                    {
                        /* check cluster security */
                        switch(psClusterInstance->psClusterDefinition->u8ClusterControlFlags & SEND_SECURITY_MASK)
                        {
                        case E_ZCL_SECURITY_NETWORK:
                            pZPSevent->uEvent.sApsDataIndEvent.eSecurityStatus = ZPS_APL_APS_E_SECURED_NWK_KEY;
                            break;

                        case E_ZCL_SECURITY_APPLINK:
                            pZPSevent->uEvent.sApsDataIndEvent.eSecurityStatus = ZPS_APL_APS_E_SECURED_LINK_KEY;
                            break;

                        default:
                            break;
                        }
                    }

                }
#endif
                // handle ZCL message if success.  If error, PDU is not valid so pass up to user
                vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n pZPSevent->uEvent.sApsDataIndEvent.eStatus: %d\n",pZPSevent->uEvent.sApsDataIndEvent.eStatus);

                if (pZPSevent->uEvent.sApsDataIndEvent.eStatus == ZPS_E_SUCCESS)
                {
                    vZCL_HandleDataIndication(pZPSevent);
                }
                else
                {
                    sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
                    sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_ZRECEIVE_FAIL;
                    psZCL_Common->eLastZpsError = pZPSevent->uEvent.sApsDataIndEvent.eStatus;
                    sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
                    vZCL_PassEventToUser(&sZCL_CallBackEvent);
                }
            }
            else
            {
                sZCL_CallBackEvent.eEventType = E_ZCL_CBET_UNHANDLED_EVENT;
                sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
                vZCL_PassEventToUser(&sZCL_CallBackEvent);

            }
            break;
        }
#ifdef CLD_GREENPOWER
    case(ZPS_EVENT_APS_ZGP_DATA_INDICATION):
        {
            vZCL_HandleZgpDataIndication(pZPSevent, psZCL_Common->u8GreenPowerMappedEpId);
            break;
        }
    case (ZPS_EVENT_APS_ZGP_DATA_CONFIRM):
    {
        vZCL_HandleZgpDataConfirm(pZPSevent, psZCL_Common->u8GreenPowerMappedEpId);
        break;
    }
#endif
    case(ZPS_EVENT_APS_DATA_CONFIRM):
        {
            // fill in callback event
            sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataConfirmEvent.u8SrcEndpoint;
            sZCL_CallBackEvent.eEventType = E_ZCL_CBET_UNHANDLED_EVENT;
            vZCL_PassEventToUser(&sZCL_CallBackEvent);
            break;
        }

        // place holder code this structure needs expanding to give Cluster info
    case(ZPS_EVENT_APS_DATA_ACK):
        {
            if(pZPSevent->uEvent.sApsDataAckEvent.u8DstEndpoint != 0 &&
               pZPSevent->uEvent.sApsDataAckEvent.u8SrcEndpoint != 0 )
            {
                // handle ACK message
                vZCL_HandleDataAcknowledgement(pZPSevent);
            }
            else
            {
                sZCL_CallBackEvent.eEventType = E_ZCL_CBET_UNHANDLED_EVENT;
                vZCL_PassEventToUser(&sZCL_CallBackEvent);
            }
            break;
        }

  // Interpan not in the Jan 2011 Certified ZB Pro stack release - will be in the ROM release.
    case ZPS_EVENT_APS_INTERPAN_DATA_INDICATION:
        // handle ZCL message if success.  If error, PDU is not valid so pass up to user
        if (pZPSevent->uEvent.sApsInterPanDataIndEvent.eStatus == ZPS_E_SUCCESS)
        {
            vZCL_HandleInterPanIndication(pZPSevent);
        }
        else
        {
            //sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
            //sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_ZRECEIVE_FAIL;
            //psZCL_Common->eLastZpsError = pZPSevent->uEvent.sApsDataIndEvent.eStatus;
            //sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
            //vZCL_PassEventToUser(&sZCL_CallBackEvent);
            // TODO Error handling
            //DBG_vPrintf(TRUE, "ZCL Ip oops %d\n", pZPSevent->uEvent.sApsInterPanDataIndEvent.eStatus);
        }
        break;
    case ZPS_EVENT_APS_INTERPAN_DATA_CONFIRM:

        break;

           // shouldn't get these, pass them up
    case(ZPS_EVENT_NONE):
    case(ZPS_EVENT_NWK_JOINED_AS_ROUTER):
    case(ZPS_EVENT_NWK_JOINED_AS_ENDDEVICE):
    case(ZPS_EVENT_NWK_STARTED):
    case(ZPS_EVENT_NWK_FAILED_TO_JOIN):
    case(ZPS_EVENT_NWK_NEW_NODE_HAS_JOINED):
    case(ZPS_EVENT_NWK_DISCOVERY_COMPLETE):
    case(ZPS_EVENT_NWK_LEAVE_INDICATION):
    case(ZPS_EVENT_NWK_LEAVE_CONFIRM):
    case(ZPS_EVENT_NWK_STATUS_INDICATION):
    case(ZPS_EVENT_NWK_ROUTE_DISCOVERY_CONFIRM):
    case(ZPS_EVENT_NWK_POLL_CONFIRM):
    case(ZPS_EVENT_ERROR):
    default:
        {
            // fill in callback event - welcome to hell
            sZCL_CallBackEvent.u8EndPoint = -1;
            sZCL_CallBackEvent.eEventType = E_ZCL_CBET_UNHANDLED_EVENT;
            vZCL_PassEventToUser(&sZCL_CallBackEvent);
            break;
        }
    }

}


/****************************************************************************
 **
 ** NAME:       vZCL_HandleDataIndication
 **
 ** DESCRIPTION:
 ** Valididates the Data Indication Event
 **
 ** PARAMETERS:               Name                    Usage
 ** ZPS_tsAfEvent              *pZPSevent               Zigbee stack event structure
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/
PRIVATE void vZCL_HandleDataIndication(ZPS_tsAfEvent *pZPSevent)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent;

    tsZCL_EndPointDefinition    *psZCL_EndPointDefinition;
    tsZCL_ClusterInstance       *psClusterInstance;

    uint16 u16inputOffset;

    tsZCL_HeaderParams sZCL_HeaderParams;

    uint8 u8Error = 0;
    teZCL_Status eCallbackReturn;
    teZCL_ZCLSendSecurity eClusterSecurityLevel;
    teZCL_ZCLSendSecurity eStackSecurityLevel;



    // fill in default parts of callback event
    sZCL_CallBackEvent.pZPSevent = pZPSevent;

    if(pZPSevent == NULL)
    {
        return;
    }
    // further error checking can only be done once we have interrogated the ZCL payload
    u16inputOffset = u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                                              &sZCL_HeaderParams);


    /* lpsw 2721 - Error return codes for unsupported manufacturer specific commands
     */
    vLog_Printf(TRACE_DEBUG,LOG_DEBUG,"\n--avant eZCL_SearchForEPentryAndCheckManufacturerId\n");
    vLog_Printf(TRACE_DEBUG,LOG_DEBUG,"\n-- sZCL_HeaderParams : \n bManufacturerSpecific : %d\nu16ManufacturerCode : %d \n",sZCL_HeaderParams.bManufacturerSpecific,sZCL_HeaderParams.u16ManufacturerCode);
    if (eZCL_SearchForEPentryAndCheckManufacturerId(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint, sZCL_HeaderParams.bManufacturerSpecific, sZCL_HeaderParams.u16ManufacturerCode, &psZCL_EndPointDefinition) != E_ZCL_SUCCESS)
    {

        if ( sZCL_HeaderParams.eFrameType == eFRAME_TYPE_COMMAND_IS_SPECIFIC_TO_A_CLUSTER ) 
        {
            u8Error = E_ZCL_CMDS_UNSUP_MANUF_CLUSTER_COMMAND;
            vLog_Printf(TRACE_DEBUG,LOG_DEBUG,"\nE_ZCL_CMDS_UNSUP_MANUF_CLUSTER_COMMAND\n");
        } 
        else 
        {
        	// Xiaomi Door button press trigger this code with Manufacturer Code 0x115F for General Command: 0x0A - Report Attributes
            u8Error = E_ZCL_CMDS_UNSUP_MANUF_GENERAL_COMMAND;
            vLog_Printf(TRACE_DEBUG,LOG_DEBUG,"\E_ZCL_CMDS_UNSUP_MANUF_GENERAL_COMMAND\n");
        }
        /*Recheck to manipulate the error so that the command is passed upto the handler when teh manufacturer code can be 0xFFFF as wild card*/
        if(  sZCL_HeaderParams.bManufacturerSpecific && 
            (  sZCL_HeaderParams.u16ManufacturerCode == 0xFFFF )&& 
            (   (sZCL_HeaderParams.u8CommandIdentifier == E_ZCL_DISCOVER_COMMANDS_RECEIVED) || 
                (sZCL_HeaderParams.u8CommandIdentifier == E_ZCL_DISCOVER_COMMANDS_GENERATED)    )
           )
        {
            u8Error=0;

        }
        /* Verrue pour passer le message Xiaomi 0x115F */
	    /* Avec cette verrue la ZiGate n'envoie pas de réponse à l'emetteur */

	    if(  sZCL_HeaderParams.bManufacturerSpecific && ((sZCL_HeaderParams.u16ManufacturerCode == 0x115F) || (sZCL_HeaderParams.u16ManufacturerCode == 0x100B) || (sZCL_HeaderParams.u16ManufacturerCode == 0x1234)  || (sZCL_HeaderParams.u16ManufacturerCode == 0x1021)))
	    {
		  vLog_Printf(1,LOG_DEBUG, "BEN: %s - %d - %s: Verrue pour passer le Attribute Report proprietaire Xiaomi 0x115F.\n", __FILE__, __LINE__, __func__);
		   u8Error=0;
	    }

	    //FRED -- Specifique à orvibo
	    if ((pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint ==0x0a) && ( sZCL_HeaderParams.eFrameType == eFRAME_TYPE_COMMAND_IS_SPECIFIC_TO_A_CLUSTER ) )
	    {
	    	u8Error=0;
	    }


    } else if (
        #ifdef ZCL_ALLOW_WILD_CARD_PROFILE
            (pZPSevent->uEvent.sApsDataIndEvent.u16ProfileId != 0xFFFF) &&
        #endif
        (psZCL_EndPointDefinition->u16ProfileEnum != pZPSevent->uEvent.sApsDataIndEvent.u16ProfileId)) {
        // To pass BDB test; FB-PIM-TC-01, filter out message with non matching profileID; don't sent default response.
        // u8Error =  E_ZCL_CMDS_SOFTWARE_FAILURE;
        PDUM_eAPduFreeAPduInstance(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);
        return;
    }


    
    if (u8Error != 0)
    {
        // send response if possible/required
        // Trac 6 - don't send default response from a default response.
        if (sZCL_HeaderParams.u8CommandIdentifier != E_ZCL_DEFAULT_RESPONSE ||
            sZCL_HeaderParams.eFrameType != eFRAME_TYPE_COMMAND_ACTS_ACCROSS_ENTIRE_PROFILE)
        {
            sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
            sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_EP_UNKNOWN;
            sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
            vZCL_PassEventToUser(&sZCL_CallBackEvent);
            eZCL_SendDefaultResponse(pZPSevent, u8Error);
        }
        // free buffer and return
        PDUM_eAPduFreeAPduInstance(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);
        return;
    }
    vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n informations : \n");
    vLog_Printf(TRACE_DEBUG,LOG_DEBUG, " DstEndpoint : %d\n", pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint);
    vLog_Printf(TRACE_DEBUG,LOG_DEBUG, " u16ClusterId : %d\n",pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId);
    vLog_Printf(TRACE_DEBUG,LOG_DEBUG, " bDirection : %d\n",!sZCL_HeaderParams.bDirection);

    // check the command is suitable for the endpoint - cluster, manufac Id, direction
    eCallbackReturn = eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                                                    pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId,
                                                    !sZCL_HeaderParams.bDirection,
                                                    &psClusterInstance);
    vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n eCallbackReturn 1 : %d\n",eCallbackReturn);
    // Trac 18: Key establishment cluster on trust centre may be acting as a client as another device joins
    // Allow the command to reach the KEC, where it can return a no resources terminate
    if ((eCallbackReturn != E_ZCL_SUCCESS )&&
            (pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId ==
                SE_CLUSTER_ID_KEY_ESTABLISHMENT))
    {

        eCallbackReturn = eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,
                                                    pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId,
                                                    sZCL_HeaderParams.bDirection,
                                                    &psClusterInstance);
        vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n eCallbackReturn 2 : %d\n",eCallbackReturn);

    }

    // Check the command was sent with sufficient security - assume it was if no cluster to check against
    // http://trac/Mars/ticket/60 ZCL response when cluster does not exist (Secure Electrans at Trac Sept 2010)
    eClusterSecurityLevel = E_ZCL_SECURITY_NETWORK;
    vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n psClusterInstance: %d\n",psClusterInstance);
    if (psClusterInstance)
    {
        eClusterSecurityLevel = (psClusterInstance->psClusterDefinition->u8ClusterControlFlags & SEND_SECURITY_MASK);
    }
    else
    {
    	vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n Check the cluster for the opposite direction (mars 60)\n");
        // Check the cluster for the opposite direction (mars 60)
        tsZCL_ClusterInstance       *psSecurityClusterInstance;
        if (eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                                                    pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId,
                                                    sZCL_HeaderParams.bDirection,
                                                    &psSecurityClusterInstance)
                                                    == E_ZCL_SUCCESS)
        {
            eClusterSecurityLevel = (psSecurityClusterInstance->psClusterDefinition->u8ClusterControlFlags & SEND_SECURITY_MASK);
        }
    }
    /* this is precautionary check, if cluster security level is up to E_ZCL_SECURITY_TEMP_APPLINK
     * and due to some reason it is not return back then forcefully take it down */
    if(E_ZCL_SECURITY_TEMP_APPLINK == eClusterSecurityLevel)
    {
        eClusterSecurityLevel = E_ZCL_SECURITY_NETWORK;
    }
    // Force the level down if the app wants to
    if (psZCL_Common->eSecuritySupported < eClusterSecurityLevel)
        eClusterSecurityLevel = psZCL_Common->eSecuritySupported;

    // Stack security is a bit mask - convert to ZCL enum.
    switch (pZPSevent->uEvent.sApsDataIndEvent.eSecurityStatus)
    {
    case ZPS_APL_APS_E_SECURED_LINK_KEY:
        eStackSecurityLevel = E_ZCL_SECURITY_APPLINK;
      break;
    case ZPS_APL_APS_E_SECURED_NWK_KEY:
        eStackSecurityLevel = E_ZCL_SECURITY_NETWORK;
        break;
    case ZPS_APL_APS_E_UNSECURED: // < RAJOUT FRED gestion des pluzzy (unsecure)
       	eStackSecurityLevel = E_ZCL_SECURITY_NETWORK;


       	break;
#ifdef CLD_GREENPOWER
#ifdef GP_DISABLE_SECURITY_FOR_CERTIFICATION
    case ZPS_APL_APS_E_UNSECURED:
        eStackSecurityLevel = E_ZCL_SECURITY_NETWORK;
        break;
#endif
#endif
    default:
        // free buffer and return
        // DBG_vPrintf(TRUE, "ZCL DROP NO SEC\n");
        PDUM_eAPduFreeAPduInstance(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);
        return;
        break;
    }

    // Are we the trust centre?
    /* fixes lpsw2737  Msg meant for the TRust ventre if Unicast (addr mode == 2, short)
     * and u16Addr is 0x0000
     *
     */
    if ( (pZPSevent->uEvent.sApsDataIndEvent.u8DstAddrMode == ZPS_E_ADDR_MODE_SHORT ) &&
          (pZPSevent->uEvent.sApsDataIndEvent.uDstAddress.u16Addr == 0))
    {
#ifndef PC_PLATFORM_BUILD
        // If we are the trust centre, check the device sending the message has completed KEC with us.
        uint64 u64RemoteIeeeAddress;
        uint8 u8DevicePermissions;
        uint8 u8Status;

        u64RemoteIeeeAddress = ZPS_u64NwkNibFindExtAddr(ZPS_pvNwkGetHandle(), pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr);
        u8Status = ZPS_bAplZdoTrustCenterGetDevicePermissions(u64RemoteIeeeAddress, &u8DevicePermissions);
        // If status errror - not in table so assume full access allowed, e.g. when working with HA profile and APS security.
        if ((u8Status == ZPS_E_SUCCESS )&&( u8DevicePermissions == ZPS_DEVICE_PERMISSIONS_DATA_REQUEST_DISALLOWED))
        {
            eStackSecurityLevel = E_ZCL_SECURITY_NETWORK;
        }
#endif
    }

    if( ((eStackSecurityLevel < eClusterSecurityLevel) &&
            (pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId == 0x0019) &&
            (pZPSevent->uEvent.sApsDataIndEvent.u8DstAddrMode == ZPS_E_ADDR_MODE_SHORT) &&
            (pZPSevent->uEvent.sApsDataIndEvent.uDstAddress.u16Addr < 0xFFF8)) ||
            (eStackSecurityLevel < eClusterSecurityLevel && pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId != 0x0019))
    {
        // send error response
        // Trac 6 - don't send default response from a default response.
        if (sZCL_HeaderParams.u8CommandIdentifier != E_ZCL_DEFAULT_RESPONSE ||
            sZCL_HeaderParams.eFrameType != eFRAME_TYPE_COMMAND_ACTS_ACCROSS_ENTIRE_PROFILE)
        {
            sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
            sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_SECURITY_INSUFFICIENT_FOR_CLUSTER;
            sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
            vZCL_PassEventToUser(&sZCL_CallBackEvent);

            // NTS compliance testing
            // 5.4.6 Cluster Usage of Security Keys, use FAILURE (0x01) status code
            eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_FAILURE);
        }
        // free buffer and return
        PDUM_eAPduFreeAPduInstance(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);
        return;
    }

    // Is command cluster specicfic or general
    vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n sZCL_HeaderParams.eFrameType : %d\n",sZCL_HeaderParams.eFrameType);
    switch (sZCL_HeaderParams.eFrameType)
    {
    case eFRAME_TYPE_COMMAND_ACTS_ACCROSS_ENTIRE_PROFILE:
        {
            if (sZCL_HeaderParams.u8CommandIdentifier == E_ZCL_DEFAULT_RESPONSE)
            {
                // fill in callback event
                sZCL_CallBackEvent.u8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;
                sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
                sZCL_CallBackEvent.eEventType = E_ZCL_CBET_DEFAULT_RESPONSE;
                sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
                u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &(sZCL_CallBackEvent.uMessage.sDefaultResponse.u8CommandId));
                u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &(sZCL_CallBackEvent.uMessage.sDefaultResponse.u8StatusCode));
                //call custom callback function
                vZCL_HandleDefaultResponse(pZPSevent);
                // call user directly
                psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
                break;
            }
            else if( psZCL_EndPointDefinition != NULL )
            {
                // check whether cluster is present on endpoint
                if ((psClusterInstance == NULL) && 
                    (bZCL_OverrideHandlingEntireProfileCmd(pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId) == FALSE))
                {

                	if ((sZCL_HeaderParams.u16ManufacturerCode == 0x1021)
                			&& (sZCL_HeaderParams.bManufacturerSpecific==1)
                			&& (pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId==0)
                		)
                	{
                		/*uint8_t u8Status;
                		u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT16, &(sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.u16AttributeEnum));
                		if (pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId ==0x0000)
                		{
                			if (sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.u16AttributeEnum==0xF000)
                			{
                				uint16 u16offset;
								uint16 u16payloadSize;

								PDUM_thAPduInstance myPDUM_thAPduInstance;
								uint16 u16AttributeId;
                				uint16    au16AttributeList[2];
                				au16AttributeList[0]=0xF000;
                				au16AttributeList[1]=0x0066;
                				tsZCL_Address sAddress;
                				sAddress.eAddressMode = pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode;
                			    sAddress.uAddress.u64DestinationAddress = pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u64Addr;


                			    // get buffer
                			       myPDUM_thAPduInstance = hZCL_AllocateAPduInstance();

                			       // write command header
                			       u16offset = u16ZCL_WriteCommandHeader(myPDUM_thAPduInstance,
                			                                          eFRAME_TYPE_COMMAND_ACTS_ACCROSS_ENTIRE_PROFILE,
                			                                          1,
                			                                          0x1021,
                			                                          1,
                			                                          1,
                			                                          sZCL_HeaderParams.u8TransactionSequenceNumber,
                			                                          E_ZCL_READ_ATTRIBUTES_RESPONSE);

                			       // calculate payload size
                			       u16payloadSize = u16offset + 8;
                			       // check buffer size
                			       if(PDUM_u16APduGetSize(psZCL_Common->hZCL_APdu) < u16payloadSize)
                			       {
                			           // free buffer and return
                			           PDUM_eAPduFreeAPduInstance(myPDUM_thAPduInstance);

                			       }


                			       // read input attribute Id
                			       u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_ATTRIBUTE_ID, &u16AttributeId);

                			       uint8_t u8errorCode=0;
                			       uint8_t datatype=0x23;
                			       uint32_t data=0x00000066;
                			       // write payload, attribute at a time
                			       u16ZCL_APduInstanceWriteNBO(myPDUM_thAPduInstance, u16offset, E_ZCL_ATTRIBUTE_ID, &u16AttributeId);
                			       u16ZCL_APduInstanceWriteNBO(myPDUM_thAPduInstance, u16offset+2, E_ZCL_UINT8, &u8errorCode);
                			       u16ZCL_APduInstanceWriteNBO(myPDUM_thAPduInstance,u16offset+3,E_ZCL_UINT8,&datatype);
                			       u16ZCL_APduInstanceWriteNBO(myPDUM_thAPduInstance,u16offset+4,E_ZCL_UINT32,&data);


                			       // transmit the request
                			       u8Status = eZCL_TransmitDataRequest(myPDUM_thAPduInstance,
                			                                   u16payloadSize,
                			                                   1,
                			                                   1,
                			                                   0x0000,
                			                                   &sAddress) ;

                				 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n u8Status : %d\n",u8Status);
                			}
                		}
                		// psClusterInstance = sControlBridge.sEndPoint.psClusterInstance;
                		 psClusterInstance = psZCL_Common->psZCL_EndPointRecord[0].psEndPointDefinition->psClusterInstance;
                		 sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
                		 u16inputOffset = u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT16, &(sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.u16AttributeEnum));
                		 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n u16inputOffset : %d\n",u16inputOffset);
                		 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n attributeEnum : %d\n",sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.u16AttributeEnum);
                		 u16inputOffset = u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &(sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType));
                		 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n u16inputOffset : %d\n",u16inputOffset);
                		 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n attributeEnum : %d\n",sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType);
                		 u16inputOffset = u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &(sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeStatus));
						 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n u16inputOffset : %d\n",u16inputOffset);
						 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n attributeEnum : %d\n",sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeStatus);

                		 u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT16, &(sZCL_CallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId));
						 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n u16inputOffset : %d\n",u16inputOffset);
						 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n attributeEnum : %d\n",sZCL_CallBackEvent.uMessage.sClusterCustomMessage.u16ClusterId);

						 vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId : %d\n",pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId);
                		 	*/

                	}else{
                		eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_UNSUPPORTED_CLUSTER);
                	}
                }
                else
                {
                	vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n vZCL_HandleEntireProfileCommand");

                    // Moved to zcl_library_options.h as some commands are optional so
                    // the command handler is built at the same time as the app and unused
                    // optional commands are garbage collected.
                    vZCL_HandleEntireProfileCommand(sZCL_HeaderParams.u8CommandIdentifier,
                        pZPSevent,
                        psZCL_EndPointDefinition,
                        psClusterInstance);
                }
            }
            break;
        }

    case eFRAME_TYPE_COMMAND_IS_SPECIFIC_TO_A_CLUSTER:
        {
            // check whether cluster is present on endpoint
            if (psClusterInstance == NULL)
            {
#ifdef CLD_GREENPOWER
                /* Check if the cluster is supported as  client*/
                eCallbackReturn = eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                                                                pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId,
                                                                sZCL_HeaderParams.bDirection,
                                                                &psClusterInstance);
                if(eCallbackReturn == E_ZCL_SUCCESS)
                {
                     eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_UNSUP_CLUSTER_COMMAND);
                }
                else
#endif
                {

                eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_UNSUPPORTED_CLUSTER);
                }
            }
            else
            {

                /* Input parameter checks & only interested in data indication events from here down */
                if( (psZCL_EndPointDefinition==NULL) || \
                    ( pZPSevent->eType != ZPS_EVENT_APS_DATA_INDICATION )  || \
                    (psClusterInstance->pCustomcallCallBackFunction == NULL))
                {
                    eCallbackReturn = E_ZCL_FAIL;
                }
                else
                {    
                    eCallbackReturn = psClusterInstance->pCustomcallCallBackFunction(pZPSevent, 
                                                                                     psZCL_EndPointDefinition,
                                                                                     psClusterInstance);
                }

                if (eCallbackReturn != E_ZCL_SUCCESS)
                {
                    /*map the corrrect custom command return codes to ZCL code */
                    switch (eCallbackReturn)
                    {
                        case E_ZCL_ERR_CUSTOM_COMMAND_HANDLER_NULL_OR_RETURNED_ERROR:
                            eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_UNSUP_CLUSTER_COMMAND);
                            break;
                        default :
                            eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SOFTWARE_FAILURE);
                            break;
                    }
                }
            }
        }
        break;
    default:
        {
            // Unknown frame type
            // Not doing a user call back here to save some code size as eFrameType can't be out of range for a bad message
            eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SOFTWARE_FAILURE);
        }
        break;
    }

    // delete the i/p buffer
    PDUM_eAPduFreeAPduInstance(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);
}

#if 1
/****************************************************************************
 **
 ** NAME:       vZCL_HandleInterPanIndication
 **
 ** DESCRIPTION:
 ** Valididates the Data Indication Event
 **
 ** PARAMETERS:               Name                    Usage
 ** ZPS_tsAfEvent              *pZPSevent               Zigbee stack event structure
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/
PRIVATE void vZCL_HandleInterPanIndication(ZPS_tsAfEvent *pZPSevent)
{
    teZCL_Status eCallbackReturn;
    tsZCL_EndPointDefinition    *psZCL_EndPointDefinition = NULL;
    tsZCL_ClusterInstance       *psClusterInstance;
    tsZCL_HeaderParams sZCL_HeaderParams;

    // further error checking can only be done once we have interrogated the ZCL payload
    u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsInterPanDataIndEvent.hAPduInst,
                                              &sZCL_HeaderParams);


    if (pZPSevent->uEvent.sApsInterPanDataIndEvent.u16ClusterId == 0x1000) {
        sZCL_HeaderParams.bDisableDefaultResponse = TRUE;
        sZCL_HeaderParams.eFrameType = 0x01;
        sZCL_HeaderParams.bDirection = FALSE;
        sZCL_HeaderParams.bDisableDefaultResponse = TRUE;
        switch(sZCL_HeaderParams.u8CommandIdentifier) {
            case 0x01:
            case 0x03:
            case 0x11:
            case 0x13:
            case 0x15:
                sZCL_HeaderParams.bDirection = TRUE;
                break;
        }
    }

    // check EP is registered and profile is valid
    if((eZCL_SearchForEPentryAndCheckManufacturerId(pZPSevent->uEvent.sApsInterPanDataIndEvent.u8DstEndpoint,
                                                    sZCL_HeaderParams.bManufacturerSpecific,
                                                    sZCL_HeaderParams.u16ManufacturerCode,
                                                    &psZCL_EndPointDefinition) != E_ZCL_SUCCESS) 
       )
    {
        // send response if possible/required
        // Trac 6 - don't send default response from a default response.
#if 0
        if (sZCL_HeaderParams.u8CommandIdentifier != E_ZCL_DEFAULT_RESPONSE ||
            sZCL_HeaderParams.eFrameType != eFRAME_TYPE_COMMAND_ACTS_ACCROSS_ENTIRE_PROFILE)
        {
            sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
            sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_EP_UNKNOWN;
            sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
            vZCL_PassEventToUser(&sZCL_CallBackEvent);
            eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SOFTWARE_FAILURE);
        }
#endif
        // free buffer and return
        PDUM_eAPduFreeAPduInstance(pZPSevent->uEvent.sApsInterPanDataIndEvent.hAPduInst);
        return;
    }

    // check the command is suitable for the endpoint - cluster, manufac Id, direction
    eCallbackReturn = eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsInterPanDataIndEvent.u8DstEndpoint,
                                                    pZPSevent->uEvent.sApsInterPanDataIndEvent.u16ClusterId,
                                                    !sZCL_HeaderParams.bDirection,
                                                    &psClusterInstance);


    if (psClusterInstance != NULL && psClusterInstance->pCustomcallCallBackFunction != NULL)
    {
        eCallbackReturn = psClusterInstance->pCustomcallCallBackFunction(pZPSevent,
                                                                         psZCL_EndPointDefinition,
                                                                         psClusterInstance);
        if (eCallbackReturn != E_ZCL_SUCCESS)
        {
            // error
            //eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SOFTWARE_FAILURE);

}
    } else {
        // error
        /*DBG_vPrintf(TRUE, "01\n");*/
    }

    PDUM_eAPduFreeAPduInstance(pZPSevent->uEvent.sApsInterPanDataIndEvent.hAPduInst);

}
#endif

/****************************************************************************
 **
 ** NAME:       vZCL_HandleDataAcknowledgement
 **
 ** DESCRIPTION:
 ** Valididates the Data Acknowledgement Event
 **
 ** PARAMETERS:               Name                    Usage
 ** ZPS_tsAfEvent              *pZPSevent               Zigbee stack event structure
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/

PRIVATE void vZCL_HandleDataAcknowledgement(ZPS_tsAfEvent *pZPSevent)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent;
    tsZCL_EndPointDefinition    *psZCL_EndPointDefinition;
    tsZCL_ClusterInstance       *psClusterInstance;
    teZCL_Status                 eCallbackReturn;

    // fill in callback event
    sZCL_CallBackEvent.u8TransactionSequenceNumber = 0;
    sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataAckEvent.u8SrcEndpoint;
    sZCL_CallBackEvent.psClusterInstance = NULL;
    sZCL_CallBackEvent.pZPSevent = pZPSevent;

    // only interested in this ACK as part of the key establishment cluster timeout mechanism
    if(!((pZPSevent->uEvent.sApsDataAckEvent.u16ClusterId == SE_CLUSTER_ID_KEY_ESTABLISHMENT)||
    (pZPSevent->uEvent.sApsDataAckEvent.u16ClusterId == SE_CLUSTER_ID_TUNNELING)))
    {
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_UNHANDLED_EVENT;
        psZCL_Common->pfZCLinternalCallBackFunction(&sZCL_CallBackEvent);
        return;
    }

    // find and post to endpoint
    if((eZCL_SearchForEPentry(pZPSevent->uEvent.sApsDataAckEvent.u8DstEndpoint, &psZCL_EndPointDefinition) != E_ZCL_SUCCESS) ||
       (psZCL_EndPointDefinition->u16ProfileEnum != pZPSevent->uEvent.sApsDataAckEvent.u16ProfileId)

       )
    {
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
        sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_KEY_ESTABLISHMENT_END_POINT_NOT_FOUND;
        psZCL_Common->pfZCLinternalCallBackFunction(&sZCL_CallBackEvent);
        return;
    }

    // find the cluster - there will be only one per EP so this method is 'safe'
    if(SE_CLUSTER_ID_KEY_ESTABLISHMENT == pZPSevent->uEvent.sApsDataAckEvent.u16ClusterId)
    {
        if(eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataAckEvent.u8DstEndpoint,
                                      SE_CLUSTER_ID_KEY_ESTABLISHMENT,
                                      TRUE,
                                     &psClusterInstance) != E_ZCL_SUCCESS)
        {
            if(eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataAckEvent.u8DstEndpoint,
                                          SE_CLUSTER_ID_KEY_ESTABLISHMENT,
                                          FALSE,
                                         &psClusterInstance) != E_ZCL_SUCCESS)
            {
                sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
                sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_KEY_ESTABLISHMENT_CLUSTER_ENTRY_NOT_FOUND;
                psZCL_Common->pfZCLinternalCallBackFunction(&sZCL_CallBackEvent);
                return;
            }
        }
    }
    else if(SE_CLUSTER_ID_TUNNELING == pZPSevent->uEvent.sApsDataAckEvent.u16ClusterId)
    {
        if(eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataAckEvent.u8DstEndpoint,
                                            SE_CLUSTER_ID_TUNNELING,
                                            TRUE,
                                            &psClusterInstance) != E_ZCL_SUCCESS)
                {
                    if(eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataAckEvent.u8DstEndpoint,
                            SE_CLUSTER_ID_TUNNELING,
                            FALSE,
                            &psClusterInstance) != E_ZCL_SUCCESS)
                    {
                        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
                        //sZCL_CallBackEvent.eZCL_Status = E_ZCL_CBET_ERROR;
                        //psZCL_Common->pfZCLinternalCallBackFunction(&sZCL_CallBackEvent);
                        return;
                    }
                }
    }

    // at this point we have found the Key Cluster, check user custom callback
    // preset result
    eCallbackReturn = E_ZCL_FAIL;
    if(psClusterInstance->pCustomcallCallBackFunction != NULL)
    {
        eCallbackReturn = psClusterInstance->pCustomcallCallBackFunction(pZPSevent, psZCL_EndPointDefinition, psClusterInstance);
    }

    // implementation error
    if(eCallbackReturn != E_ZCL_SUCCESS)
    {
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
        sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_KEY_ESTABLISHMENT_CALLBACK_ERROR;
        psZCL_Common->pfZCLinternalCallBackFunction(&sZCL_CallBackEvent);
    }

}
/****************************************************************************
 **
 ** NAME:       vZCL_HandleDefaultResponse
 **
 ** DESCRIPTION:
 ** Valididates the Data Acknowledgement Event
 **
 ** PARAMETERS:               Name                    Usage
 ** ZPS_tsAfEvent              *pZPSevent               Zigbee stack event structure
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/
PRIVATE void vZCL_HandleDefaultResponse(ZPS_tsAfEvent *pZPSevent)
{
    tsZCL_EndPointDefinition    *psZCL_EndPointDefinition;
    tsZCL_ClusterInstance       *psClusterInstance;

    // only interested in this default response as part of the OTA cluster default response handling
    if(pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId == 0x0019)//OTA_CLUSTER_ID = 0x0019
    {
        // find and post to endpoint
        if(eZCL_SearchForEPentry(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint, &psZCL_EndPointDefinition) == E_ZCL_SUCCESS)
        {
            // find the cluster - there will be only one per EP so this method is 'safe'
            if(eZCL_SearchForClusterEntry(pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                                          (uint16)0x0019,//OTA_CLUSTER_ID = 0x0019
                                          FALSE,
                                         &psClusterInstance) == E_ZCL_SUCCESS)
            {
                if(psClusterInstance->pCustomcallCallBackFunction)
                {
                    // at this point we have found the OTA Cluster, check user custom callback
                    psClusterInstance->pCustomcallCallBackFunction(pZPSevent, psZCL_EndPointDefinition, psClusterInstance);
                }
            }
        }
    }
}

/****************************************************************************
 **
 ** NAME:       vZCL_RegisterHandleGeneralCmdCallBack
 **
 ** DESCRIPTION:
 ** Registers the call back to override the ZCL handling of general command which act across entire profile
 ** if cluster is not present
 **
 ** PARAMETERS:               Name                    Usage
 ** void                     *fnPtr                   Function pointer to registered callback
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/
PUBLIC void vZCL_RegisterHandleGeneralCmdCallBack(void* fnPtr)
{
    prfnbZCLOverrideHandlingEntireProfileCommand = (bool_t (*)( uint16 ))fnPtr;
}

/****************************************************************************
 **
 ** NAME:       bZCL_OverrideHandlingEntireProfileCmd
 **
 ** DESCRIPTION:
 ** Checks whether ZCL general command handling needs to be overriden or not
 ** is not present
 **
 ** PARAMETERS:               Name                    Usage
 **
 ** RETURN:
 ** bool
 **
 ****************************************************************************/

PRIVATE bool_t bZCL_OverrideHandlingEntireProfileCmd(uint16 u16ClusterId)
{
    if(prfnbZCLOverrideHandlingEntireProfileCommand != NULL)
    {
        return prfnbZCLOverrideHandlingEntireProfileCommand(u16ClusterId);
    }
    return FALSE;
}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
