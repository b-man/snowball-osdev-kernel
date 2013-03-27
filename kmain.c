#include <serial.h>

void kmain(void)
{
	serial_init(2);
        serial_puts("Welcome to the Snowball!\n");
	serial_puts("\tThis is a test tab\n");
	serial_puts("Inserting multiple newlines..\n\n\n\n\n\n...Done!\n");
	serial_puts("ASCII test:\nabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-=~!@#$%^&*()_+\";:'[]{}\\|,./<>?\nDone!\n\r");
}
