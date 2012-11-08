/* pl011 serial driver - header file */

#include <ap9500.h>

#ifndef PL011_H
#define PL011_H

/* pl011 driver prototypes */
void pl011_putc(int c);
void serial_putc(int c);
void serial_puts(const char *str);

/* list of available UARTs */
#define UART0 0x0000
#define UART1 0x1000
#define UART2 0x7000

/* port selection macro */
#define UART_PORT(uart) (AP9500_MMAP_BASE + uart)

/* UART control registers */
#define UART_FLAG_REG 0x18
#define UART_RSR_ECR  0x04

/* UART status bits */
#define UART_TXFE_BIT 0x80
#define UART_RXFF_BIT 0x40
#define UART_TXFF_BIT 0x20
#define UART_RXFE_BIT 0x10

#endif /* !PL011_H */
