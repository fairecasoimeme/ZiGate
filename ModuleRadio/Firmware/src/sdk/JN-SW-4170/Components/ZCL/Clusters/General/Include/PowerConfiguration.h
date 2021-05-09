/*****************************************************************************
 *
 * MODULE:             Power Configuration Cluster
 *
 * COMPONENT:          PowerConfiguration.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for Power Configuration Cluster
 *
 * $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Clusters/General/Include/PowerConfiguration.h $
 *
 * $Revision: 22189 $
 *
 * $LastChangedBy: lmitch $
 *
 * $LastChangedDate: 2009-11-20 08:19:55 +0000 (Fri, 20 Nov 2009) $
 *
 * $Id: PowerConfiguration.h 22189 2009-11-20 08:19:55Z lmitch $
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

#ifndef POWER_CONFIGURATION_H
#define POWER_CONFIGURATION_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/*             PowerConfiguration Cluster - Optional Attributes             */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the PowerConfiguration cluster.                            */
/****************************************************************************/

/* Enable the optional Mains Voltage attribute */
//#define CLD_PWRCFG_ATTR_MAINS_VOLTAGE

/* Enable the optional Mains Frequency attribute */
//#define CLD_PWRCFG_ATTR_MAINS_FREQUENCY

/* Enable the optional Mains Alarm Mask attribute */
//#define CLD_PWRCFG_ATTR_MAINS_ALARM_MASK

/* Enable the optional Mains Voltage Min Threshold attribute */
//#define CLD_PWRCFG_ATTR_MAINS_VOLTAGE_MIN_THRESHOLD

/* Enable the optional Mains Voltage Max Threshold attribute */
//#define CLD_PWRCFG_ATTR_MAINS_VOLTAGE_MAX_THRESHOLD

/* Enable the optional Mains Voltage Dwell Trip Point attribute */
//#define CLD_PWRCFG_ATTR_MAINS_VOLTAGE_DWELL_TRIP_POINT

/* Enable the optional Battery Voltage attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_VOLTAGE

/* Enable the optional Battery Percentatge Remaining*/
//#define CLD_PWRCFG_ATTR_BATTERY_PERCENTAGE_REMAINING

/* Enable the optional Battery Manufacturer attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_MANUFACTURER

/* Enable the optional Battery Size attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_SIZE

/* Enable the optional Battery Amp Hour attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_AHR_RATING

/* Enable the optional Battery Quantity attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_QUANTITY

/* Enable the optional Battery Rated Voltage attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_RATED_VOLTAGE

/* Enable the optional Battery Alarm Mask attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_ALARM_MASK

/* Enable the optional Battery Voltage Min Threshold attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_VOLTAGE_MIN_THRESHOLD

/* Enable the optional Battery Voltage Threshold 1 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD1

/* Enable the optional Battery Voltage Threshold 2 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD2

/* Enable the optional Battery Voltage Threshold 3 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD3

/* Enable the optional Battery Voltage Min percentage Threshold attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_MIN_THRESHOLD    

/* Enable the optional Battery Voltage percentage Threshold 1 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD1  

/* Enable the optional Battery Voltage percentage Threshold 2 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD2 

/* Enable the optional Battery Voltage percentage Threshold 3 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD3 

/* Enable the optional Battery alarm State attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_ALARM_STATE,

/* Enable the optional Battery 2 Voltage attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_2_VOLTAGE

/* Enable the optional Battery 2 Percentatge Remaining*/
//#define CLD_PWRCFG_ATTR_BATTERY_2_PERCENTAGE_REMAINING

