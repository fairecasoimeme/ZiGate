/*****************************************************************************
*
* MODULE:             Smart Energy
*
* COMPONENT:          zcl_readAttributesRequestHandle.c
*
* AUTHOR:             we1
*
* DESCRIPTION:       Receive Read Attributes Request
*
* $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Source/zcl_readAttributesRequestHandle.c $
*
* $Revision: 19719 $
*
* $LastChangedBy: we1 $
*
* $LastChangedDate: 2009-09-10 15:15:35 +0100 (Thu, 10 Sep 2009) $
*
* $Id: zcl_readAttributesRequestHandle.c 19719 2009-09-10 14:15:35Z we1 $
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
** NAME:       vZCL_HandleReadReportingConfigurationResponse
**
** DESCRIPTION:
**
**
** PARAMETERS:               Name                      Usage
** ZPS_tsAfEvent             *pZPSevent                Zigbee Stack Event
** tsZCL_EndPointDefinition *psZCL_EndPointDefinition  EP structure
** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
**
** RETURN:
** None
**
****************************************************************************/

PUBLIC  void vZCL_HandleReadReportingConfigurationResponse(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent;

    uint16 u16inputOffset;

	tsZCL_HeaderParams sZCL_HeaderParams;


    uint16 u16payloadSize;
    void *pvReportableChange;
    uint8 u8typeSize;

    tsZCL_AttributeReportingConfigurationRecord *psAttributeReportingConfigurationRecord;
    memset(&(sZCL_CallBackEvent), 0, sizeof(tsZCL_CallBackEvent));
    // set user callback
    sZCL_CallBackEvent.eZCL_Status = E_ZCL_SUCCESS;
    sZCL_CallBackEvent.pZPSevent = pZPSevent;
    sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
    sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_READ_INDIVIDUAL_ATTRIBUTE_CONFIGURATION_RESPONSE;
    sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
    sZCL_CallBackEvent.eZCL_Status = E_ZCL_SUCCESS;

    if (psClusterInstance == NULL)
    {
        sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_CLUSTER_NOT_FOUND;
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
    }

    // read incoming request
    u16inputOffset = u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                                              &sZCL_HeaderParams);





    if (sZCL_CallBackEvent.eEventType != E_ZCL_CBET_ERROR)
    {
        // M$
        sZCL_CallBackEvent.uMessage.sAttributeReportingConfigurationRecord.eAttributeDataType = 0;
        sZCL_CallBackEvent.uMessage.sAttributeReportingConfigurationResponse.eCommandStatus = 0;
        sZCL_CallBackEvent.u8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;

        // payload investigation
        u16payloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);
        // size sanity check
        if(u16payloadSize < u16inputOffset)
        {
            // send response if possible/required
            eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
            return;
        }

        // read attributes from the device

        // parse the incoming message, read each attribute from the device and write into the outgoing buffer

        psAttributeReportingConfigurationRecord =
            &sZCL_CallBackEvent.uMessage.sAttributeReportingConfigurationResponse.sAttributeReportingConfigurationRecord;

        // loop round the report list
        if((u16payloadSize-u16inputOffset) < 4)
        {
            sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_MALFORMED_MESSAGE;
        }

        while((u16payloadSize-u16inputOffset > 0) && (sZCL_CallBackEvent.eZCL_Status == E_ZCL_SUCCESS))
        {
            // get report entry
            u16inputOffset += u16ZCL_APduInstanceReadNBO(
                pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &sZCL_CallBackEvent.uMessage.sAttributeReportingConfigurationResponse.eCommandStatus);
            u16inputOffset += u16ZCL_APduInstanceReadNBO(
                pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &psAttributeReportingConfigurationRecord->u8DirectionIsReceived);
            u16inputOffset += u16ZCL_APduInstanceReadNBO(
                pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT16, &psAttributeReportingConfigurationRecord->u16AttributeEnum);

            if(sZCL_CallBackEvent.uMessage.sAttributeReportingConfigurationResponse.eCommandStatus != E_ZCL_CMDS_SUCCESS)
            {
                // call user
                psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
                continue;
            }

            if(sZCL_CallBackEvent.uMessage.sAttributeReportingConfigurationRecord.u8DirectionIsReceived==0)
            {
                if((u16payloadSize-u16inputOffset) < 5)
                {
                    sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_MALFORMED_MESSAGE;
                }
                // M$
                psAttributeReportingConfigurationRecord->eAttributeDataType=0;
                u16inputOffset += u16ZCL_APduInstanceReadNBO(
                    pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &psAttributeReportingConfigurationRecord->eAttributeDataType);
                //read reporting intervals
                u16inputOffset += u16ZCL_APduInstanceReadNBO(
                    pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT16, &psAttributeReportingConfigurationRecord->u16MinimumReportingInterval);
                u16inputOffset += u16ZCL_APduInstanceReadNBO(
                    pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT16, &psAttributeReportingConfigurationRecord->u16MaximumReportingInterval);
                if(eZCL_DoesAttributeHaveReportableChange(psAttributeReportingConfigurationRecord->eAttributeDataType)== E_ZCL_SUCCESS)
                {
                    // check type
                    if((eZCL_GetAttributeTypeSize(psAttributeReportingConfigurationRecord->eAttributeDataType, &u8typeSize) !=E_ZCL_SUCCESS) ||
                    ((u16payloadSize-u16inputOffset) < u8typeSize))
                    {
                        // not supported
                        sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_MALFORMED_MESSAGE;
                    }
                    // read reportable change into structure
                     eZCL_GetAttributeReportableEntry(
                        &pvReportableChange, psAttributeReportingConfigurationRecord->eAttributeDataType, &psAttributeReportingConfigurationRecord->uAttributeReportableChange);
                    	u16inputOffset += u16ZCL_APduInstanceReadNBO(
                        pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, psAttributeReportingConfigurationRecord->eAttributeDataType, pvReportableChange);
                }else{
                    // check type
                    if((eZCL_GetAttributeTypeSize(psAttributeReportingConfigurationRecord->eAttributeDataType, &u8typeSize) !=E_ZCL_SUCCESS))
                    {
                        // not supported
                        sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_MALFORMED_MESSAGE;
                    }
                }
            }
            else
            {
                if((u16payloadSize-u16inputOffset) < 1)
                {
                    sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_MALFORMED_MESSAGE;
                }
                u16inputOffset += u16ZCL_APduInstanceReadNBO(
                    pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT16, &psAttributeReportingConfigurationRecord->u16TimeoutPeriodField);
            }

            // call user
            psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
        }

        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_READ_ATTRIBUTE_CONFIGURATION_RESPONSE;
    }
    psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

    // transmit
    if(sZCL_CallBackEvent.eZCL_Status != E_ZCL_SUCCESS)
    {
        eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
    }

    // incoming message is now parsed ok - send the default OK, if required
    eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SUCCESS);

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
