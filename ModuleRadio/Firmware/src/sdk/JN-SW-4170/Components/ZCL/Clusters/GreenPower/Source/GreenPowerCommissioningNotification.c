/*****************************************************************************
 *
 * MODULE:             Green Power Cluster
 *
 * COMPONENT:          GreenPowerCommissioningNotification.c
 *
 * AUTHOR:             Ramakrishna
 *
 * DESCRIPTION:        Send and Receive functions for the Green Power Commissioning notification command
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/GreenPower/Source/GreenPowerCommissioningNotification.c $
 *
 * $Revision: 85803 $
 *
 * $LastChangedBy: nxp29757 $
 *
 * $LastChangedDate: 2016-12-14 12:46:29 +0100 (Wed, 14 Dec 2016) $
 *
 * $Id: GreenPowerCommissioningNotification.c 85803 2016-12-14 11:46:29Z nxp29757 $
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
#include "zcl.h"
#include "zcl_options.h"
#include "GreenPower.h"
#include "GreenPower_internal.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Public Functions                                              ***/
/****************************************************************************/
#ifndef GP_DISABLE_COMMISSION_NOTIFICATION_CMD
/****************************************************************************
 **
 ** NAME:       eGP_ZgpCommissioningNotificationSend
 **
 ** DESCRIPTION:
 ** Sends ZGP Commissioning notification command
 **
 ** PARAMETERS:                                 Name                            Usage
 ** uint8                                       u8SourceEndPointId              Source EP Id
 ** uint8                                       u8DestinationEndPointId         Destination EP Id
 ** tsZCL_Address                               *psDestinationAddress           Destination Address
 ** uint8                                       *pu8TransactionSequenceNumber   Sequence number Pointer
 ** tsGP_ZgpCommissioningNotificationCmdPayload *psZgpCmsngNotificationPayload  Commission Notification Payload
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC teZCL_Status eGP_ZgpCommissioningNotificationSend(
                    uint8                                       u8SourceEndPointId,
                    uint8                                       u8DestinationEndPointId,
                    tsZCL_Address                               *psDestinationAddress,
                    uint8                                       *pu8TransactionSequenceNumber,
                    tsGP_ZgpCommissioningNotificationCmdPayload *psZgpCmsngNotificationPayload)
{

    zbmap16 b16Options;
    uint8 u8ItemsInPayload;
    /* asPayloadDefinition is of size 9 to take care of application id 2  */
    tsZCL_TxPayloadItem asPayloadDefinition[9] = {
         {1,  E_ZCL_BMAP16,   &psZgpCmsngNotificationPayload->b16Options}, //1
         {1,  E_ZCL_UINT32,   &psZgpCmsngNotificationPayload->uZgpdDeviceAddr.u32ZgpdSrcId}, //2
         {1,  E_ZCL_UINT32,   &psZgpCmsngNotificationPayload->u32ZgpdSecFrameCounter},//3
         {1,  E_ZCL_UINT8,    &psZgpCmsngNotificationPayload->u8ZgpdCmdId},//4
         {1,  E_ZCL_OSTRING,  &psZgpCmsngNotificationPayload->sZgpdCommandPayload},//5
         {1,  E_ZCL_UINT16,   &psZgpCmsngNotificationPayload->u16ZgppShortAddr},//6
         {1,  E_ZCL_UINT8,     &psZgpCmsngNotificationPayload->u8GPP_GPD_Link},//7
         {1,  E_ZCL_UINT32,   &psZgpCmsngNotificationPayload->u32Mic}//8
        };

    /* Get options field from payload */
    b16Options = psZgpCmsngNotificationPayload->b16Options;

    u8ItemsInPayload = 5; //  mandatory items in command payload

    /* application id 2 support */
#ifdef GP_IEEE_ADDR_SUPPORT
    if((b16Options & GP_APPLICATION_ID_MASK) == 2)
    {
        asPayloadDefinition[1].eType = E_ZCL_IEEE_ADDR;
        asPayloadDefinition[1].pvData = &psZgpCmsngNotificationPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u64ZgpdIEEEAddr;

		/* add Endpoint */
		 asPayloadDefinition[2].eType = E_ZCL_UINT8;
		 asPayloadDefinition[2].pvData = &psZgpCmsngNotificationPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint;

		 asPayloadDefinition[3].eType = E_ZCL_UINT32;
		 asPayloadDefinition[3].pvData = &psZgpCmsngNotificationPayload->u32ZgpdSecFrameCounter;

		 asPayloadDefinition[4].eType = E_ZCL_UINT8;
		 asPayloadDefinition[4].pvData = &psZgpCmsngNotificationPayload->u8ZgpdCmdId;

		 asPayloadDefinition[5].eType = E_ZCL_OSTRING;
		 asPayloadDefinition[5].pvData = &psZgpCmsngNotificationPayload->sZgpdCommandPayload;

		 asPayloadDefinition[6].eType = E_ZCL_UINT16;
		 asPayloadDefinition[6].pvData = &psZgpCmsngNotificationPayload->u16ZgppShortAddr;

		 asPayloadDefinition[7].eType = E_ZCL_UINT8;
		 asPayloadDefinition[7].pvData = &psZgpCmsngNotificationPayload->u8GPP_GPD_Link;

		 asPayloadDefinition[8].u16Quantity = 1;
		 asPayloadDefinition[8].eType = E_ZCL_UINT32;
		 asPayloadDefinition[8].pvData = &psZgpCmsngNotificationPayload->u32Mic;

        u8ItemsInPayload++;
    }
