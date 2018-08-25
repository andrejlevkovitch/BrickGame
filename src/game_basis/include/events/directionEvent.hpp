// directionEvent.hpp

#pragma once

#include "brick_game.hpp"
#include <QEvent>

namespace brick_game {
  /**\brief event, which created if put direction key*/
class directionEvent : public ::QEvent {
private:
  Direction direction_;

public:
  /**\param direction current direction*/
  directionEvent(Direction direction);
  /**\return current direction*/
  Direction direction() const;
};
}; // namespace brick_game
