# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/cmake-build-default

# Include any dependencies generated for this target.
include CMakeFiles/fork_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fork_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fork_example.dir/flags.make

CMakeFiles/fork_example.dir/examples/fork_example.c.o: CMakeFiles/fork_example.dir/flags.make
CMakeFiles/fork_example.dir/examples/fork_example.c.o: ../examples/fork_example.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/cmake-build-default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/fork_example.dir/examples/fork_example.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fork_example.dir/examples/fork_example.c.o   -c /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/examples/fork_example.c

CMakeFiles/fork_example.dir/examples/fork_example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fork_example.dir/examples/fork_example.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/examples/fork_example.c > CMakeFiles/fork_example.dir/examples/fork_example.c.i

CMakeFiles/fork_example.dir/examples/fork_example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fork_example.dir/examples/fork_example.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/examples/fork_example.c -o CMakeFiles/fork_example.dir/examples/fork_example.c.s

CMakeFiles/fork_example.dir/examples/fork_example.c.o.requires:

.PHONY : CMakeFiles/fork_example.dir/examples/fork_example.c.o.requires

CMakeFiles/fork_example.dir/examples/fork_example.c.o.provides: CMakeFiles/fork_example.dir/examples/fork_example.c.o.requires
	$(MAKE) -f CMakeFiles/fork_example.dir/build.make CMakeFiles/fork_example.dir/examples/fork_example.c.o.provides.build
.PHONY : CMakeFiles/fork_example.dir/examples/fork_example.c.o.provides

CMakeFiles/fork_example.dir/examples/fork_example.c.o.provides.build: CMakeFiles/fork_example.dir/examples/fork_example.c.o


# Object files for target fork_example
fork_example_OBJECTS = \
"CMakeFiles/fork_example.dir/examples/fork_example.c.o"

# External object files for target fork_example
fork_example_EXTERNAL_OBJECTS =

fork_example: CMakeFiles/fork_example.dir/examples/fork_example.c.o
fork_example: CMakeFiles/fork_example.dir/build.make
fork_example: CMakeFiles/fork_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/cmake-build-default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable fork_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fork_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fork_example.dir/build: fork_example

.PHONY : CMakeFiles/fork_example.dir/build

CMakeFiles/fork_example.dir/requires: CMakeFiles/fork_example.dir/examples/fork_example.c.o.requires

.PHONY : CMakeFiles/fork_example.dir/requires

CMakeFiles/fork_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fork_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fork_example.dir/clean

CMakeFiles/fork_example.dir/depend:
	cd /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/cmake-build-default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/cmake-build-default /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/cmake-build-default /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh/cmake-build-default/CMakeFiles/fork_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fork_example.dir/depend

