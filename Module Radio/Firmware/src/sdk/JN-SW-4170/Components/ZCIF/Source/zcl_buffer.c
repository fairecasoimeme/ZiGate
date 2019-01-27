/*****************************************************************************
 *
 * MODULE:             Smart Energy
 *
 * COMPONENT:          zcl_buffer.c
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:        ZCL Buffer Stack Wrapper. 
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy:  $
 *
 * $LastChangedDate:  $
 *
 * $Id: $
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
 ****************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>
#include <string.h>

#include "zcl.h"
#include "zcl_common.h"
#include "zcl_internal.h"
#include "pdum_apl.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Imported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       hZCL_AllocateAPduInstance
 **
 ** DESCRIPTION:
 ** ZCL wrapper to get a stack buffer
 **
 ** PARAMETERS:                 Name                      Usage
 ** Nothing
 **
 ** RETURN:
 ** PDUM_thAPduInstance
 **
 ****************************************************************************/

PUBLIC PDUM_thAPduInstance hZCL_AllocateAPduInstance(void)
{
    tsZCL_CallBackEvent sZCL_CallBackEvent;

    PDUM_thAPduInstance pdum_tsAPduInstance;
    
    pdum_tsAPduInstance = PDUM_hAPduAllocateAPduInstance(psZCL_Common->hZCL_APdu);

    if(pdum_tsAPduInstance==PDUM_INVALID_HANDLE)
    {
        // fill in non-attribute specific values in callback event structure
        memset(&sZCL_CallBackEvent, 0, sizeof(tsZCL_CallBackEvent));
        sZCL_CallBackEvent.eEventType = E_ZCL_CBET_ERROR;
        sZCL_CallBackEvent.eZCL_Status = E_ZCL_ERR_ZBUFFER_FAIL;
        // general c/b
        psZCL_Common->pfZCLinternalCallBackFunction(&sZCL_CallBackEvent);
    }

    return pdum_tsAPduInstance;
}

/****************************************************************************
 **
 ** NAME:       hZCL_GetBufferPoolHandle
 **
 ** DESCRIPTION:
 ** Returns number of ZCL buffer pool handle
 **
 ** PARAMETERS:               Name                    Usage
 ** none
 **
 ** RETURN:
 ** PDUM_thAPdu
 **
 ****************************************************************************/

PUBLIC PDUM_thAPdu hZCL_GetBufferPoolHandle(void)
{
    PDUM_thAPdu hZCL_APdu;

	#ifndef COOPERATIVE
    // get ZCL mutex
        vZCL_GetInternalMutex();
    #endif

    hZCL_APdu = psZCL_Common->hZCL_APdu;
    #ifndef COOPERATIVE
        vZCL_ReleaseInternalMutex();
    #endif
    return(hZCL_APdu);

}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
