#include "syscall.h"
#include "common.h"

void kprint(const char *str);

void syscall_handler() {
    // Placeholder for syscall implementation
    kprint("Syscall called\n");
}