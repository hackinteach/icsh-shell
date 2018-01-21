//
// Created by Hackinteach K. on 18/1/2018 AD.
//

#include <stdio.h>
#include "shell.h"

static char *cmd_line;
job *first_job = NULL;
//static char cmd_line[MAX_ARG_LEN];

int main(){
    /* Shell initialization */
    init_shell();
    int  id = 1;
    while(1){
        prompt();

        job *j = create_job();

        cmd_line = (char*) malloc(sizeof(char)*MAX_ARG_LEN);

        //@TODO : Add checking for & for background later.
        int foreground = (strchr(cmd_line,'&')==NULL);

        fgets(cmd_line,MAX_ARG_LEN,stdin);
        strtok(cmd_line,"\n");
        printf("%s\n",cmd_line);

        /*parse_command*/
        // @TODO Parse command
        parse_command(cmd_line,j);
        printf("%ld\n",j->first_process);
        /*start the job*/
        if(first_job){
            printf("First job\n");
            job *t;
            for(t = first_job; t->next;t=t->next){
                t->next = j;
            }
        } else{
            printf("else\n");
            first_job = j;
        }
        printf("Launching job: %d\n",j->id);
        launch_job(j,foreground,&id);
        do_job_notification();
    }
}

