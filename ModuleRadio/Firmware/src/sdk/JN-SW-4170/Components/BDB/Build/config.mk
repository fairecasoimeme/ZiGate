###############################################################################
#
# MODULE:      config_BDB.mk
#
# COMPONENT:   BDB
#
# AUTHOR:      
#
# DESCRIPTION: Base Device Behaviour Configuration
#              
#
# $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/BDB/Trunk/Build/config.mk $
#
# $Revision: 86398 $
#
# $LastChangedBy: nxp29741 $
#
# $LastChangedDate: 2017-01-24 11:21:43 +0000 (Tue, 24 Jan 2017) $
#
# $Id: config.mk 86398 2017-01-24 11:21:43Z nxp29741 $
#
###############################################################################
#
# This software is owned by NXP B.V. and/or its supplier and is protected
# under applicable copyright laws. All rights are reserved. We grant You,
# and any third parties, a license to use this software solely and
# exclusively on NXP products [NXP Microcontrollers such as JN514x, JN516x, JN517x].
# You, and any third parties must reproduce the copyright and warranty notice 
# and any other legend of ownership on each  copy or partial copy of the software.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
# POSSIBILITY OF SUCH DAMAGE. 
# 
# Copyright NXP B.V. 2015-2016. All rights reserved
#
###############################################################################

###############################################################################
# General Include and Source

BDB_INC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Include
INCFLAGS += -I$(BDB_INC_DIR)
BDB_COMN_INC_DIR += $(COMPONENTS_BASE_DIR)/BDB/Source/Common
INCFLAGS += -I$(BDB_COMN_INC_DIR)
BDB_COMN_SRC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/Common
COMN_SRC := $(shell cd $(BDB_COMN_SRC_DIR); ls *.c)
APPSRC += $(COMN_SRC)

ifeq ($(JENNIC_CHIP_FAMILY),$(filter $(JENNIC_CHIP_FAMILY),JN517x JN516x)) 
# ZigBee Common Include and Source
ZIGBEE_COMN_INC_DIR = $(COMPONENTS_BASE_DIR)/ZigbeeCommon/Include
ZIGBEE_COMN_SRC_DIR = $(COMPONENTS_BASE_DIR)/ZigbeeCommon/Source
ZIGBEE_COMN_SRC += appZpsBeaconHandler.c 
ZIGBEE_COMN_SRC += appZdpExtraction.c
APPSRC += $(ZIGBEE_COMN_SRC)
endif

ifeq ($(ZBPRO_DEVICE_TYPE), ZCR)
CFLAGS += -DZBPRO_DEVICE_TYPE_ZCR
else
CFLAGS += -DZBPRO_DEVICE_TYPE_ZED
endif

###############################################################################
# Feature Specific Includes and Sources

ifeq ($(BDB_SUPPORT_NWK_STEERING), 1)
CFLAGS += -DBDB_SUPPORT_NWK_STEERING
BDB_NS_INC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/NwkSteering
BDB_NS_SRC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/NwkSteering
INCFLAGS += -I$(BDB_NS_INC_DIR)
NS_SRC := $(shell cd $(BDB_NS_SRC_DIR); ls *.c)
APPSRC += $(NS_SRC)
endif

ifeq ($(BDB_SUPPORT_NWK_FORMATION), 1)
CFLAGS += -DBDB_SUPPORT_NWK_FORMATION
BDB_NF_INC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/NwkFormation
BDB_NF_SRC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/NwkFormation
INCFLAGS += -I$(BDB_NF_INC_DIR)
NF_SRC := $(shell cd $(BDB_NF_SRC_DIR); ls *.c)
APPSRC += $(NF_SRC)
endif

ifeq ($(BDB_SUPPORT_TOUCHLINK_INITIATOR_END_DEVICE), 1)
CFLAGS += -DBDB_SUPPORT_TOUCHLINK
BDB_TL_INC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/TouchLink
BDB_TL_SRC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/TouchLink
INCFLAGS += -I$(BDB_TL_INC_DIR)
TL_SRC = bdb_tl_end_device_initiator_target.c
TL_SRC += bdb_tl_common.c
TL_SRC += ecb_decrypt.c
APPSRC += $(TL_SRC)
endif

