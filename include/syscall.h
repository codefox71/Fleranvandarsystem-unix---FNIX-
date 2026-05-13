#ifndef SYSCALL_H
#define SYSCALL_H

// Syscall numbers
#define SYS_EXIT 1
#define SYS_FORK 2
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_EXECVE 11
#define SYS_CHDIR 12
#define SYS_TIME 13
#define SYS_GETPID 20
#define SYS_DUP 41
#define SYS_BRK 45

// Syscall handler
void syscall_handler();

#endif // SYSCALL_H