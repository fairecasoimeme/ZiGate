/*****************************************************************************
 *
 * MODULE:              Definitions specific to a particular processor
 *
 * DESCRIPTION:
 * Definitions for a specific processor, i.e. functions that can only be
 * resolved by op codes
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

#ifndef  MICRO_SPECIFIC_INCLUDED
#define  MICRO_SPECIFIC_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include <jendefs.h>

extern void (*isr_handlers[])(void);

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/** @{ Defined system call numbers */
#define SYSCALL_RESET       0
#define SYSCALL_DBG_IO      1
/** @} */

#ifdef EMBEDDED

/* Defines for ROM size (NOTE: not used anywhere!), CPU (BA1 or BA2), priority
   interrupt support */
#if defined JENNIC_CHIP_JN5121
#define MICRO_ROM_SIZE 0x00010000
#define JENNIC_CPU_BA1
#elif (defined JENNIC_CHIP_JN5139) || (defined JENNIC_CHIP_JN5139R) || (defined JENNIC_CHIP_JN5139R1)
#define MICRO_ROM_SIZE 0x00030000
#define JENNIC_CPU_BA1
#elif defined JENNIC_CHIP_JN5139J01
#define MICRO_ROM_SIZE 0x00030000
#define JENNIC_CPU_BA1
#elif defined JENNIC_CHIP_JN5139T01
#define MICRO_ROM_SIZE 0x00030000
#define JENNIC_CPU_BA1
#elif defined JENNIC_CHIP_JN5147
#define MICRO_ROM_SIZE 0x00020000
#define JENNIC_CPU_BA2
#elif (defined JENNIC_CHIP_JN5142) || (defined JENNIC_CHIP_JN5142_HDK) || (defined JENNIC_CHIP_JN5142J01)
#define MICRO_ROM_SIZE 0x00020000
#define JENNIC_CPU_BA2
#define JENNIC_HW_PRIORITY_INTERRUPTS
#elif defined JENNIC_CHIP_JN5148
#define MICRO_ROM_SIZE 0x00020000
#define JENNIC_CPU_BA2
#elif (defined JENNIC_CHIP_JN5148T01) || (defined JENNIC_CHIP_JN5148T01_HDK) || (defined JENNIC_CHIP_JN5148J01) || (defined JENNIC_CHIP_JN5148Z01)
#define MICRO_ROM_SIZE 0x00020000
#define JENNIC_CPU_BA2
#define JENNIC_HW_PRIORITY_INTERRUPTS
#elif (defined JENNIC_CHIP_FAMILY_JN516x)
#define JENNIC_CPU_BA2
#define JENNIC_HW_PRIORITY_INTERRUPTS
#else
#error Chip not supported!
#endif

/* ISR and VSR table addresses. VSR is table for all exception handlers,
   ISR table is for peripheral interrupts. ISR table definition is now
   redundant */
#ifdef CHIP_RELEASE_1
 #define MICRO_VSR_BASE 0xf0016800
 #define MICRO_ISR_BASE 0xf0017008
#else
 #ifdef CHIP_RELEASE_2
  #define MICRO_VSR_BASE 0xf0017f80
  #define MICRO_ISR_BASE 0xf001700c
 #else
  #ifdef CHIP_RELEASE_3
   #define MICRO_VSR_BASE 0xf0017f80
   #define MICRO_ISR_BASE 0xf001702c
  #else
   #define MICRO_VSR_BASE 0x04000000
  #endif
 #endif
#endif

#define MICRO_ROM_BASE 0x00000000

/* CPU defines for VSR numbers and supervisor mask bits. Values are the same
   for BA1 and BA2 */
#define MICRO_VSR_NUM_TICK      5
#define MICRO_VSR_NUM_EXT       8

#define MICRO_IEE_MASK          (1 << 2)
#define MICRO_TEE_MASK          (1 << 1)

/* The indeces below should be used as the INT value passed to the
   MICRO_SET_VSR_HANDLER macro */
