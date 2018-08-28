// brick.hpp

#pragma once

#include "abstractGame/point.hpp"
#include "brick_game.hpp"
#include <QObject>
#include <vector>

namespace brick_game {
class tetramino;
/// just briek of tetramino
class brick : public ::QObject {
  Q_OBJECT
  friend tetramino;

public:
  /// types of briecks
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
  /**\return begin center of brieck.
   * Always (0, 1)*/
  static point DEF_CENTER();

private:
  std::vector<std::vector<brick_game::Value>> field_;
  BrickType type_;
  point center_;

public:
  explicit brick(::QObject *parent = nullptr);
  /**\brief function turn brick relative to the center
   * \return true if turn was be, and false if not (last can be if brick dasn't
   * turn - O_BRICK, exm)*/
  bool turn();
  brick &operator=(brick &&rhs);
  brick &operator=(const brick &rhs);
};
}; // namespace brick_game
