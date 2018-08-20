// pauseEvent.cpp

#include "events/pauseEvent.hpp"
#include "brick_game.hpp"

brick_game::pauseEvent::pauseEvent()
    : QEvent{static_cast<Type>(brick_game::Event::pauseEvent)} {}
