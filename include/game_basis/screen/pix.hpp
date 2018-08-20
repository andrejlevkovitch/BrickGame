// pix.hpp

#pragma once

#include "brick_game.hpp"
#include <QLabel>

namespace brick_game {
class pix : public ::QLabel {
  Q_OBJECT
private:
    ::QPoint position_;
public:
  explicit pix(::QPoint pos, ::QWidget *parent = nullptr);

public slots:
  void change(::QPoint pos, Value value = Value::NONE);
};
}; // namespace brick_game
