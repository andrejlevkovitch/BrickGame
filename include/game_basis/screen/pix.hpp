// pix.hpp

#pragma once

#include "brick_game.hpp"
#include <QLabel>

namespace brick_game {
class pix : public ::QLabel {
  Q_OBJECT
public:
  explicit pix(::QWidget *parent = nullptr);

public slots:
  void change(Value value = Value::NONE);
};
}; // namespace brick_game
