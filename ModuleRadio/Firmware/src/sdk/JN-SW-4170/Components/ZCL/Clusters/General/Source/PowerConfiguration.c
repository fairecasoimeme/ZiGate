/*****************************************************************************
 *
 * MODULE:             Power Configuration Cluster
 *
 * COMPONENT:          PowerConfiguration.c
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Power Configuration cluster definition
 *
 * $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Clusters/General/Source/PowerConfiguration.c $
 *
 * $Revision: 22089 $
 *
 * $LastChangedBy: lmitch $
 *
 * $LastChangedDate: 2009-11-19 15:23:44 +0000 (Thu, 19 Nov 2009) $
 *
 * $Id: PowerConfiguration.c 22089 2009-11-19 15:23:44Z lmitch $
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
#include "PowerConfiguration.h"
#include "zcl_options.h"
#include "zcl_customcommand.h"

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

const tsZCL_AttributeDefinition asCLD_PowerConfigurationClusterAttributeDefinitions[] = {
#ifdef POWER_CONFIGURATION_SERVER
    /* Mains Information attribute set attribute ID's (3.3.2.2.1) */
#ifdef CLD_PWRCFG_ATTR_MAINS_VOLTAGE
    {E_CLD_PWRCFG_ATTR_ID_MAINS_VOLTAGE,                    E_ZCL_AF_RD,                            E_ZCL_UINT16,   (uint32)(&((tsCLD_PowerConfiguration*)(0))->u16MainsVoltage), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_MAINS_FREQUENCY
    {E_CLD_PWRCFG_ATTR_ID_MAINS_FREQUENCY,                  E_ZCL_AF_RD,                            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8MainsFrequency), 0},
#endif

    /* Mains settings attribute set attribute ID's (3.3.2.2.2) */
#ifdef CLD_PWRCFG_ATTR_MAINS_ALARM_MASK
    {E_CLD_PWRCFG_ATTR_ID_MAINS_ALARM_MASK,                 (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_BMAP8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8MainsAlarmMask), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_MAINS_VOLTAGE_MIN_THRESHOLD
    {E_CLD_PWRCFG_ATTR_ID_MAINS_VOLTAGE_MIN_THRESHOLD,      (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT16,   (uint32)(&((tsCLD_PowerConfiguration*)(0))->u16MainsVoltageMinThreshold), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_MAINS_VOLTAGE_MAX_THRESHOLD
    {E_CLD_PWRCFG_ATTR_ID_MAINS_VOLTAGE_MAX_THRESHOLD,      (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT16,   (uint32)(&((tsCLD_PowerConfiguration*)(0))->u16MainsVoltageMaxThreshold), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_MAINS_VOLTAGE_DWELL_TRIP_POINT
    {E_CLD_PWRCFG_ATTR_ID_MAINS_VOLTAGE_DWELL_TRIP_POINT,   (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT16,   (uint32)(&((tsCLD_PowerConfiguration*)(0))->u16MainsVoltageDwellTripPoint), 0},
#endif

    /* Battery information attribute set attribute ID's (3.3.2.2.3) */
#ifdef CLD_PWRCFG_ATTR_BATTERY_VOLTAGE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE,                  (E_ZCL_AF_RD),                          E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryVoltage), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_PERCENTAGE_REMAINING
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_REMAINING,     (E_ZCL_AF_RD|E_ZCL_AF_RP),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryPercentageRemaining), 0},
#endif

    /* Battery settings attribute set attribute ID's (3.3.2.2.4) */
#ifdef CLD_PWRCFG_ATTR_BATTERY_MANUFACTURER
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_MANUFACTURER,             (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_CSTRING,  (uint32)(&((tsCLD_PowerConfiguration*)(0))->sBatteryManufacturer), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_SIZE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_SIZE,                     (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_ENUM8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatterySize), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_AHR_RATING
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_AHR_RATING,               (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT16,   (uint32)(&((tsCLD_PowerConfiguration*)(0))->u16BatteryAHRating), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_QUANTITY
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_QUANTITY,                 (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryQuantity), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_RATED_VOLTAGE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_RATED_VOLTAGE,            (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryRatedVoltage), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_ALARM_MASK
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_ALARM_MASK,               (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_BMAP8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryAlarmMask), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_VOLTAGE_MIN_THRESHOLD
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_MIN_THRESHOLD,    (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryVoltageMinThreshold), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD1
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD1,       (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryVoltageThreshold1), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD2
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD2,       (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryVoltageThreshold2), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD3
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_VOLTAGE_THRESHOLD3,       (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryVoltageThreshold3), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_MIN_THRESHOLD
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_MIN_THRESHOLD, (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryPercentageMinThreshold), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD1
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD1,    (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryPercentageThreshold1), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD2
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD2,    (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryPercentageThreshold2), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD3
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_PERCENTAGE_THRESHOLD3,    (E_ZCL_AF_RD|E_ZCL_AF_WR),              E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8BatteryPercentageThreshold3), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_ALARM_STATE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_ALARM_STATE,              (E_ZCL_AF_RD|E_ZCL_AF_RP),              E_ZCL_BMAP32,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u32BatteryAlarmState), 0},
#endif

    /* Battery 2 information attribute set attribute ID's (3.3.2.2.3) */
#ifdef CLD_PWRCFG_ATTR_BATTERY_2_VOLTAGE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE,                  E_ZCL_AF_RD,                          E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2Voltage), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_PERCENTAGE_REMAINING
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_REMAINING,     (E_ZCL_AF_RD|E_ZCL_AF_RP),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2PercentageRemaining), 0},
#endif

    /* Battery 2 settings attribute set attribute ID's (3.3.2.2.4) */
#ifdef CLD_PWRCFG_ATTR_BATTERY_2_MANUFACTURER
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_MANUFACTURER,             (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_CSTRING,  (uint32)(&((tsCLD_PowerConfiguration*)(0))->sBattery2Manufacturer), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_SIZE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_SIZE,                     (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_ENUM8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2Size), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_AHR_RATING
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_AHR_RATING,               (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT16,   (uint32)(&((tsCLD_PowerConfiguration*)(0))->u16Battery2AHRating), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_QUANTITY
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_QUANTITY,                 (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2Quantity), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_RATED_VOLTAGE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_RATED_VOLTAGE,            (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2RatedVoltage), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_ALARM_MASK
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_ALARM_MASK,               (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_BMAP8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2AlarmMask), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_2_VOLTAGE_MIN_THRESHOLD
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_MIN_THRESHOLD,    (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2VoltageMinThreshold), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD1
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD1,    (E_ZCL_AF_RD|E_ZCL_AF_WR),               E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2VoltageThreshold1), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD2
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD2,    (E_ZCL_AF_RD|E_ZCL_AF_WR),               E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2VoltageThreshold2), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD3
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_VOLTAGE_THRESHOLD3,    (E_ZCL_AF_RD|E_ZCL_AF_WR),               E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2VoltageThreshold3), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_MIN_THRESHOLD
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_MIN_THRESHOLD,    (E_ZCL_AF_RD|E_ZCL_AF_WR),         E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2PercentageMinThreshold), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD1
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD1,    (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2PercentageThreshold1), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD2
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD2,    (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2PercentageThreshold2), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD3
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_PERCENTAGE_THRESHOLD3,    (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery2PercentageThreshold3), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_2_ALARM_STATE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_2_ALARM_STATE,              (E_ZCL_AF_RD|E_ZCL_AF_RP),            E_ZCL_BMAP32,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u32Battery2AlarmState), 0},
#endif

    /* Battery 3 information attribute set attribute ID's (3.3.2.2.3) */
