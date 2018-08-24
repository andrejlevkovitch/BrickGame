// screen.hpp

#pragma once

#include "brick_game.hpp"
#include "general_window.hpp"
#include <QWidget>

namespace brick_game {
class pix;

class screen : public ::QWidget { // standart screen for brick game
  Q_OBJECT
  /// have friend brick_game::general_window
  friend general_window;

public:
  /**\return number of display digits for level*/
  static int LEVEL_DIGIN_COUNT();
  /**\return number of display digits for score*/
  static int SCORE_DIGIN_COUNT();

private:
  /// general field
  std::vector<std::vector<pix *>> general_pixarr_;
  /// mini field in screen corner
  std::vector<std::vector<pix *>> dop_pixarr_;

public:
  explicit screen(::QWidget *parent = nullptr);

protected:
  /**\return ::QWidget with general field*/
  ::QWidget *create_general_field();
  /**\return ::QWidget with mini field*/
  ::QWidget *create_dop_field();

signals:
  /// send if necessary clear all fields
  void clear_all() const;
  /**\brief set level on lcd display*/
  void set_level(int level) const;
  /**\brief set score on lcd display*/
  void set_score(int score) const;
};
}; // namespace brick_game
