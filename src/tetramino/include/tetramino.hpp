// tetramino.hpp

#pragma once

#include "abstractGame/abstractGame.hpp"
#include "brick.hpp"
#include <QObject>
#include <QTimer>
#include <chrono>

namespace brick_game {
/// tetramino game
class tetramino : public brick_game::abstractGame {
  Q_OBJECT
  Q_INTERFACES(brick_game::abstractGame)
  Q_PLUGIN_METADATA(IID abstractGame_ident FILE "abstractGame.json")

public:
  static std::chrono::milliseconds BEGIN_TIME_DOWN();
  /**\return value of lines, which need destroy for next level*/
  static unsigned short LINES_TO_NEXT_LEVEL();
  /**\return number of score for destroying lines
   * \param n_line number of destroying lines*/
  static unsigned short PRICE_FOR_LINE(unsigned short n_line);
  /**\return time divider*/
  static unsigned short TIME_DIVIDED();
  /**\return start position of new brick*/
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

  /**\return left up brick corner of current brick*/
  point left_up_brick_corner() const;
  /**\return right down brick corner of current brick*/
  point right_down_brick_corner() const;
  /**\brief check can current brick be on the field
   * \return true if nothing hinder, and false if not*/
  bool is_passible() const;
  /**\brief destroy all completed lines, up the score and level*/
  void delete_solutions();
  /**\brief set current brick on the field if it not ther, and erase it, if current brick is on the field*/
  void reverse_cur_brick();
  /**\brief reverse function for mini field*/
  void reverse_next_brick();

  void rotade_cur_brick();
  void set_brick_down();
  void set_brick_right();
  void set_brick_left();
};
}; // namespace brick_game
