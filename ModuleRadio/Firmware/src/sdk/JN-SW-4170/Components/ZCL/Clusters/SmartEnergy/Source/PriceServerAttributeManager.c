/*****************************************************************************
 *
 * MODULE:             Price Cluster
 *
 * COMPONENT:          PriceServerAttributeManager.c
 *
 * AUTHOR:             nxp39458
 *
 * DESCRIPTION:        Managing server attributes.
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Tags/BlockTariffAlpha/ZCL/Clusters/SmartEnergy/Source/PriceTableManager.c $
 *
 * $Revision: 24586 $
 *
 * $LastChangedBy: Ramakrishna $
 *
 * $LastChangedDate: 2011-07-26 20:33:39 +0530 (Tue, 26 July 2011) $
 *
 * $Id: PriceTableManager.c 24586 2011-07-26 15:03:39Z Ramakrishna $
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



/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

#if defined(BLOCK_CHARGING) && !defined(TOU_CHARGING)
/****************************************************************************
 **
 ** NAME:       eSE_PriceAddNoTierBlockPrices
 **
 ** DESCRIPTION:
 ** Adds a No-Tier block prices to server attributes.  Only valid for a server.
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          Source EP Id
 ** uint8                       u8NoOfNoTierBlocks            No.of No-Tier block Prices
 ** tsSE_NoTierBlockPrices      *psNoTierBlockPrices        No-tier block price values
 **
 ** RETURN:
 ** teSE_PriceStatus
 **
 ****************************************************************************/
PUBLIC  teSE_PriceStatus eSE_PriceAddNoTierBlockPrices(
                            uint8 u8SourceEndPointId,
                            uint8 u8NoOfNoTierBlocks,
                            tsSE_NoTierBlockPrices *psNoTierBlockPrices)
{
    teSE_PriceStatus eFindPriceClusterReturn;
    tsSE_PriceCustomDataStructure *psPriceCustomDataStructure;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;

    uint16 u16AttributeId;
    uint8  u8AttrLoopIndex;

    /* error check for parameters */
    if(psNoTierBlockPrices == NULL)
    {
        return E_ZCL_ERR_PARAMETER_NULL;
    }

    if(u8NoOfNoTierBlocks > (CLD_P_ATTR_BLOCK_THRESHOLD_MAX_COUNT + 1))
    {
        return(E_ZCL_ERR_EP_RANGE);
    }

    // error check via EP number
    eFindPriceClusterReturn = eSE_FindPriceCluster(u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, &psPriceCustomDataStructure);

    /* check return status */
    if(eFindPriceClusterReturn != E_ZCL_SUCCESS)
    {
        return eFindPriceClusterReturn;
    }

    /* NoTier Block Prices Attribute Id starts from 0x0400 */
    /* Search Attribute Entry */
    u16AttributeId = E_CLD_P_ATTR_NOTIER_BLOCK1_PRICE;
    for(u8AttrLoopIndex = 0; u8AttrLoopIndex < u8NoOfNoTierBlocks; u8AttrLoopIndex++)
    {
        eZCL_SetLocalAttributeValue(u16AttributeId,
                                    FALSE,
                                    FALSE,
                                    psEndPointDefinition,
                                    psClusterInstance,
                                    &psNoTierBlockPrices->au32NoTierBlockPrices[u8AttrLoopIndex]);

        u16AttributeId++;
    }
    return E_ZCL_SUCCESS;
}
#endif /* defined(BLOCK_CHARGING) && !defined(TOU_CHARGING) */


#if defined(BLOCK_CHARGING) && defined(TOU_CHARGING)
/****************************************************************************
 **
 ** NAME:       eSE_PriceAddTierBlockPrices
 **
 ** DESCRIPTION:
 ** Adds a No-Tier block prices to server attributes.  Only valid for a server.
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          Source EP Id
 ** uint8                         u8NoOfTiers                    No.of Tiers
 ** uint8                         u8NoOfBlocks                No. Of blocks
 ** tsSE_TierBlockPrices         *psTierBlockPrices          Tier-block price values
 **
 ** RETURN:
 ** teSE_PriceStatus
 **
 ****************************************************************************/
