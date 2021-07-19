/****************************************************************************
 *
 * MODULE:              Time-Of-Flight API header
 *
 * DESCRIPTION:
 * Access functions and structures used by the application to interact with
 * the Jennic Time-Of-Flight mechanism
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
 * Copyright NXP B.V. 2014. All rights reserved
 *
 ***************************************************************************/

#ifndef _mac_tof_h_
#define _mac_tof_h_

#ifdef __cplusplus
extern "C" {
#endif


/***********************/
/**** INCLUDE FILES ****/
/***********************/
#include "jendefs.h"
#include "mac_sap.h"
#include "mac_prv.h"
#include "AppApiTof.h"

/************************/
/**** MACROS/DEFINES ****/
/************************/

/***************/
/**** Frame ****/
/***************/

/**** Broadcast IDs ****/


/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/

/**
 * MAC Result code
 * @ingroup grp_MAC
 */


/****************************/
/**** EXPORTED VARIABLES ****/
/****************************/

/****************************/
/**** EXPORTED FUNCTIONS ****/
/****************************/
PUBLIC void vTOF_Init(bool_t bEnable);
PUBLIC void vTOF_SetCalloffset(int32 s32pSecs);

#ifdef JENNIC_CHIP_FAMILY_JN514x
PUBLIC void MAC_vHandleTOFMlmeReqRsp(void *pvMac,
                      MAC_MlmeReqRsp_s *psMlmeReqRsp,
                      MAC_MlmeSyncCfm_s *psMlmeSyncCfm);
PUBLIC void vTOFProcessFrameRXComplete(tsGenFrameHeader *psRXframe);
#endif

PUBLIC bool_t bTOF_StartForwards(MAC_Addr_s *pAddr, uint8 u8TofNumberReadings, tsAppApiTof_Data *pTofData, PR_TOF_APPCALLBACK prTofCallback);
PUBLIC bool_t bTOF_StartReverse(MAC_Addr_s *pAddr, uint8 u8TofNumberReadings, tsAppApiTof_Data *pTofData, PR_TOF_APPCALLBACK prTofCallback);
PUBLIC void vTOF_SetCalloffset(int32 s32pSecs);
PUBLIC int32 s32TOF_GetCalloffset(void);

#ifdef JENNIC_CHIP_FAMILY_JN514x

/* Lookup table to access TOF functions */
#define TOF_VECTOR_TABLE_ENTRIES 8

#define TOF_POLLREQUEST_VECTOR       0
#define TOF_PRIMEREQUEST_VECTOR      1
#define TOF_DATAPOLLREQUEST_VECTOR   2
#define TOF_DATAREQUEST_VECTOR       3
#define TOF_POLLRECEIVED_VECTOR      4
#define TOF_DATARECEIVED_VECTOR      5
#define TOF_DATAPOLLRECEIVED_VECTOR  6
#define TOF_PRIMERECEIVED_VECTOR     7

extern void *aprTofVectorRamTable[TOF_VECTOR_TABLE_ENTRIES];

typedef void (*tprTOFRequest)(MAC_s *, MAC_MlmeReqRsp_s *, MAC_MlmeSyncCfm_s *);
typedef void (*tprTOFReceived)(tsGenFrameHeader *);

#define vTOFPollRequestVector ((tprTOFRequest)(aprTofVectorRamTable[TOF_POLLREQUEST_VECTOR]))
#define vTOFPrimeRequestVector ((tprTOFRequest)(aprTofVectorRamTable[TOF_PRIMEREQUEST_VECTOR]))
#define vTOFDataPollRequestVector ((tprTOFRequest)(aprTofVectorRamTable[TOF_DATAPOLLREQUEST_VECTOR]))
#define vTOFDataRequestVector ((tprTOFRequest)(aprTofVectorRamTable[TOF_DATAREQUEST_VECTOR]))
#define vTOFPollReceivedVector ((tprTOFReceived)(aprTofVectorRamTable[TOF_POLLRECEIVED_VECTOR]))
#define vTOFDataReceivedVector ((tprTOFReceived)(aprTofVectorRamTable[TOF_DATARECEIVED_VECTOR]))
#define vTOFDataPollReceivedVector ((tprTOFReceived)(aprTofVectorRamTable[TOF_DATAPOLLRECEIVED_VECTOR]))
#define vTOFPrimeReceivedVector ((tprTOFReceived)(aprTofVectorRamTable[TOF_PRIMERECEIVED_VECTOR]))

#endif

#ifdef __cplusplus
};
#endif

#endif /* _mac_tof_h_ */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
