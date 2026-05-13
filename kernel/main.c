#include "common.h"

// VGA text mode buffer
volatile unsigned char *vga = (unsigned char*)0xB8000;

void kprint(const char *str) {
    static int pos = 0;
    while (*str) {
        vga[pos * 2] = *str;
        vga[pos * 2 + 1] = 0x07; // White on black
        pos++;
        str++;
    }
}

void kernel_main() {
    kprint("FNIX Kernel starting...\n");
    kprint("Version: ");
    kprint(KERNEL_VERSION);
    kprint("\n");

    // Initialize subsystems
    init_kernel();

    // Start shell
    shell_main();

    kprint("Shutting down FNIX.\n");
}