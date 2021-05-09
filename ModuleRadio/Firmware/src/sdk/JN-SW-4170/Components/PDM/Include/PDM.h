/*****************************************************************************
 *
 * MODULE:             Persistent Data Manager
 *
 * DESCRIPTION:        Provide management of data which needs to persist over
 *                     cold or warm start
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139].
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
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ***************************************************************************/

#ifndef PDM_H_INCLUDED
#define PDM_H_INCLUDED

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "jendefs.h"
#ifndef PDM_NO_RTOS
#include "os.h"
#endif
#include "AHI_AES.h"

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
/* JN514x always uses external flash */
#ifdef JENNIC_CHIP_FAMILY_JN514x
#define PDM_EXTERNAL_FLASH
#endif
#ifdef SE_HOST_COPROCESSOR
#define PDM_EXTERNAL_FLASH
#endif
#define PDM_NUM_BLOCKS     128
#ifdef PDM_EXTERNAL_FLASH
#define PDM_NAME_SIZE      16
#else
#define PDM_NAME_SIZE      7
#ifndef PDM_USER_SUPPLIED_ID
#define PDM_USER_SUPPLIED_ID /* Defaulting to having this enabled */
#endif
#endif
#define PDM_INVALID_ID     ((uint16)(-1))

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum
{
    PDM_E_STATUS_OK,
    PDM_E_STATUS_INVLD_PARAM,
    // EEPROM based PDM codes
    PDM_E_STATUS_PDM_FULL,
    PDM_E_STATUS_NOT_SAVED,
    PDM_E_STATUS_RECOVERED,
    PDM_E_STATUS_PDM_RECOVERED_NOT_SAVED,
    PDM_E_STATUS_USER_BUFFER_SIZE,
    PDM_E_STATUS_BITMAP_SATURATED_NO_INCREMENT,
    PDM_E_STATUS_BITMAP_SATURATED_OK,
    PDM_E_STATUS_IMAGE_BITMAP_COMPLETE,
    PDM_E_STATUS_IMAGE_BITMAP_INCOMPLETE,
    PDM_E_STATUS_INTERNAL_ERROR
} PDM_teStatus;

typedef enum
{
    PDM_RECOVERY_STATE_NONE=0,
    PDM_RECOVERY_STATE_NEW, //1
    PDM_RECOVERY_STATE_RECOVERED, //2
    PDM_RECOVERY_STATE_RECOVERED_NOT_READ, //3
    PDM_RECOVERY_STATE_SAVED, //4
    PDM_RECOVERY_STATE_NOT_SAVED, //5
    PDM_RECOVERY_STATE_APPENDED, //6
    // do not move
    PDM_RECOVERY_STATE_NUMBER
} PDM_teRecoveryState;

typedef struct tag_PDM_tsRecordDescriptor
{
    PDM_teRecoveryState eState;

#ifdef PDM_EXTERNAL_FLASH
#ifndef PDM_USER_SUPPLIED_ID
    char acName[PDM_NAME_SIZE];
#else
    uint16 u16UserId;
#endif
#else
    uint16 u16UserId;
#endif

    uint8 *pu8Data;
    uint32 u32DataSize;
    bool_t bSecure;
    /* reserved fields */
    uint16 u16Id;
    struct tag_PDM_tsRecordDescriptor *psNext;

#ifdef PDM_EXTERNAL_FLASH
    uint32 au32ChangedBlocks[PDM_NUM_BLOCKS / 32]; /* 128 bits */
    uint32 au32CheckedBlocks[PDM_NUM_BLOCKS / 32]; /* 128 bits */
#else
    uint32 u32magicNumber;
#endif

} PDM_tsRecordDescriptor;

