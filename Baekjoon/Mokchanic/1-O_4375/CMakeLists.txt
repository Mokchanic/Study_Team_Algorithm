cmake_minimum_required(VERSION 3.22)

set(PACKAGE_NAME 1629) #INPUT YOUR PACKAGE

project(
    ${PACKAGE_NAME}
    ${NUMBER}
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "PACKAGE_NAME: ${PACKAGE_NAME}")

add_executable(
    ${PACKAGE_NAME}_MAIN main.cpp
)
target_compile_options(
    ${PACKAGE_NAME}_MAIN PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)
