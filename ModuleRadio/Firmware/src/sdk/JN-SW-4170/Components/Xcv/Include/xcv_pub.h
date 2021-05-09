/****************************************************************************
 *
 * MODULE:             ZED-XCV
 *
 * DESCRIPTION:
 * ZED Transceiver interface for single threaded direct memory access
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
 * @defgroup grp_XCV_STMM Transceiver infrastructure
 * @brief Transceiver infrastructure module.
 *
 * The Transceiver infrastructure module abstracts the interface to the Transceiver. This version
 * of the module is defined as a memory-mapped peripheral.
 *
 * The access routines are not explicitly shown here as they are used solely by the MAC layer and should
 * not need to be used by higher layers.
 */

#ifndef _xcv_pub_h_
#define _xcv_pub_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/

#include "jendefs.h"
#include "xcv_reg.h"

/************************/
/**** MACROS/DEFINES ****/
/************************/
/**
 * @name Elemental Read/Write
 * @ingroup grp_XCV_STMM
 * @{
 */
#define XCV_READ_L(a)           (*((volatile uint32 *)(a)))
#define XCV_WRITE_L(b, a)       (*((volatile uint32 *)(a)) = (b))
#define XCV_RMW_L(b, m, a)      (XCV_WRITE_L((((m) & (b)) | (~(m) & XCV_READ_L(a))), (a)))

/*@}*/

/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/
typedef void (*XCV_BbcIntCB_t)(void *pvClt, XCV_BbcEvt_e);
typedef void (*XCV_PhyIntCB_t)(void *pvClt, XCV_PhyEvt_e);

/****************/
/**** Device ****/
/****************/

/**
 * @ingroup grp_XCV_STMM
 * Transceiver initialisation parameters
 *
 * Parameters passed to the constructor concerned with Transceiver initialisation.
 */
typedef struct tagXCV_InitParam_s
{
} XCV_InitParam_s;

/**
 * @ingroup grp_XCV_STMM
 * Transceiver object
 *
 * The class of Transceiver object
 */
typedef struct tagXCV_s
{
    uint16          u16IER;     /**< IER shadow */
} XCV_s;

/****************************/
/**** EXPORTED VARIABLES ****/
/****************************/

/****************************/
/**** EXPORTED FUNCTIONS ****/
/****************************/

/**** Transceiver Instantiation ****/

/* Construct */
PUBLIC void
XCV_vCtor(XCV_s *psXcv,
          XCV_InitParam_s *psInitParam);

/**** XCV Device Access ****/

/* r16 is set to 0x02008000, all register offsets are from a base of
   XCV_BASE_ADDR, so offset to use from r16 is as follows: */
#define R16_OFFSET (0x02008000 - XCV_BASE_ADDR)

#define XCV_u32DevReadReg(psXcv, eOffset)       \
     ({ uint32 __result;   \
        asm volatile ("bg.lwz %[result], %[offset](r16);": [result] "=r" (__result): [offset] "i" ((((eOffset) << 2) - R16_OFFSET)));  \
        __result; })

#define XCV_u32DevReadRegNC(psXcv, eOffset)       \
     ({ uint32 __result, __u32Addr = (((eOffset) << 2) - R16_OFFSET);   \
        asm volatile("bt.add %0, r16;" : "+r" (__u32Addr) : ); \
        asm volatile ("bn.lwz %[result], 0(%[addr]);": [result] "=r" (__result): [addr] "r" (__u32Addr));  \
        __result; })

#define XCV_vDevWriteReg32(psXcv, eOffset, u32Data) \
    asm volatile("bg.sw %[offset](r16), %[value];" : : [offset] "i" (((eOffset) << 2) - R16_OFFSET), [value] "r" (u32Data) )

#define XCV_vDevWriteReg32NC(psXcv, eOffset, u32Data) \
    { uint32 __u32Addr = (((eOffset) << 2) - R16_OFFSET); \
      asm volatile("bt.add %0, r16;" : "+r" (__u32Addr) : ); \
      asm volatile("bn.sw 0(%[addr]), %[value];" : : [addr] "r" (__u32Addr), [value] "r" (u32Data) ); }

#define XCV_vDevRMWReg32(psXcv, eOffset, u32Mask, u32Data) XCV_vDevWriteReg32(psXcv, eOffset, (((u32Mask) & (u32Data)) | (~(u32Mask) & (XCV_u32DevReadReg(psXcv, eOffset)))))
#define XCV_vDevRMWReg32NC(psXcv, eOffset, u32Mask, u32Data) XCV_vDevWriteReg32NC(psXcv, eOffset, (((u32Mask) & (u32Data)) | (~(u32Mask) & (XCV_u32DevReadRegNC(psXcv, eOffset)))))

/* 16 and 8 bit accesses use 32 bit access functions */
#define XCV_u16DevReadReg(psXcv, eOffset)               ((uint16)XCV_u32DevReadReg(psXcv,eOffset))
#define XCV_u8DevReadReg(psXcv, eOffset)                ((uint8)XCV_u32DevReadReg(psXcv,eOffset))
#define XCV_vDevWriteReg16(psXcv, eOffset, u16Data)     XCV_vDevWriteReg32(psXcv,eOffset,(uint32)(u16Data))
#define XCV_vDevWriteReg8(psXcv, eOffset, u8Data)       XCV_vDevWriteReg32(psXcv,eOffset,(uint32)(u8Data))
#define XCV_vDevRMWReg16(psXcv,eOffset,u16Mask,u16Data) XCV_vDevRMWReg32(psXcv,eOffset,(uint32)u16Mask,(uint32)u16Data)
#define XCV_vDevRMWReg8(psXcv,eOffset,u8Mask,u8Data)    XCV_vDevRMWReg32(psXcv,eOffset,(uint32)u8Mask,(uint32)u8Data)

#define XCV_u16DevReadRegNC(psXcv, eOffset)               ((uint16)XCV_u32DevReadRegNC(psXcv,eOffset))
#define XCV_u8DevReadRegNC(psXcv, eOffset)                ((uint8)XCV_u32DevReadRegNC(psXcv,eOffset))
#define XCV_vDevWriteReg16NC(psXcv, eOffset, u16Data)     XCV_vDevWriteReg32NC(psXcv,eOffset,(uint32)(u16Data))
#define XCV_vDevWriteReg8NC(psXcv, eOffset, u8Data)       XCV_vDevWriteReg32NC(psXcv,eOffset,(uint32)(u8Data))
#define XCV_vDevRMWReg16NC(psXcv,eOffset,u16Mask,u16Data) XCV_vDevRMWReg32NC(psXcv,eOffset,(uint32)u16Mask,(uint32)u16Data)
#define XCV_vDevRMWReg8NC(psXcv,eOffset,u8Mask,u8Data)    XCV_vDevRMWReg32NC(psXcv,eOffset,(uint32)u8Mask,(uint32)u8Data)

/* IER write value */
PUBLIC void
XCV_vDevWriteIER(XCV_s *psXcv,
                 uint16 u16Data);

/* IER modify-write value */
PUBLIC void
XCV_vDevRMW_IER(XCV_s *psXcv,
                uint16 u16Mask,
                uint16 u16Data);

#ifdef __cplusplus
};
#endif

#endif /* _xcv_pub_h_ */

/* End of file $RCSfile: xcv_pub.h,v $ *******************************************/
