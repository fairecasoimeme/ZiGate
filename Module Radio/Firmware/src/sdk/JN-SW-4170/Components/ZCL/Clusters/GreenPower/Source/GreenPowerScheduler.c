/*****************************************************************************
 *
 * MODULE:             Green Power Scheduler
 *
 * COMPONENT:          GreenPowerScheduler.c
 *
 * AUTHOR:             Ramakrishna
 *
 * DESCRIPTION:        The Green Power Cluster Scheduler functions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/GreenPower/Source/GreenPowerScheduler.c $
 *
 * $Revision: 80174 $
 *
 * $LastChangedBy: nxp29757 $
 *
 * $LastChangedDate: 2016-06-07 12:45:17 +0200 (Tue, 07 Jun 2016) $
 *
 * $Id: GreenPowerScheduler.c 80174 2016-06-07 10:45:17Z nxp29757 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products  [NXP Microcontrollers such as JN5168, JN5164,
 * JN5161, JN5148, JN5142, JN5139].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each  copy or partial copy of the software.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <string.h>
#include "dlist.h"
#include "zcl.h"
#include "GreenPower.h"
#include "GreenPower_internal.h"
#include "dbg.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef TRACE_GP_DEBUG
#define TRACE_GP_DEBUG FALSE
#endif

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
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME: eGP_Update20mS
 *
 * DESCRIPTION:
 * Should be called by an application timer 50 times per second
 *
 * PARAMETERS:  Name                            Usage
 * uint8        u8GreenPowerEndPointId          Local Green Power End Point Id
 *
 * RETURNS:
 * teZCL_Status
 *
 ****************************************************************************/
PUBLIC teZCL_Status eGP_Update20mS(uint8 u8GreenPowerEndPointId) {
	teZCL_Status etatus = E_ZCL_SUCCESS;
	bool bIsServer = TRUE;
	tsZCL_EndPointDefinition *psEndPointDefinition;
	tsZCL_ClusterInstance *psClusterInstance;
	tsGP_GreenPowerCustomData *psGpCustomDataStructure;
	uint8 u8Loop;
	tsGP_ZgpDuplicateTable *psZgpDuplicateTable;

	if ((etatus = eGP_FindGpCluster(u8GreenPowerEndPointId, bIsServer,
			&psEndPointDefinition, &psClusterInstance, &psGpCustomDataStructure))
			!= E_ZCL_SUCCESS) {
		bIsServer = FALSE;

		if ((etatus = eGP_FindGpCluster(u8GreenPowerEndPointId, bIsServer,
				&psEndPointDefinition, &psClusterInstance,
				&psGpCustomDataStructure)) != E_ZCL_SUCCESS) {
			return etatus;
		}
	}

	// get EP mutex
#ifndef COOPERATIVE
	eZCL_GetMutex(psEndPointDefinition);
#endif

	/* Handling Proxy Commission Mode Timeout */
	if (psGpCustomDataStructure->u16CommissionWindow) {
		/* Decrement and if value is zero exit commission mode */
		if ((--psGpCustomDataStructure->u16CommissionWindow == 0x00)
				&& (psGpCustomDataStructure->eGreenPowerDeviceMode
						!= E_GP_OPERATING_MODE)) {
			vGP_ExitCommMode(psEndPointDefinition,
					psGpCustomDataStructure);
		}
	}
	/* Handling transmit channel Timeout */
	if (psGpCustomDataStructure->u16TransmitChannelTimeout) {
		/* Decrement and if value is zero change channel to operational */
		if (--psGpCustomDataStructure->u16TransmitChannelTimeout == 0x00) {
            DBG_vPrintf(TRACE_GP_DEBUG, "\n eGP_Update20mS: setting channel to back to operating = %d  \n", psGpCustomDataStructure->u8OperationalChannel);
#ifndef PC_PLATFORM_BUILD
			ZPS_vNwkNibSetChannel(ZPS_pvAplZdoGetNwkHandle(),
					psGpCustomDataStructure->u8OperationalChannel);
#endif
		}
	}
	/* initialize duplicate filter table pointer */
		psZgpDuplicateTable = psGpCustomDataStructure->asZgpDuplicateFilterTable;

	/* Handling Duplicate Filter Timeout Table */
	for (u8Loop = 0; u8Loop < GP_MAX_DUPLICATE_TABLE_ENTIRES; u8Loop++) {
		/* Decrement only if aging time is non zero value */
		if (psZgpDuplicateTable[u8Loop].u16AgingTime) {
			psZgpDuplicateTable[u8Loop].u16AgingTime--;
			break;
		}
	}
	/*vGp_TransmissionTimerCallback(u8GreenPowerEndPointId, psEndPointDefinition,
			psGpCustomDataStructure);*/

	// release mutex
#ifndef COOPERATIVE
	eZCL_ReleaseMutex(psEndPointDefinition);
#endif

	return etatus;
}

/****************************************************************************
 *
 * NAME: eGP_Update1mS
 *
 * DESCRIPTION:
 * Should be called by an application timer every 1 ms
 *
 * PARAMETERS:  Name                            Usage
 * uint8        u8GreenPowerEndPointId          Local Green Power End Point Id
 *
 * RETURNS:
 * teZCL_Status
 *
 ****************************************************************************/
PUBLIC teZCL_Status eGP_Update1mS(uint8 u8GreenPowerEndPointId) {
	teZCL_Status etatus = E_ZCL_SUCCESS;

	bool bIsServer = TRUE;
	tsZCL_EndPointDefinition *psEndPointDefinition;
	tsZCL_ClusterInstance *psClusterInstance;
	tsGP_GreenPowerCustomData *psGpCustomDataStructure;

	if ((etatus = eGP_FindGpCluster(u8GreenPowerEndPointId, bIsServer,
			&psEndPointDefinition, &psClusterInstance, &psGpCustomDataStructure))
			!= E_ZCL_SUCCESS) {
		bIsServer = FALSE;

		if ((etatus = eGP_FindGpCluster(u8GreenPowerEndPointId, bIsServer,
				&psEndPointDefinition, &psClusterInstance,
				&psGpCustomDataStructure)) != E_ZCL_SUCCESS) {
			return etatus;
		}
	}

	// get EP mutex
#ifndef COOPERATIVE
	eZCL_GetMutex(psEndPointDefinition);
#endif

	vGp_TransmissionTimerCallback(u8GreenPowerEndPointId, psEndPointDefinition,
			psGpCustomDataStructure);


	// release mutex
#ifndef COOPERATIVE
	eZCL_ReleaseMutex(psEndPointDefinition);
#endif

	return etatus;

}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
