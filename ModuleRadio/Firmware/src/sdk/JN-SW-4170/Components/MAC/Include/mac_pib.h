/*****************************************************************************
 *
 * MODULE:             Application API header
 *
 * DESCRIPTION:        Select correct interface depending on chip / chip family
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ***************************************************************************/

#include <jendefs.h>

#if ((defined JENNIC_CHIP_JN5148) || (defined JENNIC_CHIP_JN5139) || (defined JENNIC_CHIP_JN5139T01) || (defined JENNIC_CHIP_JN5139_HDK) || (defined JENNIC_CHIP_JN5139_HDK_4M) || (defined JENNIC_CHIP_JN5147)) && !(defined RAM_BUILD)
 #include "mac_pib_SingleMac.h"
#else
 #if defined JENNIC_MAC_MiniMac
  #include "mac_pib_MiniMac.h"
 #elif defined JENNIC_MAC_MiniMacShim
  #include "mac_pib_MiniMacShim.h"
 #else
  #include "mac_pib_CombinedMac.h"
 #endif
#endif
