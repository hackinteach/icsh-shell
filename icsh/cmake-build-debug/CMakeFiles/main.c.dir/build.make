# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/main.c.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.c.dir/flags.make

CMakeFiles/main.c.dir/execvp_example.c.o: CMakeFiles/main.c.dir/flags.make
CMakeFiles/main.c.dir/execvp_example.c.o: ../execvp_example.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.c.dir/execvp_example.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.c.dir/execvp_example.c.o   -c /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/execvp_example.c

CMakeFiles/main.c.dir/execvp_example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.c.dir/execvp_example.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/execvp_example.c > CMakeFiles/main.c.dir/execvp_example.c.i

CMakeFiles/main.c.dir/execvp_example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.c.dir/execvp_example.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/execvp_example.c -o CMakeFiles/main.c.dir/execvp_example.c.s

CMakeFiles/main.c.dir/execvp_example.c.o.requires:

.PHONY : CMakeFiles/main.c.dir/execvp_example.c.o.requires

CMakeFiles/main.c.dir/execvp_example.c.o.provides: CMakeFiles/main.c.dir/execvp_example.c.o.requires
	$(MAKE) -f CMakeFiles/main.c.dir/build.make CMakeFiles/main.c.dir/execvp_example.c.o.provides.build
.PHONY : CMakeFiles/main.c.dir/execvp_example.c.o.provides

CMakeFiles/main.c.dir/execvp_example.c.o.provides.build: CMakeFiles/main.c.dir/execvp_example.c.o


# Object files for target main.c
main_c_OBJECTS = \
"CMakeFiles/main.c.dir/execvp_example.c.o"

# External object files for target main.c
main_c_EXTERNAL_OBJECTS =

main.c: CMakeFiles/main.c.dir/execvp_example.c.o
main.c: CMakeFiles/main.c.dir/build.make
main.c: CMakeFiles/main.c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable main.c"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.c.dir/build: main.c

.PHONY : CMakeFiles/main.c.dir/build

CMakeFiles/main.c.dir/requires: CMakeFiles/main.c.dir/execvp_example.c.o.requires

.PHONY : CMakeFiles/main.c.dir/requires

CMakeFiles/main.c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.c.dir/clean

CMakeFiles/main.c.dir/depend:
	cd /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-debug /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-debug /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-debug/CMakeFiles/main.c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.c.dir/depend

