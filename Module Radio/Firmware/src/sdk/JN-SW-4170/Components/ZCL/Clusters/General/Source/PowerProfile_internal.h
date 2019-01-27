/*****************************************************************************
 *
 * MODULE:             Power Profile
 *
 * COMPONENT:          PowerProfile_internal.h
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        The internal API for the Power Prfoile
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA12_1v0/ZCL/Clusters/EnergyAtHome/Source/PowerProfile_internal.h $
 *
 * $Revision: 55788 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-08-05 12:59:41 +0530 (Mon, 05 Aug 2013) $
 *
 * $Id: PowerProfile_internal.h 55788 2013-08-05 07:29:41Z nxp57621 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139]. 
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

#ifndef  POLLCONTROL_INTERNAL_H_INCLUDED
#define  POLLCONTROL_INTERNAL_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "jendefs.h"

#include "zcl.h"
#include "PowerProfile.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_PPCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);
                    
PUBLIC teZCL_Status eCLD_PPPowerProfileReqReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_PP_PowerProfileReqPayload                 *psPayload);                    

PUBLIC teZCL_Status eCLD_PPEnergyPhasesScheduleReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_PP_EnergyPhasesSchedulePayload            *psPayload,
                    uint16                                          u16HeaderOffset);                    
#ifdef PP_CLIENT
PUBLIC teZCL_Status eCLD_PPGetOverallSchedulePriceReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber);
PUBLIC teZCL_Status eCLD_PPPowerProfileScheduleConstraintsReceive   (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_PP_PowerProfileScheduleConstraintsPayload *psPayload);
PUBLIC teZCL_Status eCLD_PPGetPowerProfilePriceExtendedReceive   (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_PP_GetPowerProfilePriceExtendedPayload    *psPayload);
PUBLIC teZCL_Status eCLD_PPGetPowerProfilePriceOrExtendedRspSend  (
                    uint8                                            u8SourceEndPointId,
                    uint8                                            u8DestinationEndPointId,
                    tsZCL_Address                                    *psDestinationAddress,
                    uint8                                            *pu8TransactionSequenceNumber,
                    teCLD_PP_ServerReceivedCommandID                 eCommandId,
                    tsCLD_PP_GetPowerProfilePriceRspPayload         *psPayload);
PUBLIC teZCL_Status eCLD_PPGetOverallSchedulePriceRspSend(
                    uint8                                             u8SourceEndPointId,
                    uint8                                             u8DestinationEndPointId,
                    tsZCL_Address                                     *psDestinationAddress,
                    uint8                                             *pu8TransactionSequenceNumber,
                    tsCLD_PP_GetOverallSchedulePriceRspPayload       *psPayload);
                
#endif

#ifdef PP_SERVER
PUBLIC teZCL_Status eCLD_PPPowerProfileStateReqReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber);
PUBLIC teZCL_Status eCLD_PPGetPowerProfilePriceOrExtendedRspReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_PP_GetPowerProfilePriceRspPayload         *psPayload);    
PUBLIC teZCL_Status eCLD_PPGetOverallSchedulePriceRspReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_PP_GetOverallSchedulePriceRspPayload      *psPayload);    
#endif
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* PP_INTERNAL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
