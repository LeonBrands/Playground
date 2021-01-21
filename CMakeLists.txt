#CMake
cmake_minimum_required(VERSION 3.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

#Setup project
set(PROJECT_NAME Playground)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add subprojects
add_subdirectory(raytracing/one_weekend)