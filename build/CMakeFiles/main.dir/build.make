# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Admin\Desktop\C++\SFML_Prac2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Admin\Desktop\C++\SFML_Prac2\build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/Entity.c++.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Entity.c++.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/Entity.c++.obj: C:/Users/Admin/Desktop/C++/SFML_Prac2/src/Entity.c++
CMakeFiles/main.dir/src/Entity.c++.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Admin\Desktop\C++\SFML_Prac2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/src/Entity.c++.obj"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Entity.c++.obj -MF CMakeFiles\main.dir\src\Entity.c++.obj.d -o CMakeFiles\main.dir\src\Entity.c++.obj -c C:\Users\Admin\Desktop\C++\SFML_Prac2\src\Entity.c++

CMakeFiles/main.dir/src/Entity.c++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Entity.c++.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Admin\Desktop\C++\SFML_Prac2\src\Entity.c++ > CMakeFiles\main.dir\src\Entity.c++.i

CMakeFiles/main.dir/src/Entity.c++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Entity.c++.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Admin\Desktop\C++\SFML_Prac2\src\Entity.c++ -o CMakeFiles\main.dir\src\Entity.c++.s

CMakeFiles/main.dir/src/EntityMananger.c++.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/EntityMananger.c++.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/EntityMananger.c++.obj: C:/Users/Admin/Desktop/C++/SFML_Prac2/src/EntityMananger.c++
CMakeFiles/main.dir/src/EntityMananger.c++.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Admin\Desktop\C++\SFML_Prac2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/EntityMananger.c++.obj"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/EntityMananger.c++.obj -MF CMakeFiles\main.dir\src\EntityMananger.c++.obj.d -o CMakeFiles\main.dir\src\EntityMananger.c++.obj -c C:\Users\Admin\Desktop\C++\SFML_Prac2\src\EntityMananger.c++

CMakeFiles/main.dir/src/EntityMananger.c++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/EntityMananger.c++.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Admin\Desktop\C++\SFML_Prac2\src\EntityMananger.c++ > CMakeFiles\main.dir\src\EntityMananger.c++.i

CMakeFiles/main.dir/src/EntityMananger.c++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/EntityMananger.c++.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Admin\Desktop\C++\SFML_Prac2\src\EntityMananger.c++ -o CMakeFiles\main.dir\src\EntityMananger.c++.s

CMakeFiles/main.dir/src/Game.c++.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Game.c++.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/Game.c++.obj: C:/Users/Admin/Desktop/C++/SFML_Prac2/src/Game.c++
CMakeFiles/main.dir/src/Game.c++.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Admin\Desktop\C++\SFML_Prac2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/src/Game.c++.obj"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Game.c++.obj -MF CMakeFiles\main.dir\src\Game.c++.obj.d -o CMakeFiles\main.dir\src\Game.c++.obj -c C:\Users\Admin\Desktop\C++\SFML_Prac2\src\Game.c++

CMakeFiles/main.dir/src/Game.c++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Game.c++.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Admin\Desktop\C++\SFML_Prac2\src\Game.c++ > CMakeFiles\main.dir\src\Game.c++.i

CMakeFiles/main.dir/src/Game.c++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Game.c++.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Admin\Desktop\C++\SFML_Prac2\src\Game.c++ -o CMakeFiles\main.dir\src\Game.c++.s

CMakeFiles/main.dir/src/Vec2.c++.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Vec2.c++.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/Vec2.c++.obj: C:/Users/Admin/Desktop/C++/SFML_Prac2/src/Vec2.c++
CMakeFiles/main.dir/src/Vec2.c++.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Admin\Desktop\C++\SFML_Prac2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/src/Vec2.c++.obj"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Vec2.c++.obj -MF CMakeFiles\main.dir\src\Vec2.c++.obj.d -o CMakeFiles\main.dir\src\Vec2.c++.obj -c C:\Users\Admin\Desktop\C++\SFML_Prac2\src\Vec2.c++

CMakeFiles/main.dir/src/Vec2.c++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Vec2.c++.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Admin\Desktop\C++\SFML_Prac2\src\Vec2.c++ > CMakeFiles\main.dir\src\Vec2.c++.i

CMakeFiles/main.dir/src/Vec2.c++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Vec2.c++.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Admin\Desktop\C++\SFML_Prac2\src\Vec2.c++ -o CMakeFiles\main.dir\src\Vec2.c++.s

CMakeFiles/main.dir/src/main.c++.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.c++.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/main.c++.obj: C:/Users/Admin/Desktop/C++/SFML_Prac2/src/main.c++
CMakeFiles/main.dir/src/main.c++.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Admin\Desktop\C++\SFML_Prac2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/src/main.c++.obj"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/main.c++.obj -MF CMakeFiles\main.dir\src\main.c++.obj.d -o CMakeFiles\main.dir\src\main.c++.obj -c C:\Users\Admin\Desktop\C++\SFML_Prac2\src\main.c++

CMakeFiles/main.dir/src/main.c++.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/main.c++.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Admin\Desktop\C++\SFML_Prac2\src\main.c++ > CMakeFiles\main.dir\src\main.c++.i

CMakeFiles/main.dir/src/main.c++.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/main.c++.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Admin\Desktop\C++\SFML_Prac2\src\main.c++ -o CMakeFiles\main.dir\src\main.c++.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/Entity.c++.obj" \
"CMakeFiles/main.dir/src/EntityMananger.c++.obj" \
"CMakeFiles/main.dir/src/Game.c++.obj" \
"CMakeFiles/main.dir/src/Vec2.c++.obj" \
"CMakeFiles/main.dir/src/main.c++.obj"

# External object files for target main
main_EXTERNAL_OBJECTS =

bin/main.exe: CMakeFiles/main.dir/src/Entity.c++.obj
bin/main.exe: CMakeFiles/main.dir/src/EntityMananger.c++.obj
bin/main.exe: CMakeFiles/main.dir/src/Game.c++.obj
bin/main.exe: CMakeFiles/main.dir/src/Vec2.c++.obj
bin/main.exe: CMakeFiles/main.dir/src/main.c++.obj
bin/main.exe: CMakeFiles/main.dir/build.make
bin/main.exe: C:/Program\ Files\ (x86)/SFML/lib/libsfml-graphics.a
bin/main.exe: C:/Program\ Files\ (x86)/SFML/lib/libsfml-window.a
bin/main.exe: C:/Program\ Files\ (x86)/SFML/lib/libsfml-system.a
bin/main.exe: CMakeFiles/main.dir/linkLibs.rsp
bin/main.exe: CMakeFiles/main.dir/objects1.rsp
bin/main.exe: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Admin\Desktop\C++\SFML_Prac2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable bin\main.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: bin/main.exe
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\main.dir\cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Admin\Desktop\C++\SFML_Prac2 C:\Users\Admin\Desktop\C++\SFML_Prac2 C:\Users\Admin\Desktop\C++\SFML_Prac2\build C:\Users\Admin\Desktop\C++\SFML_Prac2\build C:\Users\Admin\Desktop\C++\SFML_Prac2\build\CMakeFiles\main.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend

