// boost_test_abstractGame.cpp

#define BOOST_TEST_MODULE test_module_abstracGame
#include <boost/test/included/unit_test.hpp>

#include "abstractGame/field.hpp"
#include "abstractGame/level.hpp"
#include "abstractGame/point.hpp"
#include "abstractGame/score.hpp"
#include "abstractGame/simplExempl.hpp"
#include "abstractGame/value.hpp"
#include "test_slot.hpp"

/// test point
BOOST_AUTO_TEST_SUITE(test_point)

const int i{9}, j{15};
brick_game::point charli{j, i};
brick_game::point delta{charli};

BOOST_AUTO_TEST_CASE(test_case1) {
  brick_game::point alfa{j, i};
  BOOST_REQUIRE(alfa.getY() == i);
  BOOST_REQUIRE(alfa.getX() == j);
}

BOOST_AUTO_TEST_CASE(test_case2) {
  brick_game::point alfa{j, i};
  brick_game::point bravo{alfa};
  BOOST_CHECK(alfa == bravo);
  BOOST_CHECK(bravo == alfa);
}

BOOST_AUTO_TEST_CASE(test_case3) {
  brick_game::point alfa{j, i};
  brick_game::point charli{alfa};
  charli.down();
  BOOST_CHECK(alfa != charli);
  BOOST_CHECK(!(alfa < charli));
  BOOST_CHECK(!(alfa > charli));
  BOOST_CHECK(!(alfa == charli));
  BOOST_CHECK(!(charli > alfa));
  BOOST_CHECK(!(charli < alfa));

  charli.right();
  delta = charli;
  BOOST_CHECK(alfa != charli);
  BOOST_CHECK(alfa < charli);
  BOOST_CHECK(!(alfa > charli));
  BOOST_CHECK(!(alfa == charli));
  BOOST_CHECK(charli > alfa);
  BOOST_CHECK(!(charli < alfa));

  charli.up();
  charli.left();
  BOOST_CHECK(alfa == charli);
  BOOST_CHECK(!(alfa < charli));
  BOOST_CHECK(!(alfa > charli));
}

BOOST_AUTO_TEST_CASE(test_case4) {
  brick_game::point alfa{j, i};
  auto echo = alfa - delta;
  BOOST_CHECK(echo == (brick_game::point{-1, -1}));
  echo = delta - alfa;
  BOOST_CHECK(echo == (brick_game::point{1, 1}));
  echo = echo + alfa;
  BOOST_CHECK(echo == delta);
}

BOOST_AUTO_TEST_SUITE_END()

/// test value
BOOST_AUTO_TEST_SUITE(test_value)

BOOST_AUTO_TEST_CASE(test_case1) {
  brick_game::value alfa;
  BOOST_CHECK(alfa == brick_game::Value::NONE);
  alfa = brick_game::Value::ONE;
  BOOST_CHECK(alfa == brick_game::Value::ONE);
  BOOST_CHECK(alfa != brick_game::Value::NONE);
}

BOOST_AUTO_TEST_CASE(test_case2) {
  brick_game::value bravo{brick_game::Value::TWO};
  BOOST_CHECK(bravo == brick_game::Value::TWO);
  brick_game::value alfa;
  alfa = bravo;
  BOOST_CHECK(alfa == bravo);
}

BOOST_AUTO_TEST_CASE(test_case3) {
  test_slot t_slot;
  brick_game::value alfa;
  QObject::connect(&alfa, &brick_game::value::changed, &t_slot,
                   &test_slot::connect_slot);
  alfa = brick_game::Value::ONE;
  BOOST_CHECK(t_slot.is_connected());
  BOOST_CHECK(!t_slot.is_connected());

  brick_game::value bravo{brick_game::Value::TWO};
  alfa = bravo;
  BOOST_CHECK(t_slot.is_connected());
}

BOOST_AUTO_TEST_SUITE_END()

/// test field
BOOST_AUTO_TEST_SUITE(test_field)

struct fixture_field {
  const int n = 9;
  const int m = 9;
  brick_game::field field{n, m};
};

BOOST_FIXTURE_TEST_CASE(test_check1, fixture_field) {
  BOOST_REQUIRE(field.size() == n);
  for (int i = 0; i < field.size(); ++i) {
    BOOST_REQUIRE(field[i].size() == m);
    for (int j = 0; j < field[i].size(); ++j) {
      BOOST_CHECK(field[i][j] == brick_game::Value::NONE);
    }
  }
}

BOOST_FIXTURE_TEST_CASE(test_check2, fixture_field) {
  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[i].size(); ++j) {
      field[i][j] = brick_game::Value::ONE;
    }
  }
  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[i].size(); ++j) {
      BOOST_CHECK(field[i][j] == brick_game::Value::ONE);
    }
  }
}

