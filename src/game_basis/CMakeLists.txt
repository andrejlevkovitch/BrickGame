#cmake

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Xml REQUIRED)

set(CMAKE_AUTOMOC ON)

set(BRICKG_LBR "brickG" CACHE STRING "library name" FORCE)
file(GLOB LOGS_SRC "include/logs/*.hpp" "sources/logs/*.cpp")
file(GLOB EVENT_SRC "include/events/*.hpp" "sources/events/*.cpp")
file(GLOB RECORDT_SRC "include/recordTable/*.hpp" "sources/recordTable/*.cpp")
file(GLOB PLAYER_SRC "include/player/*.hpp" "sources/player/*.cpp")
file(GLOB SCREEN_SRC "include/screen/*.hpp" "sources/screen/*.cpp")
file(GLOB AGAME_SRC "include/abstractGame/*.hpp" "sources/abstractGame/*.cpp")

set(LIST_TARGETS "${LIST_TARGETS};${BRICKG_LBR}" CACHE STRING "append datas" FORCE)

add_library(${BRICKG_LBR} SHARED ${LOGS_SRC} ${EVENT_SRC} ${RECORDT_SRC}
  ${PLAYER_SRC} ${SCREEN_SRC} ${AGAME_SRC})

target_link_libraries(${BRICKG_LBR} Qt5::Widgets Qt5::Xml Qt5::Multimedia)

target_include_directories(${BRICKG_LBR} PUBLIC "./include")

if(BUILD_TESTING)
  find_package(Boost COMPONENTS unit_test_framework)
  find_package(Boost COMPONENTS filesystem)
  if (Boost_FOUND)
    set(BOOST_TEST_ABS "test_abstractGame")
    set(BOOST_TEST_ABS_SRC "tests/boost_test_abstractGame.cpp" "tests/test_slot.hpp")
    add_executable(${BOOST_TEST_ABS} ${BOOST_TEST_ABS_SRC})
    target_link_libraries(${BOOST_TEST_ABS} ${BRICKG_LBR} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    add_test(NAME ${BOOST_TEST_ABS} COMMAND ${BOOST_TEST_ABS})

    set(BOOST_TEST_RT "test_rt")
    set(BOOST_TEST_RT_SRC "tests/boost_test_recordTable.cpp" "tests/test_slot.hpp")
    add_executable(${BOOST_TEST_RT} ${BOOST_TEST_RT_SRC})
    target_link_libraries(${BOOST_TEST_RT} ${BRICKG_LBR} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
    add_test(NAME ${BOOST_TEST_RT} COMMAND ${BOOST_TEST_RT})
  else()
    message(WARNING "For build tests Boost necessary!")
  endif()
endif()
