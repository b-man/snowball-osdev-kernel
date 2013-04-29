/* PL011 serial driver
 *
 * Copyright (c) 2013, Brian McKenzie <mckenzba@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3. Neither the name of the organization nor the names of its contributors may
 *     be used to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdbool.h>
#include <serial.h>
#include <pl011.h>
#include <types.h>
#include <io.h>

/* pull in uart configuration */
extern pl011_cfg pl011_config[32];

/* which port to use */
static int port_select;

void pl011_init(int port)
{
	int div, frac, rem;

	pl011_cfg *config = &pl011_config[port];

	addr_t *base = config->base;
	uint32_t baud = config->baud;
	uint32_t clock = config->clock;

	/* clear interrupts and turn off the uart */
	writel((base + UART_ICR), UART_ICR_DISA);
	writel((base + UART_CR), UART_CR_DISA);

	/* compute the integer and fraction divisor */
	if (readl(base + UART_CR) & UART_CR_OSVFACT) {
		div = clock / (8 * baud);
		rem = clock % (8 * baud);
		frac = ((8 * rem / baud) >> 1);
		frac += ((8 * rem / baud) & 1);
	} else {
		div = clock / (16 * baud);
		rem = clock % (16 * baud);
		frac = ((8 * rem / baud) >> 1);
		frac += ((8 * rem / baud) & 1);
	}

	/* set the integer and fraction divisor */
	writel((base + UART_IBRD), div);
	writel((base + UART_FBRD), frac);

	/* turn on the uart */
	writel((base + UART_LCRH_RX), (UART_LCRH_8WL | UART_LCRH_RXFE));
	writel((base + UART_LCRH_TX), (UART_LCRH_8WL | UART_LCRH_TXFE));
	writel((base + UART_CR), (UART_CR_UEN | UART_CR_RXE | UART_CR_TXE));

	/* set rx and tx interrupt masks */
	pl011_rx_interrupt_mask(port, TRUE);
	pl011_tx_interrupt_mask(port, TRUE);

	port_select = port;
}

void pl011_rx_interrupt_mask(int port, bool state)
{
	pl011_cfg *config = &pl011_config[port];
	addr_t *base = config->base;

	if (state == TRUE)
		writel((base + UART_IMSC), (UART_IMSC_RXMS));
	else
		writel((base + UART_IMSC), (UART_IMSC_RXMS & ~UART_IMSC_RXMS));
}

void pl011_tx_interrupt_mask(int port, bool state)
{
	pl011_cfg *config = &pl011_config[port];
	addr_t *base = config->base;

	if (state == TRUE)
		writel((base + UART_IMSC), (UART_IMSC_TXMS));
	else
		writel((base + UART_IMSC), (UART_IMSC_TXMS & ~UART_IMSC_TXMS));
}

void pl011_putc(int port, int c)
{
	pl011_cfg *config = &pl011_config[port];
	addr_t *base = config->base;

	while (readl(base + UART_FR) & UART_TXFF_BIT)
		;

	writel(base, c);
}

void pl011_puts(int port, const char *str)
{
	while (*str) {
		if (*str == '\n')
			pl011_putc(port, '\r');

		pl011_putc(port, *str++);
	}
}

static void uart_putc(int c)
{
	if (c == '\n')
		pl011_putc(port_select, '\r');

	pl011_putc(port_select, c);
}

static void uart_puts(const char *str)
{
	pl011_puts(port_select, str);
}

/* register this driver */
serial_driver serial_drv = {
	pl011_init,
	uart_putc,
	uart_puts,
};
