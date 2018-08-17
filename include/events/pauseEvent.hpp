// pauseEvent.hpp

#pragma once

#include <QEvent>

namespace brick_game {
class pauseEvent : public ::QEvent {
public:
  pauseEvent();
};
}; // namespace brick_game
