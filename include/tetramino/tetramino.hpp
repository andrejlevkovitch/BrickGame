// tetramino.hpp

#pragma once

#include "tetramino/brick.hpp"
#include "abstractGame/abstractGame.hpp"
#include <QObject>
#include <QTimer>
#include <chrono>
#include <deque>
#include <vector>

namespace brick_game {
class tetramino : public brick_game::abstractGame {
  Q_OBJECT
public:
  static std::chrono::milliseconds BEGIN_TIME_DOWN();
  static unsigned short LINES_TO_NEXT_LEVEL();
  static unsigned short PRICE_FOR_LINE(unsigned short n_line);
  static unsigned short TIME_DIVIDED();
  static const point &BEG_POSITION();

private:
  std::deque<std::vector<Value>> field_;
  brick cur_brick_;
  brick next_brick_;
  ::QTimer timer_;
  point cur_brick_position_;
  std::chrono::milliseconds time_interval_;
  unsigned score_;
  unsigned short level_;
  unsigned short lines_;
  bool active_;
  bool is_avalibale_;

public:
  explicit tetramino(::QObject *parent = nullptr);

private:
  void start_game() override;
  void finish_game() override;
  void customEvent(::QEvent *event) override;

  void pause();

  point left_up_brick_corner() const;
  point right_down_brick_corner() const;
  bool is_passible() const;
  void delete_solutions();
  void reverse_cur_brick();
  void send_next_brick() const;
  void cleare_next_brick() const;

  void rotade_cur_brick();
  void set_brick_down();
  void set_brick_right();
  void set_brick_left();
};
}; // namespace tetris
