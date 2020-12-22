/*****************************************************************************
 *
 * MODULE:             Smart Energy
 *
 * COMPONENT:          zcl_common.h
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:       Common structure include file
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Branches/Zigbee_3_0/Source/zcl_common.h $
 *
 * $Revision: 61733 $
 *
 * $LastChangedBy: nxp39459 $
 *
 * $LastChangedDate: 2014-06-03 11:02:37 +0530 (Tue, 03 Jun 2014) $
 *
 * $Id: zcl_common.h 61733 2014-06-03 05:32:37Z nxp39459 $
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

#ifndef ZCL_COMMON_H_INCLUDED
#define ZCL_COMMON_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include <jendefs.h>

#include "dlist.h"

#include "zcl.h"
#include "zcl_customcommand.h"
#include "zcl_internal.h"
#include "zcl_heap.h"

#include "pdum_apl.h"
#include "zps_apl.h"
#include "zps_apl_af.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#ifdef CLD_BIND_SERVER

typedef struct
{
    uint8                 u8SourceEndPointId;
    uint8                 u8DestinationEndPointId;
    uint16                u16ClusterId;
    teZCL_AddressMode     eAddressMode;
    uint16                u16PDUSize;
    uint8                 au8PDU[MAX_PDU_BIND_QUEUE_PAYLOAD_SIZE];
}tsBindServerBufferedPDUInfo;

typedef struct
{
    DLIST                 lBindServerAllocList;
    DLIST                 lBindServerDeAllocList;
}tsBindServerCustomData;

typedef struct
{
    DNODE                       dllBufferNode;
    tsBindServerBufferedPDUInfo sBindServerBufferedPDUInfo;
}tsBindServerBufferedPDURecord;


PUBLIC void vZCL_BindServerTransmissionTimerCallback(void);
#endif /* CLD_BIND_SERVER */
typedef void (* tfpZCL_ZCLZPSEventHandler)(ZPS_tsAfEvent *pZPSevent);
typedef struct
{
    uint8                       u8NumberOfEndpoints;
    uint8                       u8TransactionSequenceNumber;
    uint8                       u8ApsSequenceNumberOfLastTransmit;
    uint8                       u8NumberOfTimers;
    uint8                       u8NumberOfReports;
    bool_t                      bDisableAPSACK;
#ifdef CLD_GREENPOWER
    uint8                       u8GreenPowerMappedEpId;
#endif
    bool_t                      bTimeHasBeenSynchronised;
    bool_t                      bAvoidDirectionSearch;
    ZPS_teStatus                eLastZpsError;
    teZCL_ZCLSendSecurity       eSecuritySupported;
    uint16                      u16SystemMinimumReportingInterval;
    uint16                      u16SystemMaximumReportingInterval;
    tsZCL_EndPointRecord       *psZCL_EndPointRecord;
    tfpZCL_ZCLCallBackFunction  pfZCLinternalCallBackFunction;

    PDUM_thAPdu                 hZCL_APdu;
    uint32                      u32HeapStart;
    uint32                      u32HeapEnd;
    uint32                      u32UTCTime;
    tsZCL_TimerRecord          *psTimerRecord;
    tsZCL_ReportRecord         *psReportRecord;
    // timer
    DLIST                       lTimerAllocList;
    DLIST                       lTimerDeAllocList;
    // time
    // mutexes
    tsZCL_CallBackEvent         sZCL_InternalCallBackEvent;
    tsZCL_CallBackEvent         sZCL_CallBackEvent;
    // reports
    DLIST                       lReportAllocList;
    DLIST                       lReportDeAllocList;
    // timer
    tsZCL_CallBackEvent         sTimerCallBackEvent;
    //Message signing
    tfpZCL_ZCLMessageSignatureCreationFunction      pfZCLSignatureCreationFunction;
    tfpZCL_ZCLMessageSignatureVerificationFunction  pfZCLSignatureVerificationFunction;
    #ifdef PC_PLATFORM_BUILD
        bool_t                      bPCtestDisableAttributeChecking;
    #endif

    #ifdef CLD_BIND_SERVER
        tsBindServerCustomData     sBindServerCustomData;
    #endif

} tsZCL_Common;

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC teZCL_Status eZCL_CopyStringAttributeToPreviousValue(
                     void                      *pvStringToStore,
                     teZCL_ZCLAttributeType     eAttributeDataType,
                     tsZCL_ReportRecord        *psAttributeReportingRecord);

PUBLIC  void vZCL_SetPointerToStringStorage(
                     teZCL_ZCLAttributeType       eAttributeDataType,
                     tsZCL_ReportRecord           *psAttributeReportingRecord,
                     uint8                        *pu8PointerToStringStorage);
                     
PUBLIC  uint8* pu8ZCL_GetPointerToStringStorage(
                     teZCL_ZCLAttributeType       eAttributeDataType,
                     tsZCL_ReportRecord           *psAttributeReportingRecord);
                     
PUBLIC  void vZCL_AllocateSpaceForStringReports(
                     teZCL_ZCLAttributeType       eAttributeDataType,
                     tsZCL_ReportRecord           *psAttributeReportingRecord);
                     
PUBLIC teZCL_Status eZCL_CheckForStringAttributeChange(
                     void                      *pvStringToStore,
                     teZCL_ZCLAttributeType     eAttributeDataType,
                     tsZCL_ReportRecord        *psAttributeReportingRecord);

PUBLIC teZCL_Status eZCL_IndicateReportableChange(
                     tsZCL_ReportRecord        *psAttributeReportingRecord);

PUBLIC teZCL_Status eZCL_StoreAttributeValue(
                     void                      *pvAttributeValueToStore,
                     tsZCL_ReportRecord        *psAttributeReportingRecord);

PUBLIC teZCL_Status eZCL_StoreChangeAttributeValue(
                     tsZCL_ClusterInstance     *psClusterInstance,
                     tsZCL_AttributeDefinition *psAttributeDefinition,
                     tsZCL_ReportRecord        *psAttributeReportingRecord);

PUBLIC void vZCL_PassEventToUser(tsZCL_CallBackEvent *psZCL_CallBackEvent);

PUBLIC void vZCL_RegisterHandleGeneralCmdCallBack(void* fnPtr);

PUBLIC void vZCL_RegisterCheckForManufCodeCallBack(void* fnPtr);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern PUBLIC tsZCL_Common *psZCL_Common;

#if defined __cplusplus
}
#endif

#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/





