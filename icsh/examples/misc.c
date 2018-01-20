#include <termios.h>
#include <stddef.h>
#include <stdlib.h>
#include "misc.h"

#define ARG_MAX 256
/*
Job *first_job = NULL;

*//* Find the activejob with the indicated 'pgid' *//*
Job* find_job(pid_t pgid){
    Job* j;

    for(j=first_job;j;j=j->next){
        if(j->pgid == pgid){
            return j;
        }
    }
    return NULL;
}*/

/* Return true if all processes in the Job have stopped or completed */
int job_is_stopped(Job *j){
    Process *p;

    for(p = j->first_process;p;p = p->next){
        if(!p->completed && !p->stopped){
            return 0;
        }
    }

    return 1;
}

/* Return true if all processes in the Job have completed */
int job_is_completed(Job *j){

    Process *p;

    for(p=j->first_process;p;p=p->next){
        if(!p->completed){
            return 0;
        }
    }
    return 1;
}

void free_job (Job *j)
{
    if(!j) return;
    Process* p = j->first_process;
    while(p) {
        Process *tmp = p->next;
        free_process(p);
        p = tmp;
    }
}

void free_process (Process* p)
{
    if(!p->argv) return;
    for (int i = 0; p->argv[i] && i < ARG_MAX; ++i)
    {
        free(p->argv[i]);
    }
    free(p->argv);
}

int parse_command(char *line, Process *p){
    int argc;
    char **commandLinePtr;

    /* Initialize */
    commandLinePtr = &line;
    argc = 0;
    p->argv[argc] = (char*) malloc(MAX_ARG_LEN);

    /* Fill argv[] */
    while((p->argv[argc] = strsep(commandLinePtr,WHITESPACE) ) != NULL ){
        p->argv[++argc] = (char*)malloc(MAX_ARG_LEN);
    }

    /* Set cmd name and argc */
//    p->argc = argc-1;
//    p->name = (char*)malloc(sizeof(p->argv[0]));
//    strcpy(p->name,p->argv[0]);
    return 1;
}
