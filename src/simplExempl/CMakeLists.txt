# cmake

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

set(SE_PLUGIN "se_plugin")
file(GLOB SE_SRC "include/*.hpp" "sources/*.cpp")

add_library(${SE_PLUGIN} MODULE ${SE_SRC})

target_link_libraries(${SE_PLUGIN} Qt5::Widgets)
target_include_directories(${SE_PLUGIN} PRIVATE "./include")
target_include_directories(${SE_PLUGIN} PRIVATE "../game_basis/include")

if(BUILD_TESTING)
  find_package(Boost COMPONENTS unit_test_framework)
  if (Boost_FOUND)
    set(BOOST_TEST_SE "test_simplExempl")
    file(GLOB BOOST_TEST_ABS_SE "tests/*")

    add_executable(${BOOST_TEST_SE} ${BOOST_TEST_ABS_SE} ${SE_SRC})
    target_link_libraries(${BOOST_TEST_SE} ${BRICKG_LBR} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

    target_include_directories(${BOOST_TEST_SE} PRIVATE "./include")
    target_include_directories(${BOOST_TEST_SE} PRIVATE "../game_basis/include")

    add_test(NAME ${BOOST_TEST_SE} COMMAND ${BOOST_TEST_SE})
  else()
    message(WARNING "For build tests Boost necessary!")
  endif()
endif()
