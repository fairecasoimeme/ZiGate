/*****************************************************************************
 *
 * MODULE: ZigbeeNodeControlBridge
 *
 * COMPONENT: pdm_host.c
 *
 * $AUTHOR: schrodingersket $
 *
 * DESCRIPTION:
 *
 * $HeadURL: $
 *
 * $Revision:  $
 *
 * $LastChangedBy:  $
 *
 * $LastChangedDate:  $
 *
 * $Id: $
 *
 *****************************************************************************
 *
 * This software is owned by Jennic and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on Jennic products. You, and any third parties must reproduce
 * the copyright and warranty notice and any other legend of ownership on each
 * copy or partial copy of the software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
 * ACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,
 * BE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.
 *
 * Copyright Jennic Ltd 2008. All rights reserved
 *
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <jendefs.h>
#include "PDM.h"
#include "SerialLink.h"

#ifndef PDM_NO_RTOS
#include "os.h"
#include "os_gen.h"
#endif

#include "app_common.h"
#include "uart.h"
#include "SerialLink.h"
#include "log.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

// Default length of transmitted PDM record data in bytes. Kept small to keep
// message RAM footprint small. Must be less than MAX_PACKET_SIZE.
//
uint8 PDM_RECORD_LENGTH = 244;

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern uint8 au8LinkRxBuffer[MAX_PACKET_SIZE];
extern uint16 u16PacketType,u16PacketLength;
volatile uint8 u8QueueByte;
/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
#ifndef PDM_NO_RTOS
OS_thMutex  s_hPdmMutex;
#endif
PDM_tsRecordDescriptor     *pHead = NULL;
/****************************************************************************/
/***        Exported Public Functions                                     ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME: PDM_eInitialise
 *
 * DESCRIPTION:
 * Initialise Host PDM by calling PDM_vWaitHost.
 *
 * PARAMETERS: Name                       RW  Usage
 *             u8NumberOfEEPROMsegments   R   Number of EEPROM segments; 0 indicates use all available segments.
 *             u16Length                  R   Message length
 *             pu8Data                    R   Message payload
 * RETURNS:
 * void
 ****************************************************************************/
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
)
{
	DBG_vPrintf( TRACE_DEBUG, "Host PDM: Awaiting host readiness...\n");
	PDM_vWaitHost();
	DBG_vPrintf( TRACE_DEBUG, "Host PDM: Host ready.\n");
	return PDM_E_STATUS_OK;
}


