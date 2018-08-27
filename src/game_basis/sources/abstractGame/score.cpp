// score.cpp

#include "abstractGame/score.hpp"

brick_game::score::score(::QObject *parent) : ::QObject{parent}, score_{} {}

brick_game::score::operator unsigned() const { return score_; }

brick_game::score &brick_game::score::operator=(int number) {
  score_ = number;
  emit send_score(score_);
  return *this;
}

brick_game::score &brick_game::score::operator+=(int number) {
  score_ += number;
  emit send_score(score_);
  return *this;
}

brick_game::score &brick_game::score::operator++() {
  ++score_;
  emit send_score(score_);
  return *this;
}

brick_game::score &brick_game::score::operator++(int) {
  ++score_;
  emit send_score(score_);
  return *this;
}
