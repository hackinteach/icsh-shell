//
// Created by Hackinteach K. on 18/1/2018 AD.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void forkExample1();
void forkExample2();
int forkExample3();


int main(int argc, char** argv) {
    printf("From execvp_example.c\n");
    pid_t  child;
    int    cstatus;  /* Exit status of child. */
    pid_t  c;        /* Pid of child to be returned by wait. */

//    char *args[3];   /* List of arguments for the child process. */
//    /* Set up arguments to run an exec in the child process.  */
//    /* (This example runs the "ls" program with "-l" option.) */
//    args[0] = "ls";   args[1] = "-l";
//    args[2] = NULL;   /* Indicates the end of arguments. */

    if ((child = fork()) == 0) { /* Child process. */
        printf("Child: PID of Child = %ld\n", (long) getpid());


        execvp(argv[1], argv+1); /* arg[0] has the command name. */


        /* If the child process reaches this point, then  */
        /* execvp must have failed.                       */
        fprintf(stderr, "Child process could not do execvp.\n");
        exit(1); }
    else { /* Parent process. */
        if (child == (pid_t)(-1)) {
            fprintf(stderr, "Fork failed.\n"); exit(1);
        }
        else {
            c = wait(&cstatus); /* Wait for child to complete. */
            printf("Parent: Child  %ld exited with status = %d\n",
                   (long) c, cstatus);
        } }
    return  0;
}