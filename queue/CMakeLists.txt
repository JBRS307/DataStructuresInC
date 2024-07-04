cmake_minimum_required(VERSION 3.22)

project(Queue)

add_library(queue STATIC queue.c)

set_target_properties(
    queue PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)