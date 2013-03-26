/* AP9500-specific definitions */

#ifndef AP9500_H
#define AP9500_H

/* AP9500-specific memory map defs */
#define AP9500_MMAP_BASE   0x80000000 /* peripheral base */

/* AP9500-specific serial port configuration */
#define PL011_PORT_LIST_CONFIG \
{								\
	(void *)(AP9500_MMAP_BASE + 0x0000), /* UART 0 */	\
	(void *)(AP9500_MMAP_BASE + 0x1000), /* UART 1 */	\
	(void *)(AP9500_MMAP_BASE + 0x7000), /* UART 2 */	\
}

#endif /* !AP9500_H */
