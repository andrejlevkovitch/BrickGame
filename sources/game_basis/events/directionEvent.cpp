// directionEvent.cpp

#include "events/directionEvent.hpp"

brick_game::directionEvent::directionEvent(Direction direction)
    : ::QEvent{static_cast<Type>(brick_game::Event::directionEvent)},
      direction_{direction} {}

brick_game::Direction brick_game::directionEvent::direction() const {
  return direction_;
}
