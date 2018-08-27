// brick_game.hpp

#pragma once

#include <QEvent>
#include <QPoint>
#include <QSize>
#include <QString>

namespace brick_game {
/// size of general field of BrickGame*/
const ::QSize FIELD_SIZE{10, 20};
/// size of mini scrien of BrickGame*/
const ::QSize MINI_FIELD_SIZE{4, 4};

/// valid values for class value*/
enum class Value {
  NONE,  ///< nothing, 0
  ONE,   ///< first value
  TWO,   ///< second value
  THREE, ///< thrird value
  FOUR,  ///< fourd value
  FIVE,  ///< fived value
  SIX,   ///< sixed value
  SIZE   ///< number of valid values
};
/// valid directions for event directionEvent*/
enum class Direction {
  UP,    ///< up direction
  DOWN,  ///< down direction
  RIGHT, ///< right direction
  LEFT,  ///< left direction
  SIZE   ///< number of valid values
};
/// types of events*/
enum class Event {
  pauseEvent = ::QEvent::User + 1, ///< type of pauseEvent
  directionEvent                   ///< type of directionEvent
};

#ifdef __linux__
/// path for game files (record tables etc.) linux*/
const ::QString HOME{::QString{getenv("HOME")} + ::QString{"/.brickgame/"}};
#elif _WIN32
/// path for game files (record tables etc.) windows*/
const ::QString HOME{::QString{getenv("LOCALAPPDATA")} +
                     ::QString{"/.brickgame/"}};
#endif
}; // namespace brick_game
