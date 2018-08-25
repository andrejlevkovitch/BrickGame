#cmake

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

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

add_library(${BRICKG_LBR} ${LOGS_SRC} ${EVENT_SRC} ${RECORDT_SRC}
  ${PLAYER_SRC} ${SCREEN_SRC} ${AGAME_SRC})

target_link_libraries(${BRICKG_LBR} Qt5::Widgets Qt5::Xml Qt5::Multimedia)

target_include_directories(${BRICKG_LBR} PUBLIC "./include")

if(BUILD_TESTING)
  if (Boost_FOUND)
    set(BOOST_TEST "test_game_basis")
    file(GLOB BOOST_TEST_SRC "tests/*")
    add_executable(${BOOST_TEST} ${BOOST_TEST_SRC})
    target_link_libraries(${BOOST_TEST} ${BRICKG_LBR} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    add_test(NAME TEST_GAME_BASIS COMMAND ${BOOST_TEST})
  else()
    message(WARNING "For build tests Boost necessary!")
  endif()
endif()
