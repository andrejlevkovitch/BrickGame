// game_fon.hpp

#include <QWidget>

namespace brick_game {
/// simple class, which set fon-image for screen
class game_fon : public ::QWidget {
  Q_OBJECT
private:
  ::QImage fon_;

public:
  game_fon(::QWidget *parent = nullptr);
  void paintEvent(::QPaintEvent *pevent);
};
}; // namespace brick_game