typedef struct
{
    /* this function gets called after a cold or warm start */
    void (*prInitHwCb)(void);

    /* this function gets called to erase the given sector */
    void (*prEraseCb) (uint8 u8Sector);

    /* this function gets called to write data to an addresss
     * within a given sector. address zero is the start of the
     * given sector */
    void (*prWriteCb) (uint8 u8Sector,
#ifdef SE_HOST_COPROCESSOR
                       uint32 u32Addr,
                       uint32 u32Len,
#else
                       uint16 u16Addr,
                       uint16 u16Len,
#endif
                       uint8 *pu8Data);

    /* this function gets called to read data from an addresss
     * within a given sector. address zero is the start of the
     * given sector */
    void (*prReadCb)  (uint8 u8Sector,
#ifdef SE_HOST_COPROCESSOR
                       uint32 u32Addr,
                       uint32 u32Len,
#else
                       uint16 u16Addr,
                       uint16 u16Len,
#endif
                       uint8 *pu8Data);
} PDM_tsHwFncTable;

typedef enum
{
    E_PDM_SYSTEM_EVENT_WEAR_COUNT_TRIGGER_VALUE_REACHED=0,
    E_PDM_SYSTEM_EVENT_DESCRIPTOR_SAVE_FAILED,
    E_PDM_SYSTEM_EVENT_PDM_NOT_ENOUGH_SPACE,
    E_PDM_SYSTEM_EVENT_LARGEST_RECORD_FULL_SAVE_NO_LONGER_POSSIBLE,
    E_PDM_SYSTEM_EVENT_SEGMENT_DATA_CHECKSUM_FAIL,
    E_PDM_SYSTEM_EVENT_SEGMENT_SAVE_OK,
    // nerdy event codes
    E_PDM_SYSTEM_EVENT_EEPROM_SEGMENT_HEADER_REPAIRED,
    E_PDM_SYSTEM_EVENT_SYSTEM_INTERNAL_BUFFER_WEAR_COUNT_SWAP,
    E_PDM_SYSTEM_EVENT_SYSTEM_DUPLICATE_FILE_SEGMENT_DETECTED,
    E_PDM_SYSTEM_EVENT_SYSTEM_ERROR,
    // used in test harness
    E_PDM_SYSTEM_EVENT_SEGMENT_PREWRITE,
    E_PDM_SYSTEM_EVENT_SEGMENT_POSTWRITE,
    E_PDM_SYSTEM_EVENT_SEQUENCE_DUPLICATE_DETECTED,
    E_PDM_SYSTEM_EVENT_SEQUENCE_VERIFY_FAIL,
    E_PDM_SYSTEM_EVENT_PDM_SMART_SAVE,
    E_PDM_SYSTEM_EVENT_PDM_FULL_SAVE
} PDM_eSystemEventCode;

typedef struct
{
    uint32                          u32eventNumber;
    PDM_eSystemEventCode            eSystemEventCode;
} PDM_tfpSystemEventCallback;

typedef void (*PDM_tpfvSystemEventCallback) (
    uint32                          u32eventNumber,
    PDM_eSystemEventCode            eSystemEventCode);

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/* initialise the module - call this EVERY cold start and EVERY warm start */
PUBLIC void WPDM_vInit(
        uint8                       u8StartSector,
        uint8                       u8NumSectors,
        uint32                      u32SectorSize,
#ifndef PDM_NO_RTOS
        OS_thMutex                  hPdmMutex,
        OS_thMutex                  hPdmMediaMutex,
#else
        void*                       hPdmMutex,
        void*                       hPdmMediaMutex,
#endif
        PDM_tsHwFncTable           *psHwFuncTable,
        const tsReg128             *psKey);

PUBLIC void PDM_vInit(
        uint8                       u8StartSector,
        uint8                       u8NumSectors,
        uint32                      u32SectorSize,
#ifndef PDM_NO_RTOS
        OS_thMutex                  hPdmMutex,
        OS_thMutex                  hPdmMediaMutex,
#else
        void*                       hPdmMutex,
        void*                       hPdmMediaMutex,
#endif
        PDM_tsHwFncTable           *psHwFuncTable,
        const tsReg128             *psKey);

