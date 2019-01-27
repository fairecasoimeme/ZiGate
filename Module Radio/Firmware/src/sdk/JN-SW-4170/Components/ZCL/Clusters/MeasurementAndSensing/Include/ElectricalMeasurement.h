/*****************************************************************************
 *
 * MODULE:             Electrical Measurement Cluster
 *
 * COMPONENT:          ElectricalMeasurement.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Electrical Measurement Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA_121_ZCL/Clusters/MeasurementAndSensing/Include/ElectricalMeasurement.h $
 *
 * $Revision: 60042 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2014-03-20 16:13:45 +0530 (Thu, 20 Mar 2014) $
 *
 * $Id: ElectricalMeasurement.h 60042 2014-03-20 10:43:45Z nxp57621 $
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

#ifndef ELECTRICAL_MEASUREMENT_H
#define ELECTRICAL_MEASUREMENT_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/*       Electrical Measurement Cluster - Optional Attributes              */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the temperature measurement cluster.                       */
/****************************************************************************/

/* Enable the optional Tolerance attribute */
//#define CLD_ELECTMEAS_ATTR_AC_FREQUENCY
//#define CLD_ELECTMEAS_ATTR_RMS_VOLTAGE
//#define CLD_ELECTMEAS_ATTR_RMS_CURRENT
#define CLD_ELECTMEAS_ATTR_ACTIVE_POWER
//#define CLD_ELECTMEAS_ATTR_REACTIVE_POWER
//#define CLD_ELECTMEAS_ATTR_APPARENT_POWER
//#define CLD_ELECTMEAS_ATTR_POWER_FACTOR
//#define CLD_ELECTMEAS_ATTR_AC_VOLTAGE_MULTIPLIER
//#define CLD_ELECTMEAS_ATTR_AC_VOLTAGE_DIVISOR
//#define CLD_ELECTMEAS_ATTR_AC_CURRENT_MULTIPLIER
//#define CLD_ELECTMEAS_ATTR_AC_CURRENT_DIVISOR
//#define CLD_ELECTMEAS_ATTR_AC_POWER_MULTIPLIER
//#define CLD_ELECTMEAS_ATTR_AC_POWER_DIVISOR
/* End of optional attributes */

/* Manufacturer Specific Attributes */
//#define CLD_ELECTMEAS_ATTR_MAN_SPEC_APPARENT_POWER
//#define CLD_ELECTMEAS_ATTR_MAN_SPEC_NON_ACTIVE_POWER
//#define CLD_ELECTMEAS_ATTR_MAN_SPEC_FNDMTL_REACTIVE_POWER
//#define CLD_ELECTMEAS_ATTR_MAN_SPEC_FNDMTL_APPARENT_POWER
//#define CLD_ELECTMEAS_ATTR_MAN_SPEC_FNDMTL_POWER_FACTOR
//#define CLD_ELECTMEAS_ATTR_MAN_SPEC_NON_FNDMTL_APPARENT_POWER
//#define CLD_ELECTMEAS_ATTR_MAN_SPEC_TOTAL_HARMONIC_DISTORTION
//#define CLD_ELECTMEAS_ATTR_MAN_SPEC_VBIAS
//#define CLD_ELECTMEAS_ATTR_MAN_SPEC_DIVISOR

/* Cluster ID's */
#define MEASUREMENT_AND_SENSING_CLUSTER_ID_ELECTRICAL_MEASUREMENT  0x0B04

#ifndef CLD_ELECTMEAS_CLUSTER_REVISION
    #define CLD_ELECTMEAS_CLUSTER_REVISION                         1
