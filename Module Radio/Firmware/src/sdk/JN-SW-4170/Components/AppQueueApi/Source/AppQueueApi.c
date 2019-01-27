/****************************************************************************
 *
 * MODULE:             Application Queue API
 *
 * DESCRIPTION:
 * Application Queue API. Each event type (MLME, MCPS or hardware) has two
 * queues defined here, a 'spare buffers' queue containing buffers that have
 * not been assigned and a 'used buffers' queue holding events waiting to be
 * processed by the application.
 * When a buffer is needed it is taken from the appropriate 'spare buffers'
 * queue, filled with information and then placed on the 'used buffers' queue.
 * When the application asks for the information via one of the
 * psAppQApiReadXXXInd functions, the buffer is removed from the 'used
 * buffers' queue and passed to the application. When the application has
 * finished with the information, it calls one of the
 * vAppQApiReturnXXXIndBuffer functions to place the buffer back on the
 * 'spare buffers' queue.
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


/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "mac_sap.h"
#include "AppHardwareApi.h"
#include "AppQueueApi.h"
#include "AppApi.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define APP_MAX_MLME_IND 5
#define APP_MAX_MCPS_IND 5
#define APP_MAX_HW_IND   5

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
/* Each FIFO queue has a pointer to the current read position and write
   position, and the start and end of the queue */
typedef struct
{
    void **ppvReadPtr;
    void **ppvWritePtr;
    void **ppvQueueStart;
    void **ppvQueueEnd;
} tsSFqueue;

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE MAC_DcfmIndHdr_s* psAppQApiGetMlmeBuffer(void *pvParam);
PRIVATE MAC_DcfmIndHdr_s* psAppQApiGetMcpsBuffer(void *pvParam);
PRIVATE void vAppQApiPostMlme(void *pvParam, MAC_DcfmIndHdr_s *psDcfmIndHdr);
PRIVATE void vAppQApiPostMcps(void *pvParam, MAC_DcfmIndHdr_s *psDcfmIndHdr);
PRIVATE void vFifoInit(tsSFqueue *psQueue, void **ppvDataStart, uint8 u8Entries);
PRIVATE void *pvFifoPull(tsSFqueue *psQueue);
PRIVATE bool_t bFifoPush(tsSFqueue *psQueue, void *pvData);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
/* Buffer entries */
MAC_MlmeDcfmInd_s asMlmeIndBuffer[APP_MAX_MLME_IND];
MAC_McpsDcfmInd_s asMcpsIndBuffer[APP_MAX_MCPS_IND];
AppQApiHwInd_s    asHwIndBuffer[APP_MAX_HW_IND];

/* Queues for spare buffer entries */
tsSFqueue sMlmeIndBufferQueue;
tsSFqueue sMcpsIndBufferQueue;
tsSFqueue sHwIndBufferQueue;
void     *apvMlmeIndBufferData[APP_MAX_MLME_IND + 1];
void     *apvMcpsIndBufferData[APP_MAX_MCPS_IND + 1];
void     *apvHwIndBufferData[APP_MAX_HW_IND + 1];

/* Queues for used buffer entries */
tsSFqueue sMlmeIndQueue;
tsSFqueue sMcpsIndQueue;
tsSFqueue sHwIndQueue;
void     *apvMlmeIndData[APP_MAX_MLME_IND + 1];
void     *apvMcpsIndData[APP_MAX_MCPS_IND + 1];
void     *apvHwIndData[APP_MAX_HW_IND + 1];

/* Callbacks */
PR_QIND_CALLBACK   prAppMlmeCallback;
PR_QIND_CALLBACK   prAppMcpsCallback;
PR_HWQINT_CALLBACK prAppHwCallback;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME:       bAppQApiInit
 *
 * DESCRIPTION:
 * Initialised the Application Queue API, Application API and stack. Creates
 * the queues used for passing information up to the application and fills
 * the 'spare buffers' queues with the spare buffer entries. Also registers
 * the callback handlers with the Application API layer so all upward
 * information comes through this module.
 *
 * PARAMETERS: Name            RW  Usage
 *             prMlmeCallback  R   Optional callback when MLME received
 *             prMcpsCallback  R   Optional callback when MCPS received
 *             prHwCallback    R   Optional callback when HW int received
 *
 * RETURNS:
 * TRUE if initialisation was successful
 *
 ****************************************************************************/
