#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void print_usage(void) {
    printf("Usage: todo <command> [arguments]\n");
    printf("Try 'todo --help' for more information.\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    const char *cmd = argv[1];

    if ((cmd[0] == '-' && cmd[1] == 'a' && cmd[2] == '\0') || strcmp(cmd, "--add") == 0) {
        if (argc < 3) {
            fprintf(stderr, "todo: missing task text for --add\n");
            return 1;
        }
        add(argv, argc);
    }
    else if ((cmd[0] == '-' && cmd[1] == 'l' && cmd[2] == '\0') || strcmp(cmd, "--list") == 0) {
        list();
    }
    else if ((cmd[0] == '-' && cmd[1] == 'c' && cmd[2] == '\0') || strcmp(cmd, "--clear") == 0) {
        clear();
    }
    else if ((cmd[0] == '-' && cmd[1] == 'h' && cmd[2] == '\0') || strcmp(cmd, "--help") == 0) {
        help();
    }
    else if ((cmd[0] == '-' && cmd[1] == 'r' && cmd[2] == '\0') || strcmp(cmd, "--remove") == 0) {
        if (argc < 3) {
            fprintf(stderr, "todo: missing id for --remove\n");
            return 1;
        }
        return removefromlist(argv[2]);
    }
    else if ((cmd[0] == '-' && cmd[1] == 'd' && cmd[2] == '\0') || strcmp(cmd, "--done") == 0) {
        if (argc < 3) {
            fprintf(stderr, "todo: missing id for --done\n");
            return 1;
        }
        done(argv[2]);
    }
    else {
        fprintf(stderr, "todo: unknown command '%s'\n", cmd);
        print_usage();
        return 1;
    }

    return 0;
}