/****************************************************************************
 *
 * NAME: PDM_eReadDataFromRecord
 *
 * DESCRIPTION:
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/

PUBLIC PDM_teStatus PDM_eReadDataFromRecord(
        uint16                      u16IdValue,
        void                       *pvDataBuffer,
        uint16                      u16DataBufferLength,
        uint16                     *pu16DataBytesRead)
{
	uint8 au8Buffer[MAX_PACKET_SIZE],
	      *pdmBuffer,
	      u8ReadStatus = PDM_E_STATUS_OK;

	uint16 u16TotalRecordSize,
		   u16RecordId,
	       u16TotalBlocks = 0,
	       u16CurrentBlockId = 0,
	       u16CurrentBlockSize = 0,
	       u16BlocksRead = 0;

	bool_t bNoMoreData = FALSE;

    if((pvDataBuffer == NULL) || (u16DataBufferLength == 0))
    {
        return PDM_E_STATUS_INVLD_PARAM;
    }

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eEnterCriticalSection(s_hPdmMutex);
    }
#endif

	/* flush hardware buffer */
    UART_vSetTxInterrupt(FALSE);

   	// Set bytes read to zero
   	//
   	*pu16DataBytesRead = 0;

   	// Set PDM buffer pointer to provided pointer to object to populate
   	//
   	pdmBuffer = pvDataBuffer;

   	// Create and send record load request
   	//
   	memcpy(au8Buffer, &u16IdValue, sizeof(uint16));
   	vSL_WriteMessage(E_SL_MSG_LOAD_PDM_RECORD_REQUEST, sizeof(uint16), au8Buffer, 0);

   	// Wait for record load response
   	//
   	do
   	{
   		u8QueueByte = 0xff;
		if(UART_bGetRxData((uint8*) &u8QueueByte) ){
   	    	if(TRUE == bSL_ReadMessage(&u16PacketType, &u16PacketLength, MAX_PACKET_SIZE, au8LinkRxBuffer, u8QueueByte))
   	    	{
  	    		switch(u16PacketType)
   	    		{
   	    		case(E_SL_MSG_LOAD_PDM_RECORD_RESPONSE):
   	    		{
   	    			// Get response status
   	    			//
   	    			uint8 u8Status = au8LinkRxBuffer[0];

   	    			// Load record id
   	    			//
					memcpy(&u16RecordId, &au8LinkRxBuffer[1], sizeof(uint16));

   	    			if (u16RecordId == u16IdValue)
   	    			{
   	    				// Load total record size in bytes
						//
						memcpy(&u16TotalRecordSize, &au8LinkRxBuffer[3], sizeof(uint16));

						// Read total number of expected blocks for this record
						//
						memcpy(&u16TotalBlocks, &au8LinkRxBuffer[5], sizeof(uint16));

						// Read block number for this record
						//
						memcpy(&u16CurrentBlockId, &au8LinkRxBuffer[7], sizeof(uint16));

						// Read size of this block in bytes
						//
						memcpy(&u16CurrentBlockSize, &au8LinkRxBuffer[9], sizeof(uint16));

						// Check if the record id is the one of interest.
						//
						if (u8Status != PDM_RECOVERY_STATE_NONE)
						{

							if ((*pu16DataBytesRead) + u16CurrentBlockSize > u16DataBufferLength)
							{
								// More bytes provided than can be read into RAM; don't read so we
								// prevent buffer overflow.
								//
								u8ReadStatus = PDM_E_STATUS_INVLD_PARAM;
							}
							else
							{
								// Copy block data to RAM.
								//
								memcpy(pdmBuffer, &au8LinkRxBuffer[11], u16CurrentBlockSize);
								pdmBuffer += u16CurrentBlockSize;

								// Increment bytes read
								//
								(*pu16DataBytesRead) += u16CurrentBlockSize;
							}

							// Increment blocks read
							//
	   	    				u16BlocksRead++;

							// If this is the final block to read, we're all done and can
							// exit the read loop.
							//
							if(u16BlocksRead == u16TotalBlocks)
							{
								bNoMoreData = TRUE;
							}
						}
						else
						{
							// No data available; break out of read loop.
							//
							bNoMoreData = TRUE;
						}
   	    			}
   	    		}
					break;
   	    		default:
   	    			break;
   	    		}

   	    	}

		}

		// Restart watchdog on each iteration to prevent reset on loading large
		// record sets.
		//
		vAHI_WatchdogRestart();
   	}
   	while(!bNoMoreData);


	// Send status message for read to host
	//

   	// Return 1 indicating failure if read status is not okay.
   	// This usually seems to be the case, but doesn't seem to
   	// impact performance in practice. Probably merits more
   	// research.
   	//
	au8Buffer[0] = (u8ReadStatus != PDM_E_STATUS_OK);
	au8Buffer[1] = u8ReadStatus;
	memcpy(&au8Buffer[2], &u16RecordId, sizeof(uint16));
	vSL_WriteMessage(E_SL_MSG_STATUS, 4, au8Buffer, 0);

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eExitCriticalSection(s_hPdmMutex);
    }
#endif

    UART_vSetTxInterrupt(TRUE);
    return PDM_E_STATUS_OK;
}


