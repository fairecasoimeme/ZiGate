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
 ** NAME:       vZCL_HandleReadReportingConfigurationCommand
 **
 ** DESCRIPTION:
 **
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent              *pZPSevent               Zigbee Stack Event
 ** tsZCL_EndPointDefinition *psZCL_EndPointDefinition  EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/

PUBLIC  void vZCL_HandleReadReportingConfigurationCommand(
                                             ZPS_tsAfEvent              *pZPSevent,
                                             tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                                             tsZCL_ClusterInstance      *psClusterInstance)
{
    int i;

    uint8 u8Status = E_ZCL_CMDS_SUCCESS;
    uint16 u16inputOffset, u16outputOffset = 0;

	tsZCL_HeaderParams sZCL_HeaderParams;

    uint8   u8NumberReportsInRequest;

    tsZCL_AttributeReportingConfigurationRecord    *psAttributeReportingRecord;

    bool_t bBufferAllocated = FALSE;
    bool_t bReportsWritten = FALSE;
    bool_t bBufferError = FALSE;
    bool_t bDontReReadInputMessage = FALSE;



    tsZCL_Address sZCL_Address;

    uint16 u16payloadSize;
    uint16 u16responseBufferSize;

    uint8 u8typeSize, u8SizeOfReportRecord;

    tsZCL_AttributeDefinition   *psAttributeDefinition;

    PDUM_thAPduInstance myPDUM_thAPduInstance = 0;

    void *pvReportableChange;

    uint16 u16attributeIndex;
    tsZCL_AttributeReportingConfigurationRecord    sAttributeReportingRecord;


    // build command packet for response
    // read incoming request
    u16inputOffset = u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                                              &sZCL_HeaderParams);


    // payload investigation
    u16payloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);
    // number of reports in request
    u8NumberReportsInRequest = (u16payloadSize-u16inputOffset)/3;
    // size sanity check
    if((u16payloadSize < u16inputOffset) || ((u16payloadSize-u16inputOffset)%3) || (u8NumberReportsInRequest==0))
    {
        // send response if possible/required
        eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
        return;
    }

    // build address structure
    eZCL_BuildTransmitAddressStructure(pZPSevent, &sZCL_Address);
    // size of outgoing buffer
    u16responseBufferSize = u16ZCL_GetTxPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr);

    // loop round the report list
    i=0;
    while(i<u8NumberReportsInRequest)
    {
        // Set status to success before checking each attribute
        u8Status = E_ZCL_CMDS_SUCCESS;
        // get report entry
        if(bDontReReadInputMessage==FALSE)
        {
            // record size is fixed if there is an error
            u8SizeOfReportRecord = 4;
            u16inputOffset += u16ZCL_APduInstanceReadNBO(
            pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &sAttributeReportingRecord.u8DirectionIsReceived);
            u16inputOffset += u16ZCL_APduInstanceReadNBO(
            pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT16, &sAttributeReportingRecord.u16AttributeEnum);

            // search for report entry
            if(eZCL_SearchForAttributeEntry(
               psZCL_EndPointDefinition->u8EndPointNumber,
               sAttributeReportingRecord.u16AttributeEnum,
               sZCL_HeaderParams.bManufacturerSpecific,
               sZCL_HeaderParams.bDirection,
               psClusterInstance,
               &psAttributeDefinition,
               &u16attributeIndex)== E_ZCL_SUCCESS)
            {
                if(eZCL_GetAttributeTypeSize(psAttributeDefinition->eAttributeDataType, &u8typeSize)!=E_ZCL_SUCCESS)
                {
                    // not supported
                    u8Status = E_ZCL_CMDS_UNSUPPORTED_ATTRIBUTE;
                }
                else
                {
                    // check valid type for report command
                    if((psAttributeDefinition->eAttributeDataType ==  E_ZCL_ARRAY)      ||
                       (psAttributeDefinition->eAttributeDataType ==  E_ZCL_STRUCT)     ||
                       (psAttributeDefinition->eAttributeDataType ==  E_ZCL_SET)        ||
                       (psAttributeDefinition->eAttributeDataType ==  E_ZCL_BAG)        ||
                       (psAttributeDefinition->eAttributeDataType ==  E_ZCL_UNKNOWN)
                       )
                    {
                        // not supported
                        u8Status = E_ZCL_CMDS_UNREPORTABLE_ATTRIBUTE;
                    }
                    else
                    {
                        // find report
                        if(eZCLFindReportEntryByAttributeIdAndDirection(
                            psZCL_EndPointDefinition->u8EndPointNumber,
                            psClusterInstance->psClusterDefinition->u16ClusterEnum,
                            sAttributeReportingRecord.u8DirectionIsReceived,
                            sAttributeReportingRecord.u16AttributeEnum,
                            &psAttributeReportingRecord) != E_ZCL_SUCCESS)
                        {
                            // not supported
                            u8Status = E_ZCL_CMDS_UNREPORTABLE_ATTRIBUTE;
                        }
                        else
                        {
                            // get size and check for overwrite
                            eZCL_CalculateSizeOfReportRecord(psAttributeReportingRecord, &u8SizeOfReportRecord);
                        }
                    }
                }
            }
            else
            {
                // not supported
                u8Status = E_ZCL_CMDS_UNSUPPORTED_ATTRIBUTE;
            }
        }

        if(bBufferAllocated==FALSE)
        {
            // get buffer to write the response in
            myPDUM_thAPduInstance = hZCL_AllocateAPduInstance();
            // no buffers - return. we can make this descision a bit more exotic using the incoming buffer to store the
            // outgoing command but for the moment we are implementing the KISS principle.
            if(myPDUM_thAPduInstance == PDUM_INVALID_HANDLE)
            {
                return;
            }
            bBufferAllocated = TRUE;
            // modify and write back
            u16outputOffset = u16ZCL_WriteCommandHeader(myPDUM_thAPduInstance,
                                               sZCL_HeaderParams.eFrameType,
                                               sZCL_HeaderParams.bManufacturerSpecific,
                                               sZCL_HeaderParams.u16ManufacturerCode,
                                               !sZCL_HeaderParams.bDirection,
                                               psZCL_EndPointDefinition->bDisableDefaultResponse,
                                               sZCL_HeaderParams.u8TransactionSequenceNumber,
                                               E_ZCL_READ_REPORTING_CONFIGURATION_RESPONSE);
        }


        // check if report will fit in buffer
        if((u8SizeOfReportRecord + u16outputOffset) > u16responseBufferSize)
        {
            bBufferAllocated = FALSE;

            if(bReportsWritten==TRUE)
            {
                 bReportsWritten = FALSE;
                // can't fit report in - transmit and continue
                if(eZCL_TransmitDataRequest(myPDUM_thAPduInstance,
                                    u16outputOffset,
                                    pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                                    pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,
                                    pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId,
                                    &sZCL_Address) != E_ZCL_SUCCESS)
                {
                    return;
                }
                // don't increment loop count we haven't processed any more reports just sent what we already had
                bDontReReadInputMessage=TRUE;
                continue;
            }
            else
            {
                // we are skrewed buffer(s) too small
                bBufferError=TRUE;
                break;
            }
        }

        // write in the first part of the response status/direction/AttributeId
        bReportsWritten=TRUE;
        u16outputOffset += u16ZCL_APduInstanceWriteNBO(
        myPDUM_thAPduInstance, u16outputOffset, E_ZCL_UINT8, &u8Status);
        u16outputOffset += u16ZCL_APduInstanceWriteNBO(
        myPDUM_thAPduInstance, u16outputOffset, E_ZCL_UINT8, &sAttributeReportingRecord.u8DirectionIsReceived);
        u16outputOffset += u16ZCL_APduInstanceWriteNBO(
        myPDUM_thAPduInstance, u16outputOffset, E_ZCL_UINT16, &sAttributeReportingRecord.u16AttributeEnum);

        // check if we are able to go on with the request
        if((u8Status == E_ZCL_CMDS_UNSUPPORTED_ATTRIBUTE) || (u8Status == E_ZCL_CMDS_UNREPORTABLE_ATTRIBUTE))
        {
            // we can - just skip the entry
            // increment loop
            i++;
            continue;
        }

        // at this point - all is well

        // write rest of record
        if(psAttributeReportingRecord->u8DirectionIsReceived==0)
        {
            u16outputOffset += u16ZCL_APduInstanceWriteNBO(
            myPDUM_thAPduInstance, u16outputOffset, E_ZCL_UINT8, &psAttributeReportingRecord->eAttributeDataType);
            u16outputOffset += u16ZCL_APduInstanceWriteNBO(
            myPDUM_thAPduInstance, u16outputOffset, E_ZCL_UINT16, &psAttributeReportingRecord->u16MinimumReportingInterval);
            u16outputOffset += u16ZCL_APduInstanceWriteNBO(
            myPDUM_thAPduInstance, u16outputOffset, E_ZCL_UINT16, &psAttributeReportingRecord->u16MaximumReportingInterval);
            if(eZCL_DoesAttributeHaveReportableChange(psAttributeDefinition->eAttributeDataType)== E_ZCL_SUCCESS)
            {
                // read reportable change into structure
                eZCL_GetAttributeReportableEntry(
                &pvReportableChange, psAttributeDefinition->eAttributeDataType, &psAttributeReportingRecord->uAttributeReportableChange);
                u16outputOffset += u16ZCL_APduInstanceWriteNBO(
                myPDUM_thAPduInstance, u16outputOffset, psAttributeDefinition->eAttributeDataType, pvReportableChange);
            }
        }
        else
        {
            u16outputOffset += u16ZCL_APduInstanceWriteNBO(
            myPDUM_thAPduInstance, u16outputOffset, E_ZCL_UINT16, &psAttributeReportingRecord->u16TimeoutPeriodField);
        }
        // increment loop
        i++;
    }

    // NTS testing Nov 09. Don't send a good default response here as we have a unicast response that is valid.

    // transmit
    if(bBufferError==TRUE)
    {
         // error buffer too small for 1 record free buffer and return
        eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SOFTWARE_FAILURE);
        // free buffer 
        PDUM_eAPduFreeAPduInstance(myPDUM_thAPduInstance);
    }

    // transmit request
    if(bBufferAllocated==TRUE)
    {
        eZCL_TransmitDataRequest(myPDUM_thAPduInstance,
                                        u16outputOffset,
                                        pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint,
                                        pZPSevent->uEvent.sApsDataIndEvent.u8SrcEndpoint,
                                        pZPSevent->uEvent.sApsDataIndEvent.u16ClusterId,
                                        &sZCL_Address);
    }
}