/* Enable the optional Battery 2 Manufacturer attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_2_MANUFACTURER

/* Enable the optional Battery 2 Size attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_2_SIZE

/* Enable the optional Battery 2 Amp Hour attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_2_AHR_RATING

/* Enable the optional Battery 2 Quantity attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_2_QUANTITY

/* Enable the optional Battery 2 Rated Voltage attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_2_RATED_VOLTAGE

/* Enable the optional Battery 2 Alarm Mask attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_2_ALARM_MASK

/* Enable the optional Battery 2 Voltage Min Threshold attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_2_VOLTAGE_MIN_THRESHOLD

/* Enable the optional Battery 2 Voltage Threshold 1 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD1

/* Enable the optional Battery 2 Voltage Threshold 2 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD2

/* Enable the optional Battery 2 Voltage Threshold 3 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD3

/* Enable the optional Battery 2 Voltage Min percentage Threshold attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_MIN_THRESHOLD    

/* Enable the optional Battery 2 Voltage percentage Threshold 1 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD1  

/* Enable the optional Battery 2 Voltage percentage Threshold 2 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD2 

/* Enable the optional Battery 2 Voltage percentage Threshold 3 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD3 

/* Enable the optional Battery 3 Voltage attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_3_VOLTAGE

/* Enable the optional Battery 3 Percentatge Remaining*/
//#define CLD_PWRCFG_ATTR_BATTERY_3_PERCENTAGE_REMAINING

/* Enable the optional Battery 3 Manufacturer attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_3_MANUFACTURER

/* Enable the optional Battery 3 Size attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_3_SIZE

/* Enable the optional Battery 3 Amp Hour attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_3_AHR_RATING

/* Enable the optional Battery 3 Quantity attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_3_QUANTITY

/* Enable the optional Battery 3 Rated Voltage attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_3_RATED_VOLTAGE

/* Enable the optional Battery 3 Alarm Mask attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_3_ALARM_MASK

/* Enable the optional Battery 3 Voltage Min Threshold attribute */
//#define CLD_PWRCFG_ATTR_BATTERY_3_VOLTAGE_MIN_THRESHOLD

/* Enable the optional Battery 3 Voltage Threshold 1 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD1

/* Enable the optional Battery 3 Voltage Threshold 2 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD2

/* Enable the optional Battery 3 Voltage Threshold 3 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD3

/* Enable the optional Battery 3 Voltage Min percentage Threshold attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_MIN_THRESHOLD    

/* Enable the optional Battery 3 Voltage percentage Threshold 1 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD1  

/* Enable the optional Battery 3 Voltage percentage Threshold 2 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD2 

/* Enable the optional Battery 3 Voltage percentage Threshold 3 attribute */
//#define CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD3 

/* Enable Optional attribute Attribute Reporting status */
//#define CLD_PWRCFG_ATTR_ID_ATTRIBUTE_REPORTING_STATUS
/* End of optional attributes */


/* Cluster ID's */
#define GENERAL_CLUSTER_ID_POWER_CONFIGURATION                      0x0001

/* Mains Alarm Mask */
#define CLD_PWRCFG_MAINS_VOLTAGE_TOO_LOW                            (1 << 0)
#define CLD_PWRCFG_MAINS_VOLTAGE_TOO_HIGH                           (1 << 1)

/* Battery Alarm Mask*/
#define CLD_PWRCFG_BATTERY_VOLTAGE_TOO_LOW                          (1 << 0)

#ifndef CLD_PWRCFG_CLUSTER_REVISION
    #define CLD_PWRCFG_CLUSTER_REVISION                         1
