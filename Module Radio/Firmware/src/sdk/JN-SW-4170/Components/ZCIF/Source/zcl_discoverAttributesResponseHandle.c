/*****************************************************************************
*
* MODULE:             Smart Energy
*
* COMPONENT:          ZCL
*
* AUTHOR:             we1
*
* DESCRIPTION:       Attribute Discovery
*
* $ $
*
* $Revision:  $
*
* $LastChangedBy: we1 $
*
* $LastChangedDate:  $
*
* $Id:  $
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
** NAME:       vZCL_HandleDiscoverAttributesResponse
**
** DESCRIPTION:
**
**
** PARAMETERS:               Name                      Usage
** ZPS_tsAfEvent            *pZPSevent                 Zigbee Stack Event
** tsZCL_EndPointDefinition *psZCL_EndPointDefinition  EP structure
** tsZCL_ClusterInstance    *psClusterInstance         Cluster structure
**
** RETURN:
** None
**
****************************************************************************/

PUBLIC  void vZCL_HandleDiscoverAttributesResponse(
    ZPS_tsAfEvent              *pZPSevent,
    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
    tsZCL_ClusterInstance      *psClusterInstance)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent;
    uint16 u16inputOffset;
    tsZCL_HeaderParams sZCL_HeaderParams;
    uint16 u16payloadSize;
    uint8 u8NumberOfAttributes;
    bool_t bMessageError;
    int i;

    // fill in non-attribute specific values in callback event structure
    sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
    sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
    sZCL_CallBackEvent.pZPSevent = pZPSevent;
    sZCL_CallBackEvent.eEventType = E_ZCL_CBET_DISCOVER_INDIVIDUAL_ATTRIBUTE_RESPONSE;
    sZCL_CallBackEvent.eZCL_Status = E_ZCL_SUCCESS;

    if (psClusterInstance == NULL)
    {
        sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_CLUSTER_NOT_FOUND;
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
        bMessageError = TRUE;
    }

    // read incoming request
    u16inputOffset = u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                                              &sZCL_HeaderParams);
                                              
    sZCL_CallBackEvent.u8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;
    
    if (sZCL_CallBackEvent.eEventType != E_ZCL_CBET_ERROR)
    {
        // parse the incoming message, read each attribute from the device and write into the outgoing buffer
        u16payloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);

        // number of attributes
        u8NumberOfAttributes = (u16payloadSize - u16inputOffset - 1)/3;

        // check for junk - carry on if we can
        bMessageError=FALSE;
        if((u16payloadSize - u16inputOffset- u8NumberOfAttributes*3 - 1)!= 0)
        {
            bMessageError=TRUE;
        }


        // M$ enum issue
        sZCL_CallBackEvent.uMessage.sAttributeDiscoveryResponse.eAttributeDataType = 0;

        // read discovery status
        // an option to supplying the bDiscoveryComplete on every c/b is to set it to always false
        // and add the actual status on the last Attribute Id
        u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
            u16inputOffset,
            E_ZCL_UINT8,
            &sZCL_CallBackEvent.uMessage.sAttributeDiscoveryResponse.bDiscoveryComplete);

        // parse the message
        for(i=0; i<u8NumberOfAttributes; i++)
        {
            // read the attribute record from the message into callback event structure
            // read attribute Id
            u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                u16inputOffset,
                E_ZCL_ATTRIBUTE_ID,
                &sZCL_CallBackEvent.uMessage.sAttributeDiscoveryResponse.u16AttributeEnum);
            // read type
            u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                u16inputOffset,
                E_ZCL_UINT8,
                &sZCL_CallBackEvent.uMessage.sAttributeDiscoveryResponse.eAttributeDataType);

            // call user for every attribute
            psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
        }

        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_DISCOVER_ATTRIBUTES_RESPONSE;
        if(bMessageError==TRUE)
        {
            // something not right about the message length
            sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_MALFORMED_MESSAGE;
        }
    }

    psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

    // check for junk
    if(bMessageError==TRUE)
    {
        // early termination send default response indicating error
        eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
        // free buffer in return
    }
    else
    {
        // incoming message is now parsed ok - send the default OK, if required
        eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SUCCESS);
    }

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
