/* Pl011 serial driver - prototypes and definitions
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
void pl011_puts(int port, const char *str);

/* UART control registers */
#define UART_FLAG_REG 0x18
#define UART_RSR_ECR  0x04

/* UART status bits */
#define UART_TXFE_BIT 0x80
#define UART_RXFF_BIT 0x40
#define UART_TXFF_BIT 0x20
#define UART_RXFE_BIT 0x10

#endif /* !PL011_H */
