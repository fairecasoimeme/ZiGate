/*****************************************************************************
 *
 * MODULE:      Zigbee Protocol Stack Application Layer
 *
 * COMPONENT:   zps_apl.h
 *
 * AUTHOR:      mwild
 *
 * DESCRIPTION: Application Layer global definitions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Zigbee%20Protocol%20Stack/Modules/APL/Trunk/Include/zps_apl.h $
 *
 * $Revision: 84024 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2016-10-12 14:18:30 +0100 (Wed, 12 Oct 2016) $
 *
 * $Id: zps_apl.h 84024 2016-10-12 13:18:30Z nxp29741 $
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

#ifndef ZPS_APL_H_
#define ZPS_APL_H_

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/*
 * general status type
 * The value returned can be from any layer of the ZigBee stack
 * Consult the relevant header file depending on the value
 * 0x80 - 0x8F : Zigbee device profile (zps_apl_zdp.h)
 * 0xA0 - 0xBF : Application support sub-layer (zps_apl_aps.h)
 * 0xC0 - 0xCF : Network layer (zps_nwk_sap.h)
 * 0xE0 - 0xFF : MAC layer (mac_sap.h)
 */
typedef uint8 ZPS_teStatus;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

PUBLIC extern const uint32 ZPS_g_u32AplVersion;

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#endif /* ZPS_APL_H_ */
