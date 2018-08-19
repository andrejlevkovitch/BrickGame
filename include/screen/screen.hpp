// screen.hpp

#pragma once

#include "brick_game.hpp"
#include <QWidget>

namespace brick_game {
class abstractGame;
class pauseLog;
class endDialog;
class recordTable;

class screen : public ::QWidget { // standart screen for brick game
  Q_OBJECT
private:
  abstractGame *cur_game_;
  bool is_running_;
  pauseLog *pause_log_;
  endDialog *end_dialog_;

public:
  explicit screen(::QWidget *parent = nullptr);
  void set_game(brick_game::abstractGame *game);
  void set_record_table(brick_game::recordTable *record_table);

public slots:
  void clear_field(::QSize size, ::QPoint pos = ::QPoint{}) const;

private:
  void keyPressEvent(::QKeyEvent *event) override;
  ::QWidget *create_field(::QSize size, ::QPoint pos = ::QPoint{}) const;

signals:
  void start_game_signal();
  void finish_game_signal();
  void reciver(::QPoint pos, Value value) const;
  void set_level(int level) const;
  void set_score(int score) const;
};
}; // namespace brick_game
