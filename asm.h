#ifndef ASM_H
#define ASM_H

/* assembly function entry */
#define ENTRY(x) \
        .text; .align 0; .type x,#function; .globl x; x:

#endif /* !ASM_H */