PUBLIC uint32 u32AppQApiInit(PR_QIND_CALLBACK prMlmeCallback,
                             PR_QIND_CALLBACK prMcpsCallback,
                             PR_HWQINT_CALLBACK prHwCallback)
{
    int i;

    /* Initialise 'spare buffers' queues and fill with spare buffers */
    vFifoInit(&sMlmeIndBufferQueue, apvMlmeIndBufferData, APP_MAX_MLME_IND);
    for (i = 0; i < APP_MAX_MLME_IND; i++)
    {
        bFifoPush(&sMlmeIndBufferQueue, (void *)&asMlmeIndBuffer[i]);
    }

    vFifoInit(&sMcpsIndBufferQueue, apvMcpsIndBufferData, APP_MAX_MCPS_IND);
    for (i = 0; i < APP_MAX_MCPS_IND; i++)
    {
        bFifoPush(&sMcpsIndBufferQueue, (void *)&asMcpsIndBuffer[i]);
    }

    vFifoInit(&sHwIndBufferQueue, apvHwIndBufferData, APP_MAX_HW_IND);
    for (i = 0; i < APP_MAX_HW_IND; i++)
    {
        bFifoPush(&sHwIndBufferQueue, (void *)&asHwIndBuffer[i]);
    }

    /* Initialise 'used buffers' queues */
    vFifoInit(&sMlmeIndQueue, apvMlmeIndData, APP_MAX_MLME_IND);
    vFifoInit(&sMcpsIndQueue, apvMcpsIndData, APP_MAX_MCPS_IND);
    vFifoInit(&sHwIndQueue,   apvHwIndData,   APP_MAX_HW_IND);

    /* Store callbacks */
    prAppMlmeCallback = prMlmeCallback;
    prAppMcpsCallback = prMcpsCallback;
    prAppHwCallback = prHwCallback;

    /* Register peripheral callbacks */
    vAHI_SysCtrlRegisterCallback(vAppQApiPostHwInt);
    vAHI_APRegisterCallback(vAppQApiPostHwInt);
#ifndef GDB
    vAHI_Uart0RegisterCallback(vAppQApiPostHwInt);
#endif
    vAHI_Uart1RegisterCallback(vAppQApiPostHwInt);
    vAHI_TickTimerInit(vAppQApiPostHwInt);
    vAHI_SpiRegisterCallback(vAppQApiPostHwInt);
#if (defined JENNIC_CHIP_FAMILY_JN514x) || (defined JENNIC_CHIP_FAMILY_JN516x)
    vAHI_SiRegisterCallback(vAppQApiPostHwInt);
#endif
    vAHI_Timer0RegisterCallback(vAppQApiPostHwInt);
    vAHI_Timer1RegisterCallback(vAppQApiPostHwInt);

    /* Register this layer with AppApi layer */
    return u32AppApiInit(psAppQApiGetMlmeBuffer, vAppQApiPostMlme, NULL,
                         psAppQApiGetMcpsBuffer, vAppQApiPostMcps, NULL);
}

/****************************************************************************
 *
 * NAME:       psAppQApiReadMlmeInd
 *
 * DESCRIPTION:
 * Reads a buffer pointer from the MLME used buffers queue. If the queue is
 * empty, NULL is returned.
 *
 * RETURNS:
 * MAC_MlmeDcfmInd_s * pointer to MLME buffer, or NULL
 *
 ****************************************************************************/
PUBLIC MAC_MlmeDcfmInd_s *psAppQApiReadMlmeInd(void)
{
    return (MAC_MlmeDcfmInd_s *)pvFifoPull(&sMlmeIndQueue);
}

/****************************************************************************
 *
 * NAME:       psAppQApiReadMcpsInd
 *
 * DESCRIPTION:
 * Reads a buffer pointer from the MCPS used buffers queue. If the queue is
 * empty, NULL is returned.
 *
 * RETURNS:
 * MAC_McpsDcfmInd_s * pointer to MCPS buffer, or NULL
 *
 ****************************************************************************/
PUBLIC MAC_McpsDcfmInd_s *psAppQApiReadMcpsInd(void)
{
    return (MAC_McpsDcfmInd_s *)pvFifoPull(&sMcpsIndQueue);
}

/****************************************************************************
 *
 * NAME:       psAppQApiReadHwInd
 *
 * DESCRIPTION:
 * Reads a buffer pointer from the hardware event used buffers queue. If the
 * queue is empty, NULL is returned.
 *
 * RETURNS:
 * AppQApiHwInd_s * pointer to hardware event buffer, or NULL
 *
 ****************************************************************************/
PUBLIC AppQApiHwInd_s *psAppQApiReadHwInd(void)
{
    return (AppQApiHwInd_s *)pvFifoPull(&sHwIndQueue);
}

