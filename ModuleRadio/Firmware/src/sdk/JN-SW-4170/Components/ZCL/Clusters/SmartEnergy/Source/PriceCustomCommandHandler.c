/*****************************************************************************
 *
 * MODULE:             Price Cluster
 *
 * COMPONENT:          PriceCustomCommandHandler.c
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:        Event handler for price cluster custom commands
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/SmartEnergy/Source/PriceCustomCommandHandler.c $
 *
 * $Revision: 85802 $
 *
 * $LastChangedBy: nxp29757 $
 *
 * $LastChangedDate: 2016-12-14 12:23:26 +0100 (Wed, 14 Dec 2016) $
 *
 * $Id: PriceCustomCommandHandler.c 85802 2016-12-14 11:23:26Z nxp29757 $
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
#include <string.h>

#include "zcl.h"
#include "zcl_customcommand.h"

#include "Price.h"
#include "Price_internal.h"

#include "zcl_options.h"



/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#if defined(CLD_PRICE) && !defined(PRICE_SERVER) && !defined(PRICE_CLIENT)
#error You Must Have either PRICE_SERVER and/or PRICE_CLIENT defined in zcl_options.h
#endif

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
 ** NAME:       eSE_PriceCommandHandler
 **
 ** DESCRIPTION:
 ** Handles Price Cluster custom commands
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent              *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eSE_PriceCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance)
{

	tsZCL_HeaderParams sZCL_HeaderParams;
    // further error checking can only be done once we have interrogated the ZCL payload
    u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                             &sZCL_HeaderParams);

    // store the incoming event details which can be used to send events back to user
    eZCL_SetReceiveEventAddressStructure(pZPSevent, &((tsSE_PriceCustomDataStructure *)psClusterInstance->pvEndPointCustomStructPtr)->sPrice_Common.sReceiveEventAddress);
    switch(psClusterInstance->bIsServer)
    {
#ifdef PRICE_SERVER
        case(TRUE):
        {
            switch(sZCL_HeaderParams.u8CommandIdentifier)
            {
                case(E_SE_GET_CURRENT_PRICE):
                {
                    vSE_HandleGetCurrentPrice(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }
                case(E_SE_GET_SCHEDULED_PRICES):
                {
                    vSE_HandleGetSheduledPrices(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }
                case (E_SE_PRICE_ACK):
                {
                    vSE_HandlePriceAck(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }

#ifdef BLOCK_CHARGING
                case (E_SE_GET_BLOCK_PERIOD):
                {
                    vSE_HandleGetBlockPeriods(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }
#endif /* BLOCK_CHARGING */

#ifdef PRICE_CONVERSION_FACTOR
                case(E_SE_GET_CONVERSION_FACTOR):
                {
                    vSE_HandleGetConversionFactor(pZPSevent,psEndPointDefinition, psClusterInstance);
                    break;
                }
#endif /*PRICE_CONVERSION_FACTOR */

#ifdef PRICE_CALORIFIC_VALUE
                case(E_SE_GET_CALORIFIC_VALUE):
                {
                    vSE_HandleGetCalorificValue(pZPSevent,psEndPointDefinition, psClusterInstance);
                    break;
                }
#endif /* PRICE_CALORIFIC_VALUE */

                default:
                {
                    return(E_ZCL_FAIL);
                    break;
                }
            }
            break;
        }
#endif

#ifdef PRICE_CLIENT
        case(FALSE):
        {
            switch(sZCL_HeaderParams.u8CommandIdentifier)
            {
                case(E_SE_PUBLISH_PRICE):
                {
                    vSE_HandlePublishPrice(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }

#ifdef BLOCK_CHARGING
                case(E_SE_PUBLISH_BLOCK_PERIOD):
                {
                    vSE_HandlePublishBlockPeriod(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }
#endif /* BLOCK_CHARGING */

#ifdef PRICE_CALORIFIC_VALUE
                case (E_SE_PUBLISH_CALORIFIC_VALUE):
                {
                    vSE_HandlePublishCalorificValue(pZPSevent,psEndPointDefinition,psClusterInstance);
                    break;
                }
#endif

#ifdef PRICE_CONVERSION_FACTOR
                case (E_SE_PUBLISH_CONVERSION_FACTOR):
                {
                    vSE_HandlePublishConversionFactor(pZPSevent,psEndPointDefinition,psClusterInstance);
                    break;
                }
#endif
                default:
                {
                    return(E_ZCL_FAIL);
                    break;
                }
            }
            break;
        }
#endif

       // ifdef failsafe
        default:
        {
            return(E_ZCL_FAIL);
            break;
        }
    }


#if defined(PRICE_SERVER) || defined(PRICE_CLIENT)
    // delete the i/p buffer on return
    return(E_ZCL_SUCCESS);
#endif

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

