CC=arm-none-eabi-gcc

CFLAGS=-Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -I .

# CFLAGS+=-march=armv7-a -mcpu=cortex-a9 -marm # -mfpu=vfpv3 -mfloat-abi=hard
CFLAGS+=-mcpu=cortex-a9 -marm

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
	arm-none-eabi-ld -T linker.ld $(OBJS) -o kern.elf
	arm-none-eabi-objdump -D kern.elf > kern.list
	arm-none-eabi-objcopy kern.elf -O srec kern.srec
	arm-none-eabi-objcopy kern.elf -O binary kern.bin

clean:
	rm -rf $(OBJS) *.bin *.elf *.list *.srec
