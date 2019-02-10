/*****************************************************************************
 *
 * MODULE:             Private Philips
 *
 * COMPONENT:          PrivatPhilips.c
 *
 * AUTHOR:             Akila
 *
 * DESCRIPTION:        Private Philips cluster definition
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
#include "PrivatePhilips.h"
#include "zcl_options.h"
#include "log.h"

#include "app_common.h"

#ifdef CLD_PRIVATE_PHILIPS

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

   const tsZCL_AttributeDefinition asCLD_PrivatPhilipsClusterAttributeDefinitions [] = {

    };

    tsZCL_ClusterDefinition sCLD_PrivatePhilips = {
    		GENERAL_CLUSTER_PRIVATE_PHILIPS,
            FALSE,
            E_ZCL_SECURITY_NETWORK,
            (sizeof(asCLD_PrivatPhilipsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
            (tsZCL_AttributeDefinition*)asCLD_PrivatPhilipsClusterAttributeDefinitions,
            NULL
    };
    uint8 au8PrivatePhilipsAttributeControlBits[(sizeof(asCLD_PrivatPhilipsClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];



/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       ePrivatePhilipsCommandHandler
 **
 ** DESCRIPTION: Command Handler for Private Philips command
 **
 ** PARAMETERS:
  ***pZPSevent                  : ZPS Event
 ***psEndPointDefinition     : End point definition details.
 ***psClusterInstance         : Private Philips Cluster Instance
 ***
 ** RETURN:
 **teZCL_Status
 **
 **
 ****************************************************************************/
PUBLIC  teZCL_Status ePrivatePhilipsCommandHandler(
					ZPS_tsAfEvent               *pZPSevent,
					tsZCL_EndPointDefinition    *psEndPointDefinition,
					tsZCL_ClusterInstance       *psClusterInstance)
{

	tsZCL_HeaderParams sZCL_HeaderParams;
	teZCL_Status eStatus  = E_ZCL_SUCCESS;

	uint16 u16payloadSize;
	uint16 u16AttributeId;
	uint16 u16inputOffset;
	uint16 u16typeSize;
	uint16 u16Length;
	uint8  au8LinkTxBuffer[256];

	tsZCL_CallBackEvent sZCL_CallBackEvent;

	// fill in non-attribute specific values in callback event structure
	sZCL_CallBackEvent.u8EndPoint = pZPSevent->uEvent.sApsDataIndEvent.u8DstEndpoint;
	sZCL_CallBackEvent.psClusterInstance = psClusterInstance;
	sZCL_CallBackEvent.pZPSevent = pZPSevent;
	sZCL_CallBackEvent.eEventType = E_ZCL_CBET_READ_INDIVIDUAL_ATTRIBUTE_RESPONSE;
	sZCL_CallBackEvent.eZCL_Status = E_ZCL_SUCCESS;


	u16inputOffset = u16ZCL_ReadCommandHeader(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst,
	                                              &sZCL_HeaderParams);

	sZCL_CallBackEvent.u8TransactionSequenceNumber = sZCL_HeaderParams.u8TransactionSequenceNumber;
	// payload investigation
	u16payloadSize = PDUM_u16APduInstanceGetPayloadSize(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst);

	u16Length =  0;
	ZNC_BUF_U16_UPD  ( &au8LinkTxBuffer [0],u16payloadSize,         u16Length );

	sZCL_CallBackEvent.eEventType = E_ZCL_CBET_REPORT_INDIVIDUAL_ATTRIBUTE;

		u16inputOffset += u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_ATTRIBUTE_ID,
													&u16AttributeId);
	sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.u16AttributeEnum=u16AttributeId;

    // parse the incoming message, read each attribute from the device and write into the outgoing buffer


	while(u16payloadSize-u16inputOffset > 0)
	{
		vLog_Printf(TRACE_DEBUG,LOG_DEBUG, "\n ePrivatePhilipsCommandHandler - u16payloadSize : %d / u16inputOffset : %d\n",u16payloadSize,u16inputOffset);
		sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeStatus = E_ZCL_CMDS_SUCCESS;

		u16inputOffset +=u16ZCL_APduInstanceReadNBO(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst, u16inputOffset, E_ZCL_UINT8,
		                    &sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType);

		sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.eAttributeDataType = E_ZCL_CSTRING;

		uint16                     u16stringDataLength;
	    uint8                     *pu8stringData;
		u16typeSize = u16ZCL_PhilipsGetStringAttributeTypeSizeFromBuffer(
		                                           &u16stringDataLength,
		                                           &pu8stringData,
		                                           (uint8 *)(PDUM_pvAPduInstanceGetPayload(pZPSevent->uEvent.sApsDataIndEvent.hAPduInst)) + u16inputOffset);

		uAttributeVal.sStrData.u8Length = (uint8 )u16stringDataLength;
		uAttributeVal.sStrData.pu8Data = pu8stringData;
		sZCL_CallBackEvent.uMessage.sIndividualAttributeResponse.pvAttributeData = (void *)&uAttributeVal;

	    // step over the attribute - the error flags will determine whether we go round the loop again
	    u16inputOffset += u16typeSize;

	    psEndPointDefinition->pCallBackFunctions(&sZCL_CallBackEvent);

	}

	return eStatus;
}



PUBLIC uint16 u16ZCL_PhilipsGetStringAttributeTypeSizeFromBuffer(
                        uint16                     *pu16stringDataLength,
                        uint8                     **ppu8stringData,
                        uint8                      *pu8stringLengthPosition)
{

    uint16 u16stringSize;

	u16stringSize = *pu8stringLengthPosition +1;
	*pu16stringDataLength = sizeof(&pu8stringLengthPosition[0])+1;
	*ppu8stringData = &pu8stringLengthPosition[0];

    return(u16stringSize);
}














/****************************************************************************
 *
 * NAME:       eCLD_AnalogInputBasicCreateAnalogInputBasic
 *
 * DESCRIPTION:
 * Creates a Analog input basic cluster
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
PUBLIC  teZCL_Status eCLD_PrivatePhilipsCreate(
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
   ePrivatePhilipsCommandHandler);

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