#if defined JENNIC_CPU_BA1
#define MICRO_VSR_IDX_BUS_ERROR    2
#define MICRO_VSR_IDX_TICK         5
#define MICRO_VSR_IDX_UNALIGNED    6
#define MICRO_VSR_IDX_ILLEGAL_INST 7
#define MICRO_VSR_IDX_EXT_INT      8
#define MICRO_VSR_IDX_SYSCALL      12
#define MICRO_VSR_IDX_TRAP         14
#endif

#if defined JENNIC_CHIP_FAMILY_JN514x
#define MICRO_VSR_IDX_BUS_ERROR    0
#define MICRO_VSR_IDX_TICK         1
#define MICRO_VSR_IDX_UNALIGNED    2
#define MICRO_VSR_IDX_ILLEGAL_INST 3
#define MICRO_VSR_IDX_EXT_INT      4
#define MICRO_VSR_IDX_SYSCALL      5
#define MICRO_VSR_IDX_TRAP         6
#define MICRO_VSR_IDX_GENERIC      7
#define MICRO_VSR_IDX_STACK_OVER   8
#endif

/* Defines for peripheral interrupt source bits in the PIC */
#ifdef JENNIC_CPU_BA2

#if (defined JENNIC_CHIP_JN5142) || (defined JENNIC_CHIP_JN5142_HDK) || (defined JENNIC_CHIP_JN5142J01)
#define MICRO_ISR_NUM_TMR1      0
#define MICRO_ISR_NUM_TMR2      1
#define MICRO_ISR_NUM_SYSCTRL   2
#define MICRO_ISR_NUM_BBC       3
#define MICRO_ISR_NUM_AES       4
#define MICRO_ISR_NUM_PHY       5
#define MICRO_ISR_NUM_UART0     6
#define MICRO_ISR_NUM_TMR0      8
#define MICRO_ISR_NUM_I2C       10
#define MICRO_ISR_NUM_SPIM      11
#define MICRO_ISR_NUM_ANPER     13
#define MICRO_ISR_NUM_TMR3      14
#define MICRO_ISR_NUM_TICK_TMR  15
#elif (defined JENNIC_CHIP_FAMILY_JN514x) /* Rest of JN514x family */
#define MICRO_ISR_NUM_AUDIOFIFO 0
#define MICRO_ISR_NUM_I2S       1
#define MICRO_ISR_NUM_SYSCTRL   2
#define MICRO_ISR_NUM_BBC       3
#define MICRO_ISR_NUM_AES       4
#define MICRO_ISR_NUM_PHY       5
#define MICRO_ISR_NUM_UART0     6
#define MICRO_ISR_NUM_UART1     7
#define MICRO_ISR_NUM_TMR0      8
#define MICRO_ISR_NUM_TMR1      9
#define MICRO_ISR_NUM_I2C       10
#define MICRO_ISR_NUM_SPIM      11
#define MICRO_ISR_NUM_INTPER    12
#define MICRO_ISR_NUM_ANPER     13
#define MICRO_ISR_NUM_TMR2      14
#define MICRO_ISR_NUM_TICK_TMR  15
#else /* Assume JN516x */
#define MICRO_ISR_NUM_TMR1      0
#define MICRO_ISR_NUM_TMR2      1
#define MICRO_ISR_NUM_SYSCTRL   2
#define MICRO_ISR_NUM_BBC       3
#define MICRO_ISR_NUM_AES       4
#define MICRO_ISR_NUM_PHY       5
#define MICRO_ISR_NUM_UART0     6
#define MICRO_ISR_NUM_UART1     7
#define MICRO_ISR_NUM_TMR0      8
#define MICRO_ISR_NUM_SPIS      9
#define MICRO_ISR_NUM_I2C       10
#define MICRO_ISR_NUM_SPIM      11
#define MICRO_ISR_NUM_TMR4      12
#define MICRO_ISR_NUM_ANPER     13
#define MICRO_ISR_NUM_TMR3      14
#define MICRO_ISR_NUM_TICK_TMR  15
#endif