/****************************************************************************
 *
 * NAME: PDM_eSaveRecordData
 *
 * DESCRIPTION:
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/
PUBLIC PDM_teStatus PDM_eSaveRecordData(
        uint16                      u16IdValue,
        void                       *pu8DataBuffer,
        uint16                      u16Datalength
#ifdef PDM_ENCRYPTION_ENABLED
        ,
        bool_t                      bSecure
#endif
    )
{
	uint8 au8Buffer[MAX_PACKET_SIZE],
			*pu8Buffer,
			*pdmBuffer,
			u8Status;

	// Number of UART messages required to fully persist provided record;
	//
	uint16 u16NumberOfWrites = (u16Datalength / PDM_RECORD_LENGTH) + (((u16Datalength % PDM_RECORD_LENGTH) > 0) ? 1 : 0);
	uint16 u16BlocksWritten = 0,
           u16Size = 0,
           u16MessageLength;

    // If number of writes is zero, return early since there's no data to persist.
	//
	if(u16NumberOfWrites == 0)
	{
		return PDM_E_STATUS_OK;
	}

	UART_vSetTxInterrupt(FALSE);

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eEnterCriticalSection(s_hPdmMutex);
    }
#endif

    pdmBuffer = pu8DataBuffer;
	do
	{
		// Determine size of remaining PDM record data to send.
		//
		u16Size = u16Datalength - (u16BlocksWritten * PDM_RECORD_LENGTH);

		// Create temporary variable to walk/write UART buffer
		//
		pu8Buffer = au8Buffer;

		// Write record ID value
		//
		memcpy(pu8Buffer, &u16IdValue,sizeof(uint16));
		u16MessageLength = sizeof(uint16);
		pu8Buffer += sizeof(uint16);

		// Write total PDM record size.
		//
		memcpy(pu8Buffer, &u16Datalength, sizeof(uint16));
		u16MessageLength += sizeof(uint16);
		pu8Buffer += sizeof(uint16);

		// Send total number of block writes expected.
		//
		memcpy(pu8Buffer, &u16NumberOfWrites, sizeof(uint16));
		u16MessageLength += sizeof(uint16);
		pu8Buffer += sizeof(uint16);

		// Send number of blocks written for this PDM record.
		// This number corresponds to the block id.
		//
		memcpy(pu8Buffer, &u16BlocksWritten, sizeof(uint16));
		u16MessageLength += sizeof(uint16);
		pu8Buffer += sizeof(uint16);

		// If remaining data to send is larger than PDM_RECORD_LENGTH,
		// only send PDM_RECORD_LENGTH bytes so we can send the next
		// block in another message.
		//
		if(u16Size > PDM_RECORD_LENGTH)
		{
			u16Size = PDM_RECORD_LENGTH;
		}

		// Send size of this particular block
		//
		memcpy(pu8Buffer, &u16Size, sizeof(uint16));
		u16MessageLength += sizeof(uint16);
		pu8Buffer += sizeof(uint16);

		// Send actual block data.
		//
		memcpy(pu8Buffer, pdmBuffer, u16Size);
		u16MessageLength += u16Size;
		pu8Buffer += u16Size;

		// Increment provided data to write next block on next loop iteration.
		//
		pdmBuffer += u16Size;

		// Write save data to UART
		//
		vSL_WriteMessage(E_SL_MSG_SAVE_PDM_RECORD_REQUEST, u16MessageLength, au8Buffer, 0);

		u16BlocksWritten++;
		DBG_vPrintf( TRACE_DEBUG, "\nRecord %x: Block %d/%d written.", u16IdValue, u16BlocksWritten, u16NumberOfWrites);

	}
	while(u16BlocksWritten != u16NumberOfWrites);

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eExitCriticalSection(s_hPdmMutex);
    }
#endif

    UART_vSetTxInterrupt(TRUE);

	vAHI_WatchdogRestart();

	return u8Status;
}

/****************************************************************************
 *
 * NAME: PDM_eCreateBitmap
 *
 * DESCRIPTION: Indicates to the host that it should create a bitmap counter.
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/
PUBLIC PDM_teStatus PDM_eCreateBitmap(uint16 u16IdValue, uint32 u32InitialValue)
{
	uint8 au8Buffer[MAX_PACKET_SIZE],
			*pu8Buffer,
			u8Status = PDM_E_STATUS_OK;

	uint16 u16RecordId,
	       u16MessageLength;

	// Whether save acknowledgment has been received; once received, this function
	// terminates.
	//
	bool_t bSaveAck = FALSE;

	UART_vSetTxInterrupt(FALSE);

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eEnterCriticalSection(s_hPdmMutex);
    }
#endif

	pu8Buffer = au8Buffer;

	// Write record ID value
	//
	memcpy(pu8Buffer, &u16IdValue,sizeof(uint16));
	u16MessageLength = sizeof(uint16);
	pu8Buffer += sizeof(uint16);

	// Write total initial bitmap value.
	//
	memcpy(pu8Buffer, &u32InitialValue, sizeof(uint32));
	u16MessageLength += sizeof(uint32);
	pu8Buffer += sizeof(uint32);

	// Write bitmap create request to UART
	//
	vSL_WriteMessage(E_SL_MSG_CREATE_BITMAP_RECORD_REQUEST, u16MessageLength, au8Buffer, 0);

	// Wait for acknowledgment.
	//
	bSaveAck = FALSE;
	while(bSaveAck == FALSE)
	{
		u8QueueByte = 0xff;
		if(UART_bGetRxData((uint8*)&u8QueueByte) ){
			if(TRUE == bSL_ReadMessage(&u16PacketType, &u16PacketLength, MAX_PACKET_SIZE, au8LinkRxBuffer, u8QueueByte))
			{
				if(u16PacketType == E_SL_MSG_CREATE_BITMAP_RECORD_RESPONSE)
				{
					// Load bitmap id
					//
					u16RecordId = ZNC_RTN_U16(au8LinkRxBuffer, 1);

					if (u16RecordId == u16IdValue)
					{
						// Set return status
						//
						u8Status = au8LinkRxBuffer[0];

						// Set flag to exit loop
						//
						bSaveAck = TRUE;
					}
				}
			}
		}
	}
	vAHI_WatchdogRestart();

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eExitCriticalSection(s_hPdmMutex);
    }
#endif

    UART_vSetTxInterrupt(TRUE);

	return u8Status;
}

/****************************************************************************
 *
 * NAME: PDM_eDeleteBitmap
 *
 * DESCRIPTION: Indicates to the host that it should delete a bitmap counter.
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/
PUBLIC PDM_teStatus PDM_eDeleteBitmap(uint16 u16IdValue)
{
	uint8 au8Buffer[MAX_PACKET_SIZE],
			*pu8Buffer;

	uint16 u16MessageLength;

	UART_vSetTxInterrupt(FALSE);

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eEnterCriticalSection(s_hPdmMutex);
    }
#endif

	pu8Buffer = au8Buffer;

	// Write record ID value
	//
	memcpy(pu8Buffer, &u16IdValue,sizeof(uint16));
	u16MessageLength = sizeof(uint16);
	pu8Buffer += sizeof(uint16);

	// Write bitmap create request to UART
	//
	vSL_WriteMessage(E_SL_MSG_DELETE_BITMAP_RECORD_REQUEST, u16MessageLength, au8Buffer, 0);

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eExitCriticalSection(s_hPdmMutex);
    }
#endif

    UART_vSetTxInterrupt(TRUE);

	return PDM_E_STATUS_OK;
}

/****************************************************************************
 *
 * NAME: PDM_eIncrementBitmap
 *
 * DESCRIPTION: Indicates to the host that it should increment an existing
 *              bitmap counter.
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/
PUBLIC PDM_teStatus PDM_eIncrementBitmap(uint16 u16IdValue)
{
	uint8 au8Buffer[MAX_PACKET_SIZE],
			*pu8Buffer,
			u8Status = PDM_E_STATUS_OK;

	uint16 u16RecordId,
	       u16MessageLength;

	// Whether save acknowledgment has been received; once received, this function
	// terminates.
	//
	bool_t bSaveAck = FALSE;

	UART_vSetTxInterrupt(FALSE);

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eEnterCriticalSection(s_hPdmMutex);
    }
#endif

	pu8Buffer = au8Buffer;

	// Write record ID value
	//
	memcpy(pu8Buffer, &u16IdValue,sizeof(uint16));
	u16MessageLength = sizeof(uint16);
	pu8Buffer += sizeof(uint16);

	// Write bitmap create request to UART
	//
	vSL_WriteMessage(E_SL_MSG_INCREMENT_BITMAP_RECORD_REQUEST, u16MessageLength, au8Buffer, 0);

	// Wait for acknowledgment.
	//
	bSaveAck = FALSE;
	while(bSaveAck == FALSE)
	{
		u8QueueByte = 0xff;
		if(UART_bGetRxData((uint8*)&u8QueueByte) ){
			if(TRUE == bSL_ReadMessage(&u16PacketType, &u16PacketLength, MAX_PACKET_SIZE, au8LinkRxBuffer, u8QueueByte))
			{
				if(u16PacketType == E_SL_MSG_INCREMENT_BITMAP_RECORD_RESPONSE)
				{
					// Load bitmap id
					//
					u16RecordId = ZNC_RTN_U16(au8LinkRxBuffer, 1);

					if (u16RecordId == u16IdValue)
					{
						// Set return status
						//
						u8Status = au8LinkRxBuffer[0];

						// Set flag to exit loop
						//
						bSaveAck = TRUE;
					}
				}
			}
		}
	}
	vAHI_WatchdogRestart();

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eExitCriticalSection(s_hPdmMutex);
    }
#endif

    UART_vSetTxInterrupt(TRUE);

	return u8Status;
}

/****************************************************************************
 *
 * NAME: PDM_eGetBitmap
 *
 * DESCRIPTION: Sends a request to the host to get a bitmap value.
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/

PUBLIC PDM_teStatus PDM_eGetBitmap(
        uint16                      u16IdValue,
        uint32                      *pu32InitialValue,
        uint32                      *pu32BitmapValue)
{
	uint8 *pu8Buffer,
	      au8Buffer[MAX_PACKET_SIZE];

	uint16 u16MessageLength = 0;

	uint16 u16RecordId,
	       u16MessageType;

	bool_t bGetBitmapAck = FALSE;

	if((pu32InitialValue == NULL) || (pu32BitmapValue == NULL))
    {
        return PDM_E_STATUS_INVLD_PARAM;
    }

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eEnterCriticalSection(s_hPdmMutex);
    }
#endif

	/* flush hardware buffer */
    UART_vSetTxInterrupt(FALSE);

   	pu8Buffer = au8Buffer;

   	// Copy record id to PDM record request
   	//
   	memcpy(pu8Buffer, &u16IdValue,sizeof(uint16));
   	u16MessageLength = sizeof(uint16);
   	pu8Buffer += sizeof(uint16);

   	// Send record request
   	//
   	u16MessageType = E_SL_MSG_GET_BITMAP_RECORD_REQUEST;
   	vSL_WriteMessage(u16MessageType, u16MessageLength, au8Buffer, 0);

   	while (bGetBitmapAck == FALSE)
   	{
   		u8QueueByte = 0xff;
		if(UART_bGetRxData((uint8*) &u8QueueByte) ){
			if(TRUE == bSL_ReadMessage(&u16PacketType, &u16PacketLength, MAX_PACKET_SIZE, au8LinkRxBuffer, u8QueueByte))
			{
				switch(u16PacketType)
				{
				case(E_SL_MSG_GET_BITMAP_RECORD_RESPONSE):
				{
					uint8 u8Status = au8LinkRxBuffer[0];

					// Load bitmap id
					//
					u16RecordId = ZNC_RTN_U16(au8LinkRxBuffer, 1);

					if (u16RecordId == u16IdValue)
					{
						// Load bitmap initial value
						//
						memcpy(pu32InitialValue, &au8LinkRxBuffer[3], sizeof(uint32));

						// Load bitmap value
						//
						memcpy(pu32BitmapValue, &au8LinkRxBuffer[7], sizeof(uint32));


						// Early return if status is not indicative of success.
						//
						if (u8Status != PDM_E_STATUS_OK)
						{
#ifndef PDM_NO_RTOS
							if (NULL != s_hPdmMutex)
							{
								OS_eExitCriticalSection(s_hPdmMutex);
							}
#endif
							UART_vSetTxInterrupt(TRUE);
   							return u8Status;
						}


						// Send status message for read to host; copy status
						// twice to comply with status message format.
						//
						u8Status = 0;
						memcpy(au8Buffer, &u8Status, sizeof(uint8));
						memcpy(&au8Buffer[1], &u8Status, sizeof(uint8));
						memcpy(&au8Buffer[2], &u16MessageType, sizeof(uint16));
						vSL_WriteMessage(E_SL_MSG_STATUS, 4, au8Buffer, 0);

						// Set flag to exit wait loop
						//
						bGetBitmapAck = TRUE;
					}

				}
					break;
				default:
					break;
				}
			}
		}
   	}
	vAHI_WatchdogRestart();


