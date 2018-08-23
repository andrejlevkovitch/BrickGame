// field.hpp

#pragma once

#include "abstractGame/value.hpp"
#include <deque>
#include <vector>

namespace brick_game {
class field {
private:
  std::deque<std::vector<brick_game::value>> field_;

public:
  field(int rows, int cols, ::QObject *parrent = nullptr);
  void clear_all();
  std::vector<brick_game::value> &operator[](int row);
  const std::vector<brick_game::value> &operator[](int row) const;
  brick_game::value &operator()(::QPoint pos);
  const brick_game::value &operator()(::QPoint pos) const;
  size_t size() const;
  bool empty() const;
  void erase_row_shift_down(size_t row);
  void erase_row_shift_up(size_t row);
};
}; // namespace brick_game