#endif 

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* Electrical Measurement Basic Information attribute set attribute ID's (9.1.2.2.1) */
    E_CLD_ELECTMEAS_ATTR_ID_MEASUREMENT_TYPE                = 0x0000,  /* Mandatory */
    /* Electrical Measurement DC Measurement attribute set attribute ID's (9.1.2.2.2) */
    /* Electrical Measurement DC Formatting attribute set attribute ID's (9.1.2.2.3) */
    /* Electrical Measurement AC(Non-phase specific) Measurement attribute set attribute ID's (9.1.2.2.4) */
    E_CLD_ELECTMEAS_ATTR_ID_AC_FREQUENCY                    = 0x0300,     /* Optional */
    /* Electrical Measurement AC(Non-phase specific) Formatting attribute set attribute ID's (9.1.2.2.5) */
    /* Electrical Measurement AC(Single Phase or Phase A) Single Phase or Phase A attribute set attribute ID's (9.1.2.2.6) */    
    E_CLD_ELECTMEAS_ATTR_ID_RMS_VOLATGE                     = 0x0505,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_RMS_CURRENT                     = 0x0508,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_ACTIVE_POWER                    = 0x050B,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_REACTIVE_POWER                  = 0x050E,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_APPARENT_POWER                  = 0x050F,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_POWER_FACTOR                    = 0x0510,     /* Optional */
    /* Electrical Measurement AC(Single Phase or Phase A) Formatting attribute set attribute ID's (9.1.2.2.7) */
    E_CLD_ELECTMEAS_ATTR_ID_AC_VOLTAGE_MULTIPLIER           = 0x0600,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_AC_VOLTAGE_DIVISOR              = 0x0601,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_AC_CURRENT_MULTIPLIER           = 0x0602,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_AC_CURRENT_DIVISOR              = 0x0603,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_AC_POWER_MULTIPLIER             = 0x0604,     /* Optional */
    E_CLD_ELECTMEAS_ATTR_ID_AC_POWER_DIVISOR                = 0x0605,     /* Optional */
    /* Electrical Measurement DC Manufacturer Threshold Alarms attribute set attribute ID's (9.1.2.2.8) */
    /* Electrical Measurement AC Manufacturer Threshold Alarms attribute set attribute ID's (9.1.2.2.9) */
    /* Electrical Measurement AC Phase B  Measurement attribute set attribute ID's (9.1.2.2.10) */  
    /* Electrical Measurement AC Phase C  Measurement attribute set attribute ID's (9.1.2.2.11) */ 
    /* Manufacturer Specific Attributes */
	E_CLD_ELECTMEAS_ATTR_ID_MAN_SPEC_APPARENT_POWER         = 0xFF00,     /* Man Spec */
	E_CLD_ELECTMEAS_ATTR_ID_MAN_SPEC_NON_ACTIVE_POWER,                    /* Man Spec */
	E_CLD_ELECTMEAS_ATTR_ID_MAN_SPEC_FNDMTL_REACTIVE_POWER,               /* Man Spec */
	E_CLD_ELECTMEAS_ATTR_ID_MAN_SPEC_FNDMTL_APPARENT_POWER,               /* Man Spec */
	E_CLD_ELECTMEAS_ATTR_ID_MAN_SPEC_FNDMTL_POWER_FACTOR,                 /* Man Spec */
	E_CLD_ELECTMEAS_ATTR_ID_MAN_SPEC_NON_FNDMTL_APPARENT_POWER,           /* Man Spec */
	E_CLD_ELECTMEAS_ATTR_ID_MAN_SPEC_TOTAL_HARMONIC_DISTORTION,           /* Man Spec */
	E_CLD_ELECTMEAS_ATTR_ID_MAN_SPEC_VBIAS,                               /* Man Spec */
	E_CLD_ELECTMEAS_ATTR_ID_MAN_SPEC_DIVISOR,                             /* Man Spec */
} teCLD_ElectricalMeasurement_AttributeID;

