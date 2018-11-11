###############################################################################
#
# MODULE:   Makefile
#
# DESCRIPTION: Makefile for the Control Bridge
# 
 ############################################################################
#
# This software is owned by NXP B.V. and/or its supplier and is protected
# under applicable copyright laws. All rights are reserved. We grant You,
# and any third parties, a license to use this software solely and
# exclusively on NXP products [NXP Microcontrollers such as  JN516x,
# JN517x]. 
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
# Copyright NXP B.V. 2015. All rights reserved
#
############################################################################

TARGET  =    ZigbeeNodeControlBridge

###############################################################################
# User definable make parameters that may be overwritten from the command line
# Chip variant
JENNIC_CHIP            ?= JN5169
JENNIC_CHIP_FAMILY     ?= JN516x
JENNIC_PCB             ?= DEVKIT2

ifeq ($(JENNIC_CHIP_FAMILY),JN516x)
JENNIC_CHIP            ?= JN5169
JENNIC_CHIP_FAMILY     ?= JN516x
JENNIC_SDK             ?= JN-SW-4170
ZNCLKCMD                = AppBuildZBPro.ld
JENNIC_PCB              = DEVKIT4
else
ifeq ($(JENNIC_CHIP_FAMILY),JN517x)
JENNIC_CHIP            ?= JN5179
JENNIC_CHIP_FAMILY     ?= JN517x
JENNIC_SDK             ?= JN-SW-4270
ZNCLKCMD                = AppBuildZBPro.ld
JENNIC_PCB              = DEVKIT5
endif
endif
ZBPRO_DEVICE_TYPE		= ZCR
JENNIC_MAC             ?= MiniMacShim
PDM_BUILD_TYPE         ?= _EEPROM
BAUD                   ?= 1000000

GP_SUPPORT             ?= 0
TRACE                  ?= 0

DEBUG                  ?= NONE
###############################################################################
# un-comment the lines below for Debugger
# Debug options - define DEBUG to enable
# DEBUG ?=HW
#
# Define which UART to use for HW debug
# DEBUG_PORT ?= UART1
# DEBUG_MODE ?= SWD

STACK_SIZE              = 6000
MINIMUM_HEAP_SIZE       = 2000

NODE                   ?= COORDINATOR

CRC_NEW                ?= CRC_XOR
#CRC_NEW                ?= CCITT_CRC 

ifneq ($(GP_SUPPORT), 1)
GENERATED_FILE_NAME    ?= $(TARGET)_$(JENNIC_CHIP)_$(NODE)_$(BAUD)
else
GENERATED_FILE_NAME    ?= $(TARGET)_$(JENNIC_CHIP)_GP_Proxy_$(NODE)_$(BAUD)
endif

###############################################################################
# Select the network stack (e.g. MAC, ZBPro)

JENNIC_STACK           ?= ZCL

###############################################################################
# commands options
# enable optional commands as required per applicaion.
#
NETWORK_RECOVERY       ?= 0
STACK_MEASURE          ?= 0
APP_AHI_CONTROL        ?= 1

###############################################################################

CFLAGS  += -DUART_BAUD_RATE=$(BAUD)
CFLAGS  += -D$(NODE)
CFLAGS	+= -D$(CRC_NEW)

ifeq ($(DEBUG), UART1)
CFLAGS  += -DDBG_ENABLE
CLFAGS  += -DDEBUG_BDB
$(info Building with debug UART1...)
CFLAGS  += -DUART_DEBUGGING
CFLAGS  += -DDEBUG_UART=DBG_E_UART_1
#CFLAGS  += -DDEBUG_APP_OTA
CFLAGS += -DDEBUG_CLD_IASZONE
CFLAGS  += -DEBUG_TL_NEGATIVE
CFLAGS  += -DDEBUG_COMMISSION
CFLAGS  += -DDEBUG_SCAN_REQ
CFLAGS  += -DDEBUG_SCAN
CFLAGS  += -DDEBUG_ZCL
CFLAGS	+= -DDEBUG_NWK_RECOVERY
#CFLAGS	+= -DDEBUG_PDM_EXTENDED
CFLAGS	+= -DDEBUG_ZB_CONTROLBRIDGE_TASK
CFLAGS  += -DTRACE_APP
#CFLAGS += -DDEBUG_SERIAL_LINK

CFLAGS += -DDEBUG_APP_GP
CFLAGS += -DTRACE_GP_DEBUG

endif


ifeq ($(NETWORK_RECOVERY), 1)
CFLAGS	+= -DNETWORK_RECOVERY
endif

