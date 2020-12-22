/*****************************************************************************
 *
 * MODULE:             Smart Energy
 *
 * COMPONENT:          zcl_PDUbufferReadWrite.c
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:       Modified Zigbee stack PDU buffer read and write functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Branches/Zigbee_3_0/Source/zcl_PDUbufferReadWrite.c $
 *
 * $Revision: 65946 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2014-11-24 17:32:07 +0530 (Mon, 24 Nov 2014) $
 *
 * $Id: zcl_PDUbufferReadWrite.c 65946 2014-11-24 12:02:07Z nxp57621 $
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
#include "zcl_internal.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"
#include <string.h>

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
 ** NAME:       u16ZCL_APduInstanceWriteNBO
 **
 ** DESCRIPTION:
 ** Writes an Attribute Value into a PDU buffer
 **
 ** PARAMETERS:                  Name               Usage
 ** PDUM_thAPduInstance          hAPduInst          PDU buffer
 ** uint16                       u16Pos             position in buffer
 ** teZCL_ZCLAttributeType       eAttributeDataType Attribute type
 ** void                        *pvData             Data to write
 **
 ** RETURN:
 ** uint16 - attribute size
 **
 ****************************************************************************/

PUBLIC uint16 u16ZCL_APduInstanceWriteNBO(
                                    PDUM_thAPduInstance         hAPduInst,
                                    uint16                      u16Pos,
                                    teZCL_ZCLAttributeType      eAttributeDataType,
                                    void                       *pvData)
{
    uint8 u8typeSize;

    if (hAPduInst) {
        uint16 u16APduSize = PDUM_u16APduGetSize(PDUM_thAPduInstanceGetApdu(hAPduInst));

        // get data type
        if(eZCL_GetAttributeTypeSize(eAttributeDataType, &u8typeSize)!= E_ZCL_SUCCESS)
        {
            return 0;
        }

        // write to buffer
        if ((u16Pos + u8typeSize - 1) < u16APduSize) {
            // get start
            uint8 *pu8Start = (uint8 *)(PDUM_pvAPduInstanceGetPayload(hAPduInst)) + u16Pos;
            // write type, return size
            return u16ZCL_WriteTypeNBO(pu8Start, eAttributeDataType, pvData);
        }
    }

    return 0;
}

/****************************************************************************
 **
 ** NAME:       u16ZCL_APduInstanceReadNBO
 **
 ** DESCRIPTION:
 ** Reads an Attribute Value from a PDU buffer
 **
 ** PARAMETERS:                  Name               Usage
 ** PDUM_thAPduInstance          hAPduInst          PDU buffer
 ** uint16                       u16Pos             position in buffer
 ** teZCL_ZCLAttributeType       eAttributeDataType Attribute type
 ** void                        *pvStruct           Struct to read data into
 **
 ** RETURN:
 ** uint16 - attribute size
 **
 ****************************************************************************/

PUBLIC uint16 u16ZCL_APduInstanceReadNBO(
                                    PDUM_thAPduInstance         hAPduInst,
                                    uint16                      u16Pos,
                                    teZCL_ZCLAttributeType      eAttributeDataType,
                                    void                        *pvStruct)
{
    uint8 u8typeSize;

    if (hAPduInst && pvStruct) {
        uint16 u16APduSize = PDUM_u16APduGetSize(PDUM_thAPduInstanceGetApdu(hAPduInst));
        // get data type
        if(eZCL_GetAttributeTypeSize(eAttributeDataType, &u8typeSize)!= E_ZCL_SUCCESS)
        {
            return 0;
        }

        // write to buffer
        if ((u16Pos + u8typeSize - 1) < u16APduSize) {
            // get start
            uint8 *pu8Start = (uint8 *)(PDUM_pvAPduInstanceGetPayload(hAPduInst)) + u16Pos;
            // write type, return size
            return u16ZCL_ReadTypeNBO(pu8Start, eAttributeDataType, pvStruct);
        }
    }

    return 0;
}

/****************************************************************************
 **
 ** NAME:       u16ZCL_WriteTypeNBO
 **
 ** DESCRIPTION:
 ** Writes a data type in NBO into a buffer
 **
 ** PARAMETERS:                  Name               Usage
 ** uint8                       *pu8Data            buffer
 ** teZCL_ZCLAttributeType       eAttributeDataType Attribute type
 ** void                        *pvData             data to write
 **
 ** RETURN:
 ** uint8 - attribute type size
 **
 ****************************************************************************/

