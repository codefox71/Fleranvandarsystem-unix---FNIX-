CC_X86 = gcc
CC_ARM = arm-linux-gnueabihf-gcc
AS_X86 = as
AS_ARM = arm-linux-gnueabihf-as
LD_X86 = ld
LD_ARM = arm-linux-gnueabihf-ld
OBJCOPY_ARM = arm-linux-gnueabihf-objcopy

ARCH ?= x86
ARCH_LC := $(shell printf "%s" "$(ARCH)" | tr '[:upper:]' '[:lower:]')

ifeq ($(ARCH_LC),arm)
CC = $(CC_ARM)
AS = $(AS_ARM)
LD = $(LD_ARM)
OBJCOPY = $(OBJCOPY_ARM)
CFLAGS = -ffreestanding -O2 -Iinclude -Wall -Wextra
LDFLAGS = -T linker.ld
BOOT_SRC = boot/arm_boot.s
else
CC = $(CC_X86)
AS = $(AS_X86)
LD = $(LD_X86)
CFLAGS = -m32 -ffreestanding -O2 -Iinclude -Wall -Wextra
LDFLAGS = -m elf_i386 -T linker.ld
BOOT_SRC = boot/boot.s
endif

# Source files
KERNEL_SRC = kernel/main.c kernel/init.c kernel/syscall.c kernel/graphics.c kernel/elf.c kernel/scheduler.c kernel/vfs.c
ARCH_SRC = arch/$(ARCH_LC)/boot.c arch/$(ARCH_LC)/interrupts.c arch/$(ARCH_LC)/idt.c
SHELL_SRC = shell/shell.c shell/commands.c
LIB_SRC = lib/string.c

# Object files
BOOT_OBJ = $(BOOT_SRC:.s=.o)
KERNEL_OBJ = $(KERNEL_SRC:.c=.o)
ARCH_OBJ = $(ARCH_SRC:.c=.o)
SHELL_OBJ = $(SHELL_SRC:.c=.o)
LIB_OBJ = $(LIB_SRC:.c=.o)

# Targets
all: fnix.elf

fnix.elf: $(BOOT_OBJ) $(KERNEL_OBJ) $(ARCH_OBJ) $(SHELL_OBJ) $(LIB_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

ifeq ($(ARCH_LC),arm)
fnix.img: fnix.elf
	$(OBJCOPY) -O binary $< $@
endif

%.o: %.s
ifeq ($(ARCH),arm)
	$(AS) -o $@ $<
else
	$(AS) --32 -o $@ $<
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BOOT_OBJ) $(KERNEL_OBJ) $(ARCH_OBJ) $(SHELL_OBJ) $(LIB_OBJ) fnix.elf fnix.img

.PHONY: all clean