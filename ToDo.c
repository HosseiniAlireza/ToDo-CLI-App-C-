#include "function.h"
#include <stdio.h>
#include <string.h>



int main(int argc, char *argv[]){

    if (argc<2) {
    printf("Usage: todo <command> [arguments]");
    return 0;
    }
    else if ((argv[1][0] == '-' && argv[1][1]=='a' && argv[1][2] =='\0')|| strcmp(argv[1],"--add")== 0) {
    add(argv,argc);
    }
    else if ((argv[1][0] == '-' &&argv[1][1] == 'l' && argv[1][2] =='\0')|| strcmp(argv[1],"--list")== 0) {
    list();
    }
    else if ((argv[1][0] == '-' && argv[1][1] == 'c' && argv[1][2] =='\0')|| strcmp(argv[1],"--clear")==0) {
    clear();
    }
    else if ((argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] =='\0')|| strcmp(argv[1],"--help")==0){
    help();
    }
    else if ((argv[1][0] == '-' && argv[1][1] == 'r' && argv[1][2] =='\0')|| strcmp(argv[1],"--remove")==0) {
    removefromlist(argv[2]);
    }
    else if((argv[1][0] == '-' && argv[1][1] == 'd'  && argv[1][2] == '\0')|| strcmp(argv[1],"--done")==0){
    done(argv[2]);
    }
    
    return 0;
}


