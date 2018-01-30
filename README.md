# ICSH : simple shell implementation in C.

This repository is part of **Operating System** course's assignment 1 (ICCS 222).

[Assignment 1.pdf](https://github.com/hackinteach/icsh-shell/blob/master/Assignment%201:%20IC%20Shell.pdf)

Lecturer : Dr.Sunsern Cheamanunkul


### Files
----
**Download here : [Link](https://github.com/hackinteach/icsh-shell/archive/master.zip)**

- icsh.c   : this is where I combined all the code together.
- shell.h : structs and functions declaration.
- shell.c : main part of the shell.

## Getting Started

The implementation of this ICSH shell is based on [GNU website](https://www.gnu.org/software/libc/manual/html_node/Implementing-a-Shell.html#Implementing-a-Shell) with more implementations on missing pieces. The main part of this project is about to use `execvp() ` and `fork()` commands in order to understand the processes and jobs creation.

If you don't quite understand what these lines of codes mean, I recommend you find an easier version of shell ( huge examples from Googling ) and then come back and see what these are.


## Compile
To compile this ICSH shell, just simply run `make` and then  `./icsh`, that's all :)


## Built-in Commands

 - `echo [string]` : print **string** to **stdout**
 - `echo $?` : print the exit status of the last process.
 - `fg %<int>` : move the job ( id = **int** ) into the **foreground**.
 - `bg %<int>` : move the job ( id = **int** ) into the **background**.
 - `jobs` : list for jobs that are currently executing in the background and jobs that are currently suspended.

## Other Commands
Since this shell is implemented based on POSIX system, available commands are vary among Operating System, meaning that they differ from one to another computer. Most likely to be available commands are `sleep`, `pwd`, `ls -FLAGS`, etc.



### Comments
----
Since this is my first Git repository that contains a formal README.md, I would really appreciate if you can give me some suggestions or comments either about the *Shell Implementation* or my *ReadMe*.  Thank you for taking some times looking at this repo :)

Hackinteach K.
