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
include include/CMakeFiles/canvas.dir/depend.make

# Include the progress variables for this target.
include include/CMakeFiles/canvas.dir/progress.make

# Include the compile flags for this target's objects.
include include/CMakeFiles/canvas.dir/flags.make

include/CMakeFiles/canvas.dir/__/src/canvas.cpp.o: include/CMakeFiles/canvas.dir/flags.make
include/CMakeFiles/canvas.dir/__/src/canvas.cpp.o: ../src/canvas.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matteo/code/movie_graph/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object include/CMakeFiles/canvas.dir/__/src/canvas.cpp.o"
	cd /home/matteo/code/movie_graph/build/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/canvas.dir/__/src/canvas.cpp.o -c /home/matteo/code/movie_graph/src/canvas.cpp

include/CMakeFiles/canvas.dir/__/src/canvas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/canvas.dir/__/src/canvas.cpp.i"
	cd /home/matteo/code/movie_graph/build/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matteo/code/movie_graph/src/canvas.cpp > CMakeFiles/canvas.dir/__/src/canvas.cpp.i

include/CMakeFiles/canvas.dir/__/src/canvas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/canvas.dir/__/src/canvas.cpp.s"
	cd /home/matteo/code/movie_graph/build/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matteo/code/movie_graph/src/canvas.cpp -o CMakeFiles/canvas.dir/__/src/canvas.cpp.s

# Object files for target canvas
canvas_OBJECTS = \
"CMakeFiles/canvas.dir/__/src/canvas.cpp.o"

# External object files for target canvas
canvas_EXTERNAL_OBJECTS =

include/libcanvas.a: include/CMakeFiles/canvas.dir/__/src/canvas.cpp.o
include/libcanvas.a: include/CMakeFiles/canvas.dir/build.make
include/libcanvas.a: include/CMakeFiles/canvas.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matteo/code/movie_graph/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcanvas.a"
	cd /home/matteo/code/movie_graph/build/include && $(CMAKE_COMMAND) -P CMakeFiles/canvas.dir/cmake_clean_target.cmake
	cd /home/matteo/code/movie_graph/build/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/canvas.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/CMakeFiles/canvas.dir/build: include/libcanvas.a

.PHONY : include/CMakeFiles/canvas.dir/build

include/CMakeFiles/canvas.dir/clean:
	cd /home/matteo/code/movie_graph/build/include && $(CMAKE_COMMAND) -P CMakeFiles/canvas.dir/cmake_clean.cmake
.PHONY : include/CMakeFiles/canvas.dir/clean

include/CMakeFiles/canvas.dir/depend:
	cd /home/matteo/code/movie_graph/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matteo/code/movie_graph /home/matteo/code/movie_graph/include /home/matteo/code/movie_graph/build /home/matteo/code/movie_graph/build/include /home/matteo/code/movie_graph/build/include/CMakeFiles/canvas.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/CMakeFiles/canvas.dir/depend

