// abstractGame.hpp

#pragma once

#include "abstractGame/field.hpp"
#include "abstractGame/point.hpp"
#include "brick_game.hpp"
#include <QObject>

namespace brick_game {
class general_window;
/**\brief abstract class - basis for some game*/
class abstractGame : public ::QObject {
  Q_OBJECT
    /**\brief have friend brick_game::general_window*/
  friend general_window;

public:
  /**\brief
   * if some point less then this return value, then it is in fourth quarter
   * \return proint end of general field (otside of field)*/
  static brick_game::point END_FIELD();
  /**\brief
   * if some point greater then this return value, then if is in second quarter
   * \return point rend of general field (otside of field)*/
  static brick_game::point REND_FIELD();

protected:
  /**\brief general field of BrickGame*/
  field field_;
  /**\brief mini field of BrickGame*/
  field mini_field_;

public:
  /**\param parent pointer to parent*/
  explicit abstractGame(::QObject *parent = nullptr);
  /**\brief abstract method, name of custom game
   * \return string with name of game*/
  virtual ::QString game_name() const = 0;

protected:
  /**\brief abstract method, where handles events
   * \param event input event*/
  virtual void customEvent(::QEvent *event) override = 0;
  /**\brief passible or not set point in general field
   * \param pos input position
   * \return true if it passible and false if not*/
  bool is_passible(const brick_game::point pos) const;

public slots:
  /**\brief abstract slot, which run the game if signal in*/
  virtual void start_game_slot() = 0;
  /**\brief abstract slot, which finish the game if signal in*/
  virtual void finish_game_slot() = 0;

signals:
  /**\brief signal, which talk, what game finished.
   * Send level and score for record table
   * \param level current level
   * \param score current score*/
  void end_game_signal(unsigned short level = 0, unsigned score = 0) const;
  /**\brief set level on the screen
   * \param level current level*/
  void send_level(int level) const;
  /**\brief set score on the screen
   * \param score current score */
  void send_score(int score) const;
  /**\brief signal, which talk pause is active or not
   * \param status if pause active set true, if not - false*/
  void pause_signal(bool status) const;
  /**\brief signal for player, send if want hear some sound*/
  void activity() const;
};
}; // namespace brick_game
