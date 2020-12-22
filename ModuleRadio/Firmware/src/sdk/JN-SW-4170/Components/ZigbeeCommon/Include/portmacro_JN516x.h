/*****************************************************************************
 *
 * MODULE:
 *
 * COMPONENT:
 *
 * DESCRIPTION:
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

#ifndef PORTMACRO_JN516x_H
#define PORTMACRO_JN516x_H

#include "jendefs.h"
#include "MicroSpecific.h"
/*-----------------------------------------------------------
 * Chip specific definitions.
 *
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */


/*-----------------------------------------------------------*/
#define SR_SM  (0x00000001UL)
#define SR_TEE  (0x00000002UL)
#define SR_IEE  (0x00000004UL)
#define SR_EPH  (0x00004000UL)

/*
 * Clears a bit in the CPU core status register (SPR grp 0, no. 17)
 * The value provided is a mask containing the bits to be cleared set to 1
 */
#define CLEAR_SR_BITS(bits) { \
    register unsigned int reg; \
    asm volatile ("bw.mfspr %0,r0,0x0011" :"=r"(reg) : ); \
    reg &= ~(bits); \
    asm volatile ("bw.mtspr r0,%0,0x0011" : : "r"(reg) ); \
}

/*
 * Sets a bit in the CPU core status register (SPR grp 0, no. 17)
 * The value provided is a mask containing the bits to be set, set to 1
 */
#define SET_SR_BITS(bits) { \
register unsigned int reg; \
asm volatile ("bw.mfspr %0,r0,0x0011" :"=r"(reg) : ); \
reg |= (bits); \
asm volatile ("bw.mtspr r0,%0,0x0011" : : "r"(reg) ); \
}

/*
 * Sets the PIC IPMR (Interrupt Priority Mask Register) (SPR grp 9, no. 16)
 * with the value provided. The IPMR register controls which IPL we are
 * currently at
 */
#define SET_IPL(ipl) asm volatile ("bw.mtspr r0 , %0 , 0x4810" : : "r"(ipl)  )

/*
 * Gets the PIC IPMR (Interrupt Priority Mask Register) and returns to the variable provided
 * The IPMR register controls which IPL we are currently at
 */
#define GET_IPL(ipl) asm volatile ("bw.mfspr %0 , r0 , 0x4810" :"=r"(ipl) : )
#define GET_IHPR(ihpr) asm volatile ("bw.mfspr %0 , r0 , 0x4811" :"=r"(ihpr) : )
/*
 * Sets the PIC MR (Mask Register) (SPR grp 9, no. 0)
 * with the value provided. The MR register controls which channels are
 * able to assert the external interrupt line.
 */
#define SET_PIC_MR(mask) asm volatile ("l.mtspr r0,%0,0x4800" : :"r"(mask) )


/* Critical section management. */

//#define portENABLE_INTERRUPTS();    SET_SR_BITS(SR_IEE | SR_TEE);
#define portENABLE_INTERRUPTS();      \
    {                                                                           \
        register unsigned long     rulCtrlReg;                                  \
        asm volatile ("b.mfspr %0, r0, 17;" :"=r"(rulCtrlReg) : );              \
        rulCtrlReg |= 4;                                                        \
        asm volatile ("b.mtspr r0, %0, 17;" : :"r"(rulCtrlReg));                \
    }

//#define portDISABLE_INTERRUPTS();   CLEAR_SR_BITS(SR_IEE | SR_TEE);
#define portDISABLE_INTERRUPTS();                                               \
    {                                                                           \
        register unsigned long     rulCtrlReg;                                  \
        asm volatile ("b.mfspr %0, r0, 17;" :"=r"(rulCtrlReg) : );              \
        rulCtrlReg &= 0xfffffff9;                                               \
        asm volatile ("b.mtspr r0, %0, 17;" : :"r"(rulCtrlReg));                \
    }

