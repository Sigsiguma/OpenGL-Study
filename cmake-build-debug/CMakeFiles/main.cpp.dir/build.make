# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/siguma/CLionProjects/OpenGL-Study

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/main.cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.cpp.dir/flags.make

CMakeFiles/main.cpp.dir/Cube.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/Cube.cpp.o: ../Cube.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.cpp.dir/Cube.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/Cube.cpp.o -c /Users/siguma/CLionProjects/OpenGL-Study/Cube.cpp

CMakeFiles/main.cpp.dir/Cube.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/Cube.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/siguma/CLionProjects/OpenGL-Study/Cube.cpp > CMakeFiles/main.cpp.dir/Cube.cpp.i

CMakeFiles/main.cpp.dir/Cube.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/Cube.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/siguma/CLionProjects/OpenGL-Study/Cube.cpp -o CMakeFiles/main.cpp.dir/Cube.cpp.s

CMakeFiles/main.cpp.dir/Cube.cpp.o.requires:

.PHONY : CMakeFiles/main.cpp.dir/Cube.cpp.o.requires

CMakeFiles/main.cpp.dir/Cube.cpp.o.provides: CMakeFiles/main.cpp.dir/Cube.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.cpp.dir/build.make CMakeFiles/main.cpp.dir/Cube.cpp.o.provides.build
.PHONY : CMakeFiles/main.cpp.dir/Cube.cpp.o.provides

CMakeFiles/main.cpp.dir/Cube.cpp.o.provides.build: CMakeFiles/main.cpp.dir/Cube.cpp.o


CMakeFiles/main.cpp.dir/MouseDrag.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/MouseDrag.cpp.o: ../MouseDrag.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.cpp.dir/MouseDrag.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/MouseDrag.cpp.o -c /Users/siguma/CLionProjects/OpenGL-Study/MouseDrag.cpp

CMakeFiles/main.cpp.dir/MouseDrag.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/MouseDrag.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/siguma/CLionProjects/OpenGL-Study/MouseDrag.cpp > CMakeFiles/main.cpp.dir/MouseDrag.cpp.i

CMakeFiles/main.cpp.dir/MouseDrag.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/MouseDrag.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/siguma/CLionProjects/OpenGL-Study/MouseDrag.cpp -o CMakeFiles/main.cpp.dir/MouseDrag.cpp.s

CMakeFiles/main.cpp.dir/MouseDrag.cpp.o.requires:

.PHONY : CMakeFiles/main.cpp.dir/MouseDrag.cpp.o.requires

CMakeFiles/main.cpp.dir/MouseDrag.cpp.o.provides: CMakeFiles/main.cpp.dir/MouseDrag.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.cpp.dir/build.make CMakeFiles/main.cpp.dir/MouseDrag.cpp.o.provides.build
.PHONY : CMakeFiles/main.cpp.dir/MouseDrag.cpp.o.provides

CMakeFiles/main.cpp.dir/MouseDrag.cpp.o.provides.build: CMakeFiles/main.cpp.dir/MouseDrag.cpp.o


CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o: ../ProgramObjectCreator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o -c /Users/siguma/CLionProjects/OpenGL-Study/ProgramObjectCreator.cpp

CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/siguma/CLionProjects/OpenGL-Study/ProgramObjectCreator.cpp > CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.i

CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/siguma/CLionProjects/OpenGL-Study/ProgramObjectCreator.cpp -o CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.s

CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o.requires:

.PHONY : CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o.requires

CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o.provides: CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.cpp.dir/build.make CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o.provides.build
.PHONY : CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o.provides

CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o.provides.build: CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o


CMakeFiles/main.cpp.dir/Sphere.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/Sphere.cpp.o: ../Sphere.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.cpp.dir/Sphere.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/Sphere.cpp.o -c /Users/siguma/CLionProjects/OpenGL-Study/Sphere.cpp

CMakeFiles/main.cpp.dir/Sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/Sphere.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/siguma/CLionProjects/OpenGL-Study/Sphere.cpp > CMakeFiles/main.cpp.dir/Sphere.cpp.i

CMakeFiles/main.cpp.dir/Sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/Sphere.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/siguma/CLionProjects/OpenGL-Study/Sphere.cpp -o CMakeFiles/main.cpp.dir/Sphere.cpp.s

CMakeFiles/main.cpp.dir/Sphere.cpp.o.requires:

.PHONY : CMakeFiles/main.cpp.dir/Sphere.cpp.o.requires

CMakeFiles/main.cpp.dir/Sphere.cpp.o.provides: CMakeFiles/main.cpp.dir/Sphere.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.cpp.dir/build.make CMakeFiles/main.cpp.dir/Sphere.cpp.o.provides.build
.PHONY : CMakeFiles/main.cpp.dir/Sphere.cpp.o.provides

CMakeFiles/main.cpp.dir/Sphere.cpp.o.provides.build: CMakeFiles/main.cpp.dir/Sphere.cpp.o


CMakeFiles/main.cpp.dir/Texture.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/Texture.cpp.o: ../Texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.cpp.dir/Texture.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/Texture.cpp.o -c /Users/siguma/CLionProjects/OpenGL-Study/Texture.cpp

