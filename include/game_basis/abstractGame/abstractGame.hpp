// abstractGame.hpp

#pragma once

#include "abstractGame/field.hpp"
#include "abstractGame/point.hpp"
#include "brick_game.hpp"
#include "general_window.hpp"
#include <QObject>

namespace brick_game {
class abstractGame : public ::QObject {
  Q_OBJECT
  friend general_window;

public:
  static brick_game::point END_FIELD();
  static brick_game::point RBEGIN_FIELD();

protected:
  field field_;
  field mini_field_;

public:
  explicit abstractGame(::QObject *parent = nullptr);
  virtual ::QString game_name() const = 0;

protected:
  virtual void customEvent(::QEvent *event) override = 0;
  bool is_passible(const brick_game::point pos) const;

public slots:
  virtual void start_game_slot() = 0;
  virtual void finish_game_slot() = 0;

signals:
  void end_game_signal(unsigned short level = 0, unsigned score = 0) const;
  void send_level(int level) const;
  void send_score(int score) const;
  void pause_signal(bool status) const;
  void activity() const;
};
}; // namespace brick_game
