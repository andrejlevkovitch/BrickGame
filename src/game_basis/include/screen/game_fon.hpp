// game_fon.hpp

#include <QWidget>

namespace brick_game {
class game_fon : public ::QWidget {
  Q_OBJECT
private:
  ::QImage fon_;

public:
  game_fon(::QWidget *parent = nullptr);
  void paintEvent(::QPaintEvent *pevent);
};
}; // namespace brick_game
