/* pl011 serial driver - header file */

#include <ap9500.h>

#ifndef PL011_H
#define PL011_H

/* pl011 driver prototypes */
void serial_putc(int port, int c);
void serial_puts(int port, const char *str);

/* UART control registers */
#define UART_FLAG_REG 0x18
#define UART_RSR_ECR  0x04

/* UART status bits */
#define UART_TXFE_BIT 0x80
#define UART_RXFF_BIT 0x40
#define UART_TXFF_BIT 0x20
#define UART_RXFE_BIT 0x10

#endif /* !PL011_H */
