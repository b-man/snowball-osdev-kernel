/* pl011 serial driver */

#include <serial.h>
#include <pl011.h>
#include <io.h>

/* pull in uart configuration */
extern pl011_cfg pl011_config[32];

/* which port to use */
static int port_select;

void pl011_init(int port)
{
	port_select = port;
	return;
}

void pl011_putc(int port, int c)
{
	addr_t *uart_base = pl011_config[port].base;

	while (readl((uart_base + UART_FLAG_REG)) & UART_TXFF_BIT)
		;

	writel(uart_base, c);
}

void pl011_puts(int port, const char *str)
{
	while (*str) {
		if (*str == '\n')
			pl011_putc(port, '\r');

		pl011_putc(port, *str++);
	}
}

static void uart_putc(int c)
{
	if (c == '\n')
		pl011_putc(port_select, '\r');

	pl011_putc(port_select, c);
}

static void uart_puts(const char *str)
{
	pl011_puts(port_select, str);
}

/* register this driver */
serial_driver serial_drv = {
	pl011_init,
	uart_putc,
	uart_puts,
};
