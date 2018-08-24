// pauseEvent.hpp

#pragma once

#include <QEvent>

namespace brick_game {
/**\brief event of pause*/
class pauseEvent : public ::QEvent {
public:
  pauseEvent();
};
}; // namespace brick_game
