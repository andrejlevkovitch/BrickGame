// screen.hpp

#pragma once

#include "brick_game.hpp"
#include "general_window.hpp"
#include <QWidget>

namespace brick_game {
class pix;

class screen : public ::QWidget { // standart screen for brick game
  Q_OBJECT
  friend general_window;

private:
  std::vector<std::vector<pix *>> general_pixarr_;
  std::vector<std::vector<pix *>> dop_pixarr_;

public:
  explicit screen(::QWidget *parent = nullptr);
  void restore();

private:
  ::QWidget *create_general_field();
  ::QWidget *create_dop_field();

signals:
  void clear_all(Value value = NONE) const;
  void reciver(Value value) const;
  void set_level(int level) const;
  void set_score(int score) const;
};
}; // namespace brick_game
