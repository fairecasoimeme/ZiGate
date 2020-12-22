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

/* Standard includes. */
#include <stdlib.h>
#include "portmacro_JN517x.h"
#include "dbg.h"
#include "AppHardwareApi.h"
#include "MicroSpecific.h"
#include "ARMcortexM3Registers_JN51xx.h"

#if !(defined WEAK)
#define WEAK              __attribute__ ((weak))
#endif

#ifdef DBG_ENABLE
#define DBG_EXCEPTION      TRUE
#else
#define DBG_EXCEPTION      FALSE
#endif 

#define GET_EXCEPTION_STACK_FRAME()                                   \
   {                                                                  \
        asm volatile("MRS R0, MSP");                                  \
   }

enum { R0, R1, R2, R3, R12, LR, PC, PSR, SIZE_OF_EXCEPTION_STACK};
/* PUBLIC functions */

__attribute__((used)) void vUsageFaultHandler( uint32    *pu32ExceptionArgs );
__attribute__((used)) void vMemManageFaultHandler (uint32    *pu32ExceptionArgs );
__attribute__((used)) void vUnclaimedExceptionHandler (uint32    *pu32ExceptionArgs );
__attribute__((used)) void vShowException ( uint32    *pu32RawStack );


/*Local functions */
PRIVATE void vPrintConfigurableFaultStatusRegisterBitFields ( uint32    u32RegisterData );
PRIVATE void vPrintHardFaultStatusRegisterBitFields ( uint32    u32RegisterData );
PRIVATE void vPrintSystemHandlerAndControlStateRegisterBitFields ( uint32    u32RegisterData );
PRIVATE void vPrintRegisterBit ( uint32    u32BitSet );
/*-----------------------------------------------------------*/


/* Run time exception handlers */


/*-----------------------------------------------------------*/

__attribute__((used))  void vHardFault_Handler ( void )
{
    GET_EXCEPTION_STACK_FRAME ( );
    asm volatile("B vHardFaultHandler");
}

/*-----------------------------------------------------------*/

__attribute__((used))  void vUsageFault_Handler ( void )
{

    GET_EXCEPTION_STACK_FRAME ( );
    asm volatile("B vUsageFaultHandler");
}

__attribute__((used))  void vBusFault_Handler ( void )
{
    GET_EXCEPTION_STACK_FRAME ( );
    asm volatile("B vBusFaultHandler");
}


__attribute__((used))  void vMemManage_Handler ( void )
{
    GET_EXCEPTION_STACK_FRAME ( );
    asm volatile("B vMemManageFaultHandler");
}

__attribute__((used))  void vIntDefaultHandler ( void )
{
    GET_EXCEPTION_STACK_FRAME ( );
    asm volatile("B vUnclaimedExceptionHandler");
}


__attribute__((used)) void vWatchdogHandler ( uint32    u32Device ,
                                              uint32    u32ItemBitmap )
{
    uint32 u32ExceptionArgs;
    uint32 *pu32RawStack = &u32ExceptionArgs;

    DBG_vPrintf (DBG_EXCEPTION, "\r\n **** Watchdog Handler **** \r\n");
        while ((uint32)pu32RawStack & 0x7fff)
    {
        DBG_vPrintf(DBG_EXCEPTION, "% 8x : %08x\n", pu32RawStack, *pu32RawStack);
        pu32RawStack++;
    }
}

