cmake_minimum_required(VERSION 3.28)
project(CougarEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
add_executable(${PROJECT_NAME} main.cpp
        OpenGL/include/Window/OpenGLWindow.h
        OpenGL/source/Window/OpenGLWindow.cpp)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw "-framework OpenGL")
endif()