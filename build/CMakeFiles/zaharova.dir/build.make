# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/filin_vg/lab325/stm2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/filin_vg/lab325/stm2/build

# Include any dependencies generated for this target.
include CMakeFiles/zaharova.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/zaharova.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/zaharova.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zaharova.dir/flags.make

CMakeFiles/zaharova.dir/src/main.cpp.obj: CMakeFiles/zaharova.dir/flags.make
CMakeFiles/zaharova.dir/src/main.cpp.obj: /home/filin_vg/lab325/stm2/src/main.cpp
CMakeFiles/zaharova.dir/src/main.cpp.obj: CMakeFiles/zaharova.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/filin_vg/lab325/stm2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/zaharova.dir/src/main.cpp.obj"
	/usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/zaharova.dir/src/main.cpp.obj -MF CMakeFiles/zaharova.dir/src/main.cpp.obj.d -o CMakeFiles/zaharova.dir/src/main.cpp.obj -c /home/filin_vg/lab325/stm2/src/main.cpp

CMakeFiles/zaharova.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zaharova.dir/src/main.cpp.i"
	/usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/filin_vg/lab325/stm2/src/main.cpp > CMakeFiles/zaharova.dir/src/main.cpp.i

CMakeFiles/zaharova.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zaharova.dir/src/main.cpp.s"
	/usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/filin_vg/lab325/stm2/src/main.cpp -o CMakeFiles/zaharova.dir/src/main.cpp.s

# Object files for target zaharova
zaharova_OBJECTS = \
"CMakeFiles/zaharova.dir/src/main.cpp.obj"

# External object files for target zaharova
zaharova_EXTERNAL_OBJECTS =

zaharova: CMakeFiles/zaharova.dir/src/main.cpp.obj
zaharova: CMakeFiles/zaharova.dir/build.make
zaharova: _deps/libopencm3_repo-src/lib/libopencm3_stm32f4.a
zaharova: CMakeFiles/zaharova.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/filin_vg/lab325/stm2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable zaharova"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zaharova.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zaharova.dir/build: zaharova
.PHONY : CMakeFiles/zaharova.dir/build

CMakeFiles/zaharova.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zaharova.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zaharova.dir/clean

CMakeFiles/zaharova.dir/depend:
	cd /home/filin_vg/lab325/stm2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/filin_vg/lab325/stm2 /home/filin_vg/lab325/stm2 /home/filin_vg/lab325/stm2/build /home/filin_vg/lab325/stm2/build /home/filin_vg/lab325/stm2/build/CMakeFiles/zaharova.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zaharova.dir/depend

