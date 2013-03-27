/* generic serial driver */

#include <serial.h>

extern serial_driver serial_drv;

void serial_init(int port)
{
	serial_drv.init(port);
}

void serial_putc(int c)
{
        serial_drv.putc(c);
}

void serial_puts(const char *str)
{
        serial_drv.puts(str);
}
