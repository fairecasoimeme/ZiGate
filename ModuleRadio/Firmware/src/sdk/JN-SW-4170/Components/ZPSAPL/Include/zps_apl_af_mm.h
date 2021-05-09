/****************************************************************************
 *
 * MODULE:			Zigbee Protocol Stack Application Layer
 *
 * COMPONENT:       zps_apl_af_mm.h
 *
 * REVISION:     	$Revision: 87673 $
 *
 * DATED:			$Date: 2017-03-31 16:43:26 +0100 (Fri, 31 Mar 2017) $
 *
 * AUTHOR:   		$Author: nxp29741 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Zigbee%20Protocol%20Stack/Modules/APL/Trunk/Include/zps_apl_af_mm.h $
 *
 * DESCRIPTION:		Multi Mask API
 *
 * $Id: zps_apl_af_mm.h 87673 2017-03-31 15:43:26Z nxp29741 $
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


#ifndef ZPS_APL_AF_MM_H_
#define ZPS_APL_AF_MM_H_

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <mac_vs_sap.h>
#include <zps_nwk_sap.h>
#include <pdum_apl.h>
#include <zps_apl.h>
#include <zps_apl_aps.h>
#ifndef ZPS_APL_OPT_MULTIPLE_INSTANCES
#include <zps_apl_zdo.h>
#endif
#include <zps_apl_zdp.h>
#include <zps_apl_aib.h>
#include <zps_apl_af.h>

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#ifndef ZPS_APL_MM_INLINE
#define ZPS_APL_MM_INLINE  INLINE
#endif


#ifndef ZPS_APL_MM_ALWAYS_INLINE
#define ZPS_APL_MM_ALWAYS_INLINE  ALWAYS_INLINE
#endif




/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/









/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/


PUBLIC 	void 			zps_vAplZdoHandleNlmeDcfmIndMM(void *pvApl, ZPS_tsNwkDcfmIndHdr * psNwkDcfmIndHdr);







/****************************************************************************/
/***        Exported Private Functions (must not be called by ZPS user)     */
/****************************************************************************/


/****************************************************************************/
/***        In-line Functions                                            ***/
/****************************************************************************/



/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/



#endif /*ZPS_APL_AF_MM_H_*/
