/*****************************************************************************
 *
 * MODULE:             Smart Energy
 *
 * COMPONENT:          zcl_internal.h
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:       Definitions used to build the ZCL library
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Branches/Zigbee_3_0/Source/zcl_internal.h $
 *
 * $Revision: 70975 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-07-06 12:33:15 +0530 (Mon, 06 Jul 2015) $
 *
 * $Id: zcl_internal.h 70975 2015-07-06 07:03:15Z nxp57621 $
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

#ifndef  ZCL_INTERNAL_H_INCLUDED
#define  ZCL_INTERNAL_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "dlist.h"

#include "zcl.h"
#include "zcl_common.h"
#include "zcl_heap.h"
#include "zcl_customcommand.h"

#ifdef UART_DEBUG
extern PUBLIC void vDebug(char *pcMessage);
extern PUBLIC void vDebugHex(uint32 u32Data, int iSize);
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

// 0x0000 – 0x7fff Standard ZigBee application profile.
#define MAX_STD_PROFILE_ID              (0x7FFF)
// 0x8000 – 0xbfff Reserved.
// 0xc000 – 0xffff Manufacturer Specific application profile.
#define MIN_MAN_PROFILE_ID              (0xC000)

// 0x0000 – 0xbfff Standard ZigBee device description.
#define MAX_STD_DEVICE_ID               (0xBFFF)
// 0xc000 – 0xffff Reserved.

// 0x0000 – 0x7fff Standard ZigBee cluster.
#define MAX_STD_CLUSTER_ID              (0x7FFF)
// 0x8000 – 0xfbff Reserved.
// 0xfc00 – 0xffff Manufacturer specific cluster within a standard ZigBee profile.
#define MIN_MAN_CLUSTER_ID              (0xFC00)

#define MAX_COMMAND_ID                  (0x10)

#define MAX_ENDPOINT_ID                 (240)

#ifdef UART_DEBUG
#define vZCL_HeapAlloc(A, B, C, D, E) \
    vDebugHex(u32HeapStart, 8); \
    vDebug(":"); \
    A = (B *)pvZCL_HeapAlloc((void *)(A), C, D); \
    vDebug(E); \
    vDebug(":Req:"); \
    vDebugHex(C, 4); \
    vDebug(":"); \
    vDebugHex(u32HeapStart, 8); \
    vDebug(" ")
#else
#define vZCL_HeapAlloc(A, B, C, D, E) A = (B *)pvZCL_HeapAlloc((void *)(A), C, D)
#endif

#define SE_CLUSTER_ID_KEY_ESTABLISHMENT                    (0x0800)
#define SE_CLUSTER_ID_TUNNELING                            (0x0704)

#if PC_PLATFORM_BUILD
    /*To fix Long address for Unit testing*/
    #define IEEE_SRC_ADD    0x1234567812345678LL
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef struct
{
    uint8    u8Length;
    uint8    *pu8Data;
} tsZCL_String;

typedef struct
{
    uint16    u16Length;
    uint8    *pu8Data;
} tsZCL_LString;
typedef union
  {
    uint8                       u8Data;
    uint16                      u16Data;
    uint32                      u32Data;
    uint64                      u64Data;
    float                       flData;
    double                      dbData;
    tsZCL_String                sStrData;
    tsZCL_Array                 saData;
    tsZCL_Structure             sData;
    tsZCL_Key                   sKeyData;
    tsZCL_LString               sLString;
  }uAttribData;
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/


PUBLIC teZCL_Status eZCL_CheckUserStringStructureRead(
                    teZCL_ZCLAttributeType      eAttributeDataType,
                    void                       *pvStringStruct);

PUBLIC teZCL_Status eZCL_GetStringLengthFieldSize(
                    teZCL_ZCLAttributeType      eAttributeDataType,
                    uint8                      *pu8typeSize);

PUBLIC uint16 u16ZCL_GetStringStructureSize(
                    teZCL_ZCLAttributeType      eAttributeDataType,
                    void                       *pvStringStruct);

