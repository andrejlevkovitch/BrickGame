#cmake

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Xml REQUIRED)

find_package(Boost COMPONENTS unit_test_framework)

include_directories("../game_basis/include")

set(CMAKE_AUTOMOC ON)

set(TETRAMINO_LBR "tetramino")
file(GLOB TETRAMINO_SRC "include/*.hpp" "sources/*.cpp")

add_library(${TETRAMINO_LBR} SHARED ${TETRAMINO_SRC})

target_link_libraries(${TETRAMINO_LBR} ${BRICKG_LBR} Qt5::Widgets)

target_include_directories(${TETRAMINO_LBR} PUBLIC "./include")

if(BUILD_TESTING)
  if(Boost_FOUND)
    set(BOOST_TEST_TET "test_tetramino")
    set(BOOST_TEST_TET_SRC "tests/boost_test_tetramino.cpp")

    add_executable(${BOOST_TEST_TET} ${BOOST_TEST_TET_SRC})
    target_link_libraries(${BOOST_TEST_TET} ${TETRAMINO_LBR} Qt5::Widgets)

    add_test(NAME ${BOOST_TEST_TET} COMMAND ${BOOST_TEST_TET})
  else()
    message(WARNING "for build tests you need boost")
  endif()
endif()