#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eExitCriticalSection(s_hPdmMutex);
    }
#endif

    UART_vSetTxInterrupt(TRUE);
    return PDM_E_STATUS_OK;
}

/****************************************************************************
 *
 * NAME: PDM_bDoesDataExist
 *
 * DESCRIPTION: Sends a message to the host to request information about whether
 *              a particular record exists or not. If so, the length of the record
 *              is returned.
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/

PUBLIC bool_t PDM_bDoesDataExist(
        uint16                      u16IdValue,
        uint16                      *pu16DataLength)
{
	uint8 *pu8Buffer,
	      au8Buffer[MAX_PACKET_SIZE],
	      u8RecordExists;

	uint16 u16MessageLength = 0;

	uint16 u16RecordId,
	       u16MessageType;

	bool_t bDataExists = FALSE,
		   bRecordExistenceAck = FALSE;

#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eEnterCriticalSection(s_hPdmMutex);
    }
#endif

	/* flush hardware buffer */
    UART_vSetTxInterrupt(FALSE);

   	pu8Buffer = au8Buffer;

   	// Copy record id to PDM record request
   	//
   	memcpy(pu8Buffer, &u16IdValue,sizeof(uint16));
   	u16MessageLength = sizeof(uint16);
   	pu8Buffer += sizeof(uint16);

   	// Send record request
   	//
   	u16MessageType = E_SL_MSG_PDM_EXISTENCE_REQUEST;
   	vSL_WriteMessage(u16MessageType, u16MessageLength, au8Buffer, 0);

   	while (bRecordExistenceAck == FALSE)
   	{
   		u8QueueByte = 0xff;
		if(UART_bGetRxData((uint8*) &u8QueueByte) ){
			if(TRUE == bSL_ReadMessage(&u16PacketType, &u16PacketLength, MAX_PACKET_SIZE, au8LinkRxBuffer, u8QueueByte))
			{
				switch(u16PacketType)
				{
				case(E_SL_MSG_PDM_EXISTENCE_RESPONSE):
				{
					// Load bitmap id
					//
					u16RecordId = ZNC_RTN_U16 ( au8LinkRxBuffer, 0 );

					if (u16RecordId == u16IdValue)
					{
						u8RecordExists = au8LinkRxBuffer[2];

						// If record exists, load data length from received message.
						//
						if (u8RecordExists == 1)
						{
							// Load record length
							//
							memcpy(pu16DataLength, &au8LinkRxBuffer[3], sizeof(uint16));
							bDataExists = TRUE;
						}
						else
						{
							bDataExists = FALSE;
						}

						bRecordExistenceAck = TRUE;
					}
					break;
				}
				default:
					break;
				}
			}
		}
   	}
	vAHI_WatchdogRestart();


