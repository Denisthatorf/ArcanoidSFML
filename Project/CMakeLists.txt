project(test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 20)

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")

add_executable(test ${SOURCES})
add_dependencies(test data)

target_include_directories(test
        PRIVATE
            ${CMAKE_SOURCE_DIR}/Framework/inc
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/FRAMEWORK/inc
            )

target_link_libraries(test
        PUBLIC
            Framework
            )

add_custom_target(data
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Project/data
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/Project/data
        COMMENT "copying ${CMAKE_SOURCE_DIR}/shaders to ${CMAKE_BINARY_DIR}/shaders"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )