/* general-purpose I/O operations */

#include <types.h>

#ifndef IO_H
#define IO_H

/* TODO: move this into arm-specific io.h, have arch-neutral io.h include this */

#if defined(__arm__)

/* macros used to read from and write to memory locations */
#define __arm_write8(addr, val) (*(volatile uint8_t *)(addr) = (val))
#define __arm_write32(addr, val) (*(volatile uint32_t *)(addr) = (val))

#define __arm_read8(addr) (*(volatile uint8_t *)(addr))
#define __arm_read32(addr) (*(volatile uint32_t *)(addr))

#define write8(addr, val) __arm_write8(addr, val)
#define write32(addr, val) __arm_write32(addr, val)

#define read8(addr) __arm_read8(addr)
#define read32(addr) __arm_read32(addr)

#else
#error "unsupported architecture"
#endif

#endif /* !IO_H */
