//
// Created by Hackinteach K. on 18/1/2018 AD.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_LINE_LEN    1024
#define MAX_ARGS    64
#define MAX_ARG_LEN     16
#define WHITESPACE " .,\t\n"

typedef struct command_t {
    char* name;
    int argc;
    char *argv[MAX_ARGS];
} Command;

int parseCommand(char  *line, Command *cmd);

int main(int argc, char **argv) {
    int pid, numChildren, status;
    Command command;
    char cmdLine[MAX_LINE_LEN];
    FILE *fid;

    if(argc != 2){
        printf("Usage : launch <launch_set file>\n");
        exit(-1);
    }

    fid = fopen(argv[1], "r");

    numChildren = 0;

    while(fgets(cmdLine,MAX_LINE_LEN,fid) != NULL){
        parseCommand(cmdLine,&command);
        command.argv[command.argc] = NULL;
        if( (pid = fork()) == 0){
            printf("launch : running %s ",command.name);
            if(command.argc > 1){
                for(int i=1;i<command.argc;i++){
                    printf("%s ",command.argv[i]);
                }
            }
            printf("\n\n");
            execvp(command.name,command.argv);
        }
        numChildren++;
    }
    printf("launch : %d children",numChildren);

    for(int i=0;i<numChildren;i++){
        wait(&status);
    }
    printf("\n\nlaunch: Terminating successfully\n");
    return 0;

}

int parseCommand(char *line, Command *cmd){
    int argc;
    char **commandLinePtr;

    /* Initialize */
    commandLinePtr = &line;
    argc = 0;
    cmd->argv[argc] = (char*) malloc(MAX_ARG_LEN);

    /* Fill argv[] */
    while((cmd->argv[argc] = strsep(commandLinePtr,WHITESPACE) ) != NULL ){
        cmd->argv[++argc] = (char*)malloc(MAX_ARG_LEN);
    }

    /* Set cmd name and argc */
    cmd->argc = argc-1;
    cmd->name = (char*)malloc(sizeof(cmd->argv[0]));
    strcpy(cmd->name,cmd->argv[0]);
    return 1;
}
