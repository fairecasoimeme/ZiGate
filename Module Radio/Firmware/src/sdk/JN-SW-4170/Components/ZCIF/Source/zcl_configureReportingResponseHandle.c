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
* $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Source/zcl_readAttributesResponseHandle.c $
*
* $Revision: 20501 $
*
* $LastChangedBy: lmitch $
*
* $LastChangedDate: 2009-10-05 15:30:43 +0100 (Mon, 05 Oct 2009) $
*
* $Id: zcl_readAttributesResponseHandle.c 20501 2009-10-05 14:30:43Z lmitch $
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

/****************************************************************************
**
** NAME:       vZCL_HandleConfigureReportingResponse
**
** DESCRIPTION:
**
**
** PARAMETERS:               Name                      Usage
** ZPS_tsAfEvent            *pZPSevent                 Zigbee Stack Event
** tsZCL_EndPointDefinition *psZCL_EndPointDefinition  EP structure
** tsZCL_ClusterInstance    *psClusterInstance     Cluster structure
**
** RETURN:
** bool_t - TRUE delete input buffer, FALSE don't
**
****************************************************************************/

PUBLIC  void vZCL_HandleConfigureReportingResponse(
    ZPS_tsAfEvent              *pZPSevent,
    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
    tsZCL_ClusterInstance      *psClusterInstance)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent = {0};

    uint16 u16inputOffset;

    tsZCL_HeaderParams sZCL_HeaderParams;



    uint16 u16payloadSize;

    // fill in non-attribute specific values in callback event structure
    sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
    sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
    sZCL_CallBackEvent.pZPSevent = pZPSevent;
    sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_INDIVIDUAL_ATTRIBUTES_CONFIGURE_RESPONSE;
    sZCL_CallBackEvent.eZCL_Status = E_ZCL_SUCCESS;

    if (psClusterInstance == NULL)
    {
        sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_CLUSTER_NOT_FOUND;
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
    }

    // build command packet for response
    // read incoming request
    u16inputOffset = u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                                              &sZCL_HeaderParams);
    sZCL_CallBackEvent.u8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;

    if (sZCL_CallBackEvent.eEventType != E_ZCL_CBET_ERROR)
    {
        // parse the incoming message, read each attribute from the device and write into the outgoing buffer
        u16payloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);

        // fill in non-attribute specific values in callback event structure
        sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
        sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
        sZCL_CallBackEvent.pZPSevent = pZPSevent;
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_INDIVIDUAL_ATTRIBUTES_CONFIGURE_RESPONSE;
        sZCL_CallBackEvent.eZCL_Status = E_ZCL_SUCCESS;

        // check if response has any errors, if its equal to 1 then its a rip-roaring success and we have no
        // payload to check as the first byte will be a ststus byte of E_ZCL_CMDS_SUCCESS
        if(u16payloadSize-u16inputOffset > 1)
        {
            // parse the message whilst checking for malformed messages
            while((u16payloadSize-u16inputOffset > 0) && (sZCL_CallBackEvent.eZCL_Status == E_ZCL_SUCCESS))
            {
                // read the attribute report record from the message
                // read and check status
                u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &sZCL_CallBackEvent.uMessage.sReportingConfigurationResponse.u8Status);
                u16inputOffset += u16ZCL_APduInstanceReadNBO(
                    pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &sZCL_CallBackEvent.uMessage.sReportingConfigurationResponse.u8DirectionIsReceived);
                // read attribute Id
                u16inputOffset += u16ZCL_APduInstanceReadNBO(
                    pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_ATTRIBUTE_ID, &sZCL_CallBackEvent.uMessage.sReportingConfigurationResponse.u16AttributeEnum);

                // call user for every attribute
                if(sZCL_CallBackEvent.uMessage.sReportingConfigurationResponse.u8Status != E_ZCL_CMDS_SUCCESS)
                {
                    psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
                }

                // check for length error
                if((u16payloadSize-u16inputOffset !=0) && (u16payloadSize-u16inputOffset < 3))
                {
                    sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_MALFORMED_MESSAGE;
                }
            }
        }

        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_ATTRIBUTES_CONFIGURE_RESPONSE;
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
