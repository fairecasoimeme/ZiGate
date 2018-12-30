/*****************************************************************************
 *
 * MODULE:             Private Philips Cluster
 *
 * COMPONENT:          PrivatePhilips.h
 *
 * AUTHOR:             akila
 *
 * DESCRIPTION:        Header for Private Philips Cluster
 *
 * $HeadURL:  $
 *
 * $Revision: 0 $
 *
 * $LastChangedBy:  $
 *
 * $LastChangedDate: 2018-11-25 $
 *
 * $Id:  PrivatePhilips.h  $
 *
*/

#ifndef PRIVATE_PHILIPS_H
#define PRIVATE_PHILIPS_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/


/* Cluster ID's */
#define GENERAL_CLUSTER_PRIVATE_PHILIPS                            0xFC00



/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Command codes */


typedef enum
{
    /* Analog Input (Basic) Device Information attribute set attribute ID's (3.14.1.1.2) */
    E_CLD_PRIVATE_PHILIPS_ATTR_ID_ON		                     =                0x0001, /*Mandatory */
    E_CLD_PRIVATE_PHILIPS_ATTR_ID_LIGHTPLUS   	                 =                0x0002, /*Mandatory */
    E_CLD_PRIVATE_PHILIPS_ATTR_ID_LIGHTMINUS		             =                0x0003, /*Mandatory */
    E_CLD_PRIVATE_PHILIPS_ATTR_ID_OFF			                 =                0x0004 /*Mandatory */

} teCLD_PrivatePhilipsCluster_AttrID;



typedef struct
{
	/*zuint32					    u32undef;
	zuint8						u8type;
	zuint8						u8fix;
	zuint16						u16time;*/


} tsCLD_PrivatePhilips;



/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_PrivatePhilipsCreate(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits);


PUBLIC teZCL_Status ePrivatePhilipsCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

PUBLIC uint16 u16ZCL_PhilipsGetStringAttributeTypeSizeFromBuffer(
                        uint16                     *pu16stringDataLength,
                        uint8                     **ppu8stringData,
                        uint8                      *pu8stringLengthPosition);
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
	extern const tsZCL_AttributeDefinition asCLD_PrivatPhilipsClusterAttributeDefinitions[];
    extern tsZCL_ClusterDefinition sCLD_PrivatePhilips;
    extern uint8 au8PrivatePhilipsAttributeControlBits[];


/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* BASIC_H */
