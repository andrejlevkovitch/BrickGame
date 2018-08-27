//boost_test_simplExempl.cpp

#define BOOST_TEST_MODULE test_module_simplExempl
#include <boost/test/included/unit_test.hpp>

#include "simplExempl.hpp"

/// test simplExempl
BOOST_AUTO_TEST_SUITE(test_simplExempl)
struct test_simplExempl : public brick_game::simplExempl {};

BOOST_FIXTURE_TEST_CASE(test_case1, test_simplExempl) {
  BOOST_CHECK(is_passible(test_simplExempl::REND_FIELD()) != true);
  BOOST_CHECK(is_passible(test_simplExempl::END_FIELD()) != true);
}

BOOST_FIXTURE_TEST_CASE(test_case2, test_simplExempl) {
  BOOST_CHECK(is_passible(test_simplExempl::REND_FIELD() +
                          brick_game::point{1, 1}) == true);
  BOOST_CHECK(is_passible(test_simplExempl::END_FIELD() -
                          brick_game::point{1, 1}) == true);
}

BOOST_FIXTURE_TEST_CASE(test_game_name, test_simplExempl) {
  BOOST_CHECK(!game_name().isNull());
}

BOOST_FIXTURE_TEST_CASE(test_case_4, test_simplExempl) {
  score_ = 3;
  level_ = 5;
  emit end_game_signal();
  BOOST_CHECK(!score_);
  BOOST_CHECK(!level_);
}

BOOST_AUTO_TEST_SUITE_END()
