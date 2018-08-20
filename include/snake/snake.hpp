// snake.hpp

#pragma once

#include <QObject>
#include <vector>
#include "brick_game.hpp"
#include "abstractGame/point.hpp"
#include "abstractGame/abstractGame.hpp"
#include <QTimer>
#include <list>

namespace brick_game {
class snake : public brick_game::abstractGame {
  Q_OBJECT
  public:
    static std::chrono::milliseconds BEGIN_TIME_INTERVAL();
private:
  std::vector<std::vector<Value>> field_;
  std::list<point> snake_body_;
  Direction cur_direction_;
  ::QTimer timer_;
  std::chrono::milliseconds time_interval_;
  unsigned short level_;
  unsigned score_;
  bool is_avalible_;
  bool is_active_;

public:
  snake(::QObject *parent = nullptr);
  ::QString game_name() const override;

private:
  void customEvent(::QEvent *event) override;
  Value &value_of(point);
  void pause();
  bool move_up();
  bool move_down();
  bool move_right();
  bool move_left();
  void new_feed();

public slots:
  void start_game_slot() override;
  void finish_game_slot() override;
};
}; // namespace brick_game