/* Electrical Measurement Cluster */
typedef struct
{

#ifdef ELECTRICAL_MEASUREMENT_SERVER
    zbmap32                u32MeasurementType;

#ifdef CLD_ELECTMEAS_ATTR_AC_FREQUENCY
    zuint16                u16ACFrequency;
#endif

#ifdef CLD_ELECTMEAS_ATTR_RMS_VOLTAGE
    zuint16                u16RMSVoltage;
#endif

#ifdef CLD_ELECTMEAS_ATTR_RMS_CURRENT
    zuint16                u16RMSCurrent;
#endif

#ifdef CLD_ELECTMEAS_ATTR_ACTIVE_POWER
    zint16                 i16ActivePower;
#endif

#ifdef CLD_ELECTMEAS_ATTR_REACTIVE_POWER
    zint16                 i16ReactivePower;
#endif

#ifdef CLD_ELECTMEAS_ATTR_APPARENT_POWER
    zuint16                u16ApparentPower;
#endif

#ifdef CLD_ELECTMEAS_ATTR_POWER_FACTOR
    zint8                  i8PowerFactor;
#endif

#ifdef CLD_ELECTMEAS_ATTR_AC_VOLTAGE_MULTIPLIER
    zuint16                u16ACVoltageMultiplier;
#endif

#ifdef CLD_ELECTMEAS_ATTR_AC_VOLTAGE_DIVISOR
    zuint16                u16ACVoltageDivisor;
#endif

#ifdef CLD_ELECTMEAS_ATTR_AC_CURRENT_MULTIPLIER
    zuint16                u16ACCurrentMultiplier;
#endif

#ifdef CLD_ELECTMEAS_ATTR_AC_CURRENT_DIVISOR
    zuint16                u16ACCurentDivisor;
#endif

#ifdef CLD_ELECTMEAS_ATTR_AC_POWER_MULTIPLIER
    zuint16                u16ACPowerMultiplier;
#endif

#ifdef CLD_ELECTMEAS_ATTR_AC_POWER_DIVISOR
    zuint16                u16ACPowerDivisor;
#endif

#ifdef CLD_ELECTMEAS_ATTR_MAN_SPEC_APPARENT_POWER
    zuint32                 u32ManSpecificApparentPower;
#endif

#ifdef CLD_ELECTMEAS_ATTR_MAN_SPEC_NON_ACTIVE_POWER
    zuint32                 u32NonActivePower;
#endif

#ifdef CLD_ELECTMEAS_ATTR_MAN_SPEC_FNDMTL_REACTIVE_POWER
    zint32                  i32FundamentalReactivePower;
#endif

#ifdef CLD_ELECTMEAS_ATTR_MAN_SPEC_FNDMTL_APPARENT_POWER
    zuint32                 u32FundamentalApparentPower;
#endif

#ifdef CLD_ELECTMEAS_ATTR_MAN_SPEC_FNDMTL_POWER_FACTOR
    zuint16                 u16FundamentalPowerFactor;
#endif

#ifdef CLD_ELECTMEAS_ATTR_MAN_SPEC_NON_FNDMTL_APPARENT_POWER
    zuint32                 u32NonFundamentalApparentPower;
#endif

#ifdef CLD_ELECTMEAS_ATTR_MAN_SPEC_TOTAL_HARMONIC_DISTORTION
    zuint32                 u32TotalHarmonicDistortion;
#endif

#ifdef CLD_ELECTMEAS_ATTR_MAN_SPEC_VBIAS
    zuint32                 u32VBias;
#endif

#ifdef CLD_ELECTMEAS_ATTR_MAN_SPEC_DIVISOR
    zuint16                 u16ManSpecDivisor;
#endif

#endif
    zuint16                u16ClusterRevision;

} tsCLD_ElectricalMeasurement;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_ElectricalMeasurementCreateElectricalMeasurement(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_ElectricalMeasurement;
extern uint8 au8ElectricalMeasurementAttributeControlBits[];
extern const tsZCL_AttributeDefinition asCLD_ElectricalMeasurementClusterAttributeDefinitions[];
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* ELECTRICAL_MEASUREMENT_H */
