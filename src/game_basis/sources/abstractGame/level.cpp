// level.cpp

#include "abstractGame/level.hpp"

brick_game::level::level(::QObject *parent) : ::QObject{parent}, level_{} {}

brick_game::level::operator unsigned short() const { return level_; }

brick_game::level &brick_game::level::operator=(int number) {
  level_ = number;
  emit send_level(level_);
  return *this;
}

brick_game::level &brick_game::level::operator+=(int number) {
  level_ += number;
  emit send_level(level_);
  return *this;
}

brick_game::level &brick_game::level::operator++() {
  ++level_;
  emit send_level(level_);
  return *this;
}

brick_game::level &brick_game::level::operator++(int) {
  ++level_;
  emit send_level(level_);
  return *this;
}
