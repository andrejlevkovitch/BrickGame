#cmake for qt project

cmake_minimum_required(VERSION 3.5)

project(BrickGame)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF(NOT CMAKE_BUILD_TYPE)

option(set_clang "set clang as default compiler" 0)

if(set_clang)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    message(STATUS "Use option set_clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif(set_clang)

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

set(MAIN_SRC sources/main.cpp)
set(QRESOURCES "qresources.qrc")

set(BRICKG_LBR "brickG")
file(GLOB LOGS_SRC "include/logs/*.hpp" "sources/logs/*.cpp")
file(GLOB EVENT_SRC "include/events/*.hpp" "sources/events/*.cpp")
file(GLOB RECORDT_SRC "include/recordTable/*.hpp" "sources/recordTable/*.cpp")
file(GLOB PLAYER_SRC "include/player/*.hpp" "sources/player/*.cpp")
file(GLOB SCREEN_SRC "include/screen/*.hpp" "sources/screen/*.cpp")
file(GLOB AGAME_SRC "include/abstractGame/*.hpp" "sources/abstractGame/*.cpp")
file(GLOB GWINDOW_SRC "include/general/*.hpp" "sources/general/*.cpp")

set(TETRAMINO_LBR "tetramino")
file(GLOB TETRAMINO_SRC "include/tetramino/*.hpp" "sources/tetramino/*.cpp")

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${QRESOURCES})
add_library(${BRICKG_LBR} SHARED ${LOGS_SRC} ${EVENT_SRC} ${RECORDT_SRC}
  ${PLAYER_SRC} ${SCREEN_SRC} ${AGAME_SRC} ${GWINDOW_SRC})
add_library(${TETRAMINO_LBR} SHARED ${TETRAMINO_SRC})

target_link_libraries(${PROJECT_NAME} ${BRICKG_LBR} ${TETRAMINO_LBR} Qt5::Widgets)
target_link_libraries(${BRICKG_LBR} Qt5::Widgets Qt5::Xml Qt5::Multimedia)
target_link_libraries(${TETRAMINO_LBR} Qt5::Widgets)
