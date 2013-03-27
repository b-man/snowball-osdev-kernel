#include <serial.h>
#include <pl011.h>

void kmain(void)
{
	pl011_init(2);
        serial_puts("Welcome to the Snowball!\n");
}
