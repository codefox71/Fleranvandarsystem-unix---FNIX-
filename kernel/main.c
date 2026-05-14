#include "common.h"

// VGA text mode buffer
volatile unsigned char *vga = (volatile unsigned char*)0xB8000;
int vga_pos = 0;

void kprint(const char *str) {
    while (*str) {
        if (*str == '\n') {
            vga_pos += 80 - (vga_pos % 80);
            if (vga_pos >= 80 * 25) vga_pos = 0;
            str++;
            continue;
        }

        vga[vga_pos * 2] = *str;
        vga[vga_pos * 2 + 1] = 0x07; // White on black
        vga_pos++;
        if (vga_pos >= 80 * 25) vga_pos = 0;
        str++;
    }
}

void clear_screen() {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vga[i] = ' ';
        vga[i + 1] = 0x07;
    }
    vga_pos = 0;
}

void kernel_main() {
    clear_screen();
    kprint("FNIX Kernel starting...\n");
    kprint("Version: ");
    kprint(KERNEL_VERSION);
    kprint("\n\n");

    // Initialize subsystems
    init_kernel();

    // Start shell
    shell_main();

    kprint("Shutting down FNIX.\n");
}