/****************************************************************************
 *
 * MODULE:             DBQ
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

#ifndef _utils_pub_h_
#define _utils_pub_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/

#ifdef ECOS
#include <stdio.h>
#endif
#include "jendefs.h"

/**
 * @addtogroup grp_DBQ Device Bus Mailbox
 * Methods and attributes associated with Device Bus Mailbox
 * @{
 */

/************************/
/**** MACROS/DEFINES ****/
/************************/

#define UTILS_WORD_ALIGN(x)           (((x) + 3) & ~3)

#define UTILS_BYTE_TO_WORD_OFFSET(x)  ((x) >> 2)
#define UTILS_WORD_TO_BYTE_OFFSET(x)  ((x) << 2)

/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/

/****************************/
/**** EXPORTED VARIABLES ****/
/****************************/

/****************************/
/**** EXPORTED FUNCTIONS ****/
/****************************/

PUBLIC void
UTILS_vWordToByteCopy(uint8* pu8Dst,
                      const uint32 *pu32Src,
                      uint32 u32ByteLen);

PUBLIC void
UTILS_vByteToWordCopy(uint32 *pu32Dst,
                      const uint8 *pu8Src,
                      uint32 u32ByteLen);

#ifdef ECOS
int memcmp(const void * cs,const void * ct,size_t count);
#endif

#ifdef __cplusplus
};
#endif

#endif /* _utils_pub_h_ */

/* End of file $RCSfile: utils_pub.h,v $ *******************************************/

/****************************************************************************
 *
 * CHANGE HISTORY:
 *
 * $Log: utils_pub.h,v $
 * Revision 1.2  2003/11/18 15:47:26  rcc
 * Added memcmp for eCos
 *
 * Revision 1.1.1.1  2003/09/12 12:18:55  rcc
 * Initial checkin
 *
 *
 ****************************************************************************/
