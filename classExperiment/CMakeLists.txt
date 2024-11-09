cmake_minimum_required(VERSION 3.26)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)		# 指定编译后exe放入bin文件夹中


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/lib/x64)
add_executable(OpenGL src/glad.c
        src/main.cpp
        src/line.cpp
        src/circle.cpp
        src/Paint.cpp
        src/polygonScan.cpp
        src/lineClip.cpp
        include/lineClip.h
)

target_link_libraries(OpenGL ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
target_link_libraries(OpenGL libopengl32.a  libfreeglut.a  glu32.dll) #链接对应的库文件