PUBLIC uint16 u16ZCL_WriteTypeNBO(uint8 *pu8Data, teZCL_ZCLAttributeType eAttributeDataType, void *pvData)
{
    uint8 u8NumOfBytes;

    if(!pu8Data || !pvData)
    {
        return 0;
    }

    if(eZCL_GetAttributeTypeSize(eAttributeDataType, &u8NumOfBytes) != E_ZCL_SUCCESS)
    {
        return 0;
    }

    if(u8NumOfBytes == 0 || (eAttributeDataType == E_ZCL_SIGNATURE))
        return 0;

    if (eAttributeDataType == E_ZCL_KEY_128)
    {
        memcpy(pu8Data, pvData, E_ZCL_KEY_128_SIZE);
    }
    else
    {
    #ifndef LITTLE_ENDIAN_PROCESSOR
        vReverseMemcpy(pu8Data,pvData,u8NumOfBytes);
    #else   
        memcpy(pu8Data,pvData,u8NumOfBytes);
    #endif
    }

    return ((uint16)(u8NumOfBytes));
}

/****************************************************************************
 **
 ** NAME:       u16ZCL_ReadTypeNBO
 **
 ** DESCRIPTION:
 ** Reads an Attribute Value from a PDU buffer
 **
 ** PARAMETERS:                  Name               Usage
 ** uint8                       *pu8Data            buffer
 ** teZCL_ZCLAttributeType       eAttributeDataType Attribute type
 ** void                        *pu8Struct          Struct to read data into
 **
 ** RETURN:
 ** uint8 - attribute type size
 **
 ****************************************************************************/

PUBLIC uint16 u16ZCL_ReadTypeNBO(uint8 *pu8Data, teZCL_ZCLAttributeType eAttributeDataType, uint8 *pu8Struct)
{
    uint8 i,u8NumOfBytes,u8Bytes,u8ByteCopy = 0;

    if(!pu8Struct || !pu8Data)
    {
        return 0;
    }

    if(eZCL_GetAttributeTypeSize(eAttributeDataType, &u8NumOfBytes) != E_ZCL_SUCCESS)
    {
        return 0;
    }
    
    if((u8NumOfBytes == 0) || (eAttributeDataType == E_ZCL_SIGNATURE))
        return 0;
        
    if (eAttributeDataType == E_ZCL_KEY_128)
    {
        memcpy(pu8Struct, pu8Data, E_ZCL_KEY_128_SIZE);
    }
    else
    {
        /*Find out the leading number of bytes to be filled with 0x00 or 0xFF depending on the signedness of the data type while receiving aligned */
        u8Bytes = (u8ZCL_GetAttributeAllignToFourBytesBoundary(u8NumOfBytes) - u8NumOfBytes);
#ifndef LITTLE_ENDIAN_PROCESSOR   
        uint8 *pu8Temp = (uint8*)pu8Data;     
        /*Advance the input pointer to test the signedness of incoming data */
        #ifndef PC_PLATFORM_BUILD
            pu8Temp += (u8NumOfBytes - 1);
        #endif
        /*Find out signed bit and data type so that the leading bytes can be filled up correctly*/
        if(bZCL_AttributeTypeIsSigned(eAttributeDataType) &&
            (*pu8Temp & 0x80))
        {
            u8ByteCopy  = 0xFF;
        }
        
        /*Advance the receiving pointer so that leading bytes can be filled up later */
        uint8 *pu8OutTemp = (uint8*)((uint8*)pu8Struct + u8Bytes);
        /*Do a revers copy as the input data in PDU is in LE and the receiving memory is in BE*/
        for(i=0;i<u8NumOfBytes;i++)
        {
            #ifndef PC_PLATFORM_BUILD
                *pu8OutTemp++ = *pu8Temp--;
            #else
                *pu8OutTemp++ = *pu8Temp++;
            #endif
        }
                    
        for(i=0;i<u8Bytes;i++)
        {
            *pu8Struct++ = u8ByteCopy;
        }
#else
        uint8 *pu8OutTemp = (uint8*)pu8Struct;
        uint8 *pu8Temp = (uint8*)pu8Data;
        /*Do a forward copy of bytes ( because both are in LE format )from PDU as per size of the data */
        for(i=0;i<u8NumOfBytes;i++)
        {
            *pu8OutTemp++ = *pu8Temp++;
        }       
        /* Now that the copy is over - test the MSB to check the signedness */
        if(bZCL_AttributeTypeIsSigned(eAttributeDataType) &&
            (*(pu8Temp-1) & 0x80))
        {
            u8ByteCopy  = 0xFF;
        }
        for(i=0;i<u8Bytes;i++)
        {
            *pu8OutTemp++ = u8ByteCopy;
        }
#endif
    }
    
    return ((uint16)(u8NumOfBytes));

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

