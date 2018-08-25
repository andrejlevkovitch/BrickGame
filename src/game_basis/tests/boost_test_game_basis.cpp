// boost_test_game_basis.cpp

#define BOOST_TEST_MODULE test
#include <boost/test/included/unit_test.hpp>

#include "abstractGame/field.hpp"
#include "abstractGame/point.hpp"
#include "abstractGame/simplExempl.hpp"
#include "abstractGame/value.hpp"
#include "test_slot.hpp"

/// test point
BOOST_AUTO_TEST_SUITE(test_suite1)

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
BOOST_AUTO_TEST_SUITE(test_suite2)

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
BOOST_AUTO_TEST_SUITE(test_suite3)

const int n = 9, m = 9;

BOOST_AUTO_TEST_CASE(test_check1) {
  brick_game::field field{n, m};

  BOOST_REQUIRE(field.size() == n);
  for (int i = 0; i < field.size(); ++i) {
    BOOST_REQUIRE(field[i].size() == m);
    for (int j = 0; j < field[i].size(); ++j) {
      BOOST_CHECK(field[i][j] == brick_game::Value::NONE);
    }
  }
}

BOOST_AUTO_TEST_CASE(test_check2) {
  brick_game::field field{n, m};
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

BOOST_AUTO_TEST_CASE(test_check3) {
  brick_game::field field{n, m};
  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[i].size(); ++j) {
      field[i][j] = brick_game::Value::ONE;
    }
  }
  field.erase_row_shift_down(2);
  for (auto &i : field[0]) {
    BOOST_CHECK(i == brick_game::Value::NONE);
  }
}

BOOST_AUTO_TEST_CASE(test_check4) {
  brick_game::field field{n, m};
  for (int i = 0; i < field.size(); ++i) {
    for (int j = 0; j < field[i].size(); ++j) {
      field[i][j] = brick_game::Value::ONE;
    }
  }
  field.erase_row_shift_up(2);
  for (auto &i : field[field.size() - 1]) {
    BOOST_CHECK(i == brick_game::Value::NONE);
  }
}

BOOST_AUTO_TEST_CASE(test_check5) {
  brick_game::field field{n, m};
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

/// test simplExempl
BOOST_AUTO_TEST_SUITE(test_suite4)
class test_simplExempl : public brick_game::simplExempl {
public:
  test_simplExempl(){};
  bool is_passible(const brick_game::point in) {
    return simplExempl::is_passible(in);
  }
} test_simplExempl;

BOOST_AUTO_TEST_CASE(test_case1) {
  BOOST_CHECK(test_simplExempl.is_passible(test_simplExempl::REND_FIELD()) !=
              true);
  BOOST_CHECK(test_simplExempl.is_passible(test_simplExempl::END_FIELD()) !=
              true);
}

BOOST_AUTO_TEST_CASE(test_case2) {
  BOOST_CHECK(test_simplExempl.is_passible(test_simplExempl::REND_FIELD() +
                                           brick_game::point{1, 1}) == true);
  BOOST_CHECK(test_simplExempl.is_passible(test_simplExempl::END_FIELD() -
                                           brick_game::point{1, 1}) == true);
}

BOOST_AUTO_TEST_CASE(test_case3) {
  BOOST_CHECK(!test_simplExempl.game_name().isNull());
}

BOOST_AUTO_TEST_SUITE_END()
