###############################################################################
#
# MODULE:   Config.mk
#
# DESCRIPTION: ZBPro stack configuration. Defines tool, library and
#              header file details for building an app using the ZBPro stack 
# 
###############################################################################
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
# Copyright NXP B.V. 2015-2017. All rights reserved
#
# $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Stack/Modules/ZBPro/Trunk/Build/config_ZBPro.mk $
# $Revision: 93266 $
# $LastChangedBy: nxa30967 $
# $LastChangedDate: 2018-04-14 19:37:49 +0100 (Sat, 14 Apr 2018) $
# $Id: config_ZBPro.mk 93266 2018-04-14 18:37:49Z nxa30967 $
#
###############################################################################

###############################################################################
# Tools

ifneq ($(JENNIC_CHIP_FAMILY),JN518x)
ifeq ($(OS),Windows_NT)
    PDUMCONFIG = $(TOOL_BASE_DIR)/PDUMConfig/bin/PDUMConfig.exe
    ZPSCONFIG = $(TOOL_BASE_DIR)/ZPSConfig/bin/ZPSConfig.exe
else
    PDUMCONFIG = $(TOOL_BASE_DIR)/PDUMConfig/linuxbin/PDUMConfig
    ZPSCONFIG = $(TOOL_BASE_DIR)/ZPSConfig/linuxbin/ZPSConfig
endif
STACK_SIZE ?= 5000
MINIMUM_HEAP_SIZE ?= 2000
###############################################################################
# ROM based software components

INCFLAGS += -I$(COMPONENTS_BASE_DIR)/Mac/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/MicroSpecific/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/MiniMAC/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/MMAC/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/TimerServer/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/Random/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZigbeeCommon/Include
ifeq ($(JENNIC_MAC), MAC)
$(info JENNIC_MAC is MAC )
APPLIBS +=ZPSMAC
CFLAGS  += -DREDUCED_ZIGBEE_MAC_BUILD
REDUCED_MAC_LIB_SUFFIX = ZIGBEE_
else
$(info JENNIC_MAC is Mini MAC shim )
JENNIC_MAC = MiniMacShim
#APPLIBS +=ZPSMAC_Mini
JENNIC_MAC_PLATFORM ?= SOC
###############################################################################
# Determine correct MAC library for platform

ifeq ($(JENNIC_MAC_PLATFORM),SOC)
$(info JENNIC_MAC_PLATFORM is SOC)
APPLIBS +=ZPSMAC_Mini_SOC
else
ifeq ($(JENNIC_MAC_PLATFORM),SERIAL)
$(info JENNIC_MAC_PLATFORM is SERIAL)
APPLIBS +=ZPSMAC_Mini_SERIAL
APPLIBS +=SerialMiniMacUpper
else
ifeq ($(JENNIC_MAC_PLATFORM),MULTI)
$(info JENNIC_MAC_PLATFORM is MULTI)
APPLIBS +=ZPSMAC_Mini_MULTI
APPLIBS +=SerialMiniMacUpper
endif   
endif
endif
endif

###############################################################################
# RAM based software components


CFLAGS += -DPDM_USER_SUPPLIED_ID
CFLAGS += -DPDM_NO_RTOS
ifeq ($(PDM_BUILD_TYPE),_EEPROM)
CFLAGS += -DPDM$(PDM_BUILD_TYPE)
else
ifeq ($(PDM_BUILD_TYPE),_EXTERNAL_FLASH)
CFLAGS += -DPDM$(PDM_BUILD_TYPE)
else
ifeq ($(PDM_BUILD_TYPE),_NONE)
CFLAGS += -DPDM$(PDM_BUILD_TYPE)
else
$(error PDM_BUILD_TYPE must be defined please define PDM_BUILD_TYPE=_EEPROM or PDM_BUILD_TYPE=_EXTERNAL_FLASH)
endif
endif
endif


# NB Order is significant for GNU linker

APPLIBS +=PWRM
APPLIBS +=ZPSTSV
APPLIBS +=AES_SW
APPLIBS +=PDUM
APPLIBS +=ZPSAPL
APPLIBS +=Random


INCFLAGS += $(addsuffix /Include,$(addprefix -I$(COMPONENTS_BASE_DIR)/,$(APPLIBS)))
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/PDM/Include

ifneq ($(PDM_BUILD_TYPE),_NONE)
APPLIBS +=PDM$(PDM_BUILD_TYPE)_NO_RTOS
endif

