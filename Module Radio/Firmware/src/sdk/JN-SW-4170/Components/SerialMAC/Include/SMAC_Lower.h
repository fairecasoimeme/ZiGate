/****************************************************************************
 *
 * MODULE:			SerialMAC_Lower.h
 *
 * COMPONENT:       SerialMAC
 *
 * REVISION:     	$Revision: 69515 $
 *
 * DATED:			$Date: 2015-05-06 13:00:33 +0100 (Wed, 06 May 2015) $
 *
 * AUTHOR:   		$Author: nxp97442 $
 *
 * URL:				$HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/SerialMAC/Trunk/Include/SMAC_Lower.h $
 *
 * DESCRIPTION:		Implements the Serial MAC Lower Layer (MAC Side) interface
 * 					as defined in 802.15.4 MAC Serial Interface V1.0 [doc142933].
 * 					This provides an interface to a Serial MAC Channel and
 * 					encapsulates the Remote Process Calls across the serial
 * 					link from the Serial MAC Upper Layer (Host Side) interface.
 *
 * $Id: SMAC_Lower.h 69515 2015-05-06 12:00:33Z nxp97442 $
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

#ifndef  SMAC_LOWER_H_INCLUDED
#define  SMAC_LOWER_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include "AppApi.h"
#include "SMAC_Common.h"



/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/


/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/


/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC bool bSML_AppInit(	uint8 u8Channel,
						PR_GET_BUFFER prMlmeGetBuffer,
              	  	   	PR_GET_BUFFER prMcpsGetBuffer,
              	  	   	PR_RELEASE_BUFFER prMlmeReleaseBuffer,
              	  	   	PR_RELEASE_BUFFER prMcpsReleaseBuffer);

PUBLIC bool bSML_ApiRun(void);

PUBLIC bool bSML_ApiSync(void);

PUBLIC void vSML_ApiErrorCallback(SMAC_API_ERROR_CALLBACK prCallback);



/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* SMAC_LOWER_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

