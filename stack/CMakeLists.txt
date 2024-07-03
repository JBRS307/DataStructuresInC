cmake_minimum_required(VERSION 3.22)

project(Stack)

add_library(stack STATIC stack.c)

set_target_properties(
    stack PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)