#else /* JENNIC_CPU */

/* For user VSR, tick timer is at index 0, system controller at 1, BBC at 2,
   etc. for efficiency */
#define MICRO_ISR_NUM_TICK_TMR  0
#define MICRO_ISR_NUM_SYSCTRL   1
#define MICRO_ISR_NUM_BBC       2
#define MICRO_ISR_NUM_AES       3
#define MICRO_ISR_NUM_PHY       4
#define MICRO_ISR_NUM_UART0     5
#define MICRO_ISR_NUM_UART1     6
#define MICRO_ISR_NUM_TMR0      7
#define MICRO_ISR_NUM_TMR1      8
#ifdef CHIP_RELEASE_1
#define MICRO_ISR_NUM_TMR2      9
#else
#define MICRO_ISR_NUM_I2C       9
#endif
#define MICRO_ISR_NUM_SPIM      10
#define MICRO_ISR_NUM_INTPER    11
#define MICRO_ISR_NUM_ANPER     12

#endif /* JENNIC_CPU */

/* NOTE: Following are based on values above. Not all are defined for all
   chips. So if an error is raised by the MICRO_ISR_MASK_* macros below, look
   to see if the corresponding MICRO_ISR_NUM_* macro is defined above. If it
   isn't, that peripheral is not present on the defined chip */
#define MICRO_ISR_MASK_TICK_TMR (1 << MICRO_ISR_NUM_TICK_TMR)
#define MICRO_ISR_MASK_SYSCTRL  (1 << MICRO_ISR_NUM_SYSCTRL)
#define MICRO_ISR_MASK_BBC      (1 << MICRO_ISR_NUM_BBC)
#define MICRO_ISR_MASK_AES      (1 << MICRO_ISR_NUM_AES)
#define MICRO_ISR_MASK_PHY      (1 << MICRO_ISR_NUM_PHY)
#define MICRO_ISR_MASK_UART0    (1 << MICRO_ISR_NUM_UART0)
#define MICRO_ISR_MASK_UART1    (1 << MICRO_ISR_NUM_UART1)
#define MICRO_ISR_MASK_TMR0     (1 << MICRO_ISR_NUM_TMR0)
#define MICRO_ISR_MASK_TMR1     (1 << MICRO_ISR_NUM_TMR1)
#define MICRO_ISR_MASK_TMR2     (1 << MICRO_ISR_NUM_TMR2)
#define MICRO_ISR_MASK_TMR3     (1 << MICRO_ISR_NUM_TMR3)
#define MICRO_ISR_MASK_TMR4     (1 << MICRO_ISR_NUM_TMR4)
#define MICRO_ISR_MASK_I2C      (1 << MICRO_ISR_NUM_I2C)
#define MICRO_ISR_MASK_SPIM     (1 << MICRO_ISR_NUM_SPIM)
#define MICRO_ISR_MASK_SPIS     (1 << MICRO_ISR_NUM_SPIS)
#define MICRO_ISR_MASK_INTPER   (1 << MICRO_ISR_NUM_INTPER)
#define MICRO_ISR_MASK_ANPER    (1 << MICRO_ISR_NUM_ANPER)

/* Handy macros for controlling interrupts, PIC, interrupt levels */
#ifdef JENNIC_CPU_BA2

#define FF1(__input)                               \
     ({ uint32 __result;                           \
        asm volatile ("b.ff1 %[result], %[input];" \
                      : [result] "=r" (__result)   \
                      : [input]  "r"  (__input)    \
                     );                            \
        __result; })

#define MICRO_ENABLE_INTERRUPTS();                                          \
        asm volatile ("b.ei;" : : );

#define MICRO_DISABLE_INTERRUPTS();                                         \
        asm volatile ("b.di;" : : );

#define MICRO_DISABLE_AND_SAVE_INTERRUPTS(u32Store);                        \
    {                                                                       \
        asm volatile ("bw.mfspr %0, r0, 17;" :"=r"(u32Store) : );            \
        asm volatile ("b.di;" : : );                                        \
    }

