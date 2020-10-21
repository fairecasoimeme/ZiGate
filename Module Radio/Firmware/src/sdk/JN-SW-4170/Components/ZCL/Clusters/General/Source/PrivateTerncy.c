/*****************************************************************************
 *
 * MODULE:             Private Terncy
 *
 * COMPONENT:          PrivateTerncy.c
 *
 * AUTHOR:             Akila
 *
 * DESCRIPTION:        Private Terncy cluster definition
 *
 * $HeadURL: $
 *
 * $Revision: 0 $
 *
 * $LastChangedBy: akila $
 *
 * $LastChangedDate: 2018-11-25 $
 *
 *
*/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "zcl.h"
#include "zcl_internal.h"
#include "zcl_customcommand.h"
#include "PrivateTerncy.h"
#include "zcl_options.h"
//#include "log.h"

#include "app_common.h"

#ifdef CLD_PRIVATE_TERNCY

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

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
uAttribData uAttributeVal;

   const tsZCL_AttributeDefinition asCLD_PrivatTerncyClusterAttributeDefinitions [] = {

    };

    tsZCL_ClusterDefinition sCLD_PrivateTerncy = {
    		GENERAL_CLUSTER_PRIVATE_TERNCY,
            FALSE,
            E_ZCL_SECURITY_NETWORK,
            (sizeof(asCLD_PrivatTerncyClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
            (tsZCL_AttributeDefinition*)asCLD_PrivatTerncyClusterAttributeDefinitions,
            NULL
    };
    uint8 au8PrivateTerncyAttributeControlBits[(sizeof(asCLD_PrivatTerncyClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];



/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       ePrivateTerncyCommandHandler
 **
 ** DESCRIPTION: Command Handler for Private Terncy command
 **
 ** PARAMETERS:
  ***pZPSevent                  : ZPS Event
 ***psEndPointDefinition     : End point definition details.
 ***psClusterInstance         : Private Terncy Cluster Instance
 ***
 ** RETURN:
 **teZCL_Status
 **
 **
 ****************************************************************************/
PUBLIC  teZCL_Status ePrivateTerncyCommandHandler(
					ZPS_tsAfEvent               *pZPSevent,
					tsZCL_EndPointDefinition    *psEndPointDefinition,
					tsZCL_ClusterInstance       *psClusterInstance)
{

	tsZCL_HeaderParams sZCL_HeaderParams;
	teZCL_Status eStatus  = E_ZCL_SUCCESS;

	tsZCL_CallBackEvent sZCL_CallBackEvent;
	// fill in non-attribute specific values in callback event structure
	sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
	sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
	sZCL_CallBackEvent.pZPSevent = pZPSevent;
	sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_INDIVIDUAL_ATTRIBUTE;
	sZCL_CallBackEvent.eZCL_Status = E_ZCL_SUCCESS;


	u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
	                                              &sZCL_HeaderParams);

	sZCL_CallBackEvent.u8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;
	sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.u16AttributeEnum=0;
	sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeStatus = E_ZCL_CMDS_SUCCESS;
	sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType = E_ZCL_UINT8;
	uAttributeVal.u8Data = sZCL_HeaderParams.u8CommandIdentifier;
	sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.pvAttributeData = (void *)&uAttributeVal;
	psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);


	return eStatus;
}

/****************************************************************************
 *
 * NAME:       eCLD_PrivateTerncyCreate
 *
 * DESCRIPTION:
 * Creates a Terncy private cluster
 *
 * PARAMETERS:  Name                         Usage
 *              psClusterInstance            Cluster structure
 *              bIsServer                    Server/Client Flag
 *              psClusterDefinition          Cluster Definitation
 *              pvEndPointSharedStructPtr    EndPoint Shared Structure Pointer
 *              pu8AttributeControlBits      Attribute Control Bits
 * RETURN:
 * teZCL_Status
 *
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_PrivateTerncyCreate(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits)
{

	#ifdef STRICT_PARAM_CHECK
		/* Parameter check */
		if((psClusterInstance==NULL) ||
		   (psClusterDefinition==NULL))
		{
			return E_ZCL_ERR_PARAMETER_NULL;
		}
	#endif

    /* Create an instance of a analog input basic cluster */
 vZCL_InitializeClusterInstance(
   psClusterInstance,
   bIsServer,
   psClusterDefinition,
   pvEndPointSharedStructPtr,
   pu8AttributeControlBits,
   NULL,
   ePrivateTerncyCommandHandler);

	/* Initialise attributes defaults */
	if(psClusterInstance->pvEndPointSharedStructPtr != NULL)
	{

	}


	/* As this cluster has reportable attributes enable default reporting */
	vZCL_SetDefaultReporting(psClusterInstance);

    return E_ZCL_SUCCESS;

}


#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

