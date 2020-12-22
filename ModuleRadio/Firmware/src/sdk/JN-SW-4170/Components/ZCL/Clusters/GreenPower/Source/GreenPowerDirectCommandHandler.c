/*****************************************************************************
 *
 * MODULE:             Green Power Direct command handler
 *
 * COMPONENT:          GreenPowerDirectCommandHandler.c
 *
 * AUTHOR:             Ramakrishna
 *
 * DESCRIPTION:        The handling functions for the Green Power direct commands
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/GreenPower/Source/GreenPowerDirectCommandHandler.c $
 *
 * $Revision: 80589 $
 *
 * $LastChangedBy: nxp29757 $
 *
 * $LastChangedDate: 2016-06-17 09:37:11 +0100 (Fri, 17 Jun 2016) $
 *
 * $Id: GreenPowerDirectCommandHandler.c 80589 2016-06-17 08:37:11Z nxp29757 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products  [NXP Microcontrollers such as JN5168, JN5164,
 * JN5161, JN5148, JN5142, JN5139].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each  copy or partial copy of the software.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <string.h>
#include "dlist.h"
#include "zcl.h"
#include "GreenPower.h"
#include "GreenPower_internal.h"
#include "dbg.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef TRACE_GP_DEBUG
#define TRACE_GP_DEBUG FALSE
#endif
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/



void vGP_FormGPDataIndication(tsGP_ZgpDataIndication   *psZgpDataIndication,
								ZPS_tsAfEvent               *pZPSevent);

void vBufferCommNotifAndExitCommMode(
		tsZCL_EndPointDefinition    					*psEndPointDefinition,
		tsGP_ZgpDataIndication                          *psZgpDataIndication,
		tsGP_GreenPowerCustomData                       *psGpCustomDataStructure);


bool bCheckSecurityCommCmd(
		bool 				                            bIsSinkTableEntryPresent,
		uint8											u8ZgpsSecLevel,
		uint8											*pu8SecKeyType,
		ZPS_tsAfEvent               					*pZPSevent,
		tsZCL_EndPointDefinition    					*psEndPointDefinition,
		tsGP_GreenPowerCustomData                       *psGpCustomDataStructure,
		tsGP_ZgppProxySinkTable                              *psZgpsSinkTable);

bool bDecryptAndCopyKey(ZPS_tsAfEvent               	*pZPSevent,
		tsZCL_EndPointDefinition    					*psEndPointDefinition,
		tsGP_GreenPowerCustomData                       *psGpCustomDataStructure,
		tsGP_ZgppProxySinkTable                              *psZgpsSinkTable);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eGP_GreenPowerDirectCommandHandler
 **
 ** DESCRIPTION:
 ** Green Power direct command handler
 **
 ** PARAMETERS:                    Name                           Usage
 ** ZPS_tsAfEvent               *pZPSevent                  ZPS event
 ** tsZCL_EndPointDefinition    *psEndPointDefinition       endpoint definition
 ** tsZCL_ClusterInstance       *psClusterInstance          cluster instance
 **
 ** RETURN:
 ** teZCL_Status
 ****************************************************************************/