CMakeFiles/main.cpp.dir/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/Texture.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/siguma/CLionProjects/OpenGL-Study/Texture.cpp > CMakeFiles/main.cpp.dir/Texture.cpp.i

CMakeFiles/main.cpp.dir/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/Texture.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/siguma/CLionProjects/OpenGL-Study/Texture.cpp -o CMakeFiles/main.cpp.dir/Texture.cpp.s

CMakeFiles/main.cpp.dir/Texture.cpp.o.requires:

.PHONY : CMakeFiles/main.cpp.dir/Texture.cpp.o.requires

CMakeFiles/main.cpp.dir/Texture.cpp.o.provides: CMakeFiles/main.cpp.dir/Texture.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.cpp.dir/build.make CMakeFiles/main.cpp.dir/Texture.cpp.o.provides.build
.PHONY : CMakeFiles/main.cpp.dir/Texture.cpp.o.provides

CMakeFiles/main.cpp.dir/Texture.cpp.o.provides.build: CMakeFiles/main.cpp.dir/Texture.cpp.o


CMakeFiles/main.cpp.dir/Torus.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/Torus.cpp.o: ../Torus.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.cpp.dir/Torus.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/Torus.cpp.o -c /Users/siguma/CLionProjects/OpenGL-Study/Torus.cpp

CMakeFiles/main.cpp.dir/Torus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/Torus.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/siguma/CLionProjects/OpenGL-Study/Torus.cpp > CMakeFiles/main.cpp.dir/Torus.cpp.i

CMakeFiles/main.cpp.dir/Torus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/Torus.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/siguma/CLionProjects/OpenGL-Study/Torus.cpp -o CMakeFiles/main.cpp.dir/Torus.cpp.s

CMakeFiles/main.cpp.dir/Torus.cpp.o.requires:

.PHONY : CMakeFiles/main.cpp.dir/Torus.cpp.o.requires

CMakeFiles/main.cpp.dir/Torus.cpp.o.provides: CMakeFiles/main.cpp.dir/Torus.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.cpp.dir/build.make CMakeFiles/main.cpp.dir/Torus.cpp.o.provides.build
.PHONY : CMakeFiles/main.cpp.dir/Torus.cpp.o.provides

CMakeFiles/main.cpp.dir/Torus.cpp.o.provides.build: CMakeFiles/main.cpp.dir/Torus.cpp.o


CMakeFiles/main.cpp.dir/Utility.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/Utility.cpp.o: ../Utility.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.cpp.dir/Utility.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/Utility.cpp.o -c /Users/siguma/CLionProjects/OpenGL-Study/Utility.cpp

CMakeFiles/main.cpp.dir/Utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/Utility.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/siguma/CLionProjects/OpenGL-Study/Utility.cpp > CMakeFiles/main.cpp.dir/Utility.cpp.i

CMakeFiles/main.cpp.dir/Utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/Utility.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/siguma/CLionProjects/OpenGL-Study/Utility.cpp -o CMakeFiles/main.cpp.dir/Utility.cpp.s

CMakeFiles/main.cpp.dir/Utility.cpp.o.requires:

.PHONY : CMakeFiles/main.cpp.dir/Utility.cpp.o.requires

CMakeFiles/main.cpp.dir/Utility.cpp.o.provides: CMakeFiles/main.cpp.dir/Utility.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.cpp.dir/build.make CMakeFiles/main.cpp.dir/Utility.cpp.o.provides.build
.PHONY : CMakeFiles/main.cpp.dir/Utility.cpp.o.provides

CMakeFiles/main.cpp.dir/Utility.cpp.o.provides.build: CMakeFiles/main.cpp.dir/Utility.cpp.o


CMakeFiles/main.cpp.dir/VBO.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/VBO.cpp.o: ../VBO.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/main.cpp.dir/VBO.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/VBO.cpp.o -c /Users/siguma/CLionProjects/OpenGL-Study/VBO.cpp

CMakeFiles/main.cpp.dir/VBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/VBO.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/siguma/CLionProjects/OpenGL-Study/VBO.cpp > CMakeFiles/main.cpp.dir/VBO.cpp.i

CMakeFiles/main.cpp.dir/VBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/VBO.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/siguma/CLionProjects/OpenGL-Study/VBO.cpp -o CMakeFiles/main.cpp.dir/VBO.cpp.s

CMakeFiles/main.cpp.dir/VBO.cpp.o.requires:

.PHONY : CMakeFiles/main.cpp.dir/VBO.cpp.o.requires

CMakeFiles/main.cpp.dir/VBO.cpp.o.provides: CMakeFiles/main.cpp.dir/VBO.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.cpp.dir/build.make CMakeFiles/main.cpp.dir/VBO.cpp.o.provides.build
.PHONY : CMakeFiles/main.cpp.dir/VBO.cpp.o.provides

CMakeFiles/main.cpp.dir/VBO.cpp.o.provides.build: CMakeFiles/main.cpp.dir/VBO.cpp.o


