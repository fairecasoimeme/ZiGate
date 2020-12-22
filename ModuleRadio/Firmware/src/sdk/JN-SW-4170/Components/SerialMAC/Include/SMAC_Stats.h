/****************************************************************************
 *
 * MODULE:			SMAC_Stats
 *
 * COMPONENT:       SerialMAC
 *
 * REVISION:     	$Revision: 76279 $
 *
 * DATED:			$Date: 2016-01-21 14:22:25 +0000 (Thu, 21 Jan 2016) $
 *
 * AUTHOR:   		$Author: nxp97442 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_Stats.h $
 *
 * DESCRIPTION:		Implements statistic and debug info for SerialMAC interface
 *
 * $Id: SMAC_Stats.h 76279 2016-01-21 14:22:25Z nxp97442 $
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

#ifndef  SMAC_STATS_H_INCLUDED
#define  SMAC_STATS_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "SMAC_MsgTypes.h"
#include "SMAC_Protocol.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef SMAC_INLINE
#define SMAC_INLINE INLINE
#endif

#ifndef SMAC_ALWAYS_INLINE
#define SMAC_ALWAYS_INLINE ALWAYS_INLINE
#endif


/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef struct
{
	uint32	u32TxBytes;
	uint32 	u32RxBytes;
	uint16	u16RxFifoHigh;
	uint16	u16TxFifoHigh;
	uint8	u8CRCError;
	uint8 	u8TXFull;

}SMAC_Stats_s;

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
extern SMAC_Stats_s	s_sSMAC_Stats;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void 	vSSTAT_Reset(void);
PUBLIC void 	vSSTAT_Get(SMAC_Stats_s *psStats);

/****************************************************************************/
/***        Inline Functions                                              ***/
/****************************************************************************/

SMAC_INLINE void vSTAT_Tx(void) SMAC_ALWAYS_INLINE;
SMAC_INLINE void vSTAT_Tx(void)
{
	s_sSMAC_Stats.u32TxBytes++;
}
SMAC_INLINE void vSTAT_Rx(void) SMAC_ALWAYS_INLINE;
SMAC_INLINE void vSTAT_Rx(void)
{
	s_sSMAC_Stats.u32RxBytes++;
}
SMAC_INLINE void vSTAT_RxFifo(uint16 u16Rx) SMAC_ALWAYS_INLINE;
SMAC_INLINE void vSTAT_RxFifo(uint16 u16Rx)
{
	if(u16Rx > s_sSMAC_Stats.u16RxFifoHigh)
	{
		s_sSMAC_Stats.u16RxFifoHigh = u16Rx;
	}
}
SMAC_INLINE void vSTAT_TxFifo(uint16 u16Tx) SMAC_ALWAYS_INLINE;
SMAC_INLINE void vSTAT_TxFifo(uint16 u16Tx)
{
	if(u16Tx > s_sSMAC_Stats.u16TxFifoHigh)
	{
		s_sSMAC_Stats.u16TxFifoHigh = u16Tx;
	}
}
SMAC_INLINE void vSTAT_CRCError(void) SMAC_ALWAYS_INLINE;
SMAC_INLINE void vSTAT_CRCError(void)
{
	s_sSMAC_Stats.u8CRCError++;
}
SMAC_INLINE void vSTAT_TxFull(void) SMAC_ALWAYS_INLINE;
SMAC_INLINE void vSTAT_TxFull(void)
{
	s_sSMAC_Stats.u8TXFull++;
}



#if defined __cplusplus
}
#endif

#endif  /* SMAC_STATS_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