#define MICRO_RESTORE_INTERRUPTS(u32Store);                                 \
        asm volatile ("bw.mtspr r0, %0, 17;" : :"r"(u32Store));

#ifdef JENNIC_HW_PRIORITY_INTERRUPTS
extern void vAHI_InterruptSetPriority(uint16 u16Mask, uint8 u8Level);

#define MICRO_ENABLE_TICK_TIMER_INTERRUPT();                                \
    vAHI_InterruptSetPriority(MICRO_ISR_MASK_TICK_TMR,8);

#define MICRO_SET_PIC_ENABLE(A);                                            \
    vAHI_InterruptSetPriority(A,8);

#define MICRO_CLEAR_PIC_ENABLE(A);                                          \
    vAHI_InterruptSetPriority(A,0);

#define MICRO_SET_PIC_PRIORITY_LEVEL(A,B);                                  \
    asm volatile ("bw.mtspr r0, %0, %1;" : : "r"(B), "i"(0x4820+(A)));

#define MICRO_GET_PIC_PRIORITY_LEVEL(A)                                     \
    ({                                                                      \
        register uint32 __result;                                           \
        asm volatile ("bw.mfspr %0, r0, %1;":"=r"(__result):"i"(0x4820+(A)));\
        __result;                                                           \
    })

#define MICRO_SET_ACTIVE_INT_LEVEL(A);                                      \
    asm volatile ("bw.mtspr r0, %0, 0x4810;" : :"r"(A));

#define MICRO_GET_ACTIVE_INT_LEVEL()                                        \
    ({                                                                      \
        register uint32 __result;                                           \
        asm volatile ("bw.mfspr %0, r0, 0x4810;" : "=r"(__result) :);        \
        __result;                                                           \
    })

#else /* JENNIC_HW_PRIORITY_INTERRUPTS */

#define MICRO_ENABLE_TICK_TIMER_INTERRUPT();                                \
    {                                                                       \
        register uint32 ruCtrlReg;                                          \
        asm volatile ("bw.mfspr %0, r0, 17;" :"=r"(ruCtrlReg) : );           \
        ruCtrlReg |= 2;                                                     \
        asm volatile ("bw.mtspr r0, %0, 17;" : :"r"(ruCtrlReg));             \
    }

#define MICRO_SET_PIC_ENABLE(A);                                            \
    {                                                                       \
        register uint32 ruCtrlReg;                                          \
        asm volatile ("bw.mfspr %0, r0, %1;" :"=r"(ruCtrlReg) : "i"(0x4800));\
        ruCtrlReg |= A;                                                     \
        asm volatile ("bw.mtspr r0, %0, %1;" : :"r"(ruCtrlReg), "i"(0x4800));\
    }

#define MICRO_CLEAR_PIC_ENABLE(A);                                          \
    {                                                                       \
        register uint32 ruCtrlReg;                                          \
        asm volatile ("bw.mfspr %0, r0, %1;" :"=r"(ruCtrlReg) : "i"(0x4800));\
        ruCtrlReg &= ~(A);                                                  \
        asm volatile ("bw.mtspr r0, %0, %1;" : :"r"(ruCtrlReg), "i"(0x4800));\
    }

#define MICRO_CLEAR_PIC();                                                  \
    asm volatile ("bw.mtspr r0, r0, 0x4802;" : : );

#endif /* JENNIC_HW_PRIORITY_INTERRUPTS */


/** Read SPR at u32Address and return.
 *  \param u32Address must be a constant value.
 */
#define MICRO_READ_SPR(u32Address)                                          \
({ register uint32 __result;                                                \
    asm volatile ("bw.mfspr %0, r0, %1;" :"=r"(__result) : "i"(u32Address)); \
    __result;                                                               \
})

/** Read from SPR at offset u32Offset from u32Address and return.
 *  \param u32Address must be a constant value
 *  \param u32Offset  must be a variable
 */
