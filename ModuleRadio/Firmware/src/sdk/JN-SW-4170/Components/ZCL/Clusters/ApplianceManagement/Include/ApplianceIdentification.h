/*****************************************************************************
 *
 * MODULE:             Appliance Identification Cluster
 *
 * COMPONENT:          ApplianceIdentification.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Appliance Identification Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Include/ApplianceIdentification.h $
 *
 * $Revision: 53588 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-04-25 14:45:57 +0530 (Thu, 25 Apr 2013) $
 *
 * $Id: ApplianceIdentification.h 53588 2013-04-25 09:15:57Z nxp57621 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139].
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

#ifndef APPLIANCE_IDENTIFICATION_H
#define APPLIANCE_IDENTIFICATION_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/*             Appliance Identification Cluster - Optional Attributes                          */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the Appliance Identification cluster.                                         */
/****************************************************************************/

/* Enable the optional Company name attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_COMPANY_NAME

/* Enable the optional Company ID attribute*/
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_COMPANY_ID

/* Enable the optional brand name attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_BRAND_NAME

/* Enable the optional brand ID attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_BRAND_ID

/* Enable the optional Model attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_MODEL

/* Enable the optional Part Number attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_PART_NUMBER

/* Enable the optional Product Revision attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_PRODUCT_REVISION

/* Enable the optional Software Revision attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_SOFTWARE_REVISION

/* Enable the optional Product Type Name attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_PRODUCT_TYPE_NAME

/* Enable the optional Product Type ID attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_PRODUCT_TYPE_ID

/* Enable the optional Disable CECED Specification Version attribute */
//#define   CLD_APPLIANCE_IDENTIFICATION_ATTR_CECED_SPEC_VERSION
/* End of optional attributes */

/* Cluster ID's */
#define APPLIANCE_MANAGEMENT_CLUSTER_ID_APPLIANCE_IDENTIFICATION                      0x0b00

/* Bitmap of Attribute Basic Identification */
#ifndef CLD_APPLIANCE_IDENTIFICATION_COMPANY_ID
#define CLD_APPLIANCE_IDENTIFICATION_COMPANY_ID                (0)
#endif
#ifndef CLD_APPLIANCE_IDENTIFICATION_BRAND_ID
#define CLD_APPLIANCE_IDENTIFICATION_BRAND_ID                  (0)
#endif
#ifndef CLD_APPLIANCE_IDENTIFICATION_PRODUCT_TYPE_ID
#define CLD_APPLIANCE_IDENTIFICATION_PRODUCT_TYPE_ID           (0)
#endif
#ifndef CLD_APPLIANCE_IDENTIFICATION_SPEC_VERSION
#define CLD_APPLIANCE_IDENTIFICATION_SPEC_VERSION              ((uint64)0)
#endif

#ifndef CLD_APPLIANCE_IDENTIFICATION_ATTR_BASIC_IDENTIFICATION
    #define CLD_APPLIANCE_IDENTIFICATION_ATTR_BASIC_IDENTIFICATION          (CLD_APPLIANCE_IDENTIFICATION_COMPANY_ID | \
                                                                            (CLD_APPLIANCE_IDENTIFICATION_BRAND_ID << 15) |  \
                                                                            (CLD_APPLIANCE_IDENTIFICATION_PRODUCT_TYPE_ID << 31) |  \
                                                                            ((CLD_APPLIANCE_IDENTIFICATION_SPEC_VERSION & 0x7)<< 47))
#endif

#ifndef CLD_APPLIANCE_IDENTIFICATION_CLUSTER_REVISION
    #define CLD_APPLIANCE_IDENTIFICATION_CLUSTER_REVISION                     1
#endif
/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* Basic Appliance Identification attribute set attribute ID's (9.8.2.2) */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_BASIC_IDENTIFICATION        = 0x0000, /* Mandatory */
    /* Extended Appliance Identification attribute set attribute ID's (9.8.2.4)*/
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_COMPANY_NAME                = 0x0010, /* Optional */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_COMPANY_ID,                           /* Optional */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_BRAND_NAME,                           /* Optional */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_BRAND_ID,                             /* Optional */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_MODEL,                                /* Optional */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_PART_NUMBER,                          /* Optional */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_PRODUCT_REVISION,                     /* Optional */                      
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_SOFTWARE_REVISION,                    /* Optional */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_PRODUCT_TYPE_NAME,                    /* Optional */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_PRODUCT_TYPE_ID,                      /* Optional */
    E_CLD_APPLIANCE_IDENTIFICATION_ATTR_ID_CECED_SPEC_VERSION,                   /* Optional */
} teCLD_ApplianceIdentification_Cluster_AttrID;


/* Product Type ID */
typedef enum 
{
    E_CLD_AI_PT_ID_WHITE_GOODS                                             = 0x0000,
    E_CLD_AI_PT_ID_DISHWASHER                                              = 0x5601,
    E_CLD_AI_PT_ID_TUMBLE_DRYER,
    E_CLD_AI_PT_ID_WASHER_DRYER,
    E_CLD_AI_PT_ID_WASHING_MACHINE,
    E_CLD_AI_PT_ID_HOBS                                                    = 0x5E03,
    E_CLD_AI_PT_ID_INDUCTION_HOBS                                          = 0x5E09,
    E_CLD_AI_PT_ID_OVEN                                                    = 0x5E01,
    E_CLD_AI_PT_ID_ELECTRICAL_OVEN                                         = 0x5E06,
    E_CLD_AI_PT_ID_REFRIGERATOR_FREEZER                                    = 0x6601
} teCLD_ApplianceIdentification_ProductTypeId;



/* Appliance Identification Cluster */
typedef struct
{
#ifdef APPLIANCE_IDENTIFICATION_SERVER    
    zbmap56                      u64BasicIdentification;

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_COMPANY_NAME
    tsZCL_CharacterString       sCompanyName;
    uint8                       au8CompanyName[16];
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_COMPANY_ID
    zuint16                      u16CompanyId;
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_BRAND_NAME
    tsZCL_CharacterString       sBrandName;
    uint8                       au8BrandName[16];
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_BRAND_ID
    zuint16                      u16BrandId;
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_MODEL
    tsZCL_OctetString            sModel;
    uint8                       au8Model[16];
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_PART_NUMBER
    tsZCL_OctetString            sPartNumber;
    uint8                       au8PartNumber[16];
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_PRODUCT_REVISION
    tsZCL_OctetString            sProductRevision;
    uint8                       au8ProductRevision[6];
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_SOFTWARE_REVISION
    tsZCL_OctetString            sSoftwareRevision;
    uint8                       au8SoftwareRevision[6];
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_PRODUCT_TYPE_NAME
    tsZCL_OctetString            sProductTypeName;
    uint8                       au8ProductTypeName[2];
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_PRODUCT_TYPE_ID
    zuint16                      u16ProductTypeId;
#endif

#ifdef CLD_APPLIANCE_IDENTIFICATION_ATTR_CECED_SPEC_VERSION
    zuint8                       u8CECEDSpecificationVersion;
#endif
#endif
    zuint16                      u16ClusterRevision;

} tsCLD_ApplianceIdentification;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_ApplianceIdentificationCreateApplianceIdentification(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern tsZCL_ClusterDefinition sCLD_ApplianceIdentification;
extern const tsZCL_AttributeDefinition asCLD_ApplianceIdentificationClusterAttributeDefinitions[];
extern uint8 au8ApplianceIdentificationAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* APPLIANCE_IDENTIFICATION_H */