/****************************************************************************
 **
 ** NAME:       vZCL_CalculateSizeOfReportRecord
 **
 ** DESCRIPTION:
 **
 **
 ** PARAMETERS:               Name                      Usage
 ** tsZCL_AttributeReportingConfigurationRecord *psAttributeReportingConfigurationRecord,
 ** uint8                                       *pu8SizeOfReportRecord
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eZCL_CalculateSizeOfReportRecord(
                        tsZCL_AttributeReportingConfigurationRecord *psAttributeReportingConfigurationRecord,
                        uint8                                       *pu8SizeOfReportRecord)
{

    uint8 u8typeSize;

    if((psAttributeReportingConfigurationRecord==NULL) ||(pu8SizeOfReportRecord==NULL))
    {
        return(E_ZCL_ERR_PARAMETER_NULL);
    }

    *pu8SizeOfReportRecord = (1 + 1 + 2 + 2);
    if(psAttributeReportingConfigurationRecord->u8DirectionIsReceived==0)
    {
        *pu8SizeOfReportRecord = (1 + 1 + 2 + 1 + 2 + 2);
        // check size to see if the implementation supports the data type requested
        eZCL_GetAttributeTypeSize(psAttributeReportingConfigurationRecord->eAttributeDataType, &u8typeSize);
        if(eZCL_DoesAttributeHaveReportableChange(psAttributeReportingConfigurationRecord->eAttributeDataType) == E_ZCL_SUCCESS)
        {
            *pu8SizeOfReportRecord += u8typeSize;
        }
    }
    return(E_ZCL_SUCCESS);

}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