#define MICRO_READ_SPR_OFFSET(u32Address, u32Offset)                        \
({ register uint32 __result;                                                 \
    asm volatile ("bw.mfspr %0, %1, %2;" :"=r"(__result) : "r"(u32Offset), "i"(u32Address)); \
    __result;                                                               \
})

/** Write SPR at u32Address with u32Data.
 *  \param u32Address must be a constant value.
 *  \param u32Data      must be a variable
 */
#define MICRO_WRITE_SPR(u32Address, u32Data)                                \
({                                                                          \
    asm volatile ("bw.mtspr r0, %0, %1;" : :"r"(u32Data), "i"(u32Address)); \
})

/** Write SPR at offset u32Offset from u32Address with u32Data.
 *  \param u32Address   must be a constant value.
 *  \param u32Offset    must be a variable
 *  \param u32Data      must be a variable
 */
#define MICRO_WRITE_SPR_OFFSET(u32Address, u32Offset, u32Data)              \
({                                                                          \
    asm volatile ("bw.mtspr %1, %0, %2;" : :"r"(u32Data), "r"(u32Offset), "i"(u32Address)); \
})


/** Generate a system call exception. Pass the system call number in R3.
 * Pass further arguments as applicable in R4 - R8.
 */
void __attribute__((noinline)) vMicroSyscall(volatile uint32 u32SysCallNumber, ...);

#else /* JENNIC_CPU */

#define MICRO_ENABLE_INTERRUPTS();                                          \
    {                                                                       \
        register uint32 ruCtrlReg;                                          \
        asm volatile ("l.mfspr %0, r0, 17;" :"=r"(ruCtrlReg) : );           \
        ruCtrlReg |= 4;                                                     \
        asm volatile ("l.mtspr r0, %0, 17;" : :"r"(ruCtrlReg));             \
    }

#define MICRO_DISABLE_AND_SAVE_INTERRUPTS(u32Store);                        \
    {                                                                       \
        register uint32 ruCtrlReg;                                          \
        asm volatile ("l.mfspr %0, r0, 17;" :"=r"(u32Store) : );            \
        ruCtrlReg = u32Store & 0xfffffff9;                                  \
        asm volatile ("l.mtspr r0, %0, 17;" : :"r"(ruCtrlReg));             \
    }

#define MICRO_RESTORE_INTERRUPTS(u32Store);                                 \
        asm volatile ("l.mtspr r0, %0, 17;" : :"r"(u32Store));

#define MICRO_ENABLE_TICK_TIMER_INTERRUPT();                                \
    {                                                                       \
        register uint32 ruCtrlReg;                                          \
        asm volatile ("l.mfspr %0, r0, 17;" :"=r"(ruCtrlReg) : );           \
        ruCtrlReg |= 2;                                                     \
        asm volatile ("l.mtspr r0, %0, 17;" : :"r"(ruCtrlReg));             \
    }

#define MICRO_SET_PIC_ENABLE(A);                                            \
    {                                                                       \
        register uint32 ruCtrlReg;                                          \
        asm volatile ("l.mfspr %0, r0, %1;" :"=r"(ruCtrlReg) : "i"(0x4800));\
        ruCtrlReg |= A;                                                     \
        asm volatile ("l.mtspr r0, %0, %1;" : :"r"(ruCtrlReg), "i"(0x4800));\
    }

#define MICRO_CLEAR_PIC_ENABLE(A);                                          \
    {                                                                       \
        register uint32 ruCtrlReg;                                          \
        asm volatile ("b.mfspr %0, r0, %1;" :"=r"(ruCtrlReg) : "i"(0x4800));\
        ruCtrlReg &= ~(A);                                                  \
        asm volatile ("b.mtspr r0, %0, %1;" : :"r"(ruCtrlReg), "i"(0x4800));\
    }

#define MICRO_CLEAR_PIC();                                                  \
    asm volatile ("l.mtspr r0, r0, 0x4802;" : : );

