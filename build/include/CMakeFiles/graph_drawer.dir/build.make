# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/matteo/code/movie_graph

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matteo/code/movie_graph/build

# Include any dependencies generated for this target.
include include/CMakeFiles/graph_drawer.dir/depend.make

# Include the progress variables for this target.
include include/CMakeFiles/graph_drawer.dir/progress.make

# Include the compile flags for this target's objects.
include include/CMakeFiles/graph_drawer.dir/flags.make

include/CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.o: include/CMakeFiles/graph_drawer.dir/flags.make
include/CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.o: ../src/graph_drawer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matteo/code/movie_graph/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object include/CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.o"
	cd /home/matteo/code/movie_graph/build/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.o -c /home/matteo/code/movie_graph/src/graph_drawer.cpp

include/CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.i"
	cd /home/matteo/code/movie_graph/build/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matteo/code/movie_graph/src/graph_drawer.cpp > CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.i

include/CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.s"
	cd /home/matteo/code/movie_graph/build/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matteo/code/movie_graph/src/graph_drawer.cpp -o CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.s

# Object files for target graph_drawer
graph_drawer_OBJECTS = \
"CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.o"

# External object files for target graph_drawer
graph_drawer_EXTERNAL_OBJECTS =

include/libgraph_drawer.a: include/CMakeFiles/graph_drawer.dir/__/src/graph_drawer.cpp.o
include/libgraph_drawer.a: include/CMakeFiles/graph_drawer.dir/build.make
include/libgraph_drawer.a: include/CMakeFiles/graph_drawer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matteo/code/movie_graph/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgraph_drawer.a"
	cd /home/matteo/code/movie_graph/build/include && $(CMAKE_COMMAND) -P CMakeFiles/graph_drawer.dir/cmake_clean_target.cmake
	cd /home/matteo/code/movie_graph/build/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graph_drawer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/CMakeFiles/graph_drawer.dir/build: include/libgraph_drawer.a

.PHONY : include/CMakeFiles/graph_drawer.dir/build

include/CMakeFiles/graph_drawer.dir/clean:
	cd /home/matteo/code/movie_graph/build/include && $(CMAKE_COMMAND) -P CMakeFiles/graph_drawer.dir/cmake_clean.cmake
.PHONY : include/CMakeFiles/graph_drawer.dir/clean

include/CMakeFiles/graph_drawer.dir/depend:
	cd /home/matteo/code/movie_graph/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matteo/code/movie_graph /home/matteo/code/movie_graph/include /home/matteo/code/movie_graph/build /home/matteo/code/movie_graph/build/include /home/matteo/code/movie_graph/build/include/CMakeFiles/graph_drawer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/CMakeFiles/graph_drawer.dir/depend

