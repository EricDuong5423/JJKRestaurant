# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.1.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.1.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\DSA\JJKRestaurant\Thanh Tuss"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\DSA\JJKRestaurant\Thanh Tuss\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Thanh_Tuss.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Thanh_Tuss.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Thanh_Tuss.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Thanh_Tuss.dir/flags.make

CMakeFiles/Thanh_Tuss.dir/main.cpp.obj: CMakeFiles/Thanh_Tuss.dir/flags.make
CMakeFiles/Thanh_Tuss.dir/main.cpp.obj: D:/DSA/JJKRestaurant/Thanh\ Tuss/main.cpp
CMakeFiles/Thanh_Tuss.dir/main.cpp.obj: CMakeFiles/Thanh_Tuss.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\DSA\JJKRestaurant\Thanh Tuss\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Thanh_Tuss.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Thanh_Tuss.dir/main.cpp.obj -MF CMakeFiles\Thanh_Tuss.dir\main.cpp.obj.d -o CMakeFiles\Thanh_Tuss.dir\main.cpp.obj -c "D:\DSA\JJKRestaurant\Thanh Tuss\main.cpp"

CMakeFiles/Thanh_Tuss.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Thanh_Tuss.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\DSA\JJKRestaurant\Thanh Tuss\main.cpp" > CMakeFiles\Thanh_Tuss.dir\main.cpp.i

CMakeFiles/Thanh_Tuss.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Thanh_Tuss.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\DSA\JJKRestaurant\Thanh Tuss\main.cpp" -o CMakeFiles\Thanh_Tuss.dir\main.cpp.s

# Object files for target Thanh_Tuss
Thanh_Tuss_OBJECTS = \
"CMakeFiles/Thanh_Tuss.dir/main.cpp.obj"

# External object files for target Thanh_Tuss
Thanh_Tuss_EXTERNAL_OBJECTS =

Thanh_Tuss.exe: CMakeFiles/Thanh_Tuss.dir/main.cpp.obj
Thanh_Tuss.exe: CMakeFiles/Thanh_Tuss.dir/build.make
Thanh_Tuss.exe: CMakeFiles/Thanh_Tuss.dir/linkLibs.rsp
Thanh_Tuss.exe: CMakeFiles/Thanh_Tuss.dir/objects1
Thanh_Tuss.exe: CMakeFiles/Thanh_Tuss.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\DSA\JJKRestaurant\Thanh Tuss\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Thanh_Tuss.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Thanh_Tuss.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Thanh_Tuss.dir/build: Thanh_Tuss.exe
.PHONY : CMakeFiles/Thanh_Tuss.dir/build

CMakeFiles/Thanh_Tuss.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Thanh_Tuss.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Thanh_Tuss.dir/clean

CMakeFiles/Thanh_Tuss.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\DSA\JJKRestaurant\Thanh Tuss" "D:\DSA\JJKRestaurant\Thanh Tuss" "D:\DSA\JJKRestaurant\Thanh Tuss\cmake-build-debug" "D:\DSA\JJKRestaurant\Thanh Tuss\cmake-build-debug" "D:\DSA\JJKRestaurant\Thanh Tuss\cmake-build-debug\CMakeFiles\Thanh_Tuss.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Thanh_Tuss.dir/depend

