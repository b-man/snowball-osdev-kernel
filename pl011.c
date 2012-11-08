/* pl011 serial driver */

#include <pl011.h>
#include <io.h>

void pl011_putc(int c)
{
        while (read32(UART_PORT(UART2 + UART_FLAG_REG)) & UART_TXFF_BIT)
                ;

        write32(UART_PORT(UART2), c);
}

void serial_putc(int c)
{
        if (c == '\n')
                pl011_putc('\r');

        pl011_putc(c);
}

void serial_puts(const char *str)
{
        while (*str)
                serial_putc(*str++);
}
