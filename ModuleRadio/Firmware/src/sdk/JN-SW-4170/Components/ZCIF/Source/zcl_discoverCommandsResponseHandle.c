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
PRIVATE void vZCL_HandleDiscoverCommandsResponse(
    ZPS_tsAfEvent              *pZPSevent,
    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
    tsZCL_ClusterInstance      *psClusterInstance,
    uint8                      u8Command);
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
** NAME:       vZCL_HandleDiscoverCommandsReceivedResponse
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

PUBLIC void vZCL_HandleDiscoverCommandsReceivedResponse(
    ZPS_tsAfEvent              *pZPSevent,
    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
    tsZCL_ClusterInstance      *psClusterInstance)
{
    vZCL_HandleDiscoverCommandsResponse(
                               pZPSevent,
                               psZCL_EndPointDefinition,
                               psClusterInstance,
                               E_ZCL_DISCOVER_COMMANDS_RECEIVED_RESPONSE);
}
/****************************************************************************
**
** NAME:       vZCL_HandleDiscoverCommandsReceivedResponse
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
PUBLIC void vZCL_HandleDiscoverCommandsGeneratedResponse(
    ZPS_tsAfEvent              *pZPSevent,
    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
    tsZCL_ClusterInstance      *psClusterInstance)
{
    vZCL_HandleDiscoverCommandsResponse(
                               pZPSevent,
                               psZCL_EndPointDefinition,
                               psClusterInstance,
                               E_ZCL_DISCOVER_COMMANDS_GENERATED_RESPONSE);
}

/****************************************************************************
**
** NAME:       vZCL_HandleDiscoverCommandsResponse
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

PRIVATE void vZCL_HandleDiscoverCommandsResponse(
    ZPS_tsAfEvent              *pZPSevent,
    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
    tsZCL_ClusterInstance      *psClusterInstance,
    uint8                       u8Command)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent;

    uint16 u16inputOffset;
    uint8 u8CommandEnum;
    bool_t bDiscoveryComplete;
	tsZCL_HeaderParams sZCL_HeaderParams;

    uint16 u16payloadSize;
    uint8 u8NumberOfCommands;

    bool_t bMessageError;

    int i;

    // fill in non-attribute specific values in callback event structure
    sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
    sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
    sZCL_CallBackEvent.pZPSevent = pZPSevent;
    sZCL_CallBackEvent.eEventType = E_ZCL_CBET_DISCOVER_INDIVIDUAL_COMMAND_RECEIVED_RESPONSE;
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
        u8NumberOfCommands = (u16payloadSize - u16inputOffset - 1)/1;

        // check for junk - carry on if we can
        bMessageError=FALSE;
        if((u16payloadSize - u16inputOffset- u8NumberOfCommands*1 - 1)!= 0)
        {
            bMessageError=TRUE;
        }

        // read discovery status
        // an option to supplying the bDiscoveryComplete on every c/b is to set it to always false
        // and add the actual status on the last Attribute Id
        u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
            u16inputOffset,
            E_ZCL_UINT8,
            &bDiscoveryComplete);

        // parse the message
        for(i=0; i<u8NumberOfCommands; i++)
        {
            // read the attribute record from the message into callback event structure
            // read attribute Id
            u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                u16inputOffset,
                E_ZCL_UINT8,
                &u8CommandEnum);
            if(E_ZCL_DISCOVER_COMMANDS_RECEIVED_RESPONSE == u8Command)  
            {            
                sZCL_CallBackEvent.eEventType = E_ZCL_CBET_DISCOVER_INDIVIDUAL_COMMAND_RECEIVED_RESPONSE;
                sZCL_CallBackEvent.uMessage.sCommandsReceivedDiscoveryIndividualResponse.u8CommandEnum=u8CommandEnum;
                sZCL_CallBackEvent.uMessage.sCommandsReceivedDiscoveryIndividualResponse.u8CommandIndex = i;
            }

            if(E_ZCL_DISCOVER_COMMANDS_GENERATED_RESPONSE == u8Command)  
            {    
                sZCL_CallBackEvent.eEventType = E_ZCL_CBET_DISCOVER_INDIVIDUAL_COMMAND_GENERATED_RESPONSE;            
                sZCL_CallBackEvent.uMessage.sCommandsGeneratedDiscoveryIndividualResponse.u8CommandEnum=u8CommandEnum;
                sZCL_CallBackEvent.uMessage.sCommandsGeneratedDiscoveryIndividualResponse.u8CommandIndex = i;
            }
            // call user for every attribute
            psZCL_EndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);
        }
        if(E_ZCL_DISCOVER_COMMANDS_RECEIVED_RESPONSE == u8Command)  
        {
            sZCL_CallBackEvent.uMessage.sCommandsReceivedDiscoveryResponse.bDiscoveryComplete=bDiscoveryComplete; 
            sZCL_CallBackEvent.uMessage.sCommandsReceivedDiscoveryResponse.u8NumberOfCommands=u8NumberOfCommands;
            sZCL_CallBackEvent.eEventType = E_ZCL_CBET_DISCOVER_COMMAND_RECEIVED_RESPONSE;
        }
        if(E_ZCL_DISCOVER_COMMANDS_GENERATED_RESPONSE == u8Command)  
        {
            sZCL_CallBackEvent.uMessage.sCommandsGeneratedDiscoveryResponse.bDiscoveryComplete=bDiscoveryComplete; 
            sZCL_CallBackEvent.uMessage.sCommandsGeneratedDiscoveryResponse.u8NumberOfCommands=u8NumberOfCommands;
            sZCL_CallBackEvent.eEventType = E_ZCL_CBET_DISCOVER_COMMAND_GENERATED_RESPONSE;
        }        
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
