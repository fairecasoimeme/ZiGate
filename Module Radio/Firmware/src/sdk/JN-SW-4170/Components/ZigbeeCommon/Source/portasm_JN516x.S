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
#define SPR_IPMR (0x4810)
#define SPR_IHPR (0x4811)
# Size of registers; 4 bytes for ba22
#define REG_SIZE    (4)
#define TOTAL_GP_REGS   (16)


#define GP_REGS_OFFSET     (0)
#define STACK_OFFSET_GP_REG(A) (GP_REGS_OFFSET + REG_SIZE * (A))
#define STACK_OFFSET_VECTOR    (STACK_OFFSET_GP_REG(TOTAL_GP_REGS))
#define STACK_OFFSET_SR        (STACK_OFFSET_VECTOR + REG_SIZE)
#define STACK_OFFSET_PC        (STACK_OFFSET_SR     + REG_SIZE)
#define STACK_OFFSET_EEAR      (STACK_OFFSET_PC     + REG_SIZE)
#define STACK_OFFSET_END       (STACK_OFFSET_EEAR   + REG_SIZE)


/* Special Purpose Register (SPR) definitions */
/* - System control and status group */
#define SPR_EPCR_BASE   (0x20)
#define SPR_EEAR_BASE   (0x30)
#define SPR_ESR_BASE    (0x40)

#define INT_STACK_FRAME (STACK_OFFSET_END)

###########################################################################
# Exception vector table, will be copied to ram
###########################################################################

    .globl  OSMIUM_HwVectTable
    .extern vExternalException
    .extern vBusErrorHandler
    .extern vUnclaimedException
    .extern vExternalException
    .extern vStackOverflowHandler
    .extern vAlignmentErrorHandler
    .extern vIllegalInstructionHandler
    .extern vTrapHandler
    .extern vGenericHandler

    .section .text,"ax"
    .align 4
    .type   OSMIUM_HwVectTable, @object
    .size   OSMIUM_HwVectTable, 78
OSMIUM_HwVectTable:
    b.ja vBusErrorHandler               # Bus error exception
    b.ja vUnclaimedException            # Tick timer exception
    b.ja vAlignmentErrorHandler         # Alignment error exception
    b.ja vIllegalInstructionHandler     # illegal instruction  error exception
    b.ja vExternalException             # external interrupt exception
    b.rfe                               # System Call exception
    b.nop                               #
    b.nop                               #
    b.ja vTrapHandler                   # trap error exception
    b.ja vGenericHandler                # Generic error exception
    b.ja vUnclaimedException            #  error exception
    b.ja vStackOverflowHandler          # stack overflow exception


###########################################################################
# External exception
###########################################################################

    .type vExternalException,@function
    .globl vExternalException

vExternalException:
    # Store away essentials
    b.addi  r1, r1, -INT_STACK_FRAME

    # Store General Purpose Registers (GPRs) that are overwritten here
    b.sw    STACK_OFFSET_GP_REG(3)(r1), r3
    b.sw    STACK_OFFSET_GP_REG(10)(r1), r10

    # Store EPCR and ESR, as these would be modified by a subsequent
    # interrupt
    b.mfspr r3, r0, SPR_EPCR_BASE
    b.sw    STACK_OFFSET_PC(r1), r3
    b.mfspr r3, r0, SPR_ESR_BASE
    b.sw    STACK_OFFSET_SR(r1), r3

    # Store current priority mask level in EEAR (which isn't needed)
    b.mfspr r3, r0, SPR_IPMR
    b.sw    STACK_OFFSET_EEAR(r1), r3

    # Copy priority of exception to IPMR
    b.mfspr r3, r0, SPR_IHPR
    b.mtspr r0, r3, SPR_IPMR

    # Re-enable interrupts
    b.ei

    # Store remaining registers. Assuming that we are going to call
    # out to a C handler, we don't have to save r10-r15 as these
    # would be preserved by the C code (r10 has already been saved,
    # though, as we're using it to store the pending interrupts).
    # r9 would be saved as well, but we're going to use a
    # jump-and-link instruction so we're going to obliterate it
    # ourselves.
    # Although we're not saving all the registers, we've left space
    # for them (r0, r11-r15) in the stack to be consistent with other
    # exception handlers.
    b.sw     STACK_OFFSET_GP_REG(2)(r1), r2
    b.sw     STACK_OFFSET_GP_REG(4)(r1), r4
    b.sw     STACK_OFFSET_GP_REG(5)(r1), r5
    b.sw     STACK_OFFSET_GP_REG(6)(r1), r6
    b.sw     STACK_OFFSET_GP_REG(7)(r1), r7
    b.sw     STACK_OFFSET_GP_REG(8)(r1), r8
    b.sw     STACK_OFFSET_GP_REG(9)(r1), r9

    # Determine interrupt priority and call handler(s)
    b.slli  r3,r3,2                        # vector through pseos_ExternalException_Wudo vector table for PIC interrupt sources
    b.addi  r3,r3,PIC_SwVectTable
    b.lwz   r3,0(r3)
    b.jalr  r3

    # All interrupts now dealt with. Restore registers and priority
    # level
    b.lwz    r2,  STACK_OFFSET_GP_REG(2)(r1)
    b.lwz    r3,  STACK_OFFSET_GP_REG(3)(r1)
    b.lwz    r5,  STACK_OFFSET_GP_REG(5)(r1)
    b.lwz    r6,  STACK_OFFSET_GP_REG(6)(r1)
    b.lwz    r7,  STACK_OFFSET_GP_REG(7)(r1)
    b.lwz    r8,  STACK_OFFSET_GP_REG(8)(r1)
    b.lwz    r9,  STACK_OFFSET_GP_REG(9)(r1)
    b.lwz    r10, STACK_OFFSET_GP_REG(10)(r1)

    # Disable interrupts for the last part
    b.di

    # Restore pre-interrupt EPCR and ESR (don't clear IEE bit)
    b.lwz    r4, STACK_OFFSET_SR(r1)
    b.mtspr  r0, r4, SPR_ESR_BASE
    b.lwz    r4, STACK_OFFSET_PC(r1)
    b.mtspr  r0, r4, SPR_EPCR_BASE

    # Restore priority mask level
    b.lwz    r4, STACK_OFFSET_EEAR(r1)
    b.mtspr  r0, r4, SPR_IPMR

    # Restore r4 and stack pointer
    b.lwz    r4, STACK_OFFSET_GP_REG(4)(r1)
    b.addi   r1, r1, INT_STACK_FRAME

    # All done, restore CPU state and continue

    bt.rfe

###########################################################################
# End
###########################################################################
