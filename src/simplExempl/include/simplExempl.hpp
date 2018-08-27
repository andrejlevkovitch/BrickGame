// simplExempl.hpp

#pragma once

#include "abstractGame/abstractGame.hpp"
#include "abstractGame/point.hpp"
#include "brick_game.hpp"

namespace brick_game {
/**\brief simple exemple of game*/
class simplExempl : public brick_game::abstractGame {
  Q_OBJECT
  Q_INTERFACES(brick_game::abstractGame)
  Q_PLUGIN_METADATA(IID abstractGame_ident FILE "abstractGame.json")

public:
  /**\return begin position of active element of general field*/
  static brick_game::point BEGIN_POS();

private:
  /**\brief current position of active element on general field*/
  brick_game::point cur_pos_;

public:
  explicit simplExempl(::QObject *parent = nullptr);
  /**\return name of game*/
  ::QString game_name() const override;

public slots:
  /**\brief override slot, which start the game if signal in*/
  void start_game_slot() override;
  /**\brief override slot, which finish the game if signal in*/
  void finish_game_slot() override;

protected:
  /**\brief override method, which handle custor events*/
  void customEvent(QEvent *event) override;
};
}; // namespace brick_game
