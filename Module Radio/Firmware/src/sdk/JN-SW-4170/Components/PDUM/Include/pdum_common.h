/*****************************************************************************
 *
 * MODULE:             PDU Manager
 *
 * COMPONENT:          pdum_common.h
 *
 * AUTHOR:             MRW
 *
 * DESCRIPTION:        PDU manager common definitions
 *                     Manages NPDUs
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Cortex/Modules/PDUManager/Modules/PDUM/Trunk/Include/pdum_common.h $
 *
 * $Revision: 13024 $
 *
 * $LastChangedBy: mwild $
 *
 * $LastChangedDate: 2009-05-22 13:48:28 +0100 (Fri, 22 May 2009) $
 *
 * $Id: pdum_common.h 13024 2009-05-22 12:48:28Z mwild $
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

#ifndef PDUM_COMMON_H_
#define PDUM_COMMON_H_

#include "jendefs.h"

/* ensure pdum_common.h is only included from pdum_nwk or pdum_app headers */
#if !(defined(PDUM_NWK_H_) || defined(PDUM_APP_H_))
#error "pdum_common.h should not be directly included. Include either pdum_nwk.h or pdum_app.h"
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define PDUM_INVALID_HANDLE     NULL

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Status return codes */
typedef enum {
    PDUM_E_OK,
    PDUM_E_INVALID_HANDLE,
    PDUM_E_BAD_DIRECTION,
    PDUM_E_BAD_PARAM,
    PDUM_E_NPDUS_EXHAUSTED,
    PDUM_E_NPDU_TOO_BIG,
    PDUM_E_NPDU_ALREADY_FREE,
    PDUM_E_APDU_INSTANCE_ALREADY_FREE,
    PDUM_E_APDU_INSTANCE_TOO_BIG,
    PDUM_E_INTERNAL_ERROR
} PDUM_teStatus;

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC uint16 PDUM_u16SizeNBO(const char *szFormat);

#endif /*PDUMAN_H_*/

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
