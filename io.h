/* general-purpose I/O operations */

#ifndef IO_H
#define IO_H

#include <types.h>

typedef volatile void addr_t;

/* TODO: move this into arm-specific io.h, have arch-neutral io.h include this */
#if defined(__arm__)

#define writeb(addr, val) __arm_writeb(addr, val)
#define writew(addr, val) __arm_writew(addr, val)
#define writel(addr, val) __arm_writel(addr, val)

#define readb(addr) __arm_readb(addr)
#define readw(addr) __arm_readw(addr)
#define readl(addr) __arm_readl(addr)

static inline void __arm_writeb(addr_t *addr, uint8_t val)
{
	asm volatile("strb %1, %0" : "+Qo" (*(volatile uint8_t *)(addr)) : "r" (val));
}

static inline void __arm_writew(addr_t *addr, uint16_t val)
{
	asm volatile("strh %1, %0" : "+Qo" (*(volatile uint16_t *)(addr)) : "r" (val));
}

static inline void __arm_writel(addr_t *addr, uint32_t val)
{
	asm volatile("str %1, %0" : "+Qo" (*(volatile uint32_t *)(addr)) : "r" (val));
}

static inline uint8_t __arm_readb(const addr_t *addr)
{
	uint8_t val;
	asm volatile("ldrb %1, %0" : "+Qo" (*(volatile uint8_t *)(addr)), "=r" (val));

	return val;
}

static inline uint16_t __arm_readw(const addr_t *addr)
{
	uint16_t val;
	asm volatile("ldrh %1, %0" : "+Qo" (*(volatile uint16_t *)(addr)), "=r" (val));

	return val;
}

static inline uint32_t __arm_readl(const addr_t *addr)
{
	uint32_t val;
	asm volatile("ldr %1, %0" : "+Qo" (*(volatile uint32_t *)(addr)), "=r" (val));

	return val;
}

#else
#error "unsupported architecture"
#endif

#endif /* !IO_H */