#if (defined PDM_DESCRIPTOR_BASED_API) || (defined PC_PLATFORM_BUILD)
/* always initialise ALL of your records, EVERY cold start */
PUBLIC PDM_teStatus PDM_eRegisterRecord(
        PDM_tsRecordDescriptor     *psDesc,
        uint16                      u16IdValue,
        void                       *pvData,
        uint32                      u32DataSize
        );

/* Returns the data size contained in the Descriptor Record */
PUBLIC PDM_teStatus PDM_eGetStoredDataSizeFromDescriptor(
        PDM_tsRecordDescriptor     *psDesc,
        uint32                     *pu32DataSize
        );

/* always load ALL of your records, EVERY cold start! do this before
 * calling PDM_vSaveAllBuffers(), otherwise records will be lost */
#ifdef PDM_EXTERNAL_FLASH
PUBLIC void PDM_vWarmInitHW( void);
PUBLIC PDM_teStatus PDM_eLoadRecord(
        PDM_tsRecordDescriptor     *psDesc,
#ifdef PDM_USER_SUPPLIED_ID
    uint16                      u16IdValue,
#else
                                    const char acName[PDM_NAME_SIZE],
#endif
        void                       *pvData,
        uint32                      u32DataSize,
        bool_t                      bSecure
        );

PUBLIC void PDM_vSave(void);

PUBLIC void PDM_vSaveRecord(
        PDM_tsRecordDescriptor     *psDesc);

/* discard all registered records from the NVM */
PUBLIC void PDM_vDelete(void);

/* discard a single record from the NVM */
PUBLIC void PDM_vDeleteRecord(
        PDM_tsRecordDescriptor     *psDesc);
#else
PUBLIC PDM_teStatus PDM_eLoadRecord(
        PDM_tsRecordDescriptor     *psDesc,
#ifdef PDM_USER_SUPPLIED_ID
        uint16                      u16IdValue,
#else
        const char                 *pacName,
#endif
        void                       *pvData,
        uint32                      u32DataSize,
        bool_t                      bSecure
        );

#endif

PUBLIC PDM_teStatus PDM_eBindBuffer(
        PDM_tsRecordDescriptor     *psDesc,
        void                       *pvData,
        uint32                      u32DataSize,
        bool_t                      bSecure
        );

/* this function saves every record.
 * Note that this function removes any records that haven't been
 * registered yet by PDM_eLoadRecord() */

/* The Revised API DOESN'T "remove any records that haven't been
 * registered yet"
 */
PUBLIC PDM_teStatus PDM_eSave(void);
// support for old version
#define PDM_vSave() ((void)PDM_eSave())

/* this function saves a single record, THOUGH IT MAY ON OCCASION SAVE
 * EVERY OTHER RECORD AS WELL - In the case that it does save every
 * other record as well, it removes any records that haven't been
 * registered yet by PDM_eLoadRecord() */

/* The Revised API DOESN'T do anything mentioned above after "THOUGH
 * IT MAY ON OCCASION .... " It just saves the mentioned record, kind of
 * like you might expect it to do.
 */

PUBLIC PDM_teStatus PDM_eSaveRecord(
        PDM_tsRecordDescriptor     *psDesc);
// support for old version
#define PDM_vSaveRecord(psDesc) ((void)PDM_eSaveRecord(psDesc))



/* discard all registered records from the NVM */
PUBLIC void PDM_vDelete(void);

/* discard a single record from the NVM */
PUBLIC PDM_teStatus PDM_eDeleteRecord(
        PDM_tsRecordDescriptor     *psDesc);
// support for old version
#define PDM_vDeleteRecord(psDesc) ((void)PDM_eDeleteRecord(psDesc));


PUBLIC PDM_teStatus PDM_eReLoadRecord(
        PDM_tsRecordDescriptor     *psDesc,
        void                       *pvData,
        uint32                      u32DataSize);
#endif

