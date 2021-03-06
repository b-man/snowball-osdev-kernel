/* Linker script for ARM kernel
 *
 * Copyright (c) 2013, Brian McKenzie <mckenzba@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3. Neither the name of the organization nor the names of its contributors may
 *     be used to endorse or promote products derived from this software without 
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

TARGET("elf32-littlearm")
OUTPUT_FORMAT("elf32-littlearm")

ENTRY(_start)

MEMORY
{ 
    kern (rwx) : ORIGIN = 0x00100000, LENGTH = 1M
    kstack (rwx) : ORIGIN = 0x00200000, LENGTH = 64K
}

SECTIONS
{
    .init : {
        KEEP(*(.init))
    } > kern
    .text : {
        *(.text) 
    } > kern
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > kern
    .data : {
        *(.data)
    } > kern
    .bss : {
        __sbss = .;
        *(.bss)
        __ebss = .;
    } > kern

    .stack : {
        __stack_start = .;
        __stack_size = 64K;
        . = . + __stack_size;
        . = ALIGN(8);
        __stack_end = .;
    } > kstack

    /DISCARD/ : {
        *(.comment .note)
    }
}
