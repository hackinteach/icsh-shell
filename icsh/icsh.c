//
// Created by Hackinteach K. on 18/1/2018 AD.
//

#include <stdio.h>
#include "shell.c"

static char cmd_line[MAX_ARG_LEN];

int main(){
    /* Shell initialization */
    init_shell();
    while(1){
        job *j;
        process *p;

        prompt();
        //@TODO : Add checking for & for background later.
        int foreground = 0;
        fgets(cmd_line,MAX_ARG_LEN-1,stdin);
        if(builtin_exec(cmd_line) != 0){
            parse_command(cmd_line,&p,&j);
            launch_job(&j,foreground);
            do_job_notification();
        }
    }
}

