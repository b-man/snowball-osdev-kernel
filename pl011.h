/* pl011 serial driver - header file */

#ifndef PL011_H
#define PL011_H

#include <ap9500.h>
#include <types.h>
#include <io.h>

/* pl011 port configuration structure */
typedef struct {
	uint8_t  mode; /* uart mode */
	uint32_t baud; /* baud rate */
	addr_t  *base; /* uart base address */
} pl011_cfg;

/* pl011 driver prototypes */
void pl011_init(int port);
void pl011_putc(int port, int c);
void serial_putc(int c);
void serial_puts(const char *str);

/* UART control registers */
#define UART_FLAG_REG 0x18
#define UART_RSR_ECR  0x04

/* UART status bits */
#define UART_TXFE_BIT 0x80
#define UART_RXFF_BIT 0x40
#define UART_TXFF_BIT 0x20
#define UART_RXFE_BIT 0x10

#endif /* !PL011_H */
