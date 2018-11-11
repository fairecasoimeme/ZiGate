/****************************************************************************
 *
 *                 THIS IS A GENERATED FILE. DO NOT EDIT!
 *
 * MODULE:         ZPSConfig
 *
 * COMPONENT:      zps_gen.h
 *
 * DATE:           Wed Nov  7 18:09:47 2018
 *
 * AUTHOR:         NXP Zigbee Protocol Stack Configuration Tool
 *
 * DESCRIPTION:    ZPS definitions
 *
 ****************************************************************************
 *

 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
 * Copyright NXP B.V. 2017. All rights reserved
 ****************************************************************************/

#ifndef _ZPS_GEN_H
#define _ZPS_GEN_H

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define ZPS_NWK_OPT_ALL
#define ZPS_COORDINATOR
#define ZPS_NODE_ZIGBEENODECONTROLBRIDGE

/* Profile 'ZDP' */
#define ZDP_PROFILE_ID    (0x0000)
#define ZDP_NWK_ADDR_REQ_CLUSTER_ID    (0x0000)
#define ZDP_IEEE_ADDR_REQ_CLUSTER_ID    (0x0001)
#define ZDP_NODE_DESC_REQ_CLUSTER_ID    (0x0002)
#define ZDP_POWER_DESC_REQ_CLUSTER_ID    (0x0003)
#define ZDP_SIMPLE_DESC_REQ_CLUSTER_ID    (0x0004)
#define ZDP_ACTIVE_EP_REQ_CLUSTER_ID    (0x0005)
#define ZDP_MATCH_DESC_REQ_CLUSTER_ID    (0x0006)
#define ZDP_COMPLEX_DESC_REQ_CLUSTER_ID    (0x0010)
#define ZDP_USER_DESC_REQ_CLUSTER_ID    (0x0011)
#define ZDP_DISCOVERY_CACHE_REQ_CLUSTER_ID    (0x0012)
#define ZDP_DEVICE_ANNCE_CLUSTER_ID    (0x0013)
#define ZDP_USER_DESC_SET_CLUSTER_ID    (0x0014)
#define ZDP_SYSTEM_SERVER_DISCOVERY_REQ_CLUSTER_ID    (0x0015)
#define ZDP_DISCOVERY_STORE_REQ_CLUSTER_ID    (0x0016)
#define ZDP_NODE_DESC_STORE_REQ_CLUSTER_ID    (0x0017)
#define ZDP_POWER_DESC_STORE_REQ_CLUSTER_ID    (0x0018)
#define ZDP_ACTIVE_EP_STORE_REQ_CLUSTER_ID    (0x0019)
#define ZDP_SIMPLE_DESC_STORE_REQ_CLUSTER_ID    (0x001a)
#define ZDP_REMOVE_NODE_CACHE_REQ_CLUSTER_ID    (0x001b)
#define ZDP_FIND_NODE_CHACHE_REQ_CLUSTER_ID    (0x001c)
#define ZDP_EXTENDED_SIMPLE_DESC_REQ_CLUSTER_ID    (0x001d)
#define ZDP_EXTENDED_ACTIVE_EP_REQ_CLUSTER_ID    (0x001e)
#define ZDP_END_DEVICE_BIND_REQ_CLUSTER_ID    (0x0020)
#define ZDP_BIND_REQ_CLUSTER_ID    (0x0021)
#define ZDP_UNBIND_REQ_CLUSTER_ID    (0x0022)
#define ZDP_BIND_REGISTER_REQ_CLUSTER_ID    (0x0023)
#define ZDP_REPLACE_DEVICE_REQ_CLUSTER_ID    (0x0024)
#define ZDP_STORE_BKUP_BIND_ENTRY_REQ_CLUSTER_ID    (0x0025)
#define ZDP_REMOVE_BKUP_BIND_ENTRY_REQ_CLUSTER_ID    (0x0026)
#define ZDP_BACKUP_BIND_TABLE_REQ_CLUSTER_ID    (0x0027)
#define ZDP_RECOVER_BIND_TABLE_REQ_CLUSTER_ID    (0x0028)
#define ZDP_BACKUP_SOURCE_BIND_REQ_CLUSTER_ID    (0x0029)
#define ZDP_RECOVER_SOURCE_BIND_REQ_CLUSTER_ID    (0x002a)
#define ZDP_MGMT_NWK_DISC_REQ_CLUSTER_ID    (0x0030)
#define ZDP_MGMT_LQI_REQ_CLUSTER_ID    (0x0031)
#define ZDP_MGMT_RTG_REQ_CLUSTER_ID    (0x0032)
#define ZDP_MGMT_BIND_REQ_CLUSTER_ID    (0x0033)
#define ZDP_MGMT_LEAVE_REQ_CLUSTER_ID    (0x0034)
#define ZDP_MGMT_DIRECT_JOIN_REQ_CLUSTER_ID    (0x0035)
#define ZDP_MGMT_PERMIT_JOINING_REQ_CLUSTER_ID    (0x0036)
#define ZDP_MGMT_CACHE_REQ_CLUSTER_ID    (0x0037)
#define ZDP_MGMT_NWK_UPDATE_REQ_CLUSTER_ID    (0x0038)
#define ZDP_NWK_ADDR_RSP_CLUSTER_ID    (0x8000)
#define ZDP_IEEE_ADDR_RSP_CLUSTER_ID    (0x8001)
#define ZDP_NODE_DESC_RSP_CLUSTER_ID    (0x8002)
#define ZDP_POWER_DESC_RSP_CLUSTER_ID    (0x8003)
#define ZDP_SIMPLE_DESC_RSP_CLUSTER_ID    (0x8004)
#define ZDP_ACTIVE_EP_RSP_CLUSTER_ID    (0x8005)
#define ZDP_MATCH_DESC_RSP_CLUSTER_ID    (0x8006)
#define ZDP_COMPLEX_DESC_RSP_CLUSTER_ID    (0x8010)
#define ZDP_USER_DESC_RSP_CLUSTER_ID    (0x8011)
#define ZDP_DISCOVERY_CACHE_RSP_CLUSTER_ID    (0x8012)
#define ZDP_USER_DESC_CONF_CLUSTER_ID    (0x8014)
#define ZDP_SYSTEM_SERVER_DISCOVERY_RSP_CLUSTER_ID    (0x8015)
#define ZDP_DISCOVERY_STORE_RSP_CLUSTER_ID    (0x8016)
#define ZDP_NODE_DESC_STORE_RSP_CLUSTER_ID    (0x8017)
#define ZDP_POWER_DESC_STORE_RSP_CLUSTER_ID    (0x8018)
#define ZDP_ACTIVE_EP_STORE_RSP_CLUSTER_ID    (0x8019)
#define ZDP_SIMPLE_DESC_STORE_RSP_CLUSTER_ID    (0x801a)
#define ZDP_REMOVE_NODE_CACHE_RSP_CLUSTER_ID    (0x801b)
#define ZDP_FIND_NODE_CHACHE_RSP_CLUSTER_ID    (0x801c)
#define ZDP_EXTENDED_SIMPLE_DESC_RSP_CLUSTER_ID    (0x801d)
#define ZDP_EXTENDED_ACTIVE_EP_RSP_CLUSTER_ID    (0x801e)
#define ZDP_END_DEVICE_BIND_RSP_CLUSTER_ID    (0x8020)
#define ZDP_BIND_RSP_CLUSTER_ID    (0x8021)
#define ZDP_UNBIND_RSP_CLUSTER_ID    (0x8022)
#define ZDP_BIND_REGISTER_RSP_CLUSTER_ID    (0x8023)
#define ZDP_REPLACE_DEVICE_RSP_CLUSTER_ID    (0x8024)
#define ZDP_STORE_BKUP_BIND_ENTRY_RSP_CLUSTER_ID    (0x8025)
#define ZDP_REMOVE_BKUP_BIND_ENTRY_RSP_CLUSTER_ID    (0x8026)
#define ZDP_BACKUP_BIND_TABLE_RSP_CLUSTER_ID    (0x8027)
#define ZDP_RECOVER_BIND_TABLE_RSP_CLUSTER_ID    (0x8028)
#define ZDP_BACKUP_SOURCE_BIND_RSP_CLUSTER_ID    (0x8029)
#define ZDP_RECOVER_SOURCE_BIND_RSP_CLUSTER_ID    (0x802a)
#define ZDP_MGMT_NWK_DISC_RSP_CLUSTER_ID    (0x8030)
#define ZDP_MGMT_LQI_RSP_CLUSTER_ID    (0x8031)
#define ZDP_MGMT_RTG_RSP_CLUSTER_ID    (0x8032)
#define ZDP_MGMT_BIND_RSP_CLUSTER_ID    (0x8033)
#define ZDP_MGMT_LEAVE_RSP_CLUSTER_ID    (0x8034)
#define ZDP_MGMT_DIRECT_JOIN_RSP_CLUSTER_ID    (0x8035)
#define ZDP_MGMT_PERMIT_JOINING_RSP_CLUSTER_ID    (0x8036)
#define ZDP_MGMT_CACHE_RSP_CLUSTER_ID    (0x8037)
#define ZDP_MGMT_NWK_UPDATE_RSP_CLUSTER_ID    (0x8038)
#define ZDP_PARENT_ANNCE_REQ_CLUSTER_ID    (0x001f)
#define ZDP_PARENT_ANNCE_RSP_CLUSTER_ID    (0x801f)

