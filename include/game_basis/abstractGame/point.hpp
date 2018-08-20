// point.hpp

#pragma once

#include <QPoint>

namespace brick_game {
class point {
private:
  int y_;
  int x_;

public:
  point(int x, int y);
  bool operator==(const point &rhs) const;
  point operator-(const point &rhs) const;
  point operator+(const point &rhs) const;
  bool operator>(const point &rhs) const;
  bool operator<(const point &rhs) const;
  operator ::QPoint () const;
  void down();
  void up();
  void right();
  void left();
  int getY() const;
  int getX() const;
};
}; // namespace tetris
