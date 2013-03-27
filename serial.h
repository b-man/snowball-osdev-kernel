/* generic serial driver - header file */

#ifndef SERIAL_H
#define SERIAL_H

typedef struct {
	void (*putc)(int c);
	void (*puts)(const char *str);
} serial_driver;

void serial_putc(int c);
void serial_puts(const char *str);

#endif
