// directionEvent.hpp

#pragma once

#include "brick_game.hpp"
#include <QEvent>

namespace brick_game {
class directionEvent : public ::QEvent {
private:
  Direction direction_;

public:
  directionEvent(Direction direction);
  Direction direction() const;
};
}; // namespace brick_game
