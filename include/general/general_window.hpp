// general_window.hpp

#pragma once

#include <QWidget>

namespace brick_game {
class screen;
class abstractGame;
class recordTable;
class player;
class pauseLog;
class endDialog;

/**\brief general class for BrickGame
 * \contains screen, game, recordTable, palyer end dialogs*/
class general_window : public ::QWidget {
  Q_OBJECT
private:
  screen *screen_;
  abstractGame *cur_game_;
  recordTable *record_table_;
  player *player_;
  pauseLog *pause_log_;
  endDialog *end_dialog_;

public:
  explicit general_window(::QWidget *parent = nullptr);
  ~general_window();

private:
  /**\brief handle event and send them to game*/
  void keyPressEvent(::QKeyEvent *event) override;

signals:
  /**\param game pointer to new game (in dynamic memory only!)*/
  void set_game_signal(brick_game::abstractGame *game);
  void start_game_signal();
  void finish_game_signal();

public slots:
  /**\brief slot, where set new game, and set new connects with element of the
   * BrickGame \param game pointer to new game (in dynamic memory only!)*/
  void set_game_slot(brick_game::abstractGame *game);
};
}; // namespace brick_game