#ifndef PDM_NO_RTOS
    if (NULL != s_hPdmMutex) {
        OS_eExitCriticalSection(s_hPdmMutex);
    }
#endif

    UART_vSetTxInterrupt(TRUE);
    return bDataExists;
}


/****************************************************************************
 *
 * NAME: PDM_vDeleteAllDataRecords
 *
 * DESCRIPTION: Indicate to host that it should delete ALL PDM data.
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/
PUBLIC void PDM_vDeleteAllDataRecords(void)
{
	uint8 u8Status = 0,
		  au8Buffer[4];

	uint16 u16Value = E_SL_MSG_DELETE_ALL_PDM_RECORDS_REQUEST;
	UART_vSetTxInterrupt(FALSE);

	// Write status to UART; copy status twice to comply with
	// status message format
	//
	memcpy(au8Buffer,&u8Status,sizeof(uint8));
	memcpy(&au8Buffer[1], &u8Status, sizeof(uint8));
	memcpy(&au8Buffer[2],&u16Value,sizeof(uint16));

	vSL_WriteMessage(E_SL_MSG_STATUS, 4, au8Buffer, 0);

	// Write message request to UART
	//
	vSL_WriteMessage(u16Value, 0, NULL, 0);

	UART_vSetTxInterrupt(TRUE);
}

/****************************************************************************
 *
 * NAME: PDM_vDeleteDataRecord
 *
 * DESCRIPTION: Indicate to host that it should delete ALL PDM data.
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/
PUBLIC void PDM_vDeleteDataRecord(uint16 u16IdValue)
{
	uint8 u8Status = 0,
	      u8StatusBuffer[4],
	      us8DeleteRecordBuffer[2];

	uint16 u16Value = E_SL_MSG_DELETE_PDM_RECORD_REQUEST;

	UART_vSetTxInterrupt(FALSE);

	// Send delete record status
	//
	memcpy(u8StatusBuffer,&u8Status,sizeof(uint8));
	memcpy(&u8StatusBuffer[1], &u8Status, sizeof(uint8));
	memcpy(&u8StatusBuffer[2],&u16Value,sizeof(uint16));

	vSL_WriteMessage(E_SL_MSG_STATUS, 4, u8StatusBuffer, 0);

	// Write delete record request
	//
	memcpy(us8DeleteRecordBuffer, &u16IdValue, sizeof(uint16));
	vSL_WriteMessage(u16Value, 2, us8DeleteRecordBuffer, 0);

	UART_vSetTxInterrupt(TRUE);
}

/****************************************************************************
 *
 * NAME: PDM_vWaitHost
 *
 * DESCRIPTION: Waits until PDM host indicates it's available to handle PDM
 *              records.
 *
 *
 * PARAMETERS:
 *
 *
 *
 * RETURNS:
 *
 ****************************************************************************/