__attribute__((used)) void vUsageFaultHandler(uint32 *pu32ExceptionArgs)
{
    uint32 u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK];


    // make local copies - could use memcpy but I had a library exception
    // issue with memcpy/memset/memcmp which would have driven me crazier
    // should I have used it here
    // memcpy(u32ExceptionArgs, pu32ExceptionArgs,SIZE_OF_EXCEPTION_STACK*4);

    u32ExceptionArgs[R0] = pu32ExceptionArgs[R0];
    u32ExceptionArgs[R1] = pu32ExceptionArgs[R1];
    u32ExceptionArgs[R2] = pu32ExceptionArgs[R2];
    u32ExceptionArgs[R3] = pu32ExceptionArgs[R3];
    u32ExceptionArgs[R12] = pu32ExceptionArgs[R12];
    u32ExceptionArgs[LR] = pu32ExceptionArgs[LR];
    u32ExceptionArgs[PC] = pu32ExceptionArgs[PC];
    u32ExceptionArgs[PSR] = pu32ExceptionArgs[PSR];
    DBG_vPrintf (DBG_EXCEPTION, "\r\n **** Usage fault Handler **** \r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\r\n **** Stack Register Dump **** \r\n");

    DBG_vPrintf (DBG_EXCEPTION,"\nR0 = 0x%x", u32ExceptionArgs[R0]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR1 = 0x%x", u32ExceptionArgs[R1]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR2 = 0x%x", u32ExceptionArgs[R2]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR3 = 0x%x", u32ExceptionArgs[R3]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR12 = 0x%x",u32ExceptionArgs[R12]);
	DBG_vPrintf (DBG_EXCEPTION,"\n[Subroutine Call Return Address]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nLR [R14] = 0x%x",u32ExceptionArgs[LR]);    
	DBG_vPrintf (DBG_EXCEPTION,"\n [Program counter]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nPC [R15] = 0x%x",u32ExceptionArgs[PC]);    
    DBG_vPrintf (DBG_EXCEPTION,"\nPSR = 0x%x", u32ExceptionArgs[PSR]);
    vShowException(&u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK]);
}
__attribute__((used)) void vHardFaultHandler(uint32 *pu32ExceptionArgs)
{
    uint32 u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK];


    // make local copies - could use memcpy but I had a library exception
    // issue with memcpy/memset/memcmp which would have driven me crazier
    // should I have used it here
    // memcpy(u32ExceptionArgs, pu32ExceptionArgs,SIZE_OF_EXCEPTION_STACK*4);

    u32ExceptionArgs[R0] = pu32ExceptionArgs[R0];
    u32ExceptionArgs[R1] = pu32ExceptionArgs[R1];
    u32ExceptionArgs[R2] = pu32ExceptionArgs[R2];
    u32ExceptionArgs[R3] = pu32ExceptionArgs[R3];
    u32ExceptionArgs[R12] = pu32ExceptionArgs[R12];
    u32ExceptionArgs[LR] = pu32ExceptionArgs[LR];
    u32ExceptionArgs[PC] = pu32ExceptionArgs[PC];
    u32ExceptionArgs[PSR] = pu32ExceptionArgs[PSR];
    DBG_vPrintf (DBG_EXCEPTION, "\r\n **** Hard Fault Handler **** \r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\r\n **** Stack Register Dump **** \r\n");

    DBG_vPrintf (DBG_EXCEPTION,"\nR0 = 0x%x", u32ExceptionArgs[R0]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR1 = 0x%x", u32ExceptionArgs[R1]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR2 = 0x%x", u32ExceptionArgs[R2]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR3 = 0x%x", u32ExceptionArgs[R3]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR12 = 0x%x",u32ExceptionArgs[R12]);
	DBG_vPrintf (DBG_EXCEPTION,"\n[Subroutine Call Return Address]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nLR [R14] = 0x%x",u32ExceptionArgs[LR]);
	DBG_vPrintf (DBG_EXCEPTION,"\n [Program counter]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nPC [R15] = 0x%x",u32ExceptionArgs[PC]);    
    DBG_vPrintf (DBG_EXCEPTION,"\nPSR = 0x%x", u32ExceptionArgs[PSR]);
    vShowException(&u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK]);
}
__attribute__((used)) void vBusFaultHandler(uint32 *pu32ExceptionArgs)
{
    uint32 u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK];


    // make local copies - could use memcpy but I had a library exception
    // issue with memcpy/memset/memcmp which would have driven me crazier
    // should I have used it here
    // memcpy(u32ExceptionArgs, pu32ExceptionArgs,SIZE_OF_EXCEPTION_STACK*4);

    u32ExceptionArgs[R0] = pu32ExceptionArgs[R0];
    u32ExceptionArgs[R1] = pu32ExceptionArgs[R1];
    u32ExceptionArgs[R2] = pu32ExceptionArgs[R2];
    u32ExceptionArgs[R3] = pu32ExceptionArgs[R3];
    u32ExceptionArgs[R12] = pu32ExceptionArgs[R12];
    u32ExceptionArgs[LR] = pu32ExceptionArgs[LR];
    u32ExceptionArgs[PC] = pu32ExceptionArgs[PC];
    u32ExceptionArgs[PSR] = pu32ExceptionArgs[PSR];
    DBG_vPrintf (DBG_EXCEPTION, "\r\n **** Bus fault Handler **** \r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\r\n **** Stack Register Dump **** \r\n");

    DBG_vPrintf (DBG_EXCEPTION,"\nR0 = 0x%x", u32ExceptionArgs[R0]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR1 = 0x%x", u32ExceptionArgs[R1]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR2 = 0x%x", u32ExceptionArgs[R2]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR3 = 0x%x", u32ExceptionArgs[R3]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR12 = 0x%x",u32ExceptionArgs[R12]);
	DBG_vPrintf (DBG_EXCEPTION,"\n[Subroutine Call Return Address]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nLR [R14] = 0x%x",u32ExceptionArgs[LR]);
	DBG_vPrintf (DBG_EXCEPTION,"\n [Program counter]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nPC [R15] = 0x%x",u32ExceptionArgs[PC]);    
    DBG_vPrintf (DBG_EXCEPTION,"\nPSR = 0x%x", u32ExceptionArgs[PSR]);
    vShowException(&u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK]);
}
__attribute__((used)) void vMemManageFaultHandler(uint32 *pu32ExceptionArgs)
{
    uint32 u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK];


    // make local copies - could use memcpy but I had a library exception
    // issue with memcpy/memset/memcmp which would have driven me crazier
    // should I have used it here
    // memcpy(u32ExceptionArgs, pu32ExceptionArgs,SIZE_OF_EXCEPTION_STACK*4);

    u32ExceptionArgs[R0] = pu32ExceptionArgs[R0];
    u32ExceptionArgs[R1] = pu32ExceptionArgs[R1];
    u32ExceptionArgs[R2] = pu32ExceptionArgs[R2];
    u32ExceptionArgs[R3] = pu32ExceptionArgs[R3];
    u32ExceptionArgs[R12] = pu32ExceptionArgs[R12];
    u32ExceptionArgs[LR] = pu32ExceptionArgs[LR];
    u32ExceptionArgs[PC] = pu32ExceptionArgs[PC];
    u32ExceptionArgs[PSR] = pu32ExceptionArgs[PSR];
    DBG_vPrintf (DBG_EXCEPTION, "\r\n **** Memory management fault Handler **** \r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\r\n **** Stack Register Dump **** \r\n");

    DBG_vPrintf (DBG_EXCEPTION,"\nR0 = 0x%x", u32ExceptionArgs[R0]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR1 = 0x%x", u32ExceptionArgs[R1]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR2 = 0x%x", u32ExceptionArgs[R2]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR3 = 0x%x", u32ExceptionArgs[R3]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR12 = 0x%x",u32ExceptionArgs[R12]);
	DBG_vPrintf (DBG_EXCEPTION,"\n[Subroutine Call Return Address]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nLR [R14] = 0x%x",u32ExceptionArgs[LR]);
	DBG_vPrintf (DBG_EXCEPTION,"\n [Program counter]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nPC [R15] = 0x%x",u32ExceptionArgs[PC]);    
    DBG_vPrintf (DBG_EXCEPTION,"\nPSR = 0x%x", u32ExceptionArgs[PSR]);
    vShowException(&u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK]);
}
__attribute__((used)) void vUnclaimedExceptionHandler(uint32 *pu32ExceptionArgs)
{
    uint32 u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK];


    // make local copies - could use memcpy but I had a library exception
    // issue with memcpy/memset/memcmp which would have driven me crazier
    // should I have used it here
    // memcpy(u32ExceptionArgs, pu32ExceptionArgs,SIZE_OF_EXCEPTION_STACK*4);

    u32ExceptionArgs[R0] = pu32ExceptionArgs[R0];
    u32ExceptionArgs[R1] = pu32ExceptionArgs[R1];
    u32ExceptionArgs[R2] = pu32ExceptionArgs[R2];
    u32ExceptionArgs[R3] = pu32ExceptionArgs[R3];
    u32ExceptionArgs[R12] = pu32ExceptionArgs[R12];
    u32ExceptionArgs[LR] = pu32ExceptionArgs[LR];
    u32ExceptionArgs[PC] = pu32ExceptionArgs[PC];
    u32ExceptionArgs[PSR] = pu32ExceptionArgs[PSR];
    DBG_vPrintf (DBG_EXCEPTION, "\r\n **** Unclaimed exception Handler **** \r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\r\n **** Stack Register Dump **** \r\n");

    DBG_vPrintf (DBG_EXCEPTION,"\nR0 = 0x%x", u32ExceptionArgs[R0]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR1 = 0x%x", u32ExceptionArgs[R1]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR2 = 0x%x", u32ExceptionArgs[R2]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR3 = 0x%x", u32ExceptionArgs[R3]);
    DBG_vPrintf (DBG_EXCEPTION,"\nR12 = 0x%x",u32ExceptionArgs[R12]);
	DBG_vPrintf (DBG_EXCEPTION,"\n[Subroutine Call Return Address]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nLR [R14] = 0x%x",u32ExceptionArgs[LR]);
	DBG_vPrintf (DBG_EXCEPTION,"\n [Program counter]\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"\nPC [R15] = 0x%x",u32ExceptionArgs[PC]);    
    DBG_vPrintf (DBG_EXCEPTION,"\nPSR = 0x%x", u32ExceptionArgs[PSR]);
    vShowException(&u32ExceptionArgs[SIZE_OF_EXCEPTION_STACK]);
}

__attribute__((used)) void vShowException(uint32 *pu32RawStack)
{
	volatile uint32 u32RegisterData;
    // report REG_SYSTEM_HANDLER_CNTRL_STATE
    u32RegisterData = u32REG_Read(REG_SYSTEM_HANDLER_CNTRL_STATE);
    DBG_vPrintf (DBG_EXCEPTION,"\nREG_SYSTEM_HANDLER_CNTRL_STATE = 0x%x", u32RegisterData);

    DBG_vPrintf (DBG_EXCEPTION,"\nREG_SYSTEM_HANDLER_CNTRL_STATE Register Details\r\n");
    vPrintSystemHandlerAndControlStateRegisterBitFields(u32RegisterData);

    // read addresses before valid bits
    // BusFault Address Register contains the address of the location that generated a BusFault.
    // VALID bit of the BFSR is set to 1
    u32RegisterData = u32REG_Read(REG_BUSFAULT_ADDRESS);
    DBG_vPrintf (DBG_EXCEPTION,"\nREG_BUSFAULT_ADDRESS = 0x%x", u32RegisterData);
    DBG_vPrintf (DBG_EXCEPTION,"\r\n");

    // The MMFAR contains the address of the location that generated a MemManage fault
    u32RegisterData = u32REG_Read(REG_MEMMANAGE_FAULT_ADDRESS);
    DBG_vPrintf (DBG_EXCEPTION,"REG_MEMMANAGE_FAULT_ADDRESS = 0x%x",u32RegisterData);
    DBG_vPrintf (DBG_EXCEPTION,"\r\n");

    // Configurable Fault Status Register contains the reasons for the specific fault.
    u32RegisterData = u32REG_Read(REG_CONFIGURABLE_FAULT_STATUS);
    DBG_vPrintf (DBG_EXCEPTION,"REG_CONFIGURABLE_FAULT_STATUS = 0x%x", u32RegisterData);
    DBG_vPrintf (DBG_EXCEPTION,"\r\n");

    DBG_vPrintf (DBG_EXCEPTION,"REG_CONFIGURABLE_FAULT_STATUS Register Details\r\n");
    vPrintConfigurableFaultStatusRegisterBitFields(u32RegisterData);

    // hard fault.
    u32RegisterData = u32REG_Read(REG_HARDFAULT_STATUS);
    DBG_vPrintf (DBG_EXCEPTION,"REG_HARDFAULT_STATUS = 0x%x",u32RegisterData);
    DBG_vPrintf (DBG_EXCEPTION,"\r\n");
    DBG_vPrintf (DBG_EXCEPTION,"REG_HARDFAULT_STATUS Register Details\r\n");
    vPrintHardFaultStatusRegisterBitFields(u32RegisterData);

    // Debug Fault Status Register
    u32RegisterData = u32REG_Read(REG_DEBUG_FAULT_STATUS);
    DBG_vPrintf (DBG_EXCEPTION,"REG_DEBUG_FAULT_STATUS = 0x%x",u32RegisterData);
    DBG_vPrintf (DBG_EXCEPTION,"\r\n");

    // Auxiliary Fault Status Register
    u32RegisterData = u32REG_Read(REG_AUXILIARY_FAULT_STATUS);
    DBG_vPrintf (DBG_EXCEPTION,"REG_AUXILIARY_FAULT_STATUS = 0x%x",u32RegisterData);
    DBG_vPrintf (DBG_EXCEPTION,"\r\n");
    while ((uint32)pu32RawStack & 0x7fff)
    {
        DBG_vPrintf(DBG_EXCEPTION, "% 8x : %08x\n", pu32RawStack, *pu32RawStack);
        pu32RawStack++;
    }
    if(u32REG_Read(REG_DEBUG_HALTING_STATUS_AND_CONTROL) & 0x1)
    {
        // if C_DEBUGEN == 1, debugger connected halt program execution
        MICRO_TRAP();
    }

    while (1);
}
PRIVATE void vPrintConfigurableFaultStatusRegisterBitFields(uint32 u32RegisterData)
{
    DBG_vPrintf(DBG_EXCEPTION,"MemManage Fault Status Register\r\n");

    DBG_vPrintf(DBG_EXCEPTION,"IACCVIOL : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_MMFSR_IACCVIOL_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"DACCVIOL : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_MMFSR_DACCVIOL_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"MUNSTKERR : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_MMFSR_MUNSTKERR_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"MSTKERR : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_MMFSR_MSTKERR_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"MMARVALID : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_MMFSR_MMARVALID_MASK);

    DBG_vPrintf(DBG_EXCEPTION,"BusFault Status Register\r\n");

    DBG_vPrintf(DBG_EXCEPTION,"IBUSERR : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_BFSR_IBUSERR_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"PRECISERR : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_BFSR_PRECISERR_MASK);
    // imp errors can be made p errors by  setting DISDEFWBUF bit(write to 1)
    DBG_vPrintf(DBG_EXCEPTION,"IMPRECISERR : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_BFSR_IMPRECISERR_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"UNSTKERR : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_BFSR_UNSTKERR_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"STKERR : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_BFSR_STKERR_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"BFARVALID : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_BFSR_BFARVALID_MASK);

    DBG_vPrintf(DBG_EXCEPTION,"UsageFault Status Register\r\n");

    DBG_vPrintf(DBG_EXCEPTION,"UNDEFINSTR : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_UFSR_UNDEFINSTR_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"INVSTATE : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_UFSR_INVSTATE_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"INVPC : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_UFSR_INVPC_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"NOCP : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_UFSR_NOCP_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"UNALIGNED : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_UFSR_UNALIGNED_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"DIVBYZERO : ");
    vPrintRegisterBit(u32RegisterData & REG_CONFIGURABLE_FAULT_STATUS_UFSR_DIVBYZERO_MASK);

}

PRIVATE void vPrintHardFaultStatusRegisterBitFields(uint32 u32RegisterData)
{
    DBG_vPrintf(DBG_EXCEPTION,"HardFault Status Register\r\n");

    DBG_vPrintf(DBG_EXCEPTION,"VECTTBL : ");
    vPrintRegisterBit(u32RegisterData & REG_HARDFAULT_STATUS_VECTTBL_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"FORCED : ");
    vPrintRegisterBit(u32RegisterData & REG_HARDFAULT_STATUS_FORCED_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"DEBUGEVT : ");
    vPrintRegisterBit(u32RegisterData & REG_HARDFAULT_STATUS_DEBUGEVT_MASK);

}


PRIVATE void vPrintSystemHandlerAndControlStateRegisterBitFields(uint32 u32RegisterData)
{
	DBG_vPrintf(DBG_EXCEPTION," REG_SYSTEM_HANDLER_CNTRL_STATE Fault Enable Indicators\r\n");

	DBG_vPrintf(DBG_EXCEPTION,"MEMFAULTEN : ");
    vPrintRegisterBit(u32RegisterData & REG_SYSTEM_HANDLER_CNTRL_STATE_MEMFAULTEN_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"BUSFAULTEN : ");
    vPrintRegisterBit(u32RegisterData & REG_SYSTEM_HANDLER_CNTRL_STATE_BUSFAULTEN_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"USGFAULTEN : ");
    vPrintRegisterBit(u32RegisterData & REG_SYSTEM_HANDLER_CNTRL_STATE_USGFAULTEN_MASK);

    DBG_vPrintf(DBG_EXCEPTION,"REG_SYSTEM_HANDLER_CNTRL_STATE Fault Active Indicators\r\n");

    DBG_vPrintf(DBG_EXCEPTION,"MEMFAULTACT : ");
    vPrintRegisterBit(u32RegisterData & REG_SYSTEM_HANDLER_CNTRL_STATE_MEMFAULTACT_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"BUSFAULTACT : ");
    vPrintRegisterBit(u32RegisterData & REG_SYSTEM_HANDLER_CNTRL_STATE_BUSFAULTACT_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"USGFAULTACT : ");
    vPrintRegisterBit(u32RegisterData & REG_SYSTEM_HANDLER_CNTRL_STATE_USGFAULTACT_MASK);

    DBG_vPrintf(DBG_EXCEPTION,"REG_SYSTEM_HANDLER_CNTRL_STATE Fault Pended Indicators\r\n");

    DBG_vPrintf(DBG_EXCEPTION,"MEMFAULTPENDED : ");
    vPrintRegisterBit(u32RegisterData & REG_SYSTEM_HANDLER_CNTRL_STATE_MEMFAULTPENDED_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"BUSFAULTPENDED : ");
    vPrintRegisterBit(u32RegisterData & REG_SYSTEM_HANDLER_CNTRL_STATE_BUSFAULTPENDED_MASK);
    DBG_vPrintf(DBG_EXCEPTION,"USGFAULTPENDED : ");
    vPrintRegisterBit(u32RegisterData & REG_SYSTEM_HANDLER_CNTRL_STATE_USGFAULTPENDED_MASK);

}

PRIVATE void vPrintRegisterBit(uint32 u32BitSet)
{
    if(u32BitSet != 0)
    {
      DBG_vPrintf(DBG_EXCEPTION,"1\r\n");
    }
    else
    {
      DBG_vPrintf(DBG_EXCEPTION,"0\r\n");
    }

}
/****************************************************************************
 *
 * NAME: ZPS_u8GrabMutexLock
 *
 * DESCRIPTION:  Provides mutex protection for function re-entrancy
 *               
 *               
 *
 * RETURNS: uint8 
 *
 *
 ****************************************************************************/
uint8 ZPS_u8GrabMutexLock( void* hMutex , uint32* psIntStore )
{
    if( hMutex != NULL )
    {
    
        if(*( (bool_t*)(( (void* (*) (void))hMutex )())))
        {
          * ( (uint32*) (0xBADADD04) ) = 1;
        }
    }

    /* disable interrupts */
    MICRO_DISABLE_AND_SAVE_INTERRUPTS(*psIntStore);

    if( hMutex != NULL )
        (*( (bool_t*)(( (void* (*) (void))hMutex )()))) = TRUE;

    MICRO_RESTORE_INTERRUPTS(*psIntStore);

    return 0;

}


/****************************************************************************
 *
 * NAME: ZPS_u8ReleaseMutexLock
 *
 * DESCRIPTION:  Provides mutex protection for function re-entrancy
 *               
 *               
 *
 * RETURNS: uint8 
 *
 *
 ****************************************************************************/
uint8 ZPS_u8ReleaseMutexLock( void* hMutex , uint32* psIntStore )
{

    /* disable interrupts */
    MICRO_DISABLE_AND_SAVE_INTERRUPTS(*psIntStore);

    if( hMutex != NULL )
        (*( (bool_t*)(( (void* (*) (void))hMutex )()))) = FALSE;

    MICRO_RESTORE_INTERRUPTS(*psIntStore);
    return 0;
}


/****************************************************************************
 *
 * NAME: ZPS_eEnterCriticalSection
 *
 * DESCRIPTION:  Provides protection from function re-entrancy and interrupt
 *               pre-emption.
 *               
 *
 * RETURNS:
 *
 *
 ****************************************************************************/
PUBLIC uint8 ZPS_eEnterCriticalSection(void* hMutex, uint32* psIntStore)
{
    if( hMutex != NULL )
    {
    
        if(*( (bool_t*)(( (void* (*) (void))hMutex )())))
        {
          * ( (uint32*) (0xBADADD08) ) = 1;
        }
    }
    /* disable interrupts */
    MICRO_DISABLE_AND_SAVE_INTERRUPTS(*psIntStore);

    if( hMutex != NULL )
        (*( (bool_t*)(( (void* (*) (void))hMutex )()))) = TRUE;

    return 0;
}

/****************************************************************************
 *
 * NAME: ZPS_eExitCriticalSection
 *
 * DESCRIPTION:  Allows interrupt pre-emption and function re-entrancy.
 *               
 *
 * RETURNS:
 *
 *
 ****************************************************************************/
PUBLIC uint8 ZPS_eExitCriticalSection(void* hMutex , uint32* psIntStore)
{
    if( hMutex != NULL )
        (*( (bool_t*)(( (void* (*) (void))hMutex )()))) = FALSE;

    MICRO_RESTORE_INTERRUPTS(*psIntStore);

    return 0;
}



/****************************************************************************
 *
 * NAME:       u32Reverse
 */
/**
 * Reverses 32bit data
 *
 *
 * @param u32InWord  Input 32-bit data
 *
 * @return u32OutWord Output reversed 32- bit data
 *
 * @note
 *
 ****************************************************************************/
PUBLIC uint32 u32Reverse(uint32 u32InWord)
{
    uint32 u32OutWord;

    asm volatile ("REV %[reverse], %[input];"
                  : [reverse] "=r" (u32OutWord)
                  : [input]  "r"  (u32InWord)   );

    return u32OutWord;
}
/****************************************************************************
 *
 * NAME:       vSwipeEndian
 */
/**
 * Reverses 1282bit data between AESSW_Block_u and tsReg128
 *
 *
 * @param puBlock  128 bit data of type AESSW_Block_u
 *
 * @param psReg  128 bit data of type  tsReg128
 *
 * @param bBlockToReg  direction of converesion
 * 						1 = AESSW_Block_u to tsReg128
 *						0 = tsReg128 to AESSW_Block_u
 *
 * @return
 *
 * @note
 *
 ****************************************************************************/
PUBLIC void vSwipeEndian(AESSW_Block_u *puBlock, tsReg128 *psReg, bool_t bBlockToReg)
{
    int i=0;
    for (i = 0; i < 4 ; i++)
    {
        if(bBlockToReg)
            ((uint32*)psReg)[i] = u32Reverse((uint32)(puBlock->au32[i]));
        else
            puBlock->au32[i]  = u32Reverse(((uint32*)psReg)[i]);
	}
}

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

