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

#define MAX_LINE_LEN    80
#define MAX_ARGS    64
#define MAX_ARG_LEN     1024
#define WHITESPACE " \t\n"


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
    int foreground;
    int valid;
} job;

/* Shell's attributes */
pid_t shell_pgid;
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;
job *first_job;
int lastStatus;

/* Misc function*/
void init_shell();
int parse_command(char *line, job *j);
void launch_process(process *p, pid_t pgid,
                    int infile, int outfile, int errfile,
                    int foreground);
void launch_job(job *j, int foreground, int *id);
void put_job_in_foreground(job *j, int cont);
void put_job_in_background(job *j, int cont);
void format_job_info(job *j, const char *status);
void wait_for_job(job *j);
int mark_process_status(pid_t pid, int status);
int job_is_completed(job *j);
int job_is_stopped(job *j);
job* create_job(void);
process *create_process(void);
void update_status(void);
void free_process(process* p);
void free_job(job *j);
job* find_job(pid_t pgid);
job* find_job_id(int id);
void do_job_notification(void);
void mark_job_as_running(job *j);
void continue_job(job *j, int foreground);
void prompt();
void print_job (job* j);
void print_process(process *p);
//static void pSigHandler(int signo);

/* Built in  */
/* FUNCTION DECLARATION */
int bif_exit(process *p, int infile, int outfile, int errfile);

int bif_jobs(process *p, int infile, int outfile, int errfile);

int bif_echo(process *p, int infile, int outfile, int errfile);

int bif_fg(process *p, int infile, int outfile, int errfile);

int bif_bg(process *p, int infile, int outfile, int errfile);

int launch_built_in(process *p, int infile, int outfile, int errfile);
#endif
