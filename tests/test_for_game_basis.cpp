// test_for_game_basis.cpp

#include "abstractGame/field.hpp"
#include "abstractGame/point.hpp"
#include "abstractGame/simplExempl.hpp"
#include "abstractGame/value.hpp"
#include "brick_game.hpp"
#include <QPoint>
#include <cassert>
#include <cstdlib>
#include <iostream>

class test_point {
public:
  test_point() {
    using namespace brick_game;
    int i = 10, j = 15;
    point alfa{j, i};

    assert(alfa.getY() == i);
    assert(alfa.getX() == j);

    ::QPoint bravo{j, i};
    assert(alfa == bravo);
    assert(bravo == alfa);

    point charli{j, i};
    assert(alfa == charli);
    charli.down();
    assert(alfa != charli);
    assert(!(alfa < charli));
    assert(!(alfa > charli));
    assert(!(alfa == charli));
    assert(!(charli > alfa));
    assert(!(charli < alfa));

    charli.right();
    point delta{charli};
    assert(alfa != charli);
    assert(alfa < charli);
    assert(!(alfa > charli));
    assert(!(alfa == charli));
    assert(charli > alfa);
    assert(!(charli < alfa));

    charli.up();
    charli.left();
    assert(alfa == charli);
    assert(!(alfa < charli));
    assert(!(alfa > charli));

    point echo{alfa - delta};
    assert(echo == (point{-1, -1}));
    echo = delta - alfa;
    assert(echo == (point{1, 1}));
    echo = echo + alfa;
    assert(echo == delta);
    std::cerr << "in point all right" << std::endl;
  };
};

class test_simplExempl : public brick_game::simplExempl {
public:
  test_simplExempl() {
    assert(is_passible(simplExempl::REND_FIELD() + brick_game::point{1, 1}) ==
           true);
    assert(is_passible(simplExempl::REND_FIELD()) != true);
    assert(is_passible(simplExempl::END_FIELD()) != true);
    assert(is_passible(simplExempl::END_FIELD() - brick_game::point{1, 1}) ==
           true);

    assert(!game_name().isNull());
    std::cerr << "in simplExempl all right" << std::endl;
  };
};

class test_value {
public:
  test_value() {
    using namespace brick_game;
    value alfa;
    assert(alfa == Value::NONE);
    alfa = Value::ONE;
    assert(alfa == Value::ONE);
    assert(alfa != Value::NONE);
    value bravo{Value::TWO};
    assert(alfa != bravo);
    alfa = bravo;
    assert(alfa == bravo);
    value charli{alfa};
    assert(charli == bravo);
    std::cerr << "in value all right" << std::endl;
  };
};

class test_field : public brick_game::field {
public:
  test_field() : field{9, 9} {
    assert(this->size() == 9);
    for (int i = 0; i < this->size(); ++i) {
      assert((*this)[i].size() == 9);
      for (int j = 0; j < (*this)[i].size(); ++j) {
        assert((*this)[i][j] == brick_game::Value::NONE);
        (*this)[i][j] = brick_game::Value::ONE;
      }
    }
    for (int i = 0; i < this->size(); ++i) {
      assert((*this)[i].size() == 9);
      for (int j = 0; j < (*this)[i].size(); ++j) {
        assert((*this)[i][j] == brick_game::Value::ONE);
      }
    }
    this->erase_row_shift_down(2);
    for (auto &i : (*this)[0]) {
      assert(i == brick_game::Value::NONE);
      i = brick_game::Value::ONE;
    }
    this->erase_row_shift_up(2);
    for (auto &i : (*this)[this->size() - 1]) {
      assert(i == brick_game::Value::NONE);
      i = brick_game::Value::ONE;
    }
    for (int i = 0; i < this->size(); ++i) {
      for (int j = 0; j < (*this)[i].size(); ++j) {
        ::QPoint alfa{j, i};
        assert((*this)(brick_game::point{j, i}) == brick_game::Value::ONE);
      }
    }
    std::cerr << "in field all right" << std::endl;
  };
};

int main(int argc, char *argv[]) {
  test_point{};

  test_simplExempl{};

  test_value{};

  test_field{};

  return EXIT_SUCCESS;
}
