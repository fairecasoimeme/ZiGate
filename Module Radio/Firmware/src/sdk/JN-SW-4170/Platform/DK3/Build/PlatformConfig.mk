#############################################################################
#
# MODULE:     	Platform specific Makefile for DK3 
#
# COMPONENT:  	PlatformConfig.mk
#
# VERSION:   	R and D Release 6 JAN 2011
#
# REVISION:    	1.0
#
# DATED:       	2011/01/07
#
# AUTHOR:       sbarf
#
# DESCRIPTION:	DK3 Platform specific definitions		
#
###############################################################################
# 
# This software is owned by Jennic and/or its supplier and is protected
# under applicable copyright laws. All rights are reserved. We grant You,
# and any third parties, a license to use this software solely and
# exclusively on Jennic products. You, and any third parties must reproduce
# the copyright and warranty notice and any other legend of ownership on each
# copy or partial copy of the software.
# 
# THIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER
# EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
# ACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,
# BE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,
# INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.
# 
# Copyright Jennic Ltd 2011. All rights reserved
# 
###############################################################################

###############################################################################
# Compiler

CFLAGS += -I$(PLATFORM_BASE_DIR)/Include

###############################################################################
# Linker

LDFLAGS += -L$(PLATFORM_BASE_DIR)/Library
LDLIBS += BoardLib_$(JENNIC_CHIP_FAMILY)

###############################################################################
