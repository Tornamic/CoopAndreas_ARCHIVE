# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = C:/mingw64/bin/cmake.exe

# The command to remove a file.
RM = C:/mingw64/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server/build

# Include any dependencies generated for this target.
include CMakeFiles/CPlayerManager.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CPlayerManager.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CPlayerManager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CPlayerManager.dir/flags.make

CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.obj: CMakeFiles/CPlayerManager.dir/flags.make
CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.obj: C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server/src/CPlayerManager.cpp
CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.obj: CMakeFiles/CPlayerManager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.obj"
	C:/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.obj -MF CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.obj.d -o CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.obj -c C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server/src/CPlayerManager.cpp

CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.i"
	C:/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server/src/CPlayerManager.cpp > CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.i

CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.s"
	C:/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server/src/CPlayerManager.cpp -o CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.s

CPlayerManager: CMakeFiles/CPlayerManager.dir/src/CPlayerManager.cpp.obj
CPlayerManager: CMakeFiles/CPlayerManager.dir/build.make
.PHONY : CPlayerManager

# Rule to build all files generated by this target.
CMakeFiles/CPlayerManager.dir/build: CPlayerManager
.PHONY : CMakeFiles/CPlayerManager.dir/build

CMakeFiles/CPlayerManager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CPlayerManager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CPlayerManager.dir/clean

CMakeFiles/CPlayerManager.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server/build C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server/build C:/Users/zakar/Desktop/github-repos/CoopAndreas-Project/CoopAndreas/server/build/CMakeFiles/CPlayerManager.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/CPlayerManager.dir/depend

