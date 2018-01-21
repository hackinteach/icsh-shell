//
// Created by Hackinteach K. on 20/1/2018 AD.
//

#ifndef _BUILTINH_
#define _BUILTINH_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "shell.h"

typedef struct command_t {
    char* name;
    int argc;
    char *argv[MAX_ARGS];
} command;

/* bif -- built-in function */

/* FUNCTION DECLARATION */
int bif_exit(char **args, job *j);
int bif_jobs(char **args, job *j);
int bif_echo(char **args, job *j);
int bif_fg(char **args, job *j);
int bif_bg(char **args, job *j);

/*
 * List of built-in commands
 * */
char *builtin_str[] = {
        "exit\0",
        "jobs\0",
        "echo\0",
        "fg\0",
        "bg\0"
};

/*
 * Corresponding functions
 * */
int (*builtin_func[]) (char**, job*) = {
        &bif_exit,
        &bif_jobs,
        &bif_echo,
        &bif_fg,
        &bif_bg
};

int num_builtin(){
    return sizeof(builtin_str) / sizeof(char *);
}

/*
 * IMPLEMENTATIONS
 * */
int bif_exit(char **args, job *j) {
    printf("EXITING...\n");
    exit(0);
}

void print_process(process *p) {
    for (int i = 0; p->argv[i]; ++i) {
        printf("  %s", p->argv[i]);
    }
    printf("\n");
}

int bif_jobs(char **args, job *j) {

    if (!j->pgid) {
        fprintf(stderr, "parsing failed");
    }

    process *p;
    int i = 0;
    if (j->infile) {
        printf("infile: %s\n", j->infile);
    }
    if (j->outfile) {
        printf("outfile: %s\n", j->outfile);
    }

    for (p = j->first_process; p; p = p->next) {
        printf("[%d]:", i);
        print_process(p);
        i++;
    }

    return 0;
}

int bif_echo(char **args, job *j) {
    //@TODO Implement this
    return 0;
}

int bif_fg(char **args, job *j) {
    //@TODO Implement this
    return 0;
}

int bif_bg(char **args, job *j) {
    //@TODO Implement this
    return 0;
}

char *skipwhite(char *s) {
    while (isspace(*s)) ++s;
    return s;
}

void split(char *cmd, char **args) {
    cmd = skipwhite(cmd);
    char *next = strchr(cmd, ' ');
    int i = 0;
    args[i] = (char*)malloc(sizeof(char)*MAX_ARG_LEN);
    while (next != NULL) {
        next[0] = '\0';
        args[i] = cmd;
        args[++i] = (char*)malloc(sizeof(char)*MAX_ARG_LEN);
        cmd = skipwhite(next + 1);
        next = strchr(cmd, ' ');
    }

    if (cmd[0] != '\0') {
        args[i] = cmd;
        next = strchr(cmd, '\n');
        next[0] = '\0';
        ++i;
    }

    args[i] = NULL;
}

void parse_builtin(char *line, command *cmd){
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

}

int builtin_exec(char *line, job *j){

    command cmd;

    parse_builtin(line,&cmd);
    cmd.argv[cmd.argc] = NULL;

    printf("TEST COMMAND: %s \n",cmd.argv[0]);

    if(cmd.argv[0] == NULL){
        printf("NULLED\n");
        return -1;
    }

    printf("[builtin.h] Passed NULL check\n");
    printf("[builtin.h] num builtin = %d\n",5);

    for(int i=0;i<num_builtin();i++){
        printf("[builtin.h] comparing %s : %s\n i=%d\n",cmd.argv[0],builtin_str[i],i);
        if(strcmp(cmd.argv[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(cmd.argv,j);
        }
    }

    /* built-in command not found*/
    return -1;
}

#endif


