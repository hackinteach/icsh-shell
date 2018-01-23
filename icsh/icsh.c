//
// Created by Hackinteach K. on 18/1/2018 AD.
//

#include <stdio.h>
#include "shell.h"

static char *cmd_line;
job *first_job = NULL;
//static char cmd_line[MAX_ARG_LEN];

int main() {
    /* Shell initialization */
    init_shell();
    int id = 1;
    while (1) {
        prompt();

        job *j = create_job();

        cmd_line = (char *) malloc(sizeof(char) * MAX_ARG_LEN);

        fgets(cmd_line, MAX_ARG_LEN, stdin);
        strtok(cmd_line, "\n");

        int foreground = (strchr(cmd_line, '&') == NULL);

        /*parse_command*/
        parse_command(cmd_line, j);

        /*start the job*/
        if (first_job) {
            job *t;
            for (t = first_job; t->next; t = t->next) {
                t->next = j;
            }
        } else {
            first_job = j;
        }
        launch_job(j, foreground, &id);
    }
}

