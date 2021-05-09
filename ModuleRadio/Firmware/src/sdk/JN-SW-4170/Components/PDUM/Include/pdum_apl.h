/*****************************************************************************
 *
 * MODULE:             PDU Manager
 *
 * COMPONENT:          pdum_app.h
 *
 * AUTHOR:             MRW
 *
 * DESCRIPTION:        PDU manager interface for application
 *                     Manages APDUs
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Cortex/Modules/PDUManager/Modules/PDUM/Trunk/Include/pdum_apl.h $
 *
 * $Revision: 84024 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2016-10-12 14:18:30 +0100 (Wed, 12 Oct 2016) $
 *
 * $Id: pdum_apl.h 84024 2016-10-12 13:18:30Z nxp29741 $
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
 * Copyright Jennic Ltd. 2008 All rights reserved
 *
 ****************************************************************************/

#ifndef PDUM_APP_H_
#define PDUM_APP_H_

#include "pdum_common.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* APDU instance handle */
typedef const struct pdum_tsAPduInstance_tag *PDUM_thAPduInstance;

/* APDU handle */
typedef const struct pdum_tsAPdu_tag *PDUM_thAPdu;

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Public Functions                                     ***/
/****************************************************************************/

PUBLIC uint16 PDUM_u16APduInstanceReadNBO(PDUM_thAPduInstance hAPduInst, uint16 u16Pos, const char *szFormat, void *pvStruct);
PUBLIC uint16 PDUM_u16APduInstanceWriteNBO(PDUM_thAPduInstance hAPduInst, uint16 u16Pos, const char *szFormat, ...);
PUBLIC uint16 PDUM_u16APduInstanceWriteStrNBO(PDUM_thAPduInstance hAPduInst, uint16 u16Pos, const char *szFormat, void *pvStruct);
PUBLIC void * PDUM_pvAPduInstanceGetPayload(PDUM_thAPduInstance hAPduInst);
PUBLIC uint16 PDUM_u16APduInstanceGetPayloadSize(PDUM_thAPduInstance hAPduInst);
PUBLIC PDUM_teStatus PDUM_eAPduInstanceSetPayloadSize(PDUM_thAPduInstance hAPduInst, uint16 u16Size);
PUBLIC PDUM_thAPdu PDUM_thAPduInstanceGetApdu(PDUM_thAPduInstance hAPduInst);

PUBLIC PDUM_thAPduInstance PDUM_hAPduAllocateAPduInstance(PDUM_thAPdu hAPdu);
PUBLIC PDUM_teStatus PDUM_eAPduFreeAPduInstance(PDUM_thAPduInstance hAPduInst);
PUBLIC uint16 PDUM_u16APduGetSize(PDUM_thAPdu hAPdu);

PUBLIC uint8 u8GetMaxApdu(void);
PUBLIC uint8 u8GetApduUse(void);

#ifdef DBG_ENABLE
PUBLIC void PDUM_vDBGPrintAPduInstance(PDUM_thAPduInstance hAPduInst);
#else
#define PDUM_vDBGPrintAPduInstance(apdu)
#endif

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#endif /*PDUM_APDU_H_*/
