// screen.hpp

#pragma once

#include "brick_game.hpp"
#include <QWidget>

namespace brick_game {
class screen : public ::QWidget { // standart screen for brick game
  Q_OBJECT
public:
  explicit screen(::QWidget *parent = nullptr);
  void restore();

public slots:
  void clear_field(::QSize size, ::QPoint pos = ::QPoint{}) const;

private:
  ::QWidget *create_field(::QSize size, ::QPoint pos = ::QPoint{}) const;

signals:
  void reciver(::QPoint pos, Value value) const;
  void set_level(int level) const;
  void set_score(int score) const;
};
}; // namespace brick_game
