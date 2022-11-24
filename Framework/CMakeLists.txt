cmake_minimum_required (VERSION 3.6)
project(Framework VERSION 0.0.1)

set (CMAKE_CXX_STANDARD 11)
set(SOURCES ./src/launch.cpp)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb -Wattributes ")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(Framework SHARED ./src/launch.cpp)

#set_target_properties(${MY_LIBNAME} PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(Framework
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Framework
        PRIVATE
            SDL2::Main
            SDL2::Image
)

#include(GNUInstallDirs)
#install(TARGETS Framework
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#target_link_libraries(${SDL2} ${SDL2main}) # X11)
