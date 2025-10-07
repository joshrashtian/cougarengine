cmake_minimum_required(VERSION 3.20)
project(CougarEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Silence macOS OpenGL warnings
if(APPLE)
    add_compile_definitions(GL_SILENCE_DEPRECATION)
endif()

# ---- Dependencies ----
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# ---- Target ----
add_executable(${PROJECT_NAME}
        main.cpp
        OpenGL/source/glad.c                 # ✅ Make sure glad.c is listed here
        OpenGL/source/Window/OpenGLWindow.cpp
        OpenGL/source/renderer/shader.cpp
        OpenGL/source/renderer/VertexArray.cpp
        OpenGL/source/renderer/VertexBuffer.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/include
)

# Link
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw "-framework OpenGL")
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
endif()

# Warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()