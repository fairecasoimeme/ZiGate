/****************************************************************************
 *
 * MODULE:
 *
 * COMPONENT:          $RCSfile: $
 *
 * VERSION:            $Name:  $
 *
 * REVISION:           $Revision: 8954 $
 *
 * DATED:              $Date: 2012-04-16 13:01:29 +0100 (Mon, 16 Apr 2012) $
 *
 * STATUS:             $State: $
 *
 * AUTHOR:             IDM
 *
 * DESCRIPTION:
 *
 * LAST MODIFIED BY:   $Author: nxp33194 $
 *                     $Modtime: $
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
 *
 ****************************************************************************/
/*
    Other than by continuously monitoring the stack pointer which is impractical,
    the simplest method to see the extent of stack usage is to fill the unused stack
    area with a known pattern then look for the watermark level that the stack has
    overwritten.



    NOTE: The stack is used by both the application AND the network layers
          ( 802.15.4, ZigBee and JenNet), so the stack size can be larger
          than expected.



                         --------------------------  STACK_START_ADDR
                        |       Stack grows down   |
                        |         |                |
                        |         V                |<------  u32CurrentMeasure
                        |                          |
                         ..........................   pu32MonitorStartAddr
                        |                            |
                        |                            |
                        |                            |
                        |                            |
                        |      Fill Pattern        |<-------  u32PeakMeasure
                        |      Fill Pattern        |
                        |      Fill Pattern        |
                        |      Fill Pattern        |
                        |      Fill Pattern        |
                        |      Fill Pattern        |
                        |      Fill Pattern        |
                        |      Fill Pattern        |
                        |      Fill Pattern        |
                        |      Fill Pattern        |
                         --------------------------   pu32StackEndAddr
                        |      Application         |
                        |        BSS               |
                        |                          |
                         --------------------------
                        |                          |
                        |                          |
                        |       Application        |
                        |        Code               |
                        |                          |
                        |                          |
                        |                          |
                        |                          |
                        |                          |
                        |                          |
                         --------------------------



Example use
------------

    Init
    -----
    Initialise the stack measurements as early as possible in the code:
    vInitStackMeasure();



    To display the stack usage:
    ---------------------------

    tsStackInfo sStackInfo;

    vGetStackMeasure(&sStackInfo);
    vUtils_Debug("Stack Usage");
    vUtils_DisplayMsg("Total:",sStackInfo.u32TotalSize);
    vUtils_DisplayMsg("Used :",sStackInfo.u32CurrentMeasure);
    vUtils_DisplayMsg("Peak :",sStackInfo.u32PeakMeasure);



*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <jendefs.h>

#include "stackMeasure.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define PATTERN                               0xFACEFACE

/* default to the JN5148 */
#define STACK_START_ADDR                    0x04008000


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
/* Pointer to the CPU stack threshold */
PRIVATE uint32    u32MonitorStartAddr;
PRIVATE uint32    u32StackEndAddr;

/* BSS section dimension, taken from linker file */

//extern void *__stack_low_water_mark

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: vInitStackMeasure
 *
 * DESCRIPTION:
 * initialises from the end of the bss... up to just below the stack
 * with a fill pattern
 *
 *
 * RETURNS: void
 *
 ****************************************************************************/
PUBLIC void vInitStackMeasure( void )
{
    uint32 u32StackPtr;
    PRIVATE uint32  *pu32WorkingAddr;
    //extern void *_heap_end;
    extern void *_stack_low_water_mark;


    // get the current stack pointer
    asm("l.addi %0,r1,%1" :"=r"(u32StackPtr): "i"(0));

    // top of the stack
    u32StackEndAddr = (((uint32)((&_stack_low_water_mark) + 4)) & 0xfffffffc);

    // set the start point for the pattern filled stack area
    u32MonitorStartAddr = u32StackPtr - 4; // fill from just above

    pu32WorkingAddr = (uint32 *)u32StackEndAddr;

    // write the pattern
    while( (uint32)pu32WorkingAddr++ < u32MonitorStartAddr )
    {
        // initialise stack RAM as not used with a watermark
        *pu32WorkingAddr = PATTERN;
    }
}


/****************************************************************************
 *
 * NAME: vGetStackMeasure
 *
 * DESCRIPTION:
 * searches for the initialied value in the watermarked stack RAM area
 *
 * RETURNS: loads the stack data structure
 *                uint32    u32TotalSize        total space available
 *                uint32    u32PeakMeasure      peak stack usage ( watermark)
 *                uint32    u32CurrentMeasure    current stack usage
 *
 *            These values are uninitialised if vInitStackMeasure() is not called
 *
 ****************************************************************************/
PUBLIC void vGetStackMeasure( tsStackInfo *psStackInfo )
{
    uint32 u32StackPtr;
    PRIVATE uint32  *pu32WorkingAddr;

    // if init has not been called just return, we cannot measure
    if(u32StackEndAddr==0) return;

    // get the current stack pointer
    asm("l.addi %0,r1,%1" :"=r"(u32StackPtr): "i"(0));

    // measure sizes
    psStackInfo->u32CurrentMeasure = STACK_START_ADDR - u32StackPtr;
    psStackInfo->u32TotalSize = STACK_START_ADDR - u32StackEndAddr;

    // point to the end of the bss section.. end of application RAM
    pu32WorkingAddr = (uint32 *)u32StackEndAddr;

    // pre load the watermark
    psStackInfo->u32PeakMeasure = psStackInfo->u32CurrentMeasure;

    // search for the watermark
    while( (uint32)pu32WorkingAddr++ < u32MonitorStartAddr )
    {
        // check stack RAM for use... and return the address if it has
        if( (*pu32WorkingAddr) != PATTERN )
        {
            // calc stack size and return
            psStackInfo->u32PeakMeasure =  ( STACK_START_ADDR - (uint32)pu32WorkingAddr );
            return;
        }
    }
}


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
