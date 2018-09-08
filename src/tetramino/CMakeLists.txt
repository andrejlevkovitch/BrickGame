#cmake

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Xml REQUIRED)

find_package(Boost COMPONENTS unit_test_framework)

set(CMAKE_AUTOMOC ON)

set(TETRAMINO_LBR "tetramino")
file(GLOB TETRAMINO_SRC "include/*.hpp" "sources/*.cpp")

add_library(${TETRAMINO_LBR} MODULE ${TETRAMINO_SRC})

target_link_libraries(${TETRAMINO_LBR} Qt5::Widgets)

target_include_directories(${TETRAMINO_LBR} PRIVATE "./include")
target_include_directories(${TETRAMINO_LBR} PRIVATE "../game_basis/include")

if(BUILD_TESTING)
  if(Boost_FOUND)
    set(BOOST_TEST_TET "test_tetramino")
    set(BOOST_TEST_TET_SRC "tests/boost_test_tetramino.cpp" "tests/test_slot.hpp")

    add_executable(${BOOST_TEST_TET} ${BOOST_TEST_TET_SRC} ${TETRAMINO_SRC})
    target_link_libraries(${BOOST_TEST_TET} ${BRICKG_LBR} Qt5::Widgets)

    target_include_directories(${BOOST_TEST_TET} PRIVATE "./include")
    target_include_directories(${BOOST_TEST_TET} PRIVATE "../game_basis/include")

    add_test(NAME ${BOOST_TEST_TET} COMMAND ${BOOST_TEST_TET})
  else()
    message(WARNING "for build tests you need boost")
  endif()
endif()