#ifndef PDM_EXTERNAL_FLASH
#if (defined PDM_DESCRIPTOR_BASED_API) || (defined PC_PLATFORM_BUILD)
// descriptor based API calls
PUBLIC PDM_teStatus PDM_eAppendDataToRecord(
        PDM_tsRecordDescriptor     *psDesc,
        void                       *pvData,
        uint16                      u16DataSize
        );

PUBLIC PDM_teStatus PDM_eReadPartialDataFromRecord(
        PDM_tsRecordDescriptor     *psDesc,
        uint16                      u16TableOffset,
        void                       *pvDataBuffer,
        uint16                      u16DataBufferLength,
        uint16                     *pu16DataBytesRead
    );

PUBLIC PDM_teStatus PDM_eOverWriteDataInRecord(
        PDM_tsRecordDescriptor     *psDesc,
        uint16                      u16TableOffset,
        void                       *pvDataBuffer,
        uint16                      u16DataBufferLength
    );
#endif

// non-descriptor based API calls

PUBLIC PDM_teStatus PDM_eCreateBitmap(
        uint16                      u16IdValue,
        uint32                      u32InitialValue
        );

PUBLIC PDM_teStatus PDM_eDeleteBitmap(
        uint16                      u16IdValue
        );

PUBLIC PDM_teStatus PDM_eGetBitmap(
        uint16                      u16IdValue,
        uint32                     *pu32InitialValue,
        uint32                     *pu32BitmapValue
        );

PUBLIC PDM_teStatus PDM_eIncrementBitmap(
        uint16                      u16IdValue
        );

PUBLIC PDM_teStatus PDM_eCreateImageBitmap(
        uint16                      u16IdValue,
        uint8                      *pu8RAMImageBitmap,
        uint16                      u16ImageBitmapSize);

PUBLIC PDM_teStatus PDM_eGetImageBitmap(
        uint16                      u16IdValue,
        uint8                      *pu8RAMImageBitmap,
        uint16                      u16ImageBitmapSize);

PUBLIC PDM_teStatus PDM_eSetImageBitmapBits(
        uint16                      u16IdValue,
        uint16                      u16FirstBit,
        uint16                      u16NumberOfBits,
        uint8                      *pu8RAMImageBitmap,
        uint16                      u16ImageBitmapSize);

PUBLIC PDM_teStatus PDM_eSaveImageBitmap(
        uint16                      u16IdValue,
        uint8                      *pu8RAMImageBitmap,
        uint16                      u16ImageBitmapSize,
        bool_t                      bSaveCompleteBytesOnly);

PUBLIC PDM_teStatus PDM_eIsImageBitmapComplete(
        uint16                      u16IdValue,
        uint8                      *pu8RAMImageBitmap,
        uint16                      u16ImageBitmapSize,
        bool_t                      bRAMImageBitmap);

PUBLIC PDM_teStatus PDM_eGetFirstUnusedSlotInBitmap(
        uint16                      u16IdValue,
        uint8                      *pu8RAMImageBitmap,
        uint16                      u16ImageBitmapSize,
        bool_t                      bRAMImageBitmap,
        uint16                     *pu16FirstUnusedSlotInBitmap);

PUBLIC PDM_teStatus PDM_eDeleteImageBitmap(
        uint16                      u16IdValue);

PUBLIC PDM_teStatus ePDM_ReadPartialDataFromTable(
        uint16                      u16IdValue,
        uint16                      u16TableOffset,
        void                       *pvDataBuffer,
        uint16                      u16DataBufferLength,
        uint16                     *pu16DataBytesRead
        );

#if (!defined PDM_DESCRIPTOR_BASED_API) || (defined PC_PLATFORM_BUILD) || (defined HW_TEST_BUILD)
PUBLIC PDM_teStatus PDM_eInitialise(
        uint8           u8NumberOfEEPROMsegments
#ifndef PDM_NO_RTOS
        ,
    OS_thMutex      hPdmMutex
#endif
#ifdef PDM_ENCRYPTION_ENABLED
        ,
    tsReg128                       *psEEPROMdataEncryptionKey
#endif
);

