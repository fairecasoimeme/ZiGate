/*****************************************************************************
 *
 * MODULE:             Price Cluster
 *
 * COMPONENT:          PriceCommandPublishCalorificValueReceive.c
 *
 * AUTHOR:             Ambuj Varshney
 *
 * DESCRIPTION:        Receive a publish price command
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/BlockTariff_BLG/ZCL/Clusters/SmartEnergy/Source/PriceCommandPublishPriceReceive.c $
 *
 * $Revision: 28938 $
 *
 * $LastChangedBy: nxp29740 $
 *
 * $LastChangedDate: 2011-02-02 17:42:49 +0530 (Wed, 02 Feb 2011) $
 *
 * $Id: PriceCommandPublishBlockPeriodReceive.c 28938 2011-02-02 12:12:49Z nxp29740 $
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

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"



#ifdef PRICE_CALORIFIC_VALUE

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
 ** NAME:       eSE_PublishBlockPeriodPriceReceive
 **
 ** DESCRIPTION:
 ** Receives the Publish Block Period command from ZCL.
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent            *pZPSevent                     Zigbee stack event structure
 ** tsSE_PricePublishBlockPeriodCmdPayload *psPublishBlockPeriodCmdPayload      Block Period Table record
 ** uint8                    *pu8TransactionSequenceNumber  Sequence number Pointer
 ** uint32                   *pu32CurrentTimeInMessage      Timestamp
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teSE_PriceStatus eSE_PublishCalorificValueReceive(
                            ZPS_tsAfEvent              *pZPSevent,
                            tsSE_PricePublishCalorificValueCmdPayload   *psPublishCalorificValueCmdPayload,
                            uint8                      *pu8TransactionSequenceNumber,
                            uint32                     *pu32CurrentTimeInMessage)
{

    uint16 u16ActualQuantity;

    tsZCL_RxPayloadItem asPayloadDefinition[] = {
                {1,&u16ActualQuantity, E_ZCL_UINT32,   &psPublishCalorificValueCmdPayload->u32IssuerEventId},
                {1,&u16ActualQuantity, E_ZCL_UINT32,   &psPublishCalorificValueCmdPayload->u32StartTime},
                {1,&u16ActualQuantity, E_ZCL_UINT32,   &psPublishCalorificValueCmdPayload->u32CalorificValue},
                {1,&u16ActualQuantity, E_ZCL_ENUM8,    &psPublishCalorificValueCmdPayload->e8CalorificValueUnit},
                {1,&u16ActualQuantity, E_ZCL_BMAP8,    &psPublishCalorificValueCmdPayload->b8CalorificValueTrailingDigit},
                };

    return eZCL_CustomCommandReceive(pZPSevent,
                                     pu8TransactionSequenceNumber,
                                     asPayloadDefinition,
                                     sizeof(asPayloadDefinition) / sizeof(tsZCL_RxPayloadItem),
                                     E_ZCL_ACCEPT_LESS);



}


/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif
