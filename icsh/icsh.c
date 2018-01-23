//
// Created by Hackinteach K. on 18/1/2018 AD.
//

#include <stdio.h>
#include "shell.h"

static char *cmd_line;
job *first_job = NULL;

int main() {
    /* Shell initialization */

    int id = 1;
    while (1) {
        init_shell();

        int validCmd = 0;
        do {
            prompt();


            cmd_line = (char *) malloc(sizeof(char) * MAX_ARG_LEN);

            fgets(cmd_line, MAX_ARG_LEN, stdin);
            strtok(cmd_line, "\n");

            if(strcmp(cmd_line,"") == 0){
                printf("invalid input\n");
                free(cmd_line);
                validCmd = -1;
            }

        }while(validCmd == -1);


        job *j = create_job();
        int foreground = (strchr(cmd_line, '&') == NULL);
        j->foreground = foreground;

        /*parse_command*/
        parse_command(cmd_line, j);

        if(j->valid > 0)
        {
            if(first_job)
            {
                job *t;
                for(t = first_job; t->next; t = t->next);
                t->next = j;
            }
            else
                first_job = j;
            launch_job(j, j->foreground, &id);
            do_job_notification();
//            print_job(first_job);
        }
        else if (j->valid < 0)
        {
            do_job_notification();
        }
        else (free_job(j));

    }
}

