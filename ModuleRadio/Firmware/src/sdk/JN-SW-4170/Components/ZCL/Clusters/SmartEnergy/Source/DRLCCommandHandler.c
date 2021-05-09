/****************************************************************************
 *
 * MODULE:             Zigbee Demand Response And Load Control Cluster
 *
 * COMPONENT:          $RCSfile $
 *
 * AUTHOR:             Wayne Ellis
 *
 * DESCRIPTION:
 * DRLC event handler functions
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
#include "zcl_options.h"


/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#if defined(CLD_DRLC) && !defined(DRLC_SERVER) && !defined(DRLC_CLIENT)
#error You Must Have either DRLC_SERVER and/or DRLC_CLIENT defined zcl_options.h
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
 ** NAME:       eSE_DRLCCommandHandler
 **
 ** DESCRIPTION:
 ** Handles DRLC Cluster custom commands
 **
 ** PARAMETERS:               Name                      Usage
 ** ZPS_tsAfEvent            *pZPSevent                 Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition      EP structure
 ** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/

PUBLIC  teZCL_Status eSE_DRLCCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance)
{

	tsZCL_HeaderParams sZCL_HeaderParams;
    tsDRLC_Common *psDRLC_Common;

    // initialise pointer
    psDRLC_Common = &((tsSE_DRLCCustomDataStructure *)psClusterInstance->pvEndPointCustomStructPtr)->sDRLC_Common;

    // store the incoming event details which can be used to send events back to the
    // server at anytime
    eZCL_SetReceiveEventAddressStructure(pZPSevent, &psDRLC_Common->sReceiveEventAddress);

    // further error checking can only be done once we have interrogated the ZCL payload
     u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                             &sZCL_HeaderParams);

    switch(psClusterInstance->bIsServer)
    {
#ifdef DRLC_SERVER
        // SERVER
        case(TRUE):
        {
            switch(sZCL_HeaderParams.u8CommandIdentifier)
            {
                case(SE_DRLC_REPORT_EVENT_STATUS):
                {
                    vSE_DRLCHandleReportEventStatus(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }
                case(SE_DRLC_GET_SCHEDULED_EVENTS):
                {
                    vSE_DRLCHandleGetScheduledEvents(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }
                default:
                {
                    return(E_ZCL_FAIL);
                    break;
                }
            }
            break;
        }
#endif

#ifdef DRLC_CLIENT
        case(FALSE):
        {
            // CLIENT
            switch(sZCL_HeaderParams.u8CommandIdentifier)
            {
                case(SE_DRLC_LOAD_CONTROL_EVENT):
                {
                    vSE_DRLCHandleLoadControlEvent(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }
                case(SE_DRLC_LOAD_CONTROL_EVENT_CANCEL):
                {
                    vSE_DRLCHandleLoadControlEventCancel(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }
                case(SE_DRLC_LOAD_CONTROL_EVENT_CANCEL_ALL):
                {
                    vSE_DRLCHandleLoadControlEventCancelAll(pZPSevent, psEndPointDefinition, psClusterInstance);
                    break;
                }
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

#if defined(DRLC_SERVER) || defined(DRLC_CLIENT)
    // delete the i/p buffer on return
    return(E_ZCL_SUCCESS);
#endif

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
