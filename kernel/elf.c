#include "elf.h"
#include "common.h"

void kprint(const char *str);

int load_elf(const char *filename) {
    kprint("Loading ELF: ");
    kprint(filename);
    kprint("\n");
    // Placeholder
    return 0;
}