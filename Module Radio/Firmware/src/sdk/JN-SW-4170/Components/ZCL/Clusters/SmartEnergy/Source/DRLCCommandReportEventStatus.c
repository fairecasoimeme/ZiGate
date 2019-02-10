/****************************************************************************
 *
 * MODULE:             Zigbee Demand Response And Load Control Cluster
 *
 * COMPONENT:          $RCSfile $
 *
 * AUTHOR:             Wayne Ellis
 *
 * DESCRIPTION:
 * Report Event Status Message Code
 *
 * $HeadURL: $
 *
 * $Revision: $
 *
 * $LastChangedBy: $
 *
 * $LastChangedDate: $
 *
 * $Id: $
 *
 *
 ****************************************************************************
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5164,
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
#include "zcl.h"
#include "zcl_customcommand.h"
#include "DRLC.h"
#include "DRLC_internal.h"
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
PRIVATE teSE_DRLCStatus eSE_DRLCReportEventStatusSend(
                    tsZCL_ClusterInstance      *psClusterInstance,
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address              *psDestinationAddress,
                    tsSE_DRLCReportEvent       *psReportEvent);

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
 ** NAME:       eSE_DRLCGenerateReportEventStatusMessage
 **
 ** DESCRIPTION:
 ** Generate a Report Event Status Message
 **
 ** PARAMETERS:               Name                      Usage
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 ** tsSE_DRLCReportEvent     *psReportEvent             Report Event Structure
 **
 ** RETURN:
 ** teSE_DRLCStatus
 **
 ****************************************************************************/

PUBLIC  teSE_DRLCStatus eSE_DRLCGenerateReportEventStatusMessage(
                    tsZCL_ClusterInstance       *psClusterInstance,
                    tsSE_DRLCReportEvent        *psReportEvent)
{

    tsZCL_Address sZCL_Address;
    tsDRLC_Common *psDRLC_Common;

    #ifdef STRICT_PARAM_CHECK
        // parameter checks
        if((psClusterInstance == NULL) || 
            (psReportEvent == NULL))
        {
            return(E_ZCL_ERR_PARAMETER_NULL);
        }
    #endif

    // initialise pointer
    psDRLC_Common = &((tsSE_DRLCCustomDataStructure *)psClusterInstance->pvEndPointCustomStructPtr)->sDRLC_Common;

    psReportEvent->u32EventStatusTime = u32ZCL_GetUTCTime();
#ifdef SE_MESSAGE_SIGNING
    psReportEvent->u8SignatureType = SE_DRLC_SIGNATURE_TYPE_ECDSA;
#else
    psReportEvent->u8SignatureType = SE_DRLC_NO_SIGNATURE;
#endif

    // build address structure
    eZCL_BuildClientTransmitAddressStructure(&sZCL_Address, &psDRLC_Common->sReceiveEventAddress);

    // issue publish price
    return eSE_DRLCReportEventStatusSend(
                    psClusterInstance,
                    psDRLC_Common->sReceiveEventAddress.u8DstEndpoint,
                    psDRLC_Common->sReceiveEventAddress.u8SrcEndpoint,
                    &sZCL_Address,
                    psReportEvent);

}

/****************************************************************************
 **
 ** NAME:       eSE_DRLCReportEventStatusSend
 **
 ** DESCRIPTION:
 ** Sends Report Event Status Cmd
 **
 ** PARAMETERS:                 Name                            Usage
 ** tsZCL_ClusterInstance       *psClusterInstance              Cluster Instance Structure
 ** uint8                       u8SourceEndPointId              Source EP Id
 ** uint8                       u8DestinationEndPointId         Destination EP Id
 ** tsZCL_Address               *psDestinationAddress           Destination Address
 ** tsSE_DRLCReportEvent        *psReportEvent                  Report Event Structure
 **
 ** RETURN:
 ** teSE_DRLCStatus
 **
 ****************************************************************************/

