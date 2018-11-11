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
 *
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ***************************************************************************/

/* Now building all code at once, so include vectors. MAC address is embedded
   in build for now */


EXTERN(vException_BusError)
EXTERN(vException_UnalignedAccess)
EXTERN(vException_IllegalInstruction)
EXTERN(vException_SysCall)
EXTERN(vException_Trap)
EXTERN(vException_StackOverflow)
EXTERN(_exception_external_interrupt)
PROVIDE(vException_BusError           = restore_state);
PROVIDE(vException_UnalignedAccess    = restore_state);
PROVIDE(vException_IllegalInstruction = restore_state);
PROVIDE(vException_SysCall            = restore_state);
PROVIDE(vException_Trap               = restore_state);
PROVIDE(vException_StackOverflow      = restore_state);

SECTIONS
{

        . = ABSOLUTE(_exception_vsr_table);
        
        .vsr_table :
        {
        LONG(ABSOLUTE(vException_BusError))
        LONG(ABSOLUTE(vException_UnalignedAccess))
        LONG(ABSOLUTE(vException_IllegalInstruction))
        LONG(ABSOLUTE(vException_SysCall))
        LONG(ABSOLUTE(vException_Trap))
        LONG(ABSOLUTE(vException_StackOverflow))
        } > flash

        .vsr_handlers :
        {
            KEEP(*(.vsr_handlers))
        } > flash

}
