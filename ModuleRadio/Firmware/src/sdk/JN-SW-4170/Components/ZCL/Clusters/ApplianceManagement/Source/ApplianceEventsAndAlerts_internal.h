/*****************************************************************************
 *
 * MODULE:             Groups Cluster
 *
 * COMPONENT:          Groups_internal.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        The internal API for the Groups Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Source/ApplianceEventsAndAlerts_internal.h $
 *
 * $Revision: 53387 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-04-18 20:07:02 +0530 (Thu, 18 Apr 2013) $
 *
 * $Id: ApplianceEventsAndAlerts_internal.h 53387 2013-04-18 14:37:02Z nxp57621 $
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

#ifndef  APPLIANCE_EVENTS_AND_ALERTS_INTERNAL_H_INCLUDED
#define  APPLIANCE_EVENTS_AND_ALERTS_INTERNAL_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "jendefs.h"

#include "zcl.h"
#include "ApplianceEventsAndAlerts.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_ApplianceEventsAndAlertsCommandHandler(
                ZPS_tsAfEvent               *pZPSevent,
                tsZCL_EndPointDefinition    *psEndPointDefinition,
                tsZCL_ClusterInstance       *psClusterInstance);

#ifdef APPLIANCE_EVENTS_AND_ALERTS_SERVER
PUBLIC teZCL_Status eCLD_AEAAGetAlertsReceive(
                ZPS_tsAfEvent                                   *pZPSevent,
                uint8                                           *pu8TransactionSequenceNumber);
#endif

#ifdef APPLIANCE_EVENTS_AND_ALERTS_CLIENT
PUBLIC teZCL_Status eCLD_AEAAGetAlertsResponseORAlertsNotificationReceive(
                ZPS_tsAfEvent                                                               *pZPSevent,
                uint8                                                                       *pu8TransactionSequenceNumber,
                tsCLD_AEAA_GetAlertsResponseORAlertsNotificationPayload                     *psPayload);

PUBLIC teZCL_Status eCLD_AEAAEventNotificationReceive(
                ZPS_tsAfEvent                                                               *pZPSevent,
                uint8                                                                       *pu8TransactionSequenceNumber,
                tsCLD_AEAA_EventNotificationPayload                                         *psPayload);
#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* APPLIANCE_EVENTS_AND_ALERTS_INTERNAL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
