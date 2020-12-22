/*****************************************************************************
 *
 * MODULE:             Price Cluster
 *
 * COMPONENT:          PriceCommandGetCalorificValue
 *
 * AUTHOR:             Ambuj Varshney
 *
 * DESCRIPTION:        Send and Receive functions
 *
 *
 ****************************************************************************
 *
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

#include "zcl.h"
#include "zcl_customcommand.h"

#include "Price.h"
#include "Price_internal.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"



#ifdef PRICE_CALORIFIC_VALUE

/****************************************************************************
 **
 ** NAME:       eSE_PriceGetCalorificValueSend
 **
 ** DESCRIPTION:
 ** Sends Get Current Price Request
 **
 ** PARAMETERS:         Name                           Usage
 ** uint8               u8SourceEndPointId             Source EP Id
 ** uint8               u8DestinationEndPointId        Destination EP Id
 ** tsZCL_Address      *psDestinationAddress           Destination Address
 ** uint8              *pu8TransactionSequenceNumber   Sequence number Pointer
 ** uint8                u8numberofEvents                Number of Events
 **
 ** RETURN:
 ** teSE_PriceStatus
 **
 ****************************************************************************/

PUBLIC  teSE_PriceStatus eSE_PriceGetCalorificValueSend(
                    uint8                      u8SourceEndPointId,
                    uint8                      u8DestinationEndPointId,
                    tsZCL_Address              *psDestinationAddress,
                    uint8                      *pu8TransactionSequenceNumber,
                    uint32                       u32StartTime,
                    uint8                       u8NumberOfEvents)
{

     

    tsZCL_TxPayloadItem asPayloadDefinition[] = {   {1, E_ZCL_UINT32, &u32StartTime},
                                                    {1, E_ZCL_UINT8,  &u8NumberOfEvents}
                                                };


    return eZCL_CustomCommandSend(u8SourceEndPointId,
                                  u8DestinationEndPointId,
                                  psDestinationAddress,
                                  SE_CLUSTER_ID_PRICE,
                                  FALSE,
                                  E_SE_GET_CALORIFIC_VALUE,
                                  pu8TransactionSequenceNumber,
                                  asPayloadDefinition,
                                  FALSE,
                                  0,
                                  sizeof(asPayloadDefinition) / sizeof(tsZCL_TxPayloadItem));

}

/****************************************************************************
 **
 ** NAME:       eSE_GetCalorificValueReceive
 **
 ** DESCRIPTION:
 ** Handles Get Current Price Request
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent              *pZPSevent                   Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition          EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 ** uint8                    *pu8TransactionSequenceNumber  Sequence number Pointer
 ** teSE_PriceCommandOptions  *pePriceCommandOptions        Response option
 **
 ** RETURN:
 ** teSE_PriceStatus
 **
 ****************************************************************************/

PUBLIC  teSE_PriceStatus eSE_GetCalorificValueReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    uint32                        *pu32StartTime,
                    uint8                        *pu8NumberOfEvents)
{
 
    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
            {1, &u16ActualQuantity, E_ZCL_UINT32, pu32StartTime},
            {1, &u16ActualQuantity, E_ZCL_UINT8,  pu8NumberOfEvents}
                                                };

    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     asPayloadDefinition,
                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                     E_ZCL_DISABLE_DEFAULT_RESPONSE);

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
#endif