PUBLIC void PDM_vWaitHost(void)
{
	bool_t bHostAvailableAck;
	uint8 u8QueueByte;
	volatile uint32 u32Delay;
	UART_vSetTxInterrupt(FALSE);


	bHostAvailableAck = FALSE;
	vSL_WriteMessage(E_SL_MSG_PDM_HOST_AVAILABLE, 0, NULL, 0);
	while(bHostAvailableAck == FALSE)
	{
        u32Delay++;
        if(u32Delay > 500000)
        {
        	vSL_WriteMessage(E_SL_MSG_PDM_HOST_AVAILABLE, 0, NULL, 0);
        	u32Delay = 0;
        }
   		u8QueueByte = 0xff;
		if(UART_bGetRxData(&u8QueueByte) ){
   	    	if(TRUE==bSL_ReadMessage(&u16PacketType,&u16PacketLength,MAX_PACKET_SIZE,au8LinkRxBuffer,u8QueueByte))
   	    	{
   	    		if(u16PacketType == E_SL_MSG_PDM_HOST_AVAILABLE_RESPONSE)
   	    		{
   	    			bHostAvailableAck = TRUE;
   	    		}
   	    	}
		}
	}
	vAHI_WatchdogRestart();
	UART_vSetTxInterrupt(TRUE);
}

/****************************************************************************/
/***        Exported Private Functions                                      */
/****************************************************************************/


/****************************************************************************/
/***        Local Functions                                      */
/****************************************************************************/


/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