/****************************************************************************
 *
 * NAME:       vAppQApiReturnMlmeIndBuffer
 *
 * DESCRIPTION:
 * Returns a buffer to the MLME spare buffers queue
 *
 * PARAMETERS:      Name            RW  Usage
 *                  psBuffer        R   Buffer to return
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vAppQApiReturnMlmeIndBuffer(MAC_MlmeDcfmInd_s *psBuffer)
{
    bFifoPush(&sMlmeIndBufferQueue, (void *)psBuffer);
}

/****************************************************************************
 *
 * NAME:       vAppQApiReturnMcpsIndBuffer
 *
 * DESCRIPTION:
 * Returns a buffer to the MCPS spare buffers queue
 *
 * PARAMETERS:      Name            RW  Usage
 *                  psBuffer        R   Buffer to return
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vAppQApiReturnMcpsIndBuffer(MAC_McpsDcfmInd_s *psBuffer)
{
    bFifoPush(&sMcpsIndBufferQueue, (void *)psBuffer);
}

/****************************************************************************
 *
 * NAME:       vAppQApiReturnHwIndBuffer
 *
 * DESCRIPTION:
 * Returns a buffer to the hardware event spare buffers queue
 *
 * PARAMETERS:      Name            RW  Usage
 *                  psBuffer        R   Buffer to return
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vAppQApiReturnHwIndBuffer(AppQApiHwInd_s *psBuffer)
{
    bFifoPush(&sHwIndBufferQueue, (void *)psBuffer);
}

/****************************************************************************
 *
 * NAME:       vAppQApiPostHwInt
 *
 * DESCRIPTION:
 * Called by lower layer as a callback, this takes a buffer from the spare
 * buffers queue for hardware events, populates it, and places it on the used
 * buffers queue. If a callback to the application has been defined, this is
 * called as well.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u32Device       R   Device identifier of event originator
 *                  u32ItemBitmap   R   Bitmap of events generated by device
 *
 * RETURNS:
 * void
 *
 * NOTES:
 * Runs in interrupt context
 *
 ****************************************************************************/
