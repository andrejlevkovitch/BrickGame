# cmake

set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)

find_package(Boost COMPONENTS filesystem REQUIRED)

set(QRESOURCES "${CMAKE_SOURCE_DIR}/qresources.qrc")

set(MAIN_SRC main.cpp)

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${QRESOURCES})

foreach(TARGET ${LIST_TARGETS})
  target_link_libraries(${PROJECT_NAME} ${TARGET})
endforeach()

target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
