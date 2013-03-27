/* AP9500-specific configuration information */

#include <ap9500.h>
#include <pl011.h>

/* serial port configuration */
pl011_cfg pl011_config[3] = {
	{ /* UART0 */
        	.mode = 0b00000000,
        	.baud = 115200,
		.base = (void *)(AP9500_MMAP_BASE + 0x0000),
	},
	{ /* UART1 */
		.mode = 0b00000000,
		.baud = 115200,
		.base = (void *)(AP9500_MMAP_BASE + 0x1000),
	},
	{ /* UART2 */
		.mode = 0b00000000,
		.baud = 115200,
		.base = (void *)(AP9500_MMAP_BASE + 0x7000),
	},
};
