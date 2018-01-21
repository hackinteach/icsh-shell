//
// Created by Hackinteach K. on 18/1/2018 AD.
//

#include <stdio.h>
#include "shell.h"
#include "builtin.h"

static char *cmd_line;
//static char cmd_line[MAX_ARG_LEN];

int main(){
    /* Shell initialization */
    init_shell();
    while(1){
        job *j = (job*)malloc(sizeof(job));
        process *p = (process*)malloc(sizeof(process));
        cmd_line = (char*) malloc(sizeof(char)*MAX_ARG_LEN);

        prompt();

        //@TODO : Add checking for & for background later.
        int foreground = 0;

        fgets(cmd_line,MAX_ARG_LEN,stdin);
        /*Debugging*/
        printf("Passed read cmd_line\n");
        printf("%s\n",cmd_line);
        strtok(cmd_line,"\n");

        parse_command(cmd_line,&p,j);
        printf("Passed parse_command\n");
        printf("p->argv[0]: %s\n",j->first_process->argv[0]);
        int checkBuiltIn = builtin_exec(&cmd_line,j);
        printf("cb : %d\n",checkBuiltIn);
        if(checkBuiltIn != 0){
            printf("file exec\n");
            launch_job(&j,foreground);
            do_job_notification();
        }
    }
}

