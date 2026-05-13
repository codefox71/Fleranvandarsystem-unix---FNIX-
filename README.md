# Fleranvandarsystem-unix---FNIX-
a unix like os called F-NIX or "Fleranvändarsystem - uNIX" meaning "multi-user unix"

## Features
- Written in C
- Multi-user system with root user (default password: root@123)
- Built-in commands: help, cc (placeholder), mkusr (add user)
- Architecture support: x86 and ARM (placeholders)
- Shell interface

## Building
To build FNIX kernel:
```
make ARCH=x86  # Creates fnix.elf for x86
make ARCH=arm  # Creates fnix.elf and fnix.img for ARM (requires arm-linux-gnueabihf-* tools)
```

## Creating Bootable Images
### For x86 (ISO):
1. Install grub-pc-bin or similar.
2. Create directory structure:
   ```
   mkdir -p iso/boot/grub
   cp fnix.elf iso/boot/
   ```
3. Create iso/boot/grub/grub.cfg:
   ```
   set timeout=0
   set default=0
   menuentry "FNIX" {
       multiboot /boot/fnix.elf
   }
   ```
4. Run: `grub-mkrescue -o fnix.iso iso/`

### For ARM (RPi or Luckfox Lyra):
Copy fnix.img to SD card as kernel.img, along with bootcode.bin, etc.

## Supported Hardware
- x86 PCs (via GRUB)
- Raspberry Pi 400 (ARM)
- Luckfox Lyra RK3506G2 (ARM Cortex-A7)

## Running
For x86: Boot from ISO or `qemu-system-i386 -kernel fnix.elf`
Or use the provided script: `./run_fnix.sh` (requires Homebrew and QEMU)
For ARM: Boot on RPi with kernel.img 
