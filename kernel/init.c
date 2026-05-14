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
    // Default root user
    strcpy(users[0].username, "root");
    strcpy(users[0].password, "aroot");
    users[0].uid = 0;
    users[0].gid = 0;
    num_users = 1;

    init_scheduler();
    init_graphics();
    init_vfs();
    kprint("Kernel initialized.\n");
}