PUBLIC teZCL_Status eGP_GreenPowerDirectCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance)
{
    tsGP_GreenPowerCustomData   *psGpCustomDataStructure;
    teZCL_Status                eStatus = E_ZCL_SUCCESS;
    uint8                       u8ZgpdCmdId;
    bool_t 		IsPacketValid = FALSE;
    tsGP_ZgpDataIndication                          sZgpDataIndication;
    teGP_GreenPowerBufferedCommands eBufferedCmdId = E_GP_DATA;
    /* Get Command Id & custom data structure pointer */
    u8ZgpdCmdId = (uint8)pZPSevent->uEvent.sApsZgpDataIndEvent.u8CommandId;
    psGpCustomDataStructure = (tsGP_GreenPowerCustomData*)psClusterInstance->pvEndPointCustomStructPtr;
    DBG_vPrintf(TRACE_GP_DEBUG, "ZGPD Direct command Id, : 0x%02x, status: 0x%02x, security Level: %d, u32Mic: 0x%08x, SeqNum: %d\n", u8ZgpdCmdId,
    		pZPSevent->uEvent.sApsZgpDataIndEvent.u8Status,
    		pZPSevent->uEvent.sApsZgpDataIndEvent.u2SecurityLevel,
    		pZPSevent->uEvent.sApsZgpDataIndEvent.u32Mic,
			pZPSevent->uEvent.sApsZgpDataIndEvent.u8SeqNum);

    if((psGpCustomDataStructure->u16TransmitChannelTimeout) /*&& (sZgpDataIndication.u8CommandId == E_GP_CHANNEL_REQUEST)*/)
    {
   	 DBG_vPrintf(TRACE_GP_DEBUG, "\n psGpCustomDataStructure->u16TransmitChannelTimeout return  = %d \n", psGpCustomDataStructure->u16TransmitChannelTimeout);
        return eStatus;
    }
    // get EP mutex
    #ifndef COOPERATIVE
        eZCL_GetMutex(psEndPointDefinition);
    #endif

	/* Get the info from pZPSevent to sZgpDataIndication */
	vGP_FormGPDataIndication(&sZgpDataIndication, pZPSevent);
	/* Check whether the packet is valid:
	 * 1. whether command received in appropriate mode
	 * 2. Freshness check
	 * 3. Security Check
	 */
	IsPacketValid = bGP_GPDFValidityCheck(&sZgpDataIndication, psEndPointDefinition, psClusterInstance, &eBufferedCmdId);

	if(IsPacketValid)
	{


		if(eBufferedCmdId == E_GP_COMMISSIONING_CMDS )
		{

		   if( psGpCustomDataStructure->eGreenPowerDeviceMode == E_GP_PAIRING_COMMISSION_MODE)
		   {

				if(bGP_GiveCommIndAndUpdateTable(&sZgpDataIndication, psEndPointDefinition,psGpCustomDataStructure)
						== FALSE )
				{
					DBG_vPrintf(TRACE_GP_DEBUG, "\n bGP_GiveCommIndAndUpdateTable failed \n");
					return E_ZCL_SUCCESS;
				}
		   }
		}

		/* Buffer the packet, packet will be processed in vGp_TransmissionTimerCallback*/
		eGp_BufferTransmissionPacket(
							&sZgpDataIndication,
							eBufferedCmdId,
							psGpCustomDataStructure);
	}
	else
	{
		DBG_vPrintf(TRACE_GP_DEBUG, "\n IsPacketValid  failed \n");
	}

    // release mutex
    #ifndef COOPERATIVE
        eZCL_ReleaseMutex(psEndPointDefinition);
    #endif


    return eStatus;
}





/****************************************************************************
 **
 ** NAME:       vGP_FormGPDataIndication
 **
 ** DESCRIPTION:
 ** Fills tsGP_ZgpDataIndication from ZPS_tsAfEvent
 **
 ** PARAMETERS:                    Name                           Usage
 ** tsGP_ZgpDataIndication      *psZgpDataIndication		Data Indication
 ** ZPS_tsAfEvent    			*pZPSevent       			ZPS event
 **
 ** RETURN:
 ** None
 ****************************************************************************/
