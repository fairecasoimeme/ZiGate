#############################################################################
#
# MODULE:     	Makefile for DK3 Platform
#
# COMPONENT:  	BoardLib.mk
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


# Builds the Board API
# Assumes called from AllBoardlibs.mk

BOARDCOMMON_SRC = $(BOARDCOMMON_BASE)/Common/Source
BOARDCOMMON_OBJ = $(BOARDCOMMON_BASE)/Common/Build
BOARDCOMMON_PUB = $(BOARDCOMMON_BASE)/Common/Include
BOARDDK_PUB     = $(BOARDCOMMON_BASE)/DK4/Include

# build straight to library folder for development purposes
BOARDDK_BLD  = $(BOARDDK4_BASE)/Library
BOARDDK_SRC  = $(BOARDDK4_BASE)/Source
HWAPI_PUB    = $(SDK_BASE_DIR)/Components/HardwareApi/Include
GENERAL_PUB  = $(SDK_BASE_DIR)/Components/Common/Include

TARGET = $(BOARDDK_BLD)/BoardLib_$(JENNIC_CHIP_FAMILY).a

# path to compiler settings so we can build from here
include $(SDK_BASE_DIR)/Chip/Common/Build/config.mk

#########################################################################
# Library build
#########################################################################

# also include on board peripherals order maintained as original
ARFLAGS = rcs

LIBOBJS	= $(BOARDDK_SRC)/Button.o \
          $(BOARDDK_SRC)/LcdDriver.o \
          $(BOARDCOMMON_SRC)/LcdDraw.o \
		  $(BOARDCOMMON_SRC)/LcdExtras.o \
          $(BOARDCOMMON_SRC)/LcdFont.o \
          $(BOARDCOMMON_SRC)/NXPLogo.o \
          $(BOARDDK_SRC)/HtsDriver.o \
          $(BOARDDK_SRC)/TSL2550.o \
          $(BOARDDK_SRC)/SMBus.o \
          $(BOARDDK_SRC)/LedControl.o \
          $(BOARDDK_SRC)/PCA9634.o \
		  $(BOARDDK_SRC)/LightingBoard.o \
		  $(BOARDDK_SRC)/GenericBoard.o \

 #########################################################################

CFLAGS += -DPCB_$(JENNIC_PCB)
CFLAGS += -I$(BOARDCOMMON_PUB)
CFLAGS += -I$(BOARDDK_PUB)
CFLAGS += -I$(GENERAL_PUB)
CFLAGS += -I$(HWAPI_PUB)

CFLAGS += -Werror

#########################################################################

all: $(TARGET)

%.o: $(BOARDDK_SRC)/$(notdir %).c
	$(CC) -c -o $*.o $(CFLAGS) $<

%.o: $(BOARDDK_SRC)/$(notdir %).S
	$(CC) -c -o $*.o $(ASFLAGS) $<

$(TARGET): $(LIBOBJS)
	@echo $(MAKEFLAGS)
	$(AR) $(ARFLAGS) $@ $(LIBOBJS)
	cp $@ $(subst BoardLib,libBoardLib,$@)

#########################################################################

clean:
	rm -f $(LIBOBJS) $(TARGET)

#########################################################################
