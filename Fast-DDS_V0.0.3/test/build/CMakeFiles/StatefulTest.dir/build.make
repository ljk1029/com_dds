# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/build

# Include any dependencies generated for this target.
include CMakeFiles/StatefulTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/StatefulTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/StatefulTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StatefulTest.dir/flags.make

CMakeFiles/StatefulTest.dir/StatefulTest.cpp.o: CMakeFiles/StatefulTest.dir/flags.make
CMakeFiles/StatefulTest.dir/StatefulTest.cpp.o: ../StatefulTest.cpp
CMakeFiles/StatefulTest.dir/StatefulTest.cpp.o: CMakeFiles/StatefulTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StatefulTest.dir/StatefulTest.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StatefulTest.dir/StatefulTest.cpp.o -MF CMakeFiles/StatefulTest.dir/StatefulTest.cpp.o.d -o CMakeFiles/StatefulTest.dir/StatefulTest.cpp.o -c /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/StatefulTest.cpp

CMakeFiles/StatefulTest.dir/StatefulTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StatefulTest.dir/StatefulTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/StatefulTest.cpp > CMakeFiles/StatefulTest.dir/StatefulTest.cpp.i

CMakeFiles/StatefulTest.dir/StatefulTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StatefulTest.dir/StatefulTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/StatefulTest.cpp -o CMakeFiles/StatefulTest.dir/StatefulTest.cpp.s

# Object files for target StatefulTest
StatefulTest_OBJECTS = \
"CMakeFiles/StatefulTest.dir/StatefulTest.cpp.o"

# External object files for target StatefulTest
StatefulTest_EXTERNAL_OBJECTS =

StatefulTest: CMakeFiles/StatefulTest.dir/StatefulTest.cpp.o
StatefulTest: CMakeFiles/StatefulTest.dir/build.make
StatefulTest: CMakeFiles/StatefulTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable StatefulTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StatefulTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StatefulTest.dir/build: StatefulTest
.PHONY : CMakeFiles/StatefulTest.dir/build

CMakeFiles/StatefulTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StatefulTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StatefulTest.dir/clean

CMakeFiles/StatefulTest.dir/depend:
	cd /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/build /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/build /home/ljk/gitlab/com_dds/Fast-DDS_V0.0.3/test/build/CMakeFiles/StatefulTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StatefulTest.dir/depend

