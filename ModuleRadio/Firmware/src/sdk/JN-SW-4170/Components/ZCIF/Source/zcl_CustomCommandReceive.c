/*****************************************************************************
 *
 * MODULE:             ZCL
 *
 * COMPONENT:          zcl_CustomCommandReceive.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:       ZCL custom command receiption functions
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
#include <string.h>

#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_common.h"
#include "zcl_internal.h"
#include "dbg.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"
#include "zps_nwk_pub.h"

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
 ** NAME:       eZCL_CustomCommandReceive
 **
 ** DESCRIPTION:
 ** handles rx of a custom command
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent            *pZPSevent                     Zigbee stack event structure
 ** uint8                    *pu8TransactionSequenceNumber  Sequence number Pointer
 ** tsZCL_RxPayloadItem      *psPayloadDefinition           Payload definition
 ** uint8                     u8ItemsInPayload              Number of items in the payload
 ** uint8                     u8Flags                       Accept more/less/exact
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eZCL_CustomCommandReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsZCL_RxPayloadItem         *psPayloadDefinition,
                    uint8                       u8ItemsInPayload,
                    uint8                       u8Flags)
{

    int n, x;
    uint16 u16Offset;
    uint16 u16PayloadSize;
    uint8  u8TypeSize;
    tsZCL_HeaderParams sZCL_HeaderParams;

    // parameter checks
    // input parameter checks
    if((pZPSevent == NULL)                                          ||
       ((u8ItemsInPayload > 0) && (psPayloadDefinition == NULL)))
    {
        return(E_ZCL_ERR_PARAMETER_NULL);
    }

    /* Check pointers in payload definition and mark values as invalid */
    for(n = 0; n < u8ItemsInPayload; n++)
    {
        if((psPayloadDefinition[n].pu16ActualQuantity == NULL)      ||
           (psPayloadDefinition[n].pvDestination == NULL))
        {
            return(E_ZCL_ERR_PARAMETER_NULL);
        }

        /* Get item size */
        eZCL_GetAttributeTypeSize(psPayloadDefinition[n].eType, &u8TypeSize);

        for(x = 0; x < psPayloadDefinition[n].u16MaxQuantity; x++)
        {
            /* Correct type size for strings so we can correctly handle an array of them */
            switch(psPayloadDefinition[n].eType)
            {
            case(E_ZCL_OSTRING):
                u8TypeSize = sizeof(tsZCL_OctetString);
                break;

            case(E_ZCL_CSTRING):
                u8TypeSize = sizeof(tsZCL_CharacterString);
                break;

            case(E_ZCL_LOSTRING):
                u8TypeSize = sizeof(tsZCL_LongOctetString);
                break;

            case(E_ZCL_LCSTRING):
                u8TypeSize = sizeof(tsZCL_LongCharacterString);
                break;

            default:
                break;

            }

            /* Mark item as invalid */
            vZCL_MarkAttributeInvalid(psPayloadDefinition[n].eType, (uint8 *)(psPayloadDefinition[n].pvDestination) + (x * u8TypeSize));

        }

    }

    // parse command header
    u16Offset = u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                             &sZCL_HeaderParams);
                             
    *pu8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;

    // get payload size
    u16PayloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);


    /* For each item in the payload definition list */
    for(n = 0; (n < u8ItemsInPayload) && (u16Offset < u16PayloadSize); n++)
    {

        /* Get item size */
        eZCL_GetAttributeTypeSize(psPayloadDefinition[n].eType, &u8TypeSize);

        /* For each item in the list */
        for(x = 0; (x < psPayloadDefinition[n].u16MaxQuantity) && (u16Offset < u16PayloadSize); x++)
        {
            /* If there is some payload left, but not enough to read this data type in, message must be malformed */
            if((u16PayloadSize - u16Offset) < u8TypeSize)
            {
                // send default response indicating error
                if ((u8Flags & E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR) != E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR)
                {
                    eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
                }
                // free buffer in return]
                return(E_ZCL_FAIL);
            }

            switch(psPayloadDefinition[n].eType)
            {
            case(E_ZCL_OSTRING):
            case(E_ZCL_CSTRING):
            case(E_ZCL_LOSTRING):
            case(E_ZCL_LCSTRING):
                u16Offset += u16ZCL_APduInstanceReadStringNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16Offset, psPayloadDefinition[n].eType, psPayloadDefinition[n].pvDestination);
                break;
            default:
                /* Read item */
                u16Offset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16Offset, psPayloadDefinition[n].eType, (uint8 *)(psPayloadDefinition[n].pvDestination) + (x * u8ZCL_GetAttributeAllignToFourBytesBoundary(u8TypeSize)));
                break;

            }

            *psPayloadDefinition[n].pu16ActualQuantity = (x+1);
        }

    }

    /* If we didn't get as many items as expected, and we are not prepared to accept less */
    if(((n < u8ItemsInPayload) && (u8Flags & E_ZCL_ACCEPT_LESS) == 0))
    {
        if ((u8Flags & E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR) != E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR)
        {
            // send default response indicating error
            eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
        }
        // free buffer in return]
        return(E_ZCL_FAIL);
    }

    /* If default response has not been disabled and a default response is required by the sender and incoming message was sent unicast, send one */
    if((u8Flags & E_ZCL_DISABLE_DEFAULT_RESPONSE) != E_ZCL_DISABLE_DEFAULT_RESPONSE)
    {
        eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SUCCESS);
    }

    return(E_ZCL_SUCCESS);
}