PUBLIC bool_t bZCL_CheckStringFitsInStructure(
                    uint8                       u8EndPointId,
                    uint16                      u16AttributeId,
                    bool_t                      bIsManufacturerSpecific,
                    bool_t                      bIsClientAttribute,
                    tsZCL_ClusterInstance      *psClusterInstance,
                    uint16                      u16offset,
                    PDUM_thAPduInstance         hAPduInst);

PUBLIC void vZCL_GetInternalMutex(void);

PUBLIC void vZCL_ReleaseInternalMutex(void);

PUBLIC void *pvZCL_HeapAlloc(
                    void                       *pvPointer,
                    uint32                      u32BytesNeeded,
                    bool_t                      bClear);

PUBLIC teZCL_Status eZCL_CreateTimer(
                    uint8                       u8NumberOfTimers);

PUBLIC void vZCL_TimerSchedulerUpdate(tsZCL_CallBackEvent *psZCLcallBackEvent);

PUBLIC void vReportTimerClickCallback(
                    tsZCL_CallBackEvent        *psCallBackEvent);
PUBLIC uint8 u8ZCL_GetAttributeAllignToFourBytesBoundary(
                    uint8                   u8TypeSize);                    
PUBLIC teZCL_Status eZCL_GetAttributeTypeSize(
                    teZCL_ZCLAttributeType      eAttributeDataType,
                    uint8                      *pu8typeSize) __attribute__((noinline));

PUBLIC teZCL_Status eZCL_GetNumberOfFreeReportRecordEntries(
                    uint8                      *pu8NumberOfEntries);

PUBLIC teZCL_Status eZCLAddReport(
                    tsZCL_EndPointDefinition   *psEndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance,
                    tsZCL_AttributeDefinition  *psAttributeDefinition,
                    tsZCL_AttributeReportingConfigurationRecord    *psAttributeReportingRecord);

PUBLIC teZCL_Status eZCLFindReportEntryByAttributeIdAndDirection(
                     uint8                      u8EndPoint,
                     uint16                     u16ClusterID,
                     uint8                      u8DirectionIsReceived,
                     uint16                     u16AttributeEnum,
                     tsZCL_AttributeReportingConfigurationRecord    **ppsAttributeReportingRecord);

PUBLIC teZCL_Status eZCL_CalculateSizeOfReportRecord(
                     tsZCL_AttributeReportingConfigurationRecord *psAttributeReportingConfigurationRecord,
                     uint8                                       *pu8SizeOfReportRecord);

PUBLIC teZCL_Status eZCL_DoesAttributeHaveReportableChange(
                     teZCL_ZCLAttributeType      eAttributeDataType);

PUBLIC teZCL_Status eZCL_GetAttributeReportableEntry(
                     void                      **ppvReportableChange,
                     teZCL_ZCLAttributeType      eAttributeDataType,
                     tuZCL_AttributeReportable  *puAttributeReportableChange);


PUBLIC void vZCL_HandleEntireProfileCommand(uint8                       u8CommandIdentifier,
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC teZCL_Status eZCL_CreateOptionalManagers(
                    uint8                        u8NumberOfReports,
                    uint16                       u16SystemMinimumReportingInterval,
                    uint16                       u16SystemMaximumReportingInterval);

PUBLIC bool_t bZCL_CheckManufacturerSpecificAttributeFlagMatch(
                    tsZCL_AttributeDefinition  *psAttributeDefinition,
                    bool_t                      bManufacturerSpecificAttributeFlag);
                    
PUBLIC bool_t bZCL_CheckManufacturerSpecificCommandFlagMatch(
                    tsZCL_CommandDefinition  *psCommandDefinition,
                    bool_t                    bManufacturerSpecificCommandFlag);                    

PUBLIC void *pvZCL_GetAttributePointer(tsZCL_AttributeDefinition *psAttributeDefinition,
                                       tsZCL_ClusterInstance     *psClusterInstance,
                                       uint16                     u16AttributeId);
PUBLIC bool_t bZCL_CheckAttributeDirectionFlagMatch(
                    tsZCL_AttributeDefinition  *psAttributeDefinition,
                    bool_t                      bIsServer);                    

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif
                    
#endif  /* ZCL_INTERNAL_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