#define TICK_TIMER_IP_BIT_MASK     0x10000000UL
#define CLEAR_TTMR_IP() { \
    register unsigned int reg; \
    asm volatile ("bw.mfspr %0,r0,0x5000" :"=r"(reg) : ); \
    reg &= ~TICK_TIMER_IP_BIT_MASK; \
    asm volatile ("bw.mtspr r0,%0,0x5000" : : "r"(reg) ); \
}



/*-----------------------------------------------------------*/

#define portBYTE_ALIGNMENT            4
#define portNOP()                    asm volatile ( "b.nop 0x00" );

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

#define TARGET_INITIALISE() {\
    /* disable exceptions via global disable bit */ \
    CLEAR_SR_BITS(SR_IEE | SR_TEE); \
\
    /* clear PIC MR */ \
    SET_PIC_MR(0); \
\
    SET_IPL(15); \
\
/* setup exception vector table */ \
    unsigned int i; \
    for (i = 0; i < 15; i ++) { \
        *((volatile unsigned int *)(0x04000008 + (i * 4))) = OSMIUM_HwVectTable[i]; \
    } \
\
    /* set the relocation bit to move the vector table into RAM at address 0x04000008 \
     * This is EPH (bit 14) in the Supervision Register (SR) (SPR 0x0011)  \
     */ \
    SET_SR_BITS(SR_EPH); \
\
/* set the priority registers in the PIC set by the configuration tool */ \
    asm volatile ( \
        "b.lbz r7,0(%0);" \
        "bw.mtspr r0,r7,0x4820;" \
        "b.lbz r7,1(%0);" \
        "bw.mtspr r0,r7,0x4821;" \
        "b.lbz r7,2(%0);" \
        "bw.mtspr r0,r7,0x4822;" \
        "b.lbz r7,3(%0);" \
        "bw.mtspr r0,r7,0x4823;" \
        "b.lbz r7,4(%0);" \
        "bw.mtspr r0,r7,0x4824;" \
        "b.lbz r7,5(%0);" \
        "bw.mtspr r0,r7,0x4825;" \
        "b.lbz r7,6(%0);" \
        "bw.mtspr r0,r7,0x4826;" \
        "b.lbz r7,7(%0);" \
        "bw.mtspr r0,r7,0x4827;" \
        "b.lbz r7,8(%0);" \
        "bw.mtspr r0,r7,0x4828;" \
        "b.lbz r7,9(%0);" \
        "bw.mtspr r0,r7,0x4829;" \
        "b.lbz r7,10(%0);" \
        "bw.mtspr r0,r7,0x482A;" \
        "b.lbz r7,11(%0);" \
        "bw.mtspr r0,r7,0x482B;" \
        "b.lbz r7,12(%0);" \
        "bw.mtspr r0,r7,0x482C;" \
        "b.lbz r7,13(%0);" \
        "bw.mtspr r0,r7,0x482D;" \
        "b.lbz r7,14(%0);" \
        "bw.mtspr r0,r7,0x482E;" \
        "b.lbz r7,15(%0);" \
        "bw.mtspr r0,r7,0x482F;" \
       : : "r"(PIC_ChannelPriorities) : "r7" ); \
\
\
/* enable exceptions via global enable bit */ \
   /*SET_SR_BITS(SR_IEE);*/ \
}
extern unsigned int OSMIUM_HwVectTable[9];
extern unsigned char PIC_ChannelPriorities[16];

PUBLIC uint8 ZPS_eEnterCriticalSection(void* hMutex, uint32* psIntStore);
PUBLIC uint8 ZPS_eExitCriticalSection(void* hMutex, uint32* psIntStore);
PUBLIC uint8 ZPS_u8GrabMutexLock(void* hMutex, uint32* psIntStore);
PUBLIC uint8 ZPS_u8ReleaseMutexLock(void* hMutex, uint32* psIntStore);

#endif /* PORTMACRO_JN516x_H */
