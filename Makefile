# Copyright (c) 2013, Brian McKenzie <mckenzba@gmail.com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, 
# are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright 
#     notice, this list of conditions and the following disclaimer.
#
#  2. Redistributions in binary form must reproduce the above copyright notice, 
#     this list of conditions and the following disclaimer in the documentation 
#     and/or other materials provided with the distribution.
#
#  3. Neither the name of the organization nor the names of its contributors may 
#     be used to endorse or promote products derived from this software without 
#     specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
# USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

CROSS=arm-none-eabi

CC=$(CROSS)-gcc

CFLAGS=-Wall -Werror -Wno-unused-value -g -O2 -nostdlib -nostartfiles -ffreestanding -I .

CFLAGS+=-mcpu=cortex-a9 -mthumb-interwork

OBJS = \
    config.o \
    start.o \
    kmain.o \
    pl011.o \
    string.o \
    serial.o

KERN=kernel

all: $(KERN)

%c.o:
	$(CC) $(CFLAGS) -c $< -o $@

%S.o:
	$(CC) -I. -c $< -o $@

$(KERN): $(OBJS)
	$(CROSS)-ld -T kern.ld $(OBJS) -o $(KERN).elf
	$(CROSS)-objdump -D $(KERN).elf > $(KERN).list
	$(CROSS)-objcopy $(KERN).elf -O srec $(KERN).srec
	$(CROSS)-objcopy $(KERN).elf -O binary $(KERN).bin

clean:
	rm -rf $(OBJS) *.bin *.elf *.list *.srec