ifeq ($(TRACE), 1)
CFLAGS  += -DDBG_ENABLE
$(info Building trace version ...)
APPLIBS +=DBG
else
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/DBG/Include
endif

ifeq ($(OPTIONAL_STACK_FEATURES),1)
ifneq ($(ZBPRO_DEVICE_TYPE), ZED)
APPLIBS += ZPSIPAN
else
APPLIBS += ZPSIPAN_ZED
endif
endif

ifeq ($(OPTIONAL_STACK_FEATURES),2)
ifneq ($(ZBPRO_DEVICE_TYPE), ZED)
APPLIBS += ZPSGP
else
APPLIBS += ZPSGP_ZED
endif
endif

ifeq ($(OPTIONAL_STACK_FEATURES),3)
ifneq ($(ZBPRO_DEVICE_TYPE), ZED)
APPLIBS += ZPSGP
APPLIBS += ZPSIPAN
else
APPLIBS += ZPSGP_ZED
APPLIBS += ZPSIPAN_ZED
endif
endif


###############################################################################
# Paths to components provided as source

APPSRC += ZQueue.c
APPSRC += ZTimer.c
APPSRC += app_zps_link_keys.c
###############################################################################
# Paths to network and application layer libs for stack config tools

INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZPSMAC/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZPSNWK/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZigbeeCommon/Include
ifeq ($(ZBPRO_DEVICE_TYPE), ZCR)
APPLIBS +=ZPSNWK
else
ifeq ($(ZBPRO_DEVICE_TYPE), ZED)
APPLIBS +=ZPSNWK_ZED
else
$(error ZBPRO_DEVICE_TYPE must be set to either ZCR or ZED)
endif
endif

ifeq ($(ZBPRO_DEVICE_TYPE), ZCR)
ZPS_NWK_LIB = $(COMPONENTS_BASE_DIR)/Library/libZPSNWK_$(JENNIC_CHIP_FAMILY).a
endif
ifeq ($(ZBPRO_DEVICE_TYPE), ZED)
ZPS_NWK_LIB = $(COMPONENTS_BASE_DIR)/Library/libZPSNWK_ZED_$(JENNIC_CHIP_FAMILY).a
endif


ZPS_APL_LIB = $(COMPONENTS_BASE_DIR)/Library/libZPSAPL_$(JENNIC_CHIP_FAMILY).a

LDFLAGS += -Wl,--gc-sections

#############################LEGACY CHIP END########################################

else  #Configurations for JN518x

JENNIC_CHIP_FAMILY  ?= JN518x
JENNIC_CHIP         ?= JN5180

SDK2_BASE_DIR        ?=  ../../../../../../..
ZIGBEE_BASE_DIR       = $(SDK2_BASE_DIR)/middleware/wireless/zigbee3.0
COMPONENTS_BASE_DIR   = $(ZIGBEE_BASE_DIR)
FRAMEWORK_BASE_DIR   ?= $(SDK2_BASE_DIR)/middleware/wireless/framework
FRAMEWORK_KSDK2_DIR  ?= $(SDK2_BASE_DIR)/middleware/wireless/framework_5.3.2
SUBWCREV             ?= $(SDK2_BASE_DIR)/tools/zigbee_3.0/TortoiseSVN/bin/SubWCRev.exe
TOOLCHAIN_PATH       ?= $(SDK2_BASE_DIR)/../MCUXpressoIDE_10.1.1_606/ide/tools/bin
TOOLCHAIN_DIR_PATH   ?= $(SDK2_BASE_DIR)/../MCUXpressoIDE_10.1.1_606/ide/tools
TOOL_BASE_DIR        ?= $(SDK2_BASE_DIR)/tools/zigbee_3.0
STACK_BASE_DIR       ?= $(ZIGBEE_BASE_DIR)/BuildConfig
ZIGBEE_COMMON_SRC     = $(ZIGBEE_BASE_DIR)/ZigbeeCommon/Source
WWDT_SRC              = $(SDK2_BASE_DIR)/platform/drivers/wwdt
KSDK2_PWRM_COMMON    ?= $(FRAMEWORK_KSDK2_DIR)/Common
ISP_SRC              ?= $(SDK2_BASE_DIR)/devices/$(JENNIC_CHIP)/rom_apis
OS_ABSTRACT_SRC      ?= $(FRAMEWORK_KSDK2_DIR)/OSAbstraction/Source
GENERIC_LIST_SRC     ?= $(FRAMEWORK_KSDK2_DIR)/Lists
BOARD_LEVEL_SRC      ?= $(SDK2_BASE_DIR)/boards/dk6_jn5180
CHIP_STARTUP_SRC     ?= $(SDK2_BASE_DIR)/devices/$(JENNIC_CHIP)/gcc
CHIP_SYSTEM_SRC      ?= $(SDK2_BASE_DIR)/devices/$(JENNIC_CHIP)
FSL_RNG_SRC          ?= $(SDK2_BASE_DIR)/platform/drivers/jn_rng
FSL_UART_SRC         ?= $(SDK2_BASE_DIR)/platform/drivers/flexcomm
FSL_FLASH_SRC        ?= $(SDK2_BASE_DIR)/platform/drivers/jn_flash
FSL_AES_SRC          ?= $(SDK2_BASE_DIR)/platform/drivers/aes
FSL_COMMON_SRC       ?= $(SDK2_BASE_DIR)/platform/drivers/common
FSL_INPUTMUX_SRC     ?= $(SDK2_BASE_DIR)/platform/drivers/inputmux
FSL_FMEAS_SRC        ?= $(SDK2_BASE_DIR)/platform/drivers/fmeas
FSL_EXCEPTIONS_SRC   ?= $(FRAMEWORK_BASE_DIR)/DebugExceptionHandlers_jn518x/src
DEBUG_FIFO_SRC       ?= $(FRAMEWORK_BASE_DIR)/DebugFifo/Source
ifeq ($(OS),Windows_NT)
    PDUMCONFIG = $(TOOL_BASE_DIR)/PDUMConfig/bin/PDUMConfig.exe
    ZPSCONFIG  = $(TOOL_BASE_DIR)/ZPSConfig/bin/ZPSConfig.exe
