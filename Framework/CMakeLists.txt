cmake_minimum_required (VERSION 3.6)
project(Framework VERSION 0.0.1)

set (CMAKE_CXX_STANDARD 20)
set(SOURCES ./src/launch.cpp ./src/logger.cpp)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb -Wattributes ")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(Framework SHARED ${SOURCES})

#set_target_properties(${MY_LIBNAME} PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(Framework
        PUBLIC 
            ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(Framework
        PRIVATE
            SDL2::Main
            SDL2::Image
)