###############################################################################
#
# MODULE:   config.mk
#
# DESCRIPTION: Selects a configuration makefile based on JENNIC_CHIP and
#              JENNIC_CHIP_FAMILY.
# 
###############################################################################
#
# This software is owned by NXP B.V. and/or its supplier and is protected
# under applicable copyright laws. All rights are reserved. We grant You,
# and any third parties, a license to use this software solely and
# exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139]. 
# You, and any third parties must reproduce the copyright and warranty notice
# and any other legend of ownership on each copy or partial copy of the 
# software.
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
# Copyright NXP B.V. 2012. All rights reserved
#
###############################################################################

#
# Set up defaults for stack configuration
# JENNIC_STACK specifies the full stack (MAC only, JenNet-IP, etc.) and
#   determines which set of libraries and include paths are added to the build
# JENNIC_MAC allows selection of the MAC layer:
#   MAC         for full MAC
#   MiniMac     for size-optimised variant
#   MiniMacShim for size-optimised with shim to the old API
#
# Values are normally specified by the application make file; the defaults here
# are for legacy builds that pre-date the selection process
#
###############################################################################

JENNIC_STACK ?= MAC
JENNIC_MAC   ?= MAC

###############################################################################
# Include the chip or chip family definitions.
# Chip takes precendence over chip family
###############################################################################

ifdef JENNIC_CHIP
include $(SDK_BASE_DIR)/Chip/$(JENNIC_CHIP)/Build/config_$(JENNIC_CHIP).mk
else
ifdef JENNIC_CHIP_FAMILY
include $(SDK_BASE_DIR)/Chip/$(JENNIC_CHIP_FAMILY)/Build/config_$(JENNIC_CHIP_FAMILY).mk
else
$(error JENNIC_CHIP or JENNIC_CHIP_FAMILY must be specified)
endif
endif

###############################################################################
# Define the selected Jennic chip
###############################################################################

CFLAGS += -DJENNIC_CHIP=$(JENNIC_CHIP)
CFLAGS += -DJENNIC_CHIP_$(JENNIC_CHIP)
CFLAGS += -DJENNIC_CHIP_FAMILY=$(JENNIC_CHIP_FAMILY)
CFLAGS += -DJENNIC_CHIP_FAMILY_$(JENNIC_CHIP_FAMILY)

CFLAGS += -DJENNIC_STACK_$(JENNIC_STACK)
CFLAGS += -DJENNIC_MAC_$(JENNIC_MAC)

###############################################################################
# Chip independent compiler options
###############################################################################

CFLAGS += -Wall
CFLAGS += -Wunreachable-code

# Everything needs this
CFLAGS += -DEMBEDDED

###############################################################################
# Compiler Paths
###############################################################################

TOOL_BASE_DIR ?= $(SDK_BASE_DIR)/Tools

ifeq ($(JENNIC_CHIP_FAMILY),JN517x)
$(info Using LPC XPresso toolchain)
TOOL_COMMON_BASE_DIR ?= $(SDK_BASE_DIR)/../../tools
else
TOOL_COMMON_BASE_DIR ?= $(SDK_BASE_DIR)/../Tools
endif

SUBWCREV ?= $(TOOL_BASE_DIR)/TortoiseSVN/bin/subwcrev

###############################################################################
# Toolchain
###############################################################################

CC	= gcc
AS	= as
LD	= ld
ifeq ($(JENNIC_CHIP_FAMILY),JN517x)
$(info Using gcc-ar)
AR	= gcc-ar
else
AR	= ar
endif
NM	= nm
STRIP	= strip
SIZE	= size
OBJCOPY = objcopy
OBJDUMP = objdump
RANLIB	= ranlib

ifdef CROSS_COMPILE
CC:=$(realpath $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH)/bin/$(CROSS_COMPILE)-$(CC))
AS:=$(realpath $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH)/bin/$(CROSS_COMPILE)-$(AS))
LD:=$(realpath $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH)/bin/$(CROSS_COMPILE)-$(LD))
AR:=$(realpath $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH)/bin/$(CROSS_COMPILE)-$(AR))
NM:=$(realpath $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH)/bin/$(CROSS_COMPILE)-$(NM))
STRIP:=$(realpath $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH)/bin/$(CROSS_COMPILE)-$(STRIP))
SIZE:=$(realpath $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH)/bin/$(CROSS_COMPILE)-$(SIZE))
OBJCOPY:=$(realpath $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH)/bin/$(CROSS_COMPILE)-$(OBJCOPY))
OBJDUMP:=$(realpath $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH)/bin/$(CROSS_COMPILE)-$(OBJDUMP))
endif

###############################################################################
