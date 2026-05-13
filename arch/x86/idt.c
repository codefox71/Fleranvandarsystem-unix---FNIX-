#include "common.h"
#include "idt.h"
#include "io.h"
#include "syscall.h"

void kprint(const char *str);

struct idt_entry idt[256];
struct idt_ptr idtp;

void init_idt() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    // Clear IDT
    for (int i = 0; i < 256; i++) {
        set_idt_gate(i, 0);
    }

    // Set syscall interrupt
    set_idt_gate(0x80, (uint32_t)syscall_handler);

    // Load IDT
    asm volatile("lidt %0" : : "m"(idtp));

    // Enable interrupts
    asm volatile("sti");
}

void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = 0x08; // Kernel code segment
    idt[n].zero = 0;
    idt[n].type_attr = 0x8E; // Interrupt gate
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void keyboard_handler() {
    uint8_t scancode = inb(0x60);
    // Simple scancode to ASCII
    char c = 0;
    if (scancode < 0x80) {
        if (scancode == 0x1C) c = '\n';
        else if (scancode == 0x39) c = ' ';
        else if (scancode >= 0x10 && scancode <= 0x19) c = '0' + (scancode - 0x10);
        else if (scancode >= 0x1E && scancode <= 0x26) c = 'a' + (scancode - 0x1E);
        // Add more as needed
    }
    if (c && input_pos < 255) {
        input_buffer[input_pos++] = c;
        input_buffer[input_pos] = 0;
    }

    // Send EOI
    outb(0x20, 0x20);
}