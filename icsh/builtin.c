//
// Created by Hackinteach K. on 20/1/2018 AD.
//

#include <stdio.h>
#include "builtin.h"
#include "shell.h"

/*
 * IMPLEMENTATIONS
 * */
int bif_exit(char **args){
    return 0;
}

void print_process(process *p){
    for(int i=0;p->argv[i];++i){
        printf("  %s",i,p->argv[i]);
    }
    printf("\n");
}

int bif_jobs(job *j){
    if(!j->pgid){
        fprintf(stderr, "parsing failed");
    }

    process *p;
    int i=0;
    if(j->infile){
        printf("infile: %s\n",j->infile);
    }
    if(j->outfile){
        printf("outfile: %s\n",j->outfile);
    }

    for(p=j->first_process; p ; p=p->next){
        printf("[%d]:",i);
        print_process(p);
        i++;
    }

    return 0;
}

int bif_echo(char **args){
    //@TODO Implement this
}

int bif_fg(char **args){
    //@TODO Implement this
}

int bif_bg(char **args){
    //@TODO Implement this
}



