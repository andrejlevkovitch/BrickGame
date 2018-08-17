// simplExempl.hpp

#include "abstractGame/abstractGame.hpp"
#include "abstractGame/point.hpp"
#include "brick_game.hpp"

namespace brick_game {
class simplExempl : public brick_game::abstractGame {
  Q_OBJECT
public:
  static brick_game::point BEGIN_POS();

private:
  brick_game::point cur_pos_;

public:
  explicit simplExempl(::QObject *parent = nullptr);
  void start_game() override;
  void finish_game() override;

private:
  void customEvent(QEvent *event) override;
};
}; // namespace brick_game
