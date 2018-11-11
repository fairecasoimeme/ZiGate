/*****************************************************************************
 *
 * MODULE: ZigbeeNodeControlBridge
 *
 * COMPONENT: app_zcl_event_handler.h
 *
 * $AUTHOR: Faisal Bhaiyat$
 *
 * DESCRIPTION:
 *
 * $HeadURL: $
 *
 * $Revision:  $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate:  $
 *
 * $Id:  $
 *
 ****************************************************************************
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
/****************************************************************************/
/* Description.                                                             */
/* If you do not need this file to be parsed by doxygen then delete @file   */
/****************************************************************************/

/** @file
 * Add brief description here.
 * Add more detailed description here
 */

/****************************************************************************/
/* Description End                                                          */
/****************************************************************************/

#ifndef APP_ZCL_ZB_CONTROLBRIDGE_H_
#define APP_ZCL_ZB_CONTROLBRIDGE_H_

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "zcl.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void APP_ZCL_vInitialise ( void );
PUBLIC void APP_ZCL_vSendHAToggle ( tsZCL_Address*    psAddress,
                                    uint8             u8SwitchEndPoint,
                                    uint8             u8LightEndPoint );

PUBLIC void APP_ZCL_vSendHAOff ( tsZCL_Address*    psAddress,
                                 uint8             u8SwitchEndPoint,
                                 uint8             u8LightEndPoint );
PUBLIC void APP_ZCL_vSendHAOn ( tsZCL_Address*    psAddress,
                                uint8             u8SwitchEndPoint,
                                uint8 u8LightEndPoint );

PUBLIC void APP_ZCL_vSendHAMoveUp ( tsZCL_Address*    psAddress,
                                    uint8             u8SwitchEndPoint,
                                    uint8             u8LightEndPoint,
                                    uint8             u8Rate );

PUBLIC void APP_ZCL_vSendHAMoveDown ( tsZCL_Address*    psAddress,
                                      uint8             u8SwitchEndPoint,
                                      uint8             u8LightEndPoint,
                                      uint8             u8Rate );
PUBLIC void APP_ZCL_vSendHAMoveStop ( tsZCL_Address*    psAddress,
                                      uint8             u8SwitchEndPoint,
                                      uint8             u8LightEndPoint );

PUBLIC bool_t APP_ZCL_bSendHAIdentifyQuery ( tsZCL_Address*    psAddress,
                                             uint8             u8SwitchEndPoint,
                                             uint8 u8LightEndPoint );
teZCL_Status eApp_ZLL_RegisterEndpoint ( tfpZCL_ZCLCallBackFunction    fptr );
void vAPP_ZCL_DeviceSpecific_Init ( void );

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#endif /* APP_ZCL_ZB_CONTROLBRIDGE_H_ */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
