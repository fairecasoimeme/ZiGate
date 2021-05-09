/*****************************************************************************
 *
 * MODULE:             Poll Control
 *
 * COMPONENT:          PollControl_internal.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        The internal API for the Poll Control
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA12_1v0/ZCL/Clusters/General/Source/PollControl_internal.h $
 *
 * $Revision: 55123 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-07-05 13:42:02 +0530 (Fri, 05 Jul 2013) $
 *
 * $Id: PollControl_internal.h 55123 2013-07-05 08:12:02Z nxp57621 $
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
#include "PollControl.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_PollControlCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

#ifdef POLL_CONTROL_CLIENT
PUBLIC teZCL_Status eCLD_PollControlCheckinReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber);
					
PUBLIC teZCL_Status eCLD_PollControlCheckinResponseSend(
                    uint8                                         u8SourceEndPointId,
                    uint8                                         u8DestinationEndPointId,
                    tsZCL_Address                                 *psDestinationAddress,
                    uint8                                         *pu8TransactionSequenceNumber,
					tsCLD_PollControl_CheckinResponsePayload	  *psPayload);					
#endif

#ifdef POLL_CONTROL_SERVER
PUBLIC teZCL_Status eCLD_PollControlCheckinResponseReceive(
                    ZPS_tsAfEvent               				*pZPSevent,
                    uint8                       				*pu8TransactionSequenceNumber,
					tsCLD_PollControl_CheckinResponsePayload    *psPayload);
					
PUBLIC teZCL_Status eCLD_PollControlFastPollStopReceive(
                    ZPS_tsAfEvent               				*pZPSevent,
                    uint8                       				*pu8TransactionSequenceNumber);
					
#ifdef CLD_POLL_CONTROL_CMD_SET_LONG_POLL_INTERVAL
PUBLIC teZCL_Status eCLD_PollControlSetLongPollIntervalReceive(
                    ZPS_tsAfEvent               					*pZPSevent,
                    uint8                       					*pu8TransactionSequenceNumber,
					tsCLD_PollControl_SetLongPollIntervalPayload    *psPayload);
#endif

#ifdef CLD_POLL_CONTROL_CMD_SET_SHORT_POLL_INTERVAL
PUBLIC teZCL_Status eCLD_PollControlSetShortPollIntervalReceive(
                    ZPS_tsAfEvent               					*pZPSevent,
                    uint8                       					*pu8TransactionSequenceNumber,
					tsCLD_PollControl_SetShortPollIntervalPayload   *psPayload);
#endif
				
#endif
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* POLLCONTROL_INTERNAL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
