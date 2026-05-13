#include "common.h"
#include "scheduler.h"
#include "graphics.h"
#include "vfs.h"

struct user users[MAX_USERS];
int num_users = 0;

char input_buffer[256];
int input_pos = 0;

void kprint(const char *str);

void init_kernel() {
    init_scheduler();
    init_graphics();
    init_vfs();
    kprint("Kernel initialized.\n");
}