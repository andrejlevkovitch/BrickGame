// field.hpp

#pragma once

#include "abstractGame/value.hpp"
#include <deque>
#include <vector>

namespace brick_game {
/**\brief game field of BrickGame*/
class field {
private:
  std::deque<std::vector<brick_game::value>> field_;

public:
  /**\param rows height of field
   * \param cols width of field
   * \param parrent pointr to parent*/
  field(int rows, int cols, ::QObject *parrent = nullptr);
  /**\brief clear all field (Value::NONE)*/
  void clear_all();
  /**\param row number of row of field
   * \warning don't check input value!
   * \return row of field with this number*/
  std::vector<brick_game::value> &operator[](int row);
  /**\brief const version of operator[]
   * \warning don't check input value!*/
  const std::vector<brick_game::value> &operator[](int row) const;
  /**\brief analogue of operator[] for points
   * \warning don't check input value!
   * \param pos point of elemnt on the field
   * \return reference to value*/
  brick_game::value &operator()(::QPoint pos);
  /**\brief const version of operator()(::QPoint)
   * \warning don't check input value!*/
  const brick_game::value &operator()(::QPoint pos) const;
  /**\return number of rows in this field*/
  size_t size() const;
  /**\return true if this field haven't any rows, or false if have*/
  bool empty() const;
  /**\brief this method clear some row, and shift all rows above the row down
   * \param row number of row, which you want to clean*/
  void erase_row_shift_down(size_t row);
  /**\brief this method clear some row, and shift all rows below the row up
   * \param row number of row, which you want to clean*/
  void erase_row_shift_up(size_t row);
};
}; // namespace brick_game
