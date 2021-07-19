/*****************************************************************************
 *
 * MODULE:             Private Terncy Cluster
 *
 * COMPONENT:          PrivateTerncy.h
 *
 * AUTHOR:             akila
 *
 * DESCRIPTION:        Header for Private Terncy Cluster
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

#ifndef PRIVATE_TERNCY_H
#define PRIVATE_TERNCY_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/


/* Cluster ID's */
#define GENERAL_CLUSTER_PRIVATE_TERNCY                            0xFCCC



/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Command codes */


typedef enum
{
    /* Analog Input (Basic) Device Information attribute set attribute ID's (3.14.1.1.2) */
    E_CLD_PRIVATE_TERNCY_ATTR_ID_ON		                         =                0x0000, /*Mandatory */
    E_CLD_PRIVATE_TERNCY_ATTR_ID_OFF			                 =                0x0004 /*Mandatory */

} teCLD_PrivateTerncyCluster_AttrID;



typedef struct
{

} tsCLD_PrivateTerncy;



/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_PrivateTerncyCreate(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits);


PUBLIC teZCL_Status ePrivateTerncyCommandHandler(
                    ZPS_tsAfEvent               *pZPSevent,
                    tsZCL_EndPointDefinition    *psEndPointDefinition,
                    tsZCL_ClusterInstance       *psClusterInstance);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
	extern const tsZCL_AttributeDefinition asCLD_PrivatTerncyClusterAttributeDefinitions[];
    extern tsZCL_ClusterDefinition sCLD_PrivateTerncy;
    extern uint8 au8PrivateTerncyAttributeControlBits[];


/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* BASIC_H */
