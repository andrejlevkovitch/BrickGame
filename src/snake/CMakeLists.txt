#cmake

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Xml REQUIRED)

set(CMAKE_AUTOMOC ON)

set(SNAKE_LBR "snake")
file(GLOB SNAKE_SRC "include/*.hpp" "sources/*.cpp")

add_library(${SNAKE_LBR} MODULE ${SNAKE_SRC})

target_link_libraries(${SNAKE_LBR} Qt5::Widgets)

target_include_directories(${SNAKE_LBR} PRIVATE "./include")
target_include_directories(${SNAKE_LBR} PRIVATE "../game_basis/include")
