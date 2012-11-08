/* rammap */

ENTRY(_start)

MEMORY
{
    kern : ORIGIN = 0x00100000, LENGTH = 1M
}

SECTIONS
{
    .text : { start.o(.text) *(.text*) } > kern
    .data : { *(.data) } > kern
    .bss : { *(.bss) } > kern
}