PUBLIC PDM_teStatus PDM_eSaveRecordData(
        uint16                      u16IdValue,
        void                       *pvDataBuffer,
        uint16                      u16Datalength
#ifdef PDM_ENCRYPTION_ENABLED
        ,
        bool_t                      bSecure
#endif
    );

PUBLIC PDM_teStatus PDM_eAppendDataToExistingRecord(
        uint16                      u16IdValue,
        void                       *pvData,
        uint16                      u16DataSize);

PUBLIC PDM_teStatus PDM_eReadPartialDataFromExistingRecord(
        uint16                      u16IdValue,
        uint16                      u16TableOffset,
        void                       *pvDataBuffer,
        uint16                      u16DataBufferLength,
        uint16                     *pu16DataBytesRead);

PUBLIC PDM_teStatus PDM_eOverWriteExistingDataInRecord(
        uint16                      u16IdValue,
        uint16                      u16TableOffset,
        void                       *pvDataBuffer,
        uint16                      u16DataBufferLength);

PUBLIC PDM_teStatus PDM_eReadDataFromRecord(
        uint16                      u16IdValue,
        void                       *pvDataBuffer,
        uint16                      u16DataBufferLength,
        uint16                     *pu16DataBytesRead);

PUBLIC void PDM_vDeleteDataRecord(
        uint16                      u16IdValue);

PUBLIC void PDM_vDeleteAllDataRecords(void);

PUBLIC bool_t PDM_bDoesDataExist(
        uint16                      u16IdValue,
        uint16                     *pu16DataLength);

PUBLIC uint8 PDM_u8GetSegmentCapacity(void);

PUBLIC uint8 PDM_u8GetSegmentOccupancy(void);

#endif

PUBLIC void PDM_vRegisterSystemCallback(
        PDM_tpfvSystemEventCallback fpvPDM_SystemEventCallback);

PUBLIC PDM_tpfvSystemEventCallback  PDM_pfGetSystemCallback(void);

PUBLIC void PDM_vSetWearCountTriggerLevel(
        uint32                      u32WearCountTriggerLevel);

PUBLIC PDM_teStatus PDM_eGetSegmentWearCount(
        uint8                       u8SegmentIndex,
        uint32                     *pu32WearCount);

PUBLIC PDM_teStatus PDM_eGetDeviceWearCountProfile(
        uint32      au32WearCount[],
        uint8       u8NumberOfSegments);

PUBLIC void PDM_vSetWearLevelDifference(
        uint32 u32WearLevelDifference);

#if defined UART_DEBUG
PUBLIC void vPDM_DisplayDataInFileSystem(void);

PUBLIC int iPDM_DisplayDataWithIdInFileSystem(
        uint16                      u16IdValue);

PUBLIC void vPDM_DisplayDataInEEPROM(void);

PUBLIC int iPDM_DisplayEEPROMSegmentData(
        uint8                       u8SegmentIndex);

PUBLIC char * psPDM_PrintEventID(
        PDM_eSystemEventCode        eSystemEventCode);

PUBLIC int iPDM_ReadRawEEPROMSegmentDataToBuffer(
        uint8                       u8SegmentIndex,
        uint8                      *pu8SegmentDataBuffer,
        uint8                      *pu8SegmentDataSize);

#ifdef PDM_DESCRIPTOR_BASED_API
PUBLIC char * psPDM_PrintAPIreturnStatus(
        PDM_teStatus                eStatus);

PUBLIC char * psPDM_PrintDescriptorState(
        PDM_tsRecordDescriptor     *psDesc);
#endif

#endif

#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

extern PUBLIC const uint32 PDM_g_u32Version;

#if defined __cplusplus
};
#endif

#endif /*PDM_H_INCLUDED*/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
