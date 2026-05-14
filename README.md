# Fleranvandarsystem-unix---FNIX-
a unix like os called F-NIX or "Fleranvändarsystem - uNIX" meaning "multi-user unix"

## Features
- Written in C
- Multi-user system with root user (default password: aroot)
- Built-in commands: help, cc (placeholder), mkusr (add user)
- Architecture support: x86 and ARM (placeholders)
- Shell interface

## Building
To build FNIX kernel:
```
make ARCH=x86  # Creates fnix.elf for x86
make ARCH=X86  # also works
make ARCH=arm  # Creates fnix.elf and fnix.img for ARM (requires arm-linux-gnueabihf-* tools)
make ARCH=ARM  # also works
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
- Luckfox Lyra RK3506G2 (ARM Cortex-A7) Kinda works (have not tested fully)

## Running
For x86: Boot from ISO or `qemu-system-i386 -kernel fnix.elf`
Or use the provided script: `./run_fnix.sh` (requires Homebrew and QEMU)
For ARM: Boot on RPi with kernel.img 
## New Shell Commands
- `help` — list available commands
- `clear` — clear the screen
- `version` — show kernel version
- `whoami` — show current user
- `id` — show uid and gid
- `users` — list local users
- `mkusr` — add a new user (root only)
- `su <username>` — switch to another user
- `sudo <command>` — run a command as root
- `passwd` — change current password
- `logout` — logout to login prompt
- `exit` — exit the shell

## User and sudo
The system creates the default root account automatically. Use `root` with password `aroot` to log in, then use `mkusr` or `sudo mkusr` to add users.