#############################################################################
#
# MODULE:     	Platform Configuration Makefile inc. DK3
#
# COMPONENT:  	Config.mk
#
# VERSION:   	R and D Release 6 JAN 2011
#
# DESCRIPTION:	Selects Development Kit definitions based on JENNIC_PCB
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

ifdef JENNIC_PCB
	ifeq ($(JENNIC_PCB),DEVKIT1)
		PLATFORM_BASE_DIR = $(SDK_BASE_DIR)/Platform/DK1
	else
		ifeq ($(JENNIC_PCB),DEVKIT2)
			PLATFORM_BASE_DIR = $(SDK_BASE_DIR)/Platform/DK2
		else
			ifeq ($(JENNIC_PCB),HPDEVKIT)
				PLATFORM_BASE_DIR = $(SDK_BASE_DIR)/Platform/HPDevKit
			else
				ifeq ($(JENNIC_PCB),NTS)
					PLATFORM_BASE_DIR = $(SDK_BASE_DIR)/Platform/NTS
				else
					ifeq ($(JENNIC_PCB),DEVKIT3)
						PLATFORM_BASE_DIR = $(SDK_BASE_DIR)/Platform/DK3
					else
						ifeq ($(JENNIC_PCB),DEVKIT4)
							PLATFORM_BASE_DIR = $(SDK_BASE_DIR)/Platform/DK4
						else
							ifeq ($(JENNIC_PCB),DEVKIT5)
								PLATFORM_BASE_DIR = $(SDK_BASE_DIR)/Platform/DK5
							else
								$(error JENNIC_PCB is not defined. Define for the Jennic development kit you are using.)
							endif
						endif
					endif
				endif
			endif
		endif
	endif

###############################################################################
# Compiler flags

CFLAGS += -I$(SDK_BASE_DIR)/Platform/Common/Include

# Define the selected Jennic platform

CFLAGS += -DJENNIC_PCB=$(JENNIC_PCB)
CFLAGS += -DJENNIC_PCB_$(JENNIC_PCB)

###############################################################################
# Include platform specific definitions

include $(PLATFORM_BASE_DIR)/Build/PlatformConfig.mk

endif

###############################################################################

