/****************************************************************************
 *
 * MODULE:    ZQueue.c
 *
 * DESCRIPTION:
 *
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
 *
 ***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include "MicroSpecific.h"
#include "ZQueue.h"
#include "dbg.h"
#include "pwrm.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#ifdef DEBUG_ZQUEUE
#define TRACE_ZQUEUE    TRUE
#else
#define TRACE_ZQUEUE    FALSE
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/


/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

PUBLIC void ZQ_vQueueCreate ( tszQueue*       psQueueHandle, 
                              const uint32    u32QueueLength, 
                              const uint32    u32ItemSize, 
                              uint8*          pu8StartQueue )
{
        psQueueHandle->pvHead =  pu8StartQueue;
        psQueueHandle->u32ItemSize =  u32ItemSize;
        psQueueHandle->u32Length =  u32QueueLength;
        psQueueHandle->pvWriteTo =  psQueueHandle->pvHead;
        psQueueHandle->u32MessageWaiting =  0;
        psQueueHandle->pvReadFrom =  psQueueHandle->pvHead;
        DBG_vPrintf(TRACE_ZQUEUE, "ZQ: Initialised a queue: Handle=%08x Length=%d ItemSize=%d\n", (uint32)psQueueHandle, u32QueueLength, u32ItemSize);

}

PUBLIC bool_t ZQ_bQueueSend ( void*          pvQueueHandle, 
                              const void*    pvItemToQueue )
{

    uint32 u32Store;
    tszQueue *psQueueHandle = (tszQueue *)pvQueueHandle;
    bool bReturn = FALSE;
    MICRO_DISABLE_AND_SAVE_INTERRUPTS(u32Store);
    if(psQueueHandle->u32MessageWaiting >= psQueueHandle->u32Length)
    {
        DBG_vPrintf(TRACE_ZQUEUE, "ZQ: Queue overflow: Handle=%08x\n", (uint32)pvQueueHandle);
    }
    else
    {        
        if( psQueueHandle->pvWriteTo >= (psQueueHandle->pvHead+(psQueueHandle->u32Length*psQueueHandle->u32ItemSize)))
        {
             psQueueHandle->pvWriteTo = psQueueHandle->pvHead;
        }
        ( void ) memcpy( psQueueHandle->pvWriteTo, pvItemToQueue, psQueueHandle->u32ItemSize );
        psQueueHandle->u32MessageWaiting++;
        psQueueHandle->pvWriteTo += psQueueHandle->u32ItemSize;
        
        /* Increase power manager activity count */
        PWRM_eStartActivity();        
        bReturn = TRUE;
    }
    MICRO_RESTORE_INTERRUPTS(u32Store);
    return bReturn;
}

PUBLIC bool_t ZQ_bQueueReceive ( void*    pvQueueHandle, 
                                 void*    pvItemFromQueue )
{
    uint32 u32Store;
    tszQueue *psQueueHandle = (tszQueue *)pvQueueHandle;
    bool bReturn = FALSE;
    MICRO_DISABLE_AND_SAVE_INTERRUPTS(u32Store);
    if( psQueueHandle->u32MessageWaiting >  0)
    {
        if( psQueueHandle->pvReadFrom >= (psQueueHandle->pvHead+(psQueueHandle->u32Length*psQueueHandle->u32ItemSize) ))
        {
            psQueueHandle->pvReadFrom = psQueueHandle->pvHead;
        }
        ( void ) memcpy( pvItemFromQueue, psQueueHandle->pvReadFrom, psQueueHandle->u32ItemSize );
        psQueueHandle->pvReadFrom += psQueueHandle->u32ItemSize;
        psQueueHandle->u32MessageWaiting--;
        
        /* Decrease power manager activity count */
        PWRM_eFinishActivity();
        bReturn = TRUE;        
    }
    else
    {
        bReturn =  FALSE;
    }
    MICRO_RESTORE_INTERRUPTS(u32Store);
    return bReturn;
}

PUBLIC bool_t ZQ_bQueueIsEmpty ( void*    pu8QueueHandle )
{
    uint32 u32Store;
    tszQueue *psQueueHandle = (tszQueue *)pu8QueueHandle;
    bool bReturn = FALSE;
    MICRO_DISABLE_AND_SAVE_INTERRUPTS(u32Store);
    if (psQueueHandle->u32MessageWaiting == 0)
    {
        bReturn = TRUE;
    }
    else
    {
        bReturn = FALSE;
    }
    MICRO_RESTORE_INTERRUPTS(u32Store);
    return (bReturn);
}


PUBLIC uint32 ZQ_u32QueueGetQueueSize ( void*    pu8QueueHandle )
{
    tszQueue *psQueueHandle = (tszQueue *)pu8QueueHandle;
    return psQueueHandle->u32Length;
}

PUBLIC uint32 ZQ_u32QueueGetQueueMessageWaiting ( void*    pu8QueueHandle )
{
    tszQueue *psQueueHandle = (tszQueue *)pu8QueueHandle;
    return psQueueHandle->u32MessageWaiting;
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
