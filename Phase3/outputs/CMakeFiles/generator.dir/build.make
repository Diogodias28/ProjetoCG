# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs

# Include any dependencies generated for this target.
include CMakeFiles/generator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/generator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/generator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/generator.dir/flags.make

CMakeFiles/generator.dir/codegen:
.PHONY : CMakeFiles/generator.dir/codegen

CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.o: CMakeFiles/generator.dir/flags.make
CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.o: /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp
CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.o: CMakeFiles/generator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.o -MF CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.o.d -o CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.o -c /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp

CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp > CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.i

CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp -o CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.s

# Object files for target generator
generator_OBJECTS = \
"CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.o"

# External object files for target generator
generator_EXTERNAL_OBJECTS =

generator: CMakeFiles/generator.dir/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/gen/generator.cpp.o
generator: CMakeFiles/generator.dir/build.make
generator: libdata_structs.a
generator: libtinyXML.a
generator: CMakeFiles/generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable generator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/generator.dir/build: generator
.PHONY : CMakeFiles/generator.dir/build

CMakeFiles/generator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/generator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/generator.dir/clean

CMakeFiles/generator.dir/depend:
	cd /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs /Users/patriciabastos/Documents/universidade/CG/projetoGitHub/phase3/outputs/CMakeFiles/generator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/generator.dir/depend

