// brick.hpp

#pragma once

#include "abstractGame/point.hpp"
#include "brick_game.hpp"
#include <QObject>
#include <vector>

namespace brick_game {
class tetramino;
class brick : public ::QObject {
  Q_OBJECT
  friend tetramino;

public:
  enum BrickType {
    T_BRICK,
    O_BRICK,
    L_BRICK,
    J_BRICK,
    Z_BRICK,
    S_BRICK,
    I_BRICK,
    SIZE_BRICKS
  };
  static point DEF_CENTER();

private:
  std::vector<std::vector<brick_game::Value>> field_;
  BrickType type_;
  point center_;

public:
  explicit brick(::QObject *parent = nullptr);
  bool turn();
  brick &operator=(brick &&rhs);
  brick &operator=(const brick &rhs);
};
}; // namespace tetris