/* Profile 'ZLO' */
#define ZLO_PROFILE_ID    (0x0104)
#define ZLO_BASIC_CLUSTER_ID    (0x0000)
#define ZLO_POWER_CONFIGURATION_CLUSTER_ID    (0x0001)
#define ZLO_IDENTIFY_CLUSTER_ID    (0x0003)
#define ZLO_GROUPS_CLUSTER_ID    (0x0004)
#define ZLO_SCENES_CLUSTER_ID    (0x0005)
#define ZLO_ON_OFF_CLUSTER_ID    (0x0006)
#define ZLO_LEVEL_CONTROL_CLUSTER_ID    (0x0008)
#define ZLO_COLOR_CONTROL_CLUSTER_ID    (0x0300)
#define ZLO_DOOR_LOCK_CLUSTER_ID    (0x0101)
#define ZLO_ZLL_COMMISSIONING_CLUSTER_ID    (0x1000)
#define ZLO_IASZONE_CLUSTER_ID    (0x0500)
#define ZLO_OTA_CLUSTER_ID    (0x0019)
#define ZLO_METERING_CLUSTER_ID    (0x0702)
#define ZLO_THERMOSTAT_CLUSTER_ID    (0x0201)
#define ZLO_THERMOSTAT_UI_CLUSTER_ID    (0x0204)
#define ZLO_MEASUREMENT_AND_SENSING_CLUSTER_ID_ILLUMINANCE_LEVEL_SENSING_CLUSTER_ID    (0x0401)
#define ZLO_MEASUREMENT_AND_SENSING_CLUSTER_ID_ILLUMINANCE_MEASUREMENT_CLUSTER_ID    (0x0400)
#define ZLO_MEASUREMENT_AND_SENSING_CLUSTER_ID_OCCUPANCY_SENSING_CLUSTER_ID    (0x0406)
#define ZLO_MEASUREMENT_AND_SENSING_CLUSTER_ID_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID    (0x0405)
#define ZLO_MEASUREMENT_AND_SENSING_CLUSTER_ID_TEMPERATURE_MEASUREMENT_CLUSTER_ID    (0x0402)
#define ZLO_MEASUREMENT_AND_SENSING_CLUSTER_ID_PRESSURE_MEASUREMENT_CLUSTER_ID    (0x0403)
#define ZLO_ASC_CLUSTER_ID    (0x0b03)
#define ZLO_ELECTRICAL_MEASUREMENTS_CLUSTER_ID    (0x0b04)
#define ZLO_DIAGNOSTICS_CLUSTER_ID    (0x0b05)
#define ZLO_DEFAULT_CLUSTER_ID    (0xffff)
#define ZLO_MULTISTATEINPUT_CLUSTER_ID    (0x0012)
#define ZLO_MULTISTATEOUTPUT_CLUSTER_ID    (0x0013)
#define ZLO_BINARYINPUT_CLUSTER_ID    (0x000f)
#define ZLO_XIAOMIINFORMATIONS_CLUSTER_ID    (0xff01)
#define ZLO_XIAOMIINFORMATIONS2_CLUSTER_ID    (0xff02)

/* Node 'ZigbeeNodeControlBridge' */
/* Endpoints */
#define ZIGBEENODECONTROLBRIDGE_ZDO_ENDPOINT    (0)
#define ZIGBEENODECONTROLBRIDGE_ZLO_ENDPOINT    (1)
#define ZIGBEENODECONTROLBRIDGE_ORVIBO_ENDPOINT    (10)
/* Table Sizes */
#define ZPS_NEIGHBOUR_TABLE_SIZE      (80)
#define ZPS_ADDRESS_MAP_TABLE_SIZE    (80)
#define ZPS_ROUTING_TABLE_SIZE        (70)
#define ZPS_MAC_ADDRESS_TABLE_SIZE    (80)
#define ZPS_BINDING_TABLE_SIZE        (5)
#define ZPS_GROUP_TABLE_SIZE          (5)
#define ZPS_CHILD_TABLE_SIZE          (50)
#define ZPS_MAX_CHANNEL_LIST_SIZE     (1)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern void *g_pvApl;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void* ZPS_vGetGpContext(void);
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#endif
