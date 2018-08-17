// brick_game.hpp

#pragma once

#include <QEvent>
#include <QPoint>
#include <QSize>

namespace brick_game {
const ::QSize FIELD_SIZE{10, 20};    // size of general field
const ::QSize MINI_FIELD_SIZE{4, 4}; // size of mini field

const ::QPoint MINI_SCR_BGN{FIELD_SIZE.width(), 0};

enum Value { NONE, ONE, TWO, THREE, FOUR, FIVE, SIX, SIZE };
enum class Direction { UP, DOWN, RIGHT, LEFT };
enum class Event { pauseEvent = ::QEvent::User + 1, directionEvent };

const int LEVEL_DIGIN_COUNT{2};
const int SCORE_DIGIN_COUNT{6};
}; // namespace brick_game
