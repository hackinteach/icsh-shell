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
CMAKE_BINARY_DIR = /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-default

# Include any dependencies generated for this target.
include CMakeFiles/icsh.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/icsh.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/icsh.dir/flags.make

CMakeFiles/icsh.dir/icsh.c.o: CMakeFiles/icsh.dir/flags.make
CMakeFiles/icsh.dir/icsh.c.o: ../icsh.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/icsh.dir/icsh.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/icsh.dir/icsh.c.o   -c /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh.c

CMakeFiles/icsh.dir/icsh.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/icsh.dir/icsh.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh.c > CMakeFiles/icsh.dir/icsh.c.i

CMakeFiles/icsh.dir/icsh.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/icsh.dir/icsh.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/icsh.c -o CMakeFiles/icsh.dir/icsh.c.s

CMakeFiles/icsh.dir/icsh.c.o.requires:

.PHONY : CMakeFiles/icsh.dir/icsh.c.o.requires

CMakeFiles/icsh.dir/icsh.c.o.provides: CMakeFiles/icsh.dir/icsh.c.o.requires
	$(MAKE) -f CMakeFiles/icsh.dir/build.make CMakeFiles/icsh.dir/icsh.c.o.provides.build
.PHONY : CMakeFiles/icsh.dir/icsh.c.o.provides

CMakeFiles/icsh.dir/icsh.c.o.provides.build: CMakeFiles/icsh.dir/icsh.c.o


CMakeFiles/icsh.dir/shell.c.o: CMakeFiles/icsh.dir/flags.make
CMakeFiles/icsh.dir/shell.c.o: ../shell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/icsh.dir/shell.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/icsh.dir/shell.c.o   -c /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/shell.c

CMakeFiles/icsh.dir/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/icsh.dir/shell.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/shell.c > CMakeFiles/icsh.dir/shell.c.i

CMakeFiles/icsh.dir/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/icsh.dir/shell.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/shell.c -o CMakeFiles/icsh.dir/shell.c.s

CMakeFiles/icsh.dir/shell.c.o.requires:

.PHONY : CMakeFiles/icsh.dir/shell.c.o.requires

CMakeFiles/icsh.dir/shell.c.o.provides: CMakeFiles/icsh.dir/shell.c.o.requires
	$(MAKE) -f CMakeFiles/icsh.dir/build.make CMakeFiles/icsh.dir/shell.c.o.provides.build
.PHONY : CMakeFiles/icsh.dir/shell.c.o.provides

CMakeFiles/icsh.dir/shell.c.o.provides.build: CMakeFiles/icsh.dir/shell.c.o


# Object files for target icsh
icsh_OBJECTS = \
"CMakeFiles/icsh.dir/icsh.c.o" \
"CMakeFiles/icsh.dir/shell.c.o"

# External object files for target icsh
icsh_EXTERNAL_OBJECTS =

icsh: CMakeFiles/icsh.dir/icsh.c.o
icsh: CMakeFiles/icsh.dir/shell.c.o
icsh: CMakeFiles/icsh.dir/build.make
icsh: CMakeFiles/icsh.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable icsh"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/icsh.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/icsh.dir/build: icsh

.PHONY : CMakeFiles/icsh.dir/build

CMakeFiles/icsh.dir/requires: CMakeFiles/icsh.dir/icsh.c.o.requires
CMakeFiles/icsh.dir/requires: CMakeFiles/icsh.dir/shell.c.o.requires

.PHONY : CMakeFiles/icsh.dir/requires

CMakeFiles/icsh.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/icsh.dir/cmake_clean.cmake
.PHONY : CMakeFiles/icsh.dir/clean

CMakeFiles/icsh.dir/depend:
	cd /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-default /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-default /Users/hackinteachk./Desktop/T2-2018/OS/Homeworks/icsh/cmake-build-default/CMakeFiles/icsh.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/icsh.dir/depend