PRIVATE  teSE_DRLCStatus eSE_DRLCReportEventStatusSend(
                    tsZCL_ClusterInstance       *psClusterInstance,
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    tsSE_DRLCReportEvent        *psReportEvent)
{
    uint8 u8TransactionSequenceNumber;

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
    {1,     E_ZCL_UINT32,       &psReportEvent->u32IssuerId},
    {1,     E_ZCL_UINT8,        &psReportEvent->u8EventStatus},
    {1,     E_ZCL_UINT32,       &psReportEvent->u32EventStatusTime},
    {1,     E_ZCL_UINT8,        &psReportEvent->u8CriticalityLevelApplied},
    {1,     E_ZCL_UINT16,       &psReportEvent->u16CoolingTemperatureSetPointApplied},
    {1,     E_ZCL_UINT16,       &psReportEvent->u16HeatingTemperatureSetPointApplied},
    {1,     E_ZCL_UINT8,        &psReportEvent->u8AverageLoadAdjustmentPercentageApplied},
    {1,     E_ZCL_UINT8,        &psReportEvent->u8DutyCycleApplied},
    {1,     E_ZCL_UINT8,        &psReportEvent->u8EventControl},
    {1,     E_ZCL_UINT8,        &psReportEvent->u8SignatureType},
#ifdef SE_MESSAGE_SIGNING    
    {1,     E_ZCL_SIGNATURE,    psReportEvent->sSignature.au8data},
#endif    
                                              };

    /*u8TransactionSequenceNumber = u8GetTransactionSequenceNumber();   FB lpsw1904*/

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                              u8DestinationEndPointId,
                              psDestinationAddress,
                              SE_CLUSTER_ID_DEMAND_RESPONSE_AND_LOAD_CONTROL,
                              FALSE,
                              SE_DRLC_REPORT_EVENT_STATUS,
                              &u8TransactionSequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}

/****************************************************************************
 **
 ** NAME:       eSE_DRLCReportEventStatusReceive
 **
 ** DESCRIPTION:
 ** Gets Report Event Command Field Values
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent            *pZPSevent                     Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition          EP structure
 ** tsSE_DRLCReportEvent     *psReportEvent                 Report Event Structure
 ** uint8                    *pu8TransactionSequenceNumber  Sequence number Pointer
 **
 ** RETURN:
 ** teSE_DRLCStatus
 **
 ****************************************************************************/

PUBLIC  teSE_DRLCStatus eSE_DRLCReportEventStatusReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsSE_DRLCReportEvent        *psReportEvent,
                    uint8                       *pu8TransactionSequenceNumber)
{

    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
            {1, &u16ActualQuantity, E_ZCL_UINT32,       &psReportEvent->u32IssuerId},
            {1, &u16ActualQuantity, E_ZCL_UINT8,        &psReportEvent->u8EventStatus},
            {1, &u16ActualQuantity, E_ZCL_UINT32,       &psReportEvent->u32EventStatusTime},
            {1, &u16ActualQuantity, E_ZCL_UINT8,        &psReportEvent->u8CriticalityLevelApplied},
            {1, &u16ActualQuantity, E_ZCL_UINT16,       &psReportEvent->u16CoolingTemperatureSetPointApplied},
            {1, &u16ActualQuantity, E_ZCL_UINT16,       &psReportEvent->u16HeatingTemperatureSetPointApplied},
            {1, &u16ActualQuantity, E_ZCL_UINT8,        &psReportEvent->u8AverageLoadAdjustmentPercentageApplied},
            {1, &u16ActualQuantity, E_ZCL_UINT8,        &psReportEvent->u8DutyCycleApplied},
            {1, &u16ActualQuantity, E_ZCL_UINT8,        &psReportEvent->u8EventControl},
            {1, &u16ActualQuantity, E_ZCL_UINT8,        &psReportEvent->u8SignatureType},
            {1, &u16ActualQuantity, E_ZCL_SIGNATURE,    psReportEvent->sSignature.au8data},
                                                };
   
    switch(eZCL_CustomCommandDRLCReceive(pZPSevent,
                                 psEndPointDefinition,
                                 pu8TransactionSequenceNumber,
                                 asPayloadDefinition,
                                 sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                 E_ZCL_ACCEPT_EXACT))
    {
    case E_ZCL_ERR_SIGNATURE_VERIFY_FAILED:
        if(SE_DRLC_NO_SIGNATURE == psReportEvent->u8SignatureType)
        {
            psReportEvent->bSignatureVerified = TRUE;
        }
        else
        {
            psReportEvent->bSignatureVerified = FALSE;
        }
        return(E_ZCL_SUCCESS);

    case E_ZCL_SUCCESS:
        psReportEvent->bSignatureVerified = TRUE;
        return(E_ZCL_SUCCESS);

    default:
        psReportEvent->bSignatureVerified = FALSE;
        break;

    }

    return E_ZCL_FAIL;

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
