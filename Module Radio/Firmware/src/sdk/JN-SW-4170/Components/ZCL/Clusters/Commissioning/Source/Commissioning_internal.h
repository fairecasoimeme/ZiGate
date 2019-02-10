/*****************************************************************************
 *
 * MODULE:             Commissioning Cluster
 *
 * COMPONENT:          Commissioning_internal.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        The internal API for the Commissioning Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/Commissioning/Source/Commissioning_internal.h $
 *
 * $Revision: 71852 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-08-12 11:00:24 +0200 (Wed, 12 Aug 2015) $
 *
 * $Id: Commissioning_internal.h 71852 2015-08-12 09:00:24Z nxp57621 $
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

#ifndef  COMMS_INTERNAL_H_INCLUDED
#define  COMMS_INTERNAL_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "jendefs.h"

#include "zcl.h"
#include "Commissioning.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_CommissioningCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

#ifdef COMMISSIONING_SERVER 
PUBLIC teZCL_Status eCLD_CommissioningCommandRestartDeviceReceive(
                    ZPS_tsAfEvent                            *pZPSevent,
                    uint8                                    *pu8TransactionSequenceNumber,
                    tsCLD_Commissioning_RestartDevicePayload *psPayload);

PUBLIC teZCL_Status eCLD_CommissioningCommandModifyStartupParamsReceive(
                    ZPS_tsAfEvent                                       *pZPSevent,
                    uint8                                               *pu8TransactionSequenceNumber,
                    tsCLD_Commissioning_ModifyStartupParametersPayload  *psPayload);

PUBLIC teZCL_Status eCLD_CommissioningCommandResponseSend(
                    uint8                               u8SourceEndPointId,
                    uint8                               u8DestinationEndPointId,
                    tsZCL_Address                       *psDestinationAddress,
                    uint8                               *pu8TransactionSequenceNumber,
                    tsCLD_Commissioning_ResponsePayload *psPayload,
                    teCLD_Commissioning_Command         eCLD_Commissioning_Command);
#endif /* COMMISSIONING_SERVER */                    

#ifdef COMMISSIONING_CLIENT
PUBLIC teZCL_Status eCLD_CommissioningCommandResponseReceive(
                    ZPS_tsAfEvent                       *pZPSevent,
                    uint8                               *pu8TransactionSequenceNumber,
                    tsCLD_Commissioning_ResponsePayload *psPayload);

#endif /* COMMISSIONING_CLIENT */ 
         
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* COMMS_INTERNAL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