ifeq ($(BDB_SUPPORT_TOUCHLINK_INITIATOR_ROUTER), 1)
CFLAGS += -DBDB_SUPPORT_TOUCHLINK
BDB_TL_INC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/TouchLink
BDB_TL_SRC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/TouchLink
INCFLAGS += -I$(BDB_TL_INC_DIR)
TL_SRC = bdb_tl_router_initiator_target.c
TL_SRC += bdb_tl_common.c
TL_SRC += ecb_decrypt.c
APPSRC += $(TL_SRC)
endif

ifeq ($(BDB_SUPPORT_TOUCHLINK_TARGET), 1)
CFLAGS += -DBDB_SUPPORT_TOUCHLINK
BDB_TL_INC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/TouchLink
BDB_TL_SRC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/TouchLink
INCFLAGS += -I$(BDB_TL_INC_DIR)
TL_SRC = bdb_tl_router_target.c
TL_SRC += bdb_tl_common.c
TL_SRC += ecb_decrypt.c
APPSRC += $(TL_SRC)
endif

ifeq ($(BDB_SUPPORT_FIND_AND_BIND_INITIATOR), 1)
CFLAGS += -DBDB_SUPPORT_FIND_AND_BIND_INITIATOR
BDB_FB_INI_INC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/FindAndBind
BDB_FB_INI_SRC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/FindAndBind
INCFLAGS += -I$(BDB_FB_INI_INC_DIR)
ifneq ($(BDB_SUPPORT_FIND_AND_BIND_TARGET), 1)
    FB_INI_SRC = bdb_fb_common.c
endif
FB_INI_SRC += bdb_fb_initiator.c
APPSRC += $(FB_INI_SRC)
endif

ifeq ($(BDB_SUPPORT_FIND_AND_BIND_TARGET), 1)
CFLAGS += -DBDB_SUPPORT_FIND_AND_BIND_TARGET
BDB_FB_TAR_INC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/FindAndBind
BDB_FB_TAR_SRC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/FindAndBind
INCFLAGS += -I$(BDB_FB_TAR_INC_DIR)
FB_TAR_SRC = bdb_fb_common.c
FB_TAR_SRC += bdb_fb_target.c
APPSRC += $(FB_TAR_SRC)
endif

ifeq ($(BDB_SUPPORT_OOBC), 1)
CFLAGS += -DBDB_SUPPORT_OOBC
BDB_OOB_INC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/OutOfBand
BDB_OOB_SRC_DIR = $(COMPONENTS_BASE_DIR)/BDB/Source/OutOfBand
INCFLAGS += -I$(BDB_OOB_INC_DIR)
OOB_SRC += bdb_DeviceCommissioning.c
APPSRC += $(OOB_SRC)
endif

###############################################################################
ifeq ($(JENNIC_CHIP_FAMILY),$(filter $(JENNIC_CHIP_FAMILY),JN517x JN516x)) 
BDB_SRC_DIR = $(BDB_COMN_SRC_DIR):$(ZIGBEE_COMN_SRC_DIR):$(BDB_NS_SRC_DIR):$(BDB_NF_SRC_DIR):$(BDB_TL_SRC_DIR):$(BDB_FB_INI_SRC_DIR): $(BDB_FB_TAR_SRC_DIR): $(BDB_OOB_SRC_DIR)
else
BDB_SRC_DIR = $(BDB_COMN_SRC_DIR):$(BDB_NS_SRC_DIR):$(BDB_NF_SRC_DIR):$(BDB_TL_SRC_DIR):$(BDB_FB_INI_SRC_DIR): $(BDB_FB_TAR_SRC_DIR): $(BDB_OOB_SRC_DIR)
endif