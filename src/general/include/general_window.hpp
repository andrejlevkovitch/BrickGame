// general_window.hpp

#pragma once

#include <QWidget>

class QStatusBar;
class QMenu;

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
  ::QStatusBar *status_bar_;
  ::QMenu *game_menu_;

public:
  explicit general_window(::QWidget *parent = nullptr);
  ~general_window();
  /**\brief method, where set new game, and set new connects with element of the
   * BrickGame \param game pointer to new game*/
  void set_game(brick_game::abstractGame *game);

protected:
  /**\brief handle event and send them to game*/
  void keyPressEvent(::QKeyEvent *event) override;
  /**\brief load all plugins from directory*/
  void loadPlugins();
  /**\brief add to menu new action starts the game
   * \param plugin input plugin*/
  void addToMenu(::QObject *plugin);

protected slots:
  /**\brief open pauseLog*/
  void pause(bool status);
  /**\brief open endDialog*/
  void end_game(unsigned short level, unsigned score);

signals:
  void start_game_signal();
  void finish_game_signal();
};
}; // namespace brick_game