#endif 

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum 
{
    /* Mains Information attribute set attribute ID's (3.3.2.2.1) */
    E_CLD_PWRCFG_ATTR_ID_MAINS_VOLTAGE                = 0x0000,
    E_CLD_PWRCFG_ATTR_ID_MAINS_FREQUENCY,

    /* Mains settings attribute set attribute ID's (3.3.2.2.2) */
    E_CLD_PWRCFG_ATTR_ID_MAINS_ALARM_MASK             = 0x0010,
    E_CLD_PWRCFG_ATTR_ID_MAINS_VOLTAGE_MIN_THRESHOLD,
    E_CLD_PWRCFG_ATTR_ID_MAINS_VOLTAGE_MAX_THRESHOLD,
    E_CLD_PWRCFG_ATTR_ID_MAINS_VOLTAGE_DWELL_TRIP_POINT,

    /* Battery information attribute set attribute ID's (3.3.2.2.3) */
    E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE              = 0x0020,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_REMAINING,

    /* Battery settings attribute set attribute ID's (3.3.2.2.4) */
    E_CLD_PWRCFG_ATTR_ID_BATTERY_MANUFACTURER         = 0x0030,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_SIZE,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_AHR_RATING,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_QUANTITY,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_RATED_VOLTAGE,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_ALARM_MASK,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_MIN_THRESHOLD,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD1,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD2,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD3,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_MIN_THRESHOLD,    
    E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD1,  
    E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD2, 
    E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD3, 
    E_CLD_PWRCFG_ATTR_ID_BATTERY_ALARM_STATE, 
    
    /* Battery information 2 attribute set attribute ID's (3.3.2.2.3) */
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE              = 0x0040,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_REMAINING,

    /* Battery settings 2 attribute set attribute ID's (3.3.2.2.4) */
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_MANUFACTURER         = 0x0050,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_SIZE,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_AHR_RATING,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_QUANTITY,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_RATED_VOLTAGE,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_ALARM_MASK,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_MIN_THRESHOLD,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD1,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD2,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD3,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_MIN_THRESHOLD,    
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD1,  
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD2, 
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD3, 
    E_CLD_PWRCFG_ATTR_ID_BATTERY_2_ALARM_STATE,

    /* Battery information 3 attribute set attribute ID's (3.3.2.2.3) */
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE              = 0x0060,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_REMAINING,

    /* Battery settings 3 attribute set attribute ID's (3.3.2.2.4) */
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_MANUFACTURER         = 0x0070,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_SIZE,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_AHR_RATING,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_QUANTITY,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_RATED_VOLTAGE,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_ALARM_MASK,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_MIN_THRESHOLD,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD1,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD2,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD3,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_MIN_THRESHOLD,    
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD1,  
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD2, 
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD3,
    E_CLD_PWRCFG_ATTR_ID_BATTERY_3_ALARM_STATE,
} teCLD_PWRCFG_AttributeId;


/* Battery Size */
typedef enum 
{
    E_CLD_PWRCFG_BATTERY_SIZE_NO_BATTERY    = 0x00,
    E_CLD_PWRCFG_BATTERY_SIZE_BUILT_IN,
    E_CLD_PWRCFG_BATTERY_SIZE_OTHER,
    E_CLD_PWRCFG_BATTERY_SIZE_AA,
    E_CLD_PWRCFG_BATTERY_SIZE_AAA,
    E_CLD_PWRCFG_BATTERY_SIZE_C,
    E_CLD_PWRCFG_BATTERY_SIZE_D,
    E_CLD_PWRCFG_BATTERY_SIZE_UNKNOWN       = 0xff,
} teCLD_PWRCFG_BatterySize;


