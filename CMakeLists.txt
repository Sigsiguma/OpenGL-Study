cmake_minimum_required(VERSION 3.3)
project(OpenGL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

set(CMAKE_PREFIX_PATH /usr/local/lib/)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(GLEW REQUIRED STATIC)


include_directories(/usr/local/include)
link_directories(/usr/local/lib)

link_libraries(/usr/local/lib/libglfw3.a)
link_libraries(/usr/local/lib/libGLEW.a)

file(GLOB SOURCE_FILES
        *.cpp
        *.h
        )

add_executable(main.cpp ${SOURCE_FILES} ProgramObjectCreator.h ProgramObjectCreator.cpp VBO.h VBO.cpp Utility.h Utility.cpp Sphere.cpp Sphere.h Texture.cpp Texture.h MouseDrag.cpp MouseDrag.h Cube.cpp Cube.h FrameBuffer.cpp FrameBuffer.h)

target_link_libraries(main.cpp ${OPENGL_LIBRARIES} glfw3)
target_link_libraries(main.cpp ${OpenCV_LIBS})