PUBLIC void vAppQApiPostHwInt(uint32 u32Device, uint32 u32ItemBitmap)
{
    AppQApiHwInd_s *psBuffer;

    /* Need special case for UART RX interrupt, as this is only cleared when
       the data is removed from the RX FIFO */
    if ((u32Device == E_AHI_DEVICE_UART0) || (u32Device == E_AHI_DEVICE_UART1))
    {
        if ((u32ItemBitmap == E_AHI_UART_INT_RXDATA)
            || (u32ItemBitmap == E_AHI_UART_INT_TIMEOUT))
        {
            /* Read byte from UART and store it in the bitmap to be queued */
            uint8 u8ActiveUart;

            if (u32Device == E_AHI_DEVICE_UART0)
            {
                u8ActiveUart = E_AHI_UART_0;
            }
            else
            {
                u8ActiveUart = E_AHI_UART_1;
            }
            u32ItemBitmap |= (((uint32)u8AHI_UartReadData(u8ActiveUart)) << 8);
        }
    }

    /* Get buffer for upward data */
    psBuffer = (AppQApiHwInd_s *)pvFifoPull(&sHwIndBufferQueue);

    /* If buffer available, put item on queue */
    if (psBuffer != NULL)
    {
        psBuffer->u32DeviceId = u32Device;
        psBuffer->u32ItemBitmap = u32ItemBitmap;
        bFifoPush(&sHwIndQueue, (void *)psBuffer);
    }

    /* Call callback. If there was no queue space, callback with empty
       queue indicates a problem */
    if (prAppHwCallback != NULL)
    {
        prAppHwCallback();
    }
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME:       psAppQApiGetMlmeBuffer
 *
 * DESCRIPTION:
 * Called by lower layer as a callback, this retrieves a buffer from the spare
 * buffer queue for MLME entries, or returns NULL if no buffer is available.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  pvParam         R   Unused
 *
 * RETURNS:
 * MAC_DcfmIndHdr_s * pointer to MLME buffer, or NULL
 *
 * NOTES:
 * Runs in interrupt context
 *
 ****************************************************************************/
PRIVATE MAC_DcfmIndHdr_s* psAppQApiGetMlmeBuffer(void *pvParam)
{
    return (MAC_DcfmIndHdr_s *)pvFifoPull(&sMlmeIndBufferQueue);
}

/****************************************************************************
 *
 * NAME:       psAppQApiGetMcpsBuffer
 *
 * DESCRIPTION:
 * Called by lower layer as a callback, this retrieves a buffer from the spare
 * buffer queue for MCPS entries, or returns NULL if no buffer is available.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  pvParam         R   Unused
 *
 * RETURNS:
 * MAC_DcfmIndHdr_s * pointer to MCPS buffer, or NULL
 *
 * NOTES:
 * Runs in interrupt context
 *
 ****************************************************************************/
PRIVATE MAC_DcfmIndHdr_s* psAppQApiGetMcpsBuffer(void *pvParam)
{
    return (MAC_DcfmIndHdr_s *)pvFifoPull(&sMcpsIndBufferQueue);
}

/****************************************************************************
 *
 * NAME:       vAppQApiPostMlme
 *
 * DESCRIPTION:
 * Called by lower layer as a callback, this places a buffer onto the used
 * buffers queue for MLME entries. If a callback to the application has been
 * defined, this is called as well.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  pvParam         R   Unused
 *                  psDcfmIndHdr    R   Pointer to queue entry
 *
 * RETURNS:
 * void
 *
 * NOTES:
 * Runs in interrupt context
 *
 ****************************************************************************/
PRIVATE void vAppQApiPostMlme(void *pvParam, MAC_DcfmIndHdr_s *psDcfmIndHdr)
{
    bFifoPush(&sMlmeIndQueue, (void *)psDcfmIndHdr);
    if (prAppMlmeCallback != NULL)
    {
        prAppMlmeCallback();
    }
}

/****************************************************************************
 *
 * NAME:       vAppQApiPostMcps
 *
 * DESCRIPTION:
 * Called by lower layer as a callback, this places a buffer onto the used
 * buffers queue for MCPS entries. If a callback to the application has been
 * defined, this is called as well.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  pvParam         R   Unused
 *                  psDcfmIndHdr    R   Pointer to queue entry
 *
 * RETURNS:
 * void
 *
 * NOTES:
 * Runs in interrupt context
 *
 ****************************************************************************/
PRIVATE void vAppQApiPostMcps(void *pvParam, MAC_DcfmIndHdr_s *psDcfmIndHdr)
{
    bFifoPush(&sMcpsIndQueue, (void *)psDcfmIndHdr);
    if (prAppMcpsCallback != NULL)
    {
        prAppMcpsCallback();
    }
}

/****************************************************************************
 *
 * NAME: vFifoInit
 *
 * DESCRIPTION:
 * Initialises a FIFO.
 *
 * PARAMETERS: Name         RW Usage
 *             psQueue      W  FIFO queue to initialise
 *             ppvDataStart R  Array of pointers used as queue contents
 *             u8Entries    R  Number of entries in array, and hence queue
 *
 * RETURNS:
 * void
 *
 * NOTES:
 *
 ****************************************************************************/
PUBLIC void vFifoInit(tsSFqueue *psQueue, void **ppvDataStart, uint8 u8Entries)
{
    psQueue->ppvReadPtr = &ppvDataStart[0];
    psQueue->ppvWritePtr = &ppvDataStart[0];
    psQueue->ppvQueueStart = &ppvDataStart[0];
    psQueue->ppvQueueEnd = &ppvDataStart[u8Entries];
}

/****************************************************************************
 *
 * NAME: pvFifoPull
 *
 * DESCRIPTION:
 * Takes the next entry from the FIFO, or NULL if the FIFO is empty.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  psQueue         R   FIFO from which to get entry
 *
 * RETURNS:
 * void * pointer to FIFO entry, or NULL if FIFO empty
 *
 ****************************************************************************/
PUBLIC void *pvFifoPull(tsSFqueue *psQueue)
{
    void *pvRetVal;

    if (psQueue->ppvReadPtr == psQueue->ppvWritePtr)
    {
        return (void *)NULL;
    }

    pvRetVal = *(psQueue->ppvReadPtr);

    if (psQueue->ppvReadPtr == psQueue->ppvQueueEnd)
    {
        psQueue->ppvReadPtr = psQueue->ppvQueueStart;
    }
    else
    {
        psQueue->ppvReadPtr++;
    }

    return pvRetVal;
}
/****************************************************************************
 *
 * NAME: bFifoPush
 *
 * DESCRIPTION:
 * Pushes an item onto the FIFO, if there is room
 *
 * PARAMETERS:      Name    RW  Usage
 *                  psQueue R   Queue to put item onto
 *                  pvData  R   Item to add
 *
 * RETURNS:
 * TRUE if item added successfully
 * FALSE if FIFO full
 *
 ****************************************************************************/
PUBLIC bool_t bFifoPush(tsSFqueue *psQueue, void *pvData)
{
    if (psQueue->ppvWritePtr == psQueue->ppvQueueEnd)
    {
        if (psQueue->ppvReadPtr == psQueue->ppvQueueStart)
        {
            return FALSE;
        }
    }
    else
    {
        if (psQueue->ppvReadPtr == (psQueue->ppvWritePtr + 1))
        {
            return FALSE;
        }
    }

    *(psQueue->ppvWritePtr) = pvData;

    if (psQueue->ppvWritePtr == psQueue->ppvQueueEnd)
    {
        psQueue->ppvWritePtr = psQueue->ppvQueueStart;
    }
    else
    {
        psQueue->ppvWritePtr++;
    }

    return TRUE;
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
