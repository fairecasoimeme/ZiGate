/****************************************************************************
 *
 * MODULE:			SMAC_Queue
 *
 * COMPONENT:       SerialMAC
 *
 * REVISION:     	$Revision: 69515 $
 *
 * DATED:			$Date: 2015-05-06 13:00:33 +0100 (Wed, 06 May 2015) $
 *
 * AUTHOR:   		$Author: nxp97442 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_Queue.h $
 *
 * DESCRIPTION:		Implements a FIFO queue which is used in Serial MAC
 * 					to handle memory and queue events
 *
 * $Id: SMAC_Queue.h 69515 2015-05-06 12:00:33Z nxp97442 $
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

#ifndef  SMAC_QUEUE_H_INCLUDED
#define  SMAC_QUEUE_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>


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

} SM_FifoQueue_s;




/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void vSQ_FifoInit(SM_FifoQueue_s *psQueue, void **ppvDataStart, uint8 u8Entries);
PUBLIC void *pvSQ_FifoPull(SM_FifoQueue_s *psQueue);
PUBLIC bool bSQ_FifoPush(SM_FifoQueue_s *psQueue, void *pvData);



#if defined __cplusplus
}
#endif

#endif  /* SMAC_QUEUE_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

