#cmake

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Xml REQUIRED)

set(CMAKE_AUTOMOC ON)

include_directories("../game_basis/include")

configure_file(config.h.in "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h")

set(GWINDOW_LBR "generalWindow" CACHE STRING "library name" FORCE)
file(GLOB GWINDOW_SRC "include/*.hpp" "sources/*.cpp")

set(LIST_TARGETS "${LIST_TARGETS};${GWINDOW_LBR}" CACHE STRING "append datas" FORCE)

add_library(${GWINDOW_LBR} ${GWINDOW_SRC})

target_link_libraries(${GWINDOW_LBR} Qt5::Widgets)

target_include_directories(${GWINDOW_LBR} PUBLIC "./include")
