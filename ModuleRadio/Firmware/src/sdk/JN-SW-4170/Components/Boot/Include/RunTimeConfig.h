/*****************************************************************************
 *
 * MODULE:              Heap manager
 *
*/
/****************************************************************************
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

* Copyright NXP B.V. 2012. All rights reserved
*
***************************************************************************/

#ifndef  RUNTIMECONFIG_INCLUDED
#define  RUNTIMECONFIG_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include "jendefs.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef PACK
#define PACK      __attribute__ ((packed))        /* align to byte boundary  */
#endif

#define NUM_COMPONENTS 10

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef void (*tprFunction)(void);

typedef struct
{
    uint8        u8Version;
    uint8        u8Configuration;
    uint32       u32InitFunctionAddr;
    tprFunction *pprApiFunctions;
    tprFunction  aprCallbackFunctions[0];
} tsRTC_CltRamRecord;

typedef struct
{
    uint8              u8Version;
    tprFunction        prInitFunction;
    tprFunction const *pprApiFunctions;
    tprFunction const *pprPatchFunctions;
} tsRTC_CltRomRecord;

typedef enum PACK
{
    COMP_ID_MAC = 0,
    COMP_ID_PERIPH_API,
    COMP_ID_6LOWPAN,
    COMP_ID_JENNET,
    COMP_ID_OS,
    COMP_ID_RF4CE,
    COMP_ID_SNAP
} teCompIds;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC tprFunction prRTC_GetComponentInitFunc(uint8 u8CompID);
PUBLIC tprFunction prRTC_GetApiFunc(uint8 u8CompId, uint8 u8FuncId);
PUBLIC tprFunction prRTC_GetCallbackFunc(uint8 u8CompId, uint8 u8FuncId);
PUBLIC tsRTC_CltRamRecord *psRTC_GetRamClt(uint8 u8CompId);
PUBLIC void vRTC_SetRamClt(uint8 u8CompId, tsRTC_CltRamRecord *psCltRecord);
PUBLIC tsRTC_CltRomRecord *psRTC_GetRomClt(uint8 u8CompId);
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* RUNTIMECONFIG_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

