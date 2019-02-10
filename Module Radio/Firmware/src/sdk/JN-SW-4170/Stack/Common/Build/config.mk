###############################################################################
#
# MODULE:   Config.mk
#
# DESCRIPTION: Selects a configuration makefile based on JENNIC_STACK
# 
############################################################################
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
############################################################################

###############################################################################
# Base location

COMPONENTS_BASE_DIR = $(SDK_BASE_DIR)/Components
STACK_BASE_DIR = $(SDK_BASE_DIR)/Stack

###############################################################################
# Include path for standard type definitions

CFLAGS += -I$(COMPONENTS_BASE_DIR)/Common/Include

###############################################################################
# Linker library paths

LDFLAGS += -L$(COMPONENTS_BASE_DIR)/Library

###############################################################################
# Common ROM based software components

ifneq ($(findstring $(JENNIC_MAC),MiniMacShim MAC),)
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/AppApi/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/MAC/Include
endif
ifneq ($(findstring $(JENNIC_MAC),MiniMac MiniMacShim),)
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/MiniMac/Include
endif
ifneq ($(findstring $(JENNIC_MAC),MiniMac MiniMacShim MMAC),)
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/MMAC/Include
endif
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/HardwareAPI/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/Aes/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/DBG/Include

# Software debug support
ifeq ($(DEBUG), SW)
$(info Building SW debug version ...)

LDLIBS  := SWDebug_$(JENNIC_CHIP) $(LDLIBS)

# Set SWDEBUG_PORT to UART0 or UART1 dependent on connection to serial port on board
ifeq ($(DEBUG_PORT), UART0)
CFLAGS  += -DSWDEBUG_PORT=0
$(info Software Debug will use UART0)
else 
ifeq ($(DEBUG_PORT), UART1)
CFLAGS  += -DSWDEBUG_PORT=1
$(info Software Debug will use UART1)
endif
endif

INCFLAGS += -I$(COMPONENTS_BASE_DIR)/GDB/Include
endif



###############################################################################
# Include stack specific definitions

ifndef JENNIC_STACK
$(info JENNIC_STACK is undefined, defaulting to MAC)
JENNIC_STACK ?= MAC
endif

include $(STACK_BASE_DIR)/$(JENNIC_STACK)/Build/config_$(JENNIC_STACK).mk

###############################################################################
# Setup path for default stack size definition for the selected stack

ifdef STACK_SIZE
LDFLAGS += -Wl,--defsym=__stack_size=$(STACK_SIZE)
endif

ifdef MINIMUM_HEAP_SIZE
LDFLAGS += -Wl,--defsym,__minimum_heap_size=$(MINIMUM_HEAP_SIZE)
endif

ifneq ($(wildcard App_Stack_Size.ld), )
$(error Found custom App_Stack_Size.ld file. Stack and heap sizes must now be set through the STACK_SIZE and MINIMUM_HEAP_SIZE makefile variables)
endif

###############################################################################
