/*****************************************************************************
 *
 * MODULE:             Smart Energy
 *
 * COMPONENT:          zcl_command.c
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:       ZCL command header construction functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Branches/Zigbee_3_0/Source/zcl_command.c $
 *
 * $Revision: 65582 $
 *
 * $LastChangedBy: nxp39459 $
 *
 * $LastChangedDate: 2014-11-17 10:07:52 +0530 (Mon, 17 Nov 2014) $
 *
 * $Id: zcl_command.c 65582 2014-11-17 04:37:52Z nxp39459 $
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

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define FRAME_TYPE_SHIFT                                (0)
#define MANUFACTURER_SPECIFIC_SHIFT                     (2)
#define DIRECTION_SHIFT                                 (3)
#define DISABLE_DEFAULT_RESPONSE_SHIFT                  (4)

#define APDU_FRAME_CONTROL_POSITION                     (0)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE void vZCL_BuildFrameControlField(
                uint8                 *pu8FrameFrameControlField,
                eFrameTypeSubfield     eFrameType,
                bool_t                 bManufacturerSpecific,
                bool_t                 bDirection, 
                bool_t                 bDisableDefaultResponse);



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
 ** NAME:       u16ZCL_WriteCommandHeader
 **
 ** DESCRIPTION:
 ** Builds ZCL command Frame Header
 **
 ** PARAMETERS:                 Name                        Usage
 ** PDUM_thAPduInstance         PDUM_thAPduInstance         Zigbee Buffer
 ** eFrameTypeSubfield          eFrameType                  Frame Type
 ** bool_t                      bManufacturerSpecific       Flag to Indicate Manf. Specific
 ** uint16                      u16ManufacturerCode         Manf. Code, if specific
 ** bool_t                      bDirection                  From Client/Server
 ** bool_t                      bDisableDefaultResponse     Disable Def Response
 ** uint8                       u8TransactionSequenceNumber ZCL Transaction Seq Number
 ** uint8                       u8CommandIdentifier         Command Id
 **
 ** RETURN:
 ** uint16 - Size Of Command Header, In Bytes
 **
 ****************************************************************************/

PUBLIC uint16 u16ZCL_WriteCommandHeader(
                    PDUM_thAPduInstance         PDUM_thAPduInstance,
                    eFrameTypeSubfield          eFrameType, 
                    bool_t                      bManufacturerSpecific,
                    uint16                      u16ManufacturerCode,
                    bool_t                      bDirection, 
                    bool_t                      bDisableDefaultResponse,
                    uint8                       u8TransactionSequenceNumber,
                    uint8                       u8CommandIdentifier)
{
    uint8 u8FrameControlField;
    uint16 u16offset;

    // build FC
    vZCL_BuildFrameControlField(&u8FrameControlField, eFrameType, bManufacturerSpecific, bDirection, bDisableDefaultResponse);
    u16offset = u16ZCL_APduInstanceWriteNBO(PDUM_thAPduInstance, APDU_FRAME_CONTROL_POSITION, E_ZCL_UINT8, &u8FrameControlField);

    // complete rest of command
    if(bManufacturerSpecific)
    {
        u16offset += u16ZCL_APduInstanceWriteNBO(PDUM_thAPduInstance, u16offset, E_ZCL_UINT16, &u16ManufacturerCode);
    }
    // add TSN
    u16offset += u16ZCL_APduInstanceWriteNBO(PDUM_thAPduInstance, u16offset, E_ZCL_UINT8, &u8TransactionSequenceNumber);
    // add CID
    u16offset += u16ZCL_APduInstanceWriteNBO(PDUM_thAPduInstance, u16offset, E_ZCL_UINT8, &u8CommandIdentifier);

    return(u16offset);

}

