//
// Created by Hackinteach K. on 20/1/2018 AD.
//

#ifndef _SHELLH_
#define _SHELLH_

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>


#define MAX_LINE_LEN    80
#define MAX_ARGS    64
#define MAX_ARG_LEN     1024
#define WHITESPACE " .,\t\n"


/* A process is a single process.  */
typedef struct process {
    struct process *next;       /* next process in pipeline */
    char **argv;                /* for exec */
    int argc;                   /* counting argv */
    pid_t pid;                  /* process ID */
    char completed;             /* true if process has completed */
    char stopped;               /* true if process has stopped */
    int status;                 /* reported status value */
} process;

/* A job is a pipeline of processes.  */
typedef struct job {
    struct job *next;           /* next active job */
//    char *command;              /* command line, used for messages */
    char *infile, *outfile;      /* file redirection */
    process *first_process;     /* list of processes in this job */
    pid_t pgid;                 /* process group ID */
    char notified;              /* true if user told about stopped job */
    struct termios tmodes;      /* saved terminal modes */
    int stdin, stdout, stderr;  /* standard i/o channels */
    int id;
} job;

/* Shell's attributes */
pid_t shell_pgid;
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;
job *first_job;

static void pSigHandler(int signo);

/* List of all functions to be used later */
void init_shell() {

    /* See if we are running interactively.  */
    shell_terminal = STDIN_FILENO;
    shell_is_interactive = isatty(shell_terminal);

    if (shell_is_interactive) {
        /* Loop until we are in the foreground.  */
        while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
            kill(-shell_pgid, SIGTTIN);
        /* Ignore interactive and job-control signals.  */
        struct sigaction psa;
        psa.sa_handler = pSigHandler;
        sigaction(SIGINT, &psa, NULL);

//        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
//        signal(SIGCHLD, SIG_IGN);

        /* Put ourselves in our own process group.  */
        shell_pgid = getpid();
        if (setpgid(shell_pgid, shell_pgid) < 0) {
            perror("Couldn't put the shell in its own process group");
            exit(1);
        }

        /* Grab control of the terminal.  */
        tcsetpgrp(shell_terminal, shell_pgid);

        /* Save default terminal attributes for shell.  */
        tcgetattr(shell_terminal, &shell_tmodes);
    }
}

process *create_process(void);

int parse_command(char *line, job *j) {
    int argc;
    char **commandLinePtr;
    process *p = create_process();

    j->first_process = p;

    /* Initialize */
    commandLinePtr = &line;
    argc = 0;
    p->argv = (char **) malloc(sizeof(char *) * MAX_ARGS);

    p->argv[argc] = (char *) malloc(MAX_ARG_LEN * sizeof(char));

    /* Fill argv[] */
    while ((p->argv[argc] = strsep(commandLinePtr, WHITESPACE)) != NULL) {
        p->argv[++argc] = (char *) malloc(MAX_ARG_LEN * sizeof(char));
    }

    p->argc = argc;
    return 0;
}

void launch_process(process *p, pid_t pgid,
                    int infile, int outfile, int errfile,
                    int foreground) {
    pid_t pid;

    if (shell_is_interactive) {
        /* Put the process into the process group and give the process group
           the terminal, if appropriate.
           This has to be done both by the shell and in the individual
           child processes because of potential race conditions.  */
        pid = getpid();
        if (pgid == 0) { pgid = pid; }
        setpgid(pid, pgid);
        if (foreground) { tcsetpgrp(shell_terminal, pgid); }

        /* Set the handling for job control signals back to the default.  */
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGCHLD, SIG_DFL);
    }

    /* Set the standard input/output channels of the new process.  */
    if (infile != STDIN_FILENO) {
        dup2(infile, STDIN_FILENO);
        close(infile);
    }
    if (outfile != STDOUT_FILENO) {
        dup2(outfile, STDOUT_FILENO);
        close(outfile);
    }
    if (errfile != STDERR_FILENO) {
        dup2(errfile, STDERR_FILENO);
        close(errfile);
    }

    /* Exec the new process.  Make sure we exit.  */
    execvp(p->argv[0], p->argv);
    perror("execvp");
    exit(1);
}

int launch_builtin(process *p, int infile, int outfile, int errfile);

void format_job_info(job *j, const char *status);

void wait_for_job(job *j);

void put_job_in_background(job *j, int cont);

void put_job_in_foreground(job *j, int cont);

