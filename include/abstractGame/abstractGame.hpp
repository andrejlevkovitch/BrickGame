// abstractGame.hpp

#pragma once

#include "abstractGame/point.hpp"
#include "brick_game.hpp"
#include <QObject>
#include <QMediaPlayer>

namespace brick_game {
class abstractGame : public ::QObject {
  Q_OBJECT
public:
  static brick_game::point END_FIELD();
  static brick_game::point RBEGIN_FIELD();

protected:
  bool soundless_;
  ::QMediaPlayer player_;

public:
  explicit abstractGame(::QObject *parent = nullptr);

private:
  virtual void start_game() = 0;
  virtual void finish_game() = 0;

protected:
  virtual void customEvent(::QEvent *event) override = 0;
  bool is_passible(const brick_game::point pos) const;

public slots:
  void start_game_slot();
  void finish_game_slot();
  void remove_sound_slot();

signals:
  void changed(::QPoint pos, Value value) const;
  void end_game_signal() const;
  void send_level(int level) const;
  void send_score(int score) const;
};
}; // namespace brick_game
