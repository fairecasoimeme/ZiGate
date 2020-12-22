/*****************************************************************************
 *
 * MODULE:             Analog Input Basic Cluster
 *
 * COMPONENT:          AnalogInputBasic.h
 *
 * AUTHOR:             Daniel Watson
 *
 * DESCRIPTION:        Header for Analog Input Basic Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Include/AnalogInputBasic.h $
 *
 * $Revision: 52743 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-03-15 18:39:02 +0530 (Fri, 15 Mar 2013) $
 *
 * $Id: AnalogInputBasic.h 52743 2013-03-15 13:09:02Z nxp57621 $
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

#ifndef ANALOG_INPUT_BASIC_H
#define ANALOG_INPUT_BASIC_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/*             Analog Input Basic Cluster - Optional Attributes             */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the Analog input basic cluster.                            */
/****************************************************************************/

/* Enable the optional Stack Version attribute*/
//#define   CLD_ANALOG_INPUT_BASIC_ATTR_DESCRIPTION

/* Enable the optional Max Present Value attribute */
//#define   CLD_ANALOG_INPUT_BASIC_ATTR_MAX_PRESENT_VALUE

/* Enable the optional Min Present Value attribute */
//#define   CLD_ANALOG_INPUT_BASIC_ATTR_MIN_PRESENT_VALUE

/* Enable the optional Reliability attribute */
//#define   CLD_ANALOG_INPUT_BASIC_ATTR_RELIABILITY

/* Enable the optional Resolution attribute */
//#define   CLD_ANALOG_INPUT_BASIC_ATTR_RESOLUTION

/* Enable the optional Engineering Units attribute */
//#define   CLD_ANALOG_INPUT_BASIC_ATTR_ENGINEERING_UNITS

/* Enable the optional Application Type attribute */
//#define   CLD_ANALOG_INPUT_BASIC_ATTR_APPLICATION_TYPE

/* Enable the optional Attribute Reporting Status attribute */
//#define   CLD_ANALOG_INPUT_BASIC_ATTR_ATTRIBUTE_REPORTING_STATUS

/* End of optional attributes */


/* Cluster ID's */
#define GENERAL_CLUSTER_ID_ANALOG_INPUT_BASIC                            0x000C


#ifndef CLD_ANALOG_INPUT_BASIC_CLUSTER_REVISION
    #define CLD_ANALOG_INPUT_BASIC_CLUSTER_REVISION                     1
#endif    

/* Status Flags - bit definitions and bit masks */
#define ANALOG_INPUT_BASIC_STATUS_FLAGS_IN_ALARM                              0
#define ANALOG_INPUT_BASIC_STATUS_FLAGS_FAULT                                 1
#define ANALOG_INPUT_BASIC_STATUS_FLAGS_OVERRIDDEN                            2
#define ANALOG_INPUT_BASIC_STATUS_FLAGS_OUT_OF_SERVICE                        3

#define ANALOG_INPUT_BASIC_STATUS_FLAGS_IN_ALARM_MASK                             (1 << ANALOG_INPUT_BASIC_STATUS_FLAGS_IN_ALARM)
#define ANALOG_INPUT_BASIC_STATUS_FLAGS_FAULT_MASK                                (1 << ANALOG_INPUT_BASIC_STATUS_FLAGS_FAULT)
#define ANALOG_INPUT_BASIC_STATUS_FLAGS_OVERRIDDEN_MASK                           (1 << ANALOG_INPUT_BASIC_STATUS_FLAGS_OVERRIDDEN)
#define ANALOG_INPUT_BASIC_STATUS_FLAGS_OUT_OF_SERVICE_MASK                       (1 << ANALOG_INPUT_BASIC_STATUS_FLAGS_OUT_OF_SERVICE)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Command codes */


