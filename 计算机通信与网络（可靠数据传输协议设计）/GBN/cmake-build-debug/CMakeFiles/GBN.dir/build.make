# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\AlexFan\Desktop\CI\2\GBN

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\AlexFan\Desktop\CI\2\GBN\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/GBN.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GBN.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GBN.dir/flags.make

CMakeFiles/GBN.dir/src/GBN.cpp.obj: CMakeFiles/GBN.dir/flags.make
CMakeFiles/GBN.dir/src/GBN.cpp.obj: CMakeFiles/GBN.dir/includes_CXX.rsp
CMakeFiles/GBN.dir/src/GBN.cpp.obj: ../src/GBN.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AlexFan\Desktop\CI\2\GBN\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GBN.dir/src/GBN.cpp.obj"
	C:\Users\AlexFan\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\GBN.dir\src\GBN.cpp.obj -c C:\Users\AlexFan\Desktop\CI\2\GBN\src\GBN.cpp

CMakeFiles/GBN.dir/src/GBN.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBN.dir/src/GBN.cpp.i"
	C:\Users\AlexFan\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\AlexFan\Desktop\CI\2\GBN\src\GBN.cpp > CMakeFiles\GBN.dir\src\GBN.cpp.i

CMakeFiles/GBN.dir/src/GBN.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBN.dir/src/GBN.cpp.s"
	C:\Users\AlexFan\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\AlexFan\Desktop\CI\2\GBN\src\GBN.cpp -o CMakeFiles\GBN.dir\src\GBN.cpp.s

CMakeFiles/GBN.dir/src/GBNReceiver.cpp.obj: CMakeFiles/GBN.dir/flags.make
CMakeFiles/GBN.dir/src/GBNReceiver.cpp.obj: CMakeFiles/GBN.dir/includes_CXX.rsp
CMakeFiles/GBN.dir/src/GBNReceiver.cpp.obj: ../src/GBNReceiver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AlexFan\Desktop\CI\2\GBN\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GBN.dir/src/GBNReceiver.cpp.obj"
	C:\Users\AlexFan\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\GBN.dir\src\GBNReceiver.cpp.obj -c C:\Users\AlexFan\Desktop\CI\2\GBN\src\GBNReceiver.cpp

CMakeFiles/GBN.dir/src/GBNReceiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBN.dir/src/GBNReceiver.cpp.i"
	C:\Users\AlexFan\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\AlexFan\Desktop\CI\2\GBN\src\GBNReceiver.cpp > CMakeFiles\GBN.dir\src\GBNReceiver.cpp.i

CMakeFiles/GBN.dir/src/GBNReceiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBN.dir/src/GBNReceiver.cpp.s"
	C:\Users\AlexFan\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\AlexFan\Desktop\CI\2\GBN\src\GBNReceiver.cpp -o CMakeFiles\GBN.dir\src\GBNReceiver.cpp.s

CMakeFiles/GBN.dir/src/GBNSender.cpp.obj: CMakeFiles/GBN.dir/flags.make
CMakeFiles/GBN.dir/src/GBNSender.cpp.obj: CMakeFiles/GBN.dir/includes_CXX.rsp
CMakeFiles/GBN.dir/src/GBNSender.cpp.obj: ../src/GBNSender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\AlexFan\Desktop\CI\2\GBN\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/GBN.dir/src/GBNSender.cpp.obj"
	C:\Users\AlexFan\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\GBN.dir\src\GBNSender.cpp.obj -c C:\Users\AlexFan\Desktop\CI\2\GBN\src\GBNSender.cpp

CMakeFiles/GBN.dir/src/GBNSender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GBN.dir/src/GBNSender.cpp.i"
	C:\Users\AlexFan\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\AlexFan\Desktop\CI\2\GBN\src\GBNSender.cpp > CMakeFiles\GBN.dir\src\GBNSender.cpp.i

CMakeFiles/GBN.dir/src/GBNSender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GBN.dir/src/GBNSender.cpp.s"
	C:\Users\AlexFan\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\AlexFan\Desktop\CI\2\GBN\src\GBNSender.cpp -o CMakeFiles\GBN.dir\src\GBNSender.cpp.s

# Object files for target GBN
GBN_OBJECTS = \
"CMakeFiles/GBN.dir/src/GBN.cpp.obj" \
"CMakeFiles/GBN.dir/src/GBNReceiver.cpp.obj" \
"CMakeFiles/GBN.dir/src/GBNSender.cpp.obj"

# External object files for target GBN
GBN_EXTERNAL_OBJECTS =

../bin/GBN.exe: CMakeFiles/GBN.dir/src/GBN.cpp.obj
../bin/GBN.exe: CMakeFiles/GBN.dir/src/GBNReceiver.cpp.obj
../bin/GBN.exe: CMakeFiles/GBN.dir/src/GBNSender.cpp.obj
../bin/GBN.exe: CMakeFiles/GBN.dir/build.make
../bin/GBN.exe: ../lib/libnetsim.a
../bin/GBN.exe: CMakeFiles/GBN.dir/linklibs.rsp
../bin/GBN.exe: CMakeFiles/GBN.dir/objects1.rsp
../bin/GBN.exe: CMakeFiles/GBN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\AlexFan\Desktop\CI\2\GBN\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ..\bin\GBN.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GBN.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GBN.dir/build: ../bin/GBN.exe

.PHONY : CMakeFiles/GBN.dir/build

CMakeFiles/GBN.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GBN.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GBN.dir/clean

CMakeFiles/GBN.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\AlexFan\Desktop\CI\2\GBN C:\Users\AlexFan\Desktop\CI\2\GBN C:\Users\AlexFan\Desktop\CI\2\GBN\cmake-build-debug C:\Users\AlexFan\Desktop\CI\2\GBN\cmake-build-debug C:\Users\AlexFan\Desktop\CI\2\GBN\cmake-build-debug\CMakeFiles\GBN.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GBN.dir/depend

