#include "common.h"

void kprint(const char *str);

void shell_main() {
    kprint("FNIX Shell\n");

    if (num_users == 0) {
        kprint("First boot: Create initial user\n");
        kprint("Enter username: ");
        input_pos = 0;
        while (input_buffer[input_pos] != '\n') {}
        input_buffer[input_pos] = 0;
        strcpy(users[0].username, input_buffer);
        kprint("Enter password: ");
        input_pos = 0;
        while (input_buffer[input_pos] != '\n') {}
        input_buffer[input_pos] = 0;
        strcpy(users[0].password, input_buffer);
        users[0].uid = 0;
        users[0].gid = 0;
        num_users = 1;
        kprint("User created.\n");
    }

    kprint("Type 'help' for commands.\n");

    while (1) {
        kprint("> ");
        // Wait for input
        input_pos = 0;
        while (input_buffer[input_pos] != '\n') {
            // Busy wait
        }
        input_buffer[input_pos] = 0; // Null terminate

        if (strcmp(input_buffer, "help") == 0) {
            kprint("Available commands: help, cc, mkusr, exit\n");
        } else if (strcmp(input_buffer, "cc") == 0) {
            kprint("Built-in C compiler (placeholder)\n");
        } else if (strcmp(input_buffer, "mkusr") == 0) {
            kprint("Enter username: ");
            input_pos = 0;
            while (input_buffer[input_pos] != '\n') {}
            char username[32];
            strcpy(username, input_buffer);
            username[input_pos] = 0;
            kprint("Enter password: ");
            input_pos = 0;
            while (input_buffer[input_pos] != '\n') {}
            char password[32];
            strcpy(password, input_buffer);
            password[input_pos] = 0;
            if (num_users < MAX_USERS) {
                strcpy(users[num_users].username, username);
                strcpy(users[num_users].password, password);
                users[num_users].uid = num_users;
                users[num_users].gid = 1000;
                num_users++;
                kprint("User added.\n");
            } else {
                kprint("Max users reached.\n");
            }
        } else if (strcmp(input_buffer, "exit") == 0) {
            break;
        } else {
            kprint("Unknown command: ");
            kprint(input_buffer);
            kprint("\n");
        }
    }
}