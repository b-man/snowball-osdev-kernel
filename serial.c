/* generic serial driver */

#include <serial.h>

extern serial_driver interface;

void serial_putc(int c)
{
        if (c == '\n')
                interface.putc('\r');

        interface.putc(c);
}

void serial_puts(const char *str)
{
        while (*str)
                serial_putc(*str++);
}
