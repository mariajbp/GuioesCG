# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/hc/Desktop/clion-2019.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/hc/Desktop/clion-2019.3.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hc/Desktop/cg/GuioesCG/Guiao12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hc/Desktop/cg/GuioesCG/Guiao12/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/class12.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/class12.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/class12.dir/flags.make

CMakeFiles/class12.dir/main.cpp.o: CMakeFiles/class12.dir/flags.make
CMakeFiles/class12.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hc/Desktop/cg/GuioesCG/Guiao12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/class12.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/class12.dir/main.cpp.o -c /home/hc/Desktop/cg/GuioesCG/Guiao12/main.cpp

CMakeFiles/class12.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class12.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hc/Desktop/cg/GuioesCG/Guiao12/main.cpp > CMakeFiles/class12.dir/main.cpp.i

CMakeFiles/class12.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class12.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hc/Desktop/cg/GuioesCG/Guiao12/main.cpp -o CMakeFiles/class12.dir/main.cpp.s

# Object files for target class12
class12_OBJECTS = \
"CMakeFiles/class12.dir/main.cpp.o"

# External object files for target class12
class12_EXTERNAL_OBJECTS =

class12: CMakeFiles/class12.dir/main.cpp.o
class12: CMakeFiles/class12.dir/build.make
class12: /usr/lib/x86_64-linux-gnu/libGL.so
class12: /usr/lib/x86_64-linux-gnu/libGLU.so
class12: /usr/lib/x86_64-linux-gnu/libglut.so
class12: /usr/lib/x86_64-linux-gnu/libXmu.so
class12: /usr/lib/x86_64-linux-gnu/libXi.so
class12: CMakeFiles/class12.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hc/Desktop/cg/GuioesCG/Guiao12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class12"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/class12.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/class12.dir/build: class12

.PHONY : CMakeFiles/class12.dir/build

CMakeFiles/class12.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/class12.dir/cmake_clean.cmake
.PHONY : CMakeFiles/class12.dir/clean

CMakeFiles/class12.dir/depend:
	cd /home/hc/Desktop/cg/GuioesCG/Guiao12/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hc/Desktop/cg/GuioesCG/Guiao12 /home/hc/Desktop/cg/GuioesCG/Guiao12 /home/hc/Desktop/cg/GuioesCG/Guiao12/cmake-build-debug /home/hc/Desktop/cg/GuioesCG/Guiao12/cmake-build-debug /home/hc/Desktop/cg/GuioesCG/Guiao12/cmake-build-debug/CMakeFiles/class12.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/class12.dir/depend

