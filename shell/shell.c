#include "common.h"
#include "io.h"

void kprint(const char *str);
void clear_screen();

static char scancode_to_ascii(uint8_t scancode) {
    if (scancode >= 0x02 && scancode <= 0x0B) {
        const char *map = "1234567890-=";
        return map[scancode - 0x02];
    }
    if (scancode >= 0x10 && scancode <= 0x19) {
        const char *map = "qwertyuiop";
        return map[scancode - 0x10];
    }
    if (scancode >= 0x1E && scancode <= 0x26) {
        const char *map = "asdfghjkl";
        return map[scancode - 0x1E];
    }
    if (scancode >= 0x2C && scancode <= 0x32) {
        const char *map = "zxcvbnm";
        return map[scancode - 0x2C];
    }
    if (scancode == 0x1C) return '\n';
    if (scancode == 0x0E) return '\b';
    if (scancode == 0x39) return ' ';
    return 0;
}

static char read_key() {
    while (!(inb(0x64) & 1)) {}
    uint8_t scancode = inb(0x60);
    if (scancode & 0x80) return 0;
    return scancode_to_ascii(scancode);
}

static void read_line(char *buffer, int max) {
    int idx = 0;
    while (1) {
        char c = read_key();
        if (!c) continue;
        if (c == '\n') {
            buffer[idx] = 0;
            kprint("\n");
            return;
        }
        if (c == '\b' && idx > 0) {
            idx--;
            kprint("\b ");
            kprint("\b");
            continue;
        }
        if (idx < max - 1) {
            buffer[idx++] = c;
            buffer[idx] = 0;
            char s[2] = {c, 0};
            kprint(s);
        }
    }
}

static int find_user(const char *username) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

static int starts_with(const char *str, const char *prefix) {
    while (*prefix) {
        if (*str++ != *prefix++) return 0;
    }
    return 1;
}

static void print_prompt(int current_user) {
    kprint(users[current_user].username);
    if (users[current_user].uid == 0) {
        kprint("# ");
    } else {
        kprint("$ ");
    }
}

void shell_main() {
    int current_user = -1;
    char password[64];

    kprint("FNIX Shell\n");
    kprint("Login using root/aroot or another account.\n");

    while (current_user < 0) {
        kprint("Login: ");
        read_line(input_buffer, sizeof(input_buffer));
        int user_index = find_user(input_buffer);
        if (user_index < 0) {
            kprint("User not found.\n");
            continue;
        }

        kprint("Password: ");
        read_line(password, sizeof(password));
        if (strcmp(password, users[user_index].password) == 0) {
            current_user = user_index;
            kprint("Welcome ");
            kprint(users[current_user].username);
            kprint("!\n");
        } else {
            kprint("Incorrect password.\n");
        }
    }

    kprint("Type 'help' for commands.\n");

    while (1) {
        print_prompt(current_user);
        read_line(input_buffer, sizeof(input_buffer));

        if (strcmp(input_buffer, "help") == 0) {
            kprint("Commands: help, clear, version, whoami, id, users, mkusr, su, sudo, passwd, logout, exit\n");
        } else if (strcmp(input_buffer, "clear") == 0) {
            clear_screen();
        } else if (strcmp(input_buffer, "version") == 0) {
            kprint("FNIX version: ");
            kprint(KERNEL_VERSION);
            kprint("\n");
        } else if (strcmp(input_buffer, "whoami") == 0) {
            kprint(users[current_user].username);
            kprint("\n");
        } else if (strcmp(input_buffer, "id") == 0) {
            kprint("uid=");
            char tmp[16];
            int n = users[current_user].uid;
            tmp[0] = '0' + (n / 10);
            tmp[1] = '0' + (n % 10);
            tmp[2] = 0;
            kprint(tmp);
            kprint(" gid=");
            n = users[current_user].gid;
            tmp[0] = '0' + (n / 10);
            tmp[1] = '0' + (n % 10);
            tmp[2] = 0;
            kprint(tmp);
            kprint("\n");
        } else if (strcmp(input_buffer, "users") == 0) {
            for (int i = 0; i < num_users; i++) {
                kprint(users[i].username);
                if (users[i].uid == 0) kprint(" (root)");
                kprint("\n");
            }
        } else if (starts_with(input_buffer, "echo ")) {
            kprint(input_buffer + 5);
            kprint("\n");
        } else if (strcmp(input_buffer, "mkusr") == 0) {
            if (users[current_user].uid != 0) {
                kprint("Permission denied. Use sudo or login as root.\n");
            } else if (num_users >= MAX_USERS) {
                kprint("Max users reached.\n");
            } else {
                char username[32];
                kprint("Enter new username: ");
                read_line(username, sizeof(username));
                if (find_user(username) >= 0) {
                    kprint("User already exists.\n");
                } else {
                    char password2[32];
                    kprint("Enter password: ");
                    read_line(password2, sizeof(password2));
                    strcpy(users[num_users].username, username);
                    strcpy(users[num_users].password, password2);
                    users[num_users].uid = num_users;
                    users[num_users].gid = 1000;
                    num_users++;
                    kprint("User added.\n");
                }
            }
        } else if (strcmp(input_buffer, "su") == 0) {
            kprint("Use 'su <username>' to switch.\n");
        } else if (starts_with(input_buffer, "su ")) {
            char *target = input_buffer + 3;
            int user_index = find_user(target);
            if (user_index < 0) {
                kprint("User not found.\n");
            } else {
                kprint("Password: ");
                read_line(password, sizeof(password));
                if (strcmp(password, users[user_index].password) == 0) {
                    current_user = user_index;
                    kprint("Switched to ");
                    kprint(users[current_user].username);
                    kprint("\n");
                } else {
                    kprint("Incorrect password.\n");
                }
            }
        } else if (strcmp(input_buffer, "sudo") == 0) {
            kprint("Use 'sudo <command>' to run as root.\n");
        } else if (starts_with(input_buffer, "sudo ")) {
            if (users[current_user].uid == 0) {
                kprint("Already root.\n");
            } else {
                char *command = input_buffer + 5;
                kprint("Root password: ");
                read_line(password, sizeof(password));
                if (strcmp(password, users[0].password) == 0) {
                    if (strcmp(command, "mkusr") == 0) {
                        kprint("Running mkusr as root...\n");
                        input_buffer[0] = 0;
                        strcpy(input_buffer, "mkusr");
                    } else if (strcmp(command, "clear") == 0) {
                        clear_screen();
                    } else {
                        kprint("sudo: command not implemented: ");
                        kprint(command);
                        kprint("\n");
                    }
                } else {
                    kprint("Incorrect root password.\n");
                }
            }
        } else if (strcmp(input_buffer, "passwd") == 0) {
            kprint("New password: ");
            read_line(password, sizeof(password));
            strcpy(users[current_user].password, password);
            kprint("Password updated.\n");
        } else if (strcmp(input_buffer, "logout") == 0) {
            kprint("Logging out...\n");
            current_user = -1;
            while (current_user < 0) {
                kprint("Login: ");
                read_line(input_buffer, sizeof(input_buffer));
                int user_index = find_user(input_buffer);
                if (user_index < 0) {
                    kprint("User not found.\n");
                    continue;
                }
                kprint("Password: ");
                read_line(password, sizeof(password));
                if (strcmp(password, users[user_index].password) == 0) {
                    current_user = user_index;
                    kprint("Welcome ");
                    kprint(users[current_user].username);
                    kprint("!\n");
                } else {
                    kprint("Incorrect password.\n");
                }
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