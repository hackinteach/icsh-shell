#include <termios.h>
#include <string.h>

#define ARG_MAX 256
#define MAX_LINE_LEN    80
#define MAX_ARG_LEN     16
#define WHITESPACE " .,\t\n"

/* A Process is a single Process.  */
typedef struct process
{
    struct Process *next;       /* next Process in pipeline */
    char **argv;                /* for exec */
    pid_t pid;                  /* Process ID */
    char completed;             /* true if Process has completed */
    char stopped;               /* true if Process has stopped */
    int status;                 /* reported status value */
} Process;

/* A Job is a pipeline of processes.  */
typedef struct job
{
    struct Job *next;           /* next active Job */
    char *command;              /* command line, used for messages */
    Process *first_process;     /* list of processes in this Job */
    pid_t pgid;                 /* Process group ID */
    char notified;              /* true if user told about stopped Job */
    struct termios tmodes;      /* saved terminal modes */
    int stdin, stdout, stderr;  /* standard i/o channels */
} Job;

/* Parser from main */
int parse_command(char  *line, Process *p);

/* Find the active job with the indicated 'pgid' */
Job* find_job(pid_t pgid);

/* Return true if all processes in the Job have stopped or completed */
int job_is_stopped(Job *j);

/* Return true if all processes in the Job have completed */
int job_is_completed(Job *j);

/* Cleaning stuff */
void free_job (Job *j);

/* Cleaning stuff */
void free_process (Process* p);



