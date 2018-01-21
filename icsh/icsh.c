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
        job *j = create_job();
        cmd_line = (char*) malloc(sizeof(char)*MAX_ARG_LEN);

        prompt();

        //@TODO : Add checking for & for background later.
        int foreground = 0;

        fgets(cmd_line,MAX_ARG_LEN,stdin);
        /*Debugging*/
        printf("[main] Passed read cmd_line\n");

        strtok(cmd_line,"\n");
        printf("%s\n",cmd_line);
        int checkBuiltIn = builtin_exec(cmd_line,j);

        if(checkBuiltIn != 0){
            printf("file exec\n");
            parse_command(cmd_line,j);
            printf("[main] Passed parse_command\n");
            printf("[main] p->argv[0]: %s\n",j->first_process->argv[0]);

            launch_job(&j,foreground);
            do_job_notification();
        }
    }
}

