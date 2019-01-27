###############################################################################
#
# MODULE:   config_ba2.mk
#
# DESCRIPTION: Compiler definitions for the BA2 architecture
# This file should only contain architecture specific options.
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

# Set toolchain path to use ba2 version of compiler
TOOLCHAIN_PATH = ba-elf-ba2-r36379
CROSS_COMPILE  = ba-elf

# BA2 architecture compiler flags
CFLAGS += -march=ba2 -mcpu=jn51xx
CFLAGS += -mredzone-size=4 -mbranch-cost=3

LDFLAGS += -march=ba2 -mcpu=jn51xx
LDFLAGS += -mredzone-size=4 -mbranch-cost=3

# omit frame pointer by default
CFLAGS += -fomit-frame-pointer
LDFLAGS += -fomit-frame-pointer

# default to optimise for size
CFLAGS += -Os
LDFLAGS += -Os

# Default to smallest possible enums
CFLAGS += -fshort-enums
LDFLAGS += -fshort-enums

# Turn on all common warnings
CFLAGS += -Wall 

# Turn on some additional useful warnings
CFLAGS += -Wpacked -Wcast-align

# Output each function and static data in their own sections
CFLAGS += -fdata-sections -ffunction-sections

# Debug Support

ifeq ($(DEBUG), HW)
DISABLE_LTO ?= 1
CFLAGS  += -g -DGDB
LDFLAGS  += -g
# Optimise at level 0 instead of size
CFLAGS  := $(subst -Os,-O0,$(CFLAGS))
LDFLAGS  := $(subst -Os,-O0,$(LDFLAGS))
HARDWARE_DEBUG_ENABLED=1
endif

ifeq ($(DEBUG), HW_SIZEOPT)
DISABLE_LTO ?= 1
CFLAGS  += -g -DGDB
LDFLAGS  += -g
HARDWARE_DEBUG_ENABLED=1
$(info No optimisation enabled with HW debug ...)
endif

ifeq ($(HARDWARE_DEBUG_ENABLED), 1)
# Set DEBUG_PORT to UART0 or UART1 dependant on connection to serial port on board
CFLAGS += -D$(DEBUG_PORT)_DEBUG
CFLAGS  += -DHWDEBUG
BIN_SUFFIX ?= _hwdbg
$(info Building HW debug version ...)
endif

ifeq ($(DEBUG), NONE)
DISABLE_LTO ?= 0
endif
# Link Time Optimisation configuration

# Default (unless debugging) is to compile & link using link time optimisation, 
# but allow it to be disabled by setting DISABLE_LTO=1
ifneq ($(DISABLE_LTO), 1)
CFLAGS += -flto 
LDFLAGS += -flto 
endif

###############################################################################