typedef enum
{
    /* Analog Input (Basic) Device Information attribute set attribute ID's (3.14.1.1.2) */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_DESCRIPTION                    =                0x001C, /*Optional */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_MAX_PRESENT_VALUE              =                0x0041, /*Optional */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_MIN_PRESENT_VALUE              =                0x0045, /*Optional */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_OUT_OF_SERVICE                 =                0x0051, /*Mandatory */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_PRESENT_VALUE                  =                0x0055, /* Mandatory */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_RELIABILITY                    =                0x0067, /*Optional */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_RESOLUTION                     =                0x006A, /*Optional */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_STATUS_FLAGS                   =                0x006F, /* Mandatory */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_ENGINEERING_UNITS              =                0x0075, /* Optional */
    E_CLD_ANALOG_INPUT_BASIC_ATTR_ID_APPLICATION_TYPE               =                0x0100, /*Optional */
} teCLD_AnalogInputBasicCluster_AttrID;



/* Polarity attribute */
typedef enum
{
    E_CLD_ANALOG_INPUT_BASIC_OUT_OF_SERVICE_FALSE                       =                0x0000,
    E_CLD_ANALOG_INPUT_BASIC_OUT_OF_SERVICE_TRUE
}teCLD_AnalogInputBasic_OutOfService;


/* Reliability attribute */
typedef enum
{
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_NO_FAULT_DETECTED         =                0x0000,
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_NO_SENSOR,
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_OVER_RANGE,
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_UNDER_RANGE,
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_OPEN_LOOP,
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_SHORTED_LOOP,
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_NO_OUTPUT,
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_UNRELIABLE_OTHER,
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_PROCESS_ERROR,
    E_CLD_ANALOG_INPUT_BASIC_RELIABILITY_CONFIGURATION_ERROR       =                0x000A
 }teCLD_AnalogInputBasic_Reliability;


#ifdef ANALOG_INPUT_BASIC_SERVER
/* Analog Input Basic Cluster */
typedef struct
{
#ifdef CLD_ANALOG_INPUT_BASIC_ATTR_DESCRIPTION
    tsZCL_CharacterString       sDescription;
    zuint8                      au8Description[16];
#endif

#ifdef CLD_ANALOG_INPUT_BASIC_ATTR_MAX_PRESENT_VALUE
    zsingle                     fMaxPresentValue;
#endif

#ifdef CLD_ANALOG_INPUT_BASIC_ATTR_MIN_PRESENT_VALUE
    zsingle                     fMinPresentValue;
#endif

    zbool                       bOutOfService;
    
    zsingle                     fPresentValue;

#ifdef CLD_ANALOG_INPUT_BASIC_ATTR_RELIABILITY
    zenum8                      u8Reliability;
#endif

#ifdef CLD_ANALOG_INPUT_BASIC_ATTR_RESOLUTION
    zsingle                     fResolution;
#endif

    zbmap8                      u8StatusFlags;

#ifdef CLD_ANALOG_INPUT_BASIC_ATTR_ENGINEERING_UNITS
    zenum16                     u16EngineeringUnits;
#endif

#ifdef CLD_ANALOG_INPUT_BASIC_ATTR_APPLICATION_TYPE
    zuint32                     u32ApplicationType;
#endif

#ifdef CLD_ANALOG_INPUT_BASIC_ATTR_ATTRIBUTE_REPORTING_STATUS
    zenum8                      u8AttributeReportingStatus;
#endif
    
    zuint16                     u16ClusterRevision;
} tsCLD_AnalogInputBasic;
#endif

#ifdef ANALOG_INPUT_BASIC_CLIENT
/* Analog Input Basic Cluster */
typedef struct
{
    zuint16                     u16ClusterRevision;
} tsCLD_AnalogInputBasicClient;
#endif
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_AnalogInputBasicCreateAnalogInputBasic(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
#ifdef ANALOG_INPUT_BASIC_SERVER
    extern tsZCL_ClusterDefinition sCLD_AnalogInputBasic;
    extern tsZCL_AttributeDefinition asCLD_AnalogInputBasicClusterAttributeDefinitions[];
    extern uint8 au8AnalogInputBasicAttributeControlBits[];
#endif
#ifdef ANALOG_INPUT_BASIC_CLIENT
    extern tsZCL_ClusterDefinition sCLD_AnalogInputBasicClient;
    extern tsZCL_AttributeDefinition asCLD_AnalogInputBasicClientClusterAttributeDefinitions[];
    extern uint8 au8AnalogInputBasicClientAttributeControlBits[];
#endif
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* BASIC_H */
