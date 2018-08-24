// point.cpp

#include "abstractGame/point.hpp"

brick_game::point::point(int x, int y) : y_{y}, x_{x} {}

bool brick_game::point::operator==(const point &rhs) const {
  return (this->y_ == rhs.y_ && this->x_ == rhs.x_) ? true : false;
}

bool brick_game::point::operator!=(const point &rhs) const {
  return (this->y_ != rhs.y_ || this->x_ != rhs.x_) ? true : false;
}

brick_game::point brick_game::point::operator-(const point &rhs) const {
  return point(this->x_ - rhs.x_, this->y_ - rhs.y_);
}

brick_game::point brick_game::point::operator+(const point &rhs) const {
  return point(this->x_ + rhs.x_, this->y_ + rhs.y_);
}

bool brick_game::point::operator<(const point &rhs) const {
  return (y_ < rhs.y_ && x_ < rhs.x_) ? true : false;
}

bool brick_game::point::operator>(const point &rhs) const {
  return (y_ > rhs.y_ && x_ > rhs.x_) ? true : false;
}

brick_game::point::operator ::QPoint() const {
  return ::QPoint{getX(), getY()};
}

void brick_game::point::up() { --y_; }

void brick_game::point::down() { ++y_; }

void brick_game::point::right() { ++x_; }

void brick_game::point::left() { --x_; }

int brick_game::point::getY() const { return y_; }

int brick_game::point::getX() const { return x_; }