PUBLIC  teSE_PriceStatus eSE_PriceAddTierBlockPrices(
                            uint8 u8SourceEndPointId, uint8 u8NoOfTiers,
                            uint8 u8NoOfBlocks,
                            tsSE_TierBlockPrices *psTierBlockPrices)
{
    teSE_PriceStatus eFindPriceClusterReturn;
    tsSE_PriceCustomDataStructure *psPriceCustomDataStructure;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;

    uint16 u16AttributeId;
    uint8  u8AttrLoopIndex, u8TierLoopIndex, u8Index;

    /* error check for parameters */
    if( (u8NoOfBlocks > (CLD_P_ATTR_BLOCK_THRESHOLD_MAX_COUNT + 1))  ||
        (u8NoOfTiers > CLD_P_ATTR_NUM_OF_TIERS_PRICE) )
    {
        return(E_ZCL_ERR_EP_RANGE);;
    }

    if(psTierBlockPrices == NULL)
    {
        return E_ZCL_ERR_PARAMETER_NULL;
    }

    // error check via EP number
    eFindPriceClusterReturn = eSE_FindPriceCluster(u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, &psPriceCustomDataStructure);

    /* check return status */
    if(eFindPriceClusterReturn != E_ZCL_SUCCESS)
    {
        return eFindPriceClusterReturn;
    }

    /* Tier Block Prices Attribute Id starts from 0x0410 */
    /* Search Attribute Entry */
    for(u8TierLoopIndex = 0; u8TierLoopIndex < u8NoOfTiers; u8TierLoopIndex++)
    {
        /* Initialize Attribute ID to start Tier-Block1 Price */
        u16AttributeId = E_CLD_P_ATTR_TIER1_BLOCK1_PRICE +
                            (u8TierLoopIndex * CLD_P_MAX_BLOCKS_PER_TIER);

        u8Index = u8TierLoopIndex * u8NoOfBlocks; /* To access Tier-Price values */
        for(u8AttrLoopIndex = 0; u8AttrLoopIndex < u8NoOfBlocks; u8AttrLoopIndex++)
        {
               eZCL_SetLocalAttributeValue(u16AttributeId,
                                                FALSE,
                                                FALSE,
                                                &u8TransactionSequenceNumber)
                                                psClusterInstance,
                                                &psTierBlockPrices->au32TierBlockPrices[u8Index]);

            u8Index++;            /* Increment Index */
            u16AttributeId++;    /* Increment Attr Id */
        }
    }
    return E_ZCL_SUCCESS;
}
#endif /* defined(BLOCK_CHARGING) && defined(TOU_CHARGING) */

#ifdef BLOCK_CHARGING
/****************************************************************************
 **
 ** NAME:       eSE_PriceAddBlockThresholds
 **
 ** DESCRIPTION:
 ** Adds block thresholds to server attributes.  Only valid for a server.
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       u8SourceEndPointId          Source EP Id
 ** tsSE_BlockThresholds        *psBlockThresholds          block threshold values
 **
 ** RETURN:
 ** teSE_PriceStatus
 **
 ****************************************************************************/
PUBLIC  teSE_PriceStatus eSE_PriceAddBlockThresholds(
                            uint8 u8SourceEndPointId,
                            tsSE_BlockThresholds *psBlockThresholds)
{
    teSE_PriceStatus eFindPriceClusterReturn;
    tsSE_PriceCustomDataStructure *psPriceCustomDataStructure;
    tsZCL_EndPointDefinition *psEndPointDefinition;
    tsZCL_ClusterInstance *psClusterInstance;

    uint16 u16AttributeId;
    uint8  u8AttrLoopIndex;
    uint8  u8NoOfBlockThresholds;

    /* error check for parameters */
    if(psBlockThresholds == NULL)
    {
        return E_ZCL_ERR_PARAMETER_NULL;
    }
    else if(psBlockThresholds->u8NoOfBlockThreshold > CLD_P_ATTR_BLOCK_THRESHOLD_MAX_COUNT)
    {
        return E_ZCL_ERR_PARAMETER_RANGE;
    }

    // error check via EP number
    eFindPriceClusterReturn = eSE_FindPriceCluster(u8SourceEndPointId, TRUE, &psEndPointDefinition, &psClusterInstance, &psPriceCustomDataStructure);

    /* check return status */
    if(eFindPriceClusterReturn != E_ZCL_SUCCESS)
    {
        return eFindPriceClusterReturn;
    }

    u8NoOfBlockThresholds = psBlockThresholds->u8NoOfBlockThreshold;

    /* Block Thresholds Attribute Id starts from 0x0100 */
    /* Search Attribute Entry */
    u16AttributeId = E_CLD_P_ATTR_BLOCK1_THRESHOLD;
    for(u8AttrLoopIndex = 0; u8AttrLoopIndex < u8NoOfBlockThresholds; u8AttrLoopIndex++)
    {
        eZCL_SetLocalAttributeValue(u16AttributeId,
                                    FALSE,
                                    FALSE,
                                    psEndPointDefinition,
                                    psClusterInstance,
                                    &psBlockThresholds->au48BlockThreholds[u8AttrLoopIndex]);

        u16AttributeId++;
    }

    return E_ZCL_SUCCESS;
}
#endif /* BLOCK_CHARGING */