else
    PDUMCONFIG = $(TOOL_BASE_DIR)/PDUMConfig/linuxbin/PDUMConfig
    ZPSCONFIG  = $(TOOL_BASE_DIR)/ZPSConfig/linuxbin/ZPSConfig
endif
JET_BASE            ?= $(SDK2_BASE_DIR)/tools/zigbee_3.0/JET/OTAUtils

##################################################################################
## Source included by default

APPSRC += ZQueue.c
APPSRC += ZTimer.c
APPSRC += app_zps_link_keys.c
APPSRC += fsl_os_abstraction_bm.c
APPSRC += appZdpExtraction.c
APPSRC += appZpsBeaconHandler.c
APPSRC += appZpsExtendedDebug.c
APPSRC += board.c
APPSRC += clock_config.c
APPSRC += system_jn5180.c
APPSRC += startup_jn5180.c
APPSRC += fsl_wwdt.c
APPSRC += fsl_clock.c
APPSRC += fsl_reset.c
APPSRC += fsl_rng.c
APPSRC += fsl_usart.c
APPSRC += fsl_flexcomm.c
APPSRC += fsl_flash.c
APPSRC += fsl_common.c
APPSRC += fsl_aes.c
APPSRC += fsl_power.c
APPSRC += fsl_wtimer.c
APPSRC += fsl_inputmux.c
APPSRC += fsl_fmeas.c
APPSRC += Exceptions_NVIC.c
APPSRC += MicroExceptions_arm.c
APPSRC += Debug.c

##################################################################################
## INCLUDE paths
include $(SDK2_BASE_DIR)/devices/$(JENNIC_CHIP)/gcc/config.mk

INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZPSMAC/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZPSNWK/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZigbeeCommon/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZPSAPL/Include
INCFLAGS += -I$(FRAMEWORK_BASE_DIR)/PWRM/Include
INCFLAGS += -I$(FRAMEWORK_BASE_DIR)/MiniMac/Include
INCFLAGS += -I$(FRAMEWORK_BASE_DIR)/MiniMac/mMac/Include
INCFLAGS += -I$(FRAMEWORK_BASE_DIR)/MiniMac/uMac/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZPSTSV/Include
INCFLAGS += -I$(FRAMEWORK_BASE_DIR)/DBG/Include
INCFLAGS += -I$(SDK2_BASE_DIR)/platform/drivers/aes
INCFLAGS += -I$(WWDT_SRC)
INCFLAGS += -I$(KSDK2_PWRM_COMMON)
INCFLAGS += -I$(ISP_SRC)
INCFLAGS += -I$(GENERIC_LIST_SRC)
INCFLAGS += -I$(FRAMEWORK_BASE_DIR)/PDM/Include
INCFLAGS += -I$(BOARD_LEVEL_SRC)
INCFLAGS += -I$(CHIP_SYSTEM_SRC)
INCFLAGS += -I$(FSL_COMMON_SRC)
INCFLAGS += -I$(FSL_AES_SRC)
INCFLAGS += -I$(FSL_FLASH_SRC)
INCFLAGS += -I$(FSL_INPUTMUX_SRC)
INCFLAGS += -I$(FSL_FMEAS_SRC)
INCFLAGS += -I$(FSL_EXCEPTIONS_SRC)/../inc
INCFLAGS += -I$(FRAMEWORK_BASE_DIR)/DebugFifo/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/OSAbstraction/Interface
ifeq ($(TRACE), 1)
CFLAGS  += -DDBG_ENABLE
CFLAGS  += -DDEBUG_ENABLE
$(info Building trace version ...)
endif 