/****************************************************************************
 **
 ** NAME:       u8ZCL_ReadCommandHeader
 **
 ** DESCRIPTION:
 ** Builds ZCL command Frame Header
 **
 ** PARAMETERS:                 Name                         Usage
 ** PDUM_thAPduInstance         PDUM_thAPduInstance          Zigbee Buffer
 ** eFrameTypeSubfield          peFrameType                  Frame Type
 ** bool_t                      pbManufacturerSpecific       Flag to Indicate Manf. Specific
 ** uint16                      pu16ManufacturerCode         Manf. Code, if specific
 ** bool_t                      pbDirection                  From Client/Server
 ** bool_t                      pbDisableDefaultResponse     Disable Def Response
 ** uint8                       pu8TransactionSequenceNumber ZCL Transaction Seq Number
 ** uint8                       pu8CommandIdentifier         Command Id
 **
 ** RETURN:
 ** uint16 - Size Of Command Header, In Bytes
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/

PUBLIC uint16 u16ZCL_ReadCommandHeader(
                    PDUM_thAPduInstance     PDUM_thAPduInstance,
                    tsZCL_HeaderParams      *psZCL_HeaderParams)

{
    uint8 u8FrameControlField;
    uint16 u16offset;

//    if((&(psZCL_HeaderParams->eFrameType)==NULL) || (&(psZCL_HeaderParams->bManufacturerSpecific)==NULL) || (&(psZCL_HeaderParams->u16ManufacturerCode)==NULL) || 
//       (&(psZCL_HeaderParams->bDirection)==NULL) || (&(psZCL_HeaderParams->bDisableDefaultResponse)==NULL) || (&(psZCL_HeaderParams->u8TransactionSequenceNumber)==NULL) || (&(psZCL_HeaderParams->u8CommandIdentifier)==NULL))
	if(psZCL_HeaderParams == NULL)
    {
        return(0xffff);
    }

    // read FC
    u16offset = u16ZCL_APduInstanceReadNBO(PDUM_thAPduInstance, APDU_FRAME_CONTROL_POSITION, E_ZCL_UINT8, &u8FrameControlField);
    psZCL_HeaderParams->eFrameType = (u8FrameControlField >> FRAME_TYPE_SHIFT) & 0x03;
    psZCL_HeaderParams->bManufacturerSpecific = (u8FrameControlField >> MANUFACTURER_SPECIFIC_SHIFT) & 0x1;
    psZCL_HeaderParams->bDirection = (u8FrameControlField >> DIRECTION_SHIFT) & 0x1;
    psZCL_HeaderParams->bDisableDefaultResponse = (u8FrameControlField >> DISABLE_DEFAULT_RESPONSE_SHIFT) & 0x1;

    // read rest of command
    if(psZCL_HeaderParams->bManufacturerSpecific)
    {
        u16offset += u16ZCL_APduInstanceReadNBO(PDUM_thAPduInstance, u16offset, E_ZCL_UINT16, &(psZCL_HeaderParams->u16ManufacturerCode));
    }
    // TSN
    u16offset += u16ZCL_APduInstanceReadNBO(PDUM_thAPduInstance, u16offset, E_ZCL_UINT8, &(psZCL_HeaderParams->u8TransactionSequenceNumber));
    // CID
    u16offset += u16ZCL_APduInstanceReadNBO(PDUM_thAPduInstance, u16offset, E_ZCL_UINT8, &(psZCL_HeaderParams->u8CommandIdentifier));

    return(u16offset);

}

/****************************************************************************
 **
 ** NAME:       u8GetTransactionSequenceNumber
 **
 ** DESCRIPTION:
 ** Obtains a transaction sequence number and internally incremants the
 ** value for the next request
 ** PARAMETERS:                 Name                        Usage
 ** None
 **
 ** RETURN:
 ** u8TransactionSequenceNumber
 **
 ****************************************************************************/

PUBLIC uint8 u8GetTransactionSequenceNumber(void)
{
    uint8 u8TransactionSequenceNumber;
 
    #ifndef COOPERATIVE
    // get ZCL mutex
        vZCL_GetInternalMutex();
    #endif

    // read sequence number
    u8TransactionSequenceNumber = psZCL_Common->u8TransactionSequenceNumber;

    // increment the transaction counter for next time
    psZCL_Common->u8TransactionSequenceNumber++;
    #ifndef COOPERATIVE
        vZCL_ReleaseInternalMutex();
    #endif
    // pass present value back to user
    return(u8TransactionSequenceNumber);
}
    
/****************************************************************************
 **
 ** NAME:       vZCL_BuildFrameControlField
 **
 ** DESCRIPTION:
 ** Builds ZCL command Frame Control Field
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint8                       *pu8FrameFrameControlField  ptr to FCF byte
 ** eFrameTypeSubfield          eFrameType                  Frame Type
 ** bool_t                      bManufacturerSpecific       Flag to Indicate Manf. Specific
 ** bool_t                      bDirection                  From Client/Server
 ** bool_t                      bDisableDefaultResponse     Disable Def Response
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/

PRIVATE void vZCL_BuildFrameControlField(
                uint8                 *pu8FrameFrameControlField,
                eFrameTypeSubfield     eFrameType,
                bool_t                 bManufacturerSpecific,
                bool_t                 bDirection, 
                bool_t                 bDisableDefaultResponse)
{
    *pu8FrameFrameControlField = 0;

    *pu8FrameFrameControlField |= (eFrameType << FRAME_TYPE_SHIFT);

    if(bManufacturerSpecific)
    {
        *pu8FrameFrameControlField |= (1 << MANUFACTURER_SPECIFIC_SHIFT);
    }

    if(bDirection)
    {
        *pu8FrameFrameControlField |= (1 << DIRECTION_SHIFT);
    }

    if(bDisableDefaultResponse)
    {
        *pu8FrameFrameControlField |= (1 << DISABLE_DEFAULT_RESPONSE_SHIFT);
    }

}
/****************************************************************************
 **
 ** NAME:       u16ZCL_GetTxPayloadSize
 **
 ** DESCRIPTION:
 ** Returns the maximum Payload size possible through ZCL
 **
 ** PARAMETERS:                 Name                        Usage
 ** uint16                      u16DestAddr                 Destination short address
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/
PUBLIC uint16 u16ZCL_GetTxPayloadSize(uint16 u16DestAddr)
{
        /* If fragmentation is supported APDU should be taken as reference */
    if(ZPS_bAplDoesDeviceSupportFragmentation(ZPS_pvAplZdoGetAplHandle()))
    {
        return(PDUM_u16APduGetSize(psZCL_Common->hZCL_APdu));
    }
    else /* If fragmentation is not supported find the actual payload size from network layer */
    {
        return(ZPS_u8AplGetMaxPayloadSize(ZPS_pvAplZdoGetAplHandle(),u16DestAddr));
    }
}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
