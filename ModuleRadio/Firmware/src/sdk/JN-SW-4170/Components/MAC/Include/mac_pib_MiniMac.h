/****************************************************************************
 *
 * MODULE:             MAC
 *
 * DESCRIPTION:
 * MAC - The 802.15.4 Media Access Controller
 * Private header file to be included by module files only
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

/**
 * @defgroup g_mac_pib MAC PIB
 *
 * Parameters associated with setting or getting PIB values.
 * PIB direct access allows getting and setting of PIB attributes directly by obtaining
 * the PIB handle and dereferencing it appropriately.
 * All PIB attributes can be read (got) in this manner
 * Most PIB attributes can be written (set) in this manner, however some PIB attributes
 * require an auxiliary function call to be called instead. This is because they also require
 * hardware register values to change as well.
 * The functions listed in this group indicate which PIB attributes need to be set in this manner
 * @ingroup g_mac
 */

#ifndef _mac_pib_minimac_h_
#define _mac_pib_minimac_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/

#include "jendefs.h"
#include "MiniMac.h"
#include "mac_sap.h"

/* Map old structures and functions onto new ones: code will have to be
   rebuilt to use new structures, hopefully without mishaps */
typedef tsMiniMacPib MAC_Pib_s;

#define MAC_vPibSetShortAddr(A,B)       vMiniMac_MLME_SetReq_ShortAddr(B)
#define MAC_vPibSetPanId(A,B)           vMiniMac_MLME_SetReq_PanId(B)
#define MAC_vPibSetMinBe(A,B)           vMiniMac_MLME_SetReq_MinBe(B)
#define MAC_vPibSetMaxCsmaBackoffs(A,B) vMiniMac_MLME_SetReq_MaxCsmaBackoffs(B)
#define MAC_vPibSetRxOnWhenIdle(A,B,C)  vMiniMac_MLME_SetReq_RxOnWhenIdle(B)
#define MAC_psPibGetHandle(A)           &sMiniMacPib

#ifdef __cplusplus
};
#endif

#endif /* _mac_pib_minimac_h_ */

/* End of file $RCSfile: mac_pib.h,v $ *******************************************/
