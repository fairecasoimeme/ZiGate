##############################################################################
#
# MODULE:   config_JN516x.mk
#
# DESCRIPTION:Configuration make include file for JN516x
#
#############################################################################
# 
# This software is owned by NXP and/or its supplier and is protected
# under applicable copyright laws. All rights are reserved. We grant You,
# and any third parties, a license to use this software solely and
# exclusively on NXP products. You, and any third parties must reproduce
# the copyright and warranty notice and any other legend of ownership on each
# copy or partial copy of the software.
# 
# THIS SOFTWARE IS PROVIDED "AS IS". NXP MAKES NO WARRANTIES, WHETHER
# EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
# ACCURACY OR LACK OF NEGLIGENCE. NXP SHALL NOT, IN ANY CIRCUMSTANCES,
# BE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,
# INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.
# 
# Copyright NXP 2012. All rights reserved
# 
#############################################################################

# Ensure chip and family are set
override JENNIC_CHIP_FAMILY = JN516x

# Define numeric value for chip type
CFLAGS += -DJN516x=5160
CFLAGS += -DJN5164=5164
CFLAGS += -DJENNIC_CHIP_NAME=_JN5164
CFLAGS += -DJENNIC_CHIP_FAMILY_NAME=_JN516x

# Base dir for selected chip
CHIP_BASE_DIR = $(SDK_BASE_DIR)/Chip/$(JENNIC_CHIP)

# include definitions for the BA2 architecture
include $(SDK_BASE_DIR)/Chip/Common/Build/config_ba2.mk

# Chip specific C flags
# watchdog is enabled by default on chip so allow disable if reqd
CFLAGS += -DWATCHDOG_ENABLED

# Feature set:
#   JENNIC_HW_xx is silicon feature and so fixed
#   JENNIC_SW_xx is build option and can be changed
#
#   JENNIC_HW_BBC_RXINCCA:    BBC RX during CCA capability
#   JENNIC_HW_BBC_DMA:        BBC frame buffer DMA mechanism
#   JENNIC_HW_BBC_ISA:        BBC inline security engine 
#   JENNIC_SW_EXTERNAL_FLASH: whether external flash is supported
#   JN516X_DMA_UART_BACKWARDS_COMPATIBLE_API: API behaves like the older versions with no visible UART DMA 
#   UART_BACKWARDS_COMPATIBLE_API: API behaves like the older versions (supercedes above)
#   PDM_DESCRIPTOR_BASED_API: Use new descriptorless API interface 
#
CFLAGS += -DJENNIC_HW_BBC_RXINCCA=1
CFLAGS += -DJENNIC_HW_BBC_DMA=1
CFLAGS += -DJENNIC_HW_BBC_ISA=0
CFLAGS += -DJENNIC_SW_EXTERNAL_FLASH=0
CFLAGS += -DJN516X_DMA_UART_BACKWARDS_COMPATIBLE_API=1
CFLAGS += -DUART_BACKWARDS_COMPATIBLE_API=1
#CFLAGS += -DPDM_DESCRIPTOR_BASED_API=1

# Linker flags
LDFLAGS += -nostartfiles

# Library search paths
LDFLAGS += -L$(CHIP_BASE_DIR)/Build
LDFLAGS += -L$(CHIP_BASE_DIR)/Library

# JenNet-IP always uses the MiniMac.
ifeq ($(JENNIC_STACK), JIP)
override JENNIC_MAC = MiniMac
endif

# Standard libraries: Peripheral API, MAC, etc.
ifneq ($(JENNIC_STACK), None)
 ifeq ($(JENNIC_MAC), MAC)
  LDLIBS  += AppApi_$(REDUCED_MAC_LIB_SUFFIX)$(JENNIC_CHIP_FAMILY)
  LDLIBS  += MAC_$(REDUCED_MAC_LIB_SUFFIX)$(JENNIC_CHIP_FAMILY)
  LDLIBS  += TimerServer_$(JENNIC_CHIP_FAMILY)
  LDLIBS  += TOF_$(JENNIC_CHIP_FAMILY)
  LDLIBS  += Xcv_$(JENNIC_CHIP_FAMILY)
 else
  ifneq ($(findstring $(JENNIC_MAC),MiniMac MiniMacShim),)
   LDLIBS  += MiniMac_$(JENNIC_CHIP_FAMILY)
   LDLIBS  += MiniMacShim_$(JENNIC_CHIP_FAMILY)
  endif
  LDLIBS  += MMAC_$(JENNIC_CHIP_FAMILY)
 endif
endif
LDLIBS  += Aes_$(JENNIC_CHIP_FAMILY)
LDLIBS  += HardwareApi_$(JENNIC_CHIP_FAMILY)
LDLIBS  += MicroSpecific_$(JENNIC_CHIP_FAMILY)
LDLIBS  += Boot_$(JENNIC_CHIP_FAMILY)

# Stack-specific PDM library variants
ifeq ($(JENNIC_STACK), JIP)
LDLIBS  += PDM_EEPROM_$(JENNIC_CHIP_FAMILY)
endif

# Export linker command file if building patch library
ifeq ($(JENNIC_STACK), None)
LINKER_FILE = AppBuildNone
else
ifeq ($(JENNIC_STACK), JIP)
LINKER_FILE = AppBuildJip
else
ifneq ($(findstring $(JENNIC_MAC),MiniMac MiniMacShim),)
LINKER_FILE = AppBuildNone
else
LINKER_FILE = AppBuildMac
endif
endif
endif
LINKCMD ?= $(LINKER_FILE).ld

# MAC security enable (Mini MAC with JenNet-IP)
ifneq ($(findstring $(JENNIC_MAC),MiniMac MiniMacShim),)
 ifeq ($(JENNIC_STACK), JIP)
  LDFLAGS += -Wl,-ueSecurityTxPrepare -Wl,-ueSecurityTxEncrypt -Wl,-ubSecurityRxProcess
 endif
endif

# Hardware debug support (NOTE: JN516x doesn't need separate library as JTag initialised in bootloader)
ifeq ($(HARDWARE_DEBUG_ENABLED), 1)
LDFLAGS += -Wl,--defsym,g_bSWConf_Debug=1
ifeq ($(DEBUG_PORT), UART1)
LDFLAGS += -Wl,-defsym,g_bSWConf_AltDebugPort=1
else
ifneq ($(DEBUG_PORT), UART0)
$(error if DEBUG=HW: Must define DEBUG_PORT=UART0 or DEBUG_PORT=UART1)
endif
endif
$(info  Building HW debug version ...)

endif

#########################################################################
# exports

export JENNIC_CHIP_FAMILY JENNIC_CHIP LDLIBS CFLAGS LDFLAGS LINKCMD
