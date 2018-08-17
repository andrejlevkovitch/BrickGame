// pix.cpp

#include "screen/pix.hpp"

brick_game::pix::pix(::QPoint pos, ::QWidget *parent)
    : ::QLabel{parent}, position_{pos} {
  this->setSizePolicy(::QSizePolicy::Policy::Fixed,
                      ::QSizePolicy::Policy::Fixed);
  this->setDisabled(true);
}

::QSize brick_game::pix::sizeHint() const { return ::QSize{30, 30}; }

void brick_game::pix::change(::QPoint pos, Value value) {
  if (pos == position_) {
    if (value == Value::NONE) {
      if (this->isEnabled()) {
        this->setDisabled(true);
      }
    } else {
      if (!this->isEnabled()) {
        this->setEnabled(true);
      }
    }
  }
}