PUBLIC teZCL_Status eZCL_CustomCommandInterPanReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_RxPayloadItem         *psPayloadDefinition,
                    uint8                       u8ItemsInPayload,
                    uint16                      u16Offset,
                    uint8                       u8Flags)
{
    int n, x;
    uint8  u8TypeSize;
    uint16 u16PayloadSize;

    // input parameter checks
    if((pZPSevent == NULL)                                          ||
       ((u8ItemsInPayload > 0) && (psPayloadDefinition == NULL)))
    {
        return(E_ZCL_ERR_PARAMETER_NULL);
    }

    /* Check pointers in payload definition and mark values as invalid */
    for(n = 0; n < u8ItemsInPayload; n++)
    {
        if((psPayloadDefinition[n].pu16ActualQuantity == NULL)      ||
           (psPayloadDefinition[n].pvDestination == NULL))
        {
            return(E_ZCL_ERR_PARAMETER_NULL);
        }

        /* Get item size */
        eZCL_GetAttributeTypeSize(psPayloadDefinition[n].eType, &u8TypeSize);

        for(x = 0; x < psPayloadDefinition[n].u16MaxQuantity; x++)
        {
            /* Correct type size for strings so we can correctly handle an array of them */
            switch(psPayloadDefinition[n].eType)
            {
            case(E_ZCL_OSTRING):
                u8TypeSize = sizeof(tsZCL_OctetString);
                break;

            case(E_ZCL_CSTRING):
                u8TypeSize = sizeof(tsZCL_CharacterString);
                break;

            case(E_ZCL_LOSTRING):
                u8TypeSize = sizeof(tsZCL_LongOctetString);
                break;

            case(E_ZCL_LCSTRING):
                u8TypeSize = sizeof(tsZCL_LongCharacterString);
                break;

            default:
                break;

            }

            /* Mark item as invalid */
            vZCL_MarkAttributeInvalid(psPayloadDefinition[n].eType, (uint8 *)(psPayloadDefinition[n].pvDestination) + (x * u8TypeSize));
        }
    }

    // get payload size
    u16PayloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsInterPanDataIndEvent.hAPduInst);

    /* For each item in the payload definition list */
    for(n = 0; (n < u8ItemsInPayload) && (u16Offset < u16PayloadSize); n++)
    {

        /* Get item size */
        eZCL_GetAttributeTypeSize(psPayloadDefinition[n].eType, &u8TypeSize);

        /* For each item in the list */
        for(x = 0; (x < psPayloadDefinition[n].u16MaxQuantity) && (u16Offset < u16PayloadSize); x++)
        {
            /* If there is some payload left, but not enough to read this data type in, message must be malformed */
            if((u16PayloadSize - u16Offset) < u8TypeSize)
            {
                // send default response indicating error
                if ((u8Flags & E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR) != E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR)
                {
                    eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
                }
                // free buffer in return]
                return(E_ZCL_FAIL);
            }

            switch(psPayloadDefinition[n].eType)
            {
            case(E_ZCL_OSTRING):
            case(E_ZCL_CSTRING):
            case(E_ZCL_LOSTRING):
            case(E_ZCL_LCSTRING):
                u16Offset += u16ZCL_APduInstanceReadStringNBO(pZPSevent->uEvent.sApsInterPanDataIndEvent.hAPduInst, u16Offset, psPayloadDefinition[n].eType, psPayloadDefinition[n].pvDestination);
                break;



            default:
                /* Read item */
                u16Offset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsInterPanDataIndEvent.hAPduInst, u16Offset, psPayloadDefinition[n].eType, (uint8 *)(psPayloadDefinition[n].pvDestination) + (x * u8TypeSize));
                break;

            }

            *psPayloadDefinition[n].pu16ActualQuantity = x;

        }

    }


    return 0;
}

