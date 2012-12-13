/* rammap */

TARGET("elf32-littlearm")
OUTPUT_FORMAT("elf32-littlearm")

ENTRY(_start)

MEMORY
{ 
    kern (rwx) : ORIGIN = 0x00100000, LENGTH = 1M
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

    /DISCARD/ : {
        *(.comment .note)
    }
}