ifeq ($(STACK_MEASURE), 1)
CFLAGS	+= -DSTACK_MEASURE
endif

ifeq ($(APP_AHI_CONTROL), 1)
CFLAGS	+= -DAPP_AHI_CONTROL
endif

ifneq ($(GP_SUPPORT), 1)
ifeq ($(NODE), COORDINATOR)
$(info Building Node Coordinator Only...)
APP_ZPSCFG = ZigbeeNodeControlBridgeCoordinator.zpscfg
else
$(info Building Node Full functionality ...)
APP_ZPSCFG = ZigbeeNodeControlBridge.zpscfg
endif
else
ifeq ($(NODE), COORDINATOR)
$(info Building Node Coordinator Only...)
APP_ZPSCFG = ZigbeeNodeControlBridgeCoordinator_GP_proxy.zpscfg
else
$(info Building Node Full functionality ...)
APP_ZPSCFG = ZigbeeNodeControlBridge_GP_proxy.zpscfg
endif
endif

ifeq ($(GP_SUPPORT), 1)
CFLAGS  +=-DGP_PROXY_BASIC_DEVICE
$(info  "NOTE: Make sure that app_GP.cfg Manually Changed to have device ID as 0x0061 and also remove GP cluster id from in cluster list of Endpoint 242 for Proxy build")
CFLAGS  += -DGP_CERITIFICATION_TEST
CFLAGS  += -DCLD_GREENPOWER
APP_CLUSTERS_GREENPOWER_SRC ?=1
endif

###############################################################################
# Path definitions

# Use if application directory contains multiple targets
SDK_BASE_DIR           = $(abspath ../../../../sdk/$(JENNIC_SDK))
APP_BASE               = $(abspath ../..)
APP_BLD_DIR            = $(APP_BASE)/Build/ZigbeeNodeControlBridge
APP_SRC_DIR            = $(APP_BASE)/Source/ZigbeeNodeControlBridge
ZBC_SRC_DIR            = $(COMPONENTS_BASE_DIR)/ZigbeeCommon/Source
APP_COMMON_SRC_DIR     = $(APP_BASE)/Source/Common
BDB_SRC_DIR            = $(COMPONENTS_BASE_DIR)/BDB/Source
HWAPI_SRC_DIR          = $(COMPONENTS_BASE_DIR)/HardwareAPI/Source

ifeq ($(JENNIC_CHIP_FAMILY),JN517x)

INTERRUPT_HANDLER_BBC = zps_isrMAC
LDFLAGS += -Wl,-u$(INTERRUPT_HANDLER_BBC) -Wl,-defsym,vAHI_IntHandlerBbc_select=$(INTERRUPT_HANDLER_BBC)

endif

###############################################################################
# Application Source files
# Note: Path to source file is found using vpath below, so only .c filename is required

ifeq ($(JENNIC_CHIP_FAMILY),JN516x)
APPSRC = irq_JN516x.S
APPSRC += portasm_JN516x.S
APPSRC += port_JN516x.c
endif
ifeq ($(JENNIC_CHIP_FAMILY),JN517x)
APPSRC = port_JN517x.c
endif
APPSRC += pdum_gen.c
APPSRC += zps_gen.c
APPSRC += app_Znc_cmds.c
APPSRC += app_general_events_handler.c
APPSRC += app_zcl_event_handler.c
APPSRC += app_start.c
APPSRC += SerialLink.c
APPSRC += uart.c
APPSRC += pdum_apdu.S
APPSRC += app_ota_server.c
ifeq ($(JENNIC_CHIP_FAMILY),JN517x)
APPSRC += AHI_ModuleConfiguration.c
endif

ifeq ($(NETWORK_RECOVERY), 1)
APPSRC += app_network_recovery.c
endif

ifeq ($(STACK_MEASURE), 1)
APPSRC += StackMeasure.c
endif

ifeq ($(APP_AHI_CONTROL), 1)
APPSRC += app_ahi_commands.c
endif

ifeq ($(GP_SUPPORT), 1)
APPSRC += app_green_power.c
endif

LIBNAME = $(TARGET)_PDM$(PDM_BUILD_TYPE)_BAUD_$(BAUD)_DEBUG_$(DEBUG)



###############################################################################
# Standard Application header search paths

INCFLAGS += -I$(APP_SRC_DIR)
INCFLAGS += -I$(APP_SRC_DIR)/..
INCFLAGS += -I$(APP_COMMON_SRC_DIR)