#ifdef CLD_PWRCFG_ATTR_BATTERY_3_VOLTAGE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE,                  E_ZCL_AF_RD,                          E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3Voltage), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_PERCENTAGE_REMAINING
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_REMAINING,     (E_ZCL_AF_RD|E_ZCL_AF_RP),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3PercentageRemaining), 0},
#endif

    /* Battery 3 settings attribute set attribute ID's (3.3.2.2.4) */
#ifdef CLD_PWRCFG_ATTR_BATTERY_3_MANUFACTURER
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_MANUFACTURER,             (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_CSTRING,  (uint32)(&((tsCLD_PowerConfiguration*)(0))->sBattery3Manufacturer), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_SIZE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_SIZE,                     (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_ENUM8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3Size), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_AHR_RATING
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_AHR_RATING,               (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT16,   (uint32)(&((tsCLD_PowerConfiguration*)(0))->u16Battery3AHRating), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_QUANTITY
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_QUANTITY,                 (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3Quantity), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_RATED_VOLTAGE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_RATED_VOLTAGE,            (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3RatedVoltage), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_ALARM_MASK
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_ALARM_MASK,               (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_BMAP8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3AlarmMask), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_BATTERY_3_VOLTAGE_MIN_THRESHOLD
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_MIN_THRESHOLD,    (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3VoltageMinThreshold), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD1
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD1,    (E_ZCL_AF_RD|E_ZCL_AF_WR),               E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3VoltageThreshold1), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD2
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD2,    (E_ZCL_AF_RD|E_ZCL_AF_WR),               E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3VoltageThreshold2), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD3
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_VOLTAGE_THRESHOLD3,    (E_ZCL_AF_RD|E_ZCL_AF_WR),               E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3VoltageThreshold3), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_MIN_THRESHOLD
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_MIN_THRESHOLD,    (E_ZCL_AF_RD|E_ZCL_AF_WR),         E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3PercentageMinThreshold), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD1
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD1,    (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3PercentageThreshold1), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD2
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD2,    (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3PercentageThreshold2), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD3
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_PERCENTAGE_THRESHOLD3,    (E_ZCL_AF_RD|E_ZCL_AF_WR),            E_ZCL_UINT8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8Battery3PercentageThreshold3), 0},
#endif

