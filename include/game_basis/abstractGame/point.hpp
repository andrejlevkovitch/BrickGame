// point.hpp

#pragma once

#include <QPoint>

namespace brick_game {
  /**\brief this is point, which have operace less and greter*/
class point {
private:
  int y_;
  int x_;

public:
  /**\param x,y koords of point*/
  point(int x, int y);
  /**\return true if points have same koords*/
  bool operator==(const point &rhs) const;
  /**\return true if pointa have diffirent koords*/
  bool operator!=(const point &rhs) const;
  /**\return point with koords = lhs.y - rhs.y, lhs.x - rhs.x*/
  point operator-(const point &rhs) const;
  /**\return point with koords = lhs.y + rhs.y, lhs.x + rhs.x*/
  point operator+(const point &rhs) const;
  /**\return true if lhs point is in second quarter relativaly rhs*/
  bool operator>(const point &rhs) const;
  /**\return true if lhs point is in fourth quarter relativaly rhs*/
  bool operator<(const point &rhs) const;
  /**\brief reduction to ::QPoint type*/
  operator ::QPoint () const;
  /**\brief move point down on y-koord*/
  void down();
  /**\brief move point up on y-koord*/
  void up();
  /**\brief move point right on x-koord*/
  void right();
  /**\brief move point left on x-koord*/
  void left();
  /**\return y-koord of point*/
  int getY() const;
  /**\return x-koord of point*/
  int getX() const;
};
}; // namespace tetris