/* Power Configuration Cluster */
typedef struct
{

#ifdef POWER_CONFIGURATION_SERVER
#ifdef CLD_PWRCFG_ATTR_MAINS_VOLTAGE
    zuint16                 u16MainsVoltage;
#endif

#ifdef CLD_PWRCFG_ATTR_MAINS_FREQUENCY
    zuint8                  u8MainsFrequency;
#endif

#ifdef CLD_PWRCFG_ATTR_MAINS_ALARM_MASK
    zbmap8                  u8MainsAlarmMask;
#endif

#ifdef CLD_PWRCFG_ATTR_MAINS_VOLTAGE_MIN_THRESHOLD
    uint16                  u16MainsVoltageMinThreshold;
#endif

#ifdef CLD_PWRCFG_ATTR_MAINS_VOLTAGE_MAX_THRESHOLD
    uint16                  u16MainsVoltageMaxThreshold;
#endif

#ifdef CLD_PWRCFG_ATTR_MAINS_VOLTAGE_DWELL_TRIP_POINT
    uint16                  u16MainsVoltageDwellTripPoint;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_VOLTAGE
    uint8                   u8BatteryVoltage;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_PERCENTAGE_REMAINING
    uint8                   u8BatteryPercentageRemaining;
#endif    

#ifdef CLD_PWRCFG_ATTR_BATTERY_MANUFACTURER
    tsZCL_CharacterString   sBatteryManufacturer;
    uint8                   au8BatteryManufacturer[16];
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_SIZE
    zenum8                  u8BatterySize;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_AHR_RATING
    zuint16                 u16BatteryAHRating;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_QUANTITY
    zuint8                  u8BatteryQuantity;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_RATED_VOLTAGE
    zuint8                  u8BatteryRatedVoltage;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_ALARM_MASK
    zbmap8                  u8BatteryAlarmMask;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_VOLTAGE_MIN_THRESHOLD
    zuint8                  u8BatteryVoltageMinThreshold;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD1
    zuint8                  u8BatteryVoltageThreshold1;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD2
    zuint8                  u8BatteryVoltageThreshold2;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD3
    zuint8                  u8BatteryVoltageThreshold3;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_MIN_THRESHOLD
    zuint8                  u8BatteryPercentageMinThreshold;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD1
    zuint8                  u8BatteryPercentageThreshold1;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD2
    zuint8                  u8BatteryPercentageThreshold2;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD3
    zuint8                  u8BatteryPercentageThreshold3;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_ALARM_STATE
    zbmap32                 u32BatteryAlarmState;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_VOLTAGE
    uint8                   u8Battery2Voltage;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_PERCENTAGE_REMAINING
    uint8                   u8Battery2PercentageRemaining;
#endif    

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_MANUFACTURER
    tsZCL_CharacterString   sBattery2Manufacturer;
    uint8                   au8Battery2Manufacturer[16];
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_SIZE
    zenum8                  u8Battery2Size;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_AHR_RATING
    zuint16                 u16Battery2AHRating;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_QUANTITY
    zuint8                  u8Battery2Quantity;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_RATED_VOLTAGE
    zuint8                  u8Battery2RatedVoltage;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_ALARM_MASK
    zbmap8                  u8Battery2AlarmMask;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_VOLTAGE_MIN_THRESHOLD
    zuint8                  u8Battery2VoltageMinThreshold;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD1
    zuint8                  u8Battery2VoltageThreshold1;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD2
    zuint8                  u8Battery2VoltageThreshold2;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD3
    zuint8                  u8Battery2VoltageThreshold3;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_MIN_THRESHOLD
    zuint8                  u8Battery2PercentageMinThreshold;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD1
    zuint8                  u8Battery2PercentageThreshold1;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD2
    zuint8                  u8Battery2PercentageThreshold2;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD3
    zuint8                  u8Battery2PercentageThreshold3;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_ALARM_STATE
    zbmap32                 u32Battery2AlarmState;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_VOLTAGE
    uint8                   u8Battery3Voltage;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_PERCENTAGE_REMAINING
    uint8                   u8Battery3PercentageRemaining;
#endif    

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_MANUFACTURER
    tsZCL_CharacterString   sBattery3Manufacturer;
    uint8                   au8Battery3Manufacturer[16];
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_SIZE
    zenum8                  u8Battery3Size;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_AHR_RATING
    zuint16                 u16Battery3AHRating;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_QUANTITY
    zuint8                  u8Battery3Quantity;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_RATED_VOLTAGE
    zuint8                  u8Battery3RatedVoltage;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_ALARM_MASK
    zbmap8                  u8Battery3AlarmMask;
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_VOLTAGE_MIN_THRESHOLD
    zuint8                  u8Battery3VoltageMinThreshold;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD1
    zuint8                  u8Battery3VoltageThreshold1;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD2
    zuint8                  u8Battery3VoltageThreshold2;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD3
    zuint8                  u8Battery3VoltageThreshold3;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_MIN_THRESHOLD
    zuint8                  u8Battery3PercentageMinThreshold;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD1
    zuint8                  u8Battery3PercentageThreshold1;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD2
    zuint8                  u8Battery3PercentageThreshold2;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD3
    zuint8                  u8Battery3PercentageThreshold3;
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_ALARM_STATE
    zbmap32                 u32Battery3AlarmState;
#endif

#ifdef  CLD_PWRCFG_ATTR_ID_ATTRIBUTE_REPORTING_STATUS
    zuint8                  u8AttributeReportingStatus;
#endif
#endif
    zuint16                 u16ClusterRevision;

} tsCLD_PowerConfiguration;



/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_PowerConfigurationCreatePowerConfiguration(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_PowerConfiguration;
extern uint8 au8PowerConfigurationAttributeControlBits[];
extern const tsZCL_AttributeDefinition asCLD_PowerConfigurationClusterAttributeDefinitions[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* POWER_CONFIGURATION_H */
