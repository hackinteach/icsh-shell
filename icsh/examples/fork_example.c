//
// Created by Hackinteach K. on 18/1/2018 AD.
//
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

void exec(int argcm, char **argv);


int main(int argc, char **argv) {
    for(int i=0;i<2;i++){
        forkExample3();
    }
}

/*
 * This method calls execvp() with path to executable file (argv[1] from main)
 * and argument list (argv[2] for flags).
 * */
void exec(int argc, char **argv) {
    char *cmd = argv[0];
    char *opt = argv[1];
    char *opt2 = argv[2];
    argv[argc] = NULL;
    printf(
            "cmd = %s\n"
                    "opt = %s\n"
                    "opt2 = %s\n"
                    "argc = %d\n"
                    "\n\n",
            cmd, opt, opt2, argc);

    pid_t child;
    int cstatus;  /* Exit status of child. */
    pid_t c;

    if ((child = fork()) == 0) {
        printf("Child: PID of Child = %ld\n", (long) getpid());
        execvp(cmd, argv);
        /*Print error message*/
        fprintf(stderr, "Child process could not do execvp.\n");
    } else {
        if (child == (pid_t) (-1)) {
            fprintf(stderr, "Fork failed.\n");
            exit(1);
        } else {
            c = wait(&cstatus); /* Wait for child to complete. */
            printf("Parent: Child  %ld exited with status = %d\n",
                   (long) c, cstatus);
        }
    }
}

void forkExample1() {
    int value = 0;
    fork();
    value++;
    fork();
    value++;
    fork();
    value++;
    printf("value = %d\n", value);
}

void forkExample2() {
    int val = 0;
    if (fork() == 0) {
        printf("Child has x = %d.\n", ++val);
    } else {
        printf("Parent has x = %d.\n", --val);
    }
}

int forkExample3() {
    int counter = 0;
    pid_t pid = fork();
    printf("---Begin of program execution---\n");
    if (pid == 0) {
        // child process
        for (int j = 0; j < 5;j++) {
            printf("Child process : counter = %d\n", ++counter);
        }
    } else if (pid > 0) {
        for (int j = 0; j < 5; j++) {
            printf("Parent process : counter = %d\n", ++counter);
        }
    } else {
        printf("forked failed\n");
        return 1;
    }
    printf("---end of program---\n");
    return 0;
}


