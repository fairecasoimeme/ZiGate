/*****************************************************************************
 *
 * MODULE:             Smart Energy
 *
 * COMPONENT:          Configure Reporting
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:       Send Report Configure Command
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy: we1 $
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
 ** NAME:       eZCL_SendConfigureReportingCommand
 **
 ** DESCRIPTION:
 ** Sends a Report Configure Command
 **
 ** PARAMETERS:      Name                           Usage
 ** uint8            u8SourceEndPointId             Source EP Id
 ** uint8            u8DestinationEndPointId        Destination EP Id
 ** uint16           u16ClusterId                   Cluster Id
 ** bool_t           bDirectionIsServerToClient     Direction
 ** tsZCL_Address   *psDestinationAddress           Destination Address
 ** uint8           *pu8TransactionSequenceNumber   Sequence number Pointer
 ** uint8            u8NumberOfAttributesInRequest  No. Attributes in Request
 ** bool_t           bIsManufacturerSpecific        Attribute manufacturer specific
 ** uint16           u16ManufacturerCode            Manufacturer code
 ** tsZCL_AttributeReportingConfigurationRecord    *psAttributeReportingConfigurationRecord
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eZCL_SendConfigureReportingCommand(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    uint16                      u16ClusterId,
                    bool_t                      bDirectionIsServerToClient,
                    tsZCL_Address              *psDestinationAddress,
                    uint8                      *pu8TransactionSequenceNumber,
                    uint8                       u8NumberOfAttributesInRequest,
                    bool_t                      bIsManufacturerSpecific,
                    uint16                      u16ManufacturerCode,
                    tsZCL_AttributeReportingConfigurationRecord     *psAttributeReportingConfigurationRecord)
{

    int i;
    uint16 u16offset;
    teZCL_Status eReturnValue;
    tsZCL_EndPointDefinition    *psZCL_EndPointDefinition;
    PDUM_thAPduInstance myPDUM_thAPduInstance;
    uint16 u16payloadSize = 0;
    void *pvReportableChange;
    uint8 u8typeSize;

    // parameter checks
	#ifdef STRICT_PARAM_CHECK
        if((psDestinationAddress == NULL) || (pu8TransactionSequenceNumber == NULL) || (psAttributeReportingConfigurationRecord == NULL))
        {
            return(E_ZCL_ERR_PARAMETER_NULL);
        }


        if(u8NumberOfAttributesInRequest == 0)
        {
            return(E_ZCL_ERR_ATTRIBUTES_0);
        }
    #endif
    // check whether default response to be requested
    eReturnValue = eZCL_SearchForEPentryAndCheckManufacturerId(u8SourceEndPointId, bIsManufacturerSpecific, u16ManufacturerCode, &psZCL_EndPointDefinition);
    if(eReturnValue != E_ZCL_SUCCESS)
    {
        return(eReturnValue);
    }

    // check the attributes validity
    for(i=0; i<u8NumberOfAttributesInRequest; i++)
    {
        // add rest of structure
        if(psAttributeReportingConfigurationRecord[i].u8DirectionIsReceived==0)
        {
            u8typeSize = 0;
            u16payloadSize += 1 + 2 + 1 + 2 + 2;
            if(eZCL_DoesAttributeHaveReportableChange(psAttributeReportingConfigurationRecord[i].eAttributeDataType)==E_ZCL_SUCCESS)
            {
                eZCL_GetAttributeTypeSize(psAttributeReportingConfigurationRecord[i].eAttributeDataType, &u8typeSize);
                u16payloadSize += u8typeSize;
            }
        }
        else
        {
            u16payloadSize += 1 + 2 + 2;
        }
    }

    // get buffer
    myPDUM_thAPduInstance = hZCL_AllocateAPduInstance();

    if(myPDUM_thAPduInstance == PDUM_INVALID_HANDLE)
    {
        return(E_ZCL_ERR_ZBUFFER_FAIL);
    }

    // handle sequence number pass present value back to user
    *pu8TransactionSequenceNumber = u8GetTransactionSequenceNumber();

    // write command header
    u16offset = u16ZCL_WriteCommandHeader(myPDUM_thAPduInstance,
                                       eFRAME_TYPE_COMMAND_ACTS_ACCROSS_ENTIRE_PROFILE,
                                       bIsManufacturerSpecific,
                                       u16ManufacturerCode,
                                       bDirectionIsServerToClient,
                                       psZCL_EndPointDefinition->bDisableDefaultResponse,
                                       *pu8TransactionSequenceNumber,
                                       E_ZCL_CONFIGURE_REPORTING);

    u16payloadSize += u16offset;
        // check buffer size
    if(PDUM_u16APduGetSize(psZCL_Common->hZCL_APdu) < u16payloadSize)
    {
        // free buffer and return
        PDUM_eAPduFreeAPduInstance(myPDUM_thAPduInstance);
        return(E_ZCL_ERR_ZBUFFER_FAIL);
    }

    // Build the command
    for(i=0; i<u8NumberOfAttributesInRequest; i++)
    {
        // write payload, attribute at a time
        u16offset += u16ZCL_APduInstanceWriteNBO(
        myPDUM_thAPduInstance, u16offset, E_ZCL_BOOL, &psAttributeReportingConfigurationRecord[i].u8DirectionIsReceived);
        u16offset += u16ZCL_APduInstanceWriteNBO(
        myPDUM_thAPduInstance, u16offset, E_ZCL_UINT16, &psAttributeReportingConfigurationRecord[i].u16AttributeEnum);

        if(psAttributeReportingConfigurationRecord[i].u8DirectionIsReceived==0)
        {
            // setting up a report
            u16offset += u16ZCL_APduInstanceWriteNBO(
            myPDUM_thAPduInstance, u16offset, E_ZCL_UINT8, &psAttributeReportingConfigurationRecord[i].eAttributeDataType);
            u16offset += u16ZCL_APduInstanceWriteNBO(
            myPDUM_thAPduInstance, u16offset, E_ZCL_UINT16, &psAttributeReportingConfigurationRecord[i].u16MinimumReportingInterval);
            u16offset += u16ZCL_APduInstanceWriteNBO(
            myPDUM_thAPduInstance, u16offset, E_ZCL_UINT16, &psAttributeReportingConfigurationRecord[i].u16MaximumReportingInterval);
            // add reportable change for relevant types
            if(eZCL_DoesAttributeHaveReportableChange(psAttributeReportingConfigurationRecord[i].eAttributeDataType)==E_ZCL_SUCCESS)
            {
                // get length change value ptr
                eZCL_GetAttributeReportableEntry(
                &pvReportableChange, psAttributeReportingConfigurationRecord[i].eAttributeDataType, &psAttributeReportingConfigurationRecord[i].uAttributeReportableChange);
                // write in variable length change value
                u16offset += u16ZCL_APduInstanceWriteNBO(
                myPDUM_thAPduInstance, u16offset, psAttributeReportingConfigurationRecord[i].eAttributeDataType, pvReportableChange);
            }
        }
        else
        {
            // report interval
            u16offset += u16ZCL_APduInstanceWriteNBO(
            myPDUM_thAPduInstance, u16offset, E_ZCL_UINT16, &psAttributeReportingConfigurationRecord[i].u16TimeoutPeriodField);
        }
    }

    // transmit the request
    if(eZCL_TransmitDataRequest(myPDUM_thAPduInstance,
                                u16offset,
                                u8SourceEndPointId,
                                u8DestinationEndPointId,
                                u16ClusterId,
                                psDestinationAddress) != E_ZCL_SUCCESS)
    {
        return(E_ZCL_ERR_ZTRANSMIT_FAIL);
    }

    return(E_ZCL_SUCCESS);
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
