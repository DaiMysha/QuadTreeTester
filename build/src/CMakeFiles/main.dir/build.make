# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.2

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\prive\GitRepo\QuadTreeTester

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\prive\GitRepo\QuadTreeTester\build

# Include any dependencies generated for this target.
include src/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/main.dir/flags.make

src/CMakeFiles/main.dir/main.cpp.obj: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/main.cpp.obj: src/CMakeFiles/main.dir/includes_CXX.rsp
src/CMakeFiles/main.dir/main.cpp.obj: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report D:\prive\GitRepo\QuadTreeTester\build\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/main.dir/main.cpp.obj"
	cd /d D:\prive\GitRepo\QuadTreeTester\build\src && C:\mingw64\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\main.dir\main.cpp.obj -c D:\prive\GitRepo\QuadTreeTester\src\main.cpp

src/CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	cd /d D:\prive\GitRepo\QuadTreeTester\build\src && C:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E D:\prive\GitRepo\QuadTreeTester\src\main.cpp > CMakeFiles\main.dir\main.cpp.i

src/CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	cd /d D:\prive\GitRepo\QuadTreeTester\build\src && C:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S D:\prive\GitRepo\QuadTreeTester\src\main.cpp -o CMakeFiles\main.dir\main.cpp.s

src/CMakeFiles/main.dir/main.cpp.obj.requires:
.PHONY : src/CMakeFiles/main.dir/main.cpp.obj.requires

src/CMakeFiles/main.dir/main.cpp.obj.provides: src/CMakeFiles/main.dir/main.cpp.obj.requires
	$(MAKE) -f src\CMakeFiles\main.dir\build.make src/CMakeFiles/main.dir/main.cpp.obj.provides.build
.PHONY : src/CMakeFiles/main.dir/main.cpp.obj.provides

src/CMakeFiles/main.dir/main.cpp.obj.provides.build: src/CMakeFiles/main.dir/main.cpp.obj

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.obj"

# External object files for target main
main_EXTERNAL_OBJECTS =

../lib/main.exe: src/CMakeFiles/main.dir/main.cpp.obj
../lib/main.exe: src/CMakeFiles/main.dir/build.make
../lib/main.exe: C:/Program\ Files\ (x86)/SFML/lib/libsfml-system.a
../lib/main.exe: C:/Program\ Files\ (x86)/SFML/lib/libsfml-graphics.a
../lib/main.exe: C:/Program\ Files\ (x86)/SFML/lib/libsfml-window.a
../lib/main.exe: src/CMakeFiles/main.dir/linklibs.rsp
../lib/main.exe: src/CMakeFiles/main.dir/objects1.rsp
../lib/main.exe: src/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ..\..\lib\main.exe"
	cd /d D:\prive\GitRepo\QuadTreeTester\build\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/main.dir/build: ../lib/main.exe
.PHONY : src/CMakeFiles/main.dir/build

src/CMakeFiles/main.dir/requires: src/CMakeFiles/main.dir/main.cpp.obj.requires
.PHONY : src/CMakeFiles/main.dir/requires

src/CMakeFiles/main.dir/clean:
	cd /d D:\prive\GitRepo\QuadTreeTester\build\src && $(CMAKE_COMMAND) -P CMakeFiles\main.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/main.dir/clean

src/CMakeFiles/main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\prive\GitRepo\QuadTreeTester D:\prive\GitRepo\QuadTreeTester\src D:\prive\GitRepo\QuadTreeTester\build D:\prive\GitRepo\QuadTreeTester\build\src D:\prive\GitRepo\QuadTreeTester\build\src\CMakeFiles\main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/main.dir/depend
