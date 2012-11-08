/* general-purpose I/O operations */

#ifndef IO_H
#define IO_H

#if defined(__arm__)

/* macros used to read from and write to memory locations */
#define __arm_write8(addr, val) (*(volatile unsigned char *)(addr) = (val))
#define __arm_write32(addr, val) (*(volatile unsigned int *)(addr) = (val))

#define __arm_read8(addr) (*(volatile unsigned char *)(addr))
#define __arm_read32(addr) (*(volatile unsigned int *)(addr))

#else
#error "unsupported architecture"
#endif

/* TODO: move this into arch-neutral io.h */

#define write8(addr, val) __arm_write8(addr, val)
#define write32(addr, val) __arm_write32(addr, val)

#define read8(addr) __arm_read8(addr)
#define read32(addr) __arm_read32(addr)

#endif /* !IO_H */
