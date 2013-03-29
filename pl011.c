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

#include <serial.h>
#include <pl011.h>
#include <io.h>

/* pull in uart configuration */
extern pl011_cfg pl011_config[32];

/* which port to use */
static int port_select;

void pl011_init(int port)
{
	addr_t *base = pl011_config[port].base;

	/* clear interrupts and turn off the uart */
	writel((base + UART_ICR), UART_ICR_DISA);
	writel((base + UART_CR), UART_CR_DISA);

	/* set the integer divisor and fraction divisor */
	writel((base + UART_IBRD), 0x14); /* hardcode to 115200 for now */
	writel((base + UART_FBRD), 0x35); /* http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183f/I49493.html for formula */

	/* turn on the uart */
	writel((base + UART_LCRH_RX), (UART_LCRH_8WL | UART_LCRH_RXFE));
	writel((base + UART_LCRH_TX), (UART_LCRH_8WL | UART_LCRH_TXFE));
	writel((base + UART_CR), (UART_CR_UEN | UART_CR_RXE | UART_CR_TXE | UART_CR_RTS));

	/* enable rx and tx interrupts */
	writel((base + UART_IMSC), (UART_IMSC_RXMS | UART_IMSC_TXMS));

	port_select = port;
}

void pl011_putc(int port, int c)
{
	addr_t *base = pl011_config[port].base;

	while (readl((base + UART_FR)) & UART_TXFF_BIT)
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
