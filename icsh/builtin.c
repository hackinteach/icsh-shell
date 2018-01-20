//
// Created by Hackinteach K. on 20/1/2018 AD.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "builtin.h"
/*
 * IMPLEMENTATIONS
 * */
int bif_exit(char **args) {
    exit(0);
}

void print_process(process *p) {
    for (int i = 0; p->argv[i]; ++i) {
        printf("  %s", i, p->argv[i]);
    }
    printf("\n");
}

int bif_jobs(job *j) {
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

int bif_echo(char **args) {
    //@TODO Implement this
    return 0;
}

int bif_fg(char **args) {
    //@TODO Implement this
    return 0;
}

int bif_bg(char **args) {
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

    while (next != NULL) {
        next[0] = '\0';
        args[i] = cmd;
        ++i;
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


