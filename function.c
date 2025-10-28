#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// Helper to build data file paths inside $HOME
static void build_path(char *buf, size_t buflen, const char *name) {
    const char *home = getenv("HOME");
    if (!home || !*home) {
        // Fallback to current directory if HOME is not set
        snprintf(buf, buflen, "%s", name);
        return;
    }
    snprintf(buf, buflen, "%s/%s", home, name);
}

void add(char **str, int argc) {
    if (argc < 3) {
        fprintf(stderr, "todo: missing task text for --add\n");
        fprintf(stderr, "usage: todo -a <task>\n");
        return;
    }

    int last_id = 0;
    FILE *fp = NULL;

    char path[512];
    build_path(path, sizeof(path), "tdl");

    // Read last id if file exists
    fp = fopen(path, "r");
    if (fp) {
        while (fscanf(fp, "%d%*[^\n]\n", &last_id) == 1) {
            // scan last seen id
        }
        fclose(fp);
    }

    int id = last_id + 1;

    // Append the new task
    fp = fopen(path, "a");
    if (!fp) {
        perror("todo: fopen(append)");
        return;
    }

    // Status flag 0 = pending
    fprintf(fp, "%d    %d        ", id, 0);
    for (int i = 2; i < argc; i++) {
        fprintf(fp, "%s%s", str[i], (i + 1 < argc ? " " : ""));
    }
    fputc('\n', fp);
    fclose(fp);
    printf("Added a new task (id=%d)\n", id);
}

void list() {
    FILE *fp;
    char path[512];
    build_path(path, sizeof(path), "tdl");

    fp = fopen(path, "r");
    if (!fp) {
        printf("No tasks found. (data file '%s' not present)\n", path);
        return;
    }

    char str[1024];
    printf("////////// Show All //////////\n");
    printf("ID   Done     Task\n");
    while (fgets(str, sizeof(str), fp)) {
        fputs(str, stdout);
    }
    printf("==============================\n");
    fclose(fp);
}

void clear() {
    char path[512];
    build_path(path, sizeof(path), "tdl");

    if (remove(path) == 0) {
        printf("Cleared all tasks.\n");
    } else {
        if (errno == ENOENT) {
            printf("Nothing to clear (no task file).\n");
        } else {
            perror("todo: remove");
        }
    }
}

void help() {
    printf("Usage: todo <command> [arguments]\n");
    printf("Commands:\n");
    printf("-a <task>  or    --add    <task>    Add a new task\n");
    printf("-l         or    --list             List all tasks\n");
    printf("-c         or    --clear            Clear all tasks\n");
    printf("-d <id>    or    --done   <id>      Mark task as done\n");
    printf("-r <id>    or    --remove <id>      Remove task from list\n");
    printf("-h         or    --help             Show this help message\n");
}

int removefromlist(const char *d) {
    if (!d) {
        fprintf(stderr, "todo: missing id for --remove\n");
        return 1;
    }
    int target_id = atoi(d);
    if (target_id <= 0) {
        fprintf(stderr, "todo: invalid id '%s'\n", d);
        return 1;
    }

    char path[512], path_tmp[512];
    build_path(path, sizeof(path), "tdl");
    build_path(path_tmp, sizeof(path_tmp), "tdl.tmp");

    FILE *in = fopen(path, "r");
    if (!in) {
        if (errno == ENOENT) {
            fprintf(stderr, "todo: nothing to remove (no task file)\n");
        } else {
            perror("todo: fopen(read)");
        }
        return 1;
    }
    FILE *out = fopen(path_tmp, "w");
    if (!out) {
        perror("todo: fopen(write tmp)");
        fclose(in);
        return 1;
    }

    char line[2048];
    int found = 0;

    while (fgets(line, sizeof(line), in)) {
        int id, flag, pos = 0;
        if (sscanf(line, "%d %d %n", &id, &flag, &pos) >= 2) {
            char *task = line + pos;

            size_t len = strlen(task);
            if (len > 0 && task[len - 1] == '\n') task[len - 1] = '\0';

            if (id == target_id) {
                found = 1;
                continue; // skip this line -> effectively removes it
            }

            // keep other tasks intact
            fprintf(out, "%d    %d        %s\n", id, flag, task);
        } else {
            // preserve malformed lines just in case
            fputs(line, out);
        }
    }

    fclose(in);
    fclose(out);

    if (rename(path_tmp, path) != 0) {
        perror("todo: rename(tmp->tdl)");
        remove(path_tmp);
        return 1;
    }

    if (found) {
        printf("Removed task %d.\n", target_id);
        return 0;
    } else {
        printf("Task with ID %d not found.\n", target_id);
        return 1;
    }
}

void done(const char *d) {
    if (!d) {
        fprintf(stderr, "todo: missing id for --done\n");
        return;
    }
    int target_id = atoi(d);
    if (target_id <= 0) {
        fprintf(stderr, "todo: invalid id '%s'\n", d);
        return;
    }

    char path[512], path_tmp[512];
    build_path(path, sizeof(path), "tdl");
    build_path(path_tmp, sizeof(path_tmp), "tdl.tmp");

    FILE *in = fopen(path, "r");
    if (!in) {
        if (errno == ENOENT) {
            fprintf(stderr, "todo: nothing to mark done (no task file)\n");
        } else {
            perror("todo: fopen(read)");
        }
        return;
    }
    FILE *out = fopen(path_tmp, "w");
    if (!out) {
        perror("todo: fopen(write tmp)");
        fclose(in);
        return;
    }

    char line[2048];
    int found = 0;

    while (fgets(line, sizeof(line), in)) {
        int id, flag, pos = 0;

        if (sscanf(line, "%d %d %n", &id, &flag, &pos) >= 2) {
            char *task = line + pos;

            size_t len = strlen(task);
            if (len > 0 && task[len - 1] == '\n') task[len - 1] = '\0';

            if (id == target_id) {
                flag = 1;
                found = 1;
            }
            fprintf(out, "%d    %d        %s\n", id, flag, task);
        } else {
            fputs(line, out);
        }
    }
    fclose(in);
    fclose(out);

    if (rename(path_tmp, path) != 0) {
        perror("todo: rename(tmp->tdl)");
        remove(path_tmp);
        return;
    }

    if (found)
        printf("Task %d marked as done.\n", target_id);
    else
        printf("Task with ID %d not found.\n", target_id);
}