void vGP_FormGPDataIndication(tsGP_ZgpDataIndication   *psZgpDataIndication,
								ZPS_tsAfEvent               *pZPSevent)
{
    /* Check Application Id */
    /* Copy Green Power Device Address */
	memset(psZgpDataIndication, 0, sizeof(tsGP_ZgpDataIndication));
	if(pZPSevent->uEvent.sApsZgpDataIndEvent.u8FrameType)
	{
		psZgpDataIndication->uZgpdDeviceAddr.u32ZgpdSrcId = 0;
		psZgpDataIndication->u2ApplicationId = 0;
	}
	else
	{
		if(pZPSevent->uEvent.sApsZgpDataIndEvent.u2ApplicationId == GP_APPL_ID_4_BYTE)
		{
			psZgpDataIndication->uZgpdDeviceAddr.u32ZgpdSrcId = pZPSevent->uEvent.sApsZgpDataIndEvent.uGpAddress.u32SrcId;
			DBG_vPrintf(TRACE_GP_DEBUG, "psZgpDataIndication->uZgpdDeviceAddr.u32ZgpdSrcId = %04x\n", psZgpDataIndication->uZgpdDeviceAddr.u32ZgpdSrcId);
		}
	#ifdef GP_IEEE_ADDR_SUPPORT
		else
		{
			psZgpDataIndication->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u64ZgpdIEEEAddr =
				pZPSevent->uEvent.sApsZgpDataIndEvent.uGpAddress.u64Addr;
			psZgpDataIndication->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint =  pZPSevent->uEvent.sApsZgpDataIndEvent.u8Endpoint;
			DBG_vPrintf(TRACE_GP_DEBUG, "Setting address and endpoint %016llx:%d\n", pZPSevent->uEvent.sApsZgpDataIndEvent.uGpAddress.u64Addr, pZPSevent->uEvent.sApsZgpDataIndEvent.u8Endpoint);

		}
	#endif
		psZgpDataIndication->u2ApplicationId = pZPSevent->uEvent.sApsZgpDataIndEvent.u2ApplicationId;
		psZgpDataIndication->u2SecurityKeyType = pZPSevent->uEvent.sApsZgpDataIndEvent.u2SecurityKeyType;
		psZgpDataIndication->u2SecurityLevel = pZPSevent->uEvent.sApsZgpDataIndEvent.u2SecurityLevel;
		psZgpDataIndication->bRxAfterTx = pZPSevent->uEvent.sApsZgpDataIndEvent.bRxAfterTx;
	}
	psZgpDataIndication->u8Status = pZPSevent->uEvent.sApsZgpDataIndEvent.u8Status;
	psZgpDataIndication->u8CommandId = pZPSevent->uEvent.sApsZgpDataIndEvent.u8CommandId;
	psZgpDataIndication->u8LinkQuality = pZPSevent->uEvent.sApsZgpDataIndEvent.u8LinkQuality;


	psZgpDataIndication->bAutoCommissioning = pZPSevent->uEvent.sApsZgpDataIndEvent.bAutoCommissioning;

	psZgpDataIndication->u8SeqNum = pZPSevent->uEvent.sApsZgpDataIndEvent.u8SeqNum;
	psZgpDataIndication->u32Mic = pZPSevent->uEvent.sApsZgpDataIndEvent.u32Mic;
	psZgpDataIndication->bTunneledPkt = FALSE;
	psZgpDataIndication->bFrameType = pZPSevent->uEvent.sApsZgpDataIndEvent.u8FrameType;

	if(pZPSevent->uEvent.sApsZgpDataIndEvent.u2SecurityLevel != E_GP_NO_SECURITY)
	 {
		psZgpDataIndication->u32SecFrameCounter = pZPSevent->uEvent.sApsZgpDataIndEvent.u32SecFrameCounter;
	 }
	 else
	 {
		 psZgpDataIndication->u32SecFrameCounter = pZPSevent->uEvent.sApsZgpDataIndEvent.u8SeqNum;
	 }

	psZgpDataIndication->u8RSSI = pZPSevent->uEvent.sApsZgpDataIndEvent.u8Rssi;
	psZgpDataIndication->u8GPP_GPDLink = u8GP_GetProxyDistance(pZPSevent->uEvent.sApsZgpDataIndEvent.u8LinkQuality ,pZPSevent->uEvent.sApsZgpDataIndEvent.u8Rssi);
	/* Copy Payload */
	psZgpDataIndication->pu8Pdu = (uint8*)PDUM_pvAPduInstanceGetPayload(pZPSevent->uEvent.sApsZgpDataIndEvent.hAPduInst);

	psZgpDataIndication->u8PDUSize = (uint8)PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsZgpDataIndEvent.hAPduInst);
	/**/
	{
		DBG_vPrintf(TRACE_GP_DEBUG, " \n Frame type = %d, endpoint recvd %d endpoint copied = %d",pZPSevent->uEvent.sApsZgpDataIndEvent.u8FrameType,
				 pZPSevent->uEvent.sApsZgpDataIndEvent.u8Endpoint,
				 psZgpDataIndication->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint );
		DBG_vPrintf(TRACE_GP_DEBUG, " \n RSSI = %d, LQI %d ",pZPSevent->uEvent.sApsZgpDataIndEvent.u8Rssi,
				 pZPSevent->uEvent.sApsZgpDataIndEvent.u8LinkQuality);

	}
    /* check length */
    if(psZgpDataIndication->u8PDUSize == 0xFF)
    {
    	psZgpDataIndication->u8PDUSize = 0x00;
    }

    psZgpDataIndication->u16NwkShortAddr = ZPS_u16AplZdoGetNwkAddr();
  }


