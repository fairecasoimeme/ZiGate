/****************************************************************************
 *
 * MODULE:			Serial Message Type Defines
 *
 * COMPONENT:       Serial MAC
 *
 * REVISION:     	$Revision: 73123 $
 *
 * DATED:			$Date: 2015-10-06 16:10:13 +0100 (Tue, 06 Oct 2015) $
 *
 * AUTHOR:   		$Author: nxp97442 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_MsgTypes.h $
 *
 * DESCRIPTION:		Defines the Message Types for the MAC-Host Serial
 *					protocol as defined in 802.15.4 MAC Serial Interface
 *
 * $Id: SMAC_MsgTypes.h 73123 2015-10-06 15:10:13Z nxp97442 $
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

#ifndef  SMAC_MSGTYPES_H_INCLUDED
#define  SMAC_MSGTYPES_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "SMAC_Common.h"



/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/



/* Message Type
 * ------------
 * The Message Type is a compound of bit fields used to indicate the nature of
 * the message.
 *
 *  Bit7 Bit6 Bit5 Bit4	Bit3 Bit2 Bit1 Bit0	Message Type
 *  ======================================================================
 *  0	 0	  x	   x	x	 x	  x	   x	SMT_TYPE = SMT_RPC_COMMAND
 *  0    1	  x	   x	x	 x	  x	   x	SMT_TYPE = SMT_RPC_INFO
 *  1    0	  x	   x	x	 x	  x	   x	SMT_TYPE = SMT_DEBUG
 *  1    1	  x	   x	x	 x	  x	   x	SMT_TYPE = SMT_SYNC
 *
 *	0    0	  0	   0	x	 x	  x	   x	SMT_RPC_COMMAND = RPC_API_RSVD
 *	0	 0	  0	   1	x	 x	  x	   x	SMT_RPC_COMMAND = RPC_API_MLME
 *	0	 0	  1	   0 	x	 x	  x	   x	SMT_RPC_COMMAND = RPC_API_MCPS
 *	0	 0	  1	   1	x	 x	  x	   x	SMT_RPC_COMMAND = RPC_API_MAC
 *
 *	0	 0    x	   x	0	 0	  0	   x	RPC_SUBTYPE_CALL
 *	0	 0	  x	   x	0	 0	  1	   x	RPC_SUBTYPE_RET
 *	0	 0	  x	   x	0	 1	  0	   x	RPC_SUBTYPE_REQ
 *	0	 0	  x	   x	0	 1	  1	   x	RPC_SUBTYPE_SCNF
 *	0	 0	  x	   x	1	 0	  0	   x	RPC_SUBTYPE_DCNF
 *	0	 0	  x	   x	1	 0	  1	   x	RPC_SUBTYPE_IND
 *	0	 0	  x	   x	1	 1	  0	   x	RPC_SUBTYPE_RSP
 *	0	 0	  x	   x	1	 1	  1	   x	RPC_SUBTYPE_RSVD
 *
 */

/* SMT_TYPE */
#define SMT_RPC_COMMAND						0x00				/* 00xxxxxx */
#define SMT_RPC_INFO						0x40				/* 01xxxxxx */
#define SMT_DEBUG							0x80				/* 10xxxxxx */
#define SMT_SYNC							0xC0				/* 11xxxxxx */
#define SMT_MASK							0xC0

/* SMT_SYNC Types */
#define SMT_SYNC_REQ						(SMT_SYNC | 0x15) 	/* 0xD5 */
#define SMT_SYNC_RSP						(SMT_SYNC | 0x2A)	/* 0xEA */

/* SMT_RPC_INFO Types */
#define RPC_API_NOT_SUPORTED				(SMT_RPC_INFO | 1)
#define RPC_API_NO_REPLY					(SMT_RPC_INFO | 2)
#define RPC_DEBUG_MESSAGE					(SMT_RPC_INFO | 3)
#define RPC_OTHER							(SMT_RPC_INFO | 4)

/* SMT_RPC_COMMAND Types */
#define RPC_API_RSVD						(SMT_RPC_COMMAND | 0x00)
#define RPC_API_MLME						(SMT_RPC_COMMAND | 0x10)
#define RPC_API_MCPS						(SMT_RPC_COMMAND | 0x20)
#define RPC_API_MAC_CALL					(SMT_RPC_COMMAND | 0x30)
#define RPC_API_MASK						0x30

/* SMT_RPC_API_SUBTYPE Types */
#define RPC_SUBTYPE_CALL					(SMT_RPC_COMMAND | 0x00)
#define RPC_SUBTYPE_RET						(SMT_RPC_COMMAND | 0x02)
#define RPC_SUBTYPE_REQ						(SMT_RPC_COMMAND | 0x04)
#define RPC_SUBTYPE_SCNF					(SMT_RPC_COMMAND | 0x06)
#define RPC_SUBTYPE_DCNF					(SMT_RPC_COMMAND | 0x08)
#define RPC_SUBTYPE_IND						(SMT_RPC_COMMAND | 0x0A)
#define RPC_SUBTYPE_RSP						(SMT_RPC_COMMAND | 0x0C)
#define RPC_SUBTYPE_RSVD					(SMT_RPC_COMMAND | 0x0E)
#define RPC_SUBTYPE_MASK					0x0E




/* API SUB TYPES FOR RPC_SUBTYPE_CALL
 * ----------------------------------
 * These are the API codes for the RPC_SUBTYPE_CALL and RPC_SUBTYPE_RET
 */

/* MAC API TYPES */
#define API_MAC_GET_STATUS_INFO					0x01
#define API_MAC_SLEEP							0x02

#define API_MAC_SET_SECURITY_MODE				0x11
#define API_MAC_SET_HIGH_POWER_MODE				0x12
#define API_MAC_SAVE_MAC_SETTINGS				0x13
#define API_MAC_RESTORE_MAC_SETTINGS			0x14
#define API_MAC_CURRENTLY_SCANNING				0x15
#define API_MAC_PIB_SET_PROMISCUOUS_MODE		0x16

/* PLME PIB ACCESSOR TYPES */
#define API_PHY_PLME_SET						0x50
#define API_PHY_PLME_GET						0x51

/* MAC PIB ACCESSOR API */
#define API_MAC_MLME_SET						0x60
#define API_MAC_MLME_GET						0x61

/* MAC POWER CONTROL API */
#define API_MAC_POWER_SET						0x70
#define API_MAC_POWER_GET						0x71
#define API_MAC_POWER_DELETE					0x72
#define API_MAC_POWER_SET_TABLE					0x73
#define API_MAC_POWER_GET_TABLE					0x74
#define API_MAC_POWER_CLEAR_TABLE				0x75

/* MIB IEEE TABLE API */
#define API_MIBIEEE_SET_POLICY					0x80
#define API_MIBIEEE_GET_POLICY					0x81
#define API_MIBIEEE_GET_COUNT					0x82
#define API_MIBIEEE_ADD							0x83
#define API_MIBIEEE_SET_TABLE					0x84
#define API_MIBIEEE_GET_TABLE					0x85

/* MAC PROGRAMMING */
#define API_MAC_ENTER_PROGRAMMING_MODE			0xE0

#define API_MAC_BAD_PARAMS						0xFF

#if defined __cplusplus
}
#endif

#endif  /* SMAC_MSGTYPES_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

