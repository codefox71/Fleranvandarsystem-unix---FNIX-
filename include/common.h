#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stddef.h>

// Basic types
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

// Kernel constants
#define KERNEL_VERSION "FNIX 0.1"

// User management
#define MAX_USERS 10
#define MAX_USERNAME_LEN 32
#define MAX_PASSWORD_LEN 32

struct user {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    int uid;
    int gid;
};

extern struct user users[MAX_USERS];
extern int num_users;

// Input buffer for keyboard
extern char input_buffer[256];
extern int input_pos;

// Function declarations
void kernel_main();
void init_kernel();
void shell_main();

// String functions
void strcpy(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);

#endif // COMMON_H