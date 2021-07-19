/*###############################################################################
#
# MODULE:      BDB
#
# COMPONENT:   bdb_fb_common.c
#
# AUTHOR:
#
# DESCRIPTION: BDB Find & Bind Common functionality
#
#
# $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/BDB/Trunk/Source/FindAndBind/bdb_fb_common.c $
#
# $Revision: 74650 $
#
# $LastChangedBy: nxp46755 $
#
# $LastChangedDate: 2015-11-26 08:57:07 +0000 (Thu, 26 Nov 2015) $
#
# $Id: bdb_fb_common.c 74650 2015-11-26 08:57:07Z nxp46755 $
#
###############################################################################
#
# This software is owned by NXP B.V. and/or its supplier and is protected
# under applicable copyright laws. All rights are reserved. We grant You,
# and any third parties, a license to use this software solely and
# exclusively on NXP products [NXP Microcontrollers such as JN514x, JN516x, JN517x].
# You, and any third parties must reproduce the copyright and warranty notice
# and any other legend of ownership on each  copy or partial copy of the software.
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
# Copyright NXP B.V. 2015-2016. All rights reserved
#
###############################################################################*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <string.h>
#include "bdb_fb_api.h"
#include "bdb_api.h"
#include "zcl.h"
#include "Identify.h"
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
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************
 **
 ** NAME:       BDB_vFbZclHandler
 **
 ** DESCRIPTION:
 ** This function is used to to handle ZCL events
 **
 ** PARAMETERS:                 Name               Usage
 ** tsBDB_ZCLEvent              psCallBackEvent    BDB ZCL call back structure
 **
 **
 ** RETURN:
 ** None
 **
 ****************************************************************************/
PUBLIC void BDB_vFbZclHandler(uint8 u8EventType,tsZCL_CallBackEvent *psCallBackEvent)
{
    if(u8EventType == BDB_E_ZCL_EVENT_IDENTIFY_QUERY)
    {
        #if (defined BDB_SUPPORT_FIND_AND_BIND_INITIATOR)
            BDB_vFbHandleQueryResponse(psCallBackEvent);// identify query response
        #endif
    }
    else if(u8EventType == BDB_E_ZCL_EVENT_IDENTIFY)
    {
        #if (defined BDB_SUPPORT_FIND_AND_BIND_TARGET)
            BDB_vFbHandleStopIdentification(psCallBackEvent);// identify time
        #endif
    }
}
