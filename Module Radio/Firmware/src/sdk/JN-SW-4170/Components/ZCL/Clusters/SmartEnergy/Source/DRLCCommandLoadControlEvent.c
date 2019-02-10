/****************************************************************************
 *
 * MODULE:             Zigbee Demand Response And Load Control Cluster
 *
 * COMPONENT:          $RCSfile $
 *
 * AUTHOR:             Wayne Ellis
 *
 * DESCRIPTION:
 * Load control event code
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
 ** NAME:       eSE_LoadControlEventSend
 **
 ** DESCRIPTION:
 ** Sends Load Control Event Command
 **
 ** PARAMETERS:                 Name                            Usage
 ** uint8                       u8SourceEndPointId              Source EP Id
 ** uint8                       u8DestinationEndPointId         Destination EP Id
 ** tsZCL_Address               *psDestinationAddress           Destination Address
 ** tsSE_DRLCLoadControlEvent   *psLoadControlEvent             Load Control Event Structure
 ** bool_t                      bSendWithTimeNow                send with zero in time slot
 ** uint8                       *pu8TransactionSequenceNumber   Sequence number Pointer
 **
 ** RETURN:
 ** teSE_DRLCStatus
 **
 ****************************************************************************/

PUBLIC  teSE_DRLCStatus eSE_DRLCLoadControlEventSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    tsSE_DRLCLoadControlEvent   *psLoadControlEvent,
                    bool_t                      bSendWithTimeNow,
                    uint8                       *pu8TransactionSequenceNumber)
{

    uint32 u32StartTime;

    tsZCL_TxPayloadItem asPayloadDefinition[] = {
    {1, E_ZCL_UINT32,   &psLoadControlEvent->u32IssuerId},
    {1, E_ZCL_UINT16,   &psLoadControlEvent->u16DeviceClass},
    {1, E_ZCL_UINT8,    &psLoadControlEvent->u8UtilityEnrolmentGroup},
    {1, E_ZCL_UINT32,   &u32StartTime},
    {1, E_ZCL_UINT16,   &psLoadControlEvent->u16DurationInMinutes},
    {1, E_ZCL_UINT8,    &psLoadControlEvent->u8CriticalityLevel},
    {1, E_ZCL_UINT8,    &psLoadControlEvent->u8CoolingTemperatureOffset},
    {1, E_ZCL_UINT8,    &psLoadControlEvent->u8HeatingTemperatureOffset},
    {1, E_ZCL_UINT16,   &psLoadControlEvent->u16CoolingTemperatureSetPoint},
    {1, E_ZCL_UINT16,   &psLoadControlEvent->u16HeatingTemperatureSetPoint},
    {1, E_ZCL_UINT8,    &psLoadControlEvent->u8AverageLoadAdjustmentSetPoint},
    {1, E_ZCL_UINT8,    &psLoadControlEvent->u8DutyCycle},
    {1, E_ZCL_UINT8,    &psLoadControlEvent->u8EventControl},
                                              };

    /*if(bSendWithTimeNow==TRUE)
    {
        psLoadControlEvent->u32StartTime = 0;
    }*/

    if(bSendWithTimeNow)
    {
        u32StartTime = 0;
    }
    else
    {
        u32StartTime = psLoadControlEvent->u32StartTime;
    }

    return eZCL_CustomCommandSend(u8SourceEndPointId,
                              u8DestinationEndPointId,
                              psDestinationAddress,
                              SE_CLUSTER_ID_DEMAND_RESPONSE_AND_LOAD_CONTROL,
                              TRUE,
                              SE_DRLC_LOAD_CONTROL_EVENT,
                              pu8TransactionSequenceNumber,
                              asPayloadDefinition,
                              FALSE,
                              0,
                              sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));
}

/****************************************************************************
 **
 ** NAME:       eSE_DRLCLoadControlEventReceive
 **
 ** DESCRIPTION:
 ** Gets Load Control Event Command Field Values
 **
 ** PARAMETERS:                 Name                            Usage
 ** ZPS_tsAfEvent               *pZPSevent                      Zigbee stack event structure
 ** tsZCL_EndPointDefinition    *psEndPointDefinition           EP structure
 ** tsSE_DRLCLoadControlEvent   *psLoadControlEvent             Load Control Event Structure
 ** uint8                       *pu8TransactionSequenceNumber   Sequence number Pointer
 **
 ** RETURN:
 ** teSE_DRLCStatus
 **
 ****************************************************************************/

PUBLIC  teSE_DRLCStatus eSE_DRLCLoadControlEventReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsSE_DRLCLoadControlEvent   *psLoadControlEvent,
                    uint8                       *pu8TransactionSequenceNumber)
{

    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
            {1, &u16ActualQuantity, E_ZCL_UINT32,   &psLoadControlEvent->u32IssuerId},
            {1, &u16ActualQuantity, E_ZCL_UINT16,   &psLoadControlEvent->u16DeviceClass},
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psLoadControlEvent->u8UtilityEnrolmentGroup},
            {1, &u16ActualQuantity, E_ZCL_UINT32,   &psLoadControlEvent->u32StartTime},
            {1, &u16ActualQuantity, E_ZCL_UINT16,   &psLoadControlEvent->u16DurationInMinutes},
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psLoadControlEvent->u8CriticalityLevel},
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psLoadControlEvent->u8CoolingTemperatureOffset},
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psLoadControlEvent->u8HeatingTemperatureOffset},
            {1, &u16ActualQuantity, E_ZCL_UINT16,   &psLoadControlEvent->u16CoolingTemperatureSetPoint},
            {1, &u16ActualQuantity, E_ZCL_UINT16,   &psLoadControlEvent->u16HeatingTemperatureSetPoint},
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psLoadControlEvent->u8AverageLoadAdjustmentSetPoint},
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psLoadControlEvent->u8DutyCycle},
            {1, &u16ActualQuantity, E_ZCL_UINT8,    &psLoadControlEvent->u8EventControl},
                                                };

    if(eZCL_CustomCommandDRLCReceive(pZPSevent,
                                 psEndPointDefinition,
                                 pu8TransactionSequenceNumber,
                                 asPayloadDefinition,
                                 sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                 E_ZCL_DISABLE_DEFAULT_RESPONSE) != E_ZCL_SUCCESS)
    {
        return E_ZCL_FAIL;
    }

    return E_ZCL_SUCCESS;

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