# Application specific include files
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/ZigbeeCommon/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/Random/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/Aes/Include
INCFLAGS += -I$(COMPONENTS_BASE_DIR)/HardwareAPI/Include

INCFLAGS += -I$(COMPONENTS_BASE_DIR)/BDB/Source/OutOfBand

###############################################################################
# Application libraries
# Specify additional Component libraries

#APPLIBS += 

###############################################################################

# You should not need to edit below this line

APP_CLUSTERS_MEASUREMENT_AND_SENSING_SRC    ?= 1
APP_CLUSTERS_HVAC_SRC                       ?= 1
APP_CLUSTERS_IAS_SRC                        ?= 1
APP_CLUSTERS_SMART_ENERGY_SRC               ?= 1
APP_CLUSTERS_ENERGY_AT_HOME_SRC             ?= 1
APP_CLUSTERS_OTA_SRC                        ?= 1
APP_CLUSTER_LIGHTING_SRC                    ?= 1
APP_CLUSTERS_APPLIANCE_MANAGEMENT_SRC       ?= 1
APP_CLUSTERS_CLOSURES_SRC                   ?= 1
APP_CLUSTERS_SECURITY_AND_SAFETY_SRC        ?= 1
BDB_SUPPORT_OOBC                            ?= 1
BDB_SUPPORT_NWK_STEERING                    ?= 1
BDB_SUPPORT_NWK_FORMATION                   ?= 1
ifneq ($(NODE), COORDINATOR)
APP_CLUSTER_COMMISSIONING_SRC               ?= 1
# BDB features  Enable as required
BDB_SUPPORT_TOUCHLINK_INITIATOR_ROUTER      ?= 1
endif

###############################################################################
###############################################################################
# Optional stack features to pull relevant libraries into the build.

OPTIONAL_STACK_FEATURES = $(shell $(ZPSCONFIG) -n $(TARGET) -f $(APP_SRC_DIR)/$(APP_ZPSCFG) -y )
###############################################################################
# Configure for the selected chip or chip family

include $(SDK_BASE_DIR)/Chip/Common/Build/config.mk
include $(SDK_BASE_DIR)/Platform/Common/Build/config.mk
include $(SDK_BASE_DIR)/Stack/Common/Build/config.mk
include $(SDK_BASE_DIR)/Components/BDB/Build/config.mk

###############################################################################

TEMP            = $(APPSRC:.c=.o)
APPOBJS         = $(TEMP:.S=.o)

###############################################################################
# Application dynamic dependencies

APPDEPS         = $(APPOBJS:.o=.d)


###############################################################################
# Linker

# Add application libraries before chip specific libraries to linker so
# symbols are resolved correctly (i.e. ordering is significant for GCC)

APPLDLIBS := $(foreach lib,$(APPLIBS),$(if $(wildcard $(addprefix $(COMPONENTS_BASE_DIR)/Library/lib,$(addsuffix _$(JENNIC_CHIP).a,$(lib)))),$(addsuffix _$(JENNIC_CHIP),$(lib)),$(addsuffix _$(JENNIC_CHIP_FAMILY),$(lib))))
LDLIBS := $(APPLDLIBS) $(LDLIBS)
LDLIBS += JPT_$(JENNIC_CHIP)
###############################################################################
# Dependency rules

.PHONY: all clean
# Path to directories containing application source 
vpath % $(APP_SRC_DIR):$(APP_COMMON_SRC_DIR):$(UTIL_SRC_DIR):$(ZCL_SRC):$(ZCL_SRC_DIRS):$(BDB_SRC_DIR):$(HWAPI_SRC_DIR)

all: $(GENERATED_FILE_NAME).bin

-include $(APPDEPS)
%.d:
#    rm -f $*.o
ifeq ($(JENNIC_CHIP_FAMILY),JN517x)
$(APP_SRC_DIR)/pdum_gen.c $(APP_SRC_DIR)/pdum_gen.h: $(APP_SRC_DIR)/$(APP_ZPSCFG) $(PDUMCONFIG)
	$(info Configuring the PDUM ...)
	$(PDUMCONFIG) -z $(TARGET) -e LITTLE_ENDIAN_PROCESSOR -f $< -o $(APP_SRC_DIR)

$(APP_SRC_DIR)/zps_gen.c $(APP_SRC_DIR)/zps_gen.h: $(APP_SRC_DIR)/$(APP_ZPSCFG) $(ZPSCONFIG)
	$(info Configuring the Zigbee Protocol Stack ...)
	$(ZPSCONFIG) -n $(TARGET) -e LITTLE_ENDIAN_PROCESSOR -t $(JENNIC_CHIP) -l $(ZPS_NWK_LIB) -a $(ZPS_APL_LIB) -c $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH) -f $< -o $(APP_SRC_DIR)


