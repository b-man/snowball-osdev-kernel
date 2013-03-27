/* generic serial driver - header file */

#ifndef SERIAL_H
#define SERIAL_H

/* serial driver interface */
typedef struct {
	void (*init)(int port);
	void (*putc)(int c);
	void (*puts)(const char *str);
} serial_driver;

/* serial driver prototypes */
void serial_init(int port);
void serial_putc(int c);
void serial_puts(const char *str);

#endif
