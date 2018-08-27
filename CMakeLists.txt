#cmake for qt project

cmake_minimum_required(VERSION 3.5)

project(BrickGame)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(copy_commands ALL COMMAND
  cp "${CMAKE_BINARY_DIR}/compile_commands.json" "${CMAKE_SOURCE_DIR}")

set(BUILD_SHARED_LIBS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

set(LIST_TARGETS CACHE STRING "list of targets" FORCE)
set(LIST_SUBDIRS general snake tetramino game_basis main)

include(build.cmake)

message(STATUS "SUBDIRECTORIES: ${LIST_SUBDIRS}")
message(STATUS "TARGETS: ${LIST_TARGETS}")