pdum_gen.o zps_gen.o: CFLAGS += -fno-lto
endif

ifeq ($(JENNIC_CHIP_FAMILY),JN516x)
$(APP_SRC_DIR)/pdum_gen.c $(APP_SRC_DIR)/pdum_gen.h: $(APP_SRC_DIR)/$(APP_ZPSCFG) $(PDUMCONFIG)
	$(info Configuring the PDUM ...)
	$(PDUMCONFIG) -z $(TARGET)  -f $< -o $(APP_SRC_DIR)

$(APP_SRC_DIR)/zps_gen.c $(APP_SRC_DIR)/zps_gen.h: $(APP_SRC_DIR)/$(APP_ZPSCFG) $(ZPSCONFIG)
	$(info Configuring the Zigbee Protocol Stack ...)
	$(ZPSCONFIG) -n $(TARGET)  -t $(JENNIC_CHIP) -l $(ZPS_NWK_LIB) -a $(ZPS_APL_LIB) -c $(TOOL_COMMON_BASE_DIR)/$(TOOLCHAIN_PATH) -f $< -o $(APP_SRC_DIR)

endif 

%.o: %.S
	$(info Assembling $< ...)
	$(CC) -c -o $(subst Source,Build,$@) $(CFLAGS) $(INCFLAGS) $< -MD -MF $*.d -MP
	@echo

%.o: %.c 
	$(info Compiling $< ...)
	$(CC) -c -o $(subst Source,Build,$@) $(CFLAGS) $(INCFLAGS) $< -MD -MF $*.d -MP
	@echo

$(GENERATED_FILE_NAME).elf: $(APPOBJS) $(addsuffix.a,$(addprefix $(COMPONENTS_BASE_DIR)/Library/lib,$(APPLDLIBS))) 
	$(info Linking $@ ...)
	$(CC) -Wl,--gc-sections -Wl,-u_AppColdStart -Wl,-u_AppWarmStart $(LDFLAGS) -T$(ZNCLKCMD) -o $@ -Wl,--start-group $(APPOBJS) $(addprefix -l,$(LDLIBS))  -lm -Wl,--end-group -Wl,-Map,$(GENERATED_FILE_NAME).map 
	 
	$(SIZE) $@ 
	date +%c >> $(APP_BASE)/Doc/size.txt
	$(SIZE) $@ >> $(APP_BASE)/Doc/size.txt
	
# Do a second linking with LTO disabled
	$(CC) -Wl,--cref -Wl,--gc-sections -Wl,-u_AppColdStart -Wl,-u_AppWarmStart $(LDFLAGS) -T$(ZNCLKCMD) -L $(SDK_BASE_DIR)/Stack/ZCL/Build/  -o $@ -Wl,--start-group $(APPOBJS) $(addprefix -l,$(LDLIBS)) -lm -Wl,--end-group -fno-lto -Wl,-Map,$(GENERATED_FILE_NAME)_NOLTO.map
# Run the Pyt


ifeq ($(JENNIC_CHIP_FAMILY),JN517x)
$(GENERATED_FILE_NAME).bin: $(GENERATED_FILE_NAME).elf 
	$(info Generating binary ...)
	$(OBJCOPY) -S -O binary $< $@
else
$(GENERATED_FILE_NAME).bin: $(GENERATED_FILE_NAME).elf 
	$(info Generating binary ...)
	$(OBJCOPY) -j .version -j .bir -j .flashheader -j .vsr_table -j .vsr_handlers -j .ro_mac_address -j .ro_ota_header -j .ro_se_customData -j .rodata -j .text -j .data -j .bss -j .heap -j .stack -S -O binary $< $@
    
endif    

	$(SDK_BASE_DIR)/Tools/Memsize/memsize.exe $(APP_BLD_DIR)/$(GENERATED_FILE_NAME).elf $(APP_BLD_DIR)/$(GENERATED_FILE_NAME)_NOLTO.map $(TARGET).json

################################################################################

clean:
	rm -f $(APPOBJS) $(APPDEPS) $(GENERATED_FILE_NAME).bin $(GENERATED_FILE_NAME).elf $(GENERATED_FILE_NAME).map *.o *.d
	rm -f $(APP_SRC_DIR)/pdum_gen.* $(APP_SRC_DIR)/zps_gen*.* $(APP_SRC_DIR)/pdum_apdu.*

###############################################################################

