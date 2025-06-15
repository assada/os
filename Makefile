ARCH ?= x86
ARCH_DIR = arch/$(ARCH)
KERNEL_DIR = kernel
USER_DIR = user

CFLAGS = -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -Wall -Wextra -I$(KERNEL_DIR) -I$(ARCH_DIR) -I$(ARCH_DIR)/include -I$(USER_DIR) -Iinclude
LDFLAGS = -ffreestanding -nostdlib -lgcc
ASFLAGS =
CC = i686-elf-gcc
AS = i686-elf-as
LD = i686-elf-gcc
GRUB_FILE = grub-file
GRUB_MKRESCUE = grub-mkrescue
KERNEL = deados.bin
ISO = deados.iso

SOURCES_C := $(wildcard $(KERNEL_DIR)/*.c) $(wildcard $(ARCH_DIR)/*.c) $(wildcard $(USER_DIR)/*.c)
SOURCES_ASM := $(wildcard $(ARCH_DIR)/*.s)
OBJECTS = $(SOURCES_ASM:.s=.o) $(SOURCES_C:.c=.o)
	
ISO_DIR = isodir
GRUB_DIR = $(ISO_DIR)/boot/grub
	
.PHONY: all clean iso docker-build docker-make

all: $(ISO)
	
$(KERNEL): $(OBJECTS) linker.ld
	$(LD) -T linker.ld -o $@ $(OBJECTS) $(LDFLAGS)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

iso: $(ISO)

$(ISO): $(KERNEL) grub.cfg
	mkdir -p $(GRUB_DIR)
	cp $(KERNEL) $(ISO_DIR)/boot/$(KERNEL)
	cp grub.cfg $(GRUB_DIR)/grub.cfg
	$(GRUB_MKRESCUE) -o $@ $(ISO_DIR)

check-multiboot: $(KERNEL)
	$(GRUB_FILE) --is-x86-multiboot $(KERNEL) && echo "multiboot confirmed" || echo "the file is not multiboot"

clean:
	rm -f $(OBJECTS) $(KERNEL) $(ISO)
	rm -rf $(ISO_DIR)

# Docker helpers remain unchanged
docker-build:
	docker build --progress=plain -t deados_builder .
		
docker-make:
	docker run -it -v $(shell pwd):/var/lib/deados deados_builder bash -c "cd /var/lib/deados && make"
