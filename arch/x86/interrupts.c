#include "common.h"
#include "idt.h"
#include "io.h"

void kprint(const char *str);

void init_interrupts_x86() {
    kprint("Initializing x86 interrupts...\n");
    init_idt();
}