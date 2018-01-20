//
// Created by Hackinteach K. on 18/1/2018 AD.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"
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
        parse_command(line,&p,&j);
        launch_job(&j,foreground);
        do_job_notification();
    }
}

