#cmake

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Xml REQUIRED)

set(CMAKE_AUTOMOC ON)

include_directories("../game_basis/include")

set(SNAKE_LBR "snake")
file(GLOB SNAKE_SRC "include/*.hpp" "sources/*.cpp")

set(LIST_TARGETS "${LIST_TARGETS};${SNAKE_LBR}" CACHE STRING "append datas" FORCE)

add_library(${SNAKE_LBR} ${SNAKE_SRC})

target_link_libraries(${SNAKE_LBR} Qt5::Widgets)

target_include_directories(${SNAKE_LBR} PUBLIC "./include")