BOOST_FIXTURE_TEST_CASE(test_check3, fixture_field) {
  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[i].size(); ++j) {
      field[i][j] = brick_game::Value::ONE;
    }
  }
  field.erase_row_shift_down(2);
  for (auto &i : field[0]) {
    BOOST_CHECK(i == brick_game::Value::NONE);
    i = brick_game::Value::ONE;
  }
  field.erase_row_shift_down(0);
  for (auto &i : field[0]) {
    BOOST_CHECK(i == brick_game::Value::NONE);
    i = brick_game::Value::ONE;
  }
  field.erase_row_shift_down(field.size() - 1);
  for (auto &i : field[0]) {
    BOOST_CHECK(i == brick_game::Value::NONE);
    i = brick_game::Value::ONE;
  }
}

BOOST_FIXTURE_TEST_CASE(test_check4, fixture_field) {
  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[i].size(); ++j) {
      field[i][j] = brick_game::Value::ONE;
    }
  }
  field.erase_row_shift_up(2);
  for (auto &i : field[field.size() - 1]) {
    BOOST_CHECK(i == brick_game::Value::NONE);
    i = brick_game::Value::ONE;
  }
  field.erase_row_shift_up(0);
  for (auto &i : field[field.size() - 1]) {
    BOOST_CHECK(i == brick_game::Value::NONE);
    i = brick_game::Value::ONE;
  }
  field.erase_row_shift_up(field.size() - 1);
  for (auto &i : field[field.size() - 1]) {
    BOOST_CHECK(i == brick_game::Value::NONE);
    i = brick_game::Value::ONE;
  }
}

BOOST_FIXTURE_TEST_CASE(test_check5, fixture_field) {
  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[i].size(); ++j) {
      field[i][j] = brick_game::Value::ONE;
    }
  }
  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[i].size(); ++j) {
      ::QPoint alfa{j, i};
      BOOST_CHECK(field(brick_game::point{j, i}) == brick_game::Value::ONE);
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

/// test level
BOOST_AUTO_TEST_SUITE(level)

struct fixture_level {
  brick_game::level t_level;
};

BOOST_FIXTURE_TEST_CASE(test_case_1, fixture_level) { BOOST_CHECK(!t_level); }

BOOST_FIXTURE_TEST_CASE(test_case_2, fixture_level) {
  int number = 6;
  t_level = number;
  BOOST_CHECK(t_level == number);

  t_level += number;
  BOOST_CHECK(t_level == (number * 2));
}

BOOST_FIXTURE_TEST_CASE(test_case_3, fixture_level) {
  BOOST_CHECK(++t_level);

  int number = 7;
  t_level = number;
  BOOST_CHECK(++t_level == ++number);
}

BOOST_FIXTURE_TEST_CASE(test_case_4, fixture_level) {
  test_slot t_slot;
  ::QObject::connect(&t_level, &brick_game::level::send_level, &t_slot,
                     &test_slot::connect_slot);
  t_level = 5;
  BOOST_CHECK(t_slot.is_connected());
  t_level += 5;
  BOOST_CHECK(t_slot.is_connected());
  ++t_level;
  BOOST_CHECK(t_slot.is_connected());
  t_level++;
  BOOST_CHECK(t_slot.is_connected());
}

BOOST_AUTO_TEST_SUITE_END()

/// test score
BOOST_AUTO_TEST_SUITE(score)

struct fixture_score {
  brick_game::score t_score;
};

BOOST_FIXTURE_TEST_CASE(test_case_1, fixture_score) { BOOST_CHECK(!t_score); }

BOOST_FIXTURE_TEST_CASE(test_case_2, fixture_score) {
  int number = 6;
  t_score = number;
  BOOST_CHECK(t_score == number);

  t_score += number;
  BOOST_CHECK(t_score == (number * 2));
}

BOOST_FIXTURE_TEST_CASE(test_case_3, fixture_score) {
  BOOST_CHECK(++t_score);

  int number = 7;
  t_score = number;
  BOOST_CHECK(++t_score == ++number);
}

BOOST_FIXTURE_TEST_CASE(test_case_4, fixture_score) {
  test_slot t_slot;
  ::QObject::connect(&t_score, &brick_game::score::send_score, &t_slot,
                     &test_slot::connect_slot);
  t_score = 5;
  BOOST_CHECK(t_slot.is_connected());
  t_score += 5;
  BOOST_CHECK(t_slot.is_connected());
  ++t_score ;
  BOOST_CHECK(t_slot.is_connected());
  t_score ++;
  BOOST_CHECK(t_slot.is_connected());
}

BOOST_AUTO_TEST_SUITE_END()

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
