// field.cpp

#include "abstractGame/field.hpp"
#include "brick_game.hpp"

#include <QDebug>

brick_game::field::field(int rows, int cols, ::QObject *parent)
    : field_(rows, decltype(field_)::value_type(cols, value{})) {}

void brick_game::field::clear_all() {
  for (auto &i : field_) {
    for (auto &j : i) {
      j = Value::NONE;
    }
  }
}

std::vector<brick_game::value> &brick_game::field::operator[](int row) {
  return field_[row];
}

const std::vector<brick_game::value> &brick_game::field::
operator[](int row) const {
  return field_[row];
}

brick_game::value &brick_game::field::operator()(::QPoint pos) {
  return field_[pos.y()][pos.x()];
}

const brick_game::value &brick_game::field::operator()(::QPoint pos) const {
  return field_[pos.y()][pos.x()];
}

size_t brick_game::field::size() const { return field_.size(); }

bool brick_game::field::empty() const { return field_.empty(); }

void brick_game::field::erase_row_shift_down(size_t row) {
  if (row >= field_.size()) {
    return;
  }
  while (row > 0) {
    for (int i = 0; i < field_[row].size(); ++i) {
      field_[row][i] = field_[row - 1][i];
    }
    --row;
  }
  for (auto &i : *field_.begin()) {
    i = Value::NONE;
  }
}

void brick_game::field::erase_row_shift_up(size_t row) {
  if (row >= field_.size()) {
    return;
  }
  while (row < field_.size()) {
    for (int i = 0; i < field_[row].size(); ++i) {
      field_[row][i] = field_[row + 1][i];
    }
    ++row;
  }
  for (auto &i : *field_.rbegin()) {
    i = Value::NONE;
  }
}
