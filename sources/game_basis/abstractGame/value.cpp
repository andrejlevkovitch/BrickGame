// value.cpp

#include "abstractGame/value.hpp"

brick_game::value::value(Value value) : ::QObject{}, val_{value} {}

brick_game::value::value(const value &val) {
  this->val_ = val.val_;
}

brick_game::value &brick_game::value::operator=(const value &value) {
  this->val_ = value.val_;
  emit changed(val_);
  return *this;
}

brick_game::value &brick_game::value::operator=(Value value) {
  val_ = value;
  emit changed(val_);
  return *this;
}

brick_game::value::operator brick_game::Value() const {
  return val_;
}

bool brick_game::value::operator==(const Value value) const {
  return (val_ == value);
}

bool brick_game::value::operator!=(const Value value) const {
  return (val_ != value);
}
