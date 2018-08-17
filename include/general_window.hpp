// general_window.hpp

#pragma once

#include <QWidget>

namespace brick_game {
  class screen;
  class abstractGame;
class general_window : public ::QWidget {
  Q_OBJECT
  private:
    screen *screen_;
    abstractGame *cur_game_;
public:
  explicit general_window(::QWidget *parent = nullptr);
  ~general_window();
private:
  void keyPressEvent(::QKeyEvent *event) override;
};
}; // namespace brick_game
