/*****************************************************************************
 *
 * MODULE:      Utils
 *
 * COMPONENT:   appZdpExtendedDebug.h
 *
 * AUTHOR:      nxp29741
 *
 * DESCRIPTION:
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: $
 *
 * $Id:  $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
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
 * Copyright NXP B.V. 2016. All rights reserved
 *
 ****************************************************************************/

#ifndef APPZDPEXTENDEDDEBUG_H_
#define APPZDPEXTENDEDDEBUG_H_

#include <jendefs.h>
#include <string.h>
#include "zps_apl_af.h"
#include "zps_apl_aib.h"
#include "zps_nwk_sap.h"
#include "zps_nwk_nib.h"
#include "zps_nwk_pub.h"
#include "dbg.h"


PUBLIC void vDisplayTableSizes(void);
PUBLIC void vDisplayAddressMapTable(void);
PUBLIC void vDisplayNT(void);
PUBLIC void vDisplayAPSTable(void);
PUBLIC void vDisplayDiscNT(void);
PUBLIC void vDisplayRoutingTable(void);
PUBLIC void vDisplayRouteRecordTable(void);
PUBLIC void vDisplayNWKKey(void);
PUBLIC void vDisplayNWKTransmitTable(void);
PUBLIC void vDisplayBindingTable(void);


#endif
