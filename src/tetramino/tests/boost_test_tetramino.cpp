// boost_test_tetramino.cpp

#define BOOST_TEST_MODULE test_module_tetramino
#include <boost/test/included/unit_test.hpp>

#include "test_slot.hpp"
#include "tetramino.hpp"

BOOST_AUTO_TEST_SUITE(tetramino)

struct fixture_tetramino : public brick_game::tetramino {};

BOOST_FIXTURE_TEST_CASE(delete_solutions, fixture_tetramino) {
  std::cerr << "test starting";
  const int first_row{5};
  for (auto &i : field_[first_row]) {
    i = brick_game::Value::ONE;
  }
  fixture_tetramino::delete_solutions();
  BOOST_CHECK(score_);
  BOOST_CHECK(!level_);
  BOOST_CHECK(score_ == PRICE_FOR_LINE(1));
  for (auto &i : field_[first_row]) {
    BOOST_CHECK(i == brick_game::Value::NONE);
  }

  score_ = level_ = 0;
  if (LINES_TO_NEXT_LEVEL() < field_.size()) {
    for (int i = 0; i < LINES_TO_NEXT_LEVEL() / 2; ++i) {
      for (auto &j : field_[i]) {
        j = brick_game::Value::ONE;
      }
    }
    fixture_tetramino::delete_solutions();
    for (int i = 0; i < LINES_TO_NEXT_LEVEL() - LINES_TO_NEXT_LEVEL() / 2;
         ++i) {
      for (auto &j : field_[i]) {
        j = brick_game::Value::ONE;
      }
    }
    fixture_tetramino::delete_solutions();
  }
  BOOST_CHECK(score_);
  BOOST_CHECK(level_);
  BOOST_CHECK(score_ == PRICE_FOR_LINE(4) * 2);
  BOOST_CHECK(level_ == 1);
}

BOOST_FIXTURE_TEST_CASE(gam_name, fixture_tetramino) {
  BOOST_CHECK(!fixture_tetramino::game_name().isNull());
}

BOOST_FIXTURE_TEST_CASE(set_next_brick, fixture_tetramino) {
  fixture_tetramino::reverse_next_brick();
  bool all_right{false};
  for (int i{}; i < mini_field_.size(); ++i) {
    for (auto &j : mini_field_[i]) {
      if (j != brick_game::Value::NONE) {
        all_right = true;
        break;
      }
      if (all_right) {
        break;
      }
    }
  }
  BOOST_CHECK(all_right);

  fixture_tetramino::reverse_next_brick();
  all_right = true;
  for (int i{}; i < mini_field_.size(); ++i) {
    for (auto &j : mini_field_[i]) {
      if (j != brick_game::Value::NONE) {
        all_right = false;
        break;
      }
      if (!all_right) {
        break;
      }
    }
  }
  BOOST_CHECK(all_right);
}

BOOST_FIXTURE_TEST_CASE(end_game_signal, fixture_tetramino) {
  const int a = 1;
  const int b = 500;

  test_slot t_slot;
  connect(&t_slot, &test_slot::test_signal, this,
          &brick_game::abstractGame::finish_game_slot);
  connect(this, &brick_game::abstractGame::end_game_signal, &t_slot,
          &test_slot::test_date_slot);

  fixture_tetramino::level_ = a;
  fixture_tetramino::score_ = b;
  emit t_slot.test_signal();

  BOOST_CHECK(t_slot.is_connected());
  BOOST_CHECK(t_slot.a_ = a);
  BOOST_CHECK(t_slot.b_ = b);
}

BOOST_FIXTURE_TEST_CASE(start_game_signal, fixture_tetramino) {
  for (int i = 0; i < 3; ++i) {
    fixture_tetramino::start_game_slot();

    bool all_right = false;
    for (int i{}; i < mini_field_.size(); ++i) {
      for (auto &j : mini_field_[i]) {
        if (j != brick_game::Value::NONE) {
          all_right = true;
          break;
        }
        if (all_right) {
          break;
        }
      }
    }
    BOOST_CHECK(all_right);
  }
}

BOOST_AUTO_TEST_SUITE_END()
