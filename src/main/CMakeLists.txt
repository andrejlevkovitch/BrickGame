# cmake

set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)

find_package(Boost COMPONENTS filesystem)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
  set(DEBUG_IN_FILE OFF)
else()
  set(DEBUG_IN_FILE ON)
endif()

configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set(MAIN_SRC main.cpp)

add_executable(${PROJECT_NAME} ${MAIN_SRC})

foreach(SOME_TARGET ${LIST_TARGETS})
  target_link_libraries(${PROJECT_NAME} ${SOME_TARGET})
endforeach()

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

if(Boost_FOUND)
  target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
