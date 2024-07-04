cmake_minimum_required(VERSION 3.22)

project(PriorityQueue)

add_library(priority_queue STATIC priority_queue.c)

set_target_properties(
    priority_queue PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)