void launch_job(job *j, int foreground, int *id) {
    process *p;
    pid_t pid;
    int mypipe[2], infile, outfile;
    if (j->infile) {
        j->stdin = open(j->infile, O_RDONLY);
        if (j->stdin < 0) {
            perror(j->infile);
            exit(1);
        }
    }
    if (j->outfile) {
        j->stdout = open(j->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (j->stdout < 0) {
            perror(j->outfile);
            exit(1);
        }
    }
    infile = j->stdin;
    for (p = j->first_process; p; p = p->next) {
        /* Set up pipes, if necessary.  */
        if (p->next) {
            if (pipe(mypipe) < 0) {
                perror("pipe");
                exit(1);
            }
            outfile = mypipe[1];
        } else
            outfile = j->stdout;
        if (launch_builtin(p, infile, outfile, j->stderr) == 0) {
            p->completed = 1;
        } else {
            /* Fork the child processes.  */
            pid = fork();
            if (pid == 0)
                /* This is the child process.  */
                launch_process(p, j->pgid, infile,
                               outfile, j->stderr, foreground);
            else if (pid < 0) {
                /* The fork failed.  */
                perror("fork");
                exit(1);
            } else {
                /* This is the parent process.  */
                p->pid = pid;
                if (shell_is_interactive) {
                    if (!j->pgid) {
                        j->pgid = pid;
                        j->id = *id;
                        *id = *id + 1;
                    }
                    setpgid(pid, j->pgid);
                }
            }
        }
        /* Clean up after pipes.  */
        if (infile != j->stdin)
            close(infile);
        if (outfile != j->stdout)
            close(outfile);
        infile = mypipe[0];
    }

    if (!shell_is_interactive)
        wait_for_job(j);
    else if (foreground)
        put_job_in_foreground(j, 0);
    else {
        put_job_in_background(j, 0);
        format_job_info(j, "background");
    }
}

void put_job_in_foreground(job *j, int cont) {
    /* Put the job into the foreground.  */
    tcsetpgrp(shell_terminal, j->pgid);

    /* Send the job a continue signal, if necessary.  */
    if (cont) {
        tcsetattr(shell_terminal, TCSADRAIN, &j->tmodes);
        if (kill(-j->pgid, SIGCONT) < 0)
            perror("kill (SIGCONT)");
    }

    /* Wait for it to report.  */
    wait_for_job(j);

    /* Put the shell back in the foreground.  */
    tcsetpgrp(shell_terminal, shell_pgid);

    /* Restore the shell’s terminal modes.  */
    tcgetattr(shell_terminal, &j->tmodes);
    tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
}

void put_job_in_background(job *j, int cont) {
    /* Send the job a continue signal, if necessary.  */
    if (cont) {
        if (kill(-j->pgid, SIGCONT) < 0) {
            perror("kill (SIGCONT)");
        }
    }
}

void format_job_info(job *j, const char *status) {
    fprintf(stderr, "%ld (%s): %s\n", (long) j->pgid, status, j->first_process->argv[0]);
}

int job_is_stopped(job *j);

int mark_process_status(pid_t pid, int status);

/* Return true if all processes in the job have completed.  */
int job_is_completed(job *j);

void wait_for_job(job *j) {
    int status;
    pid_t pid;

    if (!job_is_stopped(j)) {
        do {
            pid = waitpid(-1, &status, WUNTRACED);
//            pid = waitpid(WAIT_ANY, &status, WUNTRACED);
        } while (!mark_process_status(pid, status)
                 && !job_is_completed(j));
    } else {
        pid = waitpid(-1, &status, WUNTRACED);
//        pid = waitpid(WAIT_ANY, &status, WUNTRACED);
    }
}


int mark_process_status(pid_t pid, int status) {
    job *j;
    process *p;

    if (pid > 0) {
        /* Update the record for the process.  */
        for (j = first_job; j; j = j->next)
            for (p = j->first_process; p; p = p->next)
                if (p->pid == pid) {
                    p->status = status;
                    if (WIFSTOPPED (status)) {
                        p->stopped = 1;
                    } else {
                        p->completed = 1;
                        if (WIFSIGNALED (status)) {
                            fprintf(stderr, "%d: Terminated by signal %d.\n",
                                    (int) pid, WTERMSIG (p->status));
                        }
                    }
                    return 0;
                }
        fprintf(stderr, "No child process %d.\n", pid);
        return -1;
    } else if (pid == 0 || errno == ECHILD) {
        /* No processes ready to report.  */
        return -1;
    } else {
        /* Other weird errors.  */
        perror("waitpid");
        return -1;
    }
}

/* Return true if all processes in the job have completed.  */
int job_is_completed(job *j) {
    process *p;

    for (p = j->first_process; p; p = p->next)
        if (!p->completed)
            return 0;
    return 1;
}

/* Return true if all processes in the job have stopped or completed.  */
int job_is_stopped(job *j) {
    process *p;

    for (p = j->first_process; p; p = p->next)
        if (!p->completed && !p->stopped)
            return 0;
    return 1;
}

job *create_job(void) {
    job *j = (job *) malloc(sizeof(job));
    if (!j) {
        perror("malloc job");
        return NULL;
    }
    j->first_process = NULL;
    j->pgid = 0;
    j->infile = NULL;
    j->outfile = NULL;
    j->stdin = STDIN_FILENO;
    j->stdout = STDOUT_FILENO;
    j->stderr = STDERR_FILENO;
    j->notified = 0;
    return j;
}

process *create_process(void) {
    process *p = (process *) malloc(sizeof(process));
    if (!p) {
        perror("malloc process");
        return NULL;
    }
    p->next = NULL;
    p->argv = NULL;
    p->argc = 0;
    p->completed = 0;
    p->stopped = 0;
    return p;
}

void update_status(void) {
    int status;
    pid_t pid;

    do {
        pid = waitpid(-1, &status, WUNTRACED | WNOHANG);
        pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
    } while (!mark_process_status(pid, status));
}

void free_process(process *p) {
    if (!p->argv) return;
//    for (int i = 0; p->argv[i] && i < p->argc; i++) {
//        printf("%d\n",i);
//        free((p->argv[i]));
//        (p->argv[i]) = NULL;
//    }
    free(p->argv);
}

void free_job(job *j) {
    if (!j) return;
    process *p = j->first_process;
    while (p) {
        process *tmp = p->next;
        free_process(p);
        p = tmp;
    }
//    printf("done free process\n");
    free(j->infile);
    free(j->outfile);
//    printf("done free job\n");
}

job *find_job(pid_t pgid) {
    job *j;
    for (j = first_job; j; j = j->next) {
        if (j->pgid == pgid) {
            return j;
        }
    }
    return NULL;
}

job *find_job_id(int id) {
    if (id < 1) return NULL;
    job *j;
    for (j = first_job; j; j = j->next)
        if (j->id == id)
            return j;
    return NULL;
}

void do_job_notification(void) {
    job *j, *jlast, *jnext;
//    process *p;

    /* Update status information for child processes.  */
    update_status();
    jlast = NULL;
    for (j = first_job; j; j = jnext) {
        printf("NOTIFYING...\n");
        jnext = j->next;
        /* If all processes have completed, tell the user the job has
           completed and delete it from the list of active jobs.  */
        if (job_is_completed(j)) {
            format_job_info(j, "completed");
            if (jlast) {
                printf("LAST\n");
                jlast->next = jnext;
            } else {
                printf("SET FIRST\n");
                first_job = jnext;
            }
            free_job(j);
        }

            /* Notify the user about stopped jobs,
               marking them so that we won’t do this more than once.  */
        else if (job_is_stopped(j) && !j->notified) {
            format_job_info(j, "stopped");
            j->notified = 1;
            jlast = j;
        }

            /* Don’t say anything about jobs that are still running.  */
        else
            jlast = j;
    }
}

void mark_job_as_running(job *j) {
    process *p;

    for (p = j->first_process; p; p = p->next)
        p->stopped = 0;
    j->notified = 0;
}

void continue_job(job *j, int foreground) {
    mark_job_as_running(j);
    if (foreground) {
        put_job_in_foreground(j, 1);
    } else {
        put_job_in_background(j, 1);
    }
}

void prompt() {
    printf("icsh> ");
}

static void pSigHandler(int signo) {
    switch (signo) {
        case SIGINT:
            printf("Ctrl+C caught\n");
            fflush(stdout);
            break;
    }
}

/* BUILT-IN STUFF */

/* bif -- built-in function */

/* FUNCTION DECLARATION */
int bif_exit(process *p, int infile, int outfile, int errfile);

int bif_jobs(process *p, int infile, int outfile, int errfile);

int bif_echo(process *p, int infile, int outfile, int errfile);

int bif_fg(process *p, int infile, int outfile, int errfile);

int bif_bg(process *p, int infile, int outfile, int errfile);

/*
 * List of built-in commands
 * */
char *builtin_str[] = {
        "exit\0",
        "jobs\0",
        "echo\0",
        "fg\0",
        "bg\0"
};

/*
 * Corresponding functions
 * */
int (*builtin_func[])(process *p, int infile, int outfile, int errfile) = {
        &bif_exit,
        &bif_jobs,
        &bif_echo,
        &bif_fg,
        &bif_bg
};

int num_builtin() {
    return sizeof(builtin_str) / sizeof(char *);
}

/*
 * IMPLEMENTATIONS
 * */
int bif_exit(process *p, int infile, int outfile, int errfile) {
    printf("EXITING...\n");
    update_status();
    exit(0);
}

void print_process(process *p) {
    for (int i = 0; p->argv[i]; ++i) {
        printf("  %s", p->argv[i]);
    }
    printf("\n");
}

int bif_jobs(process *p, int infile, int outfile, int errfile) {
    if (p->argv[1]) {
        int i;
        int id;
        job *j;
        for (i = 1; p->argv[i]; ++i) {
            id = atoi(p->argv[i]);
            j = find_job_id(id);
            if (j) {
                if (!job_is_completed(j)) {
                    if (job_is_stopped(j)) {
                        dprintf(outfile, "[%d] %ld Stopped\n", j->id, (long) j->pgid);
                    } else {
                        dprintf(outfile, "[%d] %ld Running\n", j->id, (long) j->pgid);
                    }
                } else
                    dprintf(errfile, "jobs: %s : no such job\n", p->argv[i]);
            } else
                dprintf(errfile, "jobs: %s : no such job\n", p->argv[i]);
        }
        return 0;
    }
    job *j;
    /* Update status information for child processes.  */
    update_status();

    for (j = first_job; j; j = j->next) {
        if (!job_is_completed(j) && j->id) {
            if (job_is_stopped(j)) {
                dprintf(outfile, "[%d] %ld Stopped\n", j->id, (long) j->pgid);
            } else {
                dprintf(outfile, "[%d] %ld Running\n", j->id, (long) j->pgid);
            }
        }
    }
    return 0;
}

int bif_echo(process *p, int infile, int outfile, int errfile) {
    if (!p->argv[1]) {
        printf("Usage: echo <string>\n");
        return 0;
    }
    int i;
    for (i = 1; p->argv[i]; ++i) {
        printf("%s ", p->argv[i]);
    }
    printf("\n");
    return 0;
}

int bif_fg(process *p, int infile, int outfile, int errfile) {
    if (p->argv[1]) {
        int i;
        int id;
        job *j;
        for (i = 1; p->argv[i]; ++i) {
            id = atoi(p->argv[i]);
            j = find_job_id(id);
            if (j) {
                if (!job_is_completed(j) && job_is_stopped(j))
                    continue_job(j, 1);
                else
                    dprintf(errfile, "fg: %s : no such job\n", p->argv[i]);
            } else
                dprintf(errfile, "fg: %s : no such job\n", p->argv[i]);
        }
        return 0;
    }
    job *j;
    job *jlast = NULL;
    /* Update status information for child processes.  */
    update_status();

    for (j = first_job; j; j = j->next) {
        if (!job_is_completed(j) && j->id) {
            if (job_is_stopped(j)) {
                jlast = j;
            }
        }
    }

    if (jlast)
        continue_job(jlast, 1);
    else
        dprintf(errfile, "fg: current: no such job\n");
    return 0;
}

int bif_bg(process *p, int infile, int outfile, int errfile) {
    if (p->argv[1]) {
        int i;
        int id;
        job *j;
        for (i = 1; p->argv[i]; ++i) {
            id = atoi(p->argv[i]);
            j = find_job_id(id);
            if (j) {
                if (!job_is_completed(j) && job_is_stopped(j))
                    continue_job(j, 0);
                else
                    dprintf(errfile, "bg: %s : no such job\n", p->argv[i]);
            } else
                dprintf(errfile, "bg: %s : no such job\n", p->argv[i]);
        }
        return 0;
    }
    job *j;
    job *jlast = NULL;
    /* Update status information for child processes.  */
    update_status();

    for (j = first_job; j; j = j->next) {
        if (!job_is_completed(j) && j->id) {
            if (job_is_stopped(j)) {
                jlast = j;
            }
        }
    }

    if (jlast)
        continue_job(jlast, 0);
    else {
        dprintf(errfile, "bg: current: no such job\n");
    }
    return 0;
}

char *skipwhite(char *s) {
    while (isspace(*s)) ++s;
    return s;
}

int launch_builtin(process *p, int infile, int outfile, int errfile) {
    /* Set the std i/o channels of the new process. */
    for (int i = 0; i < num_builtin(); i++) {
        if (strcmp(builtin_str[i], p->argv[0]) == 0) {
            return (*builtin_func[i])(p, infile, outfile, errfile);
        }
    }
    /* built-in not found */
    return -1;
}

#endif