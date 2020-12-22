/*****************************************************************************
 *
 * MODULE:             IASACE Cluster
 *
 * COMPONENT:          IASACE_internal.h
 *
 * AUTHOR:             Shweta Chauhan
 *
 * DESCRIPTION:        The internal API for the IAS ACE Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/SecurityAndSafety/Source/IASACE_internal.h $
 *
 * $Revision: 65741 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2014-11-19 08:04:45 +0100 (Wed, 19 Nov 2014) $
 *
 * $Id: IASACE_internal.h 65741 2014-11-19 07:04:45Z nxp57621 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products  [NXP Microcontrollers such as JN5168, JN5164,
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

#ifndef  IASACE_INTERNAL_H_INCLUDED
#define  IASACE_INTERNAL_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "jendefs.h"

#include "zcl.h"
#include "IASACE.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_IASACECommandHandler (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    tsZCL_EndPointDefinition                        *psEndPointDefinition,
                    tsZCL_ClusterInstance                           *psClusterInstance);

#ifdef IASACE_SERVER
PUBLIC teZCL_Status eCLD_IASACE_ArmRespSend (
                uint8                                       u8SourceEndPointId,
                uint8                                       u8DestinationEndPointId,
                tsZCL_Address                               *psDestinationAddress,
                uint8                                       *pu8TransactionSequenceNumber,
                tsCLD_IASACE_ArmRespPayload                 *psPayload);
                
PUBLIC teZCL_Status eCLD_IASACE_GetZoneIDMapRespSend (
                    uint8                                           u8SourceEndPointId,
                    uint8                                           u8DestinationEndPointId,
                    tsZCL_Address                                   *psDestinationAddress,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_GetZoneIDMapRespPayload            *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_GetZoneInfoRespSend (
                    uint8                                           u8SourceEndPointId,
                    uint8                                           u8DestinationEndPointId,
                    tsZCL_Address                                   *psDestinationAddress,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_GetZoneInfoRespPayload             *psPayload);
               
PUBLIC teZCL_Status eCLD_IASACE_BypassRespSend (
                uint8                                       u8SourceEndPointId,
                uint8                                       u8DestinationEndPointId,
                tsZCL_Address                               *psDestinationAddress,
                uint8                                       *pu8TransactionSequenceNumber,
                tsCLD_IASACE_BypassRespPayload              *psPayload);
                
PUBLIC teZCL_Status eCLD_IASACE_GetZoneStatusRespSend (
                uint8                                       u8SourceEndPointId,
                uint8                                       u8DestinationEndPointId,
                tsZCL_Address                               *psDestinationAddress,
                uint8                                       *pu8TransactionSequenceNumber,
                tsCLD_IASACE_GetZoneStatusRespPayload       *psPayload);

PUBLIC teZCL_Status eCLD_IASACEArmReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,                    
                    tsCLD_IASACE_ArmPayload                         *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_BypassReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,                    
                    tsCLD_IASACE_BypassPayload                      *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_EmergencyReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber);
                    
PUBLIC teZCL_Status eCLD_IASACE_FireReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber);

PUBLIC teZCL_Status eCLD_IASACE_PanicReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber);

PUBLIC teZCL_Status eCLD_IASACE_GetZoneIDMapReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber);

PUBLIC teZCL_Status eCLD_IASACE_GetZoneInfoReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_GetZoneInfoPayload                 *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_GetPanelStatusReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber);

PUBLIC teZCL_Status eCLD_IASACE_GetBypassedZoneListReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber);

PUBLIC teZCL_Status eCLD_IASACE_GetZoneStatusReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_GetZoneStatusPayload               *psPayload);
#endif

#ifdef IASACE_CLIENT
PUBLIC teZCL_Status eCLD_IASACE_ArmRespReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_ArmRespPayload                     *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_GetZoneIDMapRespReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_GetZoneIDMapRespPayload            *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_GetZoneInfoRespReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_GetZoneInfoRespPayload             *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_ZoneStatusChangedReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_ZoneStatusChangedPayload           *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_PanelStatusChangedOrGetPanelStatusRespReceive (
                    ZPS_tsAfEvent                                                       *pZPSevent,
                    uint8                                                               *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_PanelStatusChangedOrGetPanelStatusRespPayload          *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_SetBypassedZoneListReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_SetBypassedZoneListPayload         *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_BypassRespReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_BypassRespPayload                  *psPayload);

PUBLIC teZCL_Status eCLD_IASACE_GetZoneStatusRespReceive (
                    ZPS_tsAfEvent                                   *pZPSevent,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_IASACE_GetZoneStatusRespPayload           *psPayload);
#endif                     
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* IASACE_INTERNAL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
