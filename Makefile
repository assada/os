CFLAGS = -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -Wall -Wextra
LDFLAGS = -ffreestanding -nostdlib -lgcc
ASFLAGS =
CC = i686-elf-gcc
AS = i686-elf-as
LD = i686-elf-gcc
GRUB_FILE = grub-file
GRUB_MKRESCUE = grub-mkrescue
KERNEL = deados.bin
ISO = deados.iso

SOURCES_C = kernel.c tty.c idt.c timer.c io.c vga.c gdt.c sys.c irq.c isr.c keyboard.c shell.c string.c user_space.c syscall.c rtc.c
SOURCES_ASM = boot.s idt_load.s gdt_flush.s tss_flush.s irq_flush.s isr_flush.s
OBJECTS = $(SOURCES_ASM:.s=.o) $(SOURCES_C:.c=.o)

ISO_DIR = isodir
GRUB_DIR = $(ISO_DIR)/boot/grub

.PHONY: all clean iso

all: $(ISO)

$(KERNEL): $(OBJECTS) linker.ld
	$(LD) -T linker.ld -o $(KERNEL) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

iso: $(ISO)

$(ISO): $(KERNEL) grub.cfg
	mkdir -p $(GRUB_DIR)
	cp $(KERNEL) $(ISO_DIR)/boot/$(KERNEL)
	cp grub.cfg $(GRUB_DIR)/grub.cfg
	$(GRUB_MKRESCUE) -o $(ISO) $(ISO_DIR)

check-multiboot: $(KERNEL)
	$(GRUB_FILE) --is-x86-multiboot $(KERNEL) && echo "multiboot confirmed" || echo "the file is not multiboot"

clean:
	rm -f $(OBJECTS) $(KERNEL) $(ISO)
	rm -rf $(ISO_DIR)
