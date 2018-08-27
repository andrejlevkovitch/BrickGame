// tetramino.hpp

#pragma once

#include "abstractGame/abstractGame.hpp"
#include "brick.hpp"
#include <QObject>
#include <QTimer>
#include <chrono>

namespace brick_game {
class tetramino : public brick_game::abstractGame {
  Q_OBJECT
  Q_INTERFACES(brick_game::abstractGame)
  Q_PLUGIN_METADATA(IID abstractGame_ident FILE "abstractGame.json")

public:
  static std::chrono::milliseconds BEGIN_TIME_DOWN();
  static unsigned short LINES_TO_NEXT_LEVEL();
  static unsigned short PRICE_FOR_LINE(unsigned short n_line);
  static unsigned short TIME_DIVIDED();
  static const point &BEG_POSITION();

private:
  brick cur_brick_;
  brick next_brick_;
  ::QTimer timer_;
  point cur_brick_position_;
  std::chrono::milliseconds time_interval_;
  unsigned short lines_;
  bool active_;
  bool is_avalibale_;

public:
  explicit tetramino(::QObject *parent = nullptr);

public slots:
  void start_game_slot() override;
  void finish_game_slot() override;

protected:
  ::QString game_name() const override;
  void customEvent(::QEvent *event) override;

  void pause();

  point left_up_brick_corner() const;
  point right_down_brick_corner() const;
  bool is_passible() const;
  void delete_solutions();
  void reverse_cur_brick();
  void set_next_brick();
  void cleare_next_brick();

  void rotade_cur_brick();
  void set_brick_down();
  void set_brick_right();
  void set_brick_left();
};
}; // namespace brick_game
