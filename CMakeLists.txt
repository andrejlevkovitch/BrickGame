#cmake for qt project

cmake_minimum_required(VERSION 3.5)

project(BrickGame)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(set_clang "set clang as default compiler" 0)
option(debug "set debug" 0)
option(leak_check "set leak_check" 0)
option(profiling "set profiling" 0)

if(set_clang)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    message(STATUS "Use option set_clang")
endif(set_clang)

if(debug)
  set(CMAKE_BUILD_TYPE Debug)
endif(debug)

if(debug AND leak_check)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif(debug AND leak_check)

if(debug AND profiling)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -pg")
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -pg")
endif(debug AND profiling)

message(STATUS "buid type    " ${CMAKE_BUILD_TYPE})
message(STATUS "Project      " ${PROJECT_NAME})
message(STATUS "c compiler   " ${CMAKE_C_COMPILER})
message(STATUS "cxx compiler " ${CMAKE_CXX_COMPILER})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Xml REQUIRED)

include_directories("./include")
include_directories("./include/game_basis")
include_directories("./include/general")
include_directories("./include/tetramino")
include_directories("./include/snake")

set(MAIN_SRC sources/main.cpp)
set(QRESOURCES "qresources.qrc")

set(BRICKG_LBR "brickG")
file(GLOB LOGS_SRC "include/game_basis/logs/*.hpp" "sources/game_basis/logs/*.cpp")
file(GLOB EVENT_SRC "include/game_basis/events/*.hpp" "sources/game_basis/events/*.cpp")
file(GLOB RECORDT_SRC "include/game_basis/recordTable/*.hpp" "sources/game_basis/recordTable/*.cpp")
file(GLOB PLAYER_SRC "include/game_basis/player/*.hpp" "sources/game_basis/player/*.cpp")
file(GLOB SCREEN_SRC "include/game_basis/screen/*.hpp" "sources/game_basis/screen/*.cpp")
file(GLOB AGAME_SRC "include/game_basis/abstractGame/*.hpp" "sources/game_basis/abstractGame/*.cpp")

set(GWINDOW_LBR "generalWindow")
file(GLOB GWINDOW_SRC "include/general/*.hpp" "sources/general/*.cpp")

set(TETRAMINO_LBR "tetramino")
file(GLOB TETRAMINO_SRC "include/tetramino/*.hpp" "sources/tetramino/*.cpp")

set(SNAKE_LBR "snake")
file(GLOB SNAKE_SRC "include/snake/*.hpp" "sources/snake/*.cpp")

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${QRESOURCES})
add_library(${BRICKG_LBR} SHARED ${LOGS_SRC} ${EVENT_SRC} ${RECORDT_SRC}
  ${PLAYER_SRC} ${SCREEN_SRC} ${AGAME_SRC})
add_library(${GWINDOW_LBR} SHARED ${GWINDOW_SRC})
add_library(${TETRAMINO_LBR} SHARED ${TETRAMINO_SRC})
add_library(${SNAKE_LBR} SHARED ${SNAKE_SRC})

target_link_libraries(${PROJECT_NAME} ${BRICKG_LBR} ${GWINDOW_LBR}
  ${TETRAMINO_LBR} ${SNAKE_LBR} Qt5::Widgets)
target_link_libraries(${BRICKG_LBR} Qt5::Widgets Qt5::Xml Qt5::Multimedia)
target_link_libraries(${GWINDOW_LBR} Qt5::Widgets)
target_link_libraries(${TETRAMINO_LBR} Qt5::Widgets)
target_link_libraries(${SNAKE_LBR} Qt5::Widgets)