/****************************************************************************
 **
 ** NAME:       eZCL_CustomCommandDRLCReceive
 **
 ** DESCRIPTION:
 ** handles rx of a custom command
 **
 ** PARAMETERS:               Name                          Usage
 ** ZPS_tsAfEvent            *pZPSevent                     Zigbee stack event structure
 ** tsZCL_EndPointDefinition *psEndPointDefinition          EP structure
 ** uint8                    *pu8TransactionSequenceNumber  Sequence number Pointer
 ** tsZCL_RxPayloadItem      *psPayloadDefinition           Payload definition
 ** uint8                     u8ItemsInPayload              Number of items in the payload
 ** uint8                     u8Flags                       Accept more/less/exact
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC teZCL_Status eZCL_CustomCommandDRLCReceive(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    uint8                       *pu8TransactionSequenceNumber,
                    tsZCL_RxPayloadItem         *psPayloadDefinition,
                    uint8                       u8ItemsInPayload,
                    uint8                       u8Flags)
{

    int n, x,z;
    uint16 u16Offset;
    uint16 u16HeaderSize;
    uint16 u16PayloadSize;
    uint8  u8TypeSize;
    bool_t bSignatureOk = TRUE;
    tsZCL_HeaderParams sZCL_HeaderParams;
    tfpZCL_ZCLMessageSignatureVerificationFunction pfVerifySignature = psZCL_Common->pfZCLSignatureVerificationFunction;
#ifndef PC_PLATFORM_BUILD
    uint64 u64RemoteIeeeAddress;
#endif
    // parameter checks
    // input parameter checks
    if((pZPSevent == NULL)                                          ||
       (psEndPointDefinition == NULL)                               ||
       ((u8ItemsInPayload > 0) && (psPayloadDefinition == NULL)))
    {
        return(E_ZCL_ERR_PARAMETER_NULL);
    }

    /* Check pointers in payload definition and mark values as invalid */
    for(n = 0; n < u8ItemsInPayload; n++)
    {
        if((psPayloadDefinition[n].pu16ActualQuantity == NULL)      ||
           (psPayloadDefinition[n].pvDestination == NULL))
        {
            return(E_ZCL_ERR_PARAMETER_NULL);
        }

        /* Get item size */
        eZCL_GetAttributeTypeSize(psPayloadDefinition[n].eType, &u8TypeSize);

        for(x = 0; x < psPayloadDefinition[n].u16MaxQuantity; x++)
        {
            /* Correct type size for strings so we can correctly handle an array of them */
            switch(psPayloadDefinition[n].eType)
            {
            case(E_ZCL_OSTRING):
                u8TypeSize = sizeof(tsZCL_OctetString);
                break;

            case(E_ZCL_CSTRING):
                u8TypeSize = sizeof(tsZCL_CharacterString);
                break;

            case(E_ZCL_LOSTRING):
                u8TypeSize = sizeof(tsZCL_LongOctetString);
                break;

            case(E_ZCL_LCSTRING):
                u8TypeSize = sizeof(tsZCL_LongCharacterString);
                break;

            default:
                break;

            }

            /* Mark item as invalid */
            vZCL_MarkAttributeInvalid(psPayloadDefinition[n].eType, (uint8 *)(psPayloadDefinition[n].pvDestination) + (x * u8TypeSize));

        }

    }

    // parse command header
    u16HeaderSize = u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
                             &sZCL_HeaderParams);
                             
    *pu8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;

    // get payload size
    u16PayloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);

    /* Set offset to start of payload data */
    u16Offset = u16HeaderSize;

    /* For each item in the payload definition list */
    for(n = 0; (n < u8ItemsInPayload) && (u16Offset < u16PayloadSize); n++)
    {

        /* Get item size */
        eZCL_GetAttributeTypeSize(psPayloadDefinition[n].eType, &u8TypeSize);

        /* For each item in the list */
        for(x = 0; (x < psPayloadDefinition[n].u16MaxQuantity) && (u16Offset < u16PayloadSize); x++)
        {
            /* If there is some payload left, but not enough to read this data type in, message must be malformed */
            if((u16PayloadSize - u16Offset) < u8TypeSize)
            {
                // send default response indicating error
                if ((u8Flags & E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR) != E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR)
                {
                    eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
                }
                // free buffer in return]
                return(E_ZCL_FAIL);
            }

            switch(psPayloadDefinition[n].eType)
            {
            case(E_ZCL_OSTRING):
            case(E_ZCL_CSTRING):
            case(E_ZCL_LOSTRING):
            case(E_ZCL_LCSTRING):
                u16Offset += u16ZCL_APduInstanceReadStringNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16Offset, psPayloadDefinition[n].eType, psPayloadDefinition[n].pvDestination);
                break;
            case(E_ZCL_SIGNATURE):
                bSignatureOk = FALSE;

                /* Read the signature into the buffer */
                for(z = 0; z < E_ZCL_SIGNATURE_SIZE; z++)
                {
                    u16Offset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16Offset, E_ZCL_UINT8, (uint8 *)(psPayloadDefinition[n].pvDestination) + (x * u8TypeSize) + z);
                }
                if(pfVerifySignature != NULL)
                {
#ifndef PC_PLATFORM_BUILD
                    u64RemoteIeeeAddress = ZPS_u64NwkNibFindExtAddr(ZPS_pvNwkGetHandle(), pZPSevent->uEvent.sApsDataIndEvent.uSrcAddress.u16Addr);

                    if(pfVerifySignature(psEndPointDefinition->u8EndPointNumber,
                                         u64RemoteIeeeAddress,
                                         (uint8*)(PDUM_pvAPduInstanceGetPayload(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst)) + u16HeaderSize,
                                         (uint32)(u16PayloadSize - (u16HeaderSize + E_ZCL_SIGNATURE_SIZE)),
                                         (uint8*)(psPayloadDefinition[n].pvDestination),
                                         (uint8*)(psPayloadDefinition[n].pvDestination) + (E_ZCL_SIGNATURE_SIZE/2)) == E_ZCL_SUCCESS)
                    {
                        bSignatureOk = TRUE;
                    }
#endif
                }
                break;
            default:
                /* Read item */
                u16Offset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16Offset, psPayloadDefinition[n].eType, (uint8 *)(psPayloadDefinition[n].pvDestination) + (x * u8ZCL_GetAttributeAllignToFourBytesBoundary(u8TypeSize)));
                break;

            }

            *psPayloadDefinition[n].pu16ActualQuantity = (x+1);
        }

    }

    /* If we didn't get as many items as expected, and we are not prepared to accept less, or */
    /* If there are bytes remaining in payload and we're not prepared to accept more */
    if(((n < u8ItemsInPayload) && (u8Flags & E_ZCL_ACCEPT_LESS) == 0))
    {
        if ((u8Flags & E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR) != E_ZCL_DISABLE_DEFAULT_RESPONSE_ERROR)
        {
            // send default response indicating error
            eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_MALFORMED_COMMAND);
        }
        // free buffer in return]
        return(E_ZCL_FAIL);
    }

    /* If default response has not been disabled and a default response is required by the sender and incoming message was sent unicast, send one */
    if((u8Flags & E_ZCL_DISABLE_DEFAULT_RESPONSE) != E_ZCL_DISABLE_DEFAULT_RESPONSE)
    {
        eZCL_SendDefaultResponse(pZPSevent, E_ZCL_CMDS_SUCCESS);
    }

    /* If signature verify failed, inform caller! */
    if(bSignatureOk == FALSE)
    {
        return(E_ZCL_ERR_SIGNATURE_VERIFY_FAILED);
    }

    return(E_ZCL_SUCCESS);
}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
