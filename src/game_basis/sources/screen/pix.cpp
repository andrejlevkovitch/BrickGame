// pix.cpp

#include "screen/pix.hpp"

brick_game::pix::pix(::QWidget *parent) : ::QLabel{parent} {
  this->setDisabled(true);
}

void brick_game::pix::change(Value value) {
  switch (value) {
  case Value::NONE:
    this->setStyleSheet("background-color : rgba(255, 255, 255, 0)");
    if (this->isEnabled()) {
      this->setDisabled(true);
    }
    break;
  case Value::ONE:
    this->setStyleSheet("background : blue");
    if (!this->isEnabled()) {
      this->setEnabled(true);
    }
    break;
  case Value::TWO:
    this->setStyleSheet("background : green");
    if (!this->isEnabled()) {
      this->setEnabled(true);
    }
    break;
  case Value::THREE:
    this->setStyleSheet("background : cyan");
    if (!this->isEnabled()) {
      this->setEnabled(true);
    }
    break;
  case Value::FOUR:
    this->setStyleSheet("background : red");
    if (!this->isEnabled()) {
      this->setEnabled(true);
    }
    break;
  case Value::FIVE:
    this->setStyleSheet("background : yellow");
    if (!this->isEnabled()) {
      this->setEnabled(true);
    }
    break;
  case Value::SIX:
    this->setStyleSheet("background : magenta");
    if (!this->isEnabled()) {
      this->setEnabled(true);
    }
    break;
  default:
    if (!this->isEnabled()) {
      this->setEnabled(true);
    }
    break;
  }
}
