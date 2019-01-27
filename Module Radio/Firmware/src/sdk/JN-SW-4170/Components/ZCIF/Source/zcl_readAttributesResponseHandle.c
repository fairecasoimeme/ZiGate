/*****************************************************************************
*
* MODULE:             Smart Energy
*
* COMPONENT:          zcl_readAttributesResponseHandle.c
*
* AUTHOR:             we1
*
* DESCRIPTION:       Receive a Read Attributes Response
*
* $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Branches/Zigbee_3_0/Source/zcl_readAttributesResponseHandle.c $
*
* $Revision: 65862 $
*
* $LastChangedBy: nxp58432 $
*
* $LastChangedDate: 2014-11-20 18:43:28 +0530 (Thu, 20 Nov 2014) $
*
* $Id: zcl_readAttributesResponseHandle.c 65862 2014-11-20 13:13:28Z nxp58432 $
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

#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_common.h"
#include "zcl_internal.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"
#include "Log.h"

#include "app_common.h"


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
uAttribData uAttributeVal;
/****************************************************************************/
/***        Public Functions                                              ***/
/****************************************************************************/

/****************************************************************************
**
** NAME:       vZCL_HandleAttributesReadResponse
**
** DESCRIPTION:
**
**
** PARAMETERS:               Name                      Usage
** ZPS_tsAfEvent              *pZPSevent                 Zigbee Stack Event
** tsZCL_EndPointDefinition *psZCL_EndPointDefinition  EP structure
** tsZCL_ClusterInstance    *psClusterInstance     Cluster structure
**
** RETURN:
** bool_t - TRUE delete input buffer, FALSE don't
**
****************************************************************************/
PUBLIC   void vZCL_HandleAttributesReadResponse(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent;
    uint16 u16inputOffset = 0;
    uint16 u16typeSize;
    tsZCL_HeaderParams sZCL_HeaderParams;
    uint16 u16payloadSize;
    uint16 u16Length;
    uint8                  au8LinkTxBuffer[256];

    // fill in non-attribute specific values in callback event structure
    sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
    sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
    sZCL_CallBackEvent.pZPSevent = pZPSevent;
    sZCL_CallBackEvent.eEventType = E_ZCL_CBET_READ_INDIVIDUAL_ATTRIBUTE_RESPONSE;
    sZCL_CallBackEvent.eZCL_Status = E_ZCL_SUCCESS;


    // read incoming request
    u16inputOffset = u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                                              &sZCL_HeaderParams);
    sZCL_CallBackEvent.u8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;

    // get received payload length
    u16payloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);

    u16Length =  0;
	ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [0],u16payloadSize,         u16Length );

	sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_INDIVIDUAL_ATTRIBUTE;

    /* report attribute handling */
    if(sZCL_HeaderParams.u8CommandIdentifier == E_ZCL_REPORT_ATTRIBUTES)
    {

        //Following code is required only for Mirroring in SE
        //Call-back is generated to validate the ZCL attribute report,
        //Based on the received Status byte flow is continued, else returned with default response
        if ((psClusterInstance != NULL) && (psClusterInstance->psClusterDefinition->u8ClusterControlFlags & CLUSTER_MIRROR_BIT))
        {

             sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ATTRIBUTE_REPORT_MIRROR;
             sZCL_CallBackEvent.uMessage.sReportAttributeMirror.u8DestinationEndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
             sZCL_CallBackEvent.uMessage.sReportAttributeMirror.u16ClusterId = psClusterInstance->psClusterDefinition->u16ClusterEnum;

             if (pZPSevent->uEvent.sApsDataIndEvent.u8SrcAddrMode == E_ZCL_AM_SHORT)
             {

#ifdef PC_PLATFORM_BUILD
                 sZCL_CallBackEvent.uMessage.sReportAttributeMirror.u64RemoteIeeeAddress  = IEEE_SRC_ADD;
#else
                 // Find out IEEE address from the received Short address
                 sZCL_CallBackEvent.uMessage.sReportAttributeMirror.u64RemoteIeeeAddress = ZPS_u64NwkNibFindExtAddr((void *)ZPS_pvNwkGetHandle(), pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr);
#endif
             }
             else
             {
                sZCL_CallBackEvent.uMessage.sReportAttributeMirror.u64RemoteIeeeAddress = (uint64) pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u64Addr;
             }

             sZCL_CallBackEvent.uMessage.sReportAttributeMirror.eStatus = E_ZCL_ATTR_REPORT_ERR;

             psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

             if ((sZCL_CallBackEvent.uMessage.sReportAttributeMirror.eStatus == E_ZCL_ATTR_REPORT_ERR) ||
                     (sZCL_CallBackEvent.uMessage.sReportAttributeMirror.eStatus == E_ZCL_ATTR_REPORT_EP_MISMATCH) ||
                     (sZCL_CallBackEvent.uMessage.sReportAttributeMirror.eStatus == E_ZCL_ATTR_REPORT_ADDR_MISMATCH))
             {
                 eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_NOT_AUTHORIZED);
                 return;
             }
        }

        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_INDIVIDUAL_ATTRIBUTE;
    }

    // parse the message whilst checking for malformed messages
    while((u16payloadSize-u16inputOffset > 0) && (sZCL_CallBackEvent.eZCL_Status != E_ZCL_ERR_MALFORMED_MESSAGE))
    {
    	u16Length =  0;
		ZNC_BUF_U8_UPD  ( &au8LinkTxBuffer [0],sZCL_CallBackEvent.eZCL_Status,         u16Length );
		//vSL_WriteMessage ( 0x6644, u16Length,au8LinkTxBuffer,0);
		u16Length =  0;
		ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [0],u16inputOffset,         u16Length );
		//vSL_WriteMessage ( 0x6644, u16Length,u16inputOffset,0);
        // read the attribute record from the message
        // read attribute Id
        u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_ATTRIBUTE_ID,
                &sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.u16AttributeEnum);

        // For report attribute make sure the status is set to SUCCESS before callback
        sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeStatus = E_ZCL_CMDS_SUCCESS;
                
        if(sZCL_HeaderParams.u8CommandIdentifier== E_ZCL_READ_ATTRIBUTES_RESPONSE)
        {
            // read and check status
            u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8,
                    &sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeStatus);
        }

        // unknown for now
        sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType = E_ZCL_UNKNOWN;

        // null data and status pointers for now
        sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.pvAttributeData = NULL;

        if((sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeStatus ==E_ZCL_CMDS_SUCCESS) ||
                (sZCL_HeaderParams.u8CommandIdentifier == E_ZCL_REPORT_ATTRIBUTES))
        {

            // parse the attibute record further
            u16inputOffset +=u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8,
                    &sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType);
            // read the attribute data type
            if(eZCL_GetAttributeTypeSizeFromBuffer(sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType,
                    pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,u16inputOffset, &u16typeSize)!=E_ZCL_SUCCESS)
            {

                if(u16typeSize==0)
                {
                    // we have no idea how to locate the next attribute, so abort
                    sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_MALFORMED_MESSAGE;
                }

            }

           switch(sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType)
           {
               case(E_ZCL_LOSTRING):
               case(E_ZCL_LCSTRING):
               case(E_ZCL_OSTRING):
               case(E_ZCL_CSTRING):
               //RAJOUT FRED GESTION DU TYPE STRUCTURE XIAOMI ATTR 0XFF02
               case(E_ZCL_STRUCT):
               {
                   uint16                     u16stringDataLength;
                   uint16                     u16stringDataLengthField;
                   uint8                     *pu8stringData;
                 //  uint8                     u8stringLengthPosition;

                  /* if(eZCL_GetAttributeTypeSizeFromBuffer(sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType,
                                                          pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                                                          u16inputOffset,
                                                          &u16typeSize)!= E_ZCL_SUCCESS)
                   {
                       sZCL_CallBackEvent.eZCL_Status  = E_ZCL_FAIL;
                   }*/
                   u16typeSize = u16ZCL_GetStringAttributeTypeSizeFromBuffer(
                           sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType,
                                           &u16stringDataLength,
                                           &u16stringDataLengthField,
                                           &pu8stringData,
                                           (uint8 *)(PDUM_pvAPduInstanceGetPayload(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst)) + u16inputOffset);

                   if((sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType ==E_ZCL_OSTRING ) ||
                           (sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType ==E_ZCL_CSTRING))
                   {
                       uAttributeVal.sStrData.u8Length = (uint8 )u16stringDataLength;
                       uAttributeVal.sStrData.pu8Data = pu8stringData;
                   }
                   //RAJOUT FRED GESTION DU TYPE STRUCTURE XIAOMI ATTR 0xFF02
                   else if ((sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType==E_ZCL_STRUCT) && (sZCL_HeaderParams.u16ManufacturerCode == 0x1234))
				   {

                	     uAttributeVal.sStrData.u8Length =19;
                	     uAttributeVal.sStrData.pu8Data = pu8stringData;
						 sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType=E_ZCL_CSTRING;

					}
                   else
                   {
                       uAttributeVal.sLString.u16Length = u16stringDataLength;
                       uAttributeVal.sLString.pu8Data = pu8stringData;
                   }
               }
               break;
               default:
               {
                    u16ZCL_APduInstanceReadNBO(
                             pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                             u16inputOffset,
                             sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType,
                             &(uAttributeVal.sKeyData.au8Key[0]));
               }
               break;
           }
           sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.pvAttributeData = (void *)&uAttributeVal;

           // step over the attribute - the error flags will determine whether we go round the loop again
           u16inputOffset += u16typeSize;
        }

        // call user for every attribute
        psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
    }

    // re-use last attribute generated structure for message but indicate command is complete, last attribute
    // will get 2 callbacks effectively
    sZCL_CallBackEvent.eEventType = E_ZCL_CBET_READ_ATTRIBUTES_RESPONSE;
    if(sZCL_HeaderParams.u8CommandIdentifier == E_ZCL_REPORT_ATTRIBUTES)
    {
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_ATTRIBUTES;
    }

    psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

    if(sZCL_CallBackEvent.eZCL_Status != E_ZCL_SUCCESS)
    {
        // early termination send default response indicating error
        eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
        // free buffer in return
    }
    else
    {
        // incoming message is now parsed ok - send the default OK, if required
        eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SUCCESS);
    }

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