CMakeFiles/main.cpp.dir/main.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/main.cpp.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/main.cpp.o -c /Users/siguma/CLionProjects/OpenGL-Study/main.cpp

CMakeFiles/main.cpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/siguma/CLionProjects/OpenGL-Study/main.cpp > CMakeFiles/main.cpp.dir/main.cpp.i

CMakeFiles/main.cpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/siguma/CLionProjects/OpenGL-Study/main.cpp -o CMakeFiles/main.cpp.dir/main.cpp.s

CMakeFiles/main.cpp.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/main.cpp.dir/main.cpp.o.requires

CMakeFiles/main.cpp.dir/main.cpp.o.provides: CMakeFiles/main.cpp.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/main.cpp.dir/build.make CMakeFiles/main.cpp.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/main.cpp.dir/main.cpp.o.provides

CMakeFiles/main.cpp.dir/main.cpp.o.provides.build: CMakeFiles/main.cpp.dir/main.cpp.o


# Object files for target main.cpp
main_cpp_OBJECTS = \
"CMakeFiles/main.cpp.dir/Cube.cpp.o" \
"CMakeFiles/main.cpp.dir/MouseDrag.cpp.o" \
"CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o" \
"CMakeFiles/main.cpp.dir/Sphere.cpp.o" \
"CMakeFiles/main.cpp.dir/Texture.cpp.o" \
"CMakeFiles/main.cpp.dir/Torus.cpp.o" \
"CMakeFiles/main.cpp.dir/Utility.cpp.o" \
"CMakeFiles/main.cpp.dir/VBO.cpp.o" \
"CMakeFiles/main.cpp.dir/main.cpp.o"

# External object files for target main.cpp
main_cpp_EXTERNAL_OBJECTS =

../bin/main.cpp: CMakeFiles/main.cpp.dir/Cube.cpp.o
../bin/main.cpp: CMakeFiles/main.cpp.dir/MouseDrag.cpp.o
../bin/main.cpp: CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o
../bin/main.cpp: CMakeFiles/main.cpp.dir/Sphere.cpp.o
../bin/main.cpp: CMakeFiles/main.cpp.dir/Texture.cpp.o
../bin/main.cpp: CMakeFiles/main.cpp.dir/Torus.cpp.o
../bin/main.cpp: CMakeFiles/main.cpp.dir/Utility.cpp.o
../bin/main.cpp: CMakeFiles/main.cpp.dir/VBO.cpp.o
../bin/main.cpp: CMakeFiles/main.cpp.dir/main.cpp.o
../bin/main.cpp: CMakeFiles/main.cpp.dir/build.make
../bin/main.cpp: /usr/local/lib/libglfw3.a
../bin/main.cpp: /usr/local/lib/libGLEW.a
../bin/main.cpp: /usr/local/lib/libopencv_videostab.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_ts.a
../bin/main.cpp: /usr/local/lib/libopencv_superres.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_stitching.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_contrib.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_nonfree.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_ocl.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_gpu.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_photo.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_objdetect.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_legacy.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_video.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_ml.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_calib3d.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_features2d.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_highgui.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_imgproc.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_flann.2.4.13.dylib
../bin/main.cpp: /usr/local/lib/libopencv_core.2.4.13.dylib
../bin/main.cpp: CMakeFiles/main.cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ../bin/main.cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.cpp.dir/build: ../bin/main.cpp

.PHONY : CMakeFiles/main.cpp.dir/build

CMakeFiles/main.cpp.dir/requires: CMakeFiles/main.cpp.dir/Cube.cpp.o.requires
CMakeFiles/main.cpp.dir/requires: CMakeFiles/main.cpp.dir/MouseDrag.cpp.o.requires
CMakeFiles/main.cpp.dir/requires: CMakeFiles/main.cpp.dir/ProgramObjectCreator.cpp.o.requires
CMakeFiles/main.cpp.dir/requires: CMakeFiles/main.cpp.dir/Sphere.cpp.o.requires
CMakeFiles/main.cpp.dir/requires: CMakeFiles/main.cpp.dir/Texture.cpp.o.requires
CMakeFiles/main.cpp.dir/requires: CMakeFiles/main.cpp.dir/Torus.cpp.o.requires
CMakeFiles/main.cpp.dir/requires: CMakeFiles/main.cpp.dir/Utility.cpp.o.requires
CMakeFiles/main.cpp.dir/requires: CMakeFiles/main.cpp.dir/VBO.cpp.o.requires
CMakeFiles/main.cpp.dir/requires: CMakeFiles/main.cpp.dir/main.cpp.o.requires

.PHONY : CMakeFiles/main.cpp.dir/requires

CMakeFiles/main.cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.cpp.dir/clean

CMakeFiles/main.cpp.dir/depend:
	cd /Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/siguma/CLionProjects/OpenGL-Study /Users/siguma/CLionProjects/OpenGL-Study /Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug /Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug /Users/siguma/CLionProjects/OpenGL-Study/cmake-build-debug/CMakeFiles/main.cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.cpp.dir/depend

