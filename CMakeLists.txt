cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(learnopengl.com)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)

# MY_SOURCES is a variable that sets a list of files of the `src/` folder, later used to target the sources
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${MY_SOURCES}")

target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "include/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw glad)
