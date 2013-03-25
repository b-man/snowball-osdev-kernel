CROSS=arm-none-eabi

CC=$(CROSS)-gcc

CFLAGS=-Wall -Werror -Wno-unused-value -O2 -nostdlib -nostartfiles -ffreestanding -I .

# CFLAGS+=-march=armv7-a -mcpu=cortex-a9 -marm # -mfpu=vfpv3 -mfloat-abi=hard
CFLAGS+=-mcpu=cortex-a9 -marm -g

OBJS = \
    start.o \
    kmain.o \
    pl011.o \
    string.o

all: kernel

%c.o:
	$(CC) $(CFLAGS) -c $< -o $@

%S.o:
	$(CC) -I. -c $< -o $@

kernel: $(OBJS)
	$(CROSS)-ld -T linker.ld $(OBJS) -o kern.elf
	$(CROSS)-objdump -D kern.elf > kern.list
	$(CROSS)-objcopy kern.elf -O srec kern.srec
	$(CROSS)-objcopy kern.elf -O binary kern.bin

clean:
	rm -rf $(OBJS) *.bin *.elf *.list *.srec
