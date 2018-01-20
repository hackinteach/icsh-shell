cmake_minimum_required(VERSION 3.8)
project(icsh)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES icsh.c)

add_executable(icsh icsh.c shell.c shell.h builtin.c builtin.h)

# Example stuff.
add_executable(execvp_example ./examples/execvp_example.c)
add_executable(caller ./examples/exec_caller.c builtin.c builtin.h)
add_executable(fork_example ./examples/fork_example.c)
add_executable(launch ./examples/launch.c)