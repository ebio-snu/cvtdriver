# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/tombraid/Works/ebio/cvtdriver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tombraid/Works/ebio/cvtdriver/build

# Include any dependencies generated for this target.
include CMakeFiles/dssample.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dssample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dssample.dir/flags.make

CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o: CMakeFiles/dssample.dir/flags.make
CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o: ../sample/dssampledriver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tombraid/Works/ebio/cvtdriver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o -c /home/tombraid/Works/ebio/cvtdriver/sample/dssampledriver.cpp

CMakeFiles/dssample.dir/sample/dssampledriver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dssample.dir/sample/dssampledriver.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tombraid/Works/ebio/cvtdriver/sample/dssampledriver.cpp > CMakeFiles/dssample.dir/sample/dssampledriver.cpp.i

CMakeFiles/dssample.dir/sample/dssampledriver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dssample.dir/sample/dssampledriver.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tombraid/Works/ebio/cvtdriver/sample/dssampledriver.cpp -o CMakeFiles/dssample.dir/sample/dssampledriver.cpp.s

CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o.requires:

.PHONY : CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o.requires

CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o.provides: CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o.requires
	$(MAKE) -f CMakeFiles/dssample.dir/build.make CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o.provides.build
.PHONY : CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o.provides

CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o.provides.build: CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o


# Object files for target dssample
dssample_OBJECTS = \
"CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o"

# External object files for target dssample
dssample_EXTERNAL_OBJECTS =

../lib/libdssample.so: CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o
../lib/libdssample.so: CMakeFiles/dssample.dir/build.make
../lib/libdssample.so: /usr/local/lib/libboost_system.so
../lib/libdssample.so: /usr/local/lib/libboost_date_time.so
../lib/libdssample.so: /usr/local/lib/libboost_filesystem.so
../lib/libdssample.so: /usr/local/lib/libboost_iostreams.so
../lib/libdssample.so: /usr/lib/x86_64-linux-gnu/libglog.so
../lib/libdssample.so: CMakeFiles/dssample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tombraid/Works/ebio/cvtdriver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../lib/libdssample.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dssample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dssample.dir/build: ../lib/libdssample.so

.PHONY : CMakeFiles/dssample.dir/build

CMakeFiles/dssample.dir/requires: CMakeFiles/dssample.dir/sample/dssampledriver.cpp.o.requires

.PHONY : CMakeFiles/dssample.dir/requires

CMakeFiles/dssample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dssample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dssample.dir/clean

CMakeFiles/dssample.dir/depend:
	cd /home/tombraid/Works/ebio/cvtdriver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tombraid/Works/ebio/cvtdriver /home/tombraid/Works/ebio/cvtdriver /home/tombraid/Works/ebio/cvtdriver/build /home/tombraid/Works/ebio/cvtdriver/build /home/tombraid/Works/ebio/cvtdriver/build/CMakeFiles/dssample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dssample.dir/depend
