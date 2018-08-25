#cmake

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Xml REQUIRED)

include_directories("../game_basis/include")

set(CMAKE_AUTOMOC ON)

set(TETRAMINO_LBR "tetramino" CACHE STRING "library name" FORCE)
file(GLOB TETRAMINO_SRC "include/*.hpp" "sources/*.cpp")

set(LIST_TARGETS "${LIST_TARGETS};${TETRAMINO_LBR}" CACHE STRING "append datas" FORCE)

add_library(${TETRAMINO_LBR} ${TETRAMINO_SRC})

target_link_libraries(${TETRAMINO_LBR} Qt5::Widgets)

target_include_directories(${TETRAMINO_LBR} PUBLIC "./include")
