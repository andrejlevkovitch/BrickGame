// player.hpp

#pragma once

#include <QObject>
#include <QUrl>

class QMediaPlayer;

namespace brick_game {
  /**\brief sond player for the game*/
class player : public ::QObject {
  Q_OBJECT
private:
  ::QMediaPlayer *player_;
  /// if true - game without any sounds
  bool soundless_;
  /// start theme of game
  ::QUrl begin_theme_;
  /// sound of any activity
  ::QUrl activity_;
  /// sound of new score
  ::QUrl score_;
  /// sound of level up
  ::QUrl level_up_;

public:
  player(::QObject *parent = nullptr);
  /**\brief set some sounds for current game
   * \param begin_theme start theme of game
   * \param activity sound of any activity
   * \param score sound of new score
   * \param level_up sound of level up*/
  void set_sounds(const ::QUrl &begin_theme, const ::QUrl &activity,
                  const ::QUrl &score, const ::QUrl &level_up);

public slots:
  /// set soundless true, and off all sounds
  void remove_sound();
  /// play begin_theme_
  void begin_theme();
  ///  play activity_
  void activity();
  /// play score_
  void score_changed();
  /// play level_up_
  void level_up();
  /// set player on pause
  void pause(bool);
  /// stoping player
  void stop();
};
}; // namespace brick_game
