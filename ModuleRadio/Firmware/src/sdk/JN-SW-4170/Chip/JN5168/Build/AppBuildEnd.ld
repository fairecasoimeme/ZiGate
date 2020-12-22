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

EXTERN(u32HeapStart);

/* Now building all code at once, so include vectors. MAC address is embedded
   in build for now */
SECTIONS
{

        .rodata :
        {
            *(.rodata*)
        } > flash

        .text :
        {
            *(.text*)
        } > flash

        _flash_end = ABSOLUTE(.);

        . = ORIGIN(ram);

        .data ALIGN(0x04) : AT ((LOADADDR(.text) + SIZEOF(.text) + 3) & ~ 3)
        {
            _ram_data_start = ABSOLUTE(.);
            *(.data*)
            *(.data.*)
            . = ALIGN (4);
            _ram_data_end = ABSOLUTE(.);
        } > ram

        .bss ALIGN (0x04) :
        {
            _bss_start = ABSOLUTE(.);
            *(.bss*)
            *(.bss.*)
            *(.scommon*)
            *(.scommon.*)
            *(COMMON)
            . = ALIGN (4);
            _bss_end = ABSOLUTE(.);
        } > ram

        /* reserve minimum heap size */
        .heap ALIGN (0x4) :
        {
            _heap_start = ABSOLUTE(.);
            . += __minimum_heap_size;
        } > ram

        .stack ABSOLUTE (ORIGIN(ram) + LENGTH(ram) - __stack_size):
        {
            /* make end of heap the bottom of the stack */
            _heap_end = ABSOLUTE(.);
            _stack_low_water_mark = ABSOLUTE(.);
            . += __stack_size;
        } > ram

        /* Test to check if the .data initialisation values in flash has gone
           past the end of the available space; the linker doesn't throw an
           error if that has happened. The following forces a byte to be
           stored after the .data initialisation values, but it is marked as
           NOLOAD so it never gets into the binary */
        .test (((LOADADDR(.text) + SIZEOF(.text) + 3) & ~ 3) + SIZEOF(.data)) (NOLOAD):
        {
            BYTE(0xff)
        } > flash
}

_flash_data_start = LOADADDR(.data);
_ram_data_len = (_ram_data_end - _ram_data_start + 3) & ~ 3;
_bss_len      = (_bss_end      - _bss_start      + 3) & ~ 3;
_image_len    = (_flash_end - _flash_start + _ram_data_len + 3) & ~ 3;
_ram_top      = ABSOLUTE(ORIGIN(ram)) + LENGTH(ram);
ram_top      = ABSOLUTE(ORIGIN(ram)) + LENGTH(ram);

_app_ram_start = 0x01001580; /* Page 5, word 8 (16-byte words, 16 words per page) */
PROVIDE(_heap_location  = u32HeapStart);
PROVIDE(heap_location  = u32HeapStart);

ENTRY(AppColdStart);