##################################################################################
## LIBS 

APPLIBS +=ZPSTSV
APPLIBS +=aes_sw
APPLIBS +=PDUM
APPLIBS +=Random
APPLIBS +=PDM
APPLIBS +=ZPSAPL
APPLIBS +=ZPSMAC_Mini
APPLIBS +=PWRM
INCFLAGS += $(addsuffix /Include,$(addprefix -I$(FRAMEWORK_BASE_DIR)/,$(APPLIBS)))

CFLAGS += -DPDM_USER_SUPPLIED_ID
CFLAGS += -DPDM_NO_RTOS

ifeq ($(OPTIONAL_STACK_FEATURES),1)
ifneq ($(ZBPRO_DEVICE_TYPE), ZED)
APPLIBS += ZPSIPAN
else
APPLIBS += ZPSIPAN_ZED
endif
endif

ifeq ($(OPTIONAL_STACK_FEATURES),2)
ifneq ($(ZBPRO_DEVICE_TYPE), ZED)
APPLIBS += ZPSGP
else
APPLIBS += ZPSGP_ZED
endif
endif

ifeq ($(OPTIONAL_STACK_FEATURES),3)
ifneq ($(ZBPRO_DEVICE_TYPE), ZED)
APPLIBS += ZPSGP
APPLIBS += ZPSIPAN
else
APPLIBS += ZPSGP_ZED
APPLIBS += ZPSIPAN_ZED
endif
endif

ifeq ($(ZBPRO_DEVICE_TYPE), ZCR)
APPLIBS +=ZPSNWK
else
ifeq ($(ZBPRO_DEVICE_TYPE), ZED)
APPLIBS +=ZPSNWK_ZED
else
$(error ZBPRO_DEVICE_TYPE must be set to either ZCR or ZED)
endif
endif

ifeq ($(ZBPRO_DEVICE_TYPE), ZCR)
ZPS_NWK_LIB = $(COMPONENTS_BASE_DIR)/Library/libZPSNWK_$(JENNIC_CHIP_FAMILY).a
endif
ifeq ($(ZBPRO_DEVICE_TYPE), ZED)
ZPS_NWK_LIB = $(COMPONENTS_BASE_DIR)/Library/libZPSNWK_ZED_$(JENNIC_CHIP_FAMILY).a
endif
ZPS_APL_LIB = $(COMPONENTS_BASE_DIR)/Library/libZPSAPL_$(JENNIC_CHIP_FAMILY).a
ZIGBEE_BASE_SRC = $(ZIGBEE_COMMON_SRC):$(WWDT_SRC):$(OS_ABSTRACT_SRC):$(GENERIC_LIST_SRC):$(BOARD_LEVEL_SRC)\
                  :$(CHIP_STARTUP_SRC):$(CHIP_SYSTEM_SRC):$(FSL_RNG_SRC):$(FSL_UART_SRC):$(FSL_FLASH_SRC)\
                  :$(FSL_AES_SRC):$(FSL_COMMON_SRC):$(FSL_INPUTMUX_SRC):$(FSL_FMEAS_SRC):$(FSL_EXCEPTIONS_SRC)\
                  :$(DEBUG_FIFO_SRC)
LDFLAGS += -L  $(COMPONENTS_BASE_DIR)/Library/
LDFLAGS += -L  $(COMPONENTS_BASE_DIR)/BuildConfig/ZBPro/Build
LDFLAGS += -Wl,--gc-sections
LDFLAGS += --specs=nosys.specs
endif
###############################################################################
