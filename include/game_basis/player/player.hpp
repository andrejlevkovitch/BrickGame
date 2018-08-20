// player.hpp

#pragma once

#include <QObject>
#include <QUrl>

class QMediaPlayer;

namespace brick_game {
class player : public ::QObject {
  Q_OBJECT
private:
  ::QMediaPlayer *player_;
  bool soundless_;
  ::QUrl begin_theme_;
  ::QUrl activity_;
  ::QUrl score_;
  ::QUrl level_up_;

public:
  player(::QObject *parent = nullptr);
  void set_sounds(const ::QUrl &begin_theme, const ::QUrl &activity,
                  const ::QUrl &score, const ::QUrl &level_up);

public slots:
  void remove_sound();
  void begin_theme();
  void activity();
  void score_changed();
  void level_up();
  void pause(bool);
  void stop();
};
}; // namespace brick_game
