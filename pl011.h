/* PL011 serial driver - prototypes and definitions
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

/* PL011 port configuration structure */
typedef struct {
	uint8_t  mode; /* uart mode */
	uint32_t baud; /* baud rate */
	addr_t  *base; /* uart base address */
} pl011_cfg;

/* PL011 driver prototypes */
void pl011_init(int port);
void pl011_putc(int port, int c);
void pl011_puts(int port, const char *str);

/* PL011 registers */
#define UART_DR       0x00
#define UART_RSR_ECR  0x04
#define UART_DMAWM    0x08
#define UART_TIMEOUT  0x0C
#define UART_FR       0x18
#define UART_LCRH_RX  0x1C
#define UART_ILPR     0x20
#define UART_IBRD     0x24
#define UART_FBRD     0x28
#define UART_LCRH_TX  0x2C
#define UART_CR       0x30
#define UART_IFLS     0x34
#define UART_IMSC     0x38
#define UART_RIS      0x3C
#define UART_MIS      0x40
#define UART_ICR      0x44
#define UART_DMACR    0x48
#define UART_XFCR     0x50
#define UART_XON1     0x54
#define UART_XON2     0x58
#define UART_XOFF1    0x5C
#define UART_XOFF2    0x60
#define UART_ITCR     0x80
#define UART_ITIP     0x84
#define UART_ITOP     0x88
#define UART_YDR      0x8C
#define UART_ABCR     0x100
#define UART_ABSR     0x104
#define UART_ABFMT    0x108
#define UART_ABDR     0x150
#define UART_ABDFR    0x154
#define UART_ABMR     0x158
#define UART_ABIMSC   0x15C
#define UART_ABRIS    0x160
#define UART_ABMIS    0x164
#define UART_ABICR    0x168
#define UART_IDPROD   0xFD8
#define UART_IDPROV   0xFDC
#define UART_PERIPH0  0xFE0
#define UART_PERIPH1  0xFE4
#define UART_PERIPH2  0xFE8
#define UART_PERIPH3  0xFEC
#define UART_PCELLID0 0xFF0
#define UART_PCELLID1 0xFF4
#define UART_PCELLID2 0xFF8
#define UART_PCELLID3 0xFFC

/* PL011 status bits */
#define UART_TXFE_BIT 0x80
#define UART_RXFF_BIT 0x40
#define UART_TXFF_BIT 0x20
#define UART_RXFE_BIT 0x10

#endif /* !PL011_H */
