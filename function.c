#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add(char **str,int argc){
    int last_id=0;
    FILE *fp;

char path[512];
snprintf(path, sizeof(path), "%s/tdl", getenv("HOME"));




    fp=fopen(path,"r");
    if (fp) { 
    while (fscanf(fp, "%d%*[^\n]\n", &last_id) == 1);
    fclose(fp);
    }
    
int id=last_id+1; 
 
    fp=fopen(path, "a+");
    if (fp==NULL) {
    printf("file not found");
    exit(1);
    }   
        fprintf(fp,"%d    %d        ",id,0);
    for (int i=2; i<argc; i++) {

        fprintf(fp,"%s  ",str[i]);
    }
    fputc('\n',fp);
    fclose(fp);
    printf("Added a new task\n");
}

void list(){
FILE *fp;

char path[512];
snprintf(path, sizeof(path), "%s/tdl", getenv("HOME"));



fp=fopen(path, "r");
if (fp==NULL) {
printf("file moshkel darad\n");
exit(1);
}
char str[256];
printf("////////// Show All //////////\n");
printf("ID   Done     Task\n");
while ((fgets(str,256,fp)) != NULL)
    printf("%s",str);

printf("==============================\n");



fclose(fp);

}

void clear(){

char path[512];
snprintf(path, sizeof(path), "%s/tdl", getenv("HOME"));



    remove(path);
    printf("clear all tasks\n");
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


int removefromlist(char *d){
    int target_id = atoi(d);

char path[512];
snprintf(path, sizeof(path), "%s/tdl", getenv("HOME"));




    FILE *in = fopen(path, "r");
    if (!in) {
        perror("fopen(read)");
        return 1;
    }
    FILE *out = fopen(path, "w");
    if (!out) {
        perror("fopen(write)");
        fclose(in);
        return 1;
    }

    char line[2048];
    int found = 0;
    int new_id = 0;

    while (fgets(line, sizeof(line), in)) {
        int id, flag, pos = 0;

        if (sscanf(line, "%d %d %n", &id, &flag, &pos) >= 2) {
            char *task = line + pos;

            size_t len = strlen(task);
            if (len > 0 && task[len - 1] == '\n')
                task[len - 1] = '\0';

            if (id == target_id) {
                found = 1;
                continue; 
            }

        }}}

void done(char *d) {

char path[512];
snprintf(path, sizeof(path), "%s/tdl", getenv("HOME"));


char path2[512];
snprintf(path2, sizeof(path2), "%s/tmp", getenv("HOME"));


    int target_id = atoi(d);
    FILE *in = fopen(path, "r");
    if (!in) {
        perror("fopen(read)");
        return;
    }
    FILE *out = fopen(path, "w");
    if (!out) {
        perror("fopen(write)");
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
            if (len > 0 && task[len - 1] == '\n')
                task[len - 1] = '\0';

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
    if (rename(path2,path)  != 0) {
        perror("rename");
        remove(path2);
        return;
    }

    if (found)
        printf("Task %d marked as done.\n", target_id);
    else
        printf("Task with ID %d not found.\n", target_id);
}
