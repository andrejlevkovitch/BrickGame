// pix.hpp

#pragma once

#include "brick_game.hpp"
#include <QLabel>

namespace brick_game {
  /**\brief element of brick_game::screen*/
class pix : public ::QLabel {
  Q_OBJECT
public:
  explicit pix(::QWidget *parent = nullptr);

public slots:
  /**\brief change color and some else
   * \param value changed value*/
  void change(Value value);
};
}; // namespace brick_game
