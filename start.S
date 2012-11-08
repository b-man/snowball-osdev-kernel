#include "asm.h"

.extern kmain

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
    ldr  sp, =stack+0x80000
    b    kmain @ branch to kernel main

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
