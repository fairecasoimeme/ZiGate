/*****************************************************************************
 *
 * MODULE:             Basic Cluster
 *
 * COMPONENT:          Basic.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Basic cluster definition
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Source/Basic.c $
 *
 * $Revision: 73733 $
 *
 * $LastChangedBy: nxp29772 $
 *
 * $LastChangedDate: 2015-10-28 12:30:13 +0100 (Wed, 28 Oct 2015) $
 *
 * $Id: Basic.c 73733 2015-10-28 11:30:13Z nxp29772 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5164,
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
#include "zcl.h"
#include "Basic.h"
#include "Basic_internal.h"
#include "zcl_options.h"


#ifdef CLD_BASIC

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
#ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED
    const tsZCL_CommandDefinition asCLD_BasicClusterCommandDefinitions[] = {
        {E_CLD_BASIC_CMD_RESET_TO_FACTORY_DEFAULTS,             E_ZCL_CF_RX}     /* Mandatory */    
    };
#endif

const tsZCL_AttributeDefinition asCLD_BasicClusterAttributeDefinitions[] = {
#ifdef BASIC_SERVER
        /* ZigBee Cluster Library Version */
        {E_CLD_BAS_ATTR_ID_ZCL_VERSION,             E_ZCL_AF_RD,                E_ZCL_UINT8,    (uint32)(&((tsCLD_Basic*)(0))->u8ZCLVersion),0},  /* Mandatory */

    #ifdef CLD_BAS_ATTR_APPLICATION_VERSION
        {E_CLD_BAS_ATTR_ID_APPLICATION_VERSION,     E_ZCL_AF_RD,                E_ZCL_UINT8,    (uint32)(&((tsCLD_Basic*)(0))->u8ApplicationVersion),0},
    #endif

    #ifdef CLD_BAS_ATTR_STACK_VERSION
        {E_CLD_BAS_ATTR_ID_STACK_VERSION,           E_ZCL_AF_RD,                E_ZCL_UINT8,    (uint32)(&((tsCLD_Basic*)(0))->u8StackVersion),0},
    #endif

    #ifdef CLD_BAS_ATTR_HARDWARE_VERSION
        {E_CLD_BAS_ATTR_ID_HARDWARE_VERSION,        E_ZCL_AF_RD,                E_ZCL_UINT8,    (uint32)(&((tsCLD_Basic*)(0))->u8HardwareVersion),0},
    #endif

    #ifdef CLD_BAS_ATTR_MANUFACTURER_NAME
        {E_CLD_BAS_ATTR_ID_MANUFACTURER_NAME,       E_ZCL_AF_RD,                E_ZCL_CSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sManufacturerName),0},
    #endif

    #ifdef CLD_BAS_ATTR_MODEL_IDENTIFIER
        {E_CLD_BAS_ATTR_ID_MODEL_IDENTIFIER,        E_ZCL_AF_RD,                E_ZCL_CSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sModelIdentifier),0},
    #endif

    #ifdef CLD_BAS_ATTR_DATE_CODE
        {E_CLD_BAS_ATTR_ID_DATE_CODE,               E_ZCL_AF_RD,                E_ZCL_CSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sDateCode),0},
    #endif

	#ifdef CLD_BAS_ATTR_APPLICATION_LEGRAND
        {E_CLD_BAS_ATTR_ID_LEGRAND,                ( E_ZCL_AF_RD | E_ZCL_AF_MS),      E_ZCL_UINT32,    (uint32)(&((tsCLD_Basic*)(0))->u32PrivateLegrand),0},
    #endif

        {E_CLD_BAS_ATTR_ID_POWER_SOURCE,            E_ZCL_AF_RD,                E_ZCL_ENUM8,    (uint32)(&((tsCLD_Basic*)(0))->ePowerSource),0},  /* Mandatory */

    #ifdef CLD_BAS_ATTR_GENERIC_DEVICE_CLASS    
        {E_CLD_BAS_ATTR_ID_GENERIC_DEVICE_CLASS,    E_ZCL_AF_RD,                E_ZCL_ENUM8,    (uint32)(&((tsCLD_Basic*)(0))->eGenericDeviceClass),0},  /* Optional */
    #endif

    #ifdef CLD_BAS_ATTR_GENERIC_DEVICE_TYPE    
        {E_CLD_BAS_ATTR_ID_GENERIC_DEVICE_TYPE,     E_ZCL_AF_RD,                E_ZCL_ENUM8,    (uint32)(&((tsCLD_Basic*)(0))->eGenericDeviceType),0},  /* Optional */
    #endif
     
    #ifdef CLD_BAS_ATTR_PRODUCT_CODE    
        {E_CLD_BAS_ATTR_ID_PRODUCT_CODE,            E_ZCL_AF_RD,                E_ZCL_OSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sProductCode),0},
    #endif

    #ifdef CLD_BAS_ATTR_PRODUCT_URL   
        {E_CLD_BAS_ATTR_ID_PRODUCT_URL,             E_ZCL_AF_RD,                E_ZCL_CSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sProductURL),0},
    #endif

    #ifdef CLD_BAS_ATTR_LOCATION_DESCRIPTION
        {E_CLD_BAS_ATTR_ID_LOCATION_DESCRIPTION,    (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_CSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sLocationDescription),0},
    #endif

    #ifdef CLD_BAS_ATTR_PHYSICAL_ENVIRONMENT
        {E_CLD_BAS_ATTR_ID_PHYSICAL_ENVIRONMENT,    (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_ENUM8,    (uint32)(&((tsCLD_Basic*)(0))->u8PhysicalEnvironment),0},
    #endif

    #ifdef CLD_BAS_ATTR_DEVICE_ENABLED
        {E_CLD_BAS_ATTR_ID_DEVICE_ENABLED,          (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_BOOL,     (uint32)(&((tsCLD_Basic*)(0))->bDeviceEnabled),0},
    #endif

    #ifdef CLD_BAS_ATTR_ALARM_MASK
        {E_CLD_BAS_ATTR_ID_ALARM_MASK,              (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_BMAP8,    (uint32)(&((tsCLD_Basic*)(0))->u8AlarmMask),0},
    #endif

    #ifdef CLD_BAS_ATTR_DISABLE_LOCAL_CONFIG
        {E_CLD_BAS_ATTR_ID_DISABLE_LOCAL_CONFIG,    (E_ZCL_AF_RD|E_ZCL_AF_WR),  E_ZCL_BMAP8,    (uint32)(&((tsCLD_Basic*)(0))->u8DisableLocalConfig),0},
    #endif

    #ifdef CLD_BAS_ATTR_SW_BUILD_ID
        {E_CLD_BAS_ATTR_ID_SW_BUILD_ID,             (E_ZCL_AF_RD),              E_ZCL_CSTRING,   (uint32)(&((tsCLD_Basic*)(0))->sSWBuildID),0},
    #endif
	#ifdef CLD_BAS_ATTR_ID_XIAOMI_FF01
        {E_CLD_BAS_ATTR_ID_XIAOMI_FF01,             E_ZCL_AF_RD,                E_ZCL_CSTRING,    (uint32)(&((tsCLD_Basic*)(0))->sDataXiaomiConfig),0},
	#endif
	#ifdef CLD_BAS_ATTR_ID_XIAOMI_FF02
		{E_CLD_BAS_ATTR_ID_XIAOMI_FF02,             E_ZCL_AF_RD,                E_ZCL_CSTRING,    (uint32)(&((tsCLD_Basic*)(0))->sDataXiaomiConfig2),0},
	#endif

#endif    
       {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,      (E_ZCL_AF_RD|E_ZCL_AF_GA),  E_ZCL_UINT16,    (uint32)(&((tsCLD_Basic*)(0))->u16ClusterRevision),0},   /* Mandatory  */
};

tsZCL_ClusterDefinition sCLD_Basic = {
        GENERAL_CLUSTER_ID_BASIC,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_BasicClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_BasicClusterAttributeDefinitions,
        NULL
        #ifdef ZCL_COMMAND_DISCOVERY_SUPPORTED        
            ,
            (sizeof(asCLD_BasicClusterCommandDefinitions) / sizeof(tsZCL_CommandDefinition)),
            (tsZCL_CommandDefinition*)asCLD_BasicClusterCommandDefinitions         
        #endif        
};
uint8 au8BasicClusterAttributeControlBits[(sizeof(asCLD_BasicClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];


#ifdef CLD_SM_SUPPORT_MIRROR

    const tsZCL_AttributeDefinition asCLD_BasicClusterMirrorAttributeDefinitions[] = {
        /* ZigBee Cluster Library Version */
        {E_CLD_BAS_ATTR_ID_ZCL_VERSION,      E_ZCL_AF_RD,                E_ZCL_UINT8,    (uint32)(&((tsCLD_Basic*)(0))->u8ZCLVersion),0},  /* Mandatory */

    #ifdef CLD_BAS_MIRROR_ATTR_APPLICATION_VERSION
        {E_CLD_BAS_ATTR_ID_APPLICATION_VERSION,     E_ZCL_AF_RD,                E_ZCL_UINT8,    (uint32)(&((tsCLD_Basic*)(0))->u8ApplicationVersion),0},
    #endif

    #ifdef CLD_BAS_MIRROR_ATTR_STACK_VERSION
        {E_CLD_BAS_ATTR_ID_STACK_VERSION,           E_ZCL_AF_RD,                E_ZCL_UINT8,    (uint32)(&((tsCLD_Basic*)(0))->u8StackVersion),0},
    #endif

    #ifdef CLD_BAS_MIRROR_ATTR_HARDWARE_VERSION
        {E_CLD_BAS_ATTR_ID_HARDWARE_VERSION,        E_ZCL_AF_RD,                E_ZCL_UINT8,    (uint32)(&((tsCLD_Basic*)(0))->u8HardwareVersion),0},
    #endif

    #ifdef CLD_BAS_MIRROR_ATTR_MANUFACTURER_NAME
        {E_CLD_BAS_ATTR_ID_MANUFACTURER_NAME,       E_ZCL_AF_RD,                E_ZCL_CSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sManufacturerName),0},
    #endif

    #ifdef CLD_BAS_MIRROR_ATTR_MODEL_IDENTIFIER
        {E_CLD_BAS_ATTR_ID_MODEL_IDENTIFIER,        E_ZCL_AF_RD,                E_ZCL_CSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sModelIdentifier),0},
    #endif

    #ifdef CLD_BAS_MIRROR_ATTR_DATE_CODE
        {E_CLD_BAS_ATTR_ID_DATE_CODE,               E_ZCL_AF_RD,                E_ZCL_CSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sDateCode),0},
    #endif

        {E_CLD_BAS_ATTR_ID_POWER_SOURCE,            E_ZCL_AF_RD,                E_ZCL_ENUM8,    (uint32)(&((tsCLD_Basic*)(0))->ePowerSource),0},  /* Mandatory */

     
    #ifdef CLD_BAS_MIRROR_ATTR_LOCATION_DESCRIPTION
        {E_CLD_BAS_ATTR_ID_LOCATION_DESCRIPTION,    (E_ZCL_AF_RD | E_ZCL_AF_WR),  E_ZCL_CSTRING,  (uint32)(&((tsCLD_Basic*)(0))->sLocationDescription),0},
    #endif

    #ifdef CLD_BAS_MIRROR_ATTR_PHYSICAL_ENVIRONMENT
        {E_CLD_BAS_ATTR_ID_PHYSICAL_ENVIRONMENT,    (E_ZCL_AF_RD | E_ZCL_AF_WR ),  E_ZCL_ENUM8,    (uint32)(&((tsCLD_Basic*)(0))->u8PhysicalEnvironment),0},
    #endif

    #ifdef CLD_BAS_MIRROR_ATTR_DEVICE_ENABLED
        {E_CLD_BAS_ATTR_ID_DEVICE_ENABLED,          (E_ZCL_AF_RD | E_ZCL_AF_WR),  E_ZCL_BOOL,     (uint32)(&((tsCLD_Basic*)(0))->bDeviceEnabled),0},
    #endif

    #ifdef CLD_BAS_MIRROR_ATTR_ALARM_MASK
        {E_CLD_BAS_ATTR_ID_ALARM_MASK,              (E_ZCL_AF_RD | E_ZCL_AF_WR),  E_ZCL_BMAP8,    (uint32)(&((tsCLD_Basic*)(0))->u8AlarmMask),0},
    #endif

    #ifdef CLD_BAS_MIRROR_ATTR_DISABLE_LOCAL_CONFIG
        {E_CLD_BAS_ATTR_ID_DISABLE_LOCAL_CONFIG,    (E_ZCL_AF_RD | E_ZCL_AF_WR),  E_ZCL_BMAP8,    (uint32)(&((tsCLD_Basic*)(0))->u8DisableLocalConfig),0},
    #endif

        {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,     (E_ZCL_AF_RD|E_ZCL_AF_GA),    E_ZCL_UINT16,   (uint32)(&((tsCLD_Basic*)(0))->u16ClusterRevision),0},   /* Mandatory  */
    };

    uint8  au8BasicMirrorClusterAttributeControlBits[CLD_SM_NUMBER_OF_MIRRORS][(sizeof(asCLD_BasicClusterMirrorAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];
    
    /****************************************************************************
     *
     * NAME: eSE_RegisterMirroredBasicCluster
     *
     * DESCRIPTION:
     * Registers a Basic cluster with the ZCL layer, for each mirror
     *
     * PARAMETERS:  Name                            Usage
     *              psClusterInstance               Pointer to Cluster Instance
     *              EndPointSharedStructPtr         Pointer to EndPoint Shared Structure
     * RETURNS:
     * Void
     *
     ****************************************************************************/
    PUBLIC  teZCL_Status eSE_RegisterMirroredBasicCluster(uint8 u8MirrorNum,
                                                            tsZCL_ClusterInstance *psClusterInstance,
                                                            void                  *pvEndPointSharedStructPtr)
    {
        sCLD_BasicMirror[u8MirrorNum].u16ClusterEnum = GENERAL_CLUSTER_ID_BASIC;
        sCLD_BasicMirror[u8MirrorNum].bIsManufacturerSpecificCluster = FALSE;
        sCLD_BasicMirror[u8MirrorNum].u8ClusterControlFlags = (E_ZCL_SECURITY_NETWORK | CLUSTER_MIRROR_BIT);
        sCLD_BasicMirror[u8MirrorNum].u16NumberOfAttributes = (sizeof(asCLD_BasicClusterMirrorAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition));
        sCLD_BasicMirror[u8MirrorNum].psAttributeDefinition =  (tsZCL_AttributeDefinition*)asCLD_BasicClusterMirrorAttributeDefinitions;

        //Configure Basic cluster for each Mirrored End Point
        psClusterInstance->bIsServer = TRUE;
        psClusterInstance->psClusterDefinition = &sCLD_BasicMirror[u8MirrorNum];
        psClusterInstance->pvEndPointSharedStructPtr = pvEndPointSharedStructPtr;
        psClusterInstance->pu8AttributeControlBits = au8BasicMirrorClusterAttributeControlBits[u8MirrorNum];
        psClusterInstance->pCustomcallCallBackFunction = NULL;
        psClusterInstance->pvEndPointCustomStructPtr = NULL;

        return E_ZCL_SUCCESS;
    }
#endif

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 *
 * NAME:       eCLD_BasicCreateBasic
 *
 * DESCRIPTION:
 * Creates a basic cluster
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
PUBLIC  teZCL_Status eCLD_BasicCreateBasic(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits)
{
    #ifdef STRICT_PARAM_CHECK 
        /* Parameter check */
        if((psClusterInstance==NULL) ||
           (psClusterDefinition==NULL)  )
        {
            return E_ZCL_ERR_PARAMETER_NULL;
        }
    #endif

    /* Create an instance of a basic cluster */
    vZCL_InitializeClusterInstance(
           psClusterInstance, 
           bIsServer,
           psClusterDefinition,
           pvEndPointSharedStructPtr,
           pu8AttributeControlBits,
           NULL,
           eCLD_BasicCommandHandler);

        if(pvEndPointSharedStructPtr  != NULL)
        {
#ifdef BASIC_SERVER            
            /* Initialise attributes defaults */
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->u8ZCLVersion = 0x02;

        #ifdef CLD_BAS_ATTR_APPLICATION_VERSION
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->u8ApplicationVersion = CLD_BAS_APP_VERSION;
        #endif

        #ifdef CLD_BAS_ATTR_STACK_VERSION
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->u8StackVersion = CLD_BAS_STACK_VERSION;
        #endif

        #ifdef CLD_BAS_ATTR_HARDWARE_VERSION
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->u8HardwareVersion = CLD_BAS_HARDWARE_VERSION;
        #endif

        #ifdef CLD_BAS_ATTR_MANUFACTURER_NAME
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sManufacturerName.u8MaxLength = sizeof(((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8ManufacturerName);
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sManufacturerName.u8Length = CLD_BAS_MANUF_NAME_SIZE;
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sManufacturerName.pu8Data = ((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8ManufacturerName;
        #endif

        #ifdef CLD_BAS_ATTR_MODEL_IDENTIFIER
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sModelIdentifier.u8MaxLength = sizeof(((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8ModelIdentifier);
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sModelIdentifier.u8Length = CLD_BAS_MODEL_ID_SIZE;
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sModelIdentifier.pu8Data = ((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8ModelIdentifier;
        #endif

        #ifdef CLD_BAS_ATTR_DATE_CODE
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sDateCode.u8MaxLength = sizeof(((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8DateCode);
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sDateCode.u8Length = CLD_BAS_DATE_SIZE;
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sDateCode.pu8Data = ((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8DateCode;
        #endif

		#ifdef CLD_BAS_ATTR_ID_XIAOMI_FF01
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sDataXiaomiConfig.u8MaxLength = sizeof(((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8DataXiaomiConfig);
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sDataXiaomiConfig.u8Length = 32;
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sDataXiaomiConfig.pu8Data = ((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8DataXiaomiConfig;
        #endif

		#ifdef CLD_BAS_ATTR_ID_XIAOMI_FF02
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sDataXiaomiConfig2.u8MaxLength = sizeof(((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8DataXiaomiConfig2);
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sDataXiaomiConfig2.u8Length = 32;
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sDataXiaomiConfig2.pu8Data = ((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8DataXiaomiConfig2;
        #endif

        ((tsCLD_Basic*)pvEndPointSharedStructPtr)->ePowerSource = CLD_BAS_POWER_SOURCE;
        
        #ifdef CLD_BAS_ATTR_GENERIC_DEVICE_CLASS
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->eGenericDeviceClass = CLD_BAS_DEVICE_CLASS;
        #endif
        
        #ifdef CLD_BAS_ATTR_GENERIC_DEVICE_TYPE
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->eGenericDeviceType = 0xFF;
        #endif
        
        #ifdef CLD_BAS_ATTR_PRODUCT_CODE
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sProductCode.u8MaxLength = sizeof(((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8ProductCode);
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sProductCode.u8Length = CLD_BAS_PCODE_SIZE;
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sProductCode.pu8Data = ((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8ProductCode;
        #endif

        #ifdef CLD_BAS_ATTR_PRODUCT_URL
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sProductURL.u8MaxLength = sizeof(((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8ProductURL);
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sProductURL.u8Length = CLD_BAS_URL_SIZE;
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sProductURL.pu8Data = ((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8ProductURL;
        #endif

        

        #ifdef CLD_BAS_ATTR_LOCATION_DESCRIPTION
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sLocationDescription.u8MaxLength = sizeof(((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8LocationDescription);
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sLocationDescription.u8Length = 0;
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sLocationDescription.pu8Data = ((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8LocationDescription;
        #endif

        #ifdef CLD_BAS_ATTR_PHYSICAL_ENVIRONMENT
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->u8PhysicalEnvironment = 0x00;
        #endif

        #ifdef CLD_BAS_ATTR_DEVICE_ENABLED
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->bDeviceEnabled = 0x01;
        #endif

        #ifdef CLD_BAS_ATTR_ALARM_MASK
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->u8AlarmMask = 0x00;
        #endif

        #ifdef CLD_BAS_ATTR_DISABLE_LOCAL_CONFIG
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->u8DisableLocalConfig = 0x00;
        #endif

        #ifdef CLD_BAS_ATTR_SW_BUILD_ID
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sSWBuildID.u8MaxLength = sizeof(((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8SWBuildID);
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sSWBuildID.u8Length = CLD_BAS_SW_BUILD_SIZE;
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->sSWBuildID.pu8Data = ((tsCLD_Basic*)pvEndPointSharedStructPtr)->au8SWBuildID;
        #endif

		#ifdef CLD_BAS_ATTR_APPLICATION_LEGRAND
			((tsCLD_Basic*)pvEndPointSharedStructPtr)->u32PrivateLegrand = RND_u32GetRand ( 1, 0x0000ff ) ;

		#endif

            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->ePowerSource = CLD_BAS_POWER_SOURCE;



#endif        
            ((tsCLD_Basic*)pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_BAS_CLUSTER_REVISION;
        }

    return E_ZCL_SUCCESS;

}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

