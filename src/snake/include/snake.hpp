// snake.hpp

#pragma once

#include "abstractGame/abstractGame.hpp"
#include "abstractGame/point.hpp"
#include "brick_game.hpp"
#include <QObject>
#include <QTimer>
#include <list>

namespace brick_game {
  /// just snake
class snake : public brick_game::abstractGame {
  Q_OBJECT
  Q_INTERFACES(brick_game::abstractGame)
  Q_PLUGIN_METADATA(IID abstractGame_ident FILE "abstractGame.json")

public:
  static std::chrono::milliseconds BEGIN_TIME_INTERVAL();
  /**\return score number for one feed*/
  static int SCORE_FOR_FEED();
  /**\return begin score number, which open new level*/
  static int BEGIN_LEVEL_FOR_SCORE();

private:
  std::list<point> snake_body_;
  Direction cur_direction_;
  ::QTimer timer_;
  std::chrono::milliseconds time_interval_;
  bool is_avalible_;
  bool is_active_;
  int last_level_score_;

public:
  snake(::QObject *parent = nullptr);
  ::QString game_name() const override;

protected:
  /**\brief overload method, which handle game events*/
  void customEvent(::QEvent *event) override;
  void pause();
  /**\brief method move snake body
   * \param pos new position of snake head*/
  bool motion(brick_game::point pos);
  bool move_up();
  bool move_down();
  bool move_right();
  bool move_left();
  /**\brief set new feed on screen*/
  void new_feed();
  /**\brief method increase level*/
  void level_up();

public slots:
  void start_game_slot() override;
  void finish_game_slot() override;
};
}; // namespace brick_game
