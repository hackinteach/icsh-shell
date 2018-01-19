//
// Created by Hackinteach K. on 19/1/2018 AD.
//

/* Keep track of attributes of the shell.  */

#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <sys/param.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "misc.h"

pid_t shell_pgid;
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;

/* Make sure the shell is running interactively as the foreground job
   before proceeding. */

void init_shell() {
    /* See if we're running interactively */
    shell_terminal = STDIN_FILENO;
    shell_is_interactive = isatty(shell_terminal);

    if (shell_is_interactive) {

        /* Loop until we're in the foreground */
        while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp())) {
            kill(-shell_pgid, SIGTTIN);
        }

        /* Ignore interactive and job-control signals.  */
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        signal(SIGCHLD, SIG_IGN);

        /* Put ourselves in our own process group */
        shell_pgid = getpid();
        if (setpgid(shell_pgid, shell_pgid) < 0) {
            perror("Couldn't put the shell in its own process group.");
            exit(-1);
        }

        /* Grab control of the terminal */
        tcsetpgrp(shell_terminal, shell_pgid);

        /* Save default terminal attributes for shell */
        tcgetattr(shell_terminal, &shell_tmodes);
    }
}

/*The function is executed by each child process immediately
 * after it has been forked by the shell, and never returns.*/
void launch_process(process *p, pid_t pgid, int infile, int outfile, int errfile, int foreground) {
    pid_t pid;

    if (shell_is_interactive) {
        /* Put the process into the process group,
         * gives it the terminal, if appropriate*/
        if ((pid = getpid()) == 0) {
            pgid = pid;
        }
        setpgid(pid, pgid);
        if (foreground) {
            tcsetpgrp(shell_is_interactive, pgid);
        }
    }

    if(infile != STDIN_FILENO){
        dup2(infile, STDIN_FILENO);
        close(infile);
    }

    if(outfile != STDOUT_FILENO){
        dup2(outfile, STDOUT_FILENO);
        close(outfile);
    }

    if(errfile != STDERR_FILENO){
        dup2(errfile,STDERR_FILENO);
        close(errfile);
    }

    /* Execute new process. Make sure we exit. */
    execvp(p->argv[0], p->argv);
    perror("Executing process");
    exit(1);
}

/* After creating the child processes, this function calls
 * some other functionsto put the newly created job into the
 * foreground or background */
void laucn_job(job *j, int foreground){
    process *p;
    pid_t pid;
    int mypipe[2], infile, outfile;

    infile = j->stdin;
    for(p = j->first_process;p;p=p->next){
        /* Set up pipes, if necessary */
        if(p->next){
            if(pipe(mypipe) < 0){
                perror("pipe error");
                exit(1);
            }
            outfile = mypipe[1];
        }
    }
}