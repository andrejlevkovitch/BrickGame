// abstractGame.cpp

#include "abstractGame/abstractGame.hpp"
#include "brick_game.hpp"

#include <QDebug>

brick_game::point brick_game::abstractGame::END_FIELD() {
  static const brick_game::point retval{brick_game::FIELD_SIZE.width(),
                                        brick_game::FIELD_SIZE.height()};
  return retval;
}

brick_game::point brick_game::abstractGame::RBEGIN_FIELD() {
  static const brick_game::point retval{-1, -1};
  return retval;
}

brick_game::abstractGame::abstractGame(::QObject *parent)
    : ::QObject{parent}, field_{FIELD_SIZE.height(), FIELD_SIZE.width()},
      mini_field_{MINI_FIELD_SIZE.height(), MINI_FIELD_SIZE.width()} {
  ::qDebug() << "create abstractGame";
}

bool brick_game::abstractGame::is_passible(const brick_game::point pos) const {
  if (pos < abstractGame::END_FIELD() && pos > RBEGIN_FIELD()) {
    return true;
  } else {
    return false;
  }
}
