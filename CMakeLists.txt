# Project Related
cmake_minimum_required(VERSION 3.0.0)
project (GAME_4)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)


# Prerequisites
find_package(PkgConfig REQUIRED)
find_package(SFML 2.5 COMPONENTS window graphics REQUIRED)

# OpenGL
set (OpenGL_GL_PREFERENCE GLVND) # OpenGL Vendor Neutral Dispatch
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Versioning
set (APPLICATION_VERSION_MAJOR 0)
set (APPLICATION_VERSION_MINOR 1)

# C++
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# Modules go here

# The game executable
add_subdirectory(src/entities)

add_executable(game.run src/index.cpp )

target_link_libraries(game.run entities)
target_link_libraries(game.run sfml-system sfml-window sfml-graphics)
target_link_libraries(game.run GLU)
target_link_libraries(game.run GL)
target_link_libraries(game.run GLEW)
target_link_libraries(game.run box2d)
