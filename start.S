/* Kernel entry point for ARM
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

#include "asm.h"

.extern kmain

.section .init

/* reserve 512K for the stack */
.comm stack, 0x80000

.arm

ENTRY(_start)
    ldr pc, reset_target
    ldr pc, undef_target
    ldr pc, svc_target
    ldr pc, pabt_target
    ldr pc, dabt_target
    nop /* reserved */
    ldr pc, irq_target
    ldr pc, fiq_target

reset_target: .word reset_entry
undef_target: .word undefined_entry
svc_target:   .word supervisor_entry
pabt_target:  .word prefetch_entry
dabt_target:  .word data_entry
irq_target:   .word irq_entry
fiq_target:   .word fiq_entry

ENTRY(reset_entry)
    /* set the stack pointer */
    ldr  sp, =stack+0x80000

    /* clear the bss */
    ldr  r1, =__sbss   /* load bss start adress into r1*/
    ldr  r2, =__ebss   /* load bss end address into r2 */
    mov  r0, #0        /* store our zero in r0 */
    cmp  r1, r2        /* is the bss already cleared? */
    beq  2f            /* if it is clear, skip over to 2 */
1:  str  r0, [r1], #4  /* store our zero at address in r1 */
    cmp  r1, r2        /* is the bss cleared? */
    bls  1b            /* if not, branch back to 1 */
2:
    /* branch to kmain */
    b    kmain

ENTRY(undefined_entry)
    bx  lr

ENTRY(supervisor_entry)
    bx  lr

ENTRY(prefetch_entry)
    bx  lr

ENTRY(data_entry)
    bx  lr

ENTRY(irq_entry)
    bx  lr

ENTRY(fiq_entry)
    bx  lr
