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