#endif /* JENNIC_CPU */

/* Handler registration */
#if (defined JENNIC_CHIP_FAMILY_JN514x) || (defined JENNIC_CPU_BA1)

#define MICRO_SET_INT_HANDLER(INT, FUNC);                                   \
    ((void **)(*(uint32 *)0x44))[(INT)] = (void *)(FUNC);

#define MICRO_GET_INT_HANDLER(INT)                                          \
    (((void **)(*(uint32 *)0x44))[(INT)])

/* The index values MICRO_VSR_IDX_xxx defined earlier should be used as the
   INT value passed to the following macro */
#define MICRO_SET_VSR_HANDLER(INT, FUNC);                                   \
    *(void **)(MICRO_VSR_BASE + ((INT) << 2)) = (void *)(FUNC);

#else
/* Location of isr_handlers is no longer at a known location, but we can link
   to it directly instead */
#define MICRO_SET_INT_HANDLER(INT, FUNC);                                   \
    isr_handlers[(INT)] = (void *)(FUNC);

#define MICRO_GET_INT_HANDLER(INT)                                          \
    (isr_handlers[(INT)])

#endif

/* NOP instruction */
#define MICRO_NOP()                                                         \
    {                                                                       \
        asm volatile ("b.nop;");                                            \
    }

/* TRAP instruction */
#define MICRO_TRAP()                                                         \
    {                                                                        \
        asm volatile("b.trap 0");                                            \
    }

/* JUMP instruction */
#define MICRO_JUMP_TO_ADDRESS(ADDRESS)                                      \
    {                                                                       \
       asm volatile ("b.jr %0;" : :"r"(ADDRESS));                           \
       asm volatile ("b.nop 0");                                            \
    }
#else /* EMBEDDED */

#define MICRO_ENABLE_INTERRUPTS();
#define MICRO_DISABLE_INTERRUPTS();
#define MICRO_ENABLE_TICK_TIMER_INTERRUPT();
#define MICRO_SET_PIC_ENABLE(A);
#define MICRO_CLEAR_PIC_ENABLE(A);
#define MICRO_CLEAR_PIC();
#define MICRO_SET_INT_HANDLER(INT, FUNC);
#define MICRO_SET_VSR_HANDLER(INT, FUNC);

#endif /* EMBEDDED */

/* Nested interrupt control */
#if defined NO_NESTED_INTERRUPTS
/* Map nested interrupt support to basic macros */
#define MICRO_INT_STORAGE         uint32 u32InterruptStore
#define MICRO_INT_ENABLE_ONLY(A)  MICRO_DISABLE_AND_SAVE_INTERRUPTS(u32InterruptStore)
#define MICRO_INT_RESTORE_STATE() MICRO_RESTORE_INTERRUPTS(u32InterruptStore)
#else
/* Nested interrupt support */
#define MICRO_INT_STORAGE         tsMicroIntStorage sIntStorage
#define MICRO_INT_ENABLE_ONLY(A)  vMicroIntEnableOnly(&sIntStorage, A)
#define MICRO_INT_RESTORE_STATE() vMicroIntRestoreState(&sIntStorage)
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
/* Nested interrupt control */
#if !(defined NO_NESTED_INTERRUPTS)
#if defined JENNIC_HW_PRIORITY_INTERRUPTS
typedef struct
{
    uint8 u8Level;
} tsMicroIntStorage;
#else
typedef struct
{
    uint32 u32Pic;
    uint32 u32Sr;
} tsMicroIntStorage;
#endif
#endif

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/* Nested interrupt control */
#if !(defined NO_NESTED_INTERRUPTS)
PUBLIC void vMicroIntSetGlobalEnable(uint32 u32EnableMask);
PUBLIC void vMicroIntEnableOnly(tsMicroIntStorage *, uint32 u32EnableMask);
PUBLIC void vMicroIntRestoreState(tsMicroIntStorage *);
#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif  /* MICRO_SPECIFIC_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

