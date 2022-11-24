cmake_minimum_required (VERSION 3.6)
project(arcanoid)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(Project)
add_subdirectory(Framework)