#include "vfs.h"
#include "common.h"

void kprint(const char *str);

void init_vfs() {
    kprint("VFS initialized\n");
}

int vfs_open(const char *path) {
    kprint("Opening: ");
    kprint(path);
    kprint("\n");
    return 0;
}

int vfs_read(int fd, void *buf, int count) {
    // Placeholder
    return 0;
}