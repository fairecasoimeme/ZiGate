/*****************************************************************************
*
* MODULE:             Smart Energy
*
* COMPONENT:          zcl_WriteAttributesResponseHandle.c
*
* AUTHOR:             dgave
*
* DESCRIPTION:       Receive a Write Attributes Response
*
* $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Source/zcl_readAttributesResponseHandle.c $
*
* $Revision: 16293 $
*
* $LastChangedBy: dgave $
*
* $LastChangedDate: 2009-07-03 12:37:45 +0100 (Fri, 03 Jul 2009) $
*
* $Id: zcl_readAttributesResponseHandle.c 16293 2009-07-03 11:37:45Z dgave $
*
****************************************************************************
*
* This software is owned by NXP B.V. and/or its supplier and is protected
* under applicable copyright laws. All rights are reserved. We grant You,
* and any third parties, a license to use this software solely and
* exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
* You, and any third parties must reproduce the copyright and warranty notice
* and any other legend of ownership on each copy or partial copy of the
* software.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
* Copyright NXP B.V. 2016. All rights reserved
****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>

#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_common.h"
#include "zcl_internal.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"

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
** NAME:       vZCL_HandleAttributesWriteResponse
**
** DESCRIPTION:
**
**
** PARAMETERS:               Name                      Usage
** ZPS_tsAfEvent              *pZPSevent                 Zigbee Stack Event
** tsZCL_EndPointDefinition *psZCL_EndPointDefinition  EP structure
** tsZCL_ClusterInstance    *psClusterInstance     Cluster structure
**
** RETURN:
** void
**
****************************************************************************/

PUBLIC void   vZCL_HandleAttributesWriteResponse(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent;

    uint16 u16inputOffset;
	tsZCL_HeaderParams sZCL_HeaderParams;

    uint16 u16AttributeId;
    teZCL_CommandStatus eAttributeStatus=0;

    uint16 u16payloadSize;

    // fill in non-attribute specific values in callback event structure
    sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
    sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
    sZCL_CallBackEvent.pZPSevent = pZPSevent;
    sZCL_CallBackEvent.eEventType = E_ZCL_CBET_WRITE_INDIVIDUAL_ATTRIBUTE_RESPONSE;
    sZCL_CallBackEvent.eZCL_Status = E_ZCL_SUCCESS;

    // build command packet for response
    // read incoming request
    u16inputOffset =  u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                                               &sZCL_HeaderParams);
    sZCL_CallBackEvent.u8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;


    if (sZCL_CallBackEvent.eEventType != E_ZCL_CBET_ERROR)
    {
        // parse the incoming message
        u16payloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);

        // read and check status
        u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &eAttributeStatus);

        // Special case if there is a single success attribute this means no errors
        if (eAttributeStatus != E_ZCL_CMDS_SUCCESS)
        {
            // Shift the input offset back 1 so we are ready to loop
            u16inputOffset--;

            // parse the message - special case of no errors means we don't go round this loop
            while(u16payloadSize-u16inputOffset > 0)
            {
                // read status
                u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8, &eAttributeStatus);

                // read attribute Id
                u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_ATTRIBUTE_ID, &u16AttributeId);

                // fill in attribute specific values in callback event structure
                sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.u16AttributeEnum = u16AttributeId;
                // unknown - we are only indicating a write error back to the app that made a write request
                sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType = E_ZCL_UNKNOWN;
                sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeStatus = eAttributeStatus;
                // null data and status pointers for now
                sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.pvAttributeData = NULL;

                // call user for every attribute
                psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
            }
        }

        // re-use last attribute generated structure for message but indicate command is complete, last attribute
        // will get 2 callbacks effectively
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_WRITE_ATTRIBUTES_RESPONSE;
    }

    psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

    // incoming message is now parsed ok - send the default OK, if required
    eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SUCCESS);

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
