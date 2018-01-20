//
// Created by Hackinteach K. on 20/1/2018 AD.
//
#ifndef _BUILTINH_
#define _BUILTINH_

#include <stdlib.h>
#include "shell.c"

/* FUNCTION DECLARATION */
int bif_exit(char **args);
/* bif -- built-in function */
int bif_jobs(job *j);
int bif_echo(char **args);
int bif_fg(char **args);
int bif_bg(char **args);

/*
 * List of built-in commands
 * */
char *builtin_str[] = {
        "exit",
        "jobs",
        "echo",
        "fg",
        "bg"
};

/*
 * Corresponding functions
 * */
int (*builtin_func[]) (char**) = {
        &bif_exit,
        &bif_jobs,
        &bif_echo,
        &bif_fg,
        &bif_bg
};

int num_builtin(){
    return sizeof(builtin_str) / sizeof(char *);
}

#endif