#ifdef CLD_PWRCFG_ATTR_ID_BATTERY_3_ALARM_STATE
    {E_CLD_PWRCFG_ATTR_ID_BATTERY_3_ALARM_STATE,              (E_ZCL_AF_RD|E_ZCL_AF_RP),            E_ZCL_BMAP32,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u32Battery3AlarmState), 0},
#endif

#endif
    {E_CLD_GLOBAL_ATTR_ID_CLUSTER_REVISION,                   (E_ZCL_AF_RD|E_ZCL_AF_GA),            E_ZCL_UINT16,   (uint32)(&((tsCLD_PowerConfiguration*)(0))->u16ClusterRevision),              0},   /* Mandatory  */
    
#if (defined POWER_CONFIGURATION_SERVER) && (defined CLD_PWRCFG_ATTR_ID_ATTRIBUTE_REPORTING_STATUS)
    {E_CLD_GLOBAL_ATTR_ID_ATTRIBUTE_REPORTING_STATUS,         (E_ZCL_AF_RD|E_ZCL_AF_GA),            E_ZCL_ENUM8,    (uint32)(&((tsCLD_PowerConfiguration*)(0))->u8AttributeReportingStatus),0},  /* Optional */
#endif
};

tsZCL_ClusterDefinition sCLD_PowerConfiguration = {
        GENERAL_CLUSTER_ID_POWER_CONFIGURATION,
        FALSE,
        E_ZCL_SECURITY_NETWORK,
        (sizeof(asCLD_PowerConfigurationClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition)),
        (tsZCL_AttributeDefinition*)asCLD_PowerConfigurationClusterAttributeDefinitions,
        NULL
};

uint8 au8PowerConfigurationAttributeControlBits[(sizeof(asCLD_PowerConfigurationClusterAttributeDefinitions) / sizeof(tsZCL_AttributeDefinition))];

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       eCLD_PowerConfigurationCreatePowerConfiguration
 **
 ** DESCRIPTION:
 ** Creates a power configuration cluster
 **
 ** PARAMETERS:                 Name                        Usage
 ** tsZCL_ClusterInstance    *psClusterInstance             Cluster structure
 **
 ** RETURN:
 ** teZCL_Status
 **
 ****************************************************************************/
PUBLIC  teZCL_Status eCLD_PowerConfigurationCreatePowerConfiguration(
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
                                   NULL);    

    if(pvEndPointSharedStructPtr != NULL)
    {
#ifdef POWER_CONFIGURATION_SERVER       
        /* Initialise attribute defaults */
    #ifdef CLD_PWRCFG_ATTR_MAINS_VOLTAGE_MAX_THRESHOLD
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->u16MainsVoltageMaxThreshold = 0xffff;
    #endif

    #ifdef CLD_PWRCFG_ATTR_BATTERY_MANUFACTURER
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->sBatteryManufacturer.u8MaxLength = 
        sizeof(((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->au8BatteryManufacturer);
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->sBatteryManufacturer.u8Length = 0;
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->sBatteryManufacturer.pu8Data = 
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->au8BatteryManufacturer;
    #endif

    #ifdef CLD_PWRCFG_ATTR_BATTERY_SIZE
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->u8BatterySize = 0xff;
    #endif

    #ifdef CLD_PWRCFG_ATTR_BATTERY_2_MANUFACTURER
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->sBattery2Manufacturer.u8MaxLength = 
        sizeof(((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->au8Battery2Manufacturer);
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->sBattery2Manufacturer.u8Length = 0;
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->sBattery2Manufacturer.pu8Data = 
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->au8Battery2Manufacturer;
    #endif
    
    #ifdef CLD_PWRCFG_ATTR_BATTERY_2_SIZE
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->u8Battery2Size = 0xff;
    #endif
    
    #ifdef CLD_PWRCFG_ATTR_BATTERY_3_MANUFACTURER
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->sBattery3Manufacturer.u8MaxLength = 
        sizeof(((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->au8Battery3Manufacturer);
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->sBattery3Manufacturer.u8Length = 0;
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->sBattery3Manufacturer.pu8Data = 
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->au8Battery3Manufacturer;
    #endif
    
    #ifdef CLD_PWRCFG_ATTR_BATTERY_3_SIZE
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->u8Battery3Size = 0xff;
    #endif
    
#endif
        ((tsCLD_PowerConfiguration*)psClusterInstance->pvEndPointSharedStructPtr)->u16ClusterRevision = CLD_PWRCFG_CLUSTER_REVISION;
    }

    /* As this cluster has reportable attributes enable default reporting */
    vZCL_SetDefaultReporting(psClusterInstance);
    
    return E_ZCL_SUCCESS;

}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

