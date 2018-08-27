#cmake

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Xml REQUIRED)

set(CMAKE_AUTOMOC ON)

include_directories("../game_basis/include")

set(SNAKE_LBR "snake")
file(GLOB SNAKE_SRC "include/*.hpp" "sources/*.cpp")

add_library(${SNAKE_LBR} SHARED ${SNAKE_SRC})

target_link_libraries(${SNAKE_LBR} ${BRICKG_LBR} Qt5::Widgets)

target_include_directories(${SNAKE_LBR} PUBLIC "./include")
