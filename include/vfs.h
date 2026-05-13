#ifndef VFS_H
#define VFS_H

// Virtual File System
void init_vfs();
int vfs_open(const char *path);
int vfs_read(int fd, void *buf, int count);

#endif // VFS_H