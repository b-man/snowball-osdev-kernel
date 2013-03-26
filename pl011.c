/* pl011 serial driver */

#include <pl011.h>
#include <io.h>

static volatile void *pl011_port[] = PL011_PORT_LIST_CONFIG;

static void pl011_putc(int port, int c)
{
        while (readl((pl011_port[port] + UART_FLAG_REG)) & UART_TXFF_BIT)
                ;

        writel(pl011_port[port], c);
}

void serial_putc(int port, int c)
{
        if (c == '\n')
                pl011_putc(port, '\r');

        pl011_putc(port, c);
}

void serial_puts(int port, const char *str)
{
        while (*str)
                serial_putc(port, *str++);
}