#else
    if((b16Options & GP_APPLICATION_ID_MASK) == 2)
    {
        return E_ZCL_ERR_INVALID_VALUE;
    }
#endif
    /* check if ZGP short address and ZGP distance fields are present in payload */
    if((b16Options & GP_CMSNG_NOTIFICATION_PROXY_INFO_MASK) || (b16Options & GP_CMSNG_NOTIFICATION_RX_AFTER_TX_MASK))
    {
        u8ItemsInPayload += 2; //  increase optional 2 field
    }
    /* check if MIC field are present in payload */
    if(b16Options & GP_CMSNG_NOTIFICATION_SEC_PROCESS_FAIL_MASK)
    {
        u8ItemsInPayload += 1; //  increase optional 1 field
        /* if ZGP short address and ZGP distance fields are not present in payload
         * then MIC field would be at 6th position */
        if((u8ItemsInPayload == 6) && ((b16Options & GP_APPLICATION_ID_MASK) == 0))
        {
            asPayloadDefinition[5].eType = E_ZCL_UINT32;
            asPayloadDefinition[5].pvData = &psZgpCmsngNotificationPayload->u32Mic;
        }
        else if ((u8ItemsInPayload == 7) && ((b16Options & GP_APPLICATION_ID_MASK) == 2))
        {
            asPayloadDefinition[6].eType = E_ZCL_UINT32;
            asPayloadDefinition[6].pvData = &psZgpCmsngNotificationPayload->u32Mic;
        }
    }


    return eZCL_CustomCommandSend(u8SourceEndPointId,
                              u8DestinationEndPointId,
                              psDestinationAddress,
                              GREENPOWER_CLUSTER_ID,
                              FALSE,
                              E_GP_ZGP_COMMOSSIONING_NOTIFICATION,
                              pu8TransactionSequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              u8ItemsInPayload);

}

/****************************************************************************
 **
 ** NAME:       eGP_ZgpCommissioningNotificationReceive
 **
 ** DESCRIPTION:
 ** receives ZGP commissioning notification command
 **
 ** PARAMETERS:                                 Name                            Usage
 ** ZPS_tsAfEvent                               *pZPSevent                      ZPS event
 ** tsZCL_EndPointDefinition                    *psEndPointDefinition           Endpoint definition
 ** tsZCL_ClusterInstance                       *psClusterInstance              cluster instance
 ** uint16                                      u16Offset                       offset
 ** tsGP_ZgpCommissioningNotificationCmdPayload *psZgpCmsngNotificationPayload  pointer to zgp cmsng notification command payload
 **
 ** RETURN:
 ** teZCL_Status
 ****************************************************************************/

PUBLIC teZCL_Status eGP_ZgpCommissioningNotificationReceive(
                    ZPS_tsAfEvent                               *pZPSevent,
                    uint16                                      u16Offset,
                    tsGP_ZgpCommissioningNotificationCmdPayload *psZgpCmsngNotificationPayload)
{
    uint8 u8TransactionSequenceNumber;
    uint16 u16ActualQuantity;
    zbmap16 b16Options;
    uint8  u8ItemsInPayload;

    /* asPayloadDefinition is 9 for application id 2 and 8 for application id 1*/
    tsZCL_RxPayloadItem asPayloadDefinition[9] = {
         {1, &u16ActualQuantity, E_ZCL_BMAP16,   &psZgpCmsngNotificationPayload->b16Options}, //1
         {1, &u16ActualQuantity, E_ZCL_UINT32,   &psZgpCmsngNotificationPayload->uZgpdDeviceAddr.u32ZgpdSrcId},//2
         {1, &u16ActualQuantity, E_ZCL_UINT32,   &psZgpCmsngNotificationPayload->u32ZgpdSecFrameCounter},//3
         {1, &u16ActualQuantity, E_ZCL_UINT8,    &psZgpCmsngNotificationPayload->u8ZgpdCmdId}, //4
         {1, &u16ActualQuantity, E_ZCL_OSTRING,  &psZgpCmsngNotificationPayload->sZgpdCommandPayload},//5
         {1, &u16ActualQuantity, E_ZCL_UINT16,   &psZgpCmsngNotificationPayload->u16ZgppShortAddr},//6
         {1, &u16ActualQuantity, E_ZCL_UINT8,     &psZgpCmsngNotificationPayload->u8GPP_GPD_Link},//7
         {1, &u16ActualQuantity, E_ZCL_UINT32,   &psZgpCmsngNotificationPayload->u32Mic},//8
         {1, &u16ActualQuantity, E_ZCL_UINT32,   &psZgpCmsngNotificationPayload->u32Mic}//values are not correct, overwritten below
        };
    /* Get options field from payload */
    u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                               u16Offset,
                               E_ZCL_BMAP16,
                               &b16Options);

    u8ItemsInPayload = 5; //  mandatory items in command payload
