#include <pl011.h>

#define CONSOLE_PORT 2

void kmain(void)
{
        serial_puts(CONSOLE_PORT, "Welcome to the Snowball!\n");
}
