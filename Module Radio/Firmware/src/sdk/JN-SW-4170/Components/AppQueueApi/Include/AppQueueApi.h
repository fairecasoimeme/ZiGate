/*****************************************************************************
 *
 * MODULE:              Application API header
 *
 * DESCRIPTION:
 * Access functions and structures used by the application to interact with
 * the Jennic 802.15.4 stack.
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

#ifndef  APP_Q_API_H_INCLUDED
#define  APP_Q_API_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include <mac_sap.h>
#include <AppApi.h>

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef void (*PR_QIND_CALLBACK)(void);
typedef void (*PR_HWQINT_CALLBACK)(void);

typedef struct
{
    uint32 u32DeviceId;
    uint32 u32ItemBitmap;
} AppQApiHwInd_s;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC uint32 u32AppQApiInit(PR_QIND_CALLBACK prMlmeCallback,
                             PR_QIND_CALLBACK prMcpsCallback,
                             PR_HWQINT_CALLBACK prHwCallback);
PUBLIC MAC_MlmeDcfmInd_s *psAppQApiReadMlmeInd(void);
PUBLIC MAC_McpsDcfmInd_s *psAppQApiReadMcpsInd(void);
PUBLIC AppQApiHwInd_s *psAppQApiReadHwInd(void);
PUBLIC void vAppQApiReturnMlmeIndBuffer(MAC_MlmeDcfmInd_s *psBuffer);
PUBLIC void vAppQApiReturnMcpsIndBuffer(MAC_McpsDcfmInd_s *psBuffer);
PUBLIC void vAppQApiReturnHwIndBuffer(AppQApiHwInd_s *psBuffer);
PUBLIC void vAppQApiPostHwInt(uint32 u32Device, uint32 u32ItemBitmap);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* APP_Q_API_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