#ifdef GP_IEEE_ADDR_SUPPORT
    if((b16Options & GP_APPLICATION_ID_MASK) == GP_APPL_ID_8_BYTE)
    {

        asPayloadDefinition[1].eType = E_ZCL_IEEE_ADDR;
        asPayloadDefinition[1].pvDestination = &psZgpCmsngNotificationPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u64ZgpdIEEEAddr;

		/* add Endpoint */
		 asPayloadDefinition[2].eType = E_ZCL_UINT8;
		 asPayloadDefinition[2].pvDestination = &psZgpCmsngNotificationPayload->uZgpdDeviceAddr.sZgpdDeviceAddrAppId2.u8EndPoint;

		 asPayloadDefinition[3].eType = E_ZCL_UINT32;
		 asPayloadDefinition[3].pvDestination = &psZgpCmsngNotificationPayload->u32ZgpdSecFrameCounter;

		 asPayloadDefinition[4].eType = E_ZCL_UINT8;
		 asPayloadDefinition[4].pvDestination = &psZgpCmsngNotificationPayload->u8ZgpdCmdId;

		 asPayloadDefinition[5].eType = E_ZCL_OSTRING;
		 asPayloadDefinition[5].pvDestination = &psZgpCmsngNotificationPayload->sZgpdCommandPayload;

		 asPayloadDefinition[6].eType = E_ZCL_UINT16;
		 asPayloadDefinition[6].pvDestination = &psZgpCmsngNotificationPayload->u16ZgppShortAddr;

		 asPayloadDefinition[7].eType = E_ZCL_UINT8;
		 asPayloadDefinition[7].pvDestination = &psZgpCmsngNotificationPayload->u8GPP_GPD_Link;

		 asPayloadDefinition[8].eType = E_ZCL_UINT32;
		 asPayloadDefinition[8].pvDestination = &psZgpCmsngNotificationPayload->u32Mic;

		 u8ItemsInPayload++;


    }
#else
    if((b16Options & GP_APPLICATION_ID_MASK) == GP_APPL_ID_8_BYTE)
    {
        return E_ZCL_ERR_INVALID_VALUE;
    }
#endif
    /* check if ZGP short address and ZGP distance fields are present in payload */
    if((b16Options & GP_CMSNG_NOTIFICATION_PROXY_INFO_MASK) || (b16Options & GP_CMSNG_NOTIFICATION_RX_AFTER_TX_MASK))
    {
        u8ItemsInPayload += 2; //  increase optional 2 field
    }
    /* check if MIC field are present in payload */
    if(b16Options & GP_CMSNG_NOTIFICATION_SEC_PROCESS_FAIL_MASK)
    {
        u8ItemsInPayload += 1; //  increase optional 1 field
        /* if ZGP short address and ZGP distance fields are not present in payload
         * then MIC field would be at 6th position */
        if((u8ItemsInPayload == 6) &&((b16Options & GP_APPLICATION_ID_MASK) == GP_APPL_ID_4_BYTE))
        {
            asPayloadDefinition[5].eType = E_ZCL_UINT32;
            asPayloadDefinition[5].pvDestination = &psZgpCmsngNotificationPayload->u32Mic;
        }
        if((u8ItemsInPayload == 7) &&((b16Options & GP_APPLICATION_ID_MASK) == GP_APPL_ID_8_BYTE))
	    {
		    asPayloadDefinition[6].eType = E_ZCL_UINT32;
		    asPayloadDefinition[6].pvDestination = &psZgpCmsngNotificationPayload->u32Mic;
	    }
    }

    return eZCL_CustomCommandReceive(pZPSevent,
                              &u8TransactionSequenceNumber,
                              asPayloadDefinition,
                              u8ItemsInPayload,
                              E_ZCL_DISABLE_DEFAULT_RESPONSE);

}
#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
