// abstractGame.cpp

#include "abstractGame/abstractGame.hpp"
#include "brick_game.hpp"

brick_game::point brick_game::abstractGame::END_FIELD() {
  static const brick_game::point retval{brick_game::FIELD_SIZE.width(),
                                        brick_game::FIELD_SIZE.height()};
  return retval;
}

brick_game::point brick_game::abstractGame::RBEGIN_FIELD() {
  static const brick_game::point retval{-1, -1};
  return retval;
}

brick_game::abstractGame::abstractGame(::QObject *parent) : ::QObject{parent}, soundless_{false} {}

bool brick_game::abstractGame::is_passible(const brick_game::point pos) const {
  if (pos < abstractGame::END_FIELD() && pos > RBEGIN_FIELD()) {
    return true;
  } else {
    return false;
  }
}

void brick_game::abstractGame::start_game_slot() { start_game(); }

void brick_game::abstractGame::finish_game_slot() { finish_game(); }

void brick_game::abstractGame::remove_sound_slot() {
  if (soundless_) {
    soundless_ = false;
  } else {
    soundless_ = true;
    player_.stop();
  }
};
