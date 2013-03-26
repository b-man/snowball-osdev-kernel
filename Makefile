CROSS=arm-none-eabi

CC=$(CROSS)-gcc

CFLAGS=-Wall -Werror -Wno-unused-value -O2 -g -nostdlib -nostartfiles -ffreestanding -I .

CFLAGS+=-mcpu=cortex-a9 -marm

OBJS = \
    start.o \
    kmain.o \
    pl011.o \
    string.